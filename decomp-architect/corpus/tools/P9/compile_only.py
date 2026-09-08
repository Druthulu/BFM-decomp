#!/usr/bin/env python3
"""compile_only.py — compile every eligible C translation unit with the pinned toolchain, WITHOUT the ROM (P33 B7; CI).

    tools/compile_only.py main resident ov_SC01_077 md_MAIN_013     # the PR scope (~124 TUs, ~1 min)
    tools/compile_only.py --all [-j N]                               # every binary (weekly / workflow_dispatch)
    tools/compile_only.py --list main                                # print the plan, compile nothing

What it proves: that the committed C still goes through cpp → gcc-2.7.2 cc1 → maspsx → GNU as with the Makefile's
exact flags (parsed from the Makefile at run time, never retyped — R51). It does NOT prove byte-identity: that needs
the disc (`make check-all`, done locally; docs/verification.md). A TU that fails here is a real regression (a syntax
error, a lost declaration, a header break) and is named.

Which TUs (all DERIVED, R32/R33 — the coverage line says how many of the found TUs each rule removed):
  * a binary's TUs = the Makefile's C_SRCS rule: `find <alias>_SRC_DIR -name '*.c' -not -name '.*'`, pruning every
    OTHER binary's source dir that nests inside it (main = src/ minus src/<other>/ …);
  * SKIP linked  — main's LINKED-region fallback tiles (`progress._main_linked_segs_from_makefile()`, src/<seg>.c): they
    are INCLUDE_ASM stubs whose .s lives in the ROM-derived asm/ tree;
  * SKIP include_asm — any TU with a line-start `INCLUDE_ASM(` / `INCLUDE_RODATA(` (same reason: `.include`s asm/);
  * -O0 TUs (`corpus.o0_sources()`, the Makefile's per-object `CC1FLAGS := … -O0` rules) are COMPILED at -O0, not skipped.
The jump-table rodata pad stage (tools/jtbl_rodata_pads.py) is byte-layout work between maspsx and as and needs the
raw image for `--derive`; it is not part of "does it compile" and is left out here.

Toolchain: mipsel-linux-gnu-cpp / -as on PATH (apt binutils-mipsel-linux-gnu), tools/bin/gcc-2.7.2-psx/cc1 (the tracked
tarball, extracted by tools/bootstrap.sh), tools/maspsx (submodule) under the running Python. No venv needed.
"""
import argparse
import os
import pathlib
import re
import shutil
import subprocess
import sys
import tempfile
import time
from concurrent.futures import ThreadPoolExecutor

REPO = pathlib.Path(__file__).resolve().parent.parent
MK = REPO / "Makefile"
sys.path.insert(0, str(REPO / "tools"))


def mk_var(text, name):
    m = re.search(r"^%s\s*:?=\s*(.*)$" % re.escape(name), text, re.M)
    if not m:
        sys.exit(f"compile_only: cannot find `{name} :=` in the Makefile (R32)")
    return m.group(1).strip()


def src_dirs():
    """alias -> source dir, from `<alias>_SRC_DIR := …` in the Makefile and every config/*.mk it includes."""
    texts = [MK.read_text()] + [p.read_text() for p in sorted((REPO / "config").glob("*.mk"))]
    out = {}
    for t in texts:
        for m in re.finditer(r"^(\w+)_SRC_DIR\s*:?=\s*(\S+)\s*$", t, re.M):
            out[m.group(1)] = m.group(2)
    if "main" not in out or "resident" not in out:
        sys.exit("compile_only: main/resident _SRC_DIR not found (R32)")
    return out


def tus_of(alias, dirs):
    d = REPO / dirs[alias]
    if not d.is_dir():
        sys.exit(f"compile_only: {alias}: source dir {dirs[alias]} does not exist (R43)")
    nested = [REPO / v for a, v in dirs.items() if a != alias and (REPO / v).is_relative_to(d) and (REPO / v) != d]
    out = []
    for p in sorted(d.rglob("*.c")):
        if p.name.startswith("."):
            continue
        if any(p.is_relative_to(n) for n in nested):
            continue
        out.append(p)
    return out


INCLUDE_ASM_RE = re.compile(r"^\s*INCLUDE_(ASM|RODATA)\(", re.M)


def plan(aliases):
    import corpus
    import progress
    dirs = src_dirs()
    linked = {f"src/{s}.c" for s in progress._main_linked_segs_from_makefile()}
    o0 = set(corpus.o0_sources())
    rows = []   # (alias, rel, action)  action in compile-O2 / compile-O0 / skip:linked / skip:include_asm
    for a in aliases:
        for p in tus_of(a, dirs):
            rel = p.relative_to(REPO).as_posix()
            if a == "main" and rel in linked:
                rows.append((a, rel, "skip:linked"))
            elif INCLUDE_ASM_RE.search(p.read_text(errors="replace")):
                rows.append((a, rel, "skip:include_asm"))
            elif rel in o0:
                rows.append((a, rel, "compile-O0"))
            else:
                rows.append((a, rel, "compile-O2"))
    return rows


