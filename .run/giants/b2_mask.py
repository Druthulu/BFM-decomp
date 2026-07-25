import re,subprocess,difflib,shutil,sys
OBJ=".run/drafts-behemoth2/work/func_8017D960/t.o"
OD=[c for c in ["mips-linux-gnu-objdump","mipsel-linux-gnu-objdump"] if shutil.which(c)][0]
out=subprocess.run([OD,"-drz",OBJ],capture_output=True,text=True).stdout
def words_mine():
    w=[];pend=None
    for line in out.splitlines():
        m=re.match(r'\s*[0-9a-f]+:\s+([0-9a-f]{8})\s',line)
        if m: w.append(int(m.group(1),16))
        elif 'R_MIPS_' in line and w and not isinstance(w[-1],tuple) and (w[-1]>>26) not in (2,3): w[-1]=('R',w[-1])
    return w
def words_tgt():
    w=[]
    for line in open("asm/ov_SC03_090/nonmatchings/ov_SC03_090_jr_8017CA80/func_8017D960.s"):
        m=re.match(r'\s*/\* \w+ [0-9A-F]{8} ([0-9A-F]{8}) \*/\s+(\S+)\s*(.*)',line)
        if m:
            b=bytes.fromhex(m.group(1)); v=int.from_bytes(b,'little')
            if '%hi(' in line or '%lo(' in line: w.append(('R',v))
            else: w.append(v)
    return w
def mask(x,keepimm=True):
    rel = isinstance(x,tuple)
    v = x[1] if rel else x
    op=(v>>26)&0x3F
    if op==0 or op==0x1C: k=(op<<6)|(v&0x3F)|(((v>>6)&0x1F)<<12)   # R: op,funct,shamt
    elif op in (2,3): k=(op<<26)
    elif op in (0x12,): k=v & 0xFC1F07FF                            # cop2
    elif op in (1,4,5,6,7): k=(op<<20)|(((v>>16)&0x1F)<<8)   # branch: mask displacement, keep the rt selector
    else: k=(op<<20)|((v&0xFFFF) if (keepimm and not rel) else 0)
    return (k, 'R' if rel else '')
a=[mask(x) for x in words_mine()]; b=[mask(x) for x in words_tgt()]
print("mine",len(a),"target",len(b))
sm=difflib.SequenceMatcher(None,a,b,autojunk=False)
ops=sm.get_opcodes()
eq=sum(i2-i1 for t,i1,i2,j1,j2 in ops if t=='equal')
print("REGISTER-MASKED (opcodes+immediates+sp-offsets+reloc-class kept):")
print("  aligned-identical %d / %d target ins = %.1f%%"%(eq,len(b),100.0*eq/len(b)))
bad=[o for o in ops if o[0]!='equal']
print("  divergent hunks:",len(bad),"  total divergent target ins:",sum(o[4]-o[3] for o in bad))
for t,i1,i2,j1,j2 in bad[:200]: print(f"     {t:8s} tgt[{j1}:{j2}] ({j2-j1})  mine[{i1}:{i2}] ({i2-i1})")

# --- show actual text for a sample of the replace hunks ---
import re as _re
mt=[];
_out=subprocess.run([OD,"-drz",OBJ],capture_output=True,text=True).stdout
for line in _out.splitlines():
    m=_re.match(r'\s*[0-9a-f]+:\s+[0-9a-f]{8}\s+(.*)',line)
    if m: mt.append(m.group(1).strip())
tt=[]
for line in open("asm/ov_SC03_090/nonmatchings/ov_SC03_090_jr_8017CA80/func_8017D960.s"):
    m=_re.match(r'\s*/\* \w+ [0-9A-F]{8} [0-9A-F]{8} \*/\s+(.*)',line)
    if m: tt.append(m.group(1).strip())
print("\n--- sample of divergent pairs ---")
seen={}
for t,i1,i2,j1,j2 in bad:
    if t!='replace' or (i2-i1)!=1: continue
    key=(mt[i1].split()[0], tt[j1].split()[0])
    seen.setdefault(key,[]).append((j1,tt[j1],mt[i1]))
for k,v in sorted(seen.items(), key=lambda x:-len(x[1])):
    print(f"  [{len(v):3d}x] mine `{k[0]}` vs target `{k[1]}`   e.g. tgt[{v[0][0]}]: {v[0][1]!r}  |  mine: {v[0][2]!r}")
