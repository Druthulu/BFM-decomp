#!/usr/bin/env python3
"""Def-side-wall reconcile (Phase-25 T5b/T7 lever; v2 Phase-25 T6).

A drafter writes an isolation-MATCH giant body with Ghidra-derived TYPED parameters
(void func(u32 *a0, s16 *a2)). Placed in the real overlay TU it hits `conflicting types`:
the TU's callers reference the function through the CANONICAL signature declared in
src/shared/engine_core.h (extern void func(s32, s32, void*)) — or, absent that, through
gcc-2.7.2's implicit K&R `int func()` from a call site above the definition. The gate's
sig_unify can't reach the engine_core.h decl (it lives inside a DEFINE_ macro) so the
draft never banks.

This reconciles the DEF to the canonical signature, BYTE-NEUTRALLY:
  1. strip the draft's redefinitions of types already in src/shared/engine_types.h
     (identical-definition typedefs — a redef is a hard error in gcc-2.7.2 / C89);
  2. rewrite the def signature to the canonical (return type + positional param types;
     arity-grow adds unused params so an implicit-int caller with N args still matches);
  3. cast each type-changed param AT ITS USES — never via an intermediate local, which
     introduces a fresh pseudo and shifts register allocation (proven: cast-locals broke
     func_8013B274, at-use casts banked it byte-identical).

v2 (Phase-25 T6 — the 62-stub probe found v1's ambient/strip policies WERE the residual walls;
all additions byte-gated by the same probe, cookbook §41):
  4. AMBIENT TRUTH from the PREPROCESSED TU: v1 token-scanned engine_core.h/the raw TU, which
     (a) counted symbols declared only INSIDE DEFINE_ macro bodies / block scope as ambient →
     over-stripped the draft's needed externs (`D_x undeclared`), and (b) missed the TU's own
     file-scope decl of the fn (self `conflicting types`). v2 runs cpp on the pristine TU and
     brace-depth-0-scans the REAL post-expansion file scope: what cc1 actually sees.
  5. CANONICAL source order: explicit --sig > the TU's file-scope decl of fn (includes
     engine_core.h via its #include) > implicit-int `s32 fn(s32,...)` fallback.
  6. scalar-typedef dups (u8/s16/M2C_UNK...; common.h provides them) are ALWAYS stripped —
     same set match_one strips (masked_diff.SCALAR_TYPEDEF_RE).
  7. COLLIDING typedef (same name, DIFFERENT definition than ambient) → RENAMED
     `Name` → `Name_<fnaddr>` throughout the draft. Type names emit no code → byte-neutral.
     (v1 left them → `conflicting types for SVEC/Vec3/...`.)
  8. CALLEE sig conflicts (draft's extern for a callee differs from the TU's file-scope decl:
     arity / void-return / param types) → strip the draft's extern + CAST EVERY CALL SITE to
     the draft's intended sig `((dret(*)(dparams))callee)(...)` — the §17a-1 transform
     (cookbook §20, cast_call_sites.py); gcc-2.7.2 folds a cast of a known symbol to a direct
     jal with the draft's calling convention. Applies to func_* and named (PsyQ) callees alike.
  9. DATA externs: multi-name lines split name-by-name (v1 dropped whole lines, losing
     non-ambient names); not-ambient → KEPT; ambient-identical → stripped; ambient with a
     DIFFERENT type → stripped + uses access-cast byte-neutrally to the draft's view
     (`((u8*)D_x)` / `((u8*)&D_x)` / `(*(s16*)D_x)` per array-ness pair).

The whole-binary harvest_verify byte-gate remains the sole arbiter (G3/P9) — a wrong
reconcile simply fails to bank.

Usage:
  tools/canon_sig_reconcile.py --fn func_8013B274 --draft .run/drafts-t5-batch2/func_8013B274.c \
      --out .run/t5b2-recon/func_8013B274.c --tu src/ov_SC01_077/ov_SC01_077_a.c \
      [--sig 'void func_8013B274(s32 a0, s32 a1, void *a2)']
"""
import re, os, argparse, subprocess, importlib.util

EC = 'src/shared/engine_core.h'
ET = 'src/shared/engine_types.h'


def _load(mod, rel):
    spec = importlib.util.spec_from_file_location(
        mod, os.path.join(os.path.dirname(os.path.abspath(__file__)), rel))
    m = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(m)
    return m


