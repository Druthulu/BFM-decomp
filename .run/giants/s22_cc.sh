#!/bin/bash
# compile ONE draft of func_8017DC1C the pinned-triple way, into $2 (a work dir).
# usage: s22_cc.sh <draft.c> <workdir> [extra cc1 flags e.g. -da]
set -e
cd /home/musashi/bfm-decomp
SRC="$1"; WD="$2"; shift 2
mkdir -p "$WD"
CPPFLAGS="-lang-c -Iinclude -undef -Wall -fno-builtin -Dmips -D__GNUC__=2 -D__OPTIMIZE__ -Dpsx -D_PSYQ -D_MIPSEL -D_LANGUAGE_C"
CC1FLAGS="-quiet -O2 -G0 -mips1 -mcpu=3000 -mgas -msoft-float -fgnu-linker"
python3 - "$SRC" "$WD/t.c" <<'PY'
import sys, os
sys.path.insert(0, '/home/musashi/bfm-decomp/tools')
import masked_diff
src = masked_diff.strip_scalar_typedefs(open(sys.argv[1]).read())
if '#include "common.h"' not in src: src = '#include "common.h"\n' + src
open(sys.argv[2], 'w').write(src)
PY
mipsel-linux-gnu-cpp $CPPFLAGS "$WD/t.c" > "$WD/t.i"
( cd "$WD" && /home/musashi/bfm-decomp/tools/bin/gcc-2.7.2-psx/cc1 $CC1FLAGS "$@" t.i -o t.s.raw )
.venv/bin/python tools/maspsx/maspsx.py --aspsx-version=2.56 --expand-div < "$WD/t.s.raw" > "$WD/t.s"
mipsel-linux-gnu-as -Iinclude -march=r3000 -mtune=r3000 -no-pad-sections -O1 -G0 -o "$WD/t.o" "$WD/t.s"
echo "OK -> $WD/t.o"
