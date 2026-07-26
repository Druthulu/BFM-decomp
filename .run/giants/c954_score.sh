#!/bin/bash
# c954_score.sh <draft.c> [tag] [workdir]
# compiles the draft and prints:  TAG  nins  maskedPct  keptPct  keptIdent
# (b3_align numbers -- shape-agnostic, valid even when the length drifts)
cd /home/musashi/bfm-decomp
SRC="$1"; TAG="${2:-$(basename "$1" .c)}"; WD="${3:-.run/c954/score/$TAG}"
mkdir -p "$WD"
if ! bash .run/giants/c954_cc.sh "$SRC" "$WD" >"$WD/cc.log" 2>&1; then
  echo "$TAG :: CCFAIL $(tail -2 "$WD/cc.log" | tr '\n' ' ')"; exit 0
fi
python3 .run/giants/b3_align.py "$WD/t.o" \
  asm/ov_SC06_029/nonmatchings/ov_SC06_029_jr_8017AE2C/func_8017C954.s 0 2>/dev/null \
  | python3 -c "
import sys,re
t='$TAG'
lines=sys.stdin.read().splitlines()
nins=re.search(r'mine (\d+)',lines[0]).group(1)
pct=[l for l in lines if 'aligned-identical' in l]
m=[re.search(r'(\d+) / (\d+) target ins = ([\d.]+)%',p) for p in pct]
print('%-28s nins=%s  masked=%s%% (%s)  kept=%s%% (%s)' % (t,nins,m[0].group(3),m[0].group(1),m[1].group(3),m[1].group(1)))
"
