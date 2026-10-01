MILESTONE: green

Verified: `PY tools/phaseend_index.py verify --verbose` → GREEN 1/1 (.run/logs/pe_verify.log, .run/logs/verify1.log) at 78515137ab: `.venv/bin/python tools/type_census.py --check-structs` exit 0 and `make clean && make extract-all JOBS=16 && make check-all JOBS=16` exit 0 (`extract-all: 217 extracted, 0 failed of 217`, `check-all: 218 passed, 0 failed of 218`). Fresh census of record, same tree (.run/logs/census_cs.log): `dup_classes=0 outside_canon=0 dead=0 twins_stale=0 variants=0 pad_names=0 parse_error_decls=0 controls=4/4`; non-gating `conflicting_types=18 tu_conflict=0 types_floor_lying=229 twins_listed=53 dead_kept=3 block_frames=629`. Gate reading = the ratified 2026-09-30 Changes line (listed tier-2 twins, block-scope frames and intra-canon liveness do not gate).

## Recap

Phase 3.38 was the second half of the "structs" work in the readability generation: the game's C already compiles to the original bytes, and this phase made its data types readable by giving every struct (a C record type) one definition in a small set of shared header files instead of thousands of private copies. It started from 7,255 struct definitions with 206 groups of duplicates and 40 names that meant different things in different files, and ended with 1,650 definitions, all in the canonical headers except records declared inside function bodies, with no unexplained duplicates. The two biggest types, a 0x24C-byte entity record and a 0x10C-byte record used across the engine, were designed once in `include/struct_types.h` and folded in wherever the byte check allowed; the 53 duplicate groups that remain have no evidence that they are the same type and are listed with their reason in `docs/struct-twins.md`. Along the way the function declarations were rebuilt on the new types, which took the declarations that could not see their types from 1,106 to 0 and the declarations that disagree with their function from 1,796 to 229. Every change was checked by recompiling all 218 game binaries and comparing them byte for byte, and the phase closed with that check and the struct census both green.

## Decisions that still bind

