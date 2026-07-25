#!/bin/bash
# bf14_score.sh <draft.c> <workdir> [tag] -> "TAG :: len=N d=+X mism=M shape=P% L1=Q"
cd /home/musashi/bfm-decomp
SRC="$1"; WD="$2"; TAG="${3:-$(basename $1 .c)}"
bash .run/giants/bf14_cc.sh "$SRC" "$WD" >/dev/null 2>"$WD.err" || { echo "$TAG :: COMPILE-FAIL $(tail -4 $WD.err|tr '\n' ' ')"; exit 1; }
A=$(python3 .run/giants/bf14_full.py "$WD/t.o" --count 2>/dev/null)
H=$(python3 .run/giants/bf14_hist.py "$WD/t.o" --sum 2>/dev/null)
S=$(python3 .run/giants/bf14_shape.py "$WD/t.o" 0 2>/dev/null | head -1 | grep -oP 'SHAPE-aligned \d+/\d+ = \K[0-9.]+')
echo "$TAG :: $A | shape=$S% | $H"
