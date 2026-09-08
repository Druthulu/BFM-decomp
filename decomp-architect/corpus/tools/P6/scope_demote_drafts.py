#!/usr/bin/env python3
"""scope_demote_drafts.py — the §8d scope-demote, as a gate-ladder rung.  (P31 S67, W3a)

THE GAP THIS CLOSES.  `scope_data_externs.fix()` is byte-proven and already used by the FAMILY
lanes (`family_sweep`, `bank_exemplar`, `jtbl_family_bank`) — but nothing in `gate_stage`'s recovery
ladder ever called it, so a draft written by a wave AGENT never saw it.  The S66 free-wins audit
measured the cost: of 193 stranded drafts, 89 die in cc1, and 74 of those die on `conflicting types`
— the exact error §8d exists to remove.  One byte-proven instance from that audit:
`ov_SC04_018:func_80181270`, whose fix() output goes straight to an rtu MATCH with no hand edit.

WHAT IT DOES.  For each draft in `--in`, demote the file-scope DATA externs the target TU does not
already declare at file scope down to block scope (and auto-alias a decl whose type disagrees with
the TU's).  A loosely-typed engine declares one symbol several incompatible ways across a TU, and C
tolerates that at BLOCK scope while rejecting it at file scope — so the draft must not establish a
global the TU never had.  See scope_data_externs' own docstring for the byte-proven asymmetry.

WHY A SEPARATE TOOL rather than a branch inside an existing rung: the ladder's contract is
"a no-op-safe draft-dir -> draft-dir rewrite, and the whole-binary byte-gate is the sole arbiter"
(G3/P9).  A rung that can only ever delete a conflicting global or leave the draft untouched fits
that contract exactly, and keeping it separate means the gate's own `_xform` clears its output dir
and can drop the rung with one line if it ever regresses a bank.

TU RESOLUTION IS DERIVED, NEVER ASSUMED (the `tu_for` lesson): the draft's home TU comes from the
corpus' INCLUDE_ASM line, so a draft that lands in a `_jr_<ADDR>` / `_o0` carve file is reconciled
against the file that will actually compile it.

    tools/scope_demote_drafts.py --overlay ov_SC04_018 --in .run/d --out .run/d-sd
"""
import argparse
import glob
import os
import re
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
REPO = os.path.dirname(HERE)
sys.path.insert(0, HERE)

import cdecl                       # noqa: E402  the coverage-asserting decl parser
import corpus                      # noqa: E402
import scope_data_externs as SDE                        # noqa: E402  its decl-text reader
from scope_data_externs import fix as scope_data_fix   # noqa: E402  §8d, one definition (R33)

_TU_DATA_TYPES = {}


def _tu_data_types(tu_path):
    """{D_sym -> declared type text} AS CC1 SEES IT (cdecl.tu_scope, i.e. cpp), cached per TU.

    Same call family_sweep makes (its `_tu_data_types`), for the same reason: a text scan cannot see
    a MACRO-INJECTED declaration, and that is exactly where these conflicts live — `extern Vec8
    D_80114F24;` sits inside a DEFINE_func_* macro body in engine_core.h while the overlay .c holds
    only `DEFINE_func_XXXX()`.  The FULL scope is the right question (compatibility is order-
    independent in C), not the `above=` visibility form."""
    if tu_path not in _TU_DATA_TYPES:
        try:
            sc = cdecl.tu_scope(tu_path)
            _TU_DATA_TYPES[tu_path] = {n: SDE._decl_type_text(d.text or "", n)
                                       for n, d in sc.items()
                                       if n.startswith("D_") and d.text
                                       and SDE._decl_type_text(d.text or "", n)}
        except Exception as e:                    # loud, never fatal (R32)
            print("  [tu-types] %s: %s" % (tu_path, repr(e)[:80]), flush=True)
            _TU_DATA_TYPES[tu_path] = {}
    return _TU_DATA_TYPES[tu_path]


def tu_for(binary, fn, override=None):
    """The TU this draft will be spliced into — derived from the corpus, never defaulted.

    A CorpusError PROPAGATES: falling back to `src/<bin>/<bin>.c` on an oracle failure is how the
    recovery passes ended up reconciling against a different translation unit than the one that
    compiles the code (see cast_call_sites.tu_for)."""
    if override:
        return override if os.path.isabs(override) else os.path.join(REPO, override)
    try:
        addr = int(fn[5:], 16)
    except ValueError:
        return os.path.join(REPO, "src/%s/%s.c" % (binary, binary))
    st = corpus.stubs(binary).get(addr)
    if st is None:
        return None
    return os.path.join(REPO, st.path)


def _stub_pos(tu_text, fn):
    """Char offset of this function's INCLUDE_ASM stub — the splice point fix() measures from."""
    m = re.search(r'INCLUDE_ASM\("[^"]*",\s*%s\);' % re.escape(fn), tu_text)
    return m.start() if m else None


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--overlay", required=True, help="the binary these drafts belong to")
    ap.add_argument("--in", dest="indir", required=True)
    ap.add_argument("--out", dest="outdir", required=True)
    ap.add_argument("--src-file", dest="src_file", default=None,
                    help="force the target TU (default: derived per draft from the corpus)")
    ap.add_argument("-v", "--verbose", action="store_true")
    a = ap.parse_args()

    os.makedirs(os.path.join(REPO, a.outdir), exist_ok=True)
    drafts = touched = moved_total = 0
    no_tu = no_stub = 0
    for p in sorted(glob.glob(os.path.join(REPO, a.indir, "*.c"))):
        fn = os.path.basename(p)[:-2]
        body = open(p).read()
        out_body = body
        tu = tu_for(a.overlay, fn, a.src_file)
        if tu and os.path.exists(tu):
            tu_text = open(tu).read()
            pos = _stub_pos(tu_text, fn)
            if pos is None:
                # Already spliced, or a curated name — nothing to measure "above" from.  Carry the
                # draft through unchanged rather than guessing a position (R43: a rung that cannot
                # handle an input passes it on intact; it never half-transforms it).
                no_stub += 1
            else:
                # cdecl.tu_scope sees MACRO-INJECTED file-scope decls (`extern Vec8 D_x;` inside a
                # DEFINE_func_* body in engine_core.h) that a text scan cannot; fix() falls back to
                # its own text scan when this is absent.
                tu_types = _tu_data_types(tu)
                new, mv = scope_data_fix(body, tu_text, pos, fn, tu_types)
                out_body = new
                if new != body:
                    touched += 1
                    moved_total += len(mv)
                    if a.verbose:
                        print("  %s: demoted %d  %s" % (fn, len(mv), mv))
        else:
            no_tu += 1
        open(os.path.join(REPO, a.outdir, os.path.basename(p)), "w").write(out_body)
        drafts += 1

    # R32: the denominators.  A rung that transforms 0 of N must say so — "no-op" and "never ran"
    # are indistinguishable in a gate log otherwise, and that ambiguity is what this ladder exists
    # to remove.
    print("scope-demote: drafts %d · rewritten %d · symbols demoted %d · no-TU %d · no-stub %d"
          % (drafts, touched, moved_total, no_tu, no_stub))
    return 0


if __name__ == "__main__":
    sys.exit(main())
