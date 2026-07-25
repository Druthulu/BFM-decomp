#!/usr/bin/env python3
"""Full (uncapped) masked index-wise diff of a compiled object vs the target .s.
usage: full.py <obj.o> [fn] [--all]
Prints every mismatched index (match_one caps at 40)."""
import sys, os
sys.path.insert(0, '/home/musashi/bfm-decomp/tools')
import masked_diff

OBJ = sys.argv[1]
FN = sys.argv[2] if len(sys.argv) > 2 else 'func_8017F510'
TGT = '/home/musashi/bfm-decomp/asm/ov_SC03_006/nonmatchings/ov_SC03_006_jr_8017AE2C/%s.s' % FN
mine = masked_diff.insns_from_object(OBJ, FN)
tgt = masked_diff.insns_from_s(TGT)
diffs = masked_diff.structured_diff(mine, tgt)
print('mine=%d target=%d  %d mismatched' % (len(mine), len(tgt), len(diffs)))
for i, me, tg in diffs:
    print('  %4d | %-32s | %s' % (i, me, tg))
