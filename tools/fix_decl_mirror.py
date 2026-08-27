#!/usr/bin/env python3
"""fix_decl_mirror.py — the MIRROR of fix_tu_ret_decls: bind a `void` definition to its real symbol
when the destination TU declares the function with a VALUE return. (P31 S64)

THE GAP THIS CLOSES. `fix_tu_ret_decls` repairs the common direction — the TU forward-declares
`extern void func_X(void);` while the byte-true definition returns `s32` — by RETYPING the TU's decl.
The opposite pairing has no repair at all, and it SKIPs with `definition return is 'void'` in EVERY
wave of the S63 campaign (t5d, t5e, t5f, t5g, t5h, t5i — six for six). There the TU carries
`extern s32 func_X(s32);` (a caller-derived spelling: some banked caller does read $v0) while the
byte-true definition genuinely returns nothing, so cc1 rejects the TU with
`conflicting types for 'func_X'` even though the body is byte-exact.

WHY NOT JUST RETYPE THE TU DECL DOWN TO `void` (the symmetric move)? Because it is NOT byte-neutral
in this direction. The `s32` spelling exists because a caller USES the value; narrowing the decl to
`void` makes that caller's own `x = func_X(...)` a hard error ("void value not ignored"), so the fix
would trade one broken TU for another. The asymmetry is real, which is why this is a separate tool
and not a flag on the other one.

THE REPAIR (byte-neutral by construction, and the tree's own idiom — see `impl_801833D4` and
`impl_80183BF0` in src/ov_SC04_011/ov_SC04_011_jr_8017D494.c). Define the body under a DISTINCT C
identifier and bind that identifier to the real assembler symbol with an asm label:

    void impl_80183BF0(s32 a0) __asm__("func_80183BF0");
    void impl_80183BF0(s32 a0) { ... }

Nothing then defines `func_X` under its literal C name, so the TU's `extern s32 func_X(...)`
prototype never collides; the emitted SYMBOL, the body and every call site are untouched. Byte
identity is not argued from this reasoning — the whole-binary gate remains the sole arbiter (G3/P9).

BLAST RADIUS: T0 (draft-only). This tool writes ONLY into --out; it never edits src/, config/ or any
header, so a rejected repair costs nothing to undo. (Its sibling is T1 — it edits the TU.)

  tools/fix_decl_mirror.py --pairs-file pairs.json --drafts DIR --out DIR
  tools/fix_decl_mirror.py --negative-control          # detector over every BANKED function
"""
import argparse, glob, json, os, re, shutil, sys

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
os.chdir(REPO); sys.path.insert(0, os.path.join(REPO, 'tools'))

def def_header(text, fn):
    """(return_type, params_text, span) of the DEFINITION of fn, or None.

    Anchors on the definition's start line the same way fix_tu_ret_decls.draft_ret does (a line that
    names fn with a leading type and is not an extern/call), then balances parens so a parameter list
    spanning lines — or a K&R list — is captured whole."""
    for m in re.finditer(rf'^[ \t]*([A-Za-z_][\w \t\*]*?)\s+(\**){re.escape(fn)}\s*\(', text, re.M):
        ret = m.group(1).strip()
        if ret.startswith('extern') or ret.split()[0] in ('return',):
            continue
        i = text.index('(', m.end() - 1); depth = 0; j = i
        while j < len(text):
            if text[j] == '(': depth += 1
            elif text[j] == ')':
                depth -= 1
                if depth == 0: break
            j += 1
        else:
            return None
        return ret + (' ' + m.group(2) if m.group(2) else ''), text[i + 1:j], (m.start(), m.end(), i, j)
    return None

_DECL = lambda ad: re.compile(rf'^[ \t]*extern\s+([A-Za-z_][\w \t\*]*?)\bfunc_{ad}\s*\([^;{{)]*\)\s*;', re.M | re.I)
# ANY extern decl of a func_ADDR, harvested in ONE pass per binary. Re-scanning every TU once per
# FUNCTION is what made the first negative control unusable (>15 min and still running over ~200
# overlays): the work is O(fns x files x filesize) when it is really O(files x filesize). Build the
# map once, answer from it (R33).
_ANY_DECL = re.compile(r'^[ \t]*extern\s+([A-Za-z_][\w \t\*]*?)\bfunc_([0-9A-Fa-f]+)\s*\([^;{)]*\)\s*;', re.M | re.I)
_DECLMAP = {}

