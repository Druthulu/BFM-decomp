# §P39 T3 — 2026-10-02: restruct rung S residue/check-residue; head_types --add-pads

- `restruct.py --rung S --residue --only "ov_*" --label <l>`: ledger-only; one S row per body with a P/X census site and no latest S row (plan_S never draws bodies whose bases are all TYPE-NOT-CANONICAL / not visible). Site causes TYPE-NOT-CANONICAL, TYPE-NOT-VISIBLE, NO-TYPE-IN-MAP (untyped), NO-EDIT, FILE-SCOPE (unit `<file-scope>`, fn null). No src edit, no R22.
- `restruct.py --rung S --check-residue [--only glob]` (default `ov_*`): prints `uncovered <n> sites / <m> bodies`, exit 1 if n > 0. Reads `.run/P37/census/sites.jsonl` (run the census first).
- Rung S macro carry (T3.c8, `s_base_norm`): a kept CAST_* macro stays backed when a later batch respells its nested base (`*(T *)(X + k)` ≡ `((S *)X)->unkK`).
- `head_types.py --add-pads CANDIDATES.json --header include/struct_types.h`: additive mode; keeps the generated region's fields byte-for-byte and only splits pad arrays for candidate fields `[{type, off, width, sign}]`; no struct map read. Use instead of a full regen when existing member spellings must not move.
- A canonical type that becomes live after a sweep must leave `docs/struct-twins.md ## Dead kept` (else `--check-structs` twins_stale=1). `struct_twins.py --write` needs a built tree (after `make clean` it binds fewer objects).
- `.run/P37/restruct/ledger.jsonl` is tracked under ignored `.run/`: `git add -f` it before `tools/commit_task.sh`.
