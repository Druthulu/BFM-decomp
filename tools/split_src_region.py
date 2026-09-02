#!/usr/bin/env python3
"""Split a splat src/*.c at vram boundaries, preserving matched C and NON_MATCHING blocks (H5).

When a text subsegment is resegmented (e.g. to swap a library region's stubs for real objects),
the existing curated .c must be trimmed and its matched functions relocated — splat will NOT
overwrite an existing .c, so a stale .c would place functions at the wrong addresses. This tool
partitions the file's top-level items (INCLUDE_ASM stubs, real C functions, and #ifdef
NON_MATCHING blocks) by each item's vram:

  trim <src.c> <lo> <hi> <move.frag>
     rewrite <src.c> keeping only items with vram < lo (the header is preserved verbatim);
     items in [lo, hi) are dropped (superseded by the linked objects); real-C items with
     vram >= hi are written to <move.frag> for injection into the post-region file.

  inject <dst.c> <move.frag>
     in the freshly splat-generated <dst.c>, replace each moved function's INCLUDE_ASM stub
     with its real C body (matched by function name).

Item vram comes from a func_XXXXXXXX name, else a name looked up in config/symbols.us.txt.
Brace matching is naive (counts {}); the build's SHA1 check is the backstop if an item with
string-literal braces is mis-split.
"""
import re, sys

SYMS_PATH = "config/symbols.us.txt"


def load_syms():
    s = {}
    for ln in open(SYMS_PATH):
        m = re.match(r"(\w+)\s*=\s*0x([0-9A-Fa-f]+)", ln)
        if m:
            s[m.group(1)] = int(m.group(2), 16)
    return s


_COMMENT = re.compile(r"/\*.*?\*/", re.S)
# A declarator keyword is never the symbol (mirrors gate_main._NOT_A_SYMBOL).
_NOT_A_SYMBOL = {"void", "char", "short", "int", "long", "float", "double", "signed", "unsigned",
                 "const", "volatile", "struct", "union", "enum", "static", "extern", "register",
                 "typedef", "s8", "u8", "s16", "u16", "s32", "u32", "s64", "u64", "f32", "f64",
                 "if", "for", "while", "switch", "return", "else", "do"}


def item_name(text):
    """The declared name of a top-level item, read from CODE only.

    COMMENTS ARE STRIPPED FIRST (P31 S72). The definition regex runs with re.M over the WHOLE item,
    and an item begins with its leading comment block — so a comment containing any parenthesised
    token (`harvest_verify(...)`, `func_x()`, even prose with brackets) matched BEFORE the real
    definition below it. The name then failed to resolve to an address, `coalesce` treated a real
    FUNCTION as an address-less preamble and merged it into its neighbour, and `inject` reported
    9 functions whose stubs it could not find — while their bodies sat in the file, carried inside
    another item. Two bugs with one cause: a pattern that scans prose as if it were code."""
    m = re.search(r"INCLUDE_ASM\([^,]+,\s*(\w+)\)", text)
    if m:
        return m.group(1)
    code = _COMMENT.sub("", text)
    code = re.sub(r"^\s*//[^\n]*$", "", code, flags=re.M)
    # MATCH THE DEFINITION, NOT A DECLARATION ABOVE IT (P31 S72; the §192 class, which
    # `gate_main.sym_of` fixed for itself and this tool never got). `parse` folds a run of leading
    # `extern` lines into the following function's item, and the old pattern matched the FIRST
    # line: `extern void (*D_80196184[])(void);` returned the name "void", which resolves to no
    # address, so `coalesce` treated a REAL FUNCTION as a preamble and merged it into its
    # neighbour. The body then landed inside another item while its own stub survived — 26
    # functions in one overlay with BOTH a definition and a stub, i.e. duplicate symbols at
    # assembly time. A definition ends in `{`; a declaration ends in `;`. Anchor on that, and
    # never accept a type keyword as the name.
    # LEADING WHITESPACE IS ALLOWED: agent-written bodies are sometimes indented at top level, and
    # a column-0 anchor made `    void func_8018B410(u8 *a0) {` invisible — the item then had no
    # name, no address, and was merged into its neighbour as if it were a preamble. Indented
    # CONTROL FLOW cannot be mistaken for a definition because `_NOT_A_SYMBOL` excludes
    # if/for/while/switch/do, and a call statement ends in `;` rather than `{`.
    for m in re.finditer(r"^[ \t]*[A-Za-z_][\w \t\*]*?\b(\w+)\s*\([^;{]*\)\s*\{", code, re.M):
        if m.group(1) not in _NOT_A_SYMBOL:
            return m.group(1)
    return None


