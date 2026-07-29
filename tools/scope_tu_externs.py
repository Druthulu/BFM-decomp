#!/usr/bin/env python3
"""scope_tu_externs.py — move a TU's OWN file-scope DATA externs down into their consumers, so a
byte-true block-scope declaration of a different type becomes legal (Phase 29 T48/T51, cookbook §103).

THE OTHER HALF OF THE §8d LEVER
-------------------------------
`scope_data_externs.py` fixes the INCOMING draft: it demotes the carried file-scope decls of a
templated body to block scope so the body declares no global the target TU never had. But it has a
documented give-up branch — when the TU ALREADY declares the symbol at file scope above the splice
point, it DROPS the draft's own decl entirely and lets the TU's declaration govern. That is correct
when the two types agree, and fatal when they do not: the body then compiles against the TU's type
and its codegen changes.

That is exactly the T48/T50 wall. `func_80135260` needs D_x declared as a 4-byte POINTER
(`extern u16 *D_x;`) — the canonical `extern u8 D_x;` + `(*(u16**)&D_x)` cast makes gcc-2.7.2 CSE
`&D_x` into two callee-saved registers, costing a 7th saved register and +3 instructions. Measured
twice, two independent ways (reconcile_tu and cast-at-use), both 139 ins vs the target's 136. So the
draft cannot be bent; the TU's declaration has to move.

    FILE(u8 D_x) ... then BLOCK(u16 *D_x) in a later fn   ->  "conflicting types for D_x"  (ERROR)
    (no file-scope decl) ... BLOCK(u8) ... BLOCK(u16 *)   ->  builds; each fn owns its own view

A FILE-scope extern in a shared overlay TU is a GLOBAL CONSTRAINT ON EVERY LATER FUNCTION in that
TU. The engine is loosely typed (§16), so per-function views legitimately disagree — which means the
file-scope decl is the anomaly, not the block-scope one. Moving it restores fidelity: the original
per-function sources (m2c/Ghidra) declare these symbols at block scope in precisely this way.

BYTE-NEUTRAL BY CONSTRUCTION: an `extern` emits no code, and this rewrite changes neither the symbol
nor the declared type seen at any use site — every consumer keeps the identical declaration text, only
its scope moves. Only name lookup changes. Proven on the exemplar in two steps (T48): the decl move
ALONE rebuilt ov_SC01_077 byte-identical `d19c9580`, and only then did the byte-true draft bank.
The whole-binary byte-gate (G3/P9) remains the sole arbiter — a wrong move just fails the gate.

REFUSES RATHER THAN SILENTLY SKIPPING (R32). Three conditions abort the symbol (never a quiet no-op):
  * more than one file-scope decl of the symbol above the splice point (ambiguous which one governs)
  * a reference to the symbol in a file-scope statement BELOW the decl (an initializer such as
    `void *p = &D_x;` — that reference has nowhere to move to, so the decl cannot be deleted)
  * a consumer whose body-opening brace cannot be located unambiguously
and the rewrite asserts its own coverage afterwards: no file-scope decl of a moved symbol survives
above the splice point, and every planned insertion is present.

WHY cdecl AND NOT ANOTHER REGEX (R33): `cdecl.split_statements` gives depth-0 statement SPANS (a
function definition flushes at its closing `}`), and `cdecl._mask` blanks comments and string
literals length-preservingly, so offsets stay valid. Scanning raw text for `\bD_x\b` is the
comment-scanning false-positive class that made `gather_externs` accuse `func_80135D20` on all 137
siblings (T50) and garbled `gen_harvest_targets`' hints in Phase 19.

Usage (library — the family sweep calls scope() directly; xN per family, so no subprocess):
    from scope_tu_externs import scope
    new_tu, report = scope(tu_text, ['D_8017F198', 'D_8017F19C'], above=stub_pos)

CLI (single TU — diagnostics):
    tools/scope_tu_externs.py --tu src/ov_SC01_000/ov_SC01_000_jr_8012ACE0.c \
        --syms D_8017F198,D_8017F19C,D_8017F1A4 --above func_80135260 [--in-place|--out f]

CLI (FLEET — the reusable form: derive each sibling's contested symbols from the remapped draft and
scope them across the whole family in one reproducible command):
    tools/scope_tu_externs.py --family func_80135260 --from ov_SC01_077 --from-addr 0x80135260 \
        --members .run/jtbl_members_0x80135260.json [--in-place]

The contested set is derived, never hand-listed (R33): it is the DATA symbols the remapped sibling
draft declares at block scope, intersected with the symbols that TU declares at FILE scope above the
splice point. A sibling with an empty intersection is reported and left alone.
"""
import argparse
import os
import re
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import cdecl                                                    # noqa: E402

