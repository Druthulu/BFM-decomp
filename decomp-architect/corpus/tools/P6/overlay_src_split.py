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
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import cdecl    # the ONE comment/string masking oracle (Phase 26-A) — see _split_macro_body

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))

CANON_OPEN = re.compile(r'/\*\s*=+\s*Phase-\d+ canonical-sig layer')
CANON_CLOSE = re.compile(r'end canonical-sig layer')
INCLUDE_ASM = re.compile(r'^\s*INCLUDE_ASM\("[^"]*",\s*(\w+)\)')
DEFINE_FUNC = re.compile(r'^DEFINE_func_([0-9A-Fa-f]{8})\s*\(')
# a dedup macro whose address is its FIRST arg: SETTER(func_X, ..), RETCONST(func_X, ..)
MACRO_ARG_ANCHOR = re.compile(r'^[A-Za-z_]\w*\(\s*(func_[0-9A-Fa-f]{8})\b')
# Phase 35: a shared body INCLUDED at its site (the header defines the function; a `#define SHARED_FN <name>` in the
# preamble names it for the parameterized form, and a trailing `#undef SHARED_FN` belongs to the same item)
SHARED_INCLUDE = re.compile(r'^#include\s+"((?:\.\./)*shared/[^"]+\.h)"')
SHARED_FN_DEF = re.compile(r'^#define\s+SHARED_FN\s+(\w+)')
SHARED_FN_UNDEF = re.compile(r'^#undef\s+SHARED_FN\b')


def _shared_header_rel(inc):
    """'../shared/ov/x.h' (an overlay TU) or 'shared/x.h' (a main TU) -> 'src/shared/ov/x.h'."""
    return "src/" + re.sub(r'^(\.\./)+', '', inc)


_BODY_INC = {}


def _is_body_include(line):
    """Does this `#include` line pull in a shared header that DEFINES a function (an include-at-site body)?"""
    m = SHARED_INCLUDE.match(line.strip())
    if not m:
        return False
    inc = m.group(1)
    if inc not in _BODY_INC:
        sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
        import share_census
        _BODY_INC[inc] = bool(share_census.header_defs(os.path.join(REPO, _shared_header_rel(inc))))
    return _BODY_INC[inc]


def shared_include_names(inc, preamble_text):
    """The function name(s) an include site defines: the header's definitions, with SHARED_FN resolved from the preamble."""
    sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
    import share_census
    names = []
    for nm, _empty in share_census.header_defs(os.path.join(REPO, _shared_header_rel(inc))):
        if nm == "SHARED_FN":
            m = None
            for ln in preamble_text.split("\n"):
                mm = SHARED_FN_DEF.match(ln.strip())
                if mm:
                    m = mm
            if not m:
                sys.exit(f"overlay_src_split: include of {inc} defines SHARED_FN but no `#define SHARED_FN <name>` precedes it (R43)")
            nm = m.group(1)
        names.append(nm)
    return names
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


# §37/§73 DEFINITION-SIDE ASM-LABEL ALIAS. A body whose byte-true signature conflicts with the
# fleet-canonical decl is banked by giving the DEFINITION a different C identifier and binding the
# emitted SYMBOL with a GNU asm label:
#     void aF8018A860(s32, s16 *, u8 *, u8 *) __asm__("func_80183AF8");   <- decl (stays in preamble)
#     void aF8018A860(s32, s16 *, u8 *, u8 *) { ... }                     <- THIS emits func_80183AF8
# `addr_of` resolved a def by its C NAME, so `aF8018A860` matched neither `func_<hex>` nor `syms`
# and returned None — and `partition()` then DROPPED the item, because it keeps only addressed
# ones. That is SILENT CODE LOSS during a repartition: measured P30 S38, one carve deleted the
# definitions emitting BOTH func_80183AF8 and func_80184268, and the overlay then failed to link
# with `undefined reference` — read for two sessions as a compiler/plumbing wall.
# `family_remap._alias_decl_for` already handled this exact form (and its docstring records the
# same lesson costing 137 sweep skips); the fix was never propagated here. This is the FIFTH tool
# with the same structural blindness — see cookbook §134/§139.
_ALIAS_DECL = re.compile(
    r'\b([A-Za-z_]\w*)\s*\([^;{}]*\)\s*__asm__\s*\(\s*"([^"]+)"\s*\)\s*;', re.S)
# the same shape with the quotes optional — for scanning `cdecl._mask` output, where string content
# AND its delimiters are blanked out.
_ALIAS_SCAN = re.compile(
    r'\b([A-Za-z_]\w*)\s*\([^;{}]*\)\s*__asm__\s*\([^;{}]*\)\s*;', re.S)


def _mask_cpp_directives(text):
    """Length-preserving blank of every preprocessor directive, including `\\` continuations.

    A `#define` body is not C declaration text, but it can look exactly like one. Blanking it is
    the same move `cdecl._mask` makes for comments and strings, for the same reason: a scanner must
    not be able to START a match somewhere the C grammar does not apply. Newlines are preserved so
    offsets and line numbers into the original text remain valid."""
    out, cont = [], False
    for ln in text.split('\n'):
        if cont or ln.lstrip().startswith('#'):
            cont = ln.rstrip().endswith('\\')
            out.append(' ' * len(ln))
        else:
            out.append(ln)
    return '\n'.join(out)


