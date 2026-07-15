#!/usr/bin/env python3
"""lint_symbol_refs.py — catch stale func_<ADDR> refs that a symbols.us.txt rename left dangling.

The Phase-24 T5b/T5c breakage class: Phase-21 xdedup renamed 62 PsyQ functions to their curated
names (InitHeap, GetTPage, SysEnqIntRP …) in config/symbols.us.txt, but the committed source that
references them by the OLD `func_<ADDR>` name was never updated — both `INCLUDE_ASM(func_<ADDR>)`
stub refs (src/*.c) AND `func_<ADDR>(...)` calls in shared macros (src/shared/engine_core.h). A
GENUINELY-clean rebuild then fails (splat emits `<curated>.s` / provides the symbol only under the
curated name), but INCREMENTAL builds reuse stale .s/.o and mask it (the R22 failure mode). This
went undetected from Phase 21 → 23.

This lint flags every `func_<ADDR>` token in committed src/ whose address has a CURATED (non-`func_`)
name in the symbol files and NO `func_<ADDR>` symbol of its own — i.e. a reference splat/the linker
can no longer resolve under that name. Run it after any symbols rename and in `make report`.

Exit 0 = clean; exit 1 = stale refs found (printed as file:line func_<ADDR> -> curated).
"""
import re, glob, os, sys

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))

# The files a real binary actually stacks (main/resident/overlays). The proto symbol files
# (symbols.proto-*.txt) are R13 UNVERIFIED cross-build data and are NEVER stacked into a build —
# reading them would invent phantom curated names. This is blind spot #2 (the audit read only 2 of
# these): a per-overlay rename must be seen or a genuine dangling ref hides.
def _symbol_files():
    files = []
    for p in sorted(glob.glob(os.path.join(REPO, "config/symbols*.txt"))):
        if "proto" in os.path.basename(p):
            continue
        files.append(p)
    return files


def load_symbols():
    """addr(lower hex) -> curated name (excludes the func_<ADDR>/D_<ADDR> auto-names); and the set
    of addresses that DO have a literal auto-name symbol (those resolve under func_/D_ as written).
    Covers both the func_ (code) and D_ (data) auto-name classes, across every REAL stacked file."""
    curated, autosym = {}, set()
    for p in _symbol_files():
        for m in re.finditer(r'^([A-Za-z_]\w*)\s*=\s*(0x[0-9A-Fa-f]+)', open(p).read(), re.M):
            nm, a = m.group(1), m.group(2).lower()
            if nm.lower() in ("func_" + a[2:], "d_" + a[2:]):
                autosym.add(a)
            else:
                curated.setdefault(a, nm)
    return curated, autosym


# A `func_<ADDR>` / `D_<ADDR>` given an explicit asm label — `extern void func_8005C324(...)
# __asm__("memcpy");` — emits a reference to the LABEL, not to a `func_<ADDR>` symbol, so it resolves
# at link regardless of the rename. This is blind spot #3 (the audit's 43-then-262 false positives are
# entirely this class: engine_core.h's block-copy macro binds func_8005C324 to memcpy via __asm__).
_ASM_LABEL_RE = re.compile(
    r'\b(?:func_|D_)([0-9A-Fa-f]{6,8})\b[^;{}\n]*?__asm__\s*\(\s*"[^"]+"\s*\)')


def asm_labeled_addrs(files):
    out = set()
    for cf in files:
        for m in _ASM_LABEL_RE.finditer(open(cf, errors="replace").read()):
            out.add("0x" + m.group(1).lower())
    return out


def strip_comments_strings(src):
    """blank out /* */ + // comments and string/char-literal CONTENTS (keeping newlines so line
    numbers stay correct), so a `func_<ADDR>` mentioned only in a comment/string isn't flagged.
    A bare INCLUDE_ASM(func_<ADDR>) token lives OUTSIDE the quotes, so it survives."""
    out = []
    i, n = 0, len(src)
    while i < n:
        c = src[i]
        two = src[i:i+2]
        if two == "/*":
            j = src.find("*/", i + 2)
            j = n if j < 0 else j + 2
            out.append("".join(ch if ch == "\n" else " " for ch in src[i:j])); i = j
        elif two == "//":
            j = src.find("\n", i)
            j = n if j < 0 else j
            out.append(" " * (j - i)); i = j
        elif c in '"\'':
            q = c; j = i + 1
            while j < n and src[j] != q:
                j += 2 if src[j] == "\\" else 1
            j = min(j + 1, n)
            out.append(q + " " * (j - i - 2) + q if j - i >= 2 else src[i:j]); i = j
        else:
            out.append(c); i += 1
    return "".join(out)


def main():
    curated, autosym = load_symbols()
    # Blind spot #1: src/shared/*.h (engine_core.h — 10k+ func_/D_ tokens across every overlay) was
    # never scanned, yet one dangling ref there breaks EVERY clean build at once.
    files = sorted(glob.glob(os.path.join(REPO, "src/**/*.c"), recursive=True) +
                   glob.glob(os.path.join(REPO, "src/shared/*.h")))
    asm_labeled = asm_labeled_addrs(files)      # blind spot #3: __asm__("label") resolves the ref
    stale = []
    for cf in files:
        rel = os.path.relpath(cf, REPO)
        code = strip_comments_strings(open(cf, errors="replace").read())
        for i, line in enumerate(code.splitlines(), 1):
            for m in re.finditer(r'\b(?:func_|D_)([0-9A-Fa-f]{6,8})\b', line):
                a = "0x" + m.group(1).lower()
                if a in autosym or a in asm_labeled:   # real auto-name OR bound to a label -> resolves
                    continue
                if a in curated:            # renamed to a curated name, no auto-name symbol -> DANGLING
                    stale.append((rel, i, m.group(0), curated[a]))
    if stale:
        print(f"[lint_symbol_refs] {len(stale)} STALE func_<ADDR> ref(s) — renamed in symbols, "
              f"clean-build will FAIL (fix: rename to the curated name):")
        for rel, i, tok, nm in stale:
            print(f"  {rel}:{i}  {tok} -> {nm}")
        return 1
    print("[lint_symbol_refs] OK — no stale renamed func_<ADDR> refs in committed src/")
    return 0


if __name__ == "__main__":
    sys.exit(main())
