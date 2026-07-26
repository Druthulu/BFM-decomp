#!/bin/bash
# c954_sweep.sh <base.c> <lever-spec> [lever-spec ...]
# each lever-spec = comma-separated lever names, e.g. "nprim_first,ot_last"
# runs all specs 8-way parallel, prints "spec :: line"
cd /home/musashi/bfm-decomp
BASE="$1"; shift
D=.run/c954/sweep
mkdir -p "$D"
run_one() {
  local spec="$1" base="$2" d="$3"
  local tag=$(echo "$spec" | tr ',' '+')
  local f="$d/v_$tag.c"
  python3 .run/giants/c954_mk.py "$base" "$f" $(echo "$spec" | tr ',' ' ') >/dev/null 2>"$d/e_$tag.txt" || { echo "$tag :: MKFAIL $(head -3 $d/e_$tag.txt|tr '\n' ' ')"; return; }
  local out=$(timeout 900 python3 tools/match_one.py func_8017C954 --c "$f" \
        --asm-subdir asm/ov_SC06_029/nonmatchings/ov_SC06_029_jr_8017AE2C 2>&1 | head -2 | tr '\n' ' ')
  echo "$tag :: $out"
}
export -f run_one
printf '%s\n' "$@" | xargs -P 8 -I{} bash -c 'run_one "$@"' _ {} "$BASE" "$D"
