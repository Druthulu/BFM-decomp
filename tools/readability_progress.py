#!/usr/bin/env python3
"""readability_progress — the Gen3 series: how honest and how readable the matched C is, over time.

WHY A SECOND SERIES. `docs/levers.md` (`tools/lever_progress.py`) counts LEVERS — the register pins and `asm`
statements this project inserted to force a byte match — and it is the chart of Phase 36's own goal. But Gen3 is about
the source being TRUE and readable, and the levers are only one of the ways it is not. Two more are measurable today and
neither is a lever:

  * LYING CALL DECLARATIONS. A file declares `extern void f(void);` while the function really takes an argument. It
    compiles, it matches, and it is false — and it was the largest single blocker in Phase 36's residue: six agents
    independently reached byte-identical output by restoring an argument the decompiler had dropped, and the register
    pin in each case existed only to fake the instruction the missing argument would have emitted.
  * RAW CAST DEREFERENCES. `*(u16 *)(p + 0x12)` where the original wrote a struct field. A struct is not recoverable
    from the binary — types are erased and a retail build carries no metadata — so this number falls only as the struct
    layers are inferred from base+offset+width evidence and applied.

Each row is dated and carries the commit it was taken at, so the chart is reproducible from the tree rather than typed
(R75: a published number is generated). Append a row with `--snapshot "<label>"`; `--check` asserts the last row is
this tree's.
"""
import argparse, datetime, json, pathlib, re, subprocess, sys

sys.path.insert(0, str(pathlib.Path(__file__).resolve().parent))
import argcheck

REPO = pathlib.Path(__file__).resolve().parent.parent
TSV = REPO / "docs" / "readability-progress.tsv"
DOC = REPO / "docs" / "readability.md"
SVG = REPO / "docs" / "readability-names.svg"
CAST = re.compile(r"\*\s*\(\s*(?:struct\s+|union\s+)?[A-Za-z_]\w*\s*\*+\s*\)\s*\(")
MEMBER = re.compile(r"->[A-Za-z_]\w*|\.[A-Za-z_]\w*\s*=")


