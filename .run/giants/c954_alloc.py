#!/usr/bin/env python3
"""Allocno census: rank / refs / live-length / priority / granted hard reg,
for the long-lived (global) allocnos of one -da compile work dir.
usage: c954_alloc.py <workdir> [minlen]"""
import re, math, sys

WD = sys.argv[1]
MINLEN = int(sys.argv[2]) if len(sys.argv) > 2 else 150
R = ['zero', 'at', 'v0', 'v1', 'a0', 'a1', 'a2', 'a3', 't0', 't1', 't2', 't3', 't4', 't5', 't6', 't7',
     's0', 's1', 's2', 's3', 's4', 's5', 's6', 's7', 't8', 't9', 'k0', 'k1', 'gp', 'sp', 'fp', 'ra']
lreg = open(WD + '/t.i.lreg').read()
greg = open(WD + '/t.i.greg').read()
info = {}
for m in re.finditer(r'Register (\d+) used (\d+) times across (\d+) insns', lreg):
    info[int(m.group(1))] = (int(m.group(2)), int(m.group(3)))
disp = {}
d = greg.split(';; Register dispositions:')[1].split('\n\n')[0]
for m in re.finditer(r'(\d+) in (\d+)', d):
    disp[int(m.group(1))] = int(m.group(2))
order = [int(x) for x in greg.split('regs to allocate:')[1].split('\n')[0].split()]
print('%-4s %6s %6s %6s %9s  %s' % ('rank', 'pseudo', 'refs', 'len', 'pri', 'reg'))
for k, p in enumerate(order):
    r, l = info.get(p, (0, 0))
    if l < MINLEN:
        continue
    pri = int(math.floor(math.log2(r)) * r / l * 10000) if r > 0 and l else -1
    print('%-4d %6d %6d %6d %9d  %s' % (k, p, r, l, pri, R[disp[p]] if p in disp else 'SPILL'))
