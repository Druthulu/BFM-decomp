#!/usr/bin/env python3
"""tool_census.py — the tools audit: a derived census of every tool, a need-keyed dictionary index, the kit's manifest and the
two verbatim corpora, all from one hand-kept dictionary (P33.5 task 13.5; `--check` in tools-health).

    tools/tool_census.py                 # regenerate docs/tool-index.md (the dictionary) and print the counts
    tools/tool_census.py --check         # tools-health: coverage both ways, index fresh, manifest fresh, corpora equal (rc 1 on any gap)
    tools/tool_census.py --manifest      # regenerate decomp-architect/tools/MANIFEST.md from the same data
    tools/tool_census.py --corpus        # materialise decomp-architect/corpus/tools/ and corpus/cookbook/ verbatim (+ their INDEX)
    tools/tool_census.py --all           # index + manifest + corpus
    tools/tool_census.py --consumers F   # print one file's consumers (the referrer census before a `git mv`)

Two kinds of fact, deliberately separated (R33):
  DERIVED on every run from the tree — the file set (two independent enumerations that must agree: `find` and `git ls-files`,
    R34), each tool's docstring line, its SETUP row (`docs/SETUP.md`, matched by file name), its CONSUMERS (Makefile + config/*.mk
    targets, the CI workflows, the wave playbook, and every other tool that imports it or names it), and hence its class:
    LIVE (a runtime consumer), REFERENCED (only a SETUP/doc row), ORPHAN (neither).
  AUTHORED once, in `config/tool_dictionary.tsv` (tab-separated, LF line endings, the eight columns below) — the ladder phase, the portability (PORTABLE / ADAPT / PROJECT-ONLY), the NEED
    the tool answers (the dictionary key), what it does, what it hard-codes, and the retirement verdict (LIVE / STILL-NEEDED /
    SUPERSEDED / ONE-OFF with the successor or product). Coverage is asserted BOTH ways (R32): every enumerated file has a row,
    every row names an existing file (retired ones under tools/sunset/); a new tool without a row fails `--check`.
Everything published is generated from these two (R75): docs/tool-index.md, the kit's tools/MANIFEST.md, the corpus copies
(byte-equal to their sources, asserted by sha1), and the corpus INDEX. Retired tools are excluded from the corpus except as a
pointer file naming the successor.
"""
import argparse
import csv
import hashlib
import pathlib
import re
import shutil
import subprocess
import sys

REPO = pathlib.Path(__file__).resolve().parent.parent
TOOLS = REPO / "tools"
DICT = REPO / "config" / "tool_dictionary.tsv"
INDEX = REPO / "docs" / "tool-index.md"
KIT = REPO / "decomp-architect"
MANIFEST = KIT / "tools" / "MANIFEST.md"
CORPUS_TOOLS = KIT / "corpus" / "tools"
CORPUS_COOK = KIT / "corpus" / "cookbook"
COOKBOOK_SOURCES = ["docs/matching-cookbook.md", "docs/cookbook-index.md"] + [p.relative_to(REPO).as_posix() for p in sorted((REPO / "docs" / "gcc-2.7.2-map").glob("*")) if p.is_file()]
EXCL_DIRS = {".venv", "__pycache__", "asm-differ", "m2c", "maspsx", "decomp-permuter", "brave-CUE", "reference", "psyq", "bin", "sunset"}
EXTS = {".py", ".sh", ".java"}
PHASES = ["P1", "P2", "P3", "P4", "P5", "P6", "P7", "P8", "P9", "P10", "PROJECT-ONLY"]
PHASE_TITLES = {"P1": "extraction + manifest", "P2": "the oracles + the load map", "P3": "the all-assembly baseline",
                "P4": "the compiler pinned; the probes", "P5": "the census, the harness, the reports",
                "P6": "the multipliers: signatures, dedup, families, the reconcile ladder, the carve chain",
                "P7": "the codegen map, the dumps, the permuter", "P8": "the campaign: cards, lanes, gates, recovery, harvest",
                "P9": "publish", "P10": "readability", "PROJECT-ONLY": "project-only in code (the shape is a task; the code does not transfer)"}
