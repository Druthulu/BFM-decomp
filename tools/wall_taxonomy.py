#!/usr/bin/env python3
"""wall_taxonomy.py — census-classify every UNMATCHED shared residual in ov_SC01_077 by
blocker class, so Phase 17 can size each avenue's ceiling and sequence T2-T5 (biggest first).

This is the full-census counterpart to p16_improve.py (which samples KNOWN answers): it runs the
real drafting pipeline on the LIVE INCLUDE_ASM stubs and labels each with the wall it hits.

Decision tree (per stub func, cookbook §14b/§14c/§14e/§15):
  1. m2c --valid-syntax on its .s
       - no output            -> M2C_EMPTY            (decompiler gave up; hard / Ghidra / defer)
       - non-faithful macros  -> NONFAITHFUL_DEFER    (M2C_ERROR/CLZ/MULT_HI/... => cannot byte-match, §15)
  2. else (byte-faithful) run match_one (standalone, relocation-masked):
       - MATCH + relocations  -> CONFLICT_CLASS       (body byte-correct; only a TU-level decl conflict blocks it, §14b)
                                                        -> step 3 sub-splits T2 / T3 / wall
       - MATCH + no relocs    -> LEAF_READY           (directly matchable leaf; flag — why still a stub?)
       - near, same nins, few -> PERMUTER_CLASS        (regalloc/schedule only -> T6 decomp-permuter)
       - near, diff nins/many -> STRUCTURAL_MISS       (m2c structurally wrong -> T4 context / T5 struct, or hard)
       - compile-fail         -> MCOMPILE_<reason>     (m2c output won't compile standalone -> T4/T5/T2 per reason)
  3. CONFLICT_CLASS subset only: sig_unify the draft, substitute into the full overlay TU, cc1, parse error:
       - clean compile           -> SIG_FIXABLE_KR    (T3: sig_unify/K&R resolves it)
       - conflicting D_ symbol    -> DATA_CONFLICT     (T2: byte-array data header)
       - default-promotion/arity  -> ARITY_WALL        (documented C-language dead-end, §14e)
       - other                    -> OTHER_CONFLICT

Outputs .run/wall_taxonomy.json (per-fn) + a ranked histogram to stdout. Read-only on tracked
files (step 3 writes/reads temp copies under src/ov_SC01_077/_wt_*.c and removes them).

  python3 tools/wall_taxonomy.py                      # full census (all stubs), parallel
  python3 tools/wall_taxonomy.py --limit 40           # probe the classifier on the first 40 stubs
  python3 tools/wall_taxonomy.py --jobs 16 --no-step3 # steps 1-2 only (skip TU-context sub-split)
"""
import argparse, os, re, subprocess, json, glob
from concurrent.futures import ThreadPoolExecutor

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
OV = "ov_SC01_077"
SRC = f"src/{OV}/{OV}.c"
ASM = f"asm/{OV}/nonmatchings/{OV}"
PY = ".venv/bin/python"
DRAFTS = ".run/wt_drafts"          # raw m2c output per fn
UNI = ".run/wt_uni"                # sig_unified drafts (step 3)
NONFAITHFUL = re.compile(r"M2C_ERROR|M2C_BREAK|MULT_HI|MULTU_HI|\bCLZ\b|M2C_TRAP|GLUE_F64|BSWAP")

# pinned compile flags (mirror match_one.py exactly)
CPP = "mipsel-linux-gnu-cpp"
CC1 = "tools/bin/gcc-2.7.2-psx/cc1"
CPPFLAGS = ("-lang-c -Iinclude -undef -Wall -fno-builtin -Dmips -D__GNUC__=2 "
            "-D__OPTIMIZE__ -Dpsx -D_PSYQ -D_MIPSEL -D_LANGUAGE_C").split()
CC1FLAGS = "-quiet -O2 -G0 -mips1 -mcpu=3000 -mgas -msoft-float -fgnu-linker".split()

