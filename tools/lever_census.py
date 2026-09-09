#!/usr/bin/env python3
"""lever_census.py — the census of every COMPILER-FORCING CONSTRUCT ("lever") in the fleet's C, and the Phase-36 gate
(Phase 36 T1, 2026-09-09).

    tools/lever_census.py                 # the census: summary + controls to stdout; .run/P36/census/{lever_census.json,lever_census.txt}
    tools/lever_census.py --check         # the mid-campaign gate: every surviving pin / asm statement carries `// !FAKE:` -> exit 1 otherwise
    tools/lever_census.py --check --strict   # the close gate: 0 register pins and 0 asm statements outside the GTE header -> exit 1 otherwise
    tools/lever_census.py --selftest      # the R39 fixture: every class and every decoy, in memory, no tree needed
    tools/lever_census.py --sites         # also write every site to .run/P36/census/lever_sites.jsonl (scratch; the delever ledger's input)

WHAT A LEVER IS (Drew, gate 1 of Phase 36): any construct that exists only to force the compiler's output —
    A  register pins        `register T x __asm__("$N");`  (also `asm(`/`__asm(` spellings, bare names like "a0", "$0" zero-register
                            variables, initializers, volatile/pointer qualifiers)
    B  asm statements       `__asm__ [__volatile__] ("template" : outputs : inputs : clobbers)` — kinds: barrier (empty template, no
                            operands or clobbers only), launder (empty template, "=r"(x) : "0"(x)), keepalive (empty template, inputs only),
                            instruction (a real mnemonic — hand-placed code), gte (a coprocessor-2 op: Sony's own idiom, CONSOLIDATED not
                            removed); a use of a macro whose body is one of those counts as that kind (via the macro)
    C  volatile levers      casts `(volatile T *)`, declarations inside bodies, file-scope declarations, parameters
    D  bare `register`      `register T x;` with no asm clause
    E  asm-label aliases    `extern T name(...) __asm__("symbol");` — deferred to the types phase (censused, not a Phase-36 lever)
    F  builtins             `__builtin_memcpy`, `__builtin_abs` — deferred (censused)
    G  attributes           `__attribute__((...))` — deferred (censused)
NOT levers (excluded by the manifest, never by a regex): the five hand-written 1998 assembly routines of config/verbatim_manifest.json.

HOW IT COUNTS (R32/R33). Function bodies come from share_census.scan_text (the masked-text scanner the S1 gate trusts): comments
become spaces, dead `#if 0` halves and `#define ... \\` continuation blocks are blanked, line numbers hold. Over the masked LIVE text
every token of interest (asm keyword, register, volatile, __builtin_*, __attribute__) receives exactly ONE role; a token no rule
claims is UNCLASSIFIED and fails the run. Coverage is asserted per line against the RAW text: live tokens + tokens inside macro
continuation blocks + tokens in comments/dead code == raw tokens, for every token class, or the run fails. Every site records its
TU, the binaries that compile it (a twin builds its primary's TU), the function, the line, the kind, the register or mnemonic,
and whether a `// !FAKE:` marker sits on its line or the line above (the mid-campaign honesty marker, gen3-standards §2).
Distinct bodies are counted with func_/D_ addresses normalized (the Phase-35 cross-address classes): an edit decided on one
exemplar replays to its copies.

R41: every number names its denominator. The summary JSON and the table are tracked evidence; lever_sites.jsonl and the scan
cache are ignored scratch.
"""
import argparse
import collections
import hashlib
import json
import os
import pathlib
import re
import sys
import time
from concurrent.futures import ProcessPoolExecutor

REPO = pathlib.Path(__file__).resolve().parent.parent
sys.path.insert(0, str(REPO / "tools"))
import share_census as sc  # noqa: E402  (mask_text, scan_text, fleet_and_dirs, twin_of_map, verbatim_instances, curated_names)

OUT_DIR_DEFAULT = ".run/P36/census"
TOOL_STAMP = hashlib.sha1(pathlib.Path(__file__).read_bytes()).hexdigest()[:10]   # the walker's own text: part of the cache key
GTE_HEADER_DEFAULT = "include/gte_inline.h"          # T5 writes it; until then no file is exempt from --strict

# ----------------------------------------------------------------------------------------------------------------------
# tokens
# ----------------------------------------------------------------------------------------------------------------------
ASM_KW = re.compile(r"\b(?:__asm__|__asm|asm)\b(?=\s*(?:\(|__volatile__\b|volatile\b))")
REGISTER_KW = re.compile(r"\bregister\b")
VOLATILE_KW = re.compile(r"\bvolatile\b")
BUILTIN_KW = re.compile(r"__builtin_\w+")
ATTR_KW = re.compile(r"__attribute__")
TOKEN_CLASSES = {"asm": ASM_KW, "register": REGISTER_KW, "volatile": VOLATILE_KW, "builtin": BUILTIN_KW, "attribute": ATTR_KW}
STRLIT = re.compile(r'"(?:\\.|[^"\\\n])*"')
MIPS_REG_NAMES = {"zero", "at", "v0", "v1", "a0", "a1", "a2", "a3", "t0", "t1", "t2", "t3", "t4", "t5", "t6", "t7", "t8", "t9",
                  "s0", "s1", "s2", "s3", "s4", "s5", "s6", "s7", "s8", "k0", "k1", "gp", "sp", "fp", "ra"}
GTE_MNEMONICS = {"lwc2", "swc2", "mtc2", "mfc2", "ctc2", "cfc2", "cop2", "rtps", "rtpt", "nclip", "ncds", "nccs", "ncdt", "ncct",
                 "ncs", "nct", "cdp", "cc", "dpcs", "dpct", "dpcl", "intpl", "sqr", "op", "gpf", "gpl", "avsz3", "avsz4", "mvmva"}
FAKE_MARK = "!FAKE:"
NON_LEVER_KINDS = {"gte", "verbatim-body", "gte-unsigned"}   # Sony's coprocessor idiom; a manifest-listed hand-asm routine — censused, never a lever
GTE_LEVER_KIND = "gte-lever"        # a GTE op whose clobbers exceed its canonical's (a `_m`/`_v` variant macro, or a direct statement): a steer
GTE_VARIANT_NAME = re.compile(r"(_m|_v[0-9a-f]{4})$")
_gte_tables = None


def _gte_lookup():
    """(sig_cache, canonical-by-bytes) from tools/gte_consolidate.py's files, read once; ({}, {}) when T5 has not run."""
    global _gte_tables
    if _gte_tables is None:
        cache, canon = {}, {}
        try:
            import json as _json
            base = REPO / ".run" / "P36" / "gte"
            if (base / "sig_cache.json").exists():
                cache = _json.loads((base / "sig_cache.json").read_text())
            if (base / "canonical.json").exists():
                for key, tbl in _json.loads((base / "canonical.json").read_text())["canonical"].items():
                    canon[key] = dict(name=tbl["name"], clob=sorted(tbl["clob"]))
        except Exception:   # noqa: BLE001 — a torn file reads as "no table"
            cache, canon = {}, {}
        _gte_tables = (cache, canon)
    return _gte_tables


def classify_direct_gte(inner):
    """'gte' (Sony's idiom or no canonical to compare), 'gte-lever' (clobbers beyond the canonical's), 'gte-unsigned' (a text the
    consolidation tool has not signed yet — run `tools/gte_consolidate.py --inventory`)."""
    cache, canon = _gte_lookup()
    if not canon:
        return "gte"
    try:
        import gte_consolidate as gc
        tmpl, outs, ins, clob = gc.parse_asm(inner)
        bound = gc.bind_regs(tmpl, len(outs), len(ins))
    except Exception:   # noqa: BLE001
        return "gte-unsigned"
    b = cache.get(bound)
    if not b or b.startswith("ERROR"):
        return "gte-unsigned"
    c = canon.get(f"{b}|{len(outs)}|{len(ins)}")
    if not c:
        return "gte"
    return GTE_LEVER_KIND if sorted(clob) != c["clob"] else "gte"
