#!/usr/bin/env python3
"""tools/restruct.py — the struct rewrite engine (Phase 37). T2 form: `--try` (rung 1 on one body), `--probe` (the T2 probe),
`--audit-layouts` (the layout engine against cc1), `--fanout-cost` (one canonical-header edit over every includer).

RUNG 1 (body-local, no signature change): every raw cast on a typed base becomes a typed cast-member access,
    *(u16 *)(a0 + 0x3C)  ->  ((P37S_xxxxxxxx *)a0)->unk3C
with the type declared once, at file scope, right before the function (a struct built from the struct map's layout for that
base's cluster: `unk<HEX>` fields at the offsets the sites use, `u8 pad<HEX>[n]` between them). Rung 1's RTL is a COMPONENT_REF —
the same MEM_IN_STRUCT_P flag the final `a0->unk3C` carries — so it decides the byte question (the `/s` model, cse_expr.md §4)
without touching a declaration in any other TU. The oracle is tools/delever_oracle.py: the TU compiled IN PLACE through the
build's own recipe against the snapshot baseline; a header body is judged on EVERY includer; the file is restored from this
process's own snapshot (R102). S+A: a body whose member spelling DIFFERS and that carries marked levers is judged again with the
levers stripped (delever_search.lever_free_body) — the struct hypothesis. The residual is classified by delever_search.classify
(REG / COUNT / ORDER / MIXED) over the masked instruction words.

The probe (T2) draws a stratified sample of bodies from the census (.run/P37/census/sites.jsonl + body_base_type.json + the
struct map), runs rung 1 (+ S+A) on each, and writes .run/P37/probe/probe_rows.jsonl + probe_table.md with every denominator.
Nothing here writes to the tree except the in-place compile, which is restored before the function returns.
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
import time
from concurrent.futures import ProcessPoolExecutor

sys.path.insert(0, str(pathlib.Path(__file__).resolve().parent))
import share_census as sc          # noqa: E402
import type_census as tc           # noqa: E402
import delever as dl               # noqa: E402
import delever_oracle as oracle    # noqa: E402
import delever_search as ds        # noqa: E402
import masked_diff as md           # noqa: E402

REPO = pathlib.Path(__file__).resolve().parent.parent
CENSUS = REPO / ".run/P37/census"
PROBE = REPO / ".run/P37/probe"
RAW_FORMS = ("P", "I", "X", "M")
TYPE_OF = {(1, "u"): "u8", (1, "s"): "s8", (2, "u"): "u16", (2, "s"): "s16", (4, "u"): "u32", (4, "s"): "s32",
           (8, "u"): "u64", (8, "s"): "s64", (4, "f"): "f32", (8, "f"): "f64"}

# ----------------------------------------------------------------------------------------------------------------------
# the census's view of a body
# ----------------------------------------------------------------------------------------------------------------------
_map_cache = None

def struct_map():
    global _map_cache
    if _map_cache is None:
        p = CENSUS / "struct_map.json"
        if not p.exists():
            sys.exit("restruct: no struct map — run `tools/type_census.py -j 16 --sites` first")
        _map_cache = {t["name"]: t for t in json.loads(p.read_text())["types"]}
    return _map_cache

def body_sites(tu, fn):
    """The census's site records for one body, RE-WALKED on the current file (positions on the raw text via a same-length mask)."""
    raw = (REPO / tu).read_text(errors="surrogateescape")
    masked = dl.same_len_mask(raw)
    line_of = lambda idx: masked.count("\n", 0, idx) + 1
    recs = sc.scan_text(raw, tu, shared_defs=None)
    defs = [r for r in recs if r["form"] == "def"]
    span_of_line = {}
    for d in defs:
        for ln in range(d["line"], d["end"] + 1):
            span_of_line[ln] = d
    params_of = {}
    for d in defs:
        head_start = dl.line_starts(masked)[d["line"] - 1]
        brace = masked.find("{", head_start)
        head = masked[head_start:brace] if brace != -1 else ""
        m = re.search(r"\b" + re.escape(d["name"]) + r"\s*\(", head)
        if m:
            inner, close = tc._paren_body(head, m.end() - 1)
            params_of[d["name"]] = tc._param_names(inner or "", head[close + 1:] if close != -1 else "")
    sites, _ = tc.find_sites(masked, tu, span_of_line, line_of, params_of)
    d = next((x for x in defs if x["name"] == fn), None)
    return raw, masked, d, [s for s in sites if s.get("fn") == fn]

def field_type(w, sg, ctypes):
    if sg == "p":
        # a pointer field: the sites' pointee when they agree, else void *
        pt = collections.Counter(c.rstrip("* ").strip() + " *" for c in ctypes if c and c.count("*") >= 2)
        return pt.most_common(1)[0][0] if len(pt) == 1 else "void *"
    return TYPE_OF.get((w, sg))

def build_type(tname, layout, ctypes_by_off):
    """The struct text for a cluster's layout [(off, w, sign, n)]: fields at their offsets, pads between, overlaps skipped.
    Returns (text, fields{off: (w, sign, name)}, skipped)."""
    fields, skipped, lines, cur = {}, [], [], 0
    for (off, w, sg, n) in sorted(layout, key=lambda x: (x[0], -x[3])):
        if off < cur or w is None or w == 0:
            skipped.append((off, w, sg))
            continue
        if off % (8 if w == 8 else min(w, 4)) != 0:
            # an access at an offset its width cannot be aligned to (an `lh` at +0x79): not a field of THIS base — a cross-base
            # contamination of the cluster, or an unaligned lwl/lwr pair; gcc would realign it and shift every later field
            skipped.append((off, w, "misaligned"))
            continue
        t = field_type(w, sg, ctypes_by_off.get(off, []))
        if t is None:
            skipped.append((off, w, sg))
            continue
        if off > cur:
            lines.append(f"    /* {cur:#06x} */ u8 pad{cur:X}[{off - cur:#x}];")
        name = f"unk{off:X}"
        lines.append(f"    /* {off:#06x} */ {t} {name};")
        fields[off] = (w, sg, name, t)
        cur = off + w
    text = f"typedef struct {{\n" + "\n".join(lines) + f"\n}} {tname}; /* P37 rung 1 — from the struct map (size >= {cur:#x}) */\n"
    return text, fields, skipped

