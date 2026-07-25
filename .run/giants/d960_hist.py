#!/usr/bin/env python3
"""Bucketed histogram of FULL(register-kept) divergent target indices.
usage: d960_hist.py <obj.o> [bucket]"""
import sys, re, subprocess, shutil, difflib
sys.path.insert(0, '/home/musashi/bfm-decomp/.run/giants')
OBJ = sys.argv[1]; BK = int(sys.argv[2]) if len(sys.argv) > 2 else 100
TGT = '/home/musashi/bfm-decomp/asm/ov_SC03_090/nonmatchings/ov_SC03_090_jr_8017CA80/func_8017D960.s'
OD = [c for c in ["mips-linux-gnu-objdump","mipsel-linux-gnu-objdump"] if shutil.which(c)][0]
out = subprocess.run([OD,"-drz",OBJ],capture_output=True,text=True).stdout
wm=[]
for line in out.splitlines():
    m=re.match(r'\s*[0-9a-f]+:\s+([0-9a-f]{8})\s',line)
    if m: wm.append(int(m.group(1),16))
    elif 'R_MIPS_' in line and wm and not isinstance(wm[-1],tuple) and (wm[-1]>>26) not in (2,3): wm[-1]=('R',wm[-1])
wt=[]
for line in open(TGT):
    m=re.match(r'\s*/\* \w+ [0-9A-F]{8} ([0-9A-F]{8}) \*/\s+(\S+)\s*(.*)',line)
    if m:
        v=int.from_bytes(bytes.fromhex(m.group(1)),'little')
        wt.append(('R',v) if ('%hi(' in line or '%lo(' in line) else v)
def full(x):
    rel=isinstance(x,tuple); v=x[1] if rel else x; op=(v>>26)&0x3F
    if rel: return (v&0xFFFF0000,'R')
    if op in (2,3): return (op<<26,'')
    if op in (1,4,5,6,7): return (v&0xFFFF0000,'')
    return (v,'')
a=[full(x) for x in wm]; b=[full(x) for x in wt]
sm=difflib.SequenceMatcher(None,a,b,autojunk=False)
bad=[]
for t,i1,i2,j1,j2 in sm.get_opcodes():
    if t!='equal': bad.extend(range(j1,j2))
from collections import Counter
c=Counter(i//BK for i in bad)
print('total divergent %d' % len(bad))
for k in sorted(c): print('  %5d-%5d : %4d %s' % (k*BK,(k+1)*BK-1,c[k],'#'*min(60,c[k])))
