import re, sys
N={0:'zero',1:'at',2:'v0',3:'v1',4:'a0',5:'a1',6:'a2',7:'a3'}
for i in range(8,16): N[i]='t%d'%(i-8)
for i in range(16,24): N[i]='s%d'%(i-16)
N[24]='t8';N[25]='t9';N[26]='k0';N[27]='k1';N[28]='gp';N[29]='sp';N[30]='fp';N[31]='ra'
def norm_cc1(path):
    out=[]
    for l in open(path):
        l=l.split('#')[0].rstrip()
        if not l.strip(): continue
        s=l.strip()
        if s.startswith('.') or s.endswith(':'): continue
        s=re.sub(r'\$(\d+)', lambda m:'$'+N[int(m.group(1))], s)
        s=re.sub(r'\s+',' ',s.replace('\t',' '))
        m=re.match(r'(lw|sw|lh|sh|lb|sb|lbu|lhu) (\$\w+),([A-Za-z_]\w*)$', s)
        if m:
            out.append('lui $at, %%hi(%s)'%m.group(3))
            out.append('%s %s, %%lo(%s)($at)'%(m.group(1),m.group(2),m.group(3)))
            continue
        out.append(s)
    return out
def norm_tgt(path):
    out=[]
    for l in open(path):
        m=re.match(r'\s+/\* [0-9A-F]+ [0-9A-F]{8} [0-9A-F]{8} \*/\s+(.*)',l)
        if not m: continue
        s=re.sub(r'\s+',' ',m.group(1).strip())
        out.append(s)
    return out
if __name__=='__main__':
    a=norm_cc1(sys.argv[1]); b=norm_tgt(sys.argv[2])
    n=int(sys.argv[3]) if len(sys.argv)>3 else 200
    for i in range(min(n,max(len(a),len(b)))):
        x=a[i] if i<len(a) else ''
        y=b[i] if i<len(b) else ''
        def can(z):
            z=z.replace(',',' , ')
            z=re.sub(r'0x([0-9a-fA-F]+)', lambda m:str(int(m.group(1),16)), z)
            z=re.sub(r'\s+',' ',z).strip()
            z=z.replace('addu ','addiu ') if re.search(r'addu \$\w+ , \$\w+ , -?\d', z) else z
            z=re.sub(r'^beq (\$\w+) , \$zero', r'beqz \1', z)
            z=re.sub(r'^bne (\$\w+) , \$zero', r'bnez \1', z)
            z=re.sub(r'^li (\$\w+) , (\d+)$', r'addiu \1 , $zero , \2', z)
            z=re.sub(r'\$L\d+|\.L[0-9A-F]+', 'LBL', z)
            z=re.sub(r'^lui \$\w+ ,', 'lui RD ,', z)
            return z
        mark='   ' if can(x)==can(y) else '<< '
        print(f"{i:4d} {mark}{x:38s} | {y}")
