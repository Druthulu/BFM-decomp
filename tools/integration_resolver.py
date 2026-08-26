#!/usr/bin/env python3
"""integration_resolver.py — the zero-token lane over drafts that are ALREADY CORRECT (P31 S61).

WHY THIS EXISTS. The S60 frontier analysis (docs/tool-designs/frontier-analysis-s60.md §4) measured
that the gen6+ "wall" is an INTEGRATION wall, not a codegen wall: of the 292 functions the gate had
refused six or more times, 178 (61%) had already produced a closeness-0 draft — match_one byte-
equality at the object level, whole-binary gate rejection — and across the whole open pool ~571
functions (470 closeness-0 backlog rows + 151 reloc_rejects rows with shape MATCH) had FINISHED
drafting. What remained for them was symbol identity, declaration conflicts or destination-TU
plumbing, and the fleet kept re-drafting them anyway (10,049 reject rows over 574 distinct
functions). No cookbook section can help a draft whose residual lives between the object file and
the linked image; a deterministic resolver can.

WHAT IT DOES. The ledgers only NOMINATE (binary, fn, draft) candidates — they are an index, not a
promise (a July closeness-0 draft can COMPILE-FAIL today because the fleet's declarations moved
under it; probed on func_80184A68). Every candidate is re-judged against TODAY'S tree:

  intake   backlog rows (closeness <= --closeness-max) ∪ reloc_rejects rows (shape MATCH)
           -> still an open INCLUDE_ASM stub? (else NOT-A-STUB, counted)   [corpus.stubs, R32]
  judge    rtu_match against the REAL split TU (no build tree, no locks, parallel-safe)
             CC1   -> the gate's own draft-side transforms (canon_resident_calls -> cast_call_sites
                      -> reconcile_tu, real --src-file) -> rtu once more
             DIFF  -> demoted with its CURRENT closeness (the stored one was stale)
             MATCH -> reloc_identity, the SECOND, DISAGREEING oracle (R34): rtu masks relocation
                      fields, so a body naming the WRONG symbol still reads MATCH and then dies at
                      link (§171). AGREE/UNRESOLVED/COMPILE-FAIL(standalone-only) -> stage;
                      MISMATCH + shape MATCH -> aprop_symfix rebase -> rtu -> reloc -> stage on AGREE
  stage    .run/sweep_resolver/<binary>/<fn>.c   (doubly-verified bodies only)
  gate     sweep_parallel over the stage dir (whole-binary SHA, G3/P9 — THE sole arbiter), then
           commit immediately (R42), counting banks from the INCLUDE_ASM invariant, never from
           messages (R33).
  ledger   .run/resolver/verdicts.jsonl — one row per (binary, fn, candidate) with the verdict,
           current closeness, first real diagnostic, and the (draft, split-TU) hashes; a later pass
           re-judges an item only when one of those hashes moved, so the lane converges instead of
           re-staging the same rejected body every 45 minutes.

REFUSALS (R43). `main` is not gated here — sweep_parallel refuses it; gate_main owns it — so main
rows are counted and named, never processed wrongly. A binary with no splat config, a missing draft
file, a corpus coverage defect, a draft carrying `//@EDIT` TU pre-edits (rtu applies them, the gate
cannot), and a dirty src/ tree at gate time (commit or refuse — never revert) are all refusals with
their own counter.

INSTRUMENT CHECK (R35/R39). Before the first verdict, --negative-control N re-judges N recently
BANKED functions in rtu's validation mode (the substituted TU compiled as-is against the surviving
target .s) and requires MATCH N/N; a DIFF verdict from a tool that fails its own control is not
evidence about any function.

  tools/integration_resolver.py --intake-only                # what the stock is TODAY, with denominators
  tools/integration_resolver.py -j 16                        # judge, stage, gate, commit
  tools/integration_resolver.py --no-gate --closeness-max 2  # stage only; include the grinder band
"""
import argparse
import collections
import datetime
import glob
import hashlib
import json
import os
import re
import shutil
import subprocess
import sys
import fcntl
import threading
import time
from concurrent.futures import ThreadPoolExecutor

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import backlog                                                           # noqa: E402
import corpus                                                            # noqa: E402

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
PY = ".venv/bin/python"
RUN = ".run/resolver"
LEDGER = f"{RUN}/verdicts.jsonl"
BACKLOG_MAIN = ".run/backlog.jsonl"
BACKLOG_BULK = ".run/auto/bulk/*.backlog.jsonl"
REJECTS = ".run/reloc_rejects.jsonl"
STAGE_DEFAULT = ".run/sweep_resolver"
STAGEABLE_RELOC = ("AGREE", "UNRESOLVED", "COMPILE-FAIL")   # COMPILE-FAIL = standalone-only (§ rtu_second_chance)
FINAL_NEG = ("DIFF", "CC1", "CPP", "MASPSX", "AS", "SYMBOL-MISMATCH", "GATE-REJECTED",
             "NEEDS-TU-EDIT", "NO-OBJ-FN", "UNKNOWN", "RELOC-ERR", "TIMEOUT", "EDIT-FAIL",
             "TU-BROKEN")   # re-opened automatically when the split TU (split_sha) changes

