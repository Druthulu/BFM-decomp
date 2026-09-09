#!/usr/bin/env python3
"""Unify a harvest draft's FULL signature set (callee externs AND the draft's own definition
signature) to the banked-canonical set — the recovery pass for the standalone-MATCH residual.

Phase 15 / T6 (cookbook §14c, extends canon_draft_decls). The dominant gate-failure for the
call-heavy shared core is a TU-level signature conflict on a draft whose BODY is already
byte-correct (it passes `match_one`). `canon_draft_decls` rewrites the draft's *callee* extern
lines to canonical, but it never touches the draft's OWN definition signature — and a probe
(30/30 sampled standalone-MATCH failures = type conflicts, 0 false-positives) showed the dominant
conflict is exactly that: the function is *defined* `void`/`s16`/... here, but already
*extern-declared* `s32` by the banked callers in the same TU -> `conflicting types for func_X`.

This rewrites, for each draft:
  (1) every `extern ...;` line for a func/data symbol -> the banked-canonical declaration
      (the canon_draft_decls behaviour), and
  (2) the draft's OWN `<ret> func_X(<params>) {` definition header -> the canonical RETURN type
      and canonical PARAM TYPES (names taken from the draft so the body still resolves), with an
      arity-mismatch fallback that rewrites only the return type.

Codegen-neutrality is NOT assumed (widening a narrow return is byte-neutral; a param-type change
may not be) — the whole-binary `harvest_verify` byte-gate remains the sole arbiter (G3/P9): a
unification that changes the body's bytes just fails the gate and reverts. Never a wrong match.

Usage:
  tools/sig_unify.py --overlay ov_SC01_077 --in .run/drafts-X --out .run/drafts-X-uni
"""
import argparse, os, re, glob, importlib.util

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))

_spec = importlib.util.spec_from_file_location(
    'ght', os.path.join(REPO, 'tools/gen_harvest_targets.py'))
_ght = importlib.util.module_from_spec(_spec)
_spec.loader.exec_module(_ght)

DATA_DECL_RE = re.compile(
    r'extern\s+([A-Za-z_][\w\s\*]*?\bD_[0-9A-Fa-f]+\s*(?:\[\s*\])?)\s*;')
DRAFT_EXTERN_LINE_RE = re.compile(r'^[ \t]*extern\b[^;]*;[ \t]*$', re.M)
# m2c emits callee prototypes WITHOUT `extern`: `<type> func_X(<params>);  /* extern */`.
# Canonicalize these too, else they keep m2c's GUESSED signature and `conflicting types` in the
# whole-binary build (the body is usually byte-correct; only the decl conflicts). Phase-16 fix.
PROTO_DECL_RE = re.compile(
    r'^[ \t]*[A-Za-z_][\w \t\*]*\bfunc_[0-9A-Fa-f]+\s*\([^;{]*\)\s*;[ \t]*(?:/\*[^\n]*\*/)?[ \t]*$', re.M)


def sym_of(decl):
    m = re.search(r'\b(func_[0-9A-Fa-f]+|D_[0-9A-Fa-f]+)\b', decl)
    return m.group(1) if m else None


def collect_data_decls(paths):
    out = {}
    for p in paths:
        if not os.path.exists(p):
            continue
        for m in DATA_DECL_RE.finditer(open(p).read()):
            decl = re.sub(r'\s+', ' ', m.group(1)).strip()
            s = sym_of(decl)
            if s:
                out.setdefault(s, f'extern {decl};')
    return out


def split_top_commas(s):
    """split a parameter list on top-level commas (respects nested parens/brackets)."""
    out, depth, cur = [], 0, ''
    for ch in s:
        if ch in '([':
            depth += 1
        elif ch in ')]':
            depth -= 1
        if ch == ',' and depth == 0:
            out.append(cur)
            cur = ''
        else:
            cur += ch
    if cur.strip():
        out.append(cur)
    return out


def param_type(p):
    """'s32 a0'->'s32'; 's32 *a0'->'s32 *'; 'struct Foo *x'->'struct Foo *'; 's32'->'s32'."""
    p = p.strip()
    m = re.match(r'^(.*?)([A-Za-z_]\w*)\s*$', p, re.S)
    if not m:
        return p
    head = m.group(1).strip()
    return head if head else p          # nothing before the last ident -> unnamed type


def param_name(p):
    p = p.strip()
    m = re.search(r'([A-Za-z_]\w*)\s*$', p)
    return m.group(1) if m else None


