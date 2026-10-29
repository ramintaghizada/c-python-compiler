#!/usr/bin/env python3
"""Evidence collection. Every step that touches candidate-controlled content
(compile, assemble, link, run) executes as an unprivileged user in a scratch
directory that holds only a copy of the source file; sealed data stays root-only."""
import glob, json, os, resource, shutil, signal, subprocess, tempfile

CASES = "/tests/cases"
CAND_DIR, CAND = "/app/ccomp", "/app/ccomp/main.py"
PY, AS, LD = "/usr/bin/python3", "/usr/bin/as", "/usr/bin/ld"
LIB = "/usr/lib/x86_64-linux-gnu"
ENV = {"PATH": "/usr/bin:/bin", "LANG": "C", "HOME": "/tmp"}
EVIDENCE = "/logs/verifier/evidence.json"
NOBODY = 65534


def finish(ev):
    """Single writer of evidence.json (atomic)."""
    names = ev.pop("_names", [])
    failed = {n for n, _ in ev["failed"]}
    cats = {}
    for n in names:
        c = cats.setdefault(n.rsplit("_", 1)[0], [0, 0])
        c[1] += 1
        c[0] += n not in failed
    ev["categories"] = cats
    os.makedirs(os.path.dirname(EVIDENCE), exist_ok=True)
    tmp = EVIDENCE + ".tmp"
    with open(tmp, "w") as f:
        json.dump(ev, f)
    os.replace(tmp, EVIDENCE)


def limits():
    os.setgroups([]); os.setgid(NOBODY); os.setuid(NOBODY)
    resource.setrlimit(resource.RLIMIT_FSIZE, (64 << 20, 64 << 20))
    resource.setrlimit(resource.RLIMIT_CORE, (0, 0))
    resource.setrlimit(resource.RLIMIT_NPROC, (512, 512))


def run(cmd, timeout, cwd, out_fd=None):
    """Run as the unprivileged user. stdout, if wanted, is an fd that root opened inside a
    root-only directory; root never opens any path inside the candidate-writable cwd."""
    p = subprocess.Popen(cmd, cwd=cwd, env=ENV, stdin=subprocess.DEVNULL,
                         stdout=out_fd if out_fd is not None else subprocess.DEVNULL,
                         stderr=subprocess.DEVNULL, preexec_fn=limits, start_new_session=True)
    try:
        return p.wait(timeout=timeout)
    except subprocess.TimeoutExpired:
        try: os.killpg(p.pid, signal.SIGKILL)       # process group, never by name
        except ProcessLookupError: pass
        p.wait()
        return None


def reap():
    """Kill leftover processes owned by the unprivileged user, one PID at a time.
    Selection is by owner uid only, so the harness and verifier are never touched."""
    for _ in range(3):                       # repeat in case something forks while dying
        found = False
        for entry in os.listdir("/proc"):
            if not entry.isdigit():
                continue
            try:
                if os.stat("/proc/" + entry).st_uid == NOBODY:
                    os.kill(int(entry), signal.SIGKILL)
                    found = True
            except OSError:
                pass
        if not found:
            break


def bad_candidate_files():
    if os.path.islink(CAND_DIR):
        return CAND_DIR
    for root, dirs, files in os.walk(CAND_DIR):
        if "__pycache__" in root: continue
        for fn in dirs + files:
            p = os.path.join(root, fn)
            try:
                if os.path.islink(p): return p
                if os.path.isfile(p):
                    if os.path.getsize(p) > (2 << 20): return p
                    with open(p, "rb") as f:
                        if f.read(4) == b"\x7fELF": return p
            except OSError: pass
    return None

def scan_filesystem_for_cheats():
    """Virtual sistem və taymer qovluqlarını tamamilə ötürərək infra xətasını (freeze) həll edir."""
    search_paths = ["/app", "/tmp", "/opt"]
    for s_path in search_paths:
        if not os.path.exists(s_path): continue
        for root, dirs, files in os.walk(s_path):
            # KRİTİK: İnfra xətasına (freeze) səbəb olan virtual qovluqları dərhal ötürürük
            if any(p in root for p in ["/proc", "/sys", "/dev", ".timer", "__pycache__", "v_"]):
                continue
            for file in files:
                if file.startswith("test_") or "test" in root: continue
                fp = os.path.join(root, file)
                try:
                    if os.path.isfile(fp) and not os.path.islink(fp):
                        with open(fp, "rb") as f:
                            header = f.read(4)
                            if header == b"\x7fELF":
                                content = f.read(1024 * 10) # Yalnız ilk 10KB oxu
                                if b"cc1" in content or b"gcc" in content:
                                    if not fp.startswith(("/usr", "/bin")):
                                        return True, f"Illegal binary at {fp}"
                except Exception:
                    pass
    return False, ""



