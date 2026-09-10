#!/usr/bin/env python3
"""delever.py — take the compiler-forcing constructs ("levers") out of matched C, byte-gated per translation unit
(Phase 36: the probe engine at T2, the campaign tool at T3).

    tools/delever.py --plan [--batch 300] [--headers] [--only X ...]        # what the next batch would do (no writes)
    tools/delever.py --apply --batch 300 --label tu1 [--headers] [--only X ...] [-j 12]
                                                                           # judge every drawable body of the batch's files, KEEP the winning
                                                                           # text in place, mark the survivors `// !FAKE:`, ledger every site
    tools/delever.py --restore                                             # every in-flight file back from inflight.json (never git checkout, R102)
    tools/delever.py --status                                              # the ledger's totals
    tools/delever.py --apply-body TU FN FILE --label w1 [--rung E]          # T6/T7: a reshaped function judged on the bytes and kept
    tools/delever.py --selftest                                            # the fixture: every site kind, the decoys, a stub oracle
    tools/delever.py --probe --sample 150 [--seed 1] [-j 12]                # T2's measurement (unchanged)

THE LADDER PER BODY (deterministic, zero tokens):
  replay  a body whose normalized text (`nhash`, func_/D_ addresses masked) matches a body the ledger already judged replays that
          body's accepted edit set: one compile. A disagreement falls through to the full ladder and is recorded.
  rung A  strip-all — every removable site of the body rewritten at once, one compile, the object compared with the fleet run's
          (tools/delever_oracle.py).
  rung B  greedy — if A differs: from the untouched text, the sites are re-applied one at a time (asm statements first, then pins,
          volatile, register); a site whose removal keeps the object identical is REMOVED, one that changes it is NEEDED — with the
          oracle's word (DIFFERS / COMPILE-ERROR / COMPILE-CRASH) as the reason.
The verdict of a body = the set of NEEDED sites; a body with none is lever-free.

THE REWRITE PER SITE (positional on the RAW text at the census's line/col; a token that is not what the census saw is REFUSED, R43):
  pin `register T x __asm__("$N") [= e];`   -> `T x [= e];`      (the `$0` zero-register variable: the declaration deleted, every use -> 0;
                                                                  a variable that is ever assigned is REFUSED)
  barrier `__asm__("" ::: "memory");`, keep-alive `__asm__("" : : "r"(x));`, launder `__asm__("" : "=r"(x) : "0"(x));`  -> deleted
  launder whose output and input DIFFER `__asm__("" : "=r"(p) : "0"(&D_x));`  -> the assignment it is: `p = &D_x;`
     (deleting it leaves `p` undefined — cc1 2.7.2 ABORTS on such a candidate; the T2 probe counted those as NEEDED)
  a hand-placed instruction (`addu %0,%1,$zero` / move / la / lh / lw / addiu / sll / …) -> its C statement, or REFUSED (no spelling)
  a macro-carried site: `SHB(x);` (a pure launder statement macro) -> deleted; `LAUNDER(p)` (a launder statement-expression) -> its
     value `((T)(p))`; a COMPOUND macro (XFER, DRAW, RTP_SND, …: real code around the asm) -> REFUSED, the lever is in the #define (T5)
  volatile (a cast, a body declaration, a parameter, a file-scope declaration) -> the qualifier dropped; bare `register` -> dropped
  GTE ops, the manifest's verbatim bodies: never touched. An asm-body (a whole routine in a C shell) is DEFERRED to T7 and marked.

THE FILE IS THE WRITE UNIT, ITS FINAL COMPILE THE PROOF: every body's candidates are judged against the file's ORIGINAL text; the
accepted edits of every body, the file-scope edits and the `// !FAKE:` markers are spliced once at the end, and that final text is
compiled through EVERY recipe of the file (a twin's object too; every includer of a header, in parallel) — IDENTICAL or the file-scope
edits are dropped and it is compiled again, or the file is restored and REFUSED (COMBINATION-FAILED, loud). The batch's touched files
are left in place for the outer gate (the clean fleet run, R22, in tools/delever_cycle.sh); every file's original text is in
.run/P36/delever/inflight.json before the first write, and --restore reads it.

"DONE" IS A LEDGER FACT KEYED BY TEXT: every ledger row records the body's nhash BEFORE and AFTER. A body whose current nhash is some
row's after-hash is done (drawn again only with --rejudge); one whose current nhash is some row's before-hash replays it. Markers are
comments and do not change the hash; a reshaped body (T6/T7) gets a new hash and is drawn again. Class C/D survivors are never marked
(Drew's decision 3) — the ledger is their record; class A/B survivors carry `// !FAKE: <kind> <detail> — <verdict> (P36 <rung> <label>)`.
"""
import argparse
import collections
import hashlib
import json
import os
import pathlib
import random
import re
import subprocess
import sys
import threading
import time
from concurrent.futures import ThreadPoolExecutor

REPO = pathlib.Path(__file__).resolve().parent.parent
sys.path.insert(0, str(REPO / "tools"))
import delever_oracle as oracle   # noqa: E402
import lever_census as lc         # noqa: E402
import share_census as sc         # noqa: E402

RUN = REPO / ".run" / "P36" / "delever"
CENSUS_DIR = REPO / ".run" / "P36" / "census"
SITES = CENSUS_DIR / "lever_sites.jsonl"
CENSUS_JSON = CENSUS_DIR / "lever_census.json"
LEDGER = RUN / "ledger.jsonl"
INFLIGHT = RUN / "inflight.json"
PROBE = REPO / ".run" / "P36" / "probe"
PRELUDE = "src/shared/engine_prelude.h"
REMOVABLE = {("A", "pin"), ("B", "barrier"), ("B", "launder"), ("B", "keepalive"), ("B", "instruction"),
             ("B", "gte-lever"),
             ("C", "cast"), ("C", "decl-body"), ("C", "param"), ("D", "register")}
FILE_SCOPE_REMOVABLE = {("C", "decl-file"), ("B", "barrier"), ("B", "launder"), ("B", "keepalive"), ("B", "instruction")}
# a file-scope asm statement is a TU-level site: a barrier/launder/keep-alive is judged like any other; a `.section` block is a rodata
# DEFINITION carried as assembly (asm-data) — data, not a compiler steer: refused with that reason and marked, for T7
DEFERRED_KINDS = {"asm-body"}                       # a whole routine in a C shell: T7's work, marked now (the census counts it as a lever)
MARK_KINDS = {"pin", "barrier", "launder", "keepalive", "instruction", "asm-body"}   # class A/B survivors carry the marker; C/D never
ORDER = {"barrier": 0, "launder": 1, "keepalive": 2, "instruction": 3, "pin": 4, "cast": 5, "decl-body": 6, "param": 6, "register": 7}
FILE_SCOPE_FN = "<file-scope>"
DONE_VERDICTS = {"LEVER-FREE", "RESIDUE", "NOTHING-USABLE", "DEFERRED-ONLY", "REFUSED"}   # a body the ledger settles; COMBINATION-FAILED / NO-RECIPE are redrawn
STRLIT = lc.STRLIT
FAKE = "// !FAKE:"
_LOCK = threading.Lock()


class Refuse(Exception):
    pass


# ----------------------------------------------------------------------------------------------------------------------
# text helpers (positions on the RAW text; comments masked to equal-length spaces so a ';' in a comment never ends a statement)
# ----------------------------------------------------------------------------------------------------------------------
def same_len_mask(raw):
    return sc._TOK.sub(lambda m: re.sub(r"[^\n]", " ", m.group(0)) if m.group(0)[:2] in ("/*", "//") else m.group(0), raw)


def line_starts(text):
    ls = [0]
    for ln in text.split("\n"):
        ls.append(ls[-1] + len(ln) + 1)
    return ls


def stmt_end(m, pos):
    """index just past the ';' that ends the statement starting at pos (paren depth 0, string literals skipped); -1 if none."""
    depth, i, n = 0, pos, len(m)
    while i < n:
        c = m[i]
        if c == '"':
            mm = STRLIT.match(m, i)
            i = mm.end() if mm else i + 1
            continue
        if c == "(":
            depth += 1
        elif c == ")":
            depth -= 1
        elif c == ";" and depth <= 0:
            return i + 1
        elif c == "}" and depth == 0:
            return -1
        i += 1
    return -1


def ws_after(m, pos):
    i = pos
    while i < len(m) and m[i] in " \t":
        i += 1
    return i


def norm_expr(e):
    return re.sub(r"\s+", "", e)


def consume_marker(raw, m, e):
    """The end of a removed/rewritten statement, extended over a trailing `// !FAKE:` marker on the same line (a marker from an
    earlier judgement of a site that is now going away must not survive it)."""
    le = m.find("\n", e)
    le = len(raw) if le < 0 else le
    tail = raw[e:le]
    if m[e:le].strip() == "" and FAKE in tail:
        return le
    return e


def whole_line_of(raw, m, indent_start, pos, e):
    """True when the statement at pos..e is alone on its line (a trailing marker comment does not count: m blanks comments)."""
    if raw[indent_start:pos].strip() != "":
        return False
    w = ws_after(m, e)
    return m[w:w + 1] == "\n"


def scrub_edits(raw, lines):
    """Edits that remove orphan markers: a line that is only the marker goes; otherwise the marker (and the spaces before it) goes."""
    ls = line_starts(raw)
    edits = []
    for ln in lines:
        start, end = ls[ln - 1], (ls[ln] - 1 if ln < len(ls) else len(raw))
        line = raw[start:end]
        k = line.find(FAKE)
        if k < 0:
            continue
        if line[:k].strip() == "":
            edits.append((start, min(end + 1, len(raw)), ""))
        else:
            j = k
            while j > 0 and line[j - 1] in " \t":
                j -= 1
            edits.append((start + j, end, ""))
    return edits


# ----------------------------------------------------------------------------------------------------------------------
# the rewrite of one site -> [(start, end, replacement)] on the raw text
# ----------------------------------------------------------------------------------------------------------------------
ASM_HEAD = re.compile(r"(?:__asm__|__asm|asm)\s*(?:__volatile__|volatile)?\s*\(")
PIN_CLAUSE = re.compile(r"\s*(?:__asm__|__asm|asm)\s*\(\s*\"[^\"]*\"\s*\)")
INSTR_TABLE = {
    # mnemonic -> (arity, C template) using OUT / IN1 / IN2 / IMM; the operands come from the asm's "=r"(..) / "r"(..) lists
    "addu": ("OUT = IN1;", "zero"), "move": ("OUT = IN1;", None), "addiu": ("OUT = IN1 + IMM;", None), "sll": ("OUT = IN1 << IMM;", None),
    "srl": ("OUT = (u32)IN1 >> IMM;", None), "and": ("OUT = IN1 & IN2;", None), "andi": ("OUT = IN1 & IMM;", None),
    "lui": ("OUT = IMM << 16;", None), "li": ("OUT = IMM;", None), "lw": ("OUT = *(s32 *)((s32)IN1 + IMM);", None),
    "lh": ("OUT = *(s16 *)((s32)IN1 + IMM);", None), "la": ("OUT = (s32)&SYM;", None),
}
# macro shapes (the replacement text of a #define, whitespace-normalized)
_ASM = r"(?:__asm__|__asm|asm)\s*(?:__volatile__|volatile)?"
MACRO_STMT_LAUNDER = re.compile(r"^\s*" + _ASM + r"\s*\(\s*\"\"\s*:\s*\"=r\"\s*\(\s*(\w+)\s*\)\s*:\s*\"0\"\s*\(\s*\1\s*\)\s*\)\s*;?\s*$")
MACRO_EXPR_LAUNDER = re.compile(r"^\s*\(\s*\{\s*([\w][\w\s\*]*?)\s+(\w+)\s*=\s*\(\s*\1\s*\)\s*\(\s*(\w+)\s*\)\s*;\s*" + _ASM +
                                r"\s*\(\s*\"\"\s*:\s*\"=r\"\s*\(\s*\2\s*\)\s*:\s*\"0\"\s*\(\s*\2\s*\)\s*\)\s*;\s*\2\s*;\s*\}\s*\)\s*$")


def parse_asm_operands(inner):
    """(template, outputs, inputs) — outputs/inputs as [(constraint, expr)]; the asm's own parser rules (lever_census)."""
    s = inner.strip()
    parts, i, n = [], 0, len(s)
    while i < n:
        if s[i] in " \t\r\n":
            i += 1
            continue
        mm = STRLIT.match(s, i)
        if not mm:
            break
        parts.append(mm.group(0)[1:-1])
        i = mm.end()
    rest = s[i:].strip()
    secs = lc._split_sections(rest[1:]) if rest.startswith(":") else []
    def ops(sec):
        out = []
        for mm in re.finditer(r'"([^"]*)"\s*\(', sec):
            c = lc._paren_span(sec, mm.end() - 1)
            out.append((mm.group(1), sec[mm.end():c].strip()))
        return out
    outs = ops(secs[0]) if len(secs) > 0 else []
    ins = ops(secs[1]) if len(secs) > 1 else []
    return "".join(parts), outs, ins


def instruction_to_c(inner, indent):
    """The C statement for a hand-placed single-instruction asm, or None (residue)."""
    tmpl, outs, ins = parse_asm_operands(inner)
    t = re.sub(r"\\[nt]", " ", tmpl).strip()
    if len(outs) != 1:
        return None
    out_expr = outs[0][1]
    allops = [e for _, e in outs] + [e for _, e in ins]
    def resolve(tok):
        mm = re.fullmatch(r"%(\d+)", tok)
        if mm:
            k = int(mm.group(1))
            return allops[k] if k < len(allops) else None
        return None
    IMM = r"-?(?:0x[0-9A-Fa-f]+|\d+)"
    # two-instruction address / constant materializations (one C expression each)
    mm = re.fullmatch(r"lui\s+%0\s*,\s*%%hi\((\w+)\)\s*;?\s*addiu\s+%0\s*,\s*%0\s*,\s*%%lo\(\1\)", t)
    if mm:
        return f"{indent}{out_expr} = (s32)&{mm.group(1)};"
    mm = re.fullmatch(r"lui\s+%0\s*,\s*(" + IMM + r")\s*;?\s*ori\s+%0\s*,\s*%0\s*,\s*(" + IMM + r")", t)
    if mm:
        return f"{indent}{out_expr} = ({mm.group(1)} << 16) | {mm.group(2)};"
    if ";" in t or "\n" in t:
        return None                              # other multi-instruction templates are residue
    toks = [x for x in re.split(r"[\s,]+", t) if x]
    if not toks:
        return None
    mnem = toks[0].lower()
    if mnem not in INSTR_TABLE:
        return None
    templ, note = INSTR_TABLE[mnem]
    refs = [x for x in toks[1:]]
    if mnem == "addu":
        if len(refs) != 3:
            return None
        if refs[2] in ("$zero", "$0"):
            in1 = resolve(refs[1])
            return None if in1 is None else f"{indent}{out_expr} = {in1};"
        in1, in2 = resolve(refs[1]), resolve(refs[2])
        return None if in1 is None or in2 is None else f"{indent}{out_expr} = (s32){in1} + (s32){in2};"
    if mnem == "addiu" and len(refs) == 3 and refs[1] in ("$zero", "$0") and re.fullmatch(IMM, refs[2]):
        return f"{indent}{out_expr} = {refs[2]};"
    if mnem == "move":
        if len(refs) != 2:
            return None
        in1 = resolve(refs[1])
        return None if in1 is None else f"{indent}{out_expr} = {in1};"
    if mnem == "la":
        if len(refs) != 2 or not re.fullmatch(r"[A-Za-z_]\w*", refs[1]):
            return None
        return f"{indent}{out_expr} = (s32)&{refs[1]};"
    if mnem in ("lw", "lh"):
        mm = re.fullmatch(r"(-?\w+)\((%\d+)\)", refs[1]) if len(refs) == 2 else None
        if not mm:
            return None
        base = resolve(mm.group(2))
        return None if base is None else f"{indent}{templ.replace('OUT', out_expr).replace('IN1', base).replace('IMM', mm.group(1))}"
    if mnem in ("addiu", "sll", "srl", "andi"):
        if len(refs) != 3:
            return None
        in1 = resolve(refs[1])
        if in1 is None or not re.fullmatch(IMM, refs[2]):
            return None
        return f"{indent}{templ.replace('OUT', out_expr).replace('IN1', '(s32)' + in1).replace('IMM', refs[2])}"
    if mnem == "and":
        if len(refs) != 3:
            return None
        in1, in2 = resolve(refs[1]), resolve(refs[2])
        return None if in1 is None or in2 is None else f"{indent}{out_expr} = (s32){in1} & (s32){in2};"
    if mnem in ("lui", "li"):
        if len(refs) != 2 or not re.fullmatch(r"-?(?:0x[0-9A-Fa-f]+|\d+)", refs[1]):
            return None
        return f"{indent}{templ.replace('OUT', out_expr).replace('IMM', refs[1])}"
    return None


def launder_rewrite(inner):
    """('delete', None) | ('assign', 'out = in;') | raise Refuse — a launder is deletable only when it launders a value into
    itself (or defines a value from nothing); one that copies another expression into its output IS an assignment."""
    _, outs, ins = parse_asm_operands(inner)
    if len(outs) != 1:
        raise Refuse(f"launder with {len(outs)} outputs")
    if not ins:
        return "delete", None
    if len(ins) != 1:
        raise Refuse(f"launder with {len(ins)} inputs")
    o, i = outs[0][1], ins[0][1]
    if norm_expr(o) == norm_expr(i):
        return "delete", None
    return "assign", f"{o} = {i};"


_macro_cache = {}


def macro_shape(raw, rel, name, use_line):
    """('stmt-launder' | 'expr-launder' | 'compound' | 'missing', cast_type) for the definition of NAME that governs a use at
    use_line: the LAST #define before the use in this file, else engine_prelude.h (ENGINE_SHB)."""
    key = (rel, name, use_line)
    if key in _macro_cache:
        return _macro_cache[key]
    defs = [(l0, l1, body) for (l0, l1, n, body) in lc.define_blocks(raw) if n == name and l1 < use_line]
    body = defs[-1][2] if defs else None
    if body is None and name == "ENGINE_SHB":
        pre = (REPO / PRELUDE).read_text(errors="surrogateescape")
        d = [(l0, l1, b) for (l0, l1, n, b) in lc.define_blocks(pre) if n == name]
        body = d[-1][2] if d else None
    if body is None:
        res = ("missing", None)
    else:
        b = re.sub(r"\s+", " ", sc.mask_text(body) if ("/*" in body or "//" in body) else body).strip()
        if MACRO_STMT_LAUNDER.match(b):
            res = ("stmt-launder", None)
        else:
            mm = MACRO_EXPR_LAUNDER.match(b)
            res = ("expr-launder", mm.group(1).strip()) if mm else ("compound", None)
    _macro_cache[key] = res
    return res


_GTE_CANON = None


_gte_variant_cache = {}


def gte_variant_target(raw, rel, name, use_line):
    """The canonical macro name a lever-variant macro use should point at, from the SIGNATURE of the variant's own
    governing `#define` (never from its spelling: T5 named `gte_rt_m` after Sony's `gte_rt` while that signature's
    canonical name is `gte_rt_alt`). None when there is no single canonical macro for it."""
    key = (rel, name, use_line)
    if key in _gte_variant_cache:
        return _gte_variant_cache[key]
    import gte_consolidate as gc                          # lazy: gte_consolidate imports THIS module
    gte_canonical_clob("")                                # loads the table
    body = None
    for (l0, l1, n, b) in lc.define_blocks(raw):
        if n == name and l1 < use_line:
            body = b
    inner = lc._macro_asm_inner(body) if body is not None else None
    names = None
    if inner is not None:
        names, _ = gc.canonical_match(gc.signature(inner), _GTE_CANON)
    res = names[0] if names and len(names) == 1 else None
    _gte_variant_cache[key] = res
    return res


def gte_canonical_clob(inner):
    """The canonical clobber list for a GTE asm statement's inner text, or None when it has none to take
    (no table, unsigned template, no canonical entry, or it already carries the canonical set)."""
    global _GTE_CANON
    if _GTE_CANON is None:
        import gte_consolidate as gc                      # lazy: gte_consolidate imports THIS module
        _GTE_CANON = json.loads(gc.CANON.read_text()) if gc.CANON.exists() else {}
    canon = _GTE_CANON.get("canonical") or {}
    if not canon:
        return None
    import gte_consolidate as gc
    sg = gc.signature(inner)
    names, clob = gc.canonical_match(sg, _GTE_CANON)
    if names is None or tuple(sg["clob"]) == tuple(clob):
        return None
    return clob


def site_edits(raw, m, ls, site, keep_register=False):
    """[(start, end, replacement)] for one site, or raise Refuse. `m` = same_len_mask(raw)."""
    pos = ls[site["line"] - 1] + site["col"] - 1
    cls, kind = site["cls"], site["kind"]
    indent_start = m.rfind("\n", 0, pos) + 1
    if cls == "A":
        if not m.startswith("register", pos):
            raise Refuse(f"token mismatch at {site['tu']}:{site['line']}: expected `register`")
        e = stmt_end(m, pos)
        if e < 0:
            raise Refuse(f"no statement end for the pin at {site['tu']}:{site['line']}")
        stmt = raw[pos:e]
        if site.get("zero"):
            # the zero-register variable: delete the declaration, replace every use in the body by 0
            mm = re.search(r"([A-Za-z_]\w*)\s*(?:__asm__|__asm|asm)\s*\(", stmt)
            if not mm:
                raise Refuse("zero pin without a name")
            name = mm.group(1)
            if "=" in stmt.split("__asm__")[-1].split("asm")[-1]:
                raise Refuse("zero pin with an initializer")
            if whole_line_of(raw, m, indent_start, pos, e):
                edits = [(indent_start, ws_after(m, e) + 1, "")]
            else:
                edits = [(pos, consume_marker(raw, m, e), "")]
            b0, b1 = ls[site["fn_line"] - 1], ls[site["fn_end"]] - 1
            body_m = m[b0:b1]
            if re.search(r"\b%s\s*(?:=(?!=)|\+\+|--|[-+*/&|^]=)" % re.escape(name), body_m) or re.search(r"(?:\+\+|--)\s*\b%s\b" % re.escape(name), body_m):
                raise Refuse(f"zero-register variable `{name}` is assigned in the body")
            for um in re.finditer(r"\b%s\b" % re.escape(name), body_m):
                s = b0 + um.start()
                if s < pos or s >= e:
                    edits.append((s, s + len(name), "0", ("zero-use", name)))
            return edits
        new = stmt if keep_register else re.sub(r"\bregister\b[ \t]*", "", stmt, count=1)
        new = PIN_CLAUSE.sub("", new)
        return [(pos, consume_marker(raw, m, e), new)]
    if cls == "B" and kind in DEFERRED_KINDS:
        raise Refuse("asm-body: a whole routine in a C shell is T7's work (DEFERRED)")
    if cls == "B" and kind == lc.GTE_LEVER_KIND:
        # A GTE op whose clobber list exceeds its canonical signature's is a SCHEDULING STEER wearing Sony's
        # coprocessor idiom (T5 named them and marked them; it judged only the macro DEFINITIONS, so a DIRECT
        # statement's extra clobbers were never offered to the ladder). The rewrite is the canonical clobber
        # set for that signature — not deletion: the op itself is real code. Refused when the tree has no
        # canonical table, when the statement does not sign, when its signature is not canonical, or when it
        # already carries the canonical set (then it is not a lever and the census is wrong about it, R43).
        # The survivor keeps T5's own richer `// !FAKE:` text: gte-lever is deliberately NOT in MARK_KINDS.
        name = site.get("via")
        if name:
            # a use of a LEVER VARIANT macro (`gte_x_m` / `gte_x_v<hash>`, kept per TU by T5): the lever is the variant's
            # extra clobbers, so the rewrite points the use at the canonical macro of include/gte_inline.h. The variant's
            # own `#define` is left dead for `gte_consolidate.py --sweep` (its marker for `--scrub`).
            if not m.startswith(name, pos):
                raise Refuse(f"token mismatch at {site['tu']}:{site['line']}: expected `{name}`")
            base = gte_variant_target(raw, site["tu"], name, site["line"])
            if base is None:
                raise Refuse(f"GTE lever `{name}`: no single canonical macro for its signature")
            if base == name:
                raise Refuse(f"GTE lever `{name}` already IS its canonical macro")
            return [(pos, pos + len(name), base)]
        if not ASM_HEAD.match(m, pos):
            raise Refuse(f"token mismatch at {site['tu']}:{site['line']}: expected an asm statement")
        o = m.find("(", pos)
        c = lc._paren_span(m, o)
        e = stmt_end(m, pos)
        if o < 0 or c < 0 or e < 0:
            raise Refuse("unterminated GTE asm statement")
        clob = gte_canonical_clob(m[o + 1:c])             # the MASKED inner: T5's `// !FAKE:` sits INSIDE the parens
        if clob is None:
            raise Refuse(f"GTE lever `{site.get('detail', '')}`: no canonical signature to take the clobbers from")
        import gte_consolidate as gc                      # lazy: gte_consolidate imports THIS module
        # the statement without its comments (the marker included — a de-levered site owns no honesty marker); set_clobbers
        # parses the sections positionally and a comment between `(` and the template would derail it
        clean = "".join(raw[i] for i in range(pos, e) if m[i] == raw[i])
        return [(pos, consume_marker(raw, m, e), gc.set_clobbers(clean, clob))]
    if cls == "B" and site.get("via"):
        name = site["via"]
        if not m.startswith(name, pos):
            raise Refuse(f"token mismatch at {site['tu']}:{site['line']}: expected `{name}(`")
        shape, ctype = macro_shape(raw, site["tu"], name, site["line"])
        if shape == "missing":
            raise Refuse(f"macro `{name}` is not defined in this file")
        if shape == "compound":
            raise Refuse(f"macro-carried {kind}: the lever is inside `#define {name}` with real code around it (T5)")
        o = m.find("(", pos)
        c = lc._paren_span(m, o)
        if o < 0 or c < 0:
            raise Refuse("unterminated macro use")
        if shape == "expr-launder":
            return [(pos, c + 1, f"(({ctype})({raw[o + 1:c].strip()}))")]
        if kind not in ("barrier", "launder", "keepalive"):
            raise Refuse(f"macro-carried {kind} is residue")
        e = stmt_end(m, pos)
        if e < 0:
            raise Refuse("no statement end for the macro use")
        if whole_line_of(raw, m, indent_start, pos, e):
            return [(indent_start, ws_after(m, e) + 1, "")]
        return [(pos, consume_marker(raw, m, e), "")]
    if cls == "B":
        if not ASM_HEAD.match(m, pos):
            raise Refuse(f"token mismatch at {site['tu']}:{site['line']}: expected an asm statement")
        o = m.find("(", pos)
        c = lc._paren_span(m, o)
        e = stmt_end(m, pos)
        if c < 0 or e < 0:
            raise Refuse("unterminated asm statement")
        inner = m[o + 1:c]
        if kind in ("barrier", "keepalive"):
            new = ""
        elif kind == "launder":
            how, text = launder_rewrite(inner)
            new = "" if how == "delete" else text
        elif kind == "instruction":
            if str(site.get("detail", "")).startswith("."):
                raise Refuse(f"asm-data: a `{site['detail']}` block defines data as assembly (a rodata carve, not a compiler steer) — T7")
            new = instruction_to_c(inner, "")
            if new is None:
                raise Refuse(f"instruction `{site['detail']}` has no C spelling in the table")
            new = new.strip()
        else:
            raise Refuse(f"asm kind {kind} is not removable")
        if new == "" and whole_line_of(raw, m, indent_start, pos, e):
            return [(indent_start, ws_after(m, e) + 1, "")]
        return [(pos, consume_marker(raw, m, e), new)]
    if cls == "C":
        if not m.startswith("volatile", pos):
            raise Refuse(f"token mismatch at {site['tu']}:{site['line']}: expected `volatile`")
        return [(pos, ws_after(m, pos + len("volatile")), "")]
    if cls == "D":
        if not m.startswith("register", pos):
            raise Refuse(f"token mismatch at {site['tu']}:{site['line']}: expected `register`")
        return [(pos, ws_after(m, pos + len("register")), "")]
    raise Refuse(f"class {cls}/{kind} is not removable")