def parse_canon_sig(decl):
    """'extern s32 func_X(s32 *a0, s32 a1);' -> ('s32', ['s32 *','s32'])."""
    m = re.match(r'extern\s+(.*?)\b(func_[0-9A-Fa-f]+)\s*\((.*)\)\s*;\s*$', decl.strip(), re.S)
    if not m:
        return None
    ret = re.sub(r'\s+', ' ', m.group(1)).strip()
    params = m.group(3).strip()
    if params in ('', 'void'):
        ptypes = []
    else:
        ptypes = [param_type(x) for x in split_top_commas(params)]
    return ret, ptypes


def rewrite_def(txt, fn, canon):
    """rewrite the draft's own definition header to the canonical return/param types."""
    if fn not in canon:
        return txt, False
    sig = parse_canon_sig(canon[fn])
    if not sig:
        return txt, False
    cret, cptypes = sig
    # match the definition header: `<ret> func_X(<params>) {`  (params have no nested parens here)
    rx = re.compile(r'(?P<lead>(?:^|\n)[ \t]*)(?P<ret>[A-Za-z_][\w \t\*]*?)\s*\b'
                    + re.escape(fn) + r'\s*\((?P<params>[^()]*)\)\s*\{', re.S)
    m = rx.search(txt)
    if not m:
        return txt, False
    dparams_raw = m.group('params').strip()
    if dparams_raw in ('', 'void'):
        dnames = []
    else:
        dnames = [param_name(x) for x in split_top_commas(dparams_raw)]
    if len(cptypes) == len(dnames) and all(dnames):
        newparams = ', '.join(f'{t} {n}' for t, n in zip(cptypes, dnames)) if dnames else 'void'
    elif len(cptypes) > len(dnames):
        # arity mismatch, canonical declares MORE params than the draft body uses: ADOPT the
        # canonical param types+count (the DEF-side loose-typing wall — Phase 20/21). Keep the
        # draft's names where they exist (body still resolves); synth names for the extras — unused,
        # they sit in $a0..$a3, free at -O2. The whole-binary byte-gate reverts anything not byte-exact.
        names = [(dnames[i] if i < len(dnames) and dnames[i] else f'_arg{i}') for i in range(len(cptypes))]
        newparams = ', '.join(f'{t} {n}' for t, n in zip(cptypes, names))
    else:                                  # canonical has FEWER params than the draft -> return type only
        newparams = dparams_raw if dparams_raw else 'void'
    new_hdr = f'{m.group("lead")}{cret} {fn}({newparams})\n{{'
    if re.sub(r'\s+', ' ', new_hdr).strip() == re.sub(r'\s+', ' ', m.group(0)).strip():
        return txt, False
    return txt[:m.start()] + new_hdr + txt[m.end():], True


_cdecl = _load('cdecl', 'tools/cdecl.py') if '_load' in dir() else None


def _tu_for(overlay, fn):
    """The TU that holds this function's stub — DERIVED (corpus.stubs); None if it is not an open
    stub anywhere (already banked, or not ours)."""
    try:
        import importlib.util
        spec = importlib.util.spec_from_file_location('corpus', os.path.join(REPO, 'tools/corpus.py'))
        c = importlib.util.module_from_spec(spec)
        spec.loader.exec_module(c)
        st = c.stubs(overlay).get(int(fn[5:], 16))
        return os.path.join(REPO, st.path) if st else None
    except Exception:
        return os.path.join(REPO, f'src/{overlay}/{overlay}.c')


def _canon_for(tu):
    """{symbol: 'extern <canonical decl>;'} — DERIVED from what cc1 sees in THIS TU (cpp), so the
    macro-injected `DEFINE_func_*` externs are finally visible. The old union of three raw-text
    scanners (collect_define_sigs + collect_inline_sigs + collect_extern_sigs) could not see them,
    and its DATA_DECL_RE was blind to fn-ptr / sized-array / multi-declarator decls (44 of 646
    symbols in this very corpus) — so the recovery pass silently did nothing for exactly the symbols
    that were failing."""
    import cdecl as cd
    out = {}
    for name, d in cd.tu_scope(tu).items():
        if d.storage == 'typedef':
            continue
        out[name] = d.declaration(storage='extern')
    return out


