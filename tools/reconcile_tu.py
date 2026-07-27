#!/usr/bin/env python3
"""reconcile_tu.py — conform a draft's DATA declarations to what the TARGET TU can actually SEE.

THE SUCCESSOR TO reconcile_decls.py, and the reason is structural, not a typo.

    reconcile_decls asks "what does the FLEET call this symbol?"
    C asks           "what does THIS TRANSLATION UNIT declare?"

Those are different questions, and only the second one has an answer. This engine is loosely typed:
the same address is legitimately declared with incompatible types in different overlays, so a single
fleet-wide answer is **wrong for some TU by construction** — and it is worse than a silent skip,
because it hands back an ACTIVELY WRONG declaration that then collides with the very TU it was
supposed to conform to. Measured on ov_SC01_077's 12 TUs (Phase 26-A):

    the fleet oracle AGREES with the TU's own declaration ...... 2883
    the fleet oracle CONFLICTS with it (cc1 REJECTS the result) . 548     <- 16%
    the TU declares it and the fleet oracle has NO answer ....... 357

and it is live: it rewrote 60 of 196 drafts in the current batch.

WHAT THIS DOES INSTEAD
======================
  * Ask cpp what the TU actually declares (`cdecl.tu_scope` — so macro-injected `DEFINE_func_*`
    externs are visible; a raw text scan cannot see them, §8c / cookbook §51g LAW 7).
  * Ask cc1 whether the draft's declaration can coexist with it (`cdecl.compatible`, validated
    against the real gcc-2.7.2 front end on 1,485 live pairs — NOT against the C standard and NOT
    against modern gcc, which give different answers; §51g LAW 9).
  * NO visible declaration -> no conflict is possible -> LEAVE THE DRAFT ALONE. Its extern types are
    load-bearing (%lo-folding, access width, alignment all key off the declared type), and
    scope_data_externs (§8d) will demote it to block scope so it establishes no global that the TU's
    own later block-scope externs would have to agree with.
  * A visible, COMPATIBLE declaration -> nothing to do.
  * A visible, CONFLICTING declaration -> **the TU wins** (it is the environment; we are the guest).
    Rewrite the draft's decl to the TU's, and CAST AT EVERY USE so the access the draft intended is
    preserved exactly. gcc-2.7.2 folds a compile-time cast of a known symbol, so the emitted bytes
    are unchanged — and the whole-binary byte-gate (G3/P9) remains the sole arbiter either way.

WHICH TU? DERIVED, NEVER HAND-PASSED (§51g LAW 10)
==================================================
`--src-file` was an OPTIONAL flag defaulting to `src/<ov>/<ov>.c`. ov_SC01_077 has **263 open stubs
across 12 TUs and only 13 of them are in the main .c**, so 95% of drafts were being reconciled
against a translation unit that would never compile them. The INCLUDE_ASM line is self-describing;
`corpus.stubs()` reads it. Ask, don't assume.

Usage:
    tools/reconcile_tu.py --overlay ov_SC01_077 --in <drafts> --out <dir> [--src-file <tu.c>]
    from reconcile_tu import fix;  body, notes = fix(body, tu_path, fn)
"""
import argparse
import glob
import importlib.util
import os
import re
import sys

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))


def _load(mod, rel):
    spec = importlib.util.spec_from_file_location(mod, os.path.join(REPO, rel))
    m = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(m)
    return m


cdecl = _load('cdecl', 'tools/cdecl.py')
corpus = _load('corpus', 'tools/corpus.py')


def tu_for(overlay, fn, override=None):
    """The TU this draft is spliced into — DERIVED from the corpus (§51g LAW 10)."""
    if override:
        return override
    try:
        st = corpus.stubs(overlay).get(int(fn[5:], 16))
        if st:
            return os.path.join(REPO, st.path)
    except Exception:
        pass
    return os.path.join(REPO, f'src/{overlay}/{overlay}.c')


# ---- the byte-neutral access casts ---------------------------------------------------------------
def _elem(d):
    """The element/base type the DRAFT believes the symbol has."""
    return (d.base + (' *' if d.kind == 'ptr' else '')).strip()


def _cast_sub(d, tu):
    """(regex, repl) reproducing the DRAFT's intended access to the symbol under the TU's storage.
    gcc folds a compile-time cast of a known symbol, so the emitted access is unchanged.

    NOTE the fn-ptr arms. reconcile_decls' `data_access_subs` has no fn-ptr kind, so the moment its
    parser is taught to SEE `extern void (*D_x[])(void);` it would happily rewrite a call-through
    `D_x[i]()` into `((u8 *)D_x)[i]()` — a dormant transform that fixing the parser would ARM. This
    tool handles the kind natively, which is why it supersedes that one rather than patching it."""
    sym = d.name
    rx = re.compile(rf'(&?)\b{re.escape(sym)}\b(\s*\[)?')
    c_arr = tu.kind in ('array', 'fnptr_array')
    e = _elem(d)

    if d.kind == 'fnptr':                                   # draft: void (*D_x)(P)
        acc = f'(({e} (*)({", ".join(d.params or [])})){sym})'
    elif d.kind == 'fnptr_array':                           # draft: void (*D_x[])(P)
        acc = f'(({e} (**)({", ".join(d.params or [])})){"" if c_arr else "&"}{sym})'
    elif d.kind == 'array':                                 # draft: E D_x[]
        acc = f'(({e} *){"" if c_arr else "&"}{sym})'
    else:                                                   # scalar / struct / pointer
        acc = f'(*({e} *)&{sym})' if not c_arr else f'(*({e} *){sym})'
    return rx, lambda m: f'{m.group(1)}{acc}{m.group(2) or ""}'


