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
        tmp = INCLUDERS_CACHE.with_suffix(".tmp")
        tmp.write_text(json.dumps(new_cache))
        os.replace(tmp, INCLUDERS_CACHE)
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


def restore():
    """Every in-flight file back from inflight.json, and the killed batch's ledger rows dropped (a batch that did not complete leaves no
    trace: its bodies are drawn again — a body judged all-NEEDED in the killed batch would otherwise count as done while its markers were
    restored away). The dropped rows are kept in ledger.jsonl.killed_<label> (ignored scratch)."""
    if not INFLIGHT.exists():
        sys.exit("delever --restore: no inflight.json — nothing in flight")
    d = json.loads(INFLIGHT.read_text())
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


def decl_run_end(text, d):
    """the 0-based index of the LAST line of the declaration run that opens fn's body — a C89 declaration may not follow a
    statement, so an initializer split must put its assignment after the WHOLE run, not after the last pinned declaration."""
    lines = text.split("\n")
    last = d["line"] - 1
    for i in range(d["line"], d["end"] - 1):
        s = sc.mask_text(lines[i]).strip()
        if not s or s.startswith("/*") or s.startswith("//") or s in ("{", "}"):
            continue
        if is_decl_line(sc.mask_text(lines[i])):
            last = i
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
        if len(asgs) != 1 or len(uses) != 1 or len(decls) > 1:
            continue
        ai = asgs[0][0]
        ui, u0, u1 = uses[0]
        if ai >= ui:
            continue
        mm = re.match(ASG % re.escape(v), masked[ai].strip())
        raw_stripped = lines[ai].strip()
        expr = raw_stripped[mm.start(1):mm.end(1)]
        if not expr.strip():
            continue
        cand = list(lines)
        cand[ui] = lines[ui][:u0] + f"({expr})" + lines[ui][u1:]
        cand[ai] = None                                   # the assignment goes (with its declaration when they are one)
        if decls:                                         # form B: the separate `T v;` is dead now
            cand[decls[0][0]] = None
        out.append((f"inline {v} @{ai + 1}", "\n".join(l for l in cand if l is not None)))
    return out


