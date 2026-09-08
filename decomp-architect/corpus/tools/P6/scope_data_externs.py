#!/usr/bin/env python3
"""scope_data_externs.py — place a templated body's DATA externs at the scope the target TU can accept
(Phase 26, cookbook §8d). The missing recovery step that unblocks the heavy-jr ×N family sweeps.

THE BUG IT FIXES (byte-proven on func_8015AE2C -> ov_SC01_000)
-------------------------------------------------------------
`family_remap.gather_externs` carries the exemplar's decls for every symbol the body references and
prepends them at FILE scope (family_remap.py, remap_hseq). For a per-location DATA symbol that the
target TU declares only at BLOCK scope — inside its OWN later functions, loosely typed — that carried
file-scope decl ESTABLISHES A GLOBAL DECLARATION the TU never had, and every later block-scope `extern`
of that symbol must now agree with it. They don't (the engine is loosely typed), so gcc-2.7.2 rejects
the TU. The asymmetry, both halves byte-proven by the whole-binary gate:

    BLOCK(int) -> BLOCK(struct Ent *) -> FILE(void *) ...   builds [ OK ]   (the region, stub state)
    FILE(void *) -> BLOCK(int) -> ...                       conflicting types for `D_801812A4'  (ERROR)

Example: ov_SC01_000's `D_801812A4` is a fn-ptr dispatch table declared FOUR incompatible ways in one
region — `(int)` and `(struct Ent_8015CD20 *)` at block scope inside func_8015C128 / func_8015CD20, then
`(void *)` at file scope. That compiles. Prepend the body's `extern void (*D_801812A4[])(void *);` above
them and it does not.

THE FIX
-------
Emit the carried extern at BLOCK scope (inside the function body) whenever the TU has NO file-scope decl
of that symbol above the insertion point. Then it declares no global, nothing below it can conflict, and
the TU's own decl environment is preserved exactly. This is the §8c principle ("splitting a TU means
rebuilding its declaration environment") applied to templating: a carried decl must not CHANGE the
environment — and it restores fidelity, because the original source declares these symbols at block
scope in precisely the same way (m2c/Ghidra emit per-function externs there).

BYTE-NEUTRAL: an `extern` declaration emits no code, and moving it changes neither the symbol nor the
declared type, so every access keeps its opcode. Only name lookup moves. The whole-binary byte-gate
(G3/P9) remains the sole arbiter — a wrong placement just fails the gate and the sibling reverts.

NEVER WORSE THAN THE STATUS QUO: if the symbol DOES have a file-scope decl above, we leave the line
alone (identical spelling = a legal duplicate; a differing spelling is the §41 reconcile class and is
an error at file scope either way, so demoting could not have saved it — the `reconciled` stage is the
fallback there).

SCOPE: `D_` data externs only. Function externs stay at file scope so `cast_call_sites` /
`canon_sig_reconcile` (which parse file-scope decls) keep working on them; gcc tolerates mismatched
function decls with a pedwarn, so they are not the failing class.

Usage (library — the sweep calls fix() directly; ×N per family, so no subprocess):
    from scope_data_externs import fix
    body, moved = fix(body, tu_text, insert_pos, "func_8015AE2C")

CLI (diagnostics):
    tools/scope_data_externs.py --body .run/_repro_body.c --tu src/ov_SC01_000/ov_SC01_000_jr_8015AE2C.c \
        --func func_8015AE2C [--out fixed.c]
"""
import argparse
import os
import re
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import cdecl                                                  # noqa: E402 — the ONE masking oracle (§134/R33)

# a col-0 (file-scope) `extern ...;` on one line. Leading whitespace => block scope, which is what we
# emit and never need to re-place.
FILE_EXTERN_RE = re.compile(r'^extern\b[^;{}\n]*;', re.M)
DATA_SYM_RE = re.compile(r'\bD_[0-9A-Fa-f]{6,8}\b')
# any `extern ...;` on one line, at ANY indentation (file OR block scope)
ANY_EXTERN_RE = re.compile(r'^\s*extern\b[^;{}\n]*;')


def _file_scope_data_syms(text):
    """Every D_ symbol declared by a col-0 `extern` in `text`. The symbol a decl DECLARES is its first
    D_ token — true for both `extern u8 D_x[];` and the fn-ptr-array form `extern void (*D_x[])(void *);`
    (the form reconcile_decls' regex cannot parse, which is why that tool silently skipped this class)."""
    out = set()
    for m in FILE_EXTERN_RE.finditer(text):
        d = DATA_SYM_RE.search(m.group(0))
        if d:
            out.add(d.group(0))
    return out


