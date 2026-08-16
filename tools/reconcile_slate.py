#!/usr/bin/env python3
"""reconcile_slate.py — drive a main slate to `N -> N compatible, 0 dropped` BEFORE any rebuild.

WHY (P31 S52, cookbook §176g/§176h.C2). Wave P drafted at 97% and banked 68%. The whole gap was
declaration plumbing, and the fix is NOT to bank the clean drafts and recover the rest later --
that is measurably backwards, because a banked draft's declarations become the TU's, so a
sibling-vs-sibling clash (settleable by editing either side) hardens into a file-vs-draft clash
(settleable only by editing the draft, and sometimes not at all). Of 18 parked drafts still
verifying MATCH, only 1 survived the conflict check after their wave banked, versus 5 before.

So reconciliation belongs INSIDE the wave, before the first gate. This tool automates the part
that is mechanical, and -- just as importantly -- REFUSES the part that is not, naming what a
human must decide.

WHAT IT FIXES AUTOMATICALLY (each re-verified with match_one; a repair that changes a byte is
reverted, because a declaration change is a codegen change -- §176f):
  * COSMETIC-TYPEDEF   two names for a structurally IDENTICAL struct -> adopt the other name.
                       Compared by BODY, never by name: OtBlk_80015498 and OtBlk_80016450 are the
                       same {s32 a; s32 b[4];}, while Elem12 and B12 genuinely differ and are
                       refused. (This body comparison is also the answer to §176h.C's limit.)
  * SIGNEDNESS         `extern u16 D_x` vs `extern s16 D_x` -> adopt the TU's spelling.
  * ARRAY-VS-SCALAR    `u8 D_x[]` vs `u8 D_x` -> adopt the TU's, fixing the use site
                       (`D_x[i]` <-> `(&D_x)[i]`).
  * ALIAS              `short` vs `s16` -> adopt the TU's spelling (no code change at all).

WHAT IT REFUSES, AND WHY (these are decisions, not edits):
  * DIFFERENT-STRUCT   two genuinely different layouts for one symbol -- someone modelled it wrong.
  * IMMOVABLE-TU-DECL  the draft needs the TU's own declaration changed. gate_main REVERTS src/
                       before every build, so this can never ride inside a slate: it needs its own
                       commit + rebuild + R22.
  * DEF-SIDE-RETURN    the TU prototypes the function with a different RETURN type. Adopting it
                       usually breaks the match (measured on func_8001ABBC: `void` cost the match).

Usage:
  reconcile_slate.py <slate.json> [--apply] [--max-rounds N]
     default is a DRY RUN listing what it would do.
     --apply rewrites the DRAFTS (never the tree) and loops until 0 dropped or no progress.
"""
import argparse, json, os, re, subprocess, sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import corpus
import gate_main as gm

SIG = re.compile(r"^\('(?P<ret>[^']*)', '(?P<tail>[^']*)'\)$")


FNSIG = re.compile(r"^\('(?P<ret>[^']*)', \((?P<params>.*)\)\)$")


def _parse_fnsig(sig):
    """('void', ('s32', 'u8*')) -> ('void', ['s32','u8*']); (None, None) if not a function sig."""
    m = FNSIG.match(sig)
    if not m:
        return None, None
    params = [p.strip().strip("'") for p in m.group('params').split(',') if p.strip()]
    return m.group('ret'), params