def rung1_edits(raw, d, sites, tname, fields, base_key):
    """The positional edits of rung 1 for one body/base: [(pos, end, replacement, site)], skips{reason: n}."""
    edits, skips = [], collections.Counter()
    bcls, bname = base_key.split(":", 1)
    for s in sites:
        if s["form"] not in RAW_FORMS or s.get("bclass") != bcls or str(s.get("base")) != bname:
            continue
        if s.get("index") is not None or s.get("refused"):
            skips["index"] += 1
            continue
        off = s.get("off") or 0
        if off < 0:
            skips["negative-offset"] += 1
            continue
        f = fields.get(off)
        if f is None:
            skips["no-field"] += 1
            continue
        w, sg, name, ftype = f
        if s.get("width") != w:
            skips["width"] += 1
            continue
        if s.get("sign") != sg and not (s.get("access") in ("store",) and {s.get("sign"), sg} <= {"s", "u"}):
            skips["sign"] += 1
            continue
        if sg == "p":
            # a pointer field: the site's pointee must be the field's (a `void *` field cannot be indexed or dereferenced at the site)
            site_pointee = (s.get("ctype") or "").rstrip("* ").strip() + " *"
            if site_pointee != ftype:
                skips["pointee"] += 1
                continue
        base_expr = ("&" + bname) if bcls == "gaddr" else bname
        edits.append((s["pos"], s["end"], f"(({tname} *){base_expr})->{name}", s))
    edits.sort(key=lambda e: e[0])
    kept, last = [], 0
    for e in edits:
        if e[0] < last:
            skips["overlap"] += 1       # a nested site's inner span inside an outer's — the outer was skipped as `nested`
            continue
        kept.append(e); last = e[1]
    return kept, skips

def splice(raw, d, tname, edits):
    """The TU text with the given edits applied and the typedef inserted before the function (file scope)."""
    out, last = [], 0
    for (a, b, rep, _) in sorted(edits, key=lambda e: e[0]):
        out.append(raw[last:a]); out.append(rep); last = b
    out.append(raw[last:])
    text = "".join(out)
    ins = dl.line_starts(raw)[d["line"] - 1]
    return text[:ins] + _typedef_cache[tname] + text[ins:]

def rung1_text(raw, d, sites, tname, fields, base_key):
    edits, skips = rung1_edits(raw, d, sites, tname, fields, base_key)
    if not edits:
        return None, 0, skips
    return splice(raw, d, tname, edits), len(edits), skips

def greedy_casts(tu, raw, d, tname, edits, tag):
    """Rung S2: the member spelling DIFFERS — find a minimal set of sites that must stay casts (delever's rung B shape):
    leave-one-out first (n compiles), else cumulative revert in source order until IDENTICAL, then drop every revert not needed.
    Returns (kept_sites[list of site dicts], compiles, verdict) — verdict IDENTICAL when a set was found."""
    n = len(edits)
    compiles = 0
    for i in range(n):
        sub = edits[:i] + edits[i + 1:]
        v, _, _, _ = judge_text(tu, splice(raw, d, tname, sub), tag)
        compiles += 1
        if v == "IDENTICAL":
            return [edits[i][3]], compiles, "IDENTICAL"
    K = []
    for i in range(n):
        K.append(i)
        sub = [e for j, e in enumerate(edits) if j not in K]
        v, _, _, _ = judge_text(tu, splice(raw, d, tname, sub), tag)
        compiles += 1
        if v == "IDENTICAL":
            break
    else:
        return [], compiles, "NO-SET"          # even every site reverted differs: the typedef alone or the mask moved bytes — a tool defect
    # minimise
    for j in list(K):
        trial = [k for k in K if k != j]
        sub = [e for i2, e in enumerate(edits) if i2 not in trial]
        v, _, _, _ = judge_text(tu, splice(raw, d, tname, sub), tag)
        compiles += 1
        if v == "IDENTICAL":
            K = trial
    return [edits[i][3] for i in K], compiles, "IDENTICAL"

_typedef_cache = {}

# ----------------------------------------------------------------------------------------------------------------------
# the oracle wrapper (in place, restored)
# ----------------------------------------------------------------------------------------------------------------------
_recipes = None
_by_src = None
_inc = None

def recipes():
    global _recipes, _by_src, _inc
    if _recipes is None:
        _recipes = oracle.load_recipes()["recipes"]
        _by_src = oracle.recipes_by_src(_recipes)
        _inc = dl.includers()
    return _recipes, _by_src, _inc

def recs_for(tu):
    _, by_src, inc = recipes()
    return ds.recs_for(tu, by_src, inc)

def judge_text(tu, text, tag):
    """(verdict, seconds, err, candidate_object_bytes_of_first_recipe) — the file written in place and RESTORED (R102)."""
    recs = recs_for(tu)
    if not recs:
        return "NO-RECIPE", 0.0, f"no recipe compiles {tu}", None
    path = REPO / tu
    raw = path.read_text(errors="surrogateescape")
    st = path.stat()
    write_path = tu if tu.endswith(".h") else None
    try:
        total, first, data0 = 0.0, None, None
        for i, r in enumerate(recs):
            base = oracle.baseline_bytes(r["obj"])
            if base is None:
                first = first or ("NO-BASELINE", "")
                continue
            data, dt, err = oracle.compile_obj(r, text if i == 0 else None, tag=tag, write_path=write_path)
            total += dt
            if i == 0:
                data0 = data
            if data is None:
                v = "COMPILE-CRASH" if err.startswith("CRASH:") else "COMPILE-ERROR"
                first = first or (v, err)
            elif data != base:
                first = first or ("DIFFERS", "")
        return (first[0] if first else "IDENTICAL"), total, (first[1] if first else ""), data0
    finally:
        dl.restore_file(path, raw, st)

def classify_residual(tu, fn, cand_bytes):
    """delever_search's classifier over the body's instructions: candidate object vs the baseline object of the first recipe."""
    recs = recs_for(tu)
    if not recs or cand_bytes is None:
        return None
    base = oracle.baseline_path(recs[0]["obj"])
    tmp = PROBE / "obj" / (hashlib.sha1((tu + fn).encode()).hexdigest()[:12] + ".o")
    tmp.parent.mkdir(parents=True, exist_ok=True)
    tmp.write_bytes(cand_bytes)
    try:
        mine = md.insns_from_object(str(tmp), fn)
        tgt = md.insns_from_object(str(base), fn)
    except Exception as e:      # noqa: BLE001
        return dict(kind="UNSCORED", err=str(e)[:80])
    finally:
        tmp.unlink(missing_ok=True)
    if not mine or not tgt:
        return dict(kind="UNSCORED", err="function not found in one object")
    c = ds.classify(mine, tgt)
    return dict(kind=c["kind"], score=c["score"], n_mine=c["n_mine"], n_tgt=c["n_tgt"], pairs=c["pairs"][:4])

