#!/usr/bin/env python3
"""Overlay-`.c`-aware source partition (Phase-26 §8b — jr isolation).

The overlay `src/<ov>/*.c` files carry a far richer top-level structure than the
library-region `split_src_region.py` was built for, so its "header = leading
#includes; every following item resolves to one address" model chokes (~922
unresolved). This module parses an overlay `.c` into (header, [Item]) correctly:

  header  = the leading `#include`s + the banner-delimited Phase-17 canonical-sig
            extern layer, preserved verbatim (a file-scope decl layer every split
            piece needs).
  Item    = a leading PREAMBLE (blank lines, `// @class`/comment annotations, and
            *declarations* — `extern` protos, `typedef`/`struct`/`union`/`enum`,
            `#define` — anything that is not itself an addressed anchor) attached
            to the following ADDRESSED ANCHOR, which is one of:
              - a function DEFINITION  (`<type> func_XXXX(...) { ... }`)
              - an `INCLUDE_ASM("asm/...", func_XXXX);` stub
              - a `DEFINE_func_XXXXXXXX()` dedup macro (shared engine-core body)
              - a `#ifdef NON_MATCHING ... #endif` block
            The anchor's address is its `func_XXXX` / `DEFINE_func_XXXX` hex, else a
            `config/symbols.<ov>.txt` lookup.

The definition-vs-declaration discriminator is a forward brace/semicolon scan (NOT
a regex on one line): a *definition* has a `{` body not terminated by `;`; a
*declaration* ends at a top-level `;` before any `{`, or is a braced type ending
`};`. This is what distinguishes `void func_X(void) { ... }` (anchor) from
`s32 func_X(...);  /* extern */` (preamble — the `extern` keyword is omitted, the
line ends in a trailing comment, so an "ends-with-;" test misfires).

Primary consumer: `jr_isolate_all.py` (multi-cut resegment), via `partition()`.
The whole-binary SHA1 byte-gate remains the sole correctness arbiter (G3/P9).
"""
import os
import re
import sys

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))

CANON_OPEN = re.compile(r'/\*\s*=+\s*Phase-\d+ canonical-sig layer')
CANON_CLOSE = re.compile(r'end canonical-sig layer')
INCLUDE_ASM = re.compile(r'^\s*INCLUDE_ASM\("[^"]*",\s*(\w+)\)')
DEFINE_FUNC = re.compile(r'^DEFINE_func_([0-9A-Fa-f]{8})\s*\(')
# a dedup macro whose address is its FIRST arg: SETTER(func_X, ..), RETCONST(func_X, ..)
MACRO_ARG_ANCHOR = re.compile(r'^[A-Za-z_]\w*\(\s*(func_[0-9A-Fa-f]{8})\b')
NONMATCH = re.compile(r'^#if(?:def)?\s+.*NON_MATCHING')


def load_syms(path):
    s = {}
    if not os.path.exists(path):
        return s
    for ln in open(path):
        m = re.match(r"(\w+)\s*=\s*0x([0-9A-Fa-f]+)", ln)
        if m:
            s[m.group(1)] = int(m.group(2), 16)
    return s


def addr_of(name, syms):
    if not name:
        return None
    m = re.match(r'func_([0-9A-Fa-f]{8})$', name)
    if m:
        return int(m.group(1), 16)
    return syms.get(name)


def item_func_name(text):
    """The addressed name for an INCLUDE_ASM / NON_MATCHING item (name is in the
    INCLUDE_ASM macro)."""
    m = re.search(r'INCLUDE_ASM\("[^"]*",\s*(\w+)\)', text)
    return m.group(1) if m else None


def def_name(construct_lines):
    """The defined function's name = the identifier immediately before the first
    params `(` in the (comment/string-stripped) definition signature. Robust to a
    leading banner comment and to multi-line prototypes in a shared preamble (those
    never reach here — scan_construct hands us the definition construct only)."""
    code = []
    in_block = False
    for line in construct_lines:
        c = line
        if in_block:
            if "*/" in c:
                c = c.split("*/", 1)[1]
                in_block = False
            else:
                continue
        c = re.sub(r'/\*.*?\*/', '', c)
        if "/*" in c:
            c = c.split("/*", 1)[0]
            in_block = True
        c = re.sub(r'//.*$', '', c)
        code.append(c)
        if "(" in "".join(code):
            break
    joined = "".join(code)
    m = re.search(r'([A-Za-z_]\w*)\s*\(', joined)
    return m.group(1) if m else None


