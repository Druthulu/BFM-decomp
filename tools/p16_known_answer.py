#!/usr/bin/env python3
"""p16_known_answer.py — graduated known-answer validation of the Phase-16 struct pipeline.

Take ALREADY-matched functions (known answers), revert them to INCLUDE_ASM stubs, regenerate
their .s, run the pipeline (m2c --valid-syntax -> draft), and measure how close/whether it
re-derives the byte-match we already know is correct. The byte-gate (harvest_verify) is the
ground truth; match_one gives a fast per-function score for the calibration ramp.

Restores the overlay .c from a backup afterward (never git-checkout mid-harvest — cookbook §14c).

  python3 tools/p16_known_answer.py --pick 8           # auto-pick a difficulty ladder, calibrate (m2c+match_one)
  python3 tools/p16_known_answer.py --funcs func_A,func_B
"""
import argparse, os, re, subprocess, sys, json, random

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
OV = "ov_SC01_077"
SRC = f"src/{OV}/{OV}.c"
ECORE = "src/shared/engine_core.h"
ASM = f"asm/{OV}/nonmatchings/{OV}"
BAK = ".run/p16_ka_backup.c"


def sh(cmd, **kw):
    return subprocess.run(cmd, capture_output=True, text=True, **kw)


def macro_bodies():
    """addr -> instruction-ish line count for every DEFINE_func_<addr> macro in engine_core.h."""
    txt = open(ECORE).read()
    out = {}
    for m in re.finditer(r"#define DEFINE_func_([0-9A-Fa-f]+)\(\)((?:.*\\\n)*.*\n)", txt):
        addr = m.group(1)
        body = m.group(2)
        # count statements (lines with ; or store/load) as an nins proxy
        n = len(re.findall(r"[;}]", body))
        out[addr] = n
    return out


def instantiated_in_src(addr):
    return re.search(rf"DEFINE_func_{addr}\(\)", open(SRC).read()) is not None


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--pick", type=int, default=8, help="auto-pick a difficulty ladder of N matched fns")
    ap.add_argument("--funcs", help="comma list of func_<addr> to test instead of auto-pick")
    ap.add_argument("--seed", type=int, default=11)
    a = ap.parse_args()
    os.chdir(REPO)

    # choose the ladder
    if a.funcs:
        addrs = [f.replace("func_", "") for f in a.funcs.split(",")]
    else:
        bodies = macro_bodies()
        cand = [(addr, n) for addr, n in bodies.items() if instantiated_in_src(addr)]
        # ladder: spread across size buckets
        random.seed(a.seed)
        buckets = {"tiny(1-4)": [], "easy(5-12)": [], "med(13-30)": [], "big(31+)": []}
        for addr, n in cand:
            if n <= 4: buckets["tiny(1-4)"].append((addr, n))
            elif n <= 12: buckets["easy(5-12)"].append((addr, n))
            elif n <= 30: buckets["med(13-30)"].append((addr, n))
            else: buckets["big(31+)"].append((addr, n))
        per = max(1, a.pick // 4)
        addrs = []
        for b in buckets.values():
            random.shuffle(b)
            addrs += [addr for addr, n in b[:per]]
    funcs = [f"func_{addr}" for addr in addrs]
    print(f"ladder ({len(funcs)} known-answer fns): {funcs}")

    # backup, then stub the chosen fns in the overlay .c
    src = open(SRC).read()
    open(BAK, "w").write(src)
    stubbed = []
    for fn in funcs:
        addr = fn.replace("func_", "")
        pat = rf"^[ \t]*DEFINE_func_{addr}\(\).*$"
        repl = f'INCLUDE_ASM("{ASM}", {fn});'
        new, k = re.subn(pat, repl, src, flags=re.M)
        if k:
            src = new; stubbed.append(fn)
    open(SRC, "w").write(src)
    print(f"stubbed {len(stubbed)} instantiations; re-extracting asm...")

    try:
        r = sh(["make", "extract", f"BINARY={OV}"])
        if r.returncode:
            print("EXTRACT FAIL:\n" + r.stderr[-800:]); return
        # per-fn: m2c -> draft -> match_one score
        results = []
        for fn in stubbed:
            s = f"{ASM}/{fn}.s"
            if not os.path.exists(s):
                results.append((fn, "no-asm", None)); continue
            out = sh([".venv/bin/python", "tools/m2c/m2c.py", "-t", "mipsel-gcc-c",
                      "--valid-syntax", "-f", fn, s]).stdout
            if not out.strip() or "OSError" in out:
                results.append((fn, "m2c-empty", None)); continue
            if re.search(r"M2C_ERROR|M2C_BREAK|MULT_HI|\bCLZ\b|M2C_TRAP|GLUE_F64|BSWAP", out):
                results.append((fn, "nonfaithful(defer)", None)); continue
            dpath = f".run/p16_ka/{fn}.c"
            os.makedirs(".run/p16_ka", exist_ok=True)
            open(dpath, "w").write(out)
            mo = sh([".venv/bin/python", "tools/match_one.py", fn, "--c", dpath,
                     "--asm-subdir", ASM]).stdout
            first = mo.strip().splitlines()[0] if mo.strip() else "?"
            if first.startswith("MATCH"):
                results.append((fn, "M2C-DIRECT-MATCH", 0))
            elif "mismatched" in first:
                mm = re.search(r"(\d+) mismatched", first)
                results.append((fn, "near-miss", int(mm.group(1)) if mm else -1))
            else:
                results.append((fn, first[:40], -1))
        print("\n=== KNOWN-ANSWER CALIBRATION (m2c direct, no permuter yet) ===")
        direct = 0
        for fn, status, score in results:
            print(f"  {fn:20} {status:22} {'mismatch='+str(score) if score and score>0 else ''}")
            if status == "M2C-DIRECT-MATCH": direct += 1
        print(f"\n  m2c-DIRECT re-derivation: {direct}/{len(stubbed)} (the rest are permuter candidates)")
        json.dump([{"fn": f, "status": s, "score": sc} for f, s, sc in results],
                  open(".run/p16_ka_results.json", "w"), indent=1)
    finally:
        # ALWAYS restore the matched .c (never leave a regression)
        open(SRC, "w").write(open(BAK).read())
        print(f"\nrestored {SRC} from backup.")


if __name__ == "__main__":
    main()
