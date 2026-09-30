### P35 T1 (S94, 2026-09-08) — the share census and the S1 invariant ("one source per unique function")
- **`tools/share_census.py`** — the census of byte-identical function classes (keyed by `h_exact`, never by name — R48) across all
  218 binaries, and the S1 checker. One masked pass per translation unit yields every instance's source form (`macro` / `macro-param` /
  `include` / `param-include` / `def` / `stub` / `asm-verbatim`); a sig instance with zero or two forms fails the run (R32 — the
  first run found 2,360 K&R definitions the scanner could not see; the last found 0 of 362,389). Verdicts A/B/C/D/M and flags
  E/F/TWIN-COVERED/TWIN-PENDING/TYPEDEF/PINS/ALIAS as in the docstring. The fleet, the source dirs, the contracts (`<alias>_CHECK_SHA`),
  the address spaces (`<alias>_VRAM_BASE`) and the twin sets (equal contracts) are derived from the Makefile and `config/` (R33);
  groups only through `dedup_integrate.group_members`. `--check` (exit code) = S1 with `config/dedup_exceptions.tsv` as the ledger
  (`h_exact  reason  nins  instances  note`; reason codes in the file header); `--strict-macros` / `--strict-text` are the
  post-conversion halves (T7 wires them into `tools-health`); `--scope all` counts the deferred cross-address classes as violations.
  `--selftest` is the R39 fixture (7 verdicts + the scanner on a synthetic TU). Outputs under `.run/P35/census/`: `share_census.json`
  (summary + controls), `share_census.txt` (the table), `coverage_notes.txt` (tracked); `classes.jsonl` and `cache/` (ignored).
  **Measured S94 on the pre-conversion tree:** 10,180 classes; A 1,712 · B 282 · C 6,107 · D 1,861 · M 218; same-vram unregistered
  4,667 classes / 11,767 private copies; cross-address deferred 3,801 classes; 43 s (16 workers).