def _strip(line, in_block):
    """Blank out // and /* */ comments (block state carried) + string/char literals,
    for brace/paren/semicolon token counting. Returns (code, in_block)."""
    c = line
    if in_block:
        if "*/" in c:
            c = c.split("*/", 1)[1]
            in_block = False
        else:
            return "", True
    c = re.sub(r'/\*.*?\*/', '', c)
    if "/*" in c:
        c = c.split("/*", 1)[0]
        in_block = True
    c = re.sub(r'//.*$', '', c)
    c = re.sub(r'"(?:\\.|[^"\\])*"', '""', c)
    c = re.sub(r"'(?:\\.|[^'\\])*'", "''", c)
    return c, in_block


_DECL_KW = ("extern", "typedef", "struct", "union", "enum")


def split_header(lines):
    """Return the number of leading lines that form the header (includes + the
    banner-delimited canonical-sig layer, if present)."""
    n = len(lines)
    i = 0
    while i < n and (lines[i].startswith("#include") or lines[i].strip() == ""):
        i += 1
    if i < n and CANON_OPEN.search(lines[i]):
        while i < n and not CANON_CLOSE.search(lines[i]):
            i += 1
        if i < n:
            i += 1                      # consume the close-marker line
    return i


def scan_construct(lines, i):
    """From top-level line `i`, return (end_exclusive, is_definition).

    Handles, brace/paren/comment/string aware:
      - ANSI function def   `<type> name(<typed args>) { ... }`     -> definition
      - K&R  function def   `<type> name(a, b) <type a; type b;> {` -> definition
      - prototype           `<type> name(...);`                     -> declaration
      - extern / data decl  `extern ...;`  `<type> x;`              -> declaration
      - braced type         `typedef struct { ... } T;`  `struct S {...};` -> decl
    A function header is `name(...)` closed at depth 0; a `;` immediately after its
    `)` is a prototype, a `;` after intervening K&R param decls is not the end, and a
    `{` after the header opens the body. Declarations starting with a decl keyword
    (extern/typedef/struct/union/enum) never become definitions (guards fn-ptr
    typedefs and struct-returning shapes absent from this codebase)."""
    n = len(lines)
    first = lines[i].lstrip()
    force_decl = any(first == k or first.startswith(k + " ") or first.startswith(k + "\t")
                     for k in _DECL_KW)
    paren = brace = 0
    seen_header = False        # closed a depth-0 (...) that is a function header
    body_open = False
    since_header = []          # code chars since the header ) (empty => prototype at ;)
    in_block = False
    j = i
    while j < n:
        code, in_block = _strip(lines[j], in_block)
        for ch in code:
            if ch == '(':
                paren += 1
            elif ch == ')':
                if paren > 0:
                    paren -= 1
                if paren == 0 and brace == 0 and not seen_header and not force_decl:
                    seen_header = True
                    since_header = []
                    continue
            elif ch == '{':
                brace += 1
                if brace == 1:
                    body_open = True
            elif ch == '}':
                if brace > 0:
                    brace -= 1
                if brace == 0 and body_open:
                    if seen_header and not force_decl:
                        return j + 1, True          # function body closed
                    body_open = False               # braced type -> await terminating ;
            elif ch == ';' and paren == 0 and brace == 0:
                if seen_header and not body_open and not force_decl:
                    if "".join(since_header).strip() == "":
                        return j + 1, False          # prototype: )  ;
                    # else: a K&R param decl -> keep scanning for the body {
                else:
                    return j + 1, False              # plain / braced declaration end
            if seen_header and not body_open:
                since_header.append(ch)
        j += 1
    return n, (seen_header and not force_decl) or body_open


