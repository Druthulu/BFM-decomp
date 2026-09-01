#!/bin/bash
# R22 clean-fleet verify. EXCLUSIVE BY CONSTRUCTION, and it CLEARS THE DEFERRED-CHECK DEBT.
#
# `make clean` deletes asm/ AND build/. Four separate times in P31 S68 that raced a live lane:
#   * a subagent authorised to splice src/800.c -> a FALSE "212 passed, 1 failed" red;
#   * three drafting agents reporting "asm/<binary> is MISSING from the tree" mid-draft (one
#     survived only by finding an old snapshot under .run/s46 and still returned MATCH -- luck).
# Drafting agents never WRITE src/, which is exactly why a dirty-tree check does not catch them:
# they DEPEND on state this operation destroys. R54 -- a guard that is not running is not a guard,
# so this REFUSES rather than relying on the operator remembering.
#
# `.run/R22_DEBT` is written by `parallel_gate --r22` whenever it SKIPS its own clean-fleet check
# for the same reason. A deferred check that nobody tracks reads as "verified" at session close
# (R32's corrected form), so it is a file, the session checkpoint quotes it, and only a GREEN run
# here deletes it.
set -u
cd /home/musashi/bfm-decomp

BUSY=$(find .run/S68o1 .run/S68m1 .run/*wave* -maxdepth 2 -type d -name 'scratch_*' \
       -newermt '-6 minutes' 2>/dev/null | head -5)
if [ -n "$BUSY" ] && [ -z "${R22_FORCE:-}" ]; then
  echo "R22 REFUSED — drafting scratch touched in the last 6 minutes (agents are live and read asm/):"
  echo "$BUSY" | sed 's/^/  /'
  echo "Drain the lane, or set R22_FORCE=1 if you know every agent is done."
  echo "R22 DONE (refused)"
  exit 2
fi

echo "R22 START $(date -Is)"
make clean       ; echo "CLEAN rc=$?"
make extract-all ; echo "EXTRACT rc=$?"
CHECK_OUT=$(make check-all 2>&1); CHECK_RC=$?
echo "$CHECK_OUT" | tail -40
echo "CHECK rc=$CHECK_RC"

# Clear the debt ONLY on a genuinely green fleet — read the summary line, not the exit code alone,
# because a failed build leaves the PREVIOUS binary on disk and sha1sum then reads green (R53).
if [ "$CHECK_RC" -eq 0 ] && grep -q 'check-all: .*0 failed' <<< "$CHECK_OUT"; then
  if [ -f .run/R22_DEBT ]; then
    echo "cleared .run/R22_DEBT ($(wc -l < .run/R22_DEBT) deferred check(s)) — fleet verified green"
    rm -f .run/R22_DEBT
  fi
else
  echo "R22 NOT GREEN — .run/R22_DEBT left standing"
fi
echo "R22 DONE $(date -Is)"
