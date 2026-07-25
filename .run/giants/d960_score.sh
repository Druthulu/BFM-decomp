#!/bin/bash
# d960_score.sh <draft.c> <workdir> [tag]  -> "TAG :: mine=N target=3338 M mismatched | aligned X%"
cd /home/musashi/bfm-decomp
SRC="$1"; WD="$2"; TAG="${3:-$(basename $1 .c)}"
bash .run/giants/d960_cc.sh "$SRC" "$WD" >/dev/null 2>"$WD.err" || { echo "$TAG :: COMPILE-FAIL $(tail -3 $WD.err|tr '\n' ' ')"; exit 1; }
A=$(python3 .run/giants/d960_full.py "$WD/t.o" --count)
B=$(python3 .run/giants/b3_align.py "$WD/t.o" asm/ov_SC03_090/nonmatchings/ov_SC03_090_jr_8017CA80/func_8017D960.s 0 2>/dev/null | grep 'aligned-identical' | sed 's/^ *//' | tr '\n' ' ')
echo "$TAG :: $A || $B"
