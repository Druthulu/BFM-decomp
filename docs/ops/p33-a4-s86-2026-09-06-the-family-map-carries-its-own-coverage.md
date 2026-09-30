### P33 A4 (S86, 2026-09-06) — the family map carries its own coverage
- `tools/family_hseq.py` → `.run/family_hseq.json` now records `"binaries"` (the binaries it SCANNED — 217: 141 overlays +
  75 modules + the resident) and `"open_instances"`; `load()` returns `(instances, scanned)`. Reason: at 100% `families`
  is empty, and `tools/audit_binaries.py` CHECK 4 inferred coverage from family members — a regenerated, COMPLETE map read
  as "217 onboarded overlays missing" (the P32-close `[warn]` about 6 md_ binaries was the stale pre-onboarding file).
  CHECK 4 now reads `binaries` and warns "predates the coverage field" on an old-format map (R39 control run both ways).
  `docs/family-hseq.md` regenerated (0 families — the frontier is empty).

