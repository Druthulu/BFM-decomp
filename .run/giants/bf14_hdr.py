#!/usr/bin/env python3
"""Splice a new dossier header (lines 4..135 of the b1-derived draft) into the
winning round-2 draft.  usage: bf14_hdr.py <src.c> <hdr.txt> <out.c>"""
import sys
src = open(sys.argv[1]).read().splitlines(True)
hdr = open(sys.argv[2]).read()
assert src[3].startswith('/* ====='), src[3]
assert src[134].rstrip().endswith('=== */'), src[134]
open(sys.argv[3], 'w').write(''.join(src[:3]) + hdr + ''.join(src[135:]))
print('wrote', sys.argv[3])
