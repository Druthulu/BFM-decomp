#!/usr/bin/env python3
"""tools/struct_layout.py — the o32 struct layout engine, the field map, the canonical-type WRITER and the layout INVARIANT
(Phase 37 T3, 2026-09-12). Factored out of tools/type_census.py (T1) so the census, the rewrite engine (tools/restruct.py) and
the type writer compute ONE layout for one definition (R33: derive, don't re-derive).

WHAT IT KNOWS
  * SCALARS / SDK_SIZES          the o32 widths of every scalar spelling the tree uses, and the PsyQ aggregate sizes.
  * parse_struct_body            `struct/union … { … }` body text -> fields [dict(name, type, stars, dims, bits, nested, attrs)].
  * Resolver                     type name -> (size, align, leaves[(off, width, sign)]) under the o32 rules (arrays, nested
                                 aggregates, bit-fields, `packed`, per-field `aligned(N)`); cc1-validated on 5,283 file-scope
                                 definitions / 29,248 named fields at T2 (`tools/restruct.py --audit-layouts`, 0 rejected).
  * layout_hash / field_offsets  the identity of a layout; the top-level named fields with their byte offsets (the audit's assertions).
  * field_map                    a definition's {offset: (name, width, sign, type_text)} over its top-level scalar/pointer fields —
                                 what the rewrite engine consults to turn `*(u16 *)(p + 0x3C)` into `p->unk3C`.
  * render_struct                THE WRITER: the final style of a canonical definition (owner decision 2, gate 1) —
                                     typedef struct {
                                         /* 0x00 */ s16 unk0;
                                         /* 0x02 */ u8 pad2[0x2];
                                         /* 0x04 */ s32 unk4;
                                     } Unkstruct_80078E00; /* size = 0x8 */
                                 `unk<HEX>` = a field the code ACCESSES whose meaning is unknown; `u8 pad<HEX>[n]` = bytes the code
                                 never touches (Phase 38 knows there is nothing to name there); a field is NAMED only where the
                                 record cites evidence, and the citation rides in its comment. One decision, applied everywhere.
  * audit_definition             THE INVARIANT (sotn's SYNC_FIELD, made derivable): every `unk<HEX>` / `pad<HEX>` field sits at
                                 offset HEX, every `/* 0xNN */` offset comment equals the computed offset, and the `size = 0x..`
                                 trailer equals sizeof. A drifted definition (a field inserted by hand) fails the census's --check
                                 (T8 wires it into tools-health) — no ledger and no PC build needed.
"""
import hashlib
import json
import re

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
ATTR_RX = re.compile(r"__attribute__\s*\(\(((?:[^()]|\([^()]*\))*)\)\)")     # nested parens: aligned(4), packed

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
        fattrs = " ".join(ATTR_RX.findall(stmt))
        stmt = ATTR_RX.sub("", stmt)
        base_type, decls = _split_declarators(stmt)
        if base_type is None:
            continue
        for (nm, stars, dims, bits) in decls:
            fields.append(dict(name=nm, type=base_type, stars=stars, dims=[_eval_dim(d, consts) for d in dims], bits=bits, nested=None,
                               attrs=fattrs or None))
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
            fa = f.get("attrs") or ""
            ma = re.search(r"aligned\s*\(\s*(\d+)\s*\)", fa)
            if packed:
                fal = 1
            if ma:
                fal = max(fal, int(ma.group(1)))
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

# ----------------------------------------------------------------------------------------------------------------------
# the field map (what a rewrite consults) and the naming invariant (what the census asserts)
# ----------------------------------------------------------------------------------------------------------------------
def mask_comments(text):
    """Same-length masking of /* */ and // comments (the census masks through share_census.mask_text; this is the standalone
    equivalent for a definition's own text — parse_struct_body expects MASKED text, never raw)."""
    return re.sub(r"/\*.*?\*/|//[^\n]*", lambda m: re.sub(r"[^\n]", " ", m.group(0)), text, flags=re.S)


