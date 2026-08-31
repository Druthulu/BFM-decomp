#!/usr/bin/env python3
"""restore_dropped_decls.py — put back file-scope declarations a dedup propagation deleted. (P31 S67)

WHY THIS EXISTS (byte-witnessed, ov_SC04_018).  `dedup_propagate` replaces a body with a
`DEFINE_func_*()` instantiation and removes the lines that body occupied — including the TU's
file-scope declaration layer.  That layer is NOT owned by the replaced bodies: the TU's OTHER,
non-deduped functions still reference those symbols.  Measured: one commit deleted 981 lines from
`ov_SC04_018_jr_80135D20.c` (leaving 7), three bodies became macro instantiations, and the two
surviving bodies lost every declaration they used -> `D_8018D7A4' undeclared, whole binary RED and
the fleet at 212/213.

THE RECOVERY IS DETERMINISTIC, NOT A GUESS.  Every deleted declaration is still in the file's own
history, with its ORIGINAL TYPE.  Guessing the type is how this goes wrong twice: `D_8018D7AC` is
`s16 *`, and a hand-written `extern u8 D_8018D7AC;` turns "undeclared" into "subscripted value is
neither array nor pointer" — a second wrong answer that looks like progress.

THE COMPILER IS THE ORACLE.  Build, read which identifiers it says are undeclared, look each one up
in `<ref>:<path>`, insert it, build again.  Repeat to convergence.  Nothing is inserted that the
compiler did not ask for, so a declaration whose symbol the DEFINE_ macros already supply is never
re-added (that would be `conflicting types`, trading one break for another).

    tools/restore_dropped_decls.py --binary ov_SC04_018 --ref commit:3354^
"""
import argparse
import os
import re
import subprocess
import sys

_BJOBS = int(os.environ.get('BFM_BUILD_JOBS') or (os.cpu_count() or 8))   # -j: a per-binary build is ~35 objects and was SERIAL (6.1x measured, S67)

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
UNDECL = re.compile(r"^(src/\S+\.c):(\d+): `(\w+)' undeclared")


def sh(cmd, **kw):
    return subprocess.run(cmd, cwd=REPO, capture_output=True, text=True, **kw)


def original_decl(ref, path, sym):
    """The symbol's declaration AS IT WAS, from git history. None if it had none."""
    r = sh(["git", "show", "%s:%s" % (ref, path)])
    if r.returncode:
        return None
    pat = re.compile(r"^\s*extern\s+[^;{}]*?\b%s\b[^;{}]*;\s*$" % re.escape(sym), re.M)
    m = pat.search(r.stdout)
    return m.group(0).strip() if m else None


def insert_at_file_scope(path, decls):
    """Insert directly after the LEADING #include block.

    NOT "after the last extern in the first N lines" — the whole failure being repaired is that the
    declarations which stood ABOVE the surviving bodies were deleted while a LATER copy survived
    (ov_SC04_018_jr_80135D20.c still declares `D_8018D7AC` at line 225, and the function that needs
    it starts at line 42). Anchoring on the last extern therefore inserts BELOW the point of use,
    the build fails identically, and the loop re-inserts forever — measured: 25 rounds, 100 dead
    declarations. C89 requires the declaration to precede the use, so the only safe anchor is the
    top of the file."""
    full = os.path.join(REPO, path)
    lines = open(full).read().split("\n")
    anchor = 0
    for i, ln in enumerate(lines):
        st = ln.strip()
        if st.startswith("#include"):
            anchor = i + 1
        elif st and not st.startswith(("//", "/*", "*", "#")):
            break
    lines[anchor:anchor] = list(decls)
    open(full, "w").write("\n".join(lines))


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--binary", required=True)
    ap.add_argument("--ref", required=True, help="git ref holding the pre-deletion sources")
    ap.add_argument("--max-rounds", type=int, default=25)
    a = ap.parse_args()

    total = 0
    prev_want = None
    for rnd in range(1, a.max_rounds + 1):
        r = sh(["make", "-j%d" % _BJOBS, "build", "BINARY=" + a.binary], timeout=3600)
        out = (r.stdout or "") + (r.stderr or "")
        if r.returncode == 0:
            print("build GREEN after %d round(s), %d declaration(s) restored" % (rnd - 1, total))
            return 0
        want = {}
        for ln in out.split("\n"):
            m = UNDECL.match(ln.strip())
            if m:
                want.setdefault(m.group(1), set()).add(m.group(3))
        if not want:
            # R43: this tool fixes exactly ONE failure mode. Anything else is not ours to touch.
            errs = [l for l in out.split("\n")
                    if re.search(r"\.c:\d+: ", l) and "warning" not in l][:6]
            print("REFUSING: build fails for a reason that is not an undeclared identifier:\n  "
                  + "\n  ".join(errs), file=sys.stderr)
            return 2
        # NO-PROGRESS GUARD (R32/R43). If a round asks for exactly what the last round already
        # inserted, the insertion is not taking effect and repeating it only accumulates dead
        # declarations. Refuse instead of looping — a tool that cannot fix an input must say so.
        signature = {k: sorted(v) for k, v in want.items()}
        if signature == prev_want:
            print("REFUSING: round %d asks for the same declarations round %d already inserted — "
                  "the insertion point is not above the use. Nothing further applied."
                  % (rnd, rnd - 1), file=sys.stderr)
            return 2
        prev_want = signature
        added = 0
        for path, syms in sorted(want.items()):
            decls, missing = [], []
            for s in sorted(syms):
                d = original_decl(a.ref, path, s)
                (decls.append(d) if d else missing.append(s))
            if missing:
                print("REFUSING: %s: no original declaration in %s for: %s"
                      % (path, a.ref, ", ".join(missing)), file=sys.stderr)
                return 2
            insert_at_file_scope(path, decls)
            added += len(decls)
            print("  %s: restored %d — %s" % (path, len(decls), "; ".join(decls)))
        total += added
        print("round %d: restored %d declaration(s)" % (rnd, added))
    print("REFUSING: still failing after %d rounds" % a.max_rounds, file=sys.stderr)
    return 2


if __name__ == "__main__":
    sys.exit(main())
