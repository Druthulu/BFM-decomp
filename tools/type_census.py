#!/usr/bin/env python3
"""tools/type_census.py — the type census + the struct map (Phase 37 T1, 2026-09-12).

WHAT IT MEASURES (every number the structs phase publishes comes from here — R32/R37/R75)
=====================================================================================
  1. DEFINITIONS   every struct/union/typedef definition in src/ (the canonical header, every .c at file and block scope,
                   the per-function shared headers) with its o32 LAYOUT (offset/width/sign leaves, size, align), its exact-text
                   hash and its layout hash; duplicate classes (same layout, different names), VARIANT camps (same name,
                   different layout — cookbook §64a: two types, never merged), dead names, shadowing.
  2. CAST SITES    every raw pointer-cast dereference in FIVE forms, each with the base expression classified (parameter /
                   local / D_ global by value / &D_ global by address / absolute address / nested deref / other), the offset,
                   the cast width and signedness, load vs store, and the stride when indexed:
                       P  *(T *)(base + k)          the readability series' regex (tools/readability_progress.py)
                       I  *(T *)ident               a cast of a bare identifier (the `*(u16 *)D_801152A8` form)
                       X  ((T *)e)[i]               the array-index form
                       M  M2C_FIELD(base, T *, k)   m2c's placeholder macro (== *(T *)((s8 *)base + k))
                       A  (T *)(base + k)           the ADDRESS of a field, not dereferenced (call arguments, pointer sets)
  3. DECLARATIONS  every function definition's signature (K&R read), every extern declaration spelling per name, the lying
                   set (tools/argcheck.py as a library), the asm-label aliases (`extern u16 aD_x __asm__("D_x");`), the
                   builtins and attributes the Phase-36 plan deferred to this phase.
  4. THE STRUCT MAP  bases clustered into the types the fleet needs (union-find over EVIDENCE edges only — the same global,
                   call-argument flow, assignment/return flow, pointer-field flow, dedup identity; NEVER by signature alone),
                   each type with its members, evidence histogram, layout from the union of its sites, coverage and conflicts.
  5. COVERAGE      per form: sites recorded == an independent raw regex count over the same masked text, else FAIL (R32).
                   A site the parser cannot classify is still a RECORD (base class `other`, with its text) — never a skip.
  6. CONTROLS      known-true cases (R39): the player block's live-verified widths (docs/actor-struct.md), MATRIX (32) vs
                   MATRIX_L48 (48) as two layouts, Prim_8016E7C8's exact class == its definition count, one TU-CONFLICT
                   ledger row's disagreement reproduced from the declarations.

USAGE
    tools/type_census.py [-j N] [--out-dir .run/P37/census] [--no-cache]      # the census + the map + the render
    tools/type_census.py --sites                                              # also write sites.jsonl (every record)
    tools/type_census.py --check                                              # T8's gate (exit 1 on any violation)
    tools/type_census.py --selftest                                           # the fixture: every form, both verdicts
Outputs: <out-dir>/type_census.json, type_census.txt, struct_map.json, sites.jsonl (--sites), docs/struct-map.md (rendered).
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

sys.path.insert(0, str(pathlib.Path(__file__).resolve().parent))
import share_census as sc          # noqa: E402  (mask_text, scan_text, fleet_and_dirs — R33: derive from the shared scanner)
import lever_census as lc          # noqa: E402  (enumerate_files, header_includers, src_stamp, git_head)

REPO = pathlib.Path(__file__).resolve().parent.parent
OUT_DIR_DEFAULT = ".run/P37/census"
TOOL_STAMP = hashlib.sha1(pathlib.Path(__file__).read_bytes()).hexdigest()[:10]
CANON_HEADERS = ("src/shared/engine_types.h",)       # the canonical type files (T3/T5 add src/shared/main/types.h, the slots')

# ----------------------------------------------------------------------------------------------------------------------
# types and widths (o32)
# ----------------------------------------------------------------------------------------------------------------------
SCALARS = {
    "u8": (1, "u"), "s8": (1, "s"), "char": (1, "s"), "signed char": (1, "s"), "unsigned char": (1, "u"),
    "u16": (2, "u"), "s16": (2, "s"), "short": (2, "s"), "unsigned short": (2, "u"), "signed short": (2, "s"),
    "short int": (2, "s"), "unsigned short int": (2, "u"),
    "u32": (4, "u"), "s32": (4, "s"), "int": (4, "s"), "unsigned": (4, "u"), "unsigned int": (4, "u"), "signed": (4, "s"),
    "signed int": (4, "s"), "long": (4, "s"), "unsigned long": (4, "u"), "long int": (4, "s"), "unsigned long int": (4, "u"),
    "uint": (4, "u"), "uint32_t": (4, "u"), "int32_t": (4, "s"), "uint16_t": (2, "u"), "int16_t": (2, "s"),
    "uint8_t": (1, "u"), "int8_t": (1, "s"),
    "u64": (8, "u"), "s64": (8, "s"), "long long": (8, "s"), "unsigned long long": (8, "u"),
    "f32": (4, "f"), "float": (4, "f"), "f64": (8, "f"), "double": (8, "f"),
    "M2C_UNK": (4, "s"), "M2C_UNK8": (1, "s"), "M2C_UNK16": (2, "s"), "M2C_UNK32": (4, "s"), "M2C_UNK64": (8, "s"),
    "void": (0, "v"),
}
# PsyQ layouts the SDK headers fix (include/psyq/*.h) — sizes only; used when a cast names them and for the MATRIX control
SDK_SIZES = {"MATRIX": 32, "SVECTOR": 8, "VECTOR": 16, "CVECTOR": 4, "DVECTOR": 4, "RECT": 8, "RECT32": 16,
             "POLY_F3": 20, "POLY_F4": 24, "POLY_FT3": 32, "POLY_FT4": 40, "POLY_G3": 28, "POLY_G4": 36, "POLY_GT3": 40,
             "POLY_GT4": 52, "LINE_F2": 16, "LINE_F3": 20, "LINE_F4": 24, "LINE_G2": 20, "LINE_G3": 28, "LINE_G4": 36,
             "SPRT": 20, "SPRT_8": 16, "SPRT_16": 16, "TILE": 16, "TILE_1": 12, "TILE_8": 12, "TILE_16": 12,
             "DR_TPAGE": 8, "DR_ENV": 64, "DRAWENV": 92, "DISPENV": 20, "TMD_PRIM": 60, "GsDOBJ2": 32, "GsCOORDINATE2": 80,
             "GsRVIEW2": 36, "GsF_LIGHT": 16, "GsOT": 12, "GsOT_TAG": 4, "CdlLOC": 4, "CdlFILE": 20, "CdlFILTER": 4,
             "CdlATV": 4, "CdlCB": 4}

def _norm_type(t):
    t = re.sub(r"\b(const|volatile|register|extern|static)\b", "", t)
    return re.sub(r"\s+", " ", t).strip()

def scalar_of(t):
    """(width, sign) for a scalar/pointer type text; None for an aggregate or unknown name."""
    t = _norm_type(t)
    if t.endswith("*"):
        return (4, "p")
    if t in SCALARS:
        return SCALARS[t]
    return None

# ----------------------------------------------------------------------------------------------------------------------
# the definitions: parse `struct/union … { … }` bodies and compute o32 layouts
# ----------------------------------------------------------------------------------------------------------------------
DEF_START = re.compile(r"(?<![\w.])(typedef\s+)?(struct|union|enum)\s*([A-Za-z_]\w*)?\s*(__attribute__\s*\(\([^)]*\)\)\s*)?\{")
FWD_DECL = re.compile(r"(?<![\w.])(struct|union|enum)\s+([A-Za-z_]\w*)\s*;")
ATTR_RX = re.compile(r"__attribute__\s*\(\((.*?)\)\)")

def _match_brace(text, open_idx):
    depth = 0
    i = open_idx
    n = len(text)
    while i < n:
        c = text[i]
        if c == "{":
            depth += 1
        elif c == "}":
            depth -= 1
            if depth == 0:
                return i
        i += 1
    return -1

def _split_top(text, sep=";"):
    """Split on `sep` at brace/paren depth 0."""
    out, depth, cur = [], 0, []
    for c in text:
        if c in "{(":
            depth += 1
        elif c in "})":
            depth -= 1
        if c == sep and depth == 0:
            out.append("".join(cur))
            cur = []
        else:
            cur.append(c)
    if "".join(cur).strip():
        out.append("".join(cur))
    return out

def _split_declarators(decl):
    """`type a, *b, c[4]` -> (type, [(name, stars, dims, bits)])"""
    parts = _split_top(decl, ",")
    if not parts:
        return None, []
    first = parts[0].strip()
    # bitfield?  `s16 : 16` / `u8 x : 3`
    mb = re.search(r":\s*(\d+)\s*$", first)
    if mb:
        left = first[:mb.start()].strip()
        toks = left.split()
        if len(toks) >= 2 and re.match(r"^[A-Za-z_]\w*$", toks[-1]) and toks[-1] not in SCALARS and toks[-2] not in ("struct", "union", "enum"):
            return _norm_type(" ".join(toks[:-1])), [(toks[-1], 0, [], int(mb.group(1)))]
        return _norm_type(left), [("", 0, [], int(mb.group(1)))]
    # split the first part into type + declarator: the declarator is the trailing `*... name [dims]` or a function pointer
    fp = re.match(r"^(.*?)\(\s*\*\s*([A-Za-z_]\w*)\s*\)\s*\(.*\)\s*((?:\[[^\]]*\])*)$", first)
    decls = []
    if fp:
        base_type = "void *"           # a function pointer is 4 bytes; the callee type is irrelevant to the layout
        dims = re.findall(r"\[([^\]]*)\]", fp.group(3))
        decls.append((fp.group(2), 1, dims, None))
        for extra in parts[1:]:
            e = extra.strip()
            m2 = re.match(r"^(\**)\s*([A-Za-z_]\w*)\s*((?:\[[^\]]*\])*)$", e)
            if m2:
                decls.append((m2.group(2), len(m2.group(1)), re.findall(r"\[([^\]]*)\]", m2.group(3)), None))
        return base_type, decls
    m = re.match(r"^(.*?)\s*(\**)\s*([A-Za-z_]\w*)\s*((?:\[[^\]]*\])*)\s*$", first, re.S)
    if not m:
        return _norm_type(first), []
    base_type = _norm_type(m.group(1))
    decls.append((m.group(3), len(m.group(2)), re.findall(r"\[([^\]]*)\]", m.group(4)), None))
    for extra in parts[1:]:
        e = extra.strip()
        m2 = re.match(r"^(\**)\s*([A-Za-z_]\w*)\s*((?:\[[^\]]*\])*)\s*(?::\s*(\d+))?$", e)
        if m2:
            decls.append((m2.group(2), len(m2.group(1)), re.findall(r"\[([^\]]*)\]", m2.group(3)),
                          int(m2.group(4)) if m2.group(4) else None))
    return base_type, decls

def _eval_dim(d, consts):
    d = d.strip()
    if not d:
        return None                      # flexible/unsized
    try:
        return int(eval(d, {"__builtins__": {}}, dict(consts)))   # hex, sums, `0x20-0x10`, sizeof-free; the tree's dims are literals
    except Exception:
        return None

def parse_struct_body(body, consts=None):
    """Fields of one struct/union body text (the text between the braces). Nested definitions are parsed recursively.
    Returns [dict(name, type, stars, dims, bits, nested)] in order."""
    fields = []
    consts = consts or {}
    i, n = 0, len(body)
    while i < n:
        # a nested struct/union body?
        m = DEF_START.search(body, i)
        stmt_end = body.find(";", i)
        if m and (stmt_end == -1 or m.start() < stmt_end):
            close = _match_brace(body, m.end() - 1)
            if close == -1:
                break
            inner = body[m.end():close]
            # the declarators after the nested body up to `;`
            j = body.find(";", close)
            tail = body[close + 1:j if j != -1 else n]
            nested = dict(kind=m.group(2), tag=m.group(3), fields=parse_struct_body(inner, consts) if m.group(2) != "enum" else [],
                          attrs=(m.group(4) or "") + " ".join(ATTR_RX.findall(tail)))
            tail = ATTR_RX.sub("", tail).strip()
            decls = []
            if tail:
                for part in _split_top(tail, ","):
                    e = part.strip()
                    m2 = re.match(r"^(\**)\s*([A-Za-z_]\w*)\s*((?:\[[^\]]*\])*)\s*(?::\s*(\d+))?$", e)
                    if m2:
                        decls.append((m2.group(2), len(m2.group(1)), re.findall(r"\[([^\]]*)\]", m2.group(3)),
                                      int(m2.group(4)) if m2.group(4) else None))
            if not decls:
                decls = [("", 0, [], None)]        # an anonymous member (a union inside a struct)
            for (nm, stars, dims, bits) in decls:
                fields.append(dict(name=nm, type=(m.group(2) + " " + (m.group(3) or "")).strip(), stars=stars,
                                   dims=[_eval_dim(d, consts) for d in dims], bits=bits, nested=nested))
            i = (j + 1) if j != -1 else n
            continue
        if stmt_end == -1:
            break
        stmt = body[i:stmt_end].strip()
        i = stmt_end + 1
        if not stmt:
            continue
        stmt = ATTR_RX.sub("", stmt)
        base_type, decls = _split_declarators(stmt)
        if base_type is None:
            continue
        for (nm, stars, dims, bits) in decls:
            fields.append(dict(name=nm, type=base_type, stars=stars, dims=[_eval_dim(d, consts) for d in dims], bits=bits, nested=None))
    return fields

class Resolver:
    """Type name -> (size, align, leaves) under the o32 ABI. Scope: a TU's own definitions first, then the shared headers, then the SDK."""
    def __init__(self, defs_by_name):
        self.defs = defs_by_name          # name -> definition record (tag or typedef name)
        self.cache = {}
        self.stack = set()

    def layout(self, type_text, stars=0, dims=(), bits=None):
        """(size, align, leaves) of one field's type; leaves = [(off, width, sign)]; None when unknown."""
        if stars:
            sz, al, leaves = 4, 4, [(0, 4, "p")]
        else:
            t = _norm_type(type_text)
            sc_ = scalar_of(t)
            if sc_:
                w, s = sc_
                if w == 0:
                    return None
                sz, al, leaves = w, w, [(0, w, s)]
            else:
                r = self.resolve_name(t)
                if r is None:
                    return None
                sz, al, leaves = r
        for d in reversed(list(dims)):
            if d is None:
                d = 0
            leaves = [(k * sz + off, w, s) for k in range(d) for (off, w, s) in leaves]
            sz = sz * d
        return sz, al, leaves

    def resolve_name(self, name):
        name = _norm_type(name)
        if name in self.cache:
            return self.cache[name]
        if name in self.stack:
            return None
        d = self.defs.get(name)
        if d is None:
            m = re.match(r"^(struct|union|enum)\s+(\w+)$", name)
            if m and m.group(1) == "enum":
                return (4, 4, [(0, 4, "s")])
            if m and m.group(2) in self.defs and self.defs[m.group(2)].get("kind") == m.group(1):
                d = self.defs[m.group(2)]
            elif name in SDK_SIZES:
                sz = SDK_SIZES[name]
                r = (sz, 4, [(0, 4, "s")] * (sz // 4) if sz % 4 == 0 else [(0, sz, "b")])
                self.cache[name] = r
                return r
            else:
                return None
        if d.get("kind") == "enum":
            return (4, 4, [(0, 4, "s")])
        if d.get("alias_of"):               # `typedef T Name;` — a scalar/pointer alias or an alias of another aggregate
            self.stack.add(name)
            r = self.layout(d["alias_of"], d.get("alias_stars", 0), d.get("alias_dims", ()))
            self.stack.discard(name)
            self.cache[name] = r
            return r
        self.stack.add(name)
        r = self.layout_of_fields(d["fields"], d["kind"], packed=("packed" in (d.get("attrs") or "")))
        self.stack.discard(name)
        self.cache[name] = r
        return r

    def layout_of_fields(self, fields, kind, packed=False):
        off, maxal, leaves, size = 0, 1, [], 0
        bit_off = 0
        unknown = False
        for f in fields:
            if f.get("nested"):
                nd = f["nested"]
                r = self.layout_of_fields(nd["fields"], nd["kind"], packed=("packed" in (nd.get("attrs") or ""))) if nd["kind"] != "enum" else (4, 4, [(0, 4, "s")])
            else:
                r = self.layout(f["type"], f["stars"], f["dims"])
            if r is None:
                unknown = True
                r = (0, 1, [])
            fsz, fal, fleaves = r
            if f.get("dims") and f["nested"]:
                for d in reversed(f["dims"]):
                    d = d or 0
                    fleaves = [(k * fsz + o, w, s) for k in range(d) for (o, w, s) in fleaves]
                    fsz = fsz * d
            if packed:
                fal = 1
            if f.get("bits") is not None:
                # bitfields: pack into the base type's storage unit; an anonymous `s16 : 16` is a pad of the base width
                w = fsz or 4
                if bit_off == 0:
                    off = (off + fal - 1) // fal * fal
                    unit_off = off
                    self._unit = (unit_off, w)
                unit_off, uw = self._unit
                if bit_off + f["bits"] > uw * 8:
                    off = unit_off + uw
                    off = (off + fal - 1) // fal * fal
                    unit_off = off
                    self._unit = (unit_off, w)
                    bit_off = 0
                if f["name"]:
                    leaves.append((unit_off, w, "bf"))
                bit_off += f["bits"]
                maxal = max(maxal, fal)
                end = unit_off + w
                if bit_off >= uw * 8:
                    bit_off = 0
                    off = end
                else:
                    off = unit_off
                size = max(size, end)
                if kind == "union":
                    off = 0
                continue
            bit_off = 0
            if kind == "union":
                leaves.extend((0 + o, w, s) for (o, w, s) in fleaves)
                size = max(size, fsz)
                maxal = max(maxal, fal)
                continue
            off = (off + fal - 1) // fal * fal
            leaves.extend((off + o, w, s) for (o, w, s) in fleaves)
            off += fsz
            size = max(size, off)
            maxal = max(maxal, fal)
        size = (size + maxal - 1) // maxal * maxal
        if unknown:
            return None
        return size, maxal, sorted(set(leaves))

def layout_hash(lay):
    if lay is None:
        return None
    size, al, leaves = lay
    return hashlib.sha1(json.dumps([size, leaves]).encode()).hexdigest()[:12]

def find_definitions(masked, rel, span_of_line, line_of):
    """All struct/union/enum definitions and typedef aliases in one masked file. Records carry file, line, kind, tag, names, fields."""
    out = []
    pos = 0
    while True:
        m = DEF_START.search(masked, pos)
        if not m:
            break
        open_idx = m.end() - 1
        close = _match_brace(masked, open_idx)
        if close == -1:
            break
        body = masked[open_idx + 1:close]
        # the declarators after `}` up to `;`
        j = masked.find(";", close)
        tail = masked[close + 1:j] if j != -1 else ""
        attrs = (m.group(4) or "") + " " + " ".join(ATTR_RX.findall(tail))
        tail_clean = ATTR_RX.sub("", tail).strip()
        names = []
        if m.group(1):          # typedef
            for part in _split_top(tail_clean, ","):
                e = part.strip()
                m2 = re.match(r"^(\**)\s*([A-Za-z_]\w*)\s*((?:\[[^\]]*\])*)$", e)
                if m2:
                    names.append((m2.group(2), len(m2.group(1)), re.findall(r"\[([^\]]*)\]", m2.group(3))))
        ln = line_of(m.start())
        d = span_of_line.get(ln)
        fields = parse_struct_body(body) if m.group(2) != "enum" else []
        text = re.sub(r"\s+", " ", masked[m.start():(j + 1) if j != -1 else close + 1]).strip()
        rec = dict(file=rel, line=ln, end=line_of(close), kind=m.group(2), tag=m.group(3), typedef=bool(m.group(1)),
                   names=[n for (n, s, dd) in names if s == 0 and not dd], ptr_names=[n for (n, s, dd) in names if s or dd],
                   fields=fields, attrs=attrs.strip(), scope=("block" if d else "file"), fn=(d["name"] if d else None),
                   text_hash=hashlib.sha1(text.encode()).hexdigest()[:12], nfields=len(fields),
                   is_canon=(rel in CANON_HEADERS))
        out.append(rec)
        # nested definitions inside the body are NOT separate records (they live inside the parent's layout)
        pos = (j + 1) if j != -1 else close + 1
    # scalar/alias typedefs: `typedef T Name;` / `typedef struct X Name;` / `typedef T (*Name)(...)` / `typedef T Name[4];`
    aliases = []
    for m in re.finditer(r"(?<![\w.])typedef\s+([^;{}]+?)\s*;", masked):
        txt = m.group(1)
        if "{" in txt or "}" in txt:
            continue
        fp = re.match(r"^(.*?)\(\s*\*\s*([A-Za-z_]\w*)\s*\)\s*\(.*\)$", txt, re.S)
        if fp:
            aliases.append(dict(file=rel, line=line_of(m.start()), name=fp.group(2), alias_of="void *", alias_stars=0, alias_dims=[],
                                fnptr=True))
            continue
        m2 = re.match(r"^(.*?)\s*(\**)\s*([A-Za-z_]\w*)\s*((?:\[[^\]]*\])*)$", txt.strip(), re.S)
        if not m2:
            continue
        aliases.append(dict(file=rel, line=line_of(m.start()), name=m2.group(3), alias_of=_norm_type(m2.group(1)),
                            alias_stars=len(m2.group(2)), alias_dims=[_eval_dim(d, {}) for d in re.findall(r"\[([^\]]*)\]", m2.group(4))],
                            fnptr=False))
    fwd = [dict(file=rel, line=line_of(m.start()), kind=m.group(1), tag=m.group(2)) for m in FWD_DECL.finditer(masked)]
    return out, aliases, fwd

# ----------------------------------------------------------------------------------------------------------------------
# the cast sites
# ----------------------------------------------------------------------------------------------------------------------
TYPE_IN_CAST = r"((?:struct\s+|union\s+)?[A-Za-z_]\w*)\s*(\*+)"
FORM_P = re.compile(r"\*\s*\(\s*" + TYPE_IN_CAST + r"\s*\)\s*\(")                            # *(T *)(
FORM_I = re.compile(r"\*\s*\(\s*" + TYPE_IN_CAST + r"\s*\)\s*(&?)\s*([A-Za-z_]\w*|0x[0-9A-Fa-f]+)\b(?!\s*[\(\[])")   # *(T *)ident / *(T *)0x80…
FORM_X = re.compile(r"\(\s*\(\s*" + TYPE_IN_CAST + r"\s*\)\s*([^()\[\]]+?)\s*\)\s*\[")     # ((T *)e)[
FORM_M = re.compile(r"\bM2C_FIELD\s*\(")
FORM_A = re.compile(r"(?<![\w\)\]\*])\(\s*" + TYPE_IN_CAST + r"\s*\)\s*\((?=[^()]*[+-])")     # (T *)(… + …)  not deref'd
FORM_C = re.compile(r"\(\s*\(\s*" + TYPE_IN_CAST + r"\s*\)\s*([^()\[\]]+?)\s*\)\s*->\s*([A-Za-z_]\w*)")   # ((T *)e)->f  (cast-then-member)
ABS_ADDR = re.compile(r"^0x80[0-9A-Fa-f]{6}$")
ASSIGN_OP = re.compile(r"^\s*(?:(?:\+|-|\*|/|%|&|\||\^|<<|>>)?=(?!=)|\+\+|--)")
IDENT = re.compile(r"^[A-Za-z_]\w*$")
INT_LIT = re.compile(r"^-?(?:0x[0-9A-Fa-f]+|\d+)$")

def _paren_body(text, open_idx):
    """text[open_idx] == '(' -> (inner, close_idx) or (None, -1)."""
    depth = 0
    for i in range(open_idx, len(text)):
        c = text[i]
        if c == "(":
            depth += 1
        elif c == ")":
            depth -= 1
            if depth == 0:
                return text[open_idx + 1:i], i
    return None, -1

def _strip_parens(e):
    e = e.strip()
    while e.startswith("(") and e.endswith(")"):
        inner, close = _paren_body(e, 0)
        if close == len(e) - 1:
            e = inner.strip()
        else:
            break
    return e

def _int(s):
    s = s.strip()
    try:
        return int(s, 0)
    except Exception:
        return None

def _split_plus(e):
    """Top-level `a + b` / `a - b` split (depth 0, not inside a cast's parens). Returns (lhs, op, rhs) or None."""
    depth = 0
    for i, c in enumerate(e):
        if c in "([":
            depth += 1
        elif c in ")]":
            depth -= 1
        elif depth == 0 and c in "+-" and i > 0:
            prev = e[:i].rstrip()
            if prev and prev[-1] not in "+-*/%&|^<>=(,":
                return e[:i].strip(), c, e[i + 1:].strip()
    return None

def parse_base(expr):
    """Classify the inner expression of a cast: returns dict(base, bclass, off, inner_cast, index, stride, text)."""
    e = _strip_parens(expr)
    rec = dict(base=None, bclass="other", off=0, inner_cast=None, index=None, stride=None, text=re.sub(r"\s+", " ", e)[:120])
    if ABS_ADDR.match(e):
        rec.update(base=e, bclass="abs", off=0)
        return rec
    # strip an outer cast `(s32)X` / `(u8 *)X` / `(char *)X`
    m = re.match(r"^\(\s*((?:struct\s+|union\s+)?[A-Za-z_]\w*\s*\**)\s*\)\s*(.+)$", e, re.S)
    if m and not m.group(2).lstrip().startswith(("+", "-")):
        rec["inner_cast"] = _norm_type(m.group(1))
        e = _strip_parens(m.group(2))
        # `(s32)matrix + 8`: the cast binds to `matrix`; the split below handles `matrix + 8`
    sp = _split_plus(e)
    if sp:
        lhs, op, rhs = sp
        lhs_s = _strip_parens(lhs)
        rhs_s = _strip_parens(rhs)
        # a constant on the right
        k = _int(rhs_s)
        if k is not None:
            b = parse_base(lhs_s)
            b["off"] = (b.get("off") or 0) + (k if op == "+" else -k)
            b["text"] = rec["text"]
            if rec["inner_cast"] and not b.get("inner_cast"):
                b["inner_cast"] = rec["inner_cast"]
            return b
        k = _int(lhs_s)
        if k is not None and op == "+":
            b = parse_base(rhs_s)
            b["off"] = (b.get("off") or 0) + k
            b["text"] = rec["text"]
            return b
        # an index: `base + i * 8` / `base + (i << 2)` / `base + i`
        b = parse_base(lhs_s)
        if b["bclass"] in ("param", "local", "global", "gaddr", "ident", "nested", "abs"):
            b["index"] = re.sub(r"\s+", " ", rhs_s)[:60]
            ms = re.match(r"^([A-Za-z_]\w*)\s*\*\s*(0x[0-9A-Fa-f]+|\d+)$", rhs_s) or re.match(r"^\(?\s*([A-Za-z_]\w*)\s*<<\s*(\d+)\s*\)?$", rhs_s)
            if ms:
                v = _int(ms.group(2))
                b["stride"] = (1 << v) if "<<" in rhs_s else v
            b["text"] = rec["text"]
            return b
        rec["bclass"] = "other"
        return rec
    # a nested deref
    if e.startswith("*") or FORM_M.match(e):
        rec.update(base=e[:60], bclass="nested")
        return rec
    if e.startswith("&"):
        inner = _strip_parens(e[1:])
        if IDENT.match(inner):
            rec.update(base=inner, bclass=("gaddr" if inner.startswith("D_") else "addr-of"))
            return rec
        mi = re.match(r"^([A-Za-z_]\w*)\s*\[(.+)\]$", inner)
        if mi:
            rec.update(base=mi.group(1), bclass=("gaddr" if mi.group(1).startswith("D_") else "addr-of"), index=mi.group(2)[:60])
            return rec
        rec.update(base=inner[:60], bclass="addr-of")
        return rec
    if IDENT.match(e):
        rec.update(base=e, bclass=("global" if e.startswith("D_") else "func" if e.startswith("func_") else "ident"))
        return rec
    mi = re.match(r"^([A-Za-z_]\w*)\s*\[(.+)\]$", e)
    if mi:
        rec.update(base=mi.group(1), bclass=("global" if mi.group(1).startswith("D_") else "ident"), index=mi.group(2)[:60])
        return rec
    mm = re.match(r"^([A-Za-z_]\w*)\s*->\s*([A-Za-z_]\w*)$", e)
    if mm:
        rec.update(base=e, bclass="member")
        return rec
    return rec

def _after(masked, idx):
    """The text right after idx (skipping spaces) — for the store test."""
    j = idx
    while j < len(masked) and masked[j] in " \t":
        j += 1
    return masked[j:j + 3]

def _store_kind(tail):
    m = ASSIGN_OP.match(tail)
    if not m:
        return "load"
    return "rmw" if m.group(0).strip() in ("++", "--") or "=" != m.group(0).strip() else "store"

def find_sites(masked, rel, span_of_line, line_of, params_of):
    sites = []
    raw_counts = collections.Counter()
    claimed = set()      # start offsets already recorded (a form-P match inside a form-X, etc. are distinct sites — nested is fine)

    def fn_ctx(pos):
        ln = line_of(pos)
        d = span_of_line.get(ln)
        return ln, d

    def classify(bclass, base, d):
        if bclass == "ident" and d is not None:
            if base in params_of.get(d["name"], ()):
                return "param"
            return "local"
        return bclass

    # P: *(T *)( … )
    for m in FORM_P.finditer(masked):
        raw_counts["P"] += 1
        open_idx = m.end() - 1
        inner, close = _paren_body(masked, open_idx)
        ln, d = fn_ctx(m.start())
        rec = dict(form="P", tu=rel, fn=(d["name"] if d else None), line=ln, ctype=_norm_type(m.group(1) + " " + m.group(2)),
                   stars=len(m.group(2)))
        if inner is None:
            rec.update(bclass="other", base=None, off=0, text="UNBALANCED", refused="unbalanced parens")
        else:
            b = parse_base(inner)
            b["bclass"] = classify(b["bclass"], b.get("base"), d)
            rec.update(b)
            rec["access"] = _store_kind(_after(masked, close + 1))
        sites.append(rec)
    # I: *(T *)ident  /  *(T *)&ident
    for m in FORM_I.finditer(masked):
        raw_counts["I"] += 1
        ln, d = fn_ctx(m.start())
        base = m.group(4)
        amp = m.group(3) == "&"
        if ABS_ADDR.match(base):
            bclass = "abs"
        elif amp:
            bclass = "gaddr" if base.startswith("D_") else "addr-of"
        else:
            bclass = classify("global" if base.startswith("D_") else "func" if base.startswith("func_") else "ident", base, d)
        rec = dict(form="I", tu=rel, fn=(d["name"] if d else None), line=ln, ctype=_norm_type(m.group(1) + " " + m.group(2)),
                   stars=len(m.group(2)), base=base, bclass=bclass, off=0, inner_cast=None, index=None, stride=None,
                   text=("&" if amp else "") + base, access=_store_kind(_after(masked, m.end())))
        sites.append(rec)
    # X: ((T *)e)[i]
    for m in FORM_X.finditer(masked):
        raw_counts["X"] += 1
        ln, d = fn_ctx(m.start())
        b = parse_base(m.group(3))
        b["bclass"] = classify(b["bclass"], b.get("base"), d)
        # the index expression
        idx_inner, idx_close = _paren_body(masked.replace("[", "(", 0), m.end() - 1) if False else (None, -1)
        j = masked.find("]", m.end())
        idx = masked[m.end():j].strip() if j != -1 else None
        rec = dict(form="X", tu=rel, fn=(d["name"] if d else None), line=ln, ctype=_norm_type(m.group(1) + " " + m.group(2)),
                   stars=len(m.group(2)), text=b["text"], base=b.get("base"), bclass=b["bclass"], off=b.get("off", 0),
                   inner_cast=b.get("inner_cast"), index=(idx[:60] if idx else None), stride=None,
                   access=_store_kind(_after(masked, (j + 1) if j != -1 else m.end())))
        k = _int(idx) if idx else None
        if k is not None:
            w = scalar_of(rec["ctype"].rstrip("* ").strip()) if rec["stars"] == 1 else (4, "p")
            if w:
                rec["off"] = rec["off"] + k * w[0]
                rec["index"] = None
        sites.append(rec)
    # M: M2C_FIELD(base, T *, k)
    for m in FORM_M.finditer(masked):
        raw_counts["M"] += 1
        inner, close = _paren_body(masked, m.end() - 1)
        ln, d = fn_ctx(m.start())
        rec = dict(form="M", tu=rel, fn=(d["name"] if d else None), line=ln)
        if inner is None:
            rec.update(ctype=None, stars=0, base=None, bclass="other", off=0, text="UNBALANCED", refused="unbalanced parens")
        else:
            args = _split_top(inner, ",")
            if len(args) != 3:
                rec.update(ctype=None, stars=0, base=None, bclass="other", off=0, text=inner[:80], refused="M2C_FIELD arity")
            else:
                b = parse_base(args[0])
                b["bclass"] = classify(b["bclass"], b.get("base"), d)
                k = _int(_strip_parens(args[2]))
                ctype = _norm_type(args[1])
                rec.update(b)
                rec.update(ctype=ctype, stars=ctype.count("*"), off=(b.get("off") or 0) + (k if k is not None else 0),
                           access=_store_kind(_after(masked, close + 1)))
                if k is None:
                    rec["index"] = _strip_parens(args[2])[:60]
        sites.append(rec)
    # A: (T *)(base + k)  — an address, not a dereference
    for m in FORM_A.finditer(masked):
        raw_counts["A"] += 1
        open_idx = m.end() - 1
        inner, close = _paren_body(masked, open_idx)
        ln, d = fn_ctx(m.start())
        rec = dict(form="A", tu=rel, fn=(d["name"] if d else None), line=ln, ctype=_norm_type(m.group(1) + " " + m.group(2)),
                   stars=len(m.group(2)))
        if inner is None:
            rec.update(bclass="other", base=None, off=0, text="UNBALANCED", refused="unbalanced parens")
        else:
            b = parse_base(inner)
            b["bclass"] = classify(b["bclass"], b.get("base"), d)
            rec.update(b)
            rec["access"] = "addr"
        sites.append(rec)
    # C: ((T *)e)->f — a typed cast followed by a member access: already a COMPONENT_REF (/s); counted apart (rung 1's form)
    for m in FORM_C.finditer(masked):
        raw_counts["C"] += 1
        ln, d = fn_ctx(m.start())
        b = parse_base(m.group(3))
        b["bclass"] = classify(b["bclass"], b.get("base"), d)
        rec = dict(form="C", tu=rel, fn=(d["name"] if d else None), line=ln, ctype=_norm_type(m.group(1) + " " + m.group(2)),
                   stars=len(m.group(2)), text=b["text"], base=b.get("base"), bclass=b["bclass"], off=b.get("off", 0),
                   inner_cast=b.get("inner_cast"), index=b.get("index"), stride=None, member=m.group(4),
                   access=_store_kind(_after(masked, m.end())))
        sites.append(rec)
    for r in sites:
        # the ACCESSED type is the cast's pointee: `(u16 *)` dereferenced -> u16; `(T **)` -> a pointer
        stars = r.get("stars", 0)
        ct = r.get("ctype")
        if not ct:
            w = None
        elif stars > 1 or r["form"] == "A":
            w = (4, "p")
        elif r["form"] == "C":
            w = None          # the member's width is the type's field's — resolved when the type is
        else:
            w = scalar_of(ct.rstrip("* ").strip())
        r["width"] = w[0] if w else None
        r["sign"] = w[1] if w else ("agg" if ct else None)
    return sites, raw_counts

# ----------------------------------------------------------------------------------------------------------------------
# declarations, calls and flows (for the declaration census and the struct map)
# ----------------------------------------------------------------------------------------------------------------------
NAME = r"[A-Za-z_]\w*"
EXTERN_FN = re.compile(r"\bextern\s+([A-Za-z_][\w \t*]*?)\b(" + NAME + r")\s*\(([^;{)]*)\)\s*(__asm__\s*\(\s*\"(\w+)\"\s*\))?\s*;")
EXTERN_DATA = re.compile(r"\bextern\s+([A-Za-z_][\w \t*]*?)\b(" + NAME + r")\s*((?:\[[^\]]*\])*)\s*(__asm__\s*\(\s*\"(\w+)\"\s*\))?\s*;")
BUILTIN = re.compile(r"__builtin_(\w+)")
ATTR_USE = re.compile(r"__attribute__\s*\(\(\s*(\w+)")
CALL = re.compile(r"(?<![\w.>])(" + NAME + r")\s*\(")
KEYWORDS = sc.KEYWORDS | {"sizeof", "return", "if", "while", "for", "switch", "M2C_FIELD", "M2C_BITWISE", "defined"}
ASSIGN = re.compile(r"(?<![=!<>])(" + NAME + r")\s*=(?!=)\s*([^;]+);")
RETURN = re.compile(r"\breturn\s+([^;]+);")

def _param_names(head_params, body_head_decls):
    """Names of a definition's parameters: prototype form `T a, T *b` or K&R `a, b` (types declared before `{`)."""
    names = []
    hp = head_params.strip()
    if not hp or hp == "void":
        return names
    for part in _split_top(hp, ","):
        p = part.strip()
        if not p or p == "...":
            continue
        m = re.search(r"\(\s*\*\s*(" + NAME + r")\s*\)", p)      # a function-pointer parameter
        if m:
            names.append(m.group(1))
            continue
        toks = re.findall(NAME, re.sub(r"\[[^\]]*\]", "", p))
        if not toks:
            continue
        if len(toks) == 1:
            names.append(toks[0])          # K&R name or a bare type — a bare type (`s32`) is filtered below
        else:
            names.append(toks[-1])
    return [n for n in names if n not in SCALARS and n not in ("struct", "union", "const", "volatile", "unsigned", "signed")]

def find_decls_and_flows(masked, rel, defs, span_of_line, line_of):
    """Per file: function definitions with signatures, extern declaration spellings, aliases, builtins, attributes, and the
    flow edges (calls with identifier arguments, identifier assignments, returns) per enclosing function."""
    fndefs, extern_fns, extern_data, aliases, builtins, attrs, flows = [], [], [], [], [], [], []
    raw_lines = masked.split("\n")
    line_starts = [0]
    for ln in raw_lines:
        line_starts.append(line_starts[-1] + len(ln) + 1)
    params_of = {}
    for d in defs:
        # the head: from the def's first line to its `{`
        start = line_starts[d["line"] - 1]
        brace = masked.find("{", start)
        head = masked[start:brace] if brace != -1 else ""
        m = re.search(r"\b(" + re.escape(d["name"]) + r")\s*\(", head)
        if not m:
            # an alias-named def (`__asm__("func_x")`): take the first ident(
            m = re.search(r"\b(" + NAME + r")\s*\((?=[^;]*\))", head)
        if not m:
            continue
        inner, close = _paren_body(head, m.end() - 1)
        if inner is None:
            continue
        ret = _norm_type(head[:m.start()].split(";")[-1].replace("static", "").replace("extern", "")).strip() or "int"
        kr_tail = head[close + 1:].strip()
        pnames = _param_names(inner, kr_tail)
        kr = bool(kr_tail) and bool(re.search(NAME + r"\s*[,;]", kr_tail))
        params_of[d["name"]] = pnames
        s0 = line_starts[d["line"] - 1]
        s1 = line_starts[d["end"]] - 1 if d["end"] < len(line_starts) else len(masked)
        d["nhash"] = lc.norm_hash(masked[s0:s1])          # func_/D_ addresses masked: the Phase-35 normalized-text identity
        fndefs.append(dict(tu=rel, fn=d["name"], line=d["line"], ret=ret, params=re.sub(r"\s+", " ", inner).strip(), pnames=pnames,
                           arity=len(pnames) if pnames else (0 if inner.strip() in ("", "void") else len(_split_top(inner, ","))),
                           kr=kr, nhash=d["nhash"], text_hash=d.get("text_hash")))
    for m in EXTERN_FN.finditer(masked):
        ln = line_of(m.start())
        d = span_of_line.get(ln)
        extern_fns.append(dict(tu=rel, name=m.group(2), ret=_norm_type(m.group(1)), params=re.sub(r"\s+", " ", m.group(3)).strip(),
                               line=ln, scope=("block" if d else "file"), alias=m.group(5)))
    for m in EXTERN_DATA.finditer(masked):
        if masked[m.end() - 1] != ";":
            continue
        ln = line_of(m.start())
        d = span_of_line.get(ln)
        extern_data.append(dict(tu=rel, name=m.group(2), type=_norm_type(m.group(1)), dims=m.group(3) or "", line=ln,
                                scope=("block" if d else "file"), alias=m.group(5)))
        if m.group(5):
            aliases.append(dict(tu=rel, name=m.group(2), real=m.group(5), type=_norm_type(m.group(1)), line=ln, kind="data"))
    for e in extern_fns:
        if e["alias"]:
            aliases.append(dict(tu=rel, name=e["name"], real=e["alias"], type=e["ret"], line=e["line"], kind="func"))
    for m in BUILTIN.finditer(masked):
        ln = line_of(m.start())
        builtins.append(dict(tu=rel, name=m.group(1), line=ln, fn=(span_of_line.get(ln) or {}).get("name")))
    for m in ATTR_USE.finditer(masked):
        ln = line_of(m.start())
        attrs.append(dict(tu=rel, name=m.group(1), line=ln))
    # flows, per function body
    for d in defs:
        s0 = line_starts[d["line"] - 1]
        s1 = line_starts[d["end"]] - 1 if d["end"] < len(line_starts) else len(masked)
        body = masked[s0:s1]
        fn = d["name"]
        for m in CALL.finditer(body):
            callee = m.group(1)
            if callee in KEYWORDS or callee == fn and m.start() < body.find("{"):
                continue
            inner, close = _paren_body(body, m.end() - 1)
            if inner is None or callee in params_of and False:
                continue
            args = [a.strip() for a in _split_top(inner, ",")] if inner.strip() else []
            for i, a in enumerate(args):
                a2 = _strip_parens(a)
                a2 = re.sub(r"^\(\s*(?:struct\s+|union\s+)?[A-Za-z_]\w*\s*\**\s*\)\s*", "", a2)     # drop a leading cast
                if IDENT.match(a2) and a2 not in SCALARS:
                    flows.append(dict(tu=rel, fn=fn, kind="arg", src=a2, callee=callee, i=i))
                elif re.match(r"^&\s*(D_80[0-9A-Fa-f]{6})$", a2):
                    flows.append(dict(tu=rel, fn=fn, kind="arg&", src=a2[1:].strip(), callee=callee, i=i))
        for m in ASSIGN.finditer(body):
            lhs, rhs = m.group(1), _strip_parens(m.group(2))
            if lhs in KEYWORDS:
                continue
            rhs2 = re.sub(r"^\(\s*(?:struct\s+|union\s+)?[A-Za-z_]\w*\s*\**\s*\)\s*", "", rhs)
            if IDENT.match(rhs2) and rhs2 not in SCALARS:
                flows.append(dict(tu=rel, fn=fn, kind="assign", dst=lhs, src=rhs2))
            elif re.match(r"^&\s*(D_80[0-9A-Fa-f]{6})$", rhs2):
                flows.append(dict(tu=rel, fn=fn, kind="assign&", dst=lhs, src=rhs2[1:].strip()))
            else:
                mc = re.match(r"^(" + NAME + r")\s*\((.*)\)$", rhs2, re.S)
                if mc and mc.group(1) not in KEYWORDS:
                    flows.append(dict(tu=rel, fn=fn, kind="ret-of", dst=lhs, callee=mc.group(1)))
                    continue
                # a pointer field read: `x = *(T *)(base + k)` / M2C_FIELD(base, T *, k) / ((T*)base)[i]
                mp = FORM_P.match(rhs2) or FORM_M.match(rhs2)
                if mp:
                    if rhs2.startswith("M2C_FIELD"):
                        inner, _ = _paren_body(rhs2, rhs2.find("("))
                        args = _split_top(inner or "", ",")
                        if len(args) == 3:
                            b = parse_base(args[0])
                            k = _int(_strip_parens(args[2]))
                            if b.get("base") and k is not None and b["bclass"] != "other":
                                flows.append(dict(tu=rel, fn=fn, kind="field", dst=lhs, base=b["base"], bclass=b["bclass"],
                                                  off=(b.get("off") or 0) + k))
                    else:
                        inner, _ = _paren_body(rhs2, rhs2.find("(", rhs2.find(")")))
                        if inner is not None:
                            b = parse_base(inner)
                            if b.get("base") and b["bclass"] not in ("other", "nested") and b.get("index") is None:
                                flows.append(dict(tu=rel, fn=fn, kind="field", dst=lhs, base=b["base"], bclass=b["bclass"], off=b.get("off") or 0))
        for m in RETURN.finditer(body):
            v = _strip_parens(m.group(1))
            v = re.sub(r"^\(\s*(?:struct\s+|union\s+)?[A-Za-z_]\w*\s*\**\s*\)\s*", "", v)
            if IDENT.match(v) and v not in SCALARS and v not in ("NULL",):
                flows.append(dict(tu=rel, fn=fn, kind="return", src=v))
    return fndefs, extern_fns, extern_data, aliases, builtins, attrs, flows, params_of

# ----------------------------------------------------------------------------------------------------------------------
# the per-file walker
# ----------------------------------------------------------------------------------------------------------------------
def walk_file(raw, rel):
    masked = sc.mask_text(raw)
    line_of = lambda idx: masked.count("\n", 0, idx) + 1
    recs = sc.scan_text(raw, rel, shared_defs=None)
    defs = [r for r in recs if r["form"] == "def"]
    span_of_line = {}
    for d in defs:
        for ln in range(d["line"], d["end"] + 1):
            span_of_line[ln] = d
    definitions, aliases_td, fwd = find_definitions(masked, rel, span_of_line, line_of)
    fndefs, extern_fns, extern_data, asm_aliases, builtins, attrs, flows, params_of = find_decls_and_flows(masked, rel, defs, span_of_line, line_of)
    sites, raw_counts = find_sites(masked, rel, span_of_line, line_of, params_of)
    # every site records the classification of its base in the function's parameter list
    abs_casts = sum(1 for s in sites if s.get("bclass") == "abs")
    # identifier counts for the dead-name test (type names are identifiers; the canonical header is excluded by the caller)
    ident_counts = collections.Counter(m.group(0) for m in re.finditer(r"\b[A-Za-z_]\w*\b", masked))
    ident_counts = {k: v for k, v in ident_counts.items() if not k.startswith(("func_", "D_")) and k not in SCALARS and len(k) > 1}
    return dict(rel=rel, definitions=definitions, typedef_aliases=aliases_td, fwd=fwd, sites=sites, raw_counts=dict(raw_counts), ident_counts=ident_counts,
                fndefs=fndefs, extern_fns=extern_fns, extern_data=extern_data, asm_aliases=asm_aliases, builtins=builtins,
                attrs=attrs, flows=flows, abs_casts=abs_casts, nfuncs=len(defs))

def _walk_worker(rel):
    raw = (REPO / rel).read_text(errors="surrogateescape")
    return walk_file(raw, rel)

# ----------------------------------------------------------------------------------------------------------------------
# the struct map: union-find over evidence
# ----------------------------------------------------------------------------------------------------------------------
class UF:
    """Union-find with a per-cluster offset map: a merge that would put two incompatible widths at one offset (or overlap two
    fields) is VETOED and counted — a width conflict is evidence of two types, never a union (the Plan agent's rule)."""
    def __init__(self):
        self.p = {}
        self.ev = collections.Counter()
        self.veto = collections.Counter()
        self.offs = {}            # root -> {off: (width, sign)} (the majority per offset at the time of merging)
        self.merges_of = {}       # root -> Counter(edge kind) — which evidence built the cluster
    def add_off(self, x, off, w, sg):
        r = self.find(x)
        m = self.offs.setdefault(r, {})
        if off not in m:
            m[off] = (w, sg)
    @staticmethod
    def _conflict(ma, mb):
        if not ma or not mb:
            return False
        small, big = (ma, mb) if len(ma) < len(mb) else (mb, ma)
        for off, (w, sg) in small.items():
            o = big.get(off)
            if o is not None and (o[0] != w or (o[1] != sg and {o[1], sg} - {"p", "s", "u"} == set() and False)):
                if o[0] != w:
                    return True
            # overlap: any big field starting inside [off, off+w) or containing off
            for k in range(1, w):
                if (off + k) in big:
                    return True
            if w > 1:
                for back in (1, 2, 3):
                    o2 = big.get(off - back)
                    if o2 is not None and o2[0] > back:
                        return True
        return False
    def overlap(self, a, b):
        """Offsets the two clusters share with equal width — positive evidence that they are one layout."""
        ma, mb = self.offs.get(self.find(a)), self.offs.get(self.find(b))
        if not ma or not mb:
            return 0
        small, big = (ma, mb) if len(ma) < len(mb) else (mb, ma)
        return sum(1 for off, (w, sg) in small.items() if off in big and big[off][0] == w)
    def structured(self, x, n=2):
        m = self.offs.get(self.find(x))
        return bool(m) and len(m) >= n
    def find(self, x):
        p = self.p
        if x not in p:
            p[x] = x
            return x
        r = x
        while p[r] != r:
            r = p[r]
        while p[x] != r:
            p[x], x = r, p[x]
        return r
    def union(self, a, b, kind):
        ra, rb = self.find(a), self.find(b)
        if ra == rb:
            return False
        ma, mb = self.offs.get(ra), self.offs.get(rb)
        if self._conflict(ma, mb):
            self.veto[kind] += 1
            return False
        if ra > rb:
            ra, rb = rb, ra
        self.p[rb] = ra
        if mb:
            m = self.offs.setdefault(ra, {})
            for k, v in mb.items():
                m.setdefault(k, v)
            self.offs.pop(rb, None)
        mc = self.merges_of.setdefault(ra, collections.Counter())
        mc[kind] += 1
        old = self.merges_of.pop(rb, None)
        if old:
            mc.update(old)
        self.ev[kind] += 1
        return True

class Identity:
    """A function is its DEFINITION, never its bare name (6,247 names carry more than one body text across TUs): a shared header
    body is one function fleet-wide (`H:<path>`); a private definition is its normalized-text hash (`F:<nhash>`, func_/D_ masked —
    the cross-address copies of one body share it); a callee with no definition in reach is external to its space (`X:<space>:<name>`)."""
    def __init__(self, fndefs, tu_aliases, space_of_tu, shared_fn_header):
        self.space_of_tu = space_of_tu
        self.shared = shared_fn_header
        self.by_tu = collections.defaultdict(dict)          # tu -> name -> nhash
        self.by_name = collections.defaultdict(set)         # name -> {nhash}
        self.by_alias = collections.defaultdict(dict)       # alias -> name -> nhash
        for f in fndefs:
            self.by_tu[f["tu"]][f["fn"]] = f["nhash"]
            self.by_name[f["fn"]].add(f["nhash"])
            for a in tu_aliases.get(f["tu"], ()):
                self.by_alias[a].setdefault(f["fn"], f["nhash"])
        self.tu_aliases = tu_aliases
    def def_key(self, tu, fn):
        h = self.shared.get(fn)
        if h and tu.startswith("src/shared/"):
            return "H:" + h
        nh = self.by_tu.get(tu, {}).get(fn)
        if nh:
            return "F:" + nh
        if h:
            return "H:" + h
        return "X:" + self.space_of_tu(tu) + ":" + fn
    def callee_key(self, tu, callee):
        nh = self.by_tu.get(tu, {}).get(callee)
        if nh:
            return "F:" + nh
        h = self.shared.get(callee)
        if h:
            return "H:" + h
        hs = self.by_name.get(callee)
        if hs and len(hs) == 1:
            return "F:" + next(iter(hs))
        for a in self.tu_aliases.get(tu, ()):
            nh = self.by_alias.get(a, {}).get(callee)
            if nh:
                return "F:" + nh
        return "X:" + self.space_of_tu(tu) + ":" + callee

def build_struct_map(results, tu_aliases, space_of_tu, shared_fn_header, sites_all, ident):
    uf = UF()
    node_sites = collections.defaultdict(list)          # node -> [site idx]
    RAW = ("P", "I", "X", "M")
    nested_sites = []                                   # (site idx, inner base node, inner off) — assigned after the flows settle
    typed_params = set()                                # (def key, param index) the callee itself dereferences: the only params flows may enter
    pindex = {}
    for r in results.values():
        for f in r["fndefs"]:
            pindex[(f["tu"], f["fn"])] = {pn: i for i, pn in enumerate(f["pnames"])}
    # 1. bases of cast sites (the raw dereference forms only — A and C are counted apart)
    for i, s in enumerate(sites_all):
        if s["form"] not in RAW:
            continue
        if s["bclass"] == "nested":
            inner = nested_target(s.get("text") or "")
            if inner:
                ib, ibc, ioff = inner
                fk = ident.def_key(s["tu"], s["fn"]) if s.get("fn") else "X:" + ident.space_of_tu(s["tu"]) + ":<file>"
                if ibc == "ident":
                    ibc = "param" if s.get("fn") and ib in pindex.get((s["tu"], s["fn"]), {}) else "local"
                nested_sites.append((i, base_node(ib, ibc, fk), ioff))
            continue
        node = site_node(s, ident)
        if node is None:
            continue
        s["node"] = node
        node_sites[node].append(i)
        uf.find(node)
        if s.get("index") is None and s.get("width"):
            uf.add_off(node, s["off"], s["width"], s["sign"])
        if s["bclass"] == "param" and s.get("fn"):
            pi = pindex.get((s["tu"], s["fn"]), {}).get(s["base"])
            if pi is not None:
                typed_params.add((ident.def_key(s["tu"], s["fn"]), pi))
    # 1b. a parameter's positional node (P:<fk>:<i>, what callers flow into) IS its named node (PV:<fk>:<name>)
    for r in results.values():
        for f in r["fndefs"]:
            fk = ident.def_key(f["tu"], f["fn"])
            for i, pn in enumerate(f["pnames"]):
                uf.union(f"PV:{fk}:{pn}", f"P:{fk}:{i}", "param")
                uf.union(f"L:{fk}:{pn}", f"PV:{fk}:{pn}", "param")      # a parameter named in a flow is the same base
    # 1c. a bare global's declared type seeds its AT node (so `u16 D_A` and `s32 D_B` can never be one type through a reused temp)
    for r in results.values():
        for e in r["extern_data"]:
            if e["name"].startswith("D_80") and not e["dims"]:
                w = scalar_of(e["type"])
                if w and w[0] > 0:
                    uf.add_off(f"AT:{e['name']}", 0, w[0], w[1])
    # 1d. flow-insensitivity guard: a local that is assigned from more than one distinct source in its function is a reused temp —
    #     it carries no evidence (m2c's `temp_v0`, `sp10` are reassigned freely); only single-source locals may join two nodes
    src_of = collections.defaultdict(set)
    for r in results.values():
        for f in r["flows"]:
            if f["kind"] in ("assign", "assign&", "ret-of", "field"):
                fk = ident.def_key(f["tu"], f["fn"])
                key = (fk, f["dst"])
                if f["kind"] == "assign":
                    src_of[key].add(("v", f["src"]))
                elif f["kind"] == "assign&":
                    src_of[key].add(("&", f["src"]))
                elif f["kind"] == "ret-of":
                    src_of[key].add(("r", f["callee"]))
                else:
                    src_of[key].add(("f", f["base"], f["off"]))
    single = {k for k, v in src_of.items() if len(v) == 1}
    # 2. evidence edges
    field_edges = []
    for r in results.values():
        for f in r["flows"]:
            fk = ident.def_key(f["tu"], f["fn"])
            if f["kind"] in ("assign", "assign&", "ret-of", "field") and (fk, f["dst"]) not in single:
                uf.veto[f["kind"] + "-multisource"] += 1
                continue
            if f["kind"] in ("arg", "arg&"):
                callee = ident.callee_key(f["tu"], f["callee"])
                pnode = f"P:{callee}:{f['i']}"
                src = ident_node(f["src"], fk) if f["kind"] == "arg" else f"AT:{f['src']}"
                if (callee, f["i"]) not in typed_params:               # a conduit parameter (never dereferenced) is no evidence
                    uf.veto[f["kind"] + "-conduit"] += 1
                elif uf.offs.get(uf.find(src)) and not (uf.structured(pnode) and uf.overlap(src, pnode) >= 1):
                    # both sides carry offsets: merge only on POSITIVE shared evidence (a helper touching one offset admits nothing)
                    uf.veto[f["kind"] + "-no-overlap"] += 1
                else:
                    uf.union(src, pnode, f["kind"])
            elif f["kind"] == "assign":
                uf.union(ident_node(f["dst"], fk), ident_node(f["src"], fk), "assign")
            elif f["kind"] == "assign&":
                uf.union(ident_node(f["dst"], fk), f"AT:{f['src']}", "assign&")
            elif f["kind"] == "ret-of":
                callee = ident.callee_key(f["tu"], f["callee"])
                uf.union(ident_node(f["dst"], fk), f"R:{callee}", "ret-of")
            elif f["kind"] == "return":
                uf.union(ident_node(f["src"], fk), f"R:{fk}", "return")
            elif f["kind"] == "field":
                bnode = base_node(f["base"], f["bclass"], fk)
                field_edges.append((ident_node(f["dst"], fk), bnode, f["off"]))
    # 3. pointer-field flow to a fixpoint: x = base->off  =>  node(x) ~ FLD:<cluster(base)>:off ; a nested site's base is that field
    for _ in range(4):
        changed = False
        for (dst, bnode, off) in field_edges:
            root = uf.find(bnode)
            if uf.union(dst, f"FLD:{root}:{off:#x}", "field"):
                changed = True
        for (i, bnode, off) in nested_sites:
            root = uf.find(bnode)
            node = f"FLD:{root}:{off:#x}"
            s = sites_all[i]
            if s.get("node") != node:
                if s.get("node"):
                    if uf.union(s["node"], node, "nested"):
                        changed = True
                else:
                    s["node"] = node
                    node_sites[node].append(i)
                    uf.find(node)
                    if s.get("index") is None and s.get("width"):
                        uf.add_off(node, s["off"], s["width"], s["sign"])
                    changed = True
        # canonicalize FLD nodes whose root spelling went stale
        for n in [n for n in list(uf.p) if n.startswith("FLD:")]:
            _, oldroot, off = n.split(":", 2)
            base_root = uf.find(oldroot) if oldroot in uf.p else oldroot
            canon = f"FLD:{base_root}:{off}"
            if canon != n and uf.union(n, canon, "field-canon"):
                changed = True
        if not changed:
            break
    # 4. clusters -> types
    clusters = collections.defaultdict(list)
    for node in list(uf.p):
        clusters[uf.find(node)].append(node)
    types = []
    for root, nodes in clusters.items():
        idxs = [i for n in nodes for i in node_sites.get(n, ())]
        if not idxs:
            continue
        offs = collections.defaultdict(collections.Counter)
        fns = set()
        for i in idxs:
            s = sites_all[i]
            fns.add((s["tu"], s["fn"]))
            if s.get("index") is None and s.get("width"):
                offs[s["off"]][(s["width"], s["sign"])] += 1
        # the layout from the sites: one (width, sign) per offset by majority; a WIDTH conflict is recorded (two types, or a
        # reinterpretation); a same-width signedness mix is counted apart (a store's signedness leaves no byte — spelling freedom)
        layout, conflicts, sign_mixed = [], [], 0
        for off in sorted(offs):
            (w, sg), n = offs[off].most_common(1)[0]
            layout.append((off, w, sg, n))
            widths = {a for (a, b) in offs[off]}
            if len(widths) > 1:
                conflicts.append((off, dict((f"{a}{b}", c) for (a, b), c in offs[off].items())))
            elif len(offs[off]) > 1:
                sign_mixed += 1
        # overlapping fields (a u16 at +2 inside an s32 at +0) are conflicts too
        prev_end = -1
        for (off, w, sg, n) in layout:
            if off < prev_end:
                conflicts.append((off, "overlap"))
            prev_end = max(prev_end, off + w)
        globals_ = sorted(n[3:] for n in nodes if n.startswith("AT:"))
        ptr_globals = sorted(n[4:] for n in nodes if n.startswith("PTR:"))
        params = sorted(n for n in nodes if n.startswith("P:"))
        addr = None
        if globals_:
            addr = globals_[0].replace("D_", "")
        else:
            cands = sorted(re.findall(r"func_([0-9A-Fa-f]{8})", " ".join(nodes)))
            addr = cands[0] if cands else None
        types.append(dict(id=root, name=(f"Unkstruct_{addr}" if addr else f"Unkstruct_{hashlib.sha1(root.encode()).hexdigest()[:8]}"),
                          sites=len(idxs), bodies=len(fns), nodes=len(nodes), globals_at=globals_[:20], globals_ptr=ptr_globals[:20],
                          params=len(params), size_hint=(max(o + w for (o, w, _, _) in layout) if layout else 0),
                          fields=len(layout), layout=layout[:400], conflicts=conflicts[:50],
                          evidence=collections.Counter(n.split(":")[0] for n in nodes), sign_mixed=sign_mixed,
                          merges=dict(uf.merges_of.get(root, collections.Counter())),
                          suspect=(len(layout) > 200 or (layout and max(o for (o, _, _, _) in layout) > 0x2000) or len(conflicts) >= 20)))
    types.sort(key=lambda t: -t["sites"])
    return types, uf

def nested_target(text):
    """`*(s32 *)(a0 + 0x20) + 0x1F0` -> ('a0', 'ident'|'global'|…, 0x20): the inner dereference a nested site hangs off."""
    t = text.strip()
    m = FORM_P.match(t) or FORM_M.match(t)
    if not m:
        return None
    if t.startswith("M2C_FIELD"):
        inner, _ = _paren_body(t, t.find("("))
        args = _split_top(inner or "", ",")
        if len(args) != 3:
            return None
        b = parse_base(args[0])
        k = _int(_strip_parens(args[2]))
        if b.get("base") is None or b["bclass"] in ("other", "nested", "member", "addr-of") or k is None:
            return None
        return b["base"], b["bclass"], (b.get("off") or 0) + k
    inner, _ = _paren_body(t, m.end() - 1)
    if inner is None:
        return None
    b = parse_base(inner)
    if b.get("base") is None or b["bclass"] in ("other", "nested", "member", "addr-of") or b.get("index") is not None:
        return None
    return b["base"], b["bclass"], b.get("off") or 0

def site_node(s, ident):
    b = s.get("base")
    bc = s.get("bclass")
    if bc in ("other", "nested", "member", "addr-of", "func") or b is None:
        return None
    fk = ident.def_key(s["tu"], s["fn"]) if s.get("fn") else "X:" + ident.space_of_tu(s["tu"]) + ":<file>"
    return base_node(b, bc, fk)

def base_node(b, bc, fk):
    if bc == "abs":
        return f"AT:{b}"
    if bc == "global":
        return f"PTR:{b}"
    if bc == "gaddr":
        return f"AT:{b}"
    if bc == "param":
        return f"PV:{fk}:{b}"
    if bc == "local":
        return f"L:{fk}:{b}"
    return f"L:{fk}:{b}"

def ident_node(name, fk):
    if name.startswith("D_80"):
        return f"PTR:{name}"
    return f"L:{fk}:{name}"

# ----------------------------------------------------------------------------------------------------------------------
# the census
# ----------------------------------------------------------------------------------------------------------------------
def spaces(tu_aliases):
    """tu -> symbol space: main (root .c), md_<name>, ov (overlays and the shared ov headers), slot_* (resident modules)."""
    def space_of(tu):
        if tu.startswith("src/ov_") or tu.startswith("src/shared/ov/"):
            return "ov"
        if tu.startswith("src/md_"):
            return tu.split("/")[1]
        if tu.startswith("src/shared/main/"):
            return "main"
        if tu.startswith("src/shared/slot_"):
            return tu.split("/")[2]
        als = tu_aliases.get(tu, [])
        if als and all(a.startswith("md_") for a in als):
            return als[0]
        return "main" if not als or "main" in als else als[0]
    return space_of

def run_census(jobs, use_cache=True, out_dir=OUT_DIR_DEFAULT, want_sites=False):
    t0 = time.time()
    aliases, dirs = sc.fleet_and_dirs()
    tu_aliases, headers, orphans = lc.enumerate_files(aliases, dirs)
    if orphans:
        sys.exit(f"type_census: {len(orphans)} .c file(s) under src/ belong to NO binary's source set (R32): {orphans[:6]}")
    inc, inc_tus = lc.header_includers(tu_aliases)
    files = sorted(tu_aliases) + list(headers) + sorted(p.relative_to(REPO).as_posix() for p in (REPO / "include").glob("*.h"))
    cache_p = REPO / out_dir / "cache" / "walk_cache.json"
    cache = {}
    if use_cache and cache_p.exists():
        try:
            cache = json.loads(cache_p.read_text())
        except Exception:
            cache = {}
    keys, work = {}, []
    for rel in files:
        st = (REPO / rel).stat()
        keys[rel] = f"{rel}|{int(st.st_mtime)}|{st.st_size}|{TOOL_STAMP}"
        if keys[rel] not in cache:
            work.append(rel)
    results = {}
    if work:
        with ProcessPoolExecutor(max_workers=jobs) as ex:
            for r in ex.map(_walk_worker, work, chunksize=8):
                results[r["rel"]] = r
    new_cache = {}
    for rel in files:
        r = results.get(rel) or cache.get(keys[rel])
        results[rel] = r
        new_cache[keys[rel]] = r
    if use_cache:
        cache_p.parent.mkdir(parents=True, exist_ok=True)
        cache_p.write_text(json.dumps(new_cache))
    t_walk = time.time() - t0
    space_of = spaces(tu_aliases)
    # ---- shared bodies: fn -> header (one function fleet-wide)
    shared_fn_header = {}
    for h in headers:
        m = re.search(r"/(func_[0-9A-Fa-f]{8})(?:__[0-9a-f]{8}|__t[0-9a-f]{8})?\.h$", h)
        if m:
            shared_fn_header.setdefault(m.group(1), h)
    # ---- 1. definitions
    defs_all = [d for r in results.values() for d in r["definitions"]]
    td_all = [a for r in results.values() for a in r["typedef_aliases"]]
    fwd_all = [f for r in results.values() for f in r["fwd"]]
    # name tables: canonical header first, then the file's own definitions (a TU's own wins for its own layouts)
    global_defs = {}
    for d in defs_all:
        if d["file"].startswith("include/") or d["is_canon"]:
            for n in d["names"] + ([d["tag"]] if d["tag"] else []):
                global_defs.setdefault(n, d)
    for a in td_all:
        if a["file"].startswith("include/") or a["file"] in CANON_HEADERS:
            global_defs.setdefault(a["name"], dict(kind="alias", alias_of=a["alias_of"], alias_stars=a["alias_stars"], alias_dims=a["alias_dims"]))
    by_file_defs = collections.defaultdict(dict)
    for d in defs_all:
        for n in d["names"] + ([d["tag"]] if d["tag"] else []):
            by_file_defs[d["file"]].setdefault(n, d)
    for a in td_all:
        by_file_defs[a["file"]].setdefault(a["name"], dict(kind="alias", alias_of=a["alias_of"], alias_stars=a["alias_stars"], alias_dims=a["alias_dims"]))
    layouts = {}
    unknown_layout = 0
    for d in defs_all:
        scope_defs = dict(global_defs)
        scope_defs.update(by_file_defs[d["file"]])
        res = Resolver(scope_defs)
        if d["kind"] == "enum":
            lay = (4, 4, [(0, 4, "s")])
        else:
            lay = res.layout_of_fields(d["fields"], d["kind"], packed=("packed" in d["attrs"]))
        d["layout"] = lay
        d["lhash"] = layout_hash(lay)
        d["size"] = lay[0] if lay else None
        if lay is None:
            unknown_layout += 1
    # duplicate classes by layout (non-enum, known layout, >= 1 field), exact classes by text
    by_lhash = collections.defaultdict(list)
    by_text = collections.defaultdict(list)
    for d in defs_all:
        if d["kind"] == "enum" or d["lhash"] is None or d["nfields"] == 0:
            continue
        by_lhash[d["lhash"]].append(d)
        by_text[d["text_hash"]].append(d)
    def names_of(d):
        return set(d["names"]) | ({d["tag"]} if d["tag"] else set())
    # duplicate tiers (the Plan agent's stress-test, 2026-09-12): a layout class is ONE type only with evidence beyond the layout —
    #   tier 1: identical meaningful member names (placeholder names `unk*/f*/field_*/pad*/w/b/…` are wildcards)
    #   tier 2: opaque copy blocks (every member a placeholder) — merge by (size, align)
    #   tier 3: layout twins with DIFFERENT meaningful names (`Rect {x,y,w,h}` vs `SVECTOR {vx,vy,vz,pad}`) — NOT duplicates; reported
    def name_sig(f):
        n = f.get("name") or ""
        return "*" if re.match(r"^(?:unk|f|field_?|pad|p|a|b|c|d|w|v|m|t|x|s|u|_|arr|buf|data|val|word|byte|half|tmp|r|q|n)?[0-9A-Fa-fx_]*$", n) else n
    def sig_of(d):
        return tuple(name_sig(f) for f in d["fields"])
    dup_layout_classes, layout_twins = [], []
    for lh, ds in by_lhash.items():
        nm = set()
        for d in ds:
            nm |= names_of(d)
        if len(nm) <= 1:
            continue
        sigs = collections.defaultdict(set)
        for d in ds:
            sg = sig_of(d)
            sigs[("*",) if all(x == "*" for x in sg) else sg] |= names_of(d)
        # tier 1/2 merge: every wildcard-only definition joins the class; distinct meaningful signatures are separate types
        meaningful = {sg: nms for sg, nms in sigs.items() if sg != ("*",)}
        opaque = sigs.get(("*",), set())
        rec = dict(lhash=lh, size=ds[0]["size"], n_names=len(nm), n_defs=len(ds), canon=sum(1 for d in ds if d["is_canon"]),
                   in_c=sum(1 for d in ds if d["file"].endswith(".c")), names=sorted(nm)[:40])
        if len(meaningful) <= 1:
            rec["tier"] = 1 if meaningful else 2
            dup_layout_classes.append(rec)
        else:
            # the opaque names merge with… nothing decidable without flow evidence; each meaningful signature is a type of its own
            rec["tier"] = 3
            rec["camps"] = [sorted(nms)[:6] for sg, nms in meaningful.items()]
            rec["opaque_names"] = sorted(opaque)[:10]
            layout_twins.append(rec)
            # names WITHIN one meaningful camp are still duplicates of each other
            for sg, nms in meaningful.items():
                if len(nms) > 1:
                    dup_layout_classes.append(dict(lhash=lh + ":" + hashlib.sha1(repr(sg).encode()).hexdigest()[:6], size=ds[0]["size"],
                                                   n_names=len(nms), n_defs=sum(1 for d in ds if sig_of(d) == sg), canon=0, in_c=0,
                                                   names=sorted(nms)[:40], tier=1))
            if len(opaque) > 1:
                dup_layout_classes.append(dict(lhash=lh + ":opaque", size=ds[0]["size"], n_names=len(opaque), n_defs=0, canon=0, in_c=0,
                                               names=sorted(opaque)[:40], tier=2))
    dup_layout_classes.sort(key=lambda c: -c["n_names"])
    layout_twins.sort(key=lambda c: -c["n_names"])
    exact_classes = {th: len(ds) for th, ds in by_text.items() if len(ds) > 1}
    # VARIANT camps: one name, >1 layout
    name_layouts = collections.defaultdict(set)
    name_defs = collections.defaultdict(int)
    for d in defs_all:
        if d["kind"] == "enum":
            continue
        for n in names_of(d):
            name_defs[n] += 1
            if d["lhash"]:
                name_layouts[n].add(d["lhash"])
    variants = sorted(((n, len(ls)) for n, ls in name_layouts.items() if len(ls) > 1), key=lambda x: -x[1])
    # dead names (canonical header names with no use anywhere else): a use = the name as a token outside its own definition
    canon_names = set()
    for d in defs_all:
        if d["is_canon"]:
            canon_names |= names_of(d)
    uses = collections.Counter()
    for r in results.values():
        if r["rel"] in CANON_HEADERS:
            continue
        for n, k in r.get("ident_counts", {}).items():
            if n in canon_names:
                uses[n] += k
    dead = sorted(n for n in canon_names if uses[n] == 0)
    in_c_defs = [d for d in defs_all if d["file"].endswith(".c")]
    shadow = sorted({n for d in in_c_defs for n in names_of(d) if n in canon_names})
    # ---- 2. sites
    sites_all = []
    raw_counts = collections.Counter()
    for rel in files:
        r = results[rel]
        for s in r["sites"]:
            s["space"] = space_of(rel)
            s["header"] = rel.endswith(".h")
            sites_all.append(s)
        raw_counts.update(r["raw_counts"])
    by_form = collections.Counter(s["form"] for s in sites_all)
    coverage_ok = all(by_form[f] == raw_counts[f] for f in ("P", "I", "X", "M", "A", "C"))
    refused = [s for s in sites_all if s.get("refused")]
    RAW_FORMS = ("P", "I", "X", "M")           # the raw dereference forms — the phase's counter; A (address-of) and C (typed cast-member) are counted apart
    by_bclass = collections.Counter(s["bclass"] for s in sites_all if s["form"] in RAW_FORMS)
    by_width = collections.Counter(f"{s['sign']}{s['width']}" if s.get("width") else str(s.get("sign")) for s in sites_all if s["form"] in RAW_FORMS)
    top_bases = collections.Counter((s["bclass"], s["base"]) for s in sites_all if s["form"] in RAW_FORMS and s.get("base")).most_common(40)
    deref_sites = [s for s in sites_all if s["form"] in RAW_FORMS]
    bodies_with_sites = len({(s["tu"], s["fn"]) for s in deref_sites if s.get("fn")})
    # the readability series' own regex over the RAW text (continuity with docs/readability-progress.tsv)
    import readability_progress as rp
    raw_readability = 0
    for rel in files:
        if rel.startswith("include/"):
            continue
        raw_readability += len(rp.CAST.findall((REPO / rel).read_text(errors="surrogateescape")))
    # ---- 3. declarations
    fndefs = [f for r in results.values() for f in r["fndefs"]]
    extern_fns = [e for r in results.values() for e in r["extern_fns"]]
    extern_data = [e for r in results.values() for e in r["extern_data"]]
    asm_aliases = [a for r in results.values() for a in r["asm_aliases"]]
    builtins = collections.Counter(b["name"] for r in results.values() for b in r["builtins"])
    attrs = collections.Counter(a["name"] for r in results.values() for a in r["attrs"])
    spellings = collections.defaultdict(set)
    for e in extern_fns:
        spellings[e["name"]].add(e["params"])
    multi_spelled = sum(1 for n, s in spellings.items() if len(s) > 1)
    # definitions per name: same name, different body text across TUs (the cross-address / h_text classes)
    def_texts = collections.defaultdict(set)
    for f in fndefs:
        def_texts[f["fn"]].add(f["nhash"])
    multi_body = sum(1 for n, s in def_texts.items() if len(s) > 1)
    data_types = collections.defaultdict(set)
    for e in extern_data:
        data_types[e["name"]].add(e["type"] + e["dims"])
    multi_typed_data = sum(1 for n, s in data_types.items() if len(s) > 1)
    # the lying set (argcheck as a library)
    import argcheck
    ac_defs = argcheck.definitions()
    lying = argcheck.scan(ac_defs, only_needed_argpins=False)
    lying_kinds = collections.Counter(r["kind"] for r in lying)
    lying_callees = len({r["callee"] for r in lying})
    t_decl = time.time() - t0
    # ---- 3b. global blocks: runs of adjacent D_ symbols (address + declared width == the next address) — record candidates
    decl_w = collections.defaultdict(collections.Counter)
    for e in extern_data:
        w = scalar_of(e["type"])
        if w and w[0] > 0:
            if e["dims"]:
                dims = [_eval_dim(x, {}) for x in re.findall(r"\[([^\]]*)\]", e["dims"])]
                if all(dims) and dims:
                    n = 1
                    for x in dims:
                        n *= x
                    decl_w[e["name"]][w[0] * n] += 1
            else:
                decl_w[e["name"]][w[0]] += 1
    syms = []
    for name, cnt in decl_w.items():
        m = re.match(r"^D_(80[0-9A-Fa-f]{6})$", name)
        if m:
            syms.append((int(m.group(1), 16), name, cnt.most_common(1)[0][0]))
    syms.sort()
    global_blocks, run = [], []
    for addr, name, w in syms:
        if run and addr == run[-1][0] + run[-1][2]:
            run.append((addr, name, w))
        else:
            if len(run) >= 4:
                global_blocks.append(dict(base=f"{run[0][0]:#x}", size=run[-1][0] + run[-1][2] - run[0][0], members=len(run),
                                          first=run[0][1], last=run[-1][1], widths=dict(collections.Counter(w for _, _, w in run))))
            run = [(addr, name, w)]
    if len(run) >= 4:
        global_blocks.append(dict(base=f"{run[0][0]:#x}", size=run[-1][0] + run[-1][2] - run[0][0], members=len(run), first=run[0][1], last=run[-1][1],
                                  widths=dict(collections.Counter(w for _, _, w in run))))
    global_blocks.sort(key=lambda b: -b["members"])
    # ---- 4. the struct map
    ident = Identity(fndefs, tu_aliases, space_of, shared_fn_header)
    types, uf = build_struct_map(results, tu_aliases, space_of, shared_fn_header, sites_all, ident)
    explained = sum(t["sites"] for t in types)
    unassigned = sum(1 for s in deref_sites if s.get("node") is None)
    # ---- 5. controls
    ctrl = controls(defs_all, sites_all, extern_data, by_text, name_layouts)
    parked = write_parked(out_dir)
    # ---- render + write
    summary = dict(
        head=lc.git_head(), src_stamp=lc.src_stamp(), tool_stamp=TOOL_STAMP, when=time.strftime("%Y-%m-%dT%H:%M:%SZ", time.gmtime()),
        files=len(files), tus=len(tu_aliases), headers=len(headers), functions=sum(r["nfuncs"] for r in results.values()),
        definitions=dict(total=len([d for d in defs_all if d["kind"] != "enum"]), enums=sum(1 for d in defs_all if d["kind"] == "enum"),
                         canon=sum(1 for d in defs_all if d["is_canon"] and d["kind"] != "enum"),
                         in_c_file_scope=sum(1 for d in in_c_defs if d["scope"] == "file" and d["kind"] != "enum"),
                         in_c_block_scope=sum(1 for d in in_c_defs if d["scope"] == "block" and d["kind"] != "enum"),
                         in_shared_fn_headers=sum(1 for d in defs_all if d["file"].startswith("src/shared/") and not d["is_canon"] and d["kind"] != "enum"),
                         in_include=sum(1 for d in defs_all if d["file"].startswith("include/") and d["kind"] != "enum"),
                         other_headers=sum(1 for d in defs_all if d["file"].endswith(".h") and not d["is_canon"] and not d["file"].startswith(("include/", "src/shared/")) and d["kind"] != "enum"),
                         distinct_names=len(name_defs), distinct_layouts=len(by_lhash), unknown_layout=unknown_layout,
                         dup_layout_classes=len(dup_layout_classes), dup_layout_names=sum(c["n_names"] for c in dup_layout_classes),
                         dup_tier1=sum(1 for c in dup_layout_classes if c["tier"] == 1), dup_tier2=sum(1 for c in dup_layout_classes if c["tier"] == 2),
                         layout_twin_classes=len(layout_twins), layout_twin_names=sum(c["n_names"] for c in layout_twins),
                         exact_classes=len(exact_classes), exact_copies=sum(exact_classes.values()),
                         variant_names=len(variants), dead_canon_names=len(dead), shadowed_canon_names=len(shadow),
                         typedef_aliases=len(td_all), forward_decls=len(fwd_all)),
        casts=dict(by_form=dict(by_form), raw_counts=dict(raw_counts), coverage_ok=coverage_ok, refused=len(refused),
                   deref_total=len(deref_sites), addr_form=by_form["A"], typed_cast_member=by_form["C"], bodies=bodies_with_sites,
                   by_bclass=dict(by_bclass), by_width=dict(by_width.most_common()), readability_raw_regex=raw_readability,
                   abs_casts=by_bclass.get("abs", 0), top_bases=[[bc, b, n] for ((bc, b), n) in top_bases]),
        decls=dict(fn_definitions=len(fndefs), kr_definitions=sum(1 for f in fndefs if f["kr"]), extern_fn_decls=len(extern_fns),
                   extern_data_decls=len(extern_data), declared_fn_names=len(spellings), multi_spelled_callees=multi_spelled,
                   multi_body_names=multi_body, data_symbols_declared=len(data_types), multi_typed_data_symbols=multi_typed_data,
                   asm_label_aliases=len(asm_aliases), asm_label_alias_names=len({a["name"] for a in asm_aliases}),
                   builtins=dict(builtins), attributes=dict(attrs),
                   lying=len(lying), lying_callees=lying_callees, lying_kinds=dict(lying_kinds)),
        struct_map=dict(types=len(types), explained_sites=explained, deref_sites=len(deref_sites),
                        explained_pct=round(100.0 * explained / max(1, len(deref_sites)), 1), unassigned_sites=unassigned,
                        conflicts=sum(1 for t in types if t["conflicts"]), suspect=sum(1 for t in types if t.get("suspect")),
                        evidence=dict(uf.ev), vetoed=dict(uf.veto),
                        singletons=sum(1 for t in types if t["bodies"] == 1), multi_body=sum(1 for t in types if t["bodies"] >= 2),
                        sites_in_multi_body=sum(t["sites"] for t in types if t["bodies"] >= 2),
                        top=[dict(name=t["name"], sites=t["sites"], bodies=t["bodies"], size_hint=t["size_hint"], fields=t["fields"],
                                  conflicts=len(t["conflicts"]), sign_mixed=t["sign_mixed"], merges=t["merges"],
                                  globals_at=t["globals_at"][:3], globals_ptr=t["globals_ptr"][:3]) for t in types[:25]]),
        controls=ctrl,
        global_blocks=dict(n=len(global_blocks), members=sum(b["members"] for b in global_blocks), top=global_blocks[:15]),
        parked=parked,
        timing=dict(walk_s=round(t_walk, 1), decls_s=round(t_decl, 1), total_s=round(time.time() - t0, 1)),
    )
    out = REPO / out_dir
    out.mkdir(parents=True, exist_ok=True)
    (out / "type_census.json").write_text(json.dumps(dict(summary=summary, dup_layout_classes=dup_layout_classes[:300], layout_twins=layout_twins[:100],
                                                             variants=variants[:200], dead=dead, shadow=shadow,
                                                             refused=[dict(tu=s["tu"], line=s["line"], text=s.get("text"), why=s.get("refused")) for s in refused[:200]]),
                                                        indent=1))
    (out / "struct_map.json").write_text(json.dumps(dict(head=summary["head"], types=[dict(t, evidence=dict(t["evidence"])) for t in types]), indent=None))
    # the tracked, compact form: the 300 largest types with their layouts capped at 64 fields (the full map is regenerable)
    (out / "struct_map_top.json").write_text(json.dumps(dict(head=summary["head"], when=summary["when"], n_types=len(types),
                                                             types=[dict(t, evidence=dict(t["evidence"]), layout=t["layout"][:64], conflicts=t["conflicts"][:12]) for t in types[:300]]), indent=None))
    if want_sites:
        with (out / "sites.jsonl").open("w") as fh:
            for s in sites_all:
                fh.write(json.dumps(s) + "\n")
    txt = render(summary, dup_layout_classes, variants, types)
    (out / "type_census.txt").write_text(txt)
    render_struct_map_md(summary, types, REPO / "docs" / "struct-map.md")
    return summary, txt

# ----------------------------------------------------------------------------------------------------------------------
# the Phase-36 inheritance: the parked classes, in ONE file with their reasons (the record had none — the reasons were split
# across the S104/S105 log prose, the bank lists' MSG column and each pack's mechanism.md)
# ----------------------------------------------------------------------------------------------------------------------
PICK_PY = REPO / ".run/P36/s105/pick.py"
PACKS = REPO / ".run/P36/agents"
NEEDS_RX = [("signature", re.compile(r"signature|prototype|\(void\)|returns? the|return type|parameter", re.I)),
            ("carve", re.compile(r"\bcarve", re.I)), ("gte", re.compile(r"gte_|stORGB|GTE", re.I)),
            ("struct", re.compile(r"\bstruct|\bunion|array|record", re.I)), ("irreducible", re.compile(r"irreducib|PERMANENT|proven.*plain C|NOT closed", re.I))]

def park_set():
    if PICK_PY.exists():
        m = re.search(r'PARK = set\("""(.*?)"""\.split\(\)\)', PICK_PY.read_text(), re.S)
        if m:
            return set(m.group(1).split())
    return set()

def pack_headline(alias, fn):
    d = PACKS / f"{alias}__{fn}"
    if not d.is_dir():
        # the pack may live under another overlay's alias (the same body): find any pack for the fn
        cands = sorted(PACKS.glob(f"*__{fn}"))
        if not cands:
            return None, None, []
        d = cands[0]
    mech = d / "mechanism.md"
    head = None
    body = ""
    if mech.exists():
        body = mech.read_text(errors="replace")
        for ln in body.split("\n")[1:12]:
            t = ln.strip()
            if t and not t.startswith("#"):
                head = re.sub(r"\s+", " ", t)[:220]
                break
    if head is not None:
        head = head + " ||| " + re.sub(r"\s+", " ", body[:6000])      # the needs classifier reads the whole note; the TSV keeps the headline
    patches = sorted(str(x.relative_to(REPO)) for x in list(d.glob("scratch/*patch*")) + list(d.glob("*.diff")) + list(d.glob("scratch/*.diff")) + list(d.glob("scratch/signature*")))
    return str(d.relative_to(REPO)), head, patches

def write_parked(out_dir):
    try:
        import delever_search as ds
    except Exception as e:      # the P36 ledger machinery is optional for the census proper
        return dict(error=str(e))
    park = park_set()
    if not park:
        return dict(error="no PARK set found in .run/P36/s105/pick.py")
    ex = ds.exemplars(include_done=True)
    rows = []
    seen_fn = set()
    for e in ex:
        if e["fn"] not in park:
            continue
        seen_fn.add(e["fn"])
        pack, head, patches = pack_headline(e["alias"], e["fn"])
        full = head or ""
        head = full.split(" ||| ")[0] if head else head
        needs = next((k for k, rx in NEEDS_RX if full and rx.search(full)), "?")
        rows.append(dict(fn=e["fn"], alias=e["alias"], tu=e["tu"], copies=e["copies"], sites=e["needed"] * e["copies"], needed_per_copy=e["needed"],
                         kinds=",".join(e["kinds"]), regs=" ".join(e["regs"]), needs=needs, pack=pack or "", patches=";".join(patches), headline=head or ""))
    rows.sort(key=lambda r: (-r["sites"], r["fn"]))
    banked = sorted(park - seen_fn)         # PARK names whose latest ledger verdict is not RESIDUE: minimum-lever banks (their marked sites stay)
    out = REPO / out_dir / "parked.tsv"
    with out.open("w") as fh:
        fh.write("# .run/P37/census/parked.tsv — the Phase-36 parked classes, in one file with their reasons (type_census.write_parked; generated).\n")
        fh.write("# A RESIDUE class of the P36 ledger whose exemplar is in .run/P36/s105/pick.py's PARK set; `needs` is read from the pack's mechanism.md headline\n")
        fh.write("# (signature | carve | gte | struct | irreducible | ?); `patches` lists the ready patch files. The second block lists PARK names whose latest\n")
        fh.write("# ledger verdict is LEVER-FREE (a minimum-lever bank — its surviving marked sites are counted by lever_census, not here).\n")
        fh.write("fn\talias\ttu\tcopies\tsites\tneeded_per_copy\tkinds\tregs\tneeds\tpack\tpatches\theadline\n")
        for r in rows:
            fh.write("\t".join(str(r[k]) for k in ("fn", "alias", "tu", "copies", "sites", "needed_per_copy", "kinds", "regs", "needs", "pack", "patches", "headline")) + "\n")
        fh.write("# minimum-lever banks in PARK (LEVER-FREE in the ledger): " + " ".join(banked) + "\n")
    return dict(classes=len(rows), bodies=sum(r["copies"] for r in rows), sites=sum(r["sites"] for r in rows),
                needs=dict(collections.Counter(r["needs"] for r in rows)), minimum_lever_banks=len(banked), path=str(out.relative_to(REPO)))

# ----------------------------------------------------------------------------------------------------------------------
# controls (R39)
# ----------------------------------------------------------------------------------------------------------------------
PLAYER_BLOCK = {  # docs/actor-struct.md + docs/memory-map.md §3.4 — the widths BOTH the record and the matched code agree on
    "D_80078E8C": 4, "D_80078EB2": 2, "D_80078EB4": 2, "D_80078EB6": 2, "D_80078EB8": 2}
PLAYER_BLOCK_DOC_DISPUTED = {"D_80078F08": 2, "D_80078F0C": 2}   # actor-struct.md says s16 at +0x108/+0x10C; the tree's byte-true declarations decide (reported, not asserted)

def controls(defs_all, sites_all, extern_data, by_text, name_layouts):
    out = {}
    # 1. the player block: the fleet's declared width per symbol agrees with the live-verified width
    decl_w = collections.defaultdict(collections.Counter)
    for e in extern_data:
        w = scalar_of(e["type"])
        if w and not e["dims"]:
            decl_w[e["name"]][w[0]] += 1
    ok, detail = True, []
    for sym, w in PLAYER_BLOCK.items():
        got = decl_w.get(sym)
        maj = got.most_common(1)[0][0] if got else None
        detail.append(f"{sym}:{maj if maj else '-'}/{w}")
        if maj != w:
            ok = False
    for sym, w in PLAYER_BLOCK_DOC_DISPUTED.items():
        got = decl_w.get(sym)
        maj = got.most_common(1)[0][0] if got else None
        detail.append(f"[doc-disputed {sym}: code {maj if maj else '-'} vs actor-struct.md {w}]")
    out["player_block_widths"] = dict(ok=ok, detail=" ".join(detail))
    # 2. MATRIX (32) vs MATRIX_L48 (48): two layouts
    def size_of(name):
        for d in defs_all:
            if d["is_canon"] and (name in d["names"] or d["tag"] == name):
                return d["size"]
        return None
    m32, m48 = size_of("MATRIX"), size_of("MATRIX_L48")
    out["matrix_layouts"] = dict(ok=(m32 == 32 and m48 == 48), detail=f"MATRIX={m32} MATRIX_L48={m48}")
    # 3. Prim_8016E7C8 (defined in ~1,192 .c files under two spellings): ONE layout class covers every definition
    prim_defs = [d for d in defs_all if "Prim_8016E7C8" in d["names"] or d["tag"] == "Prim_8016E7C8"]
    prim_files = len({d["file"] for d in prim_defs})
    prim_lh = collections.Counter(d["lhash"] for d in prim_defs)
    prim_texts = len({d["text_hash"] for d in prim_defs})
    top_lh, top_n = (prim_lh.most_common(1)[0] if prim_lh else (None, 0))
    out["prim_layout_class"] = dict(ok=(prim_files > 1000 and top_n == len(prim_defs) and top_lh is not None),
                                    detail=f"defs in {prim_files} files, {prim_texts} spellings, {top_n}/{len(prim_defs)} in one layout ({prim_defs[0]['size'] if prim_defs else None} B)")
    # 4. a TU-CONFLICT ledger row reproduced: D_800A651C is declared with more than one type across TUs
    types = collections.Counter(e["type"] + e["dims"] for e in extern_data if e["name"] == "D_800A651C")
    out["tu_conflict_D_800A651C"] = dict(ok=(len(types) > 1), detail=" | ".join(f"{t}:{n}" for t, n in types.most_common(5)))
    out["ok"] = sum(1 for k, v in out.items() if isinstance(v, dict) and v.get("ok"))
    out["n"] = 4
    return out

# ----------------------------------------------------------------------------------------------------------------------
# rendering
# ----------------------------------------------------------------------------------------------------------------------
def render(s, dup_classes, variants, types):
    d, c, dc, sm = s["definitions"], s["casts"], s["decls"], s["struct_map"]
    L = []
    L.append(f"type_census — {s['when']} at {s['head']} (src stamp {s['src_stamp']}, tool {s['tool_stamp']}); {s['files']} files "
             f"({s['tus']} TUs + {s['headers']} headers), {s['functions']} function definitions; walk {s['timing']['walk_s']} s, total {s['timing']['total_s']} s")
    L.append("")
    L.append(f"DEFINITIONS  {d['total']} struct/union bodies (+{d['enums']} enums): canonical header {d['canon']} · .c file-scope {d['in_c_file_scope']} · "
             f".c block-scope {d['in_c_block_scope']} · per-function shared headers {d['in_shared_fn_headers']} · other headers {d['other_headers']} · include/ {d['in_include']}")
    L.append(f"             {d['distinct_names']} distinct names · {d['distinct_layouts']} distinct layouts ({d['unknown_layout']} unresolved) · "
             f"{d['dup_layout_classes']} duplicate classes covering {d['dup_layout_names']} names (tier 1 {d['dup_tier1']} same-named, tier 2 {d['dup_tier2']} opaque; "
             f"{d['layout_twin_classes']} layout-twin classes / {d['layout_twin_names']} names kept apart) · {d['exact_classes']} exact-text classes / {d['exact_copies']} copies · "
             f"{d['variant_names']} VARIANT names (>1 layout) · {d['dead_canon_names']} dead canonical names · {d['shadowed_canon_names']} canonical names redefined in .c · "
             f"{d['typedef_aliases']} scalar/alias typedefs · {d['forward_decls']} forward decls")
    L.append(f"CAST SITES   deref {c['deref_total']} = P {c['by_form'].get('P',0)} + I {c['by_form'].get('I',0)} + X {c['by_form'].get('X',0)} + M {c['by_form'].get('M',0)}"
             f"   (+ A address-of {c['addr_form']}; + C typed cast-member {c['typed_cast_member']}) in {c['bodies']} bodies · coverage {'OK' if c['coverage_ok'] else 'FAIL'} (raw {c['raw_counts']}) · refused {c['refused']} · "
             f"absolute {c['abs_casts']} · readability regex over raw text {c['readability_raw_regex']}")
    L.append(f"             by base: " + " · ".join(f"{k} {v}" for k, v in sorted(c['by_bclass'].items(), key=lambda x: -x[1])))
    L.append(f"             by width: " + " · ".join(f"{k} {v}" for k, v in list(c['by_width'].items())[:10]))
    L.append(f"             top bases: " + " · ".join(f"{b}({bc}) {n}" for bc, b, n in c['top_bases'][:16]))
    L.append(f"DECLARATIONS {dc['fn_definitions']} function definitions ({dc['kr_definitions']} K&R) · {dc['extern_fn_decls']} extern function declarations over "
             f"{dc['declared_fn_names']} names ({dc['multi_spelled_callees']} spelled >1 way) · {dc['multi_body_names']} names with >1 body text · "
             f"{dc['extern_data_decls']} data externs over {dc['data_symbols_declared']} symbols ({dc['multi_typed_data_symbols']} typed >1 way) · "
             f"asm-label aliases {dc['asm_label_aliases']} ({dc['asm_label_alias_names']} names) · builtins {dc['builtins']} · attributes {dc['attributes']}")
    L.append(f"             lying declarations {dc['lying']} over {dc['lying_callees']} callees {dc['lying_kinds']}")
    L.append(f"STRUCT MAP   {sm['types']} types explain {sm['explained_sites']}/{sm['deref_sites']} deref sites ({sm['explained_pct']} %); unassigned {sm['unassigned_sites']}; "
             f"{sm['multi_body']} types span ≥2 bodies ({sm['sites_in_multi_body']} sites), {sm['singletons']} single-body; types with conflicts {sm['conflicts']}, suspect {sm['suspect']}")
    L.append(f"             merges by evidence {sm['evidence']}; vetoed {sm['vetoed']}")
    for t in sm["top"][:12]:
        L.append(f"             {t['name']:<22} sites {t['sites']:>7} bodies {t['bodies']:>6} fields {t['fields']:>4} size≥{t['size_hint']:#x} width-conflicts {t['conflicts']} sign-mixed {t['sign_mixed']} "
                 f"merges {dict(sorted(t['merges'].items(), key=lambda x: -x[1])[:4])} {'at ' + ','.join(t['globals_at']) if t['globals_at'] else ''}{' ptr ' + ','.join(t['globals_ptr']) if t['globals_ptr'] else ''}")
    gb = s["global_blocks"]
    L.append(f"GLOBAL BLOCKS {gb['n']} runs of ≥4 adjacent scalar D_ symbols ({gb['members']} symbols): " +
             " · ".join(f"{b['base']}+{b['size']:#x} ×{b['members']} ({b['first']}..{b['last']})" for b in gb["top"][:8]))
    pk = s.get("parked") or {}
    if pk.get("error"):
        L.append(f"PARKED (P36)  not written: {pk['error']}")
    else:
        L.append(f"PARKED (P36)  {pk['classes']} classes / {pk['bodies']} bodies / {pk['sites']} needed sites → {pk['path']}; needs {pk['needs']}; "
                 f"{pk['minimum_lever_banks']} PARK names are minimum-lever banks")
    L.append(f"CONTROLS     {s['controls']['ok']}/{s['controls']['n']}: " + " · ".join(f"{k} {'OK' if v['ok'] else 'FAIL'} ({v['detail']})" for k, v in s['controls'].items() if isinstance(v, dict)))
    L.append("")
    L.append("duplicate-layout classes (top 12): " + " | ".join(f"{cl['size']}B×{cl['n_names']} names ({cl['n_defs']} defs): {', '.join(cl['names'][:4])}…" for cl in dup_classes[:12]))
    L.append("VARIANT names (top 12): " + ", ".join(f"{n}×{k}" for n, k in variants[:12]))
    L.append("")
    L.append(f"type_census: {d['total']} definitions ({d['distinct_layouts']} layouts, {d['dup_layout_classes']} duplicate classes, {d['variant_names']} variant camps) · "
             f"{c['deref_total']} cast sites in {c['bodies']} bodies over {len(c['by_bclass'])} base classes (4 forms + A, coverage {'OK' if c['coverage_ok'] else 'FAIL'}) · "
             f"{dc['lying']} lying declarations / {dc['lying_callees']} callees · controls {s['controls']['ok']}/{s['controls']['n']}")
    L.append(f"struct_map: {sm['types']} types over {sum(1 for _ in [0])*0 + sm['types']} clusters explain {sm['explained_sites']}/{sm['deref_sites']} sites ({sm['explained_pct']} %); "
             f"{sm['unassigned_sites']} unassigned sites; {sm['conflicts']} types with conflicts")
    return "\n".join(L) + "\n"

def render_struct_map_md(s, types, path):
    sm = s["struct_map"]
    L = [f"# The struct map — the types the fleet's cast sites need (Phase 37 T1)", "",
         f"> **Generated by `tools/type_census.py` at `{s['head']}` ({s['when']}); never typed (R75).** Every raw pointer-cast dereference in "
         f"`src/` was assigned to a base (a parameter, a local, a global by value or by address, an absolute address) and the bases were clustered "
         f"by EVIDENCE only — the same global symbol, an argument passed to a callee's parameter, an assignment or return, a pointer field read, "
         f"a shared body's fleet-wide identity — never by a similar offset signature. Each cluster is one type the tree needs. Names are "
         f"placeholders (`Unkstruct_<addr>`: the lowest global instance's address, else the lowest member function's); fields are placeholders "
         f"(`unk<HEX>`) until Phase 38 cites evidence.", "",
         f"**{sm['types']} types explain {sm['explained_sites']} of {sm['deref_sites']} dereference sites ({sm['explained_pct']} %); "
         f"{sm['unassigned_sites']} sites have a base the census could not classify; {sm['conflicts']} types carry a width conflict.** "
         f"Merges by evidence: {', '.join(f'{k} {v}' for k, v in sorted(sm['evidence'].items(), key=lambda x: -x[1]))}.", "",
         "| # | type | sites | bodies | fields | size ≥ | width conflicts (+sign mixes) | instance globals | pointer globals |", "|---:|---|---:|---:|---:|---:|---:|---|---|"]
    for i, t in enumerate(types[:200], 1):
        L.append(f"| {i} | `{t['name']}` | {t['sites']} | {t['bodies']} | {t['fields']} | {t['size_hint']:#x} | {len(t['conflicts'])} (+{t['sign_mixed']} sign) | "
                 f"{', '.join(t['globals_at'][:4])}{'…' if len(t['globals_at']) > 4 else ''} | {', '.join(t['globals_ptr'][:4])}{'…' if len(t['globals_ptr']) > 4 else ''} |")
    L.append("")
    L.append(f"*{len(types)} types in all; the table shows the 200 largest by site count. The full map with every type's layout "
             f"(offset, width, sign, site count per field) and conflicts is `.run/P37/census/struct_map.json`.*")
    path.write_text("\n".join(L) + "\n")

# ----------------------------------------------------------------------------------------------------------------------
# selftest
# ----------------------------------------------------------------------------------------------------------------------
FIXTURE = r'''#include "common.h"
typedef struct { s16 vx, vy, vz, pad; } SV_a;           /* 8 bytes */
typedef struct { short vx; short vy; short vz; short pad; } SV_b;   /* the same layout under another name */
typedef struct { s32 w[8]; } Blk32_x;                    /* 32 bytes */
struct Rec { u8 a; u16 b; s32 c; u8 d[3]; };             /* 0,2,4,8..10 -> size 12 */
typedef struct { s16 : 16; u16 f; } BF;                  /* a pad bitfield then a u16 -> size 4 */
typedef struct Node { struct Node *next; s32 v; } Node;
typedef void (*Handler)(s32);
extern u16 D_80078EB4;
extern s32 func_80001000(s32 a0, s16 *p);
extern void func_80002000();
void f1(s32 a0, s32 *b, s32 c) {
    s32 x;
    *(u16 *)(a0 + 0x3C) = 5;                    /* P store, param, +0x3C u16 */
    x = *(s32 *)(a0 + 0x20);                    /* P load  -> pointer field flow */
    *(s16 *)((s32)b + 0x08) += 1;               /* P rmw, inner cast */
    *(u8 *)D_80078EB4 = 1;                      /* I store, global by value */
    *(u32 *)&D_80078EB4 = 2;                    /* I, global by address */
    ((s16 *)a0)[3] = 7;                         /* X -> offset 6 */
    M2C_FIELD(a0, u8 *, 0x41) = 0;              /* M store */
    func_80001000(a0, (s16 *)(x + 0x10));       /* arg flow a0 -> P:func_80001000:0 ; A form on x */
    *(s32 *)(*(s32 *)(a0 + 0x20) + 0x1F0) = 0;  /* nested */
    *(s16 *)0x800A1234 = 0;                     /* absolute */
    ((Node *)a0)->unk3C = 1;                    /* C: cast-then-member */
}
'''

def selftest():
    res = walk_file(FIXTURE, "src/ov_TEST/t.c")
    defs = {n: d for d in res["definitions"] for n in d["names"] + ([d["tag"]] if d["tag"] else [])}
    r = Resolver(dict(defs))
    checks = []
    checks.append(("SV_a size 8", r.resolve_name("SV_a")[0] == 8))
    checks.append(("SV_a == SV_b layout", layout_hash(r.resolve_name("SV_a")) == layout_hash(r.resolve_name("SV_b"))))
    checks.append(("Blk32_x size 32", r.resolve_name("Blk32_x")[0] == 32))
    checks.append(("struct Rec size 12", r.resolve_name("Rec")[0] == 12))
    checks.append(("BF size 4", r.resolve_name("BF")[0] == 4))
    checks.append(("Node size 8", r.resolve_name("Node")[0] == 8))
    forms = collections.Counter(s["form"] for s in res["sites"])
    checks.append(("forms P5 I3 X1 M1 A1 C1", (forms["P"], forms["I"], forms["X"], forms["M"], forms["A"], forms["C"]) == (5, 3, 1, 1, 1, 1)))
    checks.append(("C member", [s for s in res["sites"] if s["form"] == "C"][0]["member"] == "unk3C"))
    checks.append(("coverage", dict(forms) == {k: v for k, v in res["raw_counts"].items()}))
    p = [s for s in res["sites"] if s["form"] == "P"]
    checks.append(("P0 param +0x3C u16 store", p[0]["bclass"] == "param" and p[0]["off"] == 0x3C and p[0]["width"] == 2 and p[0]["access"] == "store"))
    checks.append(("P2 inner cast rmw", p[2]["inner_cast"] == "s32" and p[2]["access"] == "rmw" and p[2]["off"] == 8))
    checks.append(("P3 nested", p[3]["bclass"] == "nested"))
    checks.append(("I2 abs", [s for s in res["sites"] if s["form"] == "I"][2]["bclass"] == "abs"))
    i_ = [s for s in res["sites"] if s["form"] == "I"]
    checks.append(("I global / gaddr", i_[0]["bclass"] == "global" and i_[1]["bclass"] == "gaddr"))
    x = [s for s in res["sites"] if s["form"] == "X"][0]
    checks.append(("X offset 6", x["off"] == 6 and x["bclass"] == "param"))
    m = [s for s in res["sites"] if s["form"] == "M"][0]
    checks.append(("M off 0x41 store", m["off"] == 0x41 and m["access"] == "store" and m["width"] == 1))
    fl = res["flows"]
    checks.append(("arg flow", any(f["kind"] == "arg" and f["src"] == "a0" and f["callee"] == "func_80001000" and f["i"] == 0 for f in fl)))
    checks.append(("field flow", any(f["kind"] == "field" and f["dst"] == "x" and f["off"] == 0x20 for f in fl)))
    checks.append(("K&R-empty extern", any(e["name"] == "func_80002000" and e["params"] == "" for e in res["extern_fns"])))
    checks.append(("typedef alias fnptr", any(a["name"] == "Handler" and a["fnptr"] for a in res["typedef_aliases"])))
    checks.append(("params of f1", res["fndefs"][0]["pnames"] == ["a0", "b", "c"]))
    bad = [n for n, ok in checks if not ok]
    print(f"type_census --selftest: {len(checks) - len(bad)}/{len(checks)} checks OK" + (f"; FAILED: {bad}" if bad else ""))
    return 0 if not bad else 1

# ----------------------------------------------------------------------------------------------------------------------
def main():
    ap = argparse.ArgumentParser(description=__doc__.split("\n")[0])
    ap.add_argument("-j", "--jobs", type=int, default=os.cpu_count() or 4)
    ap.add_argument("--out-dir", default=OUT_DIR_DEFAULT)
    ap.add_argument("--no-cache", action="store_true")
    ap.add_argument("--sites", action="store_true", help="also write sites.jsonl")
    ap.add_argument("--check", action="store_true", help="T8's gate (the invariants; exit 1 on a violation)")
    ap.add_argument("--selftest", action="store_true")
    ap.add_argument("--quiet", action="store_true")
    a = ap.parse_args()
    if a.selftest:
        sys.exit(selftest())
    summary, txt = run_census(a.jobs, use_cache=not a.no_cache, out_dir=a.out_dir, want_sites=a.sites)
    if a.quiet:
        print(txt.strip().split("\n")[-2])
        print(txt.strip().split("\n")[-1])
    else:
        print(txt)
    rc = 0
    if not summary["casts"]["coverage_ok"]:
        print("type_census: COVERAGE FAIL — a form's recorded sites != its raw regex count (R32)", file=sys.stderr)
        rc = 1
    if summary["controls"]["ok"] != summary["controls"]["n"]:
        print("type_census: CONTROL FAIL", file=sys.stderr)
        rc = 1
    if a.check:
        d = summary["definitions"]
        viol = []
        if d["dup_layout_classes"]:
            viol.append(f"{d['dup_layout_classes']} duplicate-layout classes")
        if d["in_c_file_scope"] + d["in_c_block_scope"] + d["in_shared_fn_headers"] + d["other_headers"]:
            viol.append("struct definitions outside the canonical type files")
        if summary["casts"]["deref_total"]:
            viol.append(f"{summary['casts']['deref_total']} raw cast sites")
        if summary["decls"]["lying"]:
            viol.append(f"{summary['decls']['lying']} lying declarations")
        print("type_census --check: " + ("OK" if not viol else "FAIL — " + "; ".join(viol)))
        if viol:
            rc = 1
    sys.exit(rc)

if __name__ == "__main__":
    main()
