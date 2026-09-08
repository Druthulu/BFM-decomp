#!/usr/bin/env python3
"""burndown.py — Phase-29 Task-7/11: the burn-down + velocity tracker (the ROI-close instrument).

The Phase-29 milestone is NOT a checkbox count — it is "close when per-session yield floors out"
(the ROI-gated close Drew scoped at phase start). This tool makes that floor VISIBLE: each run it
snapshots the fleet's 3 headline metrics + the remaining substantial crack-frontier, appends the
snapshot to .run/burndown.jsonl, computes velocity vs the previous snapshot, and flags when recent
yield has dropped below the floor threshold.

INPUTS (read the CURRENT committed digests — regenerate them first for a fresh reading):
  - docs/progress.fleet.md   (via `make report` / `make tools-health`)  -> the 3 metrics
  - docs/family-hseq.md      (via `tools/family_hseq.py`)                -> remaining substantial frontier
Run order for a true reading:  make report && .venv/bin/python tools/family_hseq.py && tools/burndown.py

OUTPUT: a burn-down summary (current metrics, remaining frontier, velocity since last snapshot, and a
FLOOR verdict) + an appended snapshot in .run/burndown.jsonl (git HEAD keyed, so re-runs on the same
commit UPDATE rather than duplicate).

The whole-binary byte-gate remains the sole arbiter of a match (G3/P9); this only MEASURES progress.
"""
import json, os, re, sys, subprocess, argparse

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
LOG = os.path.join(REPO, "docs", "burndown.jsonl")  # tracked (committed) so velocity persists across sessions
FLEET = os.path.join(REPO, "docs", "progress.fleet.md")
HSEQ = os.path.join(REPO, "docs", "family-hseq.md")


def parse_fleet():
    """(instr_pct, distinct_pct, fn_pct) from progress.fleet.md — the authoritative digest."""
    txt = open(FLEET).read()
    def pct(label):
        m = re.search(rf"FLEET {label}[^\n]*?=\s*([0-9.]+)%", txt)
        return float(m.group(1)) if m else None
    return {
        "instr_pct": pct(r"instr-weighted"),
        "distinct_pct": pct(r"distinct-code"),
        "fn_pct": pct(r"fn-count byte-ident"),
    }


def parse_frontier():
    """(substantial_families, templatable_ins, matched_sib) from family-hseq.md."""
    txt = open(HSEQ).read()
    m = re.search(r"Substantial:\s*\*\*([\d,]+)\s*families\s*/\s*([\d,]+)\s*templatable ins\*\*,\s*(\d+)\s*with a matched sibling", txt)
    if not m:
        return {"substantial_families": None, "templatable_ins": None, "matched_sib": None}
    return {
        "substantial_families": int(m.group(1).replace(",", "")),
        "templatable_ins": int(m.group(2).replace(",", "")),
        "matched_sib": int(m.group(3)),
    }


def git_head():
    return subprocess.run(["git", "-C", REPO, "rev-parse", "--short", "HEAD"],
                          capture_output=True, text=True).stdout.strip() or "unknown"


