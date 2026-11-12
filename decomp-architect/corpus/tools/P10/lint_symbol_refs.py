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
P3.43 T9.c8: binary-scoped. A src file rename_sym maps to binaries is checked against those binaries'
own splat symbol stacks only; unmapped files (most shared headers) keep the repo-wide check. `--selftest` = fixtures.

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


def iter_symbol_defs(text):
    """The ONE symbol-file line parser: yields (name, addr lower-hex '0x...') per `Name = 0xADDR;` line.
    P3.42 T2: split out of load_symbols so tools/rename_scan.py reads symbol files the same way."""
    for m in re.finditer(r'^([A-Za-z_]\w*)\s*=\s*(0x[0-9A-Fa-f]+)', text, re.M):
        yield m.group(1), m.group(2).lower()


def load_symbols():
    """addr(lower hex) -> curated name (excludes the func_<ADDR>/D_<ADDR> auto-names); and the set
    of addresses that DO have a literal auto-name symbol (those resolve under func_/D_ as written).
    Covers both the func_ (code) and D_ (data) auto-name classes, across every REAL stacked file."""
    curated, autosym = {}, set()
    for p in _symbol_files():
        for nm, a in iter_symbol_defs(open(p).read()):
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
    return asm_labeled_in_texts(open(cf, errors="replace").read() for cf in files)


def asm_labeled_in_texts(texts):
    out = set()
    for raw in texts:
        for m in _ASM_LABEL_RE.finditer(raw):
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


def load_binary_symbols():
    """P3.43 T9.c8 (C0571): {binary: (curated, autosym)} over each binary's OWN splat symbol stack
    (rename_scan.symbol_stacks(), first file in stack order names an address), so an address curated in
    one overlay does not make another binary's func_/D_ token read stale. Proto files are never stacked."""
    import rename_scan
    real = {rename_scan._alias(p): p for p in _symbol_files()}
    per_alias, out = {}, {}
    for b, stack in rename_scan.symbol_stacks().items():
        cur, auto = {}, set()
        for fa in stack:
            if fa not in real:
                continue
            if fa not in per_alias:
                per_alias[fa] = list(iter_symbol_defs(open(real[fa]).read()))
            for nm, a in per_alias[fa]:
                if nm.lower() in ("func_" + a[2:], "d_" + a[2:]):
                    auto.add(a)
                else:
                    cur.setdefault(a, nm)
        out[b] = (cur, auto)
    return out


def _stale_name(a, maps, asm_labeled):
    """-> the curated name making address `a` dangle under `maps` = [(curated, autosym)] (one per binary the
    file is built into; stale if ANY of them has `a` curated without an auto-name), else None."""
    if a in asm_labeled:                    # bound to a label -> resolves
        return None
    for curated, autosym in maps:
        if a not in autosym and a in curated:   # renamed to a curated name, no auto-name symbol -> DANGLING
            return curated[a]
    return None


