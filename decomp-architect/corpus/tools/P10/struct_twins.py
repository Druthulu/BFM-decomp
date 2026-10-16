#!/usr/bin/env python3
"""struct_twins.py — draft the evidence for tier-2 duplicate-layout classes (P38 T5.1.c4).

`type_census.py --check-structs` gates every tier-2 row of <census>/dup_gating.tsv unless docs/struct-twins.md lists it under
`## Twins` with the row's names and an addressed cause (G62: layout twins without evidence stay apart, "per type, not per layout").
This tool joins each name to the objects it is bound to in the source, and classifies each class:

  SEPARATE  every name is bound to >= 1 object and no object is bound to two names of the class -> a `### <lhash>` section
  SHARED    two or more names bound to the same object -> not listed; printed as a fold candidate with the shared object
  UNBOUND   some name has no bound object (definition-only / member-only / macro-only) -> a `### <lhash>` section whose cause
            cites the use sites of the unbound names (U: the functions using them, the types naming them as a member or alias);
            a class none of whose cites carries an address is not written and is reported (T5.1.c7)
  SDK is not a class but a note (T5.1.c7): the base layout hash equals a Sony PsyQ struct's (PSYQ names defined in the canonical
  type files / include/, hashed by the census's own parser and Resolver); the SDK-named defs themselves were folded in T5.1.c6,
  the placeholders left in the row are classified by their bindings like any other and the cause names the SDK layout
Rows: dup_gating.tsv's tier-2 rows plus the ones the current `## Twins` list takes out of it (type_census.json), so --write is
idempotent.

Objects (the binding a use of the name establishes; scanned from src/**/*.{c,h} and include/**/*.h, comments stripped):
  G  a D_<addr> global declared with the type or cast to it (`extern N D_x;`, `(N *)&D_x`), keyed by address alone (the
     census's AT node identity, so the same address across overlay copies is one object)
  L  a local / cast base inside a function body, keyed (function identity, ident); the identity is the census's normalized
     body text (func_/D_ masked) with tier-2 names, lifted-name address/overlay suffixes and block-scope externs masked too,
     so the overlay copies of one routine bind one object
  P  a parameter slot: a prototype's keyed (binary, fn, arg index), a definition's also by function identity; R the return
  A  same routine address + same local / slot, across binaries (the copies edited apart by levers and pins)
  AG a global used by the routine at one address, counted only across binaries (per-overlay instances of one table)
  F  a member of an aggregate (no address)
  U  a use site, no object (evidence for UNBOUND only): the using function (<binary>/0x<addr>) or, outside a function, the
     name the enclosing file-scope declaration defines (a struct naming it as a member, an alias typedef); a T3 band def
     (config/type_folds.tsv `define` target under a `# T3` line) also cites its map type's <census>/sites.jsonl bodies (T3.c3)
Each G/L object is joined to its struct_map cluster through <census>/body_base_type.json when present (`--sites` run).

Usage:
  tools/struct_twins.py [--census-dir DIR]          dry run: SEPARATE/SHARED/SDK/UNBOUND counts + the SHARED list
  tools/struct_twins.py --write                     regenerate only the `## Twins` section of docs/struct-twins.md
  tools/struct_twins.py --show <lhash>              every name's full object list (with struct_map clusters)
"""
import argparse
import collections
import hashlib
import json
import re
import sys
from pathlib import Path