def _apply_tu_params(path, fn, mine, theirs):
    """§176d, mechanized: adopt the TU's parameter types on the DEFINITION and re-narrow inside
    the body, so the emitted bytes are unchanged.

        void f(s16 a0)  ->  void f(s32 a0_p) { s16 a0 = (s16)a0_p; <original body unchanged> }

    A shadowing local is used rather than rewriting every use site: it is one textual insertion,
    the body is untouched, and the cast emits the same sll/sra pair the narrow parameter did. The
    caller re-verifies with match_one and reverts if a single byte moves, so attempting it is
    free."""
    src = open(path).read()
    m = re.search(r'^([A-Za-z_][\w \t\*]*?)\b%s\s*\(([^;{]*)\)\s*\{' % re.escape(fn), src, re.M)
    if not m or len(mine) != len(theirs):
        return False
    decls = [d.strip() for d in m.group(2).split(',')]
    if len(decls) != len(mine):
        return False
    new_decls, shims = [], []
    for d, mt, tt in zip(decls, mine, theirs):
        nm = re.findall(r'(\w+)\s*$', d)
        if not nm:
            return False
        nm = nm[0]
        if mt == tt:
            new_decls.append(d)
            continue
        new_decls.append('%s %s_p' % (tt.replace('*', ' *'), nm))
        shims.append('    %s %s = (%s)%s_p;' % (mt.replace('*', ' *'), nm,
                                                mt.replace('*', ' *'), nm))
    if not shims:
        return False
    head = '%s%s(%s) {\n%s' % (m.group(1), fn, ', '.join(new_decls), '\n'.join(shims))
    open(path, 'w').write(src[:m.start()] + head + src[m.end():])
    return True


def _bodies(text):
    out = {}
    for pat in (gm.TYPEDEF_BLOCK, gm.TYPEDEF_PLAIN):
        for m in pat.finditer(text):
            out.setdefault(m.group(1), re.sub(r'\s+', ' ', m.group(0)))
    return out


def _same_struct(a_name, a_body, b_name, b_body):
    """Structurally identical modulo the typedef's own name?"""
    if not (a_body and b_body):
        return False
    return (re.sub(r'\b%s\b' % re.escape(a_name), 'X', a_body) ==
            re.sub(r'\b%s\b' % re.escape(b_name), 'X', b_body))


def verify(fn, draft):
    st = {s.symbol: s for s in corpus.stubs('main').values()}.get(fn)
    if not st:
        return False
    r = subprocess.run(['.venv/bin/python', 'tools/match_one.py', fn, '--c', draft,
                        '--asm-subdir', st.asm_dir], capture_output=True, text=True)
    o = r.stdout + r.stderr
    return 'MATCH' in o and 'NOMATCH' not in o


def classify(drop, draft_text, tu_bodies, draft_bodies):
    """-> (kind, detail). kind in {cosmetic, signedness, array, alias, refuse-*}"""
    kept, this = drop['kept'], drop['this']
    mk, mt = SIG.match(kept), SIG.match(this)
    if drop['symbol'] == drop['fn']:
        # FUNCTION conflict. SIG only parses DATA declarations -- a function signature is
        # ('void', ('s32', ...)), whose tail is a tuple, not a quoted string -- so every function
        # conflict used to fall through to "DEF-SIDE-RETURN" even when only the PARAMETERS
        # differed. That distinction decides whether the case is fixable: differing params yield
        # to the §176d lever (adopt the TU's types, narrow inside the body), differing RETURNS
        # usually cost the match (measured: `void` on func_8001ABBC).
        kr, kp = _parse_fnsig(kept)
        tr, tp = _parse_fnsig(this)
        if kr is not None and kr == tr and kp != tp:
            return 'defparams', (tp, kp)
        return 'refuse-DEF-SIDE-RETURN', f'{this} vs TU {kept}'
    if not (mk and mt):
        return 'refuse-SIGNATURE', f'{this} vs {kept}'
    kr, tr = mk['ret'].rstrip('*'), mt['ret'].rstrip('*')
    # local struct types on both sides?
    if kr in tu_bodies and tr in draft_bodies:
        if _same_struct(kr, tu_bodies[kr], tr, draft_bodies[tr]):
            return 'cosmetic', (tr, kr)
        return 'refuse-DIFFERENT-STRUCT', f'{tr} and {kr} have different layouts'
    if mk['tail'] != mt['tail']:
        return 'array', (mt['ret'], mk['ret'], mk['tail'])
    if gm._alias(mk['ret']) == gm._alias(mt['ret']):
        return 'alias', (mt['ret'], mk['ret'])
    if {kr, tr} <= {'u8', 's8', 'u16', 's16', 'u32', 's32'}:
        return 'signedness', (mt['ret'], mk['ret'])
    return 'refuse-TYPE', f'{mt["ret"]} vs {mk["ret"]}'


