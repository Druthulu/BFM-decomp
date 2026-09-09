#!/usr/bin/env python3
"""fix_arity_callers.py — the no-prototype recovery for the shared-caller ARITY conflict class
(Phase 19 / T2+T3, cookbook §17a-3b). The dominant whole-binary-gate failure once garbled hints
and sig_unify regressions are removed: a function being matched takes an argument, but an
already-banked SHARED caller macro in src/shared/engine_core.h declares it file-scope as
`extern <ret> func_X(void);` (void = "no args") and calls `func_X();`. That `(void)` prototype
conflicts with the real `<ret> func_X(<arg>)` definition -> `conflicting types for func_X`.

FIX: rewrite the caller's declaration to a no-prototype `extern <ret> func_X();` (K&R). This is
byte-NEUTRAL for the caller (the empty call `func_X()` emits identical code either way) and a
no-prototype decl is COMPATIBLE with a definition whose params are default-promotion-safe
(int/s32/u32/long/pointer — NOT char/short/s8/s16/u8/u16/float; those hit the narrow-param wall
§17-stop and are skipped). The whole-binary harvest_verify byte-gate remains the sole arbiter
(G3/P9): a wrong rewrite just fails the gate.

  tools/fix_arity_callers.py --apply  --funcs func_X,func_Y [--drafts DIR]   # rewrite (void)->()
  tools/fix_arity_callers.py --revert --funcs func_X,func_Y                  # ()->(void)
  tools/fix_arity_callers.py --apply  --from-file .run/list.txt --drafts DIR
  tools/fix_arity_callers.py --apply  --funcs ... --journal .run/arity_journal.json
  tools/fix_arity_callers.py --undo-journal .run/arity_journal.json --keep func_X   # exact undo

With --drafts, a target whose draft def has a narrow (non-promotion-safe) param is SKIPPED
(reported), since no-proto cannot satisfy it. Without --drafts, every listed target is rewritten
(let the gate filter). Run the byte-gate afterwards.

UNDO (P30 T0a — the "bare gate has no snapshot/restore" carried defect): prefer
--journal on apply + --undo-journal [--keep <banked,fns>] over --revert. --revert rewrites
`()` -> `(void)`, which is the exact inverse of a PLAIN apply but NOT of --any-proto (it relaxes
ANY prototype) — round-tripping an --any-proto edit through --revert INVENTED a `(void)` signature
in the fleet-shared header and 138/140 binaries failed check-all (measured 2026-07-21). The journal
records each substitution's literal before/after text, so --undo-journal restores per-DECL, exact
by construction: it cannot invent a signature, and it is immune to interleaved splices (a banked
draft landing in the same file between apply and undo — the Task-14 hazard the gate_stage snapshot
had to special-case). --keep names the fns whose edits stay (the banked set).
"""
import argparse, hashlib, json, os, re, glob, sys
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import shared_lock  # Stage 1: --apply/--undo-journal write the fleet-shared header

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
NARROW = re.compile(r'\b(char|short|signed\s+char|unsigned\s+char|unsigned\s+short|s8|u8|s16|u16|float|f32)\b')


def addr_of(fn):
    m = re.search(r'func_([0-9A-Fa-f]+)', fn)
    return m.group(1).upper() if m else None


def draft_is_promotion_safe(fn, drafts):
    """False iff the draft's def has a narrow scalar param (no '*'); None if no draft found."""
    cand = os.path.join(REPO, drafts, f'{fn}.c')
    if not os.path.exists(cand):
        return None
    txt = open(cand).read()
    m = re.search(rf'\b{re.escape(fn)}\s*\(([^;{{)]*)\)\s*\{{', txt) or \
        re.search(rf'\b{re.escape(fn)}\s*\(([^;{{)]*)\)\s*\n\s*\{{', txt)
    if not m:
        return None
    params = m.group(1).strip()
    if params in ('', 'void'):
        return True
    for p in params.split(','):
        if '*' in p:                      # pointer param: promotion-safe
            continue
        if NARROW.search(p):              # narrow scalar by value: NOT promotion-safe
            return False
    return True