# ----------------------------------------------------------------------------------------------------------------------
# rung 1 on one body
# ----------------------------------------------------------------------------------------------------------------------
def try_body(tu, fn, base_key=None, tname_hint=None, tag="p37", want_sa=True, want_greedy=True):
    raw, masked, d, sites = body_sites(tu, fn)
    if d is None:
        return dict(tu=tu, fn=fn, verdict="NO-BODY")
    bbt = json.loads((CENSUS / "body_base_type.json").read_text()) if base_key is None or tname_hint is None else None
    if base_key is None:
        ent = (bbt or {}).get(tu + "|" + fn, {})
        if not ent:
            return dict(tu=tu, fn=fn, verdict="NO-TYPED-BASE")
        base_key = max(ent, key=lambda k: ent[k]["sites"])
    tname = tname_hint or (bbt or {}).get(tu + "|" + fn, {}).get(base_key, {}).get("type")
    if not tname:
        return dict(tu=tu, fn=fn, base=base_key, verdict="NO-TYPE")
    t = struct_map().get(tname)
    if not t:
        return dict(tu=tu, fn=fn, base=base_key, verdict="NO-TYPE-IN-MAP")
    ctypes_by_off = collections.defaultdict(list)
    for s in sites:
        if s.get("bclass") + ":" + str(s.get("base")) == base_key and s.get("ctype"):
            ctypes_by_off[s.get("off") or 0].append(s["ctype"])
    local_name = f"P37S_{hashlib.sha1(tname.encode()).hexdigest()[:8]}"
    ttext, fields, skipped = build_type(local_name, t["layout"], ctypes_by_off)
    _typedef_cache[local_name] = ttext
    edits, skips = rung1_edits(raw, d, sites, local_name, fields, base_key)
    n = len(edits)
    row = dict(tu=tu, fn=fn, base=base_key, type=tname, type_sites=t["sites"], type_bodies=t["bodies"], fields=len(fields),
               rewritten=n, skips=dict(skips), header=tu.endswith(".h"), levers=None)
    if not edits:
        row["verdict"] = "NO-SITE-CONVERTIBLE"
        return row
    text = splice(raw, d, local_name, edits)
    v, dt, err, cand = judge_text(tu, text, tag)
    row.update(verdict=v, seconds=round(dt, 2), err=err[:160])
    if v == "DIFFERS":
        row["residual"] = classify_residual(tu, fn, cand)
        if want_greedy:
            kept, compiles, gv = greedy_casts(tu, raw, d, local_name, edits, tag + "g")
            row["s2"] = dict(verdict=gv, kept=len(kept), compiles=compiles, members=n - len(kept),
                             kept_sites=[dict(off=k.get("off"), ctype=k.get("ctype"), access=k.get("access"), line=k.get("line")) for k in kept[:8]])
    # S+A: the body's marked levers stripped as well
    lever_sites = [s for s in ds.sites_by_body().get((tu, fn), []) if s.get("cls") in "AB" and s.get("kind") in ds.AB_KINDS]
    row["levers"] = len(lever_sites)
    if want_sa and lever_sites:
        try:
            free = ds.lever_free_body(tu, raw, fn, lever_sites)
        except ds.Unstrippable as u:
            row["sa"] = dict(verdict="UNSTRIPPABLE", why=str(u.args[0])[:120])
            return row
        # the lever-free TU: re-walk its sites (positions moved) and rewrite the same base
        m2 = dl.same_len_mask(free)
        recs2 = sc.scan_text(free, tu, shared_defs=None)
        defs2 = [r for r in recs2 if r["form"] == "def"]
        d2 = next((x for x in defs2 if x["name"] == fn), None)
        if d2 is None:
            row["sa"] = dict(verdict="NO-BODY-AFTER-STRIP")
            return row
        span2 = {}
        for x in defs2:
            for ln in range(x["line"], x["end"] + 1):
                span2[ln] = x
        line_of2 = lambda idx: m2.count("\n", 0, idx) + 1
        pnames = tc._param_names(*(lambda h: (h[0] or "", h[1]))(_head_parts(m2, d2, fn)))
        sites2, _ = tc.find_sites(m2, tu, span2, line_of2, {fn: pnames})
        sites2 = [s for s in sites2 if s.get("fn") == fn]
        text2, n2, skips2 = rung1_text(free, d2, sites2, local_name, fields, base_key)
        if text2 is None:
            row["sa"] = dict(verdict="NO-SITE-CONVERTIBLE")
            return row
        v2, dt2, err2, cand2 = judge_text(tu, text2, tag + "sa")
        row["sa"] = dict(verdict=v2, seconds=round(dt2, 2), rewritten=n2, err=err2[:120])
        if v2 == "DIFFERS":
            row["sa"]["residual"] = classify_residual(tu, fn, cand2)
        # the lever-free text ALONE (no struct): the control that says whether the struct did anything
        if v2 == "IDENTICAL":
            v3, _, _, _ = judge_text(tu, free, tag + "a")
            row["sa"]["levers_off_alone"] = v3
    return row

def _head_parts(masked, d, fn):
    ls = dl.line_starts(masked)
    head_start = ls[d["line"] - 1]
    brace = masked.find("{", head_start)
    head = masked[head_start:brace] if brace != -1 else ""
    m = re.search(r"\b" + re.escape(fn) + r"\s*\(", head)
    if not m:
        return "", ""
    inner, close = tc._paren_body(head, m.end() - 1)
    return inner, (head[close + 1:] if close != -1 else "")

