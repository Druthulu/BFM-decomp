### P32 T4c (S85, 2026-09-06) — real-TU dump instruments
- `tools/cc1_dumps_tu.sh <rtu_match --work dir> <tag>` — dumps every gcc-2.7.2 pass (-dr -ds -dj -dl -dg -df -dc -dS -dL) of the
  SPLICED REAL TU that `rtu_match --work` left behind (`<dir>/<fn>/t.c`); the standalone `tools/cc1_dumps.sh` compile is not
  faithful on main TUs. Output `${DUMP_ROOT:-.run/P32/t4e}/dumps_<tag>/`.
- `tools/alloc_table.py <tag> [fn] [dump_root]` — from those dumps, the function's global allocation ORDER with refs / live
  length / priority / hard reg (global.c `allocno_compare`); the callee-saved bank is that order (§501-R).
- `tools/cc1_dumps.sh` now also writes the `.loop` dump (`-dL`): the "not desirable"/"moved to"/"matches" lines (§501-R).

