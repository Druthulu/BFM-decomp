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
  tools/struct_twins.py --inventory [--out FILE]    one row per struct/union definition of the canonical type files and
                                                    include/psyq/ (default .run/3.45/t1/struct_inventory.tsv); prints the denominators
  tools/struct_twins.py --dispositions [--check] [--ledger PATH]
                                                    write/refresh config/struct_dispositions.tsv (one row per placeholder; new rows
                                                    `undisposed`, existing dispositions kept); --check: counts per disposition and class,
                                                    FAIL (exit 1) on a missing, duplicate or unknown row or a column rule (LEDGER_HEAD)
  tools/struct_twins.py --links [--out-dir DIR] [-j N] [--propose [--policy typed|effective|views]] [--report [PATH]]
                                                    the merge-evidence census (3.45 T2; method docs/ops/p345-t2-struct-merge-evidence.md):
                                                    links (global / body / pointer incl. arg-eff, view), refusals, widths, size facts,
                                                    hubs, components, proposals per policy (typed, effective, views: one run computes all
                                                    three) -> DIR (default .run/3.45/t2) {links,refused,hubs,components,proposals}.<policy>.tsv
                                                    and {widths,sizes,eff,poly,decl_param,twins,unplaced}.tsv; sorted summary on stdout.
                                                    --propose writes the policy's (default effective) proposals into the ledger (rows whose
                                                    reason ends in `applied:<commit>` kept). T2.c4: outside policy typed the hub test keys
                                                    slots by h_exact copies and refuses hub types' pointer links (hubtypes.<policy>.tsv);
                                                    --report [PATH] writes the generated report (default docs/ops/p345-struct-merge-report.md).
                                                    T2.c5: cast-view accesses (`((T *)x)->f`, any x) feed the width maps (all policies) and,
                                                    through a parameter (or its single-source local), the parameter slot's own offsets.
                                                    Needs a built tree (build/**/*.d, the ELFs)
                                                    and fresh build/sig_evidence/census.jsonl + .run/sig.<alias>.jsonl: exit 2 otherwise
  tools/struct_twins.py --selftest                  the --links fixtures on a synthetic tree (own symtab, .d map, sig rows); exit 0 iff all pass
  (--links / --selftest import sig_evidence, which needs rabbitizer: the tool re-execs itself under .venv/bin/python when missing)

