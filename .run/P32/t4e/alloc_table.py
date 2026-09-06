#!/usr/bin/env python3
"""alloc_table.py <tag> [fn]: from .run/P32/t4e/dumps_<tag>/, print func's pseudos: refs, live insns, block, class, hard reg, priority."""
import re, sys, math
tag=sys.argv[1]; fn=sys.argv[2] if len(sys.argv)>2 else 'func_80039308'
d=f'.run/P32/t4e/dumps_{tag}'
def section(path):
    s=open(path).read()
    i=s.find(f';; Function {fn}\n')
    if i<0: i=s.find(f'Function {fn}\n')
    j=s.find(';; Function ', i+20)
    return s[i:j if j>0 else None]
lreg=section(f'{d}/{tag}.i.lreg'); greg=section(f'{d}/{tag}.i.greg'); flow=section(f'{d}/{tag}.i.flow')
regs={}
for m in re.finditer(r'Register (\d+) used (\d+) times across (\d+) insns(?: in block (-?\d+))?([^\n]*)', lreg):
    n=int(m.group(1)); regs[n]=dict(refs=int(m.group(2)),live=int(m.group(3)),block=m.group(4),extra=m.group(5).strip())
hard={}
for m in re.finditer(r'Register (\d+) in (\d+)\.', greg): hard[int(m.group(1))]=int(m.group(2))
for m in re.finditer(r'Register (\d+) in (\d+)\.', lreg): hard.setdefault(int(m.group(1)),int(m.group(2)))
# label some pseudos from the flow-dump insns
labels={}
for m in re.finditer(r'\(set \(reg/?v?:SI (\d+)\)\s*\(ashift:SI \(reg[^ ]* (\d+)\)\s*\(const_int 8\)\)', flow): labels[int(m.group(1))]=f'ashift8(r{m.group(2)})'
for m in re.finditer(r'\(set \(reg/?v?:SI (\d+)\)\s*\(const_int (\d+)\)\)', flow): labels.setdefault(int(m.group(1)),f'const {m.group(2)}')
for m in re.finditer(r'\(set \(reg/?v?:SI (\d+)\)\s*\(zero_extend:SI \(mem:QI \(reg[^ ]* (\d+)\)', flow): labels.setdefault(int(m.group(1)),f'lbu(r{m.group(2)})')
for m in re.finditer(r'\(set \(reg/?v?:SI (\d+)\)\s*\(reg/?v?:SI (\d+)\)\)', flow): labels.setdefault(int(m.group(1)),f'copy(r{m.group(2)})')
names={16:'s0',17:'s1',18:'s2',19:'s3',20:'s4',21:'s5',22:'s6',23:'s7',30:'fp',8:'t0',9:'t1',10:'t2',11:'t3',12:'t4',13:'t5',14:'t6',15:'t7',24:'t8',25:'t9',2:'v0',3:'v1',4:'a0',5:'a1',6:'a2',7:'a3'}
rows=[]
for n,r in regs.items():
    pri = (math.floor(math.log2(r['refs']))*r['refs']/r['live'])*10000 if r['refs']>0 and r['live']>0 else 0
    rows.append((pri,n,r,hard.get(n),labels.get(n,'')))
rows.sort(key=lambda x:(-x[0],x[1]))
print(f'{tag}: {len(regs)} pseudos; callee-saved holders:')
for pri,n,r,h,l in rows:
    if h is not None and h in (16,17,18,19,20,21,22,23,30):
        print(f'  r{n:<4} -> {names.get(h,h):<3} pri={pri:8.1f} refs={r["refs"]:<3} live={r["live"]:<4} blk={r["block"]} {l} {r["extra"][:40]}')
print('unallocated (no hard reg):', [n for pri,n,r,h,l in rows if h is None][:20])