def recipe_candidates(text, tu, fn, names, limit=24, rng=None, cap=40):
    """[(recipe, description, candidate text)] — the byte-neutral shape recipes of the cookbook, mechanically.
    R2 (§76/§501-R, the allocation ORDER is the bank): the formerly-pinned declarations permuted among their own lines.
    R4: one of them moved through the whole declaration run. R3 (§17a/§501-P): an initializer split off its declaration.
    R5 (§137/§501-R, the caller-saved class): the operand order of one commutative operator — the ONLY recipe here that
    needs no pinned declaration, so a residue of barriers and launders still has candidates."""
    recs_ = sc.scan_text(text, tu, shared_defs=None)
    d_ = next((r for r in recs_ if r["form"] == "def" and r["name"] == fn), None)
    if d_ is None:
        return []
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
    for p in perms[:limit]:
        ls_ = list(lines)
        for slot, src in zip(idx, p):
            ls_[slot] = body[src]
        out.append(("R2", "decl-order " + ",".join(str(x) for x in p), "\n".join(ls_)))
    # R4 (§76/§501-R again, one variable at a time): a formerly-pinned declaration moved to every other slot of the body's
    # declaration run — the allocno creation order the pin used to override. R2 permutes the pinned declarations among
    # THEIR OWN slots; this reaches the orders that involve the untouched declarations too, at one compile each.
    last = decl_run_end(text, d_)
    run_idx = [i for i in range(d_["line"], last + 1) if is_decl_line(sc.mask_text(lines[i]))]
    if dls and len(run_idx) > 1:
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
    for k, (i, t) in enumerate(dls or []):
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
    for desc, cand in commutative_swaps(text, tu, fn, d_):
        out.append(("R5", desc, cand))
    for desc, cand in inline_single_set_temps(text, tu, fn, d_):
        out.append(("R6", desc, cand))
    seen, uniq = {text}, []                               # never judge the seed twice, nor one candidate twice (R37)
    for rec, desc, cand in out:
        if cand in seen:
            continue
        seen.add(cand)
        uniq.append((rec, desc, cand))
    return uniq[:cap]


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

    def judge(tu, cand):
        path = REPO / tu
        raw, st = path.read_text(errors="surrogateescape"), path.stat()
        try:
            return oracle.judge_all(recs_for(tu), cand, tag="rec", write_path=(tu if tu.endswith(".h") else None))
        finally:
            restore_file(path, raw, st)

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
    print(f"delever --recipes: {len(todo)} RESIDUE bodies", flush=True)
    rows, won, tried, compiles = [], 0, 0, 0
    t0 = time.time()
    for (tu, fn), r in todo:
        path = REPO / tu
        raw = path.read_text(errors="surrogateescape")
        names = pin_names(sites_by[(tu, fn)])          # may be empty: R5 needs no pinned declaration
        try:
            free = lever_free(tu, raw, fn)
        except Refuse:
            continue
        cands = recipe_candidates(free, tu, fn, names)
        if not cands:
            continue
        tried += 1
        hit = None
        for rec, desc, cand in cands:
            v, dt, err = judge(tu, cand)
            compiles += len(recs_for(tu))
            if v == "IDENTICAL":
                hit = (rec, desc, cand)
                break
        row = dict(ts=time.strftime("%Y-%m-%d %H:%M:%S"), label=a.label, rung="R", calib=dict(head=oracle.head(), stamp=oracle.config_stamp()),
                   tu=tu, fn=fn, addr=fn_addr(fn, tu), aliases=r.get("aliases"), header=tu.endswith(".h"),
                   nhash_before=r.get("nhash_after"), nhash_after=None, candidates=len(cands), pins=len(names),
                   verdict=("LEVER-FREE" if hit else "RESIDUE"), recipe=(hit[0] if hit else None), how=(hit[1] if hit else None),
                   sites=([] if hit else r.get("sites", [])))
        if hit:
            path.write_text(hit[2], errors="surrogateescape")
            # the body's own markers are now orphans (its levers are gone); every OTHER body's marker is still honest, so the
            # scrub is scoped to this body's line span — a file-wide scrub would leave the census with UNMARKED sites elsewhere
            recs_ = sc.scan_text(hit[2], tu, shared_defs=None)
            d_ = next((x for x in recs_ if x["form"] == "def" and x["name"] == fn), None)
            span = range(d_["line"], d_["end"] + 1) if d_ else range(0)
            scrub = scrub_edits(hit[2], [i + 1 for i, l in enumerate(hit[2].split("\n")) if FAKE in l and i + 1 in span])
            if scrub:
                cand2 = apply_edits(hit[2], scrub)
                v2, _, _ = judge(tu, cand2)
                if v2 == "IDENTICAL":
                    path.write_text(cand2, errors="surrogateescape")
            walk = lc.walk_file(path.read_text(errors="surrogateescape"), tu, tu.endswith(".h"))
            row["nhash_after"] = next((x["nhash"] for x in walk["defs"] if x["name"] == fn), None)
            won += 1
            print(f"  {tu}:{fn} — {hit[0]} {hit[1]} IDENTICAL ({len(names)} pin(s) gone)", flush=True)
        rows.append(row)
    ledger_append(rows)
    needed = sum(len([s for s in r.get("sites", []) if s.get("verdict") == "NEEDED"]) for _, r in todo)
    print(f"recipes: {won} of {tried} bodies closed lever-free ({needed} NEEDED sites in the {len(todo)} drawn), "
          f"{compiles} compiles in {(time.time() - t0) / 60:.1f} min")
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
    src_row = next((r for r in reversed(rows) if r.get("tu") == tu and r.get("fn") == fn
                    and r.get("verdict") == "LEVER-FREE" and r.get("after_text")), None)
    if src_row is None:
        sys.exit(f"delever --propagate: no banked reshape of {tu}:{fn} in the ledger (its row must carry after_text)")
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
    print(f"delever --propagate: {tu}:{fn} -> {len(sibs)} sibling(s) of class {key[:12]}", flush=True)
    if not sibs:
        return 1                                          # R68: an empty work list is a refusal, not a success
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
        f = RUN / "propagate" / f"{stu.replace('/', '_')}__{sfn}.c"
        f.parent.mkdir(parents=True, exist_ok=True)
        f.write_text(body, errors="surrogateescape")
        r = subprocess.run([sys.executable, str(REPO / "tools/delever.py"), "--apply-body", stu, sfn, str(f),
                            "--label", a.label, "--rung", src_row.get("rung") or "R", "--dirty-ok"],
                           cwd=REPO, capture_output=True, text=True)
        line = ((r.stdout or r.stderr).strip().splitlines() or [""])[-1]
        print(f"  {line[:200]}", flush=True)
        ok += r.returncode == 0
        bad += r.returncode != 0
    print(f"delever --propagate: {ok} of {len(sibs)} sibling(s) banked, {bad} refused")
    return 0 if ok else 1


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
    new = pathlib.Path(src).read_text(errors="surrogateescape").rstrip("\n") + "\n"
    raw = path.read_text(errors="surrogateescape")
    st = path.stat()
    recs = lc.sc.scan_text(raw, tu, shared_defs=None)
    d = next((r for r in recs if r["form"] == "def" and r["name"] == fn), None)
    if d is None:
        sys.exit(f"delever --apply-body: {fn} is not defined in {tu}")
    ls = line_starts(raw)
    before = raw[ls[d["line"] - 1]:ls[d["end"]]]
    cand = raw[:ls[d["line"] - 1]] + new + raw[ls[d["end"]]:]
    if cand == raw:
        sys.exit("delever --apply-body: the new body equals the current text (no-op, R37)")
    walk = lc.walk_file(cand, tu, tu.endswith(".h"))
    levers = [s for s in walk["sites"] if s.get("fn") == fn and s["cls"] in "AB" and s["kind"] not in lc.NON_LEVER_KINDS]
    if levers and not a.allow_residue:
        sys.exit(f"delever --apply-body: the new body still carries {len(levers)} class A/B lever site(s) "
                 f"({[(s['kind'], s['detail'], s['line']) for s in levers][:6]}) — no lever of any class may remain (--allow-residue to override)")
    recipes = oracle.load_recipes()["recipes"]
    by_src = oracle.recipes_by_src(recipes)
    inc = includers()
    recs_ = [r for t in inc.get(tu, []) for r in by_src.get(t, [])] if tu.endswith(".h") else by_src.get(tu, [])
    if not recs_:
        sys.exit(f"delever --apply-body: no recipe compiles {tu}")
    try:
        v, dt, err = oracle.judge_all(recs_, cand, tag="body", write_path=(tu if tu.endswith(".h") else None))
    finally:
        restore_file(path, raw, st)
    nh_before = lc.norm_hash(sc.mask_text(before))
    nh_after = next((x["nhash"] for x in walk["defs"] if x["name"] == fn), None)
    row = dict(ts=time.strftime("%Y-%m-%d %H:%M:%S"), label=a.label, rung=a.rung, calib=dict(head=oracle.head(), stamp=oracle.config_stamp()),
               tu=tu, fn=fn, addr=fn_addr(fn, tu), aliases=None, header=tu.endswith(".h"), includers=len(inc.get(tu, [])),
               nhash_before=nh_before, nhash_after=nh_after, source=src, verdict=("LEVER-FREE" if v == "IDENTICAL" else f"BODY-{v}"),
               sites=[dict(ord=i, kind=s["kind"], cls=s["cls"], detail=s["detail"], via=s.get("via", ""), line=s["line"], verdict="NEEDED",
                           why="left by the author", oracle="") for i, s in enumerate(levers)],
               compiles=len(recs_), seconds=round(dt, 3), objects=[r["obj"] for r in recs_],
               # the body AS IT WAS: --propagate needs it to map this class's addresses onto a sibling's, and after the
               # write it exists nowhere else (the tree has moved on and the ledger is the record)
               before_text=before, after_text=new)
    if v == "IDENTICAL":
        path.write_text(cand, errors="surrogateescape")
        ledger_append([row])
        print(f"delever --apply-body: {tu}:{fn} IDENTICAL on {len(recs_)} object(s) ({dt:.2f} s) — KEPT, ledgered (rung {a.rung}, {a.label})")
        return 0
    ledger_append([row])
    print(f"delever --apply-body: {tu}:{fn} {v} on {len(recs_)} object(s) — NOT kept ({err[:200]})")
    return 1


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
            "    if (a == b) a = b & 3;\n    c = a + 1;\n    *(int *)(p + 4) = c;\n}\n")
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
    if "a = 3 & b;" not in sw[0][1] or "c = 1 + a;" not in sw[1][1]:
        fail("commutative_swaps must split at the assignment, never at `==`")
    R6FIX = ("void r6(int p)\n{\n    int v;\n    int w;\n    v = *(int *)(p + 4);\n"
             "    *(int *)(p + 4) = v & ~0x20;\n    w = 3;\n    *(int *)(p + 8) = w;\n}\n")
    inl = inline_single_set_temps(R6FIX, "src/x.c", "r6", dict(line=1, end=9))
    if [d for d, _ in inl] != ["inline v @5", "inline w @7"]:
        fail(f"inline_single_set_temps found {[d for d, _ in inl]}")
    if "= (*(int *)(p + 4)) & ~0x20;" not in inl[0][1] or "int v;" in inl[0][1]:
        fail("R6 must inline the expression at the use AND drop the now-dead declaration")
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
    ap.add_argument("--control", type=int, default=8, help="--recipes: how many LEVER-FREE bodies the control run reproduces (R39)")
    ap.add_argument("--limit", type=int, help="--recipes: stop after this many RESIDUE bodies")
    ap.add_argument("--apply-body", nargs=3, metavar=("TU", "FN", "FILE"))
    ap.add_argument("--rung", default="E")
    ap.add_argument("--allow-residue", action="store_true")
    ap.add_argument("--dirty-ok", action="store_true", help="--apply-body on a dirty tree (a wave banking several bodies before one commit)")
    ap.add_argument("--selftest", action="store_true")
    ap.add_argument("-j", "--jobs", type=int, default=12)
    a = ap.parse_args()
    if a.selftest:
        sys.exit(0 if selftest() else 1)
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
        sys.exit(propagate(a))
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
