#!/usr/bin/env python3
"""worklist.py — Phase 22: the unified byte-weighted ranked worklist (the loop's decision spine).

Joins the automation fuel manifest (.run/fuel_manifest.json — every live INCLUDE_ASM stub of
the canonical harvest overlay ov_SC01_077, class-tagged + reach-recomputed) with the near-miss
backlog (.run/backlog.jsonl via backlog.load_best) into ONE honest table, ranked by
byte-weighted PROJECT gain and grouped by idiom class. This is Drew's "sort all remaining
functions by biggest gains to smallest, possible idiom groups" deliverable AND the decision
table the hand-grind loop consults each cycle.

Byte-weighted gain (the number the giants move — the decomp.dev-comparable metric is
instruction/byte-weighted, NOT function-count): a function with reach R and N instructions,
once matched and propagated x134, makes R*N instructions byte-identical across the fleet.
  gain_ins  = reach * nins          (== the manifest's `leverage`; fleet instructions gained)
  gain_bytes= gain_ins * 4          (PS1 instructions are 4 bytes)
  pct_rem   = gain_ins / sum(gain_ins over all live stubs)   (share of ALL remaining gain)
  cum_pct   = running total of pct_rem down the ranked list   (how few giants capture most of it)
The whole-binary byte-gate (harvest_verify) remains the sole arbiter (G3/P9); this only ranks.

Usage:
  .venv/bin/python tools/worklist.py [--refresh] [--top 40] [--manifest .run/fuel_manifest.json]
    --refresh : first re-run build_fuel_manifest.py + backlog.render() (one-command loop refresh)
Outputs (the only writes): docs/worklist.md (human) + .run/worklist.json (machine).
"""
import argparse, json, os, subprocess, sys

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, os.path.join(REPO, "tools"))
import backlog  # noqa: E402  (sibling tool; for load_best)

# idiom-class display order: hand-decomp queue (GIANT) first, then the wave/recovery pools.
CLASS_ORDER = ["GIANT", "STRUCT", "PINS", "WAVE", "O0", "O1", "STUB"]


def load_backlog_by_name():
    """name -> {status, closeness, where_stuck, best_draft, klass} for currently-open near-misses."""
    out = {}
    for r in backlog.load_best():
        nm = r.get("name")
        if nm:
            out[nm] = {"status": r.get("status"), "closeness": r.get("closeness"),
                       "where_stuck": r.get("where_stuck"), "best_draft": r.get("best_draft"),
                       "bklass": r.get("klass")}
    return out


def _close_str(c):
    return str(c) if isinstance(c, int) else ""


def _clip(s, n=110):
    s = (s or "").replace("|", "/").replace("\n", " ")
    return s if len(s) <= n else s[:n - 1] + "…"


def build_rows(manifest, bl):
    targets = manifest["targets"]
    total_gain = sum((t.get("reach") or 1) * (t.get("nins") or 0) for t in targets) or 1
    rows = []
    for t in targets:
        reach = t.get("reach") or 1
        nins = t.get("nins") or 0
        gain = reach * nins
        b = bl.get(t["name"], {})
        rows.append({
            "name": t["name"], "addr": t["addr"], "class": t.get("class"),
            "reach": reach, "nins": nins, "ncalls": t.get("ncalls"),
            "gain_ins": gain, "gain_bytes": gain * 4,
            "pct_rem": 100.0 * gain / total_gain,
            "cached": bool(t.get("cached")), "region": t.get("region"),
            "lever": t.get("lever"), "bucket": t.get("bucket"),
            "bl_status": b.get("status"), "closeness": b.get("closeness"),
            "where_stuck": b.get("where_stuck"), "best_draft": b.get("best_draft"),
        })
    rows.sort(key=lambda r: (r["gain_ins"], r["reach"], r["nins"]), reverse=True)
    cum = 0.0
    for r in rows:
        cum += r["pct_rem"]
        r["cum_pct"] = cum
    return rows, total_gain