def apply_edits(raw, edits):
    """Splice non-overlapping edits (bottom-up). A zero-register USE (`zr` -> 0) that lies inside another edit's range is composed
    into that edit's replacement text (`register s32 ent __asm__("$4") = a0 + zr;` -> `s32 ent = a0 + 0;`); inside a deleted statement
    it is moot. Any other overlap -> Refuse (an insertion at a deletion's boundary is not an overlap)."""
    zero = [e for e in edits if len(e) > 3 and e[3][0] == "zero-use"]
    hosts = [list(e[:3]) for e in edits if not (len(e) > 3 and e[3][0] == "zero-use")]
    loose = []
    for (s, e, r, meta) in zero:
        name = meta[1]
        host = next((h for h in hosts if h[0] <= s and e <= h[1] and (h[0], h[1]) != (s, e)), None)
        if host is None:
            loose.append((s, e, r))
        elif host[2] == "":
            continue                                   # the use vanished with its statement
        elif not re.search(r"\b%s\b" % re.escape(name), host[2]):
            raise Refuse(f"zero-register use inside a rewritten statement whose replacement does not carry `{name}`")
        else:
            host[2] = re.sub(r"\b%s\b" % re.escape(name), "0", host[2])
    es = sorted([tuple(h) for h in hosts] + loose, key=lambda x: (x[0], x[1]))
    for a, b in zip(es, es[1:]):
        if b[0] < a[1]:
            raise Refuse(f"overlapping edits at {a[0]}..{a[1]} / {b[0]}..{b[1]}")
    out = raw
    for s, e, r in sorted(es, key=lambda x: (-x[0], -x[1])):
        out = out[:s] + r + out[e:]
    return out


def marker_edits(raw, ls, survivors, rung, label):
    """End-of-line `// !FAKE:` insertions for the class A/B survivors (NEEDED / REFUSED / DEFERRED), one marker per line naming
    every survivor on it; an existing marker on that line is replaced."""
    by_line = collections.defaultdict(list)
    for s, verdict, why in survivors:
        if s["kind"] in MARK_KINDS:
            by_line[s["line"]].append((s, verdict, why))
    edits = []
    for ln, items in by_line.items():
        start, end = ls[ln - 1], ls[ln] - 1 if ln < len(ls) else len(raw)
        line = raw[start:end]
        parts = []
        for s, verdict, why in items:
            what = f"{s['kind']}" + (f" {s['detail']}" if s.get("detail") and s.get("detail") != s.get("via") else "") + (f" via {s['via']}" if s.get("via") else "")
            parts.append(f"{what} — {verdict}" + (f" {why}" if why else ""))
        text = f"{FAKE} " + "; ".join(parts) + f" (P36 {rung} {label})"
        k = line.find(FAKE)
        if k >= 0:
            j = k
            while j > 0 and line[j - 1] in " \t":
                j -= 1
            edits.append((start + j, end, "  " + text))
        else:
            edits.append((end, end, "  " + text))
    return edits


# ----------------------------------------------------------------------------------------------------------------------
# the population
# ----------------------------------------------------------------------------------------------------------------------
def load_sites():
    return [json.loads(l) for l in SITES.read_text().splitlines() if l.strip()]


def kind_of(tu):
    return "shared" if tu.startswith("src/shared/") else "ov" if tu.startswith("src/ov_") else "md" if tu.startswith("src/md_") \
        else "resident" if tu.startswith("src/resident/") else "main"


def bodies_from_sites(sites, with_file_scope=False):
    """(tu, fn) -> body; the removable sites in `sites`, the rest in `frozen`; with_file_scope adds a per-TU pseudo-body for the
    file-scope `volatile` declarations (fn = FILE_SCOPE_FN, judged after the functions of its TU)."""
    bodies = {}
    for s in sites:
        ck = (s["cls"], s["kind"])
        if s.get("fn"):
            b = bodies.setdefault((s["tu"], s["fn"]), dict(tu=s["tu"], fn=s["fn"], fn_line=s["fn_line"], fn_end=s["fn_end"], nhash=s.get("nhash"),
                                                            aliases=s["aliases"], header=s.get("header", False), includers=s.get("includers", 0),
                                                            sites=[], frozen=[], deferred=[]))
            if ck in REMOVABLE:
                b["sites"].append(s)
            elif s["kind"] in DEFERRED_KINDS:
                b["deferred"].append(s)
            else:
                b["frozen"].append(s)
        elif with_file_scope and ck in FILE_SCOPE_REMOVABLE:
            b = bodies.setdefault((s["tu"], FILE_SCOPE_FN), dict(tu=s["tu"], fn=FILE_SCOPE_FN, fn_line=None, fn_end=None, nhash=None,
                                                                  aliases=s["aliases"], header=s.get("header", False), includers=s.get("includers", 0),
                                                                  sites=[], frozen=[], deferred=[]))
            b["sites"].append(s)
    for b in bodies.values():
        for k in ("sites", "frozen", "deferred"):
            b[k].sort(key=lambda s: (s["line"], s["col"]))
        if b["fn"] == FILE_SCOPE_FN:
            b["nhash"] = "fs:" + hashlib.sha1("\n".join(s["text"] for s in b["sites"]).encode()).hexdigest()
    return bodies


INCLUDERS_CACHE = RUN / "includers_cache.json"


def includers(use_cache=True):
    """header rel -> [TU rel] (transitive: a header included by a header is included by that header's includers). The per-file
    include lists are cached on (mtime, size) — masking every file's text costs ~29 s per batch, the cache ~2 s."""
    cache = {}
    if use_cache and INCLUDERS_CACHE.exists():
        try:
            cache = json.loads(INCLUDERS_CACHE.read_text())
        except Exception:   # noqa: BLE001 — a torn cache file is rebuilt
            cache = {}
    new_cache = {}
    direct = collections.defaultdict(set)
    hdr_inc = collections.defaultdict(set)
    for p in sorted((REPO / "src").rglob("*")):
        if p.suffix not in (".c", ".h") or p.name.startswith("."):
            continue
        rel = p.relative_to(REPO).as_posix()
        st = p.stat()
        key = f"{st.st_mtime_ns}|{st.st_size}"
        ent = cache.get(rel)
        if ent and ent[0] == key:
            incs = ent[1]
        else:
            text = p.read_text(errors="surrogateescape")
            incs = [os.path.normpath(os.path.join(os.path.dirname(rel), mm.group(1))) for mm in sc.INCLUDE_LINE.finditer(sc.mask_text(text))]
        new_cache[rel] = [key, incs]
        for k2 in incs:
            (direct if rel.endswith(".c") else hdr_inc)[k2].add(rel)
    if use_cache:
        RUN.mkdir(parents=True, exist_ok=True)
        # a UNIQUE temp per process: the name used to be fixed, so concurrent readers clobbered each other's os.replace
        # and the loser saw `FileNotFoundError: includers_cache.tmp -> includers_cache.json`, which reads like a compiler
        # crash on the candidate. Found by an agent in S102's burst of 20 (R48: never key a shared path by a bare name).
        import tempfile
        fd, tmpname = tempfile.mkstemp(dir=str(RUN), prefix="includers_cache.", suffix=".tmp")
        with os.fdopen(fd, "w") as fh:
            json.dump(new_cache, fh)
        os.replace(tmpname, INCLUDERS_CACHE)
    out = {}
    def resolve(h, seen=()):
        if h in out:
            return out[h]
        r = set(direct.get(h, ()))
        for h2 in hdr_inc.get(h, ()):
            if h2 not in seen:
                r |= resolve(h2, seen + (h,))
        out[h] = r
        return r
    for h in set(direct) | set(hdr_inc):
        resolve(h)
    return {h: sorted(v) for h, v in out.items()}


def fn_addr(fn, tu):
    mm = re.fullmatch(r"func_([0-9A-Fa-f]{8})", fn or "")
    if mm:
        return int(mm.group(1), 16)
    if fn and fn != FILE_SCOPE_FN:
        for ln in (REPO / "config" / "symbols.us.txt").read_text().splitlines():
            m2 = re.match(r"\s*(\w+)\s*=\s*0x([0-9A-Fa-f]+)\s*;", ln)
            if m2 and m2.group(1) == fn:
                return int(m2.group(2), 16)
    return None


def src_clean():
    r = subprocess.run(["git", "status", "--short", "--", "src"], cwd=REPO, capture_output=True, text=True)
    return r.stdout.strip() == "", r.stdout


def census_current():
    if not CENSUS_JSON.exists() or not SITES.exists():
        return False, "no census (run tools/lever_census.py --sites -j 16)"
    d = json.loads(CENSUS_JSON.read_text())
    st = d.get("src_stamp")
    if not st:
        return False, "the census carries no src_stamp (regenerate it)"
    if st != lc.src_stamp():
        return False, f"the census describes another tree (stamp {st}); rerun tools/lever_census.py --sites -j 16"
    return True, "ok"


def ensure_census(jobs):
    ok, why = census_current()
    if ok:
        return
    print(f"delever: {why} — running the census now", flush=True)
    lc.run_census(jobs, use_cache=True, want_sites=True)
    ok, why = census_current()
    if not ok:
        sys.exit(f"delever: the census is still not current ({why}) (R43)")


# ----------------------------------------------------------------------------------------------------------------------
# the ledger
# ----------------------------------------------------------------------------------------------------------------------
def load_ledger():
    rows = []
    if LEDGER.exists():
        for l in LEDGER.read_text().splitlines():
            if l.strip():
                rows.append(json.loads(l))
    return rows


def ledger_append(rows):
    RUN.mkdir(parents=True, exist_ok=True)
    with _LOCK, open(LEDGER, "a") as f:
        for r in rows:
            f.write(json.dumps(r) + "\n")


def ledger_index(rows):
    """(done: set of (tu, fn, nhash_after), exemplars: nhash_before -> the latest judged row) — the latest row per body wins (R70:
    the tie-break is part of the instrument: rows are appended in time order, the last one is the current verdict). "Done" is PER BODY:
    another copy of the same text elsewhere is not judged (nor marked) until its own row exists — keying done by text alone let every
    fleet-wide copy of an all-NEEDED exemplar (after-hash == before-hash) pass as done, unmarked (the T4 preflight found 2,204 drawable
    files where ~2,583 were expected). The text hash is the REPLAY key only."""
    done, ex = set(), {}
    for r in rows:
        if r.get("verdict") in DONE_VERDICTS and r.get("nhash_after"):
            done.add((r["tu"], r["fn"], r["nhash_after"]))
        if r.get("verdict") in ("LEVER-FREE", "RESIDUE") and r.get("nhash_before") and not r.get("replay_disagreed"):
            ex[r["nhash_before"]] = r
    return done, ex


# ----------------------------------------------------------------------------------------------------------------------
# the ladder on one body — judge(text, removed_ids) -> (verdict, seconds, err); the real judge ignores removed_ids (a stub uses it)
# ----------------------------------------------------------------------------------------------------------------------
def site_key(s):
    return (s["kind"], s.get("detail", ""))


def ladder(b, raw, m, ls, judge, replay_from=None, log=None):
    """Returns dict(verdict, rung, sites=[{ord, kind, cls, detail, line, verdict, why, oracle}], accepted=[edits], compiles, seconds,
    replay_disagreed). Never writes the file (the judge does, and restores)."""
    sites = list(b["sites"])
    res = dict(verdict=None, rung=None, sites=[], accepted=[], compiles=0, seconds=0.0, replay_disagreed=False, refused=0)
    per = {}
    usable = []
    for i, s in enumerate(sites):
        try:
            per[i] = site_edits(raw, m, ls, s)
            usable.append(i)
        except Refuse as ex:
            res["sites"].append(dict(ord=i, kind=s["kind"], cls=s["cls"], detail=s.get("detail", ""), via=s.get("via", ""), line=s["line"],
                                     verdict="REFUSED", why=str(ex)[:160], oracle=""))
            res["refused"] += 1
    # two zero pins in one body collide (both rewrite the same uses)
    zeros = [i for i in usable if sites[i].get("zero")]
    if len(zeros) > 1:
        for i in zeros:
            usable.remove(i)
            res["sites"].append(dict(ord=i, kind=sites[i]["kind"], cls="A", detail=sites[i]["detail"], via="", line=sites[i]["line"],
                                     verdict="REFUSED", why="two zero-register pins in one body", oracle=""))
            res["refused"] += 1
    if not usable:
        res["verdict"] = "NOTHING-USABLE"
        res["sites"].sort(key=lambda x: x["ord"])
        return res

    def judge_edits(idxs, tag):
        edits = [e for i in idxs for e in per[i]]
        try:
            cand = apply_edits(raw, edits)
        except Refuse as ex:
            return "REFUSED", str(ex)
        if cand == raw:
            return "REFUSED", "no-op edit (the candidate equals the original — an identical object would prove nothing, R37)"
        v, dt, err = judge(cand, set(idxs), tag)
        res["compiles"] += 1
        res["seconds"] += dt
        return v, err

    def close(removed, needed, rung):
        for i in usable:
            s = sites[i]
            if i in removed:
                d = dict(ord=i, kind=s["kind"], cls=s["cls"], detail=s.get("detail", ""), via=s.get("via", ""), line=s["line"],
                         verdict="REMOVED", why="", oracle="IDENTICAL")
                if s["kind"] == "launder" and per[i] and per[i][0][2].strip():
                    d["verdict"], d["why"] = "REWRITTEN", "assignment"
                elif s["kind"] == "instruction" or (s.get("via") and per[i] and per[i][0][2].strip()):
                    d["verdict"], d["why"] = "REWRITTEN", (per[i][0][2].strip()[:60])
                res["sites"].append(d)
            else:
                v, err = needed[i]
                res["sites"].append(dict(ord=i, kind=s["kind"], cls=s["cls"], detail=s.get("detail", ""), via=s.get("via", ""), line=s["line"],
                                         verdict="NEEDED", why=(err[:160] if v != "DIFFERS" else ""), oracle=v))
        res["accepted"] = [e for i in removed for e in per[i]]
        res["verdict"] = "LEVER-FREE" if not needed else "RESIDUE"
        res["rung"] = rung
        res["sites"].sort(key=lambda x: x["ord"])
        return res

    # replay: the exemplar's accepted set by ordinal, when the site sequences agree
    if replay_from:
        ex_sites = replay_from["sites"]
        same = len(ex_sites) == len(sites) and all(site_key(sites[i]) == (x["kind"], x.get("detail", "")) for i, x in enumerate(ex_sites))
        if same:
            want = [x["ord"] for x in ex_sites if x["verdict"] in ("REMOVED", "REWRITTEN") and x["ord"] in usable]
            if want:
                v, err = judge_edits(want, "R")
                if v == "IDENTICAL":
                    needed = {i: ("DIFFERS", "") for i in usable if i not in want}
                    for x in ex_sites:
                        if x["ord"] in needed:
                            needed[x["ord"]] = (x.get("oracle") or "DIFFERS", x.get("why", ""))
                    return close(set(want), needed, "replay")
                res["replay_disagreed"] = True
                if log:
                    log(f"  {b['tu']}:{b['fn']} replay of {replay_from.get('tu')}:{replay_from.get('fn')} DISAGREED ({v}) — full ladder")
    # rung A
    vA, errA = judge_edits(usable, "A")
    if vA == "IDENTICAL":
        return close(set(usable), {}, "A")
    if vA == "REFUSED":
        res["verdict"] = "REFUSED"
        for i in usable:                          # every site of the body survives, each with the reason (so each gets its marker)
            s = sites[i]
            res["sites"].append(dict(ord=i, kind=s["kind"], cls=s["cls"], detail=s.get("detail", ""), via=s.get("via", ""), line=s["line"],
                                     verdict="REFUSED", why=("body: " + errA)[:160], oracle=""))
        res["sites"].sort(key=lambda x: x["ord"])
        return res
    # rung B greedy, asm statements first
    order = sorted(usable, key=lambda i: (ORDER.get(sites[i]["kind"], 9), sites[i]["line"], sites[i]["col"]))
    accepted, needed = [], {}
    for i in order:
        v, err = judge_edits(accepted + [i], "B")
        if v == "IDENTICAL":
            accepted.append(i)
        else:
            needed[i] = (v, err)
    if log:
        log(f"  {b['tu']}:{b['fn']} A={vA} B: removed {len(accepted)} needed {len(needed)} compiles {res['compiles']}")
    return close(set(accepted), needed, "B")


# ----------------------------------------------------------------------------------------------------------------------
# the plan
# ----------------------------------------------------------------------------------------------------------------------
def class_sizes(bodies):
    c = collections.Counter(b["nhash"] for b in bodies.values() if b["nhash"] and b["sites"])
    return c


def make_plan(bodies, ledger_rows, headers, batch, only, rejudge=False, redraw=()):
    """[(file, [bodies])] in campaign order: headers by includer count desc, TUs by their largest class first (so exemplars precede
    their copies), then path; a body is drawable iff its sites are non-empty (or it has DEFERRED asm-bodies) and its nhash is not a
    ledger row's after-hash."""
    done, ex = ledger_index(ledger_rows)
    latest = {}
    for r in ledger_rows:
        latest[(r["tu"], r["fn"])] = r.get("verdict")
    sizes = class_sizes(bodies)
    files = collections.defaultdict(list)
    for (tu, fn), b in bodies.items():
        if tu.endswith(".h") != headers:
            continue
        if not b["sites"] and not b["deferred"]:
            continue
        if (tu, fn, b["nhash"]) in done and not rejudge and latest.get((tu, fn)) not in redraw:
            continue
        if only and not any(o in b["aliases"] or o == tu or tu.endswith("/" + o) or (b["nhash"] or "").startswith(o) or o == fn for o in only):
            continue
        files[tu].append(b)
    def fkey(tu):
        bs = files[tu]
        if headers:
            return (-max(b["includers"] for b in bs), tu)
        return (-max(sizes.get(b["nhash"], 1) for b in bs), tu)
    ordered = sorted(files, key=fkey)
    plan = [(tu, sorted(files[tu], key=lambda b: (b["fn"] == FILE_SCOPE_FN, b["fn_line"] or 0))) for tu in ordered[:batch]]
    return plan, len(ordered), ex


def describe_plan(plan, total_files, bodies):
    n_b = sum(len(bs) for _, bs in plan)
    n_s = sum(len(b["sites"]) for _, bs in plan for b in bs)
    n_d = sum(len(b["deferred"]) for _, bs in plan for b in bs)
    sizes = class_sizes(bodies)
    n_multi = sum(1 for _, bs in plan for b in bs if sizes.get(b["nhash"], 1) > 1)
    return (f"delever --plan: {len(plan)} of {total_files} drawable files · {n_b} bodies ({n_multi} in multi-copy classes) · "
            f"{n_s} removable sites · {n_d} deferred asm-bodies")


# ----------------------------------------------------------------------------------------------------------------------
# --apply
# ----------------------------------------------------------------------------------------------------------------------
def restore_file(path, raw, st):
    path.write_text(raw, errors="surrogateescape")
    try:
        os.utime(path, ns=(st.st_atime_ns, st.st_mtime_ns))
    except OSError:
        pass


def work_file(tu, bs, recipes_for, pool, exemplars, ledger_ex, label, log, calib_id):
    """One file: every body through the ladder (replay first) against the ORIGINAL text; the final splice compiled through every
    recipe; the file left with its final text (or restored). Returns (rows, summary)."""
    path = REPO / tu
    st = path.stat()
    raw = path.read_text(errors="surrogateescape")
    m = same_len_mask(raw)
    ls = line_starts(raw)
    is_hdr = tu.endswith(".h")
    recs = recipes_for(tu)
    out = dict(tu=tu, bodies=len(bs), rows=[], compiles=0, seconds=0.0, final="", written=False, sites_removed=0, sites_needed=0,
               sites_refused=0, sites_deferred=0, lever_free=0, residue=0, refused_bodies=0, replays=0, disagreed=0)
    if not recs:
        for b in bs:
            out["rows"].append(dict(ts=time.strftime("%Y-%m-%d %H:%M:%S"), label=label, rung=None, calib=calib_id, tu=tu, fn=b["fn"],
                                    addr=fn_addr(b["fn"], tu), aliases=b["aliases"], header=is_hdr, verdict="NO-RECIPE", sites=[]))
        return out
    primary = recs[:1] if is_hdr else recs          # a header's greedy runs on ONE includer; the final on all

    def judge_factory(recipe_list, parallel=False):
        def judge(text, removed, tag):
            try:
                if parallel and pool is not None and len(recipe_list) > 1:
                    path.write_text(text, errors="surrogateescape")
                    vs = list(pool.map(lambda r: oracle.judge(r, None, tag=tag), recipe_list))
                    bad = [v for v in vs if v[0] != "IDENTICAL"]
                    return (bad[0][0], sum(v[1] for v in vs), bad[0][2]) if bad else ("IDENTICAL", sum(v[1] for v in vs), "")
                return oracle.judge_all(recipe_list, text, tag=tag, write_path=(tu if is_hdr else None))
            finally:
                restore_file(path, raw, st)
        return judge
    judge_one = judge_factory(primary)
    judge_every = judge_factory(recs, parallel=True)

    accepted_all, survivors, rows = [], [], []
    fs_edits = []
    for b in bs:
        replay = exemplars.get(b["nhash"]) or ledger_ex.get(b["nhash"]) if b["nhash"] else None
        if replay and replay.get("tu") == tu and replay.get("fn") == b["fn"]:
            replay = None
        res = ladder(b, raw, m, ls, judge_one, replay_from=replay, log=log) if b["sites"] else \
            dict(verdict="DEFERRED-ONLY", rung=None, sites=[], accepted=[], compiles=0, seconds=0.0, replay_disagreed=False, refused=0)
        # a header whose greedy ran on one includer: the accepted set must hold on every includer (h_text headers differ per binary)
        if is_hdr and len(recs) > 1 and res["accepted"] and res["verdict"] in ("LEVER-FREE", "RESIDUE"):
            v, dt, err = judge_every(apply_edits(raw, res["accepted"]), None, "H")
            res["compiles"] += len(recs)
            res["seconds"] += dt
            if v != "IDENTICAL":
                log(f"  {tu}:{b['fn']} the one-includer verdict does not hold on every includer ({v}) — greedy on all includers")
                res = ladder(b, raw, m, ls, judge_every, replay_from=None, log=log)
                res["rung"] = (res.get("rung") or "") + "-all"
        for s in b["deferred"]:
            res["sites"].append(dict(ord=-1, kind=s["kind"], cls=s["cls"], detail=s.get("disposition", ""), via="", line=s["line"],
                                     verdict="DEFERRED", why="T7", oracle=""))
        if res.get("rung") == "replay":
            out["replays"] += 1
        if res.get("replay_disagreed"):
            out["disagreed"] += 1
        out["compiles"] += res["compiles"]
        out["seconds"] += res["seconds"]
        if b["fn"] == FILE_SCOPE_FN:
            fs_edits = res["accepted"]
        else:
            accepted_all += res["accepted"]
        for d in res["sites"]:
            if d["verdict"] in ("NEEDED", "REFUSED", "DEFERRED"):
                s = b["sites"][d["ord"]] if d["ord"] >= 0 and d["kind"] != "body" and d["verdict"] != "DEFERRED" else None
                if d["verdict"] == "DEFERRED":
                    s = next(x for x in b["deferred"] if x["line"] == d["line"])
                if s is not None:
                    survivors.append((s, d["verdict"], (d["oracle"] if d["verdict"] == "NEEDED" else d["why"]) or ""))
            out["sites_removed"] += d["verdict"] in ("REMOVED", "REWRITTEN")
            out["sites_needed"] += d["verdict"] == "NEEDED"
            out["sites_refused"] += d["verdict"] == "REFUSED"
            out["sites_deferred"] += d["verdict"] == "DEFERRED"
        out["lever_free"] += res["verdict"] == "LEVER-FREE"
        out["residue"] += res["verdict"] == "RESIDUE"
        out["refused_bodies"] += res["verdict"] in ("REFUSED", "NOTHING-USABLE")
        row = dict(ts=time.strftime("%Y-%m-%d %H:%M:%S"), label=label, rung=res.get("rung"), calib=calib_id, tu=tu, fn=b["fn"],
                   addr=fn_addr(b["fn"], tu), aliases=b["aliases"], header=is_hdr, includers=b.get("includers", 0),
                   o0=any("-O0" in r["pipeline"] for r in recs), nhash_before=b["nhash"], nhash_after=None,
                   exemplar=(dict(tu=replay["tu"], fn=replay["fn"]) if replay and res.get("rung") == "replay" else None),
                   verdict=res["verdict"], replay_disagreed=res.get("replay_disagreed", False), sites=res["sites"],
                   compiles=res["compiles"], seconds=round(res["seconds"], 3))
        rows.append((b, row))
        if res["verdict"] in ("LEVER-FREE", "RESIDUE") and b["fn"] != FILE_SCOPE_FN:
            with _LOCK:
                exemplars.setdefault(b["nhash"], dict(row, tu=tu, fn=b["fn"]))
    # the final splice: everything accepted + the markers, compiled through every recipe
    rung_label = "rung B" if any(r.get("rung") == "B" for _, r in rows) else "rung A"
    markers = marker_edits(raw, ls, survivors, rung_label, label)
    def final_text(with_fs):
        return apply_edits(raw, accepted_all + (fs_edits if with_fs else []) + markers)
    final = None
    for with_fs in ((True, False) if fs_edits else (True,)):
        cand = final_text(with_fs)
        if cand == raw:
            final, verdict = raw, "UNCHANGED"
            break
        v, dt, err = judge_every(cand, None, "F")
        out["compiles"] += len(recs)
        out["seconds"] += dt
        if v == "IDENTICAL":
            final, verdict = cand, "IDENTICAL"
            if not with_fs:
                log(f"  {tu}: the file-scope volatile edits do not combine with the bodies' — dropped (kept as NEEDED)")
                for b, row in rows:
                    if b["fn"] == FILE_SCOPE_FN:
                        row["verdict"] = "RESIDUE"
                        for d in row["sites"]:
                            if d["verdict"] in ("REMOVED", "REWRITTEN"):
                                d["verdict"], d["why"], d["oracle"] = "NEEDED", "does not combine with the bodies' edits", "DIFFERS"
                                out["sites_removed"] -= 1
                                out["sites_needed"] += 1
            break
        verdict = v
    if final is None:
        # the combination failed: restore, refuse the whole file, loudly
        restore_file(path, raw, st)
        out["final"] = f"COMBINATION-FAILED ({verdict})"
        log(f"  {tu}: COMBINATION-FAILED ({verdict}) — every body of this file REFUSED, the file restored")
        for b, row in rows:
            row["verdict"] = "COMBINATION-FAILED"
            row["nhash_after"] = None
        out["lever_free"] = out["residue"] = 0
        out["refused_bodies"] = len(rows)
        out["sites_removed"] = 0
    else:
        out["final"] = verdict
        if final != raw:
            path.write_text(final, errors="surrogateescape")
            out["written"] = True
        else:
            restore_file(path, raw, st)
        # the after-hash of every body from the FINAL text (the census's own normalization)
        try:
            walk = lc.walk_file(final, tu, is_hdr)
            nh = {d["name"]: d["nhash"] for d in walk["defs"]}
            fs_sites = [s for s in walk["sites"] if not s.get("fn") and (s["cls"], s["kind"]) in FILE_SCOPE_REMOVABLE]
            fs_hash = "fs:" + hashlib.sha1("\n".join(s["text"] for s in fs_sites).encode()).hexdigest()
            for b, row in rows:
                row["nhash_after"] = fs_hash if b["fn"] == FILE_SCOPE_FN else nh.get(b["fn"])
                if row["nhash_after"] is None and b["fn"] != FILE_SCOPE_FN:
                    row["nhash_after"] = b["nhash"]
                    log(f"  {tu}:{b['fn']}: the census did not find the function in the final text — after-hash kept as before-hash")
        except Exception as ex:   # noqa: BLE001 — the ledger must not lose the batch over a scanner hiccup
            log(f"  {tu}: after-hash walk failed ({ex}) — after-hash = before-hash")
            for b, row in rows:
                row["nhash_after"] = b["nhash"]
    out["rows"] = [row for _, row in rows]
    return out


