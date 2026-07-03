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
import argparse, base64, os, re, subprocess, sys, glob, shutil, time

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import masked_diff   # shared scalar-typedef-redef regex (SCALAR_TYPEDEF_RE), used by prep below
OV = "ov_SC01_077"
ASM = f"asm/{OV}/nonmatchings/{OV}"
PY = ".venv/bin/python"
TYPEDEFS = ("typedef unsigned char u8; typedef unsigned short u16; typedef unsigned int u32;\n"
            "typedef signed char s8; typedef short s16; typedef int s32; typedef float f32;\n"
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


def _stmt_end(text, i):
    """from index i, return the index just past the terminating ';' at brace/paren depth 0, respecting
    () [] {} and string/char literals -- so a multi-line __asm__ block is captured as one statement."""
    depth, j, n = 0, i, len(text)
    while j < n:
        c = text[j]
        if c in '"\'':
            q = c; j += 1
            while j < n and text[j] != q:
                j += 2 if text[j] == "\\" else 1
            j += 1; continue
        if c in "([{":
            depth += 1
        elif c in ")]}":
            depth -= 1
        elif c == ";" and depth == 0:
            return j + 1
        j += 1
    return n


def hide_asm(c):
    """Replace each register-`__asm__` pin declaration and each `__asm__` statement with a
    `#pragma _permuter b64literal <b64>` carrier. pycparser parses the pragma as an opaque node;
    decomp-permuter's process_pragmas (ast_util.to_c) DECODES it back to the original text when it
    serializes a candidate for compilation -> cc1 still sees the real pins/GTE asm (regalloc still
    steered, mvmva/GTE ops still compile), while pycparser never chokes on `__asm__`. (No submodule
    edit: this reuses decomp-permuter's OWN b64literal pragma carrier.)"""
    out, i = [], 0
    pat = re.compile(r"\b__asm__\b")
    while True:
        m = pat.search(c, i)
        if not m:
            out.append(c[i:]); break
        a = m.start()
        # statement start = just past the previous ; { } -- captures a `register T x __asm__(...)` pin
        # from `register`, and a bare `__asm__(...)` statement from itself.
        b = max(c.rfind(";", i, a), c.rfind("{", i, a), c.rfind("}", i, a))
        start = b + 1 if b >= 0 else i
        end = _stmt_end(c, a)
        out.append(c[i:start])
        chunk = c[start:end].strip()
        out.append("\n#pragma _permuter b64literal " + base64.b64encode(chunk.encode()).decode() + "\n")
        i = end
    return "".join(out)


def drop_preproc_and_scalar_typedefs(c):
    """Prepare draft C for the permuter/gate: strip scalar/M2C typedef REDEFS (TYPEDEFS/common.h
    provide them) and drop #include (the permuter's preprocess runs `cpp -nostdinc` with no -I, so an
    include can't resolve). KEEP #define (cpp expands it), custom struct/union/fn-ptr typedefs (the
    draft's OWN types -- dropping them left their uses undeclared), and extern callee/data decls (so
    the fn compiles in its REAL signature context)."""
    c = masked_diff.SCALAR_TYPEDEF_RE.sub("", c)
    return "\n".join(ln for ln in c.splitlines() if not ln.lstrip().startswith("#include"))


def make_base_c(draft_c):
    """permuter base.c = scalar typedefs + the draft's custom typedefs/#defines/externs + the
    M2C_FIELD-expanded, asm-hidden body. Keeping externs + custom types is essential: without them the
    permuter matches in a DIFFERENT context than the whole-binary build (-> winners don't byte-gate)."""
    body = expand_m2c_field(draft_c)
    body = hide_asm(body)
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
    # -O0 for the _o0 split subseg (its target bytes are -O0; an -O2 compile can never match them)
    csh = "compile_o0.sh" if asm_subdir.rstrip("/").endswith("_o0") else "compile.sh"
    open(f"{pd}/compile.sh", "w").write(f'#!/bin/bash\nexec {REPO}/tools/permuter/{csh} "$@"\n')
    os.chmod(f"{pd}/compile.sh", 0o755)
    return pd


def run_permuter(pd, secs, j):
    env = dict(os.environ, PATH=f"{REPO}/tools/permuter/bin:" + os.environ["PATH"])
    try:
        # run_masked.py = permuter.py + our floor-free relocation-masked scorer (Phase 24 T2, in-layer
        # rebind of src.main.Scorer; no submodule edit). Scores true masked-.text closeness (reaches 0)
        # instead of the stock mnemonic-diff floor that made the random walk diverge.
        subprocess.run([PY, "tools/permuter/run_masked.py", pd, "-j", str(j), "--stop-on-zero"],
                       cwd=REPO, env=env, capture_output=True, text=True, timeout=secs)
    except subprocess.TimeoutExpired:
        pass
    # kill stragglers
    subprocess.run(["pkill", "-f", "permuter/run_masked.py"], capture_output=True)
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
