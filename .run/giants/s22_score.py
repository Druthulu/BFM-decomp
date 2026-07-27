import sys, re, importlib.util
spec=importlib.util.spec_from_file_location('n','/home/musashi/bfm-decomp/.run/giants/s22_norm.py')
n=importlib.util.module_from_spec(spec); spec.loader.exec_module(n)
def can(z):
    z=z.replace(',',' , ')
    z=re.sub(r'0x([0-9a-fA-F]+)', lambda m:str(int(m.group(1),16)), z)
    z=re.sub(r'\s+',' ',z).strip()
    if re.search(r'addu \$\w+ , \$\w+ , -?\d', z): z=z.replace('addu ','addiu ',1)
    z=re.sub(r'^beq (\$\w+) , \$zero', r'beqz \1', z)
    z=re.sub(r'^bne (\$\w+) , \$zero', r'bnez \1', z)
    z=re.sub(r'^li (\$\w+) , (\d+)$', r'addiu \1 , $zero , \2', z)
    z=re.sub(r'\$L\d+|\.L[0-9A-F]+', 'LBL', z)
    z=re.sub(r'^lui \$\w+ ,', 'lui RD ,', z)
    return z
a=[can(x) for x in n.norm_cc1(sys.argv[1])]
b=[can(x) for x in n.norm_tgt(sys.argv[2])]
lim=int(sys.argv[3]) if len(sys.argv)>3 else len(b)
same=sum(1 for i in range(min(lim,len(a),len(b))) if a[i]==b[i])
print(f"len_mine={len(a)} len_tgt={len(b)} match_first_{lim}={same}")
if len(sys.argv)>4:
    for i in range(min(lim,max(len(a),len(b)))):
        x=a[i] if i<len(a) else ''; y=b[i] if i<len(b) else ''
        if x!=y: print(f"{i:5d} << {x:40s} | {y}")
