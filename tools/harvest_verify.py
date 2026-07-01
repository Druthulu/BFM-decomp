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
import subprocess, glob, os, re, hashlib, argparse

ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
ap.add_argument('--binary', default='resident')
ap.add_argument('--src', default='src/resident/resident.c')
ap.add_argument('--asm-subdir', default='asm/resident/nonmatchings/resident')
ap.add_argument('--out', default='build/resident/resident')
ap.add_argument('--good-sha', default='8e17e02ff8954d07c979449198f7e1645046b353')
ap.add_argument('--drafts', default='.run/drafts')
ap.add_argument('--chunk', type=int, default=8)
ap.add_argument('--verified-out', default='.run/harvest_verified.txt',
                help='per-worker result path (bulk_harvest gates distinct binaries in parallel)')
ap.add_argument('--failed-out', default='.run/harvest_failed.txt')
a = ap.parse_args()

STUB = 'INCLUDE_ASM("' + a.asm_subdir + '", {fn});'        # {fn} filled per function

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


# --- load drafts for functions still stubbed in the current source ---
src0 = open(a.src).read()
stubbed = set(re.findall(r'INCLUDE_ASM\("' + re.escape(a.asm_subdir) + r'", (func_[0-9A-Fa-f]+|DsMix)\)', src0))
drafts = {}
for cf in sorted(glob.glob(a.drafts + '/*.c')):
    fn = os.path.basename(cf)[:-2]
    if fn not in stubbed:
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
print('drafts to verify: %d  (high=%d medium=%d low=%d) of %d stubbed' % (
    len(items),
    sum(drafts[f]['conf'] == 'high' for f in items),
    sum(drafts[f]['conf'] == 'medium' for f in items),
    sum(drafts[f]['conf'] == 'low' for f in items),
    len(stubbed)))

baseline = src0                  # known byte-identical source state (accumulates verified)
verified, failed = [], []


def render(fns):
    s = baseline
    for fn in fns:
        line = STUB.format(fn=fn)
        if line not in s:
            return None          # stub missing -> skip (don't let a no-op build false-pass)
        s = s.replace(line, drafts[fn]['c'], 1)
    return s


def attempt(fns):
    s = render(fns)
    if s is None:
        return False
    open(a.src, 'w').write(s)
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
open(a.src, 'w').write(baseline)
final = build()
print('\n=== RESULT ===')
print('verified %d / failed %d ; final SHA %s  (%s)' % (
    len(verified), len(failed), final,
    'BYTE-IDENTICAL' if final == a.good_sha else '*** MISMATCH — investigate ***'))
print('VERIFIED:', ' '.join(verified) or '(none)')
print('FAILED  :', ' '.join(failed) or '(none)')
open(a.verified_out, 'w').write('\n'.join(verified) + '\n')
open(a.failed_out, 'w').write('\n'.join(failed) + '\n')
