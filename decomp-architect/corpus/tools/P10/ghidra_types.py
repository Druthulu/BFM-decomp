#!/usr/bin/env python3
"""tools/ghidra_types.py — the canonical C types as Ghidra `type` rows (P41 T7): include/struct_types.h + src/shared/engine_types.h
(+ include/common.h's scalars) -> config/ghidra/types/<program>.jsonl, one file per tracked program (config/ghidra/*.jsonl).

    ghidra_types.py --write                         regenerate config/ghidra/types/*.jsonl
    ghidra_types.py --check                         regenerate in memory; exit 1 on a stale/missing/extra file or an unplaced type
    ghidra_types.py merge <prog> -o <file>          config/ghidra/<prog>.jsonl + its type rows in EXPORT order (after the archive
                                                    rows, sorted by path) — what tools/ghidra_rebuild.sh step 5 imports and --proof cmps
    ghidra_types.py --gcc-compare <jsonl> [--sample N]   offsets/sizes of the file's rows (ours or an ExportAnnotations export) vs
                                                    gcc's DWARF (mipsel-linux-gnu-gcc -g probe + readelf); unions + bitfield structs
                                                    are always sampled, plus N others (sha1 order)

THE ROWS are byte-identical to what tools/ghidra_scripts/ExportAnnotations.java prints for the same types (key order, esc(),
TreeMap order by path, one per line): category /bfm; structs `packed:false` with gcc offsets and size; unions `packed:false`
(a non-packed Ghidra union's length is its longest member — UnionDB); typedef rows for every extra typedef name, every
`typedef A B;` alias and common.h's scalars (u8 -> /uchar ...). Ghidra spellings (12.1 source): a pointer is `<pointee name> *`
in the pointee's category (`/bfm/Foo *`, `/bfm/u8 * *`, `/void *`); an array is `<base name>[outer][inner]` (`/bfm/u8[2]`,
`/bfm/Foo *[4]`); a function-pointer field is `/void *`; a bitfield component carries the BASE type plus `bits`/`bitoff`
(LE bit offset within its minimal storage at `off`, len = that storage). Anonymous nested aggregates become /bfm types named
`<Parent>__<field>` (or `<Parent>__anon<HEX offset>` for an unnamed member). A field's comment is its trailing source comment.

PER PROGRAM: the canonical names that appear as identifiers in the program's TUs (`make -s print-C_SRCS BINARY=<alias>`) and the
non-canonical headers they include, closed over field/base dependencies; the prototypes (no TUs) take main's set; a type no
program uses goes to SLUS_007.26, so every canonical type is in >= 1 program. No Ghidra is run here.
"""
import hashlib
import json
import os
import pathlib
import re
import subprocess
import sys

sys.path.insert(0, str(pathlib.Path(__file__).resolve().parent))
import type_census as tc            # noqa: E402  (walk_file, CANON_HEADERS — the census's own reading of the headers)
import struct_layout as sl          # noqa: E402  (Resolver, parse_struct_body, mask_comments, DEF_START)
import cdecl                        # noqa: E402  (parse — the one C-declarator parser: checks struct_layout's member reading)

REPO = pathlib.Path(__file__).resolve().parent.parent
CONF_DIR = REPO / "config/ghidra"
TYPES_DIR = CONF_DIR / "types"
SCRATCH = REPO / "build/ghidra_types/gcc_compare"   # generated probe, wiped by make clean (was .run/P41/T7/gcc_compare)
CAT = "/bfm"
RAM_CAP = 0x200000                  # cookbook C0537: a layout above PSX main RAM is refused, never expanded
MAIN = "SLUS_007.26"
ALIAS = {MAIN: "main", "sep8_SLUS_007.26": None, "aug31_USA_DEMO.EXE": None}   # None = no TUs: take main's set
SCALAR_HEADER = "include/common.h"
# C scalar spellings -> Ghidra built-in names (root category; SoftwareModeling 12.1 *DataType constructors)
BUILTIN = {"char": "char", "signed char": "schar", "unsigned char": "uchar", "short": "short", "signed short": "short",
           "short int": "short", "unsigned short": "ushort", "unsigned short int": "ushort", "int": "int", "signed": "int",
           "signed int": "int", "unsigned": "uint", "unsigned int": "uint", "long": "long", "long int": "long",
           "unsigned long": "ulong", "unsigned long int": "ulong", "long long": "longlong", "unsigned long long": "ulonglong",
           "float": "float", "double": "double", "void": "void"}
INCLUDE_RX = re.compile(r'^[ \t]*#[ \t]*include[ \t]*[<"]([^">]+)[">]', re.M)
IDENT_RX = re.compile(r"\b[A-Za-z_]\w*\b")


class TypeError_(Exception):
    pass


