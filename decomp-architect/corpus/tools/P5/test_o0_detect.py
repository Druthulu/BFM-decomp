#!/usr/bin/env python3
"""test_o0_detect.py — negative control for match_one's -O0 auto-detection (P31 S59).

WHY IT EXISTS. `match_one --o0` has always existed, and nothing in the drafting path ever passed
it: `api_draft.match_one()` — the oracle every wave agent iterates against — builds a fixed argv
without it. An agent handed an -O0 target was shown an -O2 compile of its own C and a mismatch on
every instruction, feedback that cannot converge for a reason invisible in the diff. S59 made the
opt level auto-detected. This is the control on that detector.

THE DETECTION LAW (cookbook §6/§18, byte-proven): gcc-2.7.2 keeps a frame pointer at -O0 and omits
it at -O2, so an -O0 function opens with `sw $fp, N($sp)` + `addu $fp, $sp, $zero` (word 21F0A003).

THREE CHECKS:
  NC-1 COVERAGE — every .s under asm/ that carries the -O0 signature anywhere is detected as -O0,
        either by its prologue or by its subseg being an -O0 object. A miss compiles an -O0 target
        at -O2, which is the whole defect.
  NC-2 NO FALSE POSITIVES OUTSIDE THE -O0 OBJECTS — a file the signature grep does NOT find may
        only be called -O0 if it lives in a subseg the Makefile compiles -O0 (`boot`, `*_o0*`).
        Calling an -O2 function -O0 is the same defect with the sign flipped.
  NC-3 THE PROLOGUE RULE IS ANCHORED AT THE FUNCTION — the two md_MAIN_011 files whose .s opens
        with a migrated jump table / .asciz blob must still be detected. They are the reason the
        scan starts at `glabel`, not at the top of the file.

Run: .venv/bin/python tools/test_o0_detect.py
"""
import glob
import os
import re
import subprocess
import sys

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))

# Import detect_o0 without executing match_one's CLI (it parses argv at import time).
_SRC = open(os.path.join(REPO, "tools/match_one.py")).read()
_FN = _SRC[_SRC.index("def detect_o0"):_SRC.index("_sub = os.path.basename")]
_NS = {"re": re, "os": os}
exec(_FN, _NS)
detect_o0 = _NS["detect_o0"]

sys.path.insert(0, os.path.join(REPO, "tools"))
import corpus                                                        # noqa: E402

FAIL = []


def sub_is_o0(path):
    """Does the BUILD compile this subseg -O0? Asked of the Makefile, never of the name (R33) —
    md_MAIN_011 keeps its plain name and is compiled -O0 by an explicit whole-object rule."""
    sub = os.path.basename(os.path.dirname(path))
    parts = os.path.normpath(path).split(os.sep)
    binary = "main" if (len(parts) > 1 and parts[1] == "nonmatchings") else parts[1]
    return corpus.o0_subseg(binary, sub)


def main():
    os.chdir(REPO)
    files = glob.glob("asm/**/*.s", recursive=True)
    grep = set(subprocess.run(
        ["bash", "-c", "grep -rl 'addu .*\\$fp, *\\$sp\\|21F0A003' asm/ --include=*.s"],
        capture_output=True, text=True).stdout.split())
    print(f"R32 denominator: {len(files)} .s files under asm/")
    print(f"carrying the -O0 signature anywhere in the file: {len(grep)}")

    detected = {p for p in files if detect_o0(p) or sub_is_o0(p)}
    missed = sorted(grep - detected)
    print(f"detected as -O0 (prologue OR -O0 subseg): {len(detected)}")

    # NC-1
    if missed:
        FAIL.append(f"NC-1 COVERAGE: {len(missed)} signature-carrying files not detected: {missed[:5]}")
    print(f"NC-1 coverage        : {len(grep) - len(missed)}/{len(grep)} signature files detected")

    # NC-2
    fp = sorted(p for p in detected - grep if not sub_is_o0(p))
    if fp:
        FAIL.append(f"NC-2 FALSE POSITIVES: {len(fp)} files called -O0 with no signature and no -O0 subseg: {fp[:5]}")
    extra_in_o0 = len(detected - grep) - len(fp)
    print(f"NC-2 false positives : 0 outside -O0 objects ({extra_in_o0} inside them, which the "
          f"Makefile does compile -O0)")

    # NC-3
    anchored = ["asm/md_MAIN_011/nonmatchings/md_MAIN_011/func_800CF28C.s",
                "asm/md_MAIN_011/nonmatchings/md_MAIN_011/func_800D04F4.s"]
    for p in anchored:
        if not os.path.exists(p):
            print(f"NC-3 skipped ({p} absent — asm/ not extracted?)")
            break
        if not detect_o0(p):
            FAIL.append(f"NC-3 {p}: rodata-first .s not detected — the scan is not anchored at glabel")
    else:
        print(f"NC-3 rodata-first    : {len(anchored)}/{len(anchored)} detected (scan anchored at glabel)")

    if FAIL:
        print("\nFAILED:")
        for f in FAIL:
            print("  -", f)
        return 1
    print("\nALL CHECKS PASS")
    return 0


if __name__ == "__main__":
    sys.exit(main())