REPO = Path(__file__).resolve().parent.parent
CENSUS_DEFAULT = ".run/P38/census"
TWINS_DOC = REPO / "docs" / "struct-twins.md"
MAX_CITES = 8
# Sony PsyQ (libgte / libgpu / libetc / libcd / libspu / libsnd / libapi) struct typedef names
PSYQ = set("""SVECTOR VECTOR CVECTOR DVECTOR MATRIX RECT RECT32 SPOL POL3 POL4 TMESH QMESH
DR_ENV DR_MODE DR_TPAGE DR_AREA DR_OFFSET DR_TWIN DR_STP DR_MOVE DR_LOAD DR_PRIO P_TAG P_CODE
POLY_F3 POLY_F4 POLY_FT3 POLY_FT4 POLY_G3 POLY_G4 POLY_GT3 POLY_GT4 LINE_F2 LINE_F3 LINE_F4 LINE_G2 LINE_G3 LINE_G4
SPRT SPRT_8 SPRT_16 TILE TILE_1 TILE_8 TILE_16 DISPENV DRAWENV TIM_IMAGE KANJIFONT
CdlLOC CdlFILE CdlATV CdlFILTER SpuVolume SpuVoiceAttr SpuCommonAttr SpuReverbAttr SpuExtAttr SpuEnv SpuLVoiceAttr
SndVolume SndVolume2 SndRegisterAttr VabHdr ProgAtr VagAtr DIRENTRY EXEC XF_HDR""".split())

TOK = re.compile(r"[A-Za-z_]\w*|0x[0-9A-Fa-f]+|\d+|\S")
COMMENT = re.compile(r"/\*.*?\*/|//[^\n]*|\"(?:\\.|[^\"\\\n])*\"|'(?:\\.|[^'\\\n])*'", re.S)
HEX8 = re.compile(r"(80[0-9A-Fa-f]{6})$")
DSYM = re.compile(r"^D_([0-9A-Fa-f]{8})$")
NORM = re.compile(r"(?:_?[0-9A-Fa-f]{8}|_(?:SC\d\d|MAIN)_\d{3}|_md)+")   # lifted-name suffixes (address / overlay)
KEYWORDS = {"struct", "union", "const", "volatile", "extern", "static", "register", "typedef", "sizeof", "return", "if",
            "while", "for", "switch", "do", "else"}
CTYPES = {"s8", "u8", "s16", "u16", "s32", "u32", "s64", "u64", "int", "char", "short", "long", "unsigned", "signed", "void",
          "struct", "union", "const", "volatile"}


def load_rows(census):
    """every tier-2 row: dup_gating.tsv's (full names) plus the rows the current `## Twins` list already takes out of it
    (type_census.json keeps every row but caps names at 40; a listed row's names equal its `names:` line, as the census checked)"""
    rows = []
    for line in (census / "dup_gating.tsv").read_text().splitlines()[1:]:
        tier, lhash, size, n, names = line.split("\t")
        if tier == "2":
            rows.append(dict(lhash=lhash, size=int(size), names=names.split(",")))
    seen = {r["lhash"] for r in rows}
    sys.path.insert(0, str(REPO / "tools"))
    import type_census as tc
    listed, _ = tc.load_twins(TWINS_DOC.read_text() if TWINS_DOC.exists() else "")
    tcj = json.loads((census / "type_census.json").read_text())
    for r in tcj["dup_layout_classes"]:
        if r["tier"] != 2 or r["lhash"] in seen:
            continue
        names = r["names"] if len(r["names"]) == r["n_names"] else sorted((listed.get(r["lhash"]) or {}).get("names") or ())
        if len(names) != r["n_names"]:
            sys.exit(f"struct_twins: tier-2 row {r['lhash']} is neither in dup_gating.tsv nor listed with its {r['n_names']} names")
        rows.append(dict(lhash=r["lhash"], size=r["size"], names=list(names)))
        seen.add(r["lhash"])
    return rows + listed_rows(listed, seen, set(tcj.get("structs_stale") or ()))


def listed_rows(listed, seen, stale):
    """(pure) the `## Twins` rows the census took out of dup_gating.tsv (listed, not stale) but type_census.json's top-300
    dup_layout_classes cap drops (T3.c3); size from the section's own `(<n> B,` cause"""
    out = []
    for lh, t in sorted(listed.items()):
        if lh in seen or lh in stale or not t["names"]:
            continue
        m = re.search(r"\((\d+) B\b", t["cause"] or "")
        if not m:
            sys.exit(f"struct_twins: listed row {lh} is beyond type_census.json's cap and its cause names no size")
        out.append(dict(lhash=lh, size=int(m.group(1)), names=sorted(t["names"])))
    return out