def item_addr(text, syms):
    name = item_name(text)
    if name:
        m = re.match(r"func_([0-9A-Fa-f]{8})$", name)
        if m:
            return int(m.group(1), 16)
        if name in syms:
            return syms[name]
    return None


def parse(src):
    """Return (header, [item_text, ...]) splitting top-level items."""
    lines = src.split("\n")
    n = len(lines)
    i = 0
    while i < n and (lines[i].startswith("#include") or lines[i].strip() == ""):
        i += 1
    header = "\n".join(lines[:i]).rstrip("\n")
    items = []
    while i < n:
        if lines[i].strip() == "":
            i += 1
            continue
        start = i
        # leading line/block comments belong to the following item
        while i < n and (lines[i].lstrip().startswith("//") or lines[i].lstrip().startswith("/*")
                         or lines[i].lstrip().startswith("*")):
            if lines[i].lstrip().startswith("/*") and "*/" not in lines[i]:
                while i < n and "*/" not in lines[i]:
                    i += 1
            i += 1
        if i >= n:
            break
        l = lines[i]
        if l.startswith("#ifdef NON_MATCHING"):
            while i < n and not lines[i].startswith("#endif"):
                i += 1
            i += 1
        elif l.lstrip().startswith("INCLUDE_ASM"):
            i += 1
        else:
            depth = 0
            seen = False
            while i < n:
                depth += lines[i].count("{") - lines[i].count("}")
                if "{" in lines[i]:
                    seen = True
                i += 1
                if seen and depth <= 0:
                    break
        items.append("\n".join(lines[start:i]))
    return header, items


def _norm_ws(s):
    return re.sub(r"\s+", " ", s).strip()


def is_real_c(text):
    return "INCLUDE_ASM" not in text or text.startswith("#ifdef NON_MATCHING")


def coalesce(items, syms):
    """Merge address-LESS top-level items into the item that follows them. -> ([item], n_merged).

    WHY (P31 S72). `parse` yields one item per top-level construct, and `trim` demanded an address
    for every one. But an overlay `.c` is full of constructs that HAVE no address — a hoisted
    typedef block, a per-function `extern` run, a `/* HOISTED (P31 S54) ... */` banner — so `trim`
    exited with "cannot resolve address of item" and `jr_isolate` has been BLOCKED on it since
    Phase 26, which is why the overlays that need a subseg split never got one.

    The fix is the model, not the regex: those constructs are a PREAMBLE belonging to the function
    BELOW them (that is where the author put them, and it is what makes a leading `extern` block
    travel with the body that uses it). So they are not separate items at all — merge each run
    forward into the next addressed item, and the "one item = one address" invariant holds again.
    A trailing run at EOF has nothing below it and attaches to the previous item instead.

    NOT PERFECT, AND DELIBERATELY SO: a declaration used by functions on BOTH sides of the cut
    follows the first one and the other side loses it. That is the same 57-crossing-declarations
    problem main's split hit, and the answer there is the answer here — let the COMPILER enumerate
    what is missing and lift those few into a shared header (cookbook §431). This function reports
    how many preambles it moved so that risk is visible rather than silent.

    RETURNS (addr, name, text) TRIPLES, not text. The address and name are captured from the
    ADDRESSED item BEFORE the merge and carried; re-deriving them from the merged text is wrong,
    because `item_name` scans from the top and would match the preamble's prose instead of the
    function below it — which is exactly how the first version of this failed, on the very
    `/* HOISTED ... */` banner it was written to handle.
    """
    out, buf, merged = [], [], 0
    for it in items:
        a = item_addr(it, syms)
        if a is None:
            buf.append(it); continue
        text = "\n\n".join(buf + [it]) if buf else it
        merged += len(buf); buf = []
        out.append((a, item_name(it), text))          # name from the ITEM, not the merged text
    if buf:                       # trailing preamble: nothing below it, so it stays with the last item
        if out:
            a, nm, text = out[-1]
            out[-1] = (a, nm, "\n\n".join([text] + buf)); merged += len(buf)
        else:
            return [], 0          # a file with NO addressed item at all -> caller refuses
    return out, merged


