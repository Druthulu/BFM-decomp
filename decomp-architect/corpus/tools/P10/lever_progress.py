#!/usr/bin/env python3
"""lever_progress.py — the lever-removal series: what the compiler-forcing constructs cost, and how they came off.

    tools/lever_progress.py --snapshot "T6 r1"      # append today's census totals as a milestone row (evidence, with HEAD)
    tools/lever_progress.py --render                # regenerate the generated block of docs/levers.md from the data
    tools/lever_progress.py --table                 # print both tables
    tools/lever_progress.py --check                 # is the last snapshot this tree's? (a stale series is a wrong chart)

WHY THIS EXISTS. The phase that takes the levers out is the only place the project ever counts them, and the count is worth
more than the phase: it is the post-100% chart, the story's spine, and the evidence behind the day-one kit's advice on
whether to prevent levers from the first bank or clean them up at the end. Numbers are DERIVED, never typed (R75).

TWO TABLES, TWO SOURCES:
  * MILESTONES — one appended row per census snapshot (`--snapshot`), because a census is a moment: it is not recoverable
    later. Each row carries the tree's HEAD and the census's own totals, so a reader can re-derive it from that commit.
  * THE CAMPAIGN — fully derived from `.run/P36/delever/ledger.jsonl` on every run: per batch label, the date, the rungs
    used, the bodies first judged, the sites REMOVED / REWRITTEN, and — scored as a TRANSITION against what that body's
    previous row left — the sites a later rung closed and the bodies it made lever-free. Rebuilt from scratch each render,
    so it cannot drift.
"""
import argparse
import collections
import json
import pathlib
import subprocess
import sys

REPO = pathlib.Path(__file__).resolve().parent.parent
sys.path.insert(0, str(REPO / "tools"))

CENSUS = REPO / ".run" / "P36" / "census" / "lever_census.json"
LEDGER = REPO / ".run" / "P36" / "delever" / "ledger.jsonl"
SERIES = REPO / "docs" / "lever-progress.tsv"
DOC = REPO / "docs" / "levers.md"
BEGIN = "<!-- BEGIN GENERATED: lever_progress.py -->"
END = "<!-- END GENERATED -->"
COLS = ["date", "milestone", "head", "sites_AB", "pins", "asm", "bodies_AB", "distinct_AB", "marked", "unmarked",
        "gte_levers", "per_tu_asm_macros", "class_C", "class_D", "class_E", "class_F", "class_G"]


def census():
    if not CENSUS.exists():
        sys.exit("lever_progress: no census — run tools/lever_census.py --sites -j 16")
    return json.loads(CENSUS.read_text())


def ledger():
    rows = []
    if LEDGER.exists():
        for l in LEDGER.read_text().splitlines():
            if l.strip():
                rows.append(json.loads(l))
    return rows


def snapshot_row(milestone):
    d = census()
    ab, cl = d["levers_AB"], d["classes"]
    return dict(date=d.get("generated", ""), milestone=milestone, head=d.get("head", ""),
                sites_AB=ab["sites"], pins=ab["pins"], asm=ab["asm"], bodies_AB=ab["bodies"],
                distinct_AB=ab["distinct_bodies"], marked=ab["marked"], unmarked=ab["unmarked"],
                gte_levers=d.get("gte_levers", {}).get("sites", 0),
                per_tu_asm_macros=d.get("per_tu_asm_macro_definitions", {}).get("total", 0),
                **{f"class_{k}": cl.get(k, {}).get("sites", 0) for k in "CDEFG"})


def read_series():
    if not SERIES.exists():
        return []
    lines = [l for l in SERIES.read_text().splitlines() if l.strip()]
    if not lines:
        return []
    head = lines[0].split("\t")
    return [dict(zip(head, l.split("\t"))) for l in lines[1:]]


def write_series(rows):
    SERIES.write_text("\t".join(COLS) + "\n" + "".join("\t".join(str(r.get(c, "")) for c in COLS) + "\n" for r in rows))


def campaign():
    """per batch label, derived from the ledger, as STATE TRANSITIONS — not as "the first row wins".

    A body is judged more than once on purpose: rung A/B settles it with some sites left NEEDED, and a later rung (R, D or
    an agent) comes back and closes those. Counting only a body's first row credits the whole campaign to T4 and reports
    "0 removed" for the rung that actually finished the job (rung R's first batch closed 134 bodies and read as nothing).
    So each row is scored against what that body's previous row left: `removed`/`rewritten` are the first pass's, and
    `closed_later` is the fall in the NEEDED count afterwards, with `made_free` counting the bodies that reached zero."""
    prev, per = {}, collections.OrderedDict()
    for r in ledger():
        lab = r.get("label") or "-"
        key = (r.get("tu"), r.get("fn"))
        ts = (r.get("ts") or "")[:10]
        e = per.setdefault(lab, dict(label=lab, date=ts, rungs=set(), bodies=0, removed=0, rewritten=0,
                                     closed_later=0, made_free=0, refused=0))
        if ts and (not e["date"] or ts < e["date"]):
            e["date"] = ts
        if r.get("rung"):
            e["rungs"].add(str(r["rung"]))
        sites = r.get("sites", [])
        now_needed = sum(1 for s in sites if s.get("verdict") == "NEEDED")
        was = prev.get(key)
        if was is None:
            e["bodies"] += 1
            e["removed"] += sum(1 for s in sites if s.get("verdict") == "REMOVED")
            e["rewritten"] += sum(1 for s in sites if s.get("verdict") == "REWRITTEN")
            e["refused"] += sum(1 for s in sites if s.get("verdict") == "REFUSED")
        else:
            e["closed_later"] += max(0, was - now_needed)
            if was > 0 and now_needed == 0:
                e["made_free"] += 1
        prev[key] = now_needed
    return list(per.values())


