#!/usr/bin/env python3
"""reconcile_tu.py — conform a draft's DATA declarations to what the TARGET TU can actually SEE.

The successor to `reconcile_decls.py` for the templating/banking path. Two things are wrong with that
tool, and the second is structural, not a typo (Phase-26 session-8 scanner audit):

  1. ITS REGEX IS BLIND TO FUNCTION POINTERS. `DATA_DECL_LINE_RE` wants `extern <type-words> D_x[];`,
     so the `(` in
         extern void (*D_801DA75C)(void);            <- fn-ptr scalar
         extern void (*D_801812A4[])(void *);        <- fn-ptr array (a dispatch table)
     breaks the type run and the line never matches. The tool then SILENTLY SKIPS exactly the symbols
     that are failing and reports success — the classic silent skip. (Blocking func_8017A4AC, 536 ins
     x134 = 287 KB, today.)

  2. ITS ORACLE ASKS THE WRONG QUESTION. It elects a canonical decl by FLEET MAJORITY (engine_core.h
     first-seen, else a plurality vote across all overlays). But this engine is loosely typed: 34.4% of
     fleet symbols carry >= 2 mutually incompatible decl spellings, so a single fleet-wide answer is
     **provably wrong for some TU by construction** — and it is worse than a skip, because it hands back
     an ACTIVELY WRONG decl (measured: 3,717 symbols) that then collides with the very macro it was
     supposed to conform to.

The question is never "what does the fleet call this symbol". It is **"what can THIS TU see"** — because
that, and only that, is what gcc compares the draft's decl against. So:

  * Reconstruct the TU's VISIBLE file-scope decl environment above the insertion point, from BOTH
    sources (the §8c law — a decl can be invisible to any col-0 text scan):
        (a) col-0 `extern ...;` lines in the .c, and
        (b) MACRO-INJECTED externs — a `DEFINE_func_*()` / `SETTER()` / `RETCONST()` invocation expands
            at FILE scope, so its leading `extern`s are genuine file-scope declarations of the invoking
            TU even though they live in engine_core.h (1,801 macros / ~1,462 symbols).
  * If the symbol has NO visible decl -> no conflict is possible; leave the draft's decl alone (and let
    `scope_data_externs` (§8d) demote it, so it establishes no global the TU's own later block-scope
    externs would then have to agree with).
  * If it HAS one and the draft agrees -> nothing to do.
  * If it HAS one and the draft disagrees -> the TU's decl WINS (it is the environment; we are the
    guest). Rewrite the draft's decl to the visible one and CAST AT EVERY USE so the access the draft
    intended is preserved. gcc-2.7.2 folds a compile-time cast of a known symbol, so the emitted bytes
    are unchanged — and the whole-binary byte-gate (G3/P9) remains the sole arbiter either way.

COVERAGE ASSERTION (the rule ratified 2026-07-14: a scanner over the corpus must assert its own
coverage; a silent skip is a DEFECT, not a no-op). Every line in the draft that LOOKS like an extern
declaration of a `D_` symbol must be parsed by one of the forms below. Any that is not is reported
LOUDLY (and `--strict` exits non-zero) instead of being quietly ignored.

Usage:
    from reconcile_tu import fix
    body, notes = fix(body, tu_text, insert_pos, self_fn)

    tools/reconcile_tu.py --body draft.c --tu src/ov_X/ov_X.c --func func_Y [--out out.c] [--strict]
"""
import argparse
import os
import re
import sys

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
ENGINE_CORE = os.path.join(REPO, 'src/shared/engine_core.h')

# ---- the three declaration FORMS a D_ symbol can take -------------------------------------------
# plain data: `extern u8 D_x[];`  `extern struct S D_x;`  `extern s32 *D_x;`
PLAIN_RE = re.compile(
    r'^([ \t]*)extern\s+([A-Za-z_][\w \t]*?)\s*(\*?)\s*\b(D_[0-9A-Fa-f]+)\b\s*(\[[^\]]*\])?\s*;'
    r'[ \t]*(?:/\*.*?\*/)?[ \t]*\\?[ \t]*$')
# fn-ptr scalar: `extern void (*D_x)(void);`   fn-ptr array: `extern void (*D_x[])(void *);`
FNPTR_RE = re.compile(
    r'^([ \t]*)extern\s+([A-Za-z_][\w \t\*]*?)\s*\(\s*\*\s*\b(D_[0-9A-Fa-f]+)\b\s*(\[[^\]]*\])?\s*\)'
    r'\s*\(([^;]*)\)\s*;[ \t]*(?:/\*.*?\*/)?[ \t]*\\?[ \t]*$')
