#!/usr/bin/env python3
"""Byte-gate drafted matching-C against a byte-locked binary, one draft at a time.

Reads .run/drafts/<fn>.c (self-contained C: externs + the function definition) produced
by the resident-harvest-draft workflow, and for each function still stubbed as INCLUDE_ASM:
substitutes the draft for that stub in the binary's source .c, rebuilds, and KEEPS it only
if the binary stays byte-identical (`make build` SHA1 == the locked SHA). Non-matches and
compile/link failures revert to the INCLUDE_ASM stub. The build is the sole truth (G3/P9):
a wrong draft can never be accepted. Chunk-with-bisection keeps it fast on high-hit batches.

The source .c is git-committed, so `git checkout` always recovers if interrupted.
Resident defaults; pass flags for another binary.

  python3 tools/harvest_verify.py            # resident
  python3 tools/harvest_verify.py --chunk 6
"""
import subprocess, glob, os, re, sys, hashlib, argparse

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import corpus   # the derived corpus oracle (Phase 26-A) — a draft's home TU is a FACT of the tree

ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
ap.add_argument('--binary', default='resident')
ap.add_argument('--src', default=None,
                help='DEPRECATED and ignored for stub LOCATION. A draft is spliced into whichever TU '
                     'actually holds its stub, derived from the tree. Kept only as an optional FILTER: '
                     'if given, only drafts whose stub lives in this file are considered.')
ap.add_argument('--asm-subdir', default=None, help='DEPRECATED and ignored (derived per stub).')
ap.add_argument('--out', default=None, help='built image path (derived from --binary if omitted)')
ap.add_argument('--good-sha', default=None, help='locked SHA1 (read from config/check.<bin>.sha if omitted)')
ap.add_argument('--drafts', default='.run/drafts')
ap.add_argument('--chunk', type=int, default=8)
ap.add_argument('--verified-out', default='.run/harvest_verified.txt',
                help='per-worker result path (bulk_harvest gates distinct binaries in parallel)')
ap.add_argument('--failed-out', default='.run/harvest_failed.txt')
a = ap.parse_args()

# ---- derive the build target + the locked SHA from the binary, not from a caller's flag ----------
# A caller that passed --binary but forgot --good-sha used to gate an overlay against RESIDENT's SHA
# (conservative — everything fails — but baffling). The Makefile and config/check.<bin>.sha already
# state these facts; do not keep a second copy.
_OUT = {'main': 'build/us/SLUS_007.26', 'resident': 'build/resident/resident'}
if not a.out:
    a.out = _OUT.get(a.binary, f'build/{a.binary}/{a.binary}')
if not a.good_sha:
    p = f'config/check.{"us" if a.binary == "main" else a.binary}.sha'
    if not os.path.exists(p):
        sys.exit(f'harvest_verify: no --good-sha and no {p} — refusing to gate against an unknown SHA')
    a.good_sha = open(p).read().split()[0]

# Some drafts inline `typedef unsigned char u8;` etc. ("self-contained") -> when placed in a
# .c that already #includes common.h, gcc-2.7.2 (C89) errors on the redefinition. Strip those
# lines so common.h provides the types (a compile error is NOT a byte mismatch).
_TD = re.compile(r'^[ \t]*typedef\b.*\b(u8|u16|u32|u64|s8|s16|s32|s64|f32|f64)[ \t]*;[ \t]*\n', re.M)


def strip_typedefs(c):
    return _TD.sub('', c)


def sha1(path):
    return hashlib.sha1(open(path, 'rb').read()).hexdigest() if os.path.exists(path) else None


def build():
    """make build BINARY=<bin>; return the output SHA1, or None on compile/link failure
    (remove the output first so a stale file can't masquerade as a passing build)."""
    if os.path.exists(a.out):
        os.remove(a.out)
    subprocess.run(['make', 'build', 'BINARY=' + a.binary], capture_output=True, text=True)
    return sha1(a.out)