_print_lock = threading.Lock()
_stage_lock = threading.Lock()


def say(*a):
    with _print_lock:
        print("[%s] [resolver] %s" % (time.strftime("%H:%M:%S"), " ".join(str(x) for x in a)), flush=True)


def sh(cmd, timeout):
    try:
        return subprocess.run(cmd, capture_output=True, text=True, cwd=REPO, timeout=timeout)
    except subprocess.TimeoutExpired:
        return subprocess.CompletedProcess(cmd, 124, "", "TIMEOUT after %ds" % timeout)


def sha(path):
    try:
        return hashlib.sha1(open(path, "rb").read()).hexdigest()[:16]
    except OSError:
        return None


def real_binary(b):
    """The binary a row names, or None. Variant tags (ov_X-cn-cast) come from aprop_symfix output."""
    if not b:
        return None
    if b == "main" or os.path.exists(f"config/splat.{b}.yaml"):
        return b
    stem = b
    while "-" in stem:
        stem = stem.rsplit("-", 1)[0]
        if stem == "main" or os.path.exists(f"config/splat.{stem}.yaml"):
            return stem
    return None


# ------------------------------------------------------------------------------------------
# the oracles
# ------------------------------------------------------------------------------------------
def parse_rtu(out):
    first = next((l for l in out.splitlines() if l.strip()), "")
    m = re.match(r"MATCH \((\d+) ins\)", first)
    if m:
        return {"verdict": "MATCH", "nins": int(m.group(1)), "ndiff": 0, "note": first[:120]}
    m = re.match(r"DIFF\s+\S+\s+mine=(\d+) ins, target=(\d+) ins, (\d+) mismatched", first)
    if m:
        return {"verdict": "DIFF", "nins": int(m.group(2)), "ndiff": int(m.group(3)),
                "note": "mine=%s target=%s" % (m.group(1), m.group(2))}
    for tag in ("CC1", "CPP", "MASPSX", "AS"):
        if first.startswith(tag + " FAIL"):
            diag = next((l for l in out.splitlines()[1:] if l.strip()), "")
            return {"verdict": tag, "nins": None, "ndiff": None, "note": diag[:200]}
    if first.startswith("EDIT-FAIL"):
        return {"verdict": "EDIT-FAIL", "nins": None, "ndiff": None, "note": first[:200]}
    if first.startswith("ERR:"):
        return {"verdict": "NO-STUB", "nins": None, "ndiff": None, "note": first[:200]}
    if first.startswith("FAIL: object has no function"):
        return {"verdict": "NO-OBJ-FN", "nins": None, "ndiff": None, "note": first[:200]}
    if "TIMEOUT" in out[:200]:
        return {"verdict": "TIMEOUT", "nins": None, "ndiff": None, "note": "rtu_match > timeout"}
    return {"verdict": "UNKNOWN", "nins": None, "ndiff": None, "note": first[:200]}


def rtu(b, fn, stub, draft, work, o0):
    split = os.path.basename(stub.path)[:-2]
    cmd = [PY, "tools/rtu_match.py", fn, "--split", split, "--source", b, "--c", draft,
           "--asm-subdir", stub.asm_dir, "--work", work,
           "--stderr-out", os.path.join(work, "rtu_stderr.txt")]
    if o0:
        cmd.append("--o0")
    r = sh(cmd, timeout=600)
    v = parse_rtu((r.stdout or "") + ("\n" + r.stderr if r.returncode == 124 else ""))
    v["draft"] = draft
    return v


def transform(b, fn, draft, src_file, work):
    """The gate ladder's draft-side recovery (gate_stage stage 1), applied to ONE draft against
    its real split TU. Returns the transformed path, or None when nothing changed."""
    d = os.path.join(work, "x0")
    shutil.rmtree(d, ignore_errors=True)
    os.makedirs(d)
    shutil.copy(draft, os.path.join(d, fn + ".c"))
    cur = d
    for tool, suf, extra in (("canon_resident_calls.py", "-cn", []),
                             ("cast_call_sites.py", "-cast", ["--src-file", src_file]),
                             ("reconcile_tu.py", "-rc", ["--src-file", src_file])):
        out = cur + suf
        shutil.rmtree(out, ignore_errors=True)
        sh([PY, f"tools/{tool}", "--overlay", b, "--in", cur, "--out", out] + extra, timeout=900)
        if os.path.isfile(os.path.join(out, fn + ".c")):
            cur = out
    final = os.path.join(cur, fn + ".c")
    if not os.path.isfile(final) or sha(final) == sha(draft):
        return None
    return final


def reloc(b, fn, stub, draft, work, o0, tag):
    bp = os.path.join(work, f"reloc_{tag}_in.json")
    op = os.path.join(work, f"reloc_{tag}_out.json")
    json.dump([{"fn": fn, "binary": b, "draft": draft, "asm_subdir": stub.asm_dir, "o0": o0}],
              open(bp, "w"))
    r = sh([PY, "tools/reloc_identity.py", "--batch", bp, "-j", "1", "--out", op], timeout=600)
    try:
        return json.load(open(op))[0]
    except Exception:
        return {"status": "RELOC-ERR", "note": ((r.stdout or "") + (r.stderr or ""))[-300:]}