# an `extern ...;` line at ANY indentation — the block-scope-decl test inside a function body
ANY_EXTERN_RE = re.compile(r'^\s*extern\b[^;{}\n]*;')
TAG_OPEN_RE = re.compile(r'\b(?:struct|union|enum)\b[^;{}]*\{')

MARK = ('/* [T51] scoped in from file scope: a file-scope decl of these symbols constrains every\n'
        '   LATER function in this TU, which blocks a byte-true decl of a different type.\n'
        '   Declaration-only move (cookbook §103); the whole-binary byte-gate is the arbiter. */')
INDENT = '    '   # the corpus' body indentation; NOT copied from the neighbouring line, which in
                  # several TUs is itself misindented (an 8-space run inside a 4-space body).


class ScopeRefused(Exception):
    """The move is not provably safe for this symbol. Loud by design (R32) — the caller decides
    whether to skip the symbol or abort; it is never silently treated as 'nothing to do'."""


def _is_func_def(stmt):
    """A depth-0 statement that closes with `}` is a function definition; everything else (including
    an aggregate initializer, which flushes at its `;`) is not. This is the `_depth0_spans` contract,
    not a guess about column 0 — m2c emits goto labels at column 0 INSIDE bodies."""
    return stmt.text.rstrip().endswith('}')


def _body_open(stmt_text):
    """Offset just past the newline following the body-opening `{`, i.e. where block-scope decls go.

    The body brace is the first `{` at paren-depth 0 (so a parameter list cannot fool it, and the
    K&R form — whose parameter declarations sit between the signature and the brace — works too).
    A return type that DEFINES an aggregate (`struct { ... } f(void) {`) would put an earlier `{` at
    paren-depth 0; that is refused rather than mis-placed."""
    m = cdecl._mask(stmt_text)
    depth = 0
    for i, ch in enumerate(m):
        if ch == '(':
            depth += 1
        elif ch == ')':
            depth -= 1
        elif ch == '{' and depth == 0:
            if TAG_OPEN_RE.search(m[:i + 1]):
                raise ScopeRefused('body brace ambiguous (aggregate defined in the return type)')
            j = stmt_text.find('\n', i)
            return (j + 1) if j >= 0 else (i + 1)
    raise ScopeRefused('no body-opening brace found')


def plan(tu_text, syms, above=None):
    """Compute the edit plan without touching anything. Returns (edits, report).

    `above` — a char offset (typically the splice point). Only file-scope decls ABOVE it constrain a
    body spliced there, and only statements BELOW the decl can need a re-declaration.

    edits: list of (start, end, replacement) span edits, disjoint, in source order.
    report: {'moved': {sym: [fn_names]}, 'skipped': {sym: reason}, 'deleted': {sym: (start, end)}}
    """
    limit = len(tu_text) if above is None else above
    stmts = cdecl.split_statements(tu_text)
    report = {'moved': {}, 'skipped': {}, 'deleted': {}}
    deletions = []                              # (start, end)
    insertions = {}                             # stmt_index -> [decl_line, ...]

    for sym in syms:
        word = re.compile(rf'\b{re.escape(sym)}\b')
        decls = [i for i, s in enumerate(stmts)
                 if s.start < limit
                 and not _is_func_def(s)
                 and s.text.lstrip().startswith('extern')
                 and word.search(cdecl._mask(s.text))]
        if not decls:
            report['skipped'][sym] = 'no file-scope decl above the splice point'
            continue
        if len(decls) > 1:
            report['skipped'][sym] = f'{len(decls)} file-scope decls above the splice point (ambiguous)'
            continue
        di = decls[0]
        decl_line = stmts[di].text.strip()

        consumers, refused = [], None
        for j, s in enumerate(stmts[di + 1:], start=di + 1):
            body_mask = cdecl._mask(s.text)
            if not word.search(body_mask):
                continue
            if not _is_func_def(s):
                refused = (f'file-scope statement at offset {s.start} references {sym} below the '
                           f'decl — it has nowhere to move to')
                break
            if any(ANY_EXTERN_RE.match(ln) and word.search(ln) for ln in body_mask.split('\n')):
                continue                        # already owns a block-scope view of the symbol
            try:
                _body_open(s.text)
            except ScopeRefused as e:
                refused = f'consumer at offset {s.start}: {e}'
                break
            consumers.append(j)
        if refused:
            report['skipped'][sym] = refused
            continue

        deletions.append((stmts[di].start, stmts[di].end))
        report['deleted'][sym] = (stmts[di].start, stmts[di].end)
        for j in consumers:
            insertions.setdefault(j, []).append(decl_line)
        report['moved'][sym] = [_fn_name(stmts[j].text) for j in consumers]

    edits = []
    for start, end in deletions:
        # swallow the decl's own line ending so the deletion leaves no blank line behind
        e = end
        while e < len(tu_text) and tu_text[e] in ' \t':
            e += 1
        if e < len(tu_text) and tu_text[e] == '\n':
            e += 1
        edits.append((start, e, ''))
    for j, lines in insertions.items():
        s = stmts[j]
        at = _body_open(s.text)
        block = ''.join(f'{INDENT}{ln}\n' for ln in MARK.split('\n'))
        block += ''.join(f'{INDENT}{ln}\n' for ln in lines)
        edits.append((s.start + at, s.start + at, block))
    edits.sort(key=lambda e: e[0])
    return edits, report