# --- locate every live stub, in EVERY TU of the binary (Phase 26-A, HIGH) ------------------------
# This used to scan the ONE file the caller passed as --src, and silently drop every draft whose
# stub lived elsewhere. An overlay's source is spread over up to 14 .c files, so 56,742 of the
# fleet's 58,717 open stubs (96.6%) were unreachable, and THREE of the six callers passed no --src
# at all — including grinder.py, which meant 1,290 of the grinder's own 1,298 queued functions
# COULD NEVER BANK, however good the permuter's output was. ("The permuter's fuel is exhausted"
# was therefore never a safe conclusion.)
#
# Every TU links into the same image, so one `make build BINARY=<bin>` still gates them all — this
# is both correct AND strictly fewer builds than the per-split re-gate it replaces.
#
# SAFETY (G3/P9 — this is the byte-gate, so the argument must be explicit): the verdict is unchanged
# (`make build` + SHA1 == the locked hash). Only the SPLICE LOCATION is derived rather than guessed.
# INCLUDE_ASM pastes the ORIGINAL assembly, so a wrong draft always changes the bytes and always
# fails SHA1. A bug here can therefore make the tool FAIL TO BANK; it cannot make it falsely bank.
_stubs = {s.symbol: s for s in corpus.stubs(a.binary).values()}
if a.src:                                         # optional filter, not a location oracle
    _stubs = {n: s for n, s in _stubs.items() if s.path == a.src}

drafts, not_stubbed = {}, []
for cf in sorted(glob.glob(a.drafts + '/*.c')):
    fn = os.path.basename(cf)[:-2]
    if fn not in _stubs:
        not_stubbed.append(fn)                    # REPORTED, never silently dropped (R32)
        continue
    conf = 'medium'
    cp = cf[:-2] + '.conf'
    if os.path.exists(cp):
        w = open(cp).read().strip().lower().split()
        if w and w[0] in ('high', 'medium', 'low'):
            conf = w[0]
    drafts[fn] = {'c': strip_typedefs(open(cf).read()), 'conf': conf}

order = {'high': 0, 'medium': 1, 'low': 2}
items = sorted(drafts, key=lambda fn: (order[drafts[fn]['conf']], len(drafts[fn]['c'])))
print('drafts to verify: %d  (high=%d medium=%d low=%d) of %d live stubs across %d TUs' % (
    len(items),
    sum(drafts[f]['conf'] == 'high' for f in items),
    sum(drafts[f]['conf'] == 'medium' for f in items),
    sum(drafts[f]['conf'] == 'low' for f in items),
    len(_stubs), len({s.path for s in _stubs.values()})))
if not_stubbed:
    print('  (%d draft(s) skipped — not a live stub in %s: %s%s)' % (
        len(not_stubbed), a.binary, ' '.join(not_stubbed[:6]),
        ' …' if len(not_stubbed) > 6 else ''))

# baseline is now PER-FILE: {path: text}. Only the TUs we actually touch are tracked.
_touched = sorted({_stubs[fn].path for fn in items})
baseline = {p: open(p).read() for p in _touched}
verified, failed = [], []


def _stub_line(fn):
    s = _stubs[fn]
    return 'INCLUDE_ASM("%s", %s);' % (s.asm_dir, s.symbol)


def render(fns):
    """{path: text} with each draft spliced into the TU that actually holds its stub."""
    out = dict(baseline)
    for fn in fns:
        p, line = _stubs[fn].path, _stub_line(fn)
        if line not in out.get(p, ''):
            return None          # stub missing -> skip (don't let a no-op build false-pass)
        out[p] = out[p].replace(line, drafts[fn]['c'], 1)
    return out


def _write(state):
    for p, text in state.items():
        open(p, 'w').write(text)


def attempt(fns):
    s = render(fns)
    if s is None:
        return False
    _write(s)
    return build() == a.good_sha


def commit(fns):
    global baseline
    baseline = render(fns)
    verified.extend(fns)


i = 0
while i < len(items):
    chunk = items[i:i + a.chunk]
    i += a.chunk
    if attempt(chunk):
        commit(chunk)
        print('  + chunk(%d): %s' % (len(chunk), ' '.join(chunk)))
    else:
        for fn in chunk:                 # bisect: isolate the matches from the misses
            if attempt([fn]):
                commit([fn]); print('  + %s' % fn)
            else:
                failed.append(fn); print('  - %s (%s)' % (fn, drafts[fn]['conf']))

# restore the accumulated verified state and confirm the binary is byte-identical
_write(baseline)
final = build()
print('\n=== RESULT ===')
print('verified %d / failed %d ; final SHA %s  (%s)' % (
    len(verified), len(failed), final,
    'BYTE-IDENTICAL' if final == a.good_sha else '*** MISMATCH — investigate ***'))
print('VERIFIED:', ' '.join(verified) or '(none)')
print('FAILED  :', ' '.join(failed) or '(none)')
open(a.verified_out, 'w').write('\n'.join(verified) + '\n')
open(a.failed_out, 'w').write('\n'.join(failed) + '\n')