# ----------------------------------------------------------------------------------------------------------------------
# the probe (T2)
# ----------------------------------------------------------------------------------------------------------------------
def draw_sample(n, seed, strata):
    """Bodies stratified by the base's kind, from body_base_type.json: returns [(tu, fn, base_key, type, stratum)]."""
    bbt = json.loads((CENSUS / "body_base_type.json").read_text())
    smap = struct_map()
    rng = random.Random(seed)
    # every (body, base) with a type; classify the stratum
    cands = collections.defaultdict(list)
    lever_bodies = {(k[0], k[1]) for k in ds.sites_by_body()}
    for key, bases in bbt.items():
        tu, fn = key.split("|", 1)
        for bk, ent in bases.items():
            t = smap.get(ent["type"])
            if not t or ent["sites"] < 2:
                continue
            bcls = bk.split(":", 1)[0]
            if t["sites"] >= 50000:
                stratum = "A-entity(0x24C)" if t["size_hint"] >= 0x200 else "B-large-ptr-globals"
            elif bcls in ("gaddr", "global") and t["bodies"] >= 5:
                stratum = "D-record-tables"
            elif t["size_hint"] in (8, 32, 48, 16) and t["bodies"] >= 20:
                stratum = "C-matrix/vector-shaped"
            elif tu.startswith("src/shared/"):
                stratum = "E-shared-header-bodies"
            elif t["bodies"] >= 2:
                stratum = "F-other-multi-body-types"
            else:
                stratum = "G-single-body-types"
            lev = (tu, fn) in lever_bodies
            cands[stratum].append((tu, fn, bk, ent["type"], stratum, ent["sites"], lev))
    out = []
    for stratum, want in strata.items():
        pool = cands.get(stratum, [])
        rng.shuffle(pool)
        # half of each stratum from lever-bearing bodies where available (the struct hypothesis needs them)
        lev = [c for c in pool if c[6]]
        non = [c for c in pool if not c[6]]
        take = lev[: want // 2] + non[: want - min(len(lev), want // 2)]
        if len(take) < want:
            take = (lev + non)[:want]
        out.extend(take)
    return out, {k: len(v) for k, v in cands.items()}

def _probe_worker(args):
    tu, fn, bk, tname, stratum, nsites, lev = args
    try:
        row = try_body(tu, fn, base_key=bk, tname_hint=tname, tag="pr" + hashlib.sha1(tu.encode()).hexdigest()[:6])
    except Exception as e:      # noqa: BLE001
        row = dict(tu=tu, fn=fn, base=bk, type=tname, verdict="TOOL-ERROR", err=repr(e)[:200])
    row.update(stratum=stratum, base_sites=nsites, lever_body=lev)
    return row

def run_probe(a):
    PROBE.mkdir(parents=True, exist_ok=True)
    strata = {"A-entity(0x24C)": 40, "B-large-ptr-globals": 25, "C-matrix/vector-shaped": 25, "D-record-tables": 25,
              "E-shared-header-bodies": 20, "F-other-multi-body-types": 20, "G-single-body-types": 10}
    if a.sample:
        scale = a.sample / sum(strata.values())
        strata = {k: max(1, int(round(v * scale))) for k, v in strata.items()}
    sample, pool_sizes = draw_sample(a.sample or sum(strata.values()), a.seed, strata)
    # workers own whole FILES: group by tu; headers run serially at the end (their includers are other workers' files)
    by_tu = collections.defaultdict(list)
    for c in sample:
        by_tu[c[0]].append(c)
    c_files = [v for k, v in by_tu.items() if not k.endswith(".h")]
    h_files = [v for k, v in by_tu.items() if k.endswith(".h")]
    t0 = time.time()
    rows = []
    recipes()          # warm the caches in the parent before forking
    with ProcessPoolExecutor(max_workers=a.jobs) as ex:
        for res in ex.map(_probe_file, c_files):
            rows.extend(res)
    for group in h_files:
        rows.extend(_probe_file(group))
    dt = time.time() - t0
    with (PROBE / "probe_rows.jsonl").open("w") as fh:
        for r in rows:
            fh.write(json.dumps(r) + "\n")
    table = render_probe(rows, pool_sizes, dt, a.seed)
    (PROBE / "probe_table.md").write_text(table)
    print(table)

def _probe_file(group):
    return [_probe_worker(c) for c in group]

def render_probe(rows, pool_sizes, dt, seed):
    L = [f"# T2 probe (i) — rung 1 (struct spelling) on a stratified sample; seed {seed}; {len(rows)} bodies; {dt:.0f} s wall", ""]
    L.append(f"Pool sizes (bodies × typed bases in the census): {pool_sizes}")
    L.append("")
    L.append("| stratum | bodies | IDENTICAL | DIFFERS | COMPILE-ERROR/CRASH | no site / other | sites rewritten | DIFFERS closed by S2 (casts kept) | of DIFFERS with levers: S+A IDENTICAL | levers-off alone IDENTICAL | residual kinds (DIFFERS) |")
    L.append("|---|---:|---:|---:|---:|---:|---:|---:|---:|---:|---|")
    tot = collections.Counter()
    for stratum in sorted({r["stratum"] for r in rows}):
        rs = [r for r in rows if r["stratum"] == stratum]
        v = collections.Counter(r["verdict"] for r in rs)
        rew = sum(r.get("rewritten", 0) or 0 for r in rs)
        diff_lev = [r for r in rs if r["verdict"] == "DIFFERS" and r.get("levers")]
        sa_ok = sum(1 for r in diff_lev if (r.get("sa") or {}).get("verdict") == "IDENTICAL")
        alone_ok = sum(1 for r in diff_lev if (r.get("sa") or {}).get("levers_off_alone") == "IDENTICAL")
        kinds = collections.Counter((r.get("residual") or {}).get("kind", "?") for r in rs if r["verdict"] == "DIFFERS")
        ce = v["COMPILE-ERROR"] + v["COMPILE-CRASH"]
        other = len(rs) - v["IDENTICAL"] - v["DIFFERS"] - ce
        s2 = [r for r in rs if r["verdict"] == "DIFFERS" and (r.get("s2") or {}).get("verdict") == "IDENTICAL"]
        s2k = sum(r["s2"]["kept"] for r in s2)
        L.append(f"| {stratum} | {len(rs)} | {v['IDENTICAL']} | {v['DIFFERS']} | {ce} | {other} | {rew} | {len(s2)}/{v['DIFFERS']} ({s2k} casts kept) | {sa_ok}/{len(diff_lev)} | {alone_ok}/{len(diff_lev)} | {dict(kinds)} |")
        tot.update(dict(n=len(rs), ident=v["IDENTICAL"], diff=v["DIFFERS"], ce=ce, rew=rew, dl=len(diff_lev), sa=sa_ok, alone=alone_ok, s2=len(s2), s2k=s2k))
    L.append(f"| **all** | {tot['n']} | {tot['ident']} | {tot['diff']} | {tot['ce']} | {tot['n'] - tot['ident'] - tot['diff'] - tot['ce']} | {tot['rew']} | {tot['s2']}/{tot['diff']} ({tot['s2k']} casts kept) | {tot['sa']}/{tot['dl']} | {tot['alone']}/{tot['dl']} | |")
    L.append("")
    judged = tot["ident"] + tot["diff"]
    if judged:
        L.append(f"**Rung 1 is byte-neutral on {tot['ident']}/{judged} judged bodies ({100.0 * tot['ident'] / judged:.1f} %), moving {tot['rew']} sites; "
                 f"rung S2 (a minimal set of sites kept as casts, delever's rung-B shape) closes {tot['s2']} of the {tot['diff']} DIFFERS bodies keeping {tot['s2k']} casts "
                 f"({tot['ident'] + tot['s2']}/{judged} = {100.0 * (tot['ident'] + tot['s2']) / max(1, judged):.1f} % of judged bodies byte-identical with members everywhere but {tot['s2k']} sites); "
                 f"of the {tot['dl']} DIFFERS bodies that carry marked levers, {tot['sa']} become IDENTICAL with the struct AND the levers off "
                 f"(the struct hypothesis), of which {tot['alone']} were already identical with the levers off alone (the struct did not decide those).**")
    errs = collections.Counter(r.get("err", "")[:70] for r in rows if r["verdict"] in ("COMPILE-ERROR", "COMPILE-CRASH", "TOOL-ERROR"))
    if errs:
        L.append("")
        L.append("Compile errors / tool errors (top): " + " · ".join(f"{k!r} ×{n}" for k, n in errs.most_common(8)))
    skips = collections.Counter()
    for r in rows:
        for k, n in (r.get("skips") or {}).items():
            skips[k] += n
    L.append(f"\nSites skipped by the rewrite (not converted; counted): {dict(skips)}")
    secs = [r.get("seconds", 0) for r in rows if r.get("seconds")]
    if secs:
        L.append(f"Seconds per body judgement: mean {sum(secs) / len(secs):.2f}, max {max(secs):.2f} (headers judge every includer).")
    L.append("")
    L.append("Rows: `.run/P37/probe/probe_rows.jsonl` (per body: tu, fn, base, type, rewritten, skips, verdict, residual, sa).")
    return "\n".join(L) + "\n"

# ----------------------------------------------------------------------------------------------------------------------
# (ii) the declaration probe: the in-scope declaration replaced by the definition's ANSI signature, per TU and per callee
# ----------------------------------------------------------------------------------------------------------------------
NARROW = re.compile(r"\b(s16|u16|s8|u8|short|char)\b")

def _decl_repair_text(raw, rows, real_ret=None):
    """Rewrite every lying extern of the given rows (same TU, same callee) to the definition's parameter list."""
    lines = raw.split("\n")
    changed = 0
    for r in rows:
        i = r["line"] - 1
        if i >= len(lines):
            continue
        pat = re.compile(r"\b" + re.escape(r["callee"]) + r"\s*\(([^;)]*)\)")
        new, n = pat.subn(lambda m: f"{r['callee']}({r['real_params']})", lines[i], count=1)
        if n:
            lines[i] = new
            changed += 1
    return "\n".join(lines), changed

def probe_decls(a):
    import argcheck
    defs = argcheck.definitions()
    rows = argcheck.scan(defs, only_needed_argpins=False)
    by_tu = collections.defaultdict(lambda: collections.defaultdict(list))
    for r in rows:
        by_tu[r["tu"]][r["callee"]].append(r)
    rng = random.Random(a.seed)
    # stratify TUs by kind
    kinds = collections.defaultdict(list)
    for tu in by_tu:
        k = "shared-header" if tu.startswith("src/shared/") else "main" if tu.count("/") == 1 else "md" if tu.startswith("src/md_") else "ov"
        kinds[k].append(tu)
    want = {"ov": 200, "main": 40, "md": 30, "shared-header": 30}
    if a.sample:
        scale = a.sample / sum(want.values())
        want = {k: max(1, int(round(v * scale))) for k, v in want.items()}
    sample = []
    for k, n in want.items():
        pool = kinds.get(k, [])
        rng.shuffle(pool)
        sample.extend((tu, k) for tu in pool[:n])
    recipes()
    work = [(tu, k, dict(by_tu[tu]), defs) for tu, k in sample]
    out = []
    t0 = time.time()
    with ProcessPoolExecutor(max_workers=a.jobs) as ex:
        for res in ex.map(_decl_worker, [w for w in work if not w[0].endswith(".h")]):
            out.extend(res)
    for w in work:
        if w[0].endswith(".h"):
            out.extend(_decl_worker(w))
    dt = time.time() - t0
    PROBE.mkdir(parents=True, exist_ok=True)
    with (PROBE / "decl_rows.jsonl").open("w") as fh:
        for r in out:
            fh.write(json.dumps(r) + "\n")
    print(render_decls(out, dt, a.seed, sum(len(v) for v in by_tu.values()), len(by_tu)))
    (PROBE / "decl_table.md").write_text(render_decls(out, dt, a.seed, sum(len(v) for v in by_tu.values()), len(by_tu)))

def _decl_worker(args):
    tu, kind, by_callee, defs = args
    out = []
    try:
        raw = (REPO / tu).read_text(errors="surrogateescape")
    except OSError:
        return out
    for callee, rows in by_callee.items():
        text, changed = _decl_repair_text(raw, rows)
        if not changed:
            out.append(dict(tu=tu, kind=kind, callee=callee, rows=len(rows), verdict="NO-EDIT"))
            continue
        real = defs.get(callee)
        v, dt, err, _ = judge_text(tu, text, "dc" + hashlib.sha1((tu + callee).encode()).hexdigest()[:6])
        cause = None
        if v != "IDENTICAL":
            if "too few arguments" in err or "too many arguments" in err:
                cause = "arity (the call passes a different count)"
            elif "conflicting types" in err:
                cause = "conflicting declaration elsewhere in the TU"
            elif v.startswith("COMPILE"):
                cause = "compile: " + err.split("\n")[0][-70:]
            elif NARROW.search(real[1] or ""):
                cause = "narrow parameter width (caller-side conversion)"
            else:
                cause = "other (bytes moved with no narrow width)"
        out.append(dict(tu=tu, kind=kind, callee=callee, rows=len(rows), declared_kinds=sorted({r["kind"] for r in rows}),
                        real_params=real[1] if real else None, verdict=v, cause=cause, err=err[:120], seconds=round(dt, 2)))
    return out

def render_decls(rows, dt, seed, n_rows_all, n_tus_all):
    L = [f"# T2 probe (ii) — the canonical prototype (the definition's ANSI signature) per TU × callee; seed {seed}; {len(rows)} judgements; {dt:.0f} s wall", "",
         f"Population: {n_rows_all} lying declarations in {n_tus_all} TUs (argcheck). Sample: per TU, every lying callee repaired ALONE (its declarations in that TU), judged on the object.", "",
         "| TU kind | judgements | IDENTICAL | DIFFERS | COMPILE-ERROR | no edit | causes (non-identical) |", "|---|---:|---:|---:|---:|---:|---|"]
    tot = collections.Counter()
    for kind in sorted({r["kind"] for r in rows}):
        rs_ = [r for r in rows if r["kind"] == kind]
        v = collections.Counter(r["verdict"] for r in rs_)
        causes = collections.Counter((r.get("cause") or "")[:45] for r in rs_ if r["verdict"] not in ("IDENTICAL", "NO-EDIT"))
        ce = sum(n for k, n in v.items() if k.startswith("COMPILE"))
        L.append(f"| {kind} | {len(rs_)} | {v['IDENTICAL']} | {v['DIFFERS']} | {ce} | {v['NO-EDIT']} | {dict(causes.most_common(4))} |")
        tot.update(dict(n=len(rs_), ident=v["IDENTICAL"], diff=v["DIFFERS"], ce=ce, noedit=v["NO-EDIT"]))
    L.append(f"| **all** | {tot['n']} | {tot['ident']} | {tot['diff']} | {tot['ce']} | {tot['noedit']} | |")
    judged = tot["ident"] + tot["diff"] + tot["ce"]
    if judged:
        L.append("")
        L.append(f"**The definition's signature is a free replacement for {tot['ident']}/{judged} judged (TU, callee) pairs ({100.0 * tot['ident'] / judged:.1f} %); "
                 f"{tot['diff']} move bytes, {tot['ce']} refuse to compile (arity contradictions and conflicting declarations).** Per callee, the non-free "
                 f"cases are the declaration solver's input (T3): the definition's width or return axis, or a byte-proven K&R call.")
    kr = [r for r in rows if r["verdict"] in ("DIFFERS",) and "K&R-empty" in (r.get("declared_kinds") or [])]
    narrow = [r for r in rows if r["verdict"] == "DIFFERS" and "narrow parameter" in (r.get("cause") or "")]
    L.append(f"\nOf the DIFFERS: {len(narrow)} have a narrow parameter in the definition (`s16/u16/s8/u8`: the caller now converts — the width rule); "
             f"{len(kr)} were `()` declarations.")
    L.append("\nRows: `.run/P37/probe/decl_rows.jsonl`.")
    return "\n".join(L) + "\n"

# ----------------------------------------------------------------------------------------------------------------------
# (iii) the definition fold: a TU's file-scope definition that duplicates a canonical type (same layout, tier 1/2) becomes a
#       typedef alias of the canonical name (or is deleted when it IS the canonical name) — judged on the object
# ----------------------------------------------------------------------------------------------------------------------
def probe_defs(a):
    import lever_census as lc
    aliases, dirs = sc.fleet_and_dirs()
    tu_aliases, headers, _ = lc.enumerate_files(aliases, dirs)
    canon = tc._walk_worker("src/shared/engine_types.h")
    cdefs = {}
    for d in canon["definitions"]:
        for n in d["names"] + ([d["tag"]] if d["tag"] else []):
            cdefs.setdefault(n, d)
    for al in canon["typedef_aliases"]:
        cdefs.setdefault(al["name"], dict(kind="alias", alias_of=al["alias_of"], alias_stars=al["alias_stars"], alias_dims=al["alias_dims"]))
    cres = tc.Resolver(dict(cdefs))
    canon_by_lhash = collections.defaultdict(list)
    for d in canon["definitions"]:
        if d["kind"] == "enum" or not d["fields"]:
            continue
        lay = cres.layout_of_fields(d["fields"], d["kind"], packed=("packed" in d["attrs"]))
        if lay:
            d["lhash"] = tc.layout_hash(lay)
            canon_by_lhash[d["lhash"]].append(d)
    def sig(d):
        return tuple(("*" if re.match(r"^(?:unk|f|field_?|pad|p|a|b|c|d|w|v|m|t|x|s|u|_|arr|buf|data|val|word|byte|half|tmp|r|q|n)?[0-9A-Fa-fx_]*$", f.get("name") or "") else f["name"]) for f in d["fields"])
    # candidate TUs: overlay TUs including the prelude with the most file-scope definitions
    cands = []
    for tu in sorted(tu_aliases):
        if not tu.startswith("src/ov_"):
            continue
        raw = (REPO / tu).read_text(errors="surrogateescape")
        if "engine_prelude.h" not in raw:
            continue
        n = len(re.findall(r"^(?:typedef\s+)?(?:struct|union)\b[^;]*\{", raw, re.M))
        if n:
            cands.append((n, tu))
    cands.sort(reverse=True)
    rng = random.Random(a.seed)
    top = [tu for _, tu in cands[:60]]
    rng.shuffle(top)
    sample = top[:20]
    rows = []
    for tu in sample:
        r = tc._walk_worker(tu)
        raw = (REPO / tu).read_text(errors="surrogateescape")
        scope = dict(cdefs)
        for d in r["definitions"]:
            for n in d["names"] + ([d["tag"]] if d["tag"] else []):
                scope.setdefault(n, d)
        res = tc.Resolver(scope)
        ls = dl.line_starts(raw)
        edits, kinds = [], collections.Counter()
        for d in r["definitions"]:
            if d["kind"] == "enum" or d["scope"] != "file" or not d["fields"]:
                continue
            lay = res.layout_of_fields(d["fields"], d["kind"], packed=("packed" in d["attrs"]))
            if not lay:
                kinds["unresolved"] += 1
                continue
            lh = tc.layout_hash(lay)
            cs = canon_by_lhash.get(lh, [])
            names = d["names"] + ([d["tag"]] if d["tag"] else [])
            same_name = [c for c in cs if set(c["names"] + ([c["tag"]] if c["tag"] else [])) & set(names)]
            if same_name:
                # the canonical definition IS visible under this name: the local copy is a redefinition the TU tolerates only because
                # cdecl/strip left it — delete it (R43: identical text or refuse)
                if any(c["text_hash"] == d["text_hash"] for c in same_name):
                    edits.append((ls[d["line"] - 1], ls[d["end"]], "")); kinds["deleted-same"] += 1
                else:
                    kinds["same-name-different-text"] += 1
                continue
            tier = [c for c in cs if sig(c) == sig(d) or all(x == "*" for x in sig(d) + sig(c))]
            if not tier:
                kinds["no-canonical-twin"] += 1 if not cs else 0
                kinds["layout-twin-kept-apart"] += 1 if cs else 0
                continue
            c = tier[0]
            cname = c["names"][0] if c["names"] else f"struct {c['tag']}"
            if not d["typedef"] and d["tag"] and not d["names"]:
                kinds["tag-only-local"] += 1
                continue
            alias_lines = "".join(f"typedef {cname} {n};\n" for n in d["names"])
            edits.append((ls[d["line"] - 1], ls[d["end"]], alias_lines)); kinds["aliased"] += 1
        if not edits:
            rows.append(dict(tu=tu, folds=0, kinds=dict(kinds), verdict="NO-EDIT"))
            continue
        out, last = [], 0
        for (a0, b0, rep) in sorted(edits):
            out.append(raw[last:a0]); out.append(rep); last = b0
        out.append(raw[last:])
        text = "".join(out)
        v, dt, err, _ = judge_text(tu, text, "df" + hashlib.sha1(tu.encode()).hexdigest()[:6])
        rows.append(dict(tu=tu, folds=len(edits), kinds=dict(kinds), verdict=v, err=err[:160]))
        print(f"{v:14s} {len(edits):3d} folds {dict(kinds)} {tu} {err[:80]}")
    PROBE.mkdir(parents=True, exist_ok=True)
    (PROBE / "defs_rows.jsonl").write_text("".join(json.dumps(r) + "\n" for r in rows))
    v = collections.Counter(r["verdict"] for r in rows)
    folds = sum(r["folds"] for r in rows)
    print(f"restruct --probe-defs: {len(rows)} TUs, {folds} definitions folded onto the canonical header: {dict(v)}")

# ----------------------------------------------------------------------------------------------------------------------
# (iv) the layout engine audited against cc1
# ----------------------------------------------------------------------------------------------------------------------
def audit_layouts(a):
    """For every definition the census parsed: a probe TU asserting sizeof and every top-level named field's offset with the
    negative-array-size idiom, compiled through the pinned cc1 (cdecl's oracle). 0 rejections = the engine agrees with the compiler."""
    import cdecl
    files = {}
    defs_all = []
    aliases, dirs = sc.fleet_and_dirs()
    import lever_census as lc
    tu_aliases, headers, _ = lc.enumerate_files(aliases, dirs)
    todo = sorted(tu_aliases) + list(headers) + sorted(p.relative_to(REPO).as_posix() for p in (REPO / "include").glob("*.h"))
    with ProcessPoolExecutor(max_workers=a.jobs) as ex:
        for r in ex.map(tc._walk_worker, todo, chunksize=8):
            files[r["rel"]] = r
    # the census's resolvers, per file (its own definitions first, then the canonical header)
    global_defs = {}
    for r in files.values():
        for d in r["definitions"]:
            if d["file"].startswith("include/") or d["is_canon"]:
                for n in d["names"] + ([d["tag"]] if d["tag"] else []):
                    global_defs.setdefault(n, d)
        for al in r["typedef_aliases"]:
            if al["file"].startswith("include/") or al["file"] in tc.CANON_HEADERS:
                global_defs.setdefault(al["name"], dict(kind="alias", alias_of=al["alias_of"], alias_stars=al["alias_stars"], alias_dims=al["alias_dims"]))
    probes, n_defs, n_fields, unresolved = [], 0, 0, 0
    for rel, r in files.items():
        scope = dict(global_defs)
        for d in r["definitions"]:
            for n in d["names"] + ([d["tag"]] if d["tag"] else []):
                scope.setdefault(n, d)
        for al in r["typedef_aliases"]:
            scope.setdefault(al["name"], dict(kind="alias", alias_of=al["alias_of"], alias_stars=al["alias_stars"], alias_dims=al["alias_dims"]))
        res = tc.Resolver(scope)
        for d in r["definitions"]:
            if d["kind"] == "enum" or not d["fields"] or d["scope"] != "file":
                continue
            lay = res.layout_of_fields(d["fields"], d["kind"], packed=("packed" in d["attrs"]))
            if lay is None:
                unresolved += 1
                continue
            n_defs += 1
            offs = field_offsets(res, d)
            if not d["names"] and not d["tag"]:
                continue            # an anonymous, tagless definition (a member's inline type) cannot be named by a probe
            spans = [(x["line"], x["end"]) for x in r["definitions"] if x["scope"] == "file" and x["line"] <= d["line"]]
            tname = d["names"][0] if d["names"] else (f"struct {d['tag']}" if d["kind"] == "struct" else f"union {d['tag']}")
            fnspans = [(f["line"], f["fn_end"]) for f in r["fndefs"] if f.get("fn_end")]
            probes.append((rel, d["line"], tname, lay[0], offs, spans, fnspans))
            n_fields += len(offs)
    # compile in batches: each probe is its own tiny TU (a definition may depend on its file's other types: include the file's
    # own file-scope definitions verbatim before it — the masked text, in order — plus its scalar typedefs and common.h)
    rej, checked = [], 0
    with ProcessPoolExecutor(max_workers=a.jobs) as ex:
        for res_ in ex.map(_audit_one, probes, chunksize=16):
            checked += 1
            if not res_[4]:
                rej.append(res_)
    PROBE.mkdir(parents=True, exist_ok=True)
    (PROBE / "layout_audit.json").write_text(json.dumps(dict(checked=checked, definitions=n_defs, fields=n_fields, unresolved=unresolved, rejected=rej[:200]), indent=1))
    print(f"restruct --audit-layouts: {checked} file-scope definitions ({n_fields} named fields) asserted against cc1; rejected {len(rej)}; "
          f"unresolved layouts {unresolved}")
    for r in rej[:12]:
        print("  REJECT", r[0], r[1], r[2], r[3])
    return 0 if not rej else 1

def cc1_accepts(body):
    """cdecl._cc1_accepts with a scratch path keyed by the body (R111: cdecl's fixed `cc1probe.c` would collide across workers)."""
    import cdecl
    import tempfile
    d = PROBE / "cc1"
    d.mkdir(parents=True, exist_ok=True)
    fd, cpath = tempfile.mkstemp(dir=str(d), prefix="p", suffix=".c")      # unique per call (R111): identical bodies from the
    os.close(fd)                                                           # cross-address copies raced on a shared hash name
    c = pathlib.Path(cpath); i = pathlib.Path(cpath[:-2] + ".i")
    c.write_text(body, errors="surrogateescape")
    p = subprocess.run(cdecl.CPP + ["-Isrc", str(c)], capture_output=True, text=True, cwd=REPO)
    if p.returncode:
        c.unlink(missing_ok=True)
        return None
    i.write_text(p.stdout)
    r = subprocess.run([cdecl.CC1] + cdecl.CC1FLAGS + [str(i), "-o", "/dev/null"], capture_output=True, text=True, cwd=REPO)
    ok = not (r.returncode or cdecl._ERR.search(r.stderr or ""))
    if ok:
        c.unlink(missing_ok=True); i.unlink(missing_ok=True)
    else:
        c.with_suffix(".err").write_text(r.stderr[-2000:])
    return ok

def _audit_one(args):
    rel, dline, tname, size, offs, spans, fnspans = args
    raw = (REPO / rel).read_text(errors="surrogateescape")
    masked = tc._blank_dead_guards(sc.mask_text(raw), raw, rel)
    ls = dl.line_starts(masked)
    upto = ls[spans[-1][1]] if spans else len(masked)          # the target definition's end (the last span is the target)
    # the TU's real environment IN ORDER: #include lines (shared BODY headers dropped — code, not types), file-scope typedef statements
    # and struct/union definitions, each at its own position, up to the target; function bodies and externs left out
    items = []
    for m in sc.INCLUDE_LINE.finditer(masked):
        if m.start() >= upto:
            break
        target = os.path.normpath(os.path.join(os.path.dirname(rel), m.group(1)))
        if re.search(r"/func_[0-9A-Fa-f]{8}", target):
            continue
        inc = os.path.relpath(REPO / target, REPO / "include") if (REPO / target).exists() else m.group(1)
        items.append((m.start(), f'#include "{inc}"'))
    def_spans = [(ls[a0 - 1], ls[b0]) for (a0, b0) in spans]
    for (a0, b0) in def_spans:
        txt = masked[a0:b0].rstrip()
        items.append((a0, txt if txt.endswith(";") else txt + ";"))
    fn_pos = [(ls[a0 - 1], ls[b0]) for (a0, b0) in fnspans if a0 - 1 < len(ls) and b0 < len(ls)]
    for m in re.finditer(r"(?<![\w.])typedef\s+[^;{}]+?;", masked):
        if m.start() >= upto:
            break
        if any(a0 <= m.start() < b0 for (a0, b0) in def_spans):
            continue                    # inside a definition's span already emitted
        if any(a0 <= m.start() < b0 for (a0, b0) in fn_pos):
            continue                    # a block-scope typedef inside a function body: not the file scope's
        items.append((m.start(), masked[m.start():m.end()]))
    items.sort()
    body = "\n".join(t for _, t in items) + "\n"
    if '#include "common.h"' not in body:
        body = '#include "common.h"\n' + body
    body += f"char p37_size[(sizeof({tname}) == {size}) ? 1 : -1];\n"
    for (fname, off) in offs:
        body += f"char p37_{fname}[((int)&((({tname} *)0)->{fname}) == {off}) ? 1 : -1];\n"
    ok = cc1_accepts(body)
    return (rel, dline, tname, size, ok)

def field_offsets(res, d):
    """Top-level NAMED, non-bitfield fields with their byte offsets under the engine's rules — the audit's assertions."""
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

# ----------------------------------------------------------------------------------------------------------------------
# (vi) the fan-out cost of one canonical-header edit
# ----------------------------------------------------------------------------------------------------------------------
def fanout_cost(a):
    hdr = "src/shared/engine_types.h"
    _, by_src, inc = recipes()
    tus = inc.get(hdr, [])
    recs = [r for t in tus for r in by_src.get(t, [])]
    path = REPO / hdr
    raw = path.read_text(errors="surrogateescape")
    st = path.stat()
    text = raw.replace("#endif", "typedef struct { s32 p37_probe_unused; } P37_FANOUT_PROBE;\n#endif", 1) if raw.rstrip().endswith("#endif") else raw + "\ntypedef struct { s32 p37_probe_unused; } P37_FANOUT_PROBE;\n"
    t0 = time.time()
    verdicts = collections.Counter()
    try:
        path.write_text(text, errors="surrogateescape")
        def one(r):
            base = oracle.baseline_bytes(r["obj"])
            data, dt, err = oracle.compile_obj(r, None, tag="fo" + hashlib.sha1(r["obj"].encode()).hexdigest()[:6])
            if data is None:
                return "COMPILE-ERROR", dt
            return ("IDENTICAL" if data == base else "DIFFERS"), dt
        from concurrent.futures import ThreadPoolExecutor
        cpu = 0.0
        with ThreadPoolExecutor(max_workers=a.jobs) as ex:
            for v, dt in ex.map(one, recs):
                verdicts[v] += 1
                cpu += dt
    finally:
        dl.restore_file(path, raw, st)
    wall = time.time() - t0
    print(f"restruct --fanout-cost: {hdr} reaches {len(tus)} TUs / {len(recs)} objects; one harmless typedef added: {dict(verdicts)}; "
          f"wall {wall:.0f} s at -j{a.jobs} (cpu {cpu:.0f} s, {cpu / max(1, len(recs)):.3f} s/object)")

# ----------------------------------------------------------------------------------------------------------------------
def main():
    ap = argparse.ArgumentParser(description=__doc__.split("\n")[0])
    ap.add_argument("--try", dest="try_", nargs=2, metavar=("TU", "FN"))
    ap.add_argument("--base", help="bclass:name (default: the body's largest typed base)")
    ap.add_argument("--probe", action="store_true")
    ap.add_argument("--sample", type=int, default=0)
    ap.add_argument("--seed", type=int, default=37)
    ap.add_argument("--audit-layouts", action="store_true")
    ap.add_argument("--fanout-cost", action="store_true")
    ap.add_argument("--rerun-differs", action="store_true", help="re-run only the DIFFERS rows of the last probe (with S2) and re-render")
    ap.add_argument("--probe-decls", action="store_true", help="probe (ii): the definition's signature as the in-scope declaration, per TU x callee")
    ap.add_argument("--probe-defs", action="store_true", help="probe (iii): fold a TU's duplicate file-scope definitions onto the canonical header")
    ap.add_argument("-j", "--jobs", type=int, default=16)
    a = ap.parse_args()
    if a.try_:
        row = try_body(a.try_[0], a.try_[1], base_key=a.base)
        print(json.dumps(row, indent=1))
        return
    if a.probe:
        run_probe(a)
        return
    if a.rerun_differs:
        rows = [json.loads(l) for l in (PROBE / "probe_rows.jsonl").read_text().splitlines() if l.strip()]
        out = []
        for r in rows:
            if r["verdict"] == "DIFFERS":
                r2 = _probe_worker((r["tu"], r["fn"], r["base"], r["type"], r["stratum"], r.get("base_sites", 0), r.get("lever_body", False)))
                out.append(r2)
            else:
                out.append(r)
        with (PROBE / "probe_rows.jsonl").open("w") as fh:
            for r in out:
                fh.write(json.dumps(r) + "\n")
        table = render_probe(out, {}, 0, a.seed)
        (PROBE / "probe_table.md").write_text(table)
        print(table)
        return
    if a.probe_decls:
        probe_decls(a)
        return
    if a.probe_defs:
        probe_defs(a)
        return
    if a.audit_layouts:
        sys.exit(audit_layouts(a))
    if a.fanout_cost:
        fanout_cost(a)
        return
    ap.print_help()

if __name__ == "__main__":
    main()
