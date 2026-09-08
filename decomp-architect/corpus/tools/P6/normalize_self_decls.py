#!/usr/bin/env python3
"""normalize_self_decls.py — the SAME-FUNCTION decl normalize (the third §17a-1 direction).

THE GAP (Phase-29, byte-proven on func_801670E4 ×137).
`family_sweep --hseq` templates a banked function F's DEFINITION into each sibling overlay's TU.
But that sibling TU's OWN already-banked code may carry a *divergent block-scope declaration of F*
— left there when THAT overlay's caller of F was matched, in a different C form than the exemplar's
caller used. Byte-proof (func_801670E4, sibling ov_SC01_004, ov_SC01_004_jr_8015AE2C.c):

    5031  INCLUDE_ASM(..., func_801670E4);                                  <- F's stub -> the def lands here
    5076      extern void func_801670E4(struct Entity_80167540 *, s32, s32, s32);   <- a caller's block-scope decl
    5098      func_801670E4(((struct Entity_80167540 *)arg0), 0, 0, 0);            <- the bare call

F's canonical/def is `s32 func_801670E4(s32,s32,s32,s32)` (engine_core.h). Splice the def in and the
block-scope `void func_801670E4(struct*, ...)` at 5076 CONFLICTS with it — a HARD `conflicting types`,
not a byte miss (it also cascades against the canonical decl the `DEFINE_func_*` macro injects at file
scope). The EXEMPLAR (ov_SC01_077) never hit this: ITS copy of that caller used the fn-ptr CAST form
instead of a decl, so the conflict is PER-SIBLING and invisible in the exemplar. 133/137 members failed
this way; all 133 sibling TUs carry the identical block-scope decl (surveyed).

THE FIX — the same-function analog of `cast_call_sites.py`.
`cast_call_sites` (§20) fixes the CALLEE direction: the draft declares a callee with a sig that
conflicts with the TU. `reconcile_tu` (§8d/§33) fixes the DATA direction. This is the third: F itself.
For each declaration of F in the TU that is INCOMPATIBLE with F's canonical/def sig (a prototype cc1
would reject alongside the def — `cdecl.compatible`, the oracle validated against the real gcc-2.7.2
front end), we:
  (1) DROP the decl (F's def is now the declaration cc1 sees), and
  (2) CAST every call of F *in that decl's scope* to the decl's ORIGINAL sig:
        func_F(a, b)  ->  ((<ret>(*)(<origtypes>))func_F)(a, b)
gcc-2.7.2 folds a compile-time cast of a known function symbol back to a direct `jal func_F` with the
decl's calling convention, so the caller's bytes are UNCHANGED — this is the byte-faithful move, NOT
the `sig_unify` "rewrite the decl to canonical, leave the call" move, which reconverts the args to the
canonical param widths and drifts the codegen (cookbook §20). The exemplar's site proves the exact form.

SAFETY (G3/P9). A pure text transform. It edits the sibling TU (F's callers live in F's own TU, which
`harvest_verify` captures as its baseline), so `family_sweep` snapshots each edited TU and reverts on a
final-SHA MISMATCH. The edit is byte-neutral BY CONSTRUCTION (it preserves the caller's exact ABI); a
transform bug can therefore only FAIL a bank (the whole-binary gate rejects it), never falsely bank one.
Idempotent: no divergent decl of F -> the TU is returned unchanged (n=0), so it is safe to run on every
member.

Standalone:
    tools/normalize_self_decls.py --tu src/ov_SC01_004/ov_SC01_004_jr_8015AE2C.c --fn func_801670E4
    from normalize_self_decls import fix;  new, n, notes = fix(tu_text, 'func_801670E4', ref_decl)
"""
import argparse
import importlib.util
import os
import re

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))


def _load(mod, rel):
    spec = importlib.util.spec_from_file_location(mod, os.path.join(REPO, rel))
    m = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(m)
    return m


cdecl = _load('cdecl', 'tools/cdecl.py')
_ccs = _load('cast_call_sites', 'tools/cast_call_sites.py')   # reuse DECL_LINE_RE / parse_sig / cast_type

DECL_LINE_RE = _ccs.DECL_LINE_RE                              # `[extern] <type> func_X(<params>);`


def _canon_from_header(fn):
    """F's canonical decl string from src/shared/engine_core.h / engine_types.h (the DEFINE_func_*
    forward-decl a shared caller emits) — the same source reconcile_def_sig/header_sig_map read."""
    for hdr in ("src/shared/engine_core.h", "src/shared/engine_types.h"):
        p = os.path.join(REPO, hdr)
        if not os.path.exists(p):
            continue
        m = re.search(rf'extern\s+([A-Za-z_][\w ]*?\**)\s*{fn}\s*\(([^)]*)\)\s*;', open(p).read())
        if m:
            ret, params = m.group(1).strip(), " ".join(m.group(2).split())
            return f"extern {ret} {fn}({params});"
    return None


def _brace_depths(text):
    """depth_before[i] = brace nesting just before line i (0-based), length len(lines)+1.
    Counted on the comment/string-masked text so a `{` in a literal cannot fool it."""
    lines = cdecl._mask(text).split('\n')
    depth, out = 0, [0]
    for ln in lines:
        depth += ln.count('{') - ln.count('}')
        out.append(depth)
    return out


