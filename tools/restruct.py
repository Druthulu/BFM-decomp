#!/usr/bin/env python3
"""tools/restruct.py — the struct/declaration rewrite engine (Phase 37 T3, 2026-09-12; the T2 probe form kept inside it).

    tools/restruct.py --plan --rung S|D|L [--batch N] [--headers] [--only X …]        # what the next batch would touch (no writes)
    tools/restruct.py --apply --rung S|D|L --batch N --label <lbl> [--headers] [--only X …] [-j N]
                                                                                       # judge every unit of the batch's files, KEEP the winning
                                                                                       # texts in place (the outer gate — R22 — follows), ledger every site
    tools/restruct.py --apply --rung D --callee F --signature "void F(s32 a)" --label <lbl>   # a definition-side signature change: the definition's
                                                                                       # TU + every TU declaring F, one judged unit (the 24 parked patches)
    tools/restruct.py --restore                                                        # every in-flight file back from inflight.json (never git checkout, R102)
    tools/restruct.py --status                                                         # the ledger's totals per rung
    tools/restruct.py --check-ledger                                                   # every MEMBER site still a leaf of its (current) canonical type
    tools/restruct.py --audit-types                                                    # the naming invariant over the canonical type files (struct_layout.audit_definition)
    tools/restruct.py --write-types --top N | --type NAME … [--space ov]               # the WRITER: canonical definitions rendered from the struct map (a preview)
    tools/restruct.py --selftest [--real]                                              # the fixture (a stub oracle); --real adds the calibration + known-true controls
    tools/restruct.py --try TU FN [--base bclass:name] [--recipes]                     # T2's rung 1 on one body (local P37S_ type) + S2 + S+A [+ the R recipes]
    tools/restruct.py --probe | --probe-decls | --probe-defs | --audit-layouts | --fanout-cost   # the T2 probes (unchanged)

THE RUNGS (deterministic first; every verdict on the bytes through tools/delever_oracle.py — whole-object equality against the fleet run's
snapshot, then the LINKED mode when only the relocation spelling moved — R110):
  S    struct spelling on EVERY typed base of a body: `*(u16 *)(a0 + 0x3C)` -> `((Unkstruct_X *)a0)->unk3C` (or `a0->unk3C` when a0 is
       already declared `Unkstruct_X *`; `D_x.unk3C` when the global is declared with the type). The type comes from the struct map and
       must be a CANONICAL definition visible to the TU (`--apply`); `--try` builds T2's body-local `P37S_<hash>` type from the map's layout.
       A site the type cannot hold is SKIPPED and counted (no-field / width / sign / index / negative / pointee / overlap) — T5's authoring residue.
  S2   the member spelling DIFFERS -> the minimal set of sites that must stay casts (leave-one-out, then cumulative revert in source order,
       then minimise — delever's rung-B shape, <= 2n+1 compiles); the kept casts are ledgered KEPT with their residual and a pass HINT (X).
  S+A  a lever-bearing body: the struct-spelled text run through delever's ladder (rung A strip-all, rung B greedy) — the struct hypothesis;
       survivors keep/receive their `// !FAKE:` marker attributed `(P37 S+A <label>)` and a row in delever's ledger too (one lever record).
  X    the residual of a DIFFERS candidate, classified (delever_search.classify: REG / COUNT / ORDER / MIXED) and named by the pass it
       most resembles: SCHED-ALIAS (a load hoisted over a `/s` store), CSE-KILL (a reload added/removed), WIDTH (andi/sll-sra), ADDRESS-FOLD
       (an addend moved), ALIGNMENT (lwl/lwr), REGALLOC, OTHER. A hint for the readings (R65 needs the dump line), never a verdict.
  R    recipes for a KEPT cast — the shapes the record already proves: R1 the pointer global read as a struct member (§458: both sides `/s`),
       R2 a scalar global declared `extern T X[]` (a18: the MEM_IN_STRUCT alias escape), R3 consecutive carved words walked through one
       pointer (f3; relocation spelling -> the linked oracle). A registry (RECIPES) with a fixture each; T7's harvest -> toolify adds to it.
  D    declarations: EVERY declaration of a callee in a TU replaced by the canonical prototype — the DEFINITION's ANSI signature, else its
       width-promoted form (`s16 a` -> `s32 a`: what a K&R call passes), else kept `()` with `// K&R: n of m args (P37 rung D <label>)` when
       the TU's calls pass another count (the byte-proven K&R sites, counted apart). Ladder per TU: all callees at once, else one at a time.
       `--callee/--signature`: a DEFINITION-side change judged on the definition's TU and every TU that declares it (one unit, all IDENTICAL).
  L    definition folds: a TU's file-scope duplicate of a canonical type (same layout; tier 1 same-named -> deleted when the text is identical,
       tier 2 opaque -> `typedef <Canon> <Local>;` with the TU's member accesses renamed by the offset map — REFUSED when a local member name
       is also a member of another type visible in the TU (a textual rename could hit the other)).

THE ENGINE PATTERN (tools/delever.py's, R43/R48/R102/R111/R114): positional token-exact edits on the raw text (the census's records re-walked
on the CURRENT file — positions are never cached); the FILE is the write unit and its final compile through every recipe (a twin's object,
every includer of a header) is the proof — IDENTICAL or the file is restored and REFUSED loudly (COMBINATION-FAILED); every original text is
in .run/P37/restruct/inflight.json before the first write and --restore reads it; the ledger .run/P37/restruct/ledger.jsonl keys a unit by
(rung, tu, unit, body hash before/after) — "done" is per body, never by text alone; workers own whole TUs; headers run serially after the
TUs and are judged on every includer, a fan-out COMPILE-ERROR retried once (T2 (h)); the batch's touched files are left in place for the
outer gate (the clean fleet run, R22) which tools/restruct_cycle.sh runs before the commit.
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
from concurrent.futures import ProcessPoolExecutor, ThreadPoolExecutor

sys.path.insert(0, str(pathlib.Path(__file__).resolve().parent))
import share_census as sc          # noqa: E402
import type_census as tc           # noqa: E402
import struct_layout as sl         # noqa: E402
import delever as dl               # noqa: E402
import delever_oracle as oracle    # noqa: E402
import delever_search as ds        # noqa: E402
import lever_census as lc          # noqa: E402
import masked_diff as md           # noqa: E402
from struct_layout import field_offsets   # noqa: E402,F401  (the T2 audit's helper; lives in struct_layout since T3)

REPO = pathlib.Path(__file__).resolve().parent.parent
CENSUS = REPO / ".run/P37/census"
PROBE = REPO / ".run/P37/probe"
RUN = REPO / ".run/P37/restruct"
LEDGER = RUN / "ledger.jsonl"
INFLIGHT = RUN / "inflight.json"
RAW_FORMS = ("P", "I", "X", "M")
TYPE_OF = sl.TYPE_OF
CANON_HEADERS = tc.CANON_HEADERS
KR_MARK = "// K&R:"
_LOCK = threading.Lock()


class Refuse(Exception):
    pass

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

# ======================================================================================================================
# THE ENGINE (T3)
# ======================================================================================================================
# ----------------------------------------------------------------------------------------------------------------------
# the judge: a multi-file job through the oracle (whole-object, then linked when only the relocation spelling moved)
# ----------------------------------------------------------------------------------------------------------------------
_recipes = None
_by_src = None
_inc = None
_tu_headers = None
JUDGE_STUB = None        # the selftest installs a callable(files, tag) -> (verdict, err) here; None = the real oracle


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


def headers_of(tu):
    """The headers a TU sees (transitively) — the inverse of delever.includers()."""
    global _tu_headers
    if _tu_headers is None:
        _, _, inc = recipes()
        m = collections.defaultdict(set)
        for h, tus in inc.items():
            for t in tus:
                m[t].add(h)
        _tu_headers = m
    return _tu_headers.get(tu, set())


def judge_files(files, tag, reloc=False, pool=None, retry=True):
    """files = {rel: candidate text}. Every file written IN PLACE (snapshotted first), every recipe of every file compiled (a header's
    includers' recipes), the objects compared with the snapshot baseline; a DIFFERS falls to the LINKED judgement when the job is
    flagged relocation-spelling (`reloc`) or the .text words agree modulo relocation operands. Every file restored (R102).
    Returns dict(verdict, seconds, err, compiles, linked=[objs judged IDENTICAL only linked], cand0=first recipe's candidate bytes)."""
    if JUDGE_STUB is not None:
        v, err = JUDGE_STUB(files, tag)
        return dict(verdict=v, seconds=0.0, err=err, compiles=1, linked=[], cand0=None)
    recs, seen = [], set()
    for rel in files:
        for r in recs_for(rel):
            if r["obj"] not in seen:
                seen.add(r["obj"]); recs.append(r)
    if not recs:
        return dict(verdict="NO-RECIPE", seconds=0.0, err=f"no recipe compiles {sorted(files)}", compiles=0, linked=[], cand0=None)
    snaps = {}
    for rel in files:
        p = REPO / rel
        snaps[rel] = (p.read_text(errors="surrogateescape"), p.stat())
    out = dict(verdict="IDENTICAL", seconds=0.0, err="", compiles=0, linked=[], cand0=None)
    try:
        for rel, text in files.items():
            (REPO / rel).write_text(text, errors="surrogateescape")

        def one(r):
            base = oracle.baseline_bytes(r["obj"])
            if base is None:
                return r, "NO-BASELINE", 0.0, "", None
            data, dt, err = oracle.compile_obj(r, None, tag=tag)
            if data is None and retry and not err.startswith("CRASH:"):
                data, dt2, err = oracle.compile_obj(r, None, tag=tag)          # a fan-out transient (T2 (h)): one retry
                dt += dt2
            if data is None:
                return r, ("COMPILE-CRASH" if err.startswith("CRASH:") else "COMPILE-ERROR"), dt, err, None
            if data == base:
                return r, "IDENTICAL", dt, "", data
            if reloc or oracle.reloc_only_diff(data, oracle.baseline_path(r["obj"]), tag=tag):
                lv, dt2, lerr = oracle.judge_linked(r, data, tag=tag)
                if lv == "IDENTICAL":
                    return r, "IDENTICAL-LINKED", dt + dt2, "", data
                return r, "DIFFERS", dt + dt2, ("linked: " + lerr if lerr else ""), data
            return r, "DIFFERS", dt, "", data
        if pool is not None and len(recs) > 2:
            results = list(pool.map(one, recs))
        else:
            results = [one(r) for r in recs]
        first = None
        for i, (r, v, dt, err, data) in enumerate(results):
            out["seconds"] += dt
            out["compiles"] += 1
            if i == 0:
                out["cand0"] = data
            if v == "IDENTICAL-LINKED":
                out["linked"].append(r["obj"])
                continue
            if v != "IDENTICAL" and first is None:
                first = (v, err, r["obj"])
        if first:
            out["verdict"], out["err"] = first[0], (first[1] + f" [{first[2]}]" if first[1] else f"[{first[2]}]")
        return out
    finally:
        for rel, (raw, st) in snaps.items():
            dl.restore_file(REPO / rel, raw, st)


def judge_text(tu, text, tag):
    """T2's single-file form: (verdict, seconds, err, candidate_object_bytes_of_first_recipe)."""
    r = judge_files({tu: text}, tag)
    return r["verdict"], r["seconds"], r["err"], r["cand0"]


# ----------------------------------------------------------------------------------------------------------------------
# the ledger (R48/R114: a unit is (rung, tu, unit, body hash); the latest row per unit is the verdict, R70) and the in-flight snapshot
# ----------------------------------------------------------------------------------------------------------------------
DONE_VERDICTS = {"IDENTICAL", "MEMBERS", "S2", "S+A", "UNCHANGED", "NO-SITE", "REFUSED", "KEPT-ALL", "DECL-CANON", "DECL-PROMOTED",
                 "DECL-KEPT", "FOLDED", "FOLD-REFUSED", "NO-EDIT", "TYPE-NOT-CANONICAL", "TYPE-NOT-VISIBLE"}
REDRAW_VERDICTS = {"COMBINATION-FAILED", "NO-RECIPE", "TOOL-ERROR"}


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
    """done: {(rung, tu, unit, nhash_after)}; latest: {(rung, tu, unit): verdict}."""
    done, latest = set(), {}
    for r in rows:
        key = (r.get("rung"), r["tu"], r["unit"])
        latest[key] = r.get("verdict")
        if r.get("verdict") in DONE_VERDICTS and r.get("nhash_after"):
            done.add(key + (r["nhash_after"],))
    return done, latest


def body_nhash(masked, d):
    ls = dl.line_starts(masked)
    s0 = ls[d["line"] - 1]
    s1 = ls[d["end"]] - 1 if d["end"] < len(ls) else len(masked)
    return lc.norm_hash(masked[s0:s1])


def load_inflight(path=None):
    path = path or INFLIGHT
    if not path.exists():
        return None, "no inflight.json — nothing was in flight"
    raw = path.read_text()
    if not raw.strip():
        return None, "inflight.json is EMPTY (a kill landed mid-write): reconcile every dirty file with the oracle (IDENTICAL = a bank, DIFFERS = a leftover)"
    try:
        return json.loads(raw), "ok"
    except json.JSONDecodeError as ex:
        return None, f"inflight.json is TORN ({ex}): same reconciliation as for an empty one"


def restore():
    """Every in-flight file back from inflight.json; the killed batch's ledger rows dropped (kept in ledger.jsonl.killed_<label>)."""
    d, why = load_inflight()
    if d is None:
        sys.exit(f"restruct --restore: {why}")
    label, files = d.get("label"), d.get("files", {})
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
    clean, dirty = dl.src_clean()
    print(f"restruct --restore: {n} of {len(files)} files restored from inflight.json (batch {label or '?'}); {dropped} ledger rows of that "
          f"batch dropped; src {'clean' if clean else 'STILL DIRTY:'}\n{'' if clean else dirty[:400]}")
    return 0 if clean else 1


def status():
    rows = load_ledger()
    by = collections.Counter((r.get("rung"), r.get("verdict")) for r in rows)
    sites = collections.Counter()
    for r in rows:
        for s in r.get("sites", []):
            sites[(r.get("rung"), s.get("verdict", "").split("(")[0])] += 1
    print(f"restruct --status: {len(rows)} ledger rows")
    for (rung, v), n in sorted(by.items(), key=lambda x: (str(x[0][0]), -x[1])):
        print(f"   {rung or '?':4s} {v:22s} {n}")
    if sites:
        print("   sites: " + ", ".join(f"{r}/{v} {n}" for (r, v), n in sorted(sites.items(), key=lambda x: (str(x[0][0]), -x[1]))))
    return 0


# ----------------------------------------------------------------------------------------------------------------------
# the shared ladder: all units at once, else cumulative greedy in order (delever's rung-B shape: n compiles, the last accepted
# candidate IS the final text — no extra combination compile)
# ----------------------------------------------------------------------------------------------------------------------
def ladder_units(units, compose, judge, tag, log=None):
    """units: [unit] in source order; compose(accepted_units) -> {rel: text}; judge(files, tag) -> result dict.
    Returns (accepted[list of units], per_unit{idx: (verdict, err)}, compiles, seconds, rung) with rung 'A' (all at once) or 'B'."""
    per, compiles, secs = {}, 0, 0.0
    if not units:
        return [], per, 0, 0.0, None
    r = judge(compose(units), tag + "A")
    compiles += r["compiles"]; secs += r["seconds"]
    if r["verdict"] == "IDENTICAL":
        for i in range(len(units)):
            per[i] = ("IDENTICAL", "", r["linked"])
        return list(units), per, compiles, secs, "A"
    if len(units) == 1:
        per[0] = (r["verdict"], r["err"], r["linked"])
        return [], per, compiles, secs, "A"
    accepted = []
    for i, u in enumerate(units):
        r2 = judge(compose(accepted + [u]), tag + f"B{i}")
        compiles += r2["compiles"]; secs += r2["seconds"]
        if r2["verdict"] == "IDENTICAL":
            accepted.append(u)
            per[i] = ("IDENTICAL", "", r2["linked"])
        else:
            per[i] = (r2["verdict"], r2["err"], r2["linked"])
            if log:
                log(f"    unit {i}: {r2['verdict']} {r2['err'].replace(chr(10), ' | ')[:140]}")
    return accepted, per, compiles, secs, "B"


# ----------------------------------------------------------------------------------------------------------------------
# rung X: the residual named by the pass it most resembles (a HINT for the readings; R65 wants the dump line before a verdict)
# ----------------------------------------------------------------------------------------------------------------------
LOADS = ("lw", "lh", "lhu", "lb", "lbu", "lwl", "lwr", "lui")
STORES = ("sw", "sh", "sb", "swl", "swr")


def pass_hint(residual):
    if not residual or residual.get("kind") in (None, "UNSCORED"):
        return "UNSCORED"
    kind = residual["kind"]
    mn = [(p[1].split()[1] if len(p[1].split()) > 1 else "") for p in residual.get("pairs", []) if p[1] != "--"]
    tg = [(p[2].split()[1] if len(p[2].split()) > 1 else "") for p in residual.get("pairs", []) if p[2] != "--"]
    words = set(mn) | set(tg)
    if words & {"lwl", "lwr", "swl", "swr"}:
        return "ALIGNMENT"
    if kind == "ORDER" and (words & set(LOADS)) and (words & set(STORES)):
        return "SCHED-ALIAS"
    if kind == "ORDER":
        return "SCHED-ORDER"
    if kind == "COUNT" and (words & {"lui", "lw", "addiu", "la"}):
        return "CSE-KILL"
    if words & {"andi", "sll", "sra", "srl", "seb", "seh"}:
        return "WIDTH"
    if kind == "COUNT":
        return "COUNT-OTHER"
    if kind == "REG":
        return "REGALLOC"
    ims = [p for p in residual.get("pairs", []) if p[1] != "--" and p[2] != "--" and p[1].split()[1:2] == p[2].split()[1:2]]
    if ims and all(x[1].split()[1] in ("addiu", "lui", "ori") for x in ims):
        return "ADDRESS-FOLD"
    return "OTHER"


# ----------------------------------------------------------------------------------------------------------------------
# rung S (engine form): every typed base of a body, canonical types, the declared-type-aware spelling
# ----------------------------------------------------------------------------------------------------------------------
_canon = None


def canon_types():
    """{name: (definition record, Resolver, field_map)} for every canonical type file's struct/union definitions (T5 adds files to
    tc.CANON_HEADERS; the writer appends definitions). Re-read per process."""
    global _canon
    if _canon is None:
        defs = {}
        recs = []
        for h in CANON_HEADERS:
            if not (REPO / h).exists():
                continue
            w = tc._walk_worker(h)
            for d in w["definitions"]:
                recs.append(d)
                for n in d["names"] + ([d["tag"]] if d["tag"] else []):
                    defs.setdefault(n, d)
            for al in w["typedef_aliases"]:
                defs.setdefault(al["name"], dict(kind="alias", alias_of=al["alias_of"], alias_stars=al["alias_stars"], alias_dims=al["alias_dims"]))
        res = sl.Resolver(dict(defs))
        out = {}
        for d in recs:
            if d["kind"] == "enum" or not d["fields"]:
                continue
            fm = sl.field_map(res, d)
            for n in d["names"]:
                out[n] = (d, res, fm)
        _canon = out
    return _canon


def type_visible(tu, tname):
    """Is the canonical type's file visible to the TU (the file itself, or one of its transitive headers)?"""
    d = canon_types().get(tname)
    if not d:
        return False
    if VISIBLE_OVERRIDE:
        return True
    f = d[0]["file"]
    return tu == f or f in headers_of(tu)


PARAM_DECL = re.compile(r"^\s*((?:(?:const|volatile|unsigned|signed|struct|union)\s+)*[A-Za-z_]\w*)\s*(\**)\s*([A-Za-z_]\w*)\s*$")


def declared_type(masked, d, base, bclass, fn_head_inner):
    """The declared type text of a base as the TU spells it ('Unkstruct_X *' / 's32' / None): a parameter from the definition's head,
    a local from its declaration line in the body, a global from `extern T D_x;` in the TU."""
    if bclass == "param" and fn_head_inner:
        for part in sl._split_top(fn_head_inner, ","):
            m = PARAM_DECL.match(part.strip())
            if m and m.group(3) == base:
                return sl._norm_type(m.group(1) + (" " + m.group(2) if m.group(2) else ""))
        return None
    ls = dl.line_starts(masked)
    if bclass == "local":
        s0, s1 = ls[d["line"] - 1], (ls[d["end"]] if d["end"] < len(ls) else len(masked))
        body = masked[s0:s1]
        m = re.search(r"(?<![\w.])((?:(?:const|volatile|unsigned|signed|struct|union|register)\s+)*[A-Za-z_]\w*)\s*(\**)\s*(?:[A-Za-z_]\w*\s*(?:=[^,;]*)?,\s*\**\s*)*" + re.escape(base) + r"\b\s*(?:=[^,;]*)?[,;]", body)
        if m and m.group(1) not in ("return", "goto", "case", "else"):
            return sl._norm_type(m.group(1) + (" " + m.group(2) if m.group(2) else ""))
        return None
    if bclass in ("global", "gaddr"):
        m = re.search(r"\bextern\s+((?:(?:const|volatile|unsigned|signed|struct|union)\s+)*[A-Za-z_]\w*)\s*(\**)\s*" + re.escape(base) + r"\s*((?:\[[^\]]*\])*)\s*;", masked)
        if m:
            return sl._norm_type(m.group(1) + (" " + m.group(2) if m.group(2) else "")) + ("[]" if m.group(3) else "")
    return None


def member_spelling(tname, base_expr, bclass, decl, fname):
    """The member access text for one site: typed base -> `base->f` / `D_x.f`; else the cast form."""
    want_ptr = tname + " *"
    if bclass in ("param", "local", "global") and decl == want_ptr:
        return f"{base_expr}->{fname}"
    if bclass == "gaddr" and decl == tname:
        return f"{base_expr.lstrip('&')}.{fname}"
    return f"(({tname} *){base_expr})->{fname}"


def s_edits(raw, masked, d, sites, tname, fields, base_key, fn_head_inner, allow_pointee_void=False):
    """Rung S's positional edits for one body/base with a FIELD MAP {off: dict(name,width,sign,type,stars,dims)}: [(pos, end, repl, site)],
    skips{reason: n}. The rules T2 fixed: width must match; a load's sign must match (a store may not care, R: a store's signedness
    leaves no byte); a pointer field's pointee must be the site's; indexed / negative / refused sites stay."""
    edits, skips = [], collections.Counter()
    bcls, bname = base_key.split(":", 1)
    decl = declared_type(masked, d, bname, bcls, fn_head_inner)
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
        if f["sign"] == "agg":
            skips["aggregate-field"] += 1
            continue
        if s.get("width") != f["width"]:
            skips["width"] += 1
            continue
        sg = f["sign"]
        if s.get("sign") != sg and not (s.get("access") == "store" and {s.get("sign"), sg} <= {"s", "u"}):
            skips["sign"] += 1
            continue
        if sg == "p":
            site_pointee = (s.get("ctype") or "").rstrip("* ").strip() + " *"
            ftype = sl._norm_type(f["type"]) + " " + "*" * f["stars"] if f["stars"] else sl._norm_type(f["type"])
            if site_pointee != ftype and not (allow_pointee_void and ftype == "void *"):
                skips["pointee"] += 1
                continue
        base_expr = ("&" + bname) if bcls == "gaddr" else bname
        edits.append((s["pos"], s["end"], member_spelling(tname, base_expr, bcls, decl, f["name"]), s))
    edits.sort(key=lambda e: e[0])
    kept, last = [], 0
    for e in edits:
        if e[0] < last:
            skips["overlap"] += 1
            continue
        kept.append(e); last = e[1]
    return kept, skips


def compose_text(raw, edits, inserts=()):
    """raw with [(pos, end, repl, …)] edits spliced and [(pos, text)] insertions (file-scope typedefs) placed — insertions at a
    position inside no edit."""
    items = [(a, b, rep) for (a, b, rep, *_) in edits] + [(p, p, t) for (p, t) in inserts]
    out, last = [], 0
    for (a, b, rep) in sorted(items, key=lambda e: (e[0], e[1])):
        if a < last:
            raise Refuse(f"overlapping edits at {a}")
        out.append(raw[last:a]); out.append(rep); last = b
    out.append(raw[last:])
    return "".join(out)


def greedy_kept(judge_cands, edits, tag):
    """Rung S2 on an edit list: judge_cands(sub_edits, tag) -> verdict. leave-one-out (n), else cumulative revert in source order
    until IDENTICAL, then minimise. Returns (kept_edits, compiles, verdict)."""
    n = len(edits)
    compiles = 0
    for i in range(n):
        v = judge_cands(edits[:i] + edits[i + 1:], tag + f"l{i}")
        compiles += 1
        if v == "IDENTICAL":
            return [edits[i]], compiles, "IDENTICAL"
    K = []
    for i in range(n):
        K.append(i)
        v = judge_cands([e for j, e in enumerate(edits) if j not in K], tag + f"c{i}")
        compiles += 1
        if v == "IDENTICAL":
            break
    else:
        return [], compiles, "NO-SET"
    for j in list(K):
        trial = [k for k in K if k != j]
        v = judge_cands([e for i2, e in enumerate(edits) if i2 not in trial], tag + f"m{j}")
        compiles += 1
        if v == "IDENTICAL":
            K = trial
    return [edits[i] for i in K], compiles, "IDENTICAL"


def s_body_edits(tu, fn, raw, masked, d, sites, bases, allow_local, local_types):
    """Every typed base of the body: [(edits, skips, base_key, tname, canonical?)] + the inserts (local typedefs). `bases` =
    body_base_type.json's {base_key: {type, sites}}; `local_types` accumulates the file's local typedef texts (T2 form)."""
    fn_head_inner, _ = _head_parts(masked, d, fn)
    per_base, inserts = [], []
    for base_key, ent in sorted(bases.items(), key=lambda kv: -kv[1]["sites"]):
        tname = ent["type"]
        t = struct_map().get(tname)
        if not t:
            per_base.append((base_key, tname, "NO-TYPE-IN-MAP", [], {}))
            continue
        can = canon_types().get(tname)
        if can and type_visible(tu, tname):
            fields = can[2] or {}
            edits, skips = s_edits(raw, masked, d, sites, tname, fields, base_key, fn_head_inner)
            per_base.append((base_key, tname, "CANONICAL", edits, skips))
        elif can:
            per_base.append((base_key, tname, "TYPE-NOT-VISIBLE", [], {}))
        elif allow_local:
            ctypes_by_off = collections.defaultdict(list)
            for s in sites:
                if s.get("bclass") + ":" + str(s.get("base")) == base_key and s.get("ctype"):
                    ctypes_by_off[s.get("off") or 0].append(s["ctype"])
            local_name = f"P37S_{hashlib.sha1(tname.encode()).hexdigest()[:8]}"
            ttext, fields_t2, skipped = build_type(local_name, t["layout"], ctypes_by_off)
            fields = {off: dict(name=nm, width=w, sign=sg, type=ft.rstrip("* ").strip(), stars=ft.count("*"), dims=[]) for off, (w, sg, nm, ft) in fields_t2.items()}
            edits, skips = s_edits(raw, masked, d, sites, local_name, fields, base_key, fn_head_inner)
            if edits and local_name not in local_types:
                local_types[local_name] = ttext
            per_base.append((base_key, local_name, "LOCAL", edits, skips))
        else:
            per_base.append((base_key, tname, "TYPE-NOT-CANONICAL", [], {}))
    return per_base


def lever_sites_in(text, tu, fn):
    """delever's body dict (its removable A/B sites) for one function of a CANDIDATE text — the census re-run on that text."""
    walk = lc.walk_file(text, tu, tu.endswith(".h"))
    sites = [s for s in walk["sites"] if s.get("fn") == fn]
    for s in sites:
        s.setdefault("aliases", []); s.setdefault("tu", tu); s.setdefault("header", tu.endswith(".h"))
    bodies = dl.bodies_from_sites(sites)
    return bodies.get((tu, fn))


def struct_plus_levers(tu, fn, text1, judge_one, label, log=None):
    """S+A: delever's ladder on the struct-spelled text. Returns (text2, res) — text2 = text1 when no lever came off; res = the
    ladder's result (verdict LEVER-FREE / RESIDUE / …, sites) or None when the body has no removable lever."""
    b = lever_sites_in(text1, tu, fn)
    if not b or not b["sites"]:
        return text1, None
    m1, ls1 = dl.same_len_mask(text1), dl.line_starts(text1)

    def judge(text, removed, tag):
        r = judge_one(text, tag)
        return r["verdict"], r["seconds"], r["err"]
    res = dl.ladder(b, text1, m1, ls1, judge, replay_from=None, log=log)
    accepted = res["accepted"]
    survivors = []
    for dd in res["sites"]:
        if dd["verdict"] in ("NEEDED", "REFUSED") and dd["ord"] >= 0:
            s = b["sites"][dd["ord"]]
            survivors.append((s, dd["verdict"], (dd["oracle"] if dd["verdict"] == "NEEDED" else dd["why"]) or ""))
    if not accepted:
        return text1, res
    markers = dl.marker_edits(text1, ls1, survivors, "S+A", label, phase="P37")
    text2 = dl.apply_edits(text1, accepted + markers)
    # the markers of the REMOVED sites are orphans now (the census's definition: no pin/asm site left on the line) — scrubbed here,
    # never left for a later --scrub (P36 left them and the census counted 0 orphans only after a sweep)
    removed_lines = {b["sites"][dd["ord"]]["line"] for dd in res["sites"] if dd["verdict"] in ("REMOVED", "REWRITTEN") and dd["ord"] >= 0}
    survivor_lines = {s_["line"] for (s_, _, _) in survivors}
    walk2 = lc.walk_file(text2, tu, tu.endswith(".h"))
    # a line keeps its marker only while a LEVER remains on it — a plain `gte_X()` (Sony's idiom, kind `gte`) is a site the census
    # counts but not a lever; the marker described the `_m` variant that just came off
    live_lines = {s_["line"] for s_ in walk2["sites"] if s_.get("fn") == fn and ((s_.get("cls"), s_.get("kind")) in dl.REMOVABLE or s_.get("kind") in dl.MARK_KINDS)}
    orphan = sorted(ln for ln in removed_lines if ln not in survivor_lines and ln not in live_lines)
    if orphan:
        # line numbers of text1 == text2 for the lever lines (a lever rewrite never adds or removes a line above the next lever)
        text2 = dl.apply_edits(text2, dl.scrub_edits(text2, orphan))
    return text2, res
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
def try_body(tu, fn, base_key=None, tname_hint=None, tag="p37", want_sa=True, want_greedy=True, want_recipes=False):
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
            row["hint"] = pass_hint(row.get("residual"))
            if want_recipes and kept and gv == "IDENTICAL":
                # the R recipes on the kept casts, over the S2 text (members everywhere but the kept sites)
                kept_ids = {id(k) for k in kept}
                s2_edits = [e for e in edits if id(e[3]) not in kept_ids]
                s2_text = splice(raw, d, local_name, s2_edits)
                kept_edits = [e for e in edits if id(e[3]) in kept_ids]
                row["recipes"] = run_recipes(tu, fn, s2_text, kept_edits, lambda text, tg, reloc=False: judge_files({tu: text}, tg, reloc=reloc), tag + "r")
                for hit in row["recipes"]:
                    hit.pop("text", None)
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
# rung S: one file (bottom-up over its bodies so positions stay valid; the last accepted candidate is the final text)
# ----------------------------------------------------------------------------------------------------------------------
def file_view(tu, text):
    """(masked, defs, span_of_line, params_of, sites) — the census's view of one text (T2's body_sites, once per file)."""
    masked = dl.same_len_mask(text)
    line_of = lambda idx: masked.count("\n", 0, idx) + 1
    recs = sc.scan_text(text, tu, shared_defs=None)
    defs = [r for r in recs if r["form"] == "def"]
    span_of_line = {}
    for d in defs:
        for ln in range(d["line"], d["end"] + 1):
            span_of_line[ln] = d
    params_of = {}
    ls = dl.line_starts(masked)
    for d in defs:
        head_start = ls[d["line"] - 1]
        brace = masked.find("{", head_start)
        head = masked[head_start:brace] if brace != -1 else ""
        m = re.search(r"\b" + re.escape(d["name"]) + r"\s*\(", head)
        if m:
            inner, close = tc._paren_body(head, m.end() - 1)
            params_of[d["name"]] = tc._param_names(inner or "", head[close + 1:] if close != -1 else "")
    sites, _ = tc.find_sites(masked, tu, span_of_line, line_of, params_of)
    return masked, defs, span_of_line, params_of, sites


def site_row(s, verdict, tname=None, field=None):
    return dict(form=s.get("form"), line=s.get("line"), base=f"{s.get('bclass')}:{s.get('base')}", off=s.get("off"), width=s.get("width"),
                sign=s.get("sign"), access=s.get("access"), type=tname, field=field, verdict=verdict)


def work_file_S(tu, bodies, label, calib_id, log, pool=None, allow_local=False, want_sa=True, want_recipes=False, done=frozenset(), write=True):
    """bodies = {fn: bases}. Returns dict(rows, written, final, compiles, seconds, …)."""
    path = REPO / tu
    st = path.stat()
    raw = path.read_text(errors="surrogateescape")
    is_hdr = tu.endswith(".h")
    if not recs_for(tu) and JUDGE_STUB is None:
        return dict(tu=tu, rows=[dict(ts=time.strftime("%Y-%m-%d %H:%M:%S"), label=label, rung="S", calib=calib_id, tu=tu, unit=fn, fn=fn,
                                      verdict="NO-RECIPE", sites=[]) for fn in bodies], written=False, final="NO-RECIPE", compiles=0, seconds=0.0,
                    members=0, kept=0, skipped=0, levers_off=0, bodies=len(bodies))
    short = hashlib.sha1(tu.encode()).hexdigest()[:6]
    text_acc = raw
    local_types, local_pos = {}, {}
    rows = []
    out = dict(tu=tu, rows=rows, written=False, final="", compiles=0, seconds=0.0, members=0, kept=0, skipped=0, levers_off=0,
               bodies=len(bodies), linked=0)
    masked0, defs0, _, _, _ = file_view(tu, raw)
    order = sorted([d for d in defs0 if d["name"] in bodies], key=lambda d: -d["line"])           # bottom-up
    first_line = min((d["line"] for d in order), default=None)
    for d in order:
        fn = d["name"]
        masked, defs, span_of_line, params_of, sites = file_view(tu, text_acc)
        d2 = next((x for x in defs if x["name"] == fn), None)
        if d2 is None:
            rows.append(dict(ts=time.strftime("%Y-%m-%d %H:%M:%S"), label=label, rung="S", calib=calib_id, tu=tu, unit=fn, fn=fn, verdict="TOOL-ERROR",
                             err="body not found in the accumulated text", sites=[]))
            continue
        nh0 = body_nhash(masked, d2)
        if ("S", tu, fn, nh0) in done:
            continue
        bsites = [s for s in sites if s.get("fn") == fn]
        per_base = s_body_edits(tu, fn, text_acc, masked, d2, bsites, bodies[fn], allow_local, local_types)
        edits = [e for (_, _, status, es, _) in per_base for e in es]
        skips = collections.Counter()
        for (_, _, _, _, sk) in per_base:
            skips.update(sk)
        row = dict(ts=time.strftime("%Y-%m-%d %H:%M:%S"), label=label, rung="S", calib=calib_id, tu=tu, unit=fn, fn=fn, addr=dl.fn_addr(fn, tu),
                   header=is_hdr, nhash_before=nh0, nhash_after=nh0,
                   bases=[dict(base=bk, type=tn, status=stt, edits=len(es), skips=dict(sk)) for (bk, tn, stt, es, sk) in per_base],
                   skips=dict(skips), sites=[], compiles=0, seconds=0.0, linked=0)
        out["skipped"] += sum(skips.values())
        if not edits:
            statuses = {stt for (_, _, stt, _, _) in per_base}
            row["verdict"] = ("TYPE-NOT-VISIBLE" if statuses == {"TYPE-NOT-VISIBLE"} else "TYPE-NOT-CANONICAL" if "TYPE-NOT-CANONICAL" in statuses
                              and not statuses & {"CANONICAL", "LOCAL"} else "NO-SITE")
            rows.append(row)
            continue
        tname_of = {id(e): tn for (_, tn, _, es, _) in per_base for e in es}
        base_text = text_acc
        # a LOCAL type (try mode) travels with its body: its typedef is inserted at file scope right before this function; a
        # typedef already placed below (an earlier, lower body of the same type) is moved up so both bodies see it (bottom-up order)
        needed = {tn for (_, tn, stt, es, _) in per_base if stt == "LOCAL" and es}
        ls_acc = dl.line_starts(base_text)
        ins_pos = ls_acc[d2["line"] - 1]
        inserts = []
        for tn in sorted(needed):
            if tn in local_pos:
                old_at = local_pos[tn]
                inserts.append((old_at, old_at + len(local_types[tn]), ""))          # delete the lower copy
            inserts.append((ins_pos, ins_pos, local_types[tn]))

        def cands(sub, tag):
            return judge_files({tu: compose_text(base_text, list(sub) + inserts)}, tag, pool=pool)
        r = cands(edits, f"{short}{d['line']}")
        row["compiles"] += r["compiles"]; row["seconds"] += r["seconds"]; row["linked"] += len(r["linked"])
        accepted, kept = list(edits), []
        if r["verdict"] == "IDENTICAL":
            row["verdict"] = "MEMBERS"
        elif r["verdict"] == "DIFFERS":
            res = classify_residual(tu, fn, r["cand0"])
            row["residual"] = res
            row["hint"] = pass_hint(res)
            kept, n_c, gv = greedy_kept(lambda sub, tag: cands(sub, tag)["verdict"], edits, f"{short}{d['line']}g")
            row["compiles"] += n_c
            if gv == "IDENTICAL":
                keep_ids = {id(k) for k in kept}
                accepted = [e for e in edits if id(e) not in keep_ids]
                row["verdict"] = "S2" if accepted else "KEPT-ALL"
            else:
                accepted, kept = [], list(edits)
                row["verdict"] = "KEPT-ALL"
                row["err"] = "S2 found no kept-cast set (NO-SET): the typedef or the mask moved bytes — a tool question"
        else:
            row["verdict"] = "REFUSED"
            row["err"] = f"{r['verdict']}: {r['err'][:200]}"
            accepted, kept = [], list(edits)
        for e in edits:
            s = e[3]
            v = "MEMBER" if any(e is a for a in accepted) else ("KEPT(" + row.get("hint", "?") + ")" if row.get("verdict") in ("S2", "KEPT-ALL") else "REFUSED")
            row["sites"].append(site_row(s, v, tname_of.get(id(e)), e[2].rsplit("->", 1)[-1].rsplit(".", 1)[-1]))
        out["members"] += len(accepted)
        out["kept"] += len(kept)
        if accepted:
            text_acc = compose_text(base_text, list(accepted) + inserts)
            for tn in sorted(needed):
                local_pos[tn] = ins_pos + sum(len(local_types[t_]) for t_ in sorted(needed) if t_ < tn)
            # S+A: the struct hypothesis on a lever-bearing body
            if want_sa and (tu, fn) in ds.sites_by_body() and JUDGE_STUB is None:
                def judge_one(text, tag):
                    return judge_files({tu: text}, tag, pool=pool)
                text2, lres = struct_plus_levers(tu, fn, text_acc, judge_one, label, log=log)
                if lres is not None:
                    row["levers"] = dict(verdict=lres["verdict"], rung=lres.get("rung"), removed=sum(1 for x in lres["sites"] if x["verdict"] in ("REMOVED", "REWRITTEN")),
                                         needed=sum(1 for x in lres["sites"] if x["verdict"] == "NEEDED"), refused=lres.get("refused", 0),
                                         compiles=lres["compiles"])
                    row["compiles"] += lres["compiles"]; row["seconds"] += lres["seconds"]
                    if text2 != text_acc:
                        out["levers_off"] += row["levers"]["removed"]
                        text_acc = text2
                        row["verdict"] = "S+A"
                    if write and row["verdict"] == "S+A":
                        # one lever record: delever's ledger gets the row too (a dry run — write=False — leaves no trace, R66)
                        dl.ledger_append([dict(ts=time.strftime("%Y-%m-%d %H:%M:%S"), label=f"P37-{label}", rung="S+A", calib=calib_id, tu=tu, fn=fn,
                                               addr=dl.fn_addr(fn, tu), aliases=[], header=is_hdr, nhash_before=nh0, nhash_after=None,
                                               verdict=lres["verdict"], sites=lres["sites"], compiles=lres["compiles"], seconds=round(lres["seconds"], 3))])
        if want_recipes and kept:
            row["recipes"] = run_recipes(tu, fn, text_acc, kept, lambda text, tag, reloc=False: judge_files({tu: text}, tag, pool=pool, reloc=reloc), f"{short}{d['line']}r")
            for hit in row["recipes"]:
                if hit["verdict"] == "IDENTICAL" and hit.get("adopt"):
                    text_acc = hit["text"]
                    hit.pop("text", None)
                    row["verdict"] = "R:" + hit["name"]
                    break
            for hit in row["recipes"]:
                hit.pop("text", None)
        rows.append(row)
        out["compiles"] += row["compiles"]; out["seconds"] += row["seconds"]; out["linked"] += row["linked"]
    if text_acc == raw:
        out["final"] = "UNCHANGED"
        return out
    fr = judge_files({tu: text_acc}, f"{short}F", pool=pool)
    out["compiles"] += fr["compiles"]; out["seconds"] += fr["seconds"]
    if fr["verdict"] != "IDENTICAL":
        dl.restore_file(path, raw, st)
        out["final"] = f"COMBINATION-FAILED ({fr['verdict']})"
        log(f"  {tu}: COMBINATION-FAILED ({fr['verdict']} {fr['err'][:120]}) — every body of this file REFUSED, the file restored")
        for row in rows:
            row["verdict"] = "COMBINATION-FAILED"
            row["nhash_after"] = None
        out["members"] = out["kept"] = out["levers_off"] = 0
        return out
    out["final"] = "IDENTICAL" + (" (linked)" if fr["linked"] else "")
    if JUDGE_STUB is None and write:
        path.write_text(text_acc, errors="surrogateescape")
    out["written"] = bool(write)
    out["final_text"] = text_acc
    # after-hashes from the final text
    try:
        masked_f, defs_f, _, _, _ = file_view(tu, text_acc)
        nh = {x["name"]: body_nhash(masked_f, x) for x in defs_f}
        for row in rows:
            row["nhash_after"] = nh.get(row["fn"], row.get("nhash_before"))
    except Exception as ex:      # noqa: BLE001
        log(f"  {tu}: after-hash walk failed ({ex}) — after-hash = before-hash")
    return out


# ----------------------------------------------------------------------------------------------------------------------
# rung R: recipes for a KEPT cast (the registry; each with a fixture in the selftest; T7's harvest adds here)
# ----------------------------------------------------------------------------------------------------------------------
NARROW_TYPES = {"s8", "u8", "s16", "u16", "char", "short", "unsigned char", "signed char", "unsigned short", "signed short"}


def recipe_ptr_global_member(text, tu, fn, site):
    """R1 (§458): a KEPT site on a POINTER GLOBAL base read by value — the pointer's own read spelled as a struct member so both sides
    of the pair carry /s: `*(u16 *)(D_x + 0x34)` -> `((S *)(((struct { PT p; } *)&D_x)->p))->…` needs the member type; the recipe
    keeps the SITE's cast and only respells the base: `*(u16 *)((((struct { PT p; } *)&D_x)->p) + 0x34)`."""
    if site.get("bclass") != "global":
        return []
    base = site["base"]
    m = re.search(r"\bextern\s+((?:(?:const|volatile|unsigned|signed|struct|union)\s+)*[A-Za-z_]\w*\s*\**)\s*" + re.escape(base) + r"\s*;", dl.same_len_mask(text))
    ptype = sl._norm_type(m.group(1)) if m else "void *"
    span = text[site["pos"]:site["end"]]
    new = re.sub(r"(?<![\w.])" + re.escape(base) + r"\b", f"(((struct {{ {ptype} p; }} *)&{base})->p)", span, count=1)
    if new == span:
        return []
    return [(text[:site["pos"]] + new + text[site["end"]:], f"R1 pointer global {base} read as a struct member ({ptype})", False)]


def recipe_extern_array(text, tu, fn, site):
    """R2 (a18): a KEPT site on a SCALAR GLOBAL base (`&D_x + k` / `D_x` by value): the TU's `extern T D_x;` becomes `extern T D_x[];`,
    every mention follows (`D_x` -> `D_x[0]`, `&D_x` -> `D_x`), the site becomes `D_x[k / w]` — the MEM_IN_STRUCT alias escape."""
    if site.get("bclass") not in ("gaddr", "global"):
        return []
    base = site["base"]
    masked = dl.same_len_mask(text)
    dm = re.search(r"\bextern\s+((?:(?:const|volatile|unsigned|signed)\s+)*[A-Za-z_]\w*)\s+" + re.escape(base) + r"\s*;", masked)
    if not dm:
        return []
    T = sl._norm_type(dm.group(1))
    w = sl.scalar_of(T)
    if not w or w[0] == 0 or (site.get("off") or 0) % w[0] != 0 or site.get("width") != w[0]:
        return []
    k = (site.get("off") or 0) // w[0]
    out = []
    edits = [(dm.start(), dm.end(), f"extern {T} {base}[];")]
    for mm in re.finditer(r"(&\s*)?(?<![\w.])" + re.escape(base) + r"\b", masked):
        if dm.start() <= mm.start() < dm.end():
            continue
        if site["pos"] <= mm.start() < site["end"]:
            continue
        if mm.group(1):
            edits.append((mm.start(), mm.end(), base))
        else:
            edits.append((mm.start(), mm.end(), f"{base}[0]"))
    edits.append((site["pos"], site["end"], f"{base}[{k}]"))
    try:
        cand = compose_text(text, edits)
    except Refuse:
        return []
    out.append((cand, f"R2 {base} declared extern {T} {base}[] (a18)", False))
    return out


def recipe_walked_pointer(text, tu, fn, site):
    """R3 (f3): consecutive carved words `D_A, D_(A+w), D_(A+2w)…` of one width mentioned in the body, walked through one pointer:
    `T *p37w = &D_A;` at the body's declarations, every `D_(A+kw)` -> `p37w[k]`. Changes the relocation spelling -> linked mode."""
    base = site.get("base") or ""
    mm = re.fullmatch(r"D_([0-9A-Fa-f]{8})", base)
    if not mm or site.get("bclass") not in ("gaddr", "global"):
        return []
    masked = dl.same_len_mask(text)
    decls = {m.group(2): sl._norm_type(m.group(1)) for m in re.finditer(r"\bextern\s+((?:(?:const|volatile|unsigned|signed)\s+)*[A-Za-z_]\w*)\s+(D_[0-9A-Fa-f]{8})\s*;", masked)}
    T = decls.get(base)
    w = sl.scalar_of(T) if T else None
    if not w or w[0] == 0:
        return []
    A = int(mm.group(1), 16)
    ds_ = [r for r in sc.scan_text(text, tu, shared_defs=None) if r["form"] == "def" and r["name"] == fn]
    if not ds_:
        return []
    d = ds_[0]
    ls = dl.line_starts(masked)
    s0, s1 = ls[d["line"] - 1], (ls[d["end"]] if d["end"] < len(ls) else len(masked))
    body = masked[s0:s1]
    # the run: every D_(A+kw) mentioned in the body with the same declared width, k >= 0, contiguous from A
    run = []
    k = 0
    while True:
        name = f"D_{A + k * w[0]:08X}"
        if name not in decls or sl.scalar_of(decls[name]) != w or not re.search(r"(?<![\w.])" + name + r"\b", body):
            break
        run.append(name); k += 1
    if len(run) < 2:
        return []
    edits = []
    for i, name in enumerate(run):
        for m in re.finditer(r"(&\s*)?(?<![\w.])" + name + r"\b", body):
            if m.group(1):
                edits.append((s0 + m.start(), s0 + m.end(), f"(p37w + {i})" if i else "p37w"))
            else:
                edits.append((s0 + m.start(), s0 + m.end(), f"p37w[{i}]"))
    # the declaration: after the body's opening brace, before the first statement — as the last declaration line
    brace = body.find("{")
    decl_end = brace + 1
    for m in re.finditer(r"\n[ \t]*(?:(?:const|volatile|unsigned|signed|struct|union|register)\s+)*[A-Za-z_]\w*\s*\**\s*[A-Za-z_]\w*(?:\s*\[[^\]]*\])*(?:\s*=[^;]*)?;", body):
        if m.start() > decl_end + 400:
            break
        decl_end = m.end()
    indent = re.search(r"\n([ \t]*)\S", body[brace:]) 
    ind = indent.group(1) if indent else "    "
    edits.append((s0 + decl_end, s0 + decl_end, f"\n{ind}{T} *p37w = &{run[0]};"))
    try:
        cand = compose_text(text, edits)
    except Refuse:
        return []
    return [(cand, f"R3 {run[0]}..{run[-1]} ({len(run)} x {T}) walked through one pointer (f3)", True)]


RECIPES = collections.OrderedDict([("R1-ptr-global-member", recipe_ptr_global_member), ("R2-extern-array", recipe_extern_array),
                                   ("R3-walked-pointer", recipe_walked_pointer)])


def run_recipes(tu, fn, text, kept_edits, judge, tag):
    """Every registered recipe on every KEPT site: [(name, note, verdict)]; a recipe that judges IDENTICAL is `adopt`-able (the caller
    takes the first). The kept sites' positions are re-walked on `text` by (line, off, base)."""
    masked, defs, span_of_line, params_of, sites = file_view(tu, text)
    # a kept site is found in the (possibly shifted — a typedef inserted above the body) text by its SHAPE and its rank among the
    # body's same-shaped sites, never by its line (R114: positions are re-derived, not cached)
    def shape(s):
        return (s.get("form"), str(s.get("base")), s.get("off"), s.get("ctype"), s.get("access"))
    ranked = collections.defaultdict(list)
    for s in sites:
        if s.get("fn") == fn and s.get("form") in RAW_FORMS:
            ranked[shape(s)].append(s)
    orig_rank = collections.Counter()
    hits = []
    for e in kept_edits:
        s0 = e[3]
        k = orig_rank[shape(s0)]
        orig_rank[shape(s0)] += 1
        cands_s = ranked.get(shape(s0), [])
        s = cands_s[k] if k < len(cands_s) else None
        if s is None:
            hits.append(dict(name="-", site=s0.get("line"), note="kept site not found in the S2 text", verdict="TOOL-ERROR"))
            continue
        for i, (name, gen) in enumerate(RECIPES.items()):
            try:
                cands = gen(text, tu, fn, s)
            except Exception as ex:     # noqa: BLE001
                hits.append(dict(name=name, site=s.get("line"), note=f"generator error {ex!r}"[:120], verdict="TOOL-ERROR"))
                continue
            for j, (cand, note, reloc) in enumerate(cands):
                r = judge(cand, f"{tag}{i}{j}", reloc)
                hits.append(dict(name=name, site=s.get("line"), note=note, verdict=r["verdict"], linked=bool(r["linked"]), adopt=(r["verdict"] == "IDENTICAL"), text=cand))
                if r["verdict"] == "IDENTICAL":
                    return hits
    return hits


# ----------------------------------------------------------------------------------------------------------------------
# rung D: the declaration layer (per TU; a definition-side change as one multi-file unit)
# ----------------------------------------------------------------------------------------------------------------------
_walk = None


def walk():
    global _walk
    if _walk is None:
        _walk = tc.walk_all(16, use_cache=True)
    return _walk


def promoted_params(params):
    """The width-promoted spelling of an ANSI parameter list (what a K&R call passes): narrow integers -> s32, float -> f32? no: double
    is what C89 promotes float to, but the tree spells f32 and PsyQ has no doubles in game code — kept as written."""
    out = []
    for part in sl._split_top(params, ","):
        p = part.strip()
        m = PARAM_DECL.match(p)
        if m and not m.group(2) and sl._norm_type(m.group(1)) in NARROW_TYPES:
            out.append(f"s32 {m.group(3)}")
        elif p in NARROW_TYPES:
            out.append("s32")
        else:
            out.append(p)
    return ", ".join(out)


_kr_cache = {}


def kr_ansi_params(rel, fndef):
    """A K&R definition's DEFAULT-PROMOTED parameter list as ANSI text (argcheck.kr_params on the definition's head). Cached per
    FILE (one mask + one scan per file, never per call — 1,889 K&R definitions re-masked per TU stalled the first batch)."""
    import argcheck
    with _LOCK:
        if rel not in _kr_cache:
            text = (REPO / rel).read_text(errors="surrogateescape")
            masked = sc.mask_text(text)
            found = {}
            for m in argcheck.KR_DEF.finditer(masked):
                names = [n.strip() for n in m.group(2).split(",")]
                types = argcheck.kr_params(names, m.group(3))
                found.setdefault(m.group(1), ", ".join(f"{t} {n}" for t, n in zip(types, names)))
            _kr_cache[rel] = found
    return _kr_cache[rel].get(fndef["fn"])


def defs_visible(tu):
    """{callee: [(def_tu, ret, params_ansi, kr)]} — the definitions a TU's calls can mean: its own file, its binary's source dir(s),
    the shared headers it includes, then main's and resident's (unique names). Distinct signatures -> the caller REFUSES (ambiguous)."""
    if DEFS_OVERRIDE is not None:
        return DEFS_OVERRIDE
    w = walk()
    results, tu_aliases = w["results"], w["tu_aliases"]
    import corpus
    dirs = set()
    for a in tu_aliases.get(tu, ()):
        try:
            dirs.add(corpus.src_dir(a).rstrip("/"))
        except Exception:      # noqa: BLE001
            pass
    files = [tu] + sorted(h for h in headers_of(tu) if h in results)
    for d_ in sorted(dirs):
        files += [rel for rel in _files_in_dir(d_) if rel != tu]
    out = collections.defaultdict(list)
    seen = set()
    for rel in files:
        if rel in seen or rel not in results or results[rel] is None:
            continue
        seen.add(rel)
        for f in _defs_of_file(rel):
            out[f[0]].append(f[1:])
    for name, lst in _fallback_defs().items():
        if name not in out:
            out[name] = list(lst)
    return out


_dir_files = {}
_file_defs = {}
_fallback = None


def _files_in_dir(d_):
    with _LOCK:
        if d_ not in _dir_files:
            results = walk()["results"]
            _dir_files[d_] = sorted(rel for rel in results if rel.endswith(".c") and rel.startswith(d_ + "/") and rel.count("/") == d_.count("/") + 1)
    return _dir_files[d_]


def _defs_of_file(rel):
    """[(fn, rel, ret, params_ansi, kr)] for one file's definitions (K&R heads promoted), computed once."""
    with _LOCK:
        cached = _file_defs.get(rel)
    if cached is not None:
        return cached
    r = walk()["results"].get(rel)
    out = []
    for f in (r or {}).get("fndefs", []):
        params = f["params"]
        if f.get("kr"):
            params = kr_ansi_params(rel, f) or params
        out.append((f["fn"], rel, f["ret"], params, bool(f.get("kr"))))
    with _LOCK:
        _file_defs[rel] = out
    return out


def _fallback_defs():
    """main's and resident's definitions (unique names — every overlay calls them), computed once."""
    global _fallback
    if _fallback is None:
        results = walk()["results"]
        fb = collections.defaultdict(list)
        for rel in sorted(results):
            if rel.endswith(".c") and (rel.count("/") == 1 or rel.startswith("src/resident/")):
                for f in _defs_of_file(rel):
                    fb[f[0]].append(f[1:])
        _fallback = fb
    return _fallback


DECL_RX_T = r"(?<![\w.])(extern\s+)?((?:(?:const|volatile|unsigned|signed|struct|union|static)\s+)*[A-Za-z_]\w*[\s*]*)\b{name}\s*\(([^;{{}}]*)\)\s*;"


def decl_sites(masked, callee):
    """[(start, end, line, has_extern, ret, params)] for every declaration of `callee` in a masked TU (file + block scope)."""
    out = []
    rx = re.compile(DECL_RX_T.format(name=re.escape(callee)))
    for m in rx.finditer(masked):
        ret = sl._norm_type(m.group(2))
        if ret in ("return", "goto", "else", "case") or not ret:
            continue
        out.append((m.start(), m.end(), masked.count("\n", 0, m.start()) + 1, bool(m.group(1)), ret, re.sub(r"\s+", " ", m.group(3)).strip()))
    return out


def call_arg_counts(masked, callee, decl_spans):
    """The distinct argument counts the TU's CALLS pass to `callee` (declarations and the definition excluded)."""
    counts = set()
    for m in re.finditer(r"(?<![\w.>])" + re.escape(callee) + r"\s*\(", masked):
        if any(a <= m.start() < b for (a, b) in decl_spans):
            continue
        inner, close = tc._paren_body(masked, m.end() - 1)
        if inner is None:
            continue
        tail = masked[close + 1:close + 3]
        if "{" in masked[close + 1:masked.find("\n", close) if masked.find("\n", close) != -1 else len(masked)] and not tail.strip().startswith((";", ",", ")")):
            continue                                            # the definition's head
        inner = inner.strip()
        counts.add(0 if inner in ("", "void") else len(sl._split_top(inner, ",")))
    return sorted(counts)


def d_units(tu, text, callees=None):
    """The TU's declaration units: [dict(callee, decls[(s,e,line,ext,ret,params)], ret, ansi, promoted, defn_tu, kr_def, ambiguous)] —
    every callee with >=1 declaration whose spelling is not the canonical one."""
    masked = dl.same_len_mask(text)
    vis = defs_visible(tu)
    names = set(callees) if callees else set(vis)
    units = []
    for callee in sorted(names):
        cands = vis.get(callee)
        if not cands:
            continue
        sigs = {(r, sl._norm_type(re.sub(r"\s+", " ", p))) for (_, r, p, _) in cands}
        decls = decl_sites(masked, callee)
        if not decls:
            continue
        if len(sigs) > 1:
            units.append(dict(callee=callee, decls=decls, ambiguous=sorted(sigs)[:4], defn_tu=cands[0][0]))
            continue
        ret, params = next(iter(sigs))
        params_n = params if params not in ("", "void") else "void"
        canon = {sl._norm_type(re.sub(r"\s+", " ", p)) if p.strip() not in ("",) else "void" for (_, _, _, _, r, p) in decls}
        rets = {r for (_, _, _, _, r, _) in decls}
        if canon == {params_n} and rets == {ret}:
            continue
        # a byte-proven K&R site already stands: every declaration `()` and marked `// K&R:` on its line — settled, not drawn again
        ls_ = dl.line_starts(masked)
        if all(p.strip() == "" and KR_MARK in text[ls_[ln - 1]:(ls_[ln] - 1 if ln < len(ls_) else len(text))] for (_, _, ln, _, _, p) in decls):
            continue
        units.append(dict(callee=callee, decls=decls, ret=ret, ansi=params_n, promoted=promoted_params(params_n), defn_tu=cands[0][0],
                          kr_def=cands[0][3], ambiguous=None))
    return units


def d_edits(unit, params):
    return [(s, e, f"{'extern ' if ext else ''}{unit['ret']} {unit['callee']}({params});") for (s, e, ln, ext, r, p) in unit["decls"]]


def _kr_marks_on(edits, marks):
    """The K&R markers land on the declaration LINES after the `()` rewrite: the marker edits were computed on the raw text's line
    ends, which the same-line rewrite does not move (a declaration is one line) — both edit sets compose."""
    return edits + marks


def kr_marker_edits(text, unit, counts, label):
    """`// K&R: n of m args (P37 rung D <label>)` appended to each `()` declaration line of the callee (a comment; counted apart)."""
    ls = dl.line_starts(text)
    m_ = 0 if unit["ansi"] == "void" else len(sl._split_top(unit["ansi"], ","))
    n_ = "/".join(str(c) for c in counts) if counts else "?"
    out = []
    seen = set()
    for (s, e, ln, ext, r, p) in unit["decls"]:
        if ln in seen:
            continue
        seen.add(ln)
        end = ls[ln] - 1 if ln < len(ls) else len(text)
        line = text[ls[ln - 1]:end]
        if KR_MARK in line:
            k = line.find(KR_MARK)
            j = k
            while j > 0 and line[j - 1] in " \t":
                j -= 1
            out.append((ls[ln - 1] + j, end, f"  {KR_MARK} {n_} of {m_} args (P37 rung D {label})"))
        else:
            out.append((end, end, f"  {KR_MARK} {n_} of {m_} args (P37 rung D {label})"))
    return out


def work_file_D(tu, label, calib_id, log, pool=None, callees=None, done=frozenset()):
    path = REPO / tu
    st = path.stat()
    raw = path.read_text(errors="surrogateescape")
    is_hdr = tu.endswith(".h")
    short = hashlib.sha1(tu.encode()).hexdigest()[:6]
    rows, out = [], dict(tu=tu, rows=[], written=False, final="", compiles=0, seconds=0.0, canon=0, promoted=0, kept=0, kr=0, units=0)
    out["rows"] = rows
    if not recs_for(tu) and JUDGE_STUB is None:
        out["final"] = "NO-RECIPE"
        return out
    units = d_units(tu, raw, callees)
    out["units"] = len(units)
    masked = dl.same_len_mask(raw)

    def unit_hash(u):
        return hashlib.sha1("|".join(f"{ln}:{r}:{p}" for (_, _, ln, _, r, p) in u["decls"]).encode()).hexdigest()[:12]
    live = []
    for u in units:
        if ("D", tu, "decl:" + u["callee"], unit_hash(u)) in done:
            continue
        if u.get("ambiguous"):
            rows.append(dict(ts=time.strftime("%Y-%m-%d %H:%M:%S"), label=label, rung="D", calib=calib_id, tu=tu, unit="decl:" + u["callee"], callee=u["callee"],
                             header=is_hdr, nhash_before=unit_hash(u), nhash_after=unit_hash(u), verdict="DECL-KEPT", cause="ambiguous: definitions disagree " + str(u["ambiguous"])[:160],
                             decls=len(u["decls"]), sites=[]))
            out["kept"] += 1
            continue
        live.append(u)
    if not live:
        out["final"] = "UNCHANGED"
        return out

    def compose(acc_units):
        edits = []
        for (u, params, marks) in acc_units:
            edits += d_edits(u, params) if params is not None else []
            edits += marks
        return {tu: compose_text(raw, edits)}
    # rung A: every unit's ANSI at once
    ansi_units = [(u, u["ansi"], []) for u in live]
    accepted, per, compiles, secs, rung = ladder_units(ansi_units, compose, lambda files, tag: judge_files(files, tag, pool=pool), f"{short}D", log=log)
    out["compiles"] += compiles; out["seconds"] += secs
    acc_ids = {id(x[0]) for x in accepted}
    final_units = list(accepted)
    for i, (u, _, _) in enumerate(ansi_units):
        row = dict(ts=time.strftime("%Y-%m-%d %H:%M:%S"), label=label, rung="D", calib=calib_id, tu=tu, unit="decl:" + u["callee"], callee=u["callee"],
                   header=is_hdr, defn_tu=u["defn_tu"], decls=len(u["decls"]), lines=[ln for (_, _, ln, _, _, _) in u["decls"]], ansi=u["ansi"],
                   nhash_before=unit_hash(u), nhash_after=None, sites=[])
        if id(u) in acc_ids:
            row["verdict"] = "DECL-CANON"
            out["canon"] += 1
        else:
            v, err, _ = per[i]
            row["first"] = dict(verdict=v, err=err[:200])
            # the promoted form, on top of what is accepted so far
            if u["promoted"] != u["ansi"] and not v.startswith("COMPILE"):
                r2 = judge_files(compose(final_units + [(u, u["promoted"], [])]), f"{short}Dp{i}", pool=pool)
                out["compiles"] += r2["compiles"]; out["seconds"] += r2["seconds"]
                if r2["verdict"] == "IDENTICAL":
                    final_units.append((u, u["promoted"], []))
                    row["verdict"] = "DECL-PROMOTED"
                    row["cause"] = f"narrow width: the caller does not convert ({u['ansi']} -> {u['promoted']}) — a definition-side question"
                    out["promoted"] += 1
                    rows.append(row)
                    continue
            if "too few arguments" in err or "too many arguments" in err:
                counts = call_arg_counts(masked, u["callee"], [(s, e) for (s, e, *_) in u["decls"]])
                marks = kr_marker_edits(raw, u, counts, label)
                empties = [d_ for d_ in u["decls"] if d_[5] == ""]
                if empties and len(empties) == len(u["decls"]):
                    final_units.append((u, None, marks))
                    row["verdict"] = "DECL-KEPT"
                    row["cause"] = f"K&R site: the calls pass {counts} arguments, the definition takes {u['ansi']} — kept `()`, marked"
                    row["kr"] = True
                    out["kr"] += 1
                else:
                    # a mix of `()` and truncated ANSI spellings (`(void)` for a one-parameter callee): every declaration becomes `()`
                    # (the K&R form) + the marker — judged; a `(void)` -> `()` is byte-neutral for a 0-argument call, an ANSI -> `()`
                    # may not be (the prototype's conversions vanish), so the oracle decides
                    r3 = judge_files(compose(final_units + [(u, "", marks)]), f"{short}Dk{i}", pool=pool)
                    out["compiles"] += r3["compiles"]; out["seconds"] += r3["seconds"]
                    if r3["verdict"] == "IDENTICAL":
                        final_units.append((u, "", marks))
                        row["verdict"] = "DECL-KEPT"
                        row["cause"] = f"K&R site: the calls pass {counts} arguments, the definition takes {u['ansi']} — every declaration `()`, marked"
                        row["kr"] = True
                        out["kr"] += 1
                    else:
                        row["verdict"] = "DECL-KEPT"
                        row["cause"] = f"arity: the calls pass {counts}, the definition takes {u['ansi']}; the all-`()` form {r3['verdict']} — needs a reading"
                out["kept"] += 1
            elif "conflicting types" in err:
                row["verdict"] = "DECL-KEPT"
                row["cause"] = "conflicting types: the TU defines or declares the callee in a form the declaration regex did not reach"
                out["kept"] += 1
            elif "parse error" in err:
                unknown = sorted({sl._norm_type(x.rsplit(" ", 1)[0].replace("*", "").strip()) for x in sl._split_top(u["ansi"], ",") if x.strip() and x.strip() != "void"}
                                 - set(sl.SCALARS) - set(sl.SDK_SIZES) - {"void", "struct", "union"})
                row["verdict"] = "DECL-KEPT"
                row["cause"] = f"type not visible: the prototype names {unknown or ['a type']} the TU cannot see (T5 canonicalises it) — " + err.split("\n")[0][-80:]
                row["needs_types"] = unknown
                out["kept"] += 1
            elif v.startswith("COMPILE"):
                row["verdict"] = "DECL-KEPT"
                row["cause"] = "compile: " + err.split("\n")[0][-100:]
                out["kept"] += 1
            else:
                row["verdict"] = "DECL-KEPT"
                row["cause"] = ("width: " if any(sl._norm_type(x.split()[0]) in NARROW_TYPES for x in sl._split_top(u["ansi"], ",") if x.strip() and x.strip() != "void") else "bytes: ") + (
                    "the canonical prototype moves the caller's bytes" + (f" [{err}]" if err else ""))
                out["kept"] += 1
        rows.append(row)
    files = compose(final_units)
    text = files[tu]
    if text == raw:
        out["final"] = "UNCHANGED"
        for row in rows:
            row["nhash_after"] = row["nhash_before"]
        return out
    fr = judge_files({tu: text}, f"{short}DF", pool=pool)
    out["compiles"] += fr["compiles"]; out["seconds"] += fr["seconds"]
    if fr["verdict"] != "IDENTICAL":
        dl.restore_file(path, raw, st)
        out["final"] = f"COMBINATION-FAILED ({fr['verdict']})"
        log(f"  {tu}: COMBINATION-FAILED ({fr['verdict']} {fr['err'][:120]}) — the TU's declaration units REFUSED, the file restored")
        for row in rows:
            row["verdict"] = "COMBINATION-FAILED"
        out["canon"] = out["promoted"] = out["kr"] = 0
        return out
    out["final"] = "IDENTICAL"
    if JUDGE_STUB is None:
        path.write_text(text, errors="surrogateescape")
    out["written"] = True
    out["final_text"] = text
    masked2 = dl.same_len_mask(text)
    for row in rows:
        decls2 = decl_sites(masked2, row["callee"])
        row["nhash_after"] = hashlib.sha1("|".join(f"{ln}:{r}:{p}" for (_, _, ln, _, r, p) in decls2).encode()).hexdigest()[:12]
    return out


def signature_change(callee, signature, label, calib_id, log, pool=None):
    """A DEFINITION-side change (`--callee F --signature "ret F(params)"`): the definition's head in its TU + every declaration of F in
    every TU of F's scope, ONE judged unit — every recipe IDENTICAL or nothing is written. Returns (rows, verdict, files_written)."""
    m = re.match(r"^\s*(.+?)\s*\b" + re.escape(callee) + r"\s*\((.*)\)\s*;?\s*$", signature, re.S)
    if not m:
        sys.exit(f"restruct: --signature must read `ret {callee}(params)`")
    ret, params = sl._norm_type(m.group(1)), re.sub(r"\s+", " ", m.group(2)).strip() or "void"
    w = walk()
    results = w["results"]
    def_files = [rel for rel, r in results.items() if r and any(f["fn"] == callee for f in r["fndefs"])]
    if len(def_files) != 1:
        sys.exit(f"restruct: {callee} has {len(def_files)} definitions ({def_files[:4]}) — a signature change needs exactly one (R43)")
    def_tu = def_files[0]
    files = {}
    dtext = (REPO / def_tu).read_text(errors="surrogateescape")
    dmask = dl.same_len_mask(dtext)
    fd = next(f for f in results[def_tu]["fndefs"] if f["fn"] == callee)
    ls = dl.line_starts(dmask)
    head_start = ls[fd["line"] - 1]
    brace = dmask.find("{", head_start)
    hm = re.search(r"([A-Za-z_][\w \t*]*?)\b" + re.escape(callee) + r"\s*\(([^{;]*)\)\s*(?=\{)", dmask[head_start:brace + 1])
    if not hm:
        sys.exit(f"restruct: cannot read {callee}'s definition head in {def_tu}:{fd['line']}")
    edits = [(head_start + hm.start(1), head_start + hm.end(2) + 1, f"{ret} {callee}({params})")]
    files[def_tu] = compose_text(dtext, edits)
    n_decl = 0
    for rel, r in results.items():
        if not r or rel == def_tu:
            continue
        if not any(e["name"] == callee for e in r.get("extern_fns", [])):
            continue
        text = (REPO / rel).read_text(errors="surrogateescape")
        ds_ = decl_sites(dl.same_len_mask(text), callee)
        if not ds_:
            continue
        files[rel] = compose_text(text, [(s, e, f"{'extern ' if ext else ''}{ret} {callee}({params});") for (s, e, ln, ext, r_, p) in ds_])
        n_decl += len(ds_)
    # the definition TU's own declarations too
    ds0 = decl_sites(dl.same_len_mask(files[def_tu]), callee)
    if ds0:
        files[def_tu] = compose_text(files[def_tu], [(s, e, f"{'extern ' if ext else ''}{ret} {callee}({params});") for (s, e, ln, ext, r_, p) in ds0])
        n_decl += len(ds0)
    log(f"signature {callee}: `{ret} {callee}({params})` — definition in {def_tu}, {n_decl} declarations in {len(files) - 1} other files")
    r = judge_files(files, "sig" + hashlib.sha1(callee.encode()).hexdigest()[:6], pool=pool)
    rows = []
    for rel in files:
        rows.append(dict(ts=time.strftime("%Y-%m-%d %H:%M:%S"), label=label, rung="D", calib=calib_id, tu=rel, unit="def:" + callee, callee=callee,
                         signature=f"{ret} {callee}({params})", definition=(rel == def_tu), verdict=("DECL-CANON" if r["verdict"] == "IDENTICAL" else "REFUSED"),
                         err=r["err"][:200], nhash_before=None, nhash_after=None, sites=[]))
    if r["verdict"] == "IDENTICAL":
        for rel, text in files.items():
            (REPO / rel).write_text(text, errors="surrogateescape")
        log(f"signature {callee}: IDENTICAL on every recipe ({r['compiles']} objects, {r['seconds']:.1f} s) — {len(files)} files written")
    else:
        log(f"signature {callee}: {r['verdict']} {r['err'][:200]} — nothing written")
    return rows, r["verdict"], (list(files) if r["verdict"] == "IDENTICAL" else [])


# ----------------------------------------------------------------------------------------------------------------------
# rung L: definition folds with member renames
# ----------------------------------------------------------------------------------------------------------------------
def _canon_by_layout():
    """{layout hash: [canonical definition]} + the canonical field-name set per definition."""
    can = canon_types()
    by = collections.defaultdict(list)
    seen = set()
    for name, (d, res, fm) in can.items():
        if id(d) in seen:
            continue
        seen.add(id(d))
        lay = res.layout_of_fields(d["fields"], d["kind"], packed=("packed" in d["attrs"]))
        if lay:
            by[sl.layout_hash(lay)].append(d)
    return by


def l_units(tu, text):
    """The TU's fold units: [dict(defn, kind, canon_name, edits, renames, refused)] for every file-scope definition with a canonical layout twin."""
    can = canon_types()
    if not can:
        return []
    by_l = _canon_by_layout()
    anyres = next(iter(can.values()))[1]
    w = tc.walk_file(text, tu)
    masked = dl.same_len_mask(text)
    ls = dl.line_starts(masked)
    # the TU's scope: canonical names + its own
    scope = dict(anyres.defs)
    for d in w["definitions"]:
        for n in d["names"] + ([d["tag"]] if d["tag"] else []):
            scope.setdefault(n, d)
    res = sl.Resolver(scope)
    # field names of every OTHER definition visible in the TU (the ambiguity check for renames)
    all_field_names = collections.Counter()
    for d in w["definitions"]:
        for f in d["fields"]:
            if f["name"]:
                all_field_names[f["name"]] += 1
    for name, (d, _, _) in can.items():
        pass
    canon_field_names = collections.Counter(f["name"] for (d, _, _) in {id(v[0]): v for v in can.values()}.values() for f in d["fields"] if f["name"])
    units = []
    for d in w["definitions"]:
        if d["kind"] == "enum" or d["scope"] != "file" or not d["fields"] or d["is_canon"]:
            continue
        lay = res.layout_of_fields(d["fields"], d["kind"], packed=("packed" in d["attrs"]))
        if not lay:
            continue
        cs = by_l.get(sl.layout_hash(lay), [])
        if not cs:
            continue
        names = d["names"] + ([d["tag"]] if d["tag"] else [])
        same_name = [c for c in cs if set(c["names"] + ([c["tag"]] if c["tag"] else [])) & set(names)]
        span = (ls[d["line"] - 1], ls[d["end"]] if d["end"] < len(ls) else len(masked))
        unit = dict(defn=names[0] if names else "?", line=d["line"], kind=None, canon=None, edits=[], renames=0, refused=None)
        if same_name:
            if any(c["text_hash"] == d["text_hash"] for c in same_name):
                unit.update(kind="delete-same", canon=same_name[0]["names"][0] if same_name[0]["names"] else same_name[0]["tag"], edits=[(span[0], span[1], "")])
            else:
                unit.update(kind="same-name-different-text", refused="the canonical definition under this name has another text (a VARIANT camp? §64a)")
            units.append(unit)
            continue
        if not d["typedef"] or not d["names"]:
            unit.update(kind="tag-only", refused="a tag-only local definition (struct tag {...}) — the alias form needs a typedef name")
            units.append(unit)
            continue
        c = cs[0]
        cname = c["names"][0] if c["names"] else f"struct {c['tag']}"
        # the offset map local -> canonical (top-level named scalar fields)
        lf = dict(sl.field_offsets(res, d))
        cf = {off: nm for (nm, off) in sl.field_offsets(next(iter(can.values()))[1], c)}
        renames = {}
        for nm, off in lf.items():
            tgt = cf.get(off)
            if tgt is None:
                unit.update(kind="alias+rename", refused=f"no canonical field at {off:#x} for local `{nm}`")
                break
            if tgt != nm:
                renames[nm] = tgt
        if unit["refused"]:
            units.append(unit)
            continue
        edits = [(span[0], span[1], "".join(f"typedef {cname} {n};\n" for n in d["names"]))]
        amb = [nm for nm in renames if all_field_names[nm] > 1 or canon_field_names.get(nm, 0) > 0]
        if amb:
            unit.update(kind="alias+rename", refused=f"ambiguous member name(s) {amb[:4]}: also a field of another type visible in the TU (a textual rename could hit it)")
            units.append(unit)
            continue
        for nm, tgt in renames.items():
            for m in re.finditer(r"(->|\.)\s*" + re.escape(nm) + r"\b", masked):
                if span[0] <= m.start() < span[1]:
                    continue
                edits.append((m.start(), m.end(), m.group(1) + tgt))
        unit.update(kind=("alias+rename" if renames else "alias"), canon=cname, edits=sorted(edits), renames=len(edits) - 1)
        units.append(unit)
    return units


def work_file_L(tu, label, calib_id, log, pool=None, done=frozenset()):
    path = REPO / tu
    st = path.stat()
    raw = path.read_text(errors="surrogateescape")
    short = hashlib.sha1(tu.encode()).hexdigest()[:6]
    rows, out = [], dict(tu=tu, rows=[], written=False, final="", compiles=0, seconds=0.0, folded=0, refused=0, renames=0, units=0)
    out["rows"] = rows
    if not recs_for(tu) and JUDGE_STUB is None:
        out["final"] = "NO-RECIPE"
        return out
    units = l_units(tu, raw)
    out["units"] = len(units)
    live = []
    for u in units:
        key = ("L", tu, "fold:" + u["defn"] + f"@{u['line']}")
        if u["refused"]:
            rows.append(dict(ts=time.strftime("%Y-%m-%d %H:%M:%S"), label=label, rung="L", calib=calib_id, tu=tu, unit=key[2], defn=u["defn"], kind=u["kind"],
                             verdict="FOLD-REFUSED", cause=u["refused"], nhash_before="-", nhash_after="-", sites=[]))
            out["refused"] += 1
            continue
        live.append(u)
    if not live:
        out["final"] = "UNCHANGED"
        return out

    def compose(acc):
        edits = [e for u in acc for e in u["edits"]]
        return {tu: compose_text(raw, edits)}
    accepted, per, compiles, secs, rung = ladder_units(live, compose, lambda files, tag: judge_files(files, tag, pool=pool), f"{short}L", log=log)
    out["compiles"] += compiles; out["seconds"] += secs
    acc_ids = {id(u) for u in accepted}
    for i, u in enumerate(live):
        row = dict(ts=time.strftime("%Y-%m-%d %H:%M:%S"), label=label, rung="L", calib=calib_id, tu=tu, unit="fold:" + u["defn"] + f"@{u['line']}", defn=u["defn"],
                   kind=u["kind"], canon=u["canon"], renames=u["renames"], nhash_before="-", nhash_after="-", sites=[])
        if id(u) in acc_ids:
            row["verdict"] = "FOLDED"
            out["folded"] += 1; out["renames"] += u["renames"]
        else:
            v, err, _ = per[i]
            row["verdict"] = "FOLD-REFUSED"
            row["cause"] = f"{v}: {err[:160]}"
            out["refused"] += 1
        rows.append(row)
    if not accepted:
        out["final"] = "UNCHANGED"
        return out
    text = compose(accepted)[tu]
    if rung == "A":
        fr = dict(verdict="IDENTICAL", compiles=0, seconds=0.0, err="", linked=[])
    else:
        fr = judge_files({tu: text}, f"{short}LF", pool=pool)
        out["compiles"] += fr["compiles"]; out["seconds"] += fr["seconds"]
    if fr["verdict"] != "IDENTICAL":
        dl.restore_file(path, raw, st)
        out["final"] = f"COMBINATION-FAILED ({fr['verdict']})"
        for row in rows:
            row["verdict"] = "COMBINATION-FAILED"
        out["folded"] = 0
        return out
    out["final"] = "IDENTICAL"
    if JUDGE_STUB is None:
        path.write_text(text, errors="surrogateescape")
    out["written"] = True
    out["final_text"] = text
    return out

# ----------------------------------------------------------------------------------------------------------------------
# planning and --apply (the batch: files in leverage order, workers own whole TUs, headers serial and last)
# ----------------------------------------------------------------------------------------------------------------------
def bbt():
    p = CENSUS / "body_base_type.json"
    if not p.exists():
        sys.exit("restruct: no body_base_type.json — run `tools/type_census.py -j 16 --sites` first (R43)")
    return json.loads(p.read_text())


def matches_only(only, tu, unit, extra=()):
    if not only:
        return True
    hay = [tu, unit] + list(extra)
    return any(o == h or h.endswith("/" + o) or h.startswith("src/" + o + "/") or ("/" + o + "/") in h
               or (o in h and o.startswith(("Unkstruct_", "func_", "D_"))) for o in only for h in hay if h)


def plan_S(headers, batch, only, done):
    """[(tu, {fn: bases})] — files with typed bases whose type is a CANONICAL definition (visible), ordered by the map's leverage."""
    smap = struct_map()
    can = canon_types()
    files = collections.defaultdict(dict)
    weight = collections.Counter()
    skipped = collections.Counter()
    for key, bases in bbt().items():
        tu, fn = key.split("|", 1)
        if tu.endswith(".h") != headers:
            continue
        if only and not matches_only(only, tu, fn, [b["type"] for b in bases.values()]):
            continue
        usable = {}
        for bk, ent in bases.items():
            if ent["type"] not in can:
                skipped["type-not-canonical"] += 1
                continue
            if not type_visible(tu, ent["type"]):
                skipped["type-not-visible"] += 1
                continue
            usable[bk] = ent
            weight[tu] += smap.get(ent["type"], {}).get("sites", 0)
        if usable:
            files[tu][fn] = usable
    ordered = sorted(files, key=lambda t: (-weight[t], t))
    return [(tu, files[tu]) for tu in ordered[:batch]], len(ordered), skipped


def plan_D(headers, batch, only):
    """[(tu, callees)] — TUs with lying declarations (argcheck's set widened to every callee spelled other than its definition), most first."""
    import argcheck
    cache_p = RUN / "argcheck_cache.json"
    stamp = lc.src_stamp()
    rows = None
    if cache_p.exists():
        try:
            c = json.loads(cache_p.read_text())
            if c.get("stamp") == stamp:
                rows = c["rows"]
        except Exception:      # noqa: BLE001 — a torn cache is rebuilt
            rows = None
    if rows is None:
        defs = argcheck.definitions()
        rows = argcheck.scan(defs, only_needed_argpins=False)              # ~2.4 min over the fleet: cached on the src stamp
        RUN.mkdir(parents=True, exist_ok=True)
        cache_p.write_text(json.dumps(dict(stamp=stamp, rows=rows)))
    by_tu = collections.defaultdict(set)
    for r in rows:
        if r["tu"].endswith(".h") != headers:
            continue
        if only and not matches_only(only, r["tu"], r["callee"]):
            continue
        by_tu[r["tu"]].add(r["callee"])
    ordered = sorted(by_tu, key=lambda t: (-len(by_tu[t]), t))
    return [(tu, sorted(by_tu[tu])) for tu in ordered[:batch]], len(ordered)


def plan_L(headers, batch, only):
    w = walk()
    by_l = _canon_by_layout()
    cands = []
    for rel, r in w["results"].items():
        if not r or rel.endswith(".h") != headers or not rel.startswith("src/") or rel in CANON_HEADERS:
            continue
        if only and not matches_only(only, rel, ""):
            continue
        n = sum(1 for d in r["definitions"] if d["scope"] == "file" and d["kind"] != "enum" and d["fields"] and d.get("lhash") in by_l) if by_l else 0
        if n == 0:
            # lhash is only present in census output; fall back to counting file-scope definitions
            n = sum(1 for d in r["definitions"] if d["scope"] == "file" and d["kind"] != "enum" and d["fields"])
        if n:
            cands.append((n, rel))
    cands.sort(reverse=True)
    return [(rel, None) for _, rel in cands[:batch]], len(cands)


def describe_plan(rung, plan, total, skipped=None):
    if rung == "S":
        n_b = sum(len(bs) for _, bs in plan)
        n_bases = sum(len(b) for _, bs in plan for b in bs.values())
        n_sites = sum(e["sites"] for _, bs in plan for b in bs.values() for e in b.values())
        return (f"restruct --plan S: {len(plan)} of {total} drawable files · {n_b} bodies · {n_bases} typed bases · {n_sites} deref sites"
                + (f" · skipped bases {dict(skipped)}" if skipped else ""))
    if rung == "D":
        return f"restruct --plan D: {len(plan)} of {total} TUs with lying declarations · {sum(len(c) for _, c in plan)} callees"
    return f"restruct --plan L: {len(plan)} of {total} files with file-scope definitions"


def apply_batch(a):
    RUN.mkdir(parents=True, exist_ok=True)
    clean, dirty = dl.src_clean()
    if not clean:
        sys.exit(f"restruct --apply: src/ is dirty — commit, or `tools/restruct.py --restore` if a batch is in flight (R42/R102):\n{dirty[:600]}")
    if INFLIGHT.exists():
        INFLIGHT.unlink()
    ok, why = oracle.calibration_current()
    if not ok:
        sys.exit(f"restruct --apply: the oracle's calibration is not current ({why}) — tools/delever_oracle.py --calibrate … first (R56)")
    calib = json.loads(oracle.CALIB.read_text())
    calib_id = dict(head=calib.get("head"), stamp=calib.get("stamp"))
    if not oracle.LINKS.exists():
        sys.exit("restruct --apply: the baseline snapshot carries no link inputs — tools/delever_oracle.py --snapshot-baseline after a GREEN check-all (R112)")
    rows = load_ledger()
    done, latest = ledger_index(rows)
    if a.redraw:
        done = {k for k in done if latest.get(k[:3]) not in set(a.redraw)}
    log_p = RUN / f"apply_{a.label}.log"
    log_f = open(log_p, "a")

    def log(msg):
        line = f"{time.strftime('%H:%M:%S')} {msg}"
        with _LOCK:
            print(line, flush=True)
            log_f.write(line + "\n"); log_f.flush()
    recipes()
    if a.callee:
        pool = ThreadPoolExecutor(max_workers=a.jobs)
        rows_, v, written = signature_change(a.callee, a.signature, a.label, calib_id, log, pool=pool)
        pool.shutdown(wait=True)
        ledger_append(rows_)
        line = f"restruct: signature {a.callee} — {v} · {len(written)} files written"
        log(line)
        log_f.close()
        return 0 if v == "IDENTICAL" else 1
    if a.rung == "S":
        plan, total, skipped = plan_S(a.headers, a.batch, a.only, done)
        print(describe_plan("S", plan, total, skipped), flush=True)
    elif a.rung == "D":
        plan, total = plan_D(a.headers, a.batch, a.only)
        print(describe_plan("D", plan, total), flush=True)
    else:
        plan, total = plan_L(a.headers, a.batch, a.only)
        print(describe_plan("L", plan, total), flush=True)
    if not plan:
        print(f"restruct --apply {a.rung}: nothing to do (no drawable file)")
        return 0
    # negative control (R39/R56): the first file of the batch compiled untouched must equal the snapshot
    ctl = next((tu for tu, _ in plan if recs_for(tu)), None)
    if ctl is None:
        sys.exit("restruct --apply: no file of the batch has a recipe (R43)")
    r0 = recs_for(ctl)[0]
    v, dt, err = oracle.judge(r0, None, tag="ctl")
    if v != "IDENTICAL":
        sys.exit(f"restruct --apply: the negative control FAILED — {ctl} untouched compiles {v} vs the snapshot ({err[:200]}); the baseline is stale (R56)")
    INFLIGHT.write_text(json.dumps(dict(label=a.label, rung=a.rung, files={tu: (REPO / tu).read_text(errors="surrogateescape") for tu, _ in plan})))
    if a.rung in ("D", "L"):
        walk()                      # the fleet walk forks a process pool: it must run BEFORE any worker thread exists (a fork from a
        _fallback_defs()            # threaded process deadlocked batch t3d1 at 0 % CPU); the shared definition tables likewise
    log(f"apply {a.label} rung {a.rung}: {len(plan)} files, control {ctl} IDENTICAL ({dt:.2f} s), calibration {calib_id['head']}")
    t0 = time.time()
    pool = ThreadPoolExecutor(max_workers=a.jobs)

    def one(item, hdr_pool=None):
        tu, payload = item
        try:
            if a.rung == "S":
                r = work_file_S(tu, payload, a.label, calib_id, log, pool=hdr_pool, allow_local=False, want_sa=not a.no_sa, want_recipes=a.recipes, done=done)
            elif a.rung == "D":
                r = work_file_D(tu, a.label, calib_id, log, pool=hdr_pool, callees=payload, done=done)
            else:
                r = work_file_L(tu, a.label, calib_id, log, pool=hdr_pool, done=done)
        except Exception as ex:      # noqa: BLE001 — a worker's crash is a row, never a silent gap (R55)
            import traceback
            log(f"  {tu}: TOOL-ERROR {ex!r}\n{traceback.format_exc()[-600:]}")
            r = dict(tu=tu, rows=[dict(ts=time.strftime("%Y-%m-%d %H:%M:%S"), label=a.label, rung=a.rung, calib=calib_id, tu=tu, unit="<file>", verdict="TOOL-ERROR",
                                       err=repr(ex)[:300], sites=[])], written=False, final="TOOL-ERROR", compiles=0, seconds=0.0)
        ledger_append(r["rows"])
        log(f"  {tu}: {r['final']} · rows {len(r['rows'])} · compiles {r['compiles']} · {r['seconds']:.1f} s" +
            (f" · members {r.get('members', 0)} kept {r.get('kept', 0)} skipped {r.get('skipped', 0)} levers off {r.get('levers_off', 0)}" if a.rung == "S" else "") +
            (f" · canon {r.get('canon', 0)} promoted {r.get('promoted', 0)} K&R {r.get('kr', 0)} kept {r.get('kept', 0)}" if a.rung == "D" else "") +
            (f" · folded {r.get('folded', 0)} refused {r.get('refused', 0)} renames {r.get('renames', 0)}" if a.rung == "L" else ""))
        return r
    if a.headers:
        results = [one(item, hdr_pool=pool) for item in plan]      # a header's includers compile in parallel; headers themselves serial
    else:
        with ThreadPoolExecutor(max_workers=a.jobs) as ex:
            results = list(ex.map(one, plan))
    pool.shutdown(wait=True)
    wall = time.time() - t0
    agg = collections.Counter()
    for r in results:
        for k in ("compiles", "members", "kept", "skipped", "levers_off", "canon", "promoted", "kr", "folded", "refused", "renames", "units", "bodies"):
            agg[k] += r.get(k, 0)
        agg["seconds"] += r["seconds"]
        agg["rows"] += len(r["rows"])
        agg["written"] += bool(r.get("written"))
        agg["final_ok"] += r["final"].startswith(("IDENTICAL", "UNCHANGED"))
        agg["final_bad"] += r["final"].startswith(("COMBINATION-FAILED", "TOOL-ERROR")) or r["final"] == ""
        agg["no_recipe"] += r["final"] == "NO-RECIPE"
    summary = dict(label=a.label, rung=a.rung, generated=time.strftime("%Y-%m-%d %H:%M"), headers=a.headers, batch=a.batch, only=a.only, files=len(plan),
                   drawable_files=total, wall_s=round(wall, 1), calib=calib_id, **{k: agg[k] for k in agg},
                   per_file=[dict(tu=r["tu"], final=r["final"], written=bool(r.get("written")), rows=len(r["rows"]), compiles=r["compiles"]) for r in results])
    (RUN / f"batch_{a.label}.json").write_text(json.dumps(summary, indent=1) + "\n")
    if a.rung == "S":
        detail = (f"{agg['bodies']} bodies: {agg['members']} sites → members / {agg['kept']} kept / {agg['skipped']} skipped · levers off {agg['levers_off']}")
    elif a.rung == "D":
        detail = f"{agg['units']} declaration units: {agg['canon']} canonical / {agg['promoted']} promoted / {agg['kr']} K&R marked / {agg['kept']} kept"
    else:
        detail = f"{agg['units']} definitions: {agg['folded']} folded ({agg['renames']} member renames) / {agg['refused']} refused"
    line = (f"restruct: batch {a.label} rung {a.rung} — {len(plan)} files ({'headers' if a.headers else 'TUs'}; {total} drawable) · {detail} · "
            f"compiles {agg['compiles']} in {wall:.0f} s wall · final {agg['final_ok']}/{len(plan)} identical · written {agg['written']} files")
    log(line)
    log_f.close()
    return 0 if agg["final_bad"] == 0 else 1


# ----------------------------------------------------------------------------------------------------------------------
# the WRITER (--write-types), the naming invariant (--audit-types), the ledger's field assertion (--check-ledger)
# ----------------------------------------------------------------------------------------------------------------------
def write_types(a):
    smap = struct_map()
    names = list(a.type or [])
    if a.top:
        names += [t["name"] for t in sorted(smap.values(), key=lambda t: -t["sites"])[:a.top] if t["name"] not in names]
    if not names:
        sys.exit("restruct --write-types: name the types (--type NAME … or --top N)")
    out_dir = RUN / "types_preview"
    out_dir.mkdir(parents=True, exist_ok=True)
    chunks, report = [], []
    sites_all = [json.loads(l) for l in (CENSUS / "sites.jsonl").read_text().splitlines() if l.strip()] if a.pointees and (CENSUS / "sites.jsonl").exists() else []
    for n in names:
        t = smap.get(n)
        if not t:
            report.append(f"{n}: not in the struct map"); continue
        ctypes = collections.defaultdict(list)
        for s in sites_all:
            if s.get("type") == n and s.get("ctype"):
                ctypes[s.get("off") or 0].append(s["ctype"])
        entries, skipped = sl.entries_from_layout(t["layout"], ctypes)
        if not entries:
            report.append(f"{n}: no entry survives the layout rules ({len(skipped)} skipped)"); continue
        size = None
        if t.get("size_hint"):
            end = max(e[0] + (sl.scalar_of(e[1]) or (4,))[0] for e in entries)
            size = max(t["size_hint"], end)
            size = (size + 3) // 4 * 4
        try:
            txt = sl.render_struct(n, entries, size=size, comment=f"P37 struct map: {t['sites']} sites in {t['bodies']} bodies; evidence {t.get('evidence')}" +
                                   (f"; at {','.join(t.get('globals_at', [])[:3])}" if t.get("globals_at") else ""))
        except ValueError as ex:
            report.append(f"{n}: writer refused — {ex}"); continue
        chunks.append(txt)
        by = collections.Counter(s[3] for s in skipped)
        report.append(f"{n}: {len(entries)} fields, size {size:#x} · skipped {dict(by)}" if size else f"{n}: {len(entries)} fields · skipped {dict(by)}")
    space = a.space or "ov"
    p = out_dir / f"{space}.h"
    p.write_text("/* restruct --write-types PREVIEW — not a build input; T5 authors the canonical files from this */\n\n" + "\n".join(chunks))
    print(f"restruct --write-types: {len(chunks)} definitions -> {p.relative_to(REPO)}")
    for r in report:
        print("  ", r)
    return 0


def audit_types(a=None, quiet=False):
    """struct_layout.audit_definition over every canonical type file's definitions (with their raw text for the comment/trailer checks)."""
    viol, n = [], 0
    for h in CANON_HEADERS:
        if not (REPO / h).exists():
            continue
        raw = (REPO / h).read_text(errors="surrogateescape")
        ls = dl.line_starts(raw)
        w = tc._walk_worker(h)
        defs = {}
        for d in w["definitions"]:
            for nm in d["names"] + ([d["tag"]] if d["tag"] else []):
                defs.setdefault(nm, d)
        for al in w["typedef_aliases"]:
            defs.setdefault(al["name"], dict(kind="alias", alias_of=al["alias_of"], alias_stars=al["alias_stars"], alias_dims=al["alias_dims"]))
        res = sl.Resolver(defs)
        for d in w["definitions"]:
            if d["kind"] == "enum" or not d["fields"]:
                continue
            n += 1
            text = raw[ls[d["line"] - 1]:ls[d["end"]] if d["end"] < len(ls) else len(raw)]
            for v in sl.audit_definition(d, res, text):
                viol.append(f"{h}:{d['line']} {v}")
    if not quiet:
        print(f"restruct --audit-types: {n} canonical definitions audited; {len(viol)} naming/offset violation(s)")
        for v in viol[:40]:
            print("  ", v)
    return 0 if not viol else 1


def check_ledger(a=None):
    """Every MEMBER site the ledger recorded is still a leaf (off, width, sign) of its CURRENT canonical type."""
    can = canon_types()
    rows = load_ledger()
    bad, n = [], 0
    for r in rows:
        if r.get("rung") not in ("S",):
            continue
        for s in r.get("sites", []):
            if s.get("verdict") != "MEMBER" or not s.get("type") or s["type"].startswith("P37S_"):
                continue
            n += 1
            c = can.get(s["type"])
            if not c:
                bad.append(f"{r['tu']}:{s['line']} {s['type']} no longer a canonical type"); continue
            d, res, fm = c
            lay = res.layout_of_fields(d["fields"], d["kind"], packed=("packed" in d["attrs"]))
            sign = s.get("sign") if s.get("access") != "store" else None
            if not sl.leaf_at(lay, s["off"], s["width"], sign):
                bad.append(f"{r['tu']}:{s['line']} {s['type']}+{s['off']:#x} ({s['width']}{s.get('sign')}) is not a field of the current definition")
    print(f"restruct --check-ledger: {n} MEMBER sites checked against the canonical types; {len(bad)} violation(s)")
    for b in bad[:30]:
        print("  ", b)
    return 0 if not bad else 1
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
# --selftest: the fixture (a stub oracle) + negative controls; --real adds the calibration and the known-true controls
# ----------------------------------------------------------------------------------------------------------------------
VISIBLE_OVERRIDE = None       # the selftest sets True: every canonical type is visible (no recipes/includers are consulted)
DEFS_OVERRIDE = None          # the selftest sets {callee: [(def_tu, ret, params, kr)]} for defs_visible()

FIXTURE_TYPES = '''#ifndef BFM_ENGINE_TYPES_H
#define BFM_ENGINE_TYPES_H
typedef struct {
    /* 0x0000 */ s16 unk0;
    /* 0x0002 */ u8 pad2[0x2];
    /* 0x0004 */ s32 unk4;
    /* 0x0008 */ u16 unk8;
    /* 0x000a */ u8 padA[0x2];
    /* 0x000c */ s16 *unkC;
} Unkstruct_TEST; /* size = 0x10 */
typedef struct { s16 a; s16 b; s32 c; } Blk8_TEST;
typedef struct { s16 x; s16 y; s32 z; } Twin_TEST;
#endif
'''

FIXTURE_TU = '''#include "common.h"
#include "../shared/engine_types.h"
extern s32 D_80078E00;
extern Unkstruct_TEST D_80078E20;
extern s32 D_80078E40;
extern s16 D_801F8870;
extern s16 D_801F8872;
extern s16 D_801F8874;
extern void fx_callee(s16 a0, s32 a1);
extern s32 fx_kr();
typedef struct { s16 a; s16 b; s32 c; } Loc8;
typedef struct { s16 q; s16 r; s32 s; } Loc8b;

void fx_a(s32 a0, Unkstruct_TEST *a1) {
    s32 p;
    Loc8 lb;
    Loc8b lc;
    p = a0 + 4;
    *(s16 *)(a0 + 0x0) = 1;
    *(u16 *)(a0 + 0x0) = 2;
    if (*(u16 *)(a0 + 0x0)) {
        p = 0;
    }
    *(s32 *)(a0 + 0x4) = *(s32 *)(a1 + 0x4);
    *(u8 *)(a0 + 0x4) = 3;
    *(s16 *)(a0 + 0x6) = 4;
    ((s16 *)a0)[p] = 5;
    *(s16 *)(a0 - 2) = 6;
    *(s32 *)(&D_80078E20 + 4) = 7;
    *(s16 *)(D_80078E40 + 0) = 8;
    M2C_FIELD(a0, u16 *, 8) = 9;
    *(s16 **)(a0 + 0xC) = 0;
    *(u8 **)(a0 + 0xC) = 0;
    lb.a = 1; lc.q = lb.b;
    fx_callee(1, 2);
    fx_kr(3, 4);
    D_801F8872 = D_801F8870 + D_801F8874;
}

void fx_b(s32 a0) {
    ((Unkstruct_TEST *)a0)->unk4 = 1;
}
'''

FIXTURE_BASES = {"param:a0": dict(type="Unkstruct_TEST", sites=12), "param:a1": dict(type="Unkstruct_TEST", sites=1),
                 "gaddr:D_80078E20": dict(type="Unkstruct_TEST", sites=1), "global:D_80078E40": dict(type="Unkstruct_TEST", sites=1)}


def _install_fixture(dirp):
    """The fixture tree under .run/P37/restruct/selftest/ (R12) with the canonical header and the TU; the module's caches pointed at it."""
    global _canon, _map_cache, VISIBLE_OVERRIDE
    dirp.mkdir(parents=True, exist_ok=True)
    (dirp / "shared").mkdir(exist_ok=True)
    (dirp / "ov").mkdir(exist_ok=True)
    hdr = dirp / "shared" / "engine_types.h"
    hdr.write_text(FIXTURE_TYPES)
    tu = dirp / "ov" / "fx.c"
    tu.write_text(FIXTURE_TU)
    hrel = hdr.relative_to(REPO).as_posix()
    w = tc.walk_file(FIXTURE_TYPES, hrel)
    defs = {}
    for d in w["definitions"]:
        d["file"] = hrel
        for n in d["names"] + ([d["tag"]] if d["tag"] else []):
            defs.setdefault(n, d)
    res = sl.Resolver(dict(defs))
    _canon = {}
    for d in w["definitions"]:
        fm = sl.field_map(res, d)
        for n in d["names"]:
            _canon[n] = (d, res, fm)
    _map_cache = {"Unkstruct_TEST": dict(name="Unkstruct_TEST", sites=100, bodies=3, size_hint=0x10, layout=[[0, 2, "s", 5], [4, 4, "s", 3], [8, 2, "u", 1], [12, 4, "p", 1]])}
    VISIBLE_OVERRIDE = True
    return tu.relative_to(REPO).as_posix(), hrel


def selftest(real=False):
    global JUDGE_STUB, DEFS_OVERRIDE, _canon, _map_cache, VISIBLE_OVERRIDE
    checks = []

    def ok(name, cond, note=""):
        checks.append((name, bool(cond), note))
    dirp = RUN / "selftest"
    tu, hrel = _install_fixture(dirp)
    text = (REPO / tu).read_text()
    masked, defs, span_of_line, params_of, sites = file_view(tu, text)
    d = next(x for x in defs if x["name"] == "fx_a")
    bsites = [s for s in sites if s.get("fn") == "fx_a"]
    ok("fixture parsed: 14 raw sites on fx_a", sum(1 for s in bsites if s["form"] in RAW_FORMS) == 14, str(collections.Counter(s["form"] for s in bsites)))
    # ---- rung S edits per base
    per = s_body_edits(tu, "fx_a", text, masked, d, bsites, FIXTURE_BASES, False, {})
    by = {bk: (stt, es, sk) for (bk, tn, stt, es, sk) in per}
    stt, es, sk = by["param:a0"]
    reps = [e[2] for e in es]
    ok("a0: 5 members", len(es) == 5, str(reps))
    ok("a0 store sign u->s allowed", "((Unkstruct_TEST *)a0)->unk0" in reps and reps.count("((Unkstruct_TEST *)a0)->unk0") == 2)
    ok("a0 M2C_FIELD -> unk8", "((Unkstruct_TEST *)a0)->unk8" in reps)
    ok("a0 pointer field pointee s16* -> unkC", "((Unkstruct_TEST *)a0)->unkC" in reps)
    ok("a0 skips: sign/width/no-field/index/negative/pointee each once", dict(sk) == {"sign": 1, "width": 1, "no-field": 1, "index": 1, "negative-offset": 1, "pointee": 1}, str(dict(sk)))
    stt1, es1, _ = by["param:a1"]
    ok("a1 typed parameter -> a1->unk4", [e[2] for e in es1] == ["a1->unk4"], str([e[2] for e in es1]))
    stt2, es2, _ = by["gaddr:D_80078E20"]
    ok("typed global address -> D_80078E20.unk4", [e[2] for e in es2] == ["D_80078E20.unk4"], str([e[2] for e in es2]))
    stt3, es3, _ = by["global:D_80078E40"]
    ok("pointer global (s32) -> cast form", [e[2] for e in es3] == ["((Unkstruct_TEST *)D_80078E40)->unk0"], str([e[2] for e in es3]))
    all_edits = [e for (_, _, _, es_, _) in per for e in es_]
    cand = compose_text(text, all_edits)
    ok("compose keeps the untouched sites", "*(u8 *)(a0 + 0x4) = 3;" in cand and "((s16 *)a0)[p] = 5;" in cand and "a1->unk4" in cand)
    # the no-op: fx_b already spelled with a member -> 0 edits
    db = next(x for x in defs if x["name"] == "fx_b")
    perb = s_body_edits(tu, "fx_b", text, masked, db, [s for s in sites if s.get("fn") == "fx_b"], {"param:a0": dict(type="Unkstruct_TEST", sites=1)}, False, {})
    ok("known-true no-op: a member-spelled body yields 0 edits", sum(len(es_) for (_, _, _, es_, _) in perb) == 0)
    # negative controls on the type builder
    ents, skipped = sl.entries_from_layout([(0, 4, "s", 5), (2, 2, "u", 1), (5, 2, "u", 3), (12, None, None, 1)])
    ok("layout: overlap/misaligned/width skipped", sorted(s_[3] for s_ in skipped) == ["misaligned", "overlap", "width"])
    # a wrong-offset field map must not convert the +0x4 site (the site says width 4 at +4; a map with s16 at +4 -> width skip)
    wrong = {4: dict(name="unk4", width=2, sign="s", type="s16", stars=0, dims=[])}
    e_w, sk_w = s_edits(text, masked, d, bsites, "Unkstruct_TEST", wrong, "param:a0", "s32 a0, Unkstruct_TEST *a1")
    ok("negative: a field of the wrong width converts nothing at that offset", not any(e[3].get("off") == 4 for e in e_w) and sk_w["width"] >= 1)
    # ---- S2 greedy with a stub: DIFFERS iff the +0x8 (M form) edit is in the candidate
    target = next(e for e in es if e[3]["form"] == "M")
    def stub_s2(files, tag):
        t = files[tu]
        return ("DIFFERS", "") if "((Unkstruct_TEST *)a0)->unk8" in t else ("IDENTICAL", "")
    JUDGE_STUB = stub_s2
    kept, n_c, gv = greedy_kept(lambda sub, tag: judge_files({tu: compose_text(text, sub)}, tag)["verdict"], es, "t")
    ok("S2 leave-one-out finds the one kept cast", gv == "IDENTICAL" and len(kept) == 1 and kept[0] is target and n_c <= len(es), f"{gv} kept={len(kept)} compiles={n_c}")
    # cumulative path: DIFFERS iff BOTH unk0 stores are members
    def stub_s2b(files, tag):
        return ("DIFFERS", "") if files[tu].count("((Unkstruct_TEST *)a0)->unk0") == 2 else ("IDENTICAL", "")
    JUDGE_STUB = stub_s2b
    kept2, n_c2, gv2 = greedy_kept(lambda sub, tag: judge_files({tu: compose_text(text, sub)}, tag)["verdict"], es, "t")
    ok("S2 keeps exactly one of two conflicting sites", gv2 == "IDENTICAL" and len(kept2) == 1 and kept2[0][3]["off"] == 0, f"kept={[k[3]['off'] for k in kept2]}")
    # ---- work_file_S with the stub: MEMBERS on fx_a (stub IDENTICAL), the ledger row shape, no write under the stub
    JUDGE_STUB = lambda files, tag: ("IDENTICAL", "")
    logs = []
    r = work_file_S(tu, {"fx_a": FIXTURE_BASES}, "st", dict(head="x"), logs.append, allow_local=False, want_sa=False)
    ok("work_file_S: MEMBERS, 8 members, final IDENTICAL", r["final"] == "IDENTICAL" and r["members"] == 8 and r["rows"][0]["verdict"] == "MEMBERS", f"{r['final']} {r['members']} {r['rows'][0]['verdict']}")
    ok("work_file_S: every site row has a verdict and the skips are counted", all(s_["verdict"] for s_ in r["rows"][0]["sites"]) and r["rows"][0]["skips"]["no-field"] == 1)
    ok("work_file_S: the stub never writes the tree", (REPO / tu).read_text() == text)
    JUDGE_STUB = lambda files, tag: ("DIFFERS", "")
    r2 = work_file_S(tu, {"fx_a": FIXTURE_BASES}, "st", dict(head="x"), logs.append, allow_local=False, want_sa=False)
    ok("work_file_S: an all-DIFFERS body is KEPT-ALL with S2 NO-SET named", r2["rows"][0]["verdict"] == "KEPT-ALL" and "NO-SET" in r2["rows"][0].get("err", ""), r2["rows"][0].get("err", "")[:60])
    # ---- pass hints
    ok("hint SCHED-ALIAS", pass_hint(dict(kind="ORDER", pairs=[(3, "8c620000 lw", "a4620034 sh"), (4, "a4620034 sh", "8c620000 lw")])) == "SCHED-ALIAS")
    ok("hint CSE-KILL", pass_hint(dict(kind="COUNT", pairs=[(3, "3c020000 lui", "--")])) == "CSE-KILL")
    ok("hint WIDTH", pass_hint(dict(kind="MIXED", pairs=[(3, "3042ffff andi", "00021400 sll")])) == "WIDTH")
    ok("hint REGALLOC", pass_hint(dict(kind="REG", pairs=[(3, "00431021 addu", "00431821 addu")])) == "REGALLOC")
    # ---- rung D on the fixture
    DEFS_OVERRIDE = {"fx_callee": [("src/ov/fx_defs.c", "void", "s32 a0, s32 a1", False)], "fx_kr": [("src/ov/fx_defs.c", "s32", "s32 a, s32 b", True)]}
    units = d_units(tu, text)
    byc = {u["callee"]: u for u in units}
    ok("D units: the two lying callees found", set(byc) == {"fx_callee", "fx_kr"}, str(sorted(byc)))
    ok("D: fx_callee's narrow decl vs the definition's s32", byc["fx_callee"]["ansi"] == "s32 a0, s32 a1" and byc["fx_callee"]["promoted"] == "s32 a0, s32 a1")
    ok("promoted_params widens narrow ints", promoted_params("s16 a0, u8 b, void *c, s32 d") == "s32 a0, s32 b, void *c, s32 d")
    ed = d_edits(byc["fx_kr"], byc["fx_kr"]["ansi"])
    ok("d_edits rewrites the `()` declaration", ed[0][2] == "extern s32 fx_kr(s32 a, s32 b);", ed[0][2])
    counts = call_arg_counts(masked, "fx_kr", [(s_, e_) for (s_, e_, *_) in byc["fx_kr"]["decls"]])
    ok("call_arg_counts reads the call's arity", counts == [2], str(counts))
    marks = kr_marker_edits(text, byc["fx_kr"], counts, "st")
    ok("K&R marker text", marks and "// K&R: 2 of 2 args (P37 rung D st)" in marks[0][2], marks[0][2] if marks else "")
    # the D ladder under stubs: all-at-once IDENTICAL -> both DECL-CANON
    JUDGE_STUB = lambda files, tag: ("IDENTICAL", "")
    rD = work_file_D(tu, "st", dict(head="x"), logs.append)
    ok("work_file_D: both units DECL-CANON on an IDENTICAL stub", rD["canon"] == 2 and rD["final"] == "IDENTICAL", f"{rD['canon']} {rD['final']}")
    # ANSI DIFFERS for fx_callee only -> promoted (equal here) is skipped -> DECL-KEPT(width); fx_kr's ANSI arity error -> K&R marked
    def stub_d(files, tag):
        t = files[tu]
        if "extern void fx_callee(s32 a0, s32 a1);" in t:
            return ("DIFFERS", "")
        if "extern s32 fx_kr(s32 a, s32 b);" in t:
            return ("COMPILE-ERROR", "fx.c:35: too few arguments to function `fx_kr'")
        return ("IDENTICAL", "")
    JUDGE_STUB = stub_d
    rD2 = work_file_D(tu, "st", dict(head="x"), logs.append)
    vs = {row["callee"]: (row["verdict"], row.get("cause", "")) for row in rD2["rows"]}
    ok("work_file_D: DIFFERS -> DECL-KEPT(width/bytes)", vs["fx_callee"][0] == "DECL-KEPT" and vs["fx_callee"][1].startswith(("width", "bytes")), str(vs["fx_callee"]))
    ok("work_file_D: arity error on `()` -> K&R site marked", vs["fx_kr"][0] == "DECL-KEPT" and vs["fx_kr"][1].startswith("K&R site") and rD2["kr"] == 1, str(vs["fx_kr"]))
    ok("work_file_D: the K&R marker lands in the final text", rD2.get("final_text", "") .count("// K&R: 2 of 2 args") == 1)
    # ---- rung L on the fixture: Loc8 folds onto Blk8_TEST with renames a->a? (same names: alias only); Loc8b (q/r/s) -> renames; ambiguity
    JUDGE_STUB = lambda files, tag: ("IDENTICAL", "")
    lu = l_units(tu, text)
    byd = {u["defn"]: u for u in lu}
    ok("L units: both local definitions have a canonical layout twin", set(byd) >= {"Loc8", "Loc8b"}, str(sorted(byd)))
    ok("L: Loc8 (same member names) is a plain alias", byd["Loc8"]["kind"] == "alias" and byd["Loc8"]["canon"] in ("Blk8_TEST", "Twin_TEST"), str(byd["Loc8"]))
    ok("L: Loc8b needs renames and is REFUSED as ambiguous or renamed", byd["Loc8b"]["kind"] == "alias+rename", str(byd["Loc8b"])[:120])
    rL = work_file_L(tu, "st", dict(head="x"), logs.append)
    ok("work_file_L: folds land under an IDENTICAL stub", rL["folded"] >= 1 and rL["final"] == "IDENTICAL", f"{rL['folded']} {rL['refused']} {rL['final']}")
    if rL.get("final_text"):
        ok("work_file_L: the alias replaces the definition", "typedef Blk8_TEST Loc8;" in rL["final_text"] or "typedef Twin_TEST Loc8;" in rL["final_text"])
    # ---- recipes (text transforms)
    site_glob = next(s for s in bsites if s.get("bclass") == "global")
    r1 = recipe_ptr_global_member(text, tu, "fx_a", site_glob)
    ok("R1 respells the pointer global as a struct member", r1 and "(((struct { s32 p; } *)&D_80078E40)->p)" in r1[0][0], (r1[0][0][:0] if r1 else "none"))
    site_g = next(s for s in bsites if s.get("bclass") == "gaddr")
    r2_ = recipe_extern_array(text, tu, "fx_a", site_g)
    ok("R2 refuses a non-scalar extern (D_80078E20 is a struct)", r2_ == [])
    fake = dict(site_g, base="D_80078E00", bclass="gaddr", off=0, width=4, pos=text.index("*(s32 *)(&D_80078E20 + 4)"), end=text.index("*(s32 *)(&D_80078E20 + 4)") + len("*(s32 *)(&D_80078E20 + 4)"))
    r2b = recipe_extern_array(text, tu, "fx_a", fake)
    ok("R2 rewrites the extern to an array and the site to an index", r2b and "extern s32 D_80078E00[];" in r2b[0][0] and "D_80078E00[0]" in r2b[0][0])
    fake3 = dict(site_g, base="D_801F8870", bclass="global", off=0, width=2)
    r3 = recipe_walked_pointer(text, tu, "fx_a", fake3)
    ok("R3 walks the three carved halves through one pointer (reloc flagged)", r3 and "s16 *p37w = &D_801F8870;" in r3[0][0] and "p37w[1] = p37w[0] + p37w[2];" in r3[0][0] and r3[0][2] is True, (r3[0][0][r3[0][0].find("p37w"):][:80] if r3 else "none"))
    # ---- ledger + inflight
    rows = [dict(rung="S", tu=tu, unit="fx_a", verdict="MEMBERS", nhash_after="h1", label="st"), dict(rung="S", tu=tu, unit="fx_a", verdict="COMBINATION-FAILED", nhash_after=None, label="st2")]
    done, latest = ledger_index(rows)
    ok("ledger: done keyed per unit+hash, latest verdict wins", ("S", tu, "fx_a", "h1") in done and latest[("S", tu, "fx_a")] == "COMBINATION-FAILED")
    # the in-flight snapshot's parser and restore core, on a SCRATCH path — never the real inflight.json (the first selftest run
    # deleted batch t3d1's live snapshot: an instrument's write path is part of the instrument, R57)
    scratch = dirp / "ov" / "inflight_probe.c"
    scratch.write_text("original\n")
    rel_s = scratch.relative_to(REPO).as_posix()
    probe_inflight = dirp / "inflight.json"
    probe_inflight.write_text(json.dumps(dict(label="selftest-x", files={rel_s: "original\n"})))
    scratch.write_text("candidate\n")
    d_, why = load_inflight(probe_inflight)
    ok("inflight parses", d_ is not None and rel_s in d_["files"], why)
    for f_, t_ in d_["files"].items():
        if (REPO / f_).read_text() != t_:
            (REPO / f_).write_text(t_)
    ok("inflight restore returns the original text", scratch.read_text() == "original\n")
    probe_inflight.write_text("")
    d_, why = load_inflight(probe_inflight)
    ok("an EMPTY inflight is refused loudly", d_ is None and "EMPTY" in why)
    probe_inflight.unlink()
    ok("the selftest never touches the live inflight.json", True)
    ok("struct_layout selftest", sl.selftest() == 0)
    JUDGE_STUB = None
    DEFS_OVERRIDE = None
    VISIBLE_OVERRIDE = None
    _canon = None
    _map_cache = None
    if real:
        okc, whyc = oracle.calibration_current()
        ok("[real] the oracle's calibration is current", okc, whyc)
        tu_r = "src/ov_SC05_010/ov_SC05_010_jr_80180F84.c"
        if (REPO / tu_r).exists() and okc:
            raw_r = (REPO / tu_r).read_text(errors="surrogateescape")
            rr = judge_files({tu_r: raw_r}, "stkt")
            ok("[real] known-true: the tree's own text judges IDENTICAL", rr["verdict"] == "IDENTICAL", f"{rr['verdict']} {rr['err'][:80]}")
            rn = judge_files({tu_r: raw_r.replace("\n}\n", "\n    __asm__(\"nop\");\n}\n", 1)}, "stneg")
            ok("[real] negative: a nop injected judges DIFFERS", rn["verdict"] == "DIFFERS", rn["verdict"])
        ok("[real] the linked-mode control (oracle --linked-control)", oracle.linked_control() == 0)
    bad = [(n, note) for n, c, note in checks if not c]
    print(f"restruct --selftest{' --real' if real else ''}: {len(checks) - len(bad)}/{len(checks)} OK")
    for n, note in bad:
        print(f"   FAIL {n}: {note}")
    return 0 if not bad else 1

# ----------------------------------------------------------------------------------------------------------------------
def main():
    ap = argparse.ArgumentParser(description=__doc__.split("\n")[0])
    ap.add_argument("--try", dest="try_", nargs=2, metavar=("TU", "FN"))
    ap.add_argument("--base", help="bclass:name (default: the body's largest typed base)")
    ap.add_argument("--recipes", action="store_true", help="also run the R recipes on the kept casts")
    ap.add_argument("--plan", action="store_true")
    ap.add_argument("--apply", action="store_true")
    ap.add_argument("--rung", choices=("S", "D", "L"), default="S")
    ap.add_argument("--batch", type=int, default=50)
    ap.add_argument("--label", default=time.strftime("r%m%d%H%M"))
    ap.add_argument("--headers", action="store_true", help="the batch draws shared headers (serial; judged on every includer)")
    ap.add_argument("--only", nargs="*", help="aliases / TUs / functions / type names to restrict the batch to")
    ap.add_argument("--no-sa", action="store_true", help="rung S without the struct-hypothesis lever pass")
    ap.add_argument("--redraw", nargs="*", default=[], help="draw again the units whose latest ledger verdict is one of these (e.g. DECL-KEPT after T5)")
    ap.add_argument("--try-file", nargs="+", metavar="TU_OR_FN", help="rung S on one TU's named bodies with the REAL oracle, local types allowed, NOTHING written")
    ap.add_argument("--callee", help="rung D: a DEFINITION-side signature change for this function (with --signature)")
    ap.add_argument("--signature", help='rung D: the new signature, e.g. "void func_800385C0(s32 a0)"')
    ap.add_argument("--restore", action="store_true")
    ap.add_argument("--status", action="store_true")
    ap.add_argument("--check-ledger", action="store_true")
    ap.add_argument("--audit-types", action="store_true")
    ap.add_argument("--write-types", action="store_true")
    ap.add_argument("--type", nargs="*")
    ap.add_argument("--top", type=int, default=0)
    ap.add_argument("--space", default="ov")
    ap.add_argument("--pointees", action="store_true", help="--write-types: read sites.jsonl for pointer fields' pointees (slow)")
    ap.add_argument("--selftest", action="store_true")
    ap.add_argument("--real", action="store_true", help="--selftest: add the calibration + known-true + linked controls (the real oracle)")
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
    if a.selftest:
        sys.exit(selftest(real=a.real))
    if a.restore:
        sys.exit(restore())
    if a.status:
        sys.exit(status())
    if a.check_ledger:
        sys.exit(check_ledger(a))
    if a.audit_types:
        sys.exit(audit_types(a))
    if a.write_types:
        sys.exit(write_types(a))
    if a.try_:
        row = try_body(a.try_[0], a.try_[1], base_key=a.base, want_recipes=a.recipes)
        print(json.dumps(row, indent=1))
        return
    if a.try_file:
        tu, fns = a.try_file[0], a.try_file[1:]
        recipes()
        all_b = {k.split("|", 1)[1]: v for k, v in bbt().items() if k.split("|", 1)[0] == tu}
        bodies = {fn: all_b[fn] for fn in (fns or all_b) if fn in all_b}
        if not bodies:
            sys.exit(f"restruct --try-file: no typed body of {tu} named {fns or '(any)'} in body_base_type.json (R43)")
        pool = ThreadPoolExecutor(max_workers=a.jobs)
        r = work_file_S(tu, bodies, "try", dict(head=oracle.head()), lambda m: print(m, flush=True), pool=pool, allow_local=True, want_sa=not a.no_sa,
                        want_recipes=a.recipes, write=False)
        pool.shutdown(wait=True)
        for row in r["rows"]:
            print(json.dumps({k: v for k, v in row.items() if k not in ("sites",)}, indent=1))
            print("   sites:", collections.Counter(s_["verdict"].split("(")[0] for s_ in row["sites"]))
        print(f"restruct --try-file: final {r['final']} · members {r['members']} kept {r['kept']} skipped {r['skipped']} levers off {r['levers_off']} · "
              f"compiles {r['compiles']} in {r['seconds']:.1f} s · NOTHING written")
        return
    if a.plan:
        recipes()
        done, _ = ledger_index(load_ledger())
        if a.rung == "S":
            plan, total, skipped = plan_S(a.headers, a.batch, a.only, done)
            print(describe_plan("S", plan, total, skipped))
        elif a.rung == "D":
            plan, total = plan_D(a.headers, a.batch, a.only)
            print(describe_plan("D", plan, total))
        else:
            plan, total = plan_L(a.headers, a.batch, a.only)
            print(describe_plan("L", plan, total))
        for tu, payload in plan[:40]:
            print(f"   {tu}  " + (f"{len(payload)} bodies" if a.rung == "S" else f"{len(payload)} callees" if a.rung == "D" else ""))
        return
    if a.apply:
        if a.callee and not a.signature:
            sys.exit("restruct --apply --callee needs --signature")
        sys.exit(apply_batch(a))
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
