"""Register-correspondence census over index-aligned instructions (same length only)."""
import sys,os,collections
sys.path.insert(0,'/home/musashi/bfm-decomp/tools')
import masked_diff, re, subprocess, shutil
OBJ=sys.argv[1]
TGT='/home/musashi/bfm-decomp/asm/ov_SC03_116/nonmatchings/ov_SC03_116_jr_8017AE2C/func_8017BF14.s'
mine=masked_diff.insns_from_object(OBJ,'func_8017BF14')
tgt=masked_diff.insns_from_s(TGT)
R=['zero','at','v0','v1','a0','a1','a2','a3','t0','t1','t2','t3','t4','t5','t6','t7',
   's0','s1','s2','s3','s4','s5','s6','s7','t8','t9','k0','k1','gp','sp','s8','ra']
pairs=collections.Counter()
for i,(a,b) in enumerate(zip(mine,tgt)):
    aw = a if isinstance(a,int) else None
    # use raw words
for i,(a,b) in enumerate(zip(mine,tgt)):
    pass
# simpler: raw words via objdump/target parse
def words_t():
    w=[]
    for l in open(TGT):
        m=re.match(r'\s*/\* \w+ [0-9A-F]{8} ([0-9A-F]{8}) \*/',l)
        if m: w.append(int.from_bytes(bytes.fromhex(m.group(1)),'little'))
    return w
OD=[c for c in ["mips-linux-gnu-objdump","mipsel-linux-gnu-objdump"] if shutil.which(c)][0]
out=subprocess.run([OD,"-drz",OBJ],capture_output=True,text=True).stdout
def words_m():
    w=[];inside=False
    for l in out.splitlines():
        if re.match(r'^[0-9a-f]+ <func_8017BF14>:',l): inside=True;continue
        if inside:
            if re.match(r'^[0-9a-f]+ <',l) and w: break
            m=re.match(r'\s*[0-9a-f]+:\s+([0-9a-f]{8})\s',l)
            if m: w.append(int(m.group(1),16))
    return w
T,M=words_t(),words_m()
print('len',len(M),len(T))
for a,b in zip(M,T):
    if a==b: continue
    if (a>>26)!=(b>>26): continue
    for sh in (21,16,11):
        ra=(a>>sh)&0x1F; rb=(b>>sh)&0x1F
        if ra!=rb: pairs[(R[ra],R[rb])]+=1
for (a,b),n in pairs.most_common(20): print('  mine $%-4s -> target $%-4s  x%d'%(a,b,n))