UNK_RX = re.compile(r"^unk([0-9A-F]+)$")
PAD_RX = re.compile(r"^pad([0-9A-F]+)$")
# the LEADING offset comment of the final style: `    /* 0x0004 */ s32 unk4;` — a TRAILING legacy comment (`s32 unk8; /* 0x8 */`) is not judged
# (it would otherwise be paired with the NEXT field: the first audit run read 1,013 "violations" in the legacy header that way)
OFF_COMMENT_RX = re.compile(r"^[ \t]*/\*\s*0x([0-9A-Fa-f]+)\s*\*/[ \t]*([^;/\n]*;)", re.M)
SIZE_TRAILER_RX = re.compile(r"/\*\s*size\s*=\s*0x([0-9A-Fa-f]+)\s*\*/")
TYPE_OF = {(1, "u"): "u8", (1, "s"): "s8", (2, "u"): "u16", (2, "s"): "s16", (4, "u"): "u32", (4, "s"): "s32",
           (8, "u"): "u64", (8, "s"): "s64", (4, "f"): "f32", (8, "f"): "f64"}


def field_offsets(res, d):
    """Top-level NAMED, non-bitfield fields with their byte offsets under the engine's rules — the audit's assertions.
    (Moved from tools/restruct.py T2 form.)"""
    out, off, kind = [], 0, d["kind"]
    packed = "packed" in (d.get("attrs") or "")
    for f in d["fields"]:
        if f.get("nested"):
            nd = f["nested"]
            r = res.layout_of_fields(nd["fields"], nd["kind"], packed=("packed" in (nd.get("attrs") or ""))) if nd["kind"] != "enum" else (4, 4, [])
        else:
            r = res.layout(f["type"], f["stars"], f["dims"])
        if r is None:
            return out
        fsz, fal, _ = r
        if f.get("dims") and f["nested"]:
            for dd in reversed(f["dims"]):
                fsz *= (dd or 0)
        fa = f.get("attrs") or ""
        ma = re.search(r"aligned\s*\(\s*(\d+)\s*\)", fa)
        if packed:
            fal = 1
        if ma:
            fal = max(fal, int(ma.group(1)))
        if f.get("bits") is not None:
            return out          # bit-field layouts are not asserted (the unit rule is compiler-specific); stop here
        if kind == "union":
            if f["name"]:
                out.append((f["name"], 0))
            continue
        off = (off + fal - 1) // fal * fal
        if f["name"]:
            out.append((f["name"], off))
        off += fsz
    return out


def field_map(res, d):
    """{offset: dict(name, width, sign, type, stars, dims)} for the top-level SCALAR / POINTER fields of a struct definition
    (an aggregate member is listed with sign 'agg' and its size — the engine never rewrites into an aggregate without an
    explicit member path). None when a field's layout is unknown."""
    out = {}
    offs = dict(field_offsets(res, d))
    for f in d["fields"]:
        if not f["name"] or f["name"] not in offs or f.get("bits") is not None:
            continue
        if f.get("nested"):
            nd = f["nested"]
            r = res.layout_of_fields(nd["fields"], nd["kind"], packed=("packed" in (nd.get("attrs") or ""))) if nd["kind"] != "enum" else (4, 4, [(0, 4, "s")])
            if r is None:
                return None
            out[offs[f["name"]]] = dict(name=f["name"], width=r[0], sign="agg", type=f["type"], stars=0, dims=f.get("dims") or [])
            continue
        if f.get("dims"):
            r = res.layout(f["type"], f["stars"], f["dims"])
            if r is None:
                return None
            out[offs[f["name"]]] = dict(name=f["name"], width=r[0], sign="agg", type=f["type"], stars=f["stars"], dims=f["dims"])
            continue
        if f["stars"]:
            out[offs[f["name"]]] = dict(name=f["name"], width=4, sign="p", type=f["type"], stars=f["stars"], dims=[])
            continue
        w = scalar_of(f["type"])
        if w is None:
            r = res.layout(f["type"])
            if r is None:
                return None
            out[offs[f["name"]]] = dict(name=f["name"], width=r[0], sign="agg", type=f["type"], stars=0, dims=[])
            continue
        out[offs[f["name"]]] = dict(name=f["name"], width=w[0], sign=w[1], type=f["type"], stars=0, dims=[])
    return out


def leaf_at(lay, off, width, sign):
    """True when the layout's leaves carry (off, width) with a compatible sign — a store's signedness leaves no byte, so a
    store may hit a field of the other sign; a load may not. `sign` None = width only."""
    if lay is None:
        return False
    for (o, w, s) in lay[2]:
        if o == off and w == width:
            if sign is None or s == sign or {s, sign} <= {"s", "u"} and sign == "store":
                return True
            if sign in ("s", "u") and s in ("s", "u") and sign != s:
                continue
            if s == sign:
                return True
    return False


