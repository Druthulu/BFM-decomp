#!/usr/bin/env python3
"""Where are MY extra instructions? Buckets difflib opcodes by TARGET region and
reports net length delta per region (mine_len - tgt_len inside each opcode block).

usage: ins.py <obj.o> [--dump REGION]
"""
import sys, os, difflib
sys.path.insert(0, '/home/musashi/bfm-decomp/tools')
import masked_diff

FN = 'func_80183814'
TGT = ('/home/musashi/bfm-decomp/asm/ov_SC07_006/nonmatchings/'
       'ov_SC07_006_jr_8017BEBC/%s.s' % FN)
CASES = [0x801838D4,0x80183E80,0x801842E0,0x80184338,0x801848EC,0x80184D50,
         0x80184DF4,0x80185028,0x80185078,0x80185334,0x80185754,0x801857D4,
         0x80185B58,0x80185CF4,0x801860F8,0x8018650C,0x8018690C,0x80186CD0,
         0x80187590,0x80187D20,0x80187F9C,0x801887D0]
BASE = 0x80183814


def regions(ntgt):
    b = [('PRE', BASE)] + [('CASE%02d' % i, CASES[i]) for i in range(21)] \
        + [('TAIL', CASES[21])]
    out = []
    for k, (n, a) in enumerate(b):
        lo = (a - BASE) // 4
        hi = (b[k + 1][1] - BASE) // 4 if k + 1 < len(b) else ntgt
        out.append([n, lo, hi])
    out[-1][2] = ntgt
    return out


def key(d, blind=True):
    v = d['word']
    rel = d['reloc_kind']
    if rel is None and ('%hi(' in d['mnem'] or '%lo(' in d['mnem']):
        rel = 'HI16'
    if rel is None and (v >> 26) in (2, 3):
        rel = '26'
    if not blind:
        return v & masked_diff.mask_for(v, rel)
    op = (v >> 26) & 0x3F
    if op in (2, 3) or rel == '26':
        return ('J',)
    imm = 0 if rel in ('HI16', 'LO16', 'PC16') else v & 0xFFFF
    if op == 0:
        return ('R', v & 0x3F, (v >> 6) & 0x1F)
    if op == 0x1C:
        return ('R2', v & 0x3F)
    if op in (1, 4, 5, 6, 7):
        return ('B', op, (v >> 16) & 0x1F)
    return ('I', op, imm)


def main():
    obj = sys.argv[1]
    dump = sys.argv[sys.argv.index('--dump') + 1] if '--dump' in sys.argv else None
    mine_r = masked_diff.insns_from_object(obj, FN)
    tgt_r = masked_diff.insns_from_s(TGT)
    mine = [key(d) for d in mine_r]
    tgt = [key(d) for d in tgt_r]
    regs = regions(len(tgt))
    sm = difflib.SequenceMatcher(None, mine, tgt, autojunk=False)

    def rname(j):
        for n, lo, hi in regs:
            if lo <= j < hi:
                return n
        return regs[-1][0]

    delta = {n: 0 for n, _, _ in regs}
    blocks = []
    for tag, i1, i2, j1, j2 in sm.get_opcodes():
        if tag == 'equal':
            continue
        n = rname(j1 if j1 < len(tgt) else len(tgt) - 1)
        d = (i2 - i1) - (j2 - j1)
        delta[n] += d
        blocks.append((n, tag, i1, i2, j1, j2, d))

    print('mine=%d target=%d  netdelta=%+d' % (len(mine), len(tgt), len(mine) - len(tgt)))
    print('%-8s %7s   %s' % ('region', 'delta', 'blocks'))
    for n, lo, hi in regs:
        bl = [b for b in blocks if b[0] == n]
        if delta[n] or bl:
            print('%-8s %+7d   %d' % (n, delta[n], len(bl)))
    print()
    for n, tag, i1, i2, j1, j2, d in blocks:
        if dump and n != dump:
            continue
        print('== %s %s  mine[%d:%d] (%d)  tgt[%d:%d] (%d)  delta %+d'
              % (n, tag, i1, i2, i2 - i1, j1, j2, j2 - j1, d))
        for k in range(i1, i2):
            print('   M %5d | %08x %s' % (k, mine_r[k]['word'], mine_r[k]['mnem']))
        for k in range(j1, j2):
            print('   T %5d | %08x %s' % (k, tgt_r[k]['word'], tgt_r[k]['mnem']))


main()
