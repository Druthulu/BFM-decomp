import sys; sys.path.insert(0,'tools'); import masked_diff as md
mine = md.insns_from_object('.run/beh/w/func_80183814/t.o')
tgt  = md.insns_from_s('asm/ov_SC07_006/nonmatchings/ov_SC07_006_jr_8017BEBC/func_80183814.s')
BASE=0x80183814
def skel(w,r):
    op=w>>26
    if op in (2,3): return op<<26
    m=md.mask_for(w,r); w&=m
    if m==0: return 0
    if op in (0,0x1c): return (op<<26)|(w&0x7FF)
    if op==1: return (op<<26)|(w&0x1FFFFF)
    return (op<<26)|(w&0xFFFF)
def isbr(w): return (w>>26) in (1,4,5,6,7)
def score(start, ts):
    real=0; br=0; first=None
    m=min(len(ts), len(mine)-start)
    if m<len(ts): return (10**6,0,None)
    for i in range(m):
        a=mine[start+i]; b=ts[i]; r=a['reloc_kind']
        if skel(a['word'],r)!=skel(b['word'],r):
            if isbr(a['word']) and isbr(b['word']) and (a['word']>>26)==(b['word']>>26): br+=1; continue
            real+=1
            if first is None: first=i
    return (real,br,first)
REG=[('PROLOGUE+PRE',BASE+40,0x801838D4),('CASE0',0x801838D4,0x80183E80),('CASE2',0x801842E0,0x80184338),
     ('CASE5',0x80184D50,0x80184DF4),('CASE7',0x80185028,0x80185078),('CASE10',0x80185754,0x801857D4),
     ('CASE12',0x80185B58,0x80185CF4),('TAIL',0x801887D0,0x8018881C)]
print('%-13s %6s %8s %10s %10s %8s'%('region','tgtIns','realDiff','brDispOnly','firstReal','myStart'))
tot_t=0; tot_d=0
for nm,lo,hi in REG:
    ts=tgt[(lo-BASE)//4:(hi-BASE)//4]
    best=None
    for st in range(0,len(mine)-len(ts)+1):
        r,b,f=score(st,ts)
        if best is None or r<best[0]: best=(r,b,f,st)
    r,b,f,st=best
    tot_t+=len(ts); tot_d+=r
    print('%-13s %6d %8d %10d %10s %8d'%(nm,len(ts),r,b,f,st))
print('TOTAL decoded target ins=%d  real skeleton diffs=%d  (%.1f%% skeleton-identical)'%(tot_t,tot_d,100.0*(tot_t-tot_d)/tot_t))
