#!/usr/bin/env python3
"""Full (uncapped) masked index-wise diff of a compiled object vs func_8017BF14's target .s.
usage: bf14_full.py <obj.o> [--count]"""
import sys, os
sys.path.insert(0, '/home/musashi/bfm-decomp/tools')
import masked_diff
OBJ = sys.argv[1]
FN = 'func_8017BF14'
TGT = '/home/musashi/bfm-decomp/asm/ov_SC03_116/nonmatchings/ov_SC03_116_jr_8017AE2C/%s.s' % FN
mine = masked_diff.insns_from_object(OBJ, FN)
tgt = masked_diff.insns_from_s(TGT)
diffs = masked_diff.structured_diff(mine, tgt)
print('mine=%d target=%d  %d mismatched' % (len(mine), len(tgt), len(diffs)))
if '--count' not in sys.argv:
    for i, me, tg in diffs:
        print('  %4d | %-34s | %s' % (i, me, tg))