def trim(srcpath, lo, hi, movepath):
    syms = load_syms()
    header, items = parse(open(srcpath).read())
    triples, merged = coalesce(items, syms)
    if not triples:
        sys.exit(f"trim: {srcpath} has no address-bearing top-level item — refusing (R43).")
    if merged:
        print(f"trim: attached {merged} address-less preamble item(s) (comments / extern / typedef "
              f"runs) to the function below them — see coalesce(); if the build then reports a "
              f"missing declaration, lift that one into a shared header (§431).")
    keep, drop, move = [], 0, []
    for a, nm, it in triples:
        if a < lo:
            keep.append(it)
        elif a < hi:
            drop += 1
        else:
            if is_real_c(it):
                move.append((a, nm, it))
    open(srcpath, "w").write(header + "\n\n" + "\n\n".join(keep) + "\n")
    move.sort()
    with open(movepath, "w") as f:
        f.write("\n\n".join(it for _, _, it in move) + "\n")
    print(f"trim {srcpath}: kept {len(keep)} (<0x{lo:X}), dropped {drop} stubs/superseded "
          f"[0x{lo:X},0x{hi:X}), moved {len(move)} real-C funcs (>=0x{hi:X}) -> {movepath}")
    for a, nm, _ in move:
        print(f"    move 0x{a:08X} {nm}")


def inject(dstpath, movepath):
    _, moved = parse(open(movepath).read())
    triples, _ = coalesce(moved, load_syms())    # same model on the way back in
    by_name = {nm: it for _a, nm, it in triples if nm}
    dst = open(dstpath).read()
    done = []
    for name, body in by_name.items():
        # replace the whole stub line (optionally wrapped) for this function
        pat = re.compile(r"^INCLUDE_ASM\([^,]+,\s*" + re.escape(name) + r"\);\s*$", re.M)
        if pat.search(dst):
            dst = pat.sub(lambda m: body, dst, count=1)
            done.append(name)
    # A TRIVIAL FUNCTION HAS NO STUB TO REPLACE, AND THAT IS NOT A FAILURE (P31 S72).
    # splat emits an EMPTY function (`jr $ra; nop`) as real C directly rather than as an
    # INCLUDE_ASM stub, so the freshly-generated destination already DEFINES it — measured here:
    # 251 stubs and 9 real-C definitions, and inject hard-exited on all 9 while the bodies it
    # wanted to write were already present and textually identical. Accept that case, but only
    # after PROVING equivalence: a destination definition that DIFFERS from the moved one is a
    # genuine conflict and still fails, because silently keeping the wrong body is how a split
    # produces a binary that builds and is not byte-identical.
    already, conflict = [], []
    for name in [n for n in by_name if n not in done]:
        dm = re.search(r"^[A-Za-z_][^\n]*\b%s\s*\([^)]*\)\s*\{[^}]*\}" % re.escape(name),
                       dst, re.M)
        if not dm:
            conflict.append((name, "no stub and no definition in the destination"))
        elif _norm_ws(dm.group(0)) == _norm_ws(by_name[name]):
            already.append(name)
        else:
            conflict.append((name, "destination defines it DIFFERENTLY"))
    open(dstpath, "w").write(dst)
    print(f"inject {dstpath}: replaced {len(done)} stubs with matched C: {done}")
    if already:
        print(f"inject: {len(already)} function(s) already present in the destination and textually "
              f"IDENTICAL (splat emits trivial/empty functions as C, not as a stub): {already}")
    if conflict:
        sys.exit("inject: " + "; ".join(f"{n} — {why}" for n, why in conflict))


def main():
    global SYMS_PATH
    args = sys.argv[1:]
    if "--symbols" in args:                       # Phase 9: per-binary symbol file (default = the EXE's)
        k = args.index("--symbols"); SYMS_PATH = args[k + 1]; del args[k:k + 2]
    if len(args) >= 5 and args[0] == "trim":
        trim(args[1], int(args[2], 0), int(args[3], 0), args[4])
    elif len(args) == 3 and args[0] == "inject":
        inject(args[1], args[2])
    else:
        sys.exit(__doc__)


if __name__ == "__main__":
    main()
