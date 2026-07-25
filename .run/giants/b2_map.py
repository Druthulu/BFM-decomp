import re,sys,collections
F="asm/ov_SC03_090/nonmatchings/ov_SC03_090_jr_8017CA80/func_8017D960.s"
ins=[]  # (idx, addr, op, args, label_before)
lbl={}
cur=None
for line in open(F):
    m=re.match(r'\s*\.?(L[0-9A-F]+):',line.strip())
    if line.strip().endswith(':') and line.strip().startswith('.L'):
        cur=line.strip()[:-1]; continue
    m=re.match(r'\s*/\* \w+ ([0-9A-F]{8}) \w{8} \*/\s+(\S+)\s*(.*)',line)
    if m:
        ins.append([len(ins),m.group(1),m.group2 if False else m.group(2),m.group(3).strip(),cur])
        if cur: lbl[cur]=len(ins)-1
        cur=None
# branch edges
back=[];fwd=[]
addr2i={x[1]:x[0] for x in ins}
for i,a,op,args,l in ins:
    m=re.search(r'\.(L[0-9A-F]{8})',args)
    if m and op in ('j','beqz','bnez','bgez','blez','bgtz','bltz','beq','bne','b'):
        t=lbl.get('.'+m.group(1))
        if t is None: continue
        if t<i: back.append((i,t,op))
        else: fwd.append((i,t,op))
print("total ins",len(ins))
print("=== BACK EDGES (loops) ===")
for i,t,op in back:
    print(f"  ins {t:5d} (0x{ins[t][1]}) <- {i:5d} (0x{ins[i][1]})  {op}   bodylen={i-t}")
