#!/usr/bin/env python3
"""wave_snapshot.py — give a crack-wave its OWN immutable copy of the .s files it needs.

WHY (the blocker this removes):
    A wave's drafter agents read `asm/<bin>/nonmatchings/<bin>/<fn>.s` and iterate with
    `match_one`. R22's clean-fleet verify starts with `make clean`, which DELETES `asm/`.
    So a running wave blocked the authoritative byte-check, and the whole pipeline
    (draft -> gate -> bank -> R22) had to run strictly serially.

    A wave does not need the LIVE asm tree — it needs the handful of .s files for its own
    targets, and those are immutable for the life of the wave (splat regenerates them
    byte-identically from committed config + symbols; H3/R22). Snapshotting them decouples
    drafting from every tree-mutating step: waves, gates and R22 can then overlap.

WHAT IT GUARANTEES (and what it does not):
    - The snapshot is a byte-for-byte copy, recorded with a sha1 manifest, so a draft is
      always verified against exactly the bytes the wave was scoped against.
    - It does NOT weaken the byte-gate. `match_one` remains a CANDIDATE filter (§52b);
      the whole-binary `harvest_verify` on the live tree is still the sole arbiter (G3/P9).
      A stale snapshot can therefore only cause a wasted draft, never a false bank.
    - R32: fails loud if any requested target has no .s, rather than silently shipping a
      short wave (a wave that quietly drops targets looks identical to a low close-rate).

USAGE
    python3 tools/wave_snapshot.py --targets .run/s45p5/args_wave4.json --out .run/wave4
    -> .run/wave4/asm/<bin>/nonmatchings/<bin>/<fn>.s  + .run/wave4/MANIFEST.sha1
    then point the wave prompt's --asm-subdir at .run/wave4/asm/<bin>/nonmatchings/<bin>
"""
import argparse
import glob
import hashlib
import json
import os
import shutil
import sys