def _body_open_brace(body, func):
    r"""Index just past the `{` that opens `func`'s body — i.e. where block-scope decls go. Scans forward
    from the signature to the first `{` at depth 0 of the *statement* (so it handles the ANSI form with
    the brace on the signature line, the ANSI form with the brace on its own line, AND the K&R form whose
    param decls sit between the signature and the `{`). The first cut of this used `^\s*\{\s*$` — own-line
    braces only — and silently no-op'd on every ANSI draft (the same silent-skip disease as the four
    catalogued in §40/§8d; caught because the h_seq re-sweep banked 0/780).

    BOTH SCANS RUN ON `cdecl._mask`ed TEXT (P30 S48, byte-witnessed). A crack agent's draft opens with
    a header comment that NAMES the function and quotes C at it:

        /* func_801EE8E0 (ov_MAIN_012 / jr_801789AC) — 188 ins, byte-exact vs …
         *  3) The `do { } while (0)` around the loop-1 call is a REGISTER-ALLOCATION lever …

    Unmasked, `sig` matched the COMMENT's first line and `find('{')` then found the comment's
    `do {`, so every carried `extern` was spliced INTO THE COMMENT — silently commented out. The
    gate reported `'D_8011511A' undeclared` and the sweep classified it CC1-FAIL, i.e. it read as a
    property of the SIBLING (all 4 members of the family failed identically) when it was a property
    of the EXEMPLAR'S PROSE. Every richly-commented agent draft is a carrier; the trigger is any
    brace inside the header comment. Same §134 class as `_mask_cpp_directives` and the wrapped-decl
    scans — mask first, then index the ORIGINAL by the masked offsets."""
    masked = cdecl._mask(body)
    if len(masked) != len(body):          # R32: the length invariant is what makes offsets portable
        return None                       # refuse rather than mis-place a decl into live code
    sig = re.search(rf'^[^\n]*\b{re.escape(func)}\s*\(', masked, re.M)
    if not sig:
        return None
    i = masked.find('{', sig.end())
    if i < 0:
        return None
    j = body.find('\n', i)
    return (j + 1) if j >= 0 else (i + 1)


_ASM_LABEL_RE = re.compile(r'__asm__\s*\(\s*"([^"]+)"\s*\)')


def _norm_ws(s):
    return re.sub(r'\s+', ' ', s.strip())


def _alias_name(sym, func):
    """Per-FUNCTION alias, never a bare `aD<sym>` (P30 S47-F4, byte-witnessed).

    A bare alias re-creates the very collision it exists to remove, one level down: two drafts
    spliced into one TU that both alias `D_800B9A02` — each keeping its own type, which is the whole
    point — then declare `aD800B9A02` twice with different types. Measured: 9 fresh
    `conflicting types for aD800B9A02` failures caused by this fix's first cut. The group-level
    path in family_sweep suffixed from the start; this one did not, and that asymmetry is the bug."""
    return f'aD{sym[2:]}_{func[5:] if func.startswith("func_") else func}'


def _decl_type_text(line, sym):
    """The declared TYPE of `sym` in one `extern` line — everything between `extern` and the
    declarator, plus any array suffix. None if the line does not declare it."""
    m = re.search(rf'^\s*extern\s+(.*?)\b{re.escape(sym)}\b\s*(\[[^\]]*\])?', line)
    return (m.group(1) + (m.group(2) or '')) if m else None


def _file_scope_data_types(tu_text):
    """{sym -> declared type text} for every file-scope data extern ANYWHERE in the TU.

    `_file_scope_data_syms` answers "declared ABOVE the insertion point", which is the right
    question for the drop/demote decision and the WRONG one for conflict detection: a file-scope
    declaration BELOW the body must still agree with a block-scope extern inside it."""
    out = {}
    for ln in FILE_EXTERN_RE.findall(tu_text):
        d = DATA_SYM_RE.search(ln)
        if d:
            out.setdefault(d.group(0), _decl_type_text(ln, d.group(0)))
    return out


