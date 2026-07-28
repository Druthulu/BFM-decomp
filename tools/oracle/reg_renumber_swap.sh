#!/bin/bash
# swap_oracle.sh — the regalloc.md §H reg_renumber-swap oracle, mechanized.
#
# QUESTION IT ANSWERS: when a residual is "register identity AND an instruction reordering", you
# cannot tell from the diff whether the reorder is a SCHEDULING decision (S3 — C often cannot move
# it) or merely a CONSEQUENCE of the register grant (fix the regs and the schedule follows).
#
# METHOD: break at `reload` entry, swap two hard registers throughout `reg_renumber` (so every
# pseudo allocated to A gets B and vice versa), let compilation finish, and re-score the result with
# the SAME comparison match_one uses (masked_diff, reused not reimplemented — R33).
#
#   diff count DROPS  -> the residual is ALLOCATION; route to density/lifetime levers.
#   diff count STAYS  -> the reorder is not a consequence of these two registers.
#
# usage: swap_oracle.sh <hardA> <hardB>      (MIPS: v0=2 v1=3 a0=4 a1=5 a2=6 a3=7)
set -u
REPO=/home/musashi/bfm-decomp
D=$REPO/.run/giants/fable_cd4/dumps_o734
A=$1; B=$2
cd "$D" || exit 1

cat > swap_${A}_${B}.gdb <<EOF
set pagination off
set confirm off
set height 0
set debuginfod enabled off
break *0x815d4d7
commands 1
  silent
  set \$rr = *(long *)0x082d4330
  set \$mx = *(long *)0x082d3a10
  set \$i = 0
  set \$n = 0
  while \$i < \$mx
    set \$h = *(short *)(\$rr + \$i*2)
    if \$h == $A
      set *(short *)(\$rr + \$i*2) = $B
      set \$n = \$n + 1
    else
      if \$h == $B
        set *(short *)(\$rr + \$i*2) = $A
        set \$n = \$n + 1
      end
    end
    set \$i = \$i + 1
  end
  printf "SWAPPED %d pseudo(s) between hard %d and hard %d\n", \$n, $A, $B
  continue
end
run -quiet -O2 -G0 -mips1 -mcpu=3000 -mgas -msoft-float -fgnu-linker t.i -o swap_${A}_${B}.s
quit
EOF

timeout 600 gdb -batch -x swap_${A}_${B}.gdb "$REPO/tools/bin/gcc-2.7.2-psx/cc1" 2>&1 | grep -E "^SWAPPED"
[ -s swap_${A}_${B}.s ] || { echo "  (no output produced)"; exit 1; }

python3 "$REPO/tools/maspsx/maspsx.py" --aspsx-version=2.56 --expand-div < swap_${A}_${B}.s > swap_${A}_${B}.mas.s 2>/dev/null
# `as` must run from the REPO ROOT: the emitted .s carries a RELATIVE `.include "include/labels.inc"`.
( cd "$REPO" && mipsel-linux-gnu-as -march=r3000 -mtune=r3000 -no-pad-sections -O1 -G0 -Iinclude \
    -o "$D/swap_${A}_${B}.o" "$D/swap_${A}_${B}.mas.s" ) 2>/dev/null \
  || { echo "  (assemble failed)"; exit 1; }

cd "$REPO" && python3 - "$D/swap_${A}_${B}.o" "$A" "$B" <<'PY'
import sys, os
sys.path.insert(0, 'tools')
import masked_diff as M
obj, A, B = sys.argv[1], sys.argv[2], sys.argv[3]
tgt = 'asm/ov_SC01_077/nonmatchings/ov_SC01_077_jr_801734BC/func_80176734.s'
mine = M.insns_from_object(obj, 'func_80176734')
want = M.insns_from_s(tgt)
d = M.structured_diff(mine, want)
print("  swap $%s<->$%s : mine=%d ins, target=%d ins, %d mismatched  (baseline 13)"
      % (A, B, len(mine), len(want), len(d)))
PY
