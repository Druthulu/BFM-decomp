"""Structural aligner for func_8017BF14: masks registers AND sp-relative offsets,
so a frame-size drift does not hide real structural divergence.
usage: bf14_shape.py <obj.o> [nhunks] [--min N]"""
import re, subprocess, difflib, shutil, sys
OBJ = sys.argv[1]
TGT = '/home/musashi/bfm-decomp/asm/ov_SC03_116/nonmatchings/ov_SC03_116_jr_8017AE2C/func_8017BF14.s'
NH  = int(sys.argv[2]) if len(sys.argv) > 2 and not sys.argv[2].startswith('-') else 40
MIN = int(sys.argv[sys.argv.index('--min')+1]) if '--min' in sys.argv else 1
OD = [c for c in ["mips-linux-gnu-objdump", "mipsel-linux-gnu-objdump"] if shutil.which(c)][0]
out = subprocess.run([OD, "-drz", OBJ], capture_output=True, text=True).stdout
def words_mine():
    w=[]
    for line in out.splitlines():
        m=re.match(r'\s*[0-9a-f]+:\s+([0-9a-f]{8})\s',line)
        if m: w.append(int(m.group(1),16))
        elif 'R_MIPS_' in line and w and not isinstance(w[-1],tuple) and (w[-1]>>26) not in (2,3):
            w[-1]=('R',w[-1])
    return w
def words_tgt():
    w=[]
    for line in open(TGT):
        m=re.match(r'\s*/\* \w+ [0-9A-F]{8} ([0-9A-F]{8}) \*/\s+(\S+)\s*(.*)',line)
        if m:
            v=int.from_bytes(bytes.fromhex(m.group(1)),'little')
            w.append(('R',v) if ('%hi(' in line or '%lo(' in line) else v)
    return w
MEM = set(range(0x20,0x30)) | {0x32,0x3A}   # lb..sw, lwc2, swc2
def shape(x):
    rel=isinstance(x,tuple); v=x[1] if rel else x
    op=(v>>26)&0x3F
    if op==0 or op==0x1C: k=(op<<12)|(v&0x3F)|(((v>>6)&0x1F)<<7)
    elif op in (2,3): k=(op<<26)
    elif op==0x12: k=v&0xFC1F07FF
    elif op in (1,4,5,6,7): k=(op<<20)|(((v>>16)&0x1F)<<8)
    else:
        imm = 0 if rel else (v & 0xFFFF)
        base=(v>>21)&0x1F
        if op in MEM and base==29: imm=0          # mask sp offsets
        k=(op<<20)|imm
    return (k,'R' if rel else '')
mt=[m.group(1).strip() for m in (re.match(r'\s*[0-9a-f]+:\s+[0-9a-f]{8}\s+(.*)',l) for l in out.splitlines()) if m]
tt=[m.group(1).strip() for m in (re.match(r'\s*/\* \w+ [0-9A-F]{8} [0-9A-F]{8} \*/\s+(.*)',l) for l in open(TGT)) if m]
wm,wt=words_mine(),words_tgt()
a=[shape(x) for x in wm]; b=[shape(x) for x in wt]
sm=difflib.SequenceMatcher(None,a,b,autojunk=False); ops=sm.get_opcodes()
eq=sum(i2-i1 for t,i1,i2,j1,j2 in ops if t=='equal')
bad=[o for o in ops if o[0]!='equal']
print("mine %d target %d  SHAPE-aligned %d/%d = %.1f%%  hunks=%d div-tgt=%d"
      % (len(wm),len(wt),eq,len(b),100.0*eq/len(b),len(bad),sum(o[4]-o[3] for o in bad)))
n=0
for t,i1,i2,j1,j2 in bad:
    if max(j2-j1,i2-i1)<MIN: continue
    n+=1
    if n>NH: break
    print("  %-8s tgt[%d:%d](%d) mine[%d:%d](%d)"%(t,j1,j2,j2-j1,i1,i2,i2-i1))
    for k in range(j1,min(j2,j1+8)): print("     T %4d %s"%(k,tt[k] if k<len(tt) else '??'))
    for k in range(i1,min(i2,i1+8)): print("     M %4d %s"%(k,mt[k] if k<len(mt) else '??'))
