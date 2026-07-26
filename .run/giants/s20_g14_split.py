#!/usr/bin/env python3
"""Split func_80183814.s into per-case files + report per-case jal histogram."""
import re, os, sys, collections

SRC = "asm/ov_SC07_006/nonmatchings/ov_SC07_006_jr_8017BEBC/func_80183814.s"
OUT = ".run/giants/g14/cases"
os.makedirs(OUT, exist_ok=True)

CASES = [0x801838D4,0x80183E80,0x801842E0,0x80184338,0x801848EC,0x80184D50,
         0x80184DF4,0x80185028,0x80185078,0x80185334,0x80185754,0x801857D4,
         0x80185B58,0x80185CF4,0x801860F8,0x8018650C,0x8018690C,0x80186CD0,
         0x80187590,0x80187D20,0x80187F9C,0x801887D0]

lines = open(SRC).read().splitlines()
# parse: keep labels attached
recs = []  # (addr or None, rawline)
for ln in lines:
    m = re.match(r'\s*/\* [0-9A-F]+ ([0-9A-F]{8}) [0-9A-F]{8} \*/\s+(.*)', ln)
    if m:
        recs.append((int(m.group(1),16), m.group(2).rstrip()))
    else:
        recs.append((None, ln.rstrip()))

def emit(name, lo, hi):
    out = []
    for a, t in recs:
        if a is None:
            continue
        if lo <= a < hi:
            out.append("%08X  %s" % (a, t))
    open(os.path.join(OUT, name), "w").write("\n".join(out) + "\n")
    return len(out)

tot = 0
n = emit("pre.txt", 0x80183814, 0x801838D4); tot += n
print("PRE      %4d ins" % n)
for i in range(21):
    n = emit("c%02d.txt" % i, CASES[i], CASES[i+1]); tot += n
    # jal histogram
    txt = open(os.path.join(OUT, "c%02d.txt" % i)).read()
    jals = collections.Counter(re.findall(r'jal\s+(\S+)', txt))
    hot = " ".join("%s x%d" % (k.replace("func_",""), v) for k, v in sorted(jals.items()) if v)
    print("CASE%-3d  %4d ins  @%08X  %s" % (i, n, CASES[i], hot))
last = max(a for a, t in recs if a)
n = emit("tail.txt", 0x801887D0, last + 4); tot += n
print("TAIL     %4d ins" % n)
print("TOTAL   %5d ins" % tot)
