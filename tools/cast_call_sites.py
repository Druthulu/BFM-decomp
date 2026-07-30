#!/usr/bin/env python3
"""cast_call_sites.py — the §17a-1 per-site function-pointer cast recovery (Phase 20, cookbook §20).

THE wave-at-scale gate cap (the §20 loose-typing call-graph wall). At the reach-134 tail a draft
passes `match_one` (compiles STANDALONE with its own externs, masks jal/%hi/%lo) but FAILS the
whole-binary gate: a callee (e.g. func_80153C74) is DEFINED in this overlay's TU with one signature
(the engine_core.h `DEFINE_func_80153C74()` body `void func_80153C74(s16,s16)`), while the draft
declares it `extern void func_80153C74(int,int)` for its own byte-match -> in-TU
`conflicting types for func_80153C74` (a COMPILE error, not a byte miss).

Every cheaper lever fails here (cookbook §20, all 0): `sig_unify`/`canon_draft_decls` rewrite the
draft's callee extern to the ONE canonical sig but leave the CALL `func_X(a,b)` -> the args get
converted to the canonical (narrow) param types -> DIFFERENT codegen -> byte miss; `fix_arity_callers`
is the caller side, not this; no-proto `void f()` is incompatible with the overlay's narrow def
`void f(s16,s16)`; strip-externs gives implicit-int.

The ONLY fix (§17a-1, byte-proven Phase 18 Step-1): for each conflicting callee, do BOTH —
  (1) rewrite the draft's callee DECL line to the canonical (conflict-free, keeps the symbol in
      scope as a forward declaration before the call), and
  (2) CAST every CALL site to the draft's INTENDED signature:
        func_X(a, b)            ->  ((<dret>(*)(<dptypes>))func_X)(a, b)
        x = func_X(a)           ->  x = ((<dret>(*)(<dptypes>))func_X)(a)
      gcc-2.7.2 folds the cast of a known function symbol back to a direct `jal func_X` with the
      draft's calling convention, so the body bytes are unchanged — there is no global decl that can
      conflict, and the call codegen matches the byte target. (Decl lines are never cast.)

This is a PURE draft-text transform (like sig_unify / canon_resident_calls): the whole-binary
`harvest_verify` byte-gate remains the sole arbiter (G3/P9) — a wrong transform just fails the gate
and reverts. It SUPERSEDES sig_unify for the callee-conflict class (it does sig_unify's extern
canonicalization PLUS the call-site cast). Run it on the canon_resident_calls output (intended
sigs intact); the DEF-side caller-conflict class is still `fix_arity_callers`' job (composes).

Pipeline (cookbook §20):
  draft -> canon_resident_calls -> cast_call_sites -> harvest_verify --chunk 1
  (then fix_arity_callers for any residual DEF-side `conflicting types ... (void)` caller conflicts)

Usage:
  tools/cast_call_sites.py --overlay ov_SC01_077 --in .run/drafts-t6-cn --out .run/drafts-t6-cast
"""
import argparse, os, re, glob, importlib.util

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))


def _load(mod, rel):
    spec = importlib.util.spec_from_file_location(mod, os.path.join(REPO, rel))
    m = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(m)
    return m


_ght = _load('ght', 'tools/gen_harvest_targets.py')
_su = _load('su', 'tools/sig_unify.py')           # reuse split_top_commas / param_type
_cdecl = _load('cdecl', 'tools/cdecl.py')         # THE declaration oracle (Phase 26-A, §51g)
_corpus = _load('corpus', 'tools/corpus.py')      # THE corpus oracle — which TU holds a stub