def asm_label_aliases(src):
    """{C identifier -> emitted symbol} for every definition-side asm-label alias in `src`.

    MASK COMMENTS/STRINGS FIRST (§134, R33 — `cdecl._mask` is the ONE masking oracle). Scanning the
    raw text was byte-witnessed wrong the day this was written: `[^;{}]*` is greedy and spans
    newlines, so a match started inside a COMMENT (`… -> MATCH (40 ins)`), ran through the `*/` and
    the blank lines, and swallowed the real declaration — capturing `MATCH` as the identifier while
    the actual alias `aF80146AFC` never entered the map. The same scan also produced `'void': '$2'`
    from a `register u8 *p __asm__("$6")` pin. Both are the §134 class this project has now hit in
    six tools.

    `_mask` is length-preserving, so match spans are valid offsets into the ORIGINAL text — read the
    groups back out of `src` (the mask blanks string CONTENT, so the symbol is only legible there).
    A `$N` target is a hard-register pin, not a symbol alias, and is excluded."""
    # SCAN THE MASKED TEXT, READ THE SYMBOL FROM THE SOURCE.
    # Scanning the source and rejecting bad matches afterwards does NOT work: `finditer` resumes at
    # the END of the match it just yielded, so the greedy comment-spanning match consumes the real
    # declaration below it and rejecting it loses that declaration entirely (byte-witnessed on
    # ov_SC07_006: `aF80146AFC` stayed invisible even with the reject in place). Scanning the mask
    # is what actually prevents a match from STARTING inside a comment.
    # `_mask` also blanks string CONTENT *and its quotes*, so the scan pattern cannot require them —
    # `_ALIAS_SCAN` accepts any `__asm__( … )`, and the real symbol is then read back out of `src`
    # at the same offsets (the mask is length-preserving, which is what makes that legal).
    # ...AND A PREPROCESSOR DIRECTIVE IS THE OTHER PLACE A MATCH MUST NOT START (P30 S47).
    # Masking comments/strings fixed the comment case and left this one. A macro definition
    #     #define gte_SetRotMatrix(r0) __asm__ volatile ( "lw $12, 0( %0 );" … )
    # is textually `ident( … ) __asm__( … )` — indistinguishable from an alias declaration to
    # `_ALIAS_SCAN` — and `_mask` blanks string CONTENT, which DELETES the `;` characters inside
    # those asm strings that would otherwise have stopped the greedy `[^;{}]*`. So the scan starts
    # in the macro body and runs until the next real `;` **116 lines later**, swallowing the genuine
    # `s32 aF8012EFB8(…) __asm__("func_8012EFB8");` on the way; `finditer` resumes past the end, so
    # the alias never enters the map and `addr_of` returns None for its definition.
    # Consequence measured: `jr_isolate_all` refused to carve ov_SC02_037 / ov_SC03_107 / ov_MAIN_012
    # (R32, correctly — it will not rewrite a file it cannot fully place), which left 121 jr
    # functions uncarved and 122 jr member-slots unreachable, presenting as 112 `isolate-fail`s that
    # looked like a per-binary wall.
    # The mask is length-preserving, so offsets into `src` stay valid.
    masked = _mask_cpp_directives(cdecl._mask(src))
    out = {}
    for m in _ALIAS_SCAN.finditer(masked):
        real = _ALIAS_DECL.search(src[m.start():m.end()])
        if not real or real.group(2).startswith('$'):   # `$N` = hard-register pin, not an alias
            continue
        out[real.group(1)] = real.group(2)
    return out


def addr_of(name, syms, aliases=None):
    if not name:
        return None
    m = re.match(r'func_([0-9A-Fa-f]{8})$', name)
    if m:
        return int(m.group(1), 16)
    if name in syms:
        return syms[name]
    if aliases and name in aliases:            # resolve through the EMITTED symbol, not the C name
        return addr_of(aliases[name], syms)
    # D_<hex8> names encode their address exactly like func_<hex8> (splat mints both from the
    # vram). LAST so an explicit symbol-file entry or alias always wins. Without this, a
    # piece-owned island symbol absent from every symbols file (md_MAIN_003's D_800CEDF8 —
    # in no symbols.*.txt) resolved None and the S68 island-vs-object discrimination in
    # jr_isolate_all._rewrite_includes fell through to the blanket repoint (P31 S68).
    m = re.match(r'D_([0-9A-Fa-f]{8})$', name)
    if m:
        return int(m.group(1), 16)
    return None


def item_func_name(text):
    """The addressed name for an INCLUDE_ASM / NON_MATCHING item (name is in the
    INCLUDE_ASM macro)."""
    m = re.search(r'INCLUDE_ASM\("[^"]*",\s*(\w+)\)', text)
    return m.group(1) if m else None


