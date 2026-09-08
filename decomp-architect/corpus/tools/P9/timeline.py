#!/usr/bin/env python3
"""timeline.py — the project's progress timeline from its own committed digests (P33 F1).

    tools/timeline.py            # writes docs/story-timeline.md + docs/story-timeline.svg; exit 1 if the last row
                                 # disagrees with docs/progress.json (the self-check)
    tools/timeline.py --check    # regenerate in memory and exit 1 if either committed file is stale

Sources (all in the repository, keyed by DATE — never by commit hash, which the public-flip rewrite changed):
  * every commit that touched docs/progress.fleet.md (the fleet digest, since 2026-06-16): the June single-metric
    format (`FLEET byte-identical : M / T = %`) and the post-2026-07-11 three-metric format (`fn-count byte-ident`,
    `instr-weighted`, `distinct-code(uniq)`, with `MAIN game-code weighted` separate until 2026-07-22 and included in
    the fleet denominators from then on — the step this timeline annotates);
  * every commit that touched docs/progress.md (the main-EXE report, since 2026-06-14) for the days before the
    fleet digest existed;
  * phase-ends/PhaseEnd_*.md headers (`**Date:** … **Project Version:** …`) for the phase ticks;
  * `git log --format=%cs main` for commits per day.
One row per date (the last digest of that day). The chart has three polylines (instruction-weighted, distinct code,
function count), phase ticks, and the 07-22 denominator step. No run date is written, so the outputs never churn.
"""
import argparse
import datetime as dt
import json
import pathlib
import re
import subprocess
import sys

REPO = pathlib.Path(__file__).resolve().parent.parent
OUT_MD = REPO / "docs" / "story-timeline.md"
OUT_SVG = REPO / "docs" / "story-timeline.svg"


def git(*args):
    return subprocess.run(["git", "-C", str(REPO)] + list(args), capture_output=True, text=True, check=True).stdout


def num_pair(line):
    m = re.search(r":\s*([\d,]+)\s*/\s*([\d,]+)\s*=", line)
    return (int(m.group(1).replace(",", "")), int(m.group(2).replace(",", ""))) if m else None


def parse_fleet(text):
    d = {}
    for ln in text.splitlines():
        if ln.startswith("FLEET byte-identical") or ln.startswith("FLEET fn-count byte-ident"):
            d["fn"] = num_pair(ln)
        elif ln.startswith("FLEET instr-weighted"):
            d["instr"] = num_pair(ln)
        elif ln.startswith("FLEET distinct-code"):
            d["distinct"] = num_pair(ln)
        elif ln.startswith("MAIN game-code weighted"):
            d["main"] = num_pair(ln)
            d["main_included"] = "INCLUDED" in ln
        elif ln.startswith("FLEET INCLUDE_ASM stubs"):
            m = re.search(r":\s*([\d,]+)", ln); d["stubs"] = int(m.group(1).replace(",", "")) if m else None
        elif ln.startswith("# ") and "binaries:" in ln:
            m = re.match(r"# (\d+) binaries", ln); d["binaries"] = int(m.group(1)) if m else None
    return d


def parse_main(text):
    d = {}
    for ln in text.splitlines():
        m = re.match(r"REAL substantive matches\s*:\s*(\d+)", ln)
        if m: d["real"] = int(m.group(1))
        m = re.match(r"INCLUDE_ASM stubs\s*:\s*(\d+)", ln)
        if m: d["stubs"] = int(m.group(1))
        m = re.match(r"matchable functions\s*:\s*(\d+)", ln)
        if m: d["matchable"] = int(m.group(1))
    return d


def history(path, parser):
    """{date: parsed dict of the LAST commit of that day touching path}, plus commits per date."""
    rows, per_day = {}, {}
    for ln in git("log", "--reverse", "--format=%H %cs", "main", "--", path).splitlines():
        h, date = ln.split()
        text = subprocess.run(["git", "-C", str(REPO), "show", f"{h}:{path}"], capture_output=True, text=True).stdout
        d = parser(text)
        if d:
            rows[date] = d                       # later commits of the same day overwrite → the day's last state
            per_day[date] = per_day.get(date, 0) + 1
    return rows, per_day


def phase_ends():
    out = {}
    for f in sorted((REPO / "phase-ends").glob("PhaseEnd_Phase*.md")):
        head = f.read_text(encoding="utf-8", errors="replace")[:2000]
        m = re.search(r"\*\*Date:\*\*\s*(\d{4}-\d{2}-\d{2}).*?\*\*Project Version:\*\*\s*([\d.]+)", head, re.S)
        if m:
            ph = f.stem.replace("PhaseEnd_Phase", "").replace("_", ".")
            out.setdefault(m.group(1), []).append((ph, m.group(2)))
    return out


