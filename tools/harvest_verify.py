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
REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
PY = '.venv/bin/python'

import corpus   # the derived corpus oracle (Phase 26-A) — a draft's home TU is a FACT of the tree
import cdecl    # the C-declaration oracle (Phase 26-A) — the per-TU typedef strip-set (T4)

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

# A self-contained draft inlines its own typedefs (`typedef unsigned char u8;`, and often a struct
# type like `typedef struct {...} Blk16;`). Spliced into a TU that already provides those names
# (common.h + engine_types.h), gcc-2.7.2/C89 REJECTS the redefinition — a plumbing error, not a byte
# mismatch. Strip exactly the names the TARGET TU provides, per-TU (cdecl.typedef_names + the T4
# primitive). The old `_TD` here was scalar-only (no M2C_UNK, no struct typedefs) and dropped 39
# still-open functions this way; the strip-set is now derived from the tree, not hand-listed.
def sha1(path):
    return hashlib.sha1(open(path, 'rb').read()).hexdigest() if os.path.exists(path) else None


# Distinguish a DECLARATION/PLUMBING failure (byte-correct C the front end rejects — recoverable by
# strip/reconcile) from a genuine codegen miss. The build's stderr was being discarded, so a draft
# that failed to COMPILE was recorded identically to one that compiled to the wrong bytes — the exact
# "a compiler wall that is really a plumbing error" the 26-A audit exists to end (R32). We surface it.
_PLUMBING = re.compile(
    r'conflicting types|redefinition of|redeclar|parse error before|storage size|'
    r'undefined reference|prototype declaration', re.I)
_last_err = ''
_last_sha = None
_NO_BUILD = object()   # attempt() short-circuited (stub already spliced) — no build ran


def build():
    """make build BINARY=<bin>; return the output SHA1, or None on compile/link failure
    (remove the output first so a stale file can't masquerade as a passing build). Stashes the
    build's stderr + sha in _last_err/_last_sha so a single-draft failure can be CLASSIFIED."""
    global _last_err, _last_sha
    if os.path.exists(a.out):
        os.remove(a.out)
    p = subprocess.run(['make', 'build', 'BINARY=' + a.binary], capture_output=True, text=True)
    _last_err = (p.stderr or '') + (p.stdout or '')
    _last_sha = sha1(a.out)
    return _last_sha


def classify_fail(got_sha):
    """Why did this single draft fail? Only meaningful right after a 1-draft attempt().
      * no build ran (stub already spliced)            -> SKIP
      * built but wrong bytes (sha present, != good)   -> DIFF        (a genuine codegen residual)
      * did not build, stderr matches a decl conflict  -> PLUMBING:...(recoverable, not a wall)
      * did not build, other                           -> CC1-FAIL   (needs a look)"""
    if got_sha is _NO_BUILD:
        return 'SKIP'
    if got_sha is not None:
        return 'DIFF'
    m = _PLUMBING.search(_last_err)
    if m:
        # pull the offending line for the log (e.g. "redefinition of 's16'")
        for ln in _last_err.splitlines():
            if m.re.search(ln):
                return 'PLUMBING: ' + ln.strip()[:90]
        return 'PLUMBING: ' + m.group(0).lower()
    return 'CC1-FAIL'


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
    # Strip the typedefs the DRAFT's OWN target TU already provides (per-TU strip-set, T4). Computed
    # against the baseline tree (before any splice); cdecl.typedef_names is cached per TU.
    provided = cdecl.typedef_names(_stubs[fn].path)
    drafts[fn] = {'c': cdecl.strip_provided_typedefs(open(cf).read(), provided), 'conf': conf}

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


# --------------------------------------------------------------------------------------------
# jtbl prep (Phase-29 Task-14 stage 4) — the carve MUST FOLLOW THE SPLICE
# --------------------------------------------------------------------------------------------
# A draft whose function owns a switch jump table cannot link into a jtbl-CARVED TU until that
# table has its own contiguous .rodata carve. gate_stage tried this as a batch pre-pass and it
# does not work, for a reason that is the whole point of doing it here instead:
#
#   THE NON-CONTIGUITY IS ONLY DETECTABLE ONCE THE BODY IS IN THE OBJECT. While the function is
#   still INCLUDE_ASM, `jtbl_carve` reports SUCCESS and yields a spec that fails when the body
#   lands. Byte-witnessed both ways on func_80135A4C: spliced -> "NON-CONTIGUOUS 0xaa810 and
#   0xaa920"; unspliced -> "prepared 1/1", then a byte-DIFF at the gate.
#
# So we splice TEMPORARILY, ask jtbl_carve, isolate if it refuses, then un-splice and let the
# normal gate loop do the real splice. Isolation MOVES the stub's TU, so the stub map and the
# baseline are re-derived afterwards (they are keyed by path).
_JTBL_RE = re.compile(r"jtbl_[0-9A-Fa-f]{8}")
_ISO_WALLS = ("NON-CONTIGUOUS", "do not fit the span")


def _sh(cmd, timeout=1800):
    return subprocess.run(cmd, capture_output=True, text=True, cwd=REPO, timeout=timeout)


def _fn_has_jtbl(fn):
    st = _stubs.get(fn)
    if st is None:
        return False
    try:
        return bool(_JTBL_RE.search(open(os.path.join(REPO, st.asm_path)).read()))
    except OSError:
        return False


def _reload_corpus():
    """Re-derive the stub map + baseline after an isolation moved a stub to a new TU."""
    global _stubs, baseline, _touched
    for f in (corpus.stubs, corpus.sig, corpus.symbols, corpus.src_files):
        if hasattr(f, 'cache_clear'):
            f.cache_clear()
    _stubs = {x.symbol: x for x in corpus.stubs(a.binary).values()}
    if a.src:
        _stubs = {n: x for n, x in _stubs.items() if x.path == a.src}
    _touched = sorted({_stubs[fn].path for fn in items if fn in _stubs})
    baseline = {q: open(q).read() for q in _touched}


