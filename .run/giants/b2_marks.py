import re
F="asm/ov_SC03_090/nonmatchings/ov_SC03_090_jr_8017CA80/func_8017D960.s"
ins=[];cur=None;lbl={}
for line in open(F):
    s=line.strip()
    if s.startswith('.L') and s.endswith(':'): cur=s[:-1]; continue
    m=re.match(r'/\* \w+ ([0-9A-F]{8}) \w{8} \*/\s+(\S+)\s*(.*)',s)
    if m:
        ins.append((len(ins),m.group(1),m.group(2),m.group(3).strip(),cur))
        if cur: lbl[cur]=len(ins)-1
        cur=None
KEY=('rtpt','rtps','nclip','cfc2','mfc2','jal','mult','slti','jr')
for i,a,op,ar,l in ins:
    if op in KEY or (op in('swc2','lwc2')): print(f"{i:5d} 0x{a} {op:8s} {ar}")
