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


def gen3_series():
    """The post-100 % debts by date (the day's last row): levers = class A+B sites (docs/lever-progress.tsv, P36 →);
    casts = raw pointer-cast dereferences — the four-form census count when a row has it, else the one-form regex count
    (docs/readability-progress.tsv, P36 S102 →); decls = lying call declarations. Read by column NAME (the TSVs grow)."""
    out = {}
    lp = REPO / "docs" / "lever-progress.tsv"
    if lp.exists():
        lines = [l for l in lp.read_text().splitlines() if l.strip()]
        cols = lines[0].split("\t")
        for l in lines[1:]:
            v = dict(zip(cols, l.split("\t")))
            if v.get("date") and v.get("sites_AB", "").isdigit():
                out.setdefault(v["date"], {})["levers"] = int(v["sites_AB"])
    rp = REPO / "docs" / "readability-progress.tsv"
    if rp.exists():
        lines = [l for l in rp.read_text().splitlines() if l.strip()]
        cols = lines[0].split("\t")
        for l in lines[1:]:
            v = dict(zip(cols, l.split("\t")))
            if not v.get("date"):
                continue
            casts = v.get("deref_all") or v.get("raw_casts")
            if casts and casts.isdigit():
                out.setdefault(v["date"], {})["casts"] = int(casts)
                out[v["date"]]["casts_form"] = "four forms" if v.get("deref_all") else "one form"
            if v.get("narrow_decls", "").isdigit():
                out.setdefault(v["date"], {})["decls"] = int(v["narrow_decls"])
    return out


def build():
    fleet, _ = history("docs/progress.fleet.md", parse_fleet)
    mainr, _ = history("docs/progress.md", parse_main)
    g3 = gen3_series()
    commits = {}
    for ln in git("log", "--format=%cs", "main").splitlines():
        commits[ln] = commits.get(ln, 0) + 1
    pe = phase_ends()
    dates = sorted(set(fleet) | set(mainr) | set(g3))
    rows = []
    last_fleet = {}
    for date in dates:
        f = fleet.get(date) or last_fleet          # a Gen3-only day carries the fleet's standing numbers (100 % since P32)
        if fleet.get(date):
            last_fleet = fleet[date]
        m = mainr.get(date, {})
        g = g3.get(date, {})
        rows.append({"date": date, "commits": commits.get(date, 0), "phase_end": pe.get(date, []),
                     "binaries": f.get("binaries"), "fn": f.get("fn"), "instr": f.get("instr"), "distinct": f.get("distinct"),
                     "main": f.get("main"), "main_included": f.get("main_included"), "stubs": f.get("stubs"),
                     "main_real": m.get("real"), "main_stubs": m.get("stubs"), "main_matchable": m.get("matchable"),
                     "levers": g.get("levers"), "casts": g.get("casts"), "casts_form": g.get("casts_form"), "decls": g.get("decls")})
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
             "- **After 100 % (Gen3, Phase 35 →) the axes change:** the match metrics stay at 100.0 % and the story moves to the two",
             "  debts the readability phases pay down — **levers** (register pins + asm statements, `docs/lever-progress.tsv`, Phase 36 →)",
             "  and **raw casts** (pointer-cast dereferences, `docs/readability-progress.tsv`; the one-form regex count until the",
             "  Phase-37 census's four-form count takes over on 2026-09-12 — the step up on that day is the counting, not the code).",
             "  The chart's lower panel draws them.",
             "",
             "| Date | Commits | Phase closed (version) | Binaries | fn-count | instr-weighted | distinct code | main game code | Stubs | main REAL / matchable | levers | raw casts |",
             "|---|---:|---|---:|---:|---:|---:|---:|---:|---:|---:|---:|"]
    for r in rows:
        ph = ", ".join(f"P{p} (v{v})" for p, v in r["phase_end"]) or ""
        mr = f"{r['main_real']} / {r['main_matchable']}" if r["main_real"] is not None and r["main_matchable"] else "—"
        lv = f"{r['levers']:,}" if r.get("levers") is not None else "—"
        cs = f"{r['casts']:,}" if r.get("casts") is not None else "—"
        lines.append(f"| {r['date']} | {r['commits']} | {ph} | {r['binaries'] or '—'} | {pct(r['fn'])} | {pct(r['instr'])} | "
                     f"{pct(r['distinct'])} | {pct(r['main']) if r['main'] else '—'} | {r['stubs'] if r['stubs'] is not None else '—'} | {mr} | {lv} | {cs} |")
    lines += ["", f"{len(rows)} dated rows · phase ticks from the {sum(len(v) for v in phase_ends().values())} PhaseEnds · "
                  "the chart: `docs/story-timeline.svg`.", ""]
    return "\n".join(lines)