def def_name(construct_lines):
    """The defined function's name = the identifier before the LAST top-level header
    `(` that precedes the body `{`.

    Reading to the `{` (not stopping at the FIRST `(`) makes this robust to a rare but
    real overlay shape: a definition sharing a physical line with preceding
    same-line `extern ...;` declarations (`extern A(...); extern B(...); void f(...){`)
    — those earlier `name(` headers are correctly skipped so we name the DEFINITION,
    not the first extern. K&R parameter declarations carry no `(`, so they never add a
    spurious candidate; and a normal single-def construct has exactly one header `(`,
    so first==last and the result is byte-identical to the previous implementation
    (verified over the whole corpus in A9f)."""
    code = []
    in_block = False
    for line in construct_lines:
        c, in_block = _strip(line, in_block)      # blanks comments AND strings/chars
        code.append(c)
        if "{" in c:
            break
    joined = "".join(code)
    depth = 0
    name = None
    for k, ch in enumerate(joined):
        if ch == '{' and depth == 0:
            break
        if ch == '(':
            if depth == 0:                        # a top-level header ( : the ident before it
                m = re.search(r'([A-Za-z_]\w*)\s*$', joined[:k])
                if m:
                    name = m.group(1)
            depth += 1
        elif ch == ')':
            depth = max(0, depth - 1)
    return name


def _strip(line, in_block):
    """Blank out // and /* */ comments (block state carried) + string/char literals,
    for brace/paren/semicolon token counting. Returns (code, in_block).

    LEFT-TO-RIGHT, BECAUSE WHICHEVER MARKER COMES FIRST WINS (P31 S74). This used to test for
    `/*` BEFORE stripping `//`, so a LINE comment containing `/*` — which our own commentary does
    routinely, e.g.

        //            src/shared/engine_core.h src/*/*.c        (ov_SC07_006_jr_801457A4.c:3968)

    — was read as OPENING a block comment (`src/*` supplies the `/*`). Everything after it then
    stripped to "" until some later `*/`, so `scan_construct` saw blank lines where real
    declarations stood, and `comment_open_at` marked live code as comment interior. Measured: 7
    such lines in 5 tracked sources. Same class as the wrapped-comment defect above — a comment
    model that is right for the common shape and silently wrong for the one in front of it."""
    c = line
    if in_block:
        if "*/" in c:
            c = c.split("*/", 1)[1]
            in_block = False
        else:
            return "", True
    out, i, n = [], 0, len(c)
    while i < n:
        two = c[i:i + 2]
        if two == "//":                      # rest of the line is a comment
            break
        if two == "/*":
            j = c.find("*/", i + 2)
            if j == -1:                      # opens a block comment that wraps
                in_block = True
                break
            i = j + 2
            continue
        out.append(c[i])
        i += 1
    c = "".join(out)
    c = re.sub(r'"(?:\\.|[^"\\])*"', '""', c)
    c = re.sub(r"'(?:\\.|[^'\\])*'", "''", c)
    return c, in_block


def comment_open_at(lines, start_in_block=False):
    """[bool] per line — does this line BEGIN inside an unterminated /* block comment?

    ONE derived model of the file's comment state (R33), consulted by every line-based peeler in
    this module. They used to decide "is this line a comment?" from `line.strip().startswith("/*")`,
    which is blind to the shape that actually occurs 238 times across 193 of our .c files:

        extern void *func_80185C6C(); /* §183 SIGNATURE-adopted-TU;
           calls go through a (s32,s32) function-pointer cast, the TU's own idiom */

    The construct ENDS at its `;`, which is BEFORE the `/*`, so the peeler resumes on the comment's
    CONTINUATION line — and `scan_construct`, entered with in_block=False, reads comment PROSE AS
    CODE. Measured on ov_SC06_029 (P31 S74): `(s32,s32)` in the prose closed a depth-0 paren, so the
    scan latched `seen_header`, every following `;` read as a K&R parameter declaration, and one
    "construct" swallowed 15 lines of preamble up to the next real definition. Two consequences,
    both byte-relevant:
      * parse_overlay_c anchored a `def` item on a pure DECLARATION run (`func_8012C218`, whose
        definition is in the resident, not this TU);
      * def_proto/_proto_from_lines then rendered that run as the definition's "implied prototype",
        emitting `extern #define CALL_80185C6C (...) extern void func_8012C218();` into the §8b
        carried decl layer — `parse error before '#'`, which blocked five independently-MATCHed
        jr bodies from banking in ov_SC06_029 alone.

    A line that begins inside a block comment is never an anchor and never starts a construct, so
    the peelers skip it; the text itself is sliced by line and preserved verbatim either way.

    `start_in_block` is for a chunk that was CUT out of a larger file mid-comment (an item whose
    preceding anchor line opened a wrapped comment): its first line already sits inside one."""
    out, in_block = [], start_in_block
    for ln in lines:
        out.append(in_block)
        _c, in_block = _strip(ln, in_block)
    return out


