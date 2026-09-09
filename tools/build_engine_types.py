#!/usr/bin/env python3
"""Extract inline-defined NAMED struct/union types AND typedefs from an overlay .c into a shared header.

Phase 15 / T6 struct follow-up (cookbook §14c); Phase 20 typedef extension (the propagation cap).
The harvest agents defined engine types INLINE in each function's draft. Those bodies then can't be
propagated as engine_core.h macros (two macros defining the same-named type redefine it; a type used in
a shared callee's extern conflicts) — and a function whose body REFERENCES an overlay-local typedef
(`Ent`, `Obj`, …) fails dedup_propagate's compiles_standalone gate in every other overlay, so it stays
LOCAL (no ×134). Scoped finding: the named struct/union types AND the anonymous-struct typedefs in
ov_SC01_077.c have ZERO same-name-different-layout collisions, so each can live ONCE in a shared header
every overlay includes (via engine_core.h), letting the struct/typedef-using shared functions propagate.

This tool collects:
  - every NAMED `struct X {...}` / `union X {...}` definition (brace-matched, document order), and
  - every `typedef ...;` definition — `typedef struct {...} Name;` (anonymous-struct typedef, the
    Phase-20 propagation-cap blocker), `typedef <ret> (*Name)(...);` (fn-ptr), and simple aliases —
and writes a guarded header: forward declarations for the named structs, then the named-struct full
definitions in source order, then the typedefs in source order (a typedef may reference an earlier named
struct or an earlier typedef, e.g. A801593E4 holds an S801593E4*; anonymous-struct typedefs CANNOT be
forward-declared, so this ordering is load-bearing — source order is compile-valid since the source
compiles). With --strip, it also removes those definitions from the source .c (they come from the header
instead) — byte-neutral (type defs emit no code); verify with `make check`.

Usage:
  tools/build_engine_types.py --source ov_SC01_077 --out src/shared/engine_types.h [--strip]
"""
import argparse, glob, os, re, sys

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
NAMED_DEF_RE = re.compile(r'\b(struct|union)\s+([A-Za-z_]\w*)\s*\{')
TYPEDEF_RE = re.compile(r'\btypedef\b')


def blank_comments(text):
    """Same-LENGTH copy of text with /* */ and // comments (and string/char literals) replaced by
    spaces, newlines preserved. find_defs/find_typedefs scan THIS so a `typedef`/`struct` keyword
    inside a comment never matches — the generated header's own comment ('...typedef lift...') was
    scanned to the next ';' and captured `struct vec;` as a bogus `typedef vec`, self-colliding and
    blocking every --strip. Offsets are preserved, so the caller extracts/removes spans from the
    ORIGINAL text unchanged."""
    out = list(text)
    i, n = 0, len(text)
    while i < n:
        c = text[i]
        if c == '/' and i + 1 < n and text[i + 1] == '*':
            j = text.find('*/', i + 2)
            j = n if j == -1 else j + 2
            for k in range(i, j):
                if out[k] != '\n':
                    out[k] = ' '
            i = j
        elif c == '/' and i + 1 < n and text[i + 1] == '/':
            j = text.find('\n', i)
            j = n if j == -1 else j
            for k in range(i, j):
                out[k] = ' '
            i = j
        elif c in '"\'':                      # skip a string/char literal ('/*' inside it is not a comment)
            i += 1
            while i < n and text[i] != c:
                i += 2 if text[i] == '\\' else 1
            i += 1
        else:
            i += 1
    return ''.join(out)


