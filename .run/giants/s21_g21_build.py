#!/usr/bin/env python3
"""Assemble the func_80183814 draft from per-case parts + the verified template.

Case bodies live in parts.py as strings; every spawn-template instance is written
as a single line `/*TEMPLATE(K,S,B)*/` and expanded here from mktmpl.py, so the
template can be re-tuned in ONE place and re-propagated to all 35 sites.
"""
import re, sys, os
HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, HERE)
from s21_g21_mktmpl import tmpl
import s21_g21_parts as parts

TP = re.compile(r'^([ \t]*)/\*TEMPLATE\(([^,]+),([^,]+),([^)]+)\)\*/[ \t]*$', re.M)


def expand(text):
    def rep(m):
        ind = len(m.group(1)) or 8
        return tmpl(m.group(2).strip(), m.group(3).strip(),
                    m.group(4).strip(), indent=ind).rstrip('\n')
    return TP.sub(rep, text)


def main():
    out = [parts.HEADER, parts.PREAMBLE]
    for i in range(21):
        body = getattr(parts, 'C%02d' % i, None)
        out.append('    case %d:\n' % i)
        if body:
            out.append(expand(body))
        out.append('        break;\n')
    out.append(parts.TAIL)
    src = ''.join(out)
    dst = sys.argv[1] if len(sys.argv) > 1 else HERE + '/draft.c'
    open(dst, 'w').write(src)
    n = len(TP.findall(''.join(getattr(parts, 'C%02d' % i, '') for i in range(21))))
    print('wrote %s  (%d lines, %d template sites expanded)'
          % (dst, src.count('\n'), n))


main()