def is_asm_alias(ln):
    """True for a §37/§84 ASM-LABEL ALIAS: `extern T ident…  __asm__("SYM");` with ident != SYM.

    THE DROP BELOW MUST NOT REACH THESE (Phase 30 S47, byte-witnessed on func_80132018).
    The "TU already declares it above us -> drop ours" rule keys on the SYMBOL, but an alias binds a
    DIFFERENT C IDENTIFIER to that symbol. The TU's `extern void (*D_801851BC[])(void);` declares
    `D_801851BC`; it does NOT declare `tbl_D_80187044`. Dropping the alias therefore leaves the body
    referencing an undeclared name — `tbl_D_80187044' undeclared` — which cc1 reports with no
    `error:` prefix, so the sweep classified all 132 siblings as CC1-FAIL(no-diagnostic).

    The bitter part: the alias exists PRECISELY BECAUSE the TU declares that symbol with a
    conflicting type (a `void (*[])(void)` dispatch table vs this function's 20-byte-stride view).
    So the drop rule fired on exactly the declarations written to survive it, and undid the
    workaround. An alias can never collide with the TU's declaration — the identifiers differ — so
    it is demoted into the body like any other, never dropped."""
    m = _ASM_LABEL_RE.search(ln)
    if not m:
        return False
    ids = re.findall(r'[A-Za-z_]\w*', ln[:m.start()])
    return bool(ids) and ids[-1] != m.group(1)


