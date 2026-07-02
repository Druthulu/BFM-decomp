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

With --drafts, a target whose draft def has a narrow (non-promotion-safe) param is SKIPPED
(reported), since no-proto cannot satisfy it. Without --drafts, every listed target is rewritten
(let the gate filter). Run the byte-gate afterwards; --revert the gate-failures to keep the
shared header carrying no-proto only where it bought a match.
"""
import argparse, os, re, glob, sys

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
EC = os.path.join(REPO, 'src/shared/engine_core.h')
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


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    g = ap.add_mutually_exclusive_group(required=True)
    g.add_argument('--apply', action='store_true')
    g.add_argument('--revert', action='store_true')
    ap.add_argument('--funcs', help='comma-separated func_XXXX list')
    ap.add_argument('--from-file', help='file with one func_XXXX per line')
    ap.add_argument('--drafts', help='drafts dir: skip targets whose def has a narrow param (apply only)')
    ap.add_argument('--any-proto', action='store_true',
                    help='relax ANY prototype (not just (void)) -> no-proto — the generalized def-side-wall '
                         'reconciliation for non-(void) conflicting forward-decls; byte-gate filters (G3/P9)')
    a = ap.parse_args()

    fns = []
    if a.funcs:
        fns += [x.strip() for x in a.funcs.split(',') if x.strip()]
    if a.from_file:
        fns += [l.strip() for l in open(os.path.join(REPO, a.from_file)) if l.strip()]
    if not fns:
        sys.exit('no funcs given')

    txt = open(EC).read()
    applied = skipped = reverted = notfound = 0
    for fn in fns:
        ad = addr_of(fn)
        if not ad:
            continue
        if a.apply and a.drafts:
            safe = draft_is_promotion_safe(fn, a.drafts)
            if safe is False:
                print(f'  [skip narrow-param] {fn}'); skipped += 1; continue
        # match `extern <ret> func_ADDR ( void ) ;`  (ret = word chars/spaces/*) anywhere in the header
        void_re = re.compile(rf'(extern\s+[A-Za-z_][\w \t\*]*?\bfunc_{ad}\s*\()\s*void\s*(\)\s*;)', re.I)
        anyproto_re = re.compile(rf'(extern\s+[A-Za-z_][\w \t\*]*?\bfunc_{ad}\s*\()\s*[^;)]+?\s*(\)\s*;)', re.I)
        noproto_re = re.compile(rf'(extern\s+[A-Za-z_][\w \t\*]*?\bfunc_{ad}\s*\()\s*(\)\s*;)', re.I)
        if a.apply:
            new, n = (anyproto_re if a.any_proto else void_re).subn(r'\1\2', txt)
        else:
            new, n = noproto_re.subn(r'\1void\2', txt)
        if n:
            txt = new
            applied += a.apply and n
            reverted += a.revert and n
            print(f'  [{"no-proto" if a.apply else "revert"}] {fn} ({n} caller decl)')
        else:
            notfound += 1
            print(f'  [no caller (void) decl found] {fn}')
    open(EC, 'w').write(txt)
    if a.apply:
        print(f'\napplied no-proto to {applied} caller decl(s); skipped {skipped} narrow-param; '
              f'{notfound} had no (void) caller decl. Re-run the byte-gate now.')
    else:
        print(f'\nreverted {reverted} caller decl(s) to (void).')


if __name__ == '__main__':
    main()
