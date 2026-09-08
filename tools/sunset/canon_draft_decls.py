#!/usr/bin/env python3
"""Canonicalize a harvest draft's extern/data declarations to the banked-consistent set.

Phase 15 / T6d (cookbook §14c). The dominant gate-failure for the call-heavy shared core is a
TU-level DECLARATION conflict: a draft declares a callee or `D_XXXX` data global with a type that
disagrees with how the *already-banked* code (the overlay .c + engine_core.h) declares the same
symbol. The draft's BODY is byte-correct (it passes `match_one`); only its declaration collides.

This rewrites each draft's `extern ...;` lines to the canonical declaration harvested from the banked
code (functions: engine_core.h DEFINE bodies / extern decls / inline defs; data: existing
`extern <type> D_XXXX...;`). Lines for genuinely-new symbols (no canonical) are kept as the draft
wrote them. The whole-binary `harvest_verify` byte-gate remains the sole arbiter (G3/P9): a
canonicalization that changes the body's semantics (e.g. an address-use forced to a scalar type) just
fails the gate and reverts — never a wrong match.

Usage:
  tools/canon_draft_decls.py --overlay ov_SC01_077 --in .run/drafts-T6-fail --out .run/drafts-T6-recanon
"""
import argparse, os, re, glob, importlib.util

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))

# load the resolver helpers from gen_harvest_targets
_spec = importlib.util.spec_from_file_location(
    'ght', os.path.join(REPO, 'tools/gen_harvest_targets.py'))
_ght = importlib.util.module_from_spec(_spec)
_spec.loader.exec_module(_ght)

# extern declaration of a DATA symbol: `extern <type> D_XXXX;` or `extern <type> D_XXXX[];`
DATA_DECL_RE = re.compile(
    r'extern\s+([A-Za-z_][\w\s\*]*?\bD_[0-9A-Fa-f]+\s*(?:\[\s*\])?)\s*;')
# any extern line in a draft (func or data), captured whole for replacement
DRAFT_EXTERN_LINE_RE = re.compile(r'^[ \t]*extern\b[^;]*;[ \t]*$', re.M)


def sym_of(decl):
    """the identifier a declaration declares (func_XXXX or D_XXXX)."""
    m = re.search(r'\b(func_[0-9A-Fa-f]+|D_[0-9A-Fa-f]+)\b', decl)
    return m.group(1) if m else None


def collect_data_decls(paths):
    """addr-keyed canonical `extern <type> D_XXXX...;` from the banked code.
    First-seen wins (the banked set is build-consistent, so all agree)."""
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


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('--overlay', default='ov_SC01_077')
    ap.add_argument('--in', dest='indir', default='.run/drafts-T6-fail')
    ap.add_argument('--out', dest='outdir', default='.run/drafts-T6-recanon')
    args = ap.parse_args()

    c_path = os.path.join(REPO, f'src/{args.overlay}/{args.overlay}.c')
    ec = os.path.join(REPO, 'src/shared/engine_core.h')

    # canonical FUNCTION sigs: defined body > inline def > extern decl
    fdef = _ght.collect_define_sigs(ec)
    fdef.update(_ght.collect_inline_sigs(c_path))
    fdecl = _ght.collect_extern_sigs([ec, c_path])
    func_canon = {}
    for a, s in fdecl.items():
        func_canon[f'func_{a:08X}'] = f'extern {s};'
    for a, s in fdef.items():           # defined wins over declared
        func_canon[f'func_{a:08X}'] = f'extern {s};'
    # canonical DATA decls
    data_canon = collect_data_decls([c_path, ec])
    canon = {**func_canon, **data_canon}

    os.makedirs(os.path.join(REPO, args.outdir), exist_ok=True)
    n_files = n_rewritten = n_unchanged = 0
    only_stub = 0
    stub_re = re.compile(r'INCLUDE_ASM\([^,]*,\s*(func_[0-9A-Fa-f]+)\)')
    cur_stubs = set(stub_re.findall(open(c_path).read()))

    for p in sorted(glob.glob(os.path.join(REPO, args.indir, '*.c'))):
        fn = os.path.basename(p)[:-2]
        if fn not in cur_stubs:        # already banked elsewhere; skip
            continue
        only_stub += 1
        txt = open(p).read()
        changed = False

        def repl(m):
            nonlocal changed
            line = m.group(0)
            s = sym_of(line)
            if s and s in canon:
                new = canon[s]
                if re.sub(r'\s+', ' ', new).strip() != re.sub(r'\s+', ' ', line).strip():
                    changed = True
                # preserve the draft's leading indent
                indent = re.match(r'^[ \t]*', line).group(0)
                return indent + new
            return line

        new_txt = DRAFT_EXTERN_LINE_RE.sub(repl, txt)
        out_p = os.path.join(REPO, args.outdir, os.path.basename(p))
        open(out_p, 'w').write(new_txt)
        n_files += 1
        if changed:
            n_rewritten += 1
        else:
            n_unchanged += 1

    print(f'canonical decls: {len(func_canon)} func + {len(data_canon)} data')
    print(f'stubbed drafts processed: {only_stub} -> wrote {n_files} '
          f'({n_rewritten} had decls rewritten, {n_unchanged} unchanged) to {args.outdir}')


if __name__ == '__main__':
    main()