def find_defs(text):
    """Return [(kind, name, start, end)] for each named struct/union DEFINITION, brace-matched.
    end is the index just past the closing '}' (the trailing ';' is consumed separately)."""
    out = []
    for m in NAMED_DEF_RE.finditer(text):
        kind, name = m.group(1), m.group(2)
        i = m.end() - 1  # at the '{'
        depth, j = 0, i
        while j < len(text):
            if text[j] == '{':
                depth += 1
            elif text[j] == '}':
                depth -= 1
                if depth == 0:
                    break
            j += 1
        # consume everything after the closing '}' up to AND INCLUDING the next ';' — this covers
        # a trailing __attribute__((packed, aligned(1))), a typedef alias, or a var name (no ';'
        # occurs inside an attribute list, which uses ','). j is at the closing '}'.
        k = j + 1
        while k < len(text) and text[k] != ';':
            k += 1
        if k < len(text):
            k += 1  # include the ';'
        out.append((kind, name, m.start(), k))
    return out


def typedef_name(body):
    """The defined name of a `typedef ...;` declarator. Handles `typedef struct {...} Name;`,
    `typedef <ret> (*Name)(args);` (fn-ptr), and simple `typedef <type> Name[opt];` aliases."""
    s = body.strip().rstrip(';').rstrip()
    m = re.search(r'\(\s*\*\s*([A-Za-z_]\w*)\s*\)', s)   # fn-ptr declarator: (*Name)
    if m:
        return m.group(1)
    s = re.sub(r'\[[^\]]*\]\s*$', '', s).rstrip()         # drop a trailing array suffix
    m = re.search(r'([A-Za-z_]\w*)\s*$', s)               # the declared name is the last identifier
    return m.group(1) if m else None


def find_typedefs(text):
    """Return [(name, body, start, end)] for each `typedef ...;` definition. Brace-aware: the
    terminating ';' is the one at brace-depth 0, so `typedef struct {...} Name;` is captured whole."""
    out = []
    for m in TYPEDEF_RE.finditer(text):
        i, depth, end = m.end(), 0, None
        while i < len(text):
            c = text[i]
            if c == '{':
                depth += 1
            elif c == '}':
                depth -= 1
            elif c == ';' and depth == 0:
                end = i + 1
                break
            i += 1
        if end is None:
            continue
        body = text[m.start():end]
        name = typedef_name(body)
        if name:
            out.append((name, body, m.start(), end))
    return out


def resolve_type_defs(text):
    """THE type-definition model, shared by every caller (R33: one model, not one per tool).

    Returns (defs, tdefs, carried, partial):
      defs     [(kind, name, s, e)]        named struct/union defs NOT carried by a typedef
      tdefs    [(name, body, s, e)]        typedef defs (a TAGGED typedef carries its struct body)
      carried  [(kind, tag, alias)]        tags whose body a typedef carries -> forward-declare,
                                           never lift or strip independently
      partial  [(kind, name, s, e)]        genuinely malformed partial overlaps (caller decides)

    THE INVARIANT THIS EXISTS TO PROVIDE: the spans in `defs` and `tdefs` are pairwise DISJOINT.

    A `typedef struct Tag {...} Alias;` is matched by BOTH finders, with the struct span CONTAINED
    in the typedef span. A caller that treats those as two independent types does three wrong
    things at once, all of which were observed (Phase 29):
      1. it lifts the inner span, which starts at `struct` — so the emitted text is
         `struct Tag {...} Alias;`, a *variable definition* of Alias in every TU that includes it;
      2. it then lifts the typedef too -> `Alias redeclared as different kind of symbol`;
      3. it strips both spans highest-first, so the outer span's end offset is STALE by the length
         of the inner one and the second delete removes that many EXTRA characters past its
         intended end -- silently corrupting whatever followed (a declaration losing its `extern`
         and becoming a tentative definition, two declarations splicing together).
    Measured on this fleet: 13 such tag/alias pairs, 6,142 occurrences, and 0 of those tags is
    ever defined standalone -- so folding the tag into its typedef is always the correct read.

    A CONTAINED def is therefore folded (the typedef already carries the body, and carries the tag
    with it when the typedef is written tagged). Only a PARTIAL overlap is genuinely malformed.
    """
    scan = blank_comments(text)                       # scan comment-blanked; extract from `text`
    defs = find_defs(scan)
    tdefs = [(name, text[s:e], s, e) for name, _b, s, e in find_typedefs(scan)]
    carried, contained = [], []
    for d in defs:
        for tn, _tb, ts, te in tdefs:
            if ts <= d[2] and d[3] <= te:             # struct span inside the typedef span
                carried.append((d[0], d[1], tn))
                contained.append(d)
                break
    partial = [d for d in defs
               if any(ts < d[3] and d[2] < te for _, _, ts, te in tdefs) and d not in contained]
    defs = [d for d in defs if d not in contained and d not in partial]
    return defs, tdefs, carried, partial


