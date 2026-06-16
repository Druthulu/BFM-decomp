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


def item_name(text):
    m = re.search(r"INCLUDE_ASM\([^,]+,\s*(\w+)\)", text)
    if m:
        return m.group(1)
    m = re.search(r"^\s*(?:static\s+)?[\w\*]+[\s\*]+(\w+)\s*\(", text, re.M)
    return m.group(1) if m else None


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


def is_real_c(text):
    return "INCLUDE_ASM" not in text or text.startswith("#ifdef NON_MATCHING")


def trim(srcpath, lo, hi, movepath):
    syms = load_syms()
    header, items = parse(open(srcpath).read())
    keep, drop, move = [], 0, []
    for it in items:
        a = item_addr(it, syms)
        if a is None:
            sys.exit(f"trim: cannot resolve address of item:\n{it[:80]}")
        if a < lo:
            keep.append(it)
        elif a < hi:
            drop += 1
        else:
            if is_real_c(it):
                move.append((a, item_name(it), it))
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
    by_name = {item_name(it): it for it in moved}
    dst = open(dstpath).read()
    done = []
    for name, body in by_name.items():
        # replace the whole stub line (optionally wrapped) for this function
        pat = re.compile(r"^INCLUDE_ASM\([^,]+,\s*" + re.escape(name) + r"\);\s*$", re.M)
        if pat.search(dst):
            dst = pat.sub(lambda m: body, dst, count=1)
            done.append(name)
    open(dstpath, "w").write(dst)
    print(f"inject {dstpath}: replaced {len(done)} stubs with matched C: {done}")
    missing = [n for n in by_name if n not in done]
    if missing:
        sys.exit(f"inject: stubs not found for {missing}")


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