# an `asm-body` site (a whole routine as one asm statement inside a C shell) becomes `verbatim-body` only when the manifest lists the
# routine as PERMANENT-VERBATIM; an unlisted or DECOMPILE-* one stays a lever and the guard (verbatim_check) names it
NORM_SYM = re.compile(r"\b(?:func|D)_80[0-9A-Fa-f]{6}\b")
DEFINE_LINE = re.compile(r"^[ \t]*#[ \t]*define[ \t]+([A-Za-z_]\w*)(\([^)]*\))?[ \t]*(.*)$")


def norm_hash(body):
    t = NORM_SYM.sub("SYM", body)
    t = re.sub(r"\s+", " ", t).strip()
    return hashlib.sha1(t.encode("utf-8", "surrogateescape")).hexdigest()


def count_tokens(text):
    return {k: len(rx.findall(text)) for k, rx in TOKEN_CLASSES.items()}


# ----------------------------------------------------------------------------------------------------------------------
# asm statement parsing
# ----------------------------------------------------------------------------------------------------------------------
def _paren_span(text, open_idx):
    """index of the ')' matching text[open_idx] == '(' (string literals skipped), or -1."""
    depth, i, n = 0, open_idx, len(text)
    while i < n:
        c = text[i]
        if c == '"':
            m = STRLIT.match(text, i)
            i = m.end() if m else i + 1
            continue
        if c == "(":
            depth += 1
        elif c == ")":
            depth -= 1
            if depth == 0:
                return i
        i += 1
    return -1


def classify_asm_body(inner):
    """inner = the text between the asm parens. Returns (kind, detail): kind in barrier|launder|keepalive|instruction|gte|label|unparsed."""
    s = inner.strip()
    lits = STRLIT.findall(s)
    if not lits:
        return "unparsed", ""
    # the template = the leading adjacent string literals (before the first ':' at depth 0 outside literals)
    tmpl_parts, i, n = [], 0, len(s)
    while i < n:
        if s[i] in " \t\r\n":
            i += 1
            continue
        m = STRLIT.match(s, i)
        if not m:
            break
        tmpl_parts.append(m.group(0)[1:-1])
        i = m.end()
    rest = s[i:].strip()
    if rest and not rest.startswith(":"):
        return "unparsed", ""
    template = "".join(tmpl_parts)
    tmpl = re.sub(r"\\[nt]", " ", template).strip()
    if rest == "" and tmpl and re.fullmatch(r"[A-Za-z_][\w.]*(?:[+\-]\d+)?", tmpl):
        return "label", tmpl                                   # __asm__("symbol") attached to a declarator (`sym+1`: a byte alias)
    sections = _split_sections(rest[1:]) if rest else []       # outputs, inputs, clobbers
    outs = sections[0] if len(sections) > 0 else ""
    ins = sections[1] if len(sections) > 1 else ""
    clob = sections[2] if len(sections) > 2 else ""
    if tmpl == "":
        if outs.strip():
            if re.search(r'"=?[+]?r"', outs) and re.search(r'"0"', ins):
                return "launder", ""
            if re.search(r'"\+r"', outs):
                return "launder", ""
            return "launder", "out-only"
        if ins.strip():
            return "keepalive", ""
        return "barrier", ("memory" if "memory" in clob else "")
    mnem = re.split(r"[\s;]+", tmpl.lstrip())[0].lower().rstrip(",")
    words = {w.lower().rstrip(",") for w in re.split(r"[\s;]+", tmpl) if w}
    if mnem in GTE_MNEMONICS or (words & GTE_MNEMONICS) or re.search(r"\.word\s+0x4[abAB]", tmpl):
        return "gte", mnem
    return "instruction", mnem


# a statement that is a declaration (what a C shell around a whole-body asm routine may legitimately carry)
DECL_STMT = re.compile(r"^\s*(?:(?:extern|static|const|volatile|register|struct|union|enum|unsigned|signed)\b\s*)*"
                       r"[A-Za-z_]\w*\b(?:\s+[A-Za-z_]\w*\b)*(?:\s*\*+\s*|\s+)[A-Za-z_]\w*\b\s*(?:\[[^\]]*\])*"
                       r"\s*(?:\([^;{}]*\))?\s*(?:(?:__asm__|__asm|asm)\s*\(\s*\"[^\"]*\"\s*\))?\s*(?:=[^;]*)?\s*$")
# (`\b` after every identifier: without it `iVar1 = …` matched as type `iVa` + name `r1` with an initializer — three false
#  whole-body verdicts in the first guard run; a register pin's asm clause is allowed on a declarator)
STMT_KEYWORDS = {"return", "goto", "if", "while", "for", "do", "switch", "case", "break", "continue", "else"}


def is_whole_body_asm(masked, span_start, span_end, asm_start, asm_close):
    """True when the asm statement at [asm_start, asm_close] is the ONLY statement of the function whose masked span is
    [span_start, span_end): everything else between the body's braces is declarations (or nothing)."""
    o = masked.find("{", span_start, span_end)
    c = masked.rfind("}", span_start, span_end)
    if o < 0 or c < 0 or not (o < asm_start < c):
        return False
    # the statement extends to the ';' after the closing paren
    e = asm_close + 1
    while e < c and masked[e] in " \t\r\n":
        e += 1
    if e < c and masked[e] == ";":
        e += 1
    rest = masked[o + 1:asm_start] + masked[e:c]
    # a whole-body routine's asm IS the body: the shell around it holds a few declarations at most (cheap pre-filters
    # before the regex — the first guard run spent minutes matching every piece of every pinned function)
    if len(rest.strip()) > 2 * (asm_close - asm_start) + 400:
        return False
    for piece in rest.split(";"):
        p = piece.strip()
        if not p:
            continue
        if len(p) > 300 or p.split()[0] in STMT_KEYWORDS or not DECL_STMT.match(p):
            return False
    return True


def whole_body_asm_functions(raw, rel):
    """[(fn, line, asm_text)] for every function in `raw` whose body is ONE asm statement (declarations aside) — the in-function
    form of the §265 verbatim lane. Shared by tools/verbatim_check.py (the guard) and the census (R33: one detector)."""
    masked = sc.mask_text(raw)
    recs = [r for r in sc.scan_text(raw, rel, shared_defs=None) if r["form"] == "def"]
    line_starts = [0]
    for ln in masked.split("\n"):
        line_starts.append(line_starts[-1] + len(ln) + 1)
    out = []
    for d in recs:
        s0, s1 = line_starts[d["line"] - 1], line_starts[d["end"]] - 1
        for m in ASM_KW.finditer(masked, s0, s1):
            o = masked.find("(", m.end())
            cl = _paren_span(masked, o) if o >= 0 else -1
            if cl < 0:
                continue
            if is_whole_body_asm(masked, s0, s1, m.start(), cl):
                out.append((d["name"], masked.count("\n", 0, m.start()) + 1, masked[m.start():cl + 1]))
                break
    return out


def manifest_rows():
    """The verbatim manifest's rows (config/verbatim_manifest.json): the authority on which asm bodies are the original's hand asm."""
    p = REPO / "config" / "verbatim_manifest.json"
    if not p.exists():
        return []
    return json.loads(p.read_text())["rows"]


def _split_sections(s):
    """split an asm operand tail on ':' at depth 0 outside string literals (the '::' form yields an empty section)."""
    out, cur, depth, i, n = [], [], 0, 0, len(s)
    while i < n:
        c = s[i]
        if c == '"':
            m = STRLIT.match(s, i)
            seg = m.group(0) if m else c
            cur.append(seg)
            i += len(seg)
            continue
        if c == "(":
            depth += 1
        elif c == ")":
            depth -= 1
        if c == ":" and depth == 0:
            out.append("".join(cur))
            cur = []
        else:
            cur.append(c)
        i += 1
    out.append("".join(cur))
    return out


# ----------------------------------------------------------------------------------------------------------------------
# macro harvest: which macro names carry asm, and of what kind
# ----------------------------------------------------------------------------------------------------------------------
def define_blocks(raw):
    """[(start_line, end_line, name, body_text)] for every #define in RAW text (continuation lines joined); 1-based lines."""
    lines = raw.split("\n")
    out, i, n = [], 0, len(lines)
    while i < n:
        m = DEFINE_LINE.match(lines[i])
        if not m:
            i += 1
            continue
        j = i
        body = [m.group(3)]
        while lines[j].rstrip().endswith("\\") and j + 1 < n:
            j += 1
            body.append(lines[j])
        text = "\n".join(body)
        text = re.sub(r"\\\n", "\n", text)
        out.append((i + 1, j + 1, m.group(1), text))
        i = j + 1
    return out


