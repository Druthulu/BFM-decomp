#!/usr/bin/env python3
"""Generic scoping/shape sweeper over the current best base.
usage: sweep.py <out.c> <spec>
spec = comma-separated items:
   <declline>@case   move that fn-scope decl line into BOTH innermost-if blocks
   <declline>@arm    move it into all FOUR emit arms
   <declline>@qcase  quad innermost-if only
   <declline>@qarm   quad arms only
declline is matched by its stripped text, e.g. 's32 c0, c1, c2, c3;'
"""
import sys

BASE = '/home/musashi/bfm-decomp/.run/s19/m_otparm+cbmerge.c'
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


def build(spec, base=BASE):
    lines = open(base).read().split('\n')
    for item in spec:
        decl, where = item.rsplit('@', 1)
        n = len(lines)
        lines = [l for l in lines if l.strip() != decl]
        assert len(lines) == n - 1, (decl, n - len(lines))
        if where == 'case':
            idxs = cases(lines)
        elif where == 'qcase':
            idxs = [cases(lines)[1]]
        elif where == 'arm':
            idxs = arms(lines)
        elif where == 'qarm':
            idxs = arms(lines)[2:]
        else:
            raise SystemExit('bad where ' + where)
        for i in reversed(idxs):
            ind = ' ' * (len(lines[i]) - len(lines[i].lstrip()) + 4)
            lines.insert(i + 1, ind + decl)
    return '\n'.join(lines)


if __name__ == '__main__':
    out = sys.argv[1]
    open(out, 'w').write(build(sys.argv[2].split('|')))
    print('wrote', out)