def psyq_layouts():
    """base lhash -> the PsyQ names defined with that layout in the canonical type files and include/ (the census's own
    parser and resolver, so the hash is the one dup_gating.tsv's rows carry)"""
    sys.path.insert(0, str(REPO / "tools"))
    import type_census as tc
    files = list(tc.CANON_HEADERS) + sorted(str(p.relative_to(REPO)) for p in (REPO / "include").rglob("*.h"))
    defs, tds = [], []
    for rel in files:
        r = tc.walk_file((REPO / rel).read_text(errors="replace"), rel)
        defs += r["definitions"]
        tds += r["typedef_aliases"]
    g = {}
    for d in defs:
        for nm in d["names"] + ([d["tag"]] if d["tag"] else []):
            g.setdefault(nm, d)
    for a in tds:
        g.setdefault(a["name"], dict(kind="alias", alias_of=a["alias_of"], alias_stars=a["alias_stars"], alias_dims=a["alias_dims"]))
    out = collections.defaultdict(set)
    for d in defs:
        own = (set(d["names"]) | ({d["tag"]} if d["tag"] else set())) & PSYQ
        if own and d["kind"] != "enum":
            lay = tc.Resolver(g).layout_of_fields(d["fields"], d["kind"], packed=("packed" in d["attrs"]))
            if lay:
                out[tc.layout_hash(lay)] |= own
    return out


def binary_of(rel):
    p = rel.split("/")
    if p[0] == "src" and len(p) > 2 and p[1].startswith(("ov_", "md_")):
        return p[1]
    if p[0] == "src" and len(p) == 2:
        return "main"
    if p[0] == "src" and p[1] == "shared" and len(p) > 3:
        return "shared/" + p[2]
    return p[0] if p[0] != "src" else "/".join(p[:2])


def addr_of(fn):
    m = HEX8.search(fn)
    return "0x" + m.group(1).upper() if m else fn


