#!/bin/bash
# c730_sw.sh <base.c> <lever-spec> [lever-spec ...]
# each lever-spec = comma-separated lever names (or "-" for the bare base)
# 8-way parallel; prints the b3_align score for each.
cd /home/musashi/bfm-decomp
BASE="$1"; shift
D=.run/c730/sweep
mkdir -p "$D"
run_one() {
  local spec="$1" base="$2" d="$3"
  local tag=$(echo "$spec" | tr ',' '+')
  local f="$d/v_$tag.c"
  if [ "$spec" = "-" ]; then set --; else set -- $(echo "$spec" | tr ',' ' '); fi
  python3 .run/giants/c730_mk.py "$base" "$f" "$@" >/dev/null 2>"$d/e_$tag.txt" \
    || { echo "$tag :: MKFAIL $(head -3 "$d/e_$tag.txt"|tr '\n' ' ')"; return; }
  bash .run/giants/c730_score.sh "$f" "$tag" "$d/w_$tag"
}
export -f run_one
printf '%s\n' "$@" | xargs -P 8 -I{} bash -c 'run_one "$@"' _ {} "$BASE" "$D"