# the COVERAGE ORACLE — deliberately over-approximating: anything that looks like an extern of a D_ sym
CANDIDATE_RE = re.compile(r'^[ \t]*extern\b[^;]*\bD_[0-9A-Fa-f]+\b[^;]*;')
# a macro invocation at file scope, whose expansion injects file-scope externs (§8c)
MACRO_CALL_RE = re.compile(r'^(DEFINE_func_[0-9A-Fa-f]+|SETTER|RETCONST)\s*\(')


def parse_decl(line):
    """-> (sym, decl_text, kind, elem, params) or None.
    kind in {'plain','array','ptr','fnptr','fnarr'}; params only for the fn-ptr kinds."""
    m = FNPTR_RE.match(line)
    if m:
        ret, sym, arr, params = m.group(2), m.group(3), m.group(4), m.group(5)
        return (sym, line.strip().rstrip('\\').strip(),
                'fnarr' if arr else 'fnptr',
                re.sub(r'\s+', ' ', ret).strip(), re.sub(r'\s+', ' ', params).strip())
    m = PLAIN_RE.match(line)
    if m:
        base, star, sym, arr = m.group(2), m.group(3), m.group(4), m.group(5)
        kind = 'array' if arr else ('ptr' if star else 'plain')
        return (sym, line.strip().rstrip('\\').strip(), kind,
                re.sub(r'\s+', ' ', base).strip(), None)
    return None


def _norm(kind, elem, params):
    """Spelling-insensitive identity: int-family aliases are byte-identical to cast between."""
    e = re.sub(r'\b(s32|u32|int|unsigned int|unsigned|long|unsigned long|u_long)\b', 'int', elem or '')
    p = re.sub(r'\b(s32|u32|int|unsigned int|unsigned|long)\b', 'int', params or '')
    return (kind, re.sub(r'\s+', ' ', e).strip(), re.sub(r'\s+', ' ', p).strip())


# ---- the TU-VISIBLE oracle ----------------------------------------------------------------------
_MACRO_EXTERNS = None


def _macro_externs():
    """{macro_name: [extern lines]} — the file-scope decls each engine_core.h macro INJECTS into its
    invoking TU. Invisible to any col-0 scan of the .c, and load-bearing (§8c)."""
    global _MACRO_EXTERNS
    if _MACRO_EXTERNS is not None:
        return _MACRO_EXTERNS
    _MACRO_EXTERNS = {}
    if not os.path.exists(ENGINE_CORE):
        return _MACRO_EXTERNS
    lines = open(ENGINE_CORE).read().splitlines()
    hdr = re.compile(r'^#define\s+(DEFINE_func_[0-9A-Fa-f]+|SETTER|RETCONST)\b')
    i = 0
    while i < len(lines):
        m = hdr.match(lines[i])
        if not m:
            i += 1
            continue
        name, ext, j = m.group(1), [], i
        while j < len(lines):
            s = lines[j].strip().rstrip('\\').strip()
            if s.startswith('extern'):
                ext.append(s if s.endswith(';') else s + ';')
            if not lines[j].rstrip().endswith('\\'):
                break
            j += 1
        _MACRO_EXTERNS.setdefault(name, []).extend(ext)
        i = j + 1
    return _MACRO_EXTERNS


def tu_visible(tu_text, pos):
    """{sym: (decl_text, kind, elem, params)} for every DATA symbol declared at FILE scope ABOVE `pos`.
    Both §8c sources: col-0 externs in the .c, AND the externs injected by macro invocations above pos.
    (All visible decls of one symbol must already be mutually compatible — the TU compiles today — so
    the FIRST one is a sound canonical.)"""
    seen = {}
    macros = _macro_externs()
    for ln in tu_text[:pos].split('\n'):
        cand = None
        mm = MACRO_CALL_RE.match(ln)
        if mm:
            for e in macros.get(mm.group(1), []):
                p = parse_decl(e)
                if p and p[0] not in seen:
                    seen[p[0]] = p[1:]
            continue
        if ln[:1] not in (' ', '\t'):            # col-0 only: block-scope decls are not the environment
            cand = parse_decl(ln)
        if cand and cand[0] not in seen:
            seen[cand[0]] = cand[1:]
    return seen


