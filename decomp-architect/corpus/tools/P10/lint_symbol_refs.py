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

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import cdecl                      # §134/R33: the ONE comment/string masking oracle
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
    """Blank comments + string/char-literal contents, via the ONE masking oracle (`cdecl._mask`).

    §134 / R33 (P30 S39). This used to be a private char-by-char scanner — correct, but a SECOND
    implementation of the masking `cdecl._mask` already owns, and the §134 class (a line-shape
    decision made against unmasked text) had by then appeared in six tools precisely because each
    one kept its own copy. One oracle cannot diverge from itself.

    Behavioural note, verified before the swap: `_mask` blanks the quote DELIMITERS as well as the
    content, where this scanner kept the quotes. That is irrelevant here — both blank the contents,
    and every token this linter hunts (`func_<ADDR>`, `D_<ADDR>`, and the bare 2nd argument of
    `INCLUDE_ASM("...", func_X)`) lives OUTSIDE the quotes either way. Gated on the linter's own
    output being byte-identical across the change, not on the masks being byte-identical."""
    return cdecl._mask(src)


def main():
    curated, autosym = load_symbols()
    # Blind spot #1: src/shared/*.h (engine_core.h — 10k+ func_/D_ tokens across every overlay) was
    # never scanned, yet one dangling ref there breaks EVERY clean build at once.
    files = sorted(glob.glob(os.path.join(REPO, "src/**/*.c"), recursive=True) +
                   glob.glob(os.path.join(REPO, "src/shared/**/*.h"), recursive=True))
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
    # Blind spot #4 (P31 S78): the §265 verbatim `__asm__("...")` bodies. `strip_comments_strings` blanks
    # every string literal, so a renamed `func_<ADDR>` that survives INSIDE an asm body (`.ent\tfunc_X`,
    # `.end\tfunc_X`, `.globl func_X`, `jal\tfunc_X`, `func_X:`) is invisible above — and gas then dies
    # with `.size expression for func_X does not evaluate to a constant`. Scan the string bodies too,
    # and do NOT rely on `\b`: the literal escape `\t` ends in the word char `t`, so `\tfunc_X` has no
    # word boundary before the token (the exact miss that produced the first S78 red build).
    for cf in files:
        rel = os.path.relpath(cf, REPO)
        raw = open(cf, errors="replace").read()
        for sm in re.finditer(r'__asm__\s*\(((?:\s*"(?:[^"\\]|\\.)*")+)\s*\)', raw):
            body = sm.group(1)
            line0 = raw.count("\n", 0, sm.start()) + 1
            for m in re.finditer(r'(?<![0-9A-Za-z_])(?:func_|D_)([0-9A-Fa-f]{6,8})(?![0-9A-Za-z_])', body):
                a = "0x" + m.group(1).lower()
                if a in autosym or a in asm_labeled:   # blind spot #3 applies here too (memcpy binding)
                    continue
                if a in curated:
                    stale.append((rel, line0, m.group(0) + " (inside __asm__ body)", curated[a]))
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