def load_log():
    if not os.path.exists(LOG):
        return []
    return [json.loads(l) for l in open(LOG) if l.strip()]


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--label", default="", help="optional session label for this snapshot")
    ap.add_argument("--session-close", action="store_true",
                    help="mark this snapshot as a SESSION BOUNDARY. The floor verdict is computed "
                         "ONLY from these: the ROI criterion is per-SESSION yield, so averaging "
                         "mid-session snapshots silently drives the mean down and manufactures a "
                         "floor (byte-witnessed 2026-07-22: three mid-session snapshots of a +0.7pp "
                         "session read as mean +0.23 = 'AT THE FLOOR').")
    ap.add_argument("--floor-pp", type=float, default=0.3,
                    help="instr-pp/snapshot below which yield is 'at the floor' (default 0.3)")
    ap.add_argument("--no-append", action="store_true", help="report only; do not write the snapshot")
    a = ap.parse_args()

    fleet, front, head = parse_fleet(), parse_frontier(), git_head()
    if fleet["instr_pct"] is None:
        sys.exit("burndown: could not parse docs/progress.fleet.md — run `make report` first.")
    snap = {"head": head, "label": a.label, "session_close": bool(a.session_close), **fleet, **front}

    log = load_log()
    prev = next((s for s in reversed(log) if s.get("head") != head), None)  # last DIFFERENT commit

    # velocity vs the previous distinct-commit snapshot
    dv = {}
    if prev:
        for k in ("instr_pct", "distinct_pct", "fn_pct"):
            if snap.get(k) is not None and prev.get(k) is not None:
                dv[k] = round(snap[k] - prev[k], 2)

    # append/update (dedupe on HEAD so re-runs on the same commit overwrite)
    if not a.no_append:
        log = [s for s in log if s.get("head") != head] + [snap]
        os.makedirs(os.path.dirname(LOG), exist_ok=True)
        with open(LOG, "w") as f:
            for s in log:
                f.write(json.dumps(s) + "\n")

    # ---- report ----
    print("=" * 64)
    print(f"BURN-DOWN  (HEAD {head}{'  ' + a.label if a.label else ''})")
    print("=" * 64)
    print(f"  instr-weighted : {fleet['instr_pct']}%"
          + (f"   ({dv['instr_pct']:+.2f} pp since {prev['head']})" if "instr_pct" in dv else ""))
    print(f"  distinct-code  : {fleet['distinct_pct']}%"
          + (f"   ({dv['distinct_pct']:+.2f} pp)" if "distinct_pct" in dv else ""))
    print(f"  fn-count       : {fleet['fn_pct']}%"
          + (f"   ({dv['fn_pct']:+.2f} pp)" if "fn_pct" in dv else ""))
    print("-" * 64)
    if front["substantial_families"] is not None:
        crackable = front["substantial_families"] - (front["matched_sib"] or 0)
        print(f"  REMAINING substantial frontier: {front['substantial_families']} families "
              f"/ {front['templatable_ins']:,} templatable ins")
        print(f"    - {front['matched_sib']} matched-sibling (zero-crack sweep) + ~{crackable} needing a crack")
    print("-" * 64)

    # ---- floor verdict: mean instr-pp over the last N inter-commit deltas ----
    # GRANULARITY GUARD (2026-07-22). The phase's ROI criterion is "per-SESSION yield floors out",
    # so the deltas averaged here must be SESSION-to-SESSION. Mid-session snapshots are useful for
    # tracking but must NOT feed the verdict: three of them inside a single +0.7pp session average
    # to +0.23 and read as "AT THE FLOOR" — an artifact of how often someone ran the tool, not a
    # measurement of yield decay. Count only snapshots explicitly marked --session-close; older
    # records predate the flag, so treat a label containing "close" as one too.
    def _is_close(r):
        return bool(r.get("session_close")) or ("close" in (r.get("label") or "").lower())
    marks = [r for r in log if _is_close(r)]
    hist = []
    for i in range(1, len(marks)):
        a_, b_ = marks[i - 1], marks[i]
        if a_.get("head") != b_.get("head") and a_.get("instr_pct") and b_.get("instr_pct"):
            hist.append(round(b_["instr_pct"] - a_["instr_pct"], 2))
    if len(hist) >= 3:
        recent = hist[-3:]
        mean = sum(recent) / len(recent)
        verdict = "AT THE FLOOR — consider closing P29" if mean < a.floor_pp else "above floor — keep cracking"
        print(f"  velocity (last 3 snapshots, instr pp): {recent}  mean {mean:+.2f}")
        print(f"  FLOOR VERDICT (threshold {a.floor_pp} pp): {verdict}")
    else:
        print(f"  velocity: {len(hist)} SESSION-to-SESSION delta(s) logged — need >=3 for a floor "
              f"verdict ({len(marks)} session-close snapshot(s) on record).")
        print(f"  (seed more snapshots each session: `make report && tools/family_hseq.py && tools/burndown.py`)")
    print("=" * 64)


if __name__ == "__main__":
    main()
