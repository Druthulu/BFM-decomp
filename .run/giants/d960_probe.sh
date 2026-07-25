#!/bin/bash
# d960_probe.sh <draft.c> [tag] -> prints "TAG :: ..."
cd /home/musashi/bfm-decomp
SRC="$1"; TAG="${2:-$(basename $1 .c)}"
OUT=$(timeout 1800 python3 tools/match_one.py func_8017D960 --c "$SRC" \
      --asm-subdir asm/ov_SC03_090/nonmatchings/ov_SC03_090_jr_8017CA80 2>&1 | head -2)
echo "$TAG :: $(echo "$OUT" | head -1)"
echo "$TAG :: $(echo "$OUT" | sed -n 2p)"