def _file_scope_offsets(text):
    """a predicate: is byte-offset o at FILE scope (brace depth 0)?

    ONLY A FILE-SCOPE DECLARATION CONFLICTS WITH THE DEFINITION. A `extern int func_X();` written
    INSIDE another function's body has block scope: it dies at that closing brace and C is happy to
    see a different file-scope definition of the same name later in the very same TU. This is not a
    corner case — the R39 negative control fired on 856 BANKED functions before this check existed
    (e.g. src/ov_SC01_001/ov_SC01_001_after.c declares `extern int func_80145EE8();` at block scope
    on L136 and DEFINES `void func_80145EE8(s32)` at L234, and that TU compiles today). Counting
    block-scope decls would have rewritten every one of those working functions."""
    import cdecl
    masked = cdecl._mask(text)
    if len(masked) != len(text):
        masked = text                      # length invariant broken: fall back, do not mis-index
    depth, out = 0, bytearray(len(text))
    for i, ch in enumerate(masked):
        if ch == '{': depth += 1
        elif ch == '}': depth = max(0, depth - 1)
        out[i] = 1 if depth == 0 else 0
    return out

def _declmap(tu_path):
    """{addr: [(relpath, return_spelling)]} for the FILE-SCOPE extern func_ADDR decls in ONE TU.

    SCOPED TO A SINGLE FILE ON PURPOSE. A declaration in `<bin>_jr_A.c` cannot conflict with a
    definition in `<bin>_after.c`: they are different translation units and C only ever sees one at
    a time. Keying this by BINARY (globbing all of `src/<bin>/<bin>*.c`) was the SECOND defect the
    R39 negative control caught — after the block-scope fix it still fired on 580 banked functions,
    every one of them a decl sitting in a sibling TU."""
    tu_path = tu_path if os.path.isabs(tu_path) else os.path.join(REPO, tu_path)
    if tu_path in _DECLMAP: return _DECLMAP[tu_path]
    m = {}
    try: t = open(tu_path, errors='replace').read()
    except OSError:
        _DECLMAP[tu_path] = m; return m
    at_file_scope = _file_scope_offsets(t)
    rel = os.path.relpath(tu_path, REPO)
    for mm in _ANY_DECL.finditer(t):
        if not at_file_scope[mm.start()]: continue         # block scope: cannot conflict
        m.setdefault(mm.group(2).lower(), []).append((rel, mm.group(1).strip()))
    _DECLMAP[tu_path] = m
    return m


def tu_value_decls(tu_path, fn):
    """[(file, return_spelling)] for every FILE-SCOPE decl of fn, IN ITS OWN TU, returning non-void."""
    ad = re.search(r'func_([0-9A-Fa-f]+)', fn)
    if not ad: return []
    return [(f, r) for f, r in _declmap(tu_path).get(ad.group(1).lower(), [])
            if r and r.replace('*', '').strip() != 'void']


def repair(draft_text, fn):
    """the transformed draft, or (None, reason)."""
    h = def_header(draft_text, fn)
    if not h: return None, 'no definition found in the draft'
    ret, params, (s, _e, i, j) = h
    if ret.replace('*', '').strip() != 'void':
        return None, f'definition returns {ret!r}, not void — that is fix_tu_ret_decls\' direction'
    ad = re.search(r'func_([0-9A-Fa-f]+)', fn).group(1)
    alias = f'impl_{ad}'
    # a K&R list (bare identifiers) cannot be repeated in a prototype: declare it no-proto instead
    p = params.strip()
    proto = params if (not p or p == 'void' or re.search(r'[\*\s]', p.strip(' ,')) and
                       re.search(r'\b(void|char|short|int|long|unsigned|signed|float|double|struct|union|enum|[su](8|16|32)|f32|const|volatile)\b', p)) else ''
    head = draft_text[:s]
    decl = (f'/* DECL MIRROR (P31 S64, tools/fix_decl_mirror.py): this TU forward-declares\n'
            f'   `func_{ad}` with a VALUE return (a caller reads $v0), but the byte-true definition\n'
            f'   returns nothing. Defining `void func_{ad}(...)` literally would be\n'
            f'   "conflicting types for \'func_{ad}\'". Define the body under a distinct C identifier\n'
            f'   and bind it to the real assembler symbol — same idiom as impl_801833D4 /\n'
            f'   impl_80183BF0 in src/ov_SC04_011/ov_SC04_011_jr_8017D494.c. Byte-neutral: the emitted\n'
            f'   symbol, the body and every call site are unchanged. */\n'
            f'{ret} {alias}({proto}) __asm__("func_{ad}");\n\n')
    body = draft_text[s:]
    # rename ONLY the definition\'s own name token (the first one, at the header we located)
    off = body.index(fn)
    body = body[:off] + alias + body[off + len(fn):]
    return head + decl + body, None

