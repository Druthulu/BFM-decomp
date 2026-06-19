#!/bin/bash
# auto_status.sh — show the unattended run's heartbeat + recent checkpoints (remote check-in).
cd "$(dirname "$0")/.."
echo "=== heartbeat (.run/auto/heartbeat.json) ==="
[ -f .run/auto/heartbeat.json ] && cat .run/auto/heartbeat.json || echo "(no heartbeat yet)"
echo; echo "=== STOP requested? ==="; [ -f .run/auto/STOP ] && echo "YES (.run/auto/STOP present)" || echo "no"
echo; echo "=== last 8 phase-16 checkpoints ==="
git log --oneline -8 --grep='phase-16' 2>/dev/null || git log --oneline -8
echo; echo "=== supervisor tail ==="; tail -6 .run/auto/supervisor.log 2>/dev/null || echo "(none)"
