#!/bin/bash
# bf14_sw2.sh <base.c> "<tag>|<lever> [lever...]" ...  -> one line per variant, parallel
# uses bf14_mk2.py (round-2 levers).  Reports raw mismatch count + length.
cd /home/musashi/bfm-decomp
BASE="$1"; shift
run() {
  local spec="$1"; local tag="${spec%%|*}"; local lv="${spec#*|}"
  local wd=".run/giants/bf14_sw2/$tag"
  mkdir -p "$wd"
  python3 .run/giants/bf14_mk2.py "$BASE" "$wd/v.c" $lv 2>"$wd/mk.err" || { printf '%-22s :: MK-FAIL %s\n' "$tag" "$(tail -2 $wd/mk.err|tr '\n' ' ')"; return; }
  bash .run/giants/bf14_cc.sh "$wd/v.c" "$wd/w" >/dev/null 2>"$wd/cc.err" || { printf '%-22s :: COMPILE-FAIL %s\n' "$tag" "$(tail -3 $wd/cc.err|tr '\n' ' ')"; return; }
  printf '%-22s :: %s\n' "$tag" "$(python3 .run/giants/bf14_full.py "$wd/w/t.o" --count)"
}
export -f run; export BASE
printf '%s\n' "$@" | xargs -P 8 -I{} bash -c 'run "$@"' _ {}
