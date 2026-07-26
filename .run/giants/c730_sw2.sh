#!/bin/bash
# c730_sw2.sh <base_body.c> <lever-spec> ...   -> per-region (pro/part) score + total
cd /home/musashi/bfm-decomp
BASE="$1"; shift
D=.run/c730/sweep; mkdir -p "$D"
run_one() {
  local spec="$1" base="$2" d="$3"
  local tag=$(echo "$spec" | tr ',' '+')
  local f="$d/v_$tag.c"
  if [ "$spec" = "-" ]; then set --; else set -- $(echo "$spec" | tr ',' ' '); fi
  python3 .run/giants/c730_mk.py "$base" "$f" "$@" >/dev/null 2>"$d/e_$tag.txt" \
    || { echo "$tag :: MKFAIL $(head -3 "$d/e_$tag.txt"|tr '\n' ' ')"; return; }
  local w="$d/w_$tag"; mkdir -p "$w"
  bash .run/giants/c730_cc.sh "$f" "$w" >"$w/cc.log" 2>&1 || { echo "$tag :: CCFAIL $(grep -m2 -E 'error|undeclared|parse' "$w/cc.log"|tr '\n' ' ')"; return; }
  python3 .run/giants/c730_reg.py "$w/t.o" "$tag" | python3 -c "
import sys
L=sys.stdin.read().splitlines()
hdr=L[0].split()
pro=[l for l in L if l.strip().startswith('pro ')][0].split()
part=[l for l in L if l.strip().startswith('part ')][0].split()
tot=[l for l in L if 'TOTAL' in l][0].split()
print('%-34s %s %s  pro %s/%s  part %s/%s  TOT %s %s' % (hdr[0],hdr[1],hdr[2],pro[4],pro[8],part[4],part[8],tot[5],tot[8]))
"
}
export -f run_one
printf '%s\n' "$@" | xargs -P 8 -I{} bash -c 'run_one "$@"' _ {} "$BASE" "$D"
