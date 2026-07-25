"""Segment-anchored shape diff. bf14_seg.py <obj.o> <tlo> <thi> <mlo> <mhi> [nh]"""
import re,subprocess,difflib,sys
OBJ=sys.argv[1]; TLO,THI,MLO,MHI=[int(x) for x in sys.argv[2:6]]
NH=int(sys.argv[6]) if len(sys.argv)>6 else 30
TGT='/home/musashi/bfm-decomp/asm/ov_SC03_116/nonmatchings/ov_SC03_116_jr_8017AE2C/func_8017BF14.s'
TW=[];TT=[]
for l in open(TGT):
    m=re.match(r'\s*/\* \w+ [0-9A-F]{8} ([0-9A-F]{8}) \*/\s+(.*?)\s*$',l)
    if m:
        v=int.from_bytes(bytes.fromhex(m.group(1)),'little')
        TW.append(('R',v) if ('%hi(' in l or '%lo(' in l) else v); TT.append(re.sub(r'\s+',' ',m.group(2)))
out=subprocess.run(['mipsel-linux-gnu-objdump','-drz',OBJ],capture_output=True,text=True).stdout
MW=[];MT=[];inside=False
for l in out.splitlines():
    if re.match(r'^[0-9a-f]+ <func_8017BF14>:',l): inside=True;continue
    if inside:
        if re.match(r'^[0-9a-f]+ <',l) and MW: break
        m=re.match(r'\s*[0-9a-f]+:\s+([0-9a-f]{8})\s+(.*)',l)
        if m: MW.append(int(m.group(1),16)); MT.append(re.sub(r'\s+',' ',m.group(2).strip()))
        elif 'R_MIPS_' in l and MW and not isinstance(MW[-1],tuple) and (MW[-1]>>26) not in (2,3):
            MW[-1]=('R',MW[-1])
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
a=[shape(x) for x in MW[MLO:MHI]]; b=[shape(x) for x in TW[TLO:THI]]
sm=difflib.SequenceMatcher(None,a,b,autojunk=False); ops=sm.get_opcodes()
eq=sum(i2-i1 for t,i1,i2,j1,j2 in ops if t=='equal')
print('seg tgt[%d:%d](%d) mine[%d:%d](%d) shape-eq %d = %.1f%%'%(TLO,THI,THI-TLO,MLO,MHI,MHI-MLO,eq,100.0*eq/max(1,THI-TLO)))
n=0
for t,i1,i2,j1,j2 in ops:
    if t=='equal': continue
    n+=1
    if n>NH: break
    print('  %-8s tgt[%d:%d](%d) mine[%d:%d](%d)'%(t,TLO+j1,TLO+j2,j2-j1,MLO+i1,MLO+i2,i2-i1))
    for k in range(j1,min(j2,j1+7)): print('     T %4d %s'%(TLO+k,TT[TLO+k]))
    for k in range(i1,min(i2,i1+7)): print('     M %4d %s'%(MLO+k,MT[MLO+k]))
