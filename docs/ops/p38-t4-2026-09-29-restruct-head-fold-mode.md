# §P38 T4 — 2026-09-29: restruct rung L head-fold mode

- `restruct.py --rung L --only <canonical type names>` = head-fold: draws every struct def (file or block scope; `.c`; with `--headers` also `src/**/*.h` incl. `engine_types.h`, never `include/struct_types.h`) whose layout SIZE equals the named canonical's and whose hash differs; `HF_EXCLUDE` globs (`Blk152*`, `Fr_*`) carry a cause.
- Unit: def -> `typedef <Canon> <Local>;` in place; `struct <Tag>` uses -> the typedef; member accesses renamed by offset, type-aware (vars/params/casts of the local type, macro bodies whose expansions all agree); header units also rename in includers and sibling `.h` in their include closure.
- Ledger: `FOLDED` (canon, renames) / `FOLD-REFUSED` (cause) / `COMBINATION-FAILED`; settled units skipped unless `--redraw VERDICT:cause`; a same-label file-level `TOOL-ERROR` unsettles.
- `--status --rung L --only <types>` buckets head-fold rows verdict -> cause.
- Inflight record: atomic write under flock; `apply.lock` refuses a second concurrent `--apply`; a TOOL-ERROR worker restores its file.
- `restruct_cycle.sh`: commit message uses `$TASK`; commits the ledger with `git add -f`; no CURRENT_PHASE.md append when absent; on `final X/Y` X≠Y it stops and leaves the tree as restruct left it (operator reverts).
- Gotcha: a detached cycle's log stays 0 bytes until the first batch line; check `ps` for `restruct_cycl[e]` before relaunching (T4 ran one batch twice concurrently).