def make_readable():
    """chmod a+rX over the (already scanned, symlink-free) candidate tree."""
    paths = [CAND_DIR]
    for root, dirs, files in os.walk(CAND_DIR):
        paths += [os.path.join(root, x) for x in dirs + files]
    for p in paths:
        try:
            if os.path.islink(p): continue
            m = os.stat(p).st_mode
            new = m | 0o444
            if os.path.isdir(p) or m & 0o111: new |= 0o111
            os.chmod(p, new & 0o7777)
        except OSError: pass


def main():
    ev = {"runtime_ok": True, "runtime_error": "", "build_ok": True, "cheat_detected": False,
          "gate_reason": "", "cases_total": 0, "cases_passed": 0, "failed": []}


    
    # 🎯 BURADA ÇAĞIRIRIQ: Anti-cheat yoxlamasını ən başda icra et
    has_cheat, reason = scan_filesystem_for_cheats()
    if has_cheat:
        ev.update(cheat_detected=True, gate_reason=reason)
        return finish(ev) # Əgər hiylə tapılsa, dərhal yekunlaşdır və 0 xal ver

    

    names = sorted(os.path.basename(p)[:-2] for p in glob.glob(CASES + "/*.c"))
    ev["cases_total"] = len(names); ev["_names"] = names
    if not names:
        ev.update(runtime_ok=False, runtime_error="no sealed cases found"); return finish(ev)
    if not os.path.isfile(CAND):
        ev.update(build_ok=False, gate_reason="/app/ccomp/main.py missing"); return finish(ev)
    for path, mode in (("/tests", 0o700), ("/logs/verifier", 0o755)):
        try: os.chmod(path, mode)
        except OSError: pass
    bad = bad_candidate_files()
    if bad:
        ev.update(cheat_detected=True, gate_reason="binary, symlink or oversized file under /app/ccomp: " + bad)
        return finish(ev)
    make_readable()

    work = tempfile.mkdtemp(prefix="v_"); os.chmod(work, 0o755)
    outdir = os.path.join(work, "_out"); os.mkdir(outdir); os.chmod(outdir, 0o700)   # root only
    try:
        for n in names:
            d = os.path.join(work, n); os.mkdir(d); os.chmod(d, 0o777)
            src = os.path.join(d, n + ".c")
            shutil.copyfile(os.path.join(CASES, n + ".c"), src); os.chmod(src, 0o644)
            s, o, exe = (os.path.join(d, n + x) for x in (".s", ".o", ""))
            outp = os.path.join(outdir, n + ".stdout")
            try:
                if run([PY, "-E", "-s", CAND, src, "-o", s], 60, d) != 0 or not os.path.isfile(s):
                    ev["failed"].append([n, "compile"]); continue
                try:      # read-only scan; refuse symlinks so nothing outside the case dir is read
                    sfd = os.open(s, os.O_RDONLY | os.O_NOFOLLOW)
                    with os.fdopen(sfd, "rb") as f:
                        asm = f.read(64 << 20)
                except OSError:
                    ev["failed"].append([n, "compile"]); continue
                if b'.ident\t"GCC' in asm or b'.ident "GCC' in asm:
                    ev["cheat_detected"] = True; ev["gate_reason"] = "assembly produced by gcc (%s)" % n
                    break
                if run([AS, s, "-o", o], 60, d) != 0:
                    ev["failed"].append([n, "assemble"]); continue
                if run([LD, "-o", exe, "-dynamic-linker", "/lib64/ld-linux-x86-64.so.2",
                        LIB + "/crt1.o", LIB + "/crti.o", o, "-L" + LIB, "-lc", LIB + "/crtn.o"], 60, d) != 0:
                    ev["failed"].append([n, "link"]); continue
                fd = os.open(outp, os.O_WRONLY | os.O_CREAT | os.O_EXCL | os.O_NOFOLLOW, 0o600)
                try:
                    rc = run([exe], 30, d, out_fd=fd)
                finally:
                    os.close(fd)
                want_out = open(os.path.join(CASES, n + ".out"), "rb").read()
                want_rc = int(open(os.path.join(CASES, n + ".rc")).read())
                with open(outp, "rb") as f:
                    got = f.read(len(want_out) + 1)
                if rc == want_rc and got == want_out:
                    ev["cases_passed"] += 1
                else:
                    ev["failed"].append([n, "wrong output"])
            finally:
                reap()
    finally:
        shutil.rmtree(work, ignore_errors=True)
    finish(ev)


try:
    main()
except Exception as e:  # harness-side fault: still leave evidence behind
    finish({"runtime_ok": False, "runtime_error": "collector crashed: %r" % (e,), "build_ok": True,
            "cheat_detected": False, "gate_reason": "", "cases_total": 0, "cases_passed": 0, "failed": []})