KIND_RULES = (("T1 census", "the census (T1)"), ("T4 ", "mechanical strip — rung A/B (T4)"), ("T5 ", "the GTE header (T5)"),
              ("T6 ", "recipes + permuter — rungs R/D (T6)"), ("S101 rung G", "the guided search — rung G (S101)"),
              ("S102", "agents, one per class + the call-arity class (S102)"), ("S103", "agents, TU batches + regen (S103)"),
              ("S104", "agents, TU batches (S104)"), ("S105", "agents, TU batches (S105)"), ("P36 close", "P36 close"), ("P37", "P37"))


def kind_of(label):
    for key, kind in KIND_RULES:
        if label.startswith(key) or (key in label and key.startswith("S1")):
            return kind
    return "other"


def lever_rows():
    """Every increment of the lever series in order: the Phase-36 log's own census lines for T1, the T4 strip batches and the T5 GTE
    batches (`THE PHASE'S NUMBER … N sites`, the instrument's words — the TSV began at T6), then every row of docs/lever-progress.tsv.
    Returns [dict(date, label, sites, kind)]."""
    out = []
    log = REPO / "phase-ends" / "logs" / "Phase36.md"
    if log.exists():
        text = log.read_text()
        m = re.search(r"THE PHASE'S NUMBER[^:]*: ([0-9,]+) sites", text)
        if m:
            out.append(dict(date="2026-09-09", label="T1 census (the instrument's first number)", sites=int(m.group(1).replace(",", "")), kind=kind_of("T1 census")))
        seen = set()
        for mm in re.finditer(r"- \*\*(2026-09-\d\d) — (T[45]) batch `([a-z_0-9]+)`\*\*[^\n]*?THE PHASE'S NUMBER \(pins \+ asm statements, GTE excluded\): ([0-9,]+) sites", text):
            if mm.group(3) in seen:
                continue
            seen.add(mm.group(3))
            out.append(dict(date=mm.group(1), label=f"{mm.group(2)} batch {mm.group(3)}", sites=int(mm.group(4).replace(",", "")), kind=kind_of(mm.group(2) + " ")))
    lp = REPO / "docs" / "lever-progress.tsv"
    if lp.exists():
        lines = [l for l in lp.read_text().splitlines() if l.strip()]
        cols = lines[0].split("\t")
        for l in lines[1:]:
            v = dict(zip(cols, l.split("\t")))
            if v.get("date") and v.get("sites_AB", "").isdigit():
                out.append(dict(date=v["date"], label=v["milestone"], sites=int(v["sites_AB"]), kind=kind_of(v["milestone"])))
    return out


def cast_rows():
    """The raw-cast series as two INSTRUMENTS, never joined: the one-form regex count (readability rows before the census) and the
    four-form census count (`deref_all`, 2026-09-12 →). [dict(date, label, value, form)]."""
    out = []
    rp = REPO / "docs" / "readability-progress.tsv"
    if rp.exists():
        lines = [l for l in rp.read_text().splitlines() if l.strip()]
        cols = lines[0].split("\t")
        for l in lines[1:]:
            v = dict(zip(cols, l.split("\t")))
            if not v.get("date"):
                continue
            if v.get("deref_all", "").isdigit():
                out.append(dict(date=v["date"], label=v.get("label", ""), value=int(v["deref_all"]), form="four forms"))
            elif v.get("raw_casts", "").isdigit():
                out.append(dict(date=v["date"], label=v.get("label", ""), value=int(v["raw_casts"]), form="one form"))
    return out


