### P33 B2 (S86, 2026-09-06) — portable includes, audited
- 34 lines in 19 `src/ov_*/…_jr_*.c` files (15 binaries) carried `#include "/home/musashi/bfm-decomp/src/shared/
  engine_core.h"` (30) / `engine_types.h` (4) — the absolute spelling the jr-isolation tooling once wrote; byte-neutral
  here, a hard build failure on any other machine. Respelled to the tree's own `../shared/…` form (3,978 prior uses) and
  each of the 15 binaries re-gated (`make extract BINARY=<b> && make check BINARY=<b>`).
- `tools/audit_text_sources.py` (in `tools-health`) gained the **portable-include class**: an absolute path, an
  angle-bracket include (no system/SDK header is on the include path — the build's only include path is `-Iinclude`),
  or a quoted include that resolves to no file / outside the repo is an offender. R39 controls: 34 offenders in 19 files
  before the fix (all ABSOLUTE), 0 after; 4,299 sources scanned (the coverage line, R32).