def apply_edits(text, edits):
    """Apply disjoint span edits right-to-left so earlier offsets stay valid."""
    for start, end, repl in sorted(edits, key=lambda e: e[0], reverse=True):
        text = text[:start] + repl + text[end:]
    return text


def scope(tu_text, syms, above=None):
    """Move the file-scope decls of `syms` into their consumers. Returns (new_text, report).

    A no-op (text unchanged, report['moved'] empty) when no symbol qualifies. Asserts its own
    coverage afterwards (R32): every moved symbol's file-scope decl is gone above the splice point,
    and every planned insertion is present."""
    edits, report = plan(tu_text, syms, above)
    if not report['moved']:
        return tu_text, report
    before = {s: _counts(tu_text, s) for s in report['moved']}
    new = apply_edits(tu_text, edits)

    # ---- coverage assertion (R32): the rewrite did exactly what the plan said, or we fail loudly.
    # Counted as a DELTA against the pre-edit state — the TUs already carry many legitimate
    # block-scope decls of these symbols, so an absolute ">= want" would pass vacuously.
    for sym, fns in report['moved'].items():
        f_before, b_before = before[sym]
        f_after, b_after = _counts(new, sym)
        if f_after != f_before - 1:
            raise ScopeRefused(f'coverage: {sym} file-scope decls {f_before} -> {f_after}, expected -1')
        if b_after != b_before + len(fns):
            raise ScopeRefused(f'coverage: {sym} block-scope decls {b_before} -> {b_after}, '
                               f'expected +{len(fns)}')
    return new, report


def _counts(text, sym):
    """(file-scope extern decls, block-scope extern decls) of `sym`. Comment/string-masked, so a
    mention in prose cannot be counted as a declaration."""
    word = re.compile(rf'\b{re.escape(sym)}\b')
    f = b = 0
    for ln in cdecl._mask(text).split('\n'):
        if not ANY_EXTERN_RE.match(ln) or not word.search(ln):
            continue
        if ln.startswith('extern'):
            f += 1
        else:
            b += 1
    return f, b


def _fn_name(stmt_text):
    m = re.search(r'\b([A-Za-z_]\w*)\s*\(', cdecl._mask(stmt_text))
    return m.group(1) if m else '?'


def stub_pos(tu_text, func, tu_path=''):
    m = re.search(rf'INCLUDE_ASM\("[^"]*",\s*{re.escape(func)}\);', tu_text)
    if not m:
        raise ScopeRefused(f'no INCLUDE_ASM stub for {func} in {tu_path}')
    return m.start()


def contested(draft_body, tu_text, above):
    """The DATA symbols a staged draft declares — at EITHER scope — that the target TU also declares
    at FILE scope above the splice point. That intersection is exactly the set whose two declarations
    collide. Derived from the draft, never hand-listed (R33).

    BOTH SCOPES, and the first cut got this wrong (Phase 29 T55). It scanned only the draft's
    BLOCK-scope externs, because in T51's motivating family the byte-true decls had been written
    inside the function body by hand. But `family_remap.gather_externs` carries an exemplar's decls
    in at FILE scope (column 0), and those are the ones `scope_data_externs.fix` DROPS when the
    target TU already declares the symbol — its documented give-up branch, and the fatal case this
    whole lever exists for. So the scan was blind to the majority form: on `func_8014032C`
    `scope_data_fix` dropped three symbols while `contested` returned `[]`, and the tu-scoped stage
    never fired on precisely the class it was built for (`conflicting types for D_80115128`).

    The rule is scope-independent: a draft decl and a TU file-scope decl of the same symbol collide
    wherever the draft's sits."""
    draft_syms, seen = [], set()
    for ln in cdecl._mask(draft_body).split('\n'):
        if not ANY_EXTERN_RE.match(ln):
            continue
        d = re.search(r'\bD_[0-9A-Fa-f]{6,8}\b', ln)
        if d and d.group(0) not in seen:
            seen.add(d.group(0))
            draft_syms.append(d.group(0))
    file_syms = {s for s in draft_syms if _counts(tu_text[:above], s)[0]}
    return [s for s in draft_syms if s in file_syms]