def scan_file(rel, text, wanted, sink):
    """append (name, key, cite, where) for every binding of a wanted name in one file"""
    text = COMMENT.sub(lambda m: re.sub(r"[^\n]", " ", m.group(0)), text)
    # a macro whose body names a wanted type: each use of the macro inside a function is a use (U) of that type
    macros = {}
    for m in re.finditer(r"(?m)^[ \t]*#[ \t]*define[ \t]+(\w+)((?:.*\\\n)*.*)$", text):
        hit = set(re.findall(r"[A-Za-z_]\w*", m.group(2))) & wanted
        if hit:
            macros[m.group(1)] = hit
    text = re.sub(r"(?m)^[ \t]*#.*$", "", text)
    toks, lines, ln, last = [], [], 1, 0
    for m in TOK.finditer(text):
        ln += text.count("\n", last, m.start())
        last = m.start()
        toks.append(m.group(0))
        lines.append(ln)
    binary = binary_of(rel)
    depth, fn, fn_depth = 0, None, None
    parens = []             # stack of [callee or None, comma count, brace depth]
    last_group = None       # (index of '(' , index of ')') of the last top-level paren group
    knr = None              # (fn, [param idents]) between a K&R definition's `)` and its `{`
    hdrpend, fnpend, body0 = [], [], 0   # sink indexes of a header's P bindings / a body's L+P bindings; body start token
    used_by, s0 = collections.defaultdict(set), len(sink)    # D_ symbol -> addresses of this file's functions using it
    upend = []              # (name, where) of wanted names used outside a function: owner = the declaration's defined name
    stmt = 0
    n = len(toks)
    for i, t in enumerate(toks):
        if t == "(":
            if not parens and depth == 0:
                knr = None
            callee = toks[i - 1] if i and re.match(r"[A-Za-z_]\w*$", toks[i - 1]) and toks[i - 1] not in KEYWORDS else None
            parens.append([callee, 0, i])
            continue
        if t == ")":
            if parens:
                g = parens.pop()
                if not parens:
                    last_group = (g[2], i)
                    nx = toks[i + 1] if i + 1 < len(toks) else ""
                    if depth == 0 and g[0] and re.match(r"[A-Za-z_]\w*$", nx) and nx != "__asm__":
                        knr = (g[0], [x for x in toks[g[2] + 1:i] if re.match(r"[A-Za-z_]\w*$", x)])
            continue
        if t == "," and parens:
            parens[-1][1] += 1
            continue
        if t == "{":
            if depth == 0 and last_group and last_group[1] == i - 1 and last_group[0] > 0:
                fn, fn_depth = toks[last_group[0] - 1], 1
            elif depth == 0 and knr:
                fn, fn_depth = knr[0], 1
            if depth == 0 and fn:
                fnpend, hdrpend, body0 = hdrpend, [], i
                upend = []          # a definition's header: its params are P bindings, not declaration uses
            knr = None
            depth += 1
            stmt = i + 1
            continue
        if t == "}":
            depth -= 1
            if fn and depth < fn_depth:
                # the census's function identity (Phase-35 normalized text: func_/D_ masked) with the tier-2 names, address /
                # overlay suffixes of lifted names and block-scope extern lines masked too, so the copies of one routine across
                # overlays (which differ only in their per-copy type names and extern lists) bind one object
                body, x0 = [], body0
                while x0 <= i:
                    if toks[x0] == "extern":
                        while x0 <= i and toks[x0] != ";":
                            x0 += 1
                    else:
                        body.append(toks[x0])
                    x0 += 1
                norm = " ".join("@T" if x in wanted else "D_" if DSYM.match(x) else "func_" if x.startswith("func_") else NORM.sub("#", x)
                                for x in body)
                h = "F:" + hashlib.sha1(norm.encode()).hexdigest()[:12]
                for ix in fnpend:                         # a parameter also keeps its per-binary slot (its prototypes' key)
                    nm, key, cite, where = sink[ix]
                    if key[0] == "L":
                        sink[ix] = (nm, ("L", h, key[-1]), cite, where)
                    else:
                        sink.append((nm, ("P", h, key[-1]), cite, where))
                    # the same routine edited differently per overlay (levers, pins): same address, same local / slot
                    sink.append((nm, ("A", addr_of(fn), key[0], key[-1]), cite, where))
                for x in body:
                    if DSYM.match(x):
                        used_by[x].add(addr_of(fn))
                fn, fnpend = None, []
            stmt = i + 1
            continue
        if t == ";":
            if depth == 0 and not parens and not knr:
                hdrpend = []
            if depth == 0 and not parens:
                owner = toks[i - 1] if i and not knr and re.match(r"[A-Za-z_]\w*$", toks[i - 1]) else None
                for nm, wh in upend:
                    if owner and owner != nm:
                        sink.append((nm, ("U", owner), owner, wh))
                upend = []
            stmt = i + 1
            continue
        if t in macros and fn:
            for nm in macros[t]:
                sink.append((nm, ("U", f"{binary}/{addr_of(fn)}"), f"{binary}/{addr_of(fn)}", f"{rel}:{lines[i]}"))
        if t not in wanted:
            continue
        if fn:
            sink.append((t, ("U", f"{binary}/{addr_of(fn)}"), f"{binary}/{addr_of(fn)}", f"{rel}:{lines[i]}"))
        else:
            upend.append((t, f"{rel}:{lines[i]}"))
        if stmt < n and toks[stmt] == "typedef":
            continue
        j = i + 1
        stars = 0
        while j < n and toks[j] in ("*", "const", "volatile"):
            stars += toks[j] == "*"
            j += 1
        nxt = toks[j] if j < n else ""
        k = i - 1
        while k >= 0 and toks[k] in ("struct", "union", "const", "volatile"):
            k -= 1
        prev = toks[k] if k >= 0 else ""
        where = f"{rel}:{lines[i]}"
        if prev == "(" and nxt == ")" and stars:                       # cast (N *)expr
            m = j + 1
            while m < n and (toks[m] in ("&", "*", "(", ")") or toks[m] in CTYPES):
                m += 1
            op = toks[m] if m < n else ""
            if DSYM.match(op):
                sink.append((t, ("G", op), "0x" + op[2:].upper(), where))
            elif fn and re.match(r"[A-Za-z_]\w*$", op):
                fnpend.append(len(sink))
                sink.append((t, ("L", rel, fn, op), f"{binary}/{addr_of(fn)}:{op}", where))
            continue
        if re.match(r"[A-Za-z_]\w*$", nxt) and nxt not in KEYWORDS:  # declaration N [*]ident
            after = toks[j + 1] if j + 1 < n else ""
            in_params = [p for p in parens if p[0]]
            if after == "(" and not in_params:                         # N *fn(...): the return
                sink.append((t, ("R", binary, nxt), f"{addr_of(nxt)}(ret)", where))
            elif in_params:
                p = in_params[-1]
                (hdrpend if depth == 0 else []).append(len(sink))
                sink.append((t, ("P", binary, p[0], p[1]), f"{addr_of(p[0])}(arg{p[1]})", where))
            elif depth == 0 and knr and nxt in knr[1]:
                ix = knr[1].index(nxt)
                hdrpend.append(len(sink))
                sink.append((t, ("P", binary, knr[0], ix), f"{addr_of(knr[0])}(arg{ix})", where))
            elif DSYM.match(nxt):
                sink.append((t, ("G", nxt), "0x" + nxt[2:].upper(), where))
            elif fn:
                fnpend.append(len(sink))
                sink.append((t, ("L", rel, fn, nxt), f"{binary}/{addr_of(fn)}:{nxt}", where))
            elif depth == 0:
                sink.append((t, ("G", binary, nxt), nxt, where))
            else:
                sink.append((t, ("F", rel, nxt), f"field {nxt}", where))
            continue
        if nxt in (")", ",") and stars and parens and parens[-1][0]:  # abstract declarator in a prototype
            p = parens[-1]
            sink.append((t, ("P", binary, p[0], p[1]), f"{addr_of(p[0])}(arg{p[1]})", where))
    # a global's using routine: the per-overlay instances of one routine's table bind one object ("AG", counted cross-binary)
    for ix in range(s0, len(sink)):
        nm, key, cite, where = sink[ix]
        if key[0] == "G" and len(key) == 2:
            for fa in sorted(used_by.get(key[1], ())):
                sink.append((nm, ("AG", fa, binary), cite, where))