def apply_batch(a):
    RUN.mkdir(parents=True, exist_ok=True)
    clean, dirty = src_clean()
    if not clean:
        sys.exit(f"delever --apply: src/ is dirty — commit, or `tools/delever.py --restore` if a batch is in flight (R42/R102):\n{dirty[:600]}")
    if INFLIGHT.exists():
        INFLIGHT.unlink()                            # src is clean: the previous batch was committed (or restored)
    ok, why = oracle.calibration_current()
    if not ok:
        sys.exit(f"delever --apply: the oracle's calibration is not current ({why}) — tools/delever_oracle.py --calibrate … first (R56)")
    calib = json.loads(oracle.CALIB.read_text())
    calib_id = dict(head=calib.get("head"), stamp=calib.get("stamp"))
    ensure_census(a.jobs)
    recipes = oracle.load_recipes()["recipes"]
    by_src = oracle.recipes_by_src(recipes)
    inc = includers()
    sites = load_sites()
    bodies = bodies_from_sites(sites, with_file_scope=True)
    rows = load_ledger()
    plan, total, ledger_ex = make_plan(bodies, rows, a.headers, a.batch, a.only, a.rejudge, set(a.redraw or ()))
    print(describe_plan(plan, total, bodies), flush=True)
    if not plan:
        print("delever --apply: nothing to do (no drawable file)")
        return 0
    # negative control (R39/R56): the first TU of the batch compiled untouched must equal build/
    def recipes_for(tu):
        if tu.endswith(".h"):
            return [r for t in inc.get(tu, []) for r in by_src.get(t, [])]
        return by_src.get(tu, [])
    ctl = next((tu for tu, _ in plan if recipes_for(tu)), None)
    if ctl is None:
        sys.exit("delever --apply: no file of the batch has a recipe (R43)")
    r0 = recipes_for(ctl)[0]
    v, dt, err = oracle.judge(r0, None, tag="ctl")
    if v != "IDENTICAL":
        sys.exit(f"delever --apply: the negative control FAILED — {ctl} untouched compiles {v} vs build/ ({err[:200]}); the baseline is stale (R56)")
    # the in-flight snapshot BEFORE any write (the only restore, R102): the label too, so --restore can drop a killed batch's ledger rows
    INFLIGHT.write_text(json.dumps(dict(label=a.label, files={tu: (REPO / tu).read_text(errors="surrogateescape") for tu, _ in plan})))
    log_p = RUN / f"apply_{a.label}.log"
    log_f = open(log_p, "a")
    def log(msg):
        line = f"{time.strftime('%H:%M:%S')} {msg}"
        with _LOCK:
            print(line, flush=True)
            log_f.write(line + "\n")
            log_f.flush()
    log(f"apply {a.label}: {len(plan)} files, control {ctl} IDENTICAL ({dt:.2f} s), calibration {calib_id['head']}, census {json.loads(CENSUS_JSON.read_text()).get('src_stamp')}")
    exemplars = {}
    results = []
    t0 = time.time()
    pool = ThreadPoolExecutor(max_workers=a.jobs)
    if a.headers:
        # headers SERIAL (a header's edit reaches every includer; nothing else may compile meanwhile); the includers in parallel
        for tu, bs in plan:
            results.append(work_file(tu, bs, recipes_for, pool, exemplars, ledger_ex, a.label, log, calib_id))
            ledger_append(results[-1]["rows"])
    else:
        # translation units in parallel, one worker per FILE (no two candidates of one file at once; no header is edited)
        def one(item):
            tu, bs = item
            r = work_file(tu, bs, recipes_for, None, exemplars, ledger_ex, a.label, log, calib_id)
            ledger_append(r["rows"])
            return r
        covered, phase1, phase2 = set(), [], []
        for tu, bs in plan:
            fresh = [b["nhash"] for b in bs if b["nhash"] and b["nhash"] not in covered and b["nhash"] not in ledger_ex]
            (phase1 if fresh else phase2).append((tu, bs))
            covered.update(fresh)
        phase1.sort(key=lambda x: -len(x[1]))
        phase2.sort(key=lambda x: -len(x[1]))
        log(f"apply {a.label}: phase 1 (exemplar files) {len(phase1)}, phase 2 (copies replay) {len(phase2)}")
        with ThreadPoolExecutor(max_workers=a.jobs) as ex:
            results = list(ex.map(one, phase1))
        with ThreadPoolExecutor(max_workers=a.jobs) as ex:
            results += list(ex.map(one, phase2))
    pool.shutdown(wait=True)
    wall = time.time() - t0
    agg = collections.Counter()
    for r in results:
        for k in ("bodies", "compiles", "sites_removed", "sites_needed", "sites_refused", "sites_deferred", "lever_free", "residue",
                  "refused_bodies", "replays", "disagreed", "written"):
            agg[k] += r[k]
        agg["seconds"] += r["seconds"]
        agg["final_ok"] += r["final"] in ("IDENTICAL", "UNCHANGED")
        agg["final_bad"] += r["final"].startswith("COMBINATION-FAILED") or r["final"] == ""
    summary = dict(label=a.label, generated=time.strftime("%Y-%m-%d %H:%M"), headers=a.headers, batch=a.batch, only=a.only, files=len(plan),
                   drawable_files=total, wall_s=round(wall, 1), calib=calib_id, **{k: agg[k] for k in agg},
                   per_file=[dict(tu=r["tu"], bodies=r["bodies"], final=r["final"], written=r["written"], removed=r["sites_removed"],
                                  needed=r["sites_needed"], refused=r["sites_refused"], compiles=r["compiles"]) for r in results])
    (RUN / f"batch_{a.label}.json").write_text(json.dumps(summary, indent=1) + "\n")
    line = (f"delever: batch {a.label} — {len(plan)} files ({'headers' if a.headers else 'TUs'}; {total} drawable) · {agg['bodies']} bodies: "
            f"{agg['lever_free']} lever-free, {agg['residue']} residue, {agg['refused_bodies']} refused · sites removed {agg['sites_removed']} / "
            f"needed {agg['sites_needed']} / refused {agg['sites_refused']} / deferred {agg['sites_deferred']} · replays {agg['replays']} "
            f"({agg['disagreed']} disagreed) · compiles {agg['compiles']} in {wall:.0f} s wall · final {agg['final_ok']}/{len(plan)} identical · "
            f"written {agg['written']} files")
    log(line)
    log_f.close()
    return 0 if agg["final_bad"] == 0 else 1


def load_inflight():
    """the in-flight map, or None with a loud reason when the file is absent, empty or torn (a SIGTERM that landed mid-write left a
    0-byte file at S101; a traceback there hid the real state — R43: refuse, never mishandle)."""
    if not INFLIGHT.exists():
        return None, "no inflight.json — nothing was in flight"
    raw = INFLIGHT.read_text()
    if not raw.strip():
        return None, ("inflight.json is EMPTY (a kill landed mid-write): the snapshot is lost — reconcile every dirty file with the oracle "
                      "(a bank is IDENTICAL, a leftover candidate DIFFERS) and restore a DIFFERS file from HEAD only if no uncommitted bank touched it")
    try:
        return json.loads(raw), "ok"
    except json.JSONDecodeError as ex:
        return None, f"inflight.json is TORN ({ex}): same reconciliation as for an empty one"


def restore():
    """Every in-flight file back from inflight.json, and the killed batch's ledger rows dropped (a batch that did not complete leaves no
    trace: its bodies are drawn again — a body judged all-NEEDED in the killed batch would otherwise count as done while its markers were
    restored away). The dropped rows are kept in ledger.jsonl.killed_<label> (ignored scratch)."""
    d, why = load_inflight()
    if d is None:
        sys.exit(f"delever --restore: {why}")
    label, files = (d.get("label"), d.get("files")) if isinstance(d, dict) and "files" in d else (None, d)
    n = 0
    for tu, text in files.items():
        p = REPO / tu
        if p.read_text(errors="surrogateescape") != text:
            p.write_text(text, errors="surrogateescape")
            n += 1
    dropped = 0
    if label and LEDGER.exists():
        rows = LEDGER.read_text().splitlines()
        keep = [l for l in rows if l.strip() and json.loads(l).get("label") != label]
        dropped = len([l for l in rows if l.strip()]) - len(keep)
        if dropped:
            (RUN / f"ledger.jsonl.killed_{label}").write_text("\n".join(rows) + "\n")
            LEDGER.write_text("".join(l + "\n" for l in keep))
    INFLIGHT.unlink()
    clean, dirty = src_clean()
    print(f"delever --restore: {n} of {len(files)} files restored from inflight.json (batch {label or '?'}); {dropped} ledger rows of that batch "
          f"dropped{' (backup ledger.jsonl.killed_' + label + ')' if dropped else ''}; src {'clean' if clean else 'STILL DIRTY:'}\n{'' if clean else dirty[:400]}")
    return 0 if clean else 1


def scrub(a):
    """--scrub [--only …]: remove every orphan `// !FAKE:` marker (the census's definition: no pin/asm site on the line nor below), each
    file's final text judged through every recipe; the tree is left modified for the outer gate (R22) and the commit."""
    clean, dirty = src_clean()
    if not clean and not a.dirty_ok:
        sys.exit(f"delever --scrub: src/ is dirty — commit or --restore first (or --dirty-ok right after a judged pass that orphaned markers):\n{dirty[:400]}")
    ok, why = oracle.calibration_current()
    if not ok:
        sys.exit(f"delever --scrub: calibration not current ({why})")
    ensure_census(a.jobs)
    census = json.loads(CENSUS_JSON.read_text())
    if not census.get("orphan_markers", {}).get("count"):
        print("delever --scrub: the census lists no orphan marker — nothing to do")
        return 0
    recipes = oracle.load_recipes()["recipes"]
    by_src = oracle.recipes_by_src(recipes)
    inc = includers()
    files = sorted({x.split(":")[0] for x in census["orphan_markers"]["sample"]})
    if len(census["orphan_markers"]["sample"]) < census["orphan_markers"]["count"]:
        # the summary holds a sample: walk every file that has a marker at all
        files = sorted(p.relative_to(REPO).as_posix() for p in (REPO / "src").rglob("*") if p.suffix in (".c", ".h") and FAKE in p.read_text(errors="surrogateescape"))
    if a.only:
        files = [f for f in files if any(o == f or f.endswith("/" + o) or ("/" + o + "/") in f for o in a.only)]
    rows, n_lines, n_files, bad = [], 0, 0, 0
    for tu in files:
        path = REPO / tu
        st = path.stat()
        raw = path.read_text(errors="surrogateescape")
        lines = lc.walk_file(raw, tu, tu.endswith(".h"))["orphan_markers"]
        if not lines:
            continue
        cand = apply_edits(raw, scrub_edits(raw, lines))
        recs = [r for t_ in inc.get(tu, []) for r in by_src.get(t_, [])] if tu.endswith(".h") else by_src.get(tu, [])
        if not recs:
            print(f"delever --scrub: {tu}: no recipe — skipped")
            continue
        try:
            v, dt, err = oracle.judge_all(recs, cand, tag="scrub", write_path=(tu if tu.endswith(".h") else None))
        finally:
            restore_file(path, raw, st)
        row = dict(ts=time.strftime("%Y-%m-%d %H:%M:%S"), label=a.label or "scrub", rung="scrub", calib=dict(head=oracle.head(), stamp=oracle.config_stamp()),
                   tu=tu, fn=None, addr=None, aliases=None, header=tu.endswith(".h"), verdict=("SCRUBBED" if v == "IDENTICAL" else f"SCRUB-{v}"),
                   lines=lines, sites=[], compiles=len(recs), seconds=round(dt, 3))
        rows.append(row)
        if v == "IDENTICAL":
            path.write_text(cand, errors="surrogateescape")
            n_lines += len(lines)
            n_files += 1
            print(f"delever --scrub: {tu}: {len(lines)} orphan marker(s) removed, {len(recs)} object(s) identical")
        else:
            bad += 1
            print(f"delever --scrub: {tu}: {v} — NOT written ({err[:160]})")
    ledger_append(rows)
    print(f"delever --scrub: {n_lines} orphan marker(s) removed in {n_files} file(s); {bad} file(s) refused")
    return 0 if not bad else 1


# ----------------------------------------------------------------------------------------------------------------------
# --recipes (rung R): the cookbook's byte-neutral shape recipes, tried mechanically on a RESIDUE body
# ----------------------------------------------------------------------------------------------------------------------
CTRL_KW = re.compile(r"^\s*(?:if|for|while|do|switch|else|return|goto|case|default|break|continue)\b")


def pin_names(sites):
    """the variable each pin site declares, in source order (the zero-register pins excluded: their declaration is deleted)."""
    out = []
    for s in sites:
        if s["kind"] != "pin" or s.get("zero"):
            continue
        mm = re.search(r"\b([A-Za-z_]\w*)\s*(?:\[[^\]]*\])?\s*(?:__asm__|__asm|asm)\s*\(", s.get("text", ""))
        if mm:
            out.append(mm.group(1))
    return out


def is_decl_line(masked_line):
    """a whole-statement DECLARATION on one line: `<type> <name>[\\[n\\]][ = init];`. The type and the name must be separated
    (by space or `*`) — without that, `ret = f();` parses as the declaration `re t = …` and an initializer split lands its
    assignment after the first statement, where C89 forbids the declarations that follow it."""
    s = masked_line.strip()
    return bool(s.endswith(";") and not CTRL_KW.match(s) and "(" not in s.split("=")[0]
                and re.match(r"^[A-Za-z_][\w \t]*[\s*]\s*\*?\s*[A-Za-z_]\w*\s*(?:\[[^\]]*\])*\s*(?:=|;)", s))


DECL_START = re.compile(r"^(?:register\s+|static\s+|const\s+|volatile\s+|unsigned\s+|signed\s+|struct\s+|union\s+)*[A-Za-z_]\w*\s*\*?\s*[A-Za-z_]\w*\s*(?:\[[^\]]*\])*\s*=(?!=)")


def decl_run_end(text, d):
    """the 0-based index of the LAST line of the declaration run that opens fn's body — a C89 declaration may not follow a
    statement, so an initializer split must put its assignment after the WHOLE run, not after the last pinned declaration."""
    lines = text.split("\n")
    last = d["line"] - 1
    i = d["line"]
    while i < d["end"] - 1:
        s = sc.mask_text(lines[i]).strip()
        if not s or s.startswith("/*") or s.startswith("//") or s in ("{", "}"):
            i += 1
            continue
        if is_decl_line(sc.mask_text(lines[i])) or (DECL_KW.match(s) and s.endswith(";") and s.count("(") == s.count(")")) \
                or MULTI_DECL.match(s):
            last = i                                      # incl. `extern s16 (*D_x[])();` and `int t, v;` — is_decl_line refuses both
            i += 1
            continue
        # a declaration whose initializer continues on the next line(s): `s32 tmp = (ratan2(…) -` … `…) & 0xFFF;` — the run
        # continues past it (S101: the locals declared after such a line were invisible to every declaration-level move)
        if DECL_START.match(s) and "(" in s and s.count("(") > s.count(")"):
            j, depth = i, 0
            while j < d["end"] - 1:
                depth += sc.mask_text(lines[j]).count("(") - sc.mask_text(lines[j]).count(")")
                if depth <= 0 and sc.mask_text(lines[j]).rstrip().endswith(";"):
                    break
                j += 1
            last = j
            i = j + 1
            continue
        break
    return last


def decl_lines(text, tu, fn, names):
    """[(line index, text)] for the lines of fn's body that DECLARE one of `names` — one name per line, the line a whole
    statement. The lever-free text is re-scanned for them (a stripped pin can delete its line, so the census's numbers have
    moved); a name whose declaration is not found alone on one line makes the body ineligible (None)."""
    recs = sc.scan_text(text, tu, shared_defs=None)
    d = next((r for r in recs if r["form"] == "def" and r["name"] == fn), None)
    if d is None:
        return None
    lines = text.split("\n")
    found = {}
    for i in range(d["line"], d["end"] - 1):              # inside the body, never the header line
        raw_line = lines[i]
        s = sc.mask_text(raw_line).strip()
        if not is_decl_line(s):
            continue
        hits = [n for n in names if re.search(r"(?<![\w])%s\b" % re.escape(n), s.split("=")[0])]
        if len(hits) != 1 or hits[0] in found:
            continue
        found[hits[0]] = (i, raw_line)
    if len(found) != len(set(names)):
        return None
    return sorted(found.values())


COMMUTATIVE = "&|^+*"


def top_level_ops(expr):
    """positions of the BINARY commutative operators at paren/bracket depth 0 in `expr` (masked text). An operator is binary
    when the previous non-space character ends an operand (identifier, digit, `)`, `]`); that also excludes a unary `*`/`&`
    and a cast's `*`, which in any case sits inside parentheses."""
    out, depth = [], 0
    for i, c in enumerate(expr):
        if c in "([":
            depth += 1
        elif c in ")]":
            depth -= 1
        elif depth == 0 and c in COMMUTATIVE:
            if i + 1 < len(expr) and expr[i + 1] in "&|=+*":     # && || &= += *= **
                continue
            if i and expr[i - 1] in "&|=+*<>!-/%":
                continue
            prev = expr[:i].rstrip()
            if prev and (prev[-1].isalnum() or prev[-1] in "_)]"):
                out.append(i)
    return out


def commutative_swaps(text, tu, fn, d_):
    """[(description, candidate text)] — each line of fn's body that carries exactly ONE top-level commutative operator,
    with its two operands swapped. THE lever for a caller-saved ($2/$3) residual: S99 read `and v0,v1,v0` against the
    target's `and v0,v0,v1` on func_80163EC8, which is the operand order of one `&` in the source and nothing else."""
    lines = text.split("\n")
    out = []
    for i in range(d_["line"], d_["end"] - 1):
        raw_line, s = lines[i], sc.mask_text(lines[i])
        body = s.strip()
        if not body.endswith(";") or body.startswith("#"):
            continue
        # only an assignment's RHS or a `return` expression — an `if (…) stmt;` line would need the condition parsed out of
        # the statement after it, and a wrong split is a candidate that cannot compile (wasted, and noisy in the ledger)
        asg = re.search(r"(?<![=!<>+\-*/%&|^~])=(?!=)", s)
        ret = re.match(r"^\s*return\b", s)
        start = asg.end() if asg else (ret.end() if ret else -1)
        if start < 0 or start >= len(s):
            continue
        expr_end = s.rstrip().rfind(";")
        expr = s[start:expr_end]
        ops = top_level_ops(expr)
        if len(ops) != 1:
            continue
        o = start + ops[0]
        left, right = raw_line[start:o], raw_line[o + 1:expr_end]
        if not left.strip() or not right.strip():
            continue
        # a CONSTANT operand is moved to the right by fold before expansion (fold-const.c:3179-3189; lane B, verified on
        # bytes at S101: `*(p+17) & -33` and `-33 & *(p+17)` compile identically, `m & x` and `x & m` do not) — the swap
        # of a constant is a candidate that can never change the object, so it is not generated
        if any(re.fullmatch(r"[-~!]?\s*(?:0[xX][0-9A-Fa-f]+|\d+)[uUlL]*", sc.mask_text(side).strip()) for side in (left, right)):
            continue
        cand = list(lines)
        cand[i] = raw_line[:start] + " " + right.strip() + " " + raw_line[o] + " " + left.strip() + raw_line[expr_end:]
        out.append((f"swap {raw_line[o]} @{i + 1}", "\n".join(cand)))
    return out


IDENT = re.compile(r"(?<![\w.])([A-Za-z_]\w*)(?![\w])")


def inline_single_set_temps(text, tu, fn, d_):
    """[(description, candidate text)] — a local assigned ONCE and read ONCE, inlined at its use and its now-dead
    declaration removed. §501-R's S2 kill: a fresh single-set local gets a birthing boost in gcc 2.7.2's allocator, so
    creating or removing one moves the allocation — and this is the move rung D found first (S99, func_80163EC8:
    `uVar5 = *(s32 *)(psVar6 + 0x44); … = uVar5 & ~0x20;` became `… = *(s32 *)(psVar6 + 0x44) & ~0x20;`). Doing it here
    keeps the SOURCE readable: the permuter's own winner is machine-reprinted, and this phase is about readability."""
    lines = text.split("\n")
    lo, hi = d_["line"], d_["end"] - 1
    masked = [sc.mask_text(l) for l in lines]
    occ = collections.defaultdict(list)
    for i in range(lo, hi):
        for m in IDENT.finditer(masked[i]):
            occ[m.group(1)].append((i, m.start(), m.end()))
    out = []
    ASG = r"^(?:[A-Za-z_][\w \t]*[\s*]\s*\*?\s*)?%s\s*=(?!=)\s*(.+);\s*$"
    for v, places in occ.items():
        asgs, decls, uses = [], [], []
        for p in places:
            s = masked[p[0]].strip()
            if re.match(ASG % re.escape(v), s):
                asgs.append(p)
            elif is_decl_line(s) and "=" not in s.split(";")[0]:
                decls.append(p)
            else:
                uses.append(p)
        if not asgs or not uses or len(decls) > 1:
            continue
        # ONE ASSIGNMENT AT A TIME, not one per variable. The single-set case is the easy half; the lever rung D actually
        # found is narrower: `uVar5` is assigned in TWO branches of func_80163EC8, and the winning move inlined ONE of them.
        # An assignment is inlinable when its value is read exactly once before the variable is written again — the classic
        # def-with-one-use — so the assignment can go and the read can carry the expression.
        order = sorted(places)
        for ai, _, _ in asgs:
            after = [p for p in order if p[0] > ai]
            reads = [p for p in after if p not in [(x, y, z) for x, y, z in asgs] and not is_decl_line(masked[p[0]].strip())]
            if not reads:
                continue
            ui, u0, u1 = reads[0]
            nxt = [p for p in after if p[0] > ui]
            if nxt and (nxt[0][0], nxt[0][1], nxt[0][2]) not in [(x, y, z) for x, y, z in asgs]:
                continue                                  # read again before it is rewritten: the assignment is not dead
            mm = re.match(ASG % re.escape(v), masked[ai].strip())
            if not mm:
                continue
            expr = lines[ai].strip()[mm.start(1):mm.end(1)]
            if not expr.strip():
                continue
            cand = list(lines)
            cand[ui] = lines[ui][:u0] + f"({expr})" + lines[ui][u1:]
            cand[ai] = None                               # the assignment goes (with its declaration when they are one)
            if decls and len(asgs) == 1:                  # the separate `T v;` is dead only when nothing else writes v
                cand[decls[0][0]] = None
            out.append((f"inline {v} @{ai + 1}", "\n".join(l for l in cand if l is not None)))
    return out


def block_wraps(text, tu, fn, d_):
    """[(description, candidate text)] — one statement wrapped in a block. §501-R's RC-5 scope lever: a block changes the
    statement's basic-block structure and with it the allocno live range, which is how rung D closed func_80135D20 in 24 s
    (`flag = 0;` -> `do { flag = 0; } while (0);` and nothing else). The plain block is tried FIRST because it is the
    readable spelling; the do-while is gcc's stronger form and is only reached when the plain one does not hold."""
    lines = text.split("\n")
    out = []
    for i in range(d_["line"], d_["end"] - 1):
        raw_line = lines[i]
        s = sc.mask_text(raw_line).strip()
        indent = raw_line[:len(raw_line) - len(raw_line.lstrip())]
        # the INVERSE first: a one-line block around a single statement unwrapped (the search needs every move's inverse, or a
        # wrap it tried on the way cannot be undone — the S101 two-move control stalled at 6 for exactly that)
        un = re.match(r"^(?:do\s*)?\{\s*(.*;)\s*\}(\s*while\s*\(\s*0\s*\)\s*;)?$", s)
        if un and un.group(1).count("{") == 0 and simple_stmt(un.group(1)):
            inner = raw_line.strip()
            inner = re.sub(r"^(?:do\s*)?\{\s*", "", inner)
            inner = re.sub(r"\s*\}(\s*while\s*\(\s*0\s*\)\s*;)?$", "", inner)
            cand = list(lines)
            cand[i] = indent + inner
            out.append((f"unwrap @{i + 1}", "\n".join(cand)))
            continue
        if not simple_stmt(s):
            continue
        stmt = raw_line.strip()
        for tag, spelling in (("block", f"{indent}{{ {stmt} }}"), ("do-while", f"{indent}do {{ {stmt} }} while (0);")):
            cand = list(lines)
            cand[i] = spelling
            out.append((f"{tag} @{i + 1}", "\n".join(cand)))
    return out


DEREF = re.compile(r"\*\s*\(\s*((?:struct\s+|union\s+)?[A-Za-z_]\w*\s*\*+)\s*\)\s*")


DECL_KW = re.compile(r"^\s*(?:extern|static|typedef|register|const|volatile|struct|union|enum)\b")
MULTI_DECL = re.compile(r"^\s*(?:struct\s+|union\s+|unsigned\s+|signed\s+)?[A-Za-z_]\w*\s+\*?[A-Za-z_]\w*(?:\s*,\s*\*?[A-Za-z_]\w*)+\s*;\s*$")


def simple_stmt(masked_line):
    """a whole simple statement alone on its line: ends with `;`, no control keyword, no declaration (an `extern s16
    (*D_x[])();` is one too — is_decl_line refuses the `(`; so is `int t, v;`), no brace, no directive."""
    s = masked_line.strip()
    return bool(s.endswith(";") and not CTRL_KW.match(s) and not is_decl_line(s) and not DECL_KW.match(s)
                and not MULTI_DECL.match(s) and not s.startswith("#") and "{" not in s and "}" not in s)


def introduce_temps(text, tu, fn, d_):
    """[(description, candidate text)] — R8, the INVERSE of R6 (§501-P's "a fresh single-set temp at the use"): the first
    `*(T *)(…)` dereference of a simple statement hoisted into a fresh local of type T, declared at the end of the body's
    declaration run and assigned on the line before the statement. Creating a single-set local moves gcc 2.7.2's allocation
    the same way removing one does (§501-R's birthing boost) and is the count-changing class's natural move: a temp is a copy
    the compiler may or may not fold. A hoist that changes what the code does is simply DIFFERS to the oracle — the bytes are
    the correctness proof, so the generator need not prove independence."""
    lines = text.split("\n")
    out = []
    last = decl_run_end(text, d_)
    used = set(IDENT.findall(sc.mask_text("\n".join(lines[d_["line"] - 1:d_["end"]]))))
    k = 0
    while f"tmp{k}" in used:
        k += 1
    name = f"tmp{k}"
    for i in range(last + 1, d_["end"] - 1):
        raw_line, s = lines[i], sc.mask_text(lines[i])
        if not simple_stmt(s):
            continue
        # the RHS only: a dereference that is the assignment's LEFT side is the store's address, not a value to hoist
        asg = re.search(r"(?<![=!<>+\-*/%&|^~])=(?!=)", s)
        ret = re.match(r"^\s*return\b", s)
        rhs0 = asg.end() if asg else (ret.end() if ret else 0)
        mm = DEREF.search(s, rhs0)
        if not mm:
            continue
        start = mm.start()
        j = mm.end()
        # the operand: a parenthesised group (balanced) or a bare identifier
        if j < len(s) and s[j] == "(":
            depth, e = 0, j
            while e < len(s):
                if s[e] == "(":
                    depth += 1
                elif s[e] == ")":
                    depth -= 1
                    if depth == 0:
                        e += 1
                        break
                e += 1
            if depth != 0:
                continue
        else:
            m2 = re.match(r"[A-Za-z_]\w*", s[j:])
            if not m2:
                continue
            e = j + m2.end()
        expr = raw_line[start:e]
        if s[start:e].count("(") != s[start:e].count(")"):
            continue
        typ = " ".join(mm.group(1).replace("*", " * ").split())
        typ = re.sub(r"\s*\*\s*$", "", typ)                 # `s32 *` -> `s32`: the load's value type
        if typ.count("*"):
            typ = typ.replace(" * ", " *").replace(" *", "*").replace("*", " *")
        indent = raw_line[:len(raw_line) - len(raw_line.lstrip())]
        dind = lines[last][:len(lines[last]) - len(lines[last].lstrip())] if last >= d_["line"] else indent
        cand = list(lines)
        cand[i] = raw_line[:start] + name + raw_line[e:]
        cand.insert(i, f"{indent}{name} = {expr};")
        cand.insert(last + 1, f"{dind}{typ} {name};")
        out.append((f"temp {name} @{i + 1}", "\n".join(cand)))
        # the dereference's BASE hoisted into an address local (lane B, class 2: cse's find_best_addr rewrites `(mem (symbol))`
        # to `(mem (reg))` when a pointer pseudo is cheaper and lives; the S101 positive control 3 stalled on exactly the
        # inverse — an inlined pointer temp under a dereference — because nothing could put the local back)
        if j < len(s) and s[j] == "(":
            inner = raw_line[j + 1:e - 1].strip()
            if inner and not re.fullmatch(r"[A-Za-z_]\w*", sc.mask_text(inner).strip()):
                cand = list(lines)
                cand[i] = raw_line[:j] + name + raw_line[e:]
                cand.insert(i, f"{indent}{name} = {inner};")
                cand.insert(last + 1, f"{dind}s32 {name};")
                out.append((f"base {name} @{i + 1}", "\n".join(cand)))
    return out