def undo_journal(path, keep):
    """Exact per-decl undo: for each journaled edit whose fn is NOT kept, replace the recorded
    `after` text back to the recorded `before` text (one occurrence). Reports restored/kept/missing
    loudly (R32) — a missing `after` means someone else edited that decl since; it is NOT silently
    skipped."""
    raw = json.load(open(os.path.join(REPO, path)))
    entries = raw['edits'] if isinstance(raw, dict) else raw
    shas = raw.get('sha_before', {}) if isinstance(raw, dict) else {}

    # AMBIGUITY REFUSAL (P31 S70, §403). `--any-proto` collapses DISTINCT declarations of the same
    # function to the SAME `after` text. The restore below is `replace(after, before, 1)` — first
    # occurrence — so when one (file, after) group holds entries with DIFFERENT `before` values, the
    # originals get written back to the WRONG occurrences and the file is silently corrupted while
    # this function reports full success. Byte-witnessed: engine_core.h left with 97 insertions /
    # 97 deletions after `restored 382, kept 0, missing 0` (func_8012A828 rotated between three
    # declaration sites). The occurrence->original mapping is NOT recoverable from this journal
    # format, so REFUSE rather than guess (R43): a loud refusal costs one `git checkout`, a silent
    # swap costs a corrupted FLEET-SHARED header nobody notices.
    groups, ambiguous = {}, []
    for e in entries:
        if e['fn'] in keep:
            continue
        groups.setdefault((e['file'], e['after']), set()).add(e['before'])
    for (f, after), befores in sorted(groups.items()):
        if len(befores) > 1:
            ambiguous.append((f, after, sorted(befores)))
    if ambiguous:
        print(f'undo-journal: REFUSED — {len(ambiguous)} ambiguous restore group(s): the same edited '
              f'text maps back to DIFFERENT originals, and this journal does not record which '
              f'occurrence is which. Restoring would SWAP them (§403).', file=sys.stderr)
        for f, after, befores in ambiguous[:5]:
            print(f'  {os.path.relpath(f, REPO)}: {after.strip()[:70]}', file=sys.stderr)
            for b in befores[:4]:
                print(f'      <- {b.strip()[:70]}', file=sys.stderr)
        print(f'  Fix: restore the named file(s) from git instead — '
              f'`git checkout -- {os.path.relpath(ambiguous[0][0], REPO)}`', file=sys.stderr)
        return 2

    restored = kept = missing = 0
    texts = {}
    for e in entries:
        if e['fn'] in keep:
            kept += 1
            continue
        f = e['file']
        if f not in texts:
            texts[f] = open(f).read()
        if e['after'] in texts[f]:
            texts[f] = texts[f].replace(e['after'], e['before'], 1)
            restored += 1
        else:
            missing += 1
            print(f"  [MISSING] {e['fn']} in {os.path.relpath(f, REPO)} — the edited decl text is "
                  f"no longer present (later edit?); NOT restored", file=sys.stderr)
    for f, t in texts.items():
        open(f, 'w').write(t)
    # HASH BACKSTOP: when nothing was kept and nothing was missing, a correct undo must reproduce the
    # pre-edit file EXACTLY. Verify it instead of trusting the counters (R40 — the tool's own report
    # is not evidence; this whole class was caught by `git diff`, not by the success line).
    bad = []
    if not kept and not missing:
        for f in texts:
            want = shas.get(f)
            if want and hashlib.sha1(texts[f].encode()).hexdigest() != want:
                bad.append(f)
    if bad:
        for f in bad:
            print(f'  [CORRUPT] {os.path.relpath(f, REPO)} does not match its pre-edit hash after '
                  f'undo — restore it from git (§403)', file=sys.stderr)
    print(f'undo-journal: restored {restored}, kept {kept}, missing {missing}'
          + (f', HASH-MISMATCH {len(bad)}' if bad else ''))
    return 1 if (missing or bad) else 0


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    g = ap.add_mutually_exclusive_group(required=True)
    g.add_argument('--apply', action='store_true')
    g.add_argument('--revert', action='store_true')
    g.add_argument('--undo-journal', metavar='PATH',
                   help='exact per-decl undo of a --journal file (see header); honors --keep')
    ap.add_argument('--funcs', help='comma-separated func_XXXX list')
    ap.add_argument('--from-file', help='file with one func_XXXX per line')
    ap.add_argument('--drafts', help='drafts dir: skip targets whose def has a narrow param (apply only)')
    ap.add_argument('--any-proto', action='store_true',
                    help='relax ANY prototype (not just (void)) -> no-proto — the generalized def-side-wall '
                         'reconciliation for non-(void) conflicting forward-decls; byte-gate filters (G3/P9)')
    ap.add_argument('--binary', help='ALSO scan+rewrite this overlay\'s own inline caller decls in '
                    'src/<binary>/<binary>*.c (a conflicting extern is often in the overlay src, not just '
                    'the shared headers under src/shared/ — the T6 integration-recovery gap). Default: the shared headers under src/shared/ only.')
    ap.add_argument('--journal', metavar='PATH',
                    help='(apply) record each substitution\'s literal before/after to this JSON for '
                         'exact --undo-journal restore; written even when no edits were made')
    ap.add_argument('--keep', help='(undo-journal) comma-separated fns whose edits are KEPT (the banked set)')
    a = ap.parse_args()

    if a.undo_journal:
        keep = set(x.strip() for x in (a.keep or '').split(',') if x.strip())
        sys.exit(undo_journal(a.undo_journal, keep))

    fns = []
    if a.funcs:
        fns += [x.strip() for x in a.funcs.split(',') if x.strip()]
    if a.from_file:
        fns += [l.strip() for l in open(os.path.join(REPO, a.from_file)) if l.strip()]
    if not fns:
        sys.exit('no funcs given')

    # target files: engine_core.h always; + the overlay's own src (inline callers) when --binary given.
    files = sorted(set(glob.glob(os.path.join(REPO, 'src/shared/**/*.h'), recursive=True)))  # Phase 35: every shared header carries externs
    if a.binary:
        # MAIN'S SOURCES DO NOT LIVE IN src/main/ (P31 S69). They are src/*.c — src/800.c, … — so the
        # overlay-shaped glob matched NOTHING for --binary main and the tool reported success over an
        # empty file set: `main:func_80036D58` kept failing `conflicting types` through three gates
        # while this scan silently covered zero of its two offending decls. The R32 silent-narrowing
        # class, in the tool that exists to fix exactly this blocker.
        if a.binary == 'main':
            files += sorted(glob.glob(os.path.join(REPO, 'src/*.c')))
        else:
            files += sorted(glob.glob(os.path.join(REPO, f'src/{a.binary}/{a.binary}*.c')))
        if len(files) == 1:
            sys.exit('REFUSED: --binary %s selected NO source files to scan (R32: a true "0 edits" '
                     'over an empty denominator is not a result)' % a.binary)
    texts = {f: open(f).read() for f in files}
    orig_texts = dict(texts)   # §403: pre-edit content, hashed into the journal for undo verification
    applied = skipped = reverted = notfound = 0
    journal = []
    for fn in fns:
        ad = addr_of(fn)
        if not ad:
            continue
        if a.apply and a.drafts:
            safe = draft_is_promotion_safe(fn, a.drafts)
            if safe is False:
                print(f'  [skip narrow-param] {fn}'); skipped += 1; continue
        # match `extern <ret> func_ADDR ( void ) ;`  (ret = word chars/spaces/*) anywhere
        void_re = re.compile(rf'(extern\s+[A-Za-z_][\w \t\*]*?\bfunc_{ad}\s*\()\s*void\s*(\)\s*;)', re.I)
        anyproto_re = re.compile(rf'(extern\s+[A-Za-z_][\w \t\*]*?\bfunc_{ad}\s*\()\s*[^;)]+?\s*(\)\s*;)', re.I)
        noproto_re = re.compile(rf'(extern\s+[A-Za-z_][\w \t\*]*?\bfunc_{ad}\s*\()\s*(\)\s*;)', re.I)
        n = 0
        for f in files:
            if a.apply:
                # replacement FUNCTION (not a template) so each substitution's literal before/after
                # is journaled — the substrate of the exact --undo-journal restore (P30 T0a)
                def _sub(m, _f=f, _fn=fn):
                    after = m.group(1) + m.group(2)
                    journal.append({'fn': _fn, 'file': _f, 'before': m.group(0), 'after': after})
                    return after
                texts[f], k = (anyproto_re if a.any_proto else void_re).subn(_sub, texts[f])
            else:
                texts[f], k = noproto_re.subn(r'\1void\2', texts[f])
            n += k
        if n:
            applied += a.apply and n
            reverted += a.revert and n
            print(f'  [{"no-proto" if a.apply else "revert"}] {fn} ({n} caller decl)')
        else:
            notfound += 1
            print(f'  [no caller (void) decl found] {fn}')
    for f, t in texts.items():
        open(f, 'w').write(t)
    if a.apply and a.journal:
        jp = os.path.join(REPO, a.journal)
        os.makedirs(os.path.dirname(jp), exist_ok=True)
        with open(jp, 'w') as jf:
            # NEW FORMAT (§403): {edits, sha_before} so --undo-journal can VERIFY its own result.
            # The list form is still accepted on read for journals written before this change.
            json.dump({'edits': journal,
                       'sha_before': {f: hashlib.sha1(t.encode()).hexdigest()
                                      for f, t in orig_texts.items()}}, jf, indent=1)
        print(f'journal: {len(journal)} edit(s) -> {a.journal}')
    if a.apply:
        print(f'\napplied no-proto to {applied} caller decl(s); skipped {skipped} narrow-param; '
              f'{notfound} had no (void) caller decl. Re-run the byte-gate now.')
    else:
        print(f'\nreverted {reverted} caller decl(s) to (void).')


if __name__ == '__main__':
    # Stage 1: --apply and --undo-journal both rewrite caller externs in the fleet-shared
    # src/shared/engine_core.h. EXCLUSIVE so no gate can read that state mid-edit (design §2.2b).
    # No-op when gate_stage already holds the lock (BFM_SHARED_LOCK_HELD).
    with shared_lock.hold(exclusive=True, announce="fix_arity_callers"):
        main()