COLS = ["path", "phase", "portability", "need", "what", "adapts", "status", "successor_or_product"]
STATUSES = {"LIVE", "STILL-NEEDED", "SUPERSEDED", "ONE-OFF"}


def sh(cmd):
    return subprocess.run(cmd, cwd=REPO, capture_output=True, text=True)


def enumerate_tools():
    """Two independent enumerations of the in-scope tool files; they must agree (R34)."""
    def in_scope(p):
        rel = p.relative_to(REPO)
        return rel.parts[0] == "tools" and p.suffix in EXTS and not (set(rel.parts[1:-1]) & EXCL_DIRS)
    by_find = {p.relative_to(REPO).as_posix() for p in TOOLS.rglob("*") if p.is_file() and in_scope(p)}
    ls = sh(["git", "ls-files", "-z", "tools"]).stdout.split("\0")
    by_git = {rel for rel in ls if rel and (REPO / rel).is_file() and in_scope(REPO / rel)}
    if by_find != by_git:
        diff = sorted(by_find ^ by_git)
        sys.exit(f"tool_census: the two enumerations disagree on {len(diff)} file(s) (untracked or deleted tools?): {diff[:10]} (R34)")
    retired = sorted(p.relative_to(REPO).as_posix() for p in (TOOLS / "sunset").glob("*") if p.is_file() and p.suffix in EXTS) if (TOOLS / "sunset").is_dir() else []
    return sorted(by_find), retired


def docstring_line(path):
    text = (REPO / path).read_text(encoding="utf-8", errors="replace")
    if path.endswith(".py"):
        m = re.search(r'^\s*(?:r|u)?"""(.*?)"""', text, re.S | re.M) or re.search(r"^\s*'''(.*?)'''", text, re.S | re.M)
        if m:
            first = next((ln.strip() for ln in m.group(1).splitlines() if ln.strip()), "")
            return first
        for ln in text.splitlines():
            if ln.startswith("#") and not ln.startswith("#!"):
                return ln.lstrip("# ").strip()
        return ""
    for ln in text.splitlines():
        s = ln.strip()
        if s.startswith("#!") or s.startswith("//!"):
            continue
        if s.startswith("#") or s.startswith("//") or s.startswith("/*") or s.startswith("*"):
            s = s.lstrip("#/* ").strip()
            if s:
                return s
    return ""


def setup_rows():
    """file name -> the SETUP row's purpose cell (first 160 chars)."""
    out = {}
    for ln in (REPO / "docs" / "SETUP.md").read_text(encoding="utf-8", errors="replace").splitlines():
        if not ln.startswith("|"):
            continue
        cells = [c.strip() for c in ln.strip().strip("|").split("|")]
        if len(cells) < 3:
            continue
        for name in re.findall(r"`tools/([^`\s\[]+)", ln):
            out.setdefault(pathlib.Path(name).name, cells[2][:160])
    return out


def consumer_census(files):
    """file -> sorted list of consumers (Makefile/.mk targets, CI, the playbook, other tools by import or by name)."""
    corpora = {"Makefile": (REPO / "Makefile").read_text(errors="replace")}
    for p in sorted((REPO / "config").glob("*.mk")):
        corpora[p.relative_to(REPO).as_posix()] = p.read_text(errors="replace")
    for p in sorted((REPO / ".github" / "workflows").glob("*.yml")):
        corpora[p.relative_to(REPO).as_posix()] = p.read_text(errors="replace")
    corpora["docs/wave-playbook.md"] = (REPO / "docs" / "wave-playbook.md").read_text(errors="replace")
    src = {f: (REPO / f).read_text(errors="replace") for f in files}
    out = {}
    for f in files:
        name = pathlib.Path(f).name
        stem = pathlib.Path(f).stem
        cons = [k for k, t in corpora.items() if name in t]
        imp = re.compile(r"\b(?:import\s+" + re.escape(stem) + r"\b|from\s+" + re.escape(stem) + r"\s+import\b)")
        for g, t in src.items():
            if g != f and (name in t or imp.search(t)):
                cons.append(g)
        out[f] = sorted(set(cons))
    return out