def symfix(b, fn, draft, work):
    sl = os.path.join(work, "symfix_slate.json")
    out = os.path.join(work, "symfix_out.json")
    od = os.path.join(work, "symfix")
    json.dump([{"fn": fn, "binary": b, "draft": draft}], open(sl, "w"))
    sh([PY, "tools/aprop_symfix.py", sl, "--fix", "--outdir", od, "--out-slate", out], timeout=300)
    try:
        rows = json.load(open(out))
    except Exception:
        return []
    seen, fixed = set(), []
    for x in rows:
        p = x.get("draft")
        if x.get("fn") == fn and real_binary(x.get("binary")) == b and p and os.path.exists(p):
            h = sha(p)
            if h not in seen:
                seen.add(h)
                fixed.append(p)
    return fixed


# ------------------------------------------------------------------------------------------
# intake
# ------------------------------------------------------------------------------------------
def load_backlog(cmax):
    """(binary, fn) -> {closeness, ts, draft, rows}. ANY row at closeness <= cmax nominates."""
    out, n_rows, n_qual = {}, 0, 0
    for p in [BACKLOG_MAIN] + sorted(glob.glob(BACKLOG_BULK)):
        if not os.path.exists(p):
            continue
        for line in open(p, errors="replace"):
            try:
                r = json.loads(line)
            except Exception:
                continue
            n_rows += 1
            c = r.get("closeness")
            if c is None or c > cmax or not r.get("best_draft"):
                continue
            b, fn = r.get("binary"), r.get("name")
            if not (b and fn):
                continue
            n_qual += 1
            e = out.setdefault((b, fn), {"closeness": c, "ts": r.get("ts") or "", "drafts": [], "rows": 0})
            e["rows"] += 1
            e["closeness"] = min(e["closeness"], c)
            e["ts"] = max(e["ts"], r.get("ts") or "")
            if r["best_draft"] not in e["drafts"]:
                e["drafts"].append(r["best_draft"])
    return out, n_rows, n_qual


def load_rejects():
    out, n_rows, n_qual = {}, 0, 0
    if not os.path.exists(REJECTS):
        return out, 0, 0
    rows = []
    for line in open(REJECTS, errors="replace"):
        try:
            r = json.loads(line)
        except Exception:
            continue
        n_rows += 1
        if r.get("shape") != "MATCH" or r.get("status") == "AGREE":
            continue
        if not (r.get("fn") and r.get("binary") and r.get("draft")):
            continue
        n_qual += 1
        rows.append(r)
    rows.sort(key=lambda r: -(r.get("t") or 0))                 # newest first
    for r in rows:
        e = out.setdefault((r["binary"], r["fn"]), {"drafts": [], "rows": 0})
        e["rows"] += 1
        if r["draft"] not in e["drafts"]:
            e["drafts"].append(r["draft"])
    return out, n_rows, n_qual


def load_ledger():
    """(binary, fn, draft_sha, split_sha) -> last verdict, so unchanged rejects are not re-judged."""
    last = {}
    if not os.path.exists(LEDGER):
        return last
    for line in open(LEDGER, errors="replace"):
        try:
            r = json.loads(line)
        except Exception:
            continue
        k = (r.get("binary"), r.get("fn"), r.get("draft_sha"), r.get("split_sha"))
        last[k] = r.get("verdict")
    return last


_stub_cache, _stub_err = {}, {}


def stub_index(b):
    if b in _stub_cache or b in _stub_err:
        return _stub_cache.get(b), _stub_err.get(b)
    try:
        _stub_cache[b] = {s.symbol: s for s in corpus.stubs(b).values()}
    except Exception as e:                                         # CorpusError: a coverage defect
        _stub_err[b] = "%s: %s" % (type(e).__name__, str(e)[:200])
    return _stub_cache.get(b), _stub_err.get(b)


# ------------------------------------------------------------------------------------------
# judge one item
# ------------------------------------------------------------------------------------------
_tu_ok_cache = {}


def _tu_broken(binary, stub, split_sha):
    """True + first error when the split TU fails the TU-alone compile WITH NO DRAFT SPLICED.
    A CC1 verdict then belongs to the TREE, not the draft (S61: one broken TU was billed to 39
    drafts as `undeclared`). Cached per (binary, split_sha)."""
    key = (binary, split_sha)
    if key not in _tu_ok_cache:
        try:
            import decl_from_use as _dfu
            ok, errs = _dfu.tu_compiles(binary, stub.path)
            _tu_ok_cache[key] = (not ok, (errs[0] if errs else "")[:200])
        except Exception as e:
            _tu_ok_cache[key] = (False, "tu-probe failed: %r" % e)
    return _tu_ok_cache[key]


_DATA_DEF_RE = re.compile(r"^(?P<lead>(?:const\s+|static\s+|volatile\s+)*[A-Za-z_]\w*(?:\s*\*+)?\s+)"
                          r"(?P<sym>[A-Za-z_]\w*_8[0-9A-Fa-f]{7})(?P<arr>\s*\[[^\]]*\])?"
                          r"\s*(?:=[^;]*)?;\s*$", re.M)


