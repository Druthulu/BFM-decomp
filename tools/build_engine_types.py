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
import argparse, os, re, sys

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


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('--source', default='ov_SC01_077')
    ap.add_argument('--out', default='src/shared/engine_types.h')
    ap.add_argument('--strip', action='store_true', help='also remove the defs from the source .c')
    args = ap.parse_args()

    c_path = os.path.join(REPO, f'src/{args.source}/{args.source}.c')
    out_path = os.path.join(REPO, args.out)
    text = open(c_path).read()
    scan = blank_comments(text)                       # scan comment-blanked; extract from `text`
    defs = find_defs(scan)
    tdefs = [(name, text[s:e], s, e) for name, _b, s, e in find_typedefs(scan)]
    if not defs and not tdefs:
        sys.exit('no named struct/union/typedef defs found')

    # safety: a `typedef struct Tag {...} Alias;` would be matched by BOTH finders (overlapping spans),
    # and stripping both corrupts the source. Our source has only ANONYMOUS-struct typedefs (no tag),
    # so assert no overlap rather than silently corrupt; a future tagged-struct typedef errors loudly.
    for _, _, ds, de in defs:
        for _, _, ts, te in tdefs:
            if ds < te and ts < de:
                sys.exit('[overlap] a tagged-struct typedef matched both finders — handle manually')

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
           ' * struct/typedef-using shared functions propagate fleet-wide via engine_core.h. Included by',
           ' * common.h consumers. */',
           '#include "common.h"', '']
    # forward decls first (lets pointer-only references resolve regardless of order)
    for kind, name, _ in ordered:
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
        # valid. The overlap guard above guarantees these spans are disjoint.
        spans = sorted([(s, e) for _, _, s, e in defs] + [(s, e) for _, _, s, e in tdefs],
                       key=lambda t: t[0], reverse=True)
        new = text
        for s, e in spans:
            new = new[:s] + new[e:]
        # collapse the blank-line runs the removals leave
        new = re.sub(r'\n[ \t]*\n[ \t]*\n+', '\n\n', new)
        open(c_path, 'w').write(new)
        print(f'stripped {len(spans)} struct/union/typedef defs from {args.source}.c (verify byte-identical)')


if __name__ == '__main__':
    main()
