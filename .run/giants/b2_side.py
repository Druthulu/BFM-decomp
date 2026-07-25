import re,subprocess,difflib,shutil,sys
exec(open('.run/g2_mask.py').read().split('a=[mask(x)')[0])
wm=words_mine(); wt=words_tgt()
def full(x):
    rel=isinstance(x,tuple); v=x[1] if rel else x
    op=(v>>26)&0x3F
    if rel: return (v & 0xFFFF0000,'R')
    if op in (2,3): return (op<<26,'')
    if op in (1,4,5,6,7): return (v & 0xFFFF0000,'')
    return (v,'')
a=[full(x) for x in wm]; b=[full(x) for x in wt]
sm=difflib.SequenceMatcher(None,a,b,autojunk=False); ops=sm.get_opcodes()
mt=[];_o=subprocess.run([OD,"-drz",OBJ],capture_output=True,text=True).stdout
for line in _o.splitlines():
    m=re.match(r'\s*[0-9a-f]+:\s+[0-9a-f]{8}\s+(.*)',line)
    if m: mt.append(re.sub(r'\s+',' ',m.group(1).strip()))
tt=[]
for line in open("asm/ov_SC03_090/nonmatchings/ov_SC03_090_jr_8017CA80/func_8017D960.s"):
    m=re.match(r'\s*/\* \w+ [0-9A-F]{8} [0-9A-F]{8} \*/\s+(.*)',line)
    if m: tt.append(re.sub(r'\s+',' ',m.group(1).strip()))
lo,hi=int(sys.argv[1]),int(sys.argv[2])
for t,i1,i2,j1,j2 in ops:
    if j2<lo or j1>hi: continue
    for k in range(max(i1,i1),i2) if False else []: pass
    n=max(i2-i1,j2-j1)
    for k in range(n):
        mi=mt[i1+k] if i1+k<i2 else ''
        ti=tt[j1+k] if j1+k<j2 else ''
        mark=' ' if t=='equal' else '*'
        if t=='equal' and not (lo<=j1+k<=hi): continue
        print(f"{mark}{j1+k:5d} | {ti:42s} | {mi}")
