#!/usr/bin/env python3
"""audit_text_sources.py — every tracked C source must be TEXT, or grep silently skips it.

WHY THIS EXISTS (P30 SESSION-28, found the hard way). `src/ov_SC01_077/ov_SC01_077_o0.c` carried a
RAW NUL byte inside a character literal — the source read `== '<NUL>'` where it should have read
`== '\\0'`. It compiled fine (the fleet was byte-identical), so no byte-gate ever objected. But
`file(1)` classified it as `data`, and **grep treats a file containing NUL as BINARY and reports
nothing** — silently. So:

  * `grep -rn func_8013C08C src/` found NOTHING, for a function that is defined right there;
  * every grep-based audit or hand-search over `src/` skipped the whole file, invisibly;
  * an investigation into "why does this family not propagate" burned real time chasing a
    phantom missing function before `file` gave it away.

That is the SAME silent-skip class as §124 (a scanner that cannot see something reports it is not
there) — one level lower, in the tooling everyone reaches for first. The byte-gate is structurally
blind to it (R34): the bytes are correct, so it has nothing to say. It needs its own oracle.

R32: this asserts COVERAGE (every candidate file was classified) and fails on the gap, rather than
scanning until it happens to find something.

SECOND CLASS — PORTABLE INCLUDES (P33 B2, the public flip). The build's only include path is
`-Iinclude` (no system headers, no Sony headers), so every `#include` in `src/` and `include/` must
resolve inside the repository, relative to the including file or under include/. 34 lines in 19
overlay sources carried `#include "/home/musashi/bfm-decomp/src/shared/engine_core.h"` — byte-neutral
here (same header text), a hard build failure on any other machine, and invisible to the byte-gate
for the same reason the NUL was (R34). Offenders: an absolute path, an angle-bracket include
(nothing on the include path is a system header), or a quoted include that resolves outside the
repo / to no file. Controls (R39): 34 offenders in 19 files before the fix, 0 after.
"""
import os
import re
import sys

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
ROOTS = ("src", "include")
EXTS = (".c", ".h")
INCLUDE_DIR = os.path.join(REPO, "include")
_INCLUDE_RE = re.compile(rb'^\s*#\s*include\s*([<"])([^>"]+)[>"]')


def include_offenders(p, data):
    """[(reason)] for every non-portable #include in one source (see the docstring)."""
    out = []
    here = os.path.dirname(p)
    for ln_no, line in enumerate(data.split(b"\n"), 1):
        m = _INCLUDE_RE.match(line)
        if not m:
            continue
        kind, target = m.group(1), m.group(2).decode("utf-8", "replace")
        if kind == b"<":
            out.append(f"line {ln_no}: angle-bracket include <{target}> (no system/SDK header is on the include path)")
            continue
        if target.startswith("/"):
            out.append(f"line {ln_no}: ABSOLUTE include \"{target}\" (breaks every other machine)")
            continue
        cands = [os.path.normpath(os.path.join(here, target)), os.path.normpath(os.path.join(INCLUDE_DIR, target))]
        hit = next((c for c in cands if os.path.isfile(c)), None)
        if hit is None:
            out.append(f"line {ln_no}: unresolvable include \"{target}\" (not relative to the file, not under include/)")
        elif not (hit + os.sep).startswith(REPO + os.sep):
            out.append(f"line {ln_no}: include \"{target}\" resolves OUTSIDE the repo ({hit})")
    return out


def offenders():
    """[(path, reason)] for every tracked source that is not TEXT or carries a non-portable #include."""
    bad, seen = [], 0
    for root in ROOTS:
        for dirpath, _dirs, files in os.walk(os.path.join(REPO, root)):
            for f in files:
                if not f.endswith(EXTS):
                    continue
                seen += 1
                p = os.path.join(dirpath, f)
                data = open(p, "rb").read()
                rel = os.path.relpath(p, REPO)
                n = data.count(b"\x00")
                if n:
                    i = data.find(b"\x00")
                    line = data[:i].count(b"\n") + 1
                    bad.append((rel, f"{n} NUL byte(s), first at line {line}"))
                for why in include_offenders(p, data):
                    bad.append((rel, why))
    return bad, seen


def main():
    bad, seen = offenders()
    print(f"audit-text-sources: scanned {seen} tracked {'/'.join(EXTS)} file(s) under {'/'.join(ROOTS)}")
    if not bad:
        print("audit-text-sources: OK — every source is TEXT (grep can see all of them) and every "
              "#include is PORTABLE (resolves inside the repo).")
        return 0
    nul = [b for b in bad if "NUL byte" in b[1]]
    inc = [b for b in bad if "NUL byte" not in b[1]]
    if nul:
        print(f"audit-text-sources: {len(nul)} FILE(S) GREP WOULD SILENTLY SKIP:")
        for rel, why in nul:
            print(f"  {rel}: {why}")
        print("\nA NUL in C source is almost always a raw control character written into a char "
              "literal (`'<NUL>'` instead of `'\\0'`). It COMPILES, so no byte-gate objects — but the "
              "file becomes invisible to grep and to every grep-based audit. Fix the literal, then "
              "re-gate the affected binary to prove the change is byte-neutral.")
    if inc:
        print(f"audit-text-sources: {len(inc)} NON-PORTABLE #include line(s) in "
              f"{len({rel for rel, _ in inc})} file(s):")
        for rel, why in inc:
            print(f"  {rel}: {why}")
        print("\nThe build's only include path is -Iinclude; an absolute, angle-bracket, unresolvable or "
              "outside-repo include builds here and nowhere else. Respell it (`../shared/…` from src/<bin>/), "
              "then re-gate the binary.")
    return 1


if __name__ == "__main__":
    sys.exit(main())
