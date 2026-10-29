import json
from pathlib import Path

OUT = Path("/logs/verifier")

def emit(reward, valid, reason, subscores):
    reward = round(min(1.0, max(0.0, reward)), 6)
    flat = {"reward": reward, "score": reward, "valid": int(valid)}
    flat.update({k: round(float(v), 6) for k, v in subscores.items()})   # numbers only
    OUT.mkdir(parents=True, exist_ok=True)
    (OUT / "reward.json").write_text(json.dumps(flat))
    (OUT / "reward.txt").write_text(f"{reward}\n")
    (OUT / "details.json").write_text(json.dumps({
        "subscores": [{"name": k, "score": float(v)} for k, v in subscores.items()],
        "additional_data": {"reason": reason}}))
    raise SystemExit(0 if reward > 0 else 1)

def score():
    try:
        ev = json.loads((OUT / "evidence.json").read_text())
    except Exception as e:
        emit(0.0, 0, "no evidence: %s" % e, {})
    if not ev.get("runtime_ok", False):
        emit(0.0, 0, "runtime unavailable: " + str(ev.get("runtime_error")), {})
    total, passed = ev["cases_total"], ev["cases_passed"]
    subs = {"cases_passed": passed, "cases_total": total}
    for name, (p, t) in sorted(ev.get("categories", {}).items()):
        subs["cat_" + name] = p / t if t else 0.0
    if ev["cheat_detected"] or not ev["build_ok"]:
        subs["pass_fraction"] = 0.0
        emit(0.0, 1, ev["gate_reason"], subs)
    frac = passed / total                                  # fixed denominator
    subs["pass_fraction"] = frac
    emit(frac, 1, "%d of %d sealed programs correct" % (passed, total), subs)

try:
    score()
except SystemExit:
    raise
except Exception as e:   # never leave without reward files
    emit(0.0, 0, "scoring crashed: %r" % (e,), {})
