#!/bin/bash
# c730_probe.sh <draft.c> [tag] -> prints "TAG :: <line1>" / "TAG :: <line2>"
cd /home/musashi/bfm-decomp
SRC="$1"; TAG="${2:-$(basename $1 .c)}"
OUT=$(timeout 900 python3 tools/match_one.py func_8017C730 --c "$SRC" \
      --asm-subdir asm/ov_SC03_010/nonmatchings/ov_SC03_010_jr_8017AE2C 2>&1 | head -2)
echo "$TAG :: $(echo "$OUT" | head -1)"
echo "$TAG :: $(echo "$OUT" | sed -n 2p)"
