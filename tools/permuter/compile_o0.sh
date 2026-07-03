#!/bin/bash
# -O0 variant of compile.sh for the ov_SC01_077 _o0 subsegment (Phase 24 T3). The _o0 cluster is
# built -O0 (Makefile: build/src/ov_SC01_077/ov_SC01_077_o0.o CC1FLAGS := -quiet -O0 ...), so an -O2
# permuter/match_one compile can never match its target bytes. ONLY the cc1 opt level differs from
# compile.sh (-O2 -> -O0); cpp (incl. -D__OPTIMIZE__, shared by the Makefile) / maspsx / as are identical.
set -e -o pipefail
REPO="$(cd "$(dirname "${BASH_SOURCE[0]}")/../.." && pwd)"
IN="$1"; OUT="${3:-out.o}"   # args as passed by permuter: input.c -o output.o

mipsel-linux-gnu-cpp -lang-c -I"$REPO/include" -undef -Wall -fno-builtin \
    -Dmips -D__GNUC__=2 -D__OPTIMIZE__ -Dpsx -D_PSYQ -D_MIPSEL -D_LANGUAGE_C "$IN" \
  | "$REPO/tools/bin/gcc-2.7.2-psx/cc1" -quiet -O0 -G0 -mips1 -mcpu=3000 -mgas \
        -msoft-float -fgnu-linker \
  | "$REPO/.venv/bin/python" "$REPO/tools/maspsx/maspsx.py" --aspsx-version=2.56 --expand-div \
  | { printf '.include "macro.inc"\n'; cat; } \
  | mipsel-linux-gnu-as -I"$REPO/include" -march=r3000 -mtune=r3000 -no-pad-sections -O1 -G0 -o "$OUT"