def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument('--pairs-file'); ap.add_argument('--pairs')
    ap.add_argument('--drafts'); ap.add_argument('--out')
    ap.add_argument('--negative-control', action='store_true',
                    help='run the DETECTOR over every banked function and require ZERO hits (R39): a '
                         'banked function compiles in its TU, so a mirror conflict there would be a '
                         'false positive, and a false positive here silently rewrites good work.')
    a = ap.parse_args()

    if a.negative_control:
        import corpus
        bins = sorted({os.path.basename(os.path.dirname(p)) for p in glob.glob('src/ov_*/*.c')})
        hits, checked = [], 0
        for b in bins:
            try: open_syms = {x.symbol for x in corpus.stubs(b).values()}
            except Exception: continue
            for f in sorted(glob.glob(f'src/{b}/{b}*.c')):
                t = open(f, errors='replace').read()
                for m in re.finditer(r'^[ \t]*void\s+\**(?:impl_)?(func_[0-9A-Fa-f]+)\s*\(', t, re.M):
                    fn = m.group(1)
                    if fn in open_syms: continue            # still a stub, not banked
                    checked += 1
                    if tu_value_decls(f, fn):
                        hits.append(f'{b}:{fn} ({os.path.relpath(f, REPO)})')
        print(f'negative control: {checked} BANKED void-returning definitions checked across '
              f'{len(bins)} overlays; detector fired on {len(hits)}')
        if hits:
            print('FALSE POSITIVES (each is a banked fn the detector would have rewritten):')
            for h in hits[:20]: print('   ', h)
            sys.exit(3)
        print('PASS — zero false positives (R39).')
        return

    pairs = json.load(open(a.pairs_file)) if a.pairs_file else json.loads(a.pairs or '[]')
    if not (a.drafts and a.out): sys.exit('--drafts and --out are required')
    shutil.rmtree(a.out, ignore_errors=True)
    n_fix = n_skip = 0
    for b, fn in pairs:
        src = os.path.join(a.drafts, b, fn + '.c')
        if not os.path.exists(src):
            print(f'SKIP   {b:<14} {fn}  no draft at {src}'); n_skip += 1; continue
        try:
            import corpus
            st = {x.symbol: x for x in corpus.stubs(b).values()}.get(fn)
            tu = st.path if st else None
        except Exception:
            tu = None
        if not tu:
            print(f'SKIP   {b:<14} {fn}  cannot resolve its destination TU'); n_skip += 1; continue
        decls = tu_value_decls(tu, fn)
        if not decls:
            print(f'SKIP   {b:<14} {fn}  TU has no value-returning decl — not this class'); n_skip += 1; continue
        fixed, why = repair(open(src, errors='replace').read(), fn)
        if fixed is None:
            print(f'SKIP   {b:<14} {fn}  {why}'); n_skip += 1; continue
        d = os.path.join(a.out, b); os.makedirs(d, exist_ok=True)
        open(os.path.join(d, fn + '.c'), 'w').write(fixed)
        print(f'MIRROR {b:<14} {fn}  TU declares {decls[0][1]!r} at {decls[0][0]} -> impl_ alias'); n_fix += 1
    print(f'fix_decl_mirror: {n_fix} repaired into {a.out}, {n_skip} skipped of {len(pairs)} '
          f'(T0 draft-only; the whole-binary gate decides — G3/P9)')


if __name__ == "__main__":
    main()
