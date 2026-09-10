#!/bin/bash
# cc1_dumps_tu.sh <rtu_match --work dir containing <fn>/t.c> <tag> : REAL-TU gcc-2.7.2 pass dumps (-dr -ds -dj -dl -dg -df -dc -dS -dL -dR -dt -dJ)
# S103 (agent c11): -dt (the SECOND cse pass, .cse2) and -dJ (the post-reload jump pass, .jump2) added — c11's deciding fact was only in .cse2, c10's cross-jump only in .jump2.
# S103: -Isrc/shared on the cpp line: a TU's `#include "../shared/..."` resolves from any directory one level under src/,
# and a copied TU's own directory is not one (every scratch copy failed CPP-EMPTY).
# -> ${DUMP_ROOT:-.run/P32/t4e}/dumps_<tag>/ . P32 T4c (S85): the standalone tools/cc1_dumps.sh compile is NOT faithful on main
# TUs (427 vs 518 ins on func_80039308) — dump the spliced real TU instead; pair with tools/alloc_table.py.
cd /home/musashi/bfm-decomp
wd="$1"; tag="$2"; d=${DUMP_ROOT:-.run/P32/t4e}/dumps_$tag; rm -rf "$d"; mkdir -p "$d"
# S103: the first argument may also be a .c FILE (an agent's spliced TU, a --try scratch copy) — the form every T7 agent
# needed and six of them re-wrote as their own dump.sh
if [ -f "$wd" ]; then tc="$wd"; else tc=$(ls $wd/*/t.c 2>/dev/null | head -1); fi
[ -n "$tc" ] || { echo "no t.c under $wd"; exit 1; }
mipsel-linux-gnu-cpp -lang-c -Iinclude -I"$(dirname "$tc")" -Isrc/shared -undef -Wall -fno-builtin -Dmips -D__GNUC__=2 -D__OPTIMIZE__ -Dpsx -D_PSYQ -D_MIPSEL -D_LANGUAGE_C -Isrc '-DINCLUDE_ASM(a,b)=' "$tc" > $d/$tag.i 2>$d/cpp.err
if [ "$(wc -l < $d/$tag.i)" -lt 200 ]; then echo "cc1_dumps_tu: CPP-EMPTY — $d/$tag.i has $(wc -l < $d/$tag.i) lines; the TU's own directory was probably not on the include path (see cpp.err)" >&2; exit 3; fi
(cd $d && /home/musashi/bfm-decomp/tools/bin/gcc-2.7.2-psx/cc1 -quiet -O2 -G0 -mips1 -mcpu=3000 -mgas -msoft-float -fgnu-linker -dr -ds -dj -dl -dg -df -dc -dS -dL -dR -dt -dJ $tag.i -o $tag.s 2>$tag.err)
echo "== $tag: $(ls $d | tr '\n' ' ')"
