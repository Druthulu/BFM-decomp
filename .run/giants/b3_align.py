"""Shape-agnostic word-level masked sequence aligner (generalised from .run/giants/b2_*.py).

usage: python b3_align.py <obj.o> <target.s> [nhunks]
prints BOTH the register-MASKED (structural) and the register-KEPT (byte) aligned numbers.
"""
import re, subprocess, difflib, shutil, sys, collections

OBJ = sys.argv[1]
TGT = sys.argv[2]
NH = int(sys.argv[3]) if len(sys.argv) > 3 else 60
OD = [c for c in ["mips-linux-gnu-objdump", "mipsel-linux-gnu-objdump"] if shutil.which(c)][0]
out = subprocess.run([OD, "-drz", OBJ], capture_output=True, text=True).stdout


def words_mine():
    w = []
    for line in out.splitlines():
        m = re.match(r'\s*[0-9a-f]+:\s+([0-9a-f]{8})\s', line)
        if m:
            w.append(int(m.group(1), 16))
        elif 'R_MIPS_' in line and w and not isinstance(w[-1], tuple) and (w[-1] >> 26) not in (2, 3):
            w[-1] = ('R', w[-1])
    return w


def words_tgt():
    w = []
    for line in open(TGT):
        m = re.match(r'\s*/\* \w+ [0-9A-F]{8} ([0-9A-F]{8}) \*/\s+(\S+)\s*(.*)', line)
        if m:
            b = bytes.fromhex(m.group(1))
            v = int.from_bytes(b, 'little')
            if '%hi(' in line or '%lo(' in line:
                w.append(('R', v))
            else:
                w.append(v)
    return w


def mask(x, keepimm=True):
    rel = isinstance(x, tuple)
    v = x[1] if rel else x
    op = (v >> 26) & 0x3F
    if op == 0 or op == 0x1C:
        k = (op << 6) | (v & 0x3F) | (((v >> 6) & 0x1F) << 12)
    elif op in (2, 3):
        k = (op << 26)
    elif op in (0x12,):
        k = v & 0xFC1F07FF
    elif op in (1, 4, 5, 6, 7):
        k = (op << 20) | (((v >> 16) & 0x1F) << 8)
    else:
        k = (op << 20) | ((v & 0xFFFF) if (keepimm and not rel) else 0)
    return (k, 'R' if rel else '')


def full(x):
    rel = isinstance(x, tuple)
    v = x[1] if rel else x
    op = (v >> 26) & 0x3F
    if rel:
        return (v & 0xFFFF0000, 'R')
    if op in (2, 3):
        return (op << 26, '')
    if op in (1, 4, 5, 6, 7):
        return (v & 0xFFFF0000, '')
    return (v, '')


wm, wt = words_mine(), words_tgt()
print("mine", len(wm), "target", len(wt))

mt = []
for line in out.splitlines():
    m = re.match(r'\s*[0-9a-f]+:\s+[0-9a-f]{8}\s+(.*)', line)
    if m:
        mt.append(m.group(1).strip())
tt = []
for line in open(TGT):
    m = re.match(r'\s*/\* \w+ [0-9A-F]{8} [0-9A-F]{8} \*/\s+(.*)', line)
    if m:
        tt.append(m.group(1).strip())

for name, fn, show in (("REGISTER-MASKED (structural: opcodes+imms+sp-offsets kept)", mask, True),
                       ("FULL (registers KEPT; relocs + branch displacements masked)", full, False)):
    a = [fn(x) for x in wm]
    b = [fn(x) for x in wt]
    sm = difflib.SequenceMatcher(None, a, b, autojunk=False)
    ops = sm.get_opcodes()
    eq = sum(i2 - i1 for t, i1, i2, j1, j2 in ops if t == 'equal')
    bad = [o for o in ops if o[0] != 'equal']
    print(name)
    print("  aligned-identical %d / %d target ins = %.1f%%" % (eq, len(b), 100.0 * eq / len(b)))
    print("  divergent hunks: %d   total divergent target ins: %d"
          % (len(bad), sum(o[4] - o[3] for o in bad)))
    if show:
        for t, i1, i2, j1, j2 in bad[:NH]:
            print("     %-8s tgt[%d:%d] (%d)  mine[%d:%d] (%d)" % (t, j1, j2, j2 - j1, i1, i2, i2 - i1))
            for k in range(j1, min(j2, j1 + 6)):
                print("        T %4d %s" % (k, tt[k] if k < len(tt) else '??'))
            for k in range(i1, min(i2, i1 + 6)):
                print("        M %4d %s" % (k, mt[k] if k < len(mt) else '??'))
