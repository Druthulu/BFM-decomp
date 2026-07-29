#!/usr/bin/env python3
"""autopsy.py — the permuter-failure autopsy: mine the search-closer's FAILURES (Phase-29 Task-13).

docs/hindsight-study.md §7. Our flywheel (R16) has always evolved the offline tooling REACTIVELY
FROM SUCCESSES: a human or an LLM cracks a function, we distil the idiom into the cookbook and the
permuter weights. The permuter's FAILURES — every near-miss it plateaued on — are a larger and
completely unused signal. This tool turns that log into a corpus, classifies it deterministically,
and routes each cluster to one of:

  missing-transform  the byte-match IS reachable by local mutation but the permuter's mutation set
                     never tried the needed move -> extend permuter_weights. A PERMANENT offline
                     win: that whole class now closes with no LLM. The highest-value bucket.
  mis-classified     the recorded class is wrong, so the search was directed at the wrong levers
                     -> fix the routing (free).
  seed-structural    the C STRUCTURE is wrong; local mutation cannot introduce it -> one LLM seed
                     rewrite, then hand back to the permuter. The LLM spent once, minimally.
  genuine-wall       compiler-internal at this tier -> file WITH A REASON and an expiry (R35: the
                     verdict dies when the gate or the model tier changes). Never a silent give-up.

WHY A COLLECT STEP EXISTS AT ALL. Task-12 plumbed structured-residual telemetry into the backlog,
but telemetry only fills records written AFTER it landed: 1 of 6,169 records carries a `residual`
and 0 carry `passes_tried`. Meanwhile 1,752 open near-misses have their best draft ON DISK and
their target .s ON DISK, so the residual is not missing — it is one second of CPU away, and
recomputing it is strictly better than trusting a stored one (uncapped, current toolchain, current
tree). `collect` recomputes the whole corpus through the EXISTING validated compile path
(tools/match_one.py, R33 — never a second copy of the pipeline).

THE TWO INPUTS THAT MUST BE DERIVED, NOT GUESSED — both are silent-artefact generators:
  * the asm subdir  — an overlay has up to 14 TUs; the wrong one scores a draft against a
                      DIFFERENT function's asm (Phase 26-A).
  * the -O0 flag    — an -O0 TU's target bytes are -O0; scoring its draft at -O2 mismatches
                      everywhere no matter how correct the C is (§53/§54, Task-1's phantom "~3%").
Both come from corpus.py: the stub's self-describing INCLUDE_ASM line, and the Makefile's own -O0
rules. A record whose stub cannot be found is REPORTED, never silently dropped (R32) — a skipped
target produces silence, not an error, which is how 91.6% of remaining gain once went invisible.

  tools/autopsy.py collect [--limit N] [--sample N] [-j 12]   -> .run/autopsy/residuals.jsonl
  tools/autopsy.py report  [--top N]                          -> docs/autopsy.md + stdout
"""
import argparse
import collections
import json
import os
import random
import subprocess
import sys
from concurrent.futures import ThreadPoolExecutor

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import backlog
import corpus
import residual_class

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
PY = ".venv/bin/python"
OUT = ".run/autopsy/residuals.jsonl"
MD = "docs/autopsy.md"
DEFAULT_BINARY = "ov_SC01_077"          # the legacy-record convention (backlog.load_best)


# --------------------------------------------------------------------------------------------
# collect
# --------------------------------------------------------------------------------------------
def _targets():
    """Open backlog near-misses with a draft on disk, plus the reason any record is excluded.

    Returns (targets, excluded) where excluded is a Counter — every input is accounted for, so a
    shrinking corpus can never be mistaken for a shrinking frontier (R32)."""
    todo, skip = [], collections.Counter()
    for r in backlog.load_best():
        name, draft = r.get("name"), r.get("best_draft")
        if not name:
            skip["no name"] += 1
            continue
        if not draft:
            skip["no saved draft"] += 1
            continue
        if not os.path.exists(os.path.join(REPO, draft)):
            skip["draft path gone"] += 1
            continue
        todo.append(r)
    return todo, skip