def _table(rows, with_cum=True):
    head = "| # | name | class | reach | nins | gain_ins | %rem |" + (" cum% |" if with_cum else "") \
        + " cached | region | close | where it stuck | best draft |"
    sep = "|--:|------|-------|------:|-----:|---------:|-----:|" + ("-----:|" if with_cum else "") \
        + "--------|--------|------:|----------------|------------|"
    out = [head, sep]
    for i, r in enumerate(rows, 1):
        cum = f" {r['cum_pct']:.1f} |" if with_cum else ""
        out.append("| {} | {} | {} | {} | {} | {} | {:.2f} |{} {} | {} | {} | {} | {} |".format(
            i, r["name"], r["class"], r["reach"], r["nins"], r["gain_ins"], r["pct_rem"], cum,
            "Y" if r["cached"] else "n", r["region"] or "", _close_str(r["closeness"]),
            _clip(r["where_stuck"]),
            f"`{r['best_draft']}`" if r["best_draft"] else ""))
    return out


def render_md(rows, total_gain, manifest, top):
    n_over = manifest.get("n_overlays", 138)   # 138 since the P27 disc audit (was 134); the manifest always provides it
    by_class = {}
    for r in rows:
        d = by_class.setdefault(r["class"], {"n": 0, "gain": 0})
        d["n"] += 1
        d["gain"] += r["gain_ins"]
    L = []
    L.append("# Worklist — remaining functions ranked by byte-weighted project gain\n")
    L.append("> Generated by `tools/worklist.py` from `.run/fuel_manifest.json` + `.run/backlog.jsonl`. "
             "Ranked by **byte-weighted gain** `gain_ins = reach × nins` (fleet instructions made "
             "byte-identical once matched **and** propagated ×{0} — the decomp.dev-comparable metric "
             "the giants move, NOT function-count). `%rem` = share of ALL remaining gain; `cum%` = "
             "running total (shows how few giants capture most of it). `close` = backlog match_one "
             "mismatch count (lower = nearer; blank = not yet attempted). Byte-gate (harvest_verify) "
             "is the sole arbiter (G3/P9).\n".format(n_over))
    L.append(f"**Live stubs:** {len(rows)}  ·  **total remaining gain:** {total_gain:,} ins "
             f"({total_gain * 4:,} bytes ×-fleet)\n")
    # class summary, in display order
    L.append("## Idiom-class summary (the groups)\n")
    L.append("| class | count | gain_ins | % of remaining |")
    L.append("|-------|------:|---------:|---------------:|")
    seen = set()
    for c in CLASS_ORDER + sorted(set(by_class) - set(CLASS_ORDER)):
        if c in by_class and c not in seen:
            seen.add(c)
            d = by_class[c]
            L.append(f"| {c} | {d['n']} | {d['gain']:,} | {100.0 * d['gain'] / total_gain:.1f}% |")
    L.append("")
    # top-N overall
    L.append(f"## Top {top} remaining gains (all classes)\n")
    L += _table(rows[:top], with_cum=True)
    L.append("")
    # giants = the hand-decomp queue, called out explicitly
    giants = [r for r in rows if r["class"] == "GIANT"]
    if giants:
        gg = sum(r["gain_ins"] for r in giants)
        L.append(f"## GIANT hand-decomp queue — {len(giants)} fns, "
                 f"{100.0 * gg / total_gain:.1f}% of all remaining gain\n")
        L += _table(giants, with_cum=False)
        L.append("")
    # per-class groups (excluding GIANT, already shown)
    L.append("## Idiom-group tables\n")
    for c in CLASS_ORDER + sorted(set(by_class) - set(CLASS_ORDER)):
        if c == "GIANT" or c not in by_class:
            continue
        grp = [r for r in rows if r["class"] == c]
        gg = sum(r["gain_ins"] for r in grp)
        L.append(f"### {c} — {len(grp)} fns, {100.0 * gg / total_gain:.1f}% of remaining gain\n")
        L += _table(grp[:top], with_cum=False)
        if len(grp) > top:
            L.append(f"\n*(+{len(grp) - top} more {c} fns — see `.run/worklist.json`)*")
        L.append("")
    return "\n".join(L) + "\n"