def fix(body, tu_text, insert_pos, func, tu_types=None):
    """Demote the body's file-scope DATA externs that the TU does not already declare at file scope
    above `insert_pos`. Returns (new_body, [moved symbols]). A no-op (body unchanged) when nothing
    qualifies, when the body declares no data externs, or when the opening brace can't be located."""
    above = _file_scope_data_syms(tu_text[:insert_pos])

    # PREFER A CPP-DERIVED MAP (P30 S47-F4). A text scan cannot see a MACRO-INJECTED declaration —
    # `extern Vec8 D_80114F24;` lives inside a DEFINE_func_* macro in engine_core.h, and the overlay
    # .c holds only `DEFINE_func_XXXX()`. That declaration is nonetheless a genuine file-scope decl
    # of every TU invoking the macro, and it is what the draft collides with. Callers that can name
    # the TU path pass `cdecl.tu_scope(path)`-derived types; the text scan stays as the fallback.
    tu_types = tu_types if tu_types is not None else _file_scope_data_types(tu_text)
    demote = []                       # (line_text, sym)
    dropped = []                      # syms the TU ALREADY declares above us — redundant, see below
    keep_lines = []
    aliased = []                      # (sym, alias) — renamed at the end, both scope paths
    for ln in body.split('\n'):
        # BLOCK-SCOPE TOO, not just col-0 (Phase 29 SESSION-22). §8d demotes these externs on the way
        # in, so by the time a sibling draft is STAGED they are already indented — and a col-0-only
        # scan therefore saw nothing to do on exactly the drafts that needed it. C still requires a
        # block-scope `extern` to agree with a file-scope declaration in scope, so a redundant
        # redeclaration conflicts at ANY scope; the drop below must reach both.
        if ANY_EXTERN_RE.match(ln) and not FILE_EXTERN_RE.match(ln):
            d = DATA_SYM_RE.search(ln)
            if d and d.group(0) in above and not is_asm_alias(ln):
                dropped.append(d.group(0))
                continue
            # THE ALIAS MUST REACH THIS BRANCH TOO (P30 S47). A staged draft's externs are ALREADY
            # indented (see the note above), so they arrive here, not in the col-0 demote path —
            # and a first cut that aliased only demoted lines fired on 1 member out of 44.
            if d and not is_asm_alias(ln):
                _mine, _theirs = _decl_type_text(ln, d.group(0)), tu_types.get(d.group(0))
                if _mine and _theirs and _norm_ws(_mine) != _norm_ws(_theirs):
                    _al = _alias_name(d.group(0), func)
                    ln = (re.sub(rf'\b{re.escape(d.group(0))}\b', _al, ln, count=1)
                          .rstrip().rstrip(';') + f' __asm__("{d.group(0)}");')
                    aliased.append((d.group(0), _al))
            keep_lines.append(ln)
            continue
        if FILE_EXTERN_RE.match(ln):                  # col-0 extern (match => anchored at col 0)
            d = DATA_SYM_RE.search(ln)
            if d:
                # An ASM-LABEL ALIAS is demoted, never dropped: its C identifier is not the symbol,
                # so the TU's declaration does not cover it (see is_asm_alias).
                if d.group(0) not in above or is_asm_alias(ln):
                    demote.append((ln, d.group(0)))
                    continue                          # drop from the file-scope preamble
                # THE TU ALREADY DECLARES IT ABOVE US -> DROP OURS ENTIRELY (Phase 29 SESSION-22).
                # Keeping it was the SC07-quartet blocker: `conflicting types for D_800AF634` in
                # ov_SC07_006/007/010/011, which is a type-IDENTITY collision no type-STRING compare
                # can see. Both sides read `S_AF634 []` — but the templated body carries its OWN
                # block-scope `typedef struct {…} S_AF634;` while the TU's declaration comes from a
                # MACRO-INJECTED one (§8c), so the two `S_AF634`s are DISTINCT TYPES with one name
                # and cc1 rejects the redeclaration. (This is also why `cdecl.compatible` cannot
                # catch it and correctly answers "compatible".)
                #
                # A redeclaration we do not emit cannot collide — with anything, identity or type —
                # and the TU's own declaration is in scope and authoritative for the body. Strictly
                # better than the alternative, which was a hard compile error; the whole-binary
                # byte-gate remains the arbiter if the TU's type implies a different access.
                dropped.append(d.group(0))
                continue
        keep_lines.append(ln)
    if not demote and not dropped and not aliased:
        return body, []

    def _rename(txt):
        """Point every USE at the alias; never touch the asm label (it names the real symbol)."""
        for _s, _a in aliased:
            txt = re.sub(rf'\b{re.escape(_s)}\b', _a, txt)
            txt = txt.replace(f'__asm__("{_a}")', f'__asm__("{_s}")')
        return txt

    stripped = '\n'.join(keep_lines)
    if not demote:                                    # drops only — no block to place
        return _rename(stripped), dropped
    at = _body_open_brace(stripped, func)
    if at is None:                                    # can't place them safely -> leave the body alone
        return body, []

    # AUTO-ALIAS A DEMOTED EXTERN THE TU DECLARES WITH A DIFFERENT TYPE (P30 S47).
    # Demoting to block scope does NOT avoid a conflict: C requires a block-scope `extern` to agree
    # with any file-scope declaration of the same object in the TU, wherever it sits. And for DATA
    # the type is not cosmetic — it drives the load: `s16` vs `u16` is `lh` vs `lhu`. The fleet
    # genuinely reads one address at several widths (§16 loose typing): D_80078EB4 is `s16` at 2,409
    # sites and `u16` at 1,341, D_800AE620 is `Blk20`/`s32`/`Mat32`. Canonicalising would rewrite
    # thousands of BANKED sites' codegen, so the answer is not one type — it is one type PER VIEW.
    # That is the §37 asm-label alias, and the fleet already hand-writes it for exactly this symbol:
    #     extern Mtx8_8017C910_8017C910 aD800AE620 __asm__("D_800AE620");   (9 sites)
    # Emitting it automatically keeps the draft's own type — byte-truth for THIS body — while the
    # private C name makes a collision impossible. Codegen is unchanged: the asm label fixes the
    # emitted symbol, so the same load reaches the same address.
    # Scoped deliberately: only fires where the TU actually declares the symbol with a DIFFERENT
    # type text, so a member that never had a conflict is untouched.
    block_lines = []
    for ln, sym in demote:
        mine, theirs = _decl_type_text(ln, sym), tu_types.get(sym)
        if mine and theirs and _norm_ws(mine) != _norm_ws(theirs):
            alias = _alias_name(sym, func)
            block_lines.append(re.sub(rf'\b{re.escape(sym)}\b', alias, ln, count=1)
                               .rstrip().rstrip(';') + f' __asm__("{sym}");')
            aliased.append((sym, alias))
        else:
            block_lines.append(ln)
    block = ''.join(f'    {b}\n' for b in block_lines)
    return _rename(stripped[:at] + '\n' + block + stripped[at:]), \
        [s for _, s in demote] + dropped


def main():
    ap = argparse.ArgumentParser(description=__doc__,
                                 formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument('--body', required=True, help='the remapped body (file-scope externs prepended)')
    ap.add_argument('--tu', required=True, help='the target TU (.c) the body is spliced into')
    ap.add_argument('--func', required=True)
    ap.add_argument('--at', type=int, default=None,
                    help='char offset of the insertion point (default: the INCLUDE_ASM stub for --func)')
    ap.add_argument('--out')
    a = ap.parse_args()

    body, tu = open(a.body).read(), open(a.tu).read()
    pos = a.at
    if pos is None:
        m = re.search(rf'INCLUDE_ASM\("[^"]*",\s*{re.escape(a.func)}\);', tu)
        if not m:
            sys.exit(f'no INCLUDE_ASM stub for {a.func} in {a.tu} (pass --at)')
        pos = m.start()

    new, moved = fix(body, tu, pos, a.func)
    print(f'file-scope data syms above the insertion point: {len(_file_scope_data_syms(tu[:pos]))}')
    print(f'demoted to block scope: {len(moved)}  {moved}')
    if a.out:
        open(a.out, 'w').write(new)
        print(f'wrote {a.out}')


if __name__ == '__main__':
    main()