def dup_def_demote(binary, fn, stub, body, work):
    """The duplicate-symbol class (S61 live probe: assembler `symbol 'D_...' is already defined`):
    the draft DEFINES data at file scope that a still-stubbed sibling .s in the SAME TU also emits.
    rtu is blind to it (INCLUDE_ASM neutralized), so it surfaces only at the real build. Demote such
    defs to extern (single-line defs only; the sibling .s keeps emitting the bytes; the whole-binary
    SHA stays the sole arbiter). Returns a new candidate path, or None when nothing applies."""
    try:
        tu = open(stub.path, errors="replace").read()
    except OSError:
        return None
    sibs = []
    for m in re.finditer(r'INCLUDE_ASM\("([^"]+)",\s*(\w+)\)', tu):
        if m.group(2) != fn:
            sibs.append(os.path.join(m.group(1), m.group(2) + ".s"))
    if not sibs:
        return None
    emitted = set()
    for sp in sibs:
        try:
            for dm in re.finditer(r"^(?:dlabel|glabel)\s+([A-Za-z_]\w*)", open(sp, errors="replace").read(), re.M):
                emitted.add(dm.group(1))
        except OSError:
            continue
    # only lines at brace depth 0 are file-scope defs
    out, changed, depth = [], [], 0
    for line in body.split("\n"):
        m = _DATA_DEF_RE.match(line) if depth == 0 else None
        if m and m.group("sym") in emitted and not line.lstrip().startswith("extern"):
            out.append("extern " + m.group("lead").lstrip() + m.group("sym") + (m.group("arr") or "") + ";"
                       + "  /* dup-def demoted: a sibling .s still emits it (S61) */")
            changed.append(m.group("sym"))
        else:
            out.append(line)
        depth += line.count("{") - line.count("}")
    if not changed:
        return None
    os.makedirs(work, exist_ok=True)
    pth = os.path.join(work, fn + ".dupfix.c")
    open(pth, "w").write("\n".join(out))
    return pth


def resolve(item, a, ledger, stage):
    b, fn, stub = item["binary"], item["fn"], item["stub"]
    work = os.path.join(RUN, "work", "%s__%s" % (b, fn))
    shutil.rmtree(work, ignore_errors=True)
    os.makedirs(work)
    o0 = corpus.is_o0(stub.path)
    split_sha = sha(stub.path)
    src_file = stub.path
    rows, best = [], None
    staged = None
    cands = list(item["candidates"])
    for kind, draft in item["candidates"]:
        if os.path.exists(draft):
            dd = dup_def_demote(b, fn, stub, open(draft, errors="replace").read(), os.path.join(work, "dupfix"))
            if dd:
                cands.append(("dupfix:" + kind, dd))
    for kind, draft in cands:
        row = {"ts": time.strftime("%Y-%m-%d %H:%M:%S"), "run": a.run_id, "binary": b, "fn": fn,
               "kind": kind, "draft": draft, "draft_sha": sha(draft), "split_sha": split_sha,
               "stored_closeness": item.get("stored_closeness")}
        if not os.path.exists(draft):
            row.update(verdict="DRAFT-MISSING", ndiff=None, nins=None, note="")
            rows.append(row)
            continue
        if not a.fresh and ledger.get((b, fn, row["draft_sha"], split_sha)) in FINAL_NEG:
            row.update(verdict="SKIP-UNCHANGED", ndiff=None, nins=None,
                       note="same draft + same split TU as the last %s" % ledger[(b, fn, row["draft_sha"], split_sha)])
            rows.append(row)
            continue
        if "//@EDIT" in open(draft, errors="replace").read():
            row.update(verdict="NEEDS-TU-EDIT", ndiff=None, nins=None,
                       note="draft carries //@EDIT TU pre-edits; rtu applies them, the gate cannot (R43)")
            rows.append(row)
            continue
        w = os.path.join(work, "c%d" % len(rows))
        os.makedirs(w)
        v = rtu(b, fn, stub, draft, os.path.join(w, "rtu"), o0)
        body, via = draft, "raw"
        if v["verdict"] in ("CC1", "CPP") and not a.no_transforms:
            t = transform(b, fn, draft, src_file, w)
            if t:
                v2 = rtu(b, fn, stub, t, os.path.join(w, "rtu_x"), o0)
                if v2["verdict"] == "MATCH" or (v2["verdict"] == "DIFF" and v["verdict"] != "DIFF"):
                    v, body, via = v2, t, "transforms"
        if v["verdict"] == "MATCH":
            rv = reloc(b, fn, stub, body, w, o0, "a")
            st = rv.get("status")
            if st in STAGEABLE_RELOC:
                staged = (body, via, st)
            elif st in ("MISMATCH", "MISMATCH?") and rv.get("shape") == "MATCH":
                for f in symfix(b, fn, body, w):
                    v3 = rtu(b, fn, stub, f, os.path.join(w, "rtu_sf"), o0)
                    if v3["verdict"] != "MATCH":
                        continue
                    rv3 = reloc(b, fn, stub, f, w, o0, "b")
                    if rv3.get("status") in STAGEABLE_RELOC:
                        staged = (f, via + "+symfix", rv3.get("status"))
                        v = v3
                        break
                if not staged:
                    mm = rv.get("mismatches") or []
                    v = {"verdict": "SYMBOL-MISMATCH", "nins": v["nins"], "ndiff": 0,
                         "note": "; ".join("i=%s %s draft %s vs target %s%s" % (
                             m.get("i"), m.get("kind"), m.get("draft_symbol"), m.get("target_addr"),
                             (" =" + m["target_name"]) if m.get("target_name") else "") for m in mm[:3])[:240]}
            elif st == "NOT-A-STUB":
                v = {"verdict": "NOT-A-STUB", "nins": v["nins"], "ndiff": 0, "note": "banked meanwhile"}
            else:
                v = {"verdict": "RELOC-" + str(st), "nins": v["nins"], "ndiff": 0,
                     "note": str(rv.get("note") or rv.get("caveat") or "")[:200]}
        if not staged and v["verdict"] in ("CC1", "CPP"):
            _broken, _terr = _tu_broken(b, stub, split_sha)
            if _broken:
                v = {"verdict": "TU-BROKEN", "nins": v.get("nins"), "ndiff": None,
                     "note": "the split TU fails WITHOUT the draft — a tree condition, not this draft: " + _terr}
        row.update(verdict=("STAGED" if staged else v["verdict"]), ndiff=v.get("ndiff"),
                   nins=v.get("nins"), note=v.get("note", ""), via=via, body=(staged[0] if staged else body),
                   reloc=(staged[2] if staged else None))
        rows.append(row)
        if best is None or _rank(row) < _rank(best):
            best = row
        if staged:
            break
    if staged:
        body, via, st = staged
        dst_dir = os.path.join(stage, b)
        dst = os.path.join(dst_dir, fn + ".c")
        with _stage_lock:
            os.makedirs(dst_dir, exist_ok=True)
            if os.path.exists(dst) and sha(dst) != sha(body):
                rows[-1]["verdict"] = "STAGE-DUP"
                rows[-1]["note"] = "a different body is already staged for this fn"
            else:
                shutil.copy(body, dst)
                rows[-1]["staged_path"] = dst
    return rows


