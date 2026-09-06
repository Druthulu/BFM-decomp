#!/bin/bash
# cc1_dumps_tu.sh <rtu_match --work dir containing <fn>/t.c> <tag> : REAL-TU gcc-2.7.2 pass dumps (-dr -ds -dj -dl -dg -df -dc -dS -dL)
# -> ${DUMP_ROOT:-.run/P32/t4e}/dumps_<tag>/ . P32 T4c (S85): the standalone tools/cc1_dumps.sh compile is NOT faithful on main
# TUs (427 vs 518 ins on func_80039308) — dump the spliced real TU instead; pair with tools/alloc_table.py.
cd /home/musashi/bfm-decomp
wd="$1"; tag="$2"; d=${DUMP_ROOT:-.run/P32/t4e}/dumps_$tag; rm -rf "$d"; mkdir -p "$d"
tc=$(ls $wd/*/t.c 2>/dev/null | head -1); [ -n "$tc" ] || { echo "no t.c under $wd"; exit 1; }
mipsel-linux-gnu-cpp -lang-c -Iinclude -undef -Wall -fno-builtin -Dmips -D__GNUC__=2 -D__OPTIMIZE__ -Dpsx -D_PSYQ -D_MIPSEL -D_LANGUAGE_C -Isrc '-DINCLUDE_ASM(a,b)=' "$tc" > $d/$tag.i 2>$d/cpp.err
(cd $d && /home/musashi/bfm-decomp/tools/bin/gcc-2.7.2-psx/cc1 -quiet -O2 -G0 -mips1 -mcpu=3000 -mgas -msoft-float -fgnu-linker -dr -ds -dj -dl -dg -df -dc -dS -dL $tag.i -o $tag.s 2>$tag.err)
echo "== $tag: $(ls $d | tr '\n' ' ')"
