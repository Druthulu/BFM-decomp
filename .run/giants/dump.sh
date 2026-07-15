#!/bin/bash
# Produce sched1/sched2/dbr RTL dumps for a draft .c of func_801670E4
set -e
R=/home/musashi/bfm-decomp
N="$1"          # path to .c
OUT="$2"        # output prefix
CPPFLAGS="-lang-c -I$R/include -undef -Wall -fno-builtin -Dmips -D__GNUC__=2 -D__OPTIMIZE__ -Dpsx -D_PSYQ -D_MIPSEL -D_LANGUAGE_C"
CC1FLAGS="-quiet -O2 -G0 -mips1 -mcpu=3000 -mgas -msoft-float -fgnu-linker"
# prepend common.h if absent
if ! grep -q 'common.h' "$N"; then printf '#include "common.h"\n' > "$OUT.pre.c"; cat "$N" >> "$OUT.pre.c"; else cp "$N" "$OUT.pre.c"; fi
mipsel-linux-gnu-cpp $CPPFLAGS "$OUT.pre.c" > "$OUT.i" 2>/dev/null
$R/tools/bin/gcc-2.7.2-psx/cc1 $CC1FLAGS -dS -dR -dj -dc -dg -dl -dd "$OUT.i" -o "$OUT.s" 2>&1 | head -5 || true
echo "dumps: $OUT.i.* ; asm: $OUT.s"
ls -la "$OUT".i.* 2>/dev/null | awk '{print $NF}'
