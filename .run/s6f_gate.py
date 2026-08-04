#!/usr/bin/env python3
"""Gate the S6f wave drafts — grouping DERIVED from corpus.stubs, never asserted.

The wave manifest I hand-transcribed carried wrong `_jr_*` split names for three overlays (the agents
caught it). So this driver never trusts a recorded path: for every draft on disk it asks corpus.stubs
where that function's INCLUDE_ASM actually lives, groups by (binary, split), and runs the whole-binary
byte-gate once per group. The gate is the sole arbiter (G3/P9).
"""
import sys, os, re, glob, subprocess, collections, shutil
sys.path.insert(0, 'tools')
import corpus

STAGE = '.run/s6f_stage'
shutil.rmtree(STAGE, ignore_errors=True)
groups = collections.defaultdict(list)
skipped = []

for d in sorted(glob.glob(sys.argv[1] if len(sys.argv)>1 else '.run/s6f/*/*.c')):
    ov = os.path.basename(os.path.dirname(d))
    fn = os.path.basename(d)[:-2]
    # S35: an agent left scratch files (test_licm*.c) in the drafts dir and this line died on
    # int('full', 16), taking the whole gate with it. A drafts dir is agent-writable, so treat a
    # non-conforming name as a NAMED, COUNTED skip — never a crash (R32).
    m_ = re.fullmatch(r'func_([0-9A-Fa-f]{8})', fn)
    if not m_:
        skipped.append((ov, fn, 'not a func_<ADDR>.c deliverable — agent scratch?'))
        continue
    addr = int(m_.group(1), 16)
    st = corpus.stubs(ov)
    if addr not in st:
        skipped.append((ov, fn, 'not a live stub (already banked?)'))
        continue
    rec = st[addr]
    tu = rec.path if hasattr(rec, 'path') else rec[0]
    subdir = getattr(rec, 'subdir', None) or os.path.basename(tu)[:-2]
    groups[(ov, tu, subdir)].append((fn, d))

print(f"[gate] {sum(len(v) for v in groups.values())} drafts / {len(groups)} groups; skipped {len(skipped)}")
for s in skipped:
    print("   skip:", s)

banked, failed, unaccounted = [], [], []
for (ov, tu, subdir), items in sorted(groups.items()):
    gdir = os.path.join(STAGE, ov)
    os.makedirs(gdir, exist_ok=True)
    for fn, d in items:
        shutil.copy(d, os.path.join(gdir, fn + '.c'))
    good = open(f'config/check.{ov}.sha').read().split()[0]
    r = subprocess.run([
        '.venv/bin/python', 'tools/harvest_verify.py', '--binary', ov, '--src', tu,
        '--asm-subdir', f'{ov}/nonmatchings/{subdir}', '--out', f'build/{ov}/{ov}',
        '--good-sha', good, '--drafts', gdir, '--chunk', '1'], capture_output=True, text=True)
    out = r.stdout + r.stderr
    ver = [l for l in out.splitlines() if l.startswith('VERIFIED:')]
    fal = [l for l in out.splitlines() if l.startswith('FAILED  :')]
    v = [x for x in (ver[0][9:].split() if ver else []) if x != '(none)']
    f = [x for x in (fal[0][9:].split() if fal else []) if x != '(none)']
    banked += [(ov, x) for x in v]
    failed += [(ov, x) for x in f]

    # R32 COVERAGE ASSERTION — the defect this gate shipped with (P30 S38).
    # It used to grep stdout for two line-prefixes and report whatever it found. When
    # harvest_verify CRASHED (a post-carve KeyError, uncaught, which also stranded the carve in
    # config/ + src/), there was no VERIFIED and no FAILED line — so the draft was booked as
    # NOTHING, and the run printed a clean-looking tally. Wave 6 lost 10 of 16 drafts that way,
    # 9 of them claiming MATCH, while every later group ran against the mutated tree.
    # A verdict is now MANDATORY per draft: anything unaccounted for is reported LOUDLY, with the
    # child's returncode and the tail of its output, because "no verdict" is a DEFECT, not a no.
    seen = set(v) | set(f)
    miss = [fn for fn, _ in items if fn not in seen]
    if miss or r.returncode:
        unaccounted += [(ov, fn) for fn in miss]
        print(f"  {ov:<14} [{os.path.basename(tu)}] !! NO VERDICT for {len(miss)} draft(s) "
              f"(harvest_verify rc={r.returncode}): {' '.join(miss)}")
        for line in out.strip().splitlines()[-12:]:
            print(f"        | {line}")
    else:
        print(f"  {ov:<14} [{os.path.basename(tu)}] {len(v)}/{len(items)} banked"
              + (f"  FAILED: {' '.join(f)}" if f else ''))
    shutil.rmtree(gdir, ignore_errors=True)

total = sum(len(x) for x in groups.values())
print(f"\n[gate] BANKED {len(banked)} / FAILED {len(failed)} / NO-VERDICT {len(unaccounted)}"
      f"  (of {total} drafts, {len(skipped)} skipped pre-flight)")
for ov, fn in failed:
    print("   fail:", ov, fn)
for ov, fn in unaccounted:
    print("   NO VERDICT:", ov, fn)
assert len(banked) + len(failed) + len(unaccounted) == total, (
    f"gate accounting is not 1:1 — {len(banked)}+{len(failed)}+{len(unaccounted)} != {total}")
if unaccounted:
    sys.exit(1)   # a crashed child may have STRANDED A CARVE; never let this look like success