def _scope_of(depths, i, n_lines):
    """The [start, end] line range whose calls a decl at line i governs. Block scope (the decl sits
    inside a function body) -> that enclosing top-level function's body; file scope -> i..EOF."""
    if depths[i] == 0:
        return i, n_lines - 1
    start = 0
    for j in range(i, -1, -1):        # back to where this function's body opened (depth 0)
        if depths[j] == 0:
            start = j
            break
    end = n_lines - 1
    for k in range(i + 1, n_lines + 1):   # forward to where it closes (depth back to 0)
        if depths[k] == 0:
            end = k - 1
            break
    return start, end


def _is_def_or_decl_line(line, fn):
    """A line that DECLARES or DEFINES fn (so its `fn(` must never be cast as a call)."""
    if DECL_LINE_RE.match(line):
        return True
    return bool(re.match(rf'^\s*[A-Za-z_][\w \t\*]*\b{fn}\s*\([^;]*\)\s*\{{', line))   # `<ret> fn(...) {`


def fix(tu_text, fn, ref_decl=None):
    """Normalize divergent self-declarations of `fn` in a TU. `ref_decl` is fn's canonical/def decl
    string (e.g. 'extern s32 func_X(s32 a0);'); derived from engine_core.h if omitted. Returns
    (new_text, n_normalized, notes)."""
    if ref_decl is None:
        ref_decl = _canon_from_header(fn)
    if ref_decl is None:
        return tu_text, 0, [f'!! no canonical decl for {fn} — cannot judge divergence']
    try:
        ref = cdecl.parse(ref_decl)[0]
    except (cdecl.CDeclError, IndexError):
        return tu_text, 0, [f'!! unparseable ref decl: {ref_decl!r}']

    lines = tu_text.split('\n')
    depths = _brace_depths(tu_text)

    # The canonical forward decl we REWRITE each divergent decl to. It matches the def (so no
    # `conflicting types`) AND keeps forward visibility for a caller whose reference precedes the def
    # in the TU — the func_8013D53C case (a file-scope `void f(void)` forward decl, def spliced BELOW
    # it) that *dropping* the decl broke (`func_8013D53C undeclared`). This is cast_call_sites' proven
    # shape: rewrite the decl to canonical, then cast every call to its original sig (byte-exact).
    canon_line = ref_decl.strip()
    if not canon_line.startswith('extern '):
        canon_line = 'extern ' + canon_line
    if not canon_line.endswith(';'):
        canon_line += ';'

    rewrite = {}                      # decl line idx -> canonical decl replacement
    casts = []                        # (start, end, cast_type_str)
    notes = []
    for i, ln in enumerate(lines):
        m = DECL_LINE_RE.match(ln)
        if not m:
            continue
        indent, _extern, ret, name, params = m.groups()
        if name != fn:
            continue
        # A TRUE no-prototype `void fn()` (empty param list) NEVER conflicts with a prototyped def in
        # either TU order (cdecl §51g), and casting it is the §32 no-proto mis-cast trap — so skip it.
        # But `(void)` is NOT no-proto: it is a 0-param PROTOTYPE that genuinely conflicts with a
        # >0-param def (func_8013D53C: sibling `void f(void)` vs def `void f(void *)` — cdecl.compatible
        # returns False), so let the compatibility check below judge it. Skipping `(void)` here was the
        # bug that made this pass miss the (void)/(T) arity class (the BUILD SPEC's "distinct" D53C).
        if params.strip() == '':
            continue
        clean = f'extern {ret.strip()} {fn}({params});'
        try:
            d = cdecl.parse(clean)[0]
        except (cdecl.CDeclError, IndexError):
            continue
        if cdecl.compatible(ref, d):          # cc1 accepts def + this decl -> not the culprit
            continue
        dret, dptypes = _ccs.parse_sig(ret, params)
        cty = _ccs.cast_type(dret, dptypes)
        s, e = _scope_of(depths, i, len(lines))
        rewrite[i] = indent + canon_line
        casts.append((s, e, cty))
        notes.append(f'{fn}@{i + 1}: `{clean}` -> `{canon_line}`; cast calls in lines {s + 1}..{e + 1} to ({cty})')

    if not rewrite:
        return tu_text, 0, notes

    call_re = re.compile(rf'\b{re.escape(fn)}\s*\(')
    out = []
    for i, ln in enumerate(lines):
        if i in rewrite:
            out.append(rewrite[i])            # rewrite the divergent decl to canonical (keeps visibility)
            continue
        if not _is_def_or_decl_line(ln, fn):  # never cast a decl/def line's `fn(`
            for (s, e, cty) in casts:
                if s <= i <= e:
                    ln = call_re.sub(f'(({cty}){fn})(', ln)
        out.append(ln)
    return '\n'.join(out), len(rewrite), notes


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument('--tu', required=True, help='the TU file to normalize (edited in place unless --out)')
    ap.add_argument('--fn', required=True, help='func_XXXXXXXX to normalize decls of')
    ap.add_argument('--canon', default=None, help="F's canonical decl (default: derived from engine_core.h)")
    ap.add_argument('--out', default=None, help='write here instead of in place')
    ap.add_argument('--dry-run', action='store_true', help='print the notes, do not write')
    a = ap.parse_args()
    tu = os.path.join(REPO, a.tu) if not os.path.isabs(a.tu) else a.tu
    new, n, notes = fix(open(tu).read(), a.fn, a.canon)
    for nt in notes:
        print(nt)
    print(f'normalized {n} decl(s) of {a.fn} in {os.path.basename(tu)}')
    if not a.dry_run and n:
        open(os.path.join(REPO, a.out) if a.out else tu, 'w').write(new)


if __name__ == '__main__':
    main()