def _jtbl_prep():
    """Make every table-bearing draft's carve valid. Returns the list prepared."""
    todo = [fn for fn in items if _fn_has_jtbl(fn)]
    if not todo:
        return []
    done = []
    for fn in todo:
        st = _stubs.get(fn)
        if st is None:
            continue
        line = _stub_line(fn)
        txt = open(st.path).read()
        if line not in txt:
            continue
        open(st.path, 'w').write(txt.replace(line, drafts[fn]['c'], 1))   # TEMPORARY splice
        r = _sh([PY, 'tools/jtbl_carve.py', a.binary, '--func', fn])
        out = (r.stdout or '') + (r.stderr or '')
        if r.returncode and any(w in out for w in _ISO_WALLS):
            open(st.path, 'w').write(txt)                                 # un-splice before isolating
            if _sh([PY, 'tools/jr_isolate_all.py', a.binary, '--only', fn]).returncode:
                print('  [jtbl] isolate FAILED %s' % fn); continue
            if _sh(['make', '--no-print-directory', 'extract', 'BINARY=%s' % a.binary]).returncode:
                print('  [jtbl] extract-after-isolate FAILED %s' % fn); continue
            _reload_corpus()
            st = _stubs.get(fn)
            if st is None:
                print('  [jtbl] stub vanished after isolate %s' % fn); continue
            line, txt = _stub_line(fn), open(st.path).read()
            if line not in txt:
                print('  [jtbl] no stub after isolate %s' % fn); continue
            open(st.path, 'w').write(txt.replace(line, drafts[fn]['c'], 1))
            r = _sh([PY, 'tools/jtbl_carve.py', a.binary, '--func', fn])
        open(st.path, 'w').write(txt)                                     # ALWAYS un-splice
        if r.returncode:
            last = ((r.stdout or '') + (r.stderr or '')).strip().splitlines()[-1:] or ['']
            print('  [jtbl] carve FAILED %s: %s' % (fn, last[0][:120])); continue
        done.append(fn)
    if done:
        _sh(['make', '--no-print-directory', 'extract', 'BINARY=%s' % a.binary])
        _reload_corpus()
        print('  [jtbl] carved %d/%d table-bearing draft(s): %s' % (len(done), len(todo), ' '.join(done)))
    return done


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
    global _last_sha
    s = render(fns)
    if s is None:
        _last_sha = _NO_BUILD          # no build ran -> classify_fail reports SKIP, not a false CC1-FAIL
        return False
    _write(s)
    return build() == a.good_sha


def commit(fns):
    global baseline
    baseline = render(fns)
    verified.extend(fns)


_jtbl_prepared = _jtbl_prep()

i = 0
while i < len(items):
    chunk = items[i:i + a.chunk]
    i += a.chunk
    if attempt(chunk):
        commit(chunk)
        print('  + chunk(%d): %s' % (len(chunk), ' '.join(chunk)))
    elif len(chunk) == 1:
        # ATOMIC CHUNK — do NOT bisect (Phase-28 T6). The old code fell into the loop below and
        # re-ran attempt([fn]) on the SAME single element against the SAME baseline: a byte-identical
        # DUPLICATE build. classify_fail reads _last_sha/_last_err, which the failed attempt(chunk)
        # above ALREADY set — so the re-attempt bought nothing but a second cc1+maspsx+as+ld. On the
        # gate's hot path (--chunk 1, the prescribed default: chunked failures mis-attribute innocent
        # neighbours, cookbook:1568) that was 1.35 builds/draft at the measured 65% bank rate; now 1.0
        # — ~26% fewer builds, every wave, for one branch. The gate's verdict is unchanged.
        fn = chunk[0]
        klass = classify_fail(_last_sha)
        failed.append((fn, klass))
        print('  - %s (%s) [%s]' % (fn, drafts[fn]['conf'], klass))
    else:
        for fn in chunk:                 # bisect: isolate the matches from the misses, CLASSIFY the misses
            if attempt([fn]):
                commit([fn]); print('  + %s' % fn)
            else:
                klass = classify_fail(_last_sha)   # DIFF (real codegen) vs PLUMBING (recoverable) vs CC1-FAIL
                failed.append((fn, klass))
                print('  - %s (%s) [%s]' % (fn, drafts[fn]['conf'], klass))

# restore the accumulated verified state and confirm the binary is byte-identical
_write(baseline)
final = build()
# failure breakdown by class — a PLUMBING count > 0 means "recoverable, not a compiler wall" (T4)
from collections import Counter
_klass = Counter(k.split(':')[0] for _, k in failed)
print('\n=== RESULT ===')
print('verified %d / failed %d ; final SHA %s  (%s)' % (
    len(verified), len(failed), final,
    'BYTE-IDENTICAL' if final == a.good_sha else '*** MISMATCH — investigate ***'))
if _klass:
    print('  failed by class:', ' '.join('%s=%d' % (k, n) for k, n in sorted(_klass.items())))
print('VERIFIED:', ' '.join(verified) or '(none)')
print('FAILED  :', ' '.join(fn for fn, _ in failed) or '(none)')
open(a.verified_out, 'w').write('\n'.join(verified) + '\n')
# failed_out stays NAMES-only (backward-compatible for existing consumers); the class goes to a sidecar
open(a.failed_out, 'w').write('\n'.join(fn for fn, _ in failed) + '\n')
open(a.failed_out.rsplit('.', 1)[0] + '.classified.txt', 'w').write(
    '\n'.join('%s\t%s' % (fn, k) for fn, k in failed) + '\n')