def _family(a):
    """Scope the contested decls across every still-stubbed member of a family."""
    import glob
    import json
    from family_remap import remap_hseq

    members = json.load(open(a.members))
    from_addr = int(a.from_addr, 16)
    touched = skipped = nothing = 0
    for ov, addr in members:
        hits = [cf for cf in sorted(glob.glob(f'src/{ov}/{ov}*.c'))
                if re.search(rf'INCLUDE_ASM\("[^"]*",\s*{re.escape(a.family)}\);', open(cf).read())]
        if not hits:
            continue                                   # already banked — not a sweep target
        if len(hits) > 1:
            print(f'{ov:16} REFUSE  {len(hits)} stubs for {a.family} (ambiguous TU)')
            skipped += 1
            continue
        cf, text = hits[0], open(hits[0]).read()
        body, _info = remap_hseq(from_addr, a.from_ov, ov, int(addr, 16))
        if body is None:
            print(f'{ov:16} REFUSE  remap declined')
            skipped += 1
            continue
        try:
            pos = stub_pos(text, a.family, cf)
            syms = contested(body, text, pos)
            if not syms:
                nothing += 1
                continue
            new, report = scope(text, syms, pos)
        except ScopeRefused as e:
            print(f'{ov:16} REFUSE  {e}')
            skipped += 1
            continue
        if not report['moved']:
            nothing += 1
            continue
        if a.in_place:
            open(cf, 'w').write(new)
        moved = sum(len(v) for v in report['moved'].values())
        print(f'{ov:16} {"scoped" if a.in_place else "would scope"} '
              f'{len(report["moved"])} sym(s), {moved} insertion(s)')
        touched += 1
    print(f'\n=== {a.family}: {touched} TU(s) scoped · {nothing} nothing-to-do · {skipped} refused ===')
    if not a.in_place:
        print('(dry run — pass --in-place to write)')
    return 1 if skipped else 0


def main():
    ap = argparse.ArgumentParser(description=__doc__,
                                 formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument('--tu')
    ap.add_argument('--syms', help='comma-separated D_ symbols to scope')
    ap.add_argument('--above', help='function name: only consider decls above its INCLUDE_ASM stub')
    ap.add_argument('--family', help='fleet mode: scope this function\'s family')
    ap.add_argument('--from', dest='from_ov', help='fleet mode: the exemplar overlay')
    ap.add_argument('--from-addr', help='fleet mode: the exemplar address (hex)')
    ap.add_argument('--members', help='fleet mode: members.json [[ov, addr_hex], ...]')
    ap.add_argument('--out')
    ap.add_argument('--in-place', action='store_true')
    a = ap.parse_args()

    if a.family:
        if not (a.from_ov and a.from_addr and a.members):
            ap.error('--family needs --from, --from-addr and --members')
        sys.exit(_family(a))
    if not (a.tu and a.syms):
        ap.error('single-TU mode needs --tu and --syms (or use --family)')

    text = open(a.tu).read()
    pos = stub_pos(text, a.above, a.tu) if a.above else None

    new, report = scope(text, [s for s in a.syms.split(',') if s], pos)
    for sym, fns in report['moved'].items():
        print(f'moved {sym} -> {len(fns)} consumer(s): {", ".join(fns)}')
    for sym, why in report['skipped'].items():
        print(f'SKIP  {sym}: {why}')
    if not report['moved']:
        print('nothing to do')
        return
    if a.in_place:
        open(a.tu, 'w').write(new)
        print(f'rewrote {a.tu}')
    elif a.out:
        open(a.out, 'w').write(new)
        print(f'wrote {a.out}')
    else:
        print(f'(dry run — {len(new) - len(text):+d} bytes; pass --in-place or --out to write)')


if __name__ == '__main__':
    main()