def _refuse_code_after_comment_close(lines, opens, where=""):
    """R43: refuse a file where a wrapped block comment CLOSES with code after the `*/`.

    Such a line begins inside the comment (so the peelers skip it, above) yet carries a construct
    that would then never anchor — a silent loss, which is exactly the failure mode this module
    keeps paying for. Measured 0 occurrences across the 4,188 sources this parser is run on, so
    refusing costs nothing today and can never become silent later. Split the line if it fires."""
    for k, ln in enumerate(lines):
        if not opens[k] or "*/" not in ln:
            continue
        rest = ln.split("*/", 1)[1]
        if re.sub(r'/\*.*?\*/|//.*$', '', rest).strip():
            raise ValueError(
                "overlay_src_split: %sline %d closes a wrapped block comment and then carries "
                "code on the SAME line (%r). That construct can never anchor — put it on its own "
                "line. (R43: refusing rather than silently dropping it.)"
                % (where, k + 1, ln.strip()[:120]))


_DECL_KW = ("extern", "typedef", "struct", "union", "enum")


def split_header(lines):
    """Return the number of leading lines that form the header (includes + the
    banner-delimited canonical-sig layer, if present)."""
    n = len(lines)
    i = 0
    while i < n and (lines[i].startswith("#include") or lines[i].strip() == ""):
        if _is_body_include(lines[i]):
            break                       # Phase 35: an include that DEFINES a function is that function's site, not header
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
        for p, ch in enumerate(code):
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
                if seen_header and not body_open and not force_decl \
                        and "".join(since_header).strip() != "":
                    pass                             # K&R param decl -> keep scanning for `{`
                elif code[p + 1:].strip():
                    # Another construct follows on the SAME physical line, e.g.
                    # `extern A; extern B; void f(){...}`: this `;` ends a LEADING
                    # declaration, not the whole construct. force_decl was latched from
                    # the FIRST token and must not survive the `;` — re-classify from the
                    # remaining text and keep scanning, so a following DEFINITION anchors
                    # instead of being swallowed into a preamble (A9f; §26-A audit).
                    nxt = code[p + 1:].lstrip()
                    force_decl = any(nxt == k or nxt.startswith(k + " ") or nxt.startswith(k + "\t")
                                     for k in _DECL_KW)
                    seen_header = body_open = False
                    since_header = []
                    continue
                else:
                    return j + 1, False              # prototype `) ;` or plain/braced decl end
            if seen_header and not body_open:
                since_header.append(ch)
        j += 1
    return n, (seen_header and not force_decl) or body_open