def macro_kind(body):
    """the lever kind a macro body carries (its first asm statement), or None."""
    body_m = sc.mask_text(body) if "/*" in body or "//" in body else body
    m = ASM_KW.search(body_m)
    if not m:
        return None
    o = body_m.find("(", m.end())
    if o < 0:
        return "unparsed"
    c = _paren_span(body_m, o)
    if c < 0:
        return "unparsed"
    kind, _ = classify_asm_body(body_m[o + 1:c])
    return kind


# ----------------------------------------------------------------------------------------------------------------------
# the per-file walk
# ----------------------------------------------------------------------------------------------------------------------
def _stmt_bounds(masked, pos):
    """(start, end) of the statement containing pos: after the previous ; { } (depth-0 in parens is not tracked — a pin's
    initializer with parens is inside the statement, a previous statement's ')' is before its ';')."""
    b = max(masked.rfind(";", 0, pos), masked.rfind("{", 0, pos), masked.rfind("}", 0, pos))
    start = b + 1 if b >= 0 else 0
    # end: the next ';' at paren depth 0 outside literals
    depth, i, n = 0, pos, len(masked)
    while i < n:
        c = masked[i]
        if c == '"':
            m = STRLIT.match(masked, i)
            i = m.end() if m else i + 1
            continue
        if c == "(":
            depth += 1
        elif c == ")":
            depth -= 1
            if depth < 0:
                return start, i          # a declaration inside a parameter list ends at the list's ')'
        elif c == ";" and depth <= 0:
            return start, i + 1
        elif c in "{}" and depth == 0:
            return start, i
        i += 1
    return start, n


def _paren_depth_at(masked, start, pos):
    depth, i = 0, start
    while i < pos:
        c = masked[i]
        if c == '"':
            m = STRLIT.match(masked, i)
            i = m.end() if m else i + 1
            continue
        if c == "(":
            depth += 1
        elif c == ")":
            depth -= 1
        i += 1
    return depth