def _keep(draft_line, canon_decl):
    """Leave the draft's decl alone when cc1 would accept it beside the TU's. sig_unify's known
    failure mode is REGRESSING already-correct drafts (§19/§25: 'canon-first, sig_unify FALLBACK'),
    and a rewrite that changes nothing semantic can still perturb codegen. Rewrite only when the
    front end would actually reject the pair."""
    try:
        import cdecl as cd
        a = cd.parse(canon_decl)[0]
        b = cd.parse(draft_line.strip())[0]
        return cd.compatible(a, b)
    except Exception:
        return False


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('--overlay', default='ov_SC01_077')
    ap.add_argument('--src-file', dest='src_file', default=None,
                    help='overlay SPLIT .c the drafts target (e.g. ov_SC01_077_a.c / _o0.c); default = '
                         'the main .c. Reads cur_stubs + inline/extern canonical sigs from THIS file so '
                         'split-file drafts are NOT dropped (they are stubs in the split, not the main .c) '
                         'and get the def-side arity-adopt recovery. engine_prelude.h is always included.')
    ap.add_argument('--in', dest='indir', required=True)
    ap.add_argument('--out', dest='outdir', required=True)
    args = ap.parse_args()

    override = os.path.join(REPO, args.src_file) if args.src_file else None
    os.makedirs(os.path.join(REPO, args.outdir), exist_ok=True)

    n = ext_rw = def_rw = passthru = 0
    _canon_cache = {}
    for p in sorted(glob.glob(os.path.join(REPO, args.indir, '*.c'))):
        fn = os.path.basename(p)[:-2]
        txt = open(p).read()

        # WHICH TU? DERIVED (Phase 26-A, §51g LAW 10). `--src-file` was an optional hand-passed flag
        # defaulting to src/<ov>/<ov>.c, and `cur_stubs` was read from THAT file — so a draft whose
        # stub lives in a Phase-26 `_jr_<ADDR>` carve was not in the set and hit
        #     if fn not in cur_stubs: continue
        # which dropped it BEFORE THE WRITE. It never reached --out, was never gated, was never
        # logged; the summary just printed a smaller "drafts unified" and read like success.
        # MEASURED: 190 of 196 drafts (97%) silently vanished — and this is gate_stage's STAGE-2
        # RECOVERY, the pass whose whole job is to rescue the stage-1 failures. It has been a no-op
        # for almost every draft it was meant to save.
        # corpus.stubs() knows which TU holds each stub (the INCLUDE_ASM line is self-describing),
        # so the derivation IS the check and the silent drop is now structurally impossible.
        tu = override or _tu_for(args.overlay, fn)
        if tu is None:                              # not an open stub anywhere -> nothing to unify
            open(os.path.join(REPO, args.outdir, os.path.basename(p)), 'w').write(txt)
            passthru += 1                           # PASSED THROUGH and COUNTED, never dropped
            continue
        if tu not in _canon_cache:
            _canon_cache[tu] = _canon_for(tu)
        canon = _canon_cache[tu]
        ext_changed = False

        def repl(m):
            nonlocal ext_changed
            line = m.group(0)
            s = sym_of(line)
            if s and s in canon and not _keep(line, canon[s]):
                new = canon[s]
                if re.sub(r'\s+', ' ', new).strip() != re.sub(r'\s+', ' ', line).strip():
                    ext_changed = True
                return re.match(r'^[ \t]*', line).group(0) + new
            return line

        txt = DRAFT_EXTERN_LINE_RE.sub(repl, txt)

        def repl_proto(m):
            nonlocal ext_changed
            line = m.group(0)
            s = sym_of(line)
            if s and s != fn and s in canon and not _keep(line, canon[s]):
                new = canon[s]
                if re.sub(r'\s+', ' ', new).strip() != re.sub(r'\s+', ' ', line).strip():
                    ext_changed = True
                return re.match(r'^[ \t]*', line).group(0) + new
            return line

        txt = PROTO_DECL_RE.sub(repl_proto, txt)
        txt, def_changed = rewrite_def(txt, fn, canon)
        open(os.path.join(REPO, args.outdir, os.path.basename(p)), 'w').write(txt)
        n += 1
        ext_rw += ext_changed
        def_rw += def_changed

    print(f'drafts in: {n + passthru}; unified: {n}; passed through (not an open stub): {passthru}; '
          f'TUs: {len(_canon_cache)}')
    print(f'  callee-externs rewritten in {ext_rw}, OWN def-sig rewritten in {def_rw}')


if __name__ == '__main__':
    main()