BINOP = re.compile(r"<<|>>|[-+&|^*/%]")


def local_types(text, d_):
    """name -> declared type for the locals of the body's declaration run (`s32 a, b;` gives both)."""
    lines = text.split("\n")
    out = {}
    for i in range(d_["line"], decl_run_end(text, d_) + 1):
        s = sc.mask_text(lines[i]).strip()
        if not is_decl_line(s):
            continue
        head = s.rstrip(";").split("=")[0]
        m = re.match(r"^((?:struct\s+|union\s+|unsigned\s+|signed\s+)?[A-Za-z_]\w*)\s+(.*)$", head.strip())
        if not m:
            continue
        typ = m.group(1)
        for part in m.group(2).split(","):
            p = part.strip()
            stars = p.count("*")
            name = re.sub(r"[\*\[\]\d\s]", "", p)
            if name:
                out[name] = typ + (" " + "*" * stars if stars else "")
    return out


def split_operands(expr):
    """[(start, end)] of the depth-0 operands of `expr` separated by binary operators; [] when there is none."""
    depth, parts, cur = 0, [], 0
    i = 0
    while i < len(expr):
        c = expr[i]
        if c in "([":
            depth += 1
        elif c in ")]":
            depth -= 1
        elif depth == 0:
            m = BINOP.match(expr, i)
            if m:
                prev = expr[:i].rstrip()
                nxt = expr[m.end():m.end() + 1]
                # binary when the previous non-space char ends an operand, and not part of a compound/comparison token
                if prev and (prev[-1].isalnum() or prev[-1] in "_)]") and nxt not in "=" and expr[i - 1:i] not in "=<>!":
                    parts.append((cur, i))
                    cur = m.end()
                    i = m.end()
                    continue
        i += 1
    if not parts:
        return []
    parts.append((cur, len(expr)))
    return parts


def hoist_operands(text, tu, fn, d_):
    """[(description, candidate text)] — R8's second form, the exact inverse of R6: a non-trivial depth-0 operand of an
    assignment's or return's expression hoisted into a fresh local, typed like the local it feeds (an assignment to a declared
    local), else like its dereference or cast, else s32. The S101 two-move control inlined `fv = *(u16 *)(p + 0xA) - 0x30;`
    into `gv + (…)`; only a hoist of the whole operand can undo that, and a deref-only hoist could not."""
    lines = text.split("\n")
    out = []
    types = local_types(text, d_)
    used = set(IDENT.findall(sc.mask_text("\n".join(lines[d_["line"] - 1:d_["end"]]))))
    k = 0
    while f"tmp{k}" in used:
        k += 1
    name = f"tmp{k}"
    last = decl_run_end(text, d_)
    for i in range(last + 1, d_["end"] - 1):
        raw_line, s = lines[i], sc.mask_text(lines[i])
        if not simple_stmt(s):
            continue
        asg = re.search(r"(?<![=!<>+\-*/%&|^~])=(?!=)", s)
        ret = re.match(r"^\s*return\b", s)
        start = asg.end() if asg else (ret.end() if ret else -1)
        if start < 0:
            continue
        end = s.rstrip().rfind(";")
        expr = s[start:end]
        parts = split_operands(expr)
        if not parts:
            continue
        lhs = s[:asg.start()].strip() if asg else ""
        lhs_type = types.get(lhs) if re.fullmatch(r"[A-Za-z_]\w*", lhs or "") else None
        n_here = 0
        for ps, pe in parts:
            op = raw_line[start + ps:start + pe].strip()
            opm = s[start + ps:start + pe].strip()
            if not opm or re.fullmatch(r"[A-Za-z_]\w*|-?\d+|-?0x[0-9A-Fa-f]+|&[A-Za-z_]\w*", opm):
                continue                                  # a bare name, a literal, an address: nothing to hoist
            if opm.count("(") != opm.count(")"):
                continue
            mm = DEREF.match(opm)
            cast = re.match(r"^\(\s*((?:struct\s+|union\s+|unsigned\s+)?[A-Za-z_]\w*(?:\s*\*+)?)\s*\)", opm)
            if lhs_type:
                typ = lhs_type
            elif mm:
                typ = re.sub(r"\s*\*\s*$", "", " ".join(mm.group(1).replace("*", " * ").split()))
            elif cast and "(" not in cast.group(1):
                typ = " ".join(cast.group(1).split())
            else:
                typ = "s32"
            indent = raw_line[:len(raw_line) - len(raw_line.lstrip())]
            dind = lines[last][:len(lines[last]) - len(lines[last].lstrip())] if last >= d_["line"] else indent
            cand = list(lines)
            left, right = raw_line[:start + ps].rstrip(), raw_line[start + pe:].lstrip()
            cand[i] = left + " " + name + ((" " + right) if right and right[0] != ";" else right)
            cand.insert(i, f"{indent}{name} = {op};")
            cand.insert(last + 1, f"{dind}{typ} {name};")
            out.append((f"hoist {name} @{i + 1}", "\n".join(cand)))
            n_here += 1
            if n_here >= 3:
                break
    return out


def adjacent_swaps(text, tu, fn, d_):
    """[(description, candidate text)] — R9: two consecutive simple statements at the same indentation exchanged. The
    scheduling class's move (sched.c follows source order for independent statements, cookbook T2/§205); a swap that is not
    independent changes the bytes and the oracle says DIFFERS — again the bytes prove the candidate, not the generator."""
    lines = text.split("\n")
    out = []
    for i in range(d_["line"], d_["end"] - 2):
        a, b = lines[i], lines[i + 1]
        sa, sb = sc.mask_text(a), sc.mask_text(b)
        if not (simple_stmt(sa) and simple_stmt(sb)):
            continue
        if (len(a) - len(a.lstrip())) != (len(b) - len(b.lstrip())):
            continue
        cand = list(lines)
        cand[i], cand[i + 1] = b, a
        out.append((f"swap-stmts @{i + 1}", "\n".join(cand)))
    return out


SCALAR_WIDTHS = {"s32": ("u16", "s16", "u8"), "u32": ("u16", "s16", "u8"), "s16": ("s32", "u16", "u8"), "u16": ("s32", "s16", "u8"),
                 "u8": ("s32", "u16", "s16"), "s8": ("s32", "s16"),
                 # the spellings the drafters used beside the typedefs (`register short sVar2 __asm__("$2")`)
                 "int": ("u16", "s16", "u8"), "short": ("s32", "u16", "u8"), "char": ("s32", "u16")}
WIDTH_RE = r"(?:s32|u32|s16|u16|u8|s8|int|short|char)"
PARAM_WIDTHS = {"s32": ("s16", "u16", "u8"), "u32": ("u16", "s16", "u8"), "s16": ("s32", "u16"), "u16": ("s32", "s16"), "u8": ("s32", "u16"),
                "int": ("s16", "u16", "u8"), "short": ("s32", "u16")}


def width_changes(text, tu, fn, d_):
    """[(description, candidate text)] — R12: a local's declared scalar width changed (s32 -> u16/s16, u16/s16 -> s32; never
    u8). Lane B 1c-1 / 2-2 (§194-B, byte-proven): MIPS has no PROMOTE_MODE, so a narrow local is an HImode pseudo whose set
    from an SImode value cse's insert_regs refuses to join (cse.c:1017-1019) — the copy `ang = a` SURVIVES as `move s0,a0`
    instead of dissolving into one register. Read on the bytes at S101: func_80148D44/func_80148E54's whole residual is
    that one copy."""
    lines = text.split("\n")
    out = []
    for i in range(d_["line"], decl_run_end(text, d_) + 1):
        s = sc.mask_text(lines[i]).strip()
        # a multi-declarator line `int t, v;` (no initializers): one candidate per name, the line split so that name gets the
        # new width and the others keep theirs (S101: the `u8` the target kept was on a name inside such a line)
        mm = re.match(r"^(\s*)(" + WIDTH_RE + r")\s+([A-Za-z_]\w*(?:\s*,\s*[A-Za-z_]\w*)+)\s*;\s*$", lines[i])
        if mm and "=" not in s and "*" not in s and "[" not in s:
            names_ = [n.strip() for n in mm.group(3).split(",")]
            for n in names_:
                others = [x for x in names_ if x != n]
                for alt in SCALAR_WIDTHS[mm.group(2)]:
                    cand = list(lines)
                    cand[i] = f"{mm.group(1)}{mm.group(2)} {', '.join(others)};"
                    cand.insert(i + 1, f"{mm.group(1)}{alt} {n};")
                    out.append((f"width {n} {mm.group(2)}->{alt} @{i + 1}", "\n".join(cand)))
            continue
        # a one-line declaration, or the FIRST line of one whose initializer continues (`s32 tmp = (ratan2(…) -`)
        if not (is_decl_line(s) or (DECL_START.match(s) and s.count("(") > s.count(")"))) \
                or "," in s.split("=")[0] or "*" in s.split("=")[0] or "[" in s:
            continue
        m = re.match(r"^(\s*)(" + WIDTH_RE + r")(\s+[A-Za-z_]\w*\s*(?:=|;))", lines[i])
        if not m:
            continue
        name = re.search(r"[A-Za-z_]\w*", m.group(3)).group(0)
        for alt in SCALAR_WIDTHS[m.group(2)]:
            cand = list(lines)
            cand[i] = m.group(1) + alt + lines[i][m.end(2):]
            out.append((f"width {name} {m.group(2)}->{alt} @{i + 1}", "\n".join(cand)))
    return out


def protos_outside_definition(text, fn, d_):
    """[(line index, match)] — every declaration of `fn` in this TU that lies OUTSIDE its definition.

    R14 has to change a parameter's width at the definition AND at each of these, or the compile dies on `conflicting
    types`. But the bank is BODY-ONLY by contract: `apply_body_core` splices just the function's definition into the
    original file, and `--propagate` remaps that body text to siblings — so a candidate whose edits reach outside the
    definition verifies at score 0 and then cannot be banked at all. S102 measured the cost once: run s4 spent 288 compiles
    reaching 0 on func_80136824 and recorded BANK-REFUSED (`conflicting types for 'func_80136824'`) for a search that had
    succeeded. A generator refuses an input it cannot handle rather than hand back an unbankable candidate (R43); R14
    therefore offers nothing when the TU declares the function anywhere but at its definition, which is exactly the case
    its earlier banked closes did not have."""
    lines = text.split("\n")
    out = []
    for i, l in enumerate(lines):
        if i == d_["line"] - 1:
            continue
        st = sc.mask_text(l)
        m = re.match(r"^(.*?\b" + re.escape(fn) + r"\s*\()(.*)(\)\s*;.*)$", st)
        if m and (st.lstrip().startswith("extern") or i < d_["line"] - 1 or i >= d_["end"]):
            out.append((i, m))
    return out


def param_widths(text, tu, fn, d_):
    """[(description, candidate text)] — R14: a PARAMETER's declared scalar width changed in the header. MIPS has no
    PROMOTE_MODE: a `short` parameter arrives in its SImode register and gcc 2.7.2 sign-extends it IN PLACE (`sra a1,a1,16`) before
    any copy, where an `s32` parameter cast at its uses extends into the destination (`sra s4,a1,16`) — the S101 reading of
    func_80166F58 (`sra a1,a1,0x10; move s4,a1` vs mine `sra s4,a1,0x10`). A width that changes the bytes the wrong way is
    simply DIFFERS; one that matches is the original's declaration."""
    lines = text.split("\n")
    out = []
    if protos_outside_definition(text, fn, d_):
        return out                                        # R43: this candidate could never be BANKED — see below
    hi = lines[d_["line"] - 1]
    m = re.match(r"^(.*?\b" + re.escape(fn) + r"\s*\()(.*)(\).*)$", hi)
    if not m:
        return out
    parts = m.group(2).split(",")
    # the TU's own PROTOTYPES of fn must change with the header, or the compile fails on conflicting types (S101: every R14
    # candidate on func_80166F58 was a COMPILE-ERROR). A prototype in a SHARED header cannot be changed here at all, so such a
    # function is refused outright above (S102: the failure lands at bank time, on an includer, after the scorer has already
    # said 0 — 288 compiles and a BANK-REFUSED for a search that had succeeded)
    protos = []                                            # empty by construction: refused above when it would not be
    for k, part in enumerate(parts):
        pm = re.match(r"^(\s*)(" + WIDTH_RE + r")(\s+[A-Za-z_]\w*\s*)$", part)
        if not pm or pm.group(2) not in PARAM_WIDTHS:
            continue
        name = pm.group(3).strip()
        for alt in PARAM_WIDTHS[pm.group(2)]:
            np = list(parts)
            np[k] = pm.group(1) + alt + pm.group(3)
            cand = list(lines)
            cand[d_["line"] - 1] = m.group(1) + ",".join(np) + m.group(3)
            for i, pm_ in protos:
                pp = pm_.group(2).split(",")
                if k < len(pp):
                    pp[k] = re.sub(r"\b" + WIDTH_RE + r"\b", alt, pp[k], count=1)
                    cand[i] = lines[i][:pm_.start(2)] + ",".join(pp) + lines[i][pm_.end(2):]
            out.append((f"param-width {name} {pm.group(2)}->{alt} @{d_['line']}", "\n".join(cand)))
    return out


def shared_bases(text, tu, fn, d_):
    """[(description, candidate text)] — R8's fourth form: ONE address local for every dereference of the same base
    expression in the body (`*(T *)(p + 4)` … `*(U *)(p + 4)` → `tmp = p + 4; *(T *)tmp … *(U *)tmp`), stores included.
    Lane B class 2 row 6 (cse's find_best_addr keeps an address pseudo that is used twice, and it crosses calls in an $s
    register) and row 12 (a store through a BARE pointer flushes cse's whole memory table, so a global is re-loaded after
    it — the S101 reading of func_8012C890's extra `lhu` behind a `volatile` cast)."""
    lines = text.split("\n")
    out = []
    last = decl_run_end(text, d_)
    used = set(IDENT.findall(sc.mask_text("\n".join(lines[d_["line"] - 1:d_["end"]]))))
    k = 0
    while f"tmp{k}" in used:
        k += 1
    name = f"tmp{k}"
    occ = collections.defaultdict(list)                   # normalized base -> [(line, start, end, raw base)]
    for i in range(last + 1, d_["end"] - 1):
        s = sc.mask_text(lines[i])
        if not simple_stmt(s):
            continue
        for mm in DEREF.finditer(s):
            j = mm.end()
            if j >= len(s) or s[j] != "(":
                continue
            depth, e = 0, j
            while e < len(s):
                if s[e] == "(":
                    depth += 1
                elif s[e] == ")":
                    depth -= 1
                    if depth == 0:
                        e += 1
                        break
                e += 1
            if depth != 0:
                continue
            base = lines[i][j + 1:e - 1]
            nb = " ".join(sc.mask_text(base).split())
            if not nb or re.fullmatch(r"[A-Za-z_]\w*", nb):
                continue
            occ[nb].append((i, j, e, base))
    for nb, places in occ.items():
        if len(places) < 2:
            continue
        i0 = places[0][0]
        indent = lines[i0][:len(lines[i0]) - len(lines[i0].lstrip())]
        dind = lines[last][:len(lines[last]) - len(lines[last].lstrip())] if last >= d_["line"] else indent
        cand = list(lines)
        for i, j, e, _ in sorted(places, key=lambda x: (x[0], -x[1])):   # right to left within a line keeps offsets valid
            cand[i] = cand[i][:j] + name + cand[i][e:]
        cand.insert(i0, f"{indent}{name} = {places[0][3].strip()};")
        cand.insert(last + 1, f"{dind}s32 {name};")
        out.append((f"base-shared {name} @{i0 + 1}", "\n".join(cand)))
    return out


def terms_of(expr):
    """[(op, start, end)] — the depth-0 terms of a `+`/`-` chain (op '' for the first); [] unless EVERY depth-0 binary
    operator of the expression is `+` or `-` (a `*` or `&` in the chain would need precedence the generator does not model)."""
    depth, terms, cur, op = 0, [], 0, ""
    i = 0
    while i < len(expr):
        c = expr[i]
        if c in "([":
            depth += 1
        elif c in ")]":
            depth -= 1
        elif depth == 0:
            m = BINOP.match(expr, i)
            if m:
                prev = expr[:i].rstrip()
                nxt = expr[m.end():m.end() + 1]
                if prev and (prev[-1].isalnum() or prev[-1] in "_)]") and nxt not in "=" and expr[i - 1:i] not in "=<>!":
                    if m.group(0) not in ("+", "-"):
                        return []
                    terms.append((op, cur, i))
                    op, cur = m.group(0), m.end()
                    i = m.end()
                    continue
        i += 1
    if not terms:
        return []
    terms.append((op, cur, len(expr)))
    return terms


def reassociations(text, tu, fn, d_):
    """[(description, candidate text)] — R13: two adjacent terms of a `+`/`-` chain exchanged with their operators
    (`x + a - b` -> `x - b + a`). The evaluation order of a chain is the RTL order (expr.c `binop:` evaluates left to right),
    which is the birth order local-alloc ties on; read on the bytes at S101 (func_8012E364 after two moves: `addu;subu` vs
    `subu;addu`)."""
    lines = text.split("\n")
    out = []
    for i in range(d_["line"], d_["end"] - 1):
        raw_line, s = lines[i], sc.mask_text(lines[i])
        if not simple_stmt(s):
            continue
        asg = re.search(r"(?<![=!<>+\-*/%&|^~])=(?!=)", s)
        ret = re.match(r"^\s*return\b", s)
        start = asg.end() if asg else (ret.end() if ret else -1)
        if start < 0:
            continue
        end = s.rstrip().rfind(";")
        terms = terms_of(s[start:end])
        if len(terms) < 3:
            continue
        for k in range(1, len(terms) - 1):
            (o1, s1, e1), (o2, s2, e2) = terms[k], terms[k + 1]
            t1, t2 = raw_line[start + s1:start + e1].strip(), raw_line[start + s2:start + e2].strip()
            if not t1 or not t2:
                continue
            new_expr = raw_line[start:start + terms[k][1]].rstrip()
            head = new_expr[:len(new_expr) - len(o1)].rstrip() if new_expr.endswith(o1) else new_expr
            rest = raw_line[start + e2:end]
            cand = list(lines)
            cand[i] = raw_line[:start] + head + f" {o2} {t2} {o1} {t1}" + rest + raw_line[end:]
            out.append((f"assoc {o1}{o2} @{i + 1}", "\n".join(cand)))
    return out


def paren_groups(s, start, end):
    """[(open, close+1)] of every balanced parenthesised group of s[start:end], outermost first."""
    out, stack = [], []
    for i in range(start, end):
        if s[i] == "(":
            stack.append(i)
        elif s[i] == ")" and stack:
            out.append((stack.pop(), i + 1))
    return sorted(out)


def common_subexprs(text, tu, fn, d_):
    """[(description, candidate text)] — R8's third form: an RHS spelled identically by two or more statements named ONCE in
    a temp before the first (`*p = -v; *q = -v;` -> `t = -v; *p = t; *q = t;`). Lane B class 2 row 1 ("name a value the
    target computed once"); read on the bytes at S101 (func_8012E364's target negates into a fresh register and stores it
    twice; mine negates in place)."""
    lines = text.split("\n")
    out = []
    last = decl_run_end(text, d_)
    types = local_types(text, d_)
    used = set(IDENT.findall(sc.mask_text("\n".join(lines[d_["line"] - 1:d_["end"]]))))
    k = 0
    while f"tmp{k}" in used:
        k += 1
    name = f"tmp{k}"
    rhs_at = collections.defaultdict(list)
    for i in range(last + 1, d_["end"] - 1):
        s = sc.mask_text(lines[i])
        if not simple_stmt(s):
            continue
        asg = re.search(r"(?<![=!<>+\-*/%&|^~])=(?!=)", s)
        ret = re.match(r"^\s*return\b", s)
        start = asg.end() if asg else (ret.end() if ret else -1)
        if start < 0:
            continue
        end = s.rstrip().rfind(";")
        rhs = " ".join(s[start:end].split())
        if not rhs or re.fullmatch(r"[A-Za-z_]\w*|-?\d+|-?0x[0-9A-Fa-f]+", rhs):
            continue
        rhs_at[rhs].append((i, start, end))
        # a depth-0 OPERAND repeated across statements is also a value computed once in the original (S101: the target of
        # func_8017B238 shifts the parameter once into s0 and reads that; mine recomputes `src << 4` at every use)
        for ps, pe in split_operands(s[start:end]):
            op = " ".join(s[start + ps:start + pe].split())
            if op and not re.fullmatch(r"[A-Za-z_]\w*|-?\d+|-?0x[0-9A-Fa-f]+|&[A-Za-z_]\w*", op) and op != rhs:
                rhs_at[op].append((i, start + ps, start + pe))
        # and every parenthesised group at ANY depth that is not a cast and not a call's argument list (`(q << 4)` inside
        # `*(s32 *)(p + (q << 4))`): the same value computed in two statements is the original's one temp
        for gs, ge in paren_groups(s, start, end):
            inner = " ".join(s[gs + 1:ge - 1].split())
            prev = s[:gs].rstrip()
            if not inner or re.fullmatch(r"[A-Za-z_]\w*|-?\d+|-?0x[0-9A-Fa-f]+", inner) or (prev and (prev[-1].isalnum() or prev[-1] in "_)]")):
                continue                                  # bare, a literal, a call's `f(…)`, or a cast's operand `(T)(…)`
            if re.fullmatch(r"(?:struct\s+|union\s+|unsigned\s+)?[A-Za-z_]\w*\s*\**", inner):
                continue                                  # a cast `(s32 *)`
            rhs_at[inner].append((i, gs + 1, ge - 1))
    for rhs, places in rhs_at.items():
        if len({p[0] for p in places}) < 2:
            continue
        places = sorted(places)
        i0 = places[0][0]
        lhs = sc.mask_text(lines[i0])[:places[0][1] - 1].strip()
        typ = types.get(lhs) if re.fullmatch(r"[A-Za-z_]\w*", lhs) else None
        mm = DEREF.match(rhs)
        if typ is None and mm:
            typ = re.sub(r"\s*\*\s*$", "", " ".join(mm.group(1).replace("*", " * ").split()))
        typ = typ or "s32"
        indent = lines[i0][:len(lines[i0]) - len(lines[i0].lstrip())]
        dind = lines[last][:len(lines[last]) - len(lines[last].lstrip())] if last >= d_["line"] else indent
        cand = list(lines)
        for i, a_end, end in sorted(places, key=lambda x: (x[0], -x[1])):   # right to left within a line keeps offsets valid
            left, right = cand[i][:a_end].rstrip(), cand[i][end:].lstrip()
            sep = "" if left.endswith("(") else " "                      # `(tmp0)`, not `( tmp0)`, inside a kept group
            cand[i] = left + sep + name + ((" " + right) if right and right[0] not in ";)" else right)
        cand.insert(i0, f"{indent}{name} = {lines[i0][places[0][1]:places[0][2]].strip()};")
        cand.insert(last + 1, f"{dind}{typ} {name};")
        out.append((f"cse {name} @{i0 + 1}", "\n".join(cand)))
    return out


def param_copies(text, tu, fn, d_):
    """[(description, candidate text)] — R10: a parameter routed through a body-local copy (`T p2; p2 = p;` after the
    declaration run, every body use renamed), and the reverse (a local that is a plain copy of a parameter and is never
    re-assigned: its uses read the parameter, the copy goes). Lane B 1a-9 (map-proven, S13): the incoming $aN dies at the
    head copy and is free for any scratch temp's first fit; a mid-body copy keeps $aN live into the contested window."""
    lines = text.split("\n")
    out = []
    head = " ".join(lines[d_["line"] - 1].split())
    m = re.match(r"^.*?\b" + re.escape(fn) + r"\s*\((.*)\)\s*\{?$", head)
    if not m:
        return out
    params = []
    for part in m.group(1).split(","):
        # the type and the name must be SEPARATED (whitespace or `*`): without that, `void` parsed as type `voi` + name `d`
        # and a void-parameter function grew a "parameter copy" of a local called d (S101)
        pm = re.match(r"^\s*((?:struct\s+|union\s+|unsigned\s+)?[A-Za-z_]\w*)(\s*\*+\s*|\s+)([A-Za-z_]\w*)\s*$", part)
        if pm and pm.group(3) != "void":
            stars = pm.group(2).count("*")
            typ = " ".join(pm.group(1).split()) + (" " + "*" * stars if stars else "")    # `s32 *` -> the tree's `s32 *p2`
            params.append((typ, pm.group(3)))
    if not params:
        return out
    last = decl_run_end(text, d_)
    lo, hi = d_["line"], d_["end"] - 1
    masked = [sc.mask_text(l) for l in lines]
    body_names = set(IDENT.findall("\n".join(masked[lo:hi])))
    for typ, p in params:
        uses = [i for i in range(last + 1, hi) if re.search(r"(?<![\w.>])%s(?![\w])" % re.escape(p), masked[i])]
        if not uses:
            continue
        new = p + "2"
        while new in body_names:
            new += "2"
        cand = list(lines)
        for i in uses:
            cand[i] = re.sub(r"(?<![\w.>])%s(?![\w])" % re.escape(p), new, lines[i])
        dind = lines[last][:len(lines[last]) - len(lines[last].lstrip())] if last >= lo else "    "
        cand.insert(last + 1, f"{dind}{new} = {p};")
        cand.insert(last + 1, f"{dind}{typ}{'' if typ.endswith('*') else ' '}{new};")
        out.append((f"param-copy {p} @{last + 2}", "\n".join(cand)))
        # the reverse: `x = p;` (or `x = (T)p;` / `x = (T)((U)p);` — func_8017B238's `src = (u8 *)((u32)param_2)`) once, x never
        # assigned again -> every use of x reads p (the casts go with the copy; a use that needed them reads as DIFFERS)
        for i in range(last + 1, hi):
            am = re.match(r"^\s*([A-Za-z_]\w*)\s*=\s*(?:\(\s*[A-Za-z_][\w\s\*]*\)\s*\(?\s*){0,2}%s\s*\)?\s*\)?\s*;\s*$" % re.escape(p), masked[i])
            if not am:
                continue
            x = am.group(1)
            if any(re.search(r"(?<![\w.>])%s\s*(?:[-+*/&|^]|<<|>>)?=(?!=)" % re.escape(x), masked[j]) for j in range(lo, hi) if j != i):
                continue
            cand = list(lines)
            cand[i] = None
            for j in range(lo, hi):
                if j != i and cand[j] is not None and not is_decl_line(masked[j].strip()):
                    cand[j] = re.sub(r"(?<![\w.>])%s(?![\w])" % re.escape(x), p, cand[j])
            out.append((f"param-alias {x}->{p} @{i + 1}", "\n".join(l for l in cand if l is not None)))
    return out


def if_chains(masked, lo, hi):
    """[(chain_lo, chain_hi, [(arm_lo, arm_hi)])] — every brace-form if / else-if / else chain whose lines lie in
    masked[lo:hi] at the body's own depth. `chain_hi` is the line index just past the chain's last `}`; an arm span is the
    lines strictly inside that arm's braces. Depth is counted on the MASKED text, so a brace in a string or a comment is
    not a brace. Chains that do not open a brace on the `if` line (a one-statement `if` without braces) are skipped: the
    sink rewrites arm bodies and needs somewhere to put the statement."""
    out = []
    i = lo
    while i < hi:
        s_ = masked[i].strip()
        if not (s_.startswith("if") and re.match(r"^if\s*\(", s_) and s_.endswith("{")):
            i += 1
            continue
        arms, depth, arm_start, j = [], 0, i + 1, i
        while j < hi:
            nxt = masked[j].strip()
            closes = masked[j].count("}")
            # the CLOSES are counted before the OPENS: on a `} else if (…) {` line the two net to zero, and a depth
            # counter that adds both at once never comes back to zero — the chain then looks like one unterminated arm.
            if j > i and depth - closes == 0:                 # this arm's `}` is on line j
                arms.append((arm_start, j))
                m = re.match(r"^\}\s*else\b(.*)$", nxt)
                if m and m.group(1).strip().endswith("{"):    # `} else {` or `} else if (…) {`
                    arm_start, depth, j = j + 1, 1, j + 1
                    continue
                if nxt == "}" and j + 1 < hi and re.match(r"^else\b", masked[j + 1].strip()) \
                        and masked[j + 1].strip().endswith("{"):
                    arm_start, depth, j = j + 2, 1, j + 2     # the `else …{` on its own line
                    continue
                break
            depth += masked[j].count("{") - closes
            j += 1
        if len(arms) >= 2:
            out.append((i, j + 1, arms))
            i = j + 1
        else:
            i += 1
    return out


