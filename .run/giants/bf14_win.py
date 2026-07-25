"""Windowed side-by-side: bf14_win.py <obj.o> <tlo> <thi> <mlo>"""
import re,subprocess,sys
OBJ=sys.argv[1]; TLO=int(sys.argv[2]); THI=int(sys.argv[3]); MLO=int(sys.argv[4])
TGT='/home/musashi/bfm-decomp/asm/ov_SC03_116/nonmatchings/ov_SC03_116_jr_8017AE2C/func_8017BF14.s'
T=[]
for l in open(TGT):
    m=re.match(r'\s*/\* \w+ \w+ \w+ \*/\s+(.*?)\s*$',l)
    if m: T.append(re.sub(r'\s+',' ',m.group(1)))
out=subprocess.run(['mipsel-linux-gnu-objdump','-drz',OBJ],capture_output=True,text=True).stdout
M=[];inside=False
for l in out.splitlines():
    if re.match(r'^[0-9a-f]+ <func_8017BF14>:',l): inside=True;continue
    if inside:
        if re.match(r'^[0-9a-f]+ <',l): break
        m=re.match(r'\s*[0-9a-f]+:\s+[0-9a-f]{8}\s+(.*)',l)
        if m: M.append(re.sub(r'\s+',' ',m.group(1).strip()))
n=THI-TLO
for k in range(n):
    ti=TLO+k; mi=MLO+k
    print('%5d %-38s | %5d %s'%(ti,T[ti] if ti<len(T) else '',mi,M[mi] if mi<len(M) else ''))
