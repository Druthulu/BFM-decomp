"""Per-anchor-segment length + opcode delta. usage: bf14_segh.py <obj.o>"""
import re,subprocess,collections,sys
OBJ=sys.argv[1]
TGT='/home/musashi/bfm-decomp/asm/ov_SC03_116/nonmatchings/ov_SC03_116_jr_8017AE2C/func_8017BF14.s'
T=[];TW=[]
for l in open(TGT):
    m=re.match(r'\s*/\* \w+ [0-9A-F]{8} ([0-9A-F]{8}) \*/\s+(\S+)',l)
    if m: TW.append(int.from_bytes(bytes.fromhex(m.group(1)),'little')); T.append('GTE' if m.group(2) in ('rtps','rtpt','nclip') else m.group(2))
out=subprocess.run(['mipsel-linux-gnu-objdump','-drz',OBJ],capture_output=True,text=True).stdout
alias={'move':'addu','li':'addiu','b':'j','negu':'subu','c2':'GTE'}
M=[];MW=[];inside=False
for l in out.splitlines():
    if re.match(r'^[0-9a-f]+ <func_8017BF14>:',l): inside=True;continue
    if inside:
        if re.match(r'^[0-9a-f]+ <',l) and MW: break
        m=re.match(r'\s*[0-9a-f]+:\s+([0-9a-f]{8})\s+(\S+)',l)
        if m: MW.append(int(m.group(1),16)); M.append(alias.get(m.group(2),m.group(2)))
ta=[i for i,v in enumerate(TW) if (v&0xFC00003F)==0x18]
ma=[i for i,v in enumerate(MW) if (v&0xFC00003F)==0x18]
tb=[0]+ta+[len(T)]; mb=[0]+ma+[len(M)]
print('segments %d/%d'%(len(ta),len(ma)))
for k in range(len(tb)-1):
    ct=collections.Counter(T[tb[k]:tb[k+1]]); cm=collections.Counter(M[mb[k]:mb[k+1]])
    d={x:cm[x]-ct[x] for x in set(ct)|set(cm) if cm[x]!=ct[x]}
    if d: print('seg %2d tgt[%d:%d] mine[%d:%d] len%+d  %s'%(k,tb[k],tb[k+1],mb[k],mb[k+1],
        (mb[k+1]-mb[k])-(tb[k+1]-tb[k]),' '.join('%s%+d'%(a,b) for a,b in sorted(d.items(),key=lambda kv:-abs(kv[1])))))