Inventory (3.45 T1): one type = one definition record (enum skipped); names = typedef names + tag + the plain
`typedef struct X Y;` aliases resolving to it; key = first typedef name, else tag, else `<anon>@file:line` (a repeated key gets
`@file:line`). class: PsyQ (defined in include/psyq/, or a PSYQ name whose layout hash is psyq_layouts()'), ledgered (a
config/names.tsv `type` row names it), else placeholder. block: the generated region holding the line (head_types markers,
restruct band / drift markers, the hand-copied head_types region from its `/* --- T2 (P3.40) canonical definitions` comment to
the next marker), else `-`. Users: tus/binaries = the src/ and include/ files outside the canonical ones whose comment-stripped
tokens name it (binary_of); globals/params/returns/locals = G/P/R/L object keys of scan_all over every inventoried name; h_exact
= distinct function identities among its L/P keys; access_sites (lexical) = `ident->` / `ident.` occurrences of each L/P-bound
identifier inside the top-level brace span of its binding line (a definition's header: the span opening within 8 lines below),
and of each G-bound identifier in the binding's whole file, each (file, span, ident) counted once.
"""
import argparse
import bisect
import collections
import hashlib
import json
import os
import re
import sys
from pathlib import Path

REPO = Path(__file__).resolve().parent.parent
sys.path.insert(0, str(REPO / "tools"))
import type_census as tc   # noqa: E402
from struct_layout import UNK_RX, PAD_RX   # noqa: E402  (3.45 T1: the inventory's unk / pad field counts)
from struct_layout import field_offsets, scalar_of   # noqa: E402  (3.45 T2 --links: member offsets and widths)
se = None   # sig_evidence (3.45 T2 --links: the .d / ELF / placement join), imported by need_se(): it needs rabbitizer (.venv)
CENSUS_DEFAULT = tc.OUT_DIR_DEFAULT   # 3.41 T2: the gate dir, read from type_census (was a stale ".run/P38/census" literal)
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


INVENTORY_DEFAULT = ".run/3.45/t1/struct_inventory.tsv"
LEDGER = REPO / "config" / "struct_dispositions.tsv"
DISPOSITIONS = ("undisposed", "fold", "apart", "no-evidence")
LEDGER_COLS = ("key", "kind", "file_line", "size", "disposition", "target", "class", "evidence", "reason")   # class: T2.c2
CLASSES = {"undisposed": ("-",), "fold": ("global", "pointer", "body"), "apart": ("own", "conflict", "size", "hub"), "no-evidence": ("-",)}
APPLIED_RX = re.compile(r"(?:^|\s)applied:\S+$")    # a disposition applied by a later task (T7): never rewritten by --propose
CITE_RX = re.compile(r"0x[0-9A-Fa-f]{8}|[\w./-]+\.[ch]:\d+")   # an address or a file:line (apart evidence)
LEDGER_HEAD = """# config/struct_dispositions.tsv: the struct disposition ledger (Phase 3.45 T1; `class` T2.c2). One row per placeholder struct/union
# definition of the canonical type files (tools/struct_twins.py --inventory, class placeholder), keyed by its inventory key.
# disposition (closed list): undisposed (not judged yet) | fold (fold into `target`; `evidence` cites the shared object) |
#   apart (kept apart; `evidence` cites what separates it) | no-evidence (no binding or use to judge by; `reason` says why).
# class (closed list per disposition): fold global|pointer|body (the evidence class of the link that admitted it; T2.c3: a
#   body-view link is class body, an eff-flow link class pointer) |
#   apart own|conflict|size|hub (its own objects, or the refusal that keeps it apart) | no-evidence and undisposed `-`.
# Proposals: tools/struct_twins.py --links --propose [--policy typed|effective|views] (default effective; method
#   docs/ops/p345-t2-struct-merge-evidence.md) rewrites disposition..reason of every row on each run; fold and component-target
#   evidence starts `C<n>: ` (the run's component). A row whose reason ends in ` applied:<commit>` (the commit that applied it,
#   T7) is never rewritten.
# Written by tools/struct_twins.py --dispositions (new rows undisposed, dispositions kept, kind/file_line/size refreshed);
# checked by tools/struct_twins.py --dispositions --check (FAIL on a missing, duplicate or unknown row, a class outside its
#   closed list, a fold whose target is not a ledger key or a PsyQ/ledgered type, an apart without an address or file:line in
#   its evidence, a no-evidence without a reason). Tab-separated, by key.
"""
INV_COLS = ("key", "names", "tag", "kind", "size", "fields_total", "unk", "pad", "named", "file:line", "block", "class", "tus",
            "binaries", "h_exact", "access_sites", "globals", "params", "returns", "locals")
HAND_COPIED = "/* --- T2 (P3.40) canonical definitions"   # head_types output copied into struct_types.h by hand (no end marker)


def blocks_of(lines):
    """(pure) [(first line, last line, block)] of the generated regions in one header's lines (1-based)"""
    import head_types as ht
    import restruct as rs
    out = []
    for b, e, nm in ((ht.C_BEGIN, ht.C_END, "head_types"), (rs.T3_BEGIN, rs.T3_END, "restruct-band"),
                     (rs.T17_BEGIN, rs.T17_END, "restruct-drift")):
        s = next((i for i, ln in enumerate(lines, 1) if b in ln), None)
        if s:
            out.append((s, next((i for i, ln in enumerate(lines[s:], s + 1) if e in ln), len(lines)), nm))
    s = next((i for i, ln in enumerate(lines, 1) if ln.startswith(HAND_COPIED)), None)
    if s:
        out.append((s, min([b0 - 1 for b0, _, _ in out if b0 > s] or [len(lines)]), "head_types-hand"))
    return out


def type_universe(texts=None):
    """dict(defs, tds, blocks, g): the definitions, alias typedefs and generated blocks of the canonical files and include/ (or
    of `texts` {rel: raw}, the --selftest tree), and g: name -> definition / alias record (the Resolver's map)"""
    files = (sorted(texts) if texts is not None else
             list(dict.fromkeys(list(tc.CANON_HEADERS) + sorted(str(p.relative_to(REPO)) for p in (REPO / "include").rglob("*.h")))))
    defs, tds, blocks = [], [], {}
    for rel in files:     # resolution sees every header psyq_layouts() walks; rows come from the canonical files and include/psyq/
        raw = texts[rel] if texts is not None else (REPO / rel).read_text(errors="replace")
        r = tc.walk_file(raw, rel)
        defs += r["definitions"]
        tds += r["typedef_aliases"]
        blocks[rel] = blocks_of(raw.splitlines())
    g = {}
    for d in defs:
        for nm in d["names"] + ([d["tag"]] if d["tag"] else []):
            g.setdefault(nm, d)
    for a in tds:
        g.setdefault(a["name"], dict(kind="alias", alias_of=a["alias_of"], alias_stars=a["alias_stars"], alias_dims=a["alias_dims"]))
    return dict(defs=defs, tds=tds, blocks=blocks, g=g)


def inventory_defs(u=None):
    """the inventory rows without users: every struct/union definition of the canonical files and include/psyq/ (each row
    carries its definition record as `def`, for --links)"""
    u = u or type_universe()
    defs, tds, blocks, g = u["defs"], u["tds"], u["blocks"], u["g"]
    alias = {a["name"]: a for a in tds}
    extra = collections.defaultdict(list)
    for a in tds:
        nm = a["name"]
        for _ in range(8):
            x = alias.get(nm)
            if not x or x["alias_stars"] or x["alias_dims"] or x.get("fnptr"):
                break
            nm = re.sub(r"^(?:struct|union)\s+", "", x["alias_of"])
        d = g.get(nm)
        if nm != a["name"] and d is not None and d.get("kind") in ("struct", "union"):
            extra[id(d)].append(a["name"])
    ledg = {p[0] for p in (ln.split("\t") for ln in (REPO / "config" / "names.tsv").read_text().splitlines() if not ln.startswith("#"))
            if len(p) > 1 and p[1] == "type"}
    psyq, res, rows, seen = psyq_layouts(), tc.Resolver(g), [], set()
    for d in defs:
        if d["kind"] == "enum" or not (d["file"] in tc.CANON_HEADERS or d["file"].startswith("include/psyq/")):
            continue
        nms = list(dict.fromkeys(d["names"] + ([d["tag"]] if d["tag"] else []) + extra[id(d)]))
        key = d["names"][0] if d["names"] else d["tag"] or f"<anon>@{d['file']}:{d['line']}"
        if key in seen:
            key = f"{key}@{d['file']}:{d['line']}"
        seen.add(key)
        lay = res.layout_of_fields(d["fields"], d["kind"], packed=("packed" in d["attrs"]))
        fn = [f.get("name") or "" for f in d["fields"]]
        unk, pad = sum(1 for f in fn if UNK_RX.match(f)), sum(1 for f in fn if PAD_RX.match(f))
        klass = ("PsyQ" if d["file"].startswith("include/psyq/") or (set(nms) & PSYQ and lay and tc.layout_hash(lay) in psyq)
                 else "ledgered" if set(nms) & ledg else "placeholder")
        rows.append(dict(key=key, names=nms, tag=d["tag"] or "-", kind=d["kind"], size=lay[0] if lay else "?", fields_total=len(fn),
                         unk=unk, pad=pad, named=len(fn) - unk - pad, file_line=f"{d['file']}:{d['line']}",
                         block=next((nm for b0, b1, nm in blocks[d["file"]] if b0 <= d["line"] <= b1), "-"), klass=klass, **{"def": d}))
    return rows


def inventory_users(rows):
    """add tus, binaries, h_exact, access_sites, globals, params, returns, locals to each row (method: the module docstring)"""
    wanted = {nm for r in rows for nm in r["names"]}
    bind = scan_all(wanted)
    canon, tus, src = set(tc.CANON_HEADERS), collections.defaultdict(set), {}
    for p in sorted(p for dd in ("src", "include") for p in (REPO / dd).rglob("*") if p.suffix in (".c", ".h") and p.is_file()):
        rel = str(p.relative_to(REPO))
        if rel in canon or p.name.startswith(".cdecl"):
            continue
        for nm in set(re.findall(r"[A-Za-z_]\w*", COMMENT.sub(" ", p.read_text(errors="replace")))) & wanted:
            tus[nm].add(rel)

    def text_of(rel):     # (comment-stripped text, its lines, top-level brace spans as (first line, last line, start, end))
        if rel not in src:
            t = COMMENT.sub(lambda m: re.sub(r"[^\n]", " ", m.group(0)), (REPO / rel).read_text(errors="replace"))
            spans, depth, s = [], 0, 0
            for m in re.finditer(r"[{}]", t):
                if m.group(0) == "{":
                    depth, s = depth + 1, (m.start() if depth == 0 else s)
                elif depth:
                    depth -= 1
                    if not depth:
                        spans.append((t.count("\n", 0, s) + 1, t.count("\n", 0, m.end()) + 1, s, m.end()))
            src[rel] = (t, t.split("\n"), spans)
        return src[rel]
    memo = {}

    def acc(rel, span, ident):
        if (rel, span, ident) not in memo:
            t = text_of(rel)[0]
            t = t[span[2]:span[3]] if span else t
            memo[(rel, span, ident)] = len(re.findall(r"(?<![\w.>])" + re.escape(ident) + r"\s*(?:->|\.(?!\.))", t))
        return memo[(rel, span, ident)]
    for r in rows:
        objs = {k: e for nm in r["names"] for k, e in bind.get(nm, {}).items()}
        sites = set()
        for k, (ci, wh) in objs.items():
            if k[0] not in ("L", "P", "G"):
                continue
            for w in wh:
                rel, ln = w.rsplit(":", 1)
                ln = int(ln)
                if k[0] == "G":
                    sites.add((rel, None, k[-1]))
                    continue
                t, lines, spans = text_of(rel)
                sp = next((s for s in spans if s[0] <= ln <= s[1]), None) or next((s for s in spans if 0 < s[0] - ln <= 8), None)
                if k[0] == "L":
                    ident = k[-1]
                else:
                    m = re.search(r"\b(?:" + "|".join(map(re.escape, r["names"])) + r")\b[\s*]*(?:(?:const|volatile)\b[\s*]*)*([A-Za-z_]\w*)",
                                  lines[ln - 1] if ln <= len(lines) else "")
                    ident = m.group(1) if m else None
                if sp and ident:
                    sites.add((rel, sp, ident))
        users = {rel for nm in r["names"] for rel in tus.get(nm, ())}
        r.update(tus=len(users), binaries=len({binary_of(u) for u in users}),
                 h_exact=len({k[1] for k in objs if k[0] in ("L", "P") and str(k[1]).startswith("F:")}),
                 access_sites=sum(acc(*s) for s in sites), **{c: sum(1 for k in objs if k[0] == x) for c, x in
                                                              (("globals", "G"), ("params", "P"), ("returns", "R"), ("locals", "L"))})


def inventory(out):
    rows = inventory_defs()
    inventory_users(rows)
    out = REPO / out
    out.parent.mkdir(parents=True, exist_ok=True)
    with open(out, "w") as fh:
        fh.write("\t".join(INV_COLS) + "\n")
        for r in sorted(rows, key=lambda r: r["key"]):
            fh.write("\t".join(str(",".join(r["names"]) if c == "names" else r["file_line"] if c == "file:line"
                                   else r["klass"] if c == "class" else r[c]) for c in INV_COLS) + "\n")
    ph = [r for r in rows if r["klass"] == "placeholder"]
    fk = collections.Counter((r["file_line"].rsplit(":", 1)[0] if not r["file_line"].startswith("include/psyq/") else "include/psyq/",
                              r["kind"]) for r in rows)
    cl = collections.Counter(r["klass"] for r in rows)
    used = sum(1 for r in ph if r["tus"] or r["globals"] or r["params"] or r["returns"] or r["locals"])
    print(f"struct_twins --inventory: {len(rows)} definitions -> {out.relative_to(REPO)}")
    print("  by file x kind: " + " · ".join(f"{f} {k} {n}" for (f, k), n in sorted(fk.items())))
    print(f"  by class: PsyQ {cl['PsyQ']} · ledgered {cl['ledgered']} · placeholder {cl['placeholder']}")
    print(f"  placeholders {len(ph)} · with users {used} · without users {len(ph) - used}")
    print(f"  unresolved sizes {sum(1 for r in rows if r['size'] == '?')} (placeholders {sum(1 for r in ph if r['size'] == '?')})"
          f" · repeated keys disambiguated {sum(1 for r in rows if '@' in r['key'] and not r['key'].startswith('<anon>'))}")


def ledger_read(ledger):
    """the ledger's rows {key: {col: value}}, duplicate keys, malformed keys; a pre-T2.c2 row (no `class`) reads class `-`"""
    have, dup, bad = {}, [], []
    for ln in (ledger.read_text().splitlines() if ledger.exists() else ()):
        if ln.startswith("#") or not ln.strip() or ln.startswith("key\t"):
            continue
        p = ln.split("\t")
        if len(p) == len(LEDGER_COLS) - 1:
            p = p[:6] + ["-"] + p[6:]
        if len(p) != len(LEDGER_COLS) or p[4] not in DISPOSITIONS:
            bad.append(ln.split("\t")[0])
        (dup if p[0] in have else []).append(p[0])
        have.setdefault(p[0], dict(zip(LEDGER_COLS, p)))
    return have, dup, bad


def ledger_problems(have, keys_ok):
    """(pure) [(what, [keys])] of the rows breaking the column rules (LEDGER_HEAD)"""
    out = collections.defaultdict(list)
    for k, e in sorted(have.items()):
        d = e.get("disposition")
        if d not in CLASSES:
            continue
        if e.get("class") not in CLASSES[d]:
            out[f"class outside the closed list of {d}"].append(k)
        if d == "fold" and (e.get("target") in (None, "", "-", k) or e["target"] not in keys_ok):
            out["fold without a ledger / PsyQ / ledgered target"].append(k)
        if d == "apart" and not CITE_RX.search(e.get("evidence") or ""):
            out["apart without an address or file:line in evidence"].append(k)
        if d == "no-evidence" and (e.get("reason") or "-") == "-":
            out["no-evidence without a reason"].append(k)
    return sorted(out.items())


def ledger_write(ledger, ph, have, props=None):
    """write the ledger: one row per placeholder (ph {key: inventory row}) plus the disposed stale rows; props {key: (disposition,
    target, class, evidence, reason)} replaces a row's judgement unless its reason carries the applied marker -> (new, kept, applied)"""
    kept = {k: e for k, e in have.items() if k not in ph and e.get("disposition") != "undisposed"}
    lines, applied = [LEDGER_HEAD.rstrip("\n"), "\t".join(LEDGER_COLS)], 0
    for k in sorted(set(ph) | set(kept)):
        r, e = ph.get(k), have.get(k) or {}
        vals = [e.get("disposition", "undisposed")] + [e.get(c) or "-" for c in ("target", "class", "evidence", "reason")]
        if props and k in props:
            if APPLIED_RX.search(e.get("reason") or ""):
                applied += 1
            else:
                vals = list(props[k])
        lines.append("\t".join([k, r["kind"] if r else e["kind"], r["file_line"] if r else e["file_line"],
                                str(r["size"]) if r else e["size"]] + vals))
    ledger.write_text("\n".join(lines) + "\n")
    return len(set(ph) - set(have)), len(kept), applied


def dispositions(ledger, check):
    """write/refresh the ledger, or (check) count it and FAIL on a missing, duplicate or unknown row or a broken column rule"""
    rows = inventory_defs()
    ph = {r["key"]: r for r in rows if r["klass"] == "placeholder"}
    have, dup, bad = ledger_read(ledger)
    if check:
        miss, unk = sorted(set(ph) - set(have)), sorted(set(have) - set(ph))
        cnt = collections.Counter(e.get("disposition") for e in have.values())
        cc = collections.Counter((e.get("disposition"), e.get("class")) for e in have.values() if e.get("disposition") != "undisposed")
        prob = ledger_problems(have, set(have) | {r["key"] for r in rows if r["klass"] in ("PsyQ", "ledgered")})
        print(f"struct_twins --dispositions --check: placeholders {len(ph)} · undisposed {cnt['undisposed']} · rows {len(have) + len(dup)}"
              f" · " + " · ".join(f"{d} {cnt[d]}" for d in DISPOSITIONS[1:]))
        print("  by class: " + (" · ".join(f"{d}/{c} {n}" for (d, c), n in sorted(cc.items())) or "-"))
        for what, ks in (("missing", miss), ("duplicate", dup), ("unknown key", unk), ("malformed / unknown disposition", bad)) + tuple(prob):
            if ks:
                print(f"  FAIL {what}: {len(ks)} ({', '.join(ks[:8])}{' …' if len(ks) > 8 else ''})")
        sys.exit(1 if miss or dup or unk or bad or prob else 0)
    new, kept, _ = ledger_write(ledger, ph, have)
    print(f"struct_twins --dispositions: {len(ph)} placeholders -> {ledger.relative_to(REPO) if ledger.is_relative_to(REPO) else ledger}"
          f" · new {new} · kept stale (disposed, no longer a placeholder) {kept}")


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


def scan_file(rel, text, wanted, sink, detail=None):
    """append (name, key, cite, where) for every binding of a wanted name in one file; `detail` (3.45 T2 --links), when given,
    maps a declaration's or cast's sink index to dict(form decl|cast, ident, stars, arr, ext, amp, line, fn)"""
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
            if detail is not None and (DSYM.match(op) or fn and re.match(r"[A-Za-z_]\w*$", op)):
                detail[len(sink)] = dict(form="cast", ident=op, stars=stars, arr=False, ext=False, amp="&" in toks[j + 1:m],
                                         line=lines[i], fn=fn, tail=tuple(toks[m + 1:m + 4]))
            if DSYM.match(op):
                sink.append((t, ("G", op), "0x" + op[2:].upper(), where))
            elif fn and re.match(r"[A-Za-z_]\w*$", op):
                fnpend.append(len(sink))
                sink.append((t, ("L", rel, fn, op), f"{binary}/{addr_of(fn)}:{op}", where))
            continue
        if re.match(r"[A-Za-z_]\w*$", nxt) and nxt not in KEYWORDS:  # declaration N [*]ident
            after = toks[j + 1] if j + 1 < n else ""
            in_params = [p for p in parens if p[0]]
            if detail is not None:
                detail[len(sink)] = dict(form="decl", ident=nxt, stars=stars, arr=after == "[", ext="extern" in toks[stmt:i],
                                         amp=False, line=lines[i], fn=fn)
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
    """(pure) {define target: map type} for the config/type_folds.tsv rows under a `# T3` comment line (P3.40 T3 band defs, T3.c3)
    or a `# T17` one (P3.40 T17 drift defs)"""
    out, t3 = {}, False
    for line in folds_text.splitlines():
        if line.startswith("#"):
            t3 = t3 or line.startswith(("# T3", "# T17"))
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


# ------------------------------------------------------------------------------------------------------------ --links (3.45 T2)
# Method: docs/ops/p345-t2-struct-merge-evidence.md, sections "Joins" through "Components", "DECL-PARAM", "Selftest fixtures".
LINKS_DIR = ".run/3.45/t2"
HUB_K = 4             # a slot linking >= HUB_K types ...
HUB_OFFS = 2          # ... while its own accesses touch <= HUB_OFFS offsets is a hub (a pool, list or header helper)
MIN_BODY_INS = 10     # body class: h_exact classes below this many instructions are coincident look-alikes (tiny-body)
POINTER_SUBS = ("decl", "arg", "arg-eff", "ret", "ret-of", "assign", "field", "store-global", "eff-flow", "view")   # T2.c2: arg-eff, view; T2.c3: eff-flow
POLICIES = ("typed", "effective", "views")   # T2.c2: typed slots; + arg-eff (the --propose default); + local views
HUB_TYPE_SUBS = ("arg", "arg-eff", "eff-flow", "assign", "field", "ret", "ret-of", "store-global", "view")   # T2.c4: a hub type's refused links
EFF_SUBS = ("arg-eff", "eff-flow", "body-view")   # sub-kinds resting on effective types / masked copies: not in policy typed (T2.c3)
ADDR_NAME = re.compile(r"^(?:func|D)_[0-9A-Fa-f]{6,8}")   # body-view: address names are relocations (h_exact equal), masked too
TOK_RX = re.compile(r"[A-Za-z_]\w*|0[xX][0-9A-Fa-f]+[uUlL]*|\d+[uUlL]*|->|<<=|>>=|\+\+|--|&&|\|\||[-+*/%&|^<>=!]=|<<|>>|\S")
DECL_RX = re.compile(r"(?:^|(?<=[;{}]))[ \t]*(?:(?:register|static|volatile|const)\s+)*((?:(?:unsigned|signed)\s+)?(?:void|char|s8|u8|s16|u16|s32"
                     r"|u32|int|short|long)\b(?:\s+(?:int|long|char|short)\b)?|unsigned\b|signed\b)([^;{}]*);", re.M)
SCALAR_WORDS = {"s8", "u8", "s16", "u16", "s32", "u32", "int", "char", "short", "long", "unsigned", "signed"}
BYTE_WORDS = {"char", "u8", "s8", "unsigned", "signed"}   # with one star: a byte pointer (untyped slot)
LINK_ORDER = [("global", "global"), ("global", "global-view"), ("body", "body"), ("body", "body-view")] + [("pointer", s) for s in POINTER_SUBS]
ID = r"[A-Za-z_]\w*"
TQUAL = {"const", "volatile", "struct", "union", "register", "static", "extern"}
IDX = r"(?:\s*\[[^\[\]]*\])"
CHAIN_RX = re.compile(r"(?<![\w.>\])])(&\s*)?(" + ID + r")(" + IDX + r"?)((?:\s*(?:->|\.(?![.\d]))\s*" + ID + IDX + r"*)+)")
STEP_RX = re.compile(r"\s*(->|\.)\s*(" + ID + r")(" + IDX + r"*)")
IDXS_RX = re.compile(r"\[([^\[\]]*)\]")
STORE_RX = re.compile(r"\s*(?:(?:[-+*/%&|^]|<<|>>)?=(?!=)|\+\+|--)")
LOAD_PRE = re.compile(r"(?<![\w.>])(" + ID + r")\s*=\s*(?:\(\s*(?:struct\s+|union\s+)?" + ID + r"\s*\**\s*\)\s*)?$")
STORE_POST = re.compile(r"\s*=(?!=)\s*(?:\(\s*(?:struct\s+|union\s+)?" + ID + r"\s*\**\s*\)\s*)?(" + ID + r")\s*;")
SIZEOF_RX = re.compile(r"\bsizeof\s*\(\s*(?:(struct|union)\s+)?(\*\s*)?(" + ID + r")\s*(\[\s*0\s*\])?\s*\)")
PINC_RX = re.compile(r"(?<![\w.>])(" + ID + r")\s*(\+\+|--|[-+]=)|(\+\+|--)\s*(" + ID + r")(?!\s*(?:->|\.|\[))")
PADD_RX = re.compile(r"(?<![\w.>])(" + ID + r")\s*([-+])(?![-+=>])\s*(?=[\w(])")
PIDX_RX = re.compile(r"(?<![\w.>])(" + ID + r")\s*\[\s*([^\[\]]*?)\s*\]")
VIEW_RX = re.compile(r"\(\s*\(\s*(?:struct\s+|union\s+)?(" + ID + r")\s*\*\s*\)\s*(" + ID + r")\s*\)\s*(?:->\s*(" + ID + r")|\[)")
VACC_RX = re.compile(r"(?<![\w\])])(&\s*)?\(\s*(\*\s*)?\(\s*(?:(?:const|volatile)\s+)*(?:struct\s+|union\s+)?(" + ID + r")\s*\*\s*\)")   # T2.c5
VSTEP_RX = re.compile(r"(" + IDX + r"?)((?:\s*(?:->|\.(?![.\d]))\s*" + ID + IDX + r"*)+)")
COPY_RX = re.compile(r"\*\s*(" + ID + r")\s*=(?!=)\s*\*\s*(" + ID + r")\s*;")
DEREF_RX = re.compile(r"\*\s*(" + ID + r")\b(?!\s*\()")
LIT_RX = re.compile(r"^(0x[0-9A-Fa-f]+|\d+)[uUlL]*$")
_LWANTED = set()


def need_se():
    """import sig_evidence for --links / --selftest; without rabbitizer it would re-exec ITSELF under .venv (with our argv), so
    re-exec this tool there first, as sig_evidence does"""
    global se
    if se is None:
        try:
            import rabbitizer   # noqa: F401
        except ImportError:
            venv = REPO / ".venv" / "bin" / "python"
            if os.environ.get("STRUCT_TWINS_REEXEC") or not venv.exists():
                raise
            os.environ["STRUCT_TWINS_REEXEC"] = "1"
            os.execv(str(venv), [str(venv), str(Path(__file__).resolve()), *sys.argv[1:]])
        import sig_evidence
        se = sig_evidence
    return se


def _blank(text):
    """comments and strings blanked, directive lines (with continuations) emptied; newlines kept"""
    text = COMMENT.sub(lambda m: re.sub(r"[^\n]", " ", m.group(0)), text)
    return re.sub(r"(?m)^[ \t]*#(?:.*\\\n)*.*$", lambda m: "\n" * m.group(0).count("\n"), text)


def lex_events(text):
    """(pure) the lexical facts of one file: (kind, line, ...) with A access chains, Z sizeof, I pointer arithmetic, V view
    casts, C `*a = *b` copies, D unary dereferences; identifiers unresolved (phase 2 binds them)"""
    t = _blank(text)
    nl = [m.start() for m in re.finditer("\n", t)]

    def line(pos):
        return bisect.bisect_right(nl, pos - 1) + 1 if nl else 1
    ev = []
    for m in CHAIN_RX.finditer(t):
        steps = tuple((s.group(1), s.group(2), tuple(x.strip() for x in IDXS_RX.findall(s.group(3))))
                      for s in STEP_RX.finditer(m.group(4)))
        pre = t[max(0, m.start() - 160):m.start()]
        store = bool(STORE_RX.match(t, m.end())) or pre.rstrip().endswith(("++", "--"))
        ctx = None
        if not store and not m.group(1) and re.match(r"\s*;", t[m.end():m.end() + 8]):
            mp = LOAD_PRE.search(pre)
            if mp:
                ctx = ("L", mp.group(1))
        elif store and not m.group(1):
            ms = STORE_POST.match(t, m.end())
            if ms:
                ctx = ("S", ms.group(1))
        bidx = tuple(x.strip() for x in IDXS_RX.findall(m.group(3)))
        ev.append(("A", line(m.start(2)), bool(m.group(1)), m.group(2), bidx, steps, store, ctx))
    for m in SIZEOF_RX.finditer(t):
        ev.append(("Z", line(m.start()), bool(m.group(1)), bool(m.group(2)), m.group(3), bool(m.group(4))))
    for m in PINC_RX.finditer(t):
        ev.append(("I", line(m.start()), m.group(1) or m.group(4), m.group(2) or m.group(3)))
    for m in PADD_RX.finditer(t):
        ev.append(("I", line(m.start()), m.group(1), m.group(2)))
    for m in PIDX_RX.finditer(t):
        if m.group(2) != "0" and m.group(2):
            ev.append(("I", line(m.start()), m.group(1), "[" + m.group(2) + "]"))
    for m in VIEW_RX.finditer(t):
        ev.append(("V", line(m.start()), m.group(1), m.group(2), m.group(3)))
    for m in VACC_RX.finditer(t):                            # T2.c5: W cast-view accesses `((T *)x)->f`, `((T *)x)[i].f`, `(*(T *)x).f`, any x
        k, depth = m.end(), 1
        while k < len(t) and depth:
            depth += (t[k] == "(") - (t[k] == ")")
            k += 1
        x = t[m.end():k - 1].strip()
        mc = VSTEP_RX.match(t, k) if not depth and x else None
        if not mc:
            continue
        bidx = tuple(s.strip() for s in IDXS_RX.findall(mc.group(1)))
        steps = tuple((s.group(1), s.group(2), tuple(y.strip() for y in IDXS_RX.findall(s.group(3))))
                      for s in STEP_RX.finditer(mc.group(2)))
        if steps[0][0] != ("." if m.group(2) or bidx else "->") or (m.group(2) and bidx):
            continue
        store = bool(STORE_RX.match(t, mc.end())) or t[max(0, m.start() - 160):m.start()].rstrip().endswith(("++", "--"))
        ev.append(("W", line(m.start(3)), bool(m.group(1)), m.group(3), " ".join(x.split()), bidx, steps, store))
    for m in COPY_RX.finditer(t):
        ev.append(("C", line(m.start()), m.group(1), m.group(2)))
    for m in DEREF_RX.finditer(t):
        k = m.start() - 1
        while k >= 0 and t[k] in " \t\n":
            k -= 1
        if k < 0 or not (t[k].isalnum() or t[k] in "_)]"):
            ev.append(("D", line(m.start()), m.group(1)))
    for m in DECL_RX.finditer(t):                            # T2.c3: U scalar / void / byte declarations (untyped locals: eff-flow)
        base, pos, depth = " ".join(m.group(1).split()), m.start(2), 0
        for i, ch in enumerate(m.group(2) + ","):
            if ch == "," and depth == 0:
                it = re.match(r"\s*(\**)\s*(" + ID + r")\s*(\[[^\]]*\])?\s*(?:=|$)", m.group(2)[pos - m.start(2):i])
                if it:
                    ev.append(("U", line(pos + it.start(2)), it.group(2), f"{base} {it.group(1)}{'[]' if it.group(3) else ''}".strip()))
                pos = m.start(2) + i + 1
            depth += (ch in "([") - (ch in ")]")
    return ev


def _links_scan(job):
    """worker: (rel, binds, events, uses) — scan_file's declaration/cast bindings of the inventory names, lex_events, and uses =
    (inventory names in code, names only in directive lines) (T2.c2: the no-evidence reasons)"""
    rel, text = job
    if text is None:
        text = (REPO / rel).read_text(errors="replace")
    if not set(re.findall(r"[A-Za-z_]\w*", text)) & _LWANTED:
        return rel, [], lex_events(text), ((), ())
    code = set(re.findall(ID, _blank(text))) & _LWANTED
    uses = (tuple(sorted(code)), tuple(sorted(set(re.findall(ID, COMMENT.sub(" ", text))) & _LWANTED - code)))
    sink, det = [], {}
    scan_file(rel, text, _LWANTED, sink, det)
    binds = []
    for ix, dd in sorted(det.items()):
        nm, key = sink[ix][0], sink[ix][1]
        whole = dd.get("tail", (")",))[:1] in ((")",), (";",), (",",), ("=",)) or dd.get("tail", ())[:3] == ("[", "0", "]")
        binds.append((nm, key[0], key[2] if key[0] == "P" else None, key[3] if key[0] == "P" else None, dd["form"], dd["ident"],
                      dd["stars"], dd["arr"], dd["ext"], dd["amp"] and whole, dd["line"], dd["fn"]))
    return rel, binds, lex_events(text), uses


class LTypes:
    """inventory-key resolution of type spellings, and member layouts (tc.Resolver over the type universe)"""
    def __init__(self, rows, u):
        self.row = {r["key"]: r for r in rows}
        n2k = collections.defaultdict(set)
        for r in rows:
            for nm in r["names"]:
                n2k[nm].add(r["key"])
        self.key_of = {nm: min(ks) for nm, ks in n2k.items() if len(ks) == 1}
        self.ambiguous = sorted(nm for nm, ks in n2k.items() if len(ks) > 1)
        self.g = u["g"]
        self.res = tc.Resolver(u["g"])
        self._mem = {}

    def spell(self, text):
        """(key, depth) of a type spelling naming an inventory type (`T`, `struct T *`, `const T *a[2]`), else None"""
        ids = [x for x in re.findall(ID, text or "") if x not in TQUAL]
        k = self.key_of.get(ids[0]) if ids else None
        return (k, text.count("*") + text.count("[")) if k else None

    def kind(self, text):
        """`struct` (an inventory type), `other` (void, a scalar, an unresolved name) or None (a function pointer)"""
        return None if "(" in (text or "") else "struct" if self.spell(text) else "other"

    def members(self, d):
        if id(d) not in self._mem:
            offs = dict(field_offsets(self.res, d))
            self._mem[id(d)] = {f["name"]: (offs[f["name"]], f) for f in d["fields"] if f.get("name") in offs}
        return self._mem[id(d)]

    def desc(self, f):
        """a member's type: dict(key, d (aggregate record or None), stars, dims, sc (width, sign) or None, es element size)"""
        stars, dims = f["stars"], list(f.get("dims") or [])
        if f.get("nested"):
            nd = f["nested"]
            lay = self.res.layout_of_fields(nd["fields"], nd["kind"]) if nd["kind"] != "enum" else (4, 4, [])
            return dict(key=None, d=nd if nd["kind"] != "enum" else None, stars=stars, dims=dims,
                        sc=(4, "s") if nd["kind"] == "enum" else None, es=lay[0] if lay else None)
        ids = [x for x in re.findall(ID, f["type"]) if x not in TQUAL]
        key = self.key_of.get(ids[0]) if ids else None
        d = self.row[key]["def"] if key else None
        if d is None and ids and self.g.get(ids[0], {}).get("kind") in ("struct", "union"):
            d = self.g[ids[0]]
        sc = scalar_of(f["type"]) if not stars else None
        lay = self.res.layout(f["type"], stars, [])
        return dict(key=key, d=d, stars=stars, dims=dims, sc=sc if sc and sc[0] else None, es=lay[0] if lay else None)

    def chain(self, key, steps):
        """walk `->`/`.` steps from a value of inventory type `key` -> (records [(key, off, width, sign, field)], leaf desc) or
        (None, why); offsets accumulate along embedded members and restart at each pointer step"""
        path = [[key, self.row[key]["def"], 0, 0]]          # [type key, record, offset (None: unknown), first step]
        last, recs = None, []
        for si, (op, name, idxs) in enumerate(steps):
            if si:
                if op == "->":
                    if not (last["stars"] == 1 and not last["dims"]) or last["d"] is None:
                        return None, "-> through a non-pointer member"
                    path = [[last["key"], last["d"], 0, si]]
                else:
                    if last["stars"] or last["dims"] or last["d"] is None:
                        return None, ". on a non-aggregate member"
                    path.append([last["key"], last["d"], 0, si])
            m = self.members(path[-1][1]).get(name)
            if m is None:
                return None, "member not in the definition"
            off, f = m
            for p in path:
                p[2] = None if p[2] is None else p[2] + off
            last = self.desc(f)
            for ix in idxs:
                if last["dims"]:
                    n = 1
                    for dd in last["dims"][1:]:
                        n *= dd or 0
                    lit = LIT_RX.match(ix)
                    for p in path:
                        p[2] = None if p[2] is None or not lit or last["es"] is None else p[2] + int(lit.group(1), 0) * n * last["es"]
                    last = dict(last, dims=last["dims"][1:])
                elif last["stars"]:
                    path = [[last["key"], last["d"], 0, si + 1]]
                    last = dict(last, stars=last["stars"] - 1)
                    if last["d"] is None and last["sc"] is None:
                        return None, "index through an unknown pointee"
                else:
                    return None, "index on a scalar member"
        if last["stars"] and not last["dims"]:
            w, sg = 4, "p"
        elif last["dims"] or last["sc"] is None:
            return [], last                                 # an array (decays) or an aggregate: no width access
        else:
            w, sg = last["sc"]
        names = [s[1] for s in steps]
        for k, rec, off, s0 in path:
            if k and off is not None:
                recs.append((k, off, w, sg, ".".join(names[s0:])))
        return recs, last


def _cite_va(owner, va):
    return f"{owner}/0x{va:08X}"


def links_build(S):
    """the census of S (see links()) -> dict of tables and summary lines; pure over S"""
    T = S["types"]
    rows = T.row
    U = collections.Counter()                                # unplaced (what, why): binary instances
    US = collections.defaultdict(set)                        # the same: unique sites (T2.c2)
    refused, cand = [], []                                   # dict(cls, sub, a, b, cite_a, cite_b, reason, slot)
    # ---- the fleet join: file -> binaries / visible files; functions; globals
    tus, J, images, stacks = S["tus"], S["join"], S["images"], S["stacks"]
    file_bins, vis = collections.defaultdict(set), {}
    for a in sorted(tus):
        for obj, cfile, deps in tus[a]:
            for f in deps:
                file_bins[f].add(a)
                if f != cfile:
                    vis.setdefault(f, deps)
            vis[cfile] = deps
    own_sym = S["own_sym"]                                   # alias -> {(name, va)} the alias's ELF defines (not absolute)
    gobj_memo = {}

    def global_obj(b, name):
        if (b, name) not in gobj_memo:
            gobj_memo[(b, name)] = _global_obj(b, name)
        return gobj_memo[(b, name)]

    def _global_obj(b, name):
        va, why = J["resolve"](b, name)
        if why:
            return None, why
        for x in [b] + [s for s in stacks.get(b, []) if s != b]:
            if (name, va) in own_sym.get(x, ()):
                return (x, va), None
        for x in [b] + [s for s in stacks.get(b, []) if s != b]:
            if images[x][0] <= va < images[x][1]:
                return (x, va), None
        below = [(images[x][0], x) for x in [b] + stacks.get(b, []) if images[x][0] <= va]
        if below:                                            # past every image's file bytes: the bss of the nearest image below
            return (max(below)[1], va), None
        return None, "address below every image of the stack"
    callee_memo = {}

    def callee_defs(rel, name):
        """([(owner, va, def_at entry)] per binary of rel, [(why, binaries)] of the binaries it is unplaced in)"""
        if (rel, name) not in callee_memo:
            out, whys = {}, []
            for b in sorted(file_bins.get(rel, ())):
                va, why = J["resolve"](b, name)
                if not why:
                    h, owners = J["place"](b, va)
                    why = owners if h is None else None
                if not why:
                    ds = [x for o in owners for x in J["def_at"].get((o, va), [])]
                    if not ds:
                        why = "callee has no placed C definition"
                    else:
                        dd = min(ds, key=lambda x: x[:4])
                        out.setdefault((owners[0], va, dd[1], dd[2]), (owners[0], va, dd))
                if why:
                    whys.append(why)
            if not file_bins.get(rel):
                whys.append("file in no TU")
            callee_memo[(rel, name)] = (sorted(out.values(), key=lambda x: (x[0], x[1], x[2][1], x[2][2])),
                                        sorted(collections.Counter(whys).items()))
        return callee_memo[(rel, name)]
    # ---- function spans (census fndefs) and the bindings (scan_file's declarations and casts)
    spans = {}
    for rel, r in S["walk"].items():
        spans[rel] = sorted((f["line"], f["fn_end"], f["fn"], f) for f in r["fndefs"])
    span_starts = {rel: [s[0] for s in v] for rel, v in spans.items()}

    def span_at(rel, ln):
        st = span_starts.get(rel)
        if not st:
            return None
        i = bisect.bisect_right(st, ln) - 1
        return spans[rel][i] if i >= 0 and spans[rel][i][1] >= ln else None
    fb = collections.defaultdict(dict)                      # (rel, fline) -> ident -> (key, depth, cite, kind) | None (ambiguous)
    filebind = collections.defaultdict(lambda: collections.defaultdict(list))   # rel -> name -> [(key, depth, cite)]
    gdecl = []                                              # (rel, line, name, key, stars, form)
    size_f = collections.defaultdict(dict)                  # key -> {fact kind: cite}

    def size_fact(k, kind, cite):
        size_f[k].setdefault(kind, cite)

    def put(fk, ident, val):
        cur = fb[fk].get(ident, val)
        fb[fk][ident] = val if cur is not None and cur[:2] == val[:2] else None
    for rel, binds in S["binds"]:
        for nm, kk, pfn, pidx, form, ident, stars, arr, ext, amp, ln, fn in binds:
            key = T.key_of.get(nm)
            if not key:
                continue
            cite = f"{rel}:{ln}"
            sp = span_at(rel, ln)
            depth = stars + (1 if arr else 0)
            if form == "cast":
                if kk == "G" and amp:                       # `(B *)&D_x` on the object itself (not `&D_x[k]`, `&D_x + k`)
                    gdecl.append((rel, ln, ident, key, stars - 1, "cast"))
                continue
            if kk == "P":
                if sp and sp[2] == pfn and ln < sp[0] + 12 and fn is None:
                    put((rel, sp[0]), ident, (key, depth, cite, "param", pidx))
                    if depth == 0:
                        size_fact(key, "by-value parameter", cite)
                continue
            if kk == "L" and sp:
                put((rel, sp[0]), ident, (key, depth, cite, "local", None))
                if arr and not stars:
                    size_fact(key, "array", cite)
                elif depth == 0:
                    size_fact(key, "by-value local", cite)
            elif kk == "G":
                gdecl.append((rel, ln, ident, key, stars, "decl"))
                if sp:
                    put((rel, sp[0]), ident, (key, depth, cite, "global", None))
                else:
                    filebind[rel][ident].append((key, depth, cite))
                if arr and not stars:
                    size_fact(key, "array", cite)
                elif depth == 0 and not ext:
                    size_fact(key, "defined global by value", cite)
    file_memo = {}
    pnames_at = {(rel, sp[0]): set(sp[3]["pnames"]) for rel, v in spans.items() for sp in v}

    def bind_of(rel, fline, ident):
        """(key, depth, cite, kind, param index) of an identifier in a function (or at file scope), or None"""
        if fline is not None and ident in fb.get((rel, fline), {}):
            return fb[(rel, fline)][ident]
        if fline is not None and ident in pnames_at.get((rel, fline), ()):
            return None                                      # T2.c2: an untyped parameter shadows file scope (a prototype's param name)
        if (rel, ident) not in file_memo:
            c = sorted({(k, d, ci) for f in vis.get(rel, [rel]) for k, d, ci in filebind.get(f, {}).get(ident, ())},
                       key=lambda x: x[2])
            file_memo[(rel, ident)] = ((c[0][0], c[0][1], c[0][2], "global", None)
                                       if c and len({x[:2] for x in c}) == 1 else None)
        return file_memo[(rel, ident)]
    # members declared as arrays of a type (load-bearing size)
    for k in sorted(rows):
        d = rows[k]["def"]
        for f in d["fields"]:
            ks = T.key_of.get(next((x for x in re.findall(ID, f["type"]) if x not in TQUAL), ""))
            if ks and f.get("dims") and not f["stars"]:
                size_fact(ks, "member array", f"{rows[k]['file_line']} ({k}.{f['name']})")
    # ---- lexical events -> widths, own accesses, dereferences, size facts, views, field flows
    wm = collections.defaultdict(dict)                      # key -> off -> w -> [field, cite, {sign: cite}]
    own_offs = collections.defaultdict(set)                 # slot -> first-level offsets accessed through it
    deref = set()                                           # (rel, fline, ident) dereferenced in its function
    views, fflows = [], []
    vacc = []                                               # T2.c5: (rel, fline, x, first-level offset) of cast-view accesses
    wmb = collections.defaultdict(dict)                     # T2.c5: key -> off -> w -> cite, bound-identifier accesses only (apart own)
    ACC = collections.Counter()
    PF = collections.Counter()                               # pointer flows with a struct-bound side, by outcome
    for rel, events in S["events"]:
        for ev in events:
            sp = span_at(rel, ev[1])
            fl = sp[0] if sp else None
            cite = f"{rel}:{ev[1]}"
            if ev[0] == "A":
                _, ln, amp, base, bidx, steps, store, ctx = ev
                if fl is not None and (steps[0][0] == "->" or bidx):
                    deref.add((rel, fl, base))
                b = bind_of(rel, fl, base)
                if not b:
                    continue
                depth = b[1] - len(bidx)
                if bidx and depth >= 0:
                    lit = LIT_RX.match(bidx[-1])
                    if not lit or int(lit.group(1), 0):
                        size_fact(b[0], "pointer arithmetic", cite)
                if (steps[0][0] == "->") != (depth == 1) or depth not in (0, 1):
                    ACC["depth mismatch"] += 1
                    continue
                recs, leaf = T.chain(b[0], steps)
                if recs is None:
                    ACC[leaf] += 1
                    continue
                ACC["resolved"] += 1
                for k, off, w, sg, fld in recs:
                    e = wm[k].setdefault(off, {}).setdefault(w, [fld, cite, {}])
                    wmb[k].setdefault(off, {}).setdefault(w, cite)
                    if not store and not amp and w <= 2 and sg in ("s", "u"):
                        e[2].setdefault(sg, cite)
                first = T.members(rows[b[0]]["def"]).get(steps[0][1])
                if first and b[3] in ("param", "global"):
                    own_offs[("param", rel, fl, base) if b[3] == "param" else ("global", base)].add(first[0])
                if leaf.get("key") and not leaf["stars"] and not leaf["dims"] and (store or ctx):
                    size_fact(leaf["key"], "member copied whole", cite)
                if ctx and leaf.get("key") and not leaf["dims"] and fl is not None:
                    hk, hp = (recs[-1][0], recs[-1][4]) if recs else (b[0], ".".join(s[1] for s in steps))
                    fflows.append((rel, fl, ln, ctx, leaf["key"], leaf["stars"], hk, hp, base, ".".join(s[1] for s in steps)))
            elif ev[0] == "Z":
                _, ln, kw, star, name, idx0 = ev
                k = T.key_of.get(name) if not star and not idx0 else None
                if k and (kw or not bind_of(rel, fl, name)):
                    size_fact(k, "sizeof", cite)
                    continue
                b = bind_of(rel, fl, name)
                if b and b[1] == (1 if star or idx0 else 0):
                    size_fact(b[0], "sizeof", cite)
            elif ev[0] == "I":
                b = bind_of(rel, fl, ev[2])
                if b and b[1] == 1:
                    size_fact(b[0], "pointer arithmetic", cite)
                if fl is not None and ev[3].startswith("["):
                    deref.add((rel, fl, ev[2]))
            elif ev[0] == "C":
                for x in ev[2:]:
                    b = bind_of(rel, fl, x)
                    if b and b[1] == 1:
                        size_fact(b[0], "copy", cite)
                if fl is not None:
                    deref.update({(rel, fl, ev[2]), (rel, fl, ev[3])})
            elif ev[0] == "D":
                if fl is not None:
                    deref.add((rel, fl, ev[2]))
            elif ev[0] == "V":
                vb, b = T.key_of.get(ev[2]), bind_of(rel, fl, ev[3])
                if fl is not None:
                    deref.add((rel, fl, ev[3]))
                if vb and b and b[1] == 1 and b[0] != vb:
                    views.append(dict(cls="pointer", sub="view", a=b[0], b=vb, cite_a=f"{b[2]} ({ev[3]})",
                                      cite_b=f"{cite} (({ev[2]} *){ev[3]})", reason="view", slot=("view", vb)))
                    m0 = T.members(rows[vb]["def"]).get(ev[4]) if ev[4] else None
                    if m0:                                   # policy views: the view type is the hub slot, its offsets its own
                        own_offs[("view", vb)].add(m0[0])
            elif ev[0] == "W":                               # T2.c5: a cast-view access is an access of the view type's member
                _, ln, amp, tn, x, bidx, steps, store = ev
                vk = T.key_of.get(tn)
                if not vk:
                    continue
                recs, leaf = T.chain(vk, steps)
                if recs is None:
                    ACC["view: " + leaf] += 1
                    continue
                ACC["view resolved"] += 1
                for k, off, w, sg, fld in recs:
                    e = wm[k].setdefault(off, {}).setdefault(w, [fld, cite, {}])
                    if not store and not amp and w <= 2 and sg in ("s", "u"):
                        e[2].setdefault(sg, cite)
                m0 = T.members(rows[vk]["def"]).get(steps[0][1])
                if m0 and fl is not None and re.fullmatch(ID, x):
                    vacc.append((rel, fl, x, m0[0]))
    for rel, r in S["walk"].items():                         # raw cast sites on a parameter dereference it too
        for s in r["sites"]:
            if s.get("bclass") == "param" and s.get("fn") and s.get("base"):
                sp = span_at(rel, s["line"])
                if sp:
                    deref.add((rel, sp[0], s["base"]))
    # ---- placed functions: definitions by (file, line), the census span of a sig_evidence definition
    def_pl = collections.defaultdict(list)                  # (file, name) -> [(b, va)]
    for b, va, h, f, ln, name, d, I in J["defs"]:
        def_pl[(f, d["name"])].append((b, va))

    def ptype(d, i):
        ps = [p for p in se.split_top(d["params"]) if p.strip() and p.strip() != "..."] if d["params"] not in ("", "void") else []
        return ps[i].strip() if i < len(ps) else None
    # ---- class global: one object declared with two types
    objs = collections.defaultdict(dict)                     # (owner, va) -> (key, stars, form) -> first cite
    for rel, ln, name, key, stars, form in sorted(gdecl):
        if not file_bins.get(rel):
            U[("global", "file in no TU")] += 1
            US[("global", "file in no TU")].add((rel, ln, name))
            refused.append(dict(cls="global", sub="global", a=key, b="-", cite_a=f"{rel}:{ln} ({name})", cite_b="-",
                                reason="unplaced:file in no TU", slot=None))
            continue
        whys = collections.Counter()
        for b in sorted(file_bins[rel]):
            o, why = global_obj(b, name)
            if why:
                whys[why] += 1
                continue
            objs[o].setdefault((key, stars, form), f"{rel}:{ln}")
        for why, n in sorted(whys.items()):
            U[("global", why)] += n
            US[("global", why)].add((rel, ln, name))
            refused.append(dict(cls="global", sub="global", a=key, b="-", cite_a=f"{rel}:{ln} ({name})", cite_b=f"{n} binaries",
                                reason="unplaced:" + why, slot=None))
    for o in sorted(objs):
        ent = sorted(objs[o].items(), key=lambda kv: (kv[1], kv[0]))
        seen = set()
        for i, ((ka, sa, fa), ca) in enumerate(ent):
            for (kb, sb, fbm), cb in ent[i + 1:]:
                if ka == kb or sa != sb or (min(ka, kb), max(ka, kb), "cast" in (fa, fbm)) in seen:
                    continue
                seen.add((min(ka, kb), max(ka, kb), "cast" in (fa, fbm)))
                cand.append(dict(cls="global", sub="global-view" if "cast" in (fa, fbm) else "global", a=ka, b=kb,
                                 cite_a=f"{_cite_va(*o)} {ca}", cite_b=f"{_cite_va(*o)} {cb}", slot=("global",) + o))
    # ---- class body: one h_exact class typing one slot with two types
    groups = collections.defaultdict(dict)
    body_pairs = collections.defaultdict(set)                # h_exact -> {(a, b)} the body sub-kind linked (T2.c3: body-view skips them)
    for b, va, h, f, ln, name, d, I in J["defs"]:
        sr = S["sig"].get((b, va))
        if not sr or not sr[1]:
            U[("body", "no sig row (or nins 0) at the definition's address")] += 1
            US[("body", "no sig row (or nins 0) at the definition's address")].add((f, ln))
            continue
        groups[sr[0]].setdefault((f, ln), (b, va, d, sr[1]))
    for hx_ in sorted(groups):
        cps = groups[hx_]
        if len(cps) < 2:
            continue
        slots = collections.defaultdict(list)                # slot -> [(key, depth, cite)]
        for (f, ln), (b, va, d, nins) in sorted(cps.items()):
            base = f"{hx_[:12]} {_cite_va(b, va)} {f}:{ln}"
            ps = [p for p in se.split_top(d["params"]) if p.strip() and p.strip() != "..."] if d["params"] not in ("", "void") else []
            for i, p in enumerate(ps):
                s = T.spell(p) if "(" not in p else None
                if s:
                    slots[f"arg{i}"].append((s[0], s[1], base))
            s = T.spell(d["ret"])
            if s:
                slots["ret"].append((s[0], s[1], base))
            sp = span_at(f, ln)
            for ident, v in sorted((fb.get((f, sp[0]), {}) if sp else {}).items()):
                if v and v[3] == "local":
                    slots[f"local {ident}"].append((v[0], v[1], f"{base} ({v[2]})"))
        nins = min(v[3] for v in cps.values())
        for sl_ in sorted(slots):
            first = {}
            for k, dep, ci in slots[sl_]:
                first.setdefault((k, dep), ci)
            ks = sorted(first)
            for i, (ka, da) in enumerate(ks):
                for kb, db in ks[i + 1:]:
                    if da != db or ka == kb:
                        continue
                    body_pairs[hx_].add((ka, kb))
                    L = dict(cls="body", sub="body", a=ka, b=kb, cite_a=f"{first[(ka, da)]} {sl_}", cite_b=f"{first[(kb, db)]} {sl_}",
                             slot=("body", hx_, sl_))
                    if nins < MIN_BODY_INS:
                        refused.append(dict(L, reason="tiny-body"))
                    else:
                        cand.append(L)
    # ---- class pointer: flows (census, with lines), member flows, declarations vs definitions
    src_of = collections.defaultdict(set)
    for rel, r in S["walk"].items():
        for f in r["flows"]:
            if f["kind"] in ("assign", "assign&", "ret-of", "field"):
                sp = span_at(rel, f["line"])
                if sp:
                    src_of[(rel, sp[0], f["dst"])].add((f["kind"], f.get("src") or f.get("callee") or f"{f.get('base')}+{f.get('off')}"))
    for rel, fl, ln, ctx, mk, ms, hk, hp, base, path in fflows:
        if ctx[0] == "L":
            src_of[(rel, fl, ctx[1])].add(("member", f"{base}.{path}"))

    for rel, fl, x, off in vacc:                             # T2.c5: view accesses through a parameter, or a local whose single source is one
        pn = pnames_at.get((rel, fl), set())
        src = src_of.get((rel, fl, x), set()) if x not in pn else {("assign", x)}
        if len(src) == 1 and next(iter(src))[0] == "assign" and next(iter(src))[1] in pn:
            own_offs[("param", rel, fl, next(iter(src))[1])].add(off)

    def multi(rel, fl, dst, b):
        return b[3] != "global" and len(src_of.get((rel, fl, dst), ())) > 1
    # ---- effective type of an untyped parameter slot (T2.c2; spec "Effective type of an untyped slot"): the struct types of its
    #      typed uses at offset 0 (census cast sites `((M *)p)->f`, `*(M *)p`, `((M *)p)[i]`; `m = p` into a single-source local M *)
    eff = {}                                                 # (rel, fline, pname) -> dict(types {key: (line, cite)}, acc, at)
    for rel in sorted(S["walk"]):
        r = S["walk"][rel]
        for f in r["fndefs"]:
            sp = span_at(rel, f["line"])
            if not sp or sp[0] != f["line"] or sp[2] != f["fn"]:
                continue
            ps = [p for p in se.split_top(f["params"]) if p.strip() and p.strip() != "..."] if f["params"] not in ("", "void") else []
            for i, pn in enumerate(f["pnames"]):
                if i < len(ps) and untyped_param(ps[i], T):
                    eff[(rel, sp[0], pn)] = dict(types={}, acc=(rel, sp[0], pn) in deref, at=f"{rel}:{f['line']} arg{i} ({' '.join(ps[i].split())})")
        for s_ in r["sites"]:
            if (s_.get("form") not in ("C", "I", "X", "P") or s_.get("bclass") != "param" or not s_.get("fn") or s_.get("inner_cast")
                    or s_.get("off") or (s_.get("index") is not None and s_["form"] != "X")):
                continue
            sp = span_at(rel, s_["line"])
            e = eff.get((rel, sp[0], s_["base"])) if sp and sp[2] == s_["fn"] else None
            sk = T.spell(s_.get("ctype")) if e is not None else None
            if sk and sk[1] == 1:
                u = (s_["line"], f"{rel}:{s_['line']} (({s_['ctype']}){s_['base']})")
                e["types"][sk[0]] = min(e["types"].get(sk[0], u), u)
    # T2.c3 eff-flow: untyped locals (a scalar / void / byte declaration in the function, no inventory binding) and their effective
    # type, as for a parameter: census cast sites on the local at offset 0, `m = x` into a single-source local M *
    effl = {}                                                # (rel, fline, ident) -> dict(types, acc, at)
    for rel, events in S["events"]:
        for ev in events:
            if ev[0] != "U":
                continue
            sp = span_at(rel, ev[1])
            if not sp or ev[2] in sp[3]["pnames"] or fb.get((rel, sp[0]), {}).get(ev[2]):
                continue
            k_ = (rel, sp[0], ev[2])
            if not untyped_param(ev[3], T) or (k_ in effl and (effl[k_] is None or effl[k_]["sp"] != ev[3])):
                effl[k_] = None                              # not untyped, or declared twice with two spellings
            elif k_ not in effl:
                effl[k_] = dict(types={}, acc=k_ in deref, at=f"{rel}:{ev[1]} local {ev[2]} ({ev[3]})", sp=ev[3])
    effl = {k_: e for k_, e in effl.items() if e is not None}
    for rel in sorted(S["walk"]):
        r = S["walk"][rel]
        for s_ in r["sites"]:
            if (s_.get("form") not in ("C", "I", "X", "P") or s_.get("bclass") != "local" or not s_.get("fn") or s_.get("inner_cast")
                    or s_.get("off") or (s_.get("index") is not None and s_["form"] != "X")):
                continue
            sp = span_at(rel, s_["line"])
            e = effl.get((rel, sp[0], s_["base"])) if sp and sp[2] == s_["fn"] else None
            sk = T.spell(s_.get("ctype")) if e is not None else None
            if sk and sk[1] == 1:
                u = (s_["line"], f"{rel}:{s_['line']} (({s_['ctype']}){s_['base']})")
                e["types"][sk[0]] = min(e["types"].get(sk[0], u), u)
                e["acc"] = True                              # a cast-site view dereferences the local
    for rel in sorted(S["walk"]):
        r = S["walk"][rel]
        for f in r["flows"]:
            sp = span_at(rel, f["line"]) if f["kind"] == "assign" else None
            e = (eff.get((rel, sp[0], f["src"])) or effl.get((rel, sp[0], f["src"]))) if sp and sp[2] == f["fn"] else None
            bd = bind_of(rel, sp[0], f["dst"]) if e is not None else None
            if bd and bd[3] == "local" and bd[1] == 1 and not multi(rel, sp[0], f["dst"], bd):
                u = (f["line"], f"{rel}:{f['line']} ({f['dst']} = {f['src']}: {bd[2]})")
                e["types"][bd[0]] = min(e["types"].get(bd[0], u), u)
                e["acc"] = e["acc"] or (rel, sp[0], f["dst"]) in deref

    def eside(rel, fl, ident, cite):
        """an untyped identifier's effective side ([(type, cite)], poly) in its function, or None (T2.c3 eff-flow)"""
        e = eff.get((rel, fl, ident)) or effl.get((rel, fl, ident))
        if not e or not e["acc"] or not e["types"]:
            return None
        return [(M, f"{cite} ({ident}: {'poly' if len(e['types']) > 1 else 'eff'} {M}: {uc})") for M, (_, uc) in sorted(e["types"].items())], \
            len(e["types"]) > 1
    # ---- class body, sub-kind body-view (T2.c3; spec "3. body"): copies whose texts are token-identical with every inventory type
    #      spelling masked link the k-th masked position's types; other copies compare slots with declared or effective types
    mask_nm = set(T.key_of) | set(T.ambiguous)
    blanked = {}
    effl_by = collections.defaultdict(set)                   # (rel, fline) -> untyped local names
    for r_, fl_, i_ in effl:
        effl_by[(r_, fl_)].add(i_)

    def masked(f, sp):
        """(types-only masked tokens, types + address names masked, [(type name, line)] per masked type position) of one span"""
        if f not in blanked:
            blanked[f] = _blank(S["read"](f)).split("\n")
        strict, addr, pos = [], [], []
        for ln in range(sp[0], sp[1] + 1):
            for tk in TOK_RX.findall(blanked[f][ln - 1] if ln - 1 < len(blanked[f]) else ""):
                if tk in mask_nm:
                    if strict and strict[-1] in ("struct", "union"):
                        strict.pop()
                        addr.pop()
                    strict.append("@T")
                    addr.append("@T")
                    pos.append((tk, ln))
                else:
                    strict.append(tk)
                    addr.append("@A" if ADDR_NAME.match(tk) else tk)
        return strict, addr, pos
    BV = collections.Counter()                               # body-view measurement (summary)
    bv_ph, tiny_bv = set(), set()
    for hx_ in sorted(groups):
        cps = groups[hx_]
        if len(cps) < 2:
            continue
        nins = min(v[3] for v in cps.values())
        BV["classes >= 2 placed copies"] += 1
        big = nins >= MIN_BODY_INS
        BV["of them nins >= MIN_BODY_INS"] += big
        cs = []
        for (f, ln), (b, va, d, _) in sorted(cps.items()):
            sp = span_at(f, ln)
            if sp:
                cs.append((f, ln, b, va, sp) + masked(f, sp))
        if big:
            bv_ph |= {T.key_of[n] for c in cs for n, _ in c[7] if n in T.key_of and rows[T.key_of[n]]["klass"] == "placeholder"}
        BV["types-only masked texts identical (>= 2 copies)" + ("" if big else ", tiny")] += \
            any(n >= 2 for n in collections.Counter(tuple(c[5]) for c in cs).values())
        same = collections.defaultdict(list)
        for c in cs:
            same[tuple(c[6])].append(c)
        ident = [g for g in same.values() if len(g) >= 2]
        BV["+ address names masked identical (>= 2 copies)" + ("" if big else ", tiny")] += bool(ident)
        BV["+ address names masked, all copies identical" + ("" if big else ", tiny")] += len(same) == 1 and len(cs) >= 2
        got = set(body_pairs[hx_]) | {(b_, a_) for a_, b_ in body_pairs[hx_]}
        links_ = []
        for g in ident:                                      # positional: the k-th masked type of every copy against the first copy's
            c0 = g[0]
            for c in g[1:]:
                for k, ((n0, l0), (n1, l1)) in enumerate(zip(c0[7], c[7])):
                    ka, kb = T.key_of.get(n0), T.key_of.get(n1)
                    if ka and kb and ka != kb and (ka, kb) not in got:
                        got |= {(ka, kb), (kb, ka)}
                        links_.append(dict(cls="body", sub="body-view", a=ka, b=kb,
                                           cite_a=f"{hx_[:12]} {_cite_va(c0[2], c0[3])} {c0[0]}:{l0} ({n0}) pos{k}",
                                           cite_b=f"{hx_[:12]} {_cite_va(c[2], c[3])} {c[0]}:{l1} ({n1}) pos{k}", slot=("body", hx_, f"pos{k}")))
        slots = collections.defaultdict(list)                # fallback: slot -> [(key, depth, cite, effective?)]
        for f, ln, b, va, sp, *_ in cs:
            base = f"{hx_[:12]} {_cite_va(b, va)} {f}:{ln}"
            ps = [p for p in se.split_top(sp[3]["params"]) if p.strip() and p.strip() != "..."] if sp[3]["params"] not in ("", "void") else []
            for i, pn in enumerate(sp[3]["pnames"]):
                s = T.spell(ps[i]) if i < len(ps) and "(" not in ps[i] else None
                es = eside(f, sp[0], pn, base) if not s else None
                if s:
                    slots[f"arg{i}"].append((s[0], s[1], base, False))
                elif es and not es[1]:
                    slots[f"arg{i}"].append((es[0][0][0], 1, es[0][0][1], True))
            for ident_, v in sorted((fb.get((f, sp[0]), {}) or {}).items()):
                if v and v[3] == "local":
                    slots[f"local {ident_}"].append((v[0], v[1], f"{base} ({v[2]})", False))
            for ident_ in sorted(effl_by.get((f, sp[0]), ())):
                es = eside(f, sp[0], ident_, base)
                if es and not es[1]:
                    slots[f"local {ident_}"].append((es[0][0][0], 1, es[0][0][1], True))
        for sl_ in sorted(slots):
            first = {}
            for k, dep, ci, ef in slots[sl_]:
                first.setdefault((k, dep), (ci, ef))
            ks = sorted(first)
            for i, (ka, da) in enumerate(ks):
                for kb, db in ks[i + 1:]:
                    if da != db or ka == kb or (ka, kb) in got or not (first[(ka, da)][1] or first[(kb, db)][1]):
                        continue
                    got |= {(ka, kb), (kb, ka)}
                    links_.append(dict(cls="body", sub="body-view", a=ka, b=kb, cite_a=f"{first[(ka, da)][0]} {sl_}",
                                       cite_b=f"{first[(kb, db)][0]} {sl_}", slot=("body", hx_, sl_)))
        BV["classes giving body-view links" + ("" if big else " (tiny-body, refused)")] += bool(links_)
        BV["body-view link candidates" + ("" if big else " (tiny-body, refused)")] += len(links_)
        for L in links_:
            (cand.append(L) if big else refused.append(dict(L, reason="tiny-body")))

    def ptr(sub, a, b, cite_a, cite_b, slot, why=None):
        L = dict(cls="pointer", sub=sub, a=a, b=b, cite_a=cite_a, cite_b=cite_b, slot=slot)
        (refused.append(dict(L, reason=why)) if why else cand.append(L))

    def eflow(sa, sb, slot, why=None):
        """T2.c3 eff-flow links between a source side and a destination side ([(type, cite)], poly); a poly side refuses them"""
        for A, ca in sa[0]:
            for B, cb in sb[0]:
                if A != B:
                    ptr("eff-flow", A, B, ca, cb, slot, "poly" if sa[1] or sb[1] else why)

    def unplaced(sub, a, cite_a, name, whys, site):
        for w, n in whys:
            U[("callee", w)] += n
            US[("callee", w)].add(site)
            refused.append(dict(cls="pointer", sub=sub, a=a, b="-", cite_a=cite_a, cite_b=name, reason="unplaced:" + w, slot=None))
    for rel in sorted(S["walk"]):
        for f in S["walk"][rel]["flows"]:
            sp = span_at(rel, f["line"])
            if not sp or sp[2] != f["fn"]:
                continue
            fl, cite = sp[0], f"{rel}:{f['line']}"
            k = f["kind"]
            if k in ("arg", "arg&"):
                b = bind_of(rel, fl, f["src"])
                ea = eside(rel, fl, f["src"], cite) if not b and k == "arg" else None
                if ea:                                       # T2.c3 eff-flow: an untyped caller value with an effective type
                    defs, whys = callee_defs(rel, f["callee"])
                    if not defs:
                        PF[("eff-flow", "arg: callee unplaced")] += 1
                    for owner, va, dd in defs:
                        p = ptype(dd[4], f["i"])
                        s = T.spell(p) if p and "(" not in p else None
                        csp = span_at(dd[1], dd[2])
                        pn = csp[3]["pnames"][f["i"]] if csp and f["i"] < len(csp[3]["pnames"]) else None
                        at = f"{_cite_va(owner, va)} {dd[1]}:{dd[2]} arg{f['i']}"
                        eb = eside(dd[1], csp[0], pn, at) if not s and csp and pn else None
                        sb = ([(s[0], at)], False) if s and s[1] == 1 else eb
                        PF[("eff-flow", "arg: " + ("parameter typed" if s and s[1] == 1 else "parameter effective" if eb else "no slot type"))] += 1
                        if sb:
                            eflow(ea, sb, ("param", owner, va, f["i"]),
                                  "conduit" if s and not (csp and pn and (dd[1], csp[0], pn) in deref) else None)
                    continue
                if not b:
                    continue
                da = b[1] + (k == "arg&")
                ca = f"{cite} ({'&' if k == 'arg&' else ''}{f['src']}: {b[2]})"
                defs, whys = callee_defs(rel, f["callee"])
                if not defs:
                    unplaced("arg", b[0], ca, f["callee"], whys, (rel, f["line"], f["callee"]))
                for owner, va, dd in defs:
                    p = ptype(dd[4], f["i"])
                    s = T.spell(p) if p and "(" not in p else None
                    csp = span_at(dd[1], dd[2])
                    pn = csp[3]["pnames"][f["i"]] if csp and f["i"] < len(csp[3]["pnames"]) else None
                    e = eff.get((dd[1], csp[0], pn)) if not s and csp and pn else None
                    if e is not None:                        # an untyped slot: its effective type (arg-eff) or a poly slot
                        o = ("no typed use" if not e["types"] else "never dereferenced" if not e["acc"] else "depth differs" if da != 1
                             else "poly" if len(e["types"]) > 1 else "same type" if b[0] in e["types"] else "two types")
                        PF[("arg-eff", o)] += 1
                        slot = ("param", owner, va, f["i"])
                        for M, (_, uc) in sorted(e["types"].items()) if o in ("poly", "two types") else ():
                            if M != b[0]:
                                ptr("arg-eff", b[0], M, ca, f"{_cite_va(owner, va)} {e['at']} {'poly' if o == 'poly' else 'eff'} {M}: {uc}",
                                    slot, "poly" if o == "poly" else None)
                        continue
                    PF[("arg", "parameter not an inventory type" if not s else "depth differs" if s[1] != da
                        else "same type" if s[0] == b[0] else "two types")] += 1
                    if not s or s[1] != da or s[0] == b[0]:
                        continue
                    conduit = not (csp and pn and (dd[1], csp[0], pn) in deref)
                    ptr("arg", b[0], s[0], ca, f"{_cite_va(owner, va)} {dd[1]}:{dd[2]} arg{f['i']}",
                        ("param", owner, va, f["i"]), "conduit" if conduit else None)
            elif k in ("assign", "assign&"):
                bd, bs = bind_of(rel, fl, f["dst"]), bind_of(rel, fl, f["src"])
                if k == "assign" and (not bd or not bs):     # T2.c3 eff-flow: one or both sides untyped with an effective type
                    sd = ([(bd[0], f"{cite} ({f['dst']}: {bd[2]})")], False) if bd and bd[1] == 1 else None if bd else eside(rel, fl, f["dst"], cite)
                    ss = ([(bs[0], f"{cite} ({f['src']}: {bs[2]})")], False) if bs and bs[1] == 1 else None if bs else eside(rel, fl, f["src"], cite)
                    if sd and ss:
                        PF[("eff-flow", "assign")] += 1
                        if bd and bd[3] == "global":
                            o = next((x for x in (global_obj(b_, f["dst"])[0] for b_ in sorted(file_bins.get(rel, ()))) if x), None)
                            eflow(ss, sd, ("global",) + (o or ()) + (f["dst"],))
                        else:
                            eflow(ss, sd, None, "multisource" if multi(rel, fl, f["dst"], bd or (None, 1, None, "local")) else None)
                if not bd or not bs:
                    continue
                ds = bs[1] + (k == "assign&")
                PF[("assign", "depth differs" if bd[1] != ds else "same type" if bd[0] == bs[0] else "two types")] += 1
                if bd[1] == 0 and ds == 0 and bd[0] == bs[0]:
                    size_fact(bd[0], "copy", cite)
                if bd[1] != ds or bd[0] == bs[0]:
                    continue
                ca = f"{cite} ({'&' if k == 'assign&' else ''}{f['src']}: {bs[2]})"
                if bd[3] == "global":
                    o = next((x for x in (global_obj(b_, f["dst"])[0] for b_ in sorted(file_bins.get(rel, ()))) if x), None)
                    ptr("store-global", bs[0], bd[0], ca, f"{_cite_va(*o) if o else f['dst']} {bd[2]}",
                        ("global",) + (o or ()) + (f["dst"],))
                else:
                    ptr("assign", bs[0], bd[0], ca, f"{cite} ({f['dst']}: {bd[2]})", None,
                        "multisource" if multi(rel, fl, f["dst"], bd) else None)
            elif k == "ret-of":
                bd = bind_of(rel, fl, f["dst"])
                ed = eside(rel, fl, f["dst"], cite) if not bd else None
                if ed:                                       # T2.c3 eff-flow: `x = f()` into an untyped local with an effective type
                    for owner, va, dd in callee_defs(rel, f["callee"])[0]:
                        s = T.spell(dd[4]["ret"])
                        PF[("eff-flow", "ret-of: " + ("return typed" if s and s[1] == 1 else "no return type"))] += 1
                        if s and s[1] == 1:
                            eflow(([(s[0], f"{_cite_va(owner, va)} {dd[1]}:{dd[2]} ret")], False), ed, ("ret", owner, va),
                                  "multisource" if multi(rel, fl, f["dst"], (None, 1, None, "local")) else None)
                    continue
                if not bd:
                    continue
                cd = f"{cite} ({f['dst']}: {bd[2]})"
                defs, whys = callee_defs(rel, f["callee"])
                if not defs:
                    unplaced("ret-of", bd[0], cd, f["callee"], whys, (rel, f["line"], f["callee"]))
                for owner, va, dd in defs:
                    s = T.spell(dd[4]["ret"])
                    PF[("ret-of", "return not an inventory type" if not s else "depth differs" if s[1] != bd[1]
                        else "same type" if s[0] == bd[0] else "two types")] += 1
                    if not s or s[1] != bd[1] or s[0] == bd[0]:
                        continue
                    ptr("ret-of", s[0], bd[0], f"{_cite_va(owner, va)} {dd[1]}:{dd[2]} ret", cd, ("ret", owner, va),
                        "multisource" if multi(rel, fl, f["dst"], bd) else None)
            elif k == "return":
                bs = bind_of(rel, fl, f["src"])
                s = T.spell(sp[3]["ret"])
                es = eside(rel, fl, f["src"], cite) if not bs and s and s[1] == 1 else None
                if es:                                       # T2.c3 eff-flow: `return x;` an untyped value with an effective type
                    PF[("eff-flow", "return")] += 1
                    pl = sorted(def_pl.get((rel, sp[2]), ()))
                    eflow(es, ([(s[0], f"{_cite_va(*pl[0]) + ' ' if pl else ''}{rel}:{sp[0]} ret")], False),
                          ("ret",) + pl[0] if pl else ("ret", rel, sp[2]))
                if not bs or not s or s[1] != bs[1] or s[0] == bs[0]:
                    continue
                pl = sorted(def_pl.get((rel, sp[2]), ()))
                slot = ("ret",) + pl[0] if pl else ("ret", rel, sp[2])
                ptr("ret", bs[0], s[0], f"{cite} ({f['src']}: {bs[2]})",
                    f"{_cite_va(*pl[0]) + ' ' if pl else ''}{rel}:{sp[0]} ret", slot)
    for rel, fl, ln, ctx, mk, ms, hk, hp, base, path in fflows:
        b = bind_of(rel, fl, ctx[1])
        ex = eside(rel, fl, ctx[1], f"{rel}:{ln}") if not b and ms == 1 else None
        if ex:                                               # T2.c3 eff-flow: a member B * loaded into / stored from an untyped value
            PF[("eff-flow", "field")] += 1
            cm = f"{rel}:{ln} ({base} {path}: {mk} *, member {hk}.{hp} {T.row[hk]['file_line']})"
            if ctx[0] == "L":
                eflow(([(mk, cm)], False), ex, ("member", hk, hp), "multisource" if multi(rel, fl, ctx[1], (None, 1, None, "local")) else None)
            else:
                eflow(ex, ([(mk, cm)], False), ("member", hk, hp))
        if b:
            PF[("field", "depth differs" if b[1] != ms else "same type" if b[0] == mk else "two types")] += 1
        if not b or b[1] != ms or b[0] == mk:
            continue
        cm = f"{rel}:{ln} ({base} {path}: {mk}{' ' + '*' * ms if ms else ''}, member {hk}.{hp} {T.row[hk]['file_line']})"
        if ctx[0] == "L":
            ptr("field", mk, b[0], cm, f"{rel}:{ln} ({ctx[1]}: {b[2]})", ("member", hk, hp),
                "multisource" if multi(rel, fl, ctx[1], b) else None)
        else:
            ptr("field", b[0], mk, f"{rel}:{ln} ({ctx[1]}: {b[2]})", cm, ("member", hk, hp))
    # declarations vs their placed definitions: the decl links and DECL-PARAM
    dp, dp_apart = [], collections.Counter()
    for b, f, ln, dc, objs_, va, h, owners, dd in J["decls"]:
        if dd is None:
            continue
        d = dd[4]
        dps = [p for p in se.split_top(dc["params"]) if p.strip() and p.strip() != "..."] if dc["params"] not in ("", "void") else []
        fps = [p for p in se.split_top(d["params"]) if p.strip() and p.strip() != "..."] if d["params"] not in ("", "void") else []
        cdecl, cdef = f"{_cite_va(owners[0], va)} {f}:{ln}", f"{_cite_va(owners[0], va)} {dd[1]}:{dd[2]}"
        for i in range(min(len(dps), len(fps))):
            kd, kf = T.kind(dps[i]), T.kind(fps[i])
            if kd is None or kf is None:
                continue
            if kd != kf:
                dp_apart["struct vs void/scalar"] += 1
                continue
            if kd != "struct":
                continue
            sd, sf = T.spell(dps[i]), T.spell(fps[i])
            PF[("decl", "parameter, same type" if sd[0] == sf[0] else "parameter, two types")] += 1
            if sd[0] == sf[0]:
                continue
            dp.append(dict(name=dc["name"], obj=_cite_va(owners[0], va), i=i, decl=f"{f}:{ln}", decl_t=" ".join(dps[i].split()),
                           defn=f"{dd[1]}:{dd[2]}", def_t=" ".join(fps[i].split()), a=sd[0], b=sf[0], depth=(sd[1], sf[1])))
            if sd[1] == sf[1]:
                ptr("decl", sd[0], sf[0], f"{cdecl} arg{i}", f"{cdef} arg{i}", ("param", owners[0], va, i))
        PF[("decl", "placed with a definition")] += 1
        sd, sf = T.spell(dc["ret"]), T.spell(d["ret"])
        if sd and sf and sd[1] == sf[1] and sd[0] != sf[0]:
            ptr("decl", sd[0], sf[0], f"{cdecl} ret", f"{cdef} ret", ("ret", owners[0], va))
    # ---- dedup; then per policy (T2.c2): the hub guard, the union-find with its vetoes, the components
    def lkey(L):
        return (LINK_ORDER.index((L["cls"], L["sub"])) if (L["cls"], L["sub"]) in LINK_ORDER else 99, L["cite_a"], L["cite_b"], L["a"], L["b"])

    def rkey(L):
        return lkey(L) + (L["reason"],)
    cand = sorted({lkey(L): L for L in cand}.values(), key=lkey)
    refused = sorted({rkey(L): L for L in refused}.values(), key=rkey)
    views = sorted({lkey(L): L for L in views}.values(), key=lkey)

    def hkey(slot, pol):
        """T2.c4 (spec "hub", slot identity): outside policy typed the copies of one routine are one slot, keyed by
        (h_exact class, parameter i | return) when the function has a sig row; other slots are their own key"""
        if pol == "typed" or not slot:
            return slot
        if slot[0] == "param" and len(slot) == 4 or slot[0] == "ret" and len(slot) == 3 and isinstance(slot[2], int):
            sr = S["sig"].get((slot[1], slot[2]))
            if sr and sr[1]:
                return (slot[0], "h" + sr[0][:16]) + slot[3:]
        return slot

    def bkey(L, pol):
        """T2 (expert): a body / body-view link at parameter i of one h_exact class is a link at that routine's parameter slot,
        so it joins the slot's hub test and is refused with it (a generic helper copied per overlay views its argument as
        many types: c4's C1 gathered 80126B58, S800D22E4, vec, Obj through guess_AddVelocityToPos copies); outside policy typed"""
        if pol == "typed" or L["cls"] != "body" or not L.get("slot"):
            return None
        m = re.match(r"arg(\d+)$", str(L["slot"][2]))
        return ("param", "h" + str(L["slot"][1])[:16], int(m.group(1))) if m else None

    def one(k):
        return dict(members=[k], wm=type_map(wm, k), ext=type_extent(wm, k),
                    lb=({rows[k]["size"]: (k, *sorted(size_f[k].items())[0])} if size_f.get(k) else {}))

    def settle(pc, pr, pol):
        """one policy's hub guard, union-find (LINK_ORDER, then cites) with the width / size vetoes, and components"""
        refused = list(pr)
        by_slot, parts = collections.defaultdict(list), collections.defaultdict(set)
        for L in pc:
            if L["cls"] == "pointer" and L["slot"]:
                by_slot[hkey(L["slot"], pol)].append(L)
                parts[hkey(L["slot"], pol)].add(L["slot"])
            elif bkey(L, pol):
                by_slot[bkey(L, pol)].append(L)
        hubs, hub_slots = [], set()
        for slot in sorted(by_slot, key=str):
            ts = sorted({L["a"] for L in by_slot[slot]} | {L["b"] for L in by_slot[slot]})
            conf = None
            for i, x in enumerate(ts):
                for y in ts[i + 1:]:
                    c = width_conflict(type_map(wm, x), type_map(wm, y))
                    if c:
                        conf = (x, y, c)
                        break
                if conf:
                    break
            oo = (set().union(*(own_offs_param(own_offs, p, J, span_at) for p in sorted(parts[slot], key=str))) if slot[0] == "param" else
                  own_offs.get(("global", slot[-1]), set()) if slot[0] == "global" else own_offs.get(slot, set()) if slot[0] == "view" else set())
            if conf or (len(ts) >= HUB_K and len(oo) <= HUB_OFFS and parts[slot]):   # a body-only slot: hub on conflict only
                hub_slots.add(slot)
                hubs.append(dict(slot=slot, types=ts, why=(f"width conflict {conf[0]}/{conf[1]} at 0x{conf[2][0]:X}" if conf else
                                                           f"{len(ts)} types, own accesses at {len(oo)} offsets"),
                                 cites=sorted({L["cite_b"] if L["sub"] not in ("ret-of",) else L["cite_a"] for L in by_slot[slot]})[:3],
                                 copies=len(parts[slot])))
        acc_links = []
        for L in pc:
            if L["cls"] == "pointer" and hkey(L["slot"], pol) in hub_slots or bkey(L, pol) in hub_slots:
                refused.append(dict(L, reason="hub"))
            else:
                acc_links.append(L)
        htypes = []                                          # T2.c4 (spec "hub type"): header / conduit types, outside policy typed
        if pol != "typed":
            partners = collections.defaultdict(set)
            for L in acc_links:
                if L["sub"] in HUB_TYPE_SUBS:
                    partners[L["a"]].add(L["b"])
                    partners[L["b"]].add(L["a"])
            for k in sorted(partners):
                ps = sorted(partners[k])
                if len(ps) < HUB_K:
                    continue
                why = None
                for i, x in enumerate(ps):
                    for y in ps[i + 1:]:
                        c = width_conflict(type_map(wm, x), type_map(wm, y))
                        v = None if c else size_veto(one(x), one(y))
                        if c or v:
                            why = (f"{x} / {y} width 0x{c[0]:X}: {c[1]} vs {c[2]}" if c else f"{x} / {y} size: {v}")
                            break
                    if why:
                        break
                if why:
                    htypes.append(dict(type=k, partners=ps, why=why))
            hset = {h["type"] for h in htypes}
            if hset:
                keep = []
                for L in acc_links:
                    # T2 (expert): two hub types never merge on any link (c4 rerun: 800B5CB8 and 80126B58 joined by
                    # body-view copies once the 0x18 conflict left the component); that call is the review's, not the tool's
                    if L["sub"] in HUB_TYPE_SUBS and (L["a"] in hset or L["b"] in hset) or (L["a"] in hset and L["b"] in hset):
                        refused.append(dict(L, reason="hub-type", detail="hub type " + ",".join(sorted({L["a"], L["b"]} & hset))))
                    else:
                        keep.append(L)
                acc_links = keep
                for h in htypes:
                    h["refused"] = sum(1 for L in refused if L["reason"] == "hub-type" and h["type"] in (L["a"], L["b"]))
        comp = {k: one(k) for k in sorted(rows)}
        parent = {k: k for k in rows}

        def find(x):
            while parent[x] != x:
                parent[x] = parent[parent[x]]
                x = parent[x]
            return x
        accepted = []
        for L in acc_links:
            ra, rb = find(L["a"]), find(L["b"])
            if ra == rb:
                accepted.append(L)
                continue
            A, B = comp[ra], comp[rb]
            c = width_conflict(A["wm"], B["wm"])
            if c:
                refused.append(dict(L, reason="conflict", detail=f"0x{c[0]:X}: {c[1]} vs {c[2]}"))
                continue
            v = size_veto(A, B)
            if v:
                refused.append(dict(L, reason="size", detail=v))
                continue
            if ra > rb:
                ra, rb, A, B = rb, ra, B, A
            parent[rb] = ra
            A["members"] = sorted(A["members"] + B["members"])
            for off, ws in B["wm"].items():
                for w, e in ws.items():
                    cur = A["wm"].setdefault(off, {}).setdefault(w, [e[0], e[1], {}, e[3]])
                    for sg, ci in e[2].items():
                        cur[2].setdefault(sg, ci)
            for sz, e in B["lb"].items():
                A["lb"].setdefault(sz, e)
            if B["ext"] and (not A["ext"] or B["ext"][0] > A["ext"][0]):
                A["ext"] = B["ext"]
            del comp[rb]
            accepted.append(dict(L, union=True))
        refused.sort(key=rkey)
        return dict(accepted=accepted, refused=refused, hubs=hubs, htypes=htypes, comp=comp, find=find)
    P = {}
    for pol in POLICIES:
        pc = [L for L in cand if pol != "typed" or L["sub"] not in EFF_SUBS]
        pr = [L for L in refused if pol != "typed" or L["sub"] not in EFF_SUBS]
        if pol == "views":
            pc = sorted(pc + [{k: v for k, v in L.items() if k != "reason"} for L in views], key=lkey)
        else:
            pr = pr + views
        P[pol] = settle(pc, sorted(pr, key=rkey), pol)
    # ---- what a disposition cites (T2.c2): own placed objects / accesses (apart own), or what exists (no-evidence)
    own = {}
    for o in sorted(objs):
        for (k, st, fm), ci in sorted(objs[o].items(), key=lambda kv: (kv[1], kv[0])):
            own.setdefault(k, f"{_cite_va(*o)} {ci}")
    bound = {}
    for (rel, fl), m in sorted(fb.items()):
        sp = span_at(rel, fl)
        pl = sorted(def_pl.get((rel, sp[2]), ())) if sp else []
        for ident, v in sorted(m.items()):
            if v and v[3] in ("param", "local"):
                if pl:
                    own.setdefault(v[0], f"{_cite_va(*pl[0])} {v[2]} ({ident})")
                else:
                    bound.setdefault(v[0], f"{v[2]} ({ident})")
    for k in sorted(wmb):                                    # T2.c5: bound accesses only; a cast view is no object of its own
        off = min(wmb[k])
        own.setdefault(k, f"{wmb[k][off][min(wmb[k][off])]} (access {k}+0x{off:X})")
    canon = set(tc.CANON_HEADERS)
    named, macro = collections.defaultdict(list), collections.defaultdict(list)
    for rel, (code, mac) in sorted(S["uses"]):
        if rel in canon:
            continue
        for nm in code:
            if nm in T.key_of:
                named[T.key_of[nm]].append(rel)
        for nm in mac:
            if nm in T.key_of:
                macro[T.key_of[nm]].append(rel)
    member_of = collections.defaultdict(set)
    for k in sorted(rows):
        for f in rows[k]["def"]["fields"]:
            ks = T.key_of.get(next((x for x in re.findall(ID, f["type"]) if x not in TQUAL), ""))
            if ks and ks != k:
                member_of[ks].add(k)
    unpl = {}
    for L in refused:
        if L["reason"].startswith("unplaced:") and L["a"] in rows:
            unpl.setdefault(L["a"], f"unplaced: {L['reason'][9:]} ({L['cite_a']})")
    casts = {}                                               # key -> [cast sites, first cite]: raw cast views of untyped values
    for rel in sorted(S["walk"]):
        for s_ in S["walk"][rel]["sites"]:
            sk = T.spell(s_.get("ctype")) if s_.get("form") in ("C", "I", "X", "P") else None
            if sk:
                c = casts.setdefault(sk[0], [0, (rel, s_["line"])])
                c[0] += 1
                c[1] = min(c[1], (rel, s_["line"]))
    noev = {}
    for k in sorted(rows):
        nf = sorted(set(named.get(k, ())))
        noev[k] = (unpl[k] if k in unpl else f"bound only outside placed functions: {bound[k]}" if k in bound
                   else f"cast views of untyped values only ({casts[k][0]} sites, first {casts[k][1][0]}:{casts[k][1][1]}), no placed object"
                   if k in casts
                   else f"named in {len(nf)} files outside the type files (first {nf[0]}), no placed object or access" if nf
                   else f"macro only ({sorted(macro[k])[0]})" if macro.get(k)
                   else f"member of {','.join(sorted(member_of[k])[:3])}{' …' if len(member_of[k]) > 3 else ''} only" if member_of.get(k)
                   else "no users")
    poly = sorted(((k, e) for k, e in eff.items() if len(e["types"]) > 1 and e["acc"]), key=lambda kv: kv[1]["at"])
    BV["placeholders in copies (nins >= MIN_BODY_INS)"] = len(bv_ph)
    BV["of them cast views only (no-evidence reason)"] = sum(1 for k in bv_ph if noev[k].startswith("cast views"))
    BV["untyped locals with an effective type"] = sum(1 for e in effl.values() if e["acc"] and len(e["types"]) == 1)
    BV["untyped locals declared (eff-flow candidates)"] = len(effl)
    return dict(T=T, U=U, US=US, P=P, wm=wm, size_f=size_f, dp=dp, dp_apart=dp_apart, ACC=ACC, PF=PF, J=J, own=own, noev=noev,
                eff=eff, poly=poly, BV=BV)


def untyped_param(p, T):
    """(pure) a parameter spelling with no inventory type that may carry a pointer: void *, a byte pointer, or a scalar"""
    if "(" in p or "[" in p or T.spell(p):
        return False
    ids = [x for x in re.findall(ID, p) if x not in TQUAL]
    words, stars = set(ids[:-1] if len(ids) > 1 else ids), p.count("*")
    return bool(words) and (words <= SCALAR_WORDS if stars == 0 else stars == 1 and (words == {"void"} or words <= BYTE_WORDS))


def own_offs_param(own_offs, slot, J, span_at):
    """first-level offsets a callee parameter slot (param, owner, va, i) is accessed at in its own body(ies)"""
    out = set()
    for e in J["def_at"].get((slot[1], slot[2]), ()):
        sp = span_at(e[1], e[2])
        if sp and slot[3] < len(sp[3]["pnames"]):
            out |= own_offs.get(("param", e[1], sp[0], sp[3]["pnames"][slot[3]]), set())
    return out


def type_map(wm, k):
    """a type's accessed-width map as a component map: off -> w -> [field, cite, {sign: cite}, key]"""
    return {off: {w: [e[0], e[1], dict(e[2]), k] for w, e in ws.items()} for off, ws in wm.get(k, {}).items()}


def type_extent(wm, k):
    ends = [(off + w, e[1]) for off, ws in wm.get(k, {}).items() for w, e in ws.items()]
    return max(ends) if ends else None


def width_conflict(ma, mb):
    """(off, cite a, cite b) of the first conflict between two accessed-width maps (different widths at one offset, a partial
    overlap, or 1-/2-byte loads of different signs), else None"""
    if not ma or not mb:
        return None
    oa, ob = sorted(ma), sorted(mb)
    for off in oa:
        if off in mb:
            wa, wb = ma[off], mb[off]
            if not set(wa) & set(wb):
                x, y = wa[min(wa)], wb[min(wb)]
                return off, f"{x[3]}.{x[0]} {min(wa)}B {x[1]}", f"{y[3]}.{y[0]} {min(wb)}B {y[1]}"
            for w in sorted(set(wa) & set(wb)):
                sa, sb = wa[w][2], wb[w][2]
                if sa and sb and not set(sa) & set(sb):
                    x, y = wa[w], wb[w]
                    return off, f"{x[3]}.{x[0]} {min(sa)} {sa[min(sa)]}", f"{y[3]}.{y[0]} {min(sb)} {sb[min(sb)]}"
    for m1, m2, o2, flip in ((ma, mb, ob, False), (mb, ma, oa, True)):
        for off in sorted(m1):
            for w in sorted(m1[off]):
                i = bisect.bisect_right(o2, off)
                while i < len(o2) and o2[i] < off + w:
                    if o2[i] not in m1:
                        x, y = m1[off][w], m2[o2[i]][min(m2[o2[i]])]
                        cx, cy = f"{x[3]}.{x[0]} {w}B@0x{off:X} {x[1]}", f"{y[3]}.{y[0]} {min(m2[o2[i]])}B@0x{o2[i]:X} {y[1]}"
                        return (o2[i], cy, cx) if flip else (off, cx, cy)
                    i += 1
    return None


def size_veto(A, B):
    """the size veto of merging two components, or None: two load-bearing sizes, or an accessed extent past one"""
    lb = dict(A["lb"])
    for sz, e in B["lb"].items():
        lb.setdefault(sz, e)
    if len(lb) > 1:
        (s1, e1), (s2, e2) = sorted(lb.items())[:2]
        return f"load-bearing {e1[0]} {s1}B ({e1[1]} {e1[2]}) vs {e2[0]} {s2}B ({e2[1]} {e2[2]})"
    if lb:
        sz, e = next(iter(lb.items()))
        for x in (A["ext"], B["ext"]):
            if x and isinstance(sz, int) and x[0] > sz:
                return f"access to 0x{x[0]:X} ({x[1]}) past load-bearing {e[0]} {sz}B ({e[1]} {e[2]})"
    return None


def _fl_key(fl):
    f, _, ln = fl.rpartition(":")
    return (f, int(ln) if ln.isdigit() else 0)


def _clean(x):
    return " ".join(str(x).split())


def links_render(R, reach, twins=None):
    """(summary lines, {tsv name: text}, {policy: {placeholder key: ledger proposal}}, report context) of one links_build result; deterministic.
    Per policy (T2.c2): links / refused / hubs / components / proposals.<policy>.tsv; shared: widths, sizes, eff, poly, decl_param,
    twins, unplaced"""
    T, rows = R["T"], R["T"].row
    tsv, props = {}, {}
    ph = sorted(k for k, r in rows.items() if r["klass"] == "placeholder")

    def table(name, head, recs):
        tsv[name] = "\t".join(head) + "\n" + "".join("\t".join(str(x).replace("\t", " ") for x in r) + "\n" for r in recs)
    table("widths.tsv", ("type", "offset", "width", "sign", "field", "cite"),
          [(k, f"0x{off:X}", w, "".join(sorted(e[2])) or "-", e[0], e[1]) for k in sorted(R["wm"]) for off in sorted(R["wm"][k])
           for w, e in sorted(R["wm"][k][off].items())])
    table("sizes.tsv", ("type", "kind", "cite"), [(k, kind, ci) for k in sorted(R["size_f"]) for kind, ci in sorted(R["size_f"][k].items())])
    table("eff.tsv", ("slot", "status", "types"),
          [(e["at"], "never dereferenced" if not e["acc"] else "no typed use" if not e["types"] else "poly" if len(e["types"]) > 1
            else "effective", " | ".join(f"{k}: {c}" for k, (_, c) in sorted(e["types"].items())) or "-")
           for e in sorted(R["eff"].values(), key=lambda e: e["at"])])
    table("poly.tsv", ("slot", "types", "cites"),
          [(e["at"], ",".join(sorted(e["types"])), " | ".join(c for _, (_, c) in sorted(e["types"].items()))) for _, e in R["poly"]])
    table("unplaced.tsv", ("what", "why", "binary_instances", "unique_sites"),
          [(w, r, n, len(R["US"].get((w, r), ()))) for (w, r), n in sorted(R["U"].items())]
          + [(w[0] + " (join)", w[1], n, len(R["J"].get("US", {}).get(w, ()))) for w, n in sorted(R["J"]["U"].items())])
    S_ = [f"struct_twins --links: {len(rows)} inventory types (placeholder {len(ph)}) · HUB_K {HUB_K} · HUB_OFFS {HUB_OFFS}"
          f" · MIN_BODY_INS {MIN_BODY_INS} · policies {', '.join(POLICIES)}"]
    es = collections.Counter("never dereferenced" if not e["acc"] else "no typed use" if not e["types"] else "poly" if len(e["types"]) > 1
                             else "effective" for e in R["eff"].values())
    S_.append(f"untyped parameter slots {len(R['eff'])}: " + " · ".join(f"{k} {n}" for k, n in sorted(es.items()))
              + f" (poly slots listed: {len(R['poly'])})")
    S_.append("body-view / eff-flow measure (T2.c3): " + " · ".join(f"{k} {n}" for k, n in sorted(R["BV"].items())))
    dres, trows, ctx = {}, {}, {}
    for pol in POLICIES:
        Q = R["P"][pol]
        comp, find = Q["comp"], Q["find"]
        table(f"links.{pol}.tsv", ("class", "sub", "A", "B", "cite_A", "cite_B"),
              [(L["cls"], L["sub"], L["a"], L["b"], L["cite_a"], L["cite_b"]) for L in Q["accepted"]])
        table(f"refused.{pol}.tsv", ("reason", "class", "sub", "A", "B", "cite_A", "cite_B", "detail"),
              [(L["reason"], L["cls"], L["sub"], L["a"], L["b"], L["cite_a"], L["cite_b"], L.get("detail", "-")) for L in Q["refused"]])
        table(f"hubs.{pol}.tsv", ("slot", "types", "why", "cites"),
              [("/".join(str(x) if not isinstance(x, int) or x < 0x1000 else f"0x{x:08X}" for x in h["slot"]), ",".join(h["types"]), h["why"],
                " | ".join(h["cites"])) for h in Q["hubs"]])
        table(f"hubtypes.{pol}.tsv", ("type", "partners", "links_refused", "why", "partner_list"),
              [(h["type"], len(h["partners"]), h["refused"], h["why"], ",".join(h["partners"])) for h in Q["htypes"]])
        # components: numbered by size (desc), then first member
        touch = collections.defaultdict(collections.Counter)
        for L in Q["refused"]:
            for k in {L["a"], L["b"]} & set(rows):
                touch[find(k)][L["reason"].split(":")[0]] += 1
        cs = sorted(comp.items(), key=lambda kv: (-len(kv[1]["members"]), kv[0]))
        crow, cid, tgt = [], {}, {}
        for n, (root, c) in enumerate(cs, 1):
            cid[root] = f"C{n}"
            ms = c["members"]
            tgt[root] = min(ms, key=lambda k: (rows[k]["klass"] != "PsyQ", rows[k]["klass"] != "ledgered", -reach.get(k, 0),
                                               _fl_key(rows[k]["file_line"])))
            sz = next(iter(c["lb"])) if c["lb"] else max((rows[k]["size"] for k in ms if isinstance(rows[k]["size"], int)), default="?")
            lay = " ".join(f"0x{off:X}:{w}{''.join(sorted(e[2])) or '-'}:{e[3]}.{e[0]}@{e[1]}" for off in sorted(c["wm"]) for w, e in sorted(c["wm"][off].items()))
            crow.append((f"C{n}", ",".join(ms), tgt[root], sz, lay or "-", ",".join(f"{r}:{x}" for r, x in sorted(touch[root].items())) or "-",
                         sum(reach.get(k, 0) for k in ms)))
        table(f"components.{pol}.tsv", ("component", "members", "target", "merged_size", "merged_layout", "refused_touching",
                                        "projected_reach"), crow)
        # proposals (spec "Dispositions proposed"): one per placeholder
        admit = {}
        for L in Q["accepted"]:
            if L.get("union"):
                admit.setdefault(L["a"], L)
                admit.setdefault(L["b"], L)
        veto = {}
        for L in Q["refused"]:
            if L["reason"] in ("conflict", "size", "hub", "hub-type"):
                for k, o in ((L["a"], L["b"]), (L["b"], L["a"])):
                    veto.setdefault(k, (L, o))
        pp = {}
        for k in ph:
            root = find(k)
            ms = comp[root]["members"]
            if len(ms) > 1 and k != tgt[root]:
                L = admit[k]
                pp[k] = ("fold", tgt[root], L["cls"], f"{cid[root]}: {L['cite_a']} | {L['cite_b']}", f"{L['sub']} link {L['a']}~{L['b']}")
            elif len(ms) > 1:
                ev = R["own"].get(k) or f"{admit[k]['cite_a']} | {admit[k]['cite_b']}"
                pp[k] = ("apart", "-", "own", f"{cid[root]}: {ev}", f"target of {cid[root]} ({len(ms)} types)")
            elif k in veto:
                L, o = veto[k]
                pp[k] = ("apart", "-", "hub" if L["reason"] == "hub-type" else L["reason"], f"{L['cite_a']} | {L['cite_b']}" + (f" | {L['detail']}" if L.get("detail") else ""),
                         f"{L['reason']}: {L['sub']} link to {o} refused")
            elif k in R["own"]:
                pp[k] = ("apart", "-", "own", R["own"][k], "own objects, no accepted link")
            else:
                pp[k] = ("no-evidence", "-", "-", "-", R["noev"][k])
            pp[k] = tuple(_clean(x) for x in pp[k])
        props[pol] = pp
        ctx[pol] = dict(crow=crow, cs=cs, cid=cid, tgt=tgt, admit=admit, pp=pp, touch=touch)
        table(f"proposals.{pol}.tsv", ("key", "disposition", "target", "class", "evidence", "reason"), [(k,) + pp[k] for k in ph])
        # DECL-PARAM resolution under this policy
        for d in R["dp"]:
            if find(d["a"]) == find(d["b"]):
                dres[(id(d), pol)] = "yes"
            else:
                r = next((L["reason"] for L in Q["refused"] if L["sub"] == "decl" and {L["a"], L["b"]} == {d["a"], d["b"]}
                          and L["cite_a"].endswith(f"{d['decl']} arg{d['i']}")), None)
                dres[(id(d), pol)] = (f"no: link refused ({r})" if r else "no: pointer depths differ" if d["depth"][0] != d["depth"][1]
                                      else "no: different components")
        # twins re-judged (spec "Twins re-judged")
        for lh, tw in sorted((twins or {}).items()):
            ks = sorted({T.key_of[nm] for nm in tw.get("names") or () if nm in T.key_of})
            g = collections.Counter(find(k) for k in ks)
            multi = sorted(cid[r] for r, n in g.items() if n >= 2)
            trows.setdefault(lh, [lh, len(tw.get("names") or ()), len(ks)]).append(
                ("linked" if len(multi) == 1 else "split" if multi else "apart holds") + (f" ({','.join(multi)})" if multi else ""))
        # summary
        S_.append(f"policy {pol}: links accepted {len(Q['accepted'])} (class/sub-kind: links, distinct types)")
        for cl, sub in LINK_ORDER:
            xs = [L for L in Q["accepted"] if (L["cls"], L["sub"]) == (cl, sub)]
            S_.append(f"  {cl}/{sub}: {len(xs)} links, {len({k for L in xs for k in (L['a'], L['b'])})} types")
        rc = collections.Counter(L["reason"].split(":")[0] for L in Q["refused"])
        S_.append("  refused by reason: " + " · ".join(f"{r} {n}" for r, n in sorted(rc.items())))
        bands = collections.Counter(next(b for b, lo in (("21+", 21), ("6-20", 6), ("3-5", 3), ("2", 2), ("1", 1)) if len(c["members"]) >= lo)
                                    for c in comp.values())
        S_.append("  components by size band: " + " · ".join(f"{b} {bands[b]}" for b in ("1", "2", "3-5", "6-20", "21+"))
                  + f" · hubs {len(Q['hubs'])}" + (f" (copies merged: {sum(1 for h in Q['hubs'] if h['copies'] > 1)})"
                                                    f" · hub types {len(Q['htypes'])}" if pol != "typed" else ""))
        for h in Q["htypes"] if pol != "typed" else ():
            S_.append(f"    hub type {h['type']}: {len(h['partners'])} partners, {h['refused']} links refused ({h['why']})")
        S_.append("  largest 5:")
        for r in crow[:5]:
            ms = r[1].split(",")
            S_.append(f"    {r[0]}: {len(ms)} types · target {r[2]} · size {r[3]} · {','.join(ms[:6])}{' …' if len(ms) > 6 else ''}")
        for r in crow:                                       # T2.c3: a 21+ component lists every member's admitting link
            if len(r[1].split(",")) < 21:
                break
            S_.append(f"    {r[0]} members (admitting link):")
            for k in r[1].split(","):
                L = admit.get(k)
                S_.append(f"      {k}: " + (f"{L['cls']}/{L['sub']} {L['a']}~{L['b']} {L['cite_a']} | {L['cite_b']}" if L else "-"))
        dc = collections.Counter(v[0] for v in pp.values())
        cc = collections.Counter((v[0], v[2]) for v in pp.values())
        S_.append(f"  projected over {len(ph)} placeholders: folded {dc['fold']} · apart {dc['apart']} · no-evidence {dc['no-evidence']}"
                  " (" + " · ".join(f"{d}/{c} {n}" for (d, c), n in sorted(cc.items())) + ")")
        tv = collections.Counter(t[-1].split(" ")[0] if not t[-1].startswith("apart") else "apart holds" for t in trows.values())
        S_.append(f"  twins re-judged ({len(trows)} classes): linked {tv['linked']} · split {tv['split']} · apart holds {tv['apart holds']}")
        S_.append(f"  DECL-PARAM rows resolved by the folds: {sum(1 for d in R['dp'] if dres[(id(d), pol)] == 'yes')} of {len(R['dp'])}")
    table("decl_param.tsv", ("name", "object", "i", "decl", "decl_type", "def", "def_type") + tuple(f"resolved_{p}" for p in POLICIES),
          [(d["name"], d["obj"], d["i"], d["decl"], d["decl_t"], d["defn"], d["def_t"]) + tuple(dres[(id(d), p)] for p in POLICIES)
           for d in sorted(R["dp"], key=lambda d: (d["name"], d["obj"], d["i"], d["decl"]))])
    table("twins.tsv", ("lhash", "names", "inventory_keys") + tuple(f"verdict_{p}" for p in POLICIES), [trows[k] for k in sorted(trows)])
    S_.append("unplaced by reason (binary instances / unique sites):")
    for (w, r), n in sorted(R["U"].items()):
        S_.append(f"  {w}: {r}: {n} / {len(R['US'].get((w, r), ()))}")
    for w, n in sorted(R["J"]["U"].items()):
        S_.append(f"  {w[0]} (join): {w[1]}: {n} / {len(R['J'].get('US', {}).get(w, ()))}")
    dp = R["dp"]
    S_.append(f"DECL-PARAM: rows {len(dp)} · names {len({d['name'] for d in dp})} · declaration lines {len({d['decl'] for d in dp})}"
              f" · struct vs void/scalar (apart) {R['dp_apart']['struct vs void/scalar']}")
    S_.append("member accesses: " + " · ".join(f"{k} {n}" for k, n in sorted(R["ACC"].items())))
    S_.append("pointer flows with a struct-bound side (placed): " + " · ".join(f"{k}/{o} {n}" for (k, o), n in sorted(R["PF"].items())))
    S_.append(f"width-map types {len(R['wm'])} · types with a load-bearing size {len(R['size_f'])}")
    return S_, tsv, props, dict(pol=ctx, dres=dres, trows=trows, reach=reach)


REPORT_DEFAULT = "docs/ops/p345-struct-merge-report.md"
FIELD_STYLE = ("Fields: lowerCamelCase; a model-worded name carries `guess_` outermost (`guess_posX`) with a basis row; the citation or "
               "basis pointer sits in the field's comment beside its `/* 0xNN */` offset (tools/struct_layout.py:18-30; unk<HEX>/pad<HEX> "
               "keep sitting at offset HEX). Types: PascalCase (docs/wiki/Names-and-renames.md:26-40); every model-worded type name "
               "`guess_` with a basis row (outcome R122).")
NOEV_KINDS = (("bound only outside", "bound only outside placed functions"), ("cast views", "cast views of untyped values only"),
              ("named in", "named outside the type files only"), ("macro only", "macro only"), ("member of", "member of other types only"),
              ("no users", "no users"))


def _band(n):
    return next(b for b, lo in (("21+", 21), ("6-20", 6), ("3-5", 3), ("2", 2), ("1", 1)) if n >= lo)


def _slot_s(s):
    return "/".join(str(x) if not isinstance(x, int) or x < 0x1000 else f"0x{x:08X}" for x in s)


def _cap(xs, n):
    xs = list(xs)
    return ", ".join(xs[:n]) + (f" … (+{len(xs) - n})" if len(xs) > n else "")


def links_report(R, X, head):
    """(pure) the generated merge report (spec: docs/ops/p345-t2-struct-merge-evidence.md) of one links_build / links_render
    result: counts per policy side by side, the effective policy's components, hubs, conflicts, naming scope and fold batches"""
    T, rows, reach, P, C = R["T"], R["T"].row, X["reach"], R["P"], X["pol"]
    ph = sorted(k for k, r in rows.items() if r["klass"] == "placeholder")
    E, CE = P["effective"], C["effective"]
    find, comp = E["find"], E["comp"]
    o = ["# 3.45 T2 — struct merge evidence report (generated)", "",
         f"Generated by `tools/struct_twins.py --links --report` from the tree at git `{head}`. Do not edit: rerun the generator.",
         "Method: docs/ops/p345-t2-struct-merge-evidence.md. Full lists: `.run/3.45/t2/*.<policy>.tsv`. The ledger proposals",
         f"(config/struct_dispositions.tsv) follow policy `effective`; sections below the counts show it. HUB_K {HUB_K} · "
         f"HUB_OFFS {HUB_OFFS} · MIN_BODY_INS {MIN_BODY_INS} · {len(ph)} placeholders of {len(rows)} inventory types.", ""]

    def grid(title, keys, val):
        o.extend([f"## {title}", "", "| | " + " | ".join(POLICIES) + " |", "|---" * (len(POLICIES) + 1) + "|"])
        for k in keys:
            vs = [str(val(p, k)) for p in POLICIES]
            o.append(f"| {k} | " + " | ".join(vs) + " |")
        o.append("")

    def lk(p, cl, sub):
        xs = [L for L in P[p]["accepted"] if (L["cls"], L["sub"]) == (cl, sub)]
        return f"{len(xs)} / {len({k for L in xs for k in (L['a'], L['b'])})}"
    grid("Links accepted per class and sub-kind (links / distinct types)", [f"{c}/{s}" for c, s in LINK_ORDER],
         lambda p, k: lk(p, *k.split("/")))
    rc = {p: collections.Counter(L["reason"].split(":")[0] for L in P[p]["refused"]) for p in POLICIES}
    grid("Refusals by reason", sorted(set().union(*rc.values())), lambda p, k: rc[p][k])
    bc = {p: collections.Counter(_band(len(c["members"])) for c in P[p]["comp"].values()) for p in POLICIES}
    grid("Components by size band", ["1", "2", "3-5", "6-20", "21+", "hub slots", "hub slots merging copies", "hub types"],
         lambda p, k: (bc[p][k] if k[0].isdigit() else len(P[p]["hubs"]) if k == "hub slots" else len(P[p]["htypes"]) if k == "hub types"
                       else sum(1 for h in P[p]["hubs"] if h.get("copies", 1) > 1)))

    def nek(r):
        if r.startswith("unplaced:"):
            return "unplaced: " + r[9:].split(" (")[0].strip()
        return next((nm for pre, nm in NOEV_KINDS if r.startswith(pre)), "other")
    sv = {}
    for p in POLICIES:
        pp = C[p]["pp"]
        sv[p] = collections.Counter(v[0] for v in pp.values())
        sv[p].update(f"apart/{v[2]}" for v in pp.values() if v[0] == "apart")
        sv[p].update(f"fold/{v[2]}" for v in pp.values() if v[0] == "fold")
        sv[p].update(f"no-evidence: {nek(v[4])}" for v in pp.values() if v[0] == "no-evidence")
    grid("Projected survivors (placeholders)", ["fold"] + sorted(k for k in set().union(*sv.values()) if k.startswith("fold/"))
         + ["apart"] + sorted(k for k in set().union(*sv.values()) if k.startswith("apart/"))
         + ["no-evidence"] + sorted(k for k in set().union(*sv.values()) if k.startswith("no-evidence:")), lambda p, k: sv[p][k])

    hub_of = collections.defaultdict(list)
    for h in E["hubs"]:
        for r in sorted({find(k) for k in h["types"]}):
            hub_of[r].append(h)
    ht_of = collections.defaultdict(list)
    for h in E["htypes"]:
        for k in sorted(set([h["type"]] + h["partners"])):
            ht_of[find(k)].append(h["type"])
    conf_of = collections.defaultdict(list)
    for L in E["refused"]:
        if L["reason"] in ("conflict", "size"):
            for r in sorted({find(L["a"]), find(L["b"])}):
                conf_of[r].append(L)

    def why_target(t, ms):
        kl = rows[t]["klass"]
        if kl in ("PsyQ", "ledgered"):
            return f"{kl} member"
        ties = [k for k in ms if k != t and rows[k]["klass"] == kl and reach.get(k, 0) == reach.get(t, 0)]
        return f"highest reach {reach.get(t, 0)}" + (f" (tied with {len(ties)}; lowest file:line {rows[t]['file_line']})" if ties else "")

    def size_verdict(c, ms):
        if c["lb"]:
            sz, (k, kind, ci) = sorted(c["lb"].items())[0]
            return (f"{sz} B load-bearing: {k} {kind} {ci}" + (f"; accessed extent 0x{c['ext'][0]:X} ({c['ext'][1]})" if c["ext"] else ""))
        sz = max((rows[k]["size"] for k in ms if isinstance(rows[k]["size"], int)), default="?")
        return f"{sz} B (largest member; no load-bearing member)" + (f"; accessed extent 0x{c['ext'][0]:X} ({c['ext'][1]})" if c["ext"] else "")

    def admits(root, ms, t):
        for k in ms:
            L = CE["admit"].get(k)
            if k != t and L:
                o.append(f"  - `{k}`: {L['cls']}/{L['sub']} {L['a']}~{L['b']}: {L['cite_a']} | {L['cite_b']}")

    o.extend(["## The 10 largest components (policy effective)", ""])
    for root, c in CE["cs"][:10]:
        ms, t = c["members"], CE["tgt"][root]
        cf = conf_of.get(root, [])
        cfd = list({(L["reason"], L["a"], L["b"], L["sub"], L.get("detail", "-")): 0 for L in cf})
        tc_ = CE["touch"][root]
        hs = sorted(hub_of.get(root, ()), key=lambda h: (-len(h["types"]), str(h["slot"])))
        o.extend([f"### {CE['cid'][root]}: {len(ms)} types · target `{t}` ({why_target(t, ms)}) · projected reach "
                  f"{sum(reach.get(k, 0) for k in ms)}", "",
                  f"- members: {', '.join(ms)}", f"- size: {size_verdict(c, ms)}",
                  f"- width conflicts / size vetoes refused at its edge: {len(cf)} links, {len(cfd)} distinct"
                  + "".join(f"\n  - {r_} {a_}~{b_} ({s_}): {d_}" for r_, a_, b_, s_, d_ in cfd[:3]),
                  f"- refused links touching it: " + (" · ".join(f"{r} {n}" for r, n in sorted(tc_.items())) or "none"),
                  f"- hub slots touching it: {len(hs)}" + "".join(f"\n  - {_slot_s(h['slot'])} ({len(h['types'])} types; {h['why']})"
                                                                for h in hs[:5]),
                  f"- hub types touching it: {_cap(sorted(set(ht_of.get(root, ()))), 8) or 'none'}",
                  "- admitting links (one cite each):"])
        admits(root, ms, t)
        o.append("")
    small = sorted((hashlib.sha1(",".join(c["members"]).encode()).hexdigest(), root) for root, c in CE["cs"] if 2 <= len(c["members"]) <= 5)
    o.extend(["## 10 sampled small components (2-5 members; first 10 by sha1 of the member list)", ""])
    for _, root in small[:10]:
        c = comp[root]
        ms, t = c["members"], CE["tgt"][root]
        o.append(f"- {CE['cid'][root]}: {', '.join(ms)} · target `{t}` ({why_target(t, ms)}) · size {size_verdict(c, ms)}")
        admits(root, ms, t)
    o.append("")

    o.extend(["## Hubs and hub types (policy effective)", "",
              f"Hub slots {len(E['hubs'])} (merging h_exact copies: {sum(1 for h in E['hubs'] if h.get('copies', 1) > 1)}); "
              f"top 20 by types refused:", ""])
    for h in sorted(E["hubs"], key=lambda h: (-len(h["types"]), str(h["slot"])))[:20]:
        o.append(f"- {_slot_s(h['slot'])}: {len(h['types'])} types, {h.get('copies', 1)} copies; {h['why']}; {h['cites'][0] if h['cites'] else '-'}")
    for p in ("effective", "views"):
        o.extend(["", f"Hub types ({p}) {len(P[p]['htypes'])}; top 20 by links refused:", ""])
        for h in sorted(P[p]["htypes"], key=lambda h: (-h["refused"], h["type"]))[:20]:
            o.append(f"- `{h['type']}`: {len(h['partners'])} partners, {h['refused']} links refused; {h['why']}; partners "
                     f"{_cap(h['partners'], 12)}")
    o.append("")

    def ckind(L):
        d = L.get("detail", "")
        if L["reason"] == "size":
            return "size: two load-bearing sizes" if d.startswith("load-bearing") else "size: access past the load-bearing size"
        off = int(d.split(":")[0], 16) if d.startswith("0x") else -1
        kind = "partial overlap" if "@0x" in d else "width" if re.search(r" \d+B ", d) else "sign"
        return f"conflict: {kind} at " + ("0x0" if off == 0 else "0x1-0xF" if 0 < off < 0x10 else ">= 0x10")
    cv = [L for L in E["refused"] if L["reason"] in ("conflict", "size")]
    ck = collections.Counter(ckind(L) for L in cv)
    o.extend(["## Conflicts and size vetoes (policy effective)", "", f"{len(cv)} refused links; by kind and offset:", ""]
             + [f"- {k}: {n}" for k, n in sorted(ck.items())]
             + ["", "Top 20 by the two endpoints' reach:", ""])
    for L in sorted(cv, key=lambda L: (-(reach.get(L["a"], 0) + reach.get(L["b"], 0)), L["cite_a"], L["cite_b"], L["a"], L["b"]))[:20]:
        o.append(f"- {L['reason']} {L['a']}~{L['b']} ({L['cls']}/{L['sub']}): {L.get('detail', '-')}; link {L['cite_a']} | {L['cite_b']}")
    o.append("")

    dp = R["dp"]
    o.extend(["## DECL-PARAM (outcome R179)", "",
              f"Rows {len(dp)} · names {len({d['name'] for d in dp})} · declaration lines {len({d['decl'] for d in dp})} · resolved by the "
              "folds: " + " · ".join(f"{p} {sum(1 for d in dp if X['dres'][(id(d), p)] == 'yes')}" for p in POLICIES)
              + f" · struct vs void/scalar (apart, not DECL-PARAM) {R['dp_apart']['struct vs void/scalar']}", ""])
    tr = X["trows"]
    vk = {p: collections.Counter(tr[k][3 + i].split(" (")[0] for k in tr) for i, p in enumerate(POLICIES)}
    grid(f"Twins re-judged ({len(tr)} docs/struct-twins.md classes)", ["linked", "split", "apart holds"], lambda p, k: vk[p][k])
    o.extend(["Linked or split under any policy (lhash: typed | effective | views):", ""]
             + [f"- {k}: {' | '.join(tr[k][3:])}" for k in sorted(tr) if any(not v.startswith("apart") for v in tr[k][3:])] + [""])

    pp = CE["pp"]
    surv = [k for k in ph if pp[k][0] != "fold"]
    sc = collections.Counter("component target" if pp[k][4].startswith("target of") else f"{pp[k][0]}/{pp[k][2]}" for k in surv)
    o.extend(["## Naming scope (policy effective)", "",
              f"Placeholders surviving the folds (to name): {len(surv)} · " + " · ".join(f"{k} {n}" for k, n in sorted(sc.items())), "",
              "Top 20 survivors by projected reach (sum of the component members' reach):", ""])
    for k in sorted(surv, key=lambda k: (-sum(reach.get(m, 0) for m in comp[find(k)]["members"]), k))[:20]:
        c = comp[find(k)]
        ms = c["members"]
        acc = [f"0x{off:X} {e[0]}({w})" for off in sorted(c["wm"]) for w, e in sorted(c["wm"][off].items())]
        d = rows[k].get("def")
        mem = sorted(T.members(d).items(), key=lambda kv: (kv[1][0], kv[0])) if d else []
        un = [f"0x{off:X} {nm}" for nm, (off, _) in mem if off not in c["wm"]]
        o.extend([f"- `{k}`: projected reach {sum(reach.get(m, 0) for m in ms)} · {len(ms)} members"
                  + (f" ({_cap([m for m in ms if m != k], 8)})" if len(ms) > 1 else ""),
                  f"  - accessed ({len(acc)}): {_cap(acc, 16) or 'none'}", f"  - unaccessed ({len(un)}): {_cap(un, 16) or 'none'}"])
    o.extend(["", "## Planned field style", "", FIELD_STYLE, ""])

    bt = {b: collections.defaultdict(list) for b in ("B1", "B2", "B3", "B4")}
    for k in ph:
        if pp[k][0] != "fold":
            continue
        r = find(k)
        n = len(comp[r]["members"])
        b = "B4" if n >= 21 else "B3" if n >= 6 else "B1" if pp[k][2] in ("global", "body") else "B2"
        bt[b][r].append(k)
    o.extend(["## Candidate fold batches (policy effective; mechanical)", "",
              "B1 class global+body folds in components of 2-5 · B2 pointer folds in 2-5 · B3 components 6-20 · B4 each 21+ component "
              "on its own.", ""])
    for b in ("B1", "B2", "B3", "B4"):
        o.append(f"- {b}: {sum(len(v) for v in bt[b].values())} folds in {len(bt[b])} components")
    for b in ("B1", "B2", "B3"):
        o.extend(["", f"### {b}", ""] + [f"- {CE['cid'][r]} `{CE['tgt'][r]}` <- {', '.join(v)}"
                                         for r, v in sorted(bt[b].items(), key=lambda kv: int(CE['cid'][kv[0]][1:]))])
    o.extend(["", "### B4", ""] + [f"- {CE['cid'][r]} `{CE['tgt'][r]}`: {len(v)} folds" for r, v in
                                   sorted(bt["B4"].items(), key=lambda kv: int(CE['cid'][kv[0]][1:]))] + [""])
    return "\n".join(o)


def links_inputs(jobs):
    """S for links_build from the built tree; exit 2 naming a missing input"""
    global _LWANTED
    aliases, var = se.mk_vars()
    need = [se.OUT_DIR / "census.jsonl"]
    for a in aliases:
        need += [se.elf_path(a), REPO / var[(a, "SIG")]]
        dd = REPO / "build" / "src" / ("" if a == "main" else a)
        if not any(dd.glob("*.d")):
            need.append(dd / "*.d")
    miss = [p for p in need if "*" in p.name or not p.exists()]
    if miss:
        print(f"struct_twins --links: missing input {miss[0].relative_to(REPO)} (+{len(miss) - 1} more); build the fleet and run "
              f"tools/sig_evidence.py -j 16 first", file=sys.stderr)
        sys.exit(2)
    newest = max(se.elf_path(a).stat().st_mtime for a in aliases)
    if (se.OUT_DIR / "census.jsonl").stat().st_mtime < newest:
        print("struct_twins --links: build/sig_evidence/census.jsonl is older than the linked ELFs; run tools/sig_evidence.py -j 16",
              file=sys.stderr)
        sys.exit(2)
    parsed, tus, symtab, images, stacks, cls_of, info, rl, orphans = se.compare_inputs(jobs)
    J = se.join_fns(parsed, tus, symtab, images, stacks, cls_of)
    import concurrent.futures
    with concurrent.futures.ThreadPoolExecutor(8) as ex:
        syms = dict(zip(aliases, ex.map(se.elf_syms, aliases)))
    own_sym = {a: {(nm, va) for va, _, t, nm in syms[a] if t not in "Aa"} for a in aliases}
    sig = {}
    for a in aliases:
        for ln in (REPO / var[(a, "SIG")]).read_text().splitlines():
            if ln.strip():
                r = json.loads(ln)
                if r.get("src") != "IMPORTED":
                    sig.setdefault((a, int(r["addr"], 16)), (r["h_exact"], int(r.get("nins") or 0)))
    u = type_universe()
    rows = inventory_defs(u)
    types = LTypes(rows, u)
    walk = tc.walk_all(jobs)["results"]
    files = sorted(str(p.relative_to(REPO)) for d in ("src", "include") for p in (REPO / d).rglob("*")
                   if p.suffix in (".c", ".h") and p.is_file() and not p.name.startswith(".cdecl"))
    _LWANTED = set(types.key_of) | set(types.ambiguous)
    import multiprocessing as mp
    with mp.get_context("fork").Pool(jobs) as pool:
        scanned = list(pool.imap(_links_scan, [(f, None) for f in files], chunksize=16))
    return dict(types=types, tus=tus, join=J, images=images, stacks=stacks, own_sym=own_sym, sig=sig,
                read=lambda rel: (REPO / rel).read_text(errors="replace"), walk={k: v for k, v in walk.items() if v}, binds=[(r, b) for r, b, _, _ in scanned], events=[(r, e) for r, _, e, _ in scanned],
                uses=[(r, x) for r, _, _, x in scanned])


def load_reach(T):
    out = {}
    p = REPO / "docs" / "leverage-types.tsv"
    for ln in p.read_text().splitlines()[1:]:
        c = ln.split("\t")
        k = T.key_of.get(c[1]) if len(c) > 3 else None
        if k and c[3].isdigit():
            out[k] = max(out.get(k, 0), int(c[3]))
    return out


def links(out_dir, jobs, propose=None, report=None):
    import time
    t0 = time.time()
    S = links_inputs(jobs)
    R = links_build(S)
    twins, _ = tc.load_twins(TWINS_DOC.read_text() if TWINS_DOC.exists() else "")
    summ, tsv, props, X = links_render(R, load_reach(S["types"]), twins)
    out = REPO / out_dir
    out.mkdir(parents=True, exist_ok=True)
    for name, text in sorted(tsv.items()):
        (out / name).write_text(text)
    print("\n".join(summ))
    print(f"(tables -> {out.relative_to(REPO) if out.is_relative_to(REPO) else out}: {', '.join(sorted(tsv))})")
    if propose:
        ph = {k: r for k, r in S["types"].row.items() if r["klass"] == "placeholder"}
        have, dup, bad = ledger_read(LEDGER)
        new, kept, applied = ledger_write(LEDGER, ph, have, props[propose])
        cnt = collections.Counter(v[0] for v in props[propose].values())
        print(f"--propose (policy {propose}): {len(ph)} placeholders -> {LEDGER.relative_to(REPO)} · "
              + " · ".join(f"{d} {cnt[d]}" for d in DISPOSITIONS[1:]) + f" · applied kept {applied} · new {new} · stale kept {kept}")
    if report:
        import subprocess
        head = subprocess.run(["git", "rev-parse", "HEAD"], cwd=REPO, capture_output=True, text=True).stdout.strip() or "unknown"
        dirty = subprocess.run(["git", "status", "--porcelain", "--", "src", "include"], cwd=REPO, capture_output=True, text=True).stdout
        text = links_report(R, X, head + (" + uncommitted changes under src/ or include/" if dirty.strip() else ""))
        rp = (REPO / report).resolve()
        rp.write_text(text)
        print(f"--report: {rp.relative_to(REPO) if rp.is_relative_to(REPO) else rp} ({text.count(chr(10)) + 1} lines)")
    print(f"runtime {time.time() - t0:.0f} s", file=sys.stderr)


# --selftest: the method doc's fixtures on a synthetic tree (its own symtab, .d map, sig rows)
ST_HDR = """typedef struct LookA { s32 a; s16 b; } LookA;
typedef struct LookB { s32 a; s16 b; } LookB;
typedef struct GA { s32 a; s32 b; } GA;
typedef struct GB { s32 a; s32 b; s32 c; } GB;
typedef struct OA { s32 a; } OA;
typedef struct OB { s16 a; } OB;
typedef struct PA { s32 a; } PA;
typedef struct PB { s32 a; s32 b; } PB;
typedef struct WA { u16 x; } WA;
typedef struct WB { u32 x; } WB;
typedef struct HubT { s32 tag; } HubT;
typedef struct H1 { s32 a; } H1;
typedef struct H2 { s32 a; } H2;
typedef struct H3 { s32 a; } H3;
typedef struct H4 { s32 a; } H4;
typedef struct EA { s32 a; s32 b; } EA;
typedef struct EM { s32 a; } EM;
typedef struct PX { s32 a; } PX;
typedef struct PM1 { s32 a; } PM1;
typedef struct PM2 { s32 a; } PM2;
typedef struct VA { s32 a; } VA;
typedef struct VB { s32 a; s32 b; } VB;
typedef struct BVA { s32 a; } BVA;
typedef struct BVB { s32 a; s32 b; } BVB;
typedef struct BNA { s32 a; } BNA;
typedef struct BNB { s32 a; s32 b; } BNB;
typedef struct EFA { s32 a; } EFA;
typedef struct EFB { s32 a; s32 b; } EFB;
typedef struct HT { s32 a; s32 b; } HT;
typedef struct HG { s32 a; s32 b; } HG;
typedef struct HQ1 { u16 x; } HQ1;
typedef struct HQ2 { u32 x; } HQ2;
typedef struct HQ3 { s32 a; } HQ3;
typedef struct HQ4 { s32 a; } HQ4;
typedef struct CS { s32 a; } CS;
typedef struct CS1 { s32 a; } CS1;
typedef struct CS2 { s32 a; } CS2;
typedef struct CS3 { s32 a; } CS3;
typedef struct CS4 { s32 a; } CS4;
typedef struct BWA { u16 x; } BWA;
typedef struct BWB { u32 x; } BWB;
"""
ST_MAIN = """#include "struct_types.h"
extern GA D_80018000;
extern WA D_80018100;
s32 useLookA(LookA *p) { return p->a + p->b; }
s32 readWA(void) { s32 v; v = D_80018100.x; return v; }
void hubfn(HubT *p) { p->tag = 1; }
void c1(H1 *x) { hubfn(x); }
void c2(H2 *x) { hubfn(x); }
void c3(H3 *x) { hubfn(x); }
void c4(H4 *x) { hubfn(x); }
void effTake(void *p) { ((EM *)p)->a = 1; }
void effCall(EA *q) { effTake(q); }
void polyTake(void *p, s32 k) { if (k) { ((PM1 *)p)->a = 1; } else { ((PM2 *)p)->a = 2; } }
void polyCall(PX *q) { polyTake(q, 0); }
s32 viewer(VA *a) { return ((VB *)a)->b; }
void func_80010D00(void) { ((BVA *)getp())->a = 1; }
void func_80010E00(void) { ((BNA *)getp())->a = 1; }
void efTake(void *p) { ((EFB *)p)->a = 1; }
void efCall(void) { s32 q; q = getp(); ((EFA *)q)->a = 2; efTake(q); }
extern HT D_80018200;
void ht1(HT *p) { p->b = 1; }
void ht2(HT *p) { p->b = 2; }
void ht3(HT *p) { p->b = 3; }
void ht4(HT *p) { p->b = 4; }
void k1(HQ1 *x) { x->x = 1; ht1(x); }
void k2(HQ2 *x) { x->x = 2; ht2(x); }
void k3(HQ3 *x) { x->a = 3; ht3(x); }
void k4(HQ4 *x) { x->a = 4; ht4(x); }
void func_80011900(void) { ((BWA *)getp())->x = 1; }
"""
ST_OVA = """#include "struct_types.h"
extern GB D_80018000;
extern WB D_80018100;
extern OA D_80108000;
s32 useLookB(LookB *p) { return p->a + p->b; }
s32 readWB(void) { s32 v; v = D_80018100.x; return v; }
s32 readOA(void) { return D_80108000.a; }
void func_80100400(void) { ((BVB *)getp())->a = 1; }
void func_80100500(void) { ((BNB *)getq())->a = 1; }
extern HG D_80018200;
void cpy(CS *p) { p->a = 1; }
void ca1(CS1 *x) { cpy(x); }
void ca2(CS2 *x) { cpy(x); }
void func_80100900(void) { ((BWB *)getp())->x = 1; }
"""
ST_OVB = """#include "struct_types.h"
extern OB D_80108000;
void takeP(PB *p) { p->a = 0; }
void callP(PA *q) { takeP(q); }
s32 readOB(void) { return D_80108000.a; }
void cpy(CS *p) { p->a = 1; }
void cb1(CS3 *x) { cpy(x); }
void cb2(CS4 *x) { cpy(x); }
"""


def links_selftest_S():
    global _LWANTED
    hdr = tc.CANON_HEADERS[-1]
    files = {hdr: ST_HDR, "src/main.c": ST_MAIN,
             "src/ov_A/a.c": ST_OVA, "src/ov_B/b.c": ST_OVB}
    u = type_universe({hdr: ST_HDR})
    rows = inventory_defs(u)
    types = LTypes(rows, u)
    tus = {"main": [("build/src/main.o", "src/main.c", ["src/main.c", hdr])],
           "ov_A": [("build/src/ov_A/a.o", "src/ov_A/a.c", ["src/ov_A/a.c", hdr])],
           "ov_B": [("build/src/ov_B/b.o", "src/ov_B/b.c", ["src/ov_B/b.c", hdr])]}
    images = {"main": (0x80010000, 0x80020000), "ov_A": (0x80100000, 0x80110000), "ov_B": (0x80100000, 0x80110000)}
    stacks = {"main": ["main"], "ov_A": ["main", "ov_A"], "ov_B": ["main", "ov_B"]}
    fns = {"main": ["useLookA", "readWA", "hubfn", "c1", "c2", "c3", "c4", "effTake", "effCall", "polyTake", "polyCall", "viewer",
                    "func_80010D00", "func_80010E00", "efTake", "efCall", "ht1", "ht2", "ht3", "ht4", "k1", "k2", "k3", "k4",
                    "func_80011900"],
           "ov_A": ["useLookB", "readWB", "readOA", "func_80100400", "func_80100500", "cpy", "ca1", "ca2", "func_80100900"],
           "ov_B": ["takeP", "callP", "readOB", "cpy", "cb1", "cb2"]}
    syms, cls_of, sig, own_sym = {}, {}, {}, {}
    for a, names in fns.items():
        t = collections.defaultdict(set)
        own_sym[a] = set()
        for i, nm in enumerate(names):
            va = images[a][0] + 0x100 * (i + 1)
            t[nm].add(va)
            cls_of[(a, va)] = f"{a}{nm}".ljust(40, "0")
            sig[(a, va)] = (cls_of[(a, va)], 12)
            own_sym[a].add((nm, va))
        syms[a] = t
    for m_, o_ in (("func_80010D00", "func_80100400"), ("func_80010E00", "func_80100500"),
                   ("func_80011900", "func_80100900")):   # body-view: one h_exact class each
        sig[("ov_A", min(syms["ov_A"][o_]))] = sig[("main", min(syms["main"][m_]))]
    sig[("ov_B", min(syms["ov_B"]["cpy"]))] = sig[("ov_A", min(syms["ov_A"]["cpy"]))]   # T2.c4: two copies of one routine
    for a in ("main", "ov_A"):                                # D_80018000/D_80018100: main's data, absolute in ov_A's ELF
        for nm in ("D_80018000", "D_80018100", "D_80018200"):
            syms[a][nm].add(int(nm[2:], 16))
    own_sym["main"] |= {("D_80018000", 0x80018000), ("D_80018100", 0x80018100), ("D_80018200", 0x80018200)}
    for a in ("ov_A", "ov_B"):                                # D_80108000: one address, two overlay images
        syms[a]["D_80108000"].add(0x80108000)
        own_sym[a].add(("D_80108000", 0x80108000))
    parsed = {f: se.parse_text(f, txt) for f, txt in files.items()}
    J = se.join_fns(parsed, tus, syms, images, stacks, cls_of)
    _LWANTED = set(types.key_of) | set(types.ambiguous)
    scanned = [_links_scan((f, files[f])) for f in sorted(files)]
    walk = {f: tc.walk_file(files[f], f) for f in sorted(files)}
    return dict(types=types, tus=tus, join=J, images=images, stacks=stacks, own_sym=own_sym, sig=sig, walk=walk, read=files.__getitem__,
                binds=[(r, b) for r, b, _, _ in scanned], events=[(r, e) for r, _, e, _ in scanned], uses=[(r, x) for r, _, _, x in scanned])


def links_selftest():
    outs, R = [], None
    for _ in range(2):
        R = links_build(links_selftest_S())
        rr = links_render(R, {})
        outs.append((rr[:3], links_report(R, rr[3], "selftest")))
    Q = R["P"]["effective"]
    acc = {(L["cls"], frozenset((L["a"], L["b"]))) for L in Q["accepted"]}
    ref = {(L["reason"], frozenset((L["a"], L["b"]))) for L in Q["refused"]}
    f = Q["find"]
    hub_types = {frozenset(("HubT", h)) for h in ("H1", "H2", "H3", "H4")}
    sub = {pol: {(L["sub"], frozenset((L["a"], L["b"]))) for L in R["P"][pol]["accepted"]} for pol in POLICIES}
    fv, ft = R["P"]["views"]["find"], R["P"]["typed"]["find"]
    planted = {"X1": dict(key="X1", disposition="fold", target="-", **{"class": "pointer"}, evidence="C1: src/a.c:1 | src/a.c:2", reason="arg link"),
               "X2": dict(key="X2", disposition="fold", target="X1", **{"class": "pointer"}, evidence="C1: src/a.c:1 | src/a.c:2", reason="arg link")}
    prob = dict(ledger_problems(planted, set(planted)))
    cases = [
        ("look-alike pair (equal layouts and widths, no link) stays unlinked",
         f("LookA") != f("LookB") and not any(frozenset(("LookA", "LookB")) == p for _, p in acc)),
        ("shared-global pair links (class global)", ("global", frozenset(("GA", "GB"))) in acc and f("GA") == f("GB")),
        ("same address in two overlay images does not link", f("OA") != f("OB") and not any(frozenset(("OA", "OB")) == p for _, p in acc | ref)),
        ("pointer-flow pair (arg into a dereferenced parameter) links (class pointer)",
         ("pointer", frozenset(("PA", "PB"))) in acc and f("PA") == f("PB")),
        ("width conflict (u16 vs u32 at one offset) refuses the fold; both stay apart",
         ("conflict", frozenset(("WA", "WB"))) in ref and f("WA") != f("WB")),
        ("hub slot refuses its links", all(("hub", p) in ref for p in hub_types) and not any(p in hub_types for _, p in acc)
         and any(h["slot"][0] == "param" for h in Q["hubs"])),
        ("an untyped param cast to one type links arg-eff (effective, not typed)",
         ("arg-eff", frozenset(("EA", "EM"))) in sub["effective"] and f("EA") == f("EM") and ft("EA") != ft("EM")),
        ("a param cast to two types is a poly slot, its links refused",
         ("poly", frozenset(("PX", "PM1"))) in ref and ("poly", frozenset(("PX", "PM2"))) in ref and f("PX") != f("PM1")
         and f("PX") != f("PM2") and any(set(e["types"]) == {"PM1", "PM2"} for _, e in R["poly"])),
        ("the views policy links a local view the effective policy does not",
         ("view", frozenset(("VA", "VB"))) in sub["views"] and fv("VA") == fv("VB") and f("VA") != f("VB")),
        ("body-view: two copies, same masked text, A vs B at one cast position link (effective, not typed)",
         ("body-view", frozenset(("BVA", "BVB"))) in sub["effective"] and f("BVA") == f("BVB") and ft("BVA") != ft("BVB")),
        ("body-view negative: masked texts differ at that position, no body-view link",
         not any(("body-view", frozenset(("BNA", "BNB"))) in sub[p] for p in POLICIES) and f("BNA") != f("BNB")),
        ("eff-flow: an untyped caller local viewed as A passed to a parameter viewed as B links (effective, not typed)",
         ("eff-flow", frozenset(("EFA", "EFB"))) in sub["effective"] and f("EFA") == f("EFB") and ft("EFA") != ft("EFB")),
        ("a planted ledger check fails on a fold without target (and passes the same fold with one)",
         prob.get("fold without a ledger / PsyQ / ledgered target") == ["X1"] and len(prob) == 1),
        ("hub type: >= HUB_K pointer partners, two conflicting: its pointer links refused, its global link kept (effective)",
         all(("hub-type", frozenset(("HT", q))) in ref for q in ("HQ1", "HQ2", "HQ3", "HQ4")) and ("global", frozenset(("HT", "HG"))) in acc
         and f("HT") == f("HG") and f("HT") != f("HQ3") and any(h["type"] == "HT" for h in Q["htypes"])
         and not R["P"]["typed"]["htypes"] and ft("HT") == ft("HQ1")),
        ("copies of one routine are one hub slot (effective); per copy (typed) no hub",
         all(("hub", frozenset(("CS", c))) in ref for c in ("CS1", "CS2", "CS3", "CS4"))
         and any(h["slot"][0] == "param" and str(h["slot"][1]).startswith("h") and h["copies"] == 2 for h in Q["hubs"])
         and all(ft("CS") == ft(c) for c in ("CS1", "CS2", "CS3", "CS4")) and f("CS") != f("CS1")),
        ("cast-only types linked by body-view, conflicting (u16 vs u32) only through view accesses: the fold is refused",
         ("conflict", frozenset(("BWA", "BWB"))) in ref and f("BWA") != f("BWB")),
        ("two runs print identical output", outs[0] == outs[1]),
    ]
    for name, ok in cases:
        print(f"{'PASS' if ok else 'FAIL'} {name}")
    bad = sum(1 for _, ok in cases if not ok)
    print(f"struct_twins --selftest: {len(cases) - bad}/{len(cases)} pass")
    return 1 if bad else 0


def main():
    ap = argparse.ArgumentParser(description=__doc__.split("\n")[0])
    ap.add_argument("--census-dir", default=CENSUS_DEFAULT, help="census dir holding dup_gating.tsv and type_census.json (default: type_census OUT_DIR_DEFAULT, %(default)s)")
    ap.add_argument("--write", action="store_true", help="regenerate the `## Twins` section of docs/struct-twins.md")
    ap.add_argument("--show", metavar="LHASH", help="every name's objects for one class")
    ap.add_argument("--inventory", action="store_true", help="one row per struct/union definition; prints the denominators")
    ap.add_argument("--out", default=INVENTORY_DEFAULT, help="--inventory output TSV (default %(default)s)")
    ap.add_argument("--dispositions", action="store_true", help="write/refresh config/struct_dispositions.tsv")
    ap.add_argument("--check", action="store_true", help="with --dispositions: count the ledger, exit 1 on a missing/duplicate/unknown row")
    ap.add_argument("--ledger", default=str(LEDGER), help="with --dispositions: the ledger path (default %(default)s)")
    ap.add_argument("--links", action="store_true", help="the merge-evidence census (docs/ops/p345-t2-struct-merge-evidence.md)")
    ap.add_argument("--out-dir", default=LINKS_DIR, help="with --links: the tables' directory (default %(default)s)")
    ap.add_argument("-j", type=int, default=16, help="with --links: worker processes (default %(default)s)")
    ap.add_argument("--propose", action="store_true", help="with --links: write the chosen policy's proposals into the ledger")
    ap.add_argument("--report", nargs="?", const=REPORT_DEFAULT, metavar="PATH",
                    help="with --links: write the generated merge report (default %(const)s)")
    ap.add_argument("--policy", choices=POLICIES, default="effective", help="with --propose: the policy (default %(default)s)")
    ap.add_argument("--selftest", action="store_true", help="the --links fixtures on a synthetic tree; exit 0 only if all pass")
    a = ap.parse_args()
    if a.selftest or a.links:
        need_se()
    if a.selftest:
        return links_selftest()
    if a.links:
        return links(a.out_dir, a.j, a.policy if a.propose else None, a.report)
    if a.inventory:
        return inventory(a.out)
    if a.dispositions:
        return dispositions(Path(a.ledger).resolve(), a.check)
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
    sys.exit(main())
