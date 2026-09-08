#!/usr/bin/env python3
"""objdiff_report.py — docs/progress.json → an objdiff progress report (report.json) for decomp.dev (P33 D3).

    tools/objdiff_report.py [--out report.json] [--in docs/progress.json]

decomp.dev reads a GitHub Actions artifact in objdiff's report format (objdiff-core/protos/report.proto, `Report`
version 2): top-level `measures`, one `units` entry per binary with its own measures and metadata, and `categories`.
Field names are the proto's (snake_case); the output was validated with `objdiff-cli report changes` (S87).

What the numbers ARE here (every one carries its denominator in docs/progress.json, R41):
  * code = instructions × 4 bytes (MIPS): `total_code` / `matched_code` per binary from the build-derived function
    boundaries; main's code is its GAME CODE only (the linked Sony objects are a separate functions-only category);
  * functions = byte-identical / matchable per binary (REAL C + LINKED Sony objects + empties);
  * `fuzzy_match_percent` == the exact matched percentage (this project has no fuzzy state: a function is byte-identical
    or it is an assembly stub);
  * categories: `game-code` (every binary's game code) and `linked-sony-objects` (the 1,256 PsyQ functions of the main
    executable — byte-identical by link, not our C; counted in functions only, their byte size is not measured here).
The report is derived from a LOCAL clean rebuild recorded in docs/progress.json (`make report`); CI does not rebuild the
game (it has no disc) — the workflow only converts the committed JSON and uploads the artifact.
"""
import argparse
import json
import pathlib
import sys

REPO = pathlib.Path(__file__).resolve().parent.parent
VERSION = 2


def measures(code_m, code_t, fn_m, fn_t, units_t=0, units_c=0):
    pct = lambda m, t: (100.0 * m / t) if t else 0.0
    return {
        "fuzzy_match_percent": round(pct(code_m, code_t), 4),
        "total_code": int(code_t), "matched_code": int(code_m), "matched_code_percent": round(pct(code_m, code_t), 4),
        "total_data": 0, "matched_data": 0, "matched_data_percent": 0.0,
        "total_functions": int(fn_t), "matched_functions": int(fn_m), "matched_functions_percent": round(pct(fn_m, fn_t), 4),
        "complete_code": int(code_m), "complete_code_percent": round(pct(code_m, code_t), 4),
        "complete_data": 0, "complete_data_percent": 0.0,
        "total_units": int(units_t), "complete_units": int(units_c),
    }


def build(d):
    units, cm_all, ct_all, fm_all, ft_all, complete = [], 0, 0, 0, 0, 0
    game_fm = game_ft = 0
    for r in d["per_binary"]:
        im, it = r.get("instr_matched"), r.get("instr_total")
        if im is None or it is None:
            sys.exit(f"objdiff_report: {r['binary']} has no instruction totals in progress.json — regenerate it with the sigs present (make report BINARY=main)")
        code_m, code_t = im * 4, it * 4
        fn_m, fn_t = r["byte_identical"], r["matchable"]
        game_fn_t = fn_t - r["linked"]
        game_fn_m = fn_m - r["linked"]                       # every linked object is byte-identical by construction
        done = bool(fn_t) and fn_m == fn_t
        units.append({
            "name": r["binary"],
            "measures": measures(code_m, code_t, fn_m, fn_t, 1, 1 if done else 0),
            "sections": [{"name": ".text", "size": code_t, "fuzzy_match_percent": round(100.0 * code_m / code_t, 4) if code_t else 0.0}],
            "functions": [],
            "metadata": {"complete": done, "module_name": r["binary"],
                         "source_path": "src" if r["binary"] == "main" else f"src/{r['binary']}",
                         "progress_categories": ["game-code"] + (["linked-sony-objects"] if r["linked"] else []),
                         "auto_generated": False},
        })
        cm_all += code_m; ct_all += code_t; fm_all += fn_m; ft_all += fn_t; complete += int(done)
        game_fm += game_fn_m; game_ft += game_fn_t
    linked = d["counts"]["linked_psyq_objects"]
    return {
        "version": VERSION,
        "measures": measures(cm_all, ct_all, fm_all, ft_all, len(units), complete),
        "units": units,
        "categories": [
            {"id": "game-code", "name": "Game code (our C)", "measures": measures(cm_all, ct_all, game_fm, game_ft, len(units), complete)},
            {"id": "linked-sony-objects", "name": "Sony PsyQ library objects (linked, not our C)",
             "measures": measures(0, 0, linked, linked, 1, 1)},
        ],
    }


def main(argv):
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--in", dest="inp", default=str(REPO / "docs/progress.json"))
    ap.add_argument("--out", default="report.json")
    a = ap.parse_args(argv)
    d = json.loads(pathlib.Path(a.inp).read_text(encoding="utf-8"))
    if d.get("schema") != 1:
        sys.exit(f"objdiff_report: unexpected progress.json schema {d.get('schema')!r} (R43)")
    rep = build(d)
    pathlib.Path(a.out).write_text(json.dumps(rep, indent=1) + "\n", encoding="utf-8")
    m = rep["measures"]
    print(f"objdiff_report: {len(rep['units'])} units ({m['complete_units']} complete), code {m['matched_code']:,}/{m['total_code']:,} bytes "
          f"= {m['matched_code_percent']:.2f}%, functions {m['matched_functions']:,}/{m['total_functions']:,} -> {a.out}")
    return 0


if __name__ == "__main__":
    sys.exit(main(sys.argv[1:]))