def _rank(row):
    v = row["verdict"]
    order = {"STAGED": 0, "STAGE-DUP": 1, "DIFF": 2, "SYMBOL-MISMATCH": 3, "CC1": 4, "CPP": 5,
             "RELOC-ERR": 6, "NEEDS-TU-EDIT": 7, "SKIP-UNCHANGED": 8, "DRAFT-MISSING": 9}
    return (order.get(v, 10), row.get("ndiff") if row.get("ndiff") is not None else 10 ** 6)


# ------------------------------------------------------------------------------------------
# the instrument check
# ------------------------------------------------------------------------------------------
def negative_control(n, jobs):
    """rtu validation mode over N recently BANKED overlay functions: expect MATCH N/N.

    A removed INCLUDE_ASM line nominates a (binary, fn); it is BANKED only if the fn is no longer an
    open stub anywhere in that binary (a carve removes and re-adds the same line — 9 of 12 first
    picks were carves, R14) and exactly one TU now defines it. The .s is whichever nonmatchings
    dir still holds it (banking does not delete the .s)."""
    pat = re.compile(r'^-.*INCLUDE_ASM\("(asm/[^"]+)",\s*(func_[0-9A-Fa-f]+)\)')
    picks, seen = [], set()
    for c in sh(["git", "log", "--format=%h", "-80", "--", "src/"], 60).stdout.split():
        for line in sh(["git", "show", "--unified=0", c, "--", "src/"], 120).stdout.splitlines():
            m = pat.match(line)
            if not m:
                continue
            parts = m.group(1).split("/")
            if len(parts) != 4 or parts[1] == "nonmatchings":            # main: not this lane's oracle
                continue
            b, fn = parts[1], m.group(2)
            if (b, fn) in seen:
                continue
            seen.add((b, fn))
            idx, err = stub_index(b)
            if err or fn in idx:                                          # still a stub => a carve, not a bank
                continue
            defs = [q for q in glob.glob("src/%s/%s*.c" % (b, b))
                    if re.search(r"^[A-Za-z_][^;{}\n]*\b%s\s*\(" % fn, open(q, errors="replace").read(), re.M)]
            ss = glob.glob("asm/%s/nonmatchings/*/%s.s" % (b, fn))
            if len(defs) != 1 or not ss:
                continue
            picks.append((b, os.path.basename(defs[0])[:-2], fn, os.path.dirname(ss[0])))
            if len(picks) >= n:
                break
        if len(picks) >= n:
            break
    empty = os.path.join(RUN, "nc", "empty.c")
    os.makedirs(os.path.dirname(empty), exist_ok=True)
    open(empty, "w").write("")

    def one(p):
        b, split, fn, sub = p
        cmd = [PY, "tools/rtu_match.py", fn, "--split", split, "--source", b, "--c", empty,
               "--asm-subdir", sub, "--work", os.path.join(RUN, "nc", "%s__%s" % (b, fn))]
        if corpus.is_o0("src/%s/%s.c" % (b, split)):
            cmd.append("--o0")
        return (b, fn, parse_rtu(sh(cmd, 600).stdout or ""))

    with ThreadPoolExecutor(max_workers=jobs) as ex:
        res = list(ex.map(one, picks))
    ok = [r for r in res if r[2]["verdict"] == "MATCH"]
    bad = [r for r in res if r[2]["verdict"] != "MATCH"]
    say("negative control: rtu validation MATCH %d/%d on recently-banked overlay fns" % (len(ok), len(res)))
    for b, fn, v in bad:
        say("  NC FAIL %s %s: %s %s" % (b, fn, v["verdict"], v["note"]))
    return len(ok), len(res)