def read_dict():
    if not DICT.exists():
        sys.exit(f"tool_census: {DICT.relative_to(REPO)} missing — the authored dictionary is required (R32)")
    rows = []
    with open(DICT, newline="", encoding="utf-8") as fh:
        rd = csv.DictReader(fh, delimiter="\t")
        if rd.fieldnames != COLS:
            sys.exit(f"tool_census: dictionary columns {rd.fieldnames} != {COLS} — refusing (R43)")
        for r in rd:
            if r["phase"] not in PHASES or r["status"] not in STATUSES or r["portability"] not in {"PORTABLE", "ADAPT", "PROJECT-ONLY"}:
                sys.exit(f"tool_census: bad row for {r['path']}: phase={r['phase']} status={r['status']} portability={r['portability']} (R43)")
            rows.append(r)
    return rows


def census():
    files, retired = enumerate_tools()
    rows = read_dict()
    by_path = {r["path"]: r for r in rows}
    live_rows = {p for p, r in by_path.items() if r["status"] in ("LIVE", "STILL-NEEDED")}
    retired_rows = {p for p, r in by_path.items() if r["status"] in ("SUPERSEDED", "ONE-OFF")}
    gaps = []
    for f in files:
        if f not in by_path:
            gaps.append(f"no dictionary row: {f}")
        elif f in retired_rows:
            gaps.append(f"row says retired but the file is live: {f}")
    for p in live_rows:
        if p not in files:
            gaps.append(f"row for a missing live file: {p}")
    for p in retired_rows:
        expected = f"tools/sunset/{pathlib.Path(p).name}"
        if expected not in retired:
            gaps.append(f"retired row but {expected} is absent: {p}")
        if by_path[p]["status"] == "SUPERSEDED" and by_path[p]["successor_or_product"] not in by_path:
            gaps.append(f"superseded by an unknown tool: {p} -> {by_path[p]['successor_or_product']}")
        if not by_path[p]["successor_or_product"].strip():
            gaps.append(f"retired without a successor or product named: {p}")
    for r in retired:
        if pathlib.Path(r).name not in {pathlib.Path(p).name for p in retired_rows}:
            gaps.append(f"file under tools/sunset/ without a retired row: {r}")
    cons = consumer_census(files)
    setup = setup_rows()
    for p in retired_rows:
        name = pathlib.Path(p).name
        users = [c for c, t in ((f, (REPO / f).read_text(errors="replace")) for f in files) if name in t or re.search(r"\bimport\s+" + re.escape(pathlib.Path(p).stem) + r"\b", t)]
        users += [k for k in ("Makefile",) if name in (REPO / k).read_text(errors="replace")]
        if users:
            gaps.append(f"retired tool still consumed: {p} <- {users[:4]}")
    recs = []
    for f in files:
        r = by_path.get(f, {c: "" for c in COLS})
        c = cons[f]
        klass = "LIVE" if c else ("REFERENCED" if pathlib.Path(f).name in setup else "ORPHAN")
        recs.append({**r, "path": f, "doc": docstring_line(f), "setup": setup.get(pathlib.Path(f).name, ""), "consumers": c, "class": klass})
    for p in sorted(retired_rows):
        r = by_path[p]
        recs.append({**r, "doc": docstring_line(f"tools/sunset/{pathlib.Path(p).name}") if (REPO / "tools/sunset" / pathlib.Path(p).name).exists() else "",
                     "setup": setup.get(pathlib.Path(p).name, ""), "consumers": [], "class": "RETIRED"})
    return recs, files, retired, gaps


