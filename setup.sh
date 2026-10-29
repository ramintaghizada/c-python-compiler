#!/usr/bin/env bash
# Local Docker check, run from the task root folder (the one with task.toml).
# Usage: ./run_local.sh [nop|oracle|both]     (default: both)
# Mirrors the harness: image built from environment/, tests mounted at /tests,
# reference at /solution, logs collected under ./.logs/<mode>/verifier/.
set -euo pipefail
cd "$(dirname "$0")"
MODE="${1:-both}"
IMG=ccomp-task-local

docker build -t "$IMG" environment/

run_mode() {
  local mode="$1" pre=""
  rm -rf ".logs/$mode"; mkdir -p ".logs/$mode"
  [ "$mode" = oracle ] && pre="bash /solution/solve.sh && "
  docker run --rm \
    -e TASK_BUDGET_SECS=3600 \
    -v "$PWD/tests:/tests:ro" \
    -v "$PWD/solution:/solution:ro" \
    -v "$PWD/.logs/$mode:/logs" \
    "$IMG" bash -c "${pre}bash /tests/test.sh" || true
  echo "== $mode: reward $(cat ".logs/$mode/verifier/reward.txt" 2>/dev/null || echo MISSING)"
  python3 - "$mode" <<'PY'
import json, sys
e = json.load(open(".logs/%s/verifier/evidence.json" % sys.argv[1]))
print("   passed %s / %s; first failures: %s" % (e["cases_passed"], e["cases_total"], e["failed"][:5]))
PY
}

case "$MODE" in
  nop)    run_mode nop ;;
  oracle) run_mode oracle ;;
  both)   run_mode nop; run_mode oracle ;;
  *) echo "usage: $0 [nop|oracle|both]"; exit 2 ;;
esac
echo "Expected: nop = 0.0, oracle = 1.0. Leak check:"
grep -rln "compute_reward\|solve.sh" environment/ && echo "LEAK" || echo "  no leaks"