# ------------------------------------------------------------------------------------------
# gate + commit
# ------------------------------------------------------------------------------------------
def stub_removals():
    """(binary, fn) whose INCLUDE_ASM stub is GONE in the working tree vs HEAD — the bank invariant.

    NET, not gross: a carve that runs at the gate removes a stub from one TU and re-adds it in another,
    so a `-` line alone over-counts (first run, S61: 72 removed lines, 12 of them carve moves, 60 real
    banks — the commit subject said 72). A stub counts as banked only if no `+` line re-adds it."""
    pat = re.compile(r'^([-+]).*INCLUDE_ASM\("(asm/[^"]+)",\s*(\w+)\)')
    rem, add = set(), set()
    for line in sh(["git", "diff", "--unified=0", "--", "src/"], 120).stdout.splitlines():
        m = pat.match(line)
        if m:
            parts = m.group(2).split("/")
            (rem if m.group(1) == "-" else add).add((parts[1] if parts[1] != "nonmatchings" else "main", m.group(3)))
    return rem - add


def gate_and_commit(stage, gate_jobs, n_staged):
    dirty = sh(["git", "status", "--porcelain", "--", "src/", "config/"], 60).stdout.strip()
    if dirty:
        say("REFUSING to gate: src/ or config/ is dirty (%d paths). Commit it first — never revert (R42)."
            % len(dirty.splitlines()))
        return None
    if sh(["bash", "-c", "ps -eo args | grep -c '[o]x_campaign.py --gater'"], 30).stdout.strip() not in ("", "0"):
        say("note: the wave gater is running; per-binary flocks keep this SAFE, but gates will contend (§3c)")
    mk_before = sum(1 for _ in open("config/overlays.mk"))
    os.makedirs(RUN, exist_ok=True)
    log = os.path.join(RUN, "gate.log")
    say("gating %d staged draft(s) via sweep_parallel -j %d (whole-binary SHA, G3/P9) -> %s" % (n_staged, gate_jobs, log))
    with open(log, "a") as f:
        f.write("=== %s gate of %d staged ===\n" % (time.strftime("%Y-%m-%d %H:%M:%S"), n_staged))
        # no external flock here: main() already holds .run/auto/draw.lock in-process for the whole
        # judge+gate (a child `flock` on the same file would deadlock against its parent)
        p = subprocess.run([PY, "tools/sweep_parallel.py", "--drafts", stage, "-j", str(gate_jobs)],
                           cwd=REPO, stdout=f, stderr=subprocess.STDOUT)
    if p.returncode != 0:
        say("sweep_parallel exited rc=%d — see %s (verify from the exit code, not the tree)" % (p.returncode, log))
    banked = stub_removals()
    mk_after = sum(1 for _ in open("config/overlays.mk"))
    if mk_after < 0.8 * mk_before:
        say("REFUSING to commit: config/overlays.mk collapsed %d -> %d lines (a blanket committer must not "
            "adopt a collapsed file). Tree left as-is for a human." % (mk_before, mk_after))
        return banked
    if not banked and not sh(["git", "status", "--porcelain", "--", "src/", "config/"], 60).stdout.strip():
        say("gate banked 0 of %d staged (INCLUDE_ASM invariant); nothing to commit" % n_staged)
        return banked
    sh(["git", "add", "-A", "src/", "config/"], 120)
    sh(["bash", "-c", "git reset -q -- src/*.c 2>/dev/null || true"], 60)   # main TUs belong to gate_main
    if sh(["git", "diff", "--cached", "--quiet"], 60).returncode == 0:
        say("only main-TU dirt found — leaving it to gate_main; nothing to commit")
        return banked
    msg = ("feat(decomp): integration-resolver pass — %d banked of %d staged (zero model tokens)\n\n"
           "Drafts the ledgers already recorded as byte-correct (closeness 0 / reloc shape MATCH), "
           "re-judged against today's tree by rtu_match + reloc_identity, staged, and gated on the "
           "whole-binary SHA. Ledger: %s" % (len(banked), n_staged, LEDGER))
    r = sh(["git", "commit", "-q", "-m", msg], 300)
    say("committed %s: %d banked of %d staged" % (sh(["git", "rev-parse", "--short", "HEAD"], 30).stdout.strip(),
                                                    len(banked), n_staged) if r.returncode == 0 else
        "git commit FAILED rc=%d: %s" % (r.returncode, (r.stderr or "")[-300:]))
    return banked