def sink_merges(text, tu, fn, d_):
    """[(description, candidate text)] — R15: the statement AFTER an if/else chain sunk into every arm, and the variables
    it consumed deleted. `if (c) { v = e1; } else { v = e2; } w = f(v);` -> `if (c) { w = f(e1); } else { w = f(e2); }`.

    T7 agent a1's crack of func_80156044 (2026-09-10, 130 bodies, the rank-1 head class six rung-G runs left at best 1).
    The mechanism is a REGISTER move, not a scheduling one: a variable set in every arm and read after the merge is a
    CROSS-BLOCK pseudo, so (i) local-alloc never makes a quantity for it (`local-alloc.c:472`, `next_qty` reset per block
    at `:517`) and each arm holds two quantities, which is `block_alloc`'s unrolled `case 2` at `local-alloc.c:1499-1502`
    — one `qty_compare` (`:1578-1596`), higher density first; sinking makes it a third block-local quantity and
    `case 3` at `:1491-1496` FALLS THROUGH into `case 2`, applying that comparison a second time and undoing its own
    exchange, so the two caller-saved colours swap; and (ii) while it is a global allocno it can inherit a copy
    preference from whatever the merge statement's result is passed to (`set_preference` `global.c:1535+`, merged by
    `expand_preferences` `global.c:781-825`, overriding first-fit at `global.c:1034-1067`) — sinking removes it from
    `global.c` entirely. Read the whole reading in `.run/P36/agents/ov_SC04_011__func_80156044/mechanism.md`.

    Applicability is checked, not assumed: every consumed variable must be assigned exactly once in EVERY arm by a simple
    statement, must appear in the merge statement, and must occur nowhere else in the function (declaration + one
    assignment per arm + its uses in the merge statement is its whole census) — otherwise the rewrite would change what
    the code reads. The bytes remain the correctness proof (a rewrite that changes behaviour simply DIFFERS)."""
    lines = text.split("\n")
    masked = [sc.mask_text(l) for l in lines]
    lo, hi = d_["line"], d_["end"] - 1
    whole = sc.mask_text("\n".join(lines[d_["line"] - 1:d_["end"]]))
    out = []
    for c_lo, c_hi, arms in if_chains(masked, lo, hi):
        j = next((k for k in range(c_hi, hi) if masked[k].strip()), None)
        if j is None or not simple_stmt(masked[j]):
            continue
        merge_masked = masked[j]
        eq = re.search(r"(?<![=!<>+\-*/%&|^~])=(?!=)", merge_masked)
        if not eq:                                            # only an assignment merges arm values
            continue
        rhs = merge_masked[eq.end():]
        # every variable assigned exactly once, by a simple statement, in EVERY arm
        per_arm = []
        for a_lo, a_hi in arms:
            got = {}
            for k in range(a_lo, a_hi):
                if not simple_stmt(masked[k]):
                    continue
                m = re.match(r"^\s*([A-Za-z_]\w*)\s*=\s*(.+);\s*$", masked[k])
                if not m:
                    continue
                if m.group(1) in got:                         # assigned twice in one arm: not a single value
                    got[m.group(1)] = None
                else:
                    got[m.group(1)] = k
            per_arm.append(got)
        common = set(k for k, v in per_arm[0].items() if v is not None)
        for g in per_arm[1:]:
            common &= set(k for k, v in g.items() if v is not None)
        names_ = sorted(v for v in common if re.search(r"(?<![\w.>])%s(?![\w])" % re.escape(v), rhs))
        if not names_:
            continue
        decl = {}
        for v in names_:
            # the variable's whole census: one declaration, one assignment per arm, and its uses in the merge statement
            uses = len(re.findall(r"(?<![\w.>])%s(?![\w])" % re.escape(v), whole))
            in_merge = len(re.findall(r"(?<![\w.>])%s(?![\w])" % re.escape(v), merge_masked))
            d_line = next((k for k in range(lo, hi)
                           if is_decl_line(masked[k].strip())
                           and re.search(r"(?<![\w.>])%s(?![\w])\s*(?:=|;|,)" % re.escape(v), masked[k])), None)
            if d_line is None or MULTI_DECL.match(masked[d_line]) or "=" in masked[d_line]:
                decl[v] = None                                # a shared or initialised declaration: leave it standing
            else:
                decl[v] = d_line
            if uses != len(arms) + in_merge + (1 if d_line is not None else 0):
                names_ = None
                break
        if not names_:
            continue
        drop = {decl[v] for v in names_ if decl[v] is not None} | {j}
        after = {}                                            # line index -> the sunk statement to emit just after it
        for a_idx, (a_lo, a_hi) in enumerate(arms):
            stmt = lines[j].strip()
            for v in names_:
                k = per_arm[a_idx][v]
                expr = re.match(r"^\s*[A-Za-z_]\w*\s*=\s*(.+);\s*$", lines[k]).group(1).strip()
                stmt = re.sub(r"(?<![\w.>])%s(?![\w])" % re.escape(v), "(" + expr + ")", stmt)
                drop.add(k)
            tail = a_hi - 1                                   # the arm's LAST BODY line (a_hi is its `}`)
            ref = lines[tail] if lines[tail].strip() else lines[a_lo]
            after[tail] = ref[:len(ref) - len(ref.lstrip())] + stmt
        cand = []
        for k, l in enumerate(lines):                         # a dropped line may still be the one we append after
            if k not in drop:
                cand.append(l)
            if k in after:
                cand.append(after[k])
        out.append((f"sink @{j + 1} ({','.join(names_)})", "\n".join(cand)))
    return out


INT_LIT = re.compile(r"^\s*(?:\(\s*[A-Za-z_][\w \t*]*\)\s*)?(0[xX][0-9A-Fa-f]+|\d+)\s*$")


def constant_holders(text, tu, fn, d_):
    """[(description, candidate text)] — R16: a local whose ONLY assignment is one integer literal, written at every use
    and its declaration removed. R6 stops at a temp read exactly ONCE (the classic def-with-one-use); a constant holder is
    read many times and R6 never offered it, so the whole family was invisible to the search.

    T7 agent a2's crack of func_80168828 (2026-09-10): its `$3` pin held `0x40` and was read as the RHS of four stores.
    Deleting the variable is byte-neutral BY ITSELF — the pin was never doing the work — but it removes a quantity from
    the block, which is what lets the next move reach the allocator (`qty_compare`, `local-alloc.c:1579-1595`, through the
    unrolled switch at `:1485-1512`). A pinned local holding one literal is a CONSTANT-HOLDER, not a register lever, and
    the readable spelling of a constant is the constant."""
    lines = text.split("\n")
    lo, hi = d_["line"], d_["end"] - 1
    masked = [sc.mask_text(l) for l in lines]
    occ = collections.defaultdict(list)
    for i in range(lo, hi):
        for m in IDENT.finditer(masked[i]):
            occ[m.group(1)].append(i)
    out = []
    for v, where in occ.items():
        asg, decl, uses = [], [], []
        for i in where:
            st = masked[i].strip()
            m = re.match(r"^(?:[A-Za-z_][\w \t]*[\s*]\s*\*?\s*)?%s\s*=(?!=)\s*(.+);\s*$" % re.escape(v), st)
            if m:
                asg.append((i, m.group(1)))
            elif is_decl_line(st) and "=" not in st.split(";")[0]:
                decl.append(i)
            else:
                uses.append(i)
        if len(asg) != 1 or len(decl) != 1 or not uses:
            continue
        if MULTI_DECL.match(masked[decl[0]]):             # a shared declaration line: removing it would take the others
            continue
        lit = INT_LIT.match(asg[0][1])
        if not lit:
            continue
        # every use must be a plain read — never an address-of, a member/arrow base, or another assignment's target
        if any(re.search(r"&\s*%s(?![\w])|(?<![\w.>])%s\s*(?:\.|->|\[|=(?!=))" % (re.escape(v), re.escape(v)),
                         masked[i]) for i in uses):
            continue
        cand = []
        for i, l in enumerate(lines):
            if i == decl[0] or i == asg[0][0]:
                continue
            cand.append(re.sub(r"(?<![\w.>])%s(?![\w])" % re.escape(v), lit.group(1), l) if i in uses else l)
        out.append((f"const-holder {v}={lit.group(1)} x{len(uses)}", "\n".join(cand)))
    return out


def constant_run_splits(text, tu, fn, d_):
    """[(description, candidate text)] — R17: a run of consecutive statements assigning the SAME integer literal, split by
    moving the nearest differently-valued literal assignment into it, at each split point.

    T7 agent a2 (2026-09-10), the directed form of a move R9 already contains but reaches by luck: the mechanical search
    needed 2,271 compiles to find this swap in func_80168828, and R17 offers it in a handful. The decision is
    `find_free_reg`'s live-range scan, `local-alloc.c:2109-2110`
    (`for (ins = born_index; ins < dead_index; ins++) IOR_HARD_REG_SET (used, regs_live_at[ins])`): while the two constants'
    ranges are disjoint they share one caller-saved register; splitting the run makes the first live across the second, the
    intervals overlap and the second takes another colour. The discriminator in the dumps is the `.lreg` line `Register N
    used K times across M insns` — M grows when the split lands."""
    lines = text.split("\n")
    lo, hi = d_["line"], d_["end"] - 1
    masked = [sc.mask_text(l) for l in lines]

    def lit_of(i):
        if not simple_stmt(masked[i]):
            return None
        m = re.match(r"^\s*[^=]+=(?!=)\s*(.+);\s*$", masked[i])
        if not m:
            return None
        g = INT_LIT.match(m.group(1))
        return g.group(1) if g else None

    out = []
    i = lo
    while i < hi:
        k = lit_of(i)
        if k is None:
            i += 1
            continue
        j = i
        while j + 1 < hi and lit_of(j + 1) == k:
            j += 1
        if j - i + 1 < 2:                                  # a run is two or more stores of the same literal
            i = j + 1
            continue
        donors = [d for d in (i - 1, j + 1) if lo <= d < hi and lit_of(d) is not None and lit_of(d) != k]
        for d in donors:
            for cut in range(i + 1, j + 1):                # every interior split point of the run
                order = [x for x in range(i, j + 1)]
                seq = [lines[x] for x in order]
                seq.insert(cut - i, lines[d])
                cand = []
                for x, l in enumerate(lines):
                    if x == d:
                        continue
                    if x == i:
                        cand.extend(seq)
                    elif i < x <= j:
                        continue
                    else:
                        cand.append(l)
                out.append((f"const-split @{d + 1}->{cut + 1} ({lit_of(d)} into the {k} run)", "\n".join(cand)))
        i = j + 1
    return out


def bystander_moves(text, tu, fn, d_, span=6):
    """[(description, candidate text)] — R18: one INDEPENDENT simple statement moved to each other position inside its own
    brace block, up to `span` statements away. R9 is this move's adjacent special case; the distance is the point.

    T7 agent a3's reading of func_801397B0 (2026-09-10; it did NOT close that body — this is its proposal, and the body's
    own residual is the control it failed against). MIPS declares no `REG_ALLOC_ORDER`, so `find_free_reg`
    (`local-alloc.c:2158`) hands out the lowest free regno and the winner is simply whichever quantity `qty_compare`
    (`:1579`) reaches first; `combine_regs` (`:1722`) welds an index chain into one quantity that then competes with a
    short-lived value. Moving a statement that depends on NEITHER contender into or out of the interval between the
    chain's birth and its first consumer changes `reg_live_length` and flips that race — at zero instruction cost, unlike
    `R7 do-while`, whose LOOP notes are a full `sched1` barrier (`sched.c:2058-2074`) and therefore always cost one
    displaced insn (a3 enumerated all 60 wrap ranges in its body and every one paid exactly that).

    INDEPENDENCE is conservative and textual: the statement may cross only statements with which it shares NO identifier,
    so what moves is genuinely a bystander. The bytes remain the correctness proof."""
    lines = text.split("\n")
    masked = [sc.mask_text(l) for l in lines]
    lo, hi = d_["line"], d_["end"] - 1
    out = []
    # the statement's own block: the maximal run of lines at one brace depth containing only simple statements
    depth = [0] * (hi + 1)
    d = 0
    for i in range(lo, hi):
        depth[i] = d
        d += masked[i].count("{") - masked[i].count("}")
    ids = {i: set(IDENT.findall(masked[i])) for i in range(lo, hi)}
    for i in range(lo, hi):
        if not simple_stmt(masked[i]) or is_decl_line(masked[i].strip()):
            continue
        for j in range(max(lo, i - span), min(hi, i + span + 1)):
            if j == i or j == i + 1 or not simple_stmt(masked[j]) or depth[j] != depth[i]:
                continue
            # a BLANK line is transparent: the first spelling treated it as an obstacle and so never offered the very
            # move it was written from (the agent's store crosses one blank line to reach its position)
            crossed = [k for k in range(min(i, j), max(i, j) + 1) if k != i and masked[k].strip()]
            if any(depth[k] != depth[i] or not simple_stmt(masked[k]) for k in crossed):
                continue
            # Identifier-disjointness was the first spelling of "bystander" and it was far too strict — three candidates
            # in the body the move was read from, none of them the agent's. It is also not what makes the move safe:
            # byte-identical output IS the same program, so the oracle is the whole correctness proof (the same footing
            # R9's adjacent swap has always stood on). Sharing is kept only as an ORDERING preference: the statements
            # that share nothing with what they cross are the likeliest bystanders, so they are offered first.
            shares = any(ids[i] & ids[k] for k in crossed)
            seq = [l for k, l in enumerate(lines) if k != i]
            dst = j if j < i else j - 1
            seq.insert(dst, lines[i])
            out.append((shares, f"bystander @{i + 1}->{j + 1}", "\n".join(seq)))
    return [(d, c) for _, d, c in sorted(out, key=lambda t: t[0])]


_ARG_DEFS = None


def real_signatures():
    """{name: (arity, params, where, ret)} — every function's REAL signature, read from its definition, cached once."""
    global _ARG_DEFS
    if _ARG_DEFS is None:
        sys.path.insert(0, str(REPO / "tools"))
        import argcheck
        _ARG_DEFS = argcheck.definitions()
    return _ARG_DEFS


# `name(` AND `name)(` — a dropped-argument call is usually ALREADY wrapped in a cast that asserts the wrong arity,
# `((s32 (*)(void))func_801789AC)()`, so a pattern that only sees `name(` misses the whole class it was written for.
CALL = re.compile(r"(?<![\w.>])([A-Za-z_]\w*)\s*(\)?)\s*\(")


def restore_arguments(text, tu, fn, d_, cap=64):
    """[(description, candidate text)] — R19: a call whose in-scope declaration is NARROWER than the callee's real
    definition, re-issued at the callee's full arity through a function-pointer cast, with each in-scope value tried as
    the missing argument and the bytes deciding which.

    THE CLASS (P36 S102). Six T7 agents, working independently on six different functions and never seeing each other's
    results, each reached score 0 by restoring an argument the decompiled source had dropped — m2c drops them at
    unprototyped and indirect call sites. The register pin was in every case hired to fake the instruction the missing
    argument would have emitted. The mechanisms are different each time and each was proven on bytes: combine's
    `added_sets_2` gate (`combine.c:1458`) keeps a copy alive when the value has a second reference; `set_preference`
    (`global.c:1535`, called at `:1348`) records a copy preference for the argument-setup insn and `find_reg` applies it
    over first-fit (`global.c:997-1030`), after which the setup degenerates into a self-move deleted by `jump_optimize`
    (`toplev.c:3142`, `jump.c:424-443`) — so the restored argument can cost ZERO instructions; and reorg's liveness half
    (`reorg.c:3374`), where the argument's `use` in `CALL_INSN_FUNCTION_USAGE` (`reorg.c:428`) refuses a delay-slot steal.

    WHY IT MUST BE A GENERATOR AND NOT A SEARCH MOVE. Every other family here rewrites statements or declarations that
    already exist; this one changes a call's ARITY, which is why those six bodies sat at their starting distance through
    thousands of compiles across seven runs. The cast keeps the edit inside the definition, so the bank stays body-only
    at either declaration scope (widening a file-scope declaration is the types phase's job, not ours).

    The missing argument is not inferable, so it is not inferred: every parameter of the enclosing function and every
    local declared before the call is offered, nearest first, and the byte oracle picks. `cap` bounds that fan-out."""
    defs = real_signatures()
    lines = text.split("\n")
    masked = [sc.mask_text(l) for l in lines]
    lo, hi = d_["line"], d_["end"] - 1
    # what this TU claims about each callee (file scope or block scope — either way it is what the compiler sees here)
    declared = {}
    for i, l in enumerate(masked):
        for m in re.finditer(r"\bextern\s+([A-Za-z_][\w \t*]*?)\b([A-Za-z_]\w*)\s*\(([^;)]*)\)\s*;", l):
            sys.path.insert(0, str(REPO / "tools"))
            import argcheck
            # the TU's own RETURN TYPE is kept and only the ARITY is repaired: this generator restores arguments, it does
            # not re-type results. The first spelling took the return type from the definition and produced
            # `((void (*)(s32))f)(a) != 0`, which does not compile — the defining TU said `void` where this one says `int`.
            declared.setdefault(m.group(2), (argcheck.arity(m.group(3)), m.group(1).strip() or "int"))
    # the values in scope: the enclosing function's parameters, then locals in declaration order
    head = lines[d_["line"] - 1]
    params = []
    mh = re.match(r"^.*?\(([^)]*)\)", head)
    if mh:
        for part in mh.group(1).split(","):
            nm = re.findall(r"([A-Za-z_]\w*)\s*$", part.strip().rstrip("[]"))
            if nm and nm[0] not in ("void",):
                params.append(nm[0])
    locals_ = []
    for i in range(lo, hi):
        st = masked[i].strip()
        if is_decl_line(st) and not st.startswith("extern"):
            for nm in re.findall(r"([A-Za-z_]\w*)\s*(?:=|;|,|\[)", st):
                if nm not in locals_ and nm not in params:
                    locals_.append((i, nm))
    out = []
    for i in range(lo, hi):
        # NOT simple_stmt(): these calls live in `return f() != 0;` and in `if (f()) …` as often as in a plain
        # statement, and the first spelling of this generator found nothing on the very body it was written from
        # because `return` is a control keyword. A declaration line is still skipped; everything else is fair.
        st = masked[i].strip()
        if not st or is_decl_line(st) or st.startswith("#") or st.startswith("extern"):
            continue
        for m in CALL.finditer(masked[i]):
            callee = m.group(1)
            real = defs.get(callee)
            if real is None or callee == fn:
                continue
            dec = declared.get(callee)
            if dec is None or dec[0] >= real[0]:
                continue
            # the call's own argument text, balanced from the opening paren
            start = m.start()
            if m.group(2) == ")":
                # walk back over the cast wrapper `((T (*)(...))name)` to its opening paren
                k, depth2 = m.start(), 0
                while k > 0:
                    k -= 1
                    if masked[i][k] == ")":
                        depth2 += 1
                    elif masked[i][k] == "(":
                        if depth2 == 0:
                            start = k
                            break
                        depth2 -= 1
            depth, j = 0, m.end() - 1
            while j < len(masked[i]):
                if masked[i][j] == "(":
                    depth += 1
                elif masked[i][j] == ")":
                    depth -= 1
                    if depth == 0:
                        break
                j += 1
            if j >= len(masked[i]):
                continue
            args = lines[i][m.end():j].strip()
            have = 0 if args == "" else args.count(",") + 1
            if have >= real[0]:
                continue
            cast = f"(({dec[1]} (*)({real[1]})){callee})"
            avail = [n for n in params] + [n for k, n in locals_ if k < i]
            for val in avail[:cap]:
                newargs = (args + ", " + val) if args else val
                cand = list(lines)
                cand[i] = lines[i][:start] + cast + "(" + newargs + ")" + lines[i][j + 1:]
                out.append((f"argrestore {callee} +{val} @{i + 1}", "\n".join(cand)))
    return out


NARROW_FROM = ("int", "unsigned int", "u32", "s32", "long", "unsigned long")
NARROW_TO = (("short", "s16"), ("unsigned short", "u16"))


def narrow_chains(text, tu, fn, d_, cap=24):
    """[(description, candidate text)] — R20: every local in one def-use CHAIN narrowed together, and each pair of
    chains narrowed together, rather than one declaration at a time.

    T7 agent b3's crack of func_8016CBC0 (P36 S102), and it proved the joint form is NECESSARY: narrowing single
    declarations scored 45, 72, 51 and 24; each chain alone scored 43; **both chains together scored 0**. Every
    intermediate is worse than the search's own best of 11, so a beam over R12's one-declaration moves cannot reach the
    answer from either side — seven runs and 4,811 compiles stalled at 11, and the joint candidate is one compile.

    The mechanism is `insert_regs` (`cse.c:1029-1032`, the early bail at `:1018-1020`): cse puts two pseudos in one
    equivalence class only when their MODES match, so an all-`int` `w = c - 1; c = w;` is a same-mode copy that cse
    collapses and `delete_dead_from_cse` sweeps, giving `addiu c,c,-1` in place — while the narrowed copy-back is a
    TRUNCATION, no equivalence is made, the wide temp stays live and reaches reload as the `move` the target has. The
    other half is `strength_reduce`: a wide counter whose every use is `(short)x` mints a `x << 16` giv that combine
    distributes a `-1` over; a HImode pseudo cannot be that giv. MIPS defines no `PROMOTE_MODE`, which is why any of
    this is reachable from a declaration at all.

    A chain is built conservatively from the body's own text: two locals are linked when one is assigned from the other,
    optionally through a cast or a `± constant`. Only whole components are offered, so a partial narrowing that the
    measurement showed is always worse is never generated."""
    lines = text.split("\n")
    masked = [sc.mask_text(l) for l in lines]
    lo, hi = d_["line"], d_["end"] - 1
    decls = {}                                             # name -> (line index, declared type)
    for i in range(lo, hi):
        st = masked[i].strip()
        if not is_decl_line(st) or st.startswith("extern") or MULTI_DECL.match(masked[i]):
            continue
        m = re.match(r"^\s*((?:unsigned\s+|signed\s+)?[A-Za-z_]\w*)\s+([A-Za-z_]\w*)\s*(?:=[^;]*)?;\s*$", masked[i])
        if m and m.group(1) in NARROW_FROM:
            decls[m.group(2)] = (i, m.group(1))
    if not decls:
        return []
    parent = {n: n for n in decls}

    def find(x):
        while parent[x] != x:
            parent[x] = parent[parent[x]]
            x = parent[x]
        return x

    def union(a, b):
        ra, rb = find(a), find(b)
        if ra != rb:
            parent[rb] = ra

    LINK = re.compile(r"^\s*([A-Za-z_]\w*)\s*=\s*(?:\(\s*[A-Za-z_][\w \t*]*\)\s*)?([A-Za-z_]\w*)"
                      r"(?:\s*[-+]\s*\d+|\s*[-+]\s*0[xX][0-9A-Fa-f]+)?\s*;\s*$")
    for i in range(lo, hi):
        m = LINK.match(masked[i])
        if m and m.group(1) in decls and m.group(2) in decls:
            union(m.group(1), m.group(2))
    comps = collections.defaultdict(list)
    for n in decls:
        comps[find(n)].append(n)
    chains = [sorted(v) for v in comps.values() if len(v) > 1]
    if not chains:
        return []

    def apply(names, to):
        cand = list(lines)
        for n in names:
            i, old = decls[n]
            cand[i] = re.sub(r"(?<![\w])" + re.escape(old) + r"(?=\s)", to, cand[i], count=1)
        return "\n".join(cand)

    out = []
    for to, tag in NARROW_TO:
        for ch in chains[:cap]:
            out.append((f"chain-narrow {'+'.join(ch)} -> {tag}", apply(ch, to)))
        for a in range(len(chains)):                        # the PAIR form: b3's body needed two chains at once
            for b in range(a + 1, len(chains)):
                if len(out) >= cap * 3:
                    break
                out.append((f"chain-narrow {'+'.join(chains[a])} & {'+'.join(chains[b])} -> {tag}",
                            apply(chains[a] + chains[b], to)))
    return out


def second_consumer(text, tu, fn, d_):
    """[(description, candidate text)] — R21: give a computed value a SECOND CONSUMER before its copy, so the compiler
    stops deleting the copy. Two spellings, both byte-proven by T7 agents on the same day (P36 S102):

      * CHAIN (agent b6, func_80161E08, 127 bodies): `v = E; slot = v;`  ->  `v = slot = E;`
      * HOIST (agent b2, func_80162438, 127 bodies): `v = E; slot = v;`  ->  `slot = E; v = E;`

    The residual both closed was COUNT-short by exactly one `move <callee-saved>,<caller-saved>` per site — the copy the
    original keeps and our C let the compiler delete. Two gates decide it and the move defeats both. cse's
    "(set REG0 REG1) where REG0 is the cheapest" rewrite (`cse.c:7440-7501`, guarded at `:7454-7460`) deletes the copy
    only when the insn IMMEDIATELY BEFORE it set the source; and `flow` builds a LOG_LINK only to the FIRST following use
    (`flow.c:2076-2091`), so once the store sits between the compute and the copy, combine is never even offered the
    pair. The chained form reaches the same place differently: `expand_assignment` materialises the value in a compiler
    temp with two consumers, and the single link goes to the store.

    `R9 swap-stmts` can never produce either, because the two statements share the identifier `v` and its independence
    guard refuses the exchange — which is why ~2,000 compiles per body sat flat on both."""
    lines = text.split("\n")
    masked = [sc.mask_text(l) for l in lines]
    lo, hi = d_["line"], d_["end"] - 1
    ASSIGN = re.compile(r"^\s*([A-Za-z_]\w*)\s*=\s*(.+);\s*$")
    out, sites = [], []
    for i in range(lo, hi - 1):
        if not simple_stmt(masked[i]) or not simple_stmt(masked[i + 1]):
            continue
        a = ASSIGN.match(masked[i])
        if not a:
            continue
        v, expr = a.group(1), a.group(2).strip()
        b = re.match(r"^\s*(.+?)\s*=\s*" + re.escape(v) + r"\s*;\s*$", masked[i + 1])
        if not b:
            continue
        slot = lines[i + 1][:lines[i + 1].rindex("=")].strip()
        if not slot or slot == v:
            continue
        raw_expr = lines[i][lines[i].index("=") + 1:].rsplit(";", 1)[0].strip()
        ind = lines[i][:len(lines[i]) - len(lines[i].lstrip())]
        chain = list(lines)
        chain[i] = f"{ind}{v} = {slot} = {raw_expr};"
        chain[i + 1] = None
        out.append((f"chain {v}={slot} @{i + 1}", "\n".join(l for l in chain if l is not None)))
        hoist = list(lines)
        hoist[i] = f"{ind}{slot} = {raw_expr};"
        hoist[i + 1] = f"{ind}{v} = {raw_expr};"
        out.append((f"consumer-first {slot} before {v} @{i + 1}", "\n".join(hoist)))
        sites.append((i, ind, v, slot, raw_expr))
    # THE JOINT FORM: agent b6's body needed all THREE of its sites rewritten at once, and one site alone is worse than
    # the start. The same lesson R20 measured — a hill-climb over single sites walks away from the answer.
    if len(sites) > 1:
        for tag, mk in (("chain", lambda ind, v, slot, e: [f"{ind}{v} = {slot} = {e};"]),
                        ("consumer-first", lambda ind, v, slot, e: [f"{ind}{slot} = {e};", f"{ind}{v} = {e};"])):
            cand, drop = list(lines), set()
            for i, ind, v, slot, e in sites:
                repl = mk(ind, v, slot, e)
                cand[i] = "\n".join(repl)
                if len(repl) == 1:
                    drop.add(i + 1)
            out.append((f"{tag} ALL {len(sites)} sites",
                        "\n".join(l for k, l in enumerate(cand) if k not in drop)))
    return out