def _resolve(rec):
    """(asm_dir, o0, src_path) for a record, DERIVED — or (None, None, reason)."""
    binary = rec.get("binary") or DEFAULT_BINARY
    try:
        st = corpus.stubs(binary)
    except corpus.CorpusError as e:
        return None, None, "corpus error (%s): %s" % (binary, str(e).split("\n")[0][:80])
    hit = next((s for s in st.values() if s.symbol == rec["name"]), None)
    if hit is None:
        return None, None, "not a live stub in %s" % binary
    return hit.asm_dir, corpus.is_o0(hit.path), hit.path


def _one(rec):
    """Recompile one draft through match_one --json and return an enriched autopsy row."""
    name = rec["name"]
    binary = rec.get("binary") or DEFAULT_BINARY
    asm, o0, why = _resolve(rec)
    row = {"name": name, "addr": rec.get("addr"), "binary": binary,
           "reach": rec.get("reach"), "nins_logged": rec.get("nins"),
           "closeness_logged": rec.get("closeness"), "klass_logged": rec.get("klass"),
           "where_logged": rec.get("where_stuck"), "source": rec.get("source"),
           "draft": rec.get("best_draft")}
    if asm is None:
        row.update({"status": "unresolved", "note": why})
        return row
    row.update({"asm_dir": asm, "o0": bool(o0), "src": why})
    cmd = [PY, "tools/match_one.py", name, "--c", rec["best_draft"], "--asm-subdir", asm, "--json"]
    if o0:
        cmd.append("--o0")
    try:
        p = subprocess.run(cmd, capture_output=True, text=True, cwd=REPO, timeout=180)
    except subprocess.TimeoutExpired:
        row.update({"status": "timeout"})
        return row
    lines = [ln for ln in p.stdout.strip().splitlines() if ln.strip()]
    try:
        j = json.loads(lines[-1])
    except Exception:
        # a compile failure (CPP/CC1/MASPSX/AS FAIL) is itself a CLASS — the draft does not build
        # in isolation, which is plumbing, not codegen. Keep the reason; never drop the row.
        row.update({"status": "nobuild",
                    "note": (lines[0] if lines else (p.stderr.strip().splitlines() or ["?"])[0])[:120]})
        return row
    v = j.get("verdict") or {}
    row.update({"status": j.get("status"), "closeness": j.get("closeness"), "nins": j.get("nins"),
                "klass": v.get("klass"), "bucket": v.get("bucket"), "profile": v.get("profile"),
                "sig": v.get("sig"), "detail": v.get("detail"),
                "disagree": v.get("closeness_disagree"), "residual": j.get("residual")})
    return row


def collect(limit=None, sample=None, jobs=12):
    todo, skip = _targets()
    if sample:
        random.seed(1729)                       # fixed seed: a re-run samples the SAME functions
        todo = random.sample(todo, min(sample, len(todo)))
    if limit:
        todo = todo[:limit]
    print("autopsy collect: %d target(s)%s; excluded %s"
          % (len(todo), " (sampled)" if sample else "", dict(skip) or "{}"), flush=True)
    rows, done = [], 0
    with ThreadPoolExecutor(max_workers=jobs) as ex:
        for row in ex.map(_one, todo):
            rows.append(row)
            done += 1
            if done % 100 == 0:
                print("  ... %d/%d" % (done, len(todo)), flush=True)
    os.makedirs(os.path.join(REPO, os.path.dirname(OUT)), exist_ok=True)
    with open(os.path.join(REPO, OUT), "w") as f:
        for r in rows:
            f.write(json.dumps(r) + "\n")
    # COVERAGE + the second-oracle cross-check, both loud (R32/R34)
    st = collections.Counter(r.get("status") for r in rows)
    dis = [r for r in rows if r.get("disagree")]
    err = [r for r in rows if r.get("klass") == "ERROR"]
    print("\nwrote %s  (%d rows)" % (OUT, len(rows)))
    print("status:", dict(st))
    if len(rows) != len(todo):
        raise SystemExit("COVERAGE DEFECT: %d targets in, %d rows out" % (len(todo), len(rows)))
    if dis:
        raise SystemExit("ORACLE DISAGREEMENT on %d row(s): residual_class closeness != "
                         "structured_diff closeness. Fix before trusting any verdict.\n  %s"
                         % (len(dis), ", ".join(r["name"] for r in dis[:8])))
    if err:
        raise SystemExit("CLASSIFIER ERROR on %d row(s): %s"
                         % (len(err), err[0].get("detail", {}).get("error")))
    print("cross-check: closeness agrees with masked_diff.structured_diff on all %d built rows; "
          "0 classifier errors." % sum(1 for r in rows if r.get("klass")))
    return rows