# ------------------------------------------------------------------------------------------
def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--closeness-max", type=int, default=0)
    ap.add_argument("--limit", type=int, default=0, help="cap judged items (0 = all)")
    ap.add_argument("--only-binaries", default=None)
    ap.add_argument("-j", "--jobs", type=int, default=16)
    ap.add_argument("--stage", default=STAGE_DEFAULT)
    ap.add_argument("--fresh", action="store_true", help="ignore the ledger's unchanged-reject skips")
    ap.add_argument("--intake-only", action="store_true")
    ap.add_argument("--no-gate", action="store_true", help="stage only")
    ap.add_argument("--gate-jobs", type=int, default=10)
    ap.add_argument("--negative-control", type=int, default=12)
    ap.add_argument("--force", action="store_true", help="proceed even if the negative control fails")
    ap.add_argument("--no-demote", action="store_true", help="do not write current-closeness backlog rows")
    ap.add_argument("--no-transforms", action="store_true")
    ap.add_argument("--no-lock", action="store_true",
                    help="do not take .run/auto/draw.lock (ONLY when no gate can be in flight)")
    a = ap.parse_args()
    os.chdir(REPO)
    a.run_id = datetime.datetime.now().strftime("%Y%m%d-%H%M%S")
    os.makedirs(RUN, exist_ok=True)
    counts = collections.Counter()

    # ---- intake ----
    bl, bl_rows, bl_qual = load_backlog(a.closeness_max)
    rj, rj_rows, rj_qual = load_rejects()
    say("intake: backlog %d rows, %d at closeness<=%d -> %d distinct (binary,fn); reloc_rejects %d rows, "
        "%d shape-MATCH -> %d distinct; union %d"
        % (bl_rows, bl_qual, a.closeness_max, len(bl), rj_rows, rj_qual, len(rj), len(set(bl) | set(rj))))
    only = set(a.only_binaries.split(",")) if a.only_binaries else None
    items = []
    for key in sorted(set(bl) | set(rj)):
        b, fn = key
        if only and b not in only:
            counts["filtered-by-only"] += 1
            continue
        rb = real_binary(b)
        if rb is None:
            counts["BAD-BINARY"] += 1
            continue
        if rb == "main":
            counts["MAIN-UNSUPPORTED (gate_main owns it)"] += 1
            continue
        idx, err = stub_index(rb)
        if err:
            counts["HARNESS-CORPUS"] += 1
            continue
        stub = idx.get(fn)
        if stub is None:
            counts["NOT-A-STUB (banked since)"] += 1
            continue
        cands = [("backlog", d) for d in bl.get(key, {}).get("drafts", [])] + \
                [("reloc", d) for d in rj.get(key, {}).get("drafts", [])]
        seen, uniq = set(), []
        for kind, d in cands:
            h = sha(d) if os.path.exists(d) else ("missing:" + d)
            if h in seen:
                continue
            seen.add(h)
            uniq.append((kind, d))
        items.append({"binary": rb, "fn": fn, "stub": stub, "candidates": uniq,
                      "stored_closeness": bl.get(key, {}).get("closeness"),
                      "nins": corpus.s_ins_count(stub.asm_path) if hasattr(corpus, "s_ins_count") else None})
    for e in sorted(_stub_err):
        say("HARNESS-CORPUS %s: %s" % (e, _stub_err[e]))
    say("intake: %d judgeable item(s) still open; dropped: %s" % (len(items), dict(counts) or "none"))
    if a.limit and len(items) > a.limit:
        items.sort(key=lambda i: (i["stored_closeness"] if i["stored_closeness"] is not None else 99, -(i["nins"] or 0)))
        say("limit: judging %d of %d" % (a.limit, len(items)))
        items = items[:a.limit]
    if a.intake_only:
        by_bin = collections.Counter(i["binary"] for i in items)
        say("by binary (top 12): %s" % by_bin.most_common(12))
        json.dump([{k: v for k, v in i.items() if k != "stub"} for i in items],
                  open(os.path.join(RUN, "intake_%s.json" % a.run_id), "w"), indent=1, default=str)
        return 0
    if not items:
        say("nothing to judge")
        return 0

    # ---- serialise with every gate: rtu_match reads the src/ TUs a gate transiently splices into,
    # and the wave gater / maintenance sweep hold this lock for exactly that window ----
    if not a.no_lock:
        os.makedirs(".run/auto", exist_ok=True)
        _lk = open(".run/auto/draw.lock", "a+")
        try:
            fcntl.flock(_lk, fcntl.LOCK_EX | fcntl.LOCK_NB)
        except OSError:
            say("waiting for .run/auto/draw.lock (a gate or sweep is in flight; rtu must not read a TU mid-splice)")
            fcntl.flock(_lk, fcntl.LOCK_EX)
        say("holding .run/auto/draw.lock for the judge+gate")

    # ---- instrument check ----
    if a.negative_control:
        ok, n = negative_control(a.negative_control, min(a.jobs, 8))
        if ok < n and not a.force:
            say("negative control FAILED (%d/%d): the instrument is not cleared — refusing to judge (R35/R40). "
                "--force overrides." % (ok, n))
            return 2

    # ---- judge ----
    ledger = {} if a.fresh else load_ledger()
    shutil.rmtree(a.stage, ignore_errors=True)
    os.makedirs(a.stage, exist_ok=True)
    say("judging %d item(s) with -j %d (rtu_match -> transforms -> reloc_identity -> symfix); stage=%s"
        % (len(items), a.jobs, a.stage))
    t0 = time.time()
    done = [0]
    all_rows = []

    def one(it):
        try:
            rows = resolve(it, a, ledger, a.stage)
        except Exception as e:
            rows = [{"ts": time.strftime("%Y-%m-%d %H:%M:%S"), "run": a.run_id, "binary": it["binary"],
                     "fn": it["fn"], "kind": "-", "draft": None, "draft_sha": None, "split_sha": None,
                     "verdict": "HARNESS-EXC", "ndiff": None, "nins": None, "note": repr(e)[:200]}]
        done[0] += 1
        if done[0] % 25 == 0:
            say("  %d/%d judged (%.0fs)" % (done[0], len(items), time.time() - t0))
        return rows

    with ThreadPoolExecutor(max_workers=a.jobs) as ex:
        for rows in ex.map(one, items):
            all_rows.extend(rows)
    with open(LEDGER, "a") as f:
        for r in all_rows:
            f.write(json.dumps(r, default=str) + "\n")

    # ---- per-item final verdict (best candidate) ----
    final = {}
    for r in all_rows:
        k = (r["binary"], r["fn"])
        if k not in final or _rank(r) < _rank(final[k]):
            final[k] = r
    vc = collections.Counter(r["verdict"] for r in final.values())
    via = collections.Counter(r.get("via") for r in final.values() if r["verdict"] == "STAGED")
    n_staged = vc.get("STAGED", 0)
    diff_small = sum(1 for r in final.values() if r["verdict"] == "DIFF" and (r.get("ndiff") or 99) <= 2)
    say("judged %d item(s) in %.0fs: %s" % (len(final), time.time() - t0,
                                             "  ".join("%s=%d" % kv for kv in sorted(vc.items()))))
    say("staged %d/%d (%.1f%%) — via %s; DIFF within 2 ins (grinder food): %d"
        % (n_staged, len(final), 100.0 * n_staged / max(1, len(final)), dict(via), diff_small))
    if n_staged < 0.05 * len(final):
        say("FALSIFIER TRIPPED: <5%% of the stock survived intake to staging — the ledger stock is stale "
            "beyond deterministic recovery; the demoted closeness numbers are the deliverable")

    # ---- honest demotion: the stored closeness was stale; record the current one ----
    if not a.no_demote:
        n_dem = 0
        for r in final.values():
            if r["verdict"] in ("DIFF", "CC1", "CPP", "SYMBOL-MISMATCH", "NEEDS-TU-EDIT"):
                # TU-BROKEN is deliberately absent: a tree condition must not demote the draft
                if r["verdict"] == "DIFF" and r.get("ndiff") == r.get("stored_closeness"):
                    continue
                backlog.append_record({
                    "name": r["fn"], "binary": r["binary"], "nins": r.get("nins"),
                    "status": "near" if r["verdict"] == "DIFF" else "failed",
                    "closeness": r.get("ndiff") if r["verdict"] == "DIFF" else None,
                    "where_stuck": "resolver %s (real-TU rtu_match, %s): %s" % (r["verdict"], a.run_id, r.get("note", "")),
                    "best_draft": r.get("draft"), "source": "resolver"})
                n_dem += 1
        say("demoted %d item(s) with their CURRENT closeness into %s" % (n_dem, backlog.JSONL))

    summary = {"run": a.run_id, "intake_backlog_rows": bl_rows, "intake_backlog_qual": bl_qual,
               "intake_reject_rows": rj_rows, "intake_reject_qual": rj_qual, "items": len(final),
               "dropped": dict(counts), "verdicts": dict(vc), "staged": n_staged, "via": dict(via),
               "elapsed_s": round(time.time() - t0)}

    # ---- gate ----
    if n_staged and not a.no_gate:
        banked = gate_and_commit(a.stage, a.gate_jobs, n_staged)
        if banked is not None:
            with open(LEDGER, "a") as f:
                for r in final.values():
                    if r["verdict"] == "STAGED":
                        f.write(json.dumps(dict(r, ts=time.strftime("%Y-%m-%d %H:%M:%S"),
                                                verdict=("BANKED" if (r["binary"], r["fn"]) in banked else "GATE-REJECTED")),
                                           default=str) + "\n")
            summary["banked"] = len(banked)
            say("RESULT: banked %d of %d staged, of %d judged, of %d nominated (INCLUDE_ASM invariant)"
                % (len(banked), n_staged, len(final), len(set(bl) | set(rj))))
    elif n_staged:
        say("staged %d draft(s) in %s — gate with: flock .run/auto/draw.lock %s tools/sweep_parallel.py --drafts %s -j %d"
            % (n_staged, a.stage, PY, a.stage, a.gate_jobs))
    json.dump(summary, open(os.path.join(RUN, "last_summary.json"), "w"), indent=1)
    return 0


if __name__ == "__main__":
    sys.exit(main())
