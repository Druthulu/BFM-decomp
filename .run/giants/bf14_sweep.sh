#!/bin/bash
# bf14_sweep.sh <base.c> "<tag>|<lever> [lever...]" ...   -> one line per variant, parallel
cd /home/musashi/bfm-decomp
BASE="$1"; shift
run() {
  local spec="$1"; local tag="${spec%%|*}"; local lv="${spec#*|}"
  local wd=".run/giants/bf14_sw/$tag"
  mkdir -p "$wd"
  python3 .run/giants/bf14_mk.py "$BASE" "$wd/v.c" $lv 2>"$wd/mk.err" || { echo "$tag :: MK-FAIL $(tail -2 $wd/mk.err|tr '\n' ' ')"; return; }
  bash .run/giants/bf14_score.sh "$wd/v.c" "$wd/w" "$tag"
}
export -f run; export BASE
printf '%s\n' "$@" | xargs -P 8 -I{} bash -c 'run "$@"' _ {}