- norm: every latest-ledger-verdict reader goes through `restruct.ledger_latest` (T2) — already rule R100; no new rule.
- norm: tier-2 (all-placeholder) duplicate layouts are folded on SHARED evidence or listed in docs/struct-twins.md with a cause; `struct_twins.py --write` after every fold (T5.1) — rule R122 added.
- contract: head-type width conflicts resolve by the max-site split, unions deferred (T3) — docs/struct-map-decisions.md `## Resolution rule`.
- contract: cross-space canonical types live in `include/struct_types.h` via `include/common.h`; `CANON_HEADERS` = engine_types.h + struct_types.h (T3) — docs/struct-map-decisions.md `## Canonical file set`.
- contract: a head fold is keyed by canonical NAME and layout SIZE; `HF_EXCLUDE` globs carry a cause (T4) — docs/ops/p38-t4-2026-09-29-restruct-head-fold-mode.md:3.
- contract: VARIANT locals renamed `<Name>_<suffix>`; tag/typedef split `N_tag`/`N_td`; layout hash includes packed/aligned (T5, T5.1) — docs/struct-map-decisions.md `## Long-tail rules`, cookbook C0511.
- contract: repacking (TOC, LIST.CD, ISO records, EDC/ECC; type-4 terminator in the entry's last payload sector) (T8) — docs/formats.md §2.1, §4.6.
- environment: `tool_census` builds the kit corpus from git-tracked files only (T1) — not yet in docs/ops/tooling-inventory.md; see Next task needs.
- rules ratified this phase: R98, R99, R100, R101, R102, R103, R104, R105, R118, R119, R120, R121; added at close: R122.
- Next task needs: 53 listed tier-2 twins in docs/struct-twins.md (SEPARATE 44, UNBOUND 9) stay apart until use-site evidence binds them; refold with `lift_types --fold-class`, then `struct_twins.py --write`.
- Next task needs (3.39/3.40): 18 stale `conflicting types` ledger rows (func_800D20C0 15 .c + 1 .h, func_8012C098 1 .c + 1 .h; sources already canonical; restruct writes no row for a hand-fixed unit, so the census over-counts).
- Next task needs (3.39/3.40): 40 TU-CONFLICT rows in config/dedup_exceptions.tsv (census `tu_conflict=0` reads the restruct ledger, not these); biggest groups are the PsyQ prototypes ApplyMatrixSV (8) and RotTransPers (5); per-row causes logs/T6.c2.md.
- Next task needs (3.40): types_floor_lying 229 over 24 callees (K&R-empty 216, narrow 13); func_80146C3C left K&R-marked (zero-arg `$a0` callers in shared headers).
- Next task needs: block_frames 629 (block-scope stack frames that declare objects, non-gating) and dead_kept 3 (Unkstruct_80126B58, LineF2_8018F694, actor4c) are reported, not owed by any phase yet.
- Next task needs: docs/memory-map.md §3.2 LIST.CD RAM cache still TBD; close it from docs/formats.md §2.1 (0x80180000 staging, 0xE40 B, resolved into cdFileLocTable 0x800AE830).
- Next task needs: the tools/launch.py PhaseEnd-sort workaround (natural_key) is local; an upstream fix is expected; tools/launch.py and tools/commit_task.sh drift was declined at install; re-check both on the next PA update.
- Next task needs: regenerate the timeline (`tools/timeline.py`) and README (`tools/progress.py --readme`) after the phase's last commit (`timeline.py --check` counts same-day commits); README Levers reads 3,729.
- Next task needs: `restruct --selftest --real` reads red after any commit until R22 → `delever_oracle --snapshot-baseline` → `--calibrate ov_SC04_011 ov_SC03_015 md_SC07_004 main -j 16`.

## Deviations (H7 check)

- Summaries naming tools without HOW_WE_WORK.md or docs/ops/ in `Files:`: T2 (`type_census --check-structs`, `restruct.ledger_latest`), T3 (new `tools/head_types.py`, `delever.includers` -I, restruct overlap edits), T5 (`lift_types` scope), T6 (`share_body --only` comma prefixes), T10 (`progress.py`/`readability_progress.py` newest-census rule, `timeline.py` struct_defs column). T5.1 later added tooling-inventory rows for lift_types and struct_twins; T10 added tool_dictionary rows for head_types/struct_twins; `docs/ops/tooling-inventory.md` still has no row for head_types, ledger_latest or the T10 changes. Owed to the next phase's first tooling task.

## Audit

- `phaseend_index.py assemble` generates `## Agent runs` and the carry audit from the usage ledger; the CLI (`~/.claude/pa3/pa_ledger.py audit --phase 3.38`) was run at close and produced the `### Carry audit — phase 3.38` section (1 session, 2,620 requests; .run/logs/carry_audit.log), so the PhaseEnd_Phase37.5 audit's "no ledger" blocker (R105) does not recur. Tables as printed (chars), rows for scratch and harness spill files omitted:

### Carry audit — phase 3.38

| file (read) | chars | n |
|---|---|---|
| restruct.py | 270.4k | 54 |
| type_census.py | 198.6k | 44 |
| lift_types.py | 190.4k | 19 |
| 800.c | 65.1k | 12 |
| formats.md | 41.8k | 9 |
| PHASE_PLAN.md | 34.9k | 3 |
| struct_twins.py | 33.2k | 8 |
| struct_layout.py | 26.7k | 7 |
| story.md | 25.2k | 2 |

| file (write) | chars | n |
|---|---|---|
| lift_types.py | 65.2k | 14 |
| restruct.py | 56.0k | 48 |
| struct_twins.py | 30.8k | 21 |
| type_census.py | 29.6k | 34 |
| story.md | 11.7k | 4 |
| head_types.py | 10.5k | 1 |

| result kind | chars | n |
|---|---|---|
| Read | 1.3M | 248 |
| bash other | 1.1M | 794 |
| run.sh | 292.3k | 367 |
| tools/card.py | 228.8k | 18 |
| tools/type_census.py | 129.1k | 72 |
| tools/restruct.py | 127.1k | 57 |
| Grep | 125.4k | 56 |
| tools/outline.py | 119.9k | 18 |
| tools/plan_edit.py | 95.1k | 38 |
| tools/lift_types.py | 78.8k | 38 |

- whole reads over 20.0k: 0; spilled results read whole: 0; median requests after a read: 3; carry/request 1,540 chars.
- flag: 159 tool-source reads (coders and retrievers on restruct.py, type_census.py, lift_types.py, struct_twins.py; 2 critic reads of type_census.py); list in the ledger output.
- retriever re-asks: 3 of 10 retriever briefs repeated a lookup of the same run.