def counts():
    defs = argcheck.definitions()
    rows_all = argcheck.scan(defs)
    # P37 T4 (2026-09-12): a byte-proven K&R site — `()` + `// K&R: n of m args` on its line, the calls pass another count and every
    # prototype form moved the bytes — is the original's calling convention, not a lie: counted APART (`kr_sites`), never in `narrow_decls`
    kr_rows = [r for r in rows_all if r.get("kr_marked")]
    cross_rows = [r for r in rows_all if r.get("cross_binary") and not r.get("kr_marked")]   # R48: the fleet disagrees, no own definition
    rows = [r for r in rows_all if not r.get("kr_marked") and not r.get("cross_binary")]
    casts = members = 0
    for f in (REPO / "src").glob("**/*.c"):
        t = f.read_text(errors="surrogateescape")
        casts += len(CAST.findall(t))
        members += len(MEMBER.findall(t))
    for f in (REPO / "src" / "shared").glob("**/*.h"):
        t = f.read_text(errors="surrogateescape")
        casts += len(CAST.findall(t))
        members += len(MEMBER.findall(t))
    pinned = [r for r in rows if r["argpin"]]
    out = dict(definitions=len(defs), narrow_decls=len(rows),
               callees=len({r["callee"] for r in rows}),
               kr_empty=sum(1 for r in rows if r["kind"] == "K&R-empty"),
               narrow=sum(1 for r in rows if r["kind"] == "narrow"),
               pinned_rows=len(pinned), pinned_bodies=len({(r["tu"], r["in_fn"]) for r in pinned}),
               raw_casts=casts, struct_members=members,
               kr_sites=len(kr_rows), kr_callees=len({r["callee"] for r in kr_rows}),
               cross_binary=len(cross_rows), cross_callees=len({r["callee"] for r in cross_rows}))
    # Phase 37 T1 (2026-09-12): the type census's columns — the four dereference forms (the CAST regex above sees one of them, over raw
    # text), the typed cast-member accesses (the MEMBER regex counts these as members — they are the rewrite's rung 1, not finished
    # members), the struct definitions and their duplicate classes, the struct map. A snapshot REFUSES a stale census (R43/R51).
    # P38 T10: the CURRENT phase's census — the newest .run/P<N>/census/type_census.json by numeric N (was: a P37 literal)
    cjs = sorted((int(m.group(1)), q) for q in REPO.glob(".run/P*/census/type_census.json")
                 if (m := re.fullmatch(r"P(\d+)", q.parent.parent.name)))
    head = subprocess.run(["git", "rev-parse", "HEAD"], cwd=REPO, capture_output=True, text=True).stdout.strip()
    if not cjs:
        sys.exit("readability_progress: no type census — run `tools/type_census.py -j 16` first (its columns are part of the row)")
    cj = cjs[-1][1]
    print(f"readability_progress: census {cj.relative_to(REPO)}", file=sys.stderr)
    ts = json.loads(cj.read_text())["summary"]
    # fresh = taken at HEAD, or over the same src/ tree (lever_census.src_stamp: path|size|mtime of every .c/.h) — a docs-only commit
    # after the census does not stale it
    import lever_census
    if not head.startswith(ts.get("head", "?")) and ts.get("src_stamp") != lever_census.src_stamp():
        sys.exit(f"readability_progress: the type census is STALE (census {ts.get('head')} vs HEAD {head[:9]}, src stamp differs) — rerun tools/type_census.py")
    c, d, sm = ts["casts"], ts["definitions"], ts["struct_map"]
    out.update(deref_all=c["deref_total"], form_P=c["by_form"].get("P", 0), form_I=c["by_form"].get("I", 0), form_X=c["by_form"].get("X", 0),
               form_M=c["by_form"].get("M", 0), addr_form=c["addr_form"], typed_cast_member=c["typed_cast_member"],
               struct_defs=d["total"], canon_defs=d["canon"], in_c_defs=d["in_c_file_scope"] + d["in_c_block_scope"],
               distinct_layouts=d["distinct_layouts"], dup_classes=d["dup_layout_classes"], dup_names=d["dup_layout_names"],
               map_types=sm["types"], map_pct=sm["explained_pct"])
    # P3.40 T12: `uncovered` = sum over P/I/X/M of residue_census.json by_form[f].uncovered — the cast gate's measure (raw sites with no
    # ledgered RESIDUAL(<cause>)), recorded beside the raw counts so green-by-ledger never reads as debt gone. Source: the residue census
    # beside this census, else the newest; used only when its sibling type_census.json is fresh (HEAD or src stamp) and not newer than
    # it — otherwise blank (no stale number)
    rj = cj.parent / "residue_census.json"
    if not rj.exists():
        rjs = sorted(REPO.glob(".run/P*/census/residue_census.json"), key=lambda q: (q.stat().st_mtime, str(q)))
        rj = rjs[-1] if rjs else None
    out["uncovered"] = ""
    if rj is not None and (rj.parent / "type_census.json").exists():
        rs = json.loads((rj.parent / "type_census.json").read_text())["summary"]
        fresh = head.startswith(rs.get("head", "?")) or rs.get("src_stamp") == lever_census.src_stamp()
        if fresh and rj.stat().st_mtime >= (rj.parent / "type_census.json").stat().st_mtime:
            bf = json.loads(rj.read_text())["by_form"]
            out["uncovered"] = sum(int(bf.get(f, {}).get("uncovered", 0)) for f in ("P", "I", "X", "M"))
        else:
            print(f"readability_progress: residue census {rj.relative_to(REPO)} is stale — `uncovered` left blank "
                  "(run tools/type_census.py --check-casts --residue)", file=sys.stderr)
    # P3.41 T13: return-type lies — a declaration whose return type differs from the definition's (argcheck's return rows, the census's
    # decls.return_lies); blank when the census predates the key
    rl = ts.get("decls", {}).get("return_lies")
    out["return_lie_fns"] = rl["functions"] if rl else ""
    out["return_lie_sites"] = rl["sites"] if rl else ""
    out.update(names_counts("HEAD"))
    return out


NAMES_COLS = [f"names_{k}_{c}" for k in ("fn", "data") for c in ("units", "cited", "guess", "other", "placeholder")]


