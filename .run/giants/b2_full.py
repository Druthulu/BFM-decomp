import re,subprocess,difflib,shutil
exec(open('.run/g2_mask.py').read().split('a=[mask(x)')[0])
wm=words_mine(); wt=words_tgt()
def full(x):
    rel=isinstance(x,tuple); v=x[1] if rel else x
    op=(v>>26)&0x3F
    if rel: return (v & 0xFFFF0000, 'R')      # mask reloc immediate
    if op in (2,3): return (op<<26,'')
    if op in (1,4,5,6,7): return (v & 0xFFFF0000,'')  # mask branch displacement
    return (v,'')
a=[full(x) for x in wm]; b=[full(x) for x in wt]
sm=difflib.SequenceMatcher(None,a,b,autojunk=False)
ops=sm.get_opcodes()
eq=sum(i2-i1 for t,i1,i2,j1,j2 in ops if t=='equal')
print("FULL (registers KEPT; relocs + branch displacements masked)")
print("  aligned byte-identical %d / %d target ins = %.1f%%"%(eq,len(b),100.0*eq/len(b)))
bad=[]
for t,i1,i2,j1,j2 in ops:
    if t=='equal': continue
    for k in range(j1,j2): bad.append(k)
import collections
h=collections.Counter(k//200*200 for k in bad)
print("  divergent target ins: %d ; distribution by 200-ins bucket:"%len(bad))
for k in sorted(h): print("    tgt[%4d-%4d] %3d"%(k,k+199,h[k]))
