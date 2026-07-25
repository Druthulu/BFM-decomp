import re,subprocess,difflib,sys,collections
OBJ=".run/drafts-behemoth2/work/func_8017D960/t.o"
OBJDUMP="tools/bin/mips-linux-gnu-objdump"
import shutil,os
for c in ["mips-linux-gnu-objdump","mipsel-linux-gnu-objdump","mips-elf-objdump"]:
    if shutil.which(c): OBJDUMP=c;break
out=subprocess.run([OBJDUMP,"-drz",OBJ],capture_output=True,text=True).stdout
mine=[]
for line in out.splitlines():
    m=re.match(r'\s*[0-9a-f]+:\s+[0-9a-f]{8}\s+(\S+)\s*(.*)',line)
    if m: mine.append((m.group(1),m.group(2).split(';')[0].strip()))
tgt=[];cur=None
for line in open("asm/ov_SC03_090/nonmatchings/ov_SC03_090_jr_8017CA80/func_8017D960.s"):
    s=line.strip()
    m=re.match(r'/\* \w+ ([0-9A-F]{8}) \w{8} \*/\s+(\S+)\s*(.*)',s)
    if m: tgt.append((m.group(2),m.group(3).strip()))
NORM={'c2':'GTE','rtpt':'GTE','rtps':'GTE','nclip':'GTE','move':'addu','b':'j','nop':'nop','li':'addiu','beq':'beqz','bne':'bnez','negu':'subu'}
def op(o): return NORM.get(o,o)
a=[op(x[0]) for x in mine]; b=[op(x[0]) for x in tgt]
print("mine",len(a),"target",len(b))
sm=difflib.SequenceMatcher(None,a,b,autojunk=False)
tot=0;blocks=[]
for tag,i1,i2,j1,j2 in sm.get_opcodes():
    if tag=='equal': tot+=i2-i1
    else: blocks.append((tag,i1,i2,j1,j2))
print("opcode-sequence LCS match: %d / %d target ins  = %.1f%%"%(tot,len(b),100.0*tot/len(b)))
print("num divergent hunks:",len(blocks))
for tag,i1,i2,j1,j2 in blocks[:60]:
    print(f"  {tag:8s} mine[{i1}:{i2}] ({i2-i1})  tgt[{j1}:{j2}] ({j2-j1})   tgt-ops={[x for x in b[j1:min(j2,j1+6)]]}  mine-ops={[x for x in a[i1:min(i2,i1+6)]]}")
print("... total hunks",len(blocks))