def render_svg(rows):
    W, H, L, R, T, B = 1000, 430, 60, 20, 30, 70
    g3 = [r for r in rows if r.get("levers") is not None or r.get("casts") is not None]
    H_TOTAL = H + (300 if (g3 or (REPO / "docs" / "lever-progress.tsv").exists()) else 0)
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
    out = [f'<svg xmlns="http://www.w3.org/2000/svg" width="{W}" height="{H_TOTAL}" viewBox="0 0 {W} {H_TOTAL}" font-family="sans-serif">',
           f'<rect width="{W}" height="{H_TOTAL}" fill="white"/>',
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
    lv = lever_rows()
    cs = cast_rows()
    if lv or cs:
        # the lower panel — EVERY increment of the lever series on an ordinal axis (one step per recorded batch/landing), the KIND of
        # step marked where it changes; the raw casts as two instruments (the one-form regex count, then the four-form census), each as
        # a share of its own first measurement — a redefinition is a new line, never a rise
        T2, B2 = H + 34, H_TOTAL - 44
        y2 = lambda p: T2 + (1 - p / 100.0) * (B2 - T2)
        n = max(len(lv), 2)
        x2 = lambda i: L + i / (n - 1) * (W - L - R)
        out.append(f'<text x="{W/2:.0f}" y="{H + 16}" text-anchor="middle" font-size="14" font-weight="bold">After 100 % — the Gen3 debts as a share of their first measurement (every lever increment; the two raw-cast instruments)</text>')
        for p in (0, 25, 50, 75, 100):
            out.append(f'<line x1="{L}" y1="{y2(p):.1f}" x2="{W-R}" y2="{y2(p):.1f}" stroke="#ddd"/>'
                       f'<text x="{L-6}" y="{y2(p)+4:.1f}" text-anchor="end" font-size="11" fill="#555">{p}%</text>')
        if lv:
            base = lv[0]["sites"] or 1
            path = " ".join(f"{x2(i):.1f},{y2(100.0 * r['sites'] / base):.1f}" for i, r in enumerate(lv))
            # the kind markers: a dashed vertical at the first row of each kind, its label staggered near the top
            k = 0
            last_kind = None
            for i, r in enumerate(lv):
                if r["kind"] != last_kind:
                    last_kind = r["kind"]
                    xx = x2(i)
                    yy = T2 + 10 + (k % 4) * 12
                    m_ = re.search(r"\(([^)]+)\)$", r["kind"])
                    lab = r["kind"] if xx < W - R - 130 else (m_.group(1) if m_ else r["kind"].split(" ")[0])
                    out.append(f'<line x1="{xx:.1f}" y1="{T2}" x2="{xx:.1f}" y2="{B2}" stroke="#d62728" stroke-dasharray="2,3" opacity="0.6"/>'
                               f'<text x="{xx + 3:.1f}" y="{yy}" font-size="9" fill="#a00">{lab}</text>')
                    k += 1
            # the date ticks where the day changes
            last_date = None
            for i, r in enumerate(lv):
                if r["date"] != last_date:
                    last_date = r["date"]
                    out.append(f'<line x1="{x2(i):.1f}" y1="{B2}" x2="{x2(i):.1f}" y2="{B2 + 6}" stroke="#888"/>'
                               f'<text x="{x2(i) + 2:.1f}" y="{B2 + 16}" font-size="9" fill="#333">{r["date"][5:]}</text>')
            out.append(f'<polyline fill="none" stroke="#d62728" stroke-width="2" points="{path}"/>')
            out.append(f'<text x="{x2(len(lv) - 1) - 4:.1f}" y="{y2(100.0 * lv[-1]["sites"] / base) - 6:.1f}" text-anchor="end" font-size="10" fill="#d62728">{lv[-1]["sites"]:,}</text>')
            out.append(f'<text x="{W - R - 10}" y="{y2(58):.1f}" text-anchor="end" font-size="12" fill="#d62728">register pins + asm statements (the lever series, {len(lv)} increments): {lv[0]["sites"]:,} → {lv[-1]["sites"]:,}</text>')
        if cs:
            # placed at the lever step of the same day (the day's last), each instrument its own line and base
            day_last = {}
            for i, r in enumerate(lv):
                day_last[r["date"]] = i
            def xc(date):
                if date in day_last:
                    return x2(day_last[date])
                later = [i for i, r in enumerate(lv) if r["date"] > date]
                return x2(later[0]) if later else x2(n - 1)
            for form, dash, yoff in (("one form", "5,4", y2(72)), ("four forms", "", y2(65))):
                pts = [r for r in cs if r["form"] == form]
                if not pts:
                    continue
                base_c = pts[0]["value"] or 1
                path = " ".join(f"{xc(r['date']):.1f},{y2(100.0 * r['value'] / base_c):.1f}" for r in pts)
                if len(pts) == 1:
                    xx = xc(pts[0]["date"])
                    path = f"{xx - 6:.1f},{y2(100.0):.1f} {xx + 6:.1f},{y2(100.0):.1f}"
                    out.append(f'<circle cx="{xx:.1f}" cy="{y2(100.0):.1f}" r="4" fill="#9467bd"/>')
                out.append(f'<polyline fill="none" stroke="#9467bd" stroke-width="2" stroke-dasharray="{dash}" points="{path}"/>')
                what = ("raw pointer-cast dereferences — the one-form regex count (until the census, 2026-09-12)" if form == "one form"
                        else "raw pointer-cast dereferences — the four-form census (2026-09-12 →; a new instrument, its own 100 %)")
                out.append(f'<text x="{W - R - 10}" y="{yoff:.1f}" text-anchor="end" font-size="12" fill="#9467bd">{what}: {pts[0]["value"]:,} → {pts[-1]["value"]:,}</text>')
    out.append(f'<text x="{W-R}" y="{H_TOTAL-4}" text-anchor="end" font-size="10" fill="#777">generated by tools/timeline.py — keyed by date</text>')
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