def walk_file(raw, rel, is_header):
    """One file. Returns dict(sites=[...], defs=[...], macro_defs=[...], tokens=dict(raw, live, macro_block, comment_dead, unclassified),
    unclassified=[...])."""
    masked = sc.mask_text(raw)
    raw_lines = raw.split("\n")
    m_lines = masked.split("\n")
    assert len(raw_lines) == len(m_lines), f"{rel}: mask_text changed the line count"
    line_of = lambda idx: masked.count("\n", 0, idx) + 1
    # function definitions (spans) from the shared scanner
    recs = sc.scan_text(raw, rel, shared_defs=None)
    defs = [r for r in recs if r["form"] == "def"]
    span_of_line = {}
    for d in defs:
        for ln in range(d["line"], d["end"] + 1):
            span_of_line[ln] = d
    # body text per def (masked) and its normalized hash
    line_starts = [0]
    for ln in m_lines:
        line_starts.append(line_starts[-1] + len(ln) + 1)
    def span_text(d):
        return masked[line_starts[d["line"] - 1]:line_starts[d["end"]] - 1]
    for d in defs:
        d["nhash"] = norm_hash(span_text(d))
    # macro definitions (raw, continuation blocks joined) and the asm macro kinds
    mdefs = []
    macro_block_lines = set()
    for (l0, l1, name, body) in define_blocks(raw):
        kind = macro_kind(body)
        if kind:
            mdefs.append(dict(name=name, kind=kind, line=l0, end=l1, nlines=l1 - l0 + 1, text_hash=hashlib.sha1(re.sub(r"\s+", " ", body).encode()).hexdigest()[:12]))
        if l1 > l0:
            macro_block_lines.update(range(l0, l1 + 1))
    asm_macro_names = {m["name"]: m["kind"] for m in mdefs}
    # single-line #define lines stay in the masked text: their tokens are roled 'macro-def'
    define_single_lines = {l0 for (l0, l1, _, _) in define_blocks(raw) if l0 == l1}
    sites, roles, claimed = [], {}, set()
    unclassified = []
    # tokens inside string literals (an INCLUDE_ASM path, a printf text) are text, never sites
    lit_spans = [(m.start(), m.end()) for m in STRLIT.finditer(masked)]

    def in_literal(pos):
        lo, hi = 0, len(lit_spans)
        while lo < hi:
            mid = (lo + hi) // 2
            a, b = lit_spans[mid]
            if pos < a:
                hi = mid
            elif pos >= b:
                lo = mid + 1
            else:
                return True
        return False

    for cls, rx in TOKEN_CLASSES.items():
        for m in rx.finditer(masked):
            if in_literal(m.start()):
                roles[m.start()] = "string"

    def role(pos, r):
        roles[pos] = r

    def raw_line(ln):
        return raw_lines[ln - 1] if 0 < ln <= len(raw_lines) else ""

    def marked(ln):
        return FAKE_MARK in raw_line(ln) or (ln > 1 and FAKE_MARK in raw_line(ln - 1))

    def fn_of(ln):
        d = span_of_line.get(ln)
        return d["name"] if d else None

    def add_site(cls, kind, pos, text, detail="", **kw):
        ln = line_of(pos)
        d = span_of_line.get(ln)
        flat = re.sub(r"\s+", " ", text).strip()
        # a file-scope asm block keeps its whole template: the manifest match reads its `.globl`/`.ent` name
        sites.append(dict(tu=rel, fn=(d["name"] if d else None), fn_line=(d["line"] if d else None), fn_end=(d["end"] if d else None),
                          nhash=(d["nhash"] if d else None), line=ln,
                          col=pos - masked.rfind("\n", 0, pos), cls=cls, kind=kind, detail=detail,
                          text=(flat if (cls == "B" and d is None) else flat[:200]), marked=marked(ln), scope=("body" if d else "file"), **kw))

    # ---- 1. register declarations (pins and bare register)
    for m in REGISTER_KW.finditer(masked):
        pos = m.start()
        ln = line_of(pos)
        if ln in define_single_lines:
            role(pos, "macro-def")
            continue
        start, end = _stmt_bounds(masked, pos)
        stmt = masked[start:end]
        depth = _paren_depth_at(masked, start, pos)
        am = ASM_KW.search(stmt)
        if am and depth == 0:
            # the pin: register ... __asm__("R") [= init]
            o = stmt.find("(", am.end())
            c = _paren_span(stmt, o) if o >= 0 else -1
            regs = STRLIT.findall(stmt[o:c + 1]) if (o >= 0 and c >= 0) else []
            reg = regs[0][1:-1] if regs else "?"
            regn = reg.lstrip("$")
            if not (re.fullmatch(r"\$?\d{1,2}", reg) or regn in MIPS_REG_NAMES):
                # `register` + an asm LABEL on a declaration is not a pin — leave the asm token to the label rule
                role(pos, "register-bare")
                add_site("D", "register", pos, stmt, detail="with-label", init=("=" in stmt))
                continue
            for am2 in ASM_KW.finditer(stmt):
                role(start + am2.start(), "asm-pin")
            role(pos, "register-pin")
            claimed.add(start + am.start())
            zero = regn in ("0", "zero")
            add_site("A", "pin", pos, stmt, detail=reg, init=("=" in stmt), zero=zero, sp=(regn in ("29", "sp")),
                     volatile=bool(VOLATILE_KW.search(stmt)), npins=len(regs))
            for vm in VOLATILE_KW.finditer(stmt):
                role(start + vm.start(), "volatile-in-pin")
        else:
            role(pos, "register-bare")
            add_site("D", "register", pos, stmt, detail=("paren" if depth > 0 else ""), init=("=" in stmt))

    # ---- 2. asm keyword tokens not claimed by a pin
    for m in ASM_KW.finditer(masked):
        pos = m.start()
        if pos in roles:
            continue
        ln = line_of(pos)
        if ln in define_single_lines:
            role(pos, "macro-def")
            continue
        o = masked.find("(", m.end())
        c = _paren_span(masked, o) if o >= 0 else -1
        if o < 0 or c < 0:
            unclassified.append(f"{rel}:{ln}: asm without parens")
            role(pos, "unclassified")
            continue
        kind, detail = classify_asm_body(masked[o + 1:c])
        stmt_start = max(masked.rfind(";", 0, pos), masked.rfind("{", 0, pos), masked.rfind("}", 0, pos)) + 1
        head = masked[stmt_start:pos].strip()
        if kind == "label":
            # a label only when attached to a declarator (`T name(...) __asm__("sym")`, `extern T name __asm__("sym")`);
            # a bare `__asm__("nop")` statement has an empty head and is an instruction
            if head and re.search(r"[\w)\]]$", head):
                role(pos, "asm-label")
                add_site("E", "asm-label", pos, masked[stmt_start:c + 1], detail=detail)
                continue
            kind, detail = "instruction", detail.lower()
        if kind == "unparsed":
            unclassified.append(f"{rel}:{ln}: unparsed asm `{masked[o + 1:c][:60]}`")
            role(pos, "unclassified")
            continue
        role(pos, "asm-stmt")
        d = span_of_line.get(ln)
        if kind == "gte" and d:
            kind = classify_direct_gte(masked[o + 1:c])
        if d and is_whole_body_asm(masked, line_starts[d["line"] - 1], line_starts[d["end"]] - 1, pos, c):
            kind = "asm-body"           # a whole routine as one asm statement inside a C shell (any template: GTE ones too); the manifest decides its fate
        add_site("B", kind, pos, masked[pos:c + 1], detail=detail, via="")
        # the volatile qualifier of the asm keyword
        vm = re.match(r"\s*(?:__volatile__|volatile)\b", masked[m.end():o])
        if vm:
            vpos = masked.find("volatile", m.end(), o)
            if vpos >= 0:
                role(vpos, "asm-qual")
            vpos2 = masked.find("__volatile__", m.end(), o)
            if vpos2 >= 0:
                role(vpos2 + 2, "asm-qual")

    # ---- 3. uses of asm-bearing macros (SHB(x), gte_ldv0(...), LDV0_DA34(...))
    if asm_macro_names:
        use_re = re.compile(r"\b(" + "|".join(re.escape(n) for n in sorted(asm_macro_names, key=len, reverse=True)) + r")\s*\(")
        for m in use_re.finditer(masked):
            ln = line_of(m.start())
            if ln in define_single_lines:
                continue
            name = m.group(1)
            c = _paren_span(masked, m.end() - 1)
            k = asm_macro_names[name]
            if k == "gte" and GTE_VARIANT_NAME.search(name):
                k = GTE_LEVER_KIND
            add_site("B", k, m.start(), masked[m.start():c + 1] if c > 0 else name, detail=name, via=name)

    # ---- 4. volatile tokens
    for m in VOLATILE_KW.finditer(masked):
        pos = m.start()
        if pos in roles:
            continue
        ln = line_of(pos)
        if ln in define_single_lines:
            role(pos, "macro-def")
            continue
        # part of an asm keyword sequence not yet roled (e.g. `asm volatile` where the asm token was a label — impossible) -> check
        before = masked[max(0, pos - 12):pos]
        if re.search(r"(?:__asm__|__asm|asm)\s*$", before):
            role(pos, "asm-qual")
            continue
        start, end = _stmt_bounds(masked, pos)
        stmt = masked[start:end]
        depth = _paren_depth_at(masked, start, pos)
        d = span_of_line.get(ln)
        prev = masked[max(0, pos - 2):pos].strip()
        if prev.endswith("("):
            # a cast `(volatile T *)` or a parenthesized declaration
            c = _paren_span(masked, masked.rfind("(", 0, pos))
            inner = masked[masked.rfind("(", 0, pos) + 1:c] if c > 0 else ""
            if re.fullmatch(r"\s*volatile\s+[\w\s]+\*+\s*", inner):
                role(pos, "volatile-cast")
                add_site("C", "cast", pos, "(" + inner + ")", detail=inner.strip())
                continue
        if d and depth > 0 and ln == d["line"]:
            role(pos, "volatile-param")
            add_site("C", "param", pos, stmt)
        elif d:
            role(pos, "volatile-decl")
            add_site("C", "decl-body", pos, stmt, detail=("extern" if "extern" in stmt else ""))
        else:
            role(pos, "volatile-file")
            add_site("C", "decl-file", pos, stmt, detail=("extern" if "extern" in stmt else "static" if "static" in stmt else ""))

    # ---- 5. builtins and attributes
    for m in BUILTIN_KW.finditer(masked):
        pos = m.start()
        ln = line_of(pos)
        if ln in define_single_lines:
            role(pos, "macro-def")
            continue
        role(pos, "builtin")
        add_site("F", "builtin", pos, m.group(0), detail=m.group(0))
    for m in ATTR_KW.finditer(masked):
        pos = m.start()
        ln = line_of(pos)
        if ln in define_single_lines:
            role(pos, "macro-def")
            continue
        o = masked.find("(", m.end())
        c = _paren_span(masked, o) if o >= 0 else -1
        role(pos, "attribute")
        add_site("G", "attribute", pos, masked[pos:c + 1] if c > 0 else m.group(0), detail=re.sub(r"[()\s]", "", masked[o:c + 1])[:20] if c > 0 else "")

    # ---- coverage per token class: raw == live(roled) + macro-block + comment/dead
    cov = {}
    for cls, rx in TOKEN_CLASSES.items():
        raw_n = 0
        live_n = 0
        mblock_n = 0
        cdead_n = 0
        for i, (rl, ml) in enumerate(zip(raw_lines, m_lines), start=1):
            r = len(rx.findall(rl))
            if not r:
                continue
            raw_n += r
            l = len(rx.findall(ml))
            live_n += l
            if i in macro_block_lines:
                mblock_n += r - l
            else:
                cdead_n += r - l
        cov[cls] = dict(raw=raw_n, live=live_n, macro_block=mblock_n, comment_dead=cdead_n)
    # every live token must carry a role
    live_tokens = 0
    for cls, rx in TOKEN_CLASSES.items():
        for m in rx.finditer(masked):
            live_tokens += 1
            if m.start() not in roles:
                unclassified.append(f"{rel}:{line_of(m.start())}: unroled {cls} token `{m_lines[line_of(m.start()) - 1].strip()[:80]}`")
    # orphan markers: a `// !FAKE:` line with no class A/B site on it, and none on the line below either (unless that line carries its own
    # marker) — a stale honesty claim (a marked site later removed or rewritten; the delever tool consumes a trailing marker, --scrub cleans)
    ab_lines = {s["line"] for s in sites if s["cls"] in "AB"}
    orphans = [ln for ln, l in enumerate(raw_lines, start=1)
               if FAKE_MARK in l and ln not in ab_lines and not (ln + 1 in ab_lines and FAKE_MARK not in raw_line(ln + 1))]
    return dict(rel=rel, sites=sites, defs=[dict(name=d["name"], line=d["line"], end=d["end"], nhash=d["nhash"], nlines=d["nlines"]) for d in defs],
                macro_defs=mdefs, coverage=cov, live_tokens=live_tokens, roled=len(roles), unclassified=unclassified, orphan_markers=orphans)


def _walk_worker(args):
    rel, is_header = args
    raw = (REPO / rel).read_text(errors="surrogateescape")
    return walk_file(raw, rel, is_header)


# ----------------------------------------------------------------------------------------------------------------------
# the fleet
# ----------------------------------------------------------------------------------------------------------------------
def src_stamp():
    """sha1 over (path, size, mtime_ns) of every .c/.h under src/: the tree the census describes. delever refuses a census whose
    stamp is not the working tree's (R43) — a restore-write that changes only an mtime just costs a census rerun (35 s)."""
    h = hashlib.sha1()
    for p in sorted((REPO / "src").rglob("*")):
        if p.suffix in (".c", ".h") and not p.name.startswith("."):
            st = p.stat()
            h.update(f"{p.relative_to(REPO).as_posix()}|{st.st_size}|{st.st_mtime_ns}\n".encode())
    return h.hexdigest()[:16]