# THE declaration oracle (Phase 26-A §51g): a total recursive-descent parser of C's declarator
# grammar. It classifies fn-ptr / sized-array / multi-declarator decls the tu_ambient/visible_above
# regexes were structurally blind to — the class that put fn-ptr DISPATCH TABLES in NO bucket, so
# `visible_above` under-reported them and _reconcile_data block-moved the draft's extern into a
# guaranteed `conflicting types` (docs/tooling-audit.md, the two HIGH findings on this file).
cdecl = _load('cdecl', 'cdecl.py')

CPP = ['mipsel-linux-gnu-cpp', '-lang-c', '-Iinclude', '-undef', '-Wall', '-fno-builtin',
       '-Dmips', '-D__GNUC__=2', '-D__OPTIMIZE__', '-Dpsx', '-D_PSYQ', '-D_MIPSEL', '-D_LANGUAGE_C']

# the scalar/M2C typedefs common.h provides — C89 rejects the dup (same set match_one strips)
SCALAR_TYPEDEF_RE = re.compile(
    r"^[ \t]*typedef\b[^;]*\b(u8|u16|u32|u64|s8|s16|s32|s64|f32|f64|"
    r"M2C_UNK|M2C_UNK8|M2C_UNK16|M2C_UNK32|M2C_UNK64)[ \t]*;[ \t]*\n", re.M)


def _norm(s):
    return re.sub(r'\s+', ' ', s).strip()


def _strip_strings(text):
    """Blank string/char literals so brace counting can't be fooled."""
    return re.sub(r'"(?:\\.|[^"\\])*"|\'(?:\\.|[^\'\\])*\'', '""', text)


def _comment_masked(text):
    """Same-length copy with comments blanked (offsets preserved) — regex anchors found on
    the mask apply to the original. v3.1: the def-locator was anchoring inside drafts'
    @stuck comment headers, which quote the signature."""
    def blank(m):
        return re.sub(r'[^\n]', ' ', m.group(0))
    text = re.sub(r'/\*.*?\*/', blank, text, flags=re.S)
    text = re.sub(r'//[^\n]*', blank, text)
    return text


# ---------------------------------------------------------------------------
# v2 ambient truth: preprocess the TU, keep only brace-depth-0 (file-scope) text
# ---------------------------------------------------------------------------

def _file_scope_statements(tu_path):
    """cpp the pristine TU -> the file-scope statement list cc1 actually sees.
    Returns list of statement strings (depth-0 text). A function DEFINITION flushes at its
    closing '}' (the '{' followed a ')'); a typedef/struct/initializer '{...}' runs to its ';'
    (v2.1 — the v2 scanner merged a def's trailing '}' into the next statement)."""
    p = subprocess.run(CPP + [tu_path], capture_output=True, text=True)
    if p.returncode:
        raise RuntimeError(f'cpp failed on {tu_path}: {p.stderr[-400:]}')
    stmts, cur, depth = [], [], 0
    brace_after_paren = False        # the current depth-0 '{' opened a function BODY
    for line in p.stdout.split('\n'):
        if line.startswith('#'):        # cpp line markers
            continue
        line = _strip_strings(line)
        for ch in line:
            if ch == '{':
                if depth == 0:
                    last = next((c for c in reversed(cur) if not c.isspace()), '')
                    brace_after_paren = (last == ')')
                    cur.append(ch)
                depth += 1
                continue
            if ch == '}':
                depth -= 1
                if depth == 0:
                    cur.append(ch)
                    if brace_after_paren:           # function definition ends here
                        stmts.append(''.join(cur).strip())
                        cur = []
                        brace_after_paren = False
                continue
            if depth == 0:
                cur.append(ch)
                if ch == ';':
                    stmts.append(''.join(cur).strip())
                    cur = []
        if depth == 0:
            cur.append(' ')
    if ''.join(cur).strip():
        stmts.append(''.join(cur).strip())
    return stmts


_AMBIENT_CACHE = {}
_VISIBLE_CACHE = {}


