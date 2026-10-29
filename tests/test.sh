#!/usr/bin/env bash
# Evidence and anti-cheat only; compute_reward.py decides the score.
# No `set -e`: compute_reward.py must always run so the reward files always exist.
set -uo pipefail
export PATH=/usr/bin:/bin
unset PYTHONPATH PYTHONHOME LD_PRELOAD LD_LIBRARY_PATH BASH_ENV
mkdir -p /logs/verifier
rm -f /logs/verifier/evidence.json
/usr/bin/python3 -E -s /tests/collect.py        # writes /logs/verifier/evidence.json itself
exec /usr/bin/python3 -E -s /tests/compute_reward.py
