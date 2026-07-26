#!/usr/bin/env python3
"""Region-aligned scorer for func_80183814.

Aligns my compiled instruction stream against the target with difflib (so an
insertion/deletion in one case does not smear the score across all later cases),
then buckets unmatched TARGET instructions into the 23 regions
(PRE, CASE00..CASE20, TAIL).

usage: g14_score.py <obj.o> [--diff REGION]
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

def regions():
    """(name, lo_idx, hi_idx) over the target instruction index."""
    b = [('PRE', BASE)] + [('CASE%02d' % i, CASES[i]) for i in range(21)] \
        + [('TAIL', CASES[21])]
    out = []
    for k, (n, a) in enumerate(b):
        lo = (a - BASE) // 4
        hi = (b[k + 1][1] - BASE) // 4 if k + 1 < len(b) else None
        out.append([n, lo, hi])
    return out

def main():
    obj = sys.argv[1]
    want = None
    if '--diff' in sys.argv:
        want = sys.argv[sys.argv.index('--diff') + 1]
    mine_r = masked_diff.insns_from_object(obj, FN)
    tgt_r = masked_diff.insns_from_s(TGT)

    BLIND = '--blind' in sys.argv

    def key(d):
        v = d['word']
        rel = d['reloc_kind']
        if rel is None and ('%hi(' in d['mnem'] or '%lo(' in d['mnem']):
            rel = 'HI16'          # target .s carries no relocs; derive from the text
        if rel is None and (v >> 26) in (2, 3):
            rel = '26'
        if not BLIND:
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

    def show(d):
        return '%08x %s' % (d['word'], d['mnem'])

    mine = [key(d) for d in mine_r]
    tgt = [key(d) for d in tgt_r]
    regs = regions()
    if regs[-1][2] is None:
        regs[-1][2] = len(tgt)

    sm = difflib.SequenceMatcher(None, mine, tgt, autojunk=False)
    ok = [False] * len(tgt)
    pair = [None] * len(tgt)
    for i, j, n in sm.get_matching_blocks():
        for k in range(n):
            ok[j + k] = True
            pair[j + k] = i + k
    # for reporting: map each target idx to a nearby mine idx via opcodes
    mymap = {}
    for tag, i1, i2, j1, j2 in sm.get_opcodes():
        if tag == 'equal':
            for d in range(j2 - j1):
                mymap[j1 + d] = i1 + d
        else:
            for d in range(j2 - j1):
                mymap[j1 + d] = i1 + d if i1 + d < i2 else None

    print('mine=%d target=%d  %d target ins unmatched'
          % (len(mine), len(tgt), ok.count(False)))
    print('%-8s %6s %6s  %s' % ('region', 'tgt', 'bad', ''))
    for n, lo, hi in regs:
        bad = sum(1 for k in range(lo, min(hi, len(tgt))) if not ok[k])
        bar = '#' * min(60, bad)
        print('%-8s %6d %6d  %s' % (n, hi - lo, bad, bar))
    if want:
        for n, lo, hi in regs:
            if n != want:
                continue
            print('\n--- %s (target idx %d..%d) ---' % (n, lo, hi))
            for k in range(lo, min(hi, len(tgt))):
                mi = mymap.get(k)
                print('%s %5d | %-40s | %s'
                      % (' ' if ok[k] else '*', k,
                         show(mine_r[mi]) if mi is not None and mi < len(mine_r) else '',
                         show(tgt_r[k])))

main()
