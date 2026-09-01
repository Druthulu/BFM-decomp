#!/bin/bash
# R22 clean-fleet verify. EXCLUSIVE BY CONSTRUCTION.
#
# `make clean` deletes asm/ AND build/. Three separate times this session that raced a live lane:
#   * a subagent authorised to splice src/800.c -> a FALSE "212 passed, 1 failed" red;
#   * a drafting agent reading asm/md_MAIN_011 -> "asm/md_MAIN_011 is MISSING from the tree";
#   * another reading asm/md_MAIN_003 -> same, it survived only by finding an old snapshot.
# Drafting agents never WRITE src/, which is why "check for a dirty tree" does not catch them —
# they DEPEND on state this operation destroys. R54: a guard that is not running is not a guard,
# so this refuses instead of relying on the operator remembering.
cd /home/musashi/bfm-decomp
BUSY=$(find .run/S68o1 .run/S68m1 -maxdepth 2 -type d -name 'scratch_*' -newermt '-6 minutes' 2>/dev/null | head -5)
if [ -n "$BUSY" ] && [ -z "$R22_FORCE" ]; then
  echo "R22 REFUSED — drafting scratch touched in the last 6 minutes (agents are live and read asm/):"
  echo "$BUSY" | sed 's/^/  /'
  echo "Drain the lane, or set R22_FORCE=1 if you know every agent is done."
  echo "R22 DONE (refused)"
  exit 2
fi
echo "R22 START $(date -Is)"
make clean            ; echo "CLEAN rc=$?"
make extract-all      ; echo "EXTRACT rc=$?"
make check-all        ; echo "CHECK rc=$?"
echo "R22 DONE $(date -Is)"
