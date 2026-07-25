"""Anchor-segmented shape alignment (robust against repetitive-block confusion).
Anchors = the 56 `mult` sites (+ start/end). Aligns segment-by-segment.
usage: bf14_ali.py <obj.o> [--worst N]"""
import re,subprocess,difflib,sys
OBJ=sys.argv[1]
TGT='/home/musashi/bfm-decomp/asm/ov_SC03_116/nonmatchings/ov_SC03_116_jr_8017AE2C/func_8017BF14.s'
def load_tgt():
    W=[];T=[]
    for l in open(TGT):
        m=re.match(r'\s*/\* \w+ [0-9A-F]{8} ([0-9A-F]{8}) \*/\s+(.*?)\s*$',l)
        if m:
            v=int.from_bytes(bytes.fromhex(m.group(1)),'little')
            W.append(('R',v) if ('%hi(' in l or '%lo(' in l) else v); T.append(re.sub(r'\s+',' ',m.group(2)))
    return W,T
def load_mine():
    out=subprocess.run(['mipsel-linux-gnu-objdump','-drz',OBJ],capture_output=True,text=True).stdout
    W=[];T=[];inside=False
    for l in out.splitlines():
        if re.match(r'^[0-9a-f]+ <func_8017BF14>:',l): inside=True;continue
        if inside:
            if re.match(r'^[0-9a-f]+ <',l) and W: break
            m=re.match(r'\s*[0-9a-f]+:\s+([0-9a-f]{8})\s+(.*)',l)
            if m: W.append(int(m.group(1),16)); T.append(re.sub(r'\s+',' ',m.group(2).strip()))
            elif 'R_MIPS_' in l and W and not isinstance(W[-1],tuple) and (W[-1]>>26) not in (2,3):
                W[-1]=('R',W[-1])
    return W,T
MEM=set(range(0x20,0x30))|{0x32,0x3A}
def shape(x):
    rel=isinstance(x,tuple); v=x[1] if rel else x
    op=(v>>26)&0x3F
    if op==0 or op==0x1C: return ((op<<12)|(v&0x3F)|(((v>>6)&0x1F)<<7),'R' if rel else '')
    if op in (2,3): return (op<<26,'')
    if op==0x12: return (v&0xFC1F07FF,'')
    if op in (1,4,5,6,7): return ((op<<20)|(((v>>16)&0x1F)<<8),'')
    imm=0 if rel else (v&0xFFFF)
    if op in MEM and ((v>>21)&0x1F)==29: imm=0
    return ((op<<20)|imm,'R' if rel else '')
def full(x):
    rel=isinstance(x,tuple); v=x[1] if rel else x
    op=(v>>26)&0x3F
    if rel: return (v&0xFFFF0000,'R')
    if op in (2,3): return (op<<26,'')
    if op in (1,4,5,6,7): return (v&0xFFFF0000,'')
    return (v,'')

def anchors(W):
    return [i for i,v in enumerate(W) if not isinstance(v,tuple) and (v&0xFC00003F)==0x18]  # SPECIAL mult
TW,TT=load_tgt(); MW,MT=load_mine()
ta=anchors(TW); ma=anchors(MW)
if len(ta)!=len(ma):
    print('ANCHOR-MISMATCH tgt=%d mine=%d (falling back to global)'%(len(ta),len(ma)))
    ta=[];ma=[]
tb=[0]+ta+[len(TW)]; mb=[0]+ma+[len(MW)]
tot=0; ftot=0; segs=[]
for k in range(len(tb)-1):
    a=[shape(x) for x in MW[mb[k]:mb[k+1]]]; b=[shape(x) for x in TW[tb[k]:tb[k+1]]]
    sm=difflib.SequenceMatcher(None,a,b,autojunk=False)
    eq=sum(i2-i1 for t,i1,i2,j1,j2 in sm.get_opcodes() if t=='equal')
    fa=[full(x) for x in MW[mb[k]:mb[k+1]]]; fb=[full(x) for x in TW[tb[k]:tb[k+1]]]
    fsm=difflib.SequenceMatcher(None,fa,fb,autojunk=False)
    feq=sum(i2-i1 for t,i1,i2,j1,j2 in fsm.get_opcodes() if t=='equal')
    tot+=eq; ftot+=feq; segs.append((tb[k+1]-tb[k]-eq, k, tb[k],tb[k+1], mb[k],mb[k+1]))
print('ANCHOR-ALIGNED shape %d / %d = %.2f%%   BYTE %d = %.2f%%   (mine=%d target=%d)'
      %(tot,len(TW),100.0*tot/len(TW),ftot,100.0*ftot/len(TW),len(MW),len(TW)))
if '--worst' in sys.argv:
    n=int(sys.argv[sys.argv.index('--worst')+1])
    for bad,k,t0,t1,m0,m1 in sorted(segs,reverse=True)[:n]:
        print('  seg %3d bad=%4d tgt[%d:%d](%d) mine[%d:%d](%d)'%(k,bad,t0,t1,t1-t0,m0,m1,m1-m0))