def tu_for(overlay, fn, override=None):
    """The TU this draft will actually be SPLICED INTO — DERIVED from the corpus, not hand-passed.

    `--src-file` was an OPTIONAL flag defaulting to `src/<ov>/<ov>.c`. Every caller that did not
    know to set it — and none of them know about the Phase-26 `_jr_<ADDR>` carve files — was
    therefore canonicalizing drafts against the MAIN .c while `harvest_verify` (fixed in A3)
    correctly spliced them into the jr split. The recovery passes were reconciling against a
    DIFFERENT TRANSLATION UNIT than the one that would compile the code, and the heavy Phase-26
    cores live in exactly those jr files.

    The INCLUDE_ASM line is self-describing, and corpus.stubs() reads it. Ask, don't assume."""
    if override:
        return override
    try:
        st = _corpus.stubs(overlay).get(int(fn[5:], 16))
        if st:
            return os.path.join(REPO, st.path)
    except Exception:
        pass
    return os.path.join(REPO, f'src/{overlay}/{overlay}.c')

# A function declaration line (prototype ending in `;`, NOT a definition): optional `extern`,
# a type, func_X, a param list, `;`, optional trailing /* comment */. Matches both the
# `extern void func_X(int,int);` form and the bare `s32 func_X(s32,void*,s32);` m2c form.
DECL_LINE_RE = re.compile(
    # The callee NAME is any identifier, not just `func_XXXXXXXX` (Phase 29 T78). A named PsyQ
    # symbol (`RotTransPers`, `ApplyMatrixSV`) is a callee like any other, and keying on the func_
    # form made every one of them structurally invisible to this tool — see canonical_map.
    r'^([ \t]*)(extern\s+)?([A-Za-z_][\w \t\*]*?)\b([A-Za-z_]\w*)\s*\(([^;{]*)\)\s*;'
    r'[ \t]*(?:/\*[^\n]*\*/)?[ \t]*$')


def parse_sig(ret, params):
    """('void', 'int a0, int a1') -> ('void', ['int','int']);  '' / 'void' params -> []."""
    ret = re.sub(r'\s+', ' ', ret).strip()
    params = params.strip()
    if params in ('', 'void'):
        ptypes = []
    else:
        ptypes = [_su.param_type(x) for x in _su.split_top_commas(params)]
    return ret, ptypes


def norm_sig(ret, ptypes):
    """A spelling-insensitive-ish key for 'do these sigs differ': collapse whitespace, treat the
    typedef int aliases as int (s32/int/long are byte-identical params -> casting them is a no-op,
    so we must NOT count them as a difference and emit a pointless cast)."""
    def canon_t(t):
        t = re.sub(r'\s+', ' ', t).strip()
        t = re.sub(r'\s*\*', ' *', t).strip()
        # int-family aliases collapse (same calling-convention / same width)
        t = re.sub(r'\b(s32|u32|int|unsigned int|unsigned|long|unsigned long|u_long)\b', 'int', t)
        return t
    return canon_t(ret), tuple(canon_t(t) for t in ptypes)


def cast_type(dret, dptypes):
    """'void',['int','int'] -> 'void (*)(int, int)';  's32',[] -> 's32 (*)(void)'."""
    inner = ', '.join(dptypes) if dptypes else 'void'
    return f'{dret} (*)({inner})'


