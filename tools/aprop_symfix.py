"""Rebase stale SEED symbols in adapt/A-prop drafts onto the TARGET's own symbols.

WHY THIS EXISTS (S50, cookbook §171). The adapt/A-prop lanes hand an agent a *proven seed body*
from one location plus a small token-diff, and the agent adapts the code — but a per-location data
symbol (`D_8018xxxx`, a function-pointer table, a jump table) is part of the seed's ENVIRONMENT,
not its logic. Carry it over unrebased and:

  - `match_one` still scores MATCH. It compiles standalone and compares instruction encodings;
    a `%hi(D_seed)` and a `%hi(D_target)` are the same instruction with a different relocation
    TARGET NAME, and the scorer is blind to the name.
  - the whole-binary gate then fails at LINK: `undefined reference to 'D_seed'`.

That gap — standalone-MATCH, link-undefined — was the entire A-prop 91%-agent-vs-57%-gate delta
measured in S49 (24 of 24 concentrated failures; §170's TU-collision hypothesis was refuted by
the same data: 5-draft groups banked 5/5).

This is the SECOND, DISAGREEING ORACLE (R34) for that class: match_one says MATCH, the symbol
audit says the draft references a symbol the target's own .s never mentions. It is deterministic
and costs no build, so it belongs BEFORE the gate, never after.

  audit:  tools/aprop_symfix.py <slate.json>            (report only)
  fix:    tools/aprop_symfix.py <slate.json> --fix      -> .run/aprop_symfix/<fn>/<fn>.c + slate

A slate record is {fn|name, binary, draft}; the emitted slate points `draft` at the fixed copy so
`tools/gate_lane.py` consumes it unchanged.
"""
import argparse, collections, json, os, re, sys

sys.path.insert(0, os.path.join(os.path.dirname(__file__)))
import corpus

# vram-suffixed symbols: D_80185A28, func_801727D0, jtbl_8018xxxx, ...
SYM = re.compile(r'\b[A-Za-z_][A-Za-z0-9_]*_?8[0-9A-Fa-f]{7}\b')
ASM_OPS = re.compile(r'%hi\(([^)]+)\)|%lo\(([^)]+)\)|\bjal\s+([A-Za-z_]\w*)|\.word\s+([A-Za-z_]\w*)')


def _strip_comments(txt):
    return re.sub(r'//[^\n]*', '', re.sub(r'/\*.*?\*/', '', txt, flags=re.S))


def syms_in_text(txt):
    return set(SYM.findall(_strip_comments(txt)))


def draft_syms(path):
    return syms_in_text(open(path).read())


def body_text(path, name):
    """The C body of ONE function out of a file (a draft is one function; a seed's file is not).

    Matches an `DEFINE_<name>(` engine_core macro or a plain definition, then brace-matches. A
    whole-file scan would drag every OTHER function's symbols into the comparison and drown the
    signal, so callers annotating a SEED must pass through here."""
    if not path or not os.path.isfile(path):
        return None
    txt = _strip_comments(open(path).read())
    m = (re.search(rf'\bDEFINE_{re.escape(name)}\s*\(', txt) or
         re.search(rf'^[A-Za-z_][^\n=;]*\b{re.escape(name)}\s*\(', txt, re.M))
    if not m:
        return None
    i = txt.find('{', m.start())
    if i < 0:
        return None
    depth = 0
    for j in range(i, len(txt)):
        if txt[j] == '{':
            depth += 1
        elif txt[j] == '}':
            depth -= 1
            if depth == 0:
                return txt[m.start():j + 1]
    return None


def asm_syms(path):
    out = set()
    for m in ASM_OPS.finditer(open(path).read()):
        for g in m.groups():
            if g:
                out.add(g.split('+')[0].strip())
    return out


def diff_syms(c_path, asm_path, self_name):
    """Compare a C body's symbols against the symbols its target .s actually relocates.

    Shared primitive: `aprop_symfix` uses it on a DRAFT (post-hoc guard), `family_cousins.sym_map`
    uses it on the SEED BODY (pre-hoc card annotation). A matched seed has no `.s` of its own —
    it is compiled from C — so the seed side must always be read from the C text (R33: one
    implementation, two callers, rather than two drifting re-parsers).

    -> (status, stale[], asm_only[]). status: clean | STALE | AMBIGUOUS | NO_ASM | NO_DRAFT.
    """
    if not c_path or not os.path.isfile(c_path):
        return 'NO_DRAFT', [], []
    return diff_syms_text(open(c_path).read(), asm_path, self_name)