def struct_map_join(census):
    """(G key -> clusters, (tu, fn, ident) -> cluster) from body_base_type.json, or empty maps"""
    p = census / "body_base_type.json"
    g, loc = collections.defaultdict(set), {}
    if not p.exists():
        return g, loc, False
    for body, bases in json.loads(p.read_text()).items():
        tu, _, fn = body.partition("|")
        for b, e in bases.items():
            cls, _, base = b.partition(":")
            if cls in ("global", "gaddr") and DSYM.match(base):
                g[base].add(e["type"])
            elif cls in ("local", "param"):
                loc[(tu, addr_of(fn), base)] = e["type"]
    return g, loc, True


def scan_all(wanted):
    """name -> key -> [cite, [where]] over src/ and include/"""
    sink = []
    files = sorted(p for d in ("src", "include") for p in (REPO / d).rglob("*") if p.suffix in (".c", ".h") and p.is_file())
    for p in files:
        rel = str(p.relative_to(REPO))
        if p.name.startswith(".cdecl"):
            continue
        text = p.read_text(errors="replace")
        if not set(re.findall(r"[A-Za-z_]\w*", text)) & wanted:
            continue
        scan_file(rel, text, wanted, sink)
    bind = collections.defaultdict(dict)
    for name, key, cite, where in sink:
        e = bind[name].setdefault(key, [cite, []])
        e[1].append(where)
    return bind


