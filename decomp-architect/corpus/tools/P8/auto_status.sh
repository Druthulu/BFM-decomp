#!/bin/bash
# auto_status.sh — show the unattended run's state (grinder + worker) for a remote check-in.
cd "$(dirname "$0")/.."
echo "=== grinder heartbeat (.run/auto/grinder_heartbeat.json) ==="
[ -f .run/auto/grinder_heartbeat.json ] && cat .run/auto/grinder_heartbeat.json || echo "(no grinder heartbeat yet)"
echo; echo "=== worker orchestrator state (.run/auto/orch_state.json) ==="
[ -f .run/auto/orch_state.json ] && cat .run/auto/orch_state.json || echo "(worker loop not started)"
echo; echo "=== legacy auto_driver heartbeat ==="
[ -f .run/auto/heartbeat.json ] && cat .run/auto/heartbeat.json || echo "(none)"
echo; echo "=== STOP requested? ==="; [ -f .run/auto/STOP ] && echo "YES — run is halting (rm .run/auto/STOP to resume)" || echo "no (running)"
echo; echo "=== backlog (open near-misses, ranked) ==="
[ -f .run/backlog.jsonl ] && .venv/bin/python tools/backlog.py show -n 12 2>/dev/null || echo "(backlog empty)"
echo; echo "=== last 12 phase-21 checkpoints ==="
git log --oneline -12 --grep='phase-21' 2>/dev/null || git log --oneline -12
echo; echo "=== supervisor tail ==="; tail -6 .run/auto/supervisor.log 2>/dev/null || echo "(none)"
echo; echo "=== running daemons ==="; pgrep -af 'grinder.py|auto_supervisor' | sed 's/ -c .*//' | head -4 || echo "(none)"
