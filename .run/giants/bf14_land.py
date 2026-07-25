"""Landmark alignment: index of each occurrence of rare opcodes in mine vs target."""
import re,subprocess,sys,collections
OBJ=sys.argv[1]
TGT='/home/musashi/bfm-decomp/asm/ov_SC03_116/nonmatchings/ov_SC03_116_jr_8017AE2C/func_8017BF14.s'
def tgt():
    o=[]
    for l in open(TGT):
        m=re.match(r'\s*/\* \w+ \w+ \w+ \*/\s+(\S+)',l)
        if m: o.append(m.group(1))
    return o
def mine():
    out=subprocess.run(['mipsel-linux-gnu-objdump','-drz',OBJ],capture_output=True,text=True).stdout
    o=[];inside=False
    alias={'move':'addu','li':'addiu','b':'j','negu':'subu'}
    for l in out.splitlines():
        if re.match(r'^[0-9a-f]+ <func_8017BF14>:',l): inside=True;continue
        if inside:
            if re.match(r'^[0-9a-f]+ <',l): break
            m=re.match(r'\s*[0-9a-f]+:\s+[0-9a-f]{8}\s+(\S+)',l)
            if m: o.append(alias.get(m.group(1),m.group(1)))
    return o
T,M=tgt(),mine()
OPS=sys.argv[2].split(',') if len(sys.argv)>2 else ['mult']
ti=[i for i,x in enumerate(T) if x in OPS]
mi=[i for i,x in enumerate(M) if x in OPS]
print('target %d occurrences, mine %d'%(len(ti),len(mi)))
for k in range(max(len(ti),len(mi))):
    a=ti[k] if k<len(ti) else None; b=mi[k] if k<len(mi) else None
    d=(b-a) if (a is not None and b is not None) else None
    print('%3d  tgt=%-6s mine=%-6s delta=%s'%(k,a,b,d))