def esc(s):
    """ExportAnnotations.esc()."""
    if s is None:
        return "null"
    out = ['"']
    for c in s:
        if c in '"\\':
            out.append("\\" + c)
        elif c == "\n":
            out.append("\\n")
        elif c == "\r":
            out.append("\\r")
        elif c == "\t":
            out.append("\\t")
        elif ord(c) < 0x20:
            out.append("\\u%04x" % ord(c))
        else:
            out.append(c)
    out.append('"')
    return "".join(out)


def b(v):
    return "true" if v else "false"


# ----------------------------------------------------------------------------------------------------------------------
# reading the headers (type_census.walk_file; comments re-attached from the raw text by statement)
# ----------------------------------------------------------------------------------------------------------------------
def _stmt_spans(mbody):
    """(start, semicolon) of each depth-0 statement of a masked body."""
    out, depth, start = [], 0, 0
    for i, c in enumerate(mbody):
        if c in "{(":
            depth += 1
        elif c in "})":
            depth -= 1
        elif c == ";" and depth == 0:
            out.append((start, i))
            start = i + 1
    return out


def _trailing_comment(raw, pos):
    """The comment that follows a statement's `;` on the same line, delimiters and outer whitespace stripped; None if none."""
    eol = raw.find("\n", pos)
    seg = raw[pos:eol if eol != -1 else len(raw)]
    s = seg.lstrip(" \t")
    at = pos + (len(seg) - len(s))
    if s.startswith("//"):
        return s[2:].strip() or None
    if s.startswith("/*"):
        end = raw.find("*/", at + 2)
        if end == -1:
            return None
        return raw[at + 2:end].strip() or None
    return None


def _comments(mbody, rbody):
    """[(field, comment, nested_comments)] for a body, one entry per field parse_struct_body yields (per statement)."""
    out = []
    for (s, e) in _stmt_spans(mbody):
        stmt_m = mbody[s:e + 1]
        fields = sl.parse_struct_body(stmt_m)
        cm = _trailing_comment(rbody, e + 1)
        nested = None
        m = sl.DEF_START.search(stmt_m)
        if m and any(f.get("nested") for f in fields):
            close = sl._match_brace(stmt_m, m.end() - 1)
            if close != -1:
                nested = _comments(stmt_m[m.end():close], rbody[s + m.end():s + close])
        for f in fields:
            out.append((f, cm, nested if f.get("nested") else None))
    return out


def _attach(fields, triples):
    """Copy comments onto the parsed fields (`_cm`) when the per-statement parse reproduces them exactly; False otherwise."""
    if len(fields) != len(triples):
        return False
    for f, (g, cm, nested) in zip(fields, triples):
        if (f["name"], f["type"], f["stars"], f["dims"], f["bits"]) != (g["name"], g["type"], g["stars"], g["dims"], g["bits"]):
            return False
        if f.get("nested"):
            if nested is None or not _attach(f["nested"]["fields"], nested):
                return False
        f["_cm"] = cm
    return True


def _fill_dropped(fields, mbody, rbody, where):
    """(fields, [error]): struct_layout's fields of a body with every declarator it dropped restored from cdecl.parse. A
    function-pointer ARRAY `T (*f[3])(..)` (struct_layout reads no declarator) becomes struct_layout's own reading of a function
    pointer (`void *`, 1 star) with the array's dims; any other dropped or unaccounted member is an error (no silent shell)."""
    out, errs, k = [], [], 0
    for (s, e) in _stmt_spans(mbody):
        stmt = mbody[s:e + 1]
        mine = fields[k:k + len(sl.parse_struct_body(stmt))]
        k += len(mine)
        m = sl.DEF_START.search(stmt)
        if m:                                   # a nested body: check its members; its declarators are struct_layout's
            close = sl._match_brace(stmt, m.end() - 1)
            if mine and mine[0].get("nested") and close != -1:
                nd = mine[0]["nested"]
                nd["fields"], er = _fill_dropped(nd["fields"], stmt[m.end():close], rbody[s + m.end():s + close], where)
                errs += er
            out += mine
            continue
        if ":" in stmt:                         # bitfields (cdecl does not read them): one field per top-level declarator
            if len(mine) != len(sl._split_top(stmt[:-1], ",")):
                errs.append(f"{where}: struct_layout read {len(mine)} field(s) from {stmt.strip()!r}")
            out += mine
            continue
        try:
            decls = cdecl.parse(stmt)
        except cdecl.CDeclError as ex:
            errs.append(f"{where}: member {stmt.strip()!r} unreadable by cdecl: {ex}")
            out += mine
            continue
        byname = {f["name"]: f for f in mine}
        if len(byname) != len(mine) or set(byname) - {d.name for d in decls}:
            errs.append(f"{where}: struct_layout fields {sorted(byname)} not cdecl's {[d.name for d in decls]} in {stmt.strip()!r}")
        for d in decls:
            if d.name in byname:
                out.append(byname[d.name])
                continue
            ops = [o[0] for o in d.chain]
            dims = [sl._eval_dim(o[1] or "", {}) for o in d.chain if o[0] == cdecl.ARR]
            n = len(dims)
            if n and ops == [cdecl.ARR] * n + [cdecl.PTR, cdecl.FUN] and None not in dims:
                out.append(dict(name=d.name, type="void *", stars=1, dims=dims, bits=None, nested=None,
                                _cm=_trailing_comment(rbody, e + 1)))
            else:
                errs.append(f"{where}: struct_layout dropped member {d.name!r} ({d.type}) — not modelled")
    if k != len(fields):
        errs.append(f"{where}: {len(fields)} struct_layout fields, {k} accounted for by statement")
    return out, errs


