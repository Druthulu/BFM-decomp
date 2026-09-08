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
  * A visible declaration that is BELOW the splice point while the draft's is at BLOCK SCOPE ->
    cc1 ACCEPTS that (pedwarn "type mismatch with previous external decl"), so there is nothing to
    fix and everything to lose: the TU's declaration names the TU's TYPE, and a type declared below
    the splice point is not in scope AT it, so "conforming" replaces a construct cc1 compiles with
    one it cannot parse. LEAVE IT ALONE (R43). Measured on resident:func_800D06E8, P31 S75.
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
        addr = int(fn[5:], 16)                    # a curated (non-func_ADDR) name has no address here
    except ValueError:
        return os.path.join(REPO, f'src/{overlay}/{overlay}.c')
    # CorpusError PROPAGATES (R32/R35, P30 S1e) — see the identical note in cast_call_sites.tu_for.
    # A swallow here silently reconciles the draft against the DEFAULT `<ov>.c` instead of the jr/-O0
    # split TU that actually compiles it, which is a §51g LAW 10 violation dressed up as a gate refusal.
    st = corpus.stubs(overlay).get(addr)
    if st:
        return os.path.join(REPO, st.path)
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
    tool handles the kind natively, which is why it supersedes that one rather than patching it.

    TWO FORMS, and the `&` prefix SELECTS between them (P31 S75). The leading `&` used to be
    captured and re-emitted VERBATIM in front of the value form, which yields `&` applied to a cast
    — and for three of the four arms that is not merely ugly, it is a hard error. Measured on the
    real cc1:

        &(*(E *)&sym)      scalar/struct/ptr  ACCEPT   (legal; the fold is cosmetic)
        &((E *)&sym)       array              REJECT   `invalid lvalue in unary '&'`
        &((E (*)(P))sym)   fnptr              REJECT   same
        &((E (**)(P))&sym) fnptr_array        REJECT   same

    So `&sym` now emits a POINTER form built from the symbol's address directly, which is valid for
    every arm, is the same link-time constant, and keeps the drafted view's pointee type.

    ⚠️ ONLY WHEN NO SUBSCRIPT FOLLOWS. `&sym[i]` is not `&` applied to the symbol at all — `[]`
    binds tighter, so it is the address of ELEMENT i, and `&((E *)&sym)[i]` is both legal and
    correct. Folding it to a pointer form silently changes what the expression MEANS. Caught by the
    R39 negative control over the stored-draft corpus (`ov_SC02_005:func_8018DFC4`, whose
    `(s32)&((Pair8 *)D_801E4998)[idx]` would have become `(s32)((Pair8 (*)[])D_801E4998)[idx]`) —
    the trailing-`[` case is exactly the one the old code got RIGHT."""
    sym = d.name
    # `(?<![.\w])(?<!->)` — a MEMBER ACCESS is not this symbol. Without it, a struct field that
    # happens to share a global's name is rewritten at every use: `p->code` became
    # `p->(*(u32 *)&code)`, which is not even valid C. Latent since the tool was written and only
    # reachable once block-scope descent started finding such names (Phase 29 SESSION-22).
    rx = re.compile(rf'(&?)(?<![.\w])(?<!->){re.escape(sym)}\b(\s*\[)?')
    c_arr = tu.kind in ('array', 'fnptr_array')
    e = _elem(d)
    p = ", ".join(d.params or [])
    at = sym if c_arr else f'&{sym}'                        # the symbol's ADDRESS under TU storage

    if d.kind == 'fnptr':                                   # draft: void (*D_x)(P)
        val = f'(({e} (*)({p})){sym})'
        ptr = f'(({e} (**)({p})){at})'
    elif d.kind == 'fnptr_array':                           # draft: void (*D_x[])(P)
        val = f'(({e} (**)({p})){at})'
        ptr = f'(({e} (***)({p})){at})'
    elif d.kind == 'array':                                 # draft: E D_x[]
        val = f'(({e} *){at})'
        ptr = f'(({e} (*)[]){at})'
    else:                                                   # scalar / struct / pointer
        val = f'(*({e} *){at})'
        ptr = f'(({e} *){at})'
    # group(1) = a leading `&`, group(2) = a trailing `[`. The pointer form is right ONLY for a bare
    # `&sym`; with a subscript the `&` belongs to the element, so re-emit it in front of the value
    # form exactly as before (see the docstring's ⚠️).
    def rep(m):
        if m.group(1) and not m.group(2):
            return ptr                                  # `&sym` -> pointer form, `&` consumed
        return f'{m.group(1)}{val}{m.group(2) or ""}'   # `sym`, `sym[i]`, `&sym[i]` -> unchanged shape
    return rx, rep


def _draft_statements(body):
    """Every declaration-bearing statement in the draft, at FILE scope AND at BLOCK scope, as
    (Stmt-with-ABSOLUTE-spans, is_inner).

    WHY (Phase 29 SESSION-22, byte-witnessed on func_80175AB8). `split_statements` is depth-0 BY
    DESIGN, so for a draft whose body is one function definition it returns exactly ONE statement —
    the definition — and every declaration inside it is invisible. That is precisely where the data
    externs live: §8d (`scope_data_externs`) DEMOTES them to block scope on purpose, because a
    block-scope extern declares no global for the TU's own later decls to collide with.

    But C still requires a block-scope `extern` to be compatible with a file-scope declaration of the
    same identifier that is in scope — so the conflict is real, and this tool was structurally blind
    to it: it reported `reconciled: 0 draft(s), 0 data symbol(s); coverage defects: 0` for a draft
    cc1 then rejected with `conflicting types for D_8011F7BC`. A silent skip that reads exactly like
    "nothing to do" (R32).

    One level of descent is enough and is deliberate: the externs sit at the top of the function
    body, not inside nested blocks, and recursing further would start parsing arbitrary code."""
    out = []
    for st in cdecl.split_statements(body):
        out.append((st, False))
        m = re.search(r'\{', cdecl._mask(st.text))
        if not m:
            continue
        # DESCEND ONLY INTO A FUNCTION BODY. Descending into ANY `{` also enters struct/union/enum
        # definitions, whose MEMBERS then parse as declarations and get "conformed" against the TU —
        # byte-witnessed while writing this: a member `u32 code;` was rewritten to the TU's
        # declaration of `code` (`typedef void (*code)(unsigned short*);`) INSIDE the struct, and the
        # member ACCESS `p->code` became `p->(*(u32 *)&code)`. A function definition is distinguished
        # by a parameter list before the brace and by not being a tag/typedef definition.
        head = st.text[:m.start()]
        if re.match(r'\s*(typedef|struct|union|enum)\b', head) or ')' not in head:
            continue
        off = st.start + m.end()                    # first byte INSIDE the body
        inner_txt = body[off:st.end]
        for s2 in cdecl.split_statements(inner_txt):
            out.append((cdecl.Stmt(s2.text, off + s2.start, off + s2.end), True))
    return out


def fix(body, tu_path, fn):
    """Conform the draft's DATA decls to the TU. Returns (new_body, notes)."""
    # CONFLICT domain. A decl BELOW the splice point still conflicts — AT FILE SCOPE. At BLOCK
    # scope cc1 accepts it with a pedwarn, which is why `above` is consulted again in the loop
    # rather than only for argument order (P31 S75; the four-probe measurement is quoted there).
    full = cdecl.tu_scope(tu_path)
    above = set(cdecl.tu_scope(tu_path, above=fn))  # ORDER, for cc1's no-prototype rule

    plan, notes = {}, []
    for st, inner in _draft_statements(body):
        try:
            ds = cdecl.parse(st.text)
        except cdecl.CDeclError as e:
            if inner:
                continue        # ordinary CODE inside a function body — not a declaration, not a defect
            notes.append(f'!! UNPARSED (a coverage defect, not a no-op): {st.text[:60]} -> {e}')
            continue
        for d in ds:
            if d.is_definition or d.kind == 'func' or d.storage == 'typedef':
                continue
            # BLOCK SCOPE: only a real `extern` DECLARATION counts (Phase 29 SESSION-22, second cut).
            # Descending into function bodies also feeds ordinary STATEMENTS to cdecl.parse, and some
            # of them parse without raising into a declarator with an EMPTY base type and the
            # statement's symbol as its name. That fake entry then overwrote the genuine plan row for
            # the same symbol (`plan[d.name] = …`), so the span rewrite landed on a statement instead
            # of the declaration — and the R32 completion check still passed, because the conformed
            # text it looks for did appear somewhere. Byte-witnessed: `D_80126B5C` planned twice
            # ("draft 's32'" and "draft ''"), output unchanged, gate PLUMBING.
            if inner and not (st.text.lstrip().startswith('extern') and d.base.strip()):
                continue
            tu = full.get(d.name)
            if tu is None:
                continue                            # not declared here -> no conflict is possible
            # BLOCK SCOPE + TU DECLARATION BELOW -> cc1 ACCEPTS. Do not touch it. (P31 S75)
            #
            # This module's own premise — "a decl BELOW still conflicts" (see `full` above) — is
            # TRUE at file scope and FALSE at block scope, and the difference is not cosmetic. The
            # four-probe measurement against the real cc1:
            #
            #   block-scope extern, TU decl BELOW  ->  ACCEPT  (warning: "type mismatch with
            #                                          previous external decl" — a pedwarn, not an error)
            #   block-scope extern, TU decl ABOVE  ->  REJECT  `conflicting types`
            #   file-scope  extern, TU decl BELOW  ->  REJECT  `conflicting types`   <- the real job
            #   the conformed output this rung emitted -> REJECT `syntax error before 'D_x'`
            #
            # That last line is why this is a refusal and not an optimisation. The TU's declaration
            # names the TU's TYPE, and a type declared BELOW the splice point is not in scope AT it:
            # conforming to it substitutes a construct cc1 accepts for one it cannot even parse.
            # Byte-witnessed on resident:func_800D06E8 (344 ins, match_one closeness 0) — a
            # deliberate block-scoped `extern Blk80078E78 D_80078E78;` rewritten to
            # `extern Struct80078E78 D_80078E78;` whose typedef is declared 388 lines LOWER.
            #
            # The block-scope extern is not an accident to be cleaned up, either: it is what THIS
            # LADDER'S OWN `scope_demote_drafts` (§8d) rung produces on purpose, and three already-
            # banked functions in that TU use it. R43 — refuse the class, name it, leave the draft.
            if inner and d.name not in above:
                notes.append(f'-- {d.name}: block-scope extern vs a TU decl BELOW the splice point '
                             f'-> cc1 accepts (pedwarn only); LEFT ALONE (conforming it would name '
                             f'a type that is not yet in scope)')
                continue
            a, b = (tu, d) if d.name in above else (d, tu)
            if cdecl.compatible(a, b):
                continue                            # cc1 accepts both -> leave the draft's types
            plan[d.name] = (tu, d, st)
            notes.append(f'{d.name}: draft {d.type!r} vs TU {tu.type!r} -> TU wins + cast at use')

    if not plan:
        return body, notes

    # Locate each planned declaration by its SOURCE SPAN — never by re-finding its text.
    # `split_statements` preserves spans precisely because drafts get rewritten, and the text it
    # hands back is comment-STRIPPED: `extern u8  D_80078E78;` for a line that actually reads
    # `extern u8  D_80078E78;   /* cur base ($s5) */`. Matching statement-text against line-text
    # therefore misses EVERY commented declaration — and it misses it in the worst possible way,
    # SILENTLY: the uses are still cast to the draft's intended view while the declaration stays
    # unconformed, so cc1 reports `conflicting types` at the very decl the tool believed it had
    # just fixed, and the tool reports success. (Measured on func_80176218, Phase 29 SESSION-22.)
    #
    # Group the plan by STATEMENT, not by symbol. A declaration statement can declare SEVERAL
    # symbols — `extern u16 D_80078EB2, D_8011F82A, D_8011F82C, D_80078EB4, D_8011F8C4;` — and only
    # one of them may conflict. Replacing the statement with that one symbol's declaration silently
    # DROPS the other four, and the draft then fails with `D_8011F82A undeclared` several conflicts
    # later, pointing nowhere near the cause. Measured on func_80176218 (Phase 29 SESSION-21):
    # 5 declarators in, 1 out, 4 lost. Re-emit every declarator — the TU's version for the ones that
    # conflict, the draft's own for the rest.
    by_span = {}
    for _name, (_tu, _d, st) in plan.items():
        by_span.setdefault((st.start, st.end), set()).add(_name)

    pieces, pos = [], 0
    seen = emitted = 0                              # declarators IN vs OUT — asserted below (R32)
    for (a, b) in sorted(by_span):
        planned, stmt = by_span[(a, b)], body[a:b]
        ls = body.rfind('\n', 0, a) + 1             # this statement's own indentation
        indent = body[ls:a] if not body[ls:a].strip() else ''
        try:
            all_ds = [d for d in cdecl.parse(stmt)
                      if not (d.is_definition or d.kind == 'func' or d.storage == 'typedef')]
        except cdecl.CDeclError:
            all_ds = []
        if all_ds:
            decls = [(plan[d.name][0] if d.name in planned else d).declaration() for d in all_ds]
            seen += len(all_ds)
        else:                                       # unparseable — emit what we planned, and SAY so
            notes.append(f'!! could not re-parse a planned decl statement; emitting only the '
                         f'{len(planned)} conformed symbol(s) — siblings may be lost: {stmt[:70]}')
            decls = [plan[nm][0].declaration() for nm in sorted(planned)]
            seen += len(planned)
        emitted += len(decls)
        if len(decls) > 1:
            notes.append(f'-- multi-declarator statement preserved: {len(decls)} symbol(s), '
                         f'{len(planned)} conformed')
        pieces.append(body[pos:a])
        pieces.append(('\n' + indent).join(decls))
        pos = b
    pieces.append(body[pos:])
    conformed = ''.join(pieces)

    # R32 — ASSERT THE CONFORM LANDED. The bug this replaced was not a crash but a reported success,
    # so the counter that would have caught it has to be COMPARED, not merely incremented.
    if emitted < seen:
        notes.append(f'!! dropped {seen - emitted} declarator(s) while conforming')
    for nm, (tu, _d, _st) in plan.items():
        if tu.declaration() not in conformed:
            notes.append(f'!! {nm}: planned conform to {tu.type!r} did NOT land in the output '
                         f'(its uses would be cast against a declaration that was never rewritten)')

    # Cast every USE to the draft's intended view — but ONLY in CODE.
    #
    # This pass used to run `rx.sub` over every non-declaration LINE, which is every line of the
    # draft's doc comment too. Byte-witnessed on resident:func_800D06E8 (P31 S75): a 40-line header
    # comment explaining the block-scope idiom had `D_80078E78` rewritten to
    # `(*(Blk80078E78 *)&D_80078E78)` in its PROSE, eight times, including inside a quoted cc1
    # diagnostic. Harmless to the bytes and corrosive to the only artifact that explains WHY the
    # function is written the way it is — and it made a mechanical rewrite look like an authored one.
    #
    # `cdecl._mask` blanks comments and string/char literals LENGTH-PRESERVINGLY, so an offset into
    # the mask is an offset into the original: match on the mask, splice into the source (R33 — the
    # masker already exists and is the same one `split_statements` trusts for brace counting).
    masked = cdecl._mask(conformed)
    edits = []
    for _s, (tu, d, _st) in plan.items():
        rx, rep = _cast_sub(d, tu)
        for m in rx.finditer(masked):
            ls = conformed.rfind('\n', 0, m.start()) + 1
            le = conformed.find('\n', m.start())
            if re.match(r'\s*(extern|typedef)\b', conformed[ls:le if le >= 0 else len(conformed)]):
                continue                            # never cast inside a declaration line
            edits.append((m.start(), m.end(), rep(m)))
    pieces, pos = [], 0
    for a, b, text in sorted(edits):
        if a < pos:
            notes.append(f'!! overlapping cast rewrites at {a}; the later one was skipped')
            continue
        pieces.append(conformed[pos:a]); pieces.append(text); pos = b
    pieces.append(conformed[pos:])
    return ''.join(pieces), notes


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
        n = sum(1 for x in notes if not x.startswith(('!!', '--')))   # '--' = informational, not a symbol
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