def _git(*args):
    return subprocess.run(["git", *args], cwd=REPO, capture_output=True, text=True)


def names_counts(rev):
    """P3.44 T13: the names columns at git rev `rev` from docs/leverage.tsv (the units) and config/names.tsv (the tiers).
    Per unit: placeholder if named != yes (partial = some binary still uses the placeholder); else guess if the name starts
    `guess_`; else cited if the ledger has that name at tier cited; else other (named outside the ledger: SDK names).
    Blank (stderr says why) when the rev has no leverage.tsv, or names/symbols changed after leverage.tsv was regenerated."""
    blank = {k: "" for k in NAMES_COLS}
    lev = _git("show", f"{rev}:docs/leverage.tsv")
    if lev.returncode:
        print(f"readability_progress: no docs/leverage.tsv at {rev[:9]} — names columns blank", file=sys.stderr)
        return blank
    paths = ["config/names.tsv", "config/symbols*.txt"]
    last = _git("rev-list", "-1", rev, "--", "docs/leverage.tsv").stdout.strip()
    later = _git("rev-list", f"{last}..{rev}", "--", *paths).stdout.split()
    dirty = _git("status", "--porcelain", "--", *paths, "docs/leverage.tsv").stdout.strip() if rev == "HEAD" else ""
    if later or dirty:
        why = f"{len(later)} commit(s) after {last[:9]}" if later else "uncommitted edits"
        print(f"readability_progress: docs/leverage.tsv is stale at {rev[:9]} ({why} touch names/symbols — rerun "
              "tools/leverage_rank.py) — names columns blank", file=sys.stderr)
        return blank
    cited = set()
    hdr = None
    for ln in _git("show", f"{rev}:config/names.tsv").stdout.splitlines():
        if not ln.strip() or ln.startswith("#"):
            continue
        v = ln.split("\t")
        if hdr is None:
            hdr = {c: i for i, c in enumerate(v)}
            continue
        if v[hdr["tier"]] == "cited":
            cited.add(v[hdr["name"]])
    out = {k: 0 for k in NAMES_COLS}
    lines = lev.stdout.splitlines()
    h = {c: i for i, c in enumerate(lines[0].split("\t"))}
    for ln in lines[1:]:
        if not ln.strip():
            continue
        v = ln.split("\t")
        k = {"func": "fn", "data": "data"}[v[h["kind"]]]
        nm = v[h["name"]]
        tier = ("placeholder" if v[h["named"]] != "yes" else "guess" if nm.startswith("guess_")
                else "cited" if nm in cited else "other")
        out[f"names_{k}_units"] += 1
        out[f"names_{k}_{tier}"] += 1
    for k in ("fn", "data"):
        parts = sum(out[f"names_{k}_{c}"] for c in ("cited", "guess", "other", "placeholder"))
        if parts != out[f"names_{k}_units"]:
            sys.exit(f"readability_progress: names {k} at {rev[:9]}: tiers sum {parts} != units {out[f'names_{k}_units']}")
    return out


COLS = ["date", "label", "commit", "definitions", "narrow_decls", "callees", "kr_empty", "narrow", "pinned_rows", "pinned_bodies",
        "raw_casts", "struct_members",
        # P37 columns (appended 2026-09-12; older rows carry blanks — the renderer reads by name, never by position)
        "deref_all", "form_P", "form_I", "form_X", "form_M", "addr_form", "typed_cast_member", "struct_defs", "canon_defs", "in_c_defs",
        "distinct_layouts", "dup_classes", "dup_names", "map_types", "map_pct",
        # P37 T4 (2026-09-12): the byte-proven K&R sites, counted apart from the lies
        "kr_sites", "kr_callees", "cross_binary", "cross_callees",
        # P3.40 T12 (2026-11-06): the cast gate's uncovered sites, summed over the four forms (blank on older rows)
        "uncovered",
        # P3.41 T13 (2026-11-07): return-type lies, functions / call sites (blank on older rows)
        "return_lie_fns", "return_lie_sites",
        # P3.44 T13 (2026-11-13): names — units of docs/leverage.tsv by tier, functions then data (blank where leverage.tsv is absent or stale)
        *NAMES_COLS]
