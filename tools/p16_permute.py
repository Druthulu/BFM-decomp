#!/usr/bin/env python3
"""p16_permute.py — measure decomp-permuter close-rate on m2c near-miss drafts (Phase 16).

For each function: take its (sig-unified) m2c draft, expand M2C_FIELD macros to plain casts so
pycparser can parse it, build base.c + target.o, run decomp-permuter (time-boxed, -j), and report
whether it reached score 0 (a byte match). This measures the permuter's yield — the differentiator
that decides whether the unattended 5-day run is worthwhile.

A score-0 hit is written to .run/permuter/<fn>/output-*/source.c; we copy it to --winners for gating.

  python3 tools/p16_permute.py --funcs func_A,func_B --secs 300 --j 8
  python3 tools/p16_permute.py --from-drafts .run/drafts-full-uni --near-max 8 --limit 12 --secs 300
"""
import argparse, os, re, subprocess, sys, glob, shutil, time

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
OV = "ov_SC01_077"
ASM = f"asm/{OV}/nonmatchings/{OV}"
PY = ".venv/bin/python"
TYPEDEFS = ("typedef unsigned char u8; typedef unsigned short u16; typedef unsigned int u32;\n"
            "typedef signed char s8; typedef short s16; typedef int s32;\n"
            "typedef unsigned long long u64; typedef long long s64; typedef double f64;\n"
            "typedef s32 M2C_UNK; typedef s8 M2C_UNK8; typedef s16 M2C_UNK16; typedef s32 M2C_UNK32; typedef s64 M2C_UNK64;\n"
            "#define NULL ((void*)0)\n")


def sh(cmd, **kw):
    return subprocess.run(cmd, capture_output=True, text=True, cwd=REPO, **kw)


def split_args(s):
    """split a top-level comma-separated arg list (balanced parens)."""
    out, depth, cur = [], 0, ""
    for ch in s:
        if ch == "(": depth += 1; cur += ch
        elif ch == ")": depth -= 1; cur += ch
        elif ch == "," and depth == 0: out.append(cur); cur = ""
        else: cur += ch
    if cur.strip():
        out.append(cur)
    return out


def expand_m2c_field(c):
    """M2C_FIELD(EXPR, TYPE, OFF) -> (*(TYPE)((s8*)(EXPR)+(OFF))), innermost-first, repeatedly."""
    while True:
        i = c.find("M2C_FIELD(")
        if i < 0:
            return c
        # find the matching close paren for this call
        j = i + len("M2C_FIELD(")
        depth = 1
        while j < len(c) and depth:
            if c[j] == "(": depth += 1
            elif c[j] == ")": depth -= 1
            j += 1
        inner = c[i + len("M2C_FIELD("):j - 1]
        args = split_args(inner)
        if len(args) != 3:
            # malformed; bail to avoid an infinite loop
            return c
        expr, typ, off = (a.strip() for a in args)
        # if expr still has M2C_FIELD, expand it first (recurse on the substring)
        if "M2C_FIELD(" in expr:
            expr = expand_m2c_field(expr)
        repl = f"(*({typ})((s8*)({expr})+({off})))"
        c = c[:i] + repl + c[j:]


def drop_preproc_and_scalar_typedefs(c):
    """drop #include/#define and scalar/M2C typedef lines (TYPEDEFS/common.h provide them) —
    but KEEP `extern` callee/data decls so the function compiles in its REAL signature context."""
    lines = []
    for ln in c.splitlines():
        s = ln.strip()
        if s.startswith("#"):
            continue
        if re.match(r"^typedef\b", s):
            continue
        lines.append(ln)
    return "\n".join(lines)


def make_base_c(draft_c):
    """permuter base.c = scalar typedefs + the draft's canonical externs + the M2C_FIELD-expanded body.
    Keeping the externs is essential: without them callees fall back to implicit-int and the permuter
    matches in a DIFFERENT context than the whole-binary build (-> winners don't byte-gate)."""
    body = expand_m2c_field(draft_c)
    body = drop_preproc_and_scalar_typedefs(body)
    return TYPEDEFS + body + "\n"


def winner_to_draft(winner_c):
    """permuter winner (typedefs + externs + body) -> gate-ready draft (externs + body). common.h
    provides scalars/macros in the whole-binary TU. The permuter REFORMATS the typedefs (one per
    line), so strip by line filter (drop #/typedef lines, keep externs + the function def), NOT a
    string-replace of the TYPEDEFS block (that silently fails -> C89 typedef-redefinition error)."""
    return drop_preproc_and_scalar_typedefs(winner_c)


