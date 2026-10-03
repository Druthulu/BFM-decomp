# §P39 T7.1 — 2026-10-02: GTE to one spelling
- `lever_census --check --strict`: "direct GTE statements in bodies" = kind gte/gte-unsigned sites NOT via an include/gte_inline.h macro; printed split `(via-header, via-per-TU, inline)`; per-TU asm macro defs printed by kind.
- `gte_consolidate --inventory` signs every inline statement (no gte-unsigned left); `--header` emits canonical macros, inline-only signatures, and `_m`/`_v<sha4>` variants + aliases once each under a `// !FAKE:` line (pass, instrument). Header is generated: never hand-edit.
- `gte_consolidate --apply --keep-levers --only <list>`: respell inline GTE to header calls and delete per-TU GTE defs, leaving gte-lever direct statements (T8) untouched; oracle-judged per file.
- .run/P36/gte/{canonical,sig_cache}.json and .run/P36/delever/* are gitignored-but-tracked: `git add -f`, omit from commit_task paths.