def read_headers():
    """{rel: walk} for the canonical headers + common.h, comments attached, struct_layout's dropped declarators restored
    (_fill_dropped); [rel of a def whose comments did not align]; [error]."""
    walks, misaligned, errs = {}, [], []
    for rel in tc.CANON_HEADERS + (SCALAR_HEADER,):
        raw = (REPO / rel).read_text(errors="surrogateescape")
        w = tc.walk_file(raw, rel)
        masked = tc._blank_dead_guards(tc.sc.mask_text(raw), raw, rel)
        # mask_text empties directive lines (not same-length): align the raw text line by line so one index serves both
        raw = "\n".join(r if len(r) == len(mk) else mk for r, mk in zip(raw.split("\n"), masked.split("\n")))
        line_start = [0]
        for i, c in enumerate(masked):
            if c == "\n":
                line_start.append(i + 1)
        for d in w["definitions"]:
            m = sl.DEF_START.search(masked, line_start[d["line"] - 1])
            close = sl._match_brace(masked, m.end() - 1) if m else -1
            if close == -1 or not _attach(d["fields"], _comments(masked[m.end():close], raw[m.end():close])):
                misaligned.append(f"{rel}:{d['line']}")
            if close != -1:
                d["fields"], er = _fill_dropped(d["fields"], masked[m.end():close], raw[m.end():close], f"{rel}:{d['line']}")
                errs += er
        walks[rel] = w
    return walks, misaligned, errs