def repair(kind, detail, sym, path):
    """Rewrite the draft. Returns True if the file changed."""
    src = open(path).read()
    if kind == 'cosmetic':
        old, new = detail
        out = re.sub(r'\b%s\b' % re.escape(old), new, src)
    elif kind in ('signedness', 'alias'):
        old, new = detail
        out = re.sub(r'(extern\s+)%s(\s+%s\b)' % (re.escape(old), re.escape(sym)),
                     r'\g<1>%s\g<2>' % new, src)
    elif kind == 'defparams':
        mine, theirs = detail
        return _apply_tu_params(path, sym, mine, theirs)
    elif kind == 'array':
        _mine, tu_ret, tu_tail = detail
        if tu_tail == '[]':                    # TU says array, draft says scalar
            out = re.sub(r'(extern\s+[^;]*\b%s\b)\s*;' % re.escape(sym), r'\1[];', src)
            out = re.sub(r'&%s\b' % re.escape(sym), sym, out)
        else:                                  # TU says scalar, draft says array
            out = re.sub(r'(extern\s+[^;]*\b%s\b)\s*\[\s*\]\s*;' % re.escape(sym), r'\1;', src)
            out = re.sub(r'(?<![&\w])%s\b(?!\s*[;\[])' % re.escape(sym), '(&%s)' % sym, out)
    else:
        return False
    if out == src:
        return False
    open(path, 'w').write(out)
    return True


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('slate')
    ap.add_argument('--apply', action='store_true')
    ap.add_argument('--max-rounds', type=int, default=6)
    a = ap.parse_args()

    slate = json.load(open(a.slate))
    tu_bodies = _bodies(open('src/800.c').read())
    refusals, fixed_total = [], []

    for rnd in range(1, a.max_rounds + 1):
        kept, dropped = gm.resolve_conflicts(slate)
        print(f'round {rnd}: {len(slate)} -> {len(kept)} compatible, {len(dropped)} dropped')
        if not dropped:
            break
        progress = 0
        for d in dropped:
            path = next(e['draft'] for e in slate if e['fn'] == d['fn'])
            text = open(path).read()
            kind, detail = classify(d, text, tu_bodies, _bodies(text))
            if kind.startswith('refuse'):
                refusals.append((d['fn'], d['symbol'], kind, detail))
                continue
            if not a.apply:
                print(f"   would fix {d['fn']:22s} {d['symbol']:16s} {kind}")
                progress += 1
                continue
            before = text
            if not repair(kind, detail, d['symbol'], path):
                refusals.append((d['fn'], d['symbol'], 'refuse-NO-EDIT', str(detail)))
                continue
            if verify(d['fn'], path):
                print(f"   FIXED {d['fn']:22s} {d['symbol']:16s} {kind}  (re-verified MATCH)")
                fixed_total.append(d['fn'])
                progress += 1
            else:
                open(path, 'w').write(before)   # a repair that moves a byte is not a repair
                refusals.append((d['fn'], d['symbol'], 'refuse-BROKE-MATCH', kind))
                print(f"   revert {d['fn']:22s} {d['symbol']:16s} {kind} broke the match")
        if not a.apply or not progress:
            break

    kept, dropped = gm.resolve_conflicts(slate)
    print(f'\nFINAL: {len(kept)}/{len(slate)} compatible, {len(dropped)} dropped; '
          f'{len(fixed_total)} auto-reconciled')
    if refusals:
        print('\nNEEDS A HUMAN DECISION (not mechanical):')
        seen = set()
        for fn, sym, kind, detail in refusals:
            if (fn, sym) in seen:
                continue
            seen.add((fn, sym))
            print(f'   {kind:24s} {fn:22s} {sym:16s} {detail}')
    json.dump([e for e in slate if e['fn'] in {k['fn'] for k in kept}],
              open(a.slate.replace('.json', '_reconciled.json'), 'w'), indent=1)
    print(f"\nreconciled slate -> {a.slate.replace('.json', '_reconciled.json')}")


if __name__ == '__main__':
    main()
