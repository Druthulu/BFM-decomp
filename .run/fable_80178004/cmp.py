import sys
sys.path.insert(0, '/home/musashi/bfm-decomp/tools')
import masked_diff
obj = sys.argv[1]
mine = masked_diff.insns_from_object(obj, 'func_80178004')
tgt = masked_diff.insns_from_s('/home/musashi/bfm-decomp/asm/ov_SC01_077/nonmatchings/ov_SC01_077_jr_801734BC/func_80178004.s')
n = max(len(mine), len(tgt))
bad = 0; lines = []
for i in range(n):
    mw = mine[i] if i < len(mine) else None
    tw = tgt[i] if i < len(tgt) else None
    mask = masked_diff.mask_for(mw['word'], mw['reloc_kind']) if mw else 0xFFFFFFFF
    me = (mw['word'] & mask) if mw else None
    tg = (tw['word'] & mask) if tw else None
    if me != tg:
        bad += 1
        lines.append('%3d *** | %-30s | %s' % (i, (mw['mnem'] if mw else '--'), (tw['mnem'] if tw else '--')))
print('TOTAL MISMATCHES:', bad, ' mine=%d target=%d' % (len(mine), len(tgt)))
lim = int(sys.argv[2]) if len(sys.argv) > 2 else 60
for l in lines[:lim]: print(l)
