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
CAST = re.compile(r"\*\s*\(\s*(?:struct\s+|union\s+)?[A-Za-z_]\w*\s*\*+\s*\)\s*\(")
MEMBER = re.compile(r"->[A-Za-z_]\w*|\.[A-Za-z_]\w*\s*=")


def counts():
    defs = argcheck.definitions()
    rows = argcheck.scan(defs)
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
               raw_casts=casts, struct_members=members)
    # Phase 37 T1 (2026-09-12): the type census's columns — the four dereference forms (the CAST regex above sees one of them, over raw
    # text), the typed cast-member accesses (the MEMBER regex counts these as members — they are the rewrite's rung 1, not finished
    # members), the struct definitions and their duplicate classes, the struct map. A snapshot REFUSES a stale census (R43/R51).
    cj = REPO / ".run/P37/census/type_census.json"
    head = subprocess.run(["git", "rev-parse", "HEAD"], cwd=REPO, capture_output=True, text=True).stdout.strip()
    if not cj.exists():
        sys.exit("readability_progress: no type census — run `tools/type_census.py -j 16` first (its columns are part of the row)")
    ts = json.loads(cj.read_text())["summary"]
    if not head.startswith(ts.get("head", "?")):
        sys.exit(f"readability_progress: the type census is STALE (census {ts.get('head')} vs HEAD {head[:9]}) — rerun tools/type_census.py")
    c, d, sm = ts["casts"], ts["definitions"], ts["struct_map"]
    out.update(deref_all=c["deref_total"], form_P=c["by_form"].get("P", 0), form_I=c["by_form"].get("I", 0), form_X=c["by_form"].get("X", 0),
               form_M=c["by_form"].get("M", 0), addr_form=c["addr_form"], typed_cast_member=c["typed_cast_member"],
               struct_defs=d["total"], canon_defs=d["canon"], in_c_defs=d["in_c_file_scope"] + d["in_c_block_scope"],
               distinct_layouts=d["distinct_layouts"], dup_classes=d["dup_layout_classes"], dup_names=d["dup_layout_names"],
               map_types=sm["types"], map_pct=sm["explained_pct"])
    return out


COLS = ["date", "label", "commit", "definitions", "narrow_decls", "callees", "kr_empty", "narrow", "pinned_rows", "pinned_bodies",
        "raw_casts", "struct_members",
        # P37 columns (appended 2026-09-12; older rows carry blanks — the renderer reads by name, never by position)
        "deref_all", "form_P", "form_I", "form_X", "form_M", "addr_form", "typed_cast_member", "struct_defs", "canon_defs", "in_c_defs",
        "distinct_layouts", "dup_classes", "dup_names", "map_types", "map_pct"]
HEAD = "\t".join(COLS) + "\n"


def _rows():
    lines = [l for l in TSV.read_text().splitlines() if l.strip()]
    cols = lines[0].split("\t")
    rows = []
    for l in lines[1:]:
        vals = l.rstrip("\n").split("\t")
        rows.append({c: (vals[i] if i < len(vals) else "") for i, c in enumerate(cols)})
    return rows


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
           "| date | label | commit | lying declarations | of which `()` | of which `(void)` | in a pinned body | raw cast derefs (one form, raw text) | struct member reads | **raw derefs, four forms** | typed cast-member | struct defs (canonical / in .c) | layouts | duplicate classes / names | map types (% sites) |",
           "|---|---|---|---:|---:|---:|---:|---:|---:|---:|---:|---|---:|---|---|"]
    for r in rows:
        defs = f"{g(r,'struct_defs')} ({g(r,'canon_defs')} / {g(r,'in_c_defs')})" if r.get("struct_defs") else "—"
        dups = f"{g(r,'dup_classes')} / {g(r,'dup_names')}" if r.get("dup_classes") else "—"
        mp = f"{g(r,'map_types')} ({g(r,'map_pct')} %)" if r.get("map_types") else "—"
        out.append(f"| {r['date']} | {r['label']} | `{r['commit'][:9]}` | {r['narrow_decls']} | {r['kr_empty']} | {r['narrow']} | {r['pinned_rows']} | "
                   f"{r['raw_casts']} | {r['struct_members']} | **{g(r,'deref_all')}** | {g(r,'typed_cast_member')} | {defs} | {g(r,'distinct_layouts')} | {dups} | {mp} |")
    out += ["",
            "**How to read it.** A *lying declaration* is a call site whose in-scope declaration names fewer parameters",
            "than the callee's own definition. It is not a style problem: on this processor an argument travels in a",
            "register, so a dropped argument removes an instruction, and Phase 36 found register pins inserted to fake",
            "exactly that instruction. *Raw cast derefs* is the struct debt — a struct cannot be recovered from the",
            "binary, only inferred from consistent base+offset+width evidence, so this figure falls as that work lands.",
            ""]
    DOC.write_text("\n".join(out) + "\n")


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--snapshot", metavar="LABEL")
    ap.add_argument("--check", action="store_true")
    a = ap.parse_args()
    head = subprocess.run(["git", "rev-parse", "HEAD"], cwd=REPO, capture_output=True, text=True).stdout.strip()
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
    print(f"readability_progress: {a.snapshot} — {c['narrow_decls']} lying declaration(s) over {c['callees']} callee(s) "
          f"({c['kr_empty']} `()`, {c['narrow']} `(void)`), {c['pinned_rows']} in {c['pinned_bodies']} pinned bodies; "
          f"{c['raw_casts']} raw cast deref(s) by the one-form regex, {c['deref_all']} by the census's four forms (+{c['typed_cast_member']} typed "
          f"cast-member, +{c['addr_form']} address-of), {c['struct_members']} struct member read(s); {c['struct_defs']} struct definitions over "
          f"{c['distinct_layouts']} layouts ({c['dup_classes']} duplicate classes / {c['dup_names']} names); the map: {c['map_types']} types "
          f"({c['map_pct']} % of sites), at {head[:9]}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
