#!/usr/bin/env python3
"""Extract the 35 spawn-template instances + verify they are one template."""
import re, os, glob, sys

D = ".run/giants/g14/cases"
rows = []
bodies = {}
for f in sorted(glob.glob(D + "/c*.txt")):
    case = int(os.path.basename(f)[1:3])
    lines = [l.split(None, 1) for l in open(f).read().splitlines() if l.strip()]
    for i, (a, t) in enumerate(lines):
        if "func_8012EC04" not in t:
            continue
        # forward window: jal .. the loop-closing bnez (first bnez after the slti $s4)
        fwd = lines[i:i + 100]
        ftxt = "\n".join(x[1] for x in fwd)
        end = None
        for k, (aa, tt) in enumerate(fwd):
            if re.match(r'slti\s+\$v0, \$s4,', tt):
                end = k + 2
                break
        assert end, (case, a)
        blk = lines[i:i + end + 1]
        ftxt = "\n".join(x[1] for x in blk)
        pre = "\n".join(x[1] for x in lines[max(0, i - 12):i + 2])

        def g(pat, txt=None, d="?"):
            m = re.search(pat, txt if txt is not None else ftxt)
            return m.group(1) if m else d
        m = re.findall(r'addiu\s+\$a1, \$zero, (0x[0-9A-Fa-f]+)', pre)
        kind = m[-1] if m else "?"
        m = re.findall(r'addiu\s+\$s5, \$zero, (0x[0-9A-Fa-f]+)', pre)
        s5 = m[-1] if m else "(carry)"
        arr = g(r'%hi\((D_[0-9A-F]+)\)')
        both = pre + "\n" + ftxt
        start = "0x0" if re.search(r'addu\s+\$s4, \$zero, \$zero', both) \
                else g(r'addiu\s+\$s4, \$zero, (0x[0-9A-Fa-f]+)', both)
        bound = g(r'slti\s+\$v0, \$s4, (0x[0-9A-Fa-f]+)')
        memb = g(r'lw\s+\$a0, (0x[0-9A-Fa-f]+)\(\$v0\)')
        rows.append([case, a, kind, s5, arr, start, bound, memb, len(blk)])
        # normalised body for template-identity check: mask consts+syms
        norm = re.sub(r'0x[0-9A-Fa-f]+', '#', ftxt)
        norm = re.sub(r'D_[0-9A-F]+', 'SYM', norm)
        norm = re.sub(r'\.L[0-9A-F]+', 'LBL', norm)
        norm = re.sub(r'addu\s+\$s4, \$zero, \$zero', 'addiu $s4, $zero, #', norm)
        bodies.setdefault(norm, []).append((case, a))

print("%-4s %-9s %-5s %-8s %-11s %-5s %-5s %-5s %-4s  %s" %
      ("case","addr","kind","s5","array","start","bound","memb","ins","checks"))
for r in rows:
    k = int(r[2], 16); memb = r[7]
    chk = []
    chk.append("memb=k*4" if memb != "?" and int(memb,16) == k*4 else "MEMB!%s" % memb)
    off = (int(r[5],16))*4
    exp = 0x801F61C0 + off
    chk.append("arr ok" if r[4] == "D_%08X" % exp else "ARR! exp %X" % exp)
    print("%-4d %-9s %-5s %-8s %-11s %-5s %-5s %-5s %-4d  %s" %
          (r[0],r[1],r[2],r[3],r[4],r[5],r[6],r[7],r[8], " ".join(chk)))
print("count =", len(rows))
print("\ndistinct normalised bodies =", len(bodies))
for b, w in bodies.items():
    print("  variant: %d instances  len=%d  e.g. %s" % (len(w), b.count("\n")+1, w[0]))
ks = sorted(bodies.items(), key=lambda kv: -len(kv[1]))
if len(ks) > 1:
    import difflib
    a = ks[0][0].splitlines();
    for other in ks[1:]:
        print("\n--- diff vs variant %s ---" % (other[1][0],))
        for l in difflib.unified_diff(a, other[0].splitlines(), lineterm="", n=1):
            print("   ", l)
