#!/bin/bash
# bf14_score.sh <draft.c> <workdir> [tag]
cd /home/musashi/bfm-decomp
SRC="$1"; WD="$2"; TAG="${3:-$(basename $1 .c)}"
bash .run/giants/bf14_cc.sh "$SRC" "$WD" >/dev/null 2>"$WD.err" || { echo "$TAG :: COMPILE-FAIL $(tail -5 $WD.err|tr '\n' ' ')"; exit 1; }
A=$(python3 .run/giants/bf14_full.py "$WD/t.o" --count)
echo "$TAG :: $A"
