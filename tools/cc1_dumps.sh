#!/bin/bash
# usage: cc1_dumps.sh <draft.c> <tag>  -> .run/c294/dumps_<tag>/<tag>.i.{rtl,jump,cse,loop,flow,combine,sched,lreg,greg} + <tag>.s
# gcc-2.7.2 cc1 writes dump files as <inputname>.<pass> in its CWD; we cd into a private dir so
# the repo root never collects gccdump.* droppings again.
# The draft must be self-contained (its own typedefs/externs); edit the cc1 line for -O0 (boot) modules.
# Prints: the .frame line (vars= is THE frame-residue oracle, §172/§501-M), the instruction count, the reload
# spill lines, and the ghost census (tools/ghost_census.py — the old standalone-`(use)` grep UNDER-COUNTS, §172 note).
cd /home/musashi/bfm-decomp
f="$1"; tag="$2"
d=.run/c294/dumps_$tag; rm -rf $d; mkdir -p $d
src=$d/$tag.c
if ! grep -q '#include "common.h"' "$f"; then echo '#include "common.h"' > $src; fi
cat "$f" >> $src
mipsel-linux-gnu-cpp -lang-c -Iinclude -undef -Wall -fno-builtin -Dmips -D__GNUC__=2 -D__OPTIMIZE__ -Dpsx -D_PSYQ -D_MIPSEL -D_LANGUAGE_C $src > $d/$tag.i
(cd $d && ../../../tools/bin/gcc-2.7.2-psx/cc1 -quiet -O2 -G0 -mips1 -mcpu=3000 -mgas -msoft-float -fgnu-linker -dr -ds -dj -df -dc -dS -dl -dg $tag.i -o $tag.s 2>$tag.err)
echo "== $tag: $(grep -m1 '\.frame' $d/$tag.s | sed 's/\t/ /g')  ins=$(grep -cE '^\s+[a-z]' $d/$tag.s)  (dumps in $d)"
grep -n "Spilling reg\|now on stack\|now in" $d/$tag.i.greg | head -8
python3 tools/ghost_census.py "$d/$tag.i.lreg"
