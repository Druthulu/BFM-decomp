#!/usr/bin/env python3
"""t7_bank.py — Phase-25 T7 tier-M1 driver: reconcile-at-bank-time + whole-binary gate.

The T6 curriculum (docs/phase25-t6-curriculum.md) proved 44 family exemplars bank via
canon_sig_reconcile v3.1. This drives the banking with the curriculum's discipline:

  * reconcile EACH still-stubbed target against the CURRENT TU (each bank mutates ambient
    truth for the next — so re-reconcile every iteration, clearing csr's caches);
  * stage the reconciled drafts, run tools/harvest_verify.py (the whole-binary byte-gate,
    G3/P9, the SOLE arbiter — the probe's in-TU masked compare is jal-symbol-blind);
  * --good-sha from config/check.<bin>.sha (NEVER hand-typed);
  * loop per split until no new banks (handles cross-fn conflicts: a fn that fails because
    a sibling banked below it re-reconciles against the updated TU next round);
  * giants first within each split.

Usage:
  tools/t7_bank.py --tier M1                      # all M1 splits
  tools/t7_bank.py --tier M1 --split ov_SC01_077.c  # one split (pilot)
  tools/t7_bank.py --tier M1 --chunk 12
"""
import json, os, re, sys, shutil, subprocess, importlib.util, argparse
from collections import defaultdict

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
os.chdir(REPO)

spec = importlib.util.spec_from_file_location('csr', 'tools/canon_sig_reconcile.py')
csr = importlib.util.module_from_spec(spec)
spec.loader.exec_module(csr)

BIN = 'ov_SC01_077'
GOOD_SHA = open(f'config/check.{BIN}.sha').read().split()[0]


def subdir_of(split):                       # ov_SC01_077_a.c -> ov_SC01_077_a
    return split[:-2]


def stubbed_in(tu_path, subdir, fns):
    tu = open(tu_path).read()
    return [f for f in fns
            if re.search(r'INCLUDE_ASM\("asm/' + re.escape(BIN) + '/nonmatchings/'
                         + re.escape(subdir) + r'",\s*' + f + r'\);', tu)]


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('--tier', default='M1')
    ap.add_argument('--split', default=None, help='limit to one split .c (pilot)')
    ap.add_argument('--chunk', type=int, default=12)
    ap.add_argument('--worklist', default='.run/t6_worklist.json')
    a = ap.parse_args()

    wl = json.load(open(a.worklist))
    targets = wl[a.tier]
    by_split = defaultdict(list)
    for t in targets:
        by_split[t['src']].append(t)

    banked_all, failed_all = [], []
    splits = [a.split] if a.split else list(by_split)
    for split in splits:
        items = sorted(by_split[split], key=lambda t: -t['nins'])   # giants first
        subdir = subdir_of(split)
        tu_path = f'src/{BIN}/{split}'
        stage = f'.run/t7_stage_{subdir}'
        print(f'\n########## split {split}  ({len(items)} M1 targets) ##########')
        rounds = 0
        while True:
            rounds += 1
            stub = stubbed_in(tu_path, subdir, [t['fn'] for t in items])
            if not stub:
                break
            by_fn = {t['fn']: t for t in items}
            # reconcile each still-stubbed target against the CURRENT TU
            csr._AMBIENT_CACHE.clear(); csr._VISIBLE_CACHE.clear()
            shutil.rmtree(stage, ignore_errors=True); os.makedirs(stage)
            n_recon = 0
            for fn in stub:
                try:
                    out = csr.reconcile(fn, open(by_fn[fn]['draft']).read(), None, tu_path)
                    open(f'{stage}/{fn}.c', 'w').write(out)
                    n_recon += 1
                except Exception as e:
                    print(f'  ! reconcile {fn}: {e}')
            print(f'  round {rounds}: {len(stub)} stubbed, {n_recon} reconciled -> gate')
            before = set(stubbed_in(tu_path, subdir, [t['fn'] for t in items]))
            subprocess.run(['python3', 'tools/harvest_verify.py', '--binary', BIN,
                            '--src', tu_path, '--asm-subdir',
                            f'asm/{BIN}/nonmatchings/{subdir}', '--drafts', stage,
                            '--good-sha', GOOD_SHA, '--chunk', str(a.chunk),
                            '--out', f'build/{BIN}/{BIN}',          # NOT the resident default
                            '--verified-out', f'.run/t7_verified_{subdir}.txt',
                            '--failed-out', f'.run/t7_failed_{subdir}.txt'],
                           check=False)
            after = set(stubbed_in(tu_path, subdir, [t['fn'] for t in items]))
            newly = before - after
            print(f'  round {rounds}: banked {len(newly)}')
            if not newly:                       # no progress -> the rest are genuine residue
                failed_all += sorted(after)
                break
            banked_all += sorted(newly)
    print('\n==================== T7 %s SUMMARY ====================' % a.tier)
    print('banked : %d  %s' % (len(banked_all), ' '.join(sorted(banked_all))))
    print('residue: %d  %s' % (len(failed_all), ' '.join(sorted(failed_all))))


if __name__ == '__main__':
    main()