def _visible_headers(_cache=[]):
    """Basenames of the shared headers that make engine_types.h visible, DERIVED by reading the
    include graph in src/shared (R33) rather than hardcoding 'engine_core.h'."""
    if _cache:
        return _cache[0]
    want = {'engine_types.h'}
    changed = True
    while changed:
        changed = False
        for h in glob.glob(os.path.join(REPO, 'src/shared/*.h')):
            base = os.path.basename(h)
            if base in want:
                continue
            incs = {os.path.basename(i)
                    for i in re.findall(r'#include\s+"([^"]+)"', open(h).read())}
            if incs & want:
                want.add(base)
                changed = True
    _cache.append(want)
    return want


def type_visible(path):
    """True iff this TU can SEE engine_types.h. Stripping a type definition out of a TU that
    cannot see the shared replacement does not consolidate it — it deletes it. The symptom is
    three steps removed from the cause: the type goes undeclared, the next declaration hits
    `parse error` / `data definition has no type or storage class`, gcc falls back to implicit
    int, and that TENTATIVE definition collides at LINK as `multiple definition of <sym>` — a
    link error that names a data symbol nobody touched. Measured: exactly one TU in this fleet
    (ov_SC01_077_o0.c, the -O0 split) deliberately omits engine_core.h, and it is the one that
    broke. So visibility is CHECKED, never assumed."""
    incs = {os.path.basename(i)
            for i in re.findall(r'#include\s+"([^"]+)"', open(path).read())}
    return bool(incs & _visible_headers())