def fmt_cons(c):
    if not c:
        return "—"
    show = [pathlib.Path(x).name if x.startswith("tools/") else x for x in c]
    return ", ".join(show[:4]) + (f" (+{len(show) - 4})" if len(show) > 4 else "")


def render_index(recs, files, retired):
    live = [r for r in recs if r["class"] != "RETIRED"]
    from collections import Counter
    cls = Counter(r["class"] for r in live)
    port = Counter(r["portability"] for r in live)
    out = ["# The tool index — every tool, keyed by the need it answers",
           "",
           "*Generated by `tools/tool_census.py` from the tree and `config/tool_dictionary.tsv`; never edited by hand (a `--check` in tools-health asserts",
           "freshness). The derived columns come from the tree on every run; the authored ones (phase, need, portability, verdict) from the",
           "dictionary, whose coverage is asserted both ways. Read it by NEED: find the phrase that matches what you are trying to do, then the tool,",
           "then what proved it. The same data generates the day-one kit's manifest and its verbatim tool corpus.*",
           "",
           f"**Coverage:** {len(files)} tool files in scope (submodules, vendored and downloaded code excluded; `find` and `git ls-files` agree) + "
           f"{len(retired)} retired under `tools/sunset/`. Classes: LIVE {cls.get('LIVE', 0)} (a runtime consumer), REFERENCED {cls.get('REFERENCED', 0)} "
           f"(a SETUP row only), ORPHAN {cls.get('ORPHAN', 0)} (neither) — of {len(live)}. Portability: PORTABLE {port.get('PORTABLE', 0)}, ADAPT {port.get('ADAPT', 0)}, "
           f"PROJECT-ONLY {port.get('PROJECT-ONLY', 0)}.",
           ""]
    for ph in PHASES:
        sub = [r for r in live if r["phase"] == ph]
        if not sub:
            continue
        out += [f"## {ph} — {PHASE_TITLES[ph]}", "", "| When you need to… | Tool | What it does | Proven by | Adapt | Class |", "|---|---|---|---|---|---|"]
        for r in sorted(sub, key=lambda r: (r["need"].lower(), r["path"])):
            out.append(f"| {r['need']} | `{r['path'].removeprefix('tools/')}` | {r['what'] or r['doc']} | {fmt_cons(r['consumers'])} | {r['adapts'] or 'none'} | {r['class']} |")
        out.append("")
    ret = [r for r in recs if r["class"] == "RETIRED"]
    if ret:
        out += ["## Retired (`tools/sunset/`) — superseded by a named successor, or a one-off whose product exists", "",
                "| Tool | Verdict | Successor or product | What it did |", "|---|---|---|---|"]
        for r in sorted(ret, key=lambda r: r["path"]):
            out.append(f"| `{r['path'].removeprefix('tools/')}` | {r['status']} | {r['successor_or_product']} | {r['what'] or r['doc']} |")
        out.append("")
    return "\n".join(out)


