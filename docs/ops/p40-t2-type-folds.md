# §P40 T2 — 2026-10-14: restruct.py reads config/type_folds.tsv; residue causes resolve the drawn type; --restamp

## The table
- `config/type_folds.tsv`: line 1 `#` comment, header `map_type action target evidence note`; action `fold` | `define` | `residual`. Content owned by the T2 expert.
- `restruct.type_folds()` → `{map_type: (action, target)}`, read once per process; missing file = `{}`.

## Who reads it
- `bbt()`: `fold_bbt()` renames each fold/define entry's `type` to its target in the live census AND the `--bbt`/`RESTRUCT_BBT` pin, before `merge_bbt`'s canonical test; the entry keeps `map_type` (the map's name) and plan_S weighs it by that.
- `residue_cause(s, can, latest)`: residual row → its target cause (TYPE-UNION / TYPE-NO-LAYOUT / TYPE-SCALAR); fold/define → test the target; still not canonical and `latest` given → the canonical `type` of the body's latest rung-S `bases[]` entry for the same `s_base_norm`'d `<bclass>:<base>`. `residue_cause_im` falls through; `residue_rows` passes `latest`.

## --restamp
- `restruct.py --rung S --residue --restamp [--only ...] [--forms P,X]` (ledger only, apply lock): covered sites whose covering RESIDUAL entry (paired per key in ledger order, as `type_census.residue_split`) is `TYPE-NOT-CANONICAL` and whose live cause differs → one merged row per body (copy of the latest row, ts/label renewed, `restamp_of` = old label), only those entries' cause/verdict changed. Entry count, coverage, row verdict, bases and non-TNC entries untouched.
- Prints `restamp: <rows> rows, <n> sites, old->new {...}`. Commit/back up the ledger (`.run/P37/restruct/ledger.jsonl`) before a real run.
