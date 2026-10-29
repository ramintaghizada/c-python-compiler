#!/usr/bin/env bash
# Local self-check: compiles every program in /app/examples with your compiler,
# assembles (as) and links (ld) the result, runs it, and compares stdout and exit code.
# Usage: /app/check.sh [name-substring]
cd "$(dirname "$0")" || exit 1
LIB=/usr/lib/x86_64-linux-gnu
tmp=$(mktemp -d); pass=0; total=0
for c in examples/*${1:-}*.c; do
  n=$(basename "$c" .c); total=$((total+1))
  if ! python3 ccomp/main.py "$c" -o "$tmp/$n.s" 2>"$tmp/$n.err"; then
    echo "FAIL $n (compile): $(head -c 200 "$tmp/$n.err")"; continue; fi
  if ! as "$tmp/$n.s" -o "$tmp/$n.o" 2>"$tmp/$n.lerr" || \
     ! ld -o "$tmp/$n" -dynamic-linker /lib64/ld-linux-x86-64.so.2 $LIB/crt1.o $LIB/crti.o \
          "$tmp/$n.o" -L$LIB -lc $LIB/crtn.o 2>>"$tmp/$n.lerr"; then
    echo "FAIL $n (assemble/link): $(head -c 200 "$tmp/$n.lerr")"; continue; fi
  timeout 10 "$tmp/$n" > "$tmp/$n.out"; rc=$?
  if [ "$rc" = "$(cat examples/$n.rc)" ] && cmp -s "$tmp/$n.out" "examples/$n.out"; then
    pass=$((pass+1)); else echo "FAIL $n (wrong output or exit code $rc)"; fi
done
echo "passed $pass / $total  ($((100*pass/total))%)"
rm -rf "$tmp"