def canonical_map(overlay, src_file=None):
    """addr-int -> canonical sig string '<ret> func_X(<params>)' — DERIVED from what cc1 actually
    sees in the TU (`cdecl.tu_scope`, i.e. cpp), not scraped out of the raw text.

    WHY THIS CHANGED (Phase 26-A, R33; cookbook §51g LAW 7)
    ------------------------------------------------------
    It used to union three raw-text scanners:
        collect_extern_sigs([engine_core.h, the .c]) + collect_define_sigs(ec) + collect_inline_sigs(c)
    and NONE of them can see a MACRO-INJECTED declaration — an `extern` inside a `DEFINE_func_*`
    macro body, which becomes a genuine file-scope declaration of every TU that invokes the macro.
    engine_core.h is 23,546 continuation lines inside 1,801 such macros, so this was not an edge case.

    The cost, measured: `func_801387B8` (a stub in 134 TUs) calls `func_80138DE0`, which its TU
    declares — via a macro expansion — as `s32 (s32, s32, s32)`. The draft declares `s32 (s32)`.
    The map returned NOTHING for that callee, so transform() took the
        `if addr not in canon: continue   # pure stub callee -> no conflict, leave it`
    branch — on a premise that was simply false — and the draft died with `conflicting types`,
    which reads downstream as an intrinsic compiler wall. cpp answers it exactly, in 54 ms.

    NAMED SYMBOLS TOO, AND THE KEY IS THE NAME (Phase 29 T78). This used to require
    `re.fullmatch(r'func_[0-9A-Fa-f]{8}', name)` and key by the parsed address, so every CURATED or
    PsyQ-library callee was invisible: `func_8012F40C`'s family failed 138x on
    `conflicting types for RotTransPers` and this tool — the one lever for exactly that class — could
    not see the symbol at all. Curated naming is something this project does MORE of as RE quality
    improves, so a func_-only predicate rots by design (the same shape as `stub_map`'s, Phase 26-A).
    """
    c_path = src_file or os.path.join(REPO, f'src/{overlay}/{overlay}.c')
    sigs = {}
    for name, d in _cdecl.tu_scope(c_path).items():
        if d.kind != 'func':
            continue
        sigs[name] = d.declaration(storage='').rstrip(';').strip()
    return sigs, c_path


def split_sig_string(s, fn=None):
    """'void func_X(s16 a0, s16 a1)' -> ('void', 's16 a0, s16 a1')  (no extern / no ;).

    ANY identifier, not just `func_XXXXXXXX` (Phase 29 T78). This was the THIRD place keyed on the
    func_ name form, and the one that survived the first two fixes: with `canonical_map` and
    `transform` widened, `RotTransPers` reached this function and got `None`, so `transform` took its
    `if not csig: continue` branch and cast nothing — a silent skip that looked exactly like "no
    conflict found". Pass `fn` to anchor on the known callee; otherwise the last identifier before
    the parameter list is used."""
    s = s.strip()
    if fn:
        m = re.match(rf'(.*?)\b{re.escape(fn)}\s*\((.*)\)\s*$', s, re.S)
    else:
        m = re.match(r'(.*?)\b[A-Za-z_]\w*\s*\((.*)\)\s*$', s, re.S)
    if not m:
        return None
    return m.group(1).strip(), m.group(2).strip()


_ABOVE = set()          # names the TU declares ABOVE the splice point (set by main/gate_stage)


def _no_conflict(canon_sig, draft_line, fn):
    """Will cc1 accept the TU's declaration of `fn` alongside the draft's? (cdecl.compatible, which
    is validated against the REAL gcc-2.7.2 cc1 on 1,485 live corpus pairs — `cdecl.py --compat`.)

    This replaces `norm_sig(...) == norm_sig(...)`, which collapsed the int family (s32|u32|int|
    unsigned|long) to ONE token and therefore called a SIGNEDNESS change "already compatible" and
    emitted no rewrite — while cc1 rejects that redeclaration outright. It was right about codegen
    (same width, same load) and wrong about the C FRONT END, which never reaches codegen.

    Order matters, and only cc1 could have told us so: a no-prototype decl followed by a
    narrow-param prototype CONFLICTS, but the reverse order is ACCEPTED (§51g / the Phase-15
    narrow-param wall). So the TU's decl goes first iff it is declared above the splice point.
    """
    try:
        c = _cdecl.parse(f'extern {canon_sig};')[0]
        d = _cdecl.parse(draft_line.strip())[0]
    except (_cdecl.CDeclError, IndexError):
        return False                                # unparseable -> be safe, reconcile it
    a, b = (c, d) if fn in _ABOVE else (d, c)       # TU order
    return _cdecl.compatible(a, b)


