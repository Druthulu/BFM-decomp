"""Stack-slot census: sp-offset -> access counts, for target and one object, side by side."""
import re,subprocess,sys,collections
OBJ=sys.argv[1]
TGT='/home/musashi/bfm-decomp/asm/ov_SC06_029/nonmatchings/ov_SC06_029_jr_8017AE2C/func_8017C954.s'
def cens_t():
    c=collections.defaultdict(collections.Counter)
    for l in open(TGT):
        m=re.match(r'\s*/\* \w+ \w+ \w+ \*/\s+(\S+)\s+\$\w+, (-?0x[0-9A-Fa-f]+)\(\$sp\)',l)
        if m: c[int(m.group(2),16)][m.group(1)]+=1
    return c
def cens_m():
    out=subprocess.run(['mipsel-linux-gnu-objdump','-drz',OBJ],capture_output=True,text=True).stdout
    c=collections.defaultdict(collections.Counter); inside=False
    for l in out.splitlines():
        if re.match(r'^[0-9a-f]+ <func_8017C954>:',l): inside=True; continue
        if inside:
            if re.match(r'^[0-9a-f]+ <',l): break
            m=re.match(r'\s*[0-9a-f]+:\s+[0-9a-f]{8}\s+(\S+)\s+\S+,(-?\d+)\(sp\)',l)
            if m: c[int(m.group(2))][m.group(1)]+=1
    return c
T,M=cens_t(),cens_m()
def fmt(cc): return ' '.join('%s:%d'%(k,v) for k,v in sorted(cc.items()))
print('target slots=%d  mine slots=%d'%(len(T),len(M)))
ks=sorted(set(T)|set(M))
for k in ks:
    print('0x%03X  T[%-28s]  M[%s]'%(k,fmt(T[k]),fmt(M[k])))