def t3_targets(folds_text):
    """(pure) {define target: map type} for the config/type_folds.tsv rows under a `# T3` comment line (P3.40 T3 band defs, T3.c3)"""
    out, t3 = {}, False
    for line in folds_text.splitlines():
        if line.startswith("#"):
            t3 = t3 or line.startswith("# T3")
            continue
        p = line.split("\t")
        if t3 and len(p) >= 3 and p[1] == "define":
            out[p[2]] = p[0]
    return out


def t3_site_cites(lines, mtypes, cap=3):
    """(pure) {map type: [<binary>/0x<fn addr>, …]} from census sites.jsonl lines: the distinct addressed bodies using each map type,
    sorted, capped (a T3 band def is dead until rung S draws it, so its map type's use sites are its only addressed evidence)"""
    acc = collections.defaultdict(set)
    for line in lines:
        i = line.rfind('"type": "')
        if i < 0 or line[i + 9:line.index('"', i + 9)] not in mtypes:
            continue
        s = json.loads(line)
        ci = f"{binary_of(s['tu'])}/{addr_of(s.get('fn') or '')}"
        if has_addr(ci):
            acc[s["type"]].add(ci)
    return {t: sorted(v)[:cap] for t, v in acc.items()}


def collect(census):
    rows = load_rows(census)
    wanted = {nm for r in rows for nm in r["names"]}
    bind = scan_all(wanted)                       # name -> key -> (cite, [where])
    # T3.c3: an unbound T3 band def (type_folds `define` target) cites its map type's census use sites as U evidence
    fp = REPO / "config" / "type_folds.tsv"
    t3 = {nm: mt for nm, mt in (t3_targets(fp.read_text()) if fp.exists() else {}).items()
          if nm in wanted and not any(k[0] not in ("F", "AG", "U") for k in bind.get(nm, {}))}
    if t3 and (census / "sites.jsonl").exists():
        with open(census / "sites.jsonl") as fh:
            sc_ = t3_site_cites(fh, set(t3.values()))
        for nm, mt in t3.items():
            for ci in sc_.get(mt, ()):
                bind[nm][("U", ci)] = [ci, [f"T3 map type {mt}"]]
    # a type naming an unbound name as a member / alias (U owner): its own bound objects locate the use (one level)
    unb = {nm for nm in wanted if not any(k[0] not in ("F", "AG", "U") for k in bind.get(nm, {}))}
    owners = {k[1] for nm in unb for k in bind.get(nm, {}) if k[0] == "U" and "/" not in k[1]}
    obind = scan_all(owners) if owners else {}
    owner_objs = {o: cites(obind.get(o, {}), cap=3) for o in owners}
    psyq = psyq_layouts()
    out = []
    for r in rows:
        base = r["lhash"].split(":")[0]
        sdk = sorted(psyq.get(base, ()))
        owners = collections.defaultdict(set)
        for nm in r["names"]:
            for key in bind.get(nm, {}):
                if key[0] == "AG":
                    owners[key[:2]].add((nm, key[2]))
                elif key[0] not in ("F", "U"):
                    owners[key].add((nm, None))
        shared = {k: {nm for nm, _ in v} for k, v in owners.items()
                  if len({nm for nm, _ in v}) > 1 and (k[0] != "AG" or len({b for _, b in v}) > 1)}
        unbound = [nm for nm in r["names"] if not any(k[0] not in ("F", "AG", "U") for k in bind.get(nm, {}))]
        klass = "SHARED" if shared else "UNBOUND" if unbound else "SEPARATE"
        out.append(dict(r, klass=klass, sdk=sdk, shared=shared, unbound=unbound, owner_objs=owner_objs, t3={nm: t3[nm] for nm in unbound if nm in t3},
                        bind={nm: bind.get(nm, {}) for nm in r["names"]}))
    return out


def has_addr(ci):
    return "0x" in ci or re.search(r"80[0-9A-Fa-f]{6}", ci) is not None