ALL_FAMILIES = ("R2", "R3", "R4", "R5", "R6", "R7", "R8", "R9", "R10", "R12", "R13", "R14", "R15", "R16", "R17", "R18", "R19", "R20", "R21")
RUNG_R_FAMILIES = ("R2", "R3", "R4", "R5", "R6", "R7")     # the free sweep's set (R8/R9 are the search engine's until measured)


def recipe_candidates(text, tu, fn, names, limit=24, rng=None, cap=40, blocks=True, focus=(), families=RUNG_R_FAMILIES):
    """[(recipe, description, candidate text)] — the byte-neutral shape recipes of the cookbook, mechanically.
    R2 (§76/§501-R, the allocation ORDER is the bank): the formerly-pinned declarations permuted among their own lines.
    R4: one of them moved through the whole declaration run. R3 (§17a/§501-P): an initializer split off its declaration.
    R5 (§137/§501-R, the caller-saved class): the operand order of one commutative operator — the ONLY recipe here that
    needs no pinned declaration, so a residue of barriers and launders still has candidates. R6 a single-set temp inlined;
    R7 a statement wrapped in a block; R8 a temp introduced (R6's inverse); R9 two adjacent statements swapped.
    `families` selects the generators (the guided search engine, tools/delever_search.py, picks them from the residual's
    class); `cap=None` returns every candidate (the engine ranks them itself)."""
    recs_ = sc.scan_text(text, tu, shared_defs=None)
    d_ = next((r for r in recs_ if r["form"] == "def" and r["name"] == fn), None)
    if d_ is None:
        return []
    fam = set(families)
    dls = decl_lines(text, tu, fn, names) if names else None
    lines = text.split("\n")
    out = []
    rng = rng or random.Random(0)
    idx = [i for i, _ in dls] if dls else []
    body = [t for _, t in dls] if dls else []
    perms = []
    if not dls:
        perms = []
    elif len(body) <= 4:
        import itertools
        perms = [p for p in itertools.permutations(range(len(body)))][1:]      # the identity is the current text
    else:
        seen = set()
        while len(perms) < limit and len(seen) < limit * 4:
            p = tuple(rng.sample(range(len(body)), len(body)))
            seen.add(p)
            if p != tuple(range(len(body))) and p not in perms:
                perms.append(p)
    for p in (perms[:limit] if "R2" in fam else []):
        ls_ = list(lines)
        for slot, src in zip(idx, p):
            ls_[slot] = body[src]
        out.append(("R2", "decl-order " + ",".join(str(x) for x in p), "\n".join(ls_)))
    # R4 (§76/§501-R again, one variable at a time): a formerly-pinned declaration moved to every other slot of the body's
    # declaration run — the allocno creation order the pin used to override. R2 permutes the pinned declarations among
    # THEIR OWN slots; this reaches the orders that involve the untouched declarations too, at one compile each.
    last = decl_run_end(text, d_)
    run_idx = [i for i in range(d_["line"], last + 1) if is_decl_line(sc.mask_text(lines[i]))]
    if dls and len(run_idx) > 1 and "R4" in fam:
        run_txt = [lines[i] for i in run_idx]
        for i, t in dls:
            if i not in run_idx:
                continue
            src = run_idx.index(i)
            name = next((n for n in names if re.search(r"(?<![\w])%s\b" % re.escape(n), t.split("=")[0])), "?")
            for dst in range(len(run_txt)):
                if dst == src:
                    continue
                seq = list(run_txt)
                seq.insert(dst, seq.pop(src))
                ls_ = list(lines)
                for slot, txt in zip(run_idx, seq):
                    ls_[slot] = txt
                out.append(("R4", f"decl-move {name} {src}->{dst}", "\n".join(ls_)))
    for k, (i, t) in enumerate(dls if (dls and "R3" in fam) else []):
        head, _, init = t.partition("=")
        if not init.strip().endswith(";") or "==" in t:
            continue
        name = [n for n in names if re.search(r"(?<![\w])%s\b" % re.escape(n), head)]
        if len(name) != 1:
            continue
        ls_ = list(lines)
        ls_[i] = head.rstrip() + ";"
        indent = t[:len(t) - len(t.lstrip())]
        ls_.insert(last + 1, f"{indent}{name[0]} ={init.rstrip()}")
        out.append(("R3", f"init-split {name[0]}", "\n".join(ls_)))
    if "R5" in fam:
        for desc, cand in commutative_swaps(text, tu, fn, d_):
            out.append(("R5", desc, cand))
    if "R6" in fam:
        for desc, cand in inline_single_set_temps(text, tu, fn, d_):
            out.append(("R6", desc, cand))
    if "R8" in fam:
        for desc, cand in introduce_temps(text, tu, fn, d_):
            out.append(("R8", desc, cand))
        for desc, cand in hoist_operands(text, tu, fn, d_):
            out.append(("R8", desc, cand))
        for desc, cand in common_subexprs(text, tu, fn, d_):
            out.append(("R8", desc, cand))
        for desc, cand in shared_bases(text, tu, fn, d_):
            out.append(("R8", desc, cand))
    if "R14" in fam:
        for desc, cand in param_widths(text, tu, fn, d_):
            out.append(("R14", desc, cand))
    if "R9" in fam:
        for desc, cand in adjacent_swaps(text, tu, fn, d_):
            out.append(("R9", desc, cand))
    if "R10" in fam:
        for desc, cand in param_copies(text, tu, fn, d_):
            out.append(("R10", desc, cand))
    if "R12" in fam:
        for desc, cand in width_changes(text, tu, fn, d_):
            out.append(("R12", desc, cand))
    if "R13" in fam:
        for desc, cand in reassociations(text, tu, fn, d_):
            out.append(("R13", desc, cand))
    if "R15" in fam:
        for desc, cand in sink_merges(text, tu, fn, d_):
            out.append(("R15", desc, cand))
    if "R16" in fam:
        for desc, cand in constant_holders(text, tu, fn, d_):
            out.append(("R16", desc, cand))
    if "R17" in fam:
        for desc, cand in constant_run_splits(text, tu, fn, d_):
            out.append(("R17", desc, cand))
    if "R18" in fam:
        for desc, cand in bystander_moves(text, tu, fn, d_):
            out.append(("R18", desc, cand))
    if "R19" in fam:
        for desc, cand in restore_arguments(text, tu, fn, d_):
            out.append(("R19", desc, cand))
    if "R20" in fam:
        for desc, cand in narrow_chains(text, tu, fn, d_):
            out.append(("R20", desc, cand))
    if "R21" in fam:
        for desc, cand in second_consumer(text, tu, fn, d_):
            out.append(("R21", desc, cand))
    if blocks and "R7" in fam:                            # last: one candidate per statement, so the targeted recipes go first
        for desc, cand in block_wraps(text, tu, fn, d_):
            out.append(("R7", desc, cand))
    seen, uniq = {text}, []                               # never judge the seed twice, nor one candidate twice (R37)
    for rec, desc, cand in out:
        if cand in seen:
            continue
        seen.add(cand)
        uniq.append((rec, desc, cand))
    # LOCALITY: the lever says where to look. R5/R6/R7 emit one candidate per site in body order, and a flat `cap` then
    # truncates the tail — the aborted S99 sweep judged ~200 bodies at cap 40 and closed none, while the shape that closed
    # func_80135D20 was a block wrap well down its body. Candidates carrying a line (`… @N`) are ordered by distance to the
    # nearest NEEDED site; the declaration-level recipes (R2/R3/R4), which are few and have no line, keep the front.
    if focus:
        def key(item):
            m = re.search(r"@(\d+)$", item[1])
            return (1, min(abs(int(m.group(1)) - f) for f in focus)) if m else (0, 0)
        uniq.sort(key=key)
    return uniq if cap is None else uniq[:cap]


def recipes(a):
    """--recipes: rung R over the RESIDUE bodies. The seed is the body's LEVER-FREE text; the first candidate whose object is
    IDENTICAL replaces it and its markers are scrubbed with its levers. Scope, stated (R41): only a body with at least one
    formerly-PINNED declaration has candidates — the recipes are declaration-order and initializer-split levers — so a residue
    of barriers/launders/keep-alives alone is not drawable here and stays for rung D and T7. A hit banks the EXEMPLAR body;
    its copies are a separate step (their text must be remapped, not replayed: the ledger replays a SITE SET, and a reshaped
    body is not one)."""
    ensure_census(a.jobs)
    clean, dirty = src_clean()
    if not clean and not a.dirty_ok:
        sys.exit(f"delever --recipes: src/ is dirty (commit or --restore first):\n{dirty[:400]}")
    ok, why = oracle.calibration_current()
    if not ok:
        sys.exit(f"delever --recipes: calibration not current ({why})")
    by_src = oracle.recipes_by_src(oracle.load_recipes()["recipes"])
    inc = includers()
    sites_by = collections.defaultdict(list)
    for s in load_sites():
        if s.get("fn"):
            sites_by[(s["tu"], s["fn"])].append(s)
    cur = {}
    for r in load_ledger():
        if r.get("tu") and r.get("fn"):
            cur[(r["tu"], r["fn"])] = r

    def recs_for(tu):
        return [r for t_ in inc.get(tu, []) for r in by_src.get(t_, [])] if tu.endswith(".h") else by_src.get(tu, [])

    inflight = {}

    def judge(tu, cand, tag="rec"):
        """judge one candidate, and be killable: the oracle writes the candidate into the tree to compile it, so a SIGTERM
        between the write and the restore leaves a candidate in `src/`. Every in-flight file's ORIGINAL text is held in
        inflight.json, the same file `--restore` reads (P35's rule: a tool restores from its OWN snapshot, never
        `git checkout`) — S99 killed a run mid-judge and found exactly that leftover. The map is per-FILE and written under
        the lock, so a killed parallel run restores every worker's file and not just the last one's.

        `tag` names the scratch object: `compile_obj` writes `<object>.<tag>.o`, so two workers on the same object would
        clobber each other's output — which is why a worker owns a whole TU and headers stay serial."""
        path = REPO / tu
        raw, st = path.read_text(errors="surrogateescape"), path.stat()
        with _LOCK:
            RUN.mkdir(parents=True, exist_ok=True)
            inflight[tu] = raw
            INFLIGHT.write_text(json.dumps(inflight))
        try:
            return oracle.judge_all(recs_for(tu), cand, tag=tag, write_path=(tu if tu.endswith(".h") else None))
        finally:
            restore_file(path, raw, st)
            with _LOCK:
                inflight.pop(tu, None)
                if inflight:
                    INFLIGHT.write_text(json.dumps(inflight))
                else:
                    INFLIGHT.unlink(missing_ok=True)

    def lever_free(tu, raw, fn):
        m, ls = same_len_mask(raw), line_starts(raw)
        edits = []
        for s in sites_by[(tu, fn)]:
            if (s["cls"], s["kind"]) not in REMOVABLE:
                if s["kind"] in DEFERRED_KINDS:
                    raise Refuse("asm-body")
                continue
            edits += site_edits(raw, m, ls, s)
        return apply_edits(raw, edits) if edits else raw

    todo = [(k, r) for k, r in cur.items() if r.get("verdict") == "RESIDUE" and k[1] != FILE_SCOPE_FN]
    if a.only:
        todo = [(k, r) for k, r in todo if any(o in (k[0], k[1]) or o in k[0] for o in a.only)]
    csize = collections.Counter(r.get("nhash_after") or r.get("nhash_before") for _, r in todo)
    todo.sort(key=lambda x: (len([s for s in x[1].get("sites", []) if s.get("verdict") == "NEEDED"]),
                             -csize[x[1].get("nhash_after") or x[1].get("nhash_before")], x[0]))
    todo = todo[:a.limit] if a.limit else todo
    # THE CONTROL, before any verdict is believed (R39), on the first bodies drawn and on BOTH instruments:
    #   the splice machinery — the IDENTITY permutation through the same code must reproduce its input text exactly
    #   (a text assertion, no compile: if the line surgery is not byte-neutral, every "DIFFERS" below is its own);
    #   the oracle — the file exactly as the tree has it must still judge IDENTICAL (its baseline is live, R56).
    bad = []
    for (tu, fn), r in todo[:a.control]:
        raw = (REPO / tu).read_text(errors="surrogateescape")
        names = pin_names(sites_by[(tu, fn)])
        dls = decl_lines(raw, tu, fn, names) if names else None
        if dls:
            lines = raw.split("\n")
            ident = list(lines)
            for slot, src in zip([i for i, _ in dls], range(len(dls))):
                ident[slot] = [t for _, t in dls][src]
            if "\n".join(ident) != raw:
                bad.append((tu, fn, "SPLICE", "the identity permutation did not reproduce the text"))
                continue
        v, dt, err = judge(tu, raw)
        if v != "IDENTICAL":
            bad.append((tu, fn, v, err[:80]))
    print(f"delever --recipes: control {a.control - len(bad)}/{min(a.control, len(todo))} — the identity splice reproduces "
          f"its text and the untouched file its object", flush=True)
    if bad or not todo:
        for b in bad[:5]:
            print(f"  CONTROL FAILED {b[0]}:{b[1]} -> {b[2]} {b[3]}")
        sys.exit("delever --recipes: the control did not pass — no verdict from this run is usable (R39)")
    # THE SWEEP, TU-PARALLEL. A worker owns a WHOLE translation unit: the oracle writes each candidate to the real source
    # path and names its scratch object after the object it builds, so two workers sharing a TU would overwrite each other's
    # source AND their scratch objects. Shared headers stay SERIAL for the same reason one level up — two different headers
    # can be included by the same TU, and both would compile that includer's object at once (`--apply` draws them the same
    # way). Bodies of one TU are judged in that worker, in order, against that file's own text.
    by_tu = collections.OrderedDict()
    for k, r in todo:
        by_tu.setdefault(k[0], []).append((k, r))
    # BOTTOM-UP WITHIN A FILE: a banked body changes the line numbers of everything below it, and the census positions this
    # sweep rewrites from were taken before the run. Judging a file's bodies in descending order means an accepted edit never
    # moves a body still to come (the alternative is a REFUSED token mismatch on every later body of a file that banked one).
    for tu in by_tu:
        by_tu[tu].sort(key=lambda kr: -min((s["line"] for s in sites_by[kr[0]]), default=0))
    tus = [tu for tu in by_tu if not tu.endswith(".h")]
    hdrs = [tu for tu in by_tu if tu.endswith(".h")]
    print(f"delever --recipes: {len(todo)} RESIDUE bodies in {len(tus)} TU(s) + {len(hdrs)} header(s), "
          f"cap {a.cap}, {a.jobs} worker(s)", flush=True)
    state = dict(won=0, tried=0, compiles=0, done=0, skipped=0)
    rows = []
    t0 = time.time()

    def work_tu(tu, tag):
        out = []
        for (tu_, fn), r in by_tu[tu]:
            path = REPO / tu
            raw = path.read_text(errors="surrogateescape")
            names = pin_names(sites_by[(tu, fn)])      # may be empty: R5/R7 need no pinned declaration
            try:
                free = lever_free(tu, raw, fn)
            except Refuse:
                with _LOCK:
                    state["skipped"] += 1
                    state["done"] += 1
                continue
            focus = tuple(s["line"] for s in r.get("sites", []) if s.get("verdict") == "NEEDED" and s.get("line"))
            cands = recipe_candidates(free, tu, fn, names, cap=a.cap, focus=focus)
            if not cands:
                with _LOCK:
                    state["skipped"] += 1
                    state["done"] += 1
                continue
            hit, n_c = None, 0
            for rec, desc, cand in cands:
                v, dt, err = judge(tu, cand, tag=tag)
                n_c += len(recs_for(tu))
                if v == "IDENTICAL":
                    hit = (rec, desc, cand)
                    break
            # THE HASH SURVIVES A MISS. A RESIDUE row leaves the text unchanged, so its after-hash IS its before-hash; writing
            # None there (S99/S100) made the NEXT sweep's rows inherit None as their before-hash — 301 bodies with no hash,
            # which `exemplars()` then read as ONE class keyed None and `--propagate` could never find (found at S101 by
            # reading the ledger, R14; `--repair-nhash` filled them from each body's earlier rows).
            nh = r.get("nhash_after") or r.get("nhash_before")
            row = dict(ts=time.strftime("%Y-%m-%d %H:%M:%S"), label=a.label, rung="R",
                       calib=dict(head=oracle.head(), stamp=oracle.config_stamp()),
                       tu=tu, fn=fn, addr=fn_addr(fn, tu), aliases=r.get("aliases"), header=tu.endswith(".h"),
                       nhash_before=nh, nhash_after=(None if hit else nh), candidates=len(cands), pins=len(names),
                       verdict=("LEVER-FREE" if hit else "RESIDUE"), recipe=(hit[0] if hit else None),
                       how=(hit[1] if hit else None), sites=([] if hit else r.get("sites", [])))
            if hit:
                path.write_text(hit[2], errors="surrogateescape")
                # the body's own markers are now orphans (its levers are gone); every OTHER body's marker is still honest,
                # so the scrub is scoped to this body's line span — a file-wide scrub would leave the census UNMARKED elsewhere
                recs2 = sc.scan_text(hit[2], tu, shared_defs=None)
                d_ = next((x for x in recs2 if x["form"] == "def" and x["name"] == fn), None)
                span = range(d_["line"], d_["end"] + 1) if d_ else range(0)
                scrub = scrub_edits(hit[2], [i + 1 for i, l in enumerate(hit[2].split("\n")) if FAKE in l and i + 1 in span])
                if scrub:
                    cand2 = apply_edits(hit[2], scrub)
                    v2, _, _ = judge(tu, cand2, tag=tag)
                    n_c += len(recs_for(tu))
                    if v2 == "IDENTICAL":
                        path.write_text(cand2, errors="surrogateescape")
                walk = lc.walk_file(path.read_text(errors="surrogateescape"), tu, tu.endswith(".h"))
                row["nhash_after"] = next((x["nhash"] for x in walk["defs"] if x["name"] == fn), None)
            # THE ROW IS WRITTEN WHEN THE BODY IS JUDGED, not at the end of the run. A killed sweep has already written its
            # banked bodies into the tree; holding their rows until the end would leave the census calling them lever-free
            # while the ledger still called them RESIDUE — and a multi-hour sweep WILL be interrupted (S99 killed one).
            ledger_append([row])
            with _LOCK:
                state["tried"] += 1
                state["compiles"] += n_c
                state["done"] += 1
                if hit:
                    state["won"] += 1
                    print(f"  {tu}:{fn} — {hit[0]} {hit[1]} IDENTICAL ({len(names)} pin(s) gone)", flush=True)
                if state["done"] % 25 == 0:               # R55: a lane that runs unattended leaves evidence
                    el = (time.time() - t0) / 60
                    print(f"  [{state['done']}/{len(todo)}] {state['won']} closed · {state['compiles']} compiles · "
                          f"{el:.1f} min · {state['done'] / max(el, 0.01):.0f} bodies/min", flush=True)
        return out

    with ThreadPoolExecutor(max_workers=max(1, a.jobs)) as pool:
        for res in pool.map(lambda it: work_tu(it[1], f"r{it[0] % max(1, a.jobs)}"), list(enumerate(tus))):
            rows += res
    for n, tu in enumerate(hdrs):                          # serial: two headers can share an includer's object
        rows += work_tu(tu, "rh")
    needed = sum(len([s for s in r.get("sites", []) if s.get("verdict") == "NEEDED"]) for _, r in todo)
    print(f"recipes: {state['won']} of {state['tried']} bodies closed lever-free ({needed} NEEDED sites in the "
          f"{len(todo)} drawn, {state['skipped']} with no candidate), {state['compiles']} compiles in "
          f"{(time.time() - t0) / 60:.1f} min")
    return 0


def remap_body(ex_before, ex_after, sib_before):
    """the exemplar's reshaped body, with its `func_/D_` addresses replaced by the sibling's — or (None, why).

    A text class is "identical modulo addresses" (that IS the nhash), so the two old bodies' address tokens correspond
    one for one in order; the map they define is applied to the new body. This is what turns one crack into a whole
    class: the 134-copy classes are the reason the draw is ordered by copies. A ledger REPLAY cannot do it — the ledger
    replays a SITE SET, and a reshaped body is not one."""
    a, b = lc.NORM_SYM.findall(ex_before), lc.NORM_SYM.findall(sib_before)
    if len(a) != len(b):
        return None, f"{len(a)} address tokens in the exemplar, {len(b)} in the sibling"
    m = {}
    for x, y in zip(a, b):
        if m.setdefault(x, y) != y:
            return None, f"`{x}` maps to both `{m[x]}` and `{y}` — not one class"
    return lc.NORM_SYM.sub(lambda mm: m.get(mm.group(0), mm.group(0)), ex_after), None


def propagate(a):
    """--propagate TU FN: the body TU:FN was reshaped and banked; give every RESIDUE sibling of its class the same
    shape, with its own addresses, and judge each on its own objects."""
    tu, fn = a.propagate
    rows = load_ledger()
    chain = [r for r in rows if r.get("tu") == tu and r.get("fn") == fn
             and r.get("verdict") == "LEVER-FREE" and r.get("after_text")]
    if not chain:
        sys.exit(f"delever --propagate: no banked reshape of {tu}:{fn} in the ledger (its row must carry after_text)")
    # THE CLASS is what the body looked like when the campaign found it, so the key and the "before" text come from the
    # FIRST bank in this body's chain; the text to spread is the LAST one (a body reshaped, then tidied, has two rows, and
    # taking the last row's before-hash would look for siblings of a text only this body ever had).
    src_row = dict(chain[-1], nhash_before=chain[0]["nhash_before"], before_text=chain[0]["before_text"])
    key = src_row["nhash_before"]
    cur = {}
    for r in rows:
        if r.get("tu") and r.get("fn"):
            cur[(r["tu"], r["fn"])] = r
    sibs = [k for k, r in cur.items() if k != (tu, fn) and r.get("verdict") == "RESIDUE"
            and (r.get("nhash_after") or r.get("nhash_before")) == key]
    if a.only:
        sibs = [k for k in sibs if any(o in k for o in a.only)]
    sibs = sibs[:a.limit] if a.limit else sibs
    # A reshape may deliberately leave a lever standing (agent a2, S102: one of func_80168828's two pins is forced by the
    # shared header's `(void)` declaration and has no C source, the other was a constant-holder and came off). Its siblings
    # inherit exactly that shape, so the allowance is DERIVED from the exemplar's own banked text — the number of surviving
    # markers — and never simply asserted: a sibling that would carry MORE levers than the exemplar is refused below.
    ex_levers = src_row["after_text"].count(FAKE)
    print(f"delever --propagate: {tu}:{fn} -> {len(sibs)} sibling(s) of class {key[:12]}"
          + (f"; the exemplar keeps {ex_levers} marked lever(s), so its siblings may too" if ex_levers else ""), flush=True)
    if not sibs:
        return 0, 0, 0                                    # R68: an empty work list is a refusal, not a success (a tuple like every return — the
                                                          # bare `1` here killed run g4s's process after its real propagations, S101)
    ok = bad = 0
    for stu, sfn in sibs:
        path = REPO / stu
        raw = path.read_text(errors="surrogateescape")
        d = next((r for r in sc.scan_text(raw, stu, shared_defs=None) if r["form"] == "def" and r["name"] == sfn), None)
        if d is None:
            print(f"  {stu}:{sfn}: not defined there — SKIPPED", flush=True)
            bad += 1
            continue
        ls = line_starts(raw)
        sib_before = raw[ls[d["line"] - 1]:ls[d["end"]]]
        if lc.norm_hash(sc.mask_text(sib_before)) != key:
            print(f"  {stu}:{sfn}: its text is not this class any more — SKIPPED", flush=True)
            bad += 1
            continue
        body, why = remap_body(src_row["before_text"], src_row["after_text"], sib_before)
        if body is None:
            print(f"  {stu}:{sfn}: {why} — SKIPPED", flush=True)
            bad += 1
            continue
        # IN PROCESS (S101): a subprocess per sibling reloaded the recipes and the includer map every time — ~1.3 s of the
        # ~1.5 s each sibling cost, ≈40 min for run g3's 1,503 siblings
        if body.count(FAKE) > ex_levers:
            print(f"  {stu}:{sfn}: the remap left {body.count(FAKE)} lever(s) where the exemplar keeps {ex_levers} "
                  f"— SKIPPED", flush=True)
            bad += 1
            continue
        ok_, line = apply_body_core(stu, sfn, body, a.label, src_row.get("rung") or "R", source=f"propagate:{tu}:{fn}",
                                    allow_residue=(getattr(a, "allow_residue", False) or ex_levers > 0))  # getattr: the search engine builds its own Namespace for this call (R43 — a library must not assume its caller's)
        print(f"  {line[:200]}", flush=True)
        ok += ok_
        bad += not ok_
    print(f"delever --propagate: {ok} of {len(sibs)} sibling(s) banked, {bad} refused")
    return ok, len(sibs), bad


def repair_nhash():
    """--repair-nhash: fill the text hash of every RESIDUE row that carries none (the S99/S100 rung-R rows) from the same body's
    earlier rows — a RESIDUE verdict leaves the text unchanged, so the body's hash is the last one any row recorded for it.
    Rewrites the ledger in place through a temp file (the instrument's own defect, repaired once and recorded; R35)."""
    rows = load_ledger()
    last = {}
    fixed = 0
    for r in rows:
        k = (r.get("tu"), r.get("fn"))
        if not k[0] or not k[1]:
            continue
        nh = r.get("nhash_after") or r.get("nhash_before")
        if nh:
            last[k] = nh
        elif r.get("verdict") == "RESIDUE" and k in last:
            r["nhash_before"] = r["nhash_after"] = last[k]
            r["nhash_repaired"] = True
            fixed += 1
    left = sum(1 for r in rows if r.get("verdict") == "RESIDUE" and not (r.get("nhash_after") or r.get("nhash_before")))
    tmp = LEDGER.with_suffix(".tmp")
    tmp.write_text("".join(json.dumps(r) + "\n" for r in rows))
    os.replace(tmp, LEDGER)
    print(f"delever --repair-nhash: {fixed} RESIDUE row(s) given their body's hash from earlier rows; {left} still without one")
    return 0 if left == 0 else 1


def status():
    rows = load_ledger()
    done, ex = ledger_index(rows)
    latest = {}
    for r in rows:
        latest[(r["tu"], r["fn"])] = r
    c = collections.Counter(r["verdict"] for r in latest.values())
    sc_ = collections.Counter(d["verdict"] for r in latest.values() for d in r.get("sites", []))
    kinds = collections.Counter((d["kind"], d["verdict"]) for r in latest.values() for d in r.get("sites", []))
    print(f"delever --status: {len(rows)} rows, {len(latest)} bodies (latest row each): {dict(c)}")
    print(f"  sites: {dict(sc_)}")
    for (k, v), n in sorted(kinds.items()):
        print(f"    {k:12s} {v:10s} {n}")
    print(f"  after-hashes done {len(done)} · exemplars {len(ex)} · labels {sorted({r['label'] for r in rows})}")
    return 0


def apply_body(a):
    """--apply-body TU FN FILE: the function's definition replaced by FILE's text, judged through every recipe (or every includer),
    kept and ledgered on IDENTICAL; refused if the new body still carries a class A/B lever (unless --allow-residue)."""
    tu, fn, src = a.apply_body
    path = REPO / tu
    if not path.exists():
        sys.exit(f"delever --apply-body: no such file {tu}")
    clean, dirty = src_clean()
    if not clean and not a.dirty_ok:
        sys.exit(f"delever --apply-body: src/ is dirty (commit or --restore first):\n{dirty[:400]}")
    ok, why = oracle.calibration_current()
    if not ok:
        sys.exit(f"delever --apply-body: calibration not current ({why})")
    new = pathlib.Path(src).read_text(errors="surrogateescape")
    ok_, line = apply_body_core(tu, fn, new, a.label, a.rung, allow_residue=a.allow_residue, source=src)
    print(line)
    return 0 if ok_ else 1


_recipes_cache = {}


def _recipes_and_includers():
    """the recipe map and the includer map, loaded once per process (a subprocess per bank paid ~1.3 s for these)."""
    if "by_src" not in _recipes_cache:
        _recipes_cache["by_src"] = oracle.recipes_by_src(oracle.load_recipes()["recipes"])
        _recipes_cache["inc"] = includers()
    return _recipes_cache["by_src"], _recipes_cache["inc"]


