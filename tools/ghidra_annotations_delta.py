#!/usr/bin/env python3
"""ghidra_annotations_delta.py — the HAND-AUTHORED part of a Ghidra program, as a byte-stable file (P33 B5).

    ghidra_annotations_delta.py <live.jsonl> <baseline.jsonl> <out.jsonl>   [--census]

`live.jsonl` is ExportAnnotations.java's dump of the program as it is; `baseline.jsonl` is the same
dump of a FRESH rebuild of that program (import + auto-analysis + DefineFunctions + ApplySymbols, no
annotations imported). Every row auto-analysis produces on its own appears in both and subtracts
itself out — minus three counted analysis-drift classes (Error/Analysis bookmarks; auto-named DEFAULT functions the
rebuild did not create; auto-named rows that lag the curated symbol file, R15 — see the rules below); what remains — types, retyped/renamed signatures and locals, typed data, comments,
bookmarks, equates, labels that no symbol file carries — is the RE work worth committing:
config/ghidra/<program>.jsonl. The container rows (`program`, `block`, `archive`) are always kept
from `live` so an image-base or memory-map drift shows as a diff rather than a silent skip.

The proof (tools/ghidra_rebuild.sh --proof) rebuilds, imports config/ghidra/<program>.jsonl, exports,
takes the delta against the SAME rebuild's pre-import baseline, and `cmp`s it against the committed file.

`--census` prints per-kind counts of the delta (the roster decision: a program whose delta holds no
hand-authored rows need not be kept regenerable — it regenerates on demand).
"""
import collections
import json
import sys

KEEP_ALWAYS = ("program", "block", "archive")
# Analysis-origin rows that differ between the live import (Phase 1/10) and today's rebuild — measured on
# SLUS_007.26 (S87): 29 FUN_* functions inside the LINKED PsyQ regions that the live analysis created and the
# rebuild's did not (DEFAULT signature, no comment, auto name), and one "Unable to resolve constructor" Error
# bookmark. They carry no RE; a proof that kept them could never pass on a fresh rebuild.
ANALYSIS_BOOKMARKS = ("Error", "Analysis")
AUTO_NAME = ("FUN_", "func_", "thunk_FUN_")


def is_symbol_file_lag(o, b):
    """The live DB was never re-mirrored from the symbol file: it differs from the rebuilt (ApplySymbols) row ONLY
    by carrying the auto name. Importing it would overwrite a curated name with FUN_* — the symbol file wins (R15).
    Measured on the two prototypes (S87): sep8 10 rows, aug31 5 rows, nothing else."""
    if not str(o.get("name", "")).startswith(AUTO_NAME):
        return False
    return all(o.get(k) == b.get(k) for k in o if k != "name")


def is_function_set_drift(o):
    if o.get("sigsrc") != "DEFAULT" or o.get("comment") or o.get("custom"):
        return False
    if not str(o.get("name", "")).startswith(AUTO_NAME):
        return False
    return all(p.get("src") == "DEFAULT" for p in o.get("params", []) + o.get("locals", []))


def rows(path):
    with open(path, encoding="utf-8") as f:
        return [ln.rstrip("\n") for ln in f if ln.strip()]


def kind(line):
    return json.loads(line)["k"]


def main(argv):
    census = "--census" in argv
    argv = [a for a in argv if a != "--census"]
    if len(argv) != 4:
        sys.exit(__doc__)
    live, base, out = rows(argv[1]), set(rows(argv[2])), argv[3]
    base_func_rows = {json.loads(ln)["addr"]: json.loads(ln) for ln in base if kind(ln) == "func"}
    base_funcs = set(base_func_rows)
    dropped = collections.Counter()
    kept = []
    for ln in live:
        k = kind(ln)
        if k in KEEP_ALWAYS or ln not in base:
            o = json.loads(ln)
            if k == "bookmark" and o.get("type") in ANALYSIS_BOOKMARKS:
                dropped["bookmark:analysis"] += 1        # Ghidra's own Error/Analysis bookmarks — never hand-authored
                continue
            if k == "func" and o["addr"] not in base_funcs and is_function_set_drift(o):
                dropped["func:set-drift"] += 1           # a boundary the live analysis found and the rebuild did not
                continue
            if k == "func" and o["addr"] in base_funcs and is_symbol_file_lag(o, base_func_rows[o["addr"]]):
                dropped["func:name-lag"] += 1            # the DB still says FUN_*; the curated symbol file names it (R15)
                continue
            kept.append(ln)
    with open(out, "w", encoding="utf-8", newline="\n") as f:
        for ln in kept:
            f.write(ln + "\n")
    c = collections.Counter(kind(ln) for ln in kept)
    hand = sum(v for k, v in c.items() if k not in KEEP_ALWAYS)
    drop = ", ".join(f"{k} {v}" for k, v in sorted(dropped.items())) or "none"
    print(f"delta: {len(live)} live - {len(base)} baseline -> {len(kept)} rows ({hand} hand-authored; "
          f"analysis drift dropped: {drop}) -> {out}", file=sys.stderr)
    if census:
        for k in sorted(c):
            print(f"  {k:9} {c[k]}")
    return 0


if __name__ == "__main__":
    sys.exit(main(sys.argv))