def toolchain(text):
    cpp = shutil.which(mk_var(text, "MIPS_PREFIX") + "cpp")
    as_ = shutil.which(mk_var(text, "MIPS_PREFIX") + "as")
    cc1 = REPO / mk_var(text, "CC1_PSX")
    maspsx = REPO / mk_var(text, "MASPSX")
    for what, p in (("cpp", cpp), ("as", as_), ("cc1", cc1), ("maspsx", maspsx)):
        if not p or not pathlib.Path(p).exists():
            sys.exit(f"compile_only: {what} not found ({p}) — see tools/bootstrap.sh")
    return dict(
        cpp=[cpp] + mk_var(text, "CPPFLAGS").split(),
        cc1=[str(cc1)], cc1flags=mk_var(text, "CC1FLAGS").split(),
        maspsx=[sys.executable, str(maspsx), f"--aspsx-version={mk_var(text, 'ASPSX_VERSION')}"] + mk_var(text, "MASPSX_FLAGS").split(),
        as_=[as_] + mk_var(text, "ASFLAGS").split(),
    )


def compile_one(tc, rel, action, outdir):
    src = REPO / rel
    obj = outdir / (rel.replace("/", "__") + ".o")
    flags = list(tc["cc1flags"])
    if action == "compile-O0":
        flags = ["-O0" if f == "-O2" else f for f in flags]
    cmd = " | ".join([
        " ".join(tc["cpp"] + [str(src)]),
        " ".join(tc["cc1"] + flags),
        " ".join(tc["maspsx"]),
        " ".join(tc["as_"] + ["-o", str(obj)]),
    ])
    r = subprocess.run(["bash", "-o", "pipefail", "-c", cmd], cwd=REPO, capture_output=True, text=True)
    ok = r.returncode == 0 and obj.exists() and obj.stat().st_size > 0
    err = "\n".join(l for l in r.stderr.splitlines() if "used $at without" not in l)[-1500:]
    return rel, ok, err


def main(argv):
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("aliases", nargs="*")
    ap.add_argument("--all", action="store_true")
    ap.add_argument("--list", action="store_true")
    ap.add_argument("-j", type=int, default=os.cpu_count() or 2)
    a = ap.parse_args(argv)
    text = MK.read_text()
    dirs = src_dirs()
    aliases = sorted(dirs) if a.all else a.aliases
    if not aliases:
        ap.error("name binaries or pass --all")
    for x in aliases:
        if x not in dirs:
            sys.exit(f"compile_only: unknown binary alias {x!r} (R43); known: {len(dirs)} — e.g. main resident ov_SC01_077 md_MAIN_013")
    rows = plan(aliases)
    todo = [r for r in rows if r[2].startswith("compile")]
    skipped = {}
    for _, _, act in rows:
        if act.startswith("skip"):
            skipped[act] = skipped.get(act, 0) + 1
    if a.list:
        for al, rel, act in rows:
            print(f"{act:18} {al:14} {rel}")
    print(f"compile_only: {len(aliases)} binaries, {len(rows)} TUs found; to compile {len(todo)} "
          f"({sum(1 for r in todo if r[2] == 'compile-O0')} at -O0); skipped "
          + (", ".join(f"{k[5:]} {v}" for k, v in sorted(skipped.items())) or "none"))
    if a.list:
        return 0
    tc = toolchain(text)
    outdir = pathlib.Path(tempfile.mkdtemp(prefix="compile_only.", dir=str(REPO / ".run"))) if (REPO / ".run").is_dir() \
        else pathlib.Path(tempfile.mkdtemp(prefix="compile_only."))
    t0 = time.time()
    fails = []
    with ThreadPoolExecutor(max_workers=max(1, a.j)) as ex:
        for rel, ok, err in ex.map(lambda r: compile_one(tc, r[1], r[2], outdir), todo):
            if not ok:
                fails.append((rel, err))
                print(f"  FAIL {rel}\n{err}")
    shutil.rmtree(outdir, ignore_errors=True)
    n_ok = len(todo) - len(fails)
    print(f"compile_only: compiled {n_ok} of {len(todo)} eligible TUs ({len(rows)} found in {len(aliases)} binaries) "
          f"in {time.time() - t0:.1f} s at -j{a.j}; failed {len(fails)}")
    if not todo:
        print("compile_only: nothing eligible — refusing to report success on an empty plan (R43)")
        return 1
    return 1 if fails else 0


if __name__ == "__main__":
    sys.exit(main(sys.argv[1:]))
