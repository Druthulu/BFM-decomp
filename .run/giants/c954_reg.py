#!/usr/bin/env python3
"""Per-region aligned-identical report (registers KEPT and register-MASKED).
usage: c954_reg.py <obj.o> [tag]
Regions are the target's five switch arms + prologue/dispatch/epilogue."""
import re, subprocess, difflib, sys

OBJ = sys.argv[1]
TAG = sys.argv[2] if len(sys.argv) > 2 else OBJ
TGT = '/home/musashi/bfm-decomp/asm/ov_SC06_029/nonmatchings/ov_SC06_029_jr_8017AE2C/func_8017C954.s'
REGIONS = [("head", 0, 326), ("dispatch", 326, 373), ("A:F3", 373, 485), ("B:FT3", 485, 608),
           ("C:F4", 608, 761), ("D:FT4", 761, 942), ("E:new", 942, 1162), ("tail", 1162, 1194)]

out = subprocess.run(["mipsel-linux-gnu-objdump", "-drz", OBJ], capture_output=True, text=True).stdout


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
        m = re.match(r'\s*/\* \w+ [0-9A-F]{8} ([0-9A-F]{8}) \*/', line)
        if m:
            v = int.from_bytes(bytes.fromhex(m.group(1)), 'little')
            w.append(('R', v) if ('%hi(' in line or '%lo(' in line) else v)
    return w


def mask(x):
    rel = isinstance(x, tuple); v = x[1] if rel else x
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
        k = (op << 20) | (v & 0xFFFF if not rel else 0)
    return (k, 'R' if rel else '')


def full(x):
    rel = isinstance(x, tuple); v = x[1] if rel else x
    op = (v >> 26) & 0x3F
    if rel:
        return (v & 0xFFFF0000, 'R')
    if op in (2, 3):
        return (op << 26, '')
    if op in (1, 4, 5, 6, 7):
        return (v & 0xFFFF0000, '')
    return (v, '')


wm, wt = words_mine(), words_tgt()
res = {}
for name, fn in (("masked", mask), ("kept", full)):
    a = [fn(x) for x in wm]; b = [fn(x) for x in wt]
    ok = [False] * len(b)
    for t, i1, i2, j1, j2 in difflib.SequenceMatcher(None, a, b, autojunk=False).get_opcodes():
        if t == 'equal':
            for j in range(j1, j2):
                ok[j] = True
    res[name] = ok
print("%-22s mine=%d target=%d" % (TAG, len(wm), len(wt)))
for nm, lo, hi in REGIONS:
    n = hi - lo
    mk = sum(res['masked'][lo:hi]); kp = sum(res['kept'][lo:hi])
    print("   %-9s %4d ins   masked %3d/%3d %5.1f%%   kept %3d/%3d %5.1f%%"
          % (nm, n, mk, n, 100.0 * mk / n, kp, n, 100.0 * kp / n))
print("   %-9s %4d ins   masked %3d      %5.1f%%   kept %3d      %5.1f%%"
      % ("TOTAL", len(wt), sum(res['masked']), 100.0 * sum(res['masked']) / len(wt),
         sum(res['kept']), 100.0 * sum(res['kept']) / len(wt)))
