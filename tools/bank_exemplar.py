#!/usr/bin/env python3
"""Bank a cracked EXEMPLAR ×1 (carve → splice → staged gate), mirroring jtbl_family_bank.bank()'s
stage ladder (raw → scoped → recovered → reconciled) but for the exemplar's own overlay (no remap).

Usage: bank_exemplar.py <ov> <func> <crack.c>
"""
import os, sys, subprocess, re
sys.path.insert(0, 'tools')
os.chdir('/home/musashi/bfm-decomp')
import jtbl_family_bank as fb
from scope_data_externs import fix as scope_data_fix
from canon_sig_reconcile import reconcile

OV, FUNC, CRACK = sys.argv[1], sys.argv[2], sys.argv[3]


def sh(c):
    return subprocess.run(c, shell=True, capture_output=True, text=True)


dirty = sh("git status --porcelain -- config/ src/").stdout.strip()
assert not dirty, "tree dirty:\n" + dirty[:300]
keep = fb.region_files(OV)

print("== extract (committed config)")
assert sh(f"make --no-print-directory extract BINARY={OV}").returncode == 0

print("== carve")
r = sh(f"python3 tools/jtbl_carve.py {OV} --func {FUNC}")
if r.returncode and "NON-CONTIGUOUS" in (r.stdout + r.stderr):
    print("   [lazy isolation]")
    assert fb.isolate(OV, FUNC).returncode == 0, "isolate failed"
    assert sh(f"make --no-print-directory extract BINARY={OV}").returncode == 0
    r = sh(f"python3 tools/jtbl_carve.py {OV} --func {FUNC}")
assert r.returncode == 0, (r.stdout + r.stderr)[-300:]

print("== re-extract post-carve")
assert sh(f"make --no-print-directory extract BINARY={OV}").returncode == 0

cf = fb.stub_file(OV, FUNC)
print("== stub:", cf)
assert cf
orig = open(cf).read()
m = re.search(rf'INCLUDE_ASM\("[^"]*",\s*{FUNC}\);', orig)
assert m
body = open(CRACK).read()

scoped, moved = scope_data_fix(body, orig, m.start(), FUNC)
base = scoped if moved else body
stages = [("raw", lambda: body)]
if moved:
    stages.append(("scoped", lambda: scoped))
stages += [("recovered", lambda: fb.recover(base, OV, cf, FUNC) or base),
           ("reconciled", lambda: reconcile(FUNC, base, tu_path=cf))]

last_err = ""
for name, make in stages:
    try:
        cand = make()
    except Exception as e:
        last_err = f"{name}: {repr(e)[:90]}"
        continue
    open(cf, 'w').write(orig[:m.start()] + cand + orig[m.end():])
    b = sh(f"make --no-print-directory build BINARY={OV}")
    if b.returncode == 0 and "[ OK ]" in b.stdout:
        print(f"== BANKED ×1 [{name}] — BYTE-IDENTICAL (tree left banked for R22 + commit)")
        sys.exit(0)
    errs = [l.strip()[:120] for l in (b.stdout + b.stderr).split('\n')
            if re.search(r'conflicting|undeclared|parse error|redefinition', l) and 'built-in' not in l]
    last_err = f"{name}: " + (errs[0] if errs else "byte-diff")
    print(f"   [{name}] FAIL — {last_err}" + (f" (+{len(errs)-1} more)" if len(errs) > 1 else ""))
    open(cf, 'w').write(orig)

fb.revert(OV, cf, keep_regions=keep)
print("== reverted; last:", last_err)
sys.exit(1)
