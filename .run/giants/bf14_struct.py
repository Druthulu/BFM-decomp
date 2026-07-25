#!/usr/bin/env python3
"""Structure map of func_8017BF14's target asm: labels, branch edges, loops."""
import re, sys, collections
F='/home/musashi/bfm-decomp/asm/ov_SC03_116/nonmatchings/ov_SC03_116_jr_8017AE2C/func_8017BF14.s'
ins=[]   # (idx, addr, text)
lab={}   # label -> idx
lines=open(F).read().splitlines()
idx=0
pend=[]
for L in lines:
    m=re.match(r'\s*\.?(\.L[0-9A-F]+):',L) or re.match(r'\s*(\.L[0-9A-F]+):',L)
    if m: lab[m.group(1)]=idx; continue
    m=re.match(r'\s*/\* \w+ ([0-9A-F]{8}) [0-9A-F]{8} \*/\s+(.*?)\s*$',L)
    if m:
        ins.append((idx,int(m.group(1),16),re.sub(r'\s+',' ',m.group(2))))
        idx+=1
addr2idx={a:i for i,a,t in ins}
idx2addr={i:a for i,a,t in ins}
# edges
edges=collections.defaultdict(list)
for i,a,t in ins:
    m=re.search(r'\b(b\w*|j)\s+.*?(\.L[0-9A-F]+)',t)
    if m and m.group(2) in lab:
        edges[lab[m.group(2)]].append(i)
if '--labels' in sys.argv:
    for name,i in sorted(lab.items(), key=lambda kv:kv[1]):
        srcs=edges.get(i,[])
        back=[s for s in srcs if s>i]
        print('%-14s idx=%5d addr=%08X  preds=%d %s' % (name,i,idx2addr.get(i,0),len(srcs),
              ('  <== LOOP back from %s' % back) if back else ''))
if '--loops' in sys.argv:
    for name,i in sorted(lab.items(), key=lambda kv:kv[1]):
        back=[s for s in edges.get(i,[]) if s>i]
        if back:
            print('LOOP head %-12s idx=%5d addr=%08X  body %d ins, back-edges at %s' %
                  (name,i,idx2addr.get(i,0),max(back)-i+1,[idx2addr[b] for b in back]))
if '--dump' in sys.argv:
    lo=int(sys.argv[sys.argv.index('--dump')+1]); hi=int(sys.argv[sys.argv.index('--dump')+2])
    rev={v:k for k,v in lab.items()}
    for i,a,t in ins[lo:hi]:
        if i in rev: print('%s:' % rev[i])
        print('%5d %08X  %s' % (i,a,t))
print('# total ins=%d labels=%d' % (len(ins),len(lab)), file=sys.stderr)