# --------------------------------------------------------------------------------------------
# report
# --------------------------------------------------------------------------------------------
def _rows():
    p = os.path.join(REPO, OUT)
    if not os.path.exists(p):
        raise SystemExit("no %s — run: tools/autopsy.py collect" % OUT)
    return [json.loads(l) for l in open(p) if l.strip()]


def verdicts():
    """{fn_name: row} for the collected corpus, or {} if it has not been collected.

    The consumer-facing accessor (tools/grinder.py). Returns {} rather than raising so a missing
    corpus degrades to the previous undirected behaviour instead of breaking the daemon — but the
    caller must SAY which mode it is in (R32: a filter that silently does nothing is the defect).

    THE ROUTE IS RE-DERIVED HERE, NEVER READ FROM THE FILE (R33, Phase 29 T54). `klass` is the
    measurement and is trusted; `profile`/`bucket` are a policy lookup over it, and a stored lookup
    output makes a weeks-old file authoritative for a decision `residual_class._ROUTE` owns — a
    route correction would be inert until someone re-ran the whole collect, and the stale row would
    silently out-vote the live table. `route_for` reproduces the stored routes exactly under an
    unchanged table (verified 1610/1610), so this is a no-op except where the table has since been
    corrected — which is precisely when it must not be a no-op."""
    p = os.path.join(REPO, OUT)
    if not os.path.exists(p):
        return {}
    out = {}
    for line in open(p):
        if line.strip():
            r = json.loads(line)
            if r.get("name") and r.get("klass"):
                r["profile"], r["bucket"] = residual_class.route_for(r["klass"], r.get("detail"))
                out[r["name"]] = r
    return out


