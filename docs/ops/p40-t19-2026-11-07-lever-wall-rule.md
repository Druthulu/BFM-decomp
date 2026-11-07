# P40 T19 — 2026-11-07: the lever wall rule (`lever_census --walls`)

- Rule: every `config/lever_residue.tsv` row's cause ends ` wall:<tag>`, the tag a row of `config/lever_walls.tsv` (vocabulary,
  tag = column 1, `#` lines and the `tag` header skipped; 32 tags, each with pass, what, evidence).
- `tools/lever_census.py --check --strict --residue PATH [--walls config/lever_walls.tsv]` prints
  `walls: rows N, unwalled n, unknown-tag n, by tag {...}` and `unwalled by cause: {...}` (cause class = text before `(`);
  rc 1 and FAIL on residue-unused > 0, unwalled > 0 or unknown-tag > 0. Pure check: `wall_check(rows, tags, unused)`.
  Non-strict `--check` (tools-health) unchanged.
- `--write-residue` still writes new rows unwalled: a new residue row fails the gate until someone names its wall.
- T19 rewrote the 321 walled rows' old T11 tags onto the vocabulary (`.run/P40/T19/tagmap.tsv`, script
  `.run/P40/T19/rewrite_walls.py`); a renamed row's instrument gained `; T11 wall <old>` (158 rows).
- Live at T19: rows 1182, unwalled 861 (head-class 607, missing-parameter 252, asm-macro-def 1, asm-body-routine 1), unknown-tag 0.
