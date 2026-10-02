# §P39 T4 — 2026-10-02: restruct `--only main`

- `restruct.py --only main`: exact selector for the main executable's TUs: top-level `src/*.c` (`tu.count("/") == 1`) and `src/resident/**`; same test as the fallback-defs walk and the sample stratifier. Never matches `src/shared/main/*.h` (the substring rule is skipped for `main`).
- Works for `--apply --rung S`, `--residue`, `--check-residue`; with the cycle: `LABEL_PREFIX=t4_main_ TASK=T4 bash tools/restruct_cycle.sh 1 40 200 S main`.
- harness: `restruct_cycle.sh` expands ONLY unquoted, so `ONLY="src/shared/*"` is pathname-expanded by bash into the subdirs (which then match nothing); use `ONLY=shared` for the cycle (prefix `src/shared/`); call restruct directly with `--only "src/shared/*"`.