def assert_disjoint(spans, where=''):
    """R32 guard: the spans deleted from ONE file must be pairwise disjoint, or the strip corrupts
    the file. Deleting overlapping spans highest-first leaves the earlier span's end offset stale,
    so the next delete removes len(overlap) EXTRA characters past its intended end. `git status`
    still looks clean and the per-binary gate can still pass, which is exactly why this must be an
    assertion and not a code comment. Returns the spans sorted; raises on any overlap."""
    ordered = sorted(spans)
    for (s1, e1), (s2, e2) in zip(ordered, ordered[1:]):
        if s2 < e1:
            raise ValueError(f'[R32] overlapping strip spans in {where}: ({s1},{e1}) overlaps '
                             f'({s2},{e2}) — refusing to write. Spans must come from '
                             f'resolve_type_defs(), which folds contained tagged typedefs.')
    return ordered


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('--source', default='ov_SC01_077')
    ap.add_argument('--file', default=None,
                    help='explicit repo-relative source .c to lift from (overrides --source path; use for '
                         'the overlay SPLIT files, e.g. src/ov_SC01_077/ov_SC01_077_after.c, whose local '
                         'types the base-only --source lift cannot reach). Additive-merges into --out.')
    ap.add_argument('--out', default='src/shared/engine_types.h')
    ap.add_argument('--strip', action='store_true', help='also remove the defs from the source .c')
    ap.add_argument('--exclude', default=None,
                    help='comma-separated type NAMES to leave TU-local (neither lift nor strip). Use for a '
                         'type whose same name has a DIFFERENT layout in a sibling split TU (e.g. Buf differs '
                         'between _a.c and _after.c) — lifting it fleet-wide would `conflicting types` the other TU.')
    args = ap.parse_args()

    c_path = os.path.join(REPO, args.file) if args.file else os.path.join(REPO, f'src/{args.source}/{args.source}.c')
    out_path = os.path.join(REPO, args.out)
    text = open(c_path).read()
    # The def/typedef model — including the tagged-typedef containment resolution documented
    # below — lives in resolve_type_defs() so lift_types.py shares it EXACTLY (R33: one model,
    # two callers; lift_types carrying its own copy is what produced the Phase-29 corruption).
    defs, tdefs, carried, partial = resolve_type_defs(text)
    if args.exclude:                                   # leave these TU-local (cross-TU same-name conflicts)
        excl = set(x.strip() for x in args.exclude.split(',') if x.strip())
        defs = [d for d in defs if d[1] not in excl]
        tdefs = [t for t in tdefs if t[0] not in excl]
    if not defs and not tdefs:
        sys.exit('no named struct/union/typedef defs found')

    # A `typedef struct Tag {...} Alias;` is matched by BOTH finders (overlapping spans), and lifting or
    # stripping both would corrupt the source. The old guard therefore sys.exit'd on ANY overlap, with the
    # comment "our source has only ANONYMOUS-struct typedefs (no tag)".
    #
    # That was true in Phase 20 and is now false: the harvest agents write their guessed overlay-local
    # structs in the TAGGED form. MEASURED (Phase 26-A audit, CRITICAL): 1,929 tagged typedefs, in
    # **573 of the 709 type-bearing overlay .c (81%), across all 134 overlays** — so this tool hard-exits
    # on four fifths of its own corpus. And inject_capped_externs routes every type-bearing body HERE as
    # the type-heavy tail's ONLY sanctioned unblocker (§28b). This is the "3,098 type-heavy tail" and the
    # 9 zero-bank type-using families.
    #
    # It went unfixed for the most instructive reason in the whole audit: it FAILS LOUD. It was never a
    # silent skip — it printed "[overlap] ... handle manually" every time. But the message reads like a
    # rare edge case rather than an 81% coverage failure, so nobody measured it. A loud failure nobody
    # counts is as invisible as a silent one.
    #
    # The guard is simply over-conservative. A CONTAINED def (the typedef's span encloses the struct body)
    # is perfectly liftable — the typedef already carries the body; it just must not be counted twice.
    # Only a PARTIAL overlap is the malformed case the guard was actually written for.
    if partial:
        sys.exit(f'[overlap] {len(partial)} PARTIAL def/typedef span overlap(s) — genuinely malformed, '
                 f'handle manually: {[d[1] for d in partial[:5]]}')
    # the typedef carries the body -> do not lift or strip it a second time. Emit a `struct Tag;`
    # forward decl for each so pointer-only references to the tag still resolve. (resolve_type_defs
    # has already removed them from `defs`.)
    tagged_fwd = sorted({(k, n) for k, n, _ in carried})
    if tagged_fwd:
        print(f'[types] {len(carried)} tagged-struct typedef(s) folded into their typedef '
              f'(forward-declared): {[n for _, n in tagged_fwd[:6]]}')

    # dedup named structs by (kind, name); keep first (scoped check already proved 0 layout collisions)
    seen, ordered = set(), []
    for kind, name, s, e in defs:
        key = (kind, name)
        body = text[s:e]
        if key in seen:
            continue
        seen.add(key)
        ordered.append((kind, name, body))

    # dedup typedefs by name; a same-name-DIFFERENT-body pair is a real collision (the source would
    # not compile with two conflicting ones, so this only fires on a malformed source or the merge).
    tseen, tordered = {}, []
    for name, body, s, e in tdefs:
        norm = re.sub(r'\s+', ' ', body.strip())
        if name in tseen:
            if tseen[name] != norm:
                sys.exit(f'[collision] typedef {name} has two different definitions in the source')
            continue
        tseen[name] = norm
        tordered.append((name, body))

    # ADDITIVE merge: keep the types already in the existing header so a re-run after a prior
    # --strip does NOT drop earlier migrations. The header is the cumulative record; the source
    # only ever holds the NEW inline defs (the older ones were stripped in a previous pass).
    # Existing header types keep their (compile-valid) order; new source types append after.
    if os.path.exists(out_path):
        htext = open(out_path).read()
        hscan = blank_comments(htext)                 # comment-blanked scan of the existing header too
        existing = [(k, n, htext[s:e]) for k, n, s, e in find_defs(hscan)]
        merged, mseen = [], set()
        for kind, name, body in existing + ordered:
            if (kind, name) in mseen:
                continue
            mseen.add((kind, name))
            merged.append((kind, name, body))
        ordered = merged
        # the same additive + collision-checked merge for typedefs (header-first, then new source)
        existing_td = [(n, htext[s:e]) for n, _b, s, e in find_typedefs(hscan)]
        merged_td, mtseen = [], {}
        for name, body in existing_td + tordered:
            norm = re.sub(r'\s+', ' ', body.strip())
            if name in mtseen:
                if mtseen[name] != norm:
                    sys.exit(f'[collision] typedef {name} differs between header and source')
                continue
            mtseen[name] = norm
            merged_td.append((name, body))
        tordered = merged_td

    guard = 'BFM_ENGINE_TYPES_H'
    out = [f'#ifndef {guard}', f'#define {guard}',
           '/* src/shared/engine_types.h — shared engine struct/union types + typedefs (Phase 15 §14c,',
           ' * Phase 20 typedef lift). Generated by tools/build_engine_types.py from the matched bodies',
           ' * in the source overlay. Defined ONCE here (0 same-name-different-layout collisions) so the',
           ' * struct/typedef-using shared functions share fleet-wide through the per-function headers under src/shared/ (Phase 35). Included by',
           ' * common.h consumers. */',
           '#include "common.h"', '']
    # forward decls first (lets pointer-only references resolve regardless of order)
    for kind, name, _ in ordered:
        out.append(f'{kind} {name};')
    # ...including the TAGGED structs whose body is carried by their own typedef below (Phase 26-A).
    # The body is emitted once, by the typedef; the tag still needs a forward decl so a pointer-only
    # reference (`struct Tag *p;`) resolves.
    for kind, name in tagged_fwd:
        out.append(f'{kind} {name};')
    out.append('')
    # full named-struct definitions in source order (source order is compile-valid for by-value nesting)
    for kind, name, body in ordered:
        out.append(body if body.rstrip().endswith(';') else body + ';')
        out.append('')
    # typedefs last, in source order (a typedef may reference an earlier named struct or an earlier
    # typedef; anonymous-struct typedefs can't be forward-declared, so the ordering is load-bearing)
    for name, body in tordered:
        out.append(body if body.rstrip().endswith(';') else body + ';')
        out.append('')
    out.append(f'#endif /* {guard} */')
    os.makedirs(os.path.dirname(out_path), exist_ok=True)
    open(out_path, 'w').write('\n'.join(out) + '\n')
    print(f'wrote {args.out}: {len(ordered)} named types + {len(tordered)} typedefs '
          '(forward decls + defs, source order)')

    if args.strip:
        # remove the def spans (named structs + typedefs) from the source, last-first to keep offsets
        # valid. resolve_type_defs() folds contained spans so these are disjoint — ASSERTED, not
        # assumed (R32): an overlap here silently over-deletes past the span's end.
        spans = assert_disjoint([(s, e) for _, _, s, e in defs] + [(s, e) for _, _, s, e in tdefs],
                                where=c_path)[::-1]
        new = text
        for s, e in spans:
            new = new[:s] + new[e:]
        # collapse the blank-line runs the removals leave
        new = re.sub(r'\n[ \t]*\n[ \t]*\n+', '\n\n', new)
        open(c_path, 'w').write(new)
        print(f'stripped {len(spans)} struct/union/typedef defs from {args.source}.c (verify byte-identical)')


if __name__ == '__main__':
    main()