def parse_overlay_c(src, syms):
    """Return (header, items) where items = [(addr, name, kind, text)] in file order.
    kind in {asm, define, def, nonmatch, tail}. `tail` = trailing content with no
    following anchor (addr None) — normally absent in a well-formed file."""
    lines = src.split("\n")
    hdr_end = split_header(lines)
    header = "\n".join(lines[:hdr_end])
    n = len(lines)
    items = []
    i = hdr_end
    pre_start = i
    while i < n:
        raw = lines[i]
        s = raw.strip()
        # ---- peel non-anchor prefix lines into the accumulating preamble ----
        if s == "":
            i += 1
            continue
        if s.startswith("//"):
            i += 1
            continue
        if s.startswith("/*"):                      # block comment (1+ lines)
            while i < n and "*/" not in lines[i]:
                i += 1
            i = min(i + 1, n)
            continue
        if s.startswith("#") and not NONMATCH.match(raw):   # #define/#undef/#include...
            while i < n and lines[i].rstrip().endswith("\\"):
                i += 1
            i += 1
            continue
        # ---- now `raw` is a real construct: an anchor or a def/decl ----
        m = INCLUDE_ASM.match(raw)
        if m:
            items.append((addr_of(m.group(1), syms), m.group(1), "asm",
                          "\n".join(lines[pre_start:i + 1])))
            i += 1
            pre_start = i
            continue
        m = DEFINE_FUNC.match(raw)
        if m:
            items.append((int(m.group(1), 16), "func_" + m.group(1), "define",
                          "\n".join(lines[pre_start:i + 1])))
            i += 1
            pre_start = i
            continue
        m = MACRO_ARG_ANCHOR.match(raw)
        if m:                            # SETTER/RETCONST(func_X, ...) dedup macro (1 line)
            items.append((int(m.group(1)[5:], 16), m.group(1), "define",
                          "\n".join(lines[pre_start:i + 1])))
            i += 1
            pre_start = i
            continue
        if NONMATCH.match(raw):
            j = i
            while j < n and not lines[j].startswith("#endif"):
                j += 1
            j = min(j + 1, n)
            name = item_func_name("\n".join(lines[i:j]))
            items.append((addr_of(name, syms), name, "nonmatch",
                          "\n".join(lines[pre_start:j])))
            i = j
            pre_start = i
            continue
        # a definition-or-declaration; classify by forward scan
        j, is_def = scan_construct(lines, i)
        if is_def:
            name = def_name(lines[i:j])
            items.append((addr_of(name, syms), name, "def",
                          "\n".join(lines[pre_start:j])))
            i = j
            pre_start = i
        else:
            i = j                       # declaration => stays in the preamble
    if pre_start < n:
        # preserve the exact trailing chunk (incl. blank lines) so round-trip stays
        # exact; a comment/blank-only chunk is a harmless footer, anything else is a
        # genuine parser gap (kind=tail -> partition() fails loud).
        trailing = "\n".join(lines[pre_start:])
        kind = "footer" if _comment_blank_only(trailing) else "tail"
        items.append((None, None, kind, trailing))
    return header, items


def _comment_blank_only(text):
    """True if `text` is only // / /* */ comments and whitespace."""
    stripped = re.sub(r'/\*.*?\*/', '', text, flags=re.S)
    stripped = re.sub(r'//.*', '', stripped)
    return stripped.strip() == ""


def load_ov_syms(ov):
    """Merge every symbol file the overlay's splat config actually links
    (config's symbol_addrs_path) — us + resident + per-overlay."""
    cfg = os.path.join(REPO, f"config/splat.{ov}.yaml")
    syms = {}
    in_list = False
    for ln in open(cfg):
        if re.match(r'\s*symbol_addrs_path:', ln):
            in_list = True
            continue
        if in_list:
            m = re.match(r'\s*-\s*(\S+)', ln)
            if m and m.group(1).endswith(".txt"):
                syms.update(load_syms(os.path.join(REPO, m.group(1))))
            else:
                break
    if not syms:                        # fallback if the key wasn't found
        syms = load_syms(os.path.join(REPO, "config/symbols.us.txt"))
    return syms


REAL_KINDS = ("def", "define", "nonmatch")     # items splat will NOT regenerate


