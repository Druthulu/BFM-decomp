#!/usr/bin/env python3
"""Capture the whole-binary blocker for a gate-refused draft: splice -> build -> read the
compiler's OWN error -> revert. Agents cannot run the gate, so a TU-level declaration conflict is
invisible to them (§136a: classify on the build's OUTPUT, never its exit status)."""
import sys, os, re, subprocess, shutil
sys.path.insert(0, 'tools'); import corpus
for spec in sys.argv[1:]:
    ov, fn = spec.split(':')
    addr = int(fn.split('_')[1], 16)
    st = corpus.stubs(ov); rec = st.get(addr)
    if not rec:
        print(f"== {ov} {fn}: NOT A LIVE STUB (already banked?)"); continue
    tu = rec.path
    draft = f".run/s34/{ov}/{fn}.c"
    stub = f'INCLUDE_ASM("{rec.asm_dir}", {fn});'
    t = open(tu).read()
    if t.count(stub) != 1:
        print(f"== {ov} {fn}: stub line not found verbatim in {tu}"); continue
    bak = t
    open(tu, 'w').write(t.replace(stub, open(draft).read()))
    r = subprocess.run(['make', 'build', f'BINARY={ov}'], capture_output=True, text=True)
    open(tu, 'w').write(bak)                      # revert ALWAYS
    out = r.stdout + r.stderr
    # §136a, applied to MYSELF: a narrow keyword filter is exactly how a real error goes unseen.
    # Keep every cc1/ld diagnostic line that names a source position, minus the known SHB noise.
    errs = [l for l in out.splitlines()
            if re.search(r'\.[ch]:\d+|undefined reference|\bError \d+', l)
            and 'built-in function' not in l and 'Makefile:' not in l]
    print(f"== {ov} {fn}  (build rc={r.returncode})")
    if errs:
        for l in errs[:6]: print("   ", l.strip())
    else:
        print("    NO COMPILE ERROR -> the draft builds clean; the miss is a byte DIFF at whole-binary")
