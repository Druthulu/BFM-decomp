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

# A function declaration line (prototype ending in `;`, NOT a definition): optional `extern`,
# a type, func_X, a param list, `;`, optional trailing /* comment */. Matches both the
# `extern void func_X(int,int);` form and the bare `s32 func_X(s32,void*,s32);` m2c form.
DECL_LINE_RE = re.compile(
    r'^([ \t]*)(extern\s+)?([A-Za-z_][\w \t\*]*?)\b(func_[0-9A-Fa-f]+)\s*\(([^;{]*)\)\s*;'
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


def canonical_map(overlay):
    """addr-int -> canonical sig string '<ret> func_X(<params>)' for every func the TU declares
    or defines (definitions/inline win over plain externs — the authoritative in-TU signature).
    Mirrors sig_unify's precedence exactly."""
    ec = os.path.join(REPO, 'src/shared/engine_core.h')
    c_path = os.path.join(REPO, f'src/{overlay}/{overlay}.c')
    sigs = dict(_ght.collect_extern_sigs([ec, c_path]))
    sigs.update(_ght.collect_define_sigs(ec))
    sigs.update(_ght.collect_inline_sigs(c_path))
    return sigs, c_path


def split_sig_string(s):
    """'void func_X(s16 a0, s16 a1)' -> ('void', 's16 a0, s16 a1')  (no extern / no ;)."""
    m = re.match(r'(.*?)\bfunc_[0-9A-Fa-f]+\s*\((.*)\)\s*$', s.strip(), re.S)
    if not m:
        return None
    return m.group(1).strip(), m.group(2).strip()


def transform(text, self_fn, canon):
    """Return (new_text, n_callees_cast). For each callee whose canonical TU sig differs from the
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
        addr = int(fn[5:], 16)
        if addr not in canon:                       # pure stub callee: draft's decl is the only
            continue                                # one -> no conflict, leave it (don't cast)
        dret, dptypes = parse_sig(ret, params)
        csig = split_sig_string(canon[addr])
        if not csig:
            continue
        cret, cptypes = parse_sig(*csig)
        if norm_sig(dret, dptypes) == norm_sig(cret, cptypes):
            continue                                # already compatible -> no cast needed
        to_cast[fn] = cast_type(dret, dptypes)
        canon_decl[fn] = f'{indent}extern {canon[addr]};'
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
    ap.add_argument('--in', dest='indir', required=True)
    ap.add_argument('--out', dest='outdir', required=True)
    a = ap.parse_args()

    canon, _c_path = canonical_map(a.overlay)
    os.makedirs(os.path.join(REPO, a.outdir), exist_ok=True)
    drafts = touched = total_callees = 0
    for p in sorted(glob.glob(os.path.join(REPO, a.indir, '*.c'))):
        fn = os.path.basename(p)[:-2]
        new, k = transform(open(p).read(), fn, canon)
        open(os.path.join(REPO, a.outdir, os.path.basename(p)), 'w').write(new)
        drafts += 1
        if k:
            touched += 1
            total_callees += k
    print(f'canonical sigs: {len(canon)}; drafts: {drafts}; '
          f'cast-recovered: {touched} draft(s), {total_callees} callee(s)')


if __name__ == '__main__':
    main()