def apply_body_core(tu, fn, new, label, rung, allow_residue=False, source=""):
    """(ok, line): the function's definition in TU replaced by `new` (the body text), judged through every recipe (or every
    includer), kept and ledgered on IDENTICAL; refused (ok False, the reason in `line`) if the body still carries a class A/B
    lever, equals the current text, or cannot be judged. The library form of --apply-body — the engine and --propagate call it
    in process; the CLI wrapper adds the clean-tree check."""
    path = REPO / tu
    if not path.exists():
        return False, f"delever --apply-body: no such file {tu}"
    ok, why = oracle.calibration_current()
    if not ok:
        return False, f"delever --apply-body: calibration not current ({why})"
    new = new.rstrip("\n") + "\n"
    raw = path.read_text(errors="surrogateescape")
    st = path.stat()
    recs = lc.sc.scan_text(raw, tu, shared_defs=None)
    d = next((r for r in recs if r["form"] == "def" and r["name"] == fn), None)
    if d is None:
        return False, f"delever --apply-body: {fn} is not defined in {tu}"
    ls = line_starts(raw)
    before = raw[ls[d["line"] - 1]:ls[d["end"]]]
    cand = raw[:ls[d["line"] - 1]] + new + raw[ls[d["end"]]:]
    if cand == raw:
        return False, "delever --apply-body: the new body equals the current text (no-op, R37)"
    walk = lc.walk_file(cand, tu, tu.endswith(".h"))
    levers = [s for s in walk["sites"] if s.get("fn") == fn and s["cls"] in "AB" and s["kind"] not in lc.NON_LEVER_KINDS]
    if levers and not allow_residue:
        return False, (f"delever --apply-body: the new body still carries {len(levers)} class A/B lever site(s) "
                       f"({[(s['kind'], s['detail'], s['line']) for s in levers][:6]}) — no lever of any class may remain (--allow-residue to override)")
    by_src, inc = _recipes_and_includers()
    recs_ = [r for t in inc.get(tu, []) for r in by_src.get(t, [])] if tu.endswith(".h") else by_src.get(tu, [])
    if not recs_:
        return False, f"delever --apply-body: no recipe compiles {tu}"
    try:
        v, dt, err = oracle.judge_all(recs_, cand, tag="body", write_path=(tu if tu.endswith(".h") else None))
    finally:
        restore_file(path, raw, st)
    nh_before = lc.norm_hash(sc.mask_text(before))
    nh_after = next((x["nhash"] for x in walk["defs"] if x["name"] == fn), None)
    row = dict(ts=time.strftime("%Y-%m-%d %H:%M:%S"), label=label, rung=rung, calib=dict(head=oracle.head(), stamp=oracle.config_stamp()),
               tu=tu, fn=fn, addr=fn_addr(fn, tu), aliases=None, header=tu.endswith(".h"), includers=len(inc.get(tu, [])),
               nhash_before=nh_before, nhash_after=nh_after, source=source, verdict=("LEVER-FREE" if v == "IDENTICAL" else f"BODY-{v}"),
               sites=[dict(ord=i, kind=s["kind"], cls=s["cls"], detail=s["detail"], via=s.get("via", ""), line=s["line"], verdict="NEEDED",
                           why="left by the author", oracle="") for i, s in enumerate(levers)],
               compiles=len(recs_), seconds=round(dt, 3), objects=[r["obj"] for r in recs_],
               # the body AS IT WAS: --propagate needs it to map this class's addresses onto a sibling's, and after the
               # write it exists nowhere else (the tree has moved on and the ledger is the record)
               before_text=before, after_text=new)
    if v == "IDENTICAL":
        path.write_text(cand, errors="surrogateescape")
        ledger_append([row])
        return True, f"delever --apply-body: {tu}:{fn} IDENTICAL on {len(recs_)} object(s) ({dt:.2f} s) — KEPT, ledgered (rung {rung}, {label})"
    ledger_append([row])
    return False, f"delever --apply-body: {tu}:{fn} {v} on {len(recs_)} object(s) — NOT kept ({err[:200]})"


# ----------------------------------------------------------------------------------------------------------------------
# selftest: the fixture through the census's own parser, the rewrites, the ladder against a STUB oracle, the markers, a replay
# ----------------------------------------------------------------------------------------------------------------------
FIXTURE = r'''#include "common.h"
extern volatile s32 D_800B0000;
extern s32 D_800A46D0;
#define SHB(x) __asm__ __volatile__("" : "=r"(x) : "0"(x))
#define LAUNDER_X(p) \
    ({ s32 _m = (s32)(p); __asm__("" : "=r"(_m) : "0"(_m)); _m; })
#define XFERX(SRCOFF)                                                           \
    src = *(s32 *)(a0 + SRCOFF);                                                \
    __asm__("" : "=r"(src) : "0"(src));                                         \
    func_80012000(src);
/* a comment carrying a pin: register s32 fake __asm__("$5"); */
s32 func_80128218(s32 a0)
{
    register s32 zr __asm__("$0");
    register s32 s __asm__("$16") = a0 + zr;
    register s32 t __asm__("$17");
    register s32 *p __asm__("$4");
    register int plain;
    volatile s32 buf[2];
    s32 v = *(volatile s32 *)(a0 + 0x1C);
    s32 src;
    t = 3;
    __asm__ __volatile__("" ::: "memory");
    __asm__("" : "=r"(v) : "0"(v));
    __asm__("" : "=r"(p) : "0"(&D_800A46D0));
    __asm__ __volatile__("" : : "r"(s));
    __asm__("addu %0,%1,$zero" : "=r"(v) : "r"(s));
    SHB(v);
    v += (s32)LAUNDER_X(&buf);
    XFERX(0xCC);
    buf[0] = zr;
    return v + zr + plain + buf[0] + (s32)p + t + D_800B0000;
}
s32 func_80128300(s32 a0)
{
    register s32 zr __asm__("$0");
    zr = a0;
    return zr;
}
void func_80128400(void)
{
    __asm__ __volatile__(".set noreorder\n" "addiu $sp, $sp, -24\n" "sw $ra, 16($sp)\n" "jal func_80012000\n" "nop\n"
                         "lw $ra, 16($sp)\n" "jr $ra\n" "addiu $sp, $sp, 24\n" : : : "memory");
}
#if 0
static void dead(void) { register s32 x __asm__("$8"); }
#endif
'''
FIXTURE_COPY = FIXTURE.replace("func_80128218", "func_80138218").replace("D_800A46D0", "D_800B46D0").replace("D_800B0000", "D_800B1000")


def idx_of(b, kind, line):
    return next(i for i, s in enumerate(b["sites"]) if s["kind"] == kind and s["line"] == line)


def selftest():
    import tempfile
    ok = True
    def fail(msg):
        nonlocal ok
        ok = False
        print("selftest FAIL:", msg)
    d = pathlib.Path(tempfile.mkdtemp(prefix="delever_selftest_", dir=str(RUN if RUN.exists() else REPO / ".run")))
    rel = "src/fx/x.c"
    rel2 = "src/fx/y.c"
    (d / "x.c").write_text(FIXTURE)
    walk = lc.walk_file(FIXTURE, rel, False)
    sites = [dict(s, aliases=["fx"], header=False, includers=0) for s in walk["sites"]]
    bodies = bodies_from_sites(sites, with_file_scope=True)
    b = bodies[(rel, "func_80128218")]
    kinds = collections.Counter(s["kind"] for s in b["sites"])
    want = {"pin": 4, "register": 1, "decl-body": 1, "cast": 1, "barrier": 1, "launder": 5, "keepalive": 1, "instruction": 1}
    if dict(kinds) != want:
        fail(f"fixture sites {dict(kinds)} != {want}")
    raw = FIXTURE
    m = same_len_mask(raw)
    ls = line_starts(raw)
    # the rewrites, one by one
    texts = {}
    refused = {}
    for s in b["sites"]:
        try:
            texts[(s["kind"], s["line"])] = apply_edits(raw, site_edits(raw, m, ls, s))
        except Refuse as ex:
            refused[(s["kind"], s["line"], s.get("via", ""))] = str(ex)
    def line_of(text, needle):
        return next((ln for ln in text.split("\n") if needle in ln), None)
    t = texts.get(("pin", 15))
    if not t or "register" in line_of(t, "s32 s ") or 'asm' in line_of(t, "s32 s ") or "= a0 + zr;" not in line_of(t, "s32 s "):
        fail(f"pin with initializer -> `{line_of(t or '', 's32 s ')}`")
    t = texts.get(("pin", 14))
    if not t or "zr" in t.split("func_80128300")[0] or "buf[0] = 0;" not in t or "return v + 0 + plain" not in t or "= a0 + 0;" not in t:
        fail("zero pin: declaration deleted, uses -> 0 (inside the other pin's initializer too)")
    # both pins at once: the zero use inside the $16 pin's initializer is composed into that pin's replacement
    both = apply_edits(raw, site_edits(raw, m, ls, b["sites"][idx_of(b, "pin", 14)]) + site_edits(raw, m, ls, b["sites"][idx_of(b, "pin", 15)]))
    if "    s32 s = a0 + 0;" not in both or "zr" in both.split("func_80128300")[0]:
        fail(f"zero use composed into the host pin's replacement: `{line_of(both, 's32 s ')}`")
    t = texts.get(("launder", 25))
    if not t or line_of(t, "p = &D_800A46D0;") is None:
        fail("launder with a different input is an ASSIGNMENT")
    t = texts.get(("launder", 24))
    if not t or '"=r"(v) : "0"(v)' in t.split("SHB(v)")[0].split("#define")[-1]:
        fail("same-expression launder deleted")
    t = texts.get(("instruction", 27))
    if not t or "v = s;" not in t:
        fail(f"addu-$zero instruction -> assignment: `{line_of(t or '', 'v = s') }`")
    t = texts.get(("launder", 28))
    if not t or "SHB(v);" in t.split("#define XFERX")[-1]:
        fail("SHB(v); (a pure launder statement macro) deleted")
    t = texts.get(("launder", 29))
    if not t or "v += (s32)((s32)(&buf));" not in t:
        fail(f"expression-launder macro -> its value: `{line_of(t or '', 'v +=')}`")
    if not any(k[0] == "launder" and k[2] == "XFERX" for k in refused):
        fail(f"compound macro use must be REFUSED (got {refused})")
    t = texts.get(("cast", 20))
    if not t or "*(s32 *)(a0 + 0x1C)" not in t:
        fail("volatile cast dropped")
    t = texts.get(("decl-body", 19))
    if not t or "    s32 buf[2];" not in t:
        fail("volatile declaration dropped")
    t = texts.get(("register", 18))
    if not t or "    int plain;" not in t:
        fail("bare register dropped")
    t = texts.get(("barrier", 23))
    if not t or '::: "memory"' in t.split("func_80128218")[1]:
        fail("barrier deleted")
    # the assigned zero pin is refused; the asm-body is deferred (no removable site)
    b2 = bodies[(rel, "func_80128300")]
    try:
        site_edits(raw, m, ls, b2["sites"][0])
        fail("assigned zero-register variable must be REFUSED")
    except Refuse:
        pass
    b3 = bodies[(rel, "func_80128400")]
    if b3["sites"] or len(b3["deferred"]) != 1:
        fail(f"asm-body: sites {len(b3['sites'])} deferred {len(b3['deferred'])}")
    fs = bodies.get((rel, FILE_SCOPE_FN))
    if not fs or len(fs["sites"]) != 1:
        fail("file-scope volatile pseudo-body")
    # the ladder against a stub oracle: NEEDED = the $17 pin and the barrier; the keep-alive's removal CRASHES the compiler
    idx = {(s["kind"], s["line"]): i for i, s in enumerate(b["sites"])}
    needed_ids = {idx[("pin", 16)], idx[("barrier", 23)]}
    crash_ids = {idx[("keepalive", 26)]}
    calls = []
    def stub(text, removed, tag):
        calls.append(tag)
        if removed & crash_ids:
            return "COMPILE-CRASH", 0.01, "CRASH: 123 Aborted (core dumped)"
        return ("DIFFERS" if removed & needed_ids else "IDENTICAL"), 0.01, ""
    res = ladder(b, raw, m, ls, stub)
    got = {(x["kind"], x["line"]): x["verdict"] for x in res["sites"]}
    if res["verdict"] != "RESIDUE" or res["rung"] != "B":
        fail(f"ladder verdict {res['verdict']} rung {res['rung']}")
    if got.get(("pin", 16)) != "NEEDED" or got.get(("barrier", 23)) != "NEEDED" or got.get(("keepalive", 26)) != "NEEDED":
        fail(f"needed set {got}")
    if [x for x in res["sites"] if x["kind"] == "keepalive"][0]["oracle"] != "COMPILE-CRASH":
        fail("a crashing candidate must be NEEDED with the CRASH verdict")
    if got.get(("launder", 25)) != "REWRITTEN" or got.get(("instruction", 27)) != "REWRITTEN" or got.get(("launder", 29)) != "REWRITTEN":
        fail(f"rewritten verdicts {got}")
    if got.get(("launder", 30)) != "REFUSED":
        fail("the compound-macro site is REFUSED in the ladder")
    if res["compiles"] != 1 + (len(b["sites"]) - res["refused"]):
        fail(f"rung A + greedy compiles {res['compiles']} for {len(b['sites'])} sites ({res['refused']} refused)")
    # the markers: class A/B survivors only, one per line, C/D never
    survivors = [(b["sites"][x["ord"]], x["verdict"], x["oracle"] or x["why"]) for x in res["sites"] if x["verdict"] in ("NEEDED", "REFUSED")]
    survivors.append((b3["deferred"][0], "DEFERRED", "T7"))
    final = apply_edits(raw, res["accepted"] + marker_edits(raw, ls, survivors, "rung B", "self1"))
    fl = final.split("\n")
    if sum(1 for l in fl if FAKE in l) != 5:
        fail(f"markers: {sum(1 for l in fl if FAKE in l)} lines carry one (want 5: pin $17, barrier, keepalive, XFERX, asm-body)")
    if not any("pin $17 — NEEDED DIFFERS (P36 rung B self1)" in l for l in fl):
        fail("marker text for the needed pin")
    if not any("keepalive — NEEDED COMPILE-CRASH" in l for l in fl):
        fail("marker text for the crash")
    if not any("launder via XFERX — REFUSED" in l for l in fl):
        fail("marker text for the compound macro")
    if any(FAKE in l and ("buf[2]" in l or "int plain" in l) for l in fl):
        fail("class C/D sites must never carry a marker")
    if lc.walk_file(final, rel, False)["defs"][0]["nhash"] == b["nhash"]:
        fail("the after-hash must differ from the before-hash once sites were removed")
    # a marker does not change the hash: the same final text with the markers stripped hashes the same
    stripped = "\n".join(re.sub(r"\s*// !FAKE:.*$", "", l) for l in fl)
    if lc.walk_file(stripped, rel, False)["defs"][0]["nhash"] != lc.walk_file(final, rel, False)["defs"][0]["nhash"]:
        fail("markers changed the normalized hash")
    # re-marking replaces the old marker instead of stacking a second one
    ls2 = line_starts(final)
    ln17 = next(i + 1 for i, l in enumerate(fl) if 'pin $17' in l)
    again = apply_edits(final, marker_edits(final, ls2, [(dict(b["sites"][idx[("pin", 16)]], line=ln17), "NEEDED", "DIFFERS")], "rung B", "self2"))
    if again.count("pin $17 — NEEDED") != 1 or "self2" not in again or "self1)  // !FAKE" in again:
        fail("re-marking must replace the line's marker")
    # the replay on a copy with a different address environment: one compile, the same verdicts
    walk2 = lc.walk_file(FIXTURE_COPY, rel2, False)
    sites2 = [dict(s, aliases=["fy"], header=False, includers=0) for s in walk2["sites"]]
    bodies2 = bodies_from_sites(sites2, with_file_scope=True)
    bc = bodies2[(rel2, "func_80138218")]
    if bc["nhash"] != b["nhash"]:
        fail("the copy's nhash must equal the exemplar's (addresses masked)")
    exemplar_row = dict(tu=rel, fn="func_80128218", sites=res["sites"])
    calls.clear()
    res2 = ladder(bc, FIXTURE_COPY, same_len_mask(FIXTURE_COPY), line_starts(FIXTURE_COPY), stub, replay_from=exemplar_row)
    if res2["rung"] != "replay" or res2["compiles"] != 1 or {(x["kind"], x["line"]): x["verdict"] for x in res2["sites"]} != got:
        fail(f"replay: rung {res2['rung']} compiles {res2['compiles']}")
    # a disagreeing replay falls through to the full ladder
    def stub2(text, removed, tag):
        return ("DIFFERS" if removed & (needed_ids | {idx[('pin', 15)]}) else "IDENTICAL"), 0.01, ""
    res3 = ladder(bc, FIXTURE_COPY, same_len_mask(FIXTURE_COPY), line_starts(FIXTURE_COPY), stub2, replay_from=exemplar_row)
    if not res3["replay_disagreed"] or res3["rung"] != "B" or {x["line"] for x in res3["sites"] if x["verdict"] == "NEEDED"} != {15, 16, 23}:
        fail(f"disagreeing replay: {res3['replay_disagreed']} rung {res3['rung']} needed {[x['line'] for x in res3['sites'] if x['verdict'] == 'NEEDED']}")
    # a site that carried an older marker: the marker goes with the statement (a rewrite) or with the line (a deletion)
    stale = ('s32 func_80128600(s32 a0)\n{\n    register s32 s __asm__("$16") = a0;  // !FAKE: pin $16 — NEEDED DIFFERS (P36 rung B old)\n'
             '    __asm__ __volatile__("");  // !FAKE: barrier — NEEDED DIFFERS (P36 rung B old)\n    return s;\n}\n')
    ws = lc.walk_file(stale, "src/fx/z.c", False)
    sb = bodies_from_sites([dict(s, aliases=["fz"], header=False, includers=0) for s in ws["sites"]])[("src/fx/z.c", "func_80128600")]
    sm, sls = same_len_mask(stale), line_starts(stale)
    scrubbed = apply_edits(stale, [e for s in sb["sites"] for e in site_edits(stale, sm, sls, s)])
    if FAKE in scrubbed or "    s32 s = a0;\n    return s;" not in scrubbed:
        fail(f"stale markers must go with their sites:\n{scrubbed}")
    orphan_text = "int x;\n    // !FAKE: pin $5 — gone (P36 rung B old)\nint y = 1;  // !FAKE: barrier — gone (P36 rung B old)\n"
    if apply_edits(orphan_text, scrub_edits(orphan_text, [2, 3])) != "int x;\nint y = 1;\n":
        fail("scrub_edits: a marker-only line is deleted, a trailing marker stripped")
    # a no-op candidate is refused; overlapping edits are refused
    try:
        apply_edits(raw, [(0, 5, "x"), (3, 8, "y")])
        fail("overlapping edits must be refused")
    except Refuse:
        pass
    # the ledger index: after-hash done, before-hash replays, the latest row wins
    rows = [dict(tu="a.c", fn="f", verdict="RESIDUE", nhash_before="h1", nhash_after="h2", sites=[]),
            dict(tu="b.c", fn="g", verdict="LEVER-FREE", nhash_before="h1", nhash_after="h3", sites=[{"ord": 0}])]
    done, ex = ledger_index(rows)
    if done != {("a.c", "f", "h2"), ("b.c", "g", "h3")} or ex["h1"]["nhash_after"] != "h3":
        fail("ledger index: done is per body, the exemplar per text")
    # a copy elsewhere with the exemplar's after-hash is NOT done (it has no row of its own)
    fake_bodies = {("c.c", "h"): dict(tu="c.c", fn="h", fn_line=1, fn_end=3, nhash="h2", aliases=["x"], header=False, includers=0, sites=[{"line": 1, "col": 1, "kind": "pin", "cls": "A", "detail": "$1"}], frozen=[], deferred=[])}
    plan_, total_, _ = make_plan(fake_bodies, rows, False, 10, None)
    if total_ != 1:
        fail("a copy with a judged text but no row of its own must still be drawn")
    # rung R's candidate generators, on a fixture whose every answer is known by hand
    RFIX = ("void rfix(int p)\n{\n    int a = p;\n    int b;\n    int c;\n"
            "    if (a == b) a = b & c;\n    c = a + b;\n    *(int *)(p + 4) = c & 3;\n}\n")
    rd = dict(line=1, end=9)
    for line, want in [("s32 d = param_1;", True), ("ret = f();", False), ("u8 *p;", True), ("d = param_1;", False),
                       ("return x;", False), ("extern s32 D_1[];", True)]:
        if is_decl_line(line) != want:
            fail(f"is_decl_line({line!r}) != {want}")
    if top_level_ops("a & b") != [2] or top_level_ops("a && b") or top_level_ops("(s32 *)p") \
            or top_level_ops("*(s32 *)(p + 4) & 0xFF") != [16]:
        fail("top_level_ops: a binary commutative operator at depth 0, and nothing else")
    sw = commutative_swaps(RFIX, "src/x.c", "rfix", rd)
    if [s for s, _ in sw] != ["swap & @6", "swap + @7"]:
        fail(f"commutative_swaps found {[s for s, _ in sw]}")
    if "a = c & b;" not in sw[0][1] or "c = b + a;" not in sw[1][1]:
        fail("commutative_swaps must split at the assignment, never at `==`")
    if any("@8" in s for s, _ in sw):
        fail("commutative_swaps must not swap a CONSTANT operand (fold moves it right; byte-neutral, S101 micro-test)")
    R6FIX = ("void r6(int p)\n{\n    int v;\n    int w;\n    v = *(int *)(p + 4);\n"
             "    *(int *)(p + 4) = v & ~0x20;\n    w = 3;\n    *(int *)(p + 8) = w;\n}\n")
    inl = inline_single_set_temps(R6FIX, "src/x.c", "r6", dict(line=1, end=9))
    if [d for d, _ in inl] != ["inline v @5", "inline w @7"]:
        fail(f"inline_single_set_temps found {[d for d, _ in inl]}")
    if "= (*(int *)(p + 4)) & ~0x20;" not in inl[0][1] or "int v;" in inl[0][1]:
        fail("R6 must inline the expression at the use AND drop the now-dead declaration")
    bw = block_wraps(R6FIX, "src/x.c", "r6", dict(line=1, end=9))
    if [d for d, _ in bw][:2] != ["block @5", "do-while @5"] or "{ v = *(int *)(p + 4); }" not in bw[0][1]:
        fail(f"block_wraps: {[d for d, _ in bw][:3]} (the readable spelling first)")
    cands = recipe_candidates(RFIX, "src/x.c", "rfix", ["a", "b"])
    kinds_ = {r for r, _, _ in cands}
    if not {"R2", "R3", "R5"} <= kinds_ or any(c == RFIX for _, _, c in cands):
        fail(f"recipe_candidates: {kinds_} (the seed must never be a candidate)")
    if any("a = p;" in c.split("\n")[7] for _, _, c in cands if _ == "R3"):
        fail("R3 must place its assignment after the whole declaration run (C89)")
    # the address remap that propagates a reshape to a class (R48-adjacent: one crack, 134 banks)
    exb = "void func_80100000(void) { D_80200000 = func_80100004(); }"
    exa = "void func_80100000(void) { s32 t = func_80100004(); D_80200000 = t; }"
    sib = "void func_80300000(void) { D_80400000 = func_80300004(); }"
    got, why = remap_body(exb, exa, sib)
    if got != "void func_80300000(void) { s32 t = func_80300004(); D_80400000 = t; }":
        fail(f"remap_body produced {got!r} ({why})")
    if remap_body(exb, exa, "void func_80300000(void) { D_80400000 = 0; }")[0] is not None:
        fail("remap_body must refuse a sibling with a different token count")
    # R15, the sink (T7 agent a1's crack of func_80156044, 2026-09-10): the merge statement pushed into every arm and the
    # variables it consumed deleted. The three controls are the ones the applicability test exists for.
    SINKFIX = ("void func_80100000(int c) {\n"
               "    s32 base;\n"
               "    u8 *row;\n"
               "\n"
               "    if (c) {\n"
               "        base = 1;\n"
               "    } else if (c == 2) {\n"
               "        base = 2;\n"
               "    } else {\n"
               "        base = 3;\n"
               "    }\n"
               "    row = (u8 *)(base + 4);\n"
               "    use(row);\n"
               "}")
    d15 = next(r for r in sc.scan_text(SINKFIX, "src/fx/s.c", shared_defs=None)
               if r["form"] == "def" and r["name"] == "func_80100000")
    got15 = sink_merges(SINKFIX, "src/fx/s.c", "func_80100000", d15)
    if len(got15) != 1 or "sink" not in got15[0][0] or "base" not in got15[0][0]:
        fail(f"R15 must find one sink in the three-arm fixture, got {[g[0] for g in got15]}")
    else:
        c15 = got15[0][1]
        want15 = ["row = (u8 *)((1) + 4);", "row = (u8 *)((2) + 4);", "row = (u8 *)((3) + 4);"]
        if not all(w in c15 for w in want15):
            fail(f"R15 must sink the merge statement into every arm: {c15!r}")
        if "s32 base;" in c15 or "base = 1;" in c15:
            fail("R15 must delete the consumed variable's declaration and its per-arm assignments")
        if c15.count("row = ") != 3 or "row = (u8 *)(base + 4);" in c15:
            fail("R15 must remove the merge statement itself")
        if "u8 *row;" not in c15:
            fail("R15 must keep the declaration of the variable the merge statement ASSIGNS")
    # control 1: a consumed variable read anywhere else is not sinkable (its census would not add up)
    if sink_merges(SINKFIX.replace("    use(row);", "    use(row + base);"), "src/fx/s.c", "func_80100000",
                   next(r for r in sc.scan_text(SINKFIX.replace("    use(row);", "    use(row + base);"), "src/fx/s.c",
                                                shared_defs=None) if r["form"] == "def")):
        fail("R15 must refuse a variable that is read after the merge statement")
    # control 2: a variable not set in EVERY arm is not sinkable
    if sink_merges(SINKFIX.replace("        base = 2;\n", ""), "src/fx/s.c", "func_80100000",
                   next(r for r in sc.scan_text(SINKFIX.replace("        base = 2;\n", ""), "src/fx/s.c",
                                                shared_defs=None) if r["form"] == "def")):
        fail("R15 must refuse a variable one arm does not set")
    # control 3: the brace walk itself — a `} else if (…) {` line nets to zero braces and must still close its arm
    ch = if_chains([sc.mask_text(l) for l in SINKFIX.split("\n")], d15["line"], d15["end"] - 1)
    if len(ch) != 1 or len(ch[0][2]) != 3:
        fail(f"if_chains must see three arms in the fixture, got {ch}")

    # R16 / R17 (T7 agent a2's crack of func_80168828, 2026-09-10): a constant holder inlined, then the run it fed split.
    CFIX = ("void func_80100000(void) {\n"
            "    s32 c40;\n"
            "    s32 other;\n"
            "\n"
            "    c40 = 0x40;\n"
            "    other = 0x10;\n"
            "    st(0) = c40;\n"
            "    st(1) = c40;\n"
            "    st(2) = c40;\n"
            "    st(3) = other;\n"
            "}")
    dC = next(r for r in sc.scan_text(CFIX, "src/fx/c.c", shared_defs=None)
              if r["form"] == "def" and r["name"] == "func_80100000")
    h16 = constant_holders(CFIX, "src/fx/c.c", "func_80100000", dC)
    if len(h16) != 2 or not any(d.startswith("const-holder c40=0x40 x3") for d, _ in h16):
        fail(f"R16 must inline a 3-use constant holder, got {[d for d, _ in h16]}")
    else:
        c16 = next(c for d, c in h16 if d.startswith("const-holder c40"))
        if "s32 c40;" in c16 or "c40 = 0x40;" in c16 or c16.count("st(0) = 0x40;") != 1:
            fail(f"R16 must delete the declaration and the assignment and write the literal: {c16!r}")
    # control: a holder whose value is not a literal, and one written twice, are not constant holders
    if any(d.startswith("const-holder") for d, _ in
           constant_holders(CFIX.replace("c40 = 0x40;", "c40 = f();"), "src/fx/c.c", "func_80100000",
                            next(r for r in sc.scan_text(CFIX.replace("c40 = 0x40;", "c40 = f();"), "src/fx/c.c",
                                                         shared_defs=None) if r["form"] == "def"))
           if d.startswith("const-holder c40")):
        fail("R16 must refuse a holder whose single assignment is not an integer literal")
    # R17 on the inlined text: the 0x10 store moved into the run of three 0x40 stores, at each interior split point
    c16 = next(c for d, c in h16 if d.startswith("const-holder c40"))
    d17 = next(r for r in sc.scan_text(c16, "src/fx/c.c", shared_defs=None) if r["form"] == "def")
    r17 = [d for d, _ in constant_run_splits(c16, "src/fx/c.c", "func_80100000", d17) if "into the 0x40 run" in d]
    if len(r17) != 2:
        fail(f"R17 must offer both interior split points of a three-store run, got {r17}")
    # control: a run of one store has no split
    if constant_run_splits(CFIX.replace("    st(1) = c40;\n    st(2) = c40;\n", ""), "src/fx/c.c", "func_80100000",
                           next(r for r in sc.scan_text(CFIX.replace("    st(1) = c40;\n    st(2) = c40;\n", ""),
                                                        "src/fx/c.c", shared_defs=None) if r["form"] == "def")):
        fail("R17 must refuse a run shorter than two statements")

    # R18, the bystander move (T7 agent a3's proposal from func_801397B0, 2026-09-10 — the body it did NOT close)
    BFIX = ("void func_80100000(void) {\n"
            "    s32 a;\n"
            "    s32 b;\n"
            "\n"
            "    a = one();\n"
            "    b = two();\n"
            "\n"
            "    st(0) = 0;\n"
            "}")
    dB = next(r for r in sc.scan_text(BFIX, "src/fx/b.c", shared_defs=None) if r["form"] == "def")
    b18 = bystander_moves(BFIX, "src/fx/b.c", "func_80100000", dB)
    if not any(d == "bystander @8->5" for d, _ in b18):
        fail(f"R18 must offer the store moved above both assignments (across a blank line), got {[d for d, _ in b18]}")
    else:
        cB = next(c for d, c in b18 if d == "bystander @8->5")
        body = [l.strip() for l in cB.split("\n") if l.strip() and "{" not in l and "}" not in l]
        if body[2] != "st(0) = 0;" or body.count("st(0) = 0;") != 1:
            fail(f"R18 must move the statement, not copy it: {body}")
    # the true bystanders come FIRST. In this fixture `st(0) = 0;` crosses nothing it names, while `b = a + 1;` crossing
    # `a = one();` shares `a` — the disjoint move must be offered before the sharing one.
    SFIX = BFIX.replace("    b = two();", "    b = a + 1;")
    b18s = [d for d, _ in bystander_moves(SFIX, "src/fx/b.c", "func_80100000",
                                          next(r for r in sc.scan_text(SFIX, "src/fx/b.c", shared_defs=None)
                                               if r["form"] == "def"))]
    if "bystander @8->5" not in b18s or "bystander @6->5" not in b18s:
        fail(f"R18 fixture lost a move: {b18s}")
    elif b18s.index("bystander @8->5") > b18s.index("bystander @6->5"):
        fail(f"R18 must offer identifier-disjoint moves before sharing ones: {b18s}")
    # control: a blank line is transparent, a BRACE is not — nothing may move across a nested block
    NB = BFIX.replace("    st(0) = 0;", "    if (a) {\n        b = 3;\n    }\n    st(0) = 0;")
    if any(d.endswith("->5") for d, _ in
           bystander_moves(NB, "src/fx/b.c", "func_80100000",
                           next(r for r in sc.scan_text(NB, "src/fx/b.c", shared_defs=None) if r["form"] == "def"))
           if d.startswith("bystander @11")):
        fail("R18 must not move a statement across a nested block")

    # R14's bankability refusal (S102 run s4): the bank is body-only, so a width change that must also rewrite a prototype
    # outside the definition can never be banked — the generator refuses instead of spending compiles on it (R43).
    WFIX = "extern void f(s32 a);\nvoid f(s32 a) {\n    use(a);\n}\n"
    dW = next(r for r in sc.scan_text(WFIX, "src/fx/w.c", shared_defs=None) if r["form"] == "def" and r["name"] == "f")
    if param_widths(WFIX, "src/fx/w.c", "f", dW):
        fail("R14 must refuse a function the TU declares outside its definition (the bank is body-only)")
    W2 = "void f(s32 a) {\n    use(a);\n}\n"
    d2W = next(r for r in sc.scan_text(W2, "src/fx/w.c", shared_defs=None) if r["form"] == "def" and r["name"] == "f")
    if not param_widths(W2, "src/fx/w.c", "f", d2W):
        fail("R14 must still offer widths when the definition is the only declaration")

    # R19, the argument restore (P36 S102: six T7 agents reached score 0 by restoring a dropped call argument, and no
    # other family can, because every other family rewrites statements that exist while this changes a call's ARITY).
    AFIX = ("extern int callee_x(void);\n"
            "void func_80100000(s32 p) {\n"
            "    s32 a;\n"
            "    a = p + 1;\n"
            "    return callee_x() != 0;\n"
            "}")
    dA = next(r for r in sc.scan_text(AFIX, "src/fx/a.c", shared_defs=None)
              if r["form"] == "def" and r["name"] == "func_80100000")
    saved = globals().get("_ARG_DEFS")
    globals()["_ARG_DEFS"] = {"callee_x": (1, "s32 arg0", "src/fx/z.c", "void")}
    try:
        r19 = restore_arguments(AFIX, "src/fx/a.c", "func_80100000", dA)
        got = {d: c for d, c in r19}
        if len(r19) != 2:
            fail(f"R19 must offer one candidate per in-scope value (the parameter and the local), got {list(got)}")
        elif not any("((int (*)(s32 arg0))callee_x)(p)" in c for c in got.values()):
            fail(f"R19 must keep the TU's DECLARED return type and repair only the arity: {list(got.values())[:1]}")
        elif any("(*)(void)" in c or "((void (*)" in c for c in got.values()):
            fail("R19 must not take the return type from the definition (it produced an uncompilable void comparison once)")
        # a `return` statement is where these calls usually live: a simple_stmt gate found nothing on the real body
        if not any("@5" in d for d in got):
            fail(f"R19 must see a call inside a return statement, got {list(got)}")
        # control: when the declaration already matches the definition there is nothing to restore
        globals()["_ARG_DEFS"] = {"callee_x": (0, "void", "src/fx/z.c", "void")}
        if restore_arguments(AFIX, "src/fx/a.c", "func_80100000", dA):
            fail("R19 must refuse a call whose declaration already matches the definition")
    finally:
        globals()["_ARG_DEFS"] = saved

    # R20, chain narrowing (T7 agent b3's crack of func_8016CBC0, P36 S102 — it PROVED the joint form is necessary:
    # single declarations scored 45/72/51/24, each chain alone 43, both chains together 0).
    NFIX = ("void func_80100000(void) {\n"
            "    int c;\n"
            "    int w;\n"
            "    int other;\n"
            "\n"
            "    c = 15;\n"
            "    w = c - 1;\n"
            "    c = w;\n"
            "    other = f();\n"
            "}")
    dN = next(r for r in sc.scan_text(NFIX, "src/fx/n.c", shared_defs=None)
              if r["form"] == "def" and r["name"] == "func_80100000")
    n20 = narrow_chains(NFIX, "src/fx/n.c", "func_80100000", dN)
    descs = [d for d, _ in n20]
    if not any(d.startswith("chain-narrow c+w -> s16") for d in descs):
        fail(f"R20 must find the c/w copy chain and narrow it whole, got {descs}")
    elif any("other" in d for d in descs):
        fail(f"R20 must not pull in a local with no assignment link to the chain: {descs}")
    else:
        cN = next(c for d, c in n20 if d.startswith("chain-narrow c+w -> s16"))
        if "short c;" not in cN or "short w;" not in cN or "int other;" not in cN:
            fail(f"R20 must narrow every member of the chain and nothing else: {cN!r}")
    # control: a body with no linked pair offers nothing (a single declaration is R12's move, not this one)
    if narrow_chains(NFIX.replace("    c = w;\n", ""), "src/fx/n.c", "func_80100000",
                     next(r for r in sc.scan_text(NFIX.replace("    c = w;\n", ""), "src/fx/n.c", shared_defs=None)
                          if r["form"] == "def")):
        pass                                               # one link (w = c - 1) still makes a chain: that is correct
    if narrow_chains("void func_80100000(void) {\n    int a;\n    a = f();\n}", "src/fx/n.c", "func_80100000",
                     next(r for r in sc.scan_text("void func_80100000(void) {\n    int a;\n    a = f();\n}",
                                                  "src/fx/n.c", shared_defs=None) if r["form"] == "def")):
        fail("R20 must offer nothing when no two locals are linked by an assignment")

    # R21, the second consumer (T7 agents b2 and b6, P36 S102 — the same idea in two spellings, 127 bodies each).
    SFIX = ("void func_80100000(u8 *base) {\n"
            "    u8 *p;\n"
            "\n"
            "    p = base + 0x10;\n"
            "    D_80000000[0] = p;\n"
            "    p = base + 0x20;\n"
            "    D_80000000[1] = p;\n"
            "}")
    dS = next(r for r in sc.scan_text(SFIX, "src/fx/s2.c", shared_defs=None)
              if r["form"] == "def" and r["name"] == "func_80100000")
    s21 = second_consumer(SFIX, "src/fx/s2.c", "func_80100000", dS)
    ds = [d for d, _ in s21]
    if not any(d.startswith("chain p=D_80000000[0]") for d in ds) or not any("ALL 2 sites" in d for d in ds):
        fail(f"R21 must offer each site and the joint form, got {ds}")
    else:
        one = next(c for d, c in s21 if d.startswith("chain p=D_80000000[0]"))
        allc = next(c for d, c in s21 if d == "chain ALL 2 sites")
        if "p = D_80000000[0] = base + 0x10;" not in one or one.count("D_80000000[0]") != 1:
            fail(f"R21's chain must fold the two statements into one: {one!r}")
        if allc.count(" = base + 0x") != 2 or "D_80000000[1] = p;" in allc:
            fail(f"R21's joint form must rewrite every site: {allc!r}")
        hoist = next(c for d, c in s21 if d.startswith("consumer-first"))
        if "D_80000000[0] = base + 0x10;" not in hoist or "p = base + 0x10;" not in hoist:
            fail(f"R21's hoist must put the store first and repeat the expression: {hoist!r}")
    # control: a pair that does not feed a store offers nothing
    NO = "void func_80100000(void) {\n    int a;\n    a = f();\n    g(a);\n}"
    if second_consumer(NO, "src/fx/s2.c", "func_80100000",
                       next(r for r in sc.scan_text(NO, "src/fx/s2.c", shared_defs=None) if r["form"] == "def")):
        fail("R21 must offer nothing when the next statement is not an assignment OF the value")

    # the oracle's crash classification on its real message forms (R103)
    if not oracle.SIGNAL_LINE.search("bash: line 1: 3845091 Done   mipsel-linux-gnu-cpp ...\n     3845092 Aborted                 (core dumped) | tools/bin/gcc-2.7.2-psx/cc1 -quiet\n"):
        fail("SIGNAL_LINE must match bash's job-status block")
    if oracle.SIGNAL_LINE.search("src/x.c:3770: parse error before `}'\n"):
        fail("SIGNAL_LINE must not match a diagnostic")
    for f in d.glob("*"):
        f.unlink()
    d.rmdir()
    print(f"delever --selftest: {'OK' if ok else 'FAIL'} — {len(b['sites'])} sites in the exemplar, {len(refused)} refused rewrite(s), "
          f"ladder {res['verdict']} ({res['compiles']} compiles), replay {res2['rung']} ({res2['compiles']} compile), markers {sum(1 for l in fl if FAKE in l)}")
    return ok


