### §P37 S106 — 2026-09-12: the probe and the rewrite engine's first form (Phase 37 T2)

- **`tools/restruct.py`** — `--try TU FN [--base bclass:name]` (rung 1 on one body: the type from the struct map's cluster layout —
  `u8 pad<HEX>[n]` between `unk<HEX>` fields, a misaligned entry (an `lh` at +0x79) skipped, a pointer field only where the site's pointee
  equals the field's — the sites rewritten to `((P37S_<hash> *)base)->unk<HEX>` and the typedef inserted at file scope before the
  function; judged by `delever_oracle` IN PLACE and restored, every includer for a header body; DIFFERS → `delever_search.classify` on
  the body's instructions + **rung S2** (leave-one-out, then cumulative revert in source order and minimisation → the minimal set of sites
  that must stay casts) + **S+A** (the marked levers stripped as well, `delever_search.lever_free_body`); `--probe [--sample N] [--seed K]
  [-j N]` (the stratified sample: `.c` bodies in parallel by whole file, header bodies serially after — their includers are other workers'
  files) → `.run/P37/probe/probe_rows.jsonl` + `probe_table.md`; `--rerun-differs`; `--probe-decls` (per TU × lying callee: the
  definition's ANSI signature written into the callee's lying declarations, judged; causes read from the compiler's message forms —
  R103) → `decl_table.md`; `--probe-defs` (20 TUs: a file-scope duplicate of a canonical type → `typedef <Canon> <Local>;`, judged) →
  `defs_rows.jsonl`; `--audit-layouts [-j N]` (every file-scope definition's `sizeof` and named-field offsets asserted against the
  pinned cc1 with `char x[(cond) ? 1 : -1]`, the probe TU = the TU's `#include` lines + typedefs + file-scope definitions IN SOURCE
  ORDER up to the target, block-scope typedefs and `#ifndef BFM_ENGINE_TYPES_H` standalone blocks excluded, one temp file per probe —
  R111) → `layout_audit.json`; `--fanout-cost` (one harmless typedef appended to `engine_types.h`, every includer compiled, the header
  restored). Tags passed to the oracle must not contain spaces (the scratch object path lands in the pipeline).
- **T2's measurements (S106)** — the table is in `phase-ends/CURRENT_PHASE.md` (T2's log entry) and `.run/P37/probe/*.md`.
- **`tools/type_census.py` fixes from the audit:** `__attribute__` with nested parens (`aligned(4)`) parsed, per-field `aligned(N)` raises the
  field's alignment (packed → 1 otherwise), `#ifndef BFM_ENGINE_TYPES_H … #endif` blocks blanked in a TU that includes the canonical
  header (the standalone match_one form; 27 blocks in 21 files — `mask_text` blanks the directive lines, so the ranges are read from the
  RAW text), `fn_end` on every definition record, `pos`/`end` spans on every site record, the body→base→type index
  (`body_base_type.json`, ignored) and the type id on each site.