def git_head():
    import subprocess
    return subprocess.run(["git", "rev-parse", "--short", "HEAD"], cwd=REPO, capture_output=True, text=True).stdout.strip()


def enumerate_files(aliases, dirs):
    """TU -> [aliases] (a twin's TUs are its primary's, listed for both), plus every header under src/ (aliases = its includers')."""
    import compile_only
    tu_aliases = collections.defaultdict(list)
    for a in aliases:
        for p in compile_only.tus_of(a, dirs):
            tu_aliases[p.relative_to(REPO).as_posix()].append(a)
    all_c = {p.relative_to(REPO).as_posix() for p in (REPO / "src").rglob("*.c") if not p.name.startswith(".")}
    orphans = sorted(all_c - set(tu_aliases))
    headers = sorted(p.relative_to(REPO).as_posix() for p in (REPO / "src").rglob("*.h") if not p.name.startswith("."))
    return dict(tu_aliases), headers, orphans


def header_includers(tu_aliases):
    """header rel -> set(aliases) from the `#include "…"` lines of every TU (resolved relative to the TU)."""
    inc = collections.defaultdict(set)
    inc_tus = collections.defaultdict(set)
    for rel, als in tu_aliases.items():
        text = (REPO / rel).read_text(errors="surrogateescape")
        for m in sc.INCLUDE_LINE.finditer(sc.mask_text(text)):
            key = os.path.normpath(os.path.join(os.path.dirname(rel), m.group(1)))
            inc[key].update(als)
            inc_tus[key].add(rel)
    return inc, inc_tus