def _fnptr_data(tu_path, above=None):
    """cdecl SUPPLEMENT: the fn-ptr DATA dispatch tables (`extern void (*D_x[])(void);`) the
    tu_ambient/visible_above regexes are structurally blind to — their type class `[\\w \\*]`
    cannot hold a `(`, so these land in NO bucket, `visible_above` under-reports them, and
    _reconcile_data block-moves the draft's extern into a guaranteed `conflicting types`
    (docs/tooling-audit.md, the two HIGH findings). Additive: name -> (fnptr-type, is_array),
    over exactly the symbols the regex dropped."""
    out = {}
    for name, d in cdecl.tu_scope(tu_path, above=above).items():
        if d.storage != 'typedef' and d.kind in ('fnptr', 'fnptr_array'):
            out[name] = (d.type, bool(d.is_array))     # 'void (*)(void)' / 'void (*[])(void)'
    return out


def visible_above(tu_path, fn):
    """v3: the set of file-scope names (funcs+data) declared ABOVE fn's INCLUDE_ASM stub —
    what is actually in scope at the splice point. Drives the block-scope-vs-ambient branch.
    v3.3 (Phase 26-A): UNION the cdecl fn-ptr-data names the regex is blind to, so a dispatch
    table can no longer fall out of `visible` and trigger a wrong block-scope move."""
    key = (tu_path, fn)
    if key in _VISIBLE_CACHE:
        return _VISIBLE_CACHE[key]
    tu = open(tu_path).read()
    m = re.search(r'^INCLUDE_ASM\("[^"]*",\s*' + re.escape(fn) + r'\);\s*$', tu, flags=re.M)
    prefix = tu[:m.start()] if m else tu
    tmp = os.path.join(os.path.dirname(tu_path), f'.csr_amb_{fn}.c')
    open(tmp, 'w').write(prefix)
    try:
        names = set()
        for st in _file_scope_statements(tmp):
            stn = _norm(st)
            fm = re.match(r'^(?:extern\s+)?([A-Za-z_][\w \*]*?)\b([A-Za-z_]\w*)\s*\(([^()]*)\)\s*(;|\{)', stn)
            if fm:
                names.add(fm.group(2)); continue
            dm = re.match(r'^(?:extern\s+)?([A-Za-z_][\w \*]*?)\s*\b([A-Za-z_]\w*(\s*\[[^\]]*\])?'
                          r'(\s*,\s*\**[A-Za-z_]\w*(\s*\[[^\]]*\])?)*)\s*;$', stn)
            if dm and not stn.startswith('typedef'):
                for piece in dm.group(2).split(','):
                    nm = re.match(r'^\**\s*([A-Za-z_]\w*)', piece.strip())
                    if nm:
                        names.add(nm.group(1))
    finally:
        os.path.exists(tmp) and os.remove(tmp)
    names |= set(_fnptr_data(tu_path, above=fn))       # v3.3: + the fn-ptr dispatch tables
    _VISIBLE_CACHE[key] = names
    return names


def tu_ambient(tu_path):
    """The TU's REAL file-scope namespace: {'funcs': name->decl, 'data': name->(type,is_arr),
    'typedefs': name->normalized def}. Function DEFINITIONS count as decls (sig authority).
    v3.3 (Phase 26-A): the fn-ptr DATA symbols the regex drops into no bucket are supplemented
    from cdecl — additive, so every symbol the proven regex classified is byte-identical."""
    if tu_path in _AMBIENT_CACHE:
        return _AMBIENT_CACHE[tu_path]
    funcs, data, typedefs = {}, {}, {}
    for st in _file_scope_statements(tu_path):
        stn = _norm(st)
        m = re.match(r'^typedef\b(.*?)\b([A-Za-z_]\w*)\s*(\[[^\]]*\])?\s*;$', stn)
        if m and '(' not in m.group(2):
            typedefs[m.group(2)] = stn
            continue
        # function decl or definition: ret name(params) [;|{...}]
        m = re.match(r'^(?:extern\s+)?([A-Za-z_][\w \*]*?)\b([A-Za-z_]\w*)\s*\(([^()]*)\)\s*(;|\{)', stn)
        if m and m.group(1).strip() not in ('return',):
            funcs[m.group(2)] = f'{m.group(1).strip()} {m.group(2)}({m.group(3)})'
            continue
        # data decl(s): extern T a, b[4]; (also tentative defs at file scope)
        m = re.match(r'^(?:extern\s+)?([A-Za-z_][\w \*]*?)\s*\b([A-Za-z_]\w*(\s*\[[^\]]*\])?'
                     r'(\s*,\s*\**[A-Za-z_]\w*(\s*\[[^\]]*\])?)*)\s*;$', stn)
        if m and not stn.startswith('typedef'):
            base = m.group(1).strip()
            if base and base.split()[-1] not in ('struct', 'union', 'enum'):
                for piece in m.group(2).split(','):
                    piece = piece.strip()
                    dm = re.match(r'^(\**)\s*([A-Za-z_]\w*)\s*(\[[^\]]*\])?$', piece)
                    if dm:
                        data[dm.group(2)] = (base + (' ' + dm.group(1) if dm.group(1) else ''),
                                             dm.group(3) is not None)
    for name, dt in _fnptr_data(tu_path).items():      # v3.3: + the fn-ptr dispatch tables
        if name not in data and name not in funcs and name not in typedefs:
            data[name] = dt
    _AMBIENT_CACHE[tu_path] = dict(funcs=funcs, data=data, typedefs=typedefs)
    return _AMBIENT_CACHE[tu_path]