def stale_refs(curated, autosym, sources, scoped=None):
    """The checker over given text (P3.42 T2: importable by tools/rename_scan.py --selftest).
    sources = [(relpath, raw text)]; returns [(rel, line, token, curated name)] in scan order.
    scoped (P3.43 T9.c8) = {relpath: [(curated, autosym)] per binary the file is built into}: a mapped file is
    checked against its own binaries' stacks only; a file absent from it uses the repo-wide (curated, autosym)."""
    asm_labeled = asm_labeled_in_texts(raw for _, raw in sources)   # blind spot #3: __asm__("label") resolves the ref
    scoped = scoped or {}
    stale = []
    for rel, raw in sources:
        maps = scoped.get(rel) or [(curated, autosym)]
        code = strip_comments_strings(raw)
        for i, line in enumerate(code.splitlines(), 1):
            for m in re.finditer(r'\b(?:func_|D_)([0-9A-Fa-f]{6,8})\b', line):
                nm = _stale_name("0x" + m.group(1).lower(), maps, asm_labeled)
                if nm:                      # real auto-name OR bound to a label -> resolves; else DANGLING
                    stale.append((rel, i, m.group(0), nm))
    # Blind spot #4 (P31 S78): the §265 verbatim `__asm__("...")` bodies. `strip_comments_strings` blanks
    # every string literal, so a renamed `func_<ADDR>` that survives INSIDE an asm body (`.ent\tfunc_X`,
    # `.end\tfunc_X`, `.globl func_X`, `jal\tfunc_X`, `func_X:`) is invisible above — and gas then dies
    # with `.size expression for func_X does not evaluate to a constant`. Scan the string bodies too,
    # and do NOT rely on `\b`: the literal escape `\t` ends in the word char `t`, so `\tfunc_X` has no
    # word boundary before the token (the exact miss that produced the first S78 red build).
    for rel, raw in sources:
        maps = scoped.get(rel) or [(curated, autosym)]
        for sm in re.finditer(r'__asm__\s*\(((?:\s*"(?:[^"\\]|\\.)*")+)\s*\)', raw):
            body = sm.group(1)
            line0 = raw.count("\n", 0, sm.start()) + 1
            for m in re.finditer(r'(?<![0-9A-Za-z_])(?:func_|D_)([0-9A-Fa-f]{6,8})(?![0-9A-Za-z_])', body):
                nm = _stale_name("0x" + m.group(1).lower(), maps, asm_labeled)  # blind spot #3 applies here too
                if nm:
                    stale.append((rel, line0, m.group(0) + " (inside __asm__ body)", nm))
    return stale


def file_scopes(rels):
    """-> {rel: [(curated, autosym)]} for the src files rename_sym maps to binaries (src_binaries; shared headers via
    dedup group members); unmapped files are left out (repo-wide check)."""
    import rename_sym, rename_scan
    stacks = rename_scan.symbol_stacks()
    bins = load_binary_symbols()
    reg = rename_sym.load_groups()[1]
    aliases, stackers = rename_sym._aliases(), rename_sym.stackers_of(stacks)
    out = {}
    for rel in rels:
        fb = sorted(b for b in rename_sym.file_binaries(rel, reg, aliases, stackers) if b in bins)
        if fb:
            out[rel] = [bins[b] for b in fb]
    return out


def selftest():
    """P3.43 T9.c8: an overlay's name for an address must not flag another binary's auto-name token."""
    ov = ({"0x80146ca0": "guess_NextStep"}, set())
    other = ({}, {"0x80146ca0"})
    src = "void f(void){\n    func_80146CA0();\n}\n"
    srcs = [("src/sc01/a.c", src), ("src/sc02/b.c", src), ("src/shared/x.h", src)]
    sc = {"src/sc01/a.c": [ov], "src/sc02/b.c": [other]}
    st = stale_refs(*ov, srcs, sc)
    assert [(s[0], s[1], s[3]) for s in st] == [("src/sc01/a.c", 2, "guess_NextStep"),
                                                ("src/shared/x.h", 2, "guess_NextStep")], st  # unmapped: repo-wide
    assert stale_refs(*ov, srcs[1:2], {"src/sc02/b.c": [other, ov]})[0][3] == "guess_NextStep"  # ANY binary dangles
    assert stale_refs(*ov, srcs) == stale_refs(*ov, srcs, {})                # no scopes = today's behaviour
    print("[lint_symbol_refs] selftest OK")
    return 0


def main():
    if sys.argv[1:] == ["--selftest"]:
        return selftest()
    curated, autosym = load_symbols()
    # Blind spot #1: src/shared/*.h (engine_core.h — 10k+ func_/D_ tokens across every overlay) was
    # never scanned, yet one dangling ref there breaks EVERY clean build at once.
    files = sorted(glob.glob(os.path.join(REPO, "src/**/*.c"), recursive=True) +
                   glob.glob(os.path.join(REPO, "src/shared/**/*.h"), recursive=True))
    sources = [(os.path.relpath(cf, REPO), open(cf, errors="replace").read()) for cf in files]
    stale = stale_refs(curated, autosym, sources, file_scopes([rel for rel, _ in sources]))
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
