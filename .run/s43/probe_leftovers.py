#!/usr/bin/env python3
"""P30 S43 — is the '26 unpropagated members' item really cheap fuel?

For every member still open from the S40 propagation, try to mechanically remap it from EVERY
binary where the same function is already matched. A success means it is templatable (cheap fuel,
as the checkpoint claims); a reloc-count mismatch on every source means the body is structurally
distinct and there is nothing to template from — i.e. genuine work, not plumbing.

SCAN, don't sample (S4's lesson): report the rate over the whole set.
"""
import json, os, subprocess, sys
sys.path.insert(0, 'tools')
import corpus, dup_report

LEFTOVERS = {
    'func_801809E4': ['ov_SC01_080', 'ov_SC06_010'], 'func_8017E1AC': ['ov_SC01_084', 'ov_SC07_010'],
    'func_80181BB4': ['ov_SC02_031', 'ov_SC06_033'], 'func_8018676C': ['ov_SC03_007', 'ov_SC03_105'],
    'func_8017DC38': ['ov_SC03_013', 'ov_SC03_114'], 'func_801823F8': ['ov_SC03_118', 'ov_SC03_119'],
    'func_8017ED60': ['ov_SC04_011', 'ov_SC05_018'], 'func_8017E950': ['ov_SC04_018', 'ov_SC04_019'],
    'func_8017F940': ['ov_SC05_002', 'ov_SC06_014'], 'func_8017E02C': ['ov_SC02_026'],
    'func_8017E640': ['ov_SC02_039'], 'func_80183560': ['ov_SC02_041'],
    'func_8018163C': ['ov_SC03_006'], 'func_801853B4': ['ov_SC03_006'],
    'func_80186074': ['ov_SC03_007'], 'func_801814FC': ['ov_SC03_090'],
    'func_8017E3B0': ['ov_SC03_094'], 'func_80181FC4': ['ov_SC03_101'],
    'func_801828A4': ['ov_SC04_002'], 'func_80185DA8': ['ov_SC04_002'],
    'func_80180EB8': ['ov_SC05_004'], 'func_80181490': ['ov_SC05_017'],
}
MAX_SRC = 4

def matched_sources(fn, skip):
    """binaries where fn exists in source and is NOT an open stub (i.e. already matched)."""
    out, nm = [], fn.upper().replace('FUNC_', 'func_')
    for b in sorted(dup_report.BINARIES):
        if b in skip or not b.startswith('ov_'):
            continue
        try:
            if nm in corpus.stubs(b):
                continue
        except Exception:
            continue
        hit = subprocess.run(['bash', '-c', f'grep -rlF "{fn}" src/{b}/ 2>/dev/null | head -1'],
                             capture_output=True, text=True).stdout.strip()
        if hit:
            out.append(b)
        if len(out) >= MAX_SRC:
            break
    return out

os.makedirs('.run/s43/remap', exist_ok=True)
rows, ok, bad = [], 0, 0
for fn, openbins in sorted(LEFTOVERS.items()):
    addr = '0x' + fn.split('_')[1].lower()
    srcs = matched_sources(fn, set(openbins))
    for tgt in openbins:
        res = 'NO-SOURCE'
        for s in srcs:
            out = f'.run/s43/remap/{fn}.{tgt}.c'
            p = subprocess.run(['.venv/bin/python', 'tools/family_remap.py', '--addr', addr,
                                '--from', s, '--to', tgt, '--out', out],
                               capture_output=True, text=True)
            if p.returncode == 0 and os.path.exists(out):
                res = f'REMAPPED from {s}'
                break
            err = (p.stderr or p.stdout or '').strip().splitlines()
            res = ('reloc-mismatch (' + str(len(srcs)) + ' srcs tried): ' +
                   (err[-1][-60:] if err else '?'))
        rows.append((fn, tgt, len(srcs), res))
        if res.startswith('REMAPPED'):
            ok += 1
        else:
            bad += 1
        print(f'  {fn} -> {tgt}: {res}', flush=True)

print(f'\n=== RESULT: {ok} templatable / {bad} not, of {ok+bad} open member instances ===')
json.dump([{'fn': f, 'target': t, 'n_sources': n, 'result': r} for f, t, n, r in rows],
          open('.run/s43/leftover_probe.json', 'w'), indent=1)