# ---------------------------------------------------------------------------
# sig parsing (v1, unchanged — proven)
# ---------------------------------------------------------------------------

def split_params(param_str):
    param_str = param_str.strip()
    if param_str in ('', 'void'):
        return []
    out, depth, cur = [], 0, ''
    for ch in param_str:
        if ch in '([':
            depth += 1
        elif ch in ')]':
            depth -= 1
        if ch == ',' and depth == 0:
            out.append(cur.strip()); cur = ''
        else:
            cur += ch
    if cur.strip():
        out.append(cur.strip())
    return out


def parse_param(p):
    m = re.match(r'^(.*?)([A-Za-z_]\w*)\s*$', p.strip())
    if not m:
        return (p.strip(), None)
    typ, name = m.group(1).strip(), m.group(2)
    if typ == '' and name in ('void', 's32', 'u32', 'int', 's16', 'u16', 's8', 'u8', 'char', 'long'):
        return (name, None)
    return (typ, name)


def parse_sig(sig, fn):
    m = re.match(r'^(.*?)\b' + re.escape(fn) + r'\s*\((.*)\)\s*$', sig.strip(), re.S)
    if not m:
        raise ValueError(f'cannot parse sig: {sig!r}')
    ret = m.group(1).strip()
    params = [parse_param(p) for p in split_params(m.group(2))]
    return ret, params


def cast_uses(body, name, orig_type):
    """Blanket-wrap EVERY body use of `name` in `((orig_type)name)`. Byte-neutral: a cast
    emits no code; at-use casts add no pseudo (v1-proven — cast-locals shift regalloc)."""
    ot = orig_type.strip()
    return re.sub(r'\b' + re.escape(name) + r'\b', '((' + ot + ')' + name + ')', body)


# ---------------------------------------------------------------------------
# v2 draft transforms
# ---------------------------------------------------------------------------

def _uniquify_draft_types(draft, ambient_typedefs, fn):
    """v3.2: strip typedefs IDENTICAL to engine_types.h (use the ambient name); uniquify EVERY
    other draft-DEFINED type name AND struct/union TAG to <name>_<addr>. Type names/tags emit no
    code, so this is byte-neutral — and it makes any two drafts in ONE TU (and a draft vs an
    ambient type) collision-proof (the `redefinition of struct Fr` class when many exemplars bank
    into the same split, T7 M1). Only DEFINED types are touched (a used-but-not-defined
    engine_types.h name like SVECTOR is never renamed)."""
    suffix = '_' + fn.replace('func_', '')
    rename = set()

    def strip_or_mark(m):
        name = m.group(1)
        if name in ambient_typedefs and _norm(ambient_typedefs[name]) == _norm(m.group(0)):
            return ''                          # identical to engine_types.h -> strip, use ambient
        rename.add(name)                       # else uniquify (collision-proof)
        return m.group(0)

    # aggregate typedefs: typedef struct/union [Tag] {...} Name;  (attr-tolerant)
    draft = re.sub(r'typedef\s+(?:struct|union)\s*(?:[A-Za-z_]\w*\s*)?\{[^{}]*(?:\{[^{}]*\}[^{}]*)*\}\s*'
                   r'(?:__attribute__\s*\(\([^()]*(?:\([^()]*\))?[^()]*\)\)\s*)?'
                   r'([A-Za-z_]\w*)\s*;[ \t]*\n?', strip_or_mark, draft)
    # simple/alias/fnptr/array typedefs
    draft = re.sub(r'^[ \t]*typedef\s+[^;{}\n]*?\b([A-Za-z_]\w*)\s*(?:\[[^\]]*\])?\s*;[ \t]*\n?',
                   strip_or_mark, draft, flags=re.M)
    # struct/union TAG definitions (struct Foo { ... }) -> uniquify the tag everywhere
    for tag in set(re.findall(r'\b(?:struct|union)\s+([A-Za-z_]\w*)\s*\{', draft)):
        draft = re.sub(r'\b(struct|union)\s+' + re.escape(tag) + r'\b', r'\1 ' + tag + suffix, draft)
    for name in rename:
        draft = re.sub(r'\b' + re.escape(name) + r'\b', name + suffix, draft)
    return draft


