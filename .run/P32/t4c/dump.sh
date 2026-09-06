#!/bin/bash
# usage: dump.sh <draft.c> <tag>   -> .run/P32/t4c/dumps_<tag>/  (private; frame line + ins count + ghost census)
cd /home/musashi/bfm-decomp
f="$1"; tag="$2"
d=.run/P32/t4c/dumps_$tag; rm -rf $d; mkdir -p $d
src=$d/$tag.c
if ! grep -q '#include "common.h"' "$f"; then echo '#include "common.h"' > $src; fi
cat "$f" >> $src
mipsel-linux-gnu-cpp -lang-c -Iinclude -undef -Wall -fno-builtin -Dmips -D__GNUC__=2 -D__OPTIMIZE__ -Dpsx -D_PSYQ -D_MIPSEL -D_LANGUAGE_C $src > $d/$tag.i
(cd $d && /home/musashi/bfm-decomp/tools/bin/gcc-2.7.2-psx/cc1 -quiet -O2 -G0 -mips1 -mcpu=3000 -mgas -msoft-float -fgnu-linker -dr -ds -dj -df -dc -dS -dl -dg $tag.i -o $tag.s 2>$tag.err)
echo "== $tag: $(grep -m1 '\.frame' $d/$tag.s | sed 's/\t/ /g')  ins=$(grep -cE '^\s+[a-z]' $d/$tag.s)"
grep -n "Spilling reg\|now on stack" $d/$tag.i.greg | head -5
# ghost census: pseudos with 'or none' class and NO occurrence in the greg insn stream
python3 tools/ghost_census.py "$d/$tag.i.lreg"; : <<'PY'
import re,sys
lreg=open(sys.argv[1]).read(); greg=open(sys.argv[2]).read()
for m in re.finditer(r'^Register (\d+) used (\d+) times.*?; (\w+ or none|pref \w+, else \w+|\w+ or \w+)\.', lreg, re.M):
    r=m.group(1)
    if not re.search(r'\(reg[^ ]* '+r+r'\)', greg):
        print(f"   GHOST candidate: pseudo {r} refs={m.group(2)} class={m.group(3)} (no occurrence in greg)")
PY
