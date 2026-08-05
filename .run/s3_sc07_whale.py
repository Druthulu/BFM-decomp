#!/usr/bin/env python3
"""S3 — unblock the whale (func_80144B9C) in the 4 SC07 overlays.

The whale is matched in 134/138 overlays via the §38 shared-header route: a per-overlay `-O0` split
file (`<ov>_o0b.c`) whose entire content is `#include "../shared/func_80144B9C.h"`. gcc-2.7.2 has no
per-function optimize pragma, so the opt level is per FILE (§116) — the whale MUST live in its own
`-O0` object or it recompiles at -O2 and stops matching.

The 4 SC07 overlays never got that region: they have `_o0c` but no `_o0b`, and the whale sits in
`<ov>_jr_80140608.c` (an -O2 jr split). So this is not a codegen problem at all — it is 3,080
instructions of code that is BYTE-IDENTICAL to what is already banked elsewhere (h_exact, relocation
payloads included), blocked purely by a missing file boundary.

Per overlay: carve the range into its own -O0 region (o0_subsplit, which reuses jr_isolate_all's
proven plan/config/validation path), re-extract, prove the split alone is BYTE-NEUTRAL, then swap
the whale's INCLUDE_ASM for the shared header and prove it BANKS. Revert that overlay on any failure.
The whole-binary byte-gate is the sole arbiter (G3/P9); a full R22 follows because config changed.

Usage: s3_sc07_whale.py [--dry]
"""
import sys, os, re, subprocess, json

LO, HI = 0x80144B9C, 0x801457A4
OVS = ['ov_SC07_006', 'ov_SC07_007', 'ov_SC07_010', 'ov_SC07_011']
PY = '.venv/bin/python'
DRY = '--dry' in sys.argv
sys.path.insert(0, 'tools')


def sh(*cmd):
    return subprocess.run(list(cmd), capture_output=True, text=True)


def good_sha(ov):
    return open(f'config/check.{ov}.sha').read().split()[0]


def build_ok(ov):
    r = sh('make', '--no-print-directory', 'build', f'BINARY={ov}')
    return r.returncode == 0 and '[ OK ]' in (r.stdout or ''), (r.stdout or '') + (r.stderr or '')


def revert(ov):
    sh('git', 'checkout', '--', f'src/{ov}', 'config')
    sh('git', 'clean', '-fdq', f'src/{ov}')
    sh('make', '--no-print-directory', 'extract', f'BINARY={ov}')


