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
"""
import os
import sys

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
ROOTS = ("src", "include")
EXTS = (".c", ".h")


def offenders():
    """[(path, reason)] for every tracked-source file grep would treat as binary."""
    bad, seen = [], 0
    for root in ROOTS:
        for dirpath, _dirs, files in os.walk(os.path.join(REPO, root)):
            for f in files:
                if not f.endswith(EXTS):
                    continue
                seen += 1
                p = os.path.join(dirpath, f)
                data = open(p, "rb").read()
                n = data.count(b"\x00")
                if n:
                    rel = os.path.relpath(p, REPO)
                    i = data.find(b"\x00")
                    line = data[:i].count(b"\n") + 1
                    bad.append((rel, f"{n} NUL byte(s), first at line {line}"))
    return bad, seen


def main():
    bad, seen = offenders()
    print(f"audit-text-sources: scanned {seen} tracked {'/'.join(EXTS)} file(s) under {'/'.join(ROOTS)}")
    if not bad:
        print("audit-text-sources: OK — every source is TEXT (grep can see all of them).")
        return 0
    print(f"audit-text-sources: {len(bad)} FILE(S) GREP WOULD SILENTLY SKIP:")
    for rel, why in bad:
        print(f"  {rel}: {why}")
    print("\nA NUL in C source is almost always a raw control character written into a char "
          "literal (`'<NUL>'` instead of `'\\0'`). It COMPILES, so no byte-gate objects — but the "
          "file becomes invisible to grep and to every grep-based audit. Fix the literal, then "
          "re-gate the affected binary to prove the change is byte-neutral.")
    return 1


if __name__ == "__main__":
    sys.exit(main())
