#!/usr/bin/env python3
"""macro_draft.py — materialize a `DEFINE_func_XXXX()` macro body as a compilable draft .c

WHY THIS EXISTS (Phase 30 S47)
==============================
`conform_decls.py` needs a **byte-true DEFINITION** to conform the fleet's declarations to, and it
refuses (correctly) when handed a file that holds only a declaration. But for a DEDUPED function the
definition does not live in any .c file at all — it lives inside a `#define DEFINE_func_X() \\ ...`
macro in `src/shared/engine_core.h`, where two things defeat every definition parser:

  * every line ends in a backslash continuation, and
  * the definition line is INDENTED, so `^([A-Za-z_]...)` never matches.

So the single largest class of `conflicting types for func_X` — a deduped callee whose macro-local
`extern` disagrees with the fleet's — was unreachable by the tool built to fix exactly that class.
This bridges the two: it emits the macro body verbatim (dedented, continuations stripped) so the
existing conformer can read the signature it already knows how to read.

VERBATIM IS THE POINT. The draft is evidence, not a rewrite: nothing is reformatted, no types are
"cleaned up". If this file ever starts editing the body it stops being byte-truth (R33/R35).

Usage:
  tools/macro_draft.py --fn func_80128ED8 [--out .run/draft.c]     # default: .run/macro_draft_<fn>.c
"""
import argparse, os, re, sys, textwrap

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
HDR = os.path.join(REPO, "src", "shared", "engine_core.h")


def extract(fn, header=HDR):
    """(body_text, first_line, last_line) of DEFINE_<fn>()'s macro body, 1-indexed; None if absent."""
    lines = open(header, errors="replace").read().split("\n")
    for i, l in enumerate(lines):
        if re.match(rf"\s*#define\s+DEFINE_{re.escape(fn)}\(\)", l):
            j = i
            while j < len(lines) and lines[j].rstrip().endswith("\\"):
                j += 1
            raw = lines[i:j + 1]
            # strip the trailing backslash continuation from every line, drop the #define line
            body = [x.rstrip()[:-1].rstrip() if x.rstrip().endswith("\\") else x for x in raw][1:]
            return textwrap.dedent("\n".join(body)), i + 1, j + 1
    return None


def main():
    ap = argparse.ArgumentParser(description=__doc__,
                                 formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--fn", required=True)
    ap.add_argument("--out")
    ap.add_argument("--header", default=HDR)
    a = ap.parse_args()

    got = extract(a.fn, a.header)
    if not got:
        print(f"macro_draft: no DEFINE_{a.fn}() in {a.header}", file=sys.stderr)
        return 2
    body, lo, hi = got

    # R32: prove the emitted text actually contains a DEFINITION of the requested function, at
    # column 0, where a definition parser can see it. A dedent that leaves it indented is a silent
    # no-op that would surface later as "no DEFINITION" from the conformer.
    if not re.search(rf"^[A-Za-z_][\w \t\*]*\b{re.escape(a.fn)}\s*\(", body, re.M):
        print(f"macro_draft: DEFINE_{a.fn}() body carries no column-0 definition of {a.fn} "
              f"(header lines {lo}-{hi}) — refusing to emit a draft that cannot be parsed",
              file=sys.stderr)
        return 2

    out = a.out or os.path.join(REPO, ".run", f"macro_draft_{a.fn}.c")
    os.makedirs(os.path.dirname(out), exist_ok=True)
    with open(out, "w") as f:
        f.write(f'/* verbatim body of DEFINE_{a.fn}() — {a.header} lines {lo}-{hi} */\n')
        f.write('#include "engine_types.h"\n')
        f.write(body.rstrip() + "\n")
    print(out)
    return 0


if __name__ == "__main__":
    sys.exit(main())