def render_manifest(recs, files):
    live = [r for r in recs if r["class"] != "RETIRED"]
    n_sup = sum(1 for r in recs if r["class"] == "RETIRED" and r["status"] == "SUPERSEDED")
    from collections import Counter
    per = Counter(r["phase"] for r in live)
    out = ["# tools/MANIFEST.md — the source project's tools, by ladder phase, as tasks and as a dictionary",
           "",
           "> **Generated** by the source project's `tools/tool_census.py --manifest` from its tool dictionary (the same data as its tool index);",
           "> never edited by hand. **What this is, and what it is not.** The kit installs no tools (its README says so). Each row is a task for",
           "> the phase that needs it: build the tool for your target from its description, using the verbatim copy under `corpus/tools/<phase>/`",
           "> as the reference implementation and the *Adapt* column as the list of what to change. Rows whose *Adapt* says \"none\" or names only",
           "> the instruction set are copy-after-adaptation candidates; rows that name the source repository's layout, its compiler triple or",
           "> its platform SDK need the marked adaptation. The last table lists the tools that are project-only in code (their *shape* is a task;",
           "> their code does not transfer). *TODO(platform): the MIPS and PlayStation SDK hard-codes are the ones another platform replaces first.*",
           ">",
           f"> **Coverage:** {len(files)} tool files in scope (submodules, vendored and downloaded code excluded), of which {len(live)} live rows",
           f"> below; per phase: " + " · ".join(f"{ph} {per.get(ph, 0)}" for ph in PHASES if per.get(ph, 0)) + f". Superseded tools appear only as pointers to their successor ({n_sup} pointer rows); one-offs are omitted. "
           f"Table rows in all: {len(live) + n_sup} (the installer checks its copy against this figure).",
           ""]
    for ph in PHASES:
        sub = [r for r in live if r["phase"] == ph]
        if not sub:
            continue
        out += [f"## {ph} — {PHASE_TITLES[ph]}", "", "| Tool | When you need to… | What it does | Adapt |", "|---|---|---|---|"]
        for r in sorted(sub, key=lambda r: (r["need"].lower(), r["path"])):
            out.append(f"| `{r['path'].removeprefix('tools/')}` | {r['need']} | {r['what'] or r['doc']} | {r['adapts'] or 'none'} |")
        out.append("")
    sup = [r for r in recs if r["class"] == "RETIRED" and r["status"] == "SUPERSEDED"]
    if sup:
        out += ["## Superseded — pointers only", "", "| Tool | Superseded by | What it did |", "|---|---|---|"]
        for r in sorted(sup, key=lambda r: r["path"]):
            out.append(f"| `{r['path'].removeprefix('tools/')}` | `{r['successor_or_product'].removeprefix('tools/')}` | {r['what'] or r['doc']} |")
        out.append("")
    return "\n".join(out)


def sha1(p):
    return hashlib.sha1(pathlib.Path(p).read_bytes()).hexdigest()


def corpus_plan(recs):
    """(source, destination) pairs for the verbatim tool copies and the cookbook copies; plus pointer files for superseded tools."""
    copies, pointers = [], []
    for r in recs:
        if r["class"] == "RETIRED":
            if r["status"] == "SUPERSEDED":
                pointers.append((CORPUS_TOOLS / r["phase"] / (pathlib.Path(r["path"]).name + ".superseded.md"), r))
            continue
        dest = CORPUS_TOOLS / r["phase"] / r["path"].removeprefix("tools/")
        copies.append((REPO / r["path"], dest))
    for s in COOKBOOK_SOURCES:
        copies.append((REPO / s, CORPUS_COOK / pathlib.Path(s).relative_to("docs")))
    return copies, pointers


def write_corpus(recs, files):
    copies, pointers = corpus_plan(recs)
    if CORPUS_TOOLS.exists():
        shutil.rmtree(CORPUS_TOOLS)
    for src, dst in copies:
        dst.parent.mkdir(parents=True, exist_ok=True)
        shutil.copyfile(src, dst)
        shutil.copymode(src, dst)
    for dst, r in pointers:
        dst.parent.mkdir(parents=True, exist_ok=True)
        dst.write_text(f"# {pathlib.Path(r['path']).name} — superseded\n\nSuperseded by `{r['successor_or_product'].removeprefix('tools/')}` "
                       f"(see its row in the index). What it did: {r['what'] or r['doc']}\n", encoding="utf-8")
    (CORPUS_TOOLS / "INDEX.md").write_text(render_manifest(recs, files).replace("# tools/MANIFEST.md — the source project's tools, by ladder phase, as tasks and as a dictionary",
                                                                                "# corpus/tools/INDEX.md — the tool dictionary (the files beside this index are the source project's tools, verbatim)"), encoding="utf-8")
    return copies, pointers


