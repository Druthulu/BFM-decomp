#!/bin/bash
# c730_probe2.sh <draft.c> [tag] -- compiles with -da, prints score + the my/mny/mx/mn grants
cd /home/musashi/bfm-decomp
SRC="$1"; TAG="${2:-$(basename "$1" .c)}"; WD=".run/c730/p2/$TAG"
mkdir -p "$WD"
if ! bash .run/giants/c730_cc.sh "$SRC" "$WD" -da >"$WD/cc.log" 2>&1; then
  echo "$TAG :: CCFAIL $(grep -m2 -E 'error|undeclared|parse' "$WD/cc.log" | tr '\n' ' ')"; exit 0
fi
S=$(bash .run/giants/c730_score.sh "$SRC" "$TAG" "$WD" 2>/dev/null)
python3 - "$WD" "$S" <<'PY'
import re, sys
wd = sys.argv[1]
txt = open(wd + '/t.i.greg').read()
lreg = open(wd + '/t.i.lreg').read()
info = {}
for m in re.finditer(r'Register (\d+) used (\d+) times across (\d+) insns', lreg):
    info[int(m.group(1))] = (int(m.group(2)), int(m.group(3)))
disp = {}
d = txt.split(';; Register dispositions:')[1].split('\n\n')[0]
for m in re.finditer(r'(\d+) in (\d+)', d):
    disp[int(m.group(1))] = int(m.group(2))
R = ['zero','at','v0','v1','a0','a1','a2','a3','t0','t1','t2','t3','t4','t5','t6','t7',
     's0','s1','s2','s3','s4','s5','s6','s7','t8','t9','k0','k1','gp','sp','fp','ra']
# the my/mny/mx/mn quad = the four consecutive pseudos with the largest equal ref counts >60
cand = sorted([p for p, (r, l) in info.items() if r > 60 and l > 150])
out = []
for p in cand[:8]:
    mm = re.search(r'^;; %d conflicts:(.*)$' % p, txt, re.M)
    hs = [int(x) for x in mm.group(1).split()] if mm else []
    out.append('%d=%s%s' % (p, R[disp[p]] if p in disp else 'SPILL', '' if 3 in [n for n in hs if n < 32] else '!'))
print('%s   quad: %s' % (sys.argv[2].strip(), ' '.join(out)))
PY