# ----------------------------------------------------------------------------------------------------------------------
# T2's probe (unchanged in substance; the corrected rewrites apply)
# ----------------------------------------------------------------------------------------------------------------------
def features(b):
    ks = collections.Counter(s["kind"] for s in b["sites"])
    n = len(b["sites"])
    mix = "pins-only" if set(ks) <= {"pin"} else "asm-only" if not (set(ks) & {"pin", "cast", "decl-body", "register"}) else "mixed"
    return dict(kind=kind_of(b["tu"]), n=n, bucket=("1" if n == 1 else "2-4" if n <= 4 else "5-9" if n <= 9 else "10+"), mix=mix,
                zero=any(s.get("zero") for s in b["sites"]), init=any(s.get("init") for s in b["sites"] if s["kind"] == "pin"),
                instr=any(s["kind"] == "instruction" for s in b["sites"]), cast=any(s["kind"] == "cast" for s in b["sites"]),
                register=any(s["kind"] == "register" for s in b["sites"]), volatile=any(s["cls"] == "C" for s in b["sites"]),
                launder=any(s["kind"] == "launder" for s in b["sites"]), barrier=any(s["kind"] == "barrier" for s in b["sites"]),
                keepalive=any(s["kind"] == "keepalive" for s in b["sites"]))


def stratified_sample(bodies, n, seed):
    rnd = random.Random(seed)
    by_class = {}
    for key, b in bodies.items():
        if not b["sites"] or b["fn"] == FILE_SCOPE_FN:
            continue
        h = b["nhash"] or key
        cur = by_class.get(h)
        pref = {"main": 0, "resident": 1, "md": 2, "shared": 3, "ov": 4}[kind_of(b["tu"])]
        if cur is None or pref < cur[0]:
            by_class[h] = (pref, key)
    pool = [bodies[k] for _, k in by_class.values()]
    rnd.shuffle(pool)
    base = {"main": 20, "resident": 16, "md": 15, "shared": 20, "ov": 79}
    scale = n / sum(base.values())
    quota = {k: max(3, int(round(v * scale))) for k, v in base.items()}
    picked, seen = [], set()
    for kind, q in quota.items():
        cands = [b for b in pool if kind_of(b["tu"]) == kind]
        groups = collections.defaultdict(list)
        for b in cands:
            f = features(b)
            groups[(f["bucket"], f["mix"])].append(b)
        keys = sorted(groups)
        i = 0
        while len([b for b in picked if kind_of(b["tu"]) == kind]) < q and any(groups[k] for k in keys):
            k = keys[i % len(keys)]
            i += 1
            if groups[k]:
                b = groups[k].pop()
                if (b["tu"], b["fn"]) not in seen:
                    picked.append(b)
                    seen.add((b["tu"], b["fn"]))
    for flag, want in (("zero", 10), ("init", 10), ("instr", 12), ("cast", 8), ("register", 5), ("launder", 8), ("keepalive", 6)):
        have = sum(1 for b in picked if features(b)[flag])
        for b in pool:
            if have >= want:
                break
            if (b["tu"], b["fn"]) not in seen and features(b)[flag]:
                picked.append(b)
                seen.add((b["tu"], b["fn"]))
                have += 1
    return picked


def probe(sample_n, seed, jobs):
    PROBE.mkdir(parents=True, exist_ok=True)
    ok, why = oracle.calibration_current()
    if not ok:
        sys.exit(f"delever: the oracle's calibration is not current ({why}) — run tools/delever_oracle.py --calibrate first (R56)")
    ensure_census(jobs)
    recipes = oracle.load_recipes()["recipes"]
    by_src = oracle.recipes_by_src(recipes)
    sites = load_sites()
    bodies = bodies_from_sites(sites)
    inc = includers()
    sample = stratified_sample(bodies, sample_n, seed)
    log_f = open(PROBE / "probe_log.txt", "a")
    def log(msg):
        line = f"{time.strftime('%H:%M:%S')} {msg}"
        print(line, flush=True)
        log_f.write(line + "\n")
        log_f.flush()
    log(f"probe: {len(sample)} bodies sampled from {len(bodies)} lever bodies ({len({b['nhash'] for b in bodies.values() if b['sites']})} distinct classes); seed {seed}")
    by_file = collections.defaultdict(list)
    for b in sample:
        by_file[b["tu"]].append(b)
    def work(tu):
        out = []
        if tu.endswith(".h"):
            recs = [r for t in inc.get(tu, []) for r in by_src.get(t, [])][:1]
        else:
            recs = by_src.get(tu, [])[:1]
        if not recs:
            return [dict(tu=tu, fn=b["fn"], verdict="NO-RECIPE") for b in by_file[tu]]
        path = REPO / tu
        st = path.stat()
        raw = path.read_text(errors="surrogateescape")
        m = same_len_mask(raw)
        ls = line_starts(raw)
        def judge(text, removed, tag):
            try:
                return oracle.judge_all(recs, text, tag=tag, write_path=(tu if tu.endswith(".h") else None))
            finally:
                restore_file(path, raw, st)
        for b in by_file[tu]:
            res = ladder(b, raw, m, ls, judge, log=log)
            out.append(dict(tu=tu, fn=b["fn"], nhash=b["nhash"], kind=kind_of(tu), aliases=b["aliases"], header=b["header"], obj=recs[0]["obj"],
                            n_sites=len(b["sites"]), n_usable=len(b["sites"]) - res["refused"], verdict=res["verdict"], rung=res.get("rung"),
                            rung_A=("IDENTICAL" if res.get("rung") == "A" else "DIFFERS" if res.get("rung") == "B" else res["verdict"]),
                            removed=[x for x in res["sites"] if x["verdict"] in ("REMOVED", "REWRITTEN")],
                            needed=[dict(x, verdict=x["oracle"]) for x in res["sites"] if x["verdict"] == "NEEDED"],
                            refused=[x for x in res["sites"] if x["verdict"] == "REFUSED"], compiles=res["compiles"], seconds=res["seconds"],
                            features=features(b)))
        return out
    results = []
    t0 = time.time()
    tu_files = sorted(f for f in by_file if not f.endswith(".h"))
    hdr_files = sorted(f for f in by_file if f.endswith(".h"))
    with ThreadPoolExecutor(max_workers=jobs) as ex:
        for r in ex.map(work, tu_files):
            results.extend(r)
    for f in hdr_files:
        results.extend(work(f))
    wall = time.time() - t0
    with open(PROBE / "probe_results.jsonl", "w") as f:
        for r in results:
            f.write(json.dumps(r) + "\n")
    summary = summarize(results, bodies, wall, seed)
    (PROBE / "probe_summary.json").write_text(json.dumps(summary, indent=1) + "\n")
    (PROBE / "probe_table.md").write_text(render(summary) + "\n")
    print(render(summary))
    return summary


def summarize(results, bodies, wall, seed):
    judged = [r for r in results if r.get("verdict") in ("LEVER-FREE", "RESIDUE")]
    def pct(a, b):
        return round(100.0 * a / b, 1) if b else None
    by_kind = {}
    for k in ("main", "resident", "md", "shared", "ov"):
        rs = [r for r in judged if r["kind"] == k]
        if not rs:
            continue
        by_kind[k] = dict(bodies=len(rs), A_identical=sum(1 for r in rs if r["rung_A"] == "IDENTICAL"),
                          lever_free=sum(1 for r in rs if r["verdict"] == "LEVER-FREE"),
                          sites=sum(r["n_usable"] for r in rs), removed=sum(len(r["removed"]) for r in rs), needed=sum(len(r["needed"]) for r in rs),
                          compiles=sum(r["compiles"] for r in rs), mean_s_per_compile=round(sum(r["seconds"] for r in rs) / max(sum(r["compiles"] for r in rs), 1), 3))
    needed_kinds = collections.Counter(n["kind"] for r in judged for n in r["needed"])
    needed_detail = collections.Counter(f"{n['kind']}:{n['detail']}" for r in judged for n in r["needed"])
    needed_oracle = collections.Counter(n["verdict"] for r in judged for n in r["needed"])
    removed_kinds = collections.Counter(x["kind"] + ("/rewritten" if x["verdict"] == "REWRITTEN" else "") for r in judged for x in r["removed"])
    refused = collections.Counter(x["why"].split(":")[0][:60] for r in results for x in r.get("refused", []))
    sites_total = sum(r["n_usable"] for r in judged)
    sites_needed = sum(len(r["needed"]) for r in judged)
    flags = {}
    for flag in ("zero", "init", "instr", "cast", "register", "launder", "barrier", "keepalive", "volatile"):
        rs = [r for r in judged if r["features"].get(flag)]
        flags[flag] = dict(bodies=len(rs), lever_free=sum(1 for r in rs if r["verdict"] == "LEVER-FREE"))
    pop_bodies = sum(1 for b in bodies.values() if b["sites"])
    pop_sites = sum(len(b["sites"]) for b in bodies.values())
    mean_compiles = sum(r["compiles"] for r in judged) / max(len(judged), 1)
    mean_s = sum(r["seconds"] for r in judged) / max(sum(r["compiles"] for r in judged), 1)
    return dict(generated=time.strftime("%Y-%m-%d %H:%M"), seed=seed, sampled=len(results), judged=len(judged),
                not_judged=collections.Counter(r.get("verdict") for r in results if r not in judged),
                rung_A_identical=sum(1 for r in judged if r["rung_A"] == "IDENTICAL"),
                lever_free_after_B=sum(1 for r in judged if r["verdict"] == "LEVER-FREE"),
                sites=dict(total=sites_total, removed=sites_total - sites_needed, needed=sites_needed, pct_removed=pct(sites_total - sites_needed, sites_total)),
                needed_by_kind=dict(needed_kinds), needed_by_detail=dict(needed_detail.most_common(30)), needed_by_oracle=dict(needed_oracle),
                removed_by_kind=dict(removed_kinds), refused=dict(refused), by_kind=by_kind, flags=flags,
                compiles=sum(r["compiles"] for r in judged), mean_compiles_per_body=round(mean_compiles, 2), mean_s_per_compile=round(mean_s, 3),
                wall_s=round(wall, 1), population=dict(bodies=pop_bodies, sites=pop_sites),
                pricing=dict(T4_compiles_est=int(pop_bodies * mean_compiles), T4_cpu_hours_est=round(pop_bodies * mean_compiles * mean_s / 3600, 2),
                             T4_wall_hours_at_12_est=round(pop_bodies * mean_compiles * mean_s / 3600 / 12, 2),
                             residue_bodies_est=int(pop_bodies * (1 - (sum(1 for r in judged if r["verdict"] == "LEVER-FREE") / max(len(judged), 1)))),
                             residue_sites_est=int(pop_sites * (sites_needed / max(sites_total, 1)))))


def render(s):
    L = [f"# probe — {s['sampled']} bodies sampled, {s['judged']} judged (seed {s['seed']}, {s['generated']}, wall {s['wall_s']} s)", "",
         f"- rung A (strip-all) identical: **{s['rung_A_identical']} / {s['judged']}**",
         f"- lever-free after rung B: **{s['lever_free_after_B']} / {s['judged']}**",
         f"- sites: {s['sites']['total']} usable · removed {s['sites']['removed']} ({s['sites']['pct_removed']} %) · needed {s['sites']['needed']}",
         f"- needed by kind: {s['needed_by_kind']}", f"- needed by the oracle's word: {s['needed_by_oracle']}", f"- needed by detail (top): {s['needed_by_detail']}",
         f"- removed by kind: {s['removed_by_kind']}", f"- refused (rewrite not applicable): {s['refused']}",
         f"- compiles {s['compiles']} · mean {s['mean_compiles_per_body']} per body · {s['mean_s_per_compile']} s per compile", "",
         "| kind | bodies | A identical | lever-free after B | sites | removed | needed | compiles | s/compile |", "|---|---:|---:|---:|---:|---:|---:|---:|---:|"]
    for k, v in s["by_kind"].items():
        L.append(f"| {k} | {v['bodies']} | {v['A_identical']} | {v['lever_free']} | {v['sites']} | {v['removed']} | {v['needed']} | {v['compiles']} | {v['mean_s_per_compile']} |")
    L += ["", "| feature | bodies | lever-free |", "|---|---:|---:|"]
    for k, v in s["flags"].items():
        L.append(f"| {k} | {v['bodies']} | {v['lever_free']} |")
    p = s["pricing"]
    L += ["", f"**Pricing (R41; population {s['population']['bodies']:,} lever bodies / {s['population']['sites']:,} removable sites):** "
          f"T4 ≈ {p['T4_compiles_est']:,} compiles ≈ {p['T4_cpu_hours_est']} CPU-h ≈ {p['T4_wall_hours_at_12_est']} h wall at 12 workers; "
          f"residue after the mechanical ladder ≈ {p['residue_bodies_est']:,} bodies / {p['residue_sites_est']:,} sites (the sample's rates applied to the population)."]
    return "\n".join(L)


def main():
    ap = argparse.ArgumentParser(description=__doc__.split("\n")[0])
    ap.add_argument("--probe", action="store_true")
    ap.add_argument("--sample", type=int, default=150)
    ap.add_argument("--seed", type=int, default=1)
    ap.add_argument("--plan", action="store_true", help="list the next batch (no writes)")
    ap.add_argument("--apply", action="store_true", help="judge the next batch and keep the winning texts in place")
    ap.add_argument("--batch", type=int, default=300, help="files per batch")
    ap.add_argument("--headers", action="store_true", help="draw shared headers instead of translation units (serial; includers in parallel)")
    ap.add_argument("--only", nargs="*", default=None, help="restrict to these aliases / TU paths / function names / nhash prefixes")
    ap.add_argument("--rejudge", action="store_true", help="draw bodies the ledger already marks done")
    ap.add_argument("--redraw", nargs="*", default=None, help="also draw bodies whose latest ledger verdict is one of these (e.g. REFUSED NOTHING-USABLE)")
    ap.add_argument("--label", default=None, help="the batch label (ledger rows, apply_<label>.log, batch_<label>.json)")
    ap.add_argument("--restore", action="store_true", help="restore every in-flight file from inflight.json")
    ap.add_argument("--status", action="store_true")
    ap.add_argument("--scrub", action="store_true", help="remove orphan !FAKE markers (a marker whose site is gone), byte-judged per file")
    ap.add_argument("--propagate", nargs=2, metavar=("TU", "FN"),
                    help="give every RESIDUE sibling of this banked body's class the same shape, with its own addresses")
    ap.add_argument("--recipes", action="store_true",
                    help="rung R: the cookbook's byte-neutral shape recipes tried mechanically on every RESIDUE body")
    ap.add_argument("--cap", type=int, default=60, help="--recipes: candidates tried per body (each is one compile)")
    ap.add_argument("--control", type=int, default=8, help="--recipes: how many LEVER-FREE bodies the control run reproduces (R39)")
    ap.add_argument("--limit", type=int, help="--recipes: stop after this many RESIDUE bodies")
    ap.add_argument("--apply-body", nargs=3, metavar=("TU", "FN", "FILE"))
    ap.add_argument("--rung", default="E")
    ap.add_argument("--allow-residue", action="store_true")
    ap.add_argument("--dirty-ok", action="store_true", help="--apply-body on a dirty tree (a wave banking several bodies before one commit)")
    ap.add_argument("--selftest", action="store_true")
    ap.add_argument("--repair-nhash", action="store_true", help="fill the missing text hash of RESIDUE rows from each body's earlier rows")
    ap.add_argument("-j", "--jobs", type=int, default=12)
    a = ap.parse_args()
    if a.selftest:
        sys.exit(0 if selftest() else 1)
    if a.repair_nhash:
        sys.exit(repair_nhash())
    if a.probe:
        probe(a.sample, a.seed, a.jobs)
        return
    if a.restore:
        sys.exit(restore())
    if a.status:
        sys.exit(status())
    if a.scrub:
        sys.exit(scrub(a))
    if a.propagate:
        if not a.label:
            sys.exit("delever --propagate: --label is required (R48)")
        sys.exit(0 if propagate(a)[0] else 1)
    if a.recipes:
        if not a.label:
            sys.exit("delever --recipes: --label is required (R48: the ledger rows are keyed by it)")
        sys.exit(recipes(a))
    if a.apply_body:
        if not a.label:
            sys.exit("delever --apply-body: --label is required")
        sys.exit(apply_body(a))
    if a.plan:
        ensure_census(a.jobs)
        sites = load_sites()
        bodies = bodies_from_sites(sites, with_file_scope=True)
        plan, total, _ = make_plan(bodies, load_ledger(), a.headers, a.batch, a.only, a.rejudge, set(a.redraw or ()))
        print(describe_plan(plan, total, bodies))
        for tu, bs in plan[:40]:
            print(f"  {tu}: {len(bs)} bodies, {sum(len(b['sites']) for b in bs)} sites" + (f", {sum(len(b['deferred']) for b in bs)} deferred" if any(b['deferred'] for b in bs) else ""))
        if len(plan) > 40:
            print(f"  … {len(plan) - 40} more files")
        return
    if a.apply:
        if not a.label:
            sys.exit("delever --apply: --label is required (R48: the ledger rows, the log and the batch record are keyed by it)")
        sys.exit(apply_batch(a))
    ap.print_help()


if __name__ == "__main__":
    main()
