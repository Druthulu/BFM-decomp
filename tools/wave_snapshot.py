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

    copied, missing = [], []
    for t in targets:
        fn, src = t['name'], t['source']
        rel = os.path.join(src, 'nonmatchings', src, fn + '.s')
        s = os.path.join(a.asm_root, rel)
        if not os.path.exists(s):
            missing.append(fn)
            continue
        d = os.path.join(a.out, 'asm', rel)
        os.makedirs(os.path.dirname(d), exist_ok=True)
        shutil.copy2(s, d)
        copied.append((rel, sha1(d)))

    os.makedirs(a.out, exist_ok=True)
    with open(os.path.join(a.out, 'MANIFEST.sha1'), 'w') as fh:
        for rel, h in sorted(copied):
            fh.write(f'{h}  {rel}\n')

    print(f'snapshot -> {a.out}/asm   ({len(copied)} .s files, manifest written)')
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