def sha1(p):
    h = hashlib.sha1()
    with open(p, 'rb') as fh:
        for b in iter(lambda: fh.read(65536), b''):
            h.update(b)
    return h.hexdigest()


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('--targets', required=True,
                    help='JSON list of {name, source} (the wave args file)')
    ap.add_argument('--out', required=True, help='snapshot dir, e.g. .run/wave4')
    ap.add_argument('--asm-root', default='asm')
    ap.add_argument('--allow-missing', action='store_true',
                    help='downgrade the R32 coverage assertion to a warning')
    a = ap.parse_args()

    targets = json.load(open(a.targets))
    if isinstance(targets, dict):
        targets = targets.get('targets', [])

    # ---- VALIDITY GATE (S46). Every wave passes through here to get its .s files, so this is the
    # chokepoint where a bad target list can be stopped before a single agent is spawned.
    #
    # WHY IT IS HERE AND NOT LEFT TO THE CALLER: in S46 a 47-target wave burned 9.7M tokens and ~29
    # of the targets were not real — functions paired with the WRONG BINARY by a bad dedup join,
    # addresses landing mid-body inside another function's carve, addresses outside the binary's vram
    # window, and 14 functions that had ALREADY BEEN BANKED in an earlier phase. 87 of 119 agents did
    # nothing but prove those phantoms absent. This tool's own R32 coverage assertion DID fire on that
    # list (24 of 57 found) and was routed around instead of diagnosed. A gate that is a separate
    # command is a gate someone forgets; wiring it in makes the failure mode unreachable.
    try:
        import validate_targets as VT
        rows = VT.validate(targets)
        bad = [(t, v, d) for t, v, d in rows if v != 'OK']
        if bad:
            import collections as _c
            cls = _c.Counter(v for _t, v, _d in bad)
            print(f'wave_snapshot: {len(bad)} of {len(targets)} targets are INVALID — '
                  + ', '.join(f'{k}={n}' for k, n in cls.most_common()), file=sys.stderr)
            for t, v, d in bad[:12]:
                nm = t.get('name') or t.get('n')
                print(f'    [{v}] {nm}: {d}', file=sys.stderr)
            if not a.allow_missing:
                print('Fix the target list (tools/validate_targets.py explains each class), or pass '
                      '--allow-missing to proceed deliberately. An invalid target does not fail '
                      'cheaply: it burns an agent per cascade tier proving it does not exist.',
                      file=sys.stderr)
                return 1
    except ImportError:
        print('wave_snapshot: tools/validate_targets.py not importable — validity gate SKIPPED',
              file=sys.stderr)

    copied, missing = [], []

    # The GENERATED includes, too — not just the .s files.
    #
    # match_one does not merely compile: it ASSEMBLES (AS with -Iinclude, match_one.py:59), and the
    # assembly step needs splat's generated include/*.inc (macro.inc / labels.inc / gte_macros.inc /
    # include_asm.h — e.g. GTE bodies `.include macro.inc`). `make clean` deletes all four. Snapshotting
    # only the .s therefore left a wave HALF-decoupled: it would survive a clean until an agent hit a
    # macro-using function, then fail in a way that looks like a bad draft rather than a missing file.
    # (I claimed the .s snapshot alone fully decoupled waves; it did not. Checked, so recorded.)
    # include/common.h and include/psyq/ are TRACKED and survive a clean — copied anyway so the
    # snapshot is a complete, self-contained -Iinclude root.
    inc_dst = os.path.join(a.out, 'include')
    inc_n = 0
    if os.path.isdir('include'):
        for root, _dirs, files in os.walk('include'):
            for name in files:
                s = os.path.join(root, name)
                d = os.path.join(inc_dst, os.path.relpath(s, 'include'))
                os.makedirs(os.path.dirname(d), exist_ok=True)
                shutil.copy2(s, d)
                inc_n += 1

    for t in targets:
        fn = t.get('name') or t.get('n') or t.get('fn')
        src = t.get('source') or t.get('s') or t.get('binary')
        # THE TU SUBDIR IS NOT THE BINARY NAME (S56). Only a single-TU binary puts its .s at
        # asm/<bin>/nonmatchings/<bin>/; a split overlay puts each function under its own TU stem
        # (asm/ov_SC05_001/nonmatchings/ov_SC05_001_jr_8017BEBC/). Hardcoding the binary name found
        # 9 of 75 wave-Z targets -- and because the R32 assertion below then refused to ship a short
        # snapshot, six consecutive waves hand-rolled the copy and took the S46 VALIDITY GATE above
        # off the path with it. Cards already carry the answer in `sub`; use it, fall back to the
        # old convention, then glob as a last resort so a caller with neither still works.
        cand = []
        if t.get('sub'):
            cand.append(os.path.join(t['sub'], fn + '.s'))
        cand.append(os.path.join(a.asm_root, src, 'nonmatchings', src, fn + '.s'))
        hit = next((c for c in cand if os.path.exists(c)), None)
        if hit is None:
            g = glob.glob(os.path.join(a.asm_root, src, 'nonmatchings', '*', fn + '.s'))
            hit = g[0] if len(g) == 1 else None
        if hit is None:
            missing.append(fn)
            continue
        s = hit
        # Mirror the SOURCE layout under <out>/asm so a prompt can point --asm-subdir at the
        # snapshot and the path shape it sees is identical to the live tree's.
        rel = os.path.relpath(hit, a.asm_root) if not os.path.isabs(hit) and \
              os.path.commonpath([os.path.abspath(hit), os.path.abspath(a.asm_root)]) == \
              os.path.abspath(a.asm_root) else os.path.join(src, 'nonmatchings', src, fn + '.s')
        d = os.path.join(a.out, 'asm', rel)
        os.makedirs(os.path.dirname(d), exist_ok=True)
        shutil.copy2(s, d)
        copied.append((rel, sha1(d)))

    os.makedirs(a.out, exist_ok=True)
    with open(os.path.join(a.out, 'MANIFEST.sha1'), 'w') as fh:
        for rel, h in sorted(copied):
            fh.write(f'{h}  {rel}\n')

    print(f'snapshot -> {a.out}/asm   ({len(copied)} .s files, manifest written)')
    print(f'           {a.out}/include   ({inc_n} files incl. the 4 GENERATED .inc/.h '
          f'`make clean` deletes — pass -I{a.out}/include when assembling)')
    gen = ['macro.inc', 'labels.inc', 'gte_macros.inc', 'include_asm.h']
    absent = [g for g in gen if not os.path.exists(os.path.join(inc_dst, g))]
    if absent:
        # R32: a half-populated include root fails later as a phantom "bad draft"; say so NOW.
        print('COVERAGE WARNING: generated include(s) missing from the snapshot: '
              + ' '.join(absent) + ' — run `make extract` first, or waves will fail on '
              'macro-using (e.g. GTE) functions after a `make clean`.', file=sys.stderr)
    # R32: a silent skip is a defect. A short wave must be loud, not inferred later.
    if missing:
        msg = (f'{len(missing)} target(s) have NO .s under {a.asm_root}/: '
               + ' '.join(missing[:8]) + (' …' if len(missing) > 8 else ''))
        if a.allow_missing:
            print('WARNING (coverage): ' + msg)
        else:
            print('COVERAGE ASSERTION FAILED: ' + msg, file=sys.stderr)
            print('  These would be silently absent from the wave. Fix the target list, '
                  'or pass --allow-missing to proceed deliberately.', file=sys.stderr)
            return 2
    print(f'  point the wave at: {a.out}/asm/<bin>/nonmatchings/<bin>')
    return 0


if __name__ == '__main__':
    sys.exit(main())