def transform(text, self_fn, canon):
    """Return (new_text, n_callees_cast). For each callee whose canonical TU sig CONFLICTS with the
    draft's intended sig: rewrite the decl line to canonical + cast every call to the intended sig."""
    lines = text.split('\n')

    # Pass 1: scan decl lines -> intended sigs; decide which callees conflict (need casting).
    to_cast = {}          # func_Y -> cast_type string (draft's intended sig)
    canon_decl = {}       # func_Y -> canonical decl line replacement (indentation preserved)
    decl_line_idx = {}    # func_Y -> set of line indices that are its decl line(s)
    for i, ln in enumerate(lines):
        m = DECL_LINE_RE.match(ln)
        if not m:
            continue
        indent, _extern, ret, fn, params = m.group(1), m.group(2), m.group(3), m.group(4), m.group(5)
        if fn == self_fn:
            continue
        if fn not in canon:                         # pure stub callee: draft's decl is the only
            continue                                # one -> no conflict, leave it (don't cast)
        dret, dptypes = parse_sig(ret, params)
        csig = split_sig_string(canon[fn], fn)
        if not csig:
            continue
        cret, cptypes = parse_sig(*csig)
        if _no_conflict(canon[fn], ln, fn):
            continue                                # cc1 accepts both -> no rewrite, no cast
        to_cast[fn] = cast_type(dret, dptypes)
        canon_decl[fn] = f'{indent}extern {canon[fn]};'
        decl_line_idx.setdefault(fn, set()).add(i)

    if not to_cast:
        return text, 0

    # Pass 2: rebuild. Decl lines of cast-callees -> canonical decl. Body lines -> cast the calls.
    call_res = {fn: re.compile(r'\b' + re.escape(fn) + r'\s*\(') for fn in to_cast}
    out = []
    for i, ln in enumerate(lines):
        replaced_decl = None
        for fn, idxs in decl_line_idx.items():
            if i in idxs:
                replaced_decl = fn
                break
        if replaced_decl is not None:
            out.append(canon_decl[replaced_decl])    # the canonical forward decl (no cast here)
            continue
        if DECL_LINE_RE.match(ln):                   # some OTHER decl line -> never cast in a decl
            out.append(ln)
            continue
        for fn, cty in to_cast.items():              # body line -> cast every call site
            ln = call_res[fn].sub(f'(({cty}){fn})(', ln)
        out.append(ln)
    return '\n'.join(out), len(to_cast)


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument('--overlay', default='ov_SC01_077')
    ap.add_argument('--src-file', dest='src_file', default=None,
                    help='overlay .c whose local decls the draft must match (default main; use the '
                         '_a.c/_o0.c split file for drafts that land there)')
    ap.add_argument('--in', dest='indir', required=True)
    ap.add_argument('--out', dest='outdir', required=True)
    a = ap.parse_args()

    override = a.src_file and os.path.join(REPO, a.src_file)
    os.makedirs(os.path.join(REPO, a.outdir), exist_ok=True)
    drafts = touched = total_callees = 0
    cache, ncanon = {}, 0
    for p in sorted(glob.glob(os.path.join(REPO, a.indir, '*.c'))):
        fn = os.path.basename(p)[:-2]
        # PER-DRAFT: canonicalize against the TU that will actually compile it (derived), not
        # against whatever .c the caller happened to name.
        tu = tu_for(a.overlay, fn, override)
        if tu not in cache:
            cache[tu] = canonical_map(a.overlay, tu)[0]
        canon = cache[tu]
        ncanon = max(ncanon, len(canon))
        # TU order for the no-prototype rule: which of the TU's decls precede this splice point?
        # (cdecl caches the cpp run, so this is ~free per draft.)
        _ABOVE.clear()
        _ABOVE.update(_cdecl.tu_scope(tu, above=fn))
        new, k = transform(open(p).read(), fn, canon)
        open(os.path.join(REPO, a.outdir, os.path.basename(p)), 'w').write(new)
        drafts += 1
        if k:
            touched += 1
            total_callees += k
    print(f'canonical sigs: {ncanon} (per-TU, derived); TUs: {len(cache)}; drafts: {drafts}; '
          f'cast-recovered: {touched} draft(s), {total_callees} callee(s)')


if __name__ == '__main__':
    main()