def fix(body, tu_path, fn):
    """Conform the draft's DATA decls to the TU. Returns (new_body, notes)."""
    full = cdecl.tu_scope(tu_path)                  # CONFLICT domain: a decl BELOW still conflicts
    above = set(cdecl.tu_scope(tu_path, above=fn))  # ORDER, for cc1's no-prototype rule

    plan, notes = {}, []
    for st in cdecl.split_statements(body):
        try:
            ds = cdecl.parse(st.text)
        except cdecl.CDeclError as e:
            notes.append(f'!! UNPARSED (a coverage defect, not a no-op): {st.text[:60]} -> {e}')
            continue
        for d in ds:
            if d.is_definition or d.kind == 'func' or d.storage == 'typedef':
                continue
            tu = full.get(d.name)
            if tu is None:
                continue                            # not declared here -> no conflict is possible
            a, b = (tu, d) if d.name in above else (d, tu)
            if cdecl.compatible(a, b):
                continue                            # cc1 accepts both -> leave the draft's types
            plan[d.name] = (tu, d, st)
            notes.append(f'{d.name}: draft {d.type!r} vs TU {tu.type!r} -> TU wins + cast at use')

    if not plan:
        return body, notes

    # Group the plan by STATEMENT, not by symbol. A declaration statement can declare SEVERAL
    # symbols — `extern u16 D_80078EB2, D_8011F82A, D_8011F82C, D_80078EB4, D_8011F8C4;` — and only
    # one of them may conflict. Replacing the LINE with that one symbol's declaration silently
    # DROPS the other four, and the draft then fails with `D_8011F82A undeclared` several conflicts
    # later, pointing nowhere near the cause. Measured on func_80176218 (Phase 29 SESSION-21):
    # 5 declarators in, 1 out, 4 lost. Re-emit every declarator — the TU's version for the ones that
    # conflict, the draft's own for the rest.
    by_stmt = {}
    for _name, (_tu, _d, st) in plan.items():
        by_stmt.setdefault(st.text, set()).add(_name)

    out, done = [], set()
    dropped_check = [0, 0]                          # (declarators seen, declarators emitted)
    for line in body.split('\n'):
        hit_stmt = next((s for s in by_stmt
                         if s.split('\n')[0].strip() == line.strip() and s not in done), None)
        if hit_stmt:                                # the draft's decl line -> conform, preserving siblings
            done.add(hit_stmt)
            indent = re.match(r'^[ \t]*', line).group(0)
            planned = by_stmt[hit_stmt]
            try:
                all_ds = [d for d in cdecl.parse(hit_stmt)
                          if not (d.is_definition or d.kind == 'func' or d.storage == 'typedef')]
            except cdecl.CDeclError:
                all_ds = []
            if all_ds:
                for d in all_ds:
                    dropped_check[0] += 1
                    out.append(indent + (plan[d.name][0].declaration() if d.name in planned
                                         else d.declaration()))
                    dropped_check[1] += 1
                if len(all_ds) > 1:
                    notes.append(f'multi-declarator statement preserved: '
                                 f'{len(all_ds)} symbol(s), {len(planned)} conformed')
            else:                                   # unparseable — emit what we planned, and SAY so
                notes.append(f'!! could not re-parse a planned decl statement; emitted only the '
                             f'{len(planned)} conformed symbol(s) — siblings may be lost: '
                             f'{line.strip()[:70]}')
                for nm in sorted(planned):
                    out.append(indent + plan[nm][0].declaration())
            continue
        if re.match(r'\s*(extern|typedef)\b', line):
            out.append(line)                        # never cast inside a declaration line
            continue
        for _s, (tu, d, _st) in plan.items():       # cast every USE to the draft's intended view
            rx, rep = _cast_sub(d, tu)
            line = rx.sub(rep, line)
        out.append(line)
    return '\n'.join(out), notes


def main():
    ap = argparse.ArgumentParser(description=__doc__,
                                 formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument('--overlay', default='ov_SC01_077')
    ap.add_argument('--in', dest='indir', required=True)
    ap.add_argument('--out', dest='outdir', required=True)
    ap.add_argument('--src-file', dest='src_file', default=None,
                    help='override the derived TU (normally unnecessary — it is derived per draft)')
    ap.add_argument('--strict', action='store_true', help='exit non-zero on a coverage defect')
    a = ap.parse_args()

    override = a.src_file and os.path.join(REPO, a.src_file)
    os.makedirs(os.path.join(REPO, a.outdir), exist_ok=True)
    drafts = touched = syms = defects = 0
    for p in sorted(glob.glob(os.path.join(REPO, a.indir, '*.c'))):
        fn = os.path.basename(p)[:-2]
        new, notes = fix(open(p).read(), tu_for(a.overlay, fn, override), fn)
        open(os.path.join(REPO, a.outdir, os.path.basename(p)), 'w').write(new)
        drafts += 1
        n = sum(1 for x in notes if not x.startswith('!!'))
        defects += sum(1 for x in notes if x.startswith('!!'))
        if n:
            touched += 1
            syms += n
    print(f'drafts: {drafts}; reconciled: {touched} draft(s), {syms} data symbol(s); '
          f'coverage defects: {defects}')
    if a.strict and defects:
        sys.exit(1)


if __name__ == '__main__':
    main()
