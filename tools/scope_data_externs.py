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
import re
import sys

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
    catalogued in §40/§8d; caught because the h_seq re-sweep banked 0/780)."""
    sig = re.search(rf'^[^\n]*\b{re.escape(func)}\s*\(', body, re.M)
    if not sig:
        return None
    i = body.find('{', sig.end())
    if i < 0:
        return None
    j = body.find('\n', i)
    return (j + 1) if j >= 0 else (i + 1)


def fix(body, tu_text, insert_pos, func):
    """Demote the body's file-scope DATA externs that the TU does not already declare at file scope
    above `insert_pos`. Returns (new_body, [moved symbols]). A no-op (body unchanged) when nothing
    qualifies, when the body declares no data externs, or when the opening brace can't be located."""
    above = _file_scope_data_syms(tu_text[:insert_pos])

    demote = []                       # (line_text, sym)
    dropped = []                      # syms the TU ALREADY declares above us — redundant, see below
    keep_lines = []
    for ln in body.split('\n'):
        # BLOCK-SCOPE TOO, not just col-0 (Phase 29 SESSION-22). §8d demotes these externs on the way
        # in, so by the time a sibling draft is STAGED they are already indented — and a col-0-only
        # scan therefore saw nothing to do on exactly the drafts that needed it. C still requires a
        # block-scope `extern` to agree with a file-scope declaration in scope, so a redundant
        # redeclaration conflicts at ANY scope; the drop below must reach both.
        if ANY_EXTERN_RE.match(ln) and not FILE_EXTERN_RE.match(ln):
            d = DATA_SYM_RE.search(ln)
            if d and d.group(0) in above:
                dropped.append(d.group(0))
                continue
            keep_lines.append(ln)
            continue
        if FILE_EXTERN_RE.match(ln):                  # col-0 extern (match => anchored at col 0)
            d = DATA_SYM_RE.search(ln)
            if d:
                if d.group(0) not in above:
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
    if not demote and not dropped:
        return body, []

    stripped = '\n'.join(keep_lines)
    if not demote:                                    # drops only — no block to place
        return stripped, dropped
    at = _body_open_brace(stripped, func)
    if at is None:                                    # can't place them safely -> leave the body alone
        return body, []
    block = ''.join(f'    {ln}\n' for ln, _ in demote)
    return stripped[:at] + '\n' + block + stripped[at:], [s for _, s in demote] + dropped


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
