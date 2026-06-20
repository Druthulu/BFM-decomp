#!/usr/bin/env python3
"""Census the shared callees that block the parallel hand-matching wave (Phase 17 canonical-sig layer).

The calibration wave (hand-matching-process.md §7c) hit 60% match_one MATCH but only 33% whole-binary;
the entire gap was SIG CONFLICTS — parallel agents each declare an undeclared-stub shared callee (e.g.
func_80131CA8) with a different guessed signature, which then clash in the one-big-TU ov_SC01_077.c
(`conflicting types for func_X`). 100% compile-errors, ZERO codegen mismatches.

A callee that is already `defined` (engine_core.h DEFINE / inline body) or already `declared` (an extern
written somewhere) is conflict-FREE — gen_harvest_targets resolves it and every draft reuses the one sig.
The conflict set is exactly the `stub` callees (no body, no extern anywhere) that >=2 still-stub wave
targets call. Declaring ONE canonical extern for each (the canonical-sig layer) turns them `declared` ->
the wave stops conflicting on them.

This is read-only. Output: the ranked conflict-callee table + the call-edge status totals.

Usage:
  tools/census_conflict_callees.py [--source ov_SC01_077] [--targets .run/harvest_targets_s3.json]
"""
import argparse, json, os, importlib.util
from collections import defaultdict

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))

_spec = importlib.util.spec_from_file_location('ght', os.path.join(REPO, 'tools/gen_harvest_targets.py'))
_ght = importlib.util.module_from_spec(_spec)
_spec.loader.exec_module(_ght)


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('--source', default='ov_SC01_077')
    ap.add_argument('--targets', default='.run/harvest_targets_s3.json')
    ap.add_argument('--min-callers', type=int, default=2)
    ap.add_argument('--out', default='.run/conflict_callees.json')
    args = ap.parse_args()

    src = args.source
    c_path = os.path.join(REPO, f'src/{src}/{src}.c')
    ec = os.path.join(REPO, 'src/shared/engine_core.h')

    src_sig = _ght.load_sig(os.path.join(REPO, f'.run/sig.{src}.jsonl'))      # addr-int -> {calls,nins,h_exact,reach?}
    stubs = _ght.collect_stubs(c_path)                                         # current INCLUDE_ASM set
    define_sigs = _ght.collect_define_sigs(ec)
    inline_sigs = _ght.collect_inline_sigs(c_path)
    defined = {**define_sigs, **inline_sigs}
    extern_sigs = _ght.collect_extern_sigs([ec, c_path])

    s3 = json.load(open(os.path.join(REPO, args.targets)))
    tgt_addrs = [int(t['addr'], 16) for t in s3]
    remaining = [a for a in tgt_addrs if a in stubs]                           # still-stub wave targets

    def status(caddr):
        if caddr in defined:     return 'defined'
        if caddr in extern_sigs: return 'declared'
        if caddr in stubs:       return 'stub'
        return 'extern'                                                        # resident/EXE, conflict-free

    # reach map (how many overlays hold a byte-identical copy) for prioritization
    reach = {int(t['addr'], 16): t.get('reach', 1) for t in s3}

    callee_callers = defaultdict(set)        # callee_addr -> {target addrs calling it (excl. self)}
    edge_status = defaultdict(int)           # status -> # call edges (over remaining targets)
    for a in remaining:
        rec = src_sig.get(a)
        if not rec:
            continue
        for ch in set(rec.get('calls', [])):
            caddr = int(ch, 16)
            edge_status[status(caddr)] += 1
            if caddr != a:
                callee_callers[caddr].add(a)

    # THE conflict predicate (hand-matching-process.md §7c): a sig conflict needs >=2 INDEPENDENT
    # declarations of an UNDECLARED stub in the one-big-TU build. Declaration sources for callee X =
    # one extern per drafted caller + one definition if X is itself a drafted target (def-vs-extern).
    #   decl_sources = n_callers + (1 if X is a remaining target else 0)
    # An already-`declared`/`defined` callee is conflict-FREE (gen_harvest_targets feeds the one sig).
    conflicts = []
    for caddr, callers in callee_callers.items():
        if status(caddr) != 'stub':
            continue
        is_t = caddr in remaining
        decl_sources = len(callers) + (1 if is_t else 0)
        if decl_sources < 2:
            continue
        crec = src_sig.get(caddr, {})
        conflicts.append({
            'callee': f'func_{caddr:08X}', 'addr': f'{caddr:08X}',
            'n_callers': len(callers), 'is_target': is_t, 'decl_sources': decl_sources,
            'kind': 'match-first' if is_t else 'derive-declare',
            'callee_nins': crec.get('nins'), 'callee_ncalls': len(crec.get('calls', [])),
            'callee_reach': reach.get(caddr, crec.get('reach')),
        })
    conflicts.sort(key=lambda x: (-x['decl_sources'], -(x['callee_reach'] or 0)))

    blocked = {a for a in remaining
               if any(int(ch, 16) in {int(c['addr'], 16) for c in conflicts}
                      for ch in src_sig.get(a, {}).get('calls', []))}
    blk_reach = sum(reach.get(a, 1) for a in blocked)
    tot_reach = sum(reach.get(a, 1) for a in remaining)

    json.dump(conflicts, open(os.path.join(REPO, args.out), 'w'), indent=1)

    print(f'wave scope: {len(s3)} s3 targets, {len(remaining)} still-stub (remaining)')
    print('call-edge status totals (over remaining targets): '
          + '  '.join(f'{k}:{edge_status[k]}' for k in ('defined', 'declared', 'stub', 'extern')))
    mf = sum(1 for c in conflicts if c['is_target'])
    print(f'\nCONFLICT CALLEES (undeclared stub, decl_sources>=2): {len(conflicts)}  '
          f'[{mf} match-first / {len(conflicts)-mf} derive-declare]')
    print(f'{"callee":>16} {"callers":>7} {"isTgt":>5} {"srcs":>4} {"nins":>5} {"ncalls":>6} {"reach":>5}')
    for c in conflicts:
        print(f'{c["callee"]:>16} {c["n_callers"]:>7} {("Y" if c["is_target"] else ""):>5} '
              f'{c["decl_sources"]:>4} {str(c["callee_nins"] or "-"):>5} '
              f'{str(c["callee_ncalls"] or "-"):>6} {str(c["callee_reach"] or "-"):>5}')
    print(f'\nwave targets blocked by >=1 conflict callee: {len(blocked)}/{len(remaining)}  '
          f'(reach-weighted {blk_reach}/{tot_reach} = {100*blk_reach//max(tot_reach,1)}% of wave reach)')
    print(f'wrote {args.out}')


if __name__ == '__main__':
    main()