HEAD = "\t".join(COLS) + "\n"


def _rows():
    lines = [l for l in TSV.read_text().splitlines() if l.strip()]
    cols = lines[0].split("\t")
    rows = []
    for l in lines[1:]:
        vals = l.rstrip("\n").split("\t")
        rows.append({c: (vals[i] if i < len(vals) else "") for i, c in enumerate(cols)})
    return rows


def _esc(s):
    return str(s).replace("&", "&amp;").replace("<", "&lt;").replace(">", "&gt;")


def _svg_lines(path, title, panels):
    """Write a stacked-panel line graph. panels: [{"title", "subtitle", "xlabels": [str], "series": [(label, color, [num])]}];
    x = evenly spaced points (one per row), linear y from 0. Deterministic: same input, same bytes."""
    W, PH, L, R, T, B = 1000, 300, 70, 20, 50, 60
    out = [f'<svg xmlns="http://www.w3.org/2000/svg" width="{W}" height="{30 + PH * len(panels)}" '
           f'viewBox="0 0 {W} {30 + PH * len(panels)}" font-family="sans-serif">',
           f'<rect width="{W}" height="{30 + PH * len(panels)}" fill="white"/>',
           f'<text x="{W / 2:.0f}" y="20" text-anchor="middle" font-size="14" font-weight="bold">{_esc(title)}</text>']
    for pi, p in enumerate(panels):
        top = 30 + pi * PH
        n = len(p["xlabels"])
        x = lambda i: L + (W - L - R) * (0.5 if n == 1 else i / (n - 1))
        vmax = max([v for _, _, vs in p["series"] for v in vs] + [1])
        y = lambda v: top + T + (1 - v / vmax) * (PH - T - B)
        out.append(f'<text x="{L}" y="{top + 16}" font-size="13" font-weight="bold">{_esc(p["title"])}</text>'
                   f'<text x="{L}" y="{top + 32}" font-size="11" fill="#555">{_esc(p["subtitle"])}</text>')
        for q in range(5):
            v = vmax * q / 4
            out.append(f'<line x1="{L}" y1="{y(v):.1f}" x2="{W - R}" y2="{y(v):.1f}" stroke="#ddd"/>'
                       f'<text x="{L - 6}" y="{y(v) + 4:.1f}" text-anchor="end" font-size="11" fill="#555">{v:,.0f}</text>')
        for i, lab in enumerate(p["xlabels"]):
            out.append(f'<line x1="{x(i):.1f}" y1="{top + PH - B}" x2="{x(i):.1f}" y2="{top + PH - B + 5}" stroke="#888"/>'
                       f'<text x="{x(i):.1f}" y="{top + PH - B + 18}" text-anchor="middle" font-size="10" fill="#333">{_esc(lab)}</text>')
        for si, (lab, color, vs) in enumerate(p["series"]):
            pts = [(x(i), y(v)) for i, v in enumerate(vs)]
            out.append(f'<polyline fill="none" stroke="{color}" stroke-width="2" points="{" ".join(f"{a:.1f},{b:.1f}" for a, b in pts)}"/>')
            out += [f'<circle cx="{a:.1f}" cy="{b:.1f}" r="3" fill="{color}"/>' for a, b in pts]
            out.append(f'<text x="{W - R - 250}" y="{top + 16 + 14 * si}" font-size="12" fill="{color}">{_esc(lab)} ({vs[-1]:,})</text>')
    out.append("</svg>")
    path.write_text("\n".join(out) + "\n")


def render_names_svg(rows):
    rows = [r for r in rows if r.get("names_fn_units")]
    if not rows:
        return
    xl = [f'{r["date"]} {r["label"].split(":")[0]}' for r in rows]
    panels = []
    for k, what in (("fn", "function"), ("data", "data")):
        n = lambda c: [int(r[f"names_{k}_{c}"]) for r in rows]
        last = rows[-1]
        panels.append({"title": f"{what.capitalize()} units named",
                       "subtitle": f'{int(last[f"names_{k}_placeholder"]):,} of {int(last[f"names_{k}_units"]):,} {what} units '
                                   f'still placeholders (at {last["commit"][:9]})',
                       "xlabels": xl,
                       "series": [("cited", "#2ca02c", n("cited")), ("guess_", "#ff7f0e", n("guess")),
                                  ("other (outside the ledger)", "#1f77b4", n("other"))]})
    _svg_lines(SVG, "BFM-decomp — names in the matched C (from docs/readability-progress.tsv)", panels)