def cites(objs, cap=MAX_CITES, kinds=None):
    cs = sorted({c for k, (c, _) in objs.items() if (k[0] in kinds if kinds else k[0] not in ("F", "U"))},
                key=lambda c: (not has_addr(c), c))
    return cs[:cap], len(cs)


def uses(c, nm):
    """an unbound name's use-site cites: the using functions, the types naming it (member / alias) with their own objects"""
    def one(ci):
        if "/" in ci:
            return ci
        cs, total = c["owner_objs"].get(ci, ([], 0))
        return f"type {ci}" + (f" ({', '.join(cs)}{' …' if total > len(cs) else ''})" if cs else "")
    return sorted({one(ci) for k, (ci, _) in c["bind"][nm].items() if k[0] == "U"}, key=lambda x: (not has_addr(x), x))


def section(c):
    """the `### <lhash>` text, or None when its cause would carry no address (UNBOUND without addressed use sites)"""
    names = sorted(c["names"])
    unb = set(c["unbound"]) if c["klass"] == "UNBOUND" else set()
    allc = sorted({ci for nm in names if nm not in unb for k, (ci, _) in c["bind"][nm].items() if k[0] not in ("F", "U")})
    addr = [x for x in allc if "0x" in x]
    head = f"cause: {len(names)} names ({c['size']} B, all members placeholders)"
    bound = (f"bound to {len(allc)} distinct objects, none bound to two names: {', '.join(addr[:MAX_CITES])}"
             f"{' …' if len(addr) > MAX_CITES else ''}")
    if unb:
        ua = sorted({u for nm in unb for u in uses(c, nm) if has_addr(u)})
        if not ua and not addr:
            return None
        t3 = c.get("t3") or {}
        t3n = (f"; {len(t3)} T3 band def{'s' if len(t3) > 1 else ''}, dead until rung S; map type "
               + ", ".join(f"{t3[nm]} ({nm})" for nm in sorted(t3))) if t3 else ""
        cause = (f"{head}; {len(unb)} bound to no object (UNBOUND), used only by: {', '.join(ua[:MAX_CITES]) or 'no addressed site'}"
                 f"{' …' if len(ua) > MAX_CITES else ''}" + t3n + (f"; the other {len(names) - len(unb)} {bound}" if len(unb) < len(names) else ""))
    else:
        cause = f"{head} {bound}"
    if c["sdk"]:
        cause += f"; same layout as PsyQ {', '.join(c['sdk'])}, no name of the row bound to it"
    lines = [f"### {c['lhash']}", "names: " + ", ".join(names), cause + f"; full list: tools/struct_twins.py --show {c['lhash']}"]
    for nm in names:
        if nm in unb:
            us = uses(c, nm)
            t3m = (c.get("t3") or {}).get(nm)
            lines.append(f"- `{nm}`: 0 obj — " + (f"T3 band def, dead until rung S; map type {t3m}; " if t3m else "")
                         + f"used by {', '.join(us[:MAX_CITES]) if us else 'nothing outside its definition'}"
                         f"{f' (+{len(us) - MAX_CITES})' if len(us) > MAX_CITES else ''}")
            continue
        cs, total = cites(c["bind"][nm])
        more = f" (+{total - len(cs)})" if total > len(cs) else ""
        lines.append(f"- `{nm}`: {total} obj — {', '.join(cs)}{more}")
    return "\n".join(lines)


def write(classes):
    text = TWINS_DOC.read_text()
    m = re.search(r"(?m)^## Twins[ \t]*\n", text)
    if not m:
        sys.exit("struct_twins: no `## Twins` heading in docs/struct-twins.md")
    rest = re.search(r"(?m)^## ", text[m.end():])
    end = m.end() + rest.start() if rest else len(text)
    # fixed order (rows move between dup_gating.tsv and the listed set as the doc changes): most names first, then lhash
    secs = [(c, section(c)) for c in sorted(classes, key=lambda c: (-len(c["names"]), c["lhash"]))
            if c["klass"] in ("SEPARATE", "UNBOUND")]
    body = "\n\n".join(s for _c, s in secs if s)
    body = ("<!-- generated by tools/struct_twins.py --write; regenerate, do not hand-edit -->\n\n" + body + "\n\n") if body else "\n"
    TWINS_DOC.write_text(text[:m.end()] + "\n" + body + text[end:])
    return [s for s in secs if s[1]], [c for c, s in secs if not s]


