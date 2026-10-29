#!/usr/bin/env bash
# Background task timer daemon. Writes /app/.timer/* so the agent can pace itself.
set -u

TIMER_DIR="/app/.timer"
PID_FILE="$TIMER_DIR/timer.pid"
mkdir -p "$TIMER_DIR"

if [ -f "$PID_FILE" ]; then
    EXISTING_PID=$(cat "$PID_FILE" 2>/dev/null)
    if [ -n "$EXISTING_PID" ] && kill -0 "$EXISTING_PID" 2>/dev/null; then
        exit 0
    fi
fi
echo $$ > "$PID_FILE"

# The platform injects TASK_BUDGET_SECS when it arms the timer in the task
# sandbox. Without it (e.g. inside an image BUILD container), refuse to start:
# a defaulted budget once held image builds hostage for its full duration.
if [ -z "${TASK_BUDGET_SECS:-}" ]; then
    echo "[TIMER] TASK_BUDGET_SECS not set — not starting" >&2
    rm -f "$PID_FILE"
    exit 0
fi

START_EPOCH=$(date +%s)
BUDGET_SECS="$TASK_BUDGET_SECS"
echo "$START_EPOCH" > "$TIMER_DIR/start_epoch"
echo "$BUDGET_SECS" > "$TIMER_DIR/budget_secs"

while true; do
    NOW=$(date +%s)
    ELAPSED=$((NOW - START_EPOCH))
    REMAINING=$((BUDGET_SECS - ELAPSED))
    [ "$REMAINING" -lt 0 ] && REMAINING=0
    echo "$REMAINING" > "$TIMER_DIR/remaining_secs"
    echo "$ELAPSED" > "$TIMER_DIR/elapsed_secs"

    if [ "$REMAINING" -le 1800 ] && [ ! -f "$TIMER_DIR/alert_30min" ]; then
        touch "$TIMER_DIR/alert_30min"; echo "[TIMER] 30 minutes remaining" >&2
    fi
    if [ "$REMAINING" -le 600 ] && [ ! -f "$TIMER_DIR/alert_10min" ]; then
        touch "$TIMER_DIR/alert_10min"; echo "[TIMER] 10 minutes remaining" >&2
    fi
    if [ "$REMAINING" -le 300 ] && [ ! -f "$TIMER_DIR/alert_5min" ]; then
        touch "$TIMER_DIR/alert_5min"; echo "[TIMER] 5 minutes remaining" >&2
    fi
    [ "$REMAINING" -le 0 ] && { echo "[TIMER] Time expired" >&2; break; }
    sleep 10
done