def parse_overlay_c(src, syms):
    """Return (header, items) where items = [(addr, name, kind, text)] in file order.
    kind in {asm, define, def, nonmatch, tail}. `tail` = trailing content with no
    following anchor (addr None) — normally absent in a well-formed file."""
    aliases = asm_label_aliases(src)
    lines = src.split("\n")
    hdr_end = split_header(lines)
    header = "\n".join(lines[:hdr_end])
    n = len(lines)
    # THE FILE'S COMMENT STATE IS A DERIVED MODEL, NOT A PER-LINE GUESS (P31 S74, R33). See
    # comment_open_at: the `s.startswith("/*")` test below only ever saw a comment that starts a
    # LINE, so a construct whose TRAILING comment wraps left every peel branch resuming inside it.
    opens = comment_open_at(lines)
    _refuse_code_after_comment_close(lines, opens)
    items = []
    i = hdr_end
    pre_start = i
    while i < n:
        raw = lines[i]
        s = raw.strip()
        # ---- peel non-anchor prefix lines into the accumulating preamble ----
        if opens[i]:                                # interior of a wrapped block comment
            i += 1
            continue
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
        m = SHARED_INCLUDE.match(raw)
        if m:                            # Phase 35: an include-at-site shared body is an ADDRESSED anchor (kind 'include')
            names = shared_include_names(m.group(1), "\n".join(lines[pre_start:i]))
            if len(names) != 1:
                sys.exit(f"overlay_src_split: {m.group(1)} defines {len(names)} functions; an include site must define exactly one (R43)")
            j = i + 1
            while j < n and not lines[j].strip():
                j += 1
            if j < n and SHARED_FN_UNDEF.match(lines[j].strip()):
                i = j                    # the `#undef SHARED_FN` travels with the item
            name = names[0]
            items.append((addr_of(name, syms, aliases), name, "include",
                          "\n".join(lines[pre_start:i + 1])))
            i += 1
            pre_start = i
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
            items.append((addr_of(name, syms, aliases), name, "nonmatch",
                          "\n".join(lines[pre_start:j])))
            i = j
            pre_start = i
            continue
        # a definition-or-declaration; classify by forward scan
        j, is_def = scan_construct(lines, i)
        if is_def:
            name = def_name(lines[i:j])
            items.append((addr_of(name, syms, aliases), name, "def",
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


# --------------------------------------------------- macro-injected file-scope decls
# A `DEFINE_func_XXXXXXXX()` macro (src/shared/engine_core.h) expands AT FILE SCOPE to
#
#     extern <type> <sym>;  ...  (0+ lines)     <-- FILE-SCOPE declarations
#     <type> func_XXXXXXXX(...) { ... }         <-- the definition
#
# so its leading externs are part of the invoking TU's file-scope declaration environment
# — yet they are invisible to any col-0 scan of the `.c` text, because they live in the
# header. This is the §8b scoping wall a mechanical TU split hits: `func_801734BC` uses
# `D_80126B3E`, which is declared `extern s16` ONLY inside `DEFINE_func_80173460`'s macro
# header. Cut the object between them and the core is stranded from its declaration.
#
# Census (2026-07-13): 1801 macros, 1377 with leading decls, 3929 extern lines, 1462
# distinct symbols — and every leading line is an `extern` (no typedefs/structs), so the
# leading section is exactly recoverable. Their types come from engine_types.h/common.h
# (pulled in by engine_core.h at the top of every region), so they need no local-type
# guard. The 148 externs *inside* macro bodies are block-scope loose-typing shadows: they
# expand with the invocation and must NEVER be hoisted.
#
# SETTER/RETCONST (src/shared/ov_setters.h) expand to a bare definition — no externs.
_MACRO_HEADERS = ("src/shared/engine_core.h", "src/shared/ov_setters.h",
                  "src/shared/clearTbl40.h")
_MACRO_OPEN = re.compile(r'^#define\s+([A-Za-z_]\w*)\s*\(')
_INVOKE_RE = re.compile(r'^([A-Za-z_]\w*)\s*\(')
_MACRO_TABLE = None


def _split_macro_body(body):
    """(leading_externs, def_lines) — a macro body's FILE-SCOPE extern lines (everything
    before the definition header) and the definition itself.

    S33: the skip test used to be `startswith("//") or (startswith("/*") and endswith("*/"))`,
    which sees a SINGLE-LINE comment and is blind to a MULTI-LINE block one — its opening line
    does not end `*/` and its middle lines start `*`. The loop then treats that comment line as
    the definition header and returns a TRUNCATED extern set. Measured at the time of the fix:
    38 such lines live in engine_core.h macro bodies (the levers document themselves in block
    comments). Same §134 class fixed in family_remap (S6b D1/D2/D5) and dedup_propagate.find_site
    (S33). Decide on `cdecl._mask` — one oracle (R33), every comment form, immune to a `/*`
    inside a string — with the length-preservation invariant asserted, not assumed (R32)."""
    mbody = cdecl._mask("\n".join(body)).split("\n")
    if len(mbody) != len(body):
        mbody = body
    out = []
    k, n = 0, len(body)
    while k < n:
        s = body[k].strip()
        if mbody[k].strip() == "":
            k += 1
            continue
        if s.startswith("extern"):
            # A DECLARATION MAY WRAP ACROSS CONTINUATION LINES (P30 S47, byte-witnessed):
            #     extern void aF801466F0(u16 a0, …) \
            #         __asm__("func_801466F0"); \
            # Taking one line as one declaration emitted the first half as a `;`-less extern AND
            # then treated `__asm__("func_801466F0");` as THE DEFINITION HEADER — so the proto
            # generator produced `extern __asm__(""); void aF801466F0(…);` in all 22 regions that
            # hoist it. Accumulate until the statement actually terminates, testing the MASKED text
            # so a `;` inside a string or comment cannot end it early.
            # Same line-oriented blindness `family_remap._alias_decl_for` records fixing at S33 for
            # this exact wrapped-alias shape; it was never propagated here (cookbook §134/§139).
            acc = [s]
            while ";" not in mbody[k] and k + 1 < n:
                k += 1
                acc.append(body[k].strip())
            out.append(" ".join(acc))
            k += 1
            continue
        # A `static` DEFINITION inside a macro body is an INTERNAL HELPER, not the macro's
        # principal definition (P30 S47, byte-witnessed). Stopping here returned the helper as
        # "the definition", so `_proto_from_lines` hoisted `extern static inline void
        # tail_8012F274(s32 *in, s32 e);` into all 41 carved regions of ov_SC02_037 — which is
        # BOTH invalid C (`multiple storage classes`) and the wrong function: the macro's exported
        # definition sits BELOW the helper and lost its implied declaration entirely.
        # A static helper needs no hoisted declaration at all: it has internal linkage, and every
        # region that instantiates the macro gets its own copy from the expansion.
        # Skip it brace-balanced (on the MASKED body, so a brace in a string or comment cannot
        # unbalance the scan) and keep looking for the exported definition.
        if re.match(r'static\b', s):
            depth, seen = 0, False
            while k < n:
                depth += mbody[k].count("{") - mbody[k].count("}")
                seen = seen or "{" in mbody[k]
                k += 1
                if seen and depth <= 0:
                    break
            continue
        return out, body[k:]        # the definition header — the body starts here
    return out, []


def _proto_from_lines(lines):
    """`extern <ret> <name>(<params>);` — the file-scope declaration a function DEFINITION
    implies for everything below it in its TU. None if `lines` hold no definition header.

    This is the third decl source a mechanical split loses: in ONE translation unit a
    file-scope definition declares its function for all code below it, so cutting the
    definition into an earlier region strands every later caller that took its address
    (`func_8012B2CC undeclared`). A K&R definition (`void f(a, b) s32 a; s32 b; {`) declares
    an UNPROTOTYPED function, so it must render as `extern void f();` — `(a, b)` is not a
    prototype and `(void)` would be incompatible."""
    # THE CHUNK CAN OPEN INSIDE A BLOCK COMMENT (P30 S48, byte-witnessed). Item boundaries are
    # `;`-terminated, so a decl whose TRAILING comment wraps —
    #     extern void func_80153C18();  /* fleet canon: K&R empty prototype …
    #                                    * … codegen unchanged. */
    #     void func_80151664(void) {
    # — ends its item at the `;` and hands the comment's CONTINUATION to the next item. `_strip`
    # then starts with in_block=False, reads ` * a prototyped …` and `*/` as CODE, and the proto
    # comes out as `extern * a prototyped (s32) decl is `conflicting types` … */ void
    # func_80151664(void);`. It compiled only because the hoist emitted the opening `/*` line
    # immediately above it (the garbage landed back inside a comment) — but `_file_scope_decls`
    # sees a col-0 `extern …;` it cannot type and REFUSES (R32), which is what blocked 23 of the
    # 0b jr member-slots and polluted 16 region files. Same D1 backstop family_remap applies to a
    # carried preamble: a `*/` with no `/*` before it means the text opened inside a comment.
    raw = "\n".join(lines)
    _close = raw.find("*/")
    if _close != -1 and (raw.find("/*") == -1 or raw.find("/*") > _close):
        lines = raw[_close + 2:].split("\n")
    code, in_block = [], False
    for ln in lines:
        c, in_block = _strip(ln, in_block)
        if "{" in c:
            code.append(c.split("{", 1)[0])
            break
        code.append(c)
    header = re.sub(r'\s+', ' ', " ".join(code)).strip()
    name = def_name(lines)
    if not header or not name:
        return None
    m = re.search(r'\b' + re.escape(name) + r'\s*\(', header)
    if not m:
        return None
    open_i = header.index("(", m.end() - 1)
    depth, close = 0, -1
    for k in range(open_i, len(header)):
        if header[k] == "(":
            depth += 1
        elif header[k] == ")":
            depth -= 1
            if depth == 0:
                close = k
                break
    if close < 0:
        return None
    ret = re.sub(r'^extern\s+', '', header[:m.start()]).strip()
    # A FILE-LOCAL DEFINITION KEEPS ITS OWN STORAGE CLASS AND IS NEVER `extern` (P31 S71).
    # `static inline void bandsetup(...)` implies `static inline void bandsetup(...);` — prefixing
    # `extern` produces `extern static inline …`, which cc1 rejects with "multiple storage classes
    # in declaration of `bandsetup'". This surfaced the moment jr_isolate_all started PLACING
    # file-local statics instead of refusing the file, so the two changes belong together.
    params = header[open_i + 1:close].strip()
    if header[close + 1:].strip():          # K&R parameter declarations follow => unprototyped
        params = ""
    if re.match(r'^(static|register|auto)\b', ret):
        return " ".join(x for x in (ret, f"{name}({params});") if x)
    return " ".join(x for x in ("extern", ret, f"{name}({params});") if x)


_MACRO_SIG = re.compile(r'^#define\s+([A-Za-z_]\w*)\s*\(([^)]*)\)')


def macro_table():
    """{macro_name: (params, leading_externs, def_lines)} for every function-body macro in the
    shared headers (cached). `params` are the macro's formal parameter names — SETTER/RETCONST
    take the function name AND its type as arguments (`void name(void *p, ty v)`), so a
    synthesized prototype must substitute the invocation's actual args."""
    global _MACRO_TABLE
    if _MACRO_TABLE is not None:
        return _MACRO_TABLE
    tbl = {}
    for rel in _MACRO_HEADERS:
        path = os.path.join(REPO, rel)
        if not os.path.exists(path):
            continue
        lines = open(path).read().split("\n")
        i = 0
        while i < len(lines):
            m = _MACRO_SIG.match(lines[i])
            if not m:
                i += 1
                continue
            params = [p.strip() for p in m.group(2).split(",") if p.strip()]
            # the macro body = the remainder of the #define line + every `\`-continued line
            body = [re.sub(r'\\\s*$', '', lines[i][m.end():])]
            cont = lines[i].rstrip().endswith("\\")
            i += 1
            while cont and i < len(lines):
                cont = lines[i].rstrip().endswith("\\")
                body.append(re.sub(r'\\\s*$', '', lines[i]))
                i += 1
            externs, def_lines = _split_macro_body(body)
            tbl[m.group(1)] = (params, externs, def_lines)
    _MACRO_TABLE = tbl
    return tbl


def _invocation(item_text):
    """(macro_name, [args]) for a `define`-kind item (its anchor = the last non-blank line)."""
    for line in reversed(item_text.split("\n")):
        s = line.strip()
        if not s:
            continue
        m = _INVOKE_RE.match(s)
        if not m:
            return None, []
        inner = s[m.end():]
        depth, end = 1, -1
        for k, ch in enumerate(inner):
            if ch == "(":
                depth += 1
            elif ch == ")":
                depth -= 1
                if depth == 0:
                    end = k
                    break
        args = [a.strip() for a in inner[:end].split(",")] if end > 0 else []
        return m.group(1), [a for a in args if a]
    return None, []


def _expand(text, params, args):
    """Substitute a macro's formal parameters with the invocation's actual arguments."""
    for p, a in zip(params, args):
        text = re.sub(r'\b' + re.escape(p) + r'\b', a, text)
    return text


_MACRO_NAMES = re.compile(r'^(DEFINE_func_[0-9A-Fa-f]+|SETTER|RETCONST|CLEAR_TBL40)$')


def _table_or_refuse(name):
    """R43 (Phase 35): a macro invocation whose body header is gone or whose name the table lacks is a REFUSAL, never an
    empty expansion — before this, a missing header made macro_table() silently empty and every split wrong."""
    tbl = macro_table()
    if name and _MACRO_NAMES.match(name) and name not in tbl:
        sys.exit(f"overlay_src_split: {name} is invoked but no shared macro header defines it "
                 f"(headers checked: {', '.join(_MACRO_HEADERS)}) — the macro form is gone (Phase 35 T4)? (R43)")
    return tbl.get(name, ([], [], []))


def _include_site(item_text):
    """The shared header an include-kind item includes, else None."""
    for line in reversed(item_text.split("\n")):
        s = line.strip()
        if not s or SHARED_FN_UNDEF.match(s):
            continue
        m = SHARED_INCLUDE.match(s)
        return m.group(1) if m else None
    return None


def _header_text_parts(inc):
    """(leading extern lines, definition lines) of an include-site header — the body form's analogue of a macro's parts."""
    path = os.path.join(REPO, _shared_header_rel(inc))
    lines = open(path, errors="replace").read().split("\n")
    return _split_macro_body(lines)


def macro_externs(item_text):
    """The file-scope extern lines a `define`/`include`-kind item injects ([] if none)."""
    inc = _include_site(item_text)
    if inc:
        externs, _ = _header_text_parts(inc)
        return list(externs)
    name, args = _invocation(item_text)
    params, externs, _ = _table_or_refuse(name)
    return [_expand(e, params, args) for e in externs]


def macro_proto(item_text):
    """The prototype implied by a `define`/`include`-kind item's DEFINITION (None if none)."""
    inc = _include_site(item_text)
    if inc:
        _, def_lines = _header_text_parts(inc)
        return _proto_from_lines(def_lines) if def_lines else None
    name, args = _invocation(item_text)
    params, _, def_lines = _table_or_refuse(name)
    if not def_lines:
        return None
    return _proto_from_lines([_expand(l, params, args) for l in def_lines])


_TYPE_KW = ("typedef", "struct", "union", "enum")


def file_scope_types(item_text):
    """The col-0 TYPE definitions (typedef / struct / union / enum) in an item's text, each a
    complete brace-aware block.

    A file-local type defined in one region is needed by any LATER region whose carried
    prototypes reference it — `extern s32 func_80134310(Vec3s *a0, ...)` is a parse error
    without `typedef struct { s16 x, y, z; } Vec3s;`. Because each region becomes its OWN
    translation unit, re-emitting the typedef is legal (C89 forbids re-defining a typedef
    within one TU, but these are different TUs, and a region never both carries a type as
    ambient and holds its defining item — ambient comes only from strictly earlier regions)."""
    lines = item_text.split("\n")
    n, i, out = len(lines), 0, []
    while i < n:
        ln = lines[i]
        s = ln.strip()
        if not ln or ln[0].isspace() or s.startswith(("//", "/*", "#")):
            i += 1
            continue
        if not any(s == k or s.startswith(k + " ") or s.startswith(k + "\t") for k in _TYPE_KW):
            i += 1
            continue
        j, is_def = scan_construct(lines, i)
        if not is_def:
            out.append("\n".join(lines[i:j]))
        i = max(j, i + 1)
    return out


def def_proto(item_text):
    """The prototype implied by a `def`-kind item's function definition (None if none)."""
    lines = item_text.split("\n")
    n = len(lines)
    # Same derived comment-state model as parse_overlay_c (R33). An ITEM can also OPEN inside a
    # comment — its preceding anchor line wrapped one — so seed the state from the D1 test
    # `_proto_from_lines` already uses: a `*/` with no `/*` before it.
    _c, _o = item_text.find("*/"), item_text.find("/*")
    opens = comment_open_at(lines, start_in_block=(_c != -1 and (_o == -1 or _o > _c)))
    i = 0
    while i < n:                       # peel the preamble to reach the definition construct
        if opens[i]:                   # interior of a wrapped block comment: never a construct
            i += 1
            continue
        s = lines[i].strip()
        if s == "" or s.startswith("//"):
            i += 1
            continue
        if s.startswith("/*"):
            while i < n and "*/" not in lines[i]:
                i += 1
            i = min(i + 1, n)
            continue
        if s.startswith("#"):
            while i < n and lines[i].rstrip().endswith("\\"):
                i += 1
            i += 1
            continue
        j, is_def = scan_construct(lines, i)
        if is_def:
            return _proto_from_lines(lines[i:j])
        i = j
    return None


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
            # An interior YAML comment is NOT the end of the list. Five configs annotate the
            # list body (md_MAIN_001/003/008/011 note WHY symbols.resident.txt is omitted —
            # the A4 law, S45 — and us.exe similarly), and breaking on the comment silently
            # dropped every entry after it: md_MAIN_003 loaded only symbols.us.txt, so
            # D_800D3200 (in symbols.md_MAIN_003.txt) resolved to None and the o0 carve
            # refused with "unaddressable content" (P31 S68).
            if re.match(r'\s*#', ln):
                continue
            m = re.match(r'\s*-\s*(\S+)', ln)
            if m and m.group(1).endswith(".txt"):
                syms.update(load_syms(os.path.join(REPO, m.group(1))))
            else:
                break
    if not syms:                        # fallback if the key wasn't found
        syms = load_syms(os.path.join(REPO, "config/symbols.us.txt"))
    return syms


REAL_KINDS = ("def", "define", "include", "nonmatch")     # items splat will NOT regenerate (include = the Phase-35 site form)


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
    # R32 COVERAGE: a construct we could not place is a DEFECT, never a no-op. `addressed` keeps
    # only items with a resolved vram, so an unresolved def/nonmatch used to vanish from every
    # region — the file was rewritten WITHOUT it and nothing said so (P30 S38: two asm-label-alias
    # definitions deleted by one carve). Fail loud instead.
    lost = [it for it in items if it[0] is None and it[2] not in ("tail", "footer")]
    if lost:
        sys.exit(f"partition: {srcpath} has {len(lost)} construct(s) with no resolvable address — "
                 f"refusing to rewrite the file without them (R32):\n" +
                 "\n".join(f"  kind={it[2]} name={it[1]} :: {it[3].strip()[:110]}" for it in lost[:6]))
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


# --------------------------------------------------------------------------- coverage
_DEF_HDR_RE = re.compile(r'\b(func_[0-9A-Fa-f]{8})\s*\(')


def hidden_definitions(src, items):
    """R32 coverage oracle — INDEPENDENT of scan_construct's line-based classifier.

    The round-trip selftest is a SERIALISATION check, not a coverage one: an
    unrecognised construct is absorbed into the next anchor's preamble, so the
    round-trip stays exact BY CONSTRUCTION even when a definition is never anchored
    (the force_decl-latch bug, §26-A audit). This closes that blind spot by
    over-approximating: every top-level `func_XXXX(...)` header whose body is `{` (a
    real definition — not a `...);` prototype and not a call) MUST be an anchored
    def/define/asm item. Returns the names of any that are not. Empty == clean."""
    stripped, in_block = [], False
    for line in src.split("\n"):
        c, in_block = _strip(line, in_block)
        stripped.append(c)
    code = "\n".join(stripped)
    anchored = {it[0] for it in items if it[2] in ("def", "define", "include", "asm", "nonmatch")}
    missed = []
    for m in _DEF_HDR_RE.finditer(code):
        k = m.end() - 1                          # index of the header (
        depth = 0
        while k < len(code):                     # find its matching )
            if code[k] == '(':
                depth += 1
            elif code[k] == ')':
                depth -= 1
                if depth == 0:
                    break
            k += 1
        # a DEFINITION: the header ) is followed (after optional K&R `type var;` decls)
        # by `{`; a prototype/call is followed by `;`. Over-approximate deliberately.
        if not re.match(r'\s*(?:[A-Za-z_][\w\s,*]*;\s*)*\{', code[k + 1:]):
            continue
        addr = int(m.group(1)[5:], 16)
        if addr not in anchored:
            missed.append(m.group(1))
    return missed


# --------------------------------------------------------------------------- CLI
def selftest(srcpath, syms):
    """Round-trip + anchor-order + kind census + coverage — proves the parser on a file."""
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
    hidden = hidden_definitions(src, items)      # R32: swallowed definitions (serialisation-blind)
    print(f"{os.path.basename(srcpath)}: {len(items)} items {dict(kinds)}")
    print(f"  round-trip exact: {ok}")
    print(f"  addressed: {len(addrs)}  unresolved(non-footer): {len(unres)}  "
          f"non-monotonic transitions: {mono}  swallowed-defs: {len(hidden)}")
    if unres:
        for it in unres[:5]:
            print(f"    UNRESOLVED [{it[2]}]: {it[3].strip()[:90]}")
    if hidden:
        print(f"    SWALLOWED DEFINITION(S) (a coverage defect, not a no-op): {hidden[:8]}")
    if not ok:
        # locate first divergence for debugging
        a, b = src.split("\n"), rebuilt.split("\n")
        for idx in range(min(len(a), len(b))):
            if a[idx] != b[idx]:
                print(f"  first diff at line {idx+1}:\n    orig: {a[idx][:80]!r}\n"
                      f"    got : {b[idx][:80]!r}")
                break
        print(f"  line counts: orig={len(a)} rebuilt={len(b)}")
    return ok and not unres and mono == 0 and not hidden


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