_FN_EXTERN_RE = re.compile(
    r'^[ \t]*extern\s+([^;\n]*?)\b([A-Za-z_]\w*)\s*\(([^;\n]*)\)\s*;[ \t]*(?:/\*[^\n]*\*/)?[ \t]*\n',
    re.M)


def _reconcile_callees(draft, ambient_funcs, fn, visible):
    """v3: per draft extern of a CALLEE —
    * no file-scope decl VISIBLE ABOVE the splice point -> MOVE the decl (verbatim types)
      into the fn body (block scope): private, exact isolation codegen, and legal even if a
      DIFFERENT file-scope decl appears below (the block decl expires at the fn's `}`).
      This is recover_giant.py's proven block-scope idiom, with the DRAFT's types.
    * visible above -> the ambient decl is already in scope: drop the draft's line; when the
      sigs differ, cast every call site to the draft's intended sig (§17a-1, byte-proven)."""
    casts, moved = [], []

    def visit(m):
        ret, name, params = m.group(1).strip(), m.group(2), m.group(3)
        if name == fn:
            return ''                          # the fn's own forward decl: always strip
        if name == 'memcpy':
            return ''                          # TU macros / builtin provide it
        if name not in visible:
            moved.append(_norm(m.group(0).strip()))        # block-scope, verbatim
            return ''
        canon = ambient_funcs.get(name)
        if canon is None or _norm(f'{ret} {name}({params})') == _norm(canon):
            return ''                          # ambient decl serves as-is
        ptypes = [parse_param(p)[0] for p in split_params(params)]
        casts.append((name, ret or 's32', ptypes))
        return ''                              # ambient decl + call-site casts

    draft = _FN_EXTERN_RE.sub(visit, draft)
    for name, dret, ptypes in casts:
        plist = ', '.join(ptypes) if ptypes else ''
        cast = f'(({dret}(*)({plist})){name})'
        draft = _sub_skip_decls(draft, r'\b' + re.escape(name) + r'\s*\(', cast + '(')
    # R32 coverage: every fn-ptr data extern must have been consumed (stripped or block-moved) by
    # visit_fnptr above — never silently emitted verbatim into a TU that declares it differently.
    assert not _FNPTR_DATA_RE.search(draft), \
        'canon_sig_reconcile: a fn-ptr data extern survived _reconcile_data (silent skip = a defect)'
    return draft, moved


def _sub_skip_decls(text, pattern, repl):
    """Apply a blanket use-site substitution but NEVER inside declaration lines
    ('Decl lines are never cast' — cast_call_sites.py; v2.1's decl-cast broke parses)."""
    out = []
    for line in text.split('\n'):
        if re.match(r'\s*(extern|typedef)\b', line):
            out.append(line)
        else:
            out.append(re.sub(pattern, repl, line))
    return '\n'.join(out)


_DATA_EXTERN_RE = re.compile(r'^[ \t]*extern\s+([^;\n()]*?)\s*\b'
                             r'([A-Za-z_]\w*(?:\s*\[[^\]]*\])?(?:\s*,\s*\**[A-Za-z_]\w*(?:\s*\[[^\]]*\])?)*)'
                             r'\s*;[ \t]*(?:/\*[^\n]*\*/)?[ \t]*\n', re.M)

