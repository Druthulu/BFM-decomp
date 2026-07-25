"""opcode-histogram delta mine-vs-target (alignment free). usage: bf14_hist.py <obj.o> [--sum]"""
import re,collections,subprocess,sys
OBJ=sys.argv[1]
TGT='/home/musashi/bfm-decomp/asm/ov_SC03_116/nonmatchings/ov_SC03_116_jr_8017AE2C/func_8017BF14.s'
t=collections.Counter()
for l in open(TGT):
    m=re.match(r'\s*/\* \w+ \w+ \w+ \*/\s+(\S+)',l)
    if m: t['GTE' if m.group(1) in ('rtps','rtpt','nclip') else m.group(1)]+=1
out=subprocess.run(['mipsel-linux-gnu-objdump','-drz',OBJ],capture_output=True,text=True).stdout
alias={'move':'addu','li':'addiu','b':'j','negu':'subu','c2':'GTE'}
m=collections.Counter(); inside=False
for l in out.splitlines():
    if re.match(r'^[0-9a-f]+ <func_8017BF14>:',l): inside=True; continue
    if inside:
        if re.match(r'^[0-9a-f]+ <',l): break
        mm=re.match(r'\s*[0-9a-f]+:\s+[0-9a-f]{8}\s+(\S+)',l)
        if mm: m[alias.get(mm.group(1),mm.group(1))]+=1
d={k:m[k]-t[k] for k in set(t)|set(m) if m[k]!=t[k]}
tot=sum(m.values())-sum(t.values())
if '--sum' in sys.argv:
    print('len%+d L1=%d %s'%(tot,sum(abs(v) for v in d.values()),
          ' '.join('%s%+d'%(k,v) for k,v in sorted(d.items(),key=lambda kv:-abs(kv[1])))))
else:
    for k,v in sorted(d.items(),key=lambda kv:-abs(kv[1])): print('%-8s %+d'%(k,v))
    print('TOTAL %+d'%tot)
