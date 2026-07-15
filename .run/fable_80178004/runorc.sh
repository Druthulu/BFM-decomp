#!/bin/bash
# usage: runorc.sh <ver>   — dump, oracle-compile, assemble, compare
cd /home/musashi/bfm-decomp
V=$1
.run/fable_80178004/dump.sh .run/fable_80178004/$V.c $V >/dev/null 2>&1
cd .run/fable_80178004/dumps_$V
gdb -batch -x ../oracle.gdb --args /home/musashi/bfm-decomp/tools/bin/gcc-2.7.2-psx/cc1 -quiet -O2 -G0 -mips1 -mcpu=3000 -mgas -msoft-float -fgnu-linker t.i -o oracle.s 2>&1 | grep -E "ORACLE" >&2
python3 /home/musashi/bfm-decomp/tools/maspsx/maspsx.py --aspsx-version=2.56 --expand-div < oracle.s > oracle.masp.s 2>/dev/null
cd /home/musashi/bfm-decomp
mipsel-linux-gnu-as -Iinclude -march=r3000 -mtune=r3000 -no-pad-sections -O1 -G0 -o .run/fable_80178004/dumps_$V/oracle.o .run/fable_80178004/dumps_$V/oracle.masp.s
python3 .run/fable_80178004/cmp.py .run/fable_80178004/dumps_$V/oracle.o ${2:-70}
