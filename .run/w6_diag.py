#!/usr/bin/env python3
"""Run the REAL gate path for one (overlay, fn) with the child's FULL output shown.

WHY NOT s36_capture.py: that tool splices the draft straight into the TU and builds. For a
table-bearing function that is the wrong path — the jump table needs its own .rodata carve, and
§61b's law is THE CARVE MUST FOLLOW THE SPLICE, which only harvest_verify does. Splicing without
the carve produces a link/byte failure that is an artifact of the diagnosis, not the draft.

So: derive the TU from corpus.stubs (never trust a recorded path), invoke harvest_verify exactly
as .run/s6f_gate.py does, and print everything it said. Usage: w6_diag.py <drafts_dir> <ov:fn>...
"""
import sys, os, subprocess
sys.path.insert(0, 'tools')
import corpus

DRAFTS = sys.argv[1]
for spec in sys.argv[2:]:
    ov, fn = spec.split(':')
    addr = int(fn.split('_')[1], 16)
    rec = corpus.stubs(ov).get(addr)
    if not rec:
        print(f"== {ov} {fn}: NOT A LIVE STUB (already banked?)")
        continue
    sub = os.path.basename(rec.path)[:-2]
    stage = f".run/w6diag/{ov}"
    os.makedirs(stage, exist_ok=True)
    src_draft = os.path.join(DRAFTS, ov, fn + '.c')
    open(os.path.join(stage, fn + '.c'), 'w').write(open(src_draft).read())
    good = open(f'config/check.{ov}.sha').read().split()[0]
    r = subprocess.run(['.venv/bin/python', 'tools/harvest_verify.py', '--binary', ov,
                        '--src', rec.path, '--asm-subdir', f'{ov}/nonmatchings/{sub}',
                        '--out', f'build/{ov}/{ov}', '--good-sha', good,
                        '--drafts', stage, '--chunk', '1'], capture_output=True, text=True)
    print(f"===== {ov} {fn}  (TU {rec.path}, harvest_verify rc={r.returncode}) =====")
    print((r.stdout or '') + (r.stderr or ''))
