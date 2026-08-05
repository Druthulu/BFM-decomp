#!/usr/bin/env python3
"""Reproduce the wave-6 ALIAS-CLASS link failure and INSPECT the post-carve tree, then revert.

harvest_verify does carve -> build -> revert, so the interesting state (where the asm-label alias
definition ended up relative to its callers) is destroyed before anyone can look at it. This does
the same carve, dumps the evidence, builds to capture the real linker error, and reverts.

READ THE EVIDENCE, DO NOT GUESS: the hypothesis under test is that `jr_isolate_all` repartitions the
TU and separates the call site of `func_<X>` from the DEFINITION that emits it — which in this
overlay is a §37/§124 definition-side asm-label alias:
    void aF8018A860(...) __asm__("func_80183AF8");   /* decl binds the symbol */
    void aF8018A860(...) { ... }                     /* THIS is what emits func_80183AF8 */
A tool that moves code by ADDRESS cannot see that the symbol emitted at 0x80183AF8 is spelled
`aF8018A860` in the source.

Usage: w6_alias_repro.py <ov> <fn> <callee_sym>
"""
import sys, os, re, glob, subprocess, shutil

OV, FN, CALLEE = sys.argv[1], sys.argv[2], sys.argv[3]
PY = '.venv/bin/python'
sys.path.insert(0, 'tools')
import corpus


def sh(cmd, **kw):
    return subprocess.run(cmd, capture_output=True, text=True, **kw)


def snapshot(tag):
    print(f"\n----- {tag} -----")
    files = sorted(glob.glob(f'src/{OV}/*.c'))
    print(f"  TUs in src/{OV}/: {len(files)}")
    for f in files:
        t = open(f).read()
        defs = len(re.findall(r'__asm__\s*\(\s*"' + re.escape(CALLEE) + r'"\s*\)', t))
        refs = len(re.findall(r'\b' + re.escape(CALLEE) + r'\b', t))
        stub = len(re.findall(r'INCLUDE_ASM\([^)]*\b' + re.escape(CALLEE) + r'\b', t))
        if defs or refs or stub:
            print(f"    {os.path.basename(f):<46} asm-label-binds={defs} textual-refs={refs} INCLUDE_ASM={stub}")


st = corpus.stubs(OV)
addr = int(FN.split('_')[1], 16)
rec = st.get(addr)
if not rec:
    sys.exit(f"{FN} is not a live stub in {OV}")
tu, stub_line = rec.path, f'INCLUDE_ASM("{rec.asm_dir}", {rec.symbol});'
draft = open(f'.run/w6/{OV}/{FN}.c').read()

orig = open(tu).read()
assert orig.count(stub_line) == 1, "stub line not unique"
snapshot("BEFORE the carve (HEAD)")

print(f"\n[1] splicing the draft over the stub in {tu}")
open(tu, 'w').write(orig.replace(stub_line, draft, 1))

print(f"[2] jtbl_carve {OV} --func {FN}")
r = sh([PY, 'tools/jtbl_carve.py', OV, '--func', FN])
out = (r.stdout or '') + (r.stderr or '')
print(f"    rc={r.returncode}  {out.strip().splitlines()[-1][:130] if out.strip() else ''}")

if r.returncode:
    print(f"[3] carve refused -> jr_isolate_all --only {FN}  (the §61b ladder: isolate WITH the body spliced)")
    r2 = sh([PY, 'tools/jr_isolate_all.py', OV, '--only', FN])
    print(f"    isolate rc={r2.returncode}")
    r3 = sh(['make', '--no-print-directory', 'extract', f'BINARY={OV}'])
    print(f"    extract rc={r3.returncode}")
    r = sh([PY, 'tools/jtbl_carve.py', OV, '--func', FN])
    print(f"    carve retry rc={r.returncode}")
    sh(['make', '--no-print-directory', 'extract', f'BINARY={OV}'])

snapshot("AFTER the carve/isolation — WHERE DID THE ALIAS DEFINITION GO?")

print(f"\n[4] make build BINARY={OV} — the real linker error")
rb = sh(['make', 'build', f'BINARY={OV}'])
allout = (rb.stdout or '') + (rb.stderr or '')
hits = [l for l in allout.splitlines()
        if 'undefined reference' in l or 'multiple definition' in l or re.search(r'\.[ch]:\d+.*error', l)]
print(f"    build rc={rb.returncode}, {len(hits)} hard diagnostic line(s):")
for l in hits[:10]:
    print("      ", l.strip()[:190])

print("\n[5] reverting")
sh(['git', 'checkout', '--', f'src/{OV}', 'config'])
sh(['git', 'clean', '-fdq', f'src/{OV}'])
sh(['make', '--no-print-directory', 'extract', f'BINARY={OV}'])
print("    reverted + re-extracted (R22 corollary: a reverted config needs a re-extract)")