def main():
    ap = argparse.ArgumentParser(description=__doc__.split("\n")[0])
    ap.add_argument("--census-dir", default=CENSUS_DEFAULT)
    ap.add_argument("--write", action="store_true", help="regenerate the `## Twins` section of docs/struct-twins.md")
    ap.add_argument("--show", metavar="LHASH", help="every name's objects for one class")
    a = ap.parse_args()
    census = REPO / a.census_dir
    classes = collect(census)
    if a.show:
        c = next((c for c in classes if c["lhash"] == a.show), None)
        if not c:
            sys.exit(f"struct_twins: {a.show} is not a tier-2 row of {census}/dup_gating.tsv")
        g, loc, have = struct_map_join(census)
        print(f"{c['lhash']} {c['size']} B · {len(c['names'])} names · {c['klass']}" + ("" if have else " (no body_base_type.json: run the census with --sites for struct_map clusters)"))
        for nm in sorted(c["names"]):
            print(f"{nm}:")
            for k, (ci, wh) in sorted(c["bind"][nm].items(), key=lambda kv: kv[1][0]):
                lk = (wh[0].rsplit(":", 1)[0], ci.split("/")[-1].rsplit(":", 1)[0], k[-1]) if k[0] == "L" else None
                sm = sorted(g.get(k[1], ())) if k[0] == "G" else [loc[lk]] if lk in loc else []
                print(f"  {ci:<28} {k[0]}  {wh[0]}{f' (+{len(wh) - 1})' if len(wh) > 1 else ''}"
                      f"{'  struct_map ' + ','.join(sm[:4]) if sm else ''}")
        return
    cnt = collections.Counter(c["klass"] for c in classes)
    print(f"struct_twins: {len(classes)} tier-2 rows · SEPARATE {cnt['SEPARATE']} · SHARED {cnt['SHARED']} · "
          f"UNBOUND {cnt['UNBOUND']} · (SDK layout {sum(1 for c in classes if c['sdk'])})")
    for c in classes:
        if c["klass"] == "SHARED":
            def cite_of(k, nm):
                return next(ci for kk, (ci, _) in sorted(c["bind"][nm].items()) if kk[:len(k)] == k)
            k, v = min(c["shared"].items(), key=lambda kv: (-len(kv[1]), cite_of(kv[0], min(kv[1]))))
            ci = cite_of(k, min(v)) + (f" (routine {k[1]})" if k[0] in ("A", "AG") else "")
            print(f"  SHARED {c['lhash']} ({len(c['names'])} names, {len(c['shared'])} shared objects): e.g. {ci} <- {', '.join(sorted(v)[:6])}"
                  f"{' …' if len(v) > 6 else ''}")
        elif c["klass"] == "UNBOUND":
            noaddr = [nm for nm in c["unbound"] if not any(has_addr(u) for u in uses(c, nm))]
            print(f"  UNBOUND {c['lhash']} ({len(c['names'])} names): {', '.join(c['unbound'][:6])}{' …' if len(c['unbound']) > 6 else ''}"
                  + (f"; no addressed use: {', '.join(noaddr)}" if noaddr else ""))
        if c["sdk"] and c["klass"] != "SEPARATE":
            print(f"         {c['lhash']}: same layout as PsyQ {', '.join(c['sdk'])}")
    if a.write:
        done, left = write(classes)
        print(f"struct_twins: wrote {len(done)} `### <lhash>` sections to docs/struct-twins.md ## Twins")
        for c in left:
            print(f"  NOT WRITTEN {c['lhash']}: no address in any bound object or use site of {', '.join(c['unbound'])}")


if __name__ == "__main__":
    main()