def render():
    rows = _rows()
    g = lambda r, k: r.get(k, "") or "—"
    out = ["# Readability of the matched C — the Gen3 series",
           "",
           "> **Generated by `tools/readability_progress.py --snapshot`; never typed (R75).** Companion to",
           "> `docs/levers.md`, which counts the compiler-forcing levers. This one counts the two things that are wrong",
           "> with the source even where no lever remains: call declarations that are FALSE, and memory read through raw",
           "> pointer casts where the original had a struct. From Phase 37 the row carries the type census's columns",
           "> (`tools/type_census.py`): all four dereference forms, the typed cast-member intermediate, the definitions and the map.",
           "",
           "| date | label | commit | lying declarations | of which `()` | of which `(void)` | in a pinned body | raw cast derefs (one form, raw text) | struct member reads | **raw derefs, four forms** | typed cast-member | struct defs (canonical / in .c) | layouts | duplicate classes / names | map types (% sites)  K&R sites (marked, apart) | cross-binary (apart) | return-type lies (functions / sites) |",
           "|---|---|---|---:|---:|---:|---:|---:|---:|---:|---:|---|---:|---|---|---:|---:|---|"]
    for r in rows:
        defs = f"{g(r,'struct_defs')} ({g(r,'canon_defs')} / {g(r,'in_c_defs')})" if r.get("struct_defs") else "—"
        dups = f"{g(r,'dup_classes')} / {g(r,'dup_names')}" if r.get("dup_classes") else "—"
        mp = f"{g(r,'map_types')} ({g(r,'map_pct')} %)" if r.get("map_types") else "—"
        rl = f"{g(r,'return_lie_fns')} / {g(r,'return_lie_sites')}" if r.get("return_lie_fns") else "—"
        out.append(f"| {g(r,'date')} | {g(r,'label')} | `{r.get('commit', '')[:9]}` | {g(r,'narrow_decls')} | {g(r,'kr_empty')} | {g(r,'narrow')} | {g(r,'pinned_rows')} | "
                   f"{g(r,'raw_casts')} | {g(r,'struct_members')} | **{g(r,'deref_all')}** | {g(r,'typed_cast_member')} | {defs} | {g(r,'distinct_layouts')} | {dups} | {mp} | {g(r,'kr_sites')} | {g(r,'cross_binary')} | {rl} |")
    out += ["",
            "**How to read it.** A *lying declaration* is a call site whose in-scope declaration names fewer parameters",
            "than the callee's own definition. It is not a style problem: on this processor an argument travels in a",
            "register, so a dropped argument removes an instruction, and Phase 36 found register pins inserted to fake",
            "exactly that instruction. *Raw cast derefs* is the struct debt — a struct cannot be recovered from the",
            "binary, only inferred from consistent base+offset+width evidence, so this figure falls as that work lands.",
            "A *return-type lie* is a declaration whose return type differs from the definition's; the calls still match",
            "because what a caller does with the return register is a caller byte fact (C0543), not the callee's type.",
            "",
            "## Names",
            "",
            "![Names in the matched C over time](readability-names.svg)",
            "",
            "| date | label | commit | function units | cited | `guess_` | other | placeholder | data units | cited | `guess_` | other | placeholder |",
            "|---|---|---|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|"]
    for r in rows:
        if r.get("names_fn_units"):
            out.append(f"| {g(r,'date')} | {g(r,'label')} | `{r.get('commit', '')[:9]}` | "
                       + " | ".join(g(r, f"names_{k}_{c}") for k in ("fn", "data")
                                    for c in ("units", "cited", "guess", "other", "placeholder")) + " |")
    out += ["",
            "**How to read the names columns.** The units come from `docs/leverage.tsv` (`docs/leverage.md`), which",
            "`tools/leverage_rank.py` regenerates after names land; a row whose commit has no `leverage.tsv`, or where",
            "`config/names.tsv` or a `config/symbols*.txt` changed after it was regenerated, leaves these columns blank.",
            "A *function unit* is one distinct function body (one `h_exact`) fleet-wide, or a raw function target with no",
            "signature row; a *data unit* is one (address space, address). A placeholder is per binary, so one unit may cover",
            "many binaries; `named partial` counts as *placeholder* (some binary still uses the placeholder name).",
            "Of the named units, *cited* have a `cited` row in `config/names.tsv`, *`guess_`* carry the `guess_` prefix",
            "(a ledgered guess), and *other* are named outside the ledger. At P3.44 every *other* name is a PsyQ SDK name of",
            "the linked library objects (defined in `build/psyq` or named by its `*_externals.ld`), which the citation gate",
            "does not ledger; the P3.42 row predates the ledger's rows, so its *other* also holds names cited later.",
            ""]
    DOC.write_text("\n".join(out) + "\n")
    render_names_svg(rows)


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--snapshot", metavar="LABEL")
    ap.add_argument("--check", action="store_true")
    ap.add_argument("--backfill-names", action="store_true",
                    help="fill the names columns of every row whose names cells are blank, computed at that row's commit; renders")
    a = ap.parse_args()
    head = subprocess.run(["git", "rev-parse", "HEAD"], cwd=REPO, capture_output=True, text=True).stdout.strip()
    if a.backfill_names:
        lines = TSV.read_text().splitlines()
        cols = lines[0].split("\t")
        new, filled = [], 0
        for l in lines[1:]:
            vals = l.split("\t")
            r = {c: (vals[i] if i < len(vals) else "") for i, c in enumerate(cols)}
            if l.strip() and not any(r.get(k) for k in NAMES_COLS):
                nc = names_counts(r["commit"])
                if any(str(v) for v in nc.values()):
                    vals += [""] * (len(COLS) - len(vals))
                    for k in NAMES_COLS:
                        vals[COLS.index(k)] = str(nc[k])
                    l, filled = "\t".join(vals), filled + 1
                    print(f"readability_progress: backfilled {r['label']!r} at {r['commit'][:9]}", file=sys.stderr)
            new.append(l)
        TSV.write_text(HEAD + "".join(l + "\n" for l in new))
        render()
        print(f"readability_progress --backfill-names: {filled} row(s) filled")
        return 0
    if a.check:
        if not TSV.exists():
            print("readability_progress --check: no series yet")
            return 1
        last = TSV.read_text().splitlines()[-1].split("\t")
        ok = last[2] == head
        print(f"readability_progress --check: {'OK' if ok else 'STALE'} — last row {last[1]!r} at {last[2][:9]}, "
              f"HEAD {head[:9]}")
        return 0 if ok else 1
    if not a.snapshot:
        print(__doc__)
        return 2
    c = counts()
    c.update(date=datetime.date.today().isoformat(), label=a.snapshot, commit=head)
    # the header row is rewritten to the current column list; older rows keep their positions (the new columns are appended)
    old = [l for l in TSV.read_text().splitlines()[1:] if l.strip()] if TSV.exists() else []
    TSV.write_text(HEAD + "".join(l + "\n" for l in old) + "\t".join(str(c.get(k, "")) for k in COLS) + "\n")
    render()
    print(f"readability_progress: {a.snapshot} — {c['narrow_decls']} lying declaration(s) over {c['callees']} callee(s) (+{c['kr_sites']} K&R sites, +{c['cross_binary']} cross-binary apart) "
          f"({c['kr_empty']} `()`, {c['narrow']} `(void)`), {c['pinned_rows']} in {c['pinned_bodies']} pinned bodies; "
          f"{c['raw_casts']} raw cast deref(s) by the one-form regex, {c['deref_all']} by the census's four forms (+{c['typed_cast_member']} typed "
          f"cast-member, +{c['addr_form']} address-of), {c['struct_members']} struct member read(s); {c['struct_defs']} struct definitions over "
          f"{c['distinct_layouts']} layouts ({c['dup_classes']} duplicate classes / {c['dup_names']} names); the map: {c['map_types']} types "
          f"({c['map_pct']} % of sites), at {head[:9]}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