# ----------------------------------------------------------------------------------------------------------------------
# the model: Ghidra path -> entry(kind, row, deps, cname)
# ----------------------------------------------------------------------------------------------------------------------
class Model:
    def __init__(self):
        self.walks, self.misaligned, self.errors = read_headers()
        self.entries = {}            # path -> dict(kind, row, deps, cname, fields(for compare), size)
        self.name_paths = {}         # C identifier -> {paths} (tags and typedef names)
        scope = {}
        for rel in tc.CANON_HEADERS + (SCALAR_HEADER,):
            w = self.walks[rel]
            for d in w["definitions"]:
                for n in d["names"] + ([d["tag"]] if d["tag"] else []):
                    scope.setdefault(n, d)
            for a in w["typedef_aliases"]:
                scope.setdefault(a["name"], dict(kind="alias", alias_of=a["alias_of"], alias_stars=a["alias_stars"],
                                                 alias_dims=a["alias_dims"]))
        self.scope = scope
        self.res = sl.Resolver(scope)
        # the C names each Ghidra type answers to
        self.gname = {}              # C type text (`Foo`, `struct Foo`) -> Ghidra path
        defs = []
        for rel in tc.CANON_HEADERS:
            for d in self.walks[rel]["definitions"]:
                if d["kind"] == "enum":
                    self.errors.append(f"{rel}:{d['line']}: enum definitions are not modelled (none existed at P41 T7)")
                    continue
                if d["ptr_names"]:
                    self.errors.append(f"{rel}:{d['line']}: pointer/array typedef names {d['ptr_names']} are not modelled")
                own = d["tag"] or (d["names"][0] if d["names"] else None)
                if own is None:
                    continue                    # `struct { .. } obj;` declares an object, not a type
                path = f"{CAT}/{own}"
                if d["tag"]:
                    self.gname[f"{d['kind']} {d['tag']}"] = path
                for n in d["names"]:
                    self.gname[n] = path if n == own else f"{CAT}/{n}"
                if d["tag"] and d["tag"] not in d["names"]:
                    self.gname.setdefault(d["tag"], path)
                defs.append((rel, d, path))
        aliases = []
        for rel in (SCALAR_HEADER,) + tc.CANON_HEADERS:
            for a in self.walks[rel]["typedef_aliases"]:
                aliases.append((rel, a))
                self.gname.setdefault(a["name"], f"{CAT}/{a['name']}")
        for rel, d, path in defs:
            self._claim_name(d["tag"] or d["names"][0], path)
            try:
                self.composite(path, d["kind"], d["fields"], d["attrs"], top=(d, rel))
            except TypeError_ as e:
                self.errors.append(f"{rel}:{d['line']}: {path}: {e}")
            for n in d["names"]:
                if f"{CAT}/{n}" != path:
                    self._typedef(f"{CAT}/{n}", path, n, f"{rel}:{d['line']}")
        for rel, a in aliases:
            p = f"{CAT}/{a['name']}"
            try:
                base = self.spell(a["alias_of"], a["alias_stars"], a["alias_dims"], fnptr=a.get("fnptr"))
            except TypeError_ as e:
                self.errors.append(f"{rel}:{a['line']}: typedef {a['name']}: {e}")
                continue
            if base == p:
                continue                        # `typedef struct Foo Foo;` — the struct already is /bfm/Foo
            self._typedef(p, base, a["name"], f"{rel}:{a['line']}")
        for p in sorted(p for p, e in self.entries.items() if e["kind"] in ("struct", "union") and not e["comps"]):
            self.errors.append(f"{p}: no fields — a 1-byte shell (gcc sizes an empty struct 0)")   # was a WARN (T7.c1)

    # -- spelling ------------------------------------------------------------------------------------------------------
    def base_path(self, t):
        t = sl._norm_type(t)
        if t in BUILTIN:
            return "/" + BUILTIN[t]
        if t in self.gname:
            return self.gname[t]
        m = re.match(r"^(struct|union|enum)\s+(\w+)$", t)
        if m and m.group(2) in self.gname:
            return self.gname[m.group(2)]
        raise TypeError_(f"type {t!r} is not canonical, common.h or a C built-in")

    def spell(self, t, stars=0, dims=(), fnptr=False):
        if fnptr or (sl._norm_type(t) == "void *" and stars == 1):
            s = "/void *"                       # a function pointer (struct_layout reads `T (*f)(..)` as `void *`, 1 star)
        else:
            s = self.base_path(t) + " *" * stars
        for d in dims:
            if d is None:
                raise TypeError_(f"unsized array of {t}")
            s += f"[{d}]"
        return s

    def deps_of(self, spec):
        m = re.match(r"^(/[^ \[]+)", spec)
        p = m.group(1) if m else spec
        return {p} if p.startswith(CAT + "/") else set()

    def _claim_name(self, name, path):
        self.name_paths.setdefault(name, set()).add(path)

    def _put(self, path, entry, where):
        old = self.entries.get(path)
        if old is not None and old["row"] != entry["row"]:
            self.errors.append(f"{where}: {path} defined twice with different rows")
            return
        self.entries[path] = entry

    def _typedef(self, path, base, cname, where):
        self._claim_name(cname, path)
        self._put(path, dict(kind="typedef", row='{"k":"type","kind":"typedef","path":' + esc(path) + ',"base":' + esc(base) + "}",
                             deps=self.deps_of(base), cname=cname, base=base), where)

    # -- layout --------------------------------------------------------------------------------------------------------
    def elem(self, f):
        """(size, align, ghidra spec of the ELEMENT, deps) of a non-nested field's element type (dims applied by the caller)."""
        r = self.res.layout(f["type"], f["stars"], ())
        if r is None:
            raise TypeError_(f"field {f['name']!r}: unknown layout of {f['type']!r}")
        sz, al, _ = r
        spec = self.spell(f["type"], f["stars"], ())
        return sz, al, spec

    def composite(self, path, kind, fields, attrs, top=None):
        """Place every field (gcc o32 rules; bitfields by PCC_BITFIELD_TYPE_MATTERS), register the row (and nested types); (size, align)."""
        packed = "packed" in (attrs or "")
        comps, deps = [], set()
        bitpos, maxal, end = 0, 1, 0
        for i, f in enumerate(fields):
            if f.get("nested"):
                nd = f["nested"]
                if nd["kind"] == "enum":
                    raise TypeError_("nested enum")
                off_guess = (bitpos + 7) // 8
                npath = (f"{CAT}/{nd['tag']}" if nd.get("tag") else
                         f"{path}__{f['name']}" if f["name"] else f"{path}__anon{off_guess:X}")
                if nd.get("tag"):
                    self._claim_name(nd["tag"], npath)
                    self.gname.setdefault(f"{nd['kind']} {nd['tag']}", npath)
                if npath in self.entries and self.entries[npath].get("size") is not None:
                    esz, eal = self.entries[npath]["size_c"], self.entries[npath]["align"]
                else:
                    esz, eal = self.composite(npath, nd["kind"], nd["fields"], nd.get("attrs"))
                spec = npath
            else:
                esz, eal, spec = self.elem(f)
            n = 1
            for d in f["dims"]:
                if d is None:
                    raise TypeError_(f"field {f['name']!r}: unsized array")
                n *= d
            total = esz * n
            if total > RAM_CAP:
                raise TypeError_(f"field {f['name']!r}: {total:#x} bytes > PSX RAM (C0537)")
            fal = 1 if packed else eal
            ma = re.search(r"aligned\s*\(\s*(\d+)\s*\)", f.get("attrs") or "")
            if ma:
                fal = max(fal, int(ma.group(1)))
            full = spec + "".join(f"[{d}]" for d in f["dims"])
            deps |= self.deps_of(full)
            if f.get("bits") is not None:
                w = f["bits"]
                unit = esz * 8
                pos = 0 if kind == "union" else bitpos
                if w == 0:
                    pos = (pos + fal * 8 - 1) // (fal * 8) * (fal * 8)
                elif unit and pos // unit != (pos + w - 1) // unit:
                    pos = (pos + fal * 8 - 1) // (fal * 8) * (fal * 8)
                if f["name"]:
                    maxal = max(maxal, fal)
                if w and f["name"]:
                    off = pos // 8
                    boff = pos % 8
                    ln = (w + boff + 7) // 8
                    comps.append(dict(off=off, len=ln, name=f["name"], type=spec, comment=f.get("_cm"), bits=w, bitoff=boff,
                                      sortkey=pos))
                end = max(end, (pos + w + 7) // 8)
                if kind != "union":
                    bitpos = pos + w
                continue
            off = 0 if kind == "union" else ((bitpos + 7) // 8 + fal - 1) // fal * fal
            comps.append(dict(off=off, len=total, name=f["name"] or None, type=full, comment=f.get("_cm"), sortkey=off * 8))
            maxal = max(maxal, fal)
            end = max(end, off + total)
            if kind != "union":
                bitpos = (off + total) * 8
        ma = re.search(r"aligned\s*\(\s*(\d+)\s*\)", attrs or "")
        if ma:
            maxal = max(maxal, int(ma.group(1)))
        size = (end + maxal - 1) // maxal * maxal
        if size > RAM_CAP:
            raise TypeError_(f"size {size:#x} > PSX RAM (C0537)")
        if top is not None:          # consistency with the census's engine (same headers, one layout — R33)
            lay = self.res.layout_of_fields(fields, kind, packed=packed)
            if lay is not None and lay[0] != size and not ma:
                self.errors.append(f"{top[1]}:{top[0]['line']}: {path}: placement size {size} != struct_layout size {lay[0]}")
        comps.sort(key=lambda c: c["sortkey"])          # Ghidra keeps components in (bit) offset order
        if kind == "union":
            gsize = max([c["len"] for c in comps] + [0]) or 1
            fl = ",".join('{"len":%d,"name":%s,"type":%s,"comment":%s%s}' % (c["len"], esc(c["name"]), esc(c["type"]), esc(c["comment"]),
                          ',"bits":%d,"bitoff":%d' % (c["bits"], c["bitoff"]) if "bits" in c else "") for c in comps)
        else:
            gsize = size or 1                               # StructureDB.getLength(): a zero-length struct reports 1
            fl = ",".join('{"off":%d,"len":%d,"name":%s,"type":%s,"comment":%s%s}' % (c["off"], c["len"], esc(c["name"]), esc(c["type"]),
                          esc(c["comment"]), ',"bits":%d,"bitoff":%d' % (c["bits"], c["bitoff"]) if "bits" in c else "") for c in comps)
        row = '{"k":"type","kind":"%s","path":%s,"size":%d,"packed":false,"fields":[%s]}' % (kind, esc(path), gsize, fl)
        cname = None
        if top is not None:
            d = top[0]
            cname = d["names"][0] if d["names"] else f"{kind} {d['tag']}"
        self._put(path, dict(kind=kind, row=row, deps=deps - {path}, cname=cname, size=gsize, size_c=size, align=maxal, comps=comps),
                  top[1] if top else path)
        return size, maxal

    # -- per program ---------------------------------------------------------------------------------------------------
    def closure(self, paths):
        out, todo = set(), list(paths)
        while todo:
            p = todo.pop()
            if p in out or p not in self.entries:
                continue
            out.add(p)
            todo.extend(sorted(self.entries[p]["deps"]))
        return out

    def rows(self, paths):
        return [self.entries[p]["row"] for p in sorted(paths)]


def programs():
    return sorted(p.name[:-len(".jsonl")] for p in CONF_DIR.glob("*.jsonl"))


def tu_files(alias):
    out = subprocess.run(["make", "-s", "print-C_SRCS", f"BINARY={alias}"], cwd=REPO, capture_output=True, text=True)
    if out.returncode != 0:
        raise SystemExit(f"ghidra_types: make print-C_SRCS BINARY={alias} failed: {out.stderr.strip()[:200]}")
    return sorted(out.stdout.split())


def used_names(tus, canon_names, cache):
    """Canonical names appearing as identifiers in the TUs and every non-canonical header they include (transitively)."""
    seen, todo, names = set(), list(tus), set()
    skip = set(tc.CANON_HEADERS)
    while todo:
        rel = todo.pop()
        if rel in seen or rel in skip:
            continue
        seen.add(rel)
        if rel not in cache:
            p = REPO / rel
            raw = p.read_text(errors="surrogateescape") if p.is_file() else ""
            incs = []
            for inc in INCLUDE_RX.findall(raw):
                for cand in (p.parent / inc, REPO / "include" / inc):
                    if cand.is_file():
                        incs.append(cand.resolve().relative_to(REPO).as_posix())
                        break
            cache[rel] = (set(IDENT_RX.findall(sl.mask_comments(raw))), incs)
        ids, incs = cache[rel]
        names |= ids & canon_names
        todo.extend(incs)
    return names


def build(model):
    """{program: sorted rows}, [unplaced paths]."""
    canon_names = set(model.name_paths)
    cache, sets = {}, {}
    for prog in programs():
        alias = ALIAS.get(prog, prog)
        if alias is None:
            continue
        names = used_names(tu_files(alias), canon_names, cache)
        sets[prog] = model.closure({p for n in names for p in model.name_paths[n]})
    for prog in programs():
        if ALIAS.get(prog, prog) is None:
            sets[prog] = set(sets[MAIN])
    placed = set().union(*sets.values()) if sets else set()
    rest = set(model.entries) - placed
    sets[MAIN] |= model.closure(rest)
    unplaced = sorted(set(model.entries) - set().union(*sets.values()))
    return {prog: model.rows(sets[prog]) for prog in sorted(sets)}, unplaced, len(rest)


def text_of(rows):
    return "".join(r + "\n" for r in rows)


def generate():
    model = Model()
    if model.errors:
        for e in model.errors[:40]:
            print("ghidra_types: ERROR", e, file=sys.stderr)
        raise SystemExit(f"ghidra_types: {len(model.errors)} modelling error(s) — nothing written")
    out, unplaced, n_rest = build(model)
    return model, out, unplaced, n_rest


def summary(model, out, n_rest):
    kinds = {}
    for e in model.entries.values():
        kinds[e["kind"]] = kinds.get(e["kind"], 0) + 1
    print(f"ghidra_types: {len(model.entries)} types ({', '.join(f'{k} {v}' for k, v in sorted(kinds.items()))}); "
          f"{n_rest} used by no program -> {MAIN}; comments misaligned in {len(model.misaligned)} defs")
    for prog, rows in out.items():
        print(f"  {prog:22} {len(rows)} rows")


# ----------------------------------------------------------------------------------------------------------------------
# merge (export order) for the rebuild
# ----------------------------------------------------------------------------------------------------------------------
HEAD_KINDS = ("program", "block", "archive")


def merge(prog, out_path):
    conf = CONF_DIR / f"{prog}.jsonl"
    tf = pathlib.Path(os.environ.get("BFM_TYPES_FILE") or TYPES_DIR / f"{prog}.jsonl")  # override: proof controls (T7.c3)
    if not conf.is_file() or not tf.is_file():
        raise SystemExit(f"ghidra_types merge: missing {conf if not conf.is_file() else tf}")
    lines = [ln.rstrip("\n") for ln in conf.read_text(encoding="utf-8").splitlines() if ln.strip()]
    head, types, tail = [], {}, []
    for ln in lines:
        k = json.loads(ln)["k"]
        if k in HEAD_KINDS:
            if tail or types:
                raise SystemExit(f"ghidra_types merge: {conf}: a {k} row after the type/annotation rows")
            head.append(ln)
        elif k == "type":
            if tail:
                raise SystemExit(f"ghidra_types merge: {conf}: a type row after the annotation rows")
            types[json.loads(ln)["path"]] = ln
        else:
            tail.append(ln)
    for ln in (x for x in tf.read_text(encoding="utf-8").splitlines() if x.strip()):
        p = json.loads(ln)["path"]
        if p in types and types[p] != ln:
            raise SystemExit(f"ghidra_types merge: {p} is in {conf} with a different row — resolve by hand in the headers")
        types[p] = ln
    rows = head + [types[p] for p in sorted(types)] + tail
    out = pathlib.Path(out_path)
    out.parent.mkdir(parents=True, exist_ok=True)
    out.write_text(text_of(rows), encoding="utf-8", newline="\n")
    print(f"ghidra_types merge: {prog}: {len(lines)} config rows + {len(types)} type rows -> {out}")


# ----------------------------------------------------------------------------------------------------------------------
# gcc's layouts (DWARF of a mipsel-linux-gnu-gcc -g probe) vs a rows file
# ----------------------------------------------------------------------------------------------------------------------
DIE_RX = re.compile(r"^\s*<(\d+)><([0-9a-f]+)>: Abbrev Number: \d+ \((DW_TAG_\w+)\)")
AT_RX = re.compile(r"^\s*<[0-9a-f]+>\s+(DW_AT_\w+)\s*:\s*(.*)$")


def parse_dwarf(text):
    dies, stack = {}, []
    cur = None
    for ln in text.splitlines():
        m = DIE_RX.match(ln)
        if m:
            depth, off, tag = int(m.group(1)), int(m.group(2), 16), m.group(3)
            cur = dict(tag=tag, off=off, attrs={}, kids=[])
            dies[off] = cur
            del stack[depth:]
            if stack:
                stack[-1]["kids"].append(cur)
            stack.append(cur)
            continue
        m = AT_RX.match(ln)
        if m and cur is not None:
            v = m.group(2).strip()
            if m.group(1) == "DW_AT_name":
                v = v.split("): ")[-1] if v.startswith("(") else v
            cur["attrs"][m.group(1)] = v
    return dies


def _ref(v):
    m = re.search(r"<0x([0-9a-f]+)>", v or "")
    return int(m.group(1), 16) if m else None


def _num(v):
    m = re.match(r"^(-?(?:0x[0-9a-f]+|\d+))", (v or "").strip())
    return int(m.group(1), 0) if m else None


def die_size(dies, off, depth=0):
    d = dies.get(off)
    if d is None or depth > 50:
        return None
    a = d["attrs"]
    if "DW_AT_byte_size" in a:
        return _num(a["DW_AT_byte_size"])
    if d["tag"] == "DW_TAG_array_type":
        n = 1
        for k in d["kids"]:
            if k["tag"] == "DW_TAG_subrange_type":
                ka = k["attrs"]
                if "DW_AT_count" in ka:
                    n *= _num(ka["DW_AT_count"])
                elif "DW_AT_upper_bound" in ka:
                    n *= _num(ka["DW_AT_upper_bound"]) + 1
                else:
                    n *= 0
        es = die_size(dies, _ref(a.get("DW_AT_type")), depth + 1)
        return None if es is None else es * n
    if d["tag"] in ("DW_TAG_typedef", "DW_TAG_const_type", "DW_TAG_volatile_type"):
        return die_size(dies, _ref(a.get("DW_AT_type")), depth + 1)
    if d["tag"] == "DW_TAG_pointer_type":
        return 4
    return None


def gcc_compare(path_in, sample_n):
    model = Model()
    rows = {}
    for ln in pathlib.Path(path_in).read_text(encoding="utf-8").splitlines():
        if not ln.strip():
            continue
        o = json.loads(ln)
        if o.get("k") == "type" and o.get("kind") in ("struct", "union") and o["path"].startswith(CAT + "/"):
            rows[o["path"]] = o
    nameable = {p: model.entries[p]["cname"] for p in rows if p in model.entries and model.entries[p].get("cname")}
    always = sorted(p for p in nameable if rows[p]["kind"] == "union" or any("bits" in f for f in rows[p]["fields"]))
    others = sorted((p for p in nameable if p not in always), key=lambda p: hashlib.sha1(p.encode()).hexdigest())
    sample = always + sorted(others[:sample_n])
    SCRATCH.mkdir(parents=True, exist_ok=True)
    probe = SCRATCH / "probe.c"
    src = ['#include "common.h"', '#include "engine_types.h"']
    for i, p in enumerate(sample):
        src.append(f"{nameable[p]} *bfm_gcc_probe_{i};")
    probe.write_text("\n".join(src) + "\n")
    obj = SCRATCH / "probe.o"
    cc = subprocess.run(["mipsel-linux-gnu-gcc", "-g", "-gdwarf-4", "-O0", "-std=gnu89", "-w", "-fno-eliminate-unused-debug-types",
                         "-Iinclude", "-Isrc/shared", "-D_LANGUAGE_C", "-c", str(probe), "-o", str(obj)],
                        cwd=REPO, capture_output=True, text=True)
    if cc.returncode != 0:
        raise SystemExit("ghidra_types --gcc-compare: probe compile failed:\n" + cc.stderr[-1500:])
    rd = subprocess.run(["mipsel-linux-gnu-readelf", "--debug-dump=info", str(obj)], capture_output=True, text=True)
    dies = parse_dwarf(rd.stdout)
    var_type = {}
    for d in dies.values():
        if d["tag"] == "DW_TAG_variable" and d["attrs"].get("DW_AT_name", "").startswith("bfm_gcc_probe_"):
            var_type[int(d["attrs"]["DW_AT_name"].rsplit("_", 1)[1])] = _ref(d["attrs"].get("DW_AT_type"))
    bad, n_fields = [], 0
    for i, p in enumerate(sample):
        ptr = dies.get(var_type.get(i))
        t = dies.get(_ref(ptr["attrs"].get("DW_AT_type"))) if ptr else None
        while t is not None and t["tag"] in ("DW_TAG_typedef", "DW_TAG_const_type", "DW_TAG_volatile_type"):
            t = dies.get(_ref(t["attrs"].get("DW_AT_type")))
        if t is None:
            bad.append(f"{p}: no DWARF type")
            continue
        o = rows[p]
        gsize = _num(t["attrs"].get("DW_AT_byte_size")) or 0
        want = gsize
        if o["kind"] == "union":                # a non-packed Ghidra union is its longest member (UnionDB)
            want = max([die_size(dies, _ref(k["attrs"].get("DW_AT_type"))) or 0 for k in t["kids"] if k["tag"] == "DW_TAG_member"] + [0])
        if (want or 1) != o["size"]:
            bad.append(f"{p}: size row {o['size']} gcc {gsize}" + (f" (longest member {want})" if want != gsize else ""))
        gm = []
        for k in t["kids"]:
            if k["tag"] != "DW_TAG_member":
                continue
            a = k["attrs"]
            nm = a.get("DW_AT_name")
            off = _num(a.get("DW_AT_data_member_location")) or 0
            bits = _num(a.get("DW_AT_bit_size"))
            if bits is not None:
                if "DW_AT_data_bit_offset" in a:
                    pos = _num(a["DW_AT_data_bit_offset"])
                else:                            # DWARF 2-4: DW_AT_bit_offset counts from the storage unit's MSB
                    unit = (_num(a.get("DW_AT_byte_size")) or die_size(dies, _ref(a.get("DW_AT_type")))) * 8
                    pos = off * 8 + unit - _num(a["DW_AT_bit_offset"]) - bits
                gm.append((nm, pos // 8, bits, pos % 8, None))
            else:
                gm.append((nm, off, None, None, die_size(dies, _ref(a.get("DW_AT_type")))))
        rm = [(f["name"], f.get("off", 0), f.get("bits"), f.get("bitoff"), None if "bits" in f else f["len"]) for f in o["fields"]]
        n_fields += len(gm)
        if gm != rm:
            diff = [f"{x} != {y}" for x, y in zip(rm, gm) if x != y][:3] or [f"{len(rm)} row fields vs {len(gm)} gcc members"]
            bad.append(f"{p}: fields differ: " + "; ".join(diff))
    n_u = sum(1 for p in sample if rows[p]["kind"] == "union")
    n_b = sum(1 for p in sample if any("bits" in f for f in rows[p]["fields"]))
    print(f"ghidra_types --gcc-compare {path_in}: {len(sample)} types ({n_u} unions, {n_b} bitfield structs, {len(sample) - len(always)} "
          f"sampled of {len(others)}), {n_fields} members vs gcc {subprocess.run(['mipsel-linux-gnu-gcc', '-dumpversion'], capture_output=True, text=True).stdout.strip()} DWARF")
    for p in sample:
        print("  sample", p, "=", nameable[p])
    for x in bad:
        print("  MISMATCH", x)
    print("ghidra_types --gcc-compare:", "ALL EQUAL" if not bad else f"{len(bad)} MISMATCH(ES)")
    return 1 if bad else 0


# ----------------------------------------------------------------------------------------------------------------------
def main(argv):
    if argv[:1] == ["merge"]:
        if len(argv) != 4 or argv[2] != "-o":
            raise SystemExit("usage: ghidra_types.py merge <prog> -o <file>")
        merge(argv[1], argv[3])
        return 0
    if argv[:1] == ["--gcc-compare"]:
        n = int(argv[argv.index("--sample") + 1]) if "--sample" in argv else 24
        return gcc_compare(argv[1], n)
    if argv not in (["--write"], ["--check"]):
        raise SystemExit(__doc__)
    model, out, unplaced, n_rest = generate()
    summary(model, out, n_rest)
    if unplaced:
        print(f"ghidra_types: {len(unplaced)} type(s) in no program: {unplaced[:5]}")
    if argv == ["--write"]:
        TYPES_DIR.mkdir(parents=True, exist_ok=True)
        for prog, rows in out.items():
            (TYPES_DIR / f"{prog}.jsonl").write_text(text_of(rows), encoding="utf-8", newline="\n")
        for extra in sorted(set(p.name for p in TYPES_DIR.glob("*.jsonl")) - {f"{q}.jsonl" for q in out}):
            (TYPES_DIR / extra).unlink()
        print(f"ghidra_types: wrote {len(out)} files to {TYPES_DIR.relative_to(REPO)}/")
        return 1 if unplaced else 0
    stale = []
    for prog, rows in out.items():
        f = TYPES_DIR / f"{prog}.jsonl"
        if not f.is_file() or f.read_text(encoding="utf-8") != text_of(rows):
            stale.append(f.relative_to(REPO).as_posix())
    extra = sorted(set(p.name for p in TYPES_DIR.glob("*.jsonl")) - {f"{q}.jsonl" for q in out}) if TYPES_DIR.is_dir() else []
    for x in stale + extra:
        print(f"ghidra_types --check: STALE {x} (run tools/ghidra_types.py --write)")
    ok = not (stale or extra or unplaced)
    print("ghidra_types --check:", "OK" if ok else "FAIL")
    return 0 if ok else 1


if __name__ == "__main__":
    sys.exit(main(sys.argv[1:]))