def run_census(jobs, use_cache=True, out_dir=OUT_DIR_DEFAULT, want_sites=False, gte_header=GTE_HEADER_DEFAULT):
    t0 = time.time()
    aliases, dirs = sc.fleet_and_dirs()
    tu_aliases, headers, orphans = enumerate_files(aliases, dirs)
    if orphans:
        sys.exit(f"lever_census: {len(orphans)} .c file(s) under src/ belong to NO binary's source set (R32): {orphans[:6]}")
    inc, inc_tus = header_includers(tu_aliases)
    rows = manifest_rows()
    # the file-scope / concrete-binary rows excluded from the census: only the dispositions that are NOT the project's C
    # (PERMANENT-VERBATIM = the original's hand asm; SDK-VERBATIM = Sony's code carried as asm); a DECOMPILE-*/UNCERTAIN row
    # is a lever until it is resolved
    verb = {(r["binary"], int(r["addr"], 16)) for r in rows
            if r.get("addr") and r["binary"] != "ov_*" and r.get("disposition") in ("PERMANENT-VERBATIM", "SDK-VERBATIM")}
    # the in-function rows: fn -> disposition (binary "ov_*" = every overlay and the shared headers)
    # PERMANENT-VERBATIM (the original's hand asm) and SDK-VERBATIM (Sony's code carried as asm where no SDK object matched) are
    # not the project's C and not levers; every other disposition (DECOMPILE-*, UNCERTAIN, UNLISTED) is a lever until resolved
    perm_in_fn = {r["fn"] for r in rows if r.get("form") == "in-function" and r.get("disposition") in ("PERMANENT-VERBATIM", "SDK-VERBATIM")}
    listed_in_fn = {r["fn"]: r.get("disposition") for r in rows if r.get("form") == "in-function"}
    names_by_alias = {a: sc.curated_names(a) for a in aliases}
    # scan (cached by mtime/size)
    cache_p = REPO / out_dir / "cache" / "walk_cache.json"
    cache = {}
    if use_cache and cache_p.exists():
        try:
            cache = json.loads(cache_p.read_text())
        except Exception:
            cache = {}
    work, keys = [], {}
    files = [(rel, False) for rel in sorted(tu_aliases)] + [(h, True) for h in headers]
    for rel, is_h in files:
        st = (REPO / rel).stat()
        keys[rel] = f"{rel}|{int(st.st_mtime)}|{st.st_size}|{TOOL_STAMP}"     # a tool change invalidates every cached walk (R35)
        if keys[rel] not in cache:
            work.append((rel, is_h))
    results = {}
    if work:
        with ProcessPoolExecutor(max_workers=jobs) as ex:
            for r in ex.map(_walk_worker, work, chunksize=4):
                results[r["rel"]] = r
    new_cache = {}
    for rel, is_h in files:
        r = results.get(rel) or cache.get(keys[rel])
        if r is None:
            r = walk_file((REPO / rel).read_text(errors="surrogateescape"), rel, is_h)
        results[rel] = r
        new_cache[keys[rel]] = r
    if use_cache:
        cache_p.parent.mkdir(parents=True, exist_ok=True)
        cache_p.write_text(json.dumps(new_cache))
    # attribute aliases, exclude the verbatim bodies, gather
    sites, defs_all, mdefs_all, unclassified = [], [], [], []
    orphan_all = []
    cov_total = {k: collections.Counter() for k in TOKEN_CLASSES}
    verbatim_sites = 0
    verbatim_fns = set()
    for rel, r in results.items():
        als = tu_aliases.get(rel) or sorted(inc.get(rel, ()))
        # verbatim: (alias, addr) rows -> function names in this file's aliases
        vnames = set()
        for a in als:
            for (va, vaddr) in verb:
                if va == a:
                    vnames.add(f"func_{vaddr:08X}")
                    nm = names_by_alias[a].get(vaddr)
                    if nm:
                        vnames.add(nm)
        for s in r["sites"]:
            # a manifest body is a FILE-SCOPE `__asm__(".text … .globl <fn> … .ent <fn> …")` that defines the whole routine
            vfn = None
            if s["cls"] == "B" and s["scope"] == "file":
                # the template is C string text: `\t` / `\n` are two-character escapes, not whitespace; one block may define a
                # data label and then the routine, so every `.globl`/`.ent` name is tried against the manifest
                for gm in re.finditer(r"\.(?:globl|ent)(?:\s|\\[tn])+([A-Za-z_]\w*)", s["text"]):
                    if gm.group(1) in vnames:
                        vfn = gm.group(1)
                        break
            if s["fn"] in vnames or vfn:
                verbatim_sites += 1
                verbatim_fns.add((rel, s["fn"] or vfn))
                continue
            if s["kind"] == "asm-body" and s["fn"] in perm_in_fn:
                s = dict(s, kind="verbatim-body", disposition=listed_in_fn[s["fn"]])
            elif s["kind"] == "asm-body":
                s = dict(s, disposition=listed_in_fn.get(s["fn"], "UNLISTED"))
            s = dict(s, aliases=als, header=(rel in inc), includers=len(inc_tus.get(rel, ())))
            sites.append(s)
        for d in r["defs"]:
            defs_all.append(dict(d, tu=rel, aliases=als))
        for md in r["macro_defs"]:
            mdefs_all.append(dict(md, tu=rel))
        unclassified.extend(r["unclassified"])
        orphan_all.extend(f"{rel}:{ln}" for ln in r.get("orphan_markers", ()))
        for k, c in r["coverage"].items():
            cov_total[k].update(c)
    coverage = {k: dict(v) for k, v in cov_total.items()}
    cov_ok = all(v["raw"] == v["live"] + v["macro_block"] + v["comment_dead"] for v in coverage.values()) and not unclassified
    # ---- summaries
    def by_cls(cls):
        ss = [s for s in sites if s["cls"] == cls]
        bodies = {(s["tu"], s["fn"]) for s in ss if s["fn"]}
        nh = {}
        for d in defs_all:
            nh[(d["tu"], d["name"])] = d["nhash"]
        distinct = {nh.get(b) for b in bodies if nh.get(b)}
        return dict(sites=len(ss), in_bodies=sum(1 for s in ss if s["fn"]), file_scope=sum(1 for s in ss if not s["fn"]),
                    bodies=len(bodies), distinct_bodies=len(distinct), tus=len({s["tu"] for s in ss}),
                    marked=sum(1 for s in ss if s["marked"]), unmarked=sum(1 for s in ss if not s["marked"]),
                    kinds=dict(collections.Counter(s["kind"] for s in ss)))
    classes = {c: by_cls(c) for c in "ABCDEFG"}
    # union A-D at body level
    nh = {(d["tu"], d["name"]): d["nhash"] for d in defs_all}
    union_bodies = {(s["tu"], s["fn"]) for s in sites if s["cls"] in "ABCD" and s["fn"]}
    union_distinct = collections.Counter(nh.get(b) for b in union_bodies if nh.get(b))
    lever_bodies_ab = {(s["tu"], s["fn"]) for s in sites if s["cls"] in "AB" and s["fn"] and s["kind"] not in NON_LEVER_KINDS}
    ab_distinct = collections.Counter(nh.get(b) for b in lever_bodies_ab if nh.get(b))
    kinds_b = collections.Counter((s["kind"], "via-macro" if s.get("via") else "direct") for s in sites if s["cls"] == "B")
    pins = [s for s in sites if s["cls"] == "A"]
    regs = collections.Counter(s["detail"] for s in pins)
    mnems = collections.Counter(s["detail"] for s in sites if s["cls"] == "B" and s["kind"] == "instruction")
    gte_m = collections.Counter(s["detail"] for s in sites if s["cls"] == "B" and s["kind"] == "gte")
    gte_header_sites = sum(1 for s in sites if s["tu"] == gte_header)
    by_kind_of_binary = collections.Counter()
    for b in union_bodies:
        tu = b[0]
        k = "shared" if tu.startswith("src/shared/") else "ov" if tu.startswith("src/ov_") else "md" if tu.startswith("src/md_") \
            else "resident" if tu.startswith("src/resident/") else "main"
        by_kind_of_binary[k] += 1
    macro_names = collections.Counter(m["name"] for m in mdefs_all)
    macro_kinds = collections.Counter(m["kind"] for m in mdefs_all)
    macro_texts = collections.defaultdict(set)
    for m in mdefs_all:
        macro_texts[m["name"]].add(m["text_hash"])
    summary = dict(
        generated=time.strftime("%Y-%m-%d"), binaries=len(aliases), tus=len(tu_aliases), headers=len(headers),
        head=git_head(), src_stamp=src_stamp(),
        orphan_markers=dict(count=len(orphan_all), sample=orphan_all[:40]),
        coverage=coverage, coverage_ok=cov_ok, unclassified=len(unclassified),
        verbatim_excluded=dict(sites=verbatim_sites, functions=len(verbatim_fns), manifest_rows=len(verb)),
        classes=classes,
        union_AD=dict(bodies=len(union_bodies), distinct_bodies=len(union_distinct),
                      multi_copy_classes=sum(1 for v in union_distinct.values() if v > 1),
                      copies_in_multi=sum(v for v in union_distinct.values() if v > 1),
                      by_kind=dict(by_kind_of_binary)),
        levers_AB=dict(sites=sum(1 for s in sites if s["cls"] in "AB" and s["kind"] not in NON_LEVER_KINDS),
                       pins=len(pins), asm=sum(1 for s in sites if s["cls"] == "B" and s["kind"] not in NON_LEVER_KINDS),
                       bodies=len(lever_bodies_ab), distinct_bodies=len(ab_distinct),
                       unmarked=sum(1 for s in sites if s["cls"] in "AB" and s["kind"] not in NON_LEVER_KINDS and not s["marked"]),
                       marked=sum(1 for s in sites if s["cls"] in "AB" and s["kind"] not in NON_LEVER_KINDS and s["marked"]),
                       what="register pins + asm statements excluding GTE ops: the classes the phase drives to 0"),
        pins=dict(sites=len(pins), zero=sum(1 for s in pins if s.get("zero")), sp=sum(1 for s in pins if s.get("sp")),
                  init=sum(1 for s in pins if s.get("init")), volatile_qualified=sum(1 for s in pins if s.get("volatile")),
                  bare_name=sum(1 for s in pins if not str(s["detail"]).startswith("$")),
                  spelling=dict(collections.Counter(("__asm__" if "__asm__" in s["text"] else "__asm" if "__asm" in s["text"] else "asm") for s in pins)),
                  registers=dict(regs.most_common(40))),
        asm=dict(kinds={f"{k}/{v}": n for (k, v), n in sorted(kinds_b.items())}, instruction_mnemonics=dict(mnems.most_common(30)),
                 gte_mnemonics=dict(gte_m.most_common(30)), gte_header=gte_header, gte_header_sites=gte_header_sites),
        volatile=dict(kinds=classes["C"]["kinds"]),
        verbatim_in_function=dict(sites=sum(1 for s in sites if s["kind"] == "verbatim-body"),
                                  routines=len({s["fn"] for s in sites if s["kind"] == "verbatim-body"}),
                                  by_disposition={k: len({s["fn"] for s in sites if s["kind"] == "verbatim-body" and s["disposition"] == k})
                                                  for k in ("PERMANENT-VERBATIM", "SDK-VERBATIM")},
                                  private_copies=sum(1 for s in sites if s["kind"] == "verbatim-body" and not s["tu"].startswith("src/shared/")),
                                  shared_headers=sum(1 for s in sites if s["kind"] == "verbatim-body" and s["tu"].startswith("src/shared/")),
                                  unlisted_routines=sorted({f"{s['fn']}:{s['disposition']}" for s in sites if s["kind"] == "asm-body"}),
                                  unlisted_sites=sum(1 for s in sites if s["kind"] == "asm-body"),
                                  what="whole routines written in assembly inside a C shell (the §265 lane's in-function form): the manifest's "
                                       "PERMANENT-VERBATIM rows are hand asm and not levers; an asm-body the manifest does not list as permanent "
                                       "stays a lever (unlisted_routines names them with their disposition)"),
        gte_levers=dict(sites=sum(1 for s in sites if s["kind"] == GTE_LEVER_KIND),
                        marked=sum(1 for s in sites if s["kind"] == GTE_LEVER_KIND and s["marked"]),
                        unmarked=sum(1 for s in sites if s["kind"] == GTE_LEVER_KIND and not s["marked"]),
                        via_macro=sum(1 for s in sites if s["kind"] == GTE_LEVER_KIND and s.get("via")),
                        direct=sum(1 for s in sites if s["kind"] == GTE_LEVER_KIND and not s.get("via")),
                        unsigned=sum(1 for s in sites if s["kind"] == "gte-unsigned"),
                        what="GTE ops whose clobbers exceed the canonical macro's (a scheduling steer): levers for T7, outside the headline number"),
        per_tu_asm_macro_definitions=dict(total=sum(1 for m in mdefs_all if m["tu"] != gte_header),
                                          by_kind=dict(collections.Counter(m["kind"] for m in mdefs_all if m["tu"] != gte_header)),
                                          gte_variants=sum(1 for m in mdefs_all if m["tu"] != gte_header and m["kind"] == "gte" and GTE_VARIANT_NAME.search(m["name"])),
                                          what="asm-bearing #define blocks outside the GTE header: 0 at the close (T5 deletes the canonical duplicates, T7 the variants)"),
        macro_definitions=dict(total=len(mdefs_all), names=len(macro_names), kinds=dict(macro_kinds),
                               names_with_multiple_texts=sum(1 for n, t in macro_texts.items() if len(t) > 1),
                               top=[(n, c, len(macro_texts[n])) for n, c in macro_names.most_common(25)]),
        elapsed_s=round(time.time() - t0, 1),
    )
    ctrl = controls(sites, defs_all)
    summary["controls"] = [dict(name=n, got=g, expected=e, status=st, ok=(st != "MISMATCH")) for n, g, e, st in ctrl]
    out = REPO / out_dir
    out.mkdir(parents=True, exist_ok=True)
    (out / "lever_census.json").write_text(json.dumps(summary, indent=1, sort_keys=True) + "\n")
    (out / "lever_unclassified.txt").write_text("\n".join(unclassified) + "\n")
    if want_sites:
        with open(out / "lever_sites.jsonl", "w") as f:
            for s in sites:
                f.write(json.dumps(s) + "\n")
    table = render(summary)
    (out / "lever_census.txt").write_text(table + "\n")
    return summary, sites, table