def build():
    fleet, _ = history("docs/progress.fleet.md", parse_fleet)
    mainr, _ = history("docs/progress.md", parse_main)
    commits = {}
    for ln in git("log", "--format=%cs", "main").splitlines():
        commits[ln] = commits.get(ln, 0) + 1
    pe = phase_ends()
    dates = sorted(set(fleet) | set(mainr))
    rows = []
    for date in dates:
        f = fleet.get(date, {})
        m = mainr.get(date, {})
        rows.append({"date": date, "commits": commits.get(date, 0), "phase_end": pe.get(date, []),
                     "binaries": f.get("binaries"), "fn": f.get("fn"), "instr": f.get("instr"), "distinct": f.get("distinct"),
                     "main": f.get("main"), "main_included": f.get("main_included"), "stubs": f.get("stubs"),
                     "main_real": m.get("real"), "main_stubs": m.get("stubs"), "main_matchable": m.get("matchable")})
    return rows


def pct(p):
    return f"{100.0 * p[0] / p[1]:.1f}%" if p and p[1] else "—"


def render_md(rows):
    first_three = next((r["date"] for r in rows if r["instr"]), None)
    step = next((r["date"] for r in rows if r["main_included"]), None)
    si = next((i for i, r in enumerate(rows) if r["main_included"]), None)
    if si and si > 0 and rows[si - 1]["instr"] and rows[si]["instr"]:
        a, b = rows[si - 1], rows[si]
        step_note = (f"instruction-weighted {pct(a['instr'])} on {a['date']} → {pct(b['instr'])} on {b['date']}, distinct code "
                     f"{pct(a['distinct'])} → {pct(b['distinct'])} — the larger denominator was absorbed by that day's banking "
                     f"({b['commits']} commits), so the curves are continuous rather than stepped")
    else:
        step_note = "(no adjacent rows to compare)"
    lines = ["# The progress timeline — every day the digests changed, from the repository's own committed reports",
             "",
             "> Generated by `tools/timeline.py` from `docs/progress.fleet.md` / `docs/progress.md` history and the PhaseEnd",
             "> headers — keyed by date, never by commit hash (the history was rewritten before publication). Regenerate,",
             "> never edit. One row per day (that day's last digest). The self-check asserts the last row equals",
             "> `docs/progress.json`.",
             "",
             f"- **Function count** (`fn`) is the only fleet metric until **{first_three}**, when the instruction-weighted and",
             "  distinct-code metrics were added (roadmap v1's metrics contract). Before the fleet digest existed (2026-06-14 →",
             "  06-15) only the main executable's report is available (`main REAL / matchable`).",
             f"- **{step}: the main executable enters the fleet denominators** (the roadmap §1 metrics contract): its game code",
             "  (then <1% matched) stopped being reported separately and joined the instruction-weighted and distinct-code",
             f"  totals. What the rows show across that step: {step_note}.",
             "- The **binaries** column is the fleet denominator: 136 → 140 (2026-07-15, the disc audit) → 213 (P30's module",
             "  onboarding) → 218 (P32, the last five payloads).",
             "",
             "| Date | Commits | Phase closed (version) | Binaries | fn-count | instr-weighted | distinct code | main game code | Stubs | main REAL / matchable |",
             "|---|---:|---|---:|---:|---:|---:|---:|---:|---:|"]
    for r in rows:
        ph = ", ".join(f"P{p} (v{v})" for p, v in r["phase_end"]) or ""
        mr = f"{r['main_real']} / {r['main_matchable']}" if r["main_real"] is not None and r["main_matchable"] else "—"
        lines.append(f"| {r['date']} | {r['commits']} | {ph} | {r['binaries'] or '—'} | {pct(r['fn'])} | {pct(r['instr'])} | "
                     f"{pct(r['distinct'])} | {pct(r['main']) if r['main'] else '—'} | {r['stubs'] if r['stubs'] is not None else '—'} | {mr} |")
    lines += ["", f"{len(rows)} dated rows · phase ticks from the {sum(len(v) for v in phase_ends().values())} PhaseEnds · "
                  "the chart: `docs/story-timeline.svg`.", ""]
    return "\n".join(lines)