results = {}
for ov in OVS:
    print(f"\n===== {ov} =====", flush=True)
    import importlib, corpus
    for f in (corpus.stubs, corpus.sig, corpus.symbols, corpus.src_files):
        if hasattr(f, 'cache_clear'):
            f.cache_clear()
    if LO not in corpus.stubs(ov):
        print("  whale is not a live stub here — skipping"); results[ov] = 'not-stub'; continue

    r = sh(PY, 'tools/o0_subsplit.py', ov, '--lo', hex(LO), '--hi', hex(HI),
           *(['--dry-run'] if DRY else []))
    out = (r.stdout or '') + (r.stderr or '')
    print('  [subsplit]', out.strip().splitlines()[-1][:150] if out.strip() else f'rc={r.returncode}')
    if r.returncode:
        results[ov] = 'subsplit-fail'; continue
    if DRY:
        results[ov] = 'dry'; continue

    if sh('make', '--no-print-directory', 'extract', f'BINARY={ov}').returncode:
        print("  extract FAILED"); revert(ov); results[ov] = 'extract-fail'; continue

    # The split alone must be BYTE-NEUTRAL — it only moves code between objects.
    ok, log = build_ok(ov)
    if not ok:
        hard = [l for l in log.splitlines() if 'undefined reference' in l or 'error' in l.lower()][:2]
        print("  split is NOT byte-neutral — reverting:", *hard)
        revert(ov); results[ov] = 'split-not-neutral'; continue
    print("  split byte-neutral ✓")

    # Find the new -O0 region file holding the whale and swap the stub for the shared header.
    for f in (corpus.stubs, corpus.sig, corpus.symbols, corpus.src_files):
        if hasattr(f, 'cache_clear'):
            f.cache_clear()
    rec = corpus.stubs(ov).get(LO)
    if rec is None:
        print("  whale vanished from the corpus after the split"); revert(ov); results[ov] = 'lost'; continue
    tu = rec.path
    txt = open(tu).read()
    stub = f'INCLUDE_ASM("{rec.asm_dir}", {rec.symbol});'
    if stub not in txt:
        print(f"  stub line not found verbatim in {tu}"); revert(ov); results[ov] = 'no-stub-line'; continue
    print(f"  whale now in {os.path.basename(tu)} — swapping in the shared header")
    new_txt = txt.replace(stub, '#include "../shared/func_80144B9C.h"', 1)
    # DROP THE AMBIENT DECLS THE HEADER ALSO DECLARES (§8b/§8d).
    # In the 134 working overlays the whale sits in a CLEAN -O0 file (`common.h` + the header only),
    # so the TU's own decls of D_80126B58 / D_801274CC / D_801274D0 live in OTHER TUs and never meet
    # the header's. Here the region was carved out of a jr file, and jr_isolate_all hoists the
    # parent's file-scope decls into every new region as its `ambient` set — so the same TU now
    # declares those symbols twice, with the loose-typed spellings the fleet uses
    # (`extern void *D_801274CC` vs the header's `extern s32 D_801274CC`). The header is byte-proven
    # across 134 overlays, so the AMBIENT copy is the one to drop, and only in this file.
    # BOTH axes: the header declares DATA (D_*) and FUNCTION (func_*) symbols, and the ambient set
    # carried in by the carve can collide on either. The first pass only dropped D_*, and the three
    # remaining overlays then failed on func_801336E8 / func_8005C324 (the memcpy alias) instead.
    hdr_syms = set(re.findall(r'\b(?:D_|func_)[0-9A-Fa-f]{8}\b',
                              open('src/shared/func_80144B9C.h').read()))
    kept, dropped = [], 0
    for line in new_txt.split('\n'):
        st = line.strip()
        # STRIP A TRAILING COMMENT BEFORE THE `;` TEST. The last holdout was
        #   extern void func_8005C324(int,int,int) __asm__("memcpy"); /* Phase-24: ... */
        # which ends with `*/`, so an endswith(';') test skipped it — the §134 shape yet again.
        # Safe to drop HERE specifically: after the carve this file holds only the whale, so its
        # call now emits `func_8005C324` exactly as it does in the 134 overlays where the whale
        # sits in a clean -O0 file with no alias decl in scope. The parent jr file keeps its alias.
        st = re.sub(r'/\*.*?\*/\s*$', '', st).strip()
        st = re.sub(r'//.*$', '', st).strip()
        if st.startswith('extern ') and st.endswith(';') and '{' not in st:
            named = set(re.findall(r'\b(?:D_|func_)[0-9A-Fa-f]{8}\b', st))
            if named and named <= hdr_syms:      # every symbol on this line is header-declared
                dropped += 1
                continue
        kept.append(line)
    if dropped:
        print(f"    dropped {dropped} ambient extern line(s) the shared header already declares")
    open(tu, 'w').write('\n'.join(kept))

    ok, log = build_ok(ov)
    if ok:
        print(f"  ✅ BANKED — {ov} byte-identical with the whale from source")
        results[ov] = 'BANKED'
    else:
        hard = [l for l in log.splitlines()
                if 'undefined reference' in l or 'conflicting' in l or 'error' in l.lower()][:2]
        print("  gate refused:", *[h.strip()[:150] for h in hard])
        revert(ov); results[ov] = 'gate-fail'

print("\n=== S3 SUMMARY ===")
for ov, v in results.items():
    print(f"  {ov:<14} {v}")
print("\nNEXT: R22 (config changed => full blast radius): make clean && make extract-all && make check-all")