# bucket -> which Phase-17 avenue addresses it (for the report)
AVENUE = {
    "DATA_CONFLICT":     "T2 (DATA-symbol byte-array header)",
    "SIG_FIXABLE_KR":    "T3 (K&R / sig_unify loose-signature) — gate-proven",
    "LOOSE_TYPING_WALL": "— loose-typing wall (§14e): a hard int/ptr conflict (rare; warnings are byte-neutral)",
    "VOID_VALUE_MISUSE": "T4/T5 — m2c used a void-returning fn's result (structural/type miss)",
    "ARITY_WALL":        "— documented C-language wall (§14e): param-count / default-promotion",
    "OTHER_CONFLICT":    "T3/T4 (residual decl conflict)",
    "M2C_DECOMP_FAIL":   "T4 (provide jump tables / jtbl context to m2c, §8) | hard",
    "PERMUTER_CLASS":    "T6 candidate — near-miss, same nins (needs permuter to confirm)",
    "STRUCTURAL_MISS":   "T4 (rich context) / T5 (struct) to fix m2c structure",
    "MCOMPILE_arg-arity":     "T4/T5 (m2c arg-count recovery)",
    "MCOMPILE_fnptr-call":    "T4 (type fn-pointer tables in m2c context, §15 S2)",
    "MCOMPILE_bad-switch":    "T4/T5 (m2c switch reconstruction) | hard",
    "MCOMPILE_bad-deref":     "T5 (struct) / T4 (context) — m2c deref'd a non-pointer",
    "MCOMPILE_undeclared-D_": "T2 (data header) / T4 (context)",
    "MCOMPILE_stack-var":     "T5 (struct/stack) / T4 (context)",
    "MCOMPILE_m2c-incomplete-arg": "T4/T5 (m2c arg recovery)",
    "MCOMPILE_NULL":          "harness (common.h) — should be rare now",
    "MCOMPILE_parse-error":   "T4/T5 (m2c structural)",
    "MCOMPILE_undeclared-other": "T4 (context) — undeclared callee/symbol",
    "MCOMPILE_conflicting-types": "T3 (sig) — standalone conflict (rare)",
    "MCOMPILE_other":         "investigate",
    "MCOMPILE_cpp-fail":      "harness/preprocessor",
    "LEAF_READY":        "T6 trivial — directly matchable, harvest it",
    "NONFAITHFUL_DEFER": "— defer (GTE/handwritten/special; not m2c-matchable)",
    "M2C_EMPTY":         "— defer / Ghidra (m2c produced nothing)",
    "NO_ASM":            "— consistency error (re-extract)",
}
# permuter-class thresholds (cookbook §3/§15: <=8 easy, modest count = regalloc/schedule)
PERMUTE_MAX_MISMATCH = 16


def sh(cmd, **kw):
    return subprocess.run(cmd, capture_output=True, text=True, cwd=REPO, **kw)


def stub_funcs():
    txt = open(os.path.join(REPO, SRC)).read()
    return re.findall(r'INCLUDE_ASM\([^,]*,\s*(func_[0-9A-Fa-f]+)\)', txt)


def asm_stats(fn):
    """(target_nins, reloc_count) from the splat .s; reloc = jal + %hi + %lo lines."""
    p = os.path.join(REPO, ASM, fn + ".s")
    if not os.path.exists(p):
        return None, None
    txt = open(p).read()
    nins = len(re.findall(r'/\*\s*[0-9A-Fa-f]+\s+[0-9A-Fa-f]+\s+[0-9A-Fa-f]{8}\s*\*/', txt))
    relocs = len(re.findall(r'%hi|%lo|\bjal\b', txt))
    return nins, relocs


def sub_class_compile(out):
    """sub-classify a match_one compile failure by its error text (mirrors p16_improve.classify_fail)."""
    if "CPP FAIL" in out:
        return "cpp-fail"
    if re.search(r"`NULL' undeclared", out):
        return "NULL"
    if re.search(r"`sp[0-9A-Fa-f]+' undeclared|_m2c_stack", out):
        return "stack-var"
    if re.search(r"`(subroutine_arg|saved_reg)\w*' undeclared", out):
        return "m2c-incomplete-arg"
    m = re.search(r"`([A-Za-z_]\w*)' undeclared", out)
    if m:
        return "undeclared-D_" if m.group(1).startswith("D_") else "undeclared-other"
    if "conflicting types" in out:
        return "conflicting-types"
    if "redefinition" in out:
        return "redefinition"
    if "parse error" in out:
        return "parse-error"
    if "invalid type argument of" in out:   # m2c deref'd a non-pointer (?/M2C_UNK) -> type-inference miss
        return "bad-deref"
    if "too few arguments" in out or "too many arguments" in out:  # m2c arg-count inconsistency
        return "arg-arity"
    if "called object is not a function" in out:  # m2c fn-pointer-table call, table not typed (§15 S2)
        return "fnptr-call"
    if "case label not within a switch" in out or "default label not within" in out:
        return "bad-switch"                       # m2c switch-reconstruction artifact
    return "other"


