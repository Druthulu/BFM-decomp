import re,sys
F="asm/ov_SC03_090/nonmatchings/ov_SC03_090_jr_8017CA80/func_8017D960.s"
ins=[];cur=None
for line in open(F):
    s=line.strip()
    if s.startswith('.L') and s.endswith(':'): cur=s[:-1]; continue
    m=re.match(r'/\* \w+ ([0-9A-F]{8}) \w{8} \*/\s+(\S+)\s*(.*)',s)
    if m: ins.append((len(ins),m.group(1),m.group(2),m.group(3).strip(),cur)); cur=None
a,b=int(sys.argv[1]),int(sys.argv[2])
for i,ad,op,ar,l in ins[a:b]:
    print(f"{i:5d} {l or '':>12s} {op:9s} {ar}")
