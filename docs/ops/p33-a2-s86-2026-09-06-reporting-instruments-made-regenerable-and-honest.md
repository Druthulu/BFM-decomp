### P33 A2 (S86, 2026-09-06) — reporting instruments made regenerable and honest
- `tools/main_seed_ends.py [--map build/us/SLUS_007.26.map] [--out .run/seeds.main.txt]` — main's game-code function
  boundaries DERIVED from the build (link-map `.text` sections × each object's `nm` symbols; LINKED subsegs and
  `build/psyq/` skipped; tiling + 4-alignment + first-symbol-at-0 asserted, R32; totals printed with denominators).
  Feeds the rewritten `make sig-main` (§6.8 above).
- `tools/progress.py`: main's sig = `.run/sig.main.jsonl` (build-derived) → legacy `.run/sig.SLUS_007.26.jsonl` →
  **SystemExit** (no silent `mt=0`); the digest's oracle clause comes from `progress.main_oracle_line()` (live
  `corpus.audit('main')`), the provenance + date of the sig used are printed on the MAIN line.
- `tools/backlog.py`: `linked_closed(binary, addr)` — a main address inside a LINKED PsyQ range is retired by `prune`
  (byte-identical by link, not work); controls: `0x80062144` True, `0x80018730` False, non-main False. The legacy S70
  row `func_80062144` is gone; `docs/backlog.md` reads 0 open.
- `tools/dup_report.py`: main's sig path → `.run/sig.main.jsonl`.