# the known-true bodies as they were at T1 (commit 357f8a1ed): a control holds only while the body's normalized text is the one the
# count was made on — the campaign removes pins byte-identically, and a control that kept expecting them would fail on its own
# staleness (batch tus7 of T4 removed func_80184034's three bare-name pins; the census then refused a correct tree)
CONTROL_NHASH = {
    ("src/800.c", "func_800226C0"): "47f1042f0dda6f163009793a11ef16f405c29af1",
    ("src/shared/ov/func_80178004.h", None): "90d67fb489780cf0ef81f1a7b4b4f74dfe3c782b",
    ("src/ov_SC03_006/ov_SC03_006_jr_8017AE2C.c", "func_80184034"): "2dce73f8716c32324b1b3517f11bd03a4e9966af",
}


def controls(sites, defs):
    """known-true cases (R39): counted independently with grep at T1 (2026-09-09) — see the phase log. Each returns
    (name, got, expected, status) with status OK / MISMATCH / N-A (the body's text is no longer the one the count was made on)."""
    cur = {}
    for d in defs:
        cur[(d["tu"], d["name"])] = d["nhash"]
        cur.setdefault((d["tu"], None), d["nhash"])
    def status(key, got, want):
        if CONTROL_NHASH.get(key) and cur.get(key) != CONTROL_NHASH[key]:
            return "N-A"
        return "OK" if got == want else "MISMATCH"
    out = []
    n = sum(1 for s in sites if s["tu"] == "src/800.c" and s["fn"] == "func_800226C0" and s["cls"] == "A")
    out.append(("src/800.c func_800226C0 pins", n, 45, status(("src/800.c", "func_800226C0"), n, 45)))
    n = sum(1 for s in sites if s["tu"] == "src/shared/ov/func_80178004.h" and s["cls"] == "A")
    out.append(("src/shared/ov/func_80178004.h pins", n, 26, status(("src/shared/ov/func_80178004.h", None), n, 26)))
    n = sum(1 for s in sites if s["tu"] == "src/ov_SC03_006/ov_SC03_006_jr_8017AE2C.c" and s["fn"] == "func_80184034" and s["cls"] == "A")
    out.append(("ov_SC03_006 func_80184034 bare-name pins", n, 3, status(("src/ov_SC03_006/ov_SC03_006_jr_8017AE2C.c", "func_80184034"), n, 3)))
    n = sum(1 for s in sites if s["tu"] == "src/shared/engine_prelude.h" and s["cls"] == "B")
    out.append(("engine_prelude.h asm sites (a macro definition only)", n, 0, "OK" if n == 0 else "MISMATCH"))
    return out


def render(s):
    L = []
    c = s["classes"]
    L.append(f"lever_census: {s['binaries']} binaries · {s['tus']:,} TUs + {s['headers']:,} headers · "
             f"coverage {'OK' if s['coverage_ok'] else 'FAIL'} · unclassified {s['unclassified']} · "
             f"verbatim excluded {s['verbatim_excluded']['functions']} fn / {s['verbatim_excluded']['sites']} sites (manifest {s['verbatim_excluded']['manifest_rows']})")
    for k, v in s["coverage"].items():
        L.append(f"  coverage {k:9s} raw {v['raw']:6d} = live {v['live']:6d} + macro-block {v['macro_block']:5d} + comment/dead {v['comment_dead']:5d}")
    L.append("  class  sites  in-bodies  file-scope  bodies  distinct  TUs  marked  unmarked   kinds")
    names = dict(A="A pins", B="B asm", C="C volatile", D="D register", E="E asm-label", F="F builtin", G="G attribute")
    for k in "ABCDEFG":
        v = c[k]
        L.append(f"  {names[k]:12s} {v['sites']:6d} {v['in_bodies']:9d} {v['file_scope']:10d} {v['bodies']:7d} {v['distinct_bodies']:9d} "
                 f"{v['tus']:5d} {v['marked']:7d} {v['unmarked']:9d}   {v['kinds']}")
    u = s["union_AD"]
    L.append(f"  UNION A–D: {u['bodies']:,} bodies · {u['distinct_bodies']:,} distinct (addresses normalized) · "
             f"{u['multi_copy_classes']:,} multi-copy classes holding {u['copies_in_multi']:,} bodies · by kind {u['by_kind']}")
    ab = s["levers_AB"]
    L.append(f"  THE PHASE'S NUMBER (pins + asm statements, GTE excluded): {ab['sites']:,} sites in {ab['bodies']:,} bodies "
             f"({ab['distinct_bodies']:,} distinct) · marked !FAKE {ab['marked']:,} · UNMARKED {ab['unmarked']:,}")
    L.append(f"  orphan !FAKE markers (no pin/asm site on the line nor below): {s.get('orphan_markers', {}).get('count', 0)}")
    g = s.get("gte_levers", {})
    if g:
        L.append(f"  GTE levers (clobbers beyond the canonical macro's): {g['sites']:,} sites ({g['via_macro']:,} via a variant macro, {g['direct']:,} direct) · "
                 f"marked {g['marked']:,} · UNMARKED {g['unmarked']:,} · unsigned GTE statements {g['unsigned']:,}")
        pt = s.get("per_tu_asm_macro_definitions", {})
        L.append(f"  per-TU asm macro definitions outside the GTE header: {pt.get('total', 0):,} {pt.get('by_kind', {})} (GTE variants {pt.get('gte_variants', 0):,})")
    p = s["pins"]
    L.append(f"  pins: {p['sites']:,} · $0 {p['zero']:,} · $sp {p['sp']} · with initializer {p['init']:,} · volatile-qualified "
             f"{p['volatile_qualified']} · bare-name {p['bare_name']} · spellings {p['spelling']}")
    vb = s["verbatim_in_function"]
    L.append(f"  whole-body asm routines in C shells, manifest PERMANENT (hand asm, NOT levers): {vb['routines']} routines · {vb['sites']:,} sites "
             f"({vb['private_copies']:,} private copies + {vb['shared_headers']} shared headers); asm-bodies NOT permanent (levers): "
             f"{vb['unlisted_sites']} site(s) {vb['unlisted_routines']}")
    L.append(f"  asm kinds: {s['asm']['kinds']}")
    L.append(f"  instruction mnemonics: {s['asm']['instruction_mnemonics']}")
    L.append(f"  gte mnemonics: {s['asm']['gte_mnemonics']}")
    m = s["macro_definitions"]
    L.append(f"  asm-bearing macro definitions: {m['total']:,} ({m['names']} names, {m['names_with_multiple_texts']} with >1 text) kinds {m['kinds']}")
    L.append("  controls (R39):")
    for r in s["controls"]:
        L.append(f"    {r['name']:52s} got {str(r['got']):6s} expected {r['expected']}  {r.get('status', 'OK' if r['ok'] else 'MISMATCH')}")
    L.append(f"  elapsed {s['elapsed_s']} s")
    return "\n".join(L)


# ----------------------------------------------------------------------------------------------------------------------
# selftest (R39): every class and every decoy, in memory
# ----------------------------------------------------------------------------------------------------------------------
FIXTURE = r'''#include "common.h"
/* a comment that says register x __asm__("$4") and asm volatile("") — never a site */
#define SHB(x) __asm__ __volatile__("" : "=r"(x) : "0"(x))
#define GTE_LDV0(r0) __asm__ volatile ("lwc2 $0, 0( %0 );" \
    "lwc2 $1, 4( %0 )" : : "r"( r0 ) : "memory")
extern volatile u16 D_8011511A;
extern u16 aD800B9A02 __asm__("D_800B9A02");
int aF80128300(int a) __asm__("func_80128300");
struct P { s16 x; s16 y; } __attribute__((packed));
#if 0
void func_DEAD0002(void) { register s32 dead __asm__("$5"); }
#endif
INCLUDE_ASM("asm/x/asm(", func_80128400);

s32 func_80128218(s32 a0, register s32 a1) {
    register s32 zr __asm__("$0");
    register u32 s __asm__("$16") = a0;
    register volatile s32 *p asm("$4") = &D_8011511A;
    register u8 *q __asm("$7");
    register int plain;
    volatile int buf[2];
    s32 v = *(volatile s32 *)(a0 + 0x1C);
    __asm__ __volatile__("" ::: "memory");
    __asm__ __volatile__("");
    __asm__("" : "=r"(v) : "0"(v));
    __asm__ __volatile__("" : : "r"(s));
    __asm__("addu %0,%1,$zero" : "=r"(v) : "r"(s));
    __asm__("la %0, D_800A5E94" : "=r"(p));
    SHB(v);
    GTE_LDV0(p);
    q = (u8 *)__builtin_memcpy((void *)a0, (void *)a1, 8);
    return v + zr + plain + buf[0] + (s32)q;
}
void func_80128500(void) {
    register s32 keep __asm__("$17"); // !FAKE: pin $17 — SCHED-ANTIDEP
    keep = 1;
    // !FAKE: stale — nothing on this line nor the next
    // !FAKE: barrier — CROSSJUMP-FENCE
    __asm__ __volatile__("");
}
'''