# fn-ptr DATA externs (dispatch tables): `extern void (*D_x[])(void);` / `extern s32 (*D_x)(s32);`.
# _DATA_EXTERN_RE's type class `[^;\n()]*?` forbids the `(`, so it is 100% blind to these (F1, 436
# draft lines) — the class that IS the per-overlay jump-table dispatch arrays jtbl_family_bank banks.
_FNPTR_DATA_RE = re.compile(
    r'^[ \t]*extern\s+[^;\n]*?\(\s*\*\s*([A-Za-z_]\w*)\s*(?:\[[^\]]*\])?\s*\)\s*\([^;]*\)'
    r'\s*;[ \t]*(?:/\*[^\n]*\*/)?[ \t]*\n', re.M)


def _reconcile_data(draft, ambient_data, visible):
    """v3: per data-extern name —
    * not visible above the splice point -> MOVE to block scope with the DRAFT's type
      verbatim (the draft's extern types are load-bearing: %lo-folding, access width and
      alignment all key off the declared type — v2.2's ambient rewrite byte-drifted 18 fns);
    * visible above, identical -> drop; visible + different type -> drop + access-cast the
      uses to the draft's view (alignment caveat: a NARROWER ambient object (u8 vs word)
      makes gcc emit unaligned lwl/lwr through the cast — those land in BYTEDRIFT and route
      to the reconcile_decls/§33 TU-retype tier, not this transform)."""
    casts, moved = [], []

    # v3.3: fn-ptr DATA externs (dispatch tables) FIRST — _DATA_EXTERN_RE below cannot see them.
    # visible -> STRIP (the ambient/engine_core.h decl serves; a call-through `D_x[i]()` is
    # decl-INDEPENDENT indirect codegen, so NO access-cast — casting a fn-ptr would mangle
    # `D_x[i]()` into `((u8*)D_x)[i]()`, the dormant transform the reconcile_decls audit named).
    # not visible -> block-move the draft's decl verbatim (its type is exact + expires at the `}`).
    def visit_fnptr(m):
        name = m.group(1)
        if name not in visible:
            moved.append(_norm(m.group(0).strip()))
        return ''

    draft = _FNPTR_DATA_RE.sub(visit_fnptr, draft)

    def visit(m):
        base = m.group(1).strip()
        # v3.3: bail on a `(` in the CODE, not in a trailing comment — F2: an ordinary scalar extern
        # was silently abandoned because a drafter wrote '(' in prose (87 corpus lines).
        if not base or '(' in m.group(0).split('/*')[0]:
            return m.group(0)
        kept = []
        for piece in m.group(2).split(','):
            piece = piece.strip()
            dm = re.match(r'^(\**)\s*([A-Za-z_]\w*)\s*(\[[^\]]*\])?$', piece)
            if not dm:
                kept.append(piece); continue
            stars, name, arr = dm.group(1), dm.group(2), dm.group(3)
            dtype = base + (' ' + stars if stars else '')
            d_is_arr = arr is not None
            if name not in visible:
                moved.append(f'extern {base} {piece};')    # block-scope, verbatim
                continue
            atype, a_is_arr = ambient_data.get(name, (None, None))
            if atype is None or (_norm(atype) == _norm(dtype) and a_is_arr == d_is_arr):
                continue                       # ambient decl serves as-is
            casts.append((name, dtype, d_is_arr, a_is_arr))
        if kept:
            return f'extern {base} ' + ', '.join(kept) + ';\n'
        return ''

    draft = _DATA_EXTERN_RE.sub(visit, draft)
    for name, dtype, d_is_arr, a_is_arr in casts:
        elem = dtype                            # element/base type of the draft's view
        if d_is_arr or dtype.endswith('*'):
            ptr = (elem.rstrip('* ') + ' *') if d_is_arr else elem
            repl = f'(({_norm(ptr)}){name})' if a_is_arr else f'(({_norm(ptr)})&{name})'
        else:
            repl = f'(*({_norm(dtype)}*){name})' if a_is_arr else f'(*({_norm(dtype)}*)&{name})'
        draft = _sub_skip_decls(draft, r'\b' + re.escape(name) + r'\b', repl)
    return draft, moved


# ---------------------------------------------------------------------------
# main reconcile
# ---------------------------------------------------------------------------

