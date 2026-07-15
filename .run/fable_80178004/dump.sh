#!/bin/bash
# Reproduce match_one's exact pinned-triple compile, with RTL/alloc/sched dumps.
# usage: dump.sh <cfile> <tag>
cd /home/musashi/bfm-decomp
C="$1"; TAG="$2"
WD=.run/fable_80178004/dumps_$TAG
mkdir -p "$WD"
python3 - "$C" "$WD/t.c" <<'PYEOF'
import sys, re
src = open(sys.argv[1]).read()
SCALAR_TYPEDEF_RE = re.compile(r'^\s*typedef\s+(?:unsigned|signed)?\s*(?:char|short|int|long)[^;]*\b[usf](?:8|16|32|64)\s*;\s*$', re.M)
src = SCALAR_TYPEDEF_RE.sub('', src)
if '#include "common.h"' not in src:
    src = '#include "common.h"\n' + src
open(sys.argv[2],'w').write(src)
PYEOF
mipsel-linux-gnu-cpp -lang-c -Iinclude -undef -Wall -fno-builtin -Dmips -D__GNUC__=2 -D__OPTIMIZE__ -Dpsx -D_PSYQ -D_MIPSEL -D_LANGUAGE_C "$WD/t.c" > "$WD/t.i" || exit 1
( cd "$WD" && /home/musashi/bfm-decomp/tools/bin/gcc-2.7.2-psx/cc1 -quiet -O2 -G0 -mips1 -mcpu=3000 -mgas -msoft-float -fgnu-linker -dc -dS -dl -dg -dR -dd -dj -dJ t.i -o t.s ) || exit 1
ls "$WD" | grep '^t\.i\.'