def selftest():
    r = walk_file(FIXTURE, "src/fx/x.c", False)
    got = collections.Counter((s["cls"], s["kind"]) for s in r["sites"])
    want = collections.Counter({("A", "pin"): 5, ("D", "register"): 2, ("C", "decl-file"): 1, ("C", "decl-body"): 1, ("C", "cast"): 1,
                                ("B", "barrier"): 3, ("B", "launder"): 2, ("B", "keepalive"): 1, ("B", "instruction"): 2, ("B", "gte"): 1,
                                ("E", "asm-label"): 2, ("F", "builtin"): 1, ("G", "attribute"): 1})
    ok = True
    if got != want:
        print(f"selftest: sites got {dict(got)}\n          want {dict(want)}"); ok = False
    pins = [s for s in r["sites"] if s["cls"] == "A"]
    regs = sorted(s["detail"] for s in pins)
    if regs != ["$0", "$16", "$17", "$4", "$7"]:
        print(f"selftest: pin registers {regs}"); ok = False
    if sum(1 for s in pins if s.get("init")) != 2 or sum(1 for s in pins if s.get("zero")) != 1 or sum(1 for s in pins if s.get("volatile")) != 1:
        print("selftest: pin attributes (init/zero/volatile) wrong"); ok = False
    if sorted(s["kind"] for s in r["sites"] if s["cls"] == "D") != ["register", "register"] or \
       sorted(s["detail"] for s in r["sites"] if s["cls"] == "D") != ["", "paren"]:
        print(f"selftest: bare register kinds {[(s['kind'], s['detail']) for s in r['sites'] if s['cls'] == 'D']}"); ok = False
    marked = sorted((s["kind"], s["marked"]) for s in r["sites"] if s["fn"] == "func_80128500")
    if marked != [("barrier", True), ("pin", True)]:
        print(f"selftest: !FAKE marks {marked}"); ok = False
    if len(r["orphan_markers"]) != 1:
        print(f"selftest: orphan markers {r['orphan_markers']} (want exactly the stale line)"); ok = False
    via = sorted(s["detail"] for s in r["sites"] if s.get("via"))
    if via != ["GTE_LDV0", "SHB"]:
        print(f"selftest: macro uses {via}"); ok = False
    mk = sorted((m["name"], m["kind"]) for m in r["macro_defs"])
    if mk != [("GTE_LDV0", "gte"), ("SHB", "launder")]:
        print(f"selftest: macro definitions {mk}"); ok = False
    cov = r["coverage"]
    bad = [k for k, v in cov.items() if v["raw"] != v["live"] + v["macro_block"] + v["comment_dead"]]
    if bad or r["unclassified"]:
        print(f"selftest: coverage {cov} unclassified {r['unclassified']}"); ok = False
    # the dead pin and the comment are comment/dead; the GTE define's first line is macro-block; the `asm(` inside the
    # INCLUDE_ASM path string is a live token with the role "string"
    if cov["register"]["comment_dead"] != 2 or cov["asm"]["macro_block"] != 1 or cov["asm"]["comment_dead"] != 3 or cov["asm"]["live"] != 16:
        print(f"selftest: coverage buckets {cov['register']} / {cov['asm']}"); ok = False
    if not any(s["kind"] == "instruction" and s["detail"] == "addu" for s in r["sites"]) or \
       not any(s["kind"] == "instruction" and s["detail"] == "la" for s in r["sites"]):
        print("selftest: instruction mnemonics not recorded"); ok = False
    if sorted(d["name"] for d in r["defs"]) != ["func_80128218", "func_80128500"]:
        print(f"selftest: defs {[d['name'] for d in r['defs']]}"); ok = False
    print(f"selftest: {'OK' if ok else 'FAIL'} — {len(r['sites'])} sites, {len(r['defs'])} defs, {len(r['macro_defs'])} asm macros")
    return ok


# ----------------------------------------------------------------------------------------------------------------------
def main():
    ap = argparse.ArgumentParser(description=__doc__.split("\n")[0])
    ap.add_argument("--check", action="store_true", help="exit 1 if any pin / asm statement (GTE excluded) lacks a `// !FAKE:` marker")
    ap.add_argument("--strict", action="store_true", help="with --check: exit 1 if ANY pin / asm statement remains outside the GTE header")
    ap.add_argument("--gte-header", default=GTE_HEADER_DEFAULT)
    ap.add_argument("--out-dir", default=OUT_DIR_DEFAULT)
    ap.add_argument("--sites", action="store_true", help="also write every site to lever_sites.jsonl (scratch)")
    ap.add_argument("-j", "--jobs", type=int, default=os.cpu_count() or 4)
    ap.add_argument("--no-cache", action="store_true")
    ap.add_argument("--selftest", action="store_true")
    ap.add_argument("--quiet", action="store_true")
    a = ap.parse_args()
    if a.selftest:
        sys.exit(0 if selftest() else 1)
    s, sites, table = run_census(a.jobs, use_cache=not a.no_cache, out_dir=a.out_dir, want_sites=a.sites or a.check, gte_header=a.gte_header)
    if not a.quiet:
        print(table)
    rc = 0
    if not s["coverage_ok"]:
        print(f"lever_census: COVERAGE DEFECT — {s['unclassified']} unclassified token(s) or a raw/live mismatch (R32); see {a.out_dir}/lever_unclassified.txt")
        rc = 1
    if any(not c["ok"] for c in s["controls"]):
        print("lever_census: a known-true control MISMATCHED (R39) — the instrument is wrong, not the tree")
        rc = 1
    if a.check:
        if s["orphan_markers"]["count"]:
            print(f"lever_census --check: {s['orphan_markers']['count']} ORPHAN !FAKE marker(s) — a marker with no pin/asm site on its line "
                  f"(nor below): {s['orphan_markers']['sample'][:6]} — tools/delever.py --scrub cleans them")
            rc = 1
        ab = [x for x in sites if x["cls"] in "AB" and x["kind"] not in NON_LEVER_KINDS and x["tu"] != a.gte_header]
        un = [x for x in ab if not x["marked"]]
        if a.strict:
            pt = s.get("per_tu_asm_macro_definitions", {}).get("total", 0)
            gl = s.get("gte_levers", {}).get("sites", 0)
            print(f"lever_census --check --strict: pins {s['pins']['sites']}, asm {sum(1 for x in ab if x['cls'] == 'B' and x['kind'] != GTE_LEVER_KIND)}, "
                  f"gte-levers {gl}, per-TU asm macro definitions {pt}, volatile-needed {s['classes']['C']['sites']}, register-needed {s['classes']['D']['sites']} — "
                  f"{'OK' if not ab and not pt else 'FAIL'}")
            if ab or pt:
                for x in ab[:10]:
                    print(f"  {x['tu']}:{x['line']} {x['fn']} {x['cls']}/{x['kind']} {x['detail']}")
                rc = 1
        else:
            print(f"lever_census --check: {len(ab):,} pin/asm sites, {len(ab) - len(un):,} marked !FAKE, {len(un):,} UNMARKED — {'OK' if not un else 'FAIL'}")
            if un:
                for x in un[:10]:
                    print(f"  {x['tu']}:{x['line']} {x['fn']} {x['cls']}/{x['kind']} {x['detail']}")
                rc = 1
    sys.exit(rc)


if __name__ == "__main__":
    main()