def reconcile(fn, draft, canon_sig=None, tu_path=None):
    amb = tu_ambient(tu_path) if tu_path else dict(funcs={}, data={}, typedefs={})
    vis = visible_above(tu_path, fn) if tu_path else set()

    # 0) v2 #6: scalar typedef dups (common.h) — always strip
    draft = SCALAR_TYPEDEF_RE.sub('', draft)

    # 1) v3.2: strip ambient-identical typedefs; uniquify every other draft-defined type + tag
    draft = _uniquify_draft_types(draft, amb['typedefs'], fn)

    # 1b) v3: callee + data externs (block-scope move / ambient + casts)
    draft, moved_fns = _reconcile_callees(draft, amb['funcs'], fn, vis)
    draft, moved_data = _reconcile_data(draft, amb['data'], vis)
    moved = moved_fns + moved_data

    # locate the definition signature (ret fn(params) {) — search on a comment-masked copy
    # (v3.1: drafts' @stuck headers quote the sig and mis-anchored the rewrite); offsets of
    # the mask apply to the real text.
    dm = None
    for cand in re.finditer(r'(?:^|\n)((?:[A-Za-z_][\w ]*?\*?\s*)\b' + re.escape(fn) + r'\s*\([^;{]*\))\s*\n?\{',
                            _comment_masked(draft)):
        dm = cand                                # last match = the definition
    if not dm:
        raise ValueError(f'no definition of {fn} found in draft')
    draft_sig = dm.group(1)
    dret, dparams = parse_sig(draft_sig, fn)

    # 2) canonical: --sig > TU file-scope decl (incl. engine_core.h) > implicit-int fallback
    canon_sig = canon_sig or amb['funcs'].get(fn)
    if not canon_sig:
        cret, cparams = 's32', [('s32', None)] * len(dparams)
    else:
        cret, cparams = parse_sig(canon_sig, fn)

    # 3) new param list (draft names, canonical types); record type-changed positions
    new_params, changed = [], []
    for i in range(max(len(dparams), len(cparams))):
        dt, dn = dparams[i] if i < len(dparams) else (None, None)
        ct, cn = cparams[i] if i < len(cparams) else (None, None)
        if dt is None:
            new_params.append(f'{ct} _unused{i}'); continue
        if ct is None:
            new_params.append(f'{dt} {dn}' if dn else dt); continue
        ntd, ntc = _norm(dt), _norm(ct)
        if dn is None:
            new_params.append(ct); continue
        new_params.append(f'{ct} {dn}' if not ct.endswith('*') else f'{ct}{dn}')
        if ntc != ntd:
            changed.append((dn, dt))

    new_sig = f'{cret} {fn}(' + ', '.join(new_params) + ')'

    head, body = draft[:dm.start(1)], draft[dm.end(1):]
    if moved:                                   # v3: block-scope decls at body top
        body = body.replace('{', '{\n    ' + '\n    '.join(moved) + '\n', 1)
    for name, orig_type in changed:
        body = _sub_skip_decls(body, r'\b' + re.escape(name) + r'\b',
                               '((' + orig_type.strip() + ')' + name + ')')

    return head + new_sig + body


def main():
    import frozen; frozen.refuse("canon_sig_reconcile.py", "the types phase (Phase 37): one canonical declaration per symbol", "it reconciles declarations against engine_core.h (gone)")  # Phase 35 T6: FROZEN
    ap = argparse.ArgumentParser()
    ap.add_argument('--fn', required=True)
    ap.add_argument('--draft', required=True)
    ap.add_argument('--out', required=True)
    ap.add_argument('--sig', default=None, help='explicit canonical sig (else TU file-scope decl / implicit-int)')
    ap.add_argument('--tu', default=None, help='target TU .c — preprocessed for the REAL file-scope ambient (v2)')
    a = ap.parse_args()
    out = reconcile(a.fn, open(a.draft).read(), a.sig, a.tu)
    os.makedirs(os.path.dirname(a.out), exist_ok=True)
    open(a.out, 'w').write(out)
    amb = tu_ambient(a.tu) if a.tu else dict(funcs={})
    canon = a.sig or amb['funcs'].get(a.fn) or '(implicit-int s32-form)'
    print(f'{a.fn}: reconciled -> {a.out}  [canonical: {canon}]')


if __name__ == '__main__':
    main()