def md_tables():
    rows = read_series()
    out = [BEGIN, "", "### Milestones — the count, at each moment a census ran", "",
           "| date | milestone | pins | asm | **class A+B sites** | bodies | distinct | GTE levers | per-TU asm macros | C | D | E | F | G | HEAD |",
           "|---|---|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|---|"]
    for r in rows:
        out.append("| {date} | {milestone} | {pins} | {asm} | **{sites_AB}** | {bodies_AB} | {distinct_AB} | {gte_levers} | "
                   "{per_tu_asm_macros} | {class_C} | {class_D} | {class_E} | {class_F} | {class_G} | `{head}` |".format(**r))
    out += ["", "### The campaign — every batch, from the ledger (derived on every render)", "",
            "| batch | date | rungs | bodies first judged | sites removed | rewritten | sites closed later | bodies made lever-free |",
            "|---|---|---|---:|---:|---:|---:|---:|"]
    tot = dict(bodies=0, removed=0, rewritten=0, closed_later=0, made_free=0)
    for e in campaign():
        if not any(e[k] for k in tot):
            continue                                      # a bookkeeping batch (a scrub, a re-mark) moved no site
        out.append(f"| `{e['label']}` | {e['date']} | {','.join(sorted(e['rungs'])) or '-'} | {e['bodies']:,} | "
                   f"{e['removed']:,} | {e['rewritten']:,} | {e['closed_later']:,} | {e['made_free']:,} |")
        for k in tot:
            tot[k] += e[k]
    out.append(f"| **total** | | | **{tot['bodies']:,}** | **{tot['removed']:,}** | **{tot['rewritten']:,}** | "
               f"**{tot['closed_later']:,}** | **{tot['made_free']:,}** |")
    out += ["", f"*Generated by `tools/lever_progress.py --render` from `.run/P36/census/lever_census.json` "
                f"and `.run/P36/delever/ledger.jsonl`; the series lives in `docs/lever-progress.tsv` (R75: published "
                f"numbers are generated, never typed).*", "", END]
    return "\n".join(out)


def render():
    if not DOC.exists():
        sys.exit(f"lever_progress: {DOC.relative_to(REPO)} does not exist yet")
    t = DOC.read_text()
    if BEGIN not in t or END not in t:
        sys.exit(f"lever_progress: {DOC.relative_to(REPO)} has no generated block ({BEGIN} … {END})")
    pre, rest = t.split(BEGIN, 1)
    _, post = rest.split(END, 1)
    DOC.write_text(pre + md_tables() + post)
    print(f"lever_progress: rendered {len(read_series())} milestone row(s) + {len(campaign())} batch row(s) "
          f"into {DOC.relative_to(REPO)}")


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--snapshot", metavar="MILESTONE", help="append today's census totals as a milestone row")
    ap.add_argument("--render", action="store_true")
    ap.add_argument("--table", action="store_true")
    ap.add_argument("--check", action="store_true")
    a = ap.parse_args()
    if a.snapshot:
        rows = read_series()
        row = snapshot_row(a.snapshot)
        rows = [r for r in rows if not (r.get("milestone") == row["milestone"] and r.get("head") == row["head"])]
        rows.append(row)
        write_series(rows)
        print(f"lever_progress: {row['milestone']} — {row['sites_AB']:,} class A+B sites "
              f"({row['pins']:,} pins + {row['asm']:,} asm) in {row['bodies_AB']:,} bodies, "
              f"{row['unmarked']} unmarked, at {row['head']}")
    if a.render or a.snapshot:
        if DOC.exists():
            render()
    if a.table:
        print(md_tables())
    if a.check:
        rows, d = read_series(), census()
        if not rows:
            sys.exit("lever_progress --check: the series is empty (run --snapshot)")
        last = rows[-1]
        if last.get("head") != d.get("head") or int(last.get("sites_AB", -1)) != d["levers_AB"]["sites"]:
            sys.exit(f"lever_progress --check: the series' last row ({last.get('milestone')}, {last.get('sites_AB')} sites "
                     f"at {last.get('head')}) is not this tree ({d['levers_AB']['sites']} at {d.get('head')}) — "
                     f"run --snapshot after the census (R75)")
        print(f"lever_progress --check: OK — {len(rows)} milestone(s), last {last['milestone']} "
              f"({last['sites_AB']} class A+B sites)")
    return 0


if __name__ == "__main__":
    sys.exit(main())
