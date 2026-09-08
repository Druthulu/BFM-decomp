#!/usr/bin/env python3
"""tools/interleave_check.py <overlay> — the `_JTBL_INTERLEAVE` order in config/overlays.mk must equal the yaml's
subseg sequence (tailN data / .rodata carves / trailing) position by position; any blanket restore of either
file silently breaks that (P31 S62: ov_SC03_015, ov_SC02_005 — extract rot + unwinnable pad searches). Prints
ALIGNED or the first mismatching positions. Zero-token; run after any overlays.mk or splat yaml restore."""
import re,sys
ov=sys.argv[1]
fix='--fix' in sys.argv[2:]
mk=open('config/overlays.mk').read()
# P32 T1a (cookbook §498): a binary may carry `--pre <obj>` BEFORE `--order` (the resident's §8f leading-rodata
# sandwich, `--pre hdr.rodata.o`); the old anchor `:= --order` read such a line as n=0 and reported a false DRIFT.
m=re.search(r'^%s_JTBL_INTERLEAVE := (?:--pre \S+ )?--order (\S+)'%ov,mk,re.M)
order=m.group(1).split(',') if m else []
y=open('config/splat.%s.yaml'%ov).read()
yseq=[]
for a,k,n in re.findall(r'^\s*- \[0x([0-9a-fA-F]+), (\.rodata|data|bin|c), (\S+?)\]',y,re.M):
    if k=='data' and n.startswith('tail'): yseq.append(n+'.data.o')
    elif k=='.rodata': yseq.append(n+'.o')
    elif k=='bin' and n=='trailing': yseq.append('trailing.o')
print('%s order n=%d yaml n=%d %s'%(ov,len(order),len(yseq),'ALIGNED' if order==yseq else 'DRIFT'))
if fix and order!=yseq and m:
    # --fix: the yaml is what `make extract` splits, so the order is REGENERATED from it (never edited by hand)
    new=m.group(0).replace(m.group(1),','.join(yseq))
    mk2=mk.replace(m.group(0),new,1); open('config/overlays.mk','w').write(mk2)
    print('  FIXED: order rewritten from the yaml (%d pieces)'%len(yseq))
for i in range(max(len(order),len(yseq))):
    o=order[i] if i<len(order) else '-'; yy=yseq[i] if i<len(yseq) else '-'
    if o!=yy: print('  !! %-36s | %s'%(o,yy))
