#!/usr/bin/env python3
"""ghidra_annotations_delta.py — the HAND-AUTHORED part of a Ghidra program, as a byte-stable file (P33 B5).

    ghidra_annotations_delta.py <live.jsonl> <baseline.jsonl> <out.jsonl>   [--census]

`live.jsonl` is ExportAnnotations.java's dump of the program as it is; `baseline.jsonl` is the same
dump of a FRESH rebuild of that program (import + auto-analysis + DefineFunctions + ApplySymbols, no
annotations imported). Every row auto-analysis produces on its own appears in both and subtracts
itself out; what remains — types, retyped/renamed signatures and locals, typed data, comments,
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
    kept = [ln for ln in live if kind(ln) in KEEP_ALWAYS or ln not in base]
    with open(out, "w", encoding="utf-8", newline="\n") as f:
        for ln in kept:
            f.write(ln + "\n")
    c = collections.Counter(kind(ln) for ln in kept)
    hand = sum(v for k, v in c.items() if k not in KEEP_ALWAYS)
    print(f"delta: {len(live)} live - {len(base)} baseline -> {len(kept)} rows ({hand} hand-authored) -> {out}",
          file=sys.stderr)
    if census:
        for k in sorted(c):
            print(f"  {k:9} {c[k]}")
    return 0


if __name__ == "__main__":
    sys.exit(main(sys.argv))
