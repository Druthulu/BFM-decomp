#!/bin/bash
# decomp-permuter compile command for BFM — the PINNED triple (docs/SETUP.md §5.4).
# Invoked by the permuter as:  ./compile.sh input.c -o output.o
# input.c is preprocessed C (pycparser-parseable). This mirrors the Makefile c-rule
# exactly so permuter objects are build-faithful:
#   cpp -> cc1 (gcc-2.7.2-psx) -> maspsx (--aspsx-version=2.56 --expand-div) -> mipsel-as
set -e -o pipefail
REPO="$(cd "$(dirname "${BASH_SOURCE[0]}")/../.." && pwd)"
IN="$1"; OUT="${3:-out.o}"   # args as passed by permuter: input.c -o output.o

mipsel-linux-gnu-cpp -lang-c -I"$REPO/include" -undef -Wall -fno-builtin \
    -Dmips -D__GNUC__=2 -D__OPTIMIZE__ -Dpsx -D_PSYQ -D_MIPSEL -D_LANGUAGE_C "$IN" \
  | "$REPO/tools/bin/gcc-2.7.2-psx/cc1" -quiet -O2 -G0 -mips1 -mcpu=3000 -mgas \
        -msoft-float -fgnu-linker \
  | "$REPO/.venv/bin/python" "$REPO/tools/maspsx/maspsx.py" --aspsx-version=2.56 --expand-div \
  | mipsel-linux-gnu-as -I"$REPO/include" -march=r3000 -mtune=r3000 -no-pad-sections -O1 -G0 -o "$OUT"
