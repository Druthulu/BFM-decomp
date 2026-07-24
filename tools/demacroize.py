#!/usr/bin/env python3
"""demacroize.py — the per-overlay-local escape from a shared-header self-decl conflict.

THE BLOCKER.  A byte-correct draft for `func_X` fails the whole-binary gate with
`conflicting types for func_X`, because a `DEFINE_func_*` macro in `src/shared/engine_core.h`
forward-declares `func_X` with a caller-derived signature the byte-true definition cannot
satisfy (typically `void` where the real return is live).  This is the single largest stranded
class.

WHY THE OBVIOUS FIXES ARE WRONG.
  * Rewriting the DRAFT to the header's signature compiles but byte-MISMATCHes — the body
    genuinely needs its own signature (§20; §58b: forcing a `void` return dropped the return
    computation).  The draft is byte-truth; the header decl is a stub-era guess.
  * Rewriting the SHARED HEADER decl (`fix_header_decl`) is fleet-blind: it passed the
    per-binary gate on 3 of 3 and then failed R22 139/140, because that decl reaches ~137 other
    overlays where those functions are ALREADY matched and a caller's codegen shifts under the
    widened declaration (§63 UPDATE).  Off-limits.

THE ESCAPE.  The conflicting `extern` lives INSIDE the macro BODY, so it only exists where the
macro is INSTANTIATED.  Replacing that instantiation, in this overlay's own TU, with the macro's
own expansion — with only the conflicting declaration corrected to the draft's byte-true
signature — dissolves the conflict while writing nothing outside `src/<binary>/`.  Every other
overlay is textually untouched, so no R22 risk is created by construction.  This is the
"per-overlay-local decl" §63's own note named as the unexplored alternative.

THE PRICE, STATED HONESTLY.  The de-macroized function can no longer be propagated ×138 from the
shared macro (`dedup_propagate` would re-macroize it).  A bank recovered this way is ×1: it
credits the FULL distinct-code unit (progress.py marks an h_exact class matched if ANY instance
is) but only ~1/138 of the instruction-weighted headline.

CAVEAT (why --apply must still be byte-gated).  The macro's own function is ALREADY matched in
this binary.  Correcting the declaration it sees can shift ITS codegen — the §63 failure mode,
relocated somewhere the per-binary gate can actually see it.  The whole-binary byte-gate is the
arbiter (G3/P9); this tool only prepares the edit.

  tools/demacroize.py --binary ov_SC07_006 --fn func_8012CC88 --draft <draft.c> --emit-edits
  tools/demacroize.py --binary ov_SC07_006 --fn func_8012CC88 --draft <draft.c> --apply
"""
import argparse, os, re, sys

HERE = os.path.dirname(os.path.abspath(__file__))
REPO = os.path.dirname(HERE)
sys.path.insert(0, HERE)
import cdecl
import corpus

ENGINE_CORE = 'src/shared/engine_core.h'


def macro_bodies(header=ENGINE_CORE):
    """{macro: body_text} for every DEFINE_func_* in the shared header (continuations joined)."""
    text = open(os.path.join(REPO, header), errors='replace').read()
    out = {}
    for m in re.finditer(r'^#define\s+(DEFINE_func_[0-9A-Fa-f]+)\s*\(\s*\)', text, re.M):
        i, body = text.find('\n', m.end()), []
        if i < 0:
            continue
        i += 1
        while i < len(text):
            nl = text.find('\n', i)
            line = text[i:nl] if nl >= 0 else text[i:]
            body.append(line.rstrip().rstrip('\\').rstrip())
            if not line.rstrip().endswith('\\') or nl < 0:
                break
            i = nl + 1
        out[m.group(1)] = '\n'.join(body)
    return out


def draft_decl(fn, draft_text):
    """`extern <byte-true sig>;` reconstructed from the draft's own definition (cdecl renders it,
    so the spelling is canonical rather than copied source text)."""
    for d in cdecl.declarations(cdecl.split_statements(draft_text), path='<draft>'):
        if d.name == fn and d.is_definition:
            return d.declaration(storage='extern')
    raise SystemExit('demacroize: no definition of %s in the draft' % fn)


def plan(binary, fn, draft_text):
    """[(macro, old_instantiation, new_expansion)] — every macro instantiated in fn's home TU
    whose body declares fn incompatibly with the draft's definition."""
    stub = {s.symbol: s for s in corpus.stubs(binary).values()}.get(fn)
    if stub is None:
        raise SystemExit('demacroize: %s is not an INCLUDE_ASM stub in %s (already banked?)' % (fn, binary))
    tu_path = os.path.join(REPO, stub.path)
    tu_text = open(tu_path, errors='replace').read()
    want = draft_decl(fn, draft_text)
    want_d = cdecl.parse(want)[0]

    out = []
    for macro, body in sorted(macro_bodies().items()):
        if not re.search(r'\b%s\s*\(\s*\)' % re.escape(macro), tu_text):
            continue                                     # not instantiated in THIS TU
        hit = None
        for stmt in re.findall(r'\bextern\b[^;{}]*;', body):
            try:
                ds = cdecl.parse(stmt)
            except cdecl.CDeclError:
                continue
            for d in ds:
                if d.name == fn and not (cdecl.compatible(d, want_d) and cdecl.compatible(want_d, d)):
                    hit = stmt
        if hit is None:
            continue
        # Correct ONLY the conflicting declaration; never DROP it (§57a correction 1 — dropping a
        # decl breaks the def-after-caller order the caller relies on).
        out.append((macro, stub, hit, body.replace(hit, want, 1)))
    return tu_path, out


def main():
    ap = argparse.ArgumentParser(description=__doc__,
                                 formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument('--binary', required=True)
    ap.add_argument('--fn', required=True)
    ap.add_argument('--draft', required=True)
    g = ap.add_mutually_exclusive_group(required=True)
    g.add_argument('--emit-edits', action='store_true', help='print //@EDIT lines for rtu_match (read-only)')
    g.add_argument('--apply', action='store_true', help='rewrite the TU in place (T1; byte-gate after)')
    a = ap.parse_args()

    draft_text = open(a.draft, errors='replace').read()
    tu_path, items = plan(a.binary, a.fn, draft_text)
    if not items:
        print('demacroize: nothing to do for %s (no instantiated macro declares it incompatibly)' % a.fn)
        return 1

    if a.emit_edits:
        for macro, _stub, _old, new in items:
            # rtu_match applies these to the TU before splicing; \n is unescaped there.
            print('//@EDIT %s()||%s' % (macro, new.replace('\\', '\\\\').replace('\n', '\\n')))
        print('// %d macro instantiation(s) in %s' % (len(items), os.path.relpath(tu_path, REPO)),
              file=sys.stderr)
        return 0

    text = open(tu_path, errors='replace').read()
    for macro, _stub, _old, new in items:
        pat = re.compile(r'^([ \t]*)%s\(\s*\)' % re.escape(macro), re.M)
        if not pat.search(text):
            raise SystemExit('demacroize: instantiation of %s not found for in-place edit' % macro)
        text = pat.sub(lambda m: '%s/* de-macroized: per-overlay-local decl for %s (byte-true sig); '
                                 'do NOT re-macroize */\n%s' % (m.group(1), a.fn, new), text, count=1)
    open(tu_path, 'w').write(text)
    print('demacroize: expanded %d macro(s) in %s for %s'
          % (len(items), os.path.relpath(tu_path, REPO), a.fn))
    return 0


if __name__ == '__main__':
    sys.exit(main())
