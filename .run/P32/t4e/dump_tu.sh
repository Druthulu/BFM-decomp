#!/bin/bash
# dump_tu.sh <rtu work dir containing func_*/t.c> <tag> : real-TU gcc-2.7.2 dumps -> .run/P32/t4e/dumps_<tag>/
cd /home/musashi/bfm-decomp
wd="$1"; tag="$2"; d=.run/P32/t4e/dumps_$tag; rm -rf "$d"; mkdir -p "$d"
tc=$(ls $wd/*/t.c 2>/dev/null | head -1); [ -n "$tc" ] || { echo "no t.c under $wd"; exit 1; }
mipsel-linux-gnu-cpp -lang-c -Iinclude -undef -Wall -fno-builtin -Dmips -D__GNUC__=2 -D__OPTIMIZE__ -Dpsx -D_PSYQ -D_MIPSEL -D_LANGUAGE_C -Isrc '-DINCLUDE_ASM(a,b)=' "$tc" > $d/$tag.i 2>$d/cpp.err
(cd $d && /home/musashi/bfm-decomp/tools/bin/gcc-2.7.2-psx/cc1 -quiet -O2 -G0 -mips1 -mcpu=3000 -mgas -msoft-float -fgnu-linker -dr -ds -dj -dl -dg -df -dc -dS -dL $tag.i -o $tag.s 2>$tag.err)
echo "== $tag: $(ls $d | tr '\n' ' ')"