def setup(fn, draft_c, asm_subdir=ASM):
    pd = os.path.join(REPO, ".run/permuter", fn)
    if os.path.exists(pd):
        shutil.rmtree(pd)
    os.makedirs(pd)
    open(f"{pd}/base.c", "w").write(make_base_c(draft_c))
    s = os.path.join(REPO, asm_subdir, fn + ".s")
    tgt = f"{pd}/target.s"
    with open(tgt, "w") as f:
        f.write('.set noat\n.set noreorder\n.include "macro.inc"\n.section .text\n\n')
        f.write(open(s, errors="replace").read())
    r = sh(["mipsel-linux-gnu-as", "-Iinclude", "-march=r3000", "-mtune=r3000",
            "-no-pad-sections", "-O1", "-G0", tgt, "-o", f"{pd}/target.o"])
    if r.returncode:
        return None
    open(f"{pd}/settings.toml", "w").write(f'func_name = "{fn}"\ncompiler_type = "gcc"\n')
    open(f"{pd}/compile.sh", "w").write(f'#!/bin/bash\nexec {REPO}/tools/permuter/compile.sh "$@"\n')
    os.chmod(f"{pd}/compile.sh", 0o755)
    return pd


def run_permuter(pd, secs, j):
    env = dict(os.environ, PATH=f"{REPO}/tools/permuter/bin:" + os.environ["PATH"])
    try:
        subprocess.run([PY, "tools/decomp-permuter/permuter.py", pd, "-j", str(j), "--stop-on-zero"],
                       cwd=REPO, env=env, capture_output=True, text=True, timeout=secs)
    except subprocess.TimeoutExpired:
        pass
    # kill stragglers
    subprocess.run(["pkill", "-f", "decomp-permuter/permuter.py"], capture_output=True)
    # ONLY output-0-* is a true byte-match; output-<N>-* are intermediate bests (score N != 0)
    win = glob.glob(f"{pd}/output-0-*/source.c")
    return win[0] if win else None


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--funcs")
    ap.add_argument("--from-drafts", default=".run/drafts-full-uni")
    ap.add_argument("--near-max", type=int, default=8)
    ap.add_argument("--limit", type=int, default=12)
    ap.add_argument("--secs", type=int, default=300)
    ap.add_argument("--j", type=int, default=8)
    ap.add_argument("--winners", default=".run/permuter-winners")
    a = ap.parse_args()
    os.chdir(REPO)
    os.makedirs(a.winners, exist_ok=True)

    if a.funcs:
        funcs = a.funcs.split(",")
    else:
        # pick near-miss drafts (match_one mismatch in [1, near-max]) from the drafts dir
        funcs = []
        for cf in sorted(glob.glob(a.from_drafts + "/*.c")):
            fn = os.path.basename(cf)[:-2]
            r = sh([PY, "tools/match_one.py", fn, "--c", cf, "--asm-subdir", ASM])
            first = (r.stdout.strip().splitlines() or ["?"])[0]
            m = re.search(r"(\d+) mismatched", first)
            if m and 1 <= int(m.group(1)) <= a.near_max:
                funcs.append(fn)
            if len(funcs) >= a.limit:
                break
    print(f"permuter batch: {len(funcs)} near-miss fns, {a.secs}s each @ -j{a.j}")
    won = 0
    for k, fn in enumerate(funcs, 1):
        cf = os.path.join(a.from_drafts, fn + ".c")
        if not os.path.exists(cf):
            print(f"  [{k}/{len(funcs)}] {fn}: no draft"); continue
        pd = setup(fn, open(cf).read())
        if not pd:
            print(f"  [{k}/{len(funcs)}] {fn}: setup failed (target.o)"); continue
        t0 = time.time()
        win = run_permuter(pd, a.secs, a.j)
        dt = int(time.time() - t0)
        if win:
            shutil.copy(win, os.path.join(a.winners, fn + ".c")); won += 1
            print(f"  [{k}/{len(funcs)}] {fn}: *** MATCH in {dt}s ***", flush=True)
        else:
            print(f"  [{k}/{len(funcs)}] {fn}: no match ({dt}s)", flush=True)
    print(f"\nPERMUTER YIELD: {won}/{len(funcs)} closed -> .run/permuter-winners (gate these whole-binary)")


if __name__ == "__main__":
    main()
