# §P39 T1 — 2026-10-01: restruct stale-row supersede; timeline --check

- `restruct.py --rung D --redraw <KEY> [--headers]`: a lifted latest `decl:` row whose (tu, callee) has no argcheck lying row any more (hand-fixed unit) gets a superseding `DECL-NONE` row, cause `already canonical: no lying declaration left (stale <verdict> row superseded)`; `--plan` lists them, `--apply` appends them (no compile). `.c` and `.h` units are separate runs (`--headers`).
- `timeline.py --check` does not compare the latest row's `Commits` cell (it counts that day's commits, so any same-day commit, including the timeline's own, moved it). All other cells compared exactly.
- `tools/expert_ttl.py` (PA harness) has a PROJECT-ONLY row in `config/tool_dictionary.tsv`; a new tool needs a row + `make kit-corpus`, else `make tools-health` fails in `tool_census --check`. Any tool edit also needs `make kit-corpus` (corpus copies).
