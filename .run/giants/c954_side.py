#!/usr/bin/env python3
"""Side-by-side index-wise listing of a compiled object vs target .s over a range.
usage: c954_side.py <obj.o> <lo> <hi> [fn]"""
import sys, os, re, subprocess, shutil
sys.path.insert(0, '/home/musashi/bfm-decomp/tools')
import masked_diff

OBJ = sys.argv[1]; LO = int(sys.argv[2]); HI = int(sys.argv[3])
FN = sys.argv[4] if len(sys.argv) > 4 else 'func_8017C954'
TGT = '/home/musashi/bfm-decomp/asm/ov_SC06_029/nonmatchings/ov_SC06_029_jr_8017AE2C/%s.s' % FN

OD = [c for c in ["mips-linux-gnu-objdump", "mipsel-linux-gnu-objdump"] if shutil.which(c)][0]
out = subprocess.run([OD, "-drz", OBJ], capture_output=True, text=True).stdout
mt = []
inside = False
for line in out.splitlines():
    if re.match(r'^[0-9a-f]+ <%s>:' % FN, line): inside = True; continue
    if inside:
        if re.match(r'^[0-9a-f]+ <', line): break
        m = re.match(r'\s*[0-9a-f]+:\s+[0-9a-f]{8}\s+(.*)', line)
        if m: mt.append(re.sub(r'\s+', ' ', m.group(1).strip()))
tt = []
for line in open(TGT):
    m = re.match(r'\s*/\* \w+ [0-9A-F]{8} [0-9A-F]{8} \*/\s+(.*)', line)
    if m: tt.append(re.sub(r'\s+', ' ', m.group(1).strip().rstrip()))

mine = masked_diff.insns_from_object(OBJ, FN)
tgt = masked_diff.insns_from_s(TGT)
diffs = {i for i, a, b in masked_diff.structured_diff(mine, tgt)}
for k in range(LO, min(HI, max(len(mt), len(tt)))):
    flag = '*' if k in diffs else ' '
    print('%s %4d | %-38s | %s' % (flag, k, mt[k] if k < len(mt) else '', tt[k] if k < len(tt) else ''))
