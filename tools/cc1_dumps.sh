#!/bin/bash
# usage: dump.sh <draft.c> <tag>  -> .run/c294/<tag>.{s,greg,lreg,combine} + orphan-slot report
# gcc-2.7.2 cc1 writes dump files as <inputname>.<pass> in its CWD; we cd into a private dir so
# the repo root never collects gccdump.* droppings again.
cd /home/musashi/bfm-decomp
f="$1"; tag="$2"
d=.run/c294/dumps_$tag; rm -rf $d; mkdir -p $d
src=$d/$tag.c
if ! grep -q '#include "common.h"' "$f"; then echo '#include "common.h"' > $src; fi
cat "$f" >> $src
mipsel-linux-gnu-cpp -lang-c -Iinclude -undef -Wall -fno-builtin -Dmips -D__GNUC__=2 -D__OPTIMIZE__ -Dpsx -D_PSYQ -D_MIPSEL -D_LANGUAGE_C $src > $d/$tag.i
(cd $d && ../../../tools/bin/gcc-2.7.2-psx/cc1 -quiet -O2 -G0 -mips1 -mcpu=3000 -mgas -msoft-float -fgnu-linker -dr -ds -dj -dc -dl -dg $tag.i -o $tag.s 2>$tag.err)
echo "== $tag: dumps in $d"
grep -c "^(insn" $d/$tag.i.greg 2>/dev/null | sed 's/^/greg insns: /'
# orphan slots: pseudos whose ONLY appearance after reload is inside a (use ...) — count stack slots
python3 - "$d/$tag.i.greg" <<'PY'
import re, sys
t = open(sys.argv[1]).read()
# every "Register N ... in stack slot" style line differs by gcc version; instead pull the
# reload-era equivalences: (reg N) replaced by (mem (plus (reg 29) (const_int X)))
slots = {}
for m in re.finditer(r'\(insn [0-9]+ [0-9]+ [0-9]+[^\n]*\n?[^(]*\(use \(reg[^ ]* ([0-9]+)\)', t):
    slots.setdefault(m.group(1), 0)
uses = re.findall(r'\(use \(reg[:A-Z]* ([0-9]+)[ )]', t)
print("USE-referenced pseudos in greg:", sorted(set(uses), key=int))
PY
