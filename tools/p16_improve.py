#!/usr/bin/env python3
"""p16_improve.py — known-answer-guided harness improvement loop (Phase 16, Drew's method).

Take ALREADY-matched functions (known answers) in a difficulty band, revert them to stubs,
run the real pipeline (m2c --valid-syntax -> sig_unify -> match_one / optional whole-binary
gate), and CATEGORIZE every failure into an actionable CLASS. Since the answer is known-reachable,
every fail is a harness gap we can diagnose + fix generally; the fix then transfers to the
unmatched functions that hit the same class.

Reports: re-derivation rate (the harness CEILING for this band) + a ranked failure-class
histogram (what to fix next). Restores the overlay .c afterward (never git-checkout, §14c).

  python3 tools/p16_improve.py --band easy --n 40            # easy band, match_one categorize
  python3 tools/p16_improve.py --band med  --n 30 --gate     # medium, whole-binary ceiling too
  bands: tiny(1-4) easy(5-12) med(13-40) big(41+)  (stmt-count proxy from the macro body)
"""
import argparse, os, re, subprocess, glob, random

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
OV = "ov_SC01_077"; SRC = f"src/{OV}/{OV}.c"; ECORE = "src/shared/engine_core.h"
ASM = f"asm/{OV}/nonmatchings/{OV}"; BAK = ".run/p16_improve_bak.c"; PY = ".venv/bin/python"
GOOD = "d19c9580a02dc63ba1f0e7e0c770f3b10de35635"
BANDS = {"tiny": (1, 4), "easy": (5, 12), "med": (13, 40), "big": (41, 10**9)}


def sh(cmd, **kw): return subprocess.run(cmd, capture_output=True, text=True, cwd=REPO, **kw)


def macro_bodies():
    txt = open(os.path.join(REPO, ECORE)).read()
    out = {}
    for m in re.finditer(r"#define DEFINE_func_([0-9A-Fa-f]+)\(\)((?:.*\\\n)*.*\n)", txt):
        out[m.group(1)] = len(re.findall(r"[;}]", m.group(2)))
    return out


def classify_fail(fn, cpath):
    """Run match_one; return ('match',0) | ('near',n) | ('class', label) for an actionable bucket."""
    r = sh([PY, "tools/match_one.py", fn, "--c", cpath, "--asm-subdir", ASM])
    out = r.stdout
    first = (out.strip().splitlines() or ["?"])[0]
    if first.startswith("MATCH"):
        return ("match", 0)
    m = re.search(r"(\d+) mismatched", first)
    if m:
        return ("near", int(m.group(1)))
    # compile failure -> sub-classify by the error text (the actionable class)
    if "CPP FAIL" in out:
        return ("class", "cpp-fail")
    if re.search(r"`NULL' undeclared", out):
        return ("class", "compile:NULL")
    if re.search(r"`sp[0-9A-Fa-f]+' undeclared|_m2c_stack", out):
        return ("class", "compile:stack-var")
    if re.search(r"`(subroutine_arg|saved_reg)\w*' undeclared", out):
        return ("class", "compile:m2c-incomplete-arg")
    m2 = re.search(r"`([A-Za-z_]\w*)' undeclared", out)
    if m2:
        return ("class", f"compile:undeclared-{'D_' if m2.group(1).startswith('D_') else 'other'}")
    if "conflicting types" in out:
        return ("class", "compile:conflicting-types")
    if "redefinition" in out:
        return ("class", "compile:redefinition")
    if "parse error" in out:
        return ("class", "compile:parse-error")
    return ("class", "compile:other")


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--band", choices=list(BANDS), default="easy")
    ap.add_argument("--n", type=int, default=40)
    ap.add_argument("--seed", type=int, default=3)
    ap.add_argument("--gate", action="store_true", help="also run sig_unify + whole-binary gate for the true ceiling")
    a = ap.parse_args()
    os.chdir(REPO)
    lo, hi = BANDS[a.band]
    bodies = macro_bodies()
    srctxt = open(SRC).read()
    cand = [addr for addr, n in bodies.items()
            if lo <= n <= hi and re.search(rf"DEFINE_func_{addr}\(\)", srctxt)]
    random.seed(a.seed); random.shuffle(cand)
    funcs = [f"func_{addr}" for addr in cand[:a.n]]
    print(f"band={a.band}({lo}-{hi} stmts)  testing {len(funcs)} known-answer fns")

    open(BAK, "w").write(srctxt)
    s = srctxt
    for fn in funcs:
        s = re.sub(rf"^[ \t]*DEFINE_func_{fn[5:]}\(\).*$", f'INCLUDE_ASM("{ASM}", {fn});', s, flags=re.M)
    open(SRC, "w").write(s)
    try:
        if sh(["make", "extract", f"BINARY={OV}"]).returncode:
            print("EXTRACT FAIL"); return
        os.makedirs(".run/p16_imp", exist_ok=True)
        for f in glob.glob(".run/p16_imp/*.c"):
            os.remove(f)
        cats, near_hist, matched = {}, [], 0
        for fn in funcs:
            spath = f"{ASM}/{fn}.s"
            if not os.path.exists(spath):
                cats["no-asm"] = cats.get("no-asm", 0) + 1; continue
            out = sh([PY, "tools/m2c/m2c.py", "-t", "mipsel-gcc-c", "--valid-syntax", "-f", fn, spath]).stdout
            if not out.strip() or "OSError" in out:
                cats["m2c-empty"] = cats.get("m2c-empty", 0) + 1; continue
            if re.search(r"M2C_ERROR|M2C_BREAK|MULT_HI|\bCLZ\b|M2C_TRAP|GLUE_F64|BSWAP", out):
                cats["nonfaithful(GTE/special)"] = cats.get("nonfaithful(GTE/special)", 0) + 1; continue
            cp = f".run/p16_imp/{fn}.c"; open(cp, "w").write(out)
            kind, val = classify_fail(fn, cp)
            if kind == "match":
                matched += 1
            elif kind == "near":
                near_hist.append(val); cats[f"near-miss"] = cats.get("near-miss", 0) + 1
            else:
                cats[val] = cats.get(val, 0) + 1
        n = len(funcs)
        print(f"\n=== BAND {a.band}: match_one re-derivation = {matched}/{n} = {100*matched//max(n,1)}% (the harness ceiling, match_one) ===")
        if near_hist:
            ez = sum(1 for x in near_hist if x <= 8)
            print(f"  near-misses: {len(near_hist)} (permuter candidates; {ez} are <=8 mismatch = easy permute)")
        print("  FAILURE CLASSES (ranked — fix the top ones):")
        for cls, c in sorted(cats.items(), key=lambda x: -x[1]):
            print(f"    {c:4} {cls}")
        if a.gate:
            print("\n=== whole-binary ceiling (sig_unify + gate) ===")
            sh([PY, "tools/sig_unify.py", "--overlay", OV, "--in", ".run/p16_imp", "--out", ".run/p16_imp-uni"])
            gd = ".run/p16_imp-uni" if os.path.isdir(os.path.join(REPO, ".run/p16_imp-uni")) else ".run/p16_imp"
            r = sh([PY, "tools/harvest_verify.py", "--binary", OV, "--src", SRC, "--asm-subdir", ASM,
                    "--out", f"build/{OV}/{OV}", "--good-sha", GOOD, "--drafts", gd, "--chunk", "4"])
            for line in r.stdout.splitlines():
                if "verified" in line and "failed" in line:
                    print("  " + line.strip())
    finally:
        open(SRC, "w").write(open(BAK).read())
        print(f"\nrestored {SRC}.")


if __name__ == "__main__":
    main()