def render_struct(name, entries, size=None, kind="struct", indent="    ", comment=None, tag=None):
    """THE WRITER. entries = [(off, type_text, field_name, dims_or_None, note_or_None)] sorted by offset, non-overlapping; the gaps
    become `u8 pad<HEX>[n]`; `size` (else the end of the last field) rounds to the alignment of the widest scalar; the trailer
    names the size. Returns the text (ending with a newline). Refuses overlaps and misaligned scalars (ValueError)."""
    lines = [f"typedef {kind} {tag + ' ' if tag else ''}{{"]
    if comment:
        lines.append(f"{indent}/* {comment} */")
    cur, maxal = 0, 1
    for (off, ttext, fname, dims, note) in sorted(entries, key=lambda e: e[0]):
        if off < cur:
            raise ValueError(f"render_struct {name}: {fname} at {off:#x} overlaps the previous field ending at {cur:#x}")
        sc_ = scalar_of(ttext)
        w = sc_[0] if sc_ else None
        al = (8 if w == 8 else min(w, 4)) if w else 4
        if w and off % al:
            raise ValueError(f"render_struct {name}: {fname} ({ttext}) at {off:#x} is not {al}-aligned")
        if off > cur:
            lines.append(f"{indent}/* {cur:#06x} */ u8 pad{cur:X}[{off - cur:#x}];")
        dtxt = "".join(f"[{d:#x}]" if isinstance(d, int) else f"[{d}]" for d in (dims or []))
        lines.append(f"{indent}/* {off:#06x} */ {ttext} {fname}{dtxt};" + (f" /* {note} */" if note else ""))
        n = 1
        for d in (dims or []):
            n *= (d if isinstance(d, int) else 1)
        cur = off + (w or 0) * n if w else off + 4 * n
        maxal = max(maxal, al)
    end = size if size is not None else (cur + maxal - 1) // maxal * maxal
    if end < cur:
        raise ValueError(f"render_struct {name}: size {end:#x} is smaller than the last field's end {cur:#x}")
    if end > cur:
        lines.append(f"{indent}/* {cur:#06x} */ u8 pad{cur:X}[{end - cur:#x}];")
    lines.append(f"}} {name}; /* size = {end:#x} */")
    return "\n".join(lines) + "\n"


def entries_from_layout(layout, ctypes_by_off=None, prefer_pointee=None):
    """The struct map's layout [(off, w, sign, n)] -> render_struct entries [(off, type, unk<HEX>, None, None)], skipping what a
    struct cannot hold: overlaps (the earlier/wider-supported entry wins by count), misaligned widths, unknown widths. Returns
    (entries, skipped[(off, w, sign, reason)]). A pointer field takes the sites' pointee when they agree, else `void *`."""
    entries, skipped, cur = [], [], 0
    for (off, w, sg, n) in sorted(layout, key=lambda x: (x[0], -x[3])):
        if w is None or w == 0:
            skipped.append((off, w, sg, "width"))
            continue
        if off < cur:
            skipped.append((off, w, sg, "overlap"))
            continue
        al = 8 if w == 8 else min(w, 4)
        if off % al:
            skipped.append((off, w, sg, "misaligned"))
            continue
        if sg == "p":
            pt = {}
            for c in (ctypes_by_off or {}).get(off, []):
                if c and c.count("*") >= 2:
                    k = c.rstrip("* ").strip() + " *"
                    pt[k] = pt.get(k, 0) + 1
            t = (prefer_pointee or {}).get(off) or (next(iter(pt)) if len(pt) == 1 else "void *")
        else:
            t = TYPE_OF.get((w, sg))
            if t is None:
                skipped.append((off, w, sg, "sign"))
                continue
        entries.append((off, t, f"unk{off:X}", None, None))
        cur = off + w
    return entries, skipped


