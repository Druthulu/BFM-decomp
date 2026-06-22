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


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('--overlay', default='ov_SC01_077')
    ap.add_argument('--in', dest='indir', required=True)
    ap.add_argument('--out', dest='outdir', required=True)
    args = ap.parse_args()

    c_path = os.path.join(REPO, f'src/{args.overlay}/{args.overlay}.c')
    ec = os.path.join(REPO, 'src/shared/engine_core.h')

    fdef = _ght.collect_define_sigs(ec)
    fdef.update(_ght.collect_inline_sigs(c_path))
    fdecl = _ght.collect_extern_sigs([ec, c_path])
    func_canon = {}
    for a, s in fdecl.items():
        func_canon[f'func_{a:08X}'] = f'extern {s};'
    for a, s in fdef.items():
        func_canon[f'func_{a:08X}'] = f'extern {s};'
    data_canon = collect_data_decls([c_path, ec])
    canon = {**func_canon, **data_canon}

    os.makedirs(os.path.join(REPO, args.outdir), exist_ok=True)
    stub_re = re.compile(r'INCLUDE_ASM\([^,]*,\s*(func_[0-9A-Fa-f]+)\)')
    cur_stubs = set(stub_re.findall(open(c_path).read()))

    n = ext_rw = def_rw = 0
    for p in sorted(glob.glob(os.path.join(REPO, args.indir, '*.c'))):
        fn = os.path.basename(p)[:-2]
        if fn not in cur_stubs:
            continue
        txt = open(p).read()
        ext_changed = False

        def repl(m):
            nonlocal ext_changed
            line = m.group(0)
            s = sym_of(line)
            if s and s in canon:
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
            if s and s != fn and s in canon:
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

    print(f'canonical decls: {len(func_canon)} func + {len(data_canon)} data')
    print(f'drafts unified: {n}  (callee-externs rewritten in {ext_rw}, OWN def-sig rewritten in {def_rw})')


if __name__ == '__main__':
    main()
