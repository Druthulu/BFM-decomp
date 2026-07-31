#!/usr/bin/env bash
# treelock.sh — THE mutex for tree-writing campaigns. Source it or wrap a command with it.
#
#   tools/treelock.sh <name> <command…>       # acquire, run, release (even on failure/kill)
#   tools/treelock.sh --status                # who holds it
#
# WHY (P30, twice in one session — the second time I caused it myself):
# `src/`, `config/`, `asm/` and `build/` are ONE shared mutable state. Any two of {gate_stage,
# dedup_propagate, family_sweep, jtbl_family_bank, make clean/extract/check} running at once can
# interleave writes and leave the fleet incoherent — and a killed writer performs NO undo, so the
# damage outlives the process.
#
# The first attempt at a guard was `while pgrep -f dedup_propagate; do sleep; done`. That is
# STRUCTURALLY WRONG and it failed within the hour: a CAMPAIGN is a LOOP of short-lived processes
# (15 sequential dedup_propagate invocations), so between every pair there is a window with no
# matching process. A parallel gate polled during one of those windows, saw "clear", and started —
# then a `make clean` deleted asm/ under the still-running campaign. Result: 63 of 140 binaries
# failed check-all and every uncommitted bank had to be reverted.
#
# The lesson, stated generally: **guard the CAMPAIGN, not the process.** Presence-of-a-process is a
# sampling test on a gappy signal; a lock file is a statement of intent that spans the gaps.
# Uses flock(1) — held for the WHOLE wrapped command, released by the kernel on exit or kill.
set -uo pipefail
REPO="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
LOCK="$REPO/.run/tree.lock"
mkdir -p "$(dirname "$LOCK")"

if [ "${1:-}" = "--status" ]; then
  if flock -n "$LOCK" true 2>/dev/null; then echo "tree lock: FREE"; else
    echo "tree lock: HELD by -> $(cat "$LOCK.owner" 2>/dev/null || echo '(unknown)')"; fi
  exit 0
fi

NAME="${1:?usage: treelock.sh <name> <command...>}"; shift
[ $# -gt 0 ] || { echo "treelock: no command given" >&2; exit 2; }

exec 9>"$LOCK"
if ! flock -w "${TREELOCK_WAIT:-14400}" 9; then
  echo "treelock: timed out waiting for the tree (held by $(cat "$LOCK.owner" 2>/dev/null))" >&2
  exit 75
fi
echo "$NAME pid=$$ since=$(date +%H:%M:%S)" > "$LOCK.owner"
trap 'rm -f "$LOCK.owner"' EXIT
echo "[treelock] acquired by $NAME"
"$@"
rc=$?
echo "[treelock] released by $NAME (rc=$rc)"
exit $rc