def check_corpus(recs, files):
    gaps = []
    copies, pointers = corpus_plan(recs)
    for src, dst in copies:
        if not dst.exists():
            gaps.append(f"corpus copy missing: {dst.relative_to(REPO)}")
        elif sha1(src) != sha1(dst):
            gaps.append(f"corpus copy differs from its source: {dst.relative_to(REPO)}")
    for dst, r in pointers:
        if not dst.exists():
            gaps.append(f"corpus pointer missing: {dst.relative_to(REPO)}")
    expected = {d for _, d in copies} | {d for d, _ in pointers} | {CORPUS_TOOLS / "INDEX.md", CORPUS_COOK / "README.md"}
    present = {p for p in CORPUS_TOOLS.rglob("*") if p.is_file()} | {p for p in CORPUS_COOK.rglob("*") if p.is_file()} if CORPUS_TOOLS.exists() else set()
    for p in sorted(present - expected):
        gaps.append(f"corpus file without a dictionary entry: {p.relative_to(REPO)}")
    if not (CORPUS_COOK / "README.md").exists():
        gaps.append("corpus/cookbook/README.md (the front page) is missing")
    return gaps, len(copies), len(pointers)


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--check", action="store_true")
    ap.add_argument("--manifest", action="store_true")
    ap.add_argument("--corpus", action="store_true")
    ap.add_argument("--all", action="store_true")
    ap.add_argument("--consumers", metavar="FILE")
    a = ap.parse_args()
    recs, files, retired, gaps = census()
    if a.consumers:
        rec = next((r for r in recs if r["path"] == a.consumers or r["path"].endswith("/" + a.consumers) or pathlib.Path(r["path"]).name == a.consumers), None)
        if not rec:
            sys.exit(f"tool_census: {a.consumers} is not in the census")
        print(f"{rec['path']}: class {rec['class']}; consumers ({len(rec['consumers'])}): " + (", ".join(rec["consumers"]) or "none"))
        return 0
    from collections import Counter
    cls = Counter(r["class"] for r in recs)
    print(f"tool_census: {len(files)} tool files (find == git ls-files) + {len(retired)} retired; classes {dict(cls)}; dictionary rows {len(read_dict())}")
    index_text, manifest_text = render_index(recs, files, retired), render_manifest(recs, files)
    if a.check:
        if gaps:
            for g in gaps:
                print("  GAP", g)
        if not INDEX.exists() or INDEX.read_text(encoding="utf-8") != index_text:
            gaps.append("docs/tool-index.md is stale — run tools/tool_census.py")
        if not MANIFEST.exists() or MANIFEST.read_text(encoding="utf-8") != manifest_text:
            gaps.append("decomp-architect/tools/MANIFEST.md is stale — run tools/tool_census.py --manifest")
        cg, nc, npt = check_corpus(recs, files)
        gaps += cg
        for g in cg:
            print("  GAP", g)
        print(f"tool_census --check: corpus {nc} copies + {npt} pointers checked; {len(gaps)} gap(s)")
        print("tool_census --check: OK" if not gaps else "tool_census --check: FAIL")
        return 1 if gaps else 0
    if gaps:
        for g in gaps:
            print("  GAP", g)
        print(f"tool_census: {len(gaps)} coverage gap(s) — fix the dictionary before publishing (R32)")
        return 1
    INDEX.write_text(index_text, encoding="utf-8")
    print(f"tool_census: wrote {INDEX.relative_to(REPO)}")
    if a.manifest or a.all:
        MANIFEST.write_text(manifest_text, encoding="utf-8")
        print(f"tool_census: wrote {MANIFEST.relative_to(REPO)}")
    if a.corpus or a.all:
        copies, pointers = write_corpus(recs, files)
        print(f"tool_census: corpus materialised — {len(copies)} verbatim copies, {len(pointers)} pointers, INDEX.md")
    return 0


if __name__ == "__main__":
    sys.exit(main())
