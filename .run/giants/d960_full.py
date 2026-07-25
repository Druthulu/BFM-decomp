#!/usr/bin/env python3
"""Full (uncapped) masked index-wise diff of a compiled object vs func_8017D960's target .s.
usage: d960_full.py <obj.o> [--count]"""
import sys, os
sys.path.insert(0, '/home/musashi/bfm-decomp/tools')
import masked_diff
OBJ = sys.argv[1]
FN = 'func_8017D960'
TGT = '/home/musashi/bfm-decomp/asm/ov_SC03_090/nonmatchings/ov_SC03_090_jr_8017CA80/%s.s' % FN
mine = masked_diff.insns_from_object(OBJ, FN)
tgt = masked_diff.insns_from_s(TGT)
diffs = masked_diff.structured_diff(mine, tgt)
print('mine=%d target=%d  %d mismatched' % (len(mine), len(tgt), len(diffs)))
if '--count' not in sys.argv:
    for i, me, tg in diffs:
        print('  %4d | %-34s | %s' % (i, me, tg))
