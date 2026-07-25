"""Full positional diff (same-length assumption) + register-permutation class summary."""
import re, subprocess, shutil, sys, collections

OBJ = sys.argv[1]
TGT = sys.argv[2]
OD = [c for c in ["mips-linux-gnu-objdump", "mipsel-linux-gnu-objdump"] if shutil.which(c)][0]
out = subprocess.run([OD, "-drz", OBJ], capture_output=True, text=True).stdout

mw, mt = [], []
for line in out.splitlines():
    m = re.match(r'\s*[0-9a-f]+:\s+([0-9a-f]{8})\s+(.*)', line)
    if m:
        mw.append(int(m.group(1), 16)); mt.append(m.group(2).strip())
    elif 'R_MIPS_' in line and mw and not isinstance(mw[-1], tuple) and (mw[-1] >> 26) not in (2, 3):
        mw[-1] = ('R', mw[-1])
tw, tt = [], []
for line in open(TGT):
    m = re.match(r'\s*/\* \w+ [0-9A-F]{8} ([0-9A-F]{8}) \*/\s+(.*)', line)
    if m:
        v = int.from_bytes(bytes.fromhex(m.group(1)), 'little')
        tw.append(('R', v) if ('%hi(' in line or '%lo(' in line) else v)
        tt.append(m.group(2).strip())


def norm(x):
    rel = isinstance(x, tuple); v = x[1] if rel else x
    op = (v >> 26) & 0x3F
    if rel: return (v & 0xFFFF0000, 'R')
    if op in (2, 3): return (op << 26, '')
    if op in (1, 4, 5, 6, 7): return (v & 0xFFFF0000, '')
    return (v, '')


print("mine %d target %d" % (len(mw), len(tw)))
n = min(len(mw), len(tw))
bad = [i for i in range(n) if norm(mw[i]) != norm(tw[i])]
print("positional mismatches: %d" % len(bad))
buckets = collections.Counter(i // 100 * 100 for i in bad)
print("by 100-ins bucket:", dict(sorted(buckets.items())))
for i in bad:
    print("  %4d | %-34s | %s" % (i, mt[i], tt[i]))