def report(top=25):
    rows = _rows()
    built = [r for r in rows if r.get("klass")]
    by_bucket = collections.Counter(r["bucket"] for r in built)
    by_klass = collections.Counter(r["klass"] for r in built)
    by_status = collections.Counter(r.get("status") for r in rows)

    # weight by REACH: a class that blocks a reach-138 core is worth ~138 members
    reach_w = collections.Counter()
    for r in built:
        reach_w[r["klass"]] += (r.get("reach") or 1)

    # the SECOND ORACLE (R34): where the deterministic verdict disagrees with the human/LLM label
    # a wave agent typed. Neither is authoritative — the DISAGREEMENT is the finding, and it is
    # precisely the autopsy's `mis-classified` bucket.
    agree, disagree = 0, []
    for r in built:
        kl = (r.get("klass_logged") or "").strip()
        if not kl or kl.upper() in ("WAVE", "GIANT", "STUB", "OTHER", "PINS", "STRUCT"):
            continue                                    # generic tags carry no class claim
        want = residual_class._ROUTE.get(r["klass"], (None, None))[0]
        import permuter_weights
        got = permuter_weights.classify(kl, r.get("where_logged") or "")
        if want and got and want == got:
            agree += 1
        elif want and got:
            disagree.append((r["name"], kl, got, r["klass"], want))

    clusters = collections.Counter(r["sig"] for r in built)

    L = []
    L.append("# Autopsy — the permuter's failures, classified\n")
    L.append("> Generated by `tools/autopsy.py report` from `.run/autopsy/residuals.jsonl` "
             "(built by `collect`, which recompiles every open backlog draft through "
             "`tools/match_one.py` and classifies the FULL residual with `tools/residual_class.py`).\n")
    L.append("> A verdict here is a **candidate**, never a bank: the whole-binary byte-gate "
             "remains the sole arbiter (G3/P9).\n")
    L.append("**Corpus:** %d record(s) · %d classified · status %s\n"
             % (len(rows), len(built), dict(by_status)))

    L.append("\n## Buckets — what tool each failure actually wants\n")
    L.append("| bucket | fns | reach-weighted | meaning |")
    L.append("|--------|----:|---------------:|---------|")
    MEAN = {"permuter": "local mutation CAN reach it — permuter fuel (a plateau here is a "
                        "**missing-transform** candidate)",
            "structural": "local mutation CANNOT introduce it — wants a C-level idiom, not CPU",
            "integration": "byte-correct standalone; blocked on plumbing (§58/§59 reconcile ladder)",
            "redraft": "the stored draft is NOT this function — un-attempted work misfiled as a "
                       "near-miss; route to a fresh crack, not to a wall",
            "unknown": "the residue the LLM tier is for"}
    for b, n in by_bucket.most_common():
        rw = sum(r.get("reach") or 1 for r in built if r["bucket"] == b)
        L.append("| %s | %d | %d | %s |" % (b, n, rw, MEAN.get(b, "")))

    L.append("\n## Classes\n")
    L.append("| class | fns | reach-weighted | bucket | permuter profile |")
    L.append("|-------|----:|---------------:|--------|------------------|")
    for k, n in by_klass.most_common():
        prof, bucket = residual_class._ROUTE.get(k, (None, "?"))
        L.append("| %s | %d | %d | %s | %s |" % (k, n, reach_w[k], bucket, prof or "—"))

    L.append("\n## Top clusters (the batch-autopsy work items)\n")
    L.append("One representative per signature diagnoses the whole cluster — that is what makes "
             "the LLM pass a *batch* autopsy rather than N per-function reads.\n")
    L.append("| # | signature | fns | reach-weighted | example |")
    L.append("|--:|-----------|----:|---------------:|---------|")
    for i, (sg, n) in enumerate(clusters.most_common(top), 1):
        members = [r for r in built if r["sig"] == sg]
        rw = sum(r.get("reach") or 1 for r in members)
        ex = min(members, key=lambda r: (r.get("closeness") or 10**9))
        L.append("| %d | `%s` | %d | %d | %s (close=%s, %s ins) |"
                 % (i, sg, n, rw, ex["name"], ex.get("closeness"), ex.get("nins")))

    L.append("\n## Second oracle — deterministic verdict vs the recorded label\n")
    L.append("The recorded `klass` is what a wave agent typed months ago; the verdict is derived "
             "from today's bytes. Neither is authoritative — **the disagreement is the finding**, "
             "and it is exactly the `mis-classified` bucket (a wrongly-labelled residual sends the "
             "directed search at the wrong levers, so it plateaus and then reads as a wall).\n")
    L.append("- labelled records comparable: **%d** · agree **%d** · disagree **%d**\n"
             % (agree + len(disagree), agree, len(disagree)))
    if disagree:
        L.append("| fn | recorded label | label routes to | measured class | measured routes to |")
        L.append("|----|----------------|-----------------|----------------|--------------------|")
        for nm, kl, got, mk, want in disagree[:top]:
            L.append("| %s | `%s` | %s | %s | %s |" % (nm, kl, got, mk, want))

    open(os.path.join(REPO, MD), "w").write("\n".join(L) + "\n")

    print("\n== buckets ==")
    for b, n in by_bucket.most_common():
        print("  %-12s %5d fns  reach-weighted %7d   %s"
              % (b, n, sum(r.get("reach") or 1 for r in built if r["bucket"] == b), MEAN.get(b, "")))
    print("\n== classes ==")
    for k, n in by_klass.most_common():
        print("  %-18s %5d   reach-weighted %7d   -> %s / %s"
              % (k, n, reach_w[k], residual_class._ROUTE.get(k, (None, "?"))[1],
                 residual_class._ROUTE.get(k, (None, None))[0] or "—"))
    print("\n== top clusters ==")
    for sg, n in clusters.most_common(top):
        print("  %-34s %4d" % (sg, n))
    print("\n== second oracle ==")
    print("  labelled+comparable %d: agree %d, disagree %d" % (agree + len(disagree), agree, len(disagree)))
    for nm, kl, got, mk, want in disagree[:12]:
        print("    %-18s recorded %-16s -> %-9s | measured %-17s -> %s" % (nm, kl, got, mk, want))
    print("\nwrote %s" % MD)


def main():
    ap = argparse.ArgumentParser(description=__doc__,
                                 formatter_class=argparse.RawDescriptionHelpFormatter)
    sub = ap.add_subparsers(dest="cmd", required=True)
    c = sub.add_parser("collect")
    c.add_argument("--limit", type=int)
    c.add_argument("--sample", type=int, help="random SAMPLE (fixed seed) — probe before scaling")
    c.add_argument("-j", "--jobs", type=int, default=12)
    r = sub.add_parser("report")
    r.add_argument("--top", type=int, default=25)
    a = ap.parse_args()
    if a.cmd == "collect":
        collect(a.limit, a.sample, a.jobs)
    else:
        report(a.top)


if __name__ == "__main__":
    main()