def assert_partition(manifest, source="ov_SC01_077"):
    """R32 coverage assertion (Phase-27 T8, tooling-audit.md:1173): every live stub of the manifest's
    SOURCE overlay lives in exactly one worklist row. worklist's universe is ONE overlay (~263 stubs),
    NOT the fleet's 53k — so this asserts the manifest is a partition OF ov_SC01_077, and says so. A
    silent under-cover (a stub in no row) is the class the audit exists to catch; an over-cover (a row
    that is no longer a live stub) means the manifest is stale. Independently enumerates the live stubs
    from the INVARIANT (corpus.stubs = still-INCLUDE_ASM), never the manifest's own scan (R33)."""
    import corpus
    live = {s.symbol for s in corpus.stubs(source).values()}
    rows = {t["name"] for t in manifest["targets"]}
    missing = sorted(live - rows)      # live stub in NO worklist row -> invisible work
    stale = sorted(rows - live)        # worklist row that is no longer a live stub -> stale manifest
    dup = len(manifest["targets"]) - len({t["name"] for t in manifest["targets"]})
    ok = not missing and not stale and not dup
    print(f"worklist --assert-partition (source {source}): {len(live)} live stubs, {len(rows)} rows "
          f"-> {'PARTITION OK' if ok else 'FAIL'}")
    if missing:
        print(f"  [FAIL] {len(missing)} live stub(s) in NO row (invisible work): {missing[:8]}")
    if stale:
        print(f"  [FAIL] {len(stale)} row(s) not a live stub (stale manifest — --refresh): {stale[:8]}")
    if dup:
        print(f"  [FAIL] {dup} duplicate row name(s)")
    return 0 if ok else 1


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--manifest", default=".run/fuel_manifest.json")
    ap.add_argument("--top", type=int, default=40)
    ap.add_argument("--refresh", action="store_true",
                    help="first re-run build_fuel_manifest.py + backlog.render() (loop refresh)")
    ap.add_argument("--assert-partition", action="store_true",
                    help="R32: assert the manifest partitions its source overlay's live stubs, then exit")
    a = ap.parse_args()
    if a.refresh:
        subprocess.run([sys.executable, os.path.join(REPO, "tools/build_fuel_manifest.py")], check=True)
        backlog.render()
    manifest = json.load(open(os.path.join(REPO, a.manifest)))
    if getattr(a, "assert_partition", False):
        # The manifest key is `source_overlay`, NOT `source` (Phase-28 T7). Reading `source` meant the
        # `, "ov_SC01_077"` DEFAULT always fired — so the R32 partition assertion checked a hardcoded
        # binary regardless of what the manifest was actually about, and would print "PARTITION OK"
        # while validating the wrong binary. An assertion that silently targets a default is not an
        # assertion. Fail loudly if the key is truly absent rather than guess.
        src = manifest.get("source_overlay")
        if not src:
            sys.exit("worklist --assert-partition: manifest has no `source_overlay` key — cannot "
                     "know which binary to partition-check (refusing to guess a default, R32/R35).")
        sys.exit(assert_partition(manifest, src))
    bl = load_backlog_by_name()
    rows, total_gain = build_rows(manifest, bl)
    json.dump({"note": "Phase-22 ranked worklist; gain_ins = reach*nins (byte-weighted). "
                       "Byte-gate is the sole arbiter (G3/P9).",
               "total_remaining_gain_ins": total_gain, "n_stubs": len(rows), "rows": rows},
              open(os.path.join(REPO, ".run/worklist.json"), "w"), indent=1)
    md = render_md(rows, total_gain, manifest, a.top)
    open(os.path.join(REPO, "docs/worklist.md"), "w").write(md)
    giants = [r for r in rows if r["class"] == "GIANT"]
    gg = sum(r["gain_ins"] for r in giants)
    print(f"worklist -> docs/worklist.md + .run/worklist.json")
    print(f"  {len(rows)} live stubs | total remaining gain {total_gain:,} ins")
    print(f"  GIANT queue: {len(giants)} fns = {100.0 * gg / total_gain:.1f}% of remaining gain")
    print(f"  top fn: {rows[0]['name']} ({rows[0]['class']}, reach {rows[0]['reach']}, "
          f"{rows[0]['nins']} ins, {rows[0]['pct_rem']:.2f}% of remaining)")


if __name__ == "__main__":
    main()