def audit_definition(d, res, text=None):
    """THE INVARIANT on one definition record (type_census.find_definitions shape): [violations as strings]; [] = OK.
    (1) every `unk<HEX>`/`pad<HEX>` top-level field sits at offset HEX; (2) when `text` (the definition's raw source text) is
    given, every `/* 0xNN */ … ;` field comment equals the computed offset of the field it annotates and the `size = 0x..`
    trailer equals sizeof. Fields with other names are not judged by (1) — the record's evidence-cited names carry a comment."""
    out = []
    offs = field_offsets(res, d)
    name = (d.get("names") or [d.get("tag") or "?"])[0]
    for (fname, off) in offs:
        for rx, what in ((UNK_RX, "unk"), (PAD_RX, "pad")):
            m = rx.match(fname)
            if m and int(m.group(1), 16) != off:
                out.append(f"{name}.{fname}: named for offset {int(m.group(1), 16):#x} but laid out at {off:#x}")
    if text:
        by_name = dict(offs)
        for m in OFF_COMMENT_RX.finditer(text):
            want = int(m.group(1), 16)
            decl = m.group(2)
            first = decl.split(",")[0]                      # `u16 cx, cy, cz;` — the comment names the FIRST declarator's offset
            m2 = re.search(r"([A-Za-z_]\w*)\s*(?:\[[^\]]*\])*\s*(?::\s*\d+)?\s*[;,]?\s*$", first.rstrip(";") + ";")
            if not m2:
                continue
            fname = m2.group(1)
            if fname in by_name and by_name[fname] != want:
                out.append(f"{name}.{fname}: comment says {want:#x}, laid out at {by_name[fname]:#x}")
        ms = SIZE_TRAILER_RX.search(text)
        lay = res.layout_of_fields(d["fields"], d["kind"], packed=("packed" in (d.get("attrs") or "")))
        if ms and lay and int(ms.group(1), 16) != lay[0]:
            out.append(f"{name}: trailer says size {int(ms.group(1), 16):#x}, sizeof is {lay[0]:#x}")
    return out


def selftest():
    """The writer round-trips through the parser and the invariant holds; a drifted definition is caught; a hand layout agrees."""
    checks = []
    entries = [(0, "s16", "unk0", None, None), (4, "s32", "unk4", None, None), (8, "u8", "unk8", [4], None), (0x10, "void *", "unk10", None, None)]
    txt = render_struct("Unkstruct_TEST", entries)
    checks.append(("writer emits pad2", "u8 pad2[0x2]" in txt))
    checks.append(("writer trailer", "/* size = 0x14 */" in txt))
    body = mask_comments(txt)[txt.index("{") + 1:txt.rindex("}")]
    fields = parse_struct_body(body)
    d = dict(kind="struct", tag=None, names=["Unkstruct_TEST"], fields=fields, attrs="")
    res = Resolver({"Unkstruct_TEST": d})
    lay = res.resolve_name("Unkstruct_TEST")
    checks.append(("parsed size 0x14", lay is not None and lay[0] == 0x14))
    checks.append(("field_map", field_map(res, d)[4]["name"] == "unk4" and field_map(res, d)[8]["sign"] == "agg"))
    checks.append(("audit OK", audit_definition(d, res, txt) == []))
    # a drifted definition: a field inserted by hand shifts unk4 to 0x8 -> the invariant names it
    drift = txt.replace("/* 0x0002 */ u8 pad2[0x2];", "/* 0x0002 */ u8 pad2[0x2];\n    s32 inserted;")
    fields2 = parse_struct_body(mask_comments(drift)[drift.index("{") + 1:drift.rindex("}")])
    d2 = dict(kind="struct", tag=None, names=["Unkstruct_TEST"], fields=fields2, attrs="")
    v = audit_definition(d2, Resolver({"Unkstruct_TEST": d2}), drift)
    checks.append(("drift caught", any("unk4" in x for x in v)))
    # the layout skip rules: an overlap, a misaligned half, an unknown width
    ents, skipped = entries_from_layout([(0, 4, "s", 5), (2, 2, "u", 1), (5, 2, "u", 3), (8, 2, "u", 2), (12, None, None, 1)])
    checks.append(("overlap/misaligned/width skipped", [s[3] for s in skipped] == ["overlap", "misaligned", "width"] and [e[0] for e in ents] == [0, 8]))
    checks.append(("leaf_at", leaf_at(lay, 4, 4, "s") and not leaf_at(lay, 4, 2, "s") and not leaf_at(lay, 6, 2, "u")))
    try:
        render_struct("X", [(0, "s32", "a", None, None), (2, "s16", "b", None, None)])
        checks.append(("overlap refused", False))
    except ValueError:
        checks.append(("overlap refused", True))
    bad = [c for c, ok in checks if not ok]
    print(f"struct_layout --selftest: {len(checks) - len(bad)}/{len(checks)} OK" + (f"; FAILED: {bad}" if bad else ""))
    return 0 if not bad else 1


if __name__ == "__main__":
    import sys
    sys.exit(selftest() if "--selftest" in sys.argv else 0)
