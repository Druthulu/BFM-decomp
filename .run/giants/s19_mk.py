#!/usr/bin/env python3
"""Compose variants of the b3 draft from named levers.
usage: mk.py <out.c> lever[,lever...]
levers:
  otparm   - declare `u32 *otp;` inside each of the 4 emit ARMS (drop fn-scope decl)
  tpcase   - declare `u32 *tp;` inside each of the 2 innermost-if blocks (per CASE)
  tparm    - declare `u32 *tp;` inside each of the 4 emit ARMS
  cbmerge  - reuse `cb` as the unlit rgbc temp
  cbcase   - declare `u32 cb;` inside each innermost-if block
  uvwcase  - declare `u32 uvw;` inside the quad innermost-if block
"""
import sys

BASE = '/home/musashi/bfm-decomp/.run/giants/s18_func_8017F510_b3.c'
IFANCH = 'if (my >= -0x6E && mny < 0x6F) {'


def arms(lines):
    out = []
    for i, l in enumerate(lines):
        s = l.strip()
        if s == 'if (f0) {':
            out.append(i)
        elif s == '} else {' and lines[i - 1].strip().startswith('pkt += 0x'):
            out.append(i)
    assert len(out) == 4, out
    return sorted(out)


def cases(lines):
    out = [i for i, l in enumerate(lines) if l.strip() == IFANCH]
    assert len(out) == 2, out
    return out


def insert_at(lines, idxs, decl):
    for i in reversed(idxs):
        ind = ' ' * (len(lines[i]) - len(lines[i].lstrip()) + 4)
        lines.insert(i + 1, ind + decl)


def build(levers, base=BASE):
    s = open(base).read()
    if 'cbmerge' in levers:
        for T in ('PolyFT3', 'PolyFT4'):
            old = '((%s *)pkt)->rgbc = (tp[0] & 0xFF000000) | col;' % T
            new = ('cb = (tp[0] & 0xFF000000) | col;\n'
                   + ' ' * 0 + '@IND@((%s *)pkt)->rgbc = cb;' % T)
            assert old in s, T
            i = s.index(old)
            ind = ' ' * (i - s.rindex('\n', 0, i) - 1)
            s = s.replace(old, new.replace('@IND@', ind), 1)
    lines = s.split('\n')
    if 'otparm' in levers:
        lines = [l for l in lines if l.strip() != 'u32 *otp;']
        insert_at(lines, arms(lines), 'u32 *otp;')
    if 'tparm' in levers:
        lines = [l for l in lines if l.strip() != 'u32 *tp;']
        insert_at(lines, arms(lines), 'u32 *tp;')
    if 'tpcase' in levers:
        lines = [l for l in lines if l.strip() != 'u32 *tp;']
        insert_at(lines, cases(lines), 'u32 *tp;')
    if 'cbcase' in levers:
        lines = [l for l in lines if l.strip() != 'u32 cb;']
        insert_at(lines, cases(lines), 'u32 cb;')
    if 'uvwcase' in levers:
        lines = [l for l in lines if l.strip() != 'u32 uvw;']
        insert_at(lines, [cases(lines)[1]], 'u32 uvw;')
    return '\n'.join(lines)


if __name__ == '__main__':
    out = sys.argv[1]
    lv = [] if sys.argv[2] == 'none' else sys.argv[2].split(',')
    open(out, 'w').write(build(lv))
    print('wrote', out, lv)