def rewrite_asm_subseg(text, old_sub, new_sub):
    """Repoint an INCLUDE_ASM stub's path component to the new subseg name."""
    return text.replace(f'/nonmatchings/{old_sub}"', f'/nonmatchings/{new_sub}"')


def partition(srcpath, cuts, syms_path, verbose=True):
    """Split `srcpath` at the sorted vram `cuts` (each = the low bound of a new
    region). Returns [(lo, hi, [item...]), ...] region descriptors WITHOUT writing
    (the caller assigns subseg names + output paths). lo/hi are vram bounds; the
    first region is [start, cuts[0]) and the last is [cuts[-1], +inf)."""
    header, items = parse_overlay_c(open(srcpath).read(), load_syms(syms_path))
    tail = [it for it in items if it[0] is None and it[2] == "tail"]
    if tail:
        sys.exit(f"partition: {srcpath} has unaddressable trailing content:\n"
                 f"{tail[0][3][:160]}")
    footer = [it for it in items if it[2] == "footer"]
    addressed = [it for it in items if it[0] is not None]
    cuts = sorted(set(cuts))
    bounds = [None] + cuts + [None]     # (start,cut0),(cut0,cut1),...,(cutN,end)
    regions = []
    for lo, hi in zip(bounds[:-1], bounds[1:]):
        sel = sorted((it for it in addressed
                      if (lo is None or it[0] >= lo) and (hi is None or it[0] < hi)),
                     key=lambda it: it[0])
        regions.append((lo, hi, sel))
    if footer:                          # documentation footer -> stays with the last region
        lo, hi, sel = regions[-1]
        regions[-1] = (lo, hi, sel + footer)
    if verbose:
        for lo, hi, sel in regions:
            rc = sum(1 for it in sel if it[2] in REAL_KINDS)
            print(f"  region [{'.' if lo is None else hex(lo)},"
                  f"{'.' if hi is None else hex(hi)}): {len(sel)} items ({rc} real-C)")
    return header, regions


# --------------------------------------------------------------------------- CLI
def selftest(srcpath, syms):
    """Round-trip + anchor-order + kind census — proves the parser on a real file."""
    src = open(srcpath).read()
    header, items = parse_overlay_c(src, syms)
    rebuilt = header + "\n" + "\n".join(it[3] for it in items)
    # exact round-trip (allow a single trailing-newline difference)
    ok = rebuilt == src or rebuilt + "\n" == src or rebuilt == src + "\n"
    from collections import Counter
    kinds = Counter(it[2] for it in items)
    addrs = [it[0] for it in items if it[0] is not None]
    unres = [it for it in items if it[0] is None and it[2] != "footer"]
    mono = sum(1 for a, b in zip(addrs, addrs[1:]) if b < a)
    print(f"{os.path.basename(srcpath)}: {len(items)} items {dict(kinds)}")
    print(f"  round-trip exact: {ok}")
    print(f"  addressed: {len(addrs)}  unresolved(non-footer): {len(unres)}  "
          f"non-monotonic transitions: {mono}")
    if unres:
        for it in unres[:5]:
            print(f"    UNRESOLVED [{it[2]}]: {it[3].strip()[:90]}")
    if not ok:
        # locate first divergence for debugging
        a, b = src.split("\n"), rebuilt.split("\n")
        for idx in range(min(len(a), len(b))):
            if a[idx] != b[idx]:
                print(f"  first diff at line {idx+1}:\n    orig: {a[idx][:80]!r}\n"
                      f"    got : {b[idx][:80]!r}")
                break
        print(f"  line counts: orig={len(a)} rebuilt={len(b)}")
    return ok and not unres and mono == 0


def _ov_from_path(p):
    m = re.search(r'src/(ov_\w+?)/', p)
    return m.group(1) if m else None


def main():
    args = sys.argv[1:]
    if len(args) == 2 and args[0] == "selftest":
        ov = _ov_from_path(args[1])
        syms = load_ov_syms(ov) if ov else load_syms(os.path.join(REPO, "config/symbols.us.txt"))
        ok = selftest(args[1], syms)
        sys.exit(0 if ok else 1)
    sys.exit(__doc__)


if __name__ == "__main__":
    main()