def diff_syms_text(c_text, asm_path, self_name, ignore=()):
    """`ignore` names FUNCTION IDENTITIES to exclude from both sides — the caller's own name plus,
    for a seed body, the SEED's name. Compared case-insensitively (sig_image spells hex lowercase,
    splat uppercase) and with the `DEFINE_` macro prefix stripped, or a macro-bodied seed reports
    its own name as a stale symbol and every 1:1 rename degrades to AMBIGUOUS."""
    if c_text is None:
        return 'NO_DRAFT', [], []
    if not asm_path or not os.path.exists(asm_path):
        return 'NO_ASM', [], []
    ign = {n.lower() for n in (self_name, *ignore) if n}
    def own(s):
        return re.sub(r'^DEFINE_', '', s).lower() in ign
    d, a = syms_in_text(c_text), asm_syms(asm_path)
    stale = sorted(s for s in d - a if not own(s))
    asm_only = sorted(s for s in a - d if not own(s) and not s.startswith('.'))
    if not stale:
        return 'clean', [], asm_only
    # 1:1 is the mechanically-safe case (one seed symbol, one target symbol to take its place).
    return ('STALE' if len(stale) == 1 and len(asm_only) == 1 else 'AMBIGUOUS'), stale, asm_only


def audit_one(fn, binary, draft):
    return diff_syms(draft, corpus.asm_path(binary, fn), fn)


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('slate')
    ap.add_argument('--fix', action='store_true', help='write rebased copies + a gateable slate')
    ap.add_argument('--outdir', default='.run/aprop_symfix')
    ap.add_argument('--out-slate', default='.run/aprop_symfix_slate.json')
    ap.add_argument('--skip', help='json list of already-banked fn names to exclude')
    a = ap.parse_args()

    recs = [r for r in json.load(open(a.slate)) if isinstance(r, dict) and (r.get('fn') or r.get('name'))]
    skip = set(json.load(open(a.skip))) if a.skip else set()
    seen, rows = set(), []
    for r in recs:
        fn = r.get('fn') or r['name']
        if fn in skip or fn in seen:
            continue
        seen.add(fn)
        draft = r.get('draft') or f".run/aprop1/{fn}/{fn}.c"
        st, stale, asm_only = audit_one(fn, r['binary'], draft)
        rows.append(dict(fn=fn, binary=r['binary'], draft=draft, status=st,
                         stale=stale, asm_only=asm_only, sub=r.get('sub')))

    cls = collections.Counter(x['status'] for x in rows)
    if not rows:  # R32: a silent skip is a DEFECT
        sys.exit(f"R32: {a.slate} yielded 0 auditable records — wrong shape or everything skipped?")
    print(f"{len(rows)} drafts audited: {dict(cls)}")
    for x in rows:
        if x['status'] in ('STALE', 'AMBIGUOUS'):
            print(f"  {x['status']:9} {x['fn']:16} {x['binary']:12} "
                  f"draft-only={x['stale']} asm-only={x['asm_only']}")

    if not a.fix:
        json.dump(rows, open('.run/aprop_symcheck.json', 'w'), indent=1)
        print("audit only — wrote .run/aprop_symcheck.json")
        return

    slate, deltas = [], collections.Counter()
    for x in rows:
        if x['status'] != 'STALE':
            continue
        old, new = x['stale'][0], x['asm_only'][0]
        txt = open(x['draft']).read()
        fixed, n = re.subn(rf'\b{re.escape(old)}\b', new, txt)
        if n == 0:  # R32: prove the edit ran (R37) rather than assuming it did
            print(f"  !! {x['fn']}: 0 substitutions of {old} — skipped")
            continue
        d = os.path.join(a.outdir, x['fn'])
        os.makedirs(d, exist_ok=True)
        p = os.path.join(d, f"{x['fn']}.c")
        open(p, 'w').write(fixed)
        deltas[int(new[2:], 16) - int(old[2:], 16)] += 1
        slate.append(dict(fn=x['fn'], binary=x['binary'], sub=x['sub'], draft=p,
                          rebased=f"{old}->{new}", subs=n))
    json.dump(slate, open(a.out_slate, 'w'), indent=1)
    print(f"\nrebased {len(slate)}/{cls['STALE']} STALE drafts -> {a.outdir}")
    print(f"seed->target vram deltas: {[(hex(k), v) for k, v in deltas.items()]}")
    print(f"gateable slate: {a.out_slate}")


if __name__ == '__main__':   # importable: family_cousins reuses the primitives above
    main()