def classify_12(fn):
    """steps 1-2: returns a dict (no TU-context sub-split yet)."""
    nins, relocs = asm_stats(fn)
    rec = {"fn": fn, "addr": fn[5:], "nins": nins, "relocs": relocs,
           "mine_ins": None, "mismatch": None, "bucket": None}
    if nins is None:
        rec["bucket"] = "NO_ASM"; return rec
    spath = f"{ASM}/{fn}.s"
    m2c = sh([PY, "tools/m2c/m2c.py", "-t", "mipsel-gcc-c", "--valid-syntax", "-f", fn, spath])
    out = m2c.stdout
    if not out.strip() or "OSError" in out:
        rec["bucket"] = "M2C_EMPTY"; return rec
    if NONFAITHFUL.search(out):
        rec["bucket"] = "NONFAITHFUL_DEFER"; return rec
    if "Decompilation failure" in out or "is not provided" in out:  # m2c gave up (no usable draft)
        rec["bucket"] = "M2C_DECOMP_FAIL"
        rec["m2c_fail"] = "jumptable" if "jump table is not provided" in out else "other"
        return rec
    cp = os.path.join(REPO, DRAFTS, fn + ".c")
    open(cp, "w").write(out)
    mo = sh([PY, "tools/match_one.py", fn, "--c", f"{DRAFTS}/{fn}.c", "--asm-subdir", ASM])
    o = mo.stdout
    first = (o.strip().splitlines() or ["?"])[0]
    if first.startswith("MATCH"):
        rec["bucket"] = "CONFLICT_CLASS" if (relocs or 0) > 0 else "LEAF_READY"
        return rec
    md = re.search(r"mine=(\d+) ins, target=(\d+) ins, (\d+) mismatched", first)
    if md:
        mine, tgt, mm = int(md.group(1)), int(md.group(2)), int(md.group(3))
        rec["mine_ins"], rec["mismatch"] = mine, mm
        if mine == tgt and mm <= PERMUTE_MAX_MISMATCH:
            rec["bucket"] = "PERMUTER_CLASS"
        else:
            rec["bucket"] = "STRUCTURAL_MISS"
        return rec
    # compile failure -> sub-classify
    rec["bucket"] = "MCOMPILE_" + sub_class_compile(o)
    return rec


def tu_compile_error(fn):
    """step 3: substitute the sig_unified draft into the FULL overlay TU, cc1, return error text ('' = clean)."""
    draft = os.path.join(REPO, UNI, fn + ".c")
    if not os.path.exists(draft):
        draft = os.path.join(REPO, DRAFTS, fn + ".c")
    body = open(draft).read()
    # strip the draft's own #include lines (the overlay .c already includes common.h/engine_core.h)
    body = re.sub(r'^[ \t]*#\s*include\b.*$', '', body, flags=re.M)
    src = open(os.path.join(REPO, SRC)).read()
    stub = re.compile(rf'^[ \t]*INCLUDE_ASM\([^,]*,\s*{fn}\)\s*;?[ \t]*$', re.M)
    if not stub.search(src):
        return "NO-STUB"
    sub = stub.sub(lambda m: body, src, count=1)
    # write a temp .c IN THE OVERLAY DIR so the `../shared/...` relative includes resolve
    tmp = os.path.join(REPO, f"src/{OV}", f"_wt_{fn}.c")
    open(tmp, "w").write(sub)
    try:
        p = subprocess.run([CPP] + CPPFLAGS + [tmp], capture_output=True, cwd=REPO)
        if p.returncode:
            return "CPP:" + p.stderr.decode()[-1200:]
        p = subprocess.run([CC1] + CC1FLAGS, input=p.stdout, capture_output=True, cwd=REPO)
        if not p.returncode:
            return ""
        # The baseline TU already emits harmless WARNINGS (e.g. pre-existing "makes integer from
        # pointer" on shared loose callees) and still builds byte-identical. The real blocker is the
        # non-warning ERROR that flips rc!=0 — keep only those (else every failure is misattributed
        # to the baseline's loose-typing warnings). Verified: baseline cc1 rc=0 with those warnings.
        errlines = [l for l in p.stderr.decode().splitlines() if re.search(r":\d+:", l) and "warning:" not in l]
        return "\n".join(errlines)[-1600:]
    finally:
        os.remove(tmp)


