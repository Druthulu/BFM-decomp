#!/bin/bash
# c730_sweep.sh <base.c> <lever-spec> [lever-spec ...]
# each lever-spec = comma-separated lever names, e.g. "nprim_first,ot_last"
# runs all specs 8-way parallel, prints "spec :: line"
cd /home/musashi/bfm-decomp
BASE="$1"; shift
D=.run/c730/sweep
mkdir -p "$D"
run_one() {
  local spec="$1" base="$2" d="$3"
  local tag=$(echo "$spec" | tr ',' '+')
  local f="$d/v_$tag.c"
  if [ "$spec" = "-" ]; then set --; else set -- $(echo "$spec" | tr ',' ' '); fi
  python3 .run/giants/c730_mk.py "$base" "$f" "$@" >/dev/null 2>"$d/e_$tag.txt" || { echo "$tag :: MKFAIL $(head -3 $d/e_$tag.txt|tr '\n' ' ')"; return; }
  local out=$(timeout 900 python3 tools/match_one.py func_8017C730 --c "$f" \
        --asm-subdir asm/ov_SC03_010/nonmatchings/ov_SC03_010_jr_8017AE2C 2>&1 | head -2 | tr '\n' ' ')
  echo "$tag :: $out"
}
export -f run_one
printf '%s\n' "$@" | xargs -P 8 -I{} bash -c 'run_one "$@"' _ {} "$BASE" "$D"