# ---- the byte-neutral access casts ---------------------------------------------------------------
def _cast_subs(sym, dkind, delem, dparams, ckind):
    """(regex, repl) reproducing the DRAFT's intended access to `sym` under the TU's canonical storage.
    gcc folds a compile-time cast of a known symbol, so the emitted access is unchanged."""
    rx = re.compile(rf'(&?)\b{re.escape(sym)}\b(\s*\[)?')
    c_is_arr = ckind in ('array', 'fnarr')

    if dkind == 'fnptr':                                   # draft: void (*D_x)(P) ; TU: some scalar
        acc = f'((({delem} (*)({dparams})){sym}))'
        return [(rx, lambda m: f'{m.group(1)}{acc}{m.group(2) or ""}')]

    if dkind == 'fnarr':                                   # draft: void (*D_x[])(P) ; TU: scalar/array
        base = f'(({delem} (**)({dparams})){"" if c_is_arr else "&"}{sym})'
        return [(rx, lambda m: f'{m.group(1)}{base}{m.group(2) or ""}')]

    if dkind == 'array':                                   # draft: E D_x[]
        base = f'(({delem} *){"" if c_is_arr else "&"}{sym})'
        return [(rx, lambda m: f'{m.group(1)}{base}{m.group(2) or ""}')]

    # draft: a scalar / struct / pointer -> force the intended width+type via a cast-lvalue
    star = ' *' if dkind == 'ptr' else ''
    acc = f'(*({delem}{star} *)&{sym})'
    return [(rx, lambda m: f'{m.group(1)}{acc}{m.group(2) or ""}')]


def fix(body, tu_text, insert_pos, self_fn=None):
    """Conform the draft's file-scope DATA decls to what the TU can SEE above `insert_pos`.
    Returns (new_body, notes). notes carries the coverage report — UNPARSED lines are DEFECTS."""
    vis = tu_visible(tu_text, insert_pos)
    lines = body.split('\n')

    plan, decl_at, notes = {}, {}, []
    unparsed = []
    for i, ln in enumerate(lines):
        if not CANDIDATE_RE.match(ln):
            continue
        p = parse_decl(ln)
        if not p:
            unparsed.append((i + 1, ln.strip()))            # COVERAGE DEFECT — never silently skip
            continue
        sym, _dtext, dkind, delem, dparams = p
        if sym not in vis:
            continue                                        # no visible decl -> no conflict possible
        cdecl, ckind, celem, cparams = vis[sym]
        if _norm(dkind, delem, dparams) == _norm(ckind, celem, cparams):
            continue                                        # already agrees
        plan[sym] = (cdecl, _cast_subs(sym, dkind, delem, dparams, ckind))
        decl_at[sym] = i
        notes.append(f'{sym}: draft {dkind}({delem}{"/" + dparams if dparams else ""}) '
                     f'-> TU-visible `{cdecl}` + cast at use')

    if unparsed:
        notes.append(f'!! COVERAGE DEFECT: {len(unparsed)} extern line(s) of a D_ symbol did not parse '
                     f'— a silent skip is a defect, not a no-op: ' +
                     '; '.join(f'L{n}: {t[:60]}' for n, t in unparsed[:3]))

    if not plan:
        return body, notes

    out = []
    for i, ln in enumerate(lines):
        sym = next((s for s, j in decl_at.items() if j == i), None)
        if sym is not None:
            indent = re.match(r'^[ \t]*', ln).group(0)
            out.append(indent + plan[sym][0])               # the TU's decl replaces the draft's
            continue
        if CANDIDATE_RE.match(ln):                          # never cast inside another decl line
            out.append(ln)
            continue
        for _s, (_c, subs) in plan.items():
            for rx, rep in subs:
                ln = rx.sub(rep, ln)
        out.append(ln)
    return '\n'.join(out), notes


def main():
    ap = argparse.ArgumentParser(description=__doc__,
                                 formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument('--body', required=True)
    ap.add_argument('--tu', required=True)
    ap.add_argument('--func', required=True)
    ap.add_argument('--out')
    ap.add_argument('--strict', action='store_true', help='exit non-zero on a coverage defect')
    a = ap.parse_args()

    tu = open(a.tu).read()
    m = re.search(rf'INCLUDE_ASM\("[^"]*",\s*{re.escape(a.func)}\);', tu)
    pos = m.start() if m else len(tu)
    new, notes = fix(open(a.body).read(), tu, pos, a.func)
    vis = tu_visible(tu, pos)
    print(f'TU-visible data symbols above the insertion point: {len(vis)} '
          f'({len(_macro_externs())} macros scanned for injected externs)')
    for n in notes:
        print('  ' + n)
    if a.out:
        open(a.out, 'w').write(new)
        print(f'wrote {a.out}')
    if a.strict and any(n.startswith('!!') for n in notes):
        sys.exit(1)


if __name__ == '__main__':
    main()