def sub_class_conflict(err):
    # err is now ERROR-only (warnings filtered out); empty => the draft built clean = a real T3 win.
    if err == "":
        return "SIG_FIXABLE_KR"
    if "void value not ignored" in err:        # m2c used a void-returning fn's result -> structural/type miss
        return "VOID_VALUE_MISUSE"
    if re.search(r"default promotion|empty parameter", err):
        return "ARITY_WALL"
    m = re.search(r"conflicting types for `([A-Za-z_]\w*)'", err)
    if m:
        return "DATA_CONFLICT" if m.group(1).startswith("D_") else "ARITY_WALL"
    if "too few arguments" in err or "too many arguments" in err:
        return "ARITY_WALL"
    if "makes integer from pointer" in err or "makes pointer from integer" in err:
        return "LOOSE_TYPING_WALL"            # only if it ever becomes a hard error (rc!=0); ~0 in practice
    return "OTHER_CONFLICT"


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--limit", type=int, default=0, help="only the first N stubs (probe)")
    ap.add_argument("--jobs", type=int, default=12)
    ap.add_argument("--no-step3", action="store_true", help="skip the TU-context conflict sub-split")
    ap.add_argument("--out", default=".run/wall_taxonomy.json")
    a = ap.parse_args()
    os.chdir(REPO)
    os.makedirs(DRAFTS, exist_ok=True); os.makedirs(UNI, exist_ok=True)
    for f in glob.glob(os.path.join(REPO, f"src/{OV}", "_wt_*.c")):  # clear any stray step-3 temps
        os.remove(f)
    funcs = stub_funcs()
    if a.limit:
        funcs = funcs[:a.limit]
    print(f"census: {len(funcs)} unmatched stubs in {OV}  (jobs={a.jobs})")

    with ThreadPoolExecutor(max_workers=a.jobs) as ex:
        recs = list(ex.map(classify_12, funcs))

    # step 3: TU-context sub-split for CONFLICT_CLASS
    conflict = [r for r in recs if r["bucket"] == "CONFLICT_CLASS"]
    if conflict and not a.no_step3:
        print(f"step 3: TU-context sub-split on {len(conflict)} CONFLICT_CLASS fns (sig_unify + full-TU cc1)...")
        sh([PY, "tools/sig_unify.py", "--overlay", OV, "--in", DRAFTS, "--out", UNI])

        def step3(r):
            err = tu_compile_error(r["fn"])
            r["bucket"] = sub_class_conflict(err)
            r["tu_err"] = err[:200]
            return r
        with ThreadPoolExecutor(max_workers=max(4, a.jobs // 2)) as ex:  # full-TU cc1 is RAM/CPU heavier
            list(ex.map(step3, conflict))

    json.dump(recs, open(a.out, "w"), indent=1)

    # ranked histogram
    from collections import Counter
    cnt = Counter(r["bucket"] for r in recs)
    nins_by = Counter()
    for r in recs:
        nins_by[r["bucket"]] += (r["nins"] or 0)
    n = len(recs)
    print(f"\n=== WALL TAXONOMY — {n} unmatched shared residuals in {OV} ===")
    print(f"  {'count':>5} {'%':>5} {'Σnins':>7}  bucket                         avenue")
    for b, c in cnt.most_common():
        print(f"  {c:5} {100*c//max(n,1):4}% {nins_by[b]:7}  {b:30} {AVENUE.get(b,'?')}")
    jt = sum(1 for r in recs if r["bucket"] == "M2C_DECOMP_FAIL" and r.get("m2c_fail") == "jumptable")
    if jt:
        print(f"  (of M2C_DECOMP_FAIL: {jt} are jump-table — feedable to m2c via the §8 jtbl context lever)")
    print(f"\nwrote {a.out}")


if __name__ == "__main__":
    main()