def render_svg(rows):
    W, H, L, R, T, B = 1000, 430, 60, 20, 30, 70
    d0 = dt.date.fromisoformat(rows[0]["date"]); d1 = dt.date.fromisoformat(rows[-1]["date"])
    span = max((d1 - d0).days, 1)
    x = lambda date: L + (dt.date.fromisoformat(date) - d0).days / span * (W - L - R)
    y = lambda p: T + (1 - p / 100.0) * (H - T - B)
    def poly(key, color, label, yoff):
        pts = [(x(r["date"]), y(100.0 * r[key][0] / r[key][1])) for r in rows if r.get(key) and r[key][1]]
        if not pts:
            return ""
        path = " ".join(f"{px:.1f},{py:.1f}" for px, py in pts)
        lx, ly = pts[-1]
        return (f'<polyline fill="none" stroke="{color}" stroke-width="2" points="{path}"/>'
                f'<text x="{L + 10}" y="{yoff}" font-size="12" fill="{color}">{label}</text>')
    out = [f'<svg xmlns="http://www.w3.org/2000/svg" width="{W}" height="{H}" viewBox="0 0 {W} {H}" font-family="sans-serif">',
           f'<rect width="{W}" height="{H}" fill="white"/>',
           f'<text x="{W/2:.0f}" y="18" text-anchor="middle" font-size="14" font-weight="bold">BFM-decomp — matched percentage over time (from the committed digests)</text>']
    for p in (0, 25, 50, 75, 100):
        out.append(f'<line x1="{L}" y1="{y(p):.1f}" x2="{W-R}" y2="{y(p):.1f}" stroke="#ddd"/>'
                   f'<text x="{L-6}" y="{y(p)+4:.1f}" text-anchor="end" font-size="11" fill="#555">{p}%</text>')
    # month ticks
    m = dt.date(d0.year, d0.month, 1)
    while m <= d1:
        if m >= d0:
            out.append(f'<line x1="{x(m.isoformat()):.1f}" y1="{T}" x2="{x(m.isoformat()):.1f}" y2="{H-B}" stroke="#eee"/>'
                       f'<text x="{x(m.isoformat()):.1f}" y="{H-B+16}" text-anchor="middle" font-size="11" fill="#555">{m.strftime("%b %Y")}</text>')
        m = dt.date(m.year + (m.month == 12), (m.month % 12) + 1, 1)
    # phase ticks
    for r in rows:
        for ph, ver in r["phase_end"]:
            xx = x(r["date"])
            out.append(f'<line x1="{xx:.1f}" y1="{H-B}" x2="{xx:.1f}" y2="{H-B-8}" stroke="#888"/>')
            if ph in ("7", "15", "23", "26", "29", "30", "31", "32"):
                out.append(f'<text x="{xx:.1f}" y="{H-B+30}" text-anchor="middle" font-size="10" fill="#333">P{ph}</text>')
    step = next((r for r in rows if r["main_included"]), None)
    if step:
        xx = x(step["date"])
        out.append(f'<line x1="{xx:.1f}" y1="{T}" x2="{xx:.1f}" y2="{H-B}" stroke="#c33" stroke-dasharray="4,3"/>'
                   f'<text x="{xx+4:.1f}" y="{T+14}" font-size="11" fill="#c33">{step["date"]}: main enters the denominators</text>')
    out.append(poly("instr", "#1f77b4", "instruction-weighted (all binaries)", H - B - 8))
    out.append(poly("distinct", "#2ca02c", "distinct code (each body once)", H - B - 22))
    out.append(poly("fn", "#999", "function count", H - B - 36))
    out.append(f'<text x="{W-R}" y="{H-4}" text-anchor="end" font-size="10" fill="#777">generated by tools/timeline.py — keyed by date</text>')
    out.append("</svg>")
    return "\n".join(out) + "\n"


def selfcheck(rows):
    pj = REPO / "docs" / "progress.json"
    if not pj.exists():
        sys.exit("timeline: docs/progress.json missing (make report BINARY=main)")
    d = json.loads(pj.read_text())["fleet"]
    last = rows[-1]
    want = {"fn": (d["fn_count"]["matched"], d["fn_count"]["total"]),
            "instr": (d["instr_weighted"]["matched"], d["instr_weighted"]["total"]),
            "distinct": (d["distinct_code"]["matched"], d["distinct_code"]["total"]),
            "main": (d["main_game_code"]["matched"], d["main_game_code"]["total"])}
    bad = {k: (last.get(k), v) for k, v in want.items() if tuple(last.get(k) or ()) != v}
    if bad:
        sys.exit(f"timeline: the last row ({last['date']}) disagrees with docs/progress.json: {bad}")


def main(argv):
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--check", action="store_true")
    a = ap.parse_args(argv)
    rows = build()
    if not rows:
        sys.exit("timeline: no digest history found (R43)")
    selfcheck(rows)
    md, svg = render_md(rows), render_svg(rows)
    if a.check:
        stale = [p.name for p, t in ((OUT_MD, md), (OUT_SVG, svg)) if not p.exists() or p.read_text() != t]
        if stale:
            sys.exit(f"timeline --check: STALE {stale} — run tools/timeline.py")
        print(f"timeline --check: fresh ({len(rows)} rows)")
        return 0
    OUT_MD.write_text(md, encoding="utf-8"); OUT_SVG.write_text(svg, encoding="utf-8")
    print(f"timeline: {len(rows)} dated rows ({rows[0]['date']} → {rows[-1]['date']}), self-check vs progress.json OK -> {OUT_MD.name}, {OUT_SVG.name}")
    return 0


if __name__ == "__main__":
    sys.exit(main(sys.argv[1:]))
