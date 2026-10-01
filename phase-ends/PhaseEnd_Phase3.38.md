# PhaseEnd — Phase 3.38: Struct unification (implements Gen 3.38)
Approved: 2026-09-29 | Closed: 2026-09-30 | Planner: claude-opus-5-5/medium | Tasks: 10 done, 1 superseded

## Milestone
Milestone: `make tools-health` OK and `make kit-corpus` clean at phase start (T1); `PY tools/type_census.py --check-structs` → 0 duplicate-layout classes, 0 definitions outside the canonical type files, 0 dead names, 0 variant names, 0 legacy `pad<SIZE>` names, 0 parse-error (type-not-visible) declarations, controls 4/4 (from 7,255 defs / 206 dup classes / 40 variant camps / 26 `pad<SIZE>`); R22 `check-all: 218 passed, 0 failed of 218` — verified by: `.venv/bin/python tools/type_census.py --check-structs` exit 0 and `make clean && make extract-all JOBS=16 && make check-all JOBS=16` exit 0 at the closing commit
Verified: `make tools-health` → exit 0 `tools-health: OK — sigs fresh; corpus(+resident) + cdecl + binaries + report(lint+dedup) + cookbook-index all green.` (run.sh tools-health, T10.c2); after the story edit `make kit-corpus` + `tool_census.py --check` → 0 gaps OK

## Tasks
- T1 — phase-start health and baselines | Done: tools-health OK and kit-corpus regenerated after repairing the PA3 migration's retired-doc breakage; R22 green; delever baseline snapshotted at a8cdd934b and calibrated; fresh P38 type-census baseline. | commit: - | tasks/T1.md | logs/T1.md
- T2 — --check-structs instrument and actor-struct fix | Done: `type_census.py --check-structs` gates the struct milestone's counts; on the T1 tree it FAILS with T1's baseline; actor-struct doc fixed so controls show 0 doc-disputed. | commit: - | tasks/T2.md | logs/T2.md
- T3 — head-type layouts and canonical files | Done: the two head types and the player block are each defined once in `include/struct_types.h` (included by `include/common.h`, so visible to ov, main and md_* alike), every overlapping offset resolved by the max-site split with a per-offset record; proven IDENTICAL on 9 exemplar TUs across ov/md/main; restruct now sees include/ and no longer refuses nested-base overlap edits. | commit: - | tasks/T3.md | logs/T3.md
- T4 — fold the head types fleet-wide (rung L) | Done: 162 of 200 local head-type definitions folded onto `Unkstruct_800B5CB8` through judged rung-L head-fold batches (accesses renamed by offset), each batch committed after its R22; 38 kept with cause; the three canonical names sit in no dup class, layout twin or variant camp. | commit: - | tasks/T4.md | logs/T4.md
- T5 — long tail: one definition per type (partial; question) | Done: 1308 types lifted to engine_types.h; pad_names 0; variants 0; dead 142→134 listed residuals; dup_classes 198 and outside_canon 3680 not reachable under the current gate definitions without violating the done-when's own "twins apart" clause. | commit: - | tasks/T5.md | logs/T5.md
- T5.1 — long tail: one definition per type (gate reading fixed) | Done: every struct type in the fleet has one definition in the canonical headers; `type_census --check-structs` gating counts dup_classes/outside_canon/dead/twins_stale/variants/pad_names all 0; R22 green. Done (cont.): the only nonzero gating count is parse_error_decls=1106, which is T6's scope (plan), so --check-structs exits 1 on that alone. | commit: - | tasks/T5.1.md | logs/T5.1.md
- T6 — declaration layer on the canonical types | Done: redrew every DECL-KEPT "type not visible", "conflicting types" and "syntax error" unit to exhaustion (9 restruct cycles, all R22 green); parse_error_decls 1106 → 0, `--check-structs` OK; residues bucketed with named causes. | commit: - | tasks/T6.md | logs/T6.md
- T7 — milestone gate and record | Done: `type_census --check-structs` exits 0 on a fresh census under the ratified T5.1 reading; R22 218/218; selftests, calibration and lever_progress OK; struct map and levers rendered; phase cookbook entries C0510-C0513 added. | commit: - | tasks/T7.md | logs/T7.md
- T8 — docs/formats.md: LIST.CD verified on US, runtime reader, repack note, LZSS ring + terminator rules | Done: docs/formats.md §2.1/§2.2/§2.3/§4.1/§4.4/§4.6 now state the LIST.CD layout as verified on US, name the runtime reader (LoaderInitFileTable 0x8001971C → cdFileLocTable 0x800AE830, looked up by ResourceGetCdLoc 0x8001B788), correct the TOC length field, add the repack note, the uncleared-ring rule and the type-4 terminator-sector rule. | commit: - | tasks/T8.md | logs/T8.md
- T9 — story §10 + retrospective §7 for P37 T5-close, PA3 migration and P38 | Done: story §10 and retrospective §7 now cover the end of old P37 (T4 close, the 17-day gap, the re-scope), the PA3 migration's four breakages, and P38 with start-to-end counts; §7 heading Phases 35-38; timeline regenerated (79 rows). | commit: - | tasks/T9.md | logs/T9.md

## Decisions that still bind
- T1 — tool_census builds the kit corpus from git-tracked files only; an untracked file (e.g. PhaseEnd_Phase37.md) never enters the kit.
- T2 — every "latest ledger verdict" reader goes through `restruct.ledger_latest`; no second filter.
- T3 — head-type width conflicts resolve by the max-site split (the width most sites use wins the offset; the losers are recorded per offset in docs/struct-map-decisions.md); unions are deferred until a reader-facing reason appears (27 union candidates on 800B5CB8, 4 on 80126B58 listed there).
- T3 — the canonical file for cross-space types is `include/struct_types.h` reached through `include/common.h`, not per-space files — the map shows one layout per head across ov, md_* and main, so a per-space file would be a duplicate by construction.
- T4 — a head fold is keyed by the canonical NAME and layout SIZE, not by layout hash; non-head objects of the same size are excluded by name glob with a cause (`HF_EXCLUDE`: Blk152* copy blob, Fr_* stack frame); width/sign mismatches are left to the byte judge, never refused up front.
- T5 — a divergent-layout local of a VARIANT name is renamed `<Name>_<suffix>` (TU suffix); the canon/most-used layout keeps the name.
- T5.1 — tier-2 (all-placeholder) duplicate layouts are either folded (SHARED evidence) or listed in docs/struct-twins.md with a per-class cause; regenerate with struct_twins.py --write after every fold.
- T5.1 — the census layout hash includes alignment attrs (packed/aligned); two defs differing only in attrs are different types.
- T8 — repacking contract lives in docs/formats.md §2.1 (rebuild .CD TOC, LIST.CD, ISO directory records; EDC/ECC for raw 2352-byte images) and §4.6 (type-4 terminator must fall in the entry's last payload sector).
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

## Rules proposed
- (none)

## Cookbook entries added
- (none)

## Research
R3.38-001 | remaining work after P37 close (T5-T10, P35/P36 end-state, Gen3 roadmap, constraints, open decisions) | What remains after Phase 37; shape of next generation | phase37, phase38, structs, gen3, roadmap, constraints | retriever-digest | 2026-09-29 | 35 lines
R3.38-002 | dup-class tiers, dead_canon_names, outside_canon, check-structs, selftest, lift_types scope | type_census / lift_types mechanics | type_census, lift_types, tier, dead_canon, check-structs | retriever-code | 2026-09-30 | 31 lines
R3.38-003 | terse chronological digest of T5.1 coder logs for writing logs/T5.1.md and tasks/T5.1.md | T5.1 coder-log digest (c1..c8) | T5.1, bfm-decomp, type_census, lift_types, struct_twins | retriever-digest | 2026-09-30 | 41 lines

## Audit
- seed: median 24k, max 26k, n=17 (phase 3.38)
- CLAUDE.md: 909 bytes
- .claude/skills/commit-task-autostage/SKILL.md: 1024 bytes
- .claude/skills/project-architect/SKILL.md: 12987 bytes
- .claude/skills/restruct-cycle-watch/SKILL.md: 1119 bytes
- .claude/skills/retire-doc-consumers/SKILL.md: 927 bytes
- .claude-state/memory/MEMORY.md: 76 bytes
- HOW_WE_WORK.md: 6192 bytes
- cookbook/INDEX.md: 244246 bytes
- rules/INDEX.md: 14164 bytes
### Carry audit — phase 3.38 (2026-09-30T01:21:01Z → open UTC, 1 sessions, 2659 requests)

| file (read) | chars | n |
|---|---|---|
| restruct.py | 270.4k | 54 |
| type_census.py | 198.6k | 44 |
| lift_types.py | 190.4k | 19 |
| 800.c | 65.1k | 12 |
| formats.md | 41.8k | 9 |
| PHASE_PLAN.md | 34.9k | 3 |
| struct_twins.py | 33.2k | 8 |
| bxlfdjzu2.txt | 29.3k | 1 |
| struct_layout.py | 26.7k | 7 |
| story.md | 25.2k | 2 |
| file (write) | chars | n |
|---|---|---|
| lift_types.py | 65.2k | 14 |
| restruct.py | 56.0k | 48 |
| struct_twins.py | 30.8k | 21 |
| type_census.py | 29.6k | 34 |
| analysis-readme-story.md | 14.3k | 1 |
| story.md | 11.7k | 4 |
| head_types.py | 10.5k | 1 |
| retriever-digest-t51-coder-logs-digest.md | 9.1k | 1 |
| result kind | chars | n |
|---|---|---|
| Read | 1.3M | 249 |
| bash other | 1.1M | 805 |
| run.sh | 295.1k | 368 |
| tools/card.py | 228.8k | 18 |
| tools/type_census.py | 129.1k | 72 |
| tools/restruct.py | 127.1k | 57 |
| Grep | 125.4k | 56 |
| tools/outline.py | 119.9k | 18 |
| tools/plan_edit.py | 95.1k | 38 |
| tools/lift_types.py | 78.8k | 38 |
- spilled: 2 results, 65.9k chars on disk, 0 read whole
- whole reads over 20.0k: 0
- seed floor: retriever-code 5,364 (n 8, prev —) · retriever-digest 5,577 (n 5, prev —)
- outline credit: 34 outlines · 23 followed by a ranged read · 1.3M chars credited
- warm pings: 132 pings over 7 runs, 25 warmed waits over the TTL, rewrites across warmed waits 0, waits past the cap 3, pings cost $2.8878 vs rewrites replaced $14.5215, cheaper than one rewrite: yes
- toasts by cause (waiting): question 3, review 1, replan 0, permission 4, input 0, discussion 14, crash 0, idle 0, stop 0, subagent-stop 0, model 0, other 0
- router turns by cause: loop 59, relay 131, re-arm 30, other 20, relay cost $9.6458
- retriever re-asks: 3 of 10 retriever briefs repeat a lookup of the same run
- router: pa-session bb1f13fc · requests 470 · ctx at end 286.2k · growth T1 +11.8k, T1 +2.7k, T2 +4.0k, T3 +4.7k, T3 +2.9k, T4 +15.4k, T5 +10.1k, T5.1 +76.2k, T5.1 +9.9k, T5.1 +4.5k, T6 +22.8k, T7 +1.9k, T8 +3.0k, T8 +7.4k, T9 +2.5k, T10 +5.2k · top: other 35.1k/173, Agent 26.2k/25, tools/plan_edit.py 12.8k/24, tools/managed.py 2.7k/2, run.sh 2.1k/1
- noise: 91 lines 6.7k chars — usage: : 69 lines/4.5k, No such file or directory: 22 lines/2.2k
- price: read $0.20/Mtok · 1h write $6.96/Mtok · output $17.39/Mtok (phase model mix)
- median requests after a read: 3
- carry/request: 1532 chars, 2659 requests
- flag: 159 tool-source reads by coder-opus55, critic, expert-opus55, retriever-code
  /home/musashi/bfm-decomp/tools/lift_types.py  18.1k chars  coder-opus55
  /home/musashi/bfm-decomp/tools/build_engine_types.py  4.2k chars  coder-opus55
  /home/musashi/bfm-decomp/tools/build_engine_types.py  2.9k chars  coder-opus55
  /home/musashi/bfm-decomp/tools/lift_types.py  23.1k chars  coder-opus55
  /home/musashi/bfm-decomp/tools/lift_types.py  3.7k chars  coder-opus55
  /home/musashi/bfm-decomp/tools/lift_types.py  2.2k chars  coder-opus55
  /home/musashi/bfm-decomp/tools/restruct.py  16.1k chars  coder-opus55
  /home/musashi/bfm-decomp/tools/restruct.py  9.8k chars  coder-opus55
  /home/musashi/bfm-decomp/tools/restruct.py  4.9k chars  coder-opus55
  /home/musashi/bfm-decomp/tools/restruct.py  4.0k chars  coder-opus55
  /home/musashi/bfm-decomp/tools/restruct.py  2.2k chars  coder-opus55
  /home/musashi/bfm-decomp/tools/restruct.py  31.7k chars  coder-opus55
  /home/musashi/bfm-decomp/tools/restruct.py  357 chars  coder-opus55
  /home/musashi/bfm-decomp/tools/type_census.py  5.8k chars  coder-opus55
  /home/musashi/bfm-decomp/tools/struct_layout.py  11.4k chars  coder-opus55
  /home/musashi/bfm-decomp/tools/type_census.py  2.2k chars  coder-opus55
  /home/musashi/bfm-decomp/tools/restruct.py  1.2k chars  coder-opus55
  /home/musashi/bfm-decomp/tools/restruct.py  2.3k chars  coder-opus55
  /home/musashi/bfm-decomp/tools/restruct.py  1.2k chars  coder-opus55
  /home/musashi/bfm-decomp/tools/restruct.py  619 chars  coder-opus55
  /home/musashi/bfm-decomp/tools/restruct_cycle.sh  8.9k chars  retriever-code
  /home/musashi/bfm-decomp/tools/restruct.py  10.5k chars  retriever-code
  /home/musashi/bfm-decomp/tools/restruct.py  2.7k chars  retriever-code
  /home/musashi/bfm-decomp/tools/restruct.py  4.2k chars  retriever-code
  /home/musashi/bfm-decomp/tools/type_census.py  2.2k chars  retriever-code
  /home/musashi/bfm-decomp/tools/restruct.py  1.7k chars  retriever-code
  /home/musashi/bfm-decomp/tools/restruct.py  1.1k chars  retriever-code
  /home/musashi/bfm-decomp/tools/type_census.py  1.4k chars  retriever-code
  /home/musashi/bfm-decomp/tools/type_census.py  559 chars  coder-opus55
  /home/musashi/bfm-decomp/tools/type_census.py  3.3k chars  coder-opus55
  /home/musashi/bfm-decomp/tools/struct_twins.py  21.0k chars  coder-opus55
  /home/musashi/bfm-decomp/tools/lift_types.py  9.1k chars  coder-opus55
  /home/musashi/bfm-decomp/tools/lift_types.py  5.9k chars  coder-opus55
  /home/musashi/bfm-decomp/tools/type_census.py  2.8k chars  coder-opus55
  /home/musashi/bfm-decomp/tools/lift_types.py  3.5k chars  coder-opus55
  /home/musashi/bfm-decomp/tools/struct_twins.py  1.7k chars  coder-opus55
  /home/musashi/bfm-decomp/tools/struct_twins.py  2.9k chars  coder-opus55
  /home/musashi/bfm-decomp/tools/type_census.py  6.2k chars  coder-opus55
  /home/musashi/bfm-decomp/tools/type_census.py  5.5k chars  coder-opus55
  /home/musashi/bfm-decomp/tools/type_census.py  10.1k chars  coder-opus55
  /home/musashi/bfm-decomp/tools/type_census.py  3.4k chars  coder-opus55
  /home/musashi/bfm-decomp/tools/type_census.py  8.3k chars  coder-opus55
  /home/musashi/bfm-decomp/tools/restruct.py  1.8k chars  retriever-code
  /home/musashi/bfm-decomp/tools/restruct.py  1.9k chars  retriever-code
  /home/musashi/bfm-decomp/tools/type_census.py  1.2k chars  retriever-code
  /home/musashi/bfm-decomp/tools/delever.py  2.7k chars  retriever-code
  /home/musashi/bfm-decomp/tools/type_census.py  811 chars  retriever-code
  /home/musashi/.claude/projects/-home-musashi-bfm-decomp/bb1f13fc-0c2b-4cfc-9adb-4982c97e89df/tool-results/bxlfdjzu2.txt  29.3k chars  expert-opus55
  /home/musashi/bfm-decomp/tools/delever.py  2.0k chars  coder-opus55
  /home/musashi/bfm-decomp/tools/restruct.py  2.9k chars  coder-opus55
  /home/musashi/bfm-decomp/tools/restruct.py  887 chars  coder-opus55
  /home/musashi/bfm-decomp/tools/restruct.py  806 chars  coder-opus55
  /home/musashi/bfm-decomp/tools/launch.py  1.7k chars  coder-opus55
  /home/musashi/bfm-decomp/tools/tool_census.py  9.9k chars  coder-opus55
  /home/musashi/bfm-decomp/tools/tool_census.py  2.8k chars  coder-opus55
  /home/musashi/bfm-decomp/tools/tool_census.py  4.0k chars  coder-opus55
  /home/musashi/bfm-decomp/tools/type_census.py  2.2k chars  retriever-code
  /home/musashi/bfm-decomp/tools/restruct.py  10.7k chars  retriever-code
  /home/musashi/bfm-decomp/tools/struct_layout.py  6.5k chars  retriever-code
  /home/musashi/bfm-decomp/tools/restruct.py  3.8k chars  retriever-code
  /home/musashi/bfm-decomp/tools/restruct.py  4.7k chars  retriever-code
  /home/musashi/bfm-decomp/tools/restruct.py  6.5k chars  retriever-code
  /home/musashi/bfm-decomp/tools/struct_layout.py  1.5k chars  retriever-code
  /home/musashi/bfm-decomp/tools/restruct.py  5.1k chars  retriever-code
  /home/musashi/bfm-decomp/tools/type_census.py  7.3k chars  retriever-code
  /home/musashi/bfm-decomp/tools/type_census.py  2.4k chars  retriever-code
  /home/musashi/bfm-decomp/tools/lift_types.py  16.0k chars  retriever-code
  /home/musashi/bfm-decomp/tools/struct_layout.py  2.2k chars  retriever-code
  /home/musashi/bfm-decomp/tools/type_census.py  2.1k chars  retriever-code
  /home/musashi/bfm-decomp/tools/type_census.py  1.5k chars  coder-opus55
  /home/musashi/bfm-decomp/tools/struct_layout.py  3.1k chars  coder-opus55
  /home/musashi/bfm-decomp/tools/type_census.py  11.5k chars  coder-opus55
  /home/musashi/bfm-decomp/tools/type_census.py  305 chars  coder-opus55
  /home/musashi/bfm-decomp/tools/lift_types.py  9.1k chars  coder-opus55
  /home/musashi/bfm-decomp/tools/struct_layout.py  1.7k chars  coder-opus55
  /home/musashi/bfm-decomp/tools/lift_types.py  2.4k chars  coder-opus55
  /home/musashi/bfm-decomp/tools/progress.py  17.4k chars  coder-opus55
  /home/musashi/bfm-decomp/tools/readability_progress.py  9.4k chars  coder-opus55
  /home/musashi/bfm-decomp/tools/timeline.py  7.8k chars  coder-opus55
  /home/musashi/bfm-decomp/tools/timeline.py  683 chars  coder-opus55
  /home/musashi/bfm-decomp/tools/commit_task.sh  2.7k chars  coder-opus55
  /home/musashi/bfm-decomp/tools/restruct.py  6.5k chars  coder-opus55
  /home/musashi/bfm-decomp/tools/restruct.py  1.3k chars  coder-opus55
  /home/musashi/bfm-decomp/tools/restruct.py  4.5k chars  coder-opus55
  /home/musashi/bfm-decomp/tools/restruct.py  10.3k chars  coder-opus55
  /home/musashi/bfm-decomp/tools/restruct.py  2.3k chars  coder-opus55
  /home/musashi/bfm-decomp/tools/restruct.py  416 chars  coder-opus55
  /home/musashi/bfm-decomp/tools/restruct.py  5.2k chars  coder-opus55
  /home/musashi/bfm-decomp/tools/commit_task.sh  1.4k chars  expert-opus55
  /home/musashi/bfm-decomp/tools/commit_task.sh  170 chars  expert-opus55
  /home/musashi/bfm-decomp/tools/commit_task.sh  395 chars  expert-opus55
  /home/musashi/bfm-decomp/tools/type_census.py  4.6k chars  coder-opus55
  /home/musashi/bfm-decomp/tools/type_census.py  1.9k chars  coder-opus55
  /home/musashi/bfm-decomp/tools/type_census.py  23.1k chars  coder-opus55
  /home/musashi/bfm-decomp/tools/type_census.py  11.0k chars  coder-opus55
  /home/musashi/bfm-decomp/tools/type_census.py  6.7k chars  coder-opus55
  /home/musashi/bfm-decomp/tools/type_census.py  1.4k chars  coder-opus55
  /home/musashi/bfm-decomp/tools/restruct.py  3.1k chars  retriever-code
  /home/musashi/bfm-decomp/tools/restruct.py  3.5k chars  retriever-code
  /home/musashi/bfm-decomp/tools/type_census.py  7.1k chars  retriever-code
  /home/musashi/bfm-decomp/tools/type_census.py  1.7k chars  retriever-code
  /home/musashi/bfm-decomp/tools/restruct.py  7.6k chars  retriever-code
  /home/musashi/bfm-decomp/tools/restruct.py  850 chars  retriever-code
  /home/musashi/bfm-decomp/tools/type_census.py  2.7k chars  retriever-code
  /home/musashi/bfm-decomp/tools/restruct.py  1.7k chars  retriever-code
  /home/musashi/bfm-decomp/tools/restruct.py  3.6k chars  retriever-code
  /home/musashi/bfm-decomp/tools/restruct.py  1.8k chars  retriever-code
  /home/musashi/bfm-decomp/tools/restruct.py  26.1k chars  coder-opus55
  /home/musashi/bfm-decomp/tools/restruct.py  4.8k chars  coder-opus55
  /home/musashi/bfm-decomp/tools/restruct.py  7.2k chars  coder-opus55
  /home/musashi/bfm-decomp/tools/restruct.py  1.3k chars  coder-opus55
  /home/musashi/bfm-decomp/tools/lift_types.py  21.0k chars  coder-opus55
  /home/musashi/bfm-decomp/tools/build_engine_types.py  9.9k chars  coder-opus55
  /home/musashi/bfm-decomp/tools/type_census.py  4.1k chars  coder-opus55
  /home/musashi/bfm-decomp/tools/type_census.py  4.0k chars  coder-opus55
  /home/musashi/bfm-decomp/tools/type_census.py  4.4k chars  coder-opus55
  /home/musashi/bfm-decomp/tools/struct_layout.py  371 chars  coder-opus55
  /home/musashi/bfm-decomp/tools/type_census.py  3.7k chars  critic
  /home/musashi/bfm-decomp/tools/type_census.py  1.0k chars  critic
  /home/musashi/bfm-decomp/tools/struct_twins.py  3.2k chars  coder-opus55
  /home/musashi/bfm-decomp/tools/struct_twins.py  944 chars  coder-opus55
  /home/musashi/bfm-decomp/tools/struct_twins.py  983 chars  coder-opus55
  /home/musashi/bfm-decomp/tools/struct_twins.py  392 chars  coder-opus55
  /home/musashi/bfm-decomp/tools/struct_twins.py  2.1k chars  coder-opus55
  /home/musashi/bfm-decomp/tools/share_body.py  2.5k chars  coder-opus55
  /home/musashi/bfm-decomp/tools/share_body.py  4.5k chars  coder-opus55
  /home/musashi/bfm-decomp/tools/lift_types.py  32.0k chars  coder-opus55
  /home/musashi/bfm-decomp/tools/lift_types.py  2.1k chars  coder-opus55
  /home/musashi/bfm-decomp/tools/restruct_cycle.sh  8.3k chars  retriever-code
  /home/musashi/bfm-decomp/tools/restruct.py  10.0k chars  retriever-code
  /home/musashi/bfm-decomp/tools/type_census.py  5.8k chars  retriever-code
  /home/musashi/bfm-decomp/tools/type_census.py  3.4k chars  retriever-code
  /home/musashi/bfm-decomp/tools/restruct.py  5.6k chars  retriever-code
  /home/musashi/bfm-decomp/tools/type_census.py  3.6k chars  retriever-code
  /home/musashi/bfm-decomp/tools/restruct.py  1.1k chars  retriever-code
  /home/musashi/bfm-decomp/tools/restruct.py  1.3k chars  retriever-code
  /home/musashi/bfm-decomp/tools/type_census.py  2.0k chars  retriever-code
  /home/musashi/bfm-decomp/tools/restruct.py  12.1k chars  coder-opus55
  /home/musashi/bfm-decomp/tools/restruct.py  10.7k chars  coder-opus55
  /home/musashi/bfm-decomp/tools/restruct.py  1.2k chars  coder-opus55
  /home/musashi/bfm-decomp/tools/delever_search.py  2.8k chars  coder-opus55
  /home/musashi/bfm-decomp/tools/restruct.py  312 chars  coder-opus55
  /home/musashi/bfm-decomp/tools/delever_search.py  1.1k chars  coder-opus55
  /home/musashi/bfm-decomp/tools/restruct.py  1.8k chars  coder-opus55
  /home/musashi/bfm-decomp/tools/restruct.py  794 chars  coder-opus55
  /home/musashi/bfm-decomp/tools/tool_census.py  1.6k chars  coder-opus55
  /home/musashi/bfm-decomp/tools/tool_census.py  3.0k chars  coder-opus55
  /home/musashi/bfm-decomp/tools/doc_links.py  2.5k chars  coder-opus55
  /home/musashi/bfm-decomp/tools/type_census.py  7.8k chars  retriever-code
  /home/musashi/bfm-decomp/tools/type_census.py  4.8k chars  retriever-code
  /home/musashi/bfm-decomp/tools/type_census.py  9.0k chars  retriever-code
  /home/musashi/bfm-decomp/tools/type_census.py  1.6k chars  retriever-code
  /home/musashi/bfm-decomp/tools/lift_types.py  21.0k chars  retriever-code
  /home/musashi/bfm-decomp/tools/type_census.py  2.4k chars  retriever-code
  /home/musashi/bfm-decomp/tools/lift_types.py  11.2k chars  coder-opus55
  /home/musashi/bfm-decomp/tools/lift_types.py  2.1k chars  coder-opus55
  /home/musashi/bfm-decomp/tools/lift_types.py  4.8k chars  coder-opus55
  /home/musashi/bfm-decomp/tools/lift_types.py  1.0k chars  coder-opus55
  /home/musashi/bfm-decomp/tools/lift_types.py  1.9k chars  coder-opus55

## Agent runs
- - | discuss | other | claude-opus-5-5 | medium | ctx 30k | $0.195 | saved - | completed | parent bb1f13fc
- - | discuss | other | claude-opus-5-5 | medium | ctx 42k | $0.335 | saved - | completed | parent bb1f13fc
- - | coder-opus55 | coder | claude-opus-5-5 | medium | ctx 28k | $0.174 | saved - | completed | parent bb1f13fc
- T1 | expert-opus55 | expert | claude-opus-5-5 | medium | ctx 80k | $0.904 | saved $10.22 | completed | parent bb1f13fc
- T1 | discuss | other | claude-opus-5-5 | medium | ctx 46k | $0.311 | saved - | completed | parent bb1f13fc
- T1 | coder-opus55 | coder | claude-opus-5-5 | medium | ctx 87k | $1.009 | saved - | completed | parent a4558a55
- T1 | expert-opus55 | expert | claude-opus-5-5 | medium | ctx 44k | $0.260 | saved - | completed | parent bb1f13fc
- T1 | coder-opus55 | coder | claude-opus-5-5 | medium | ctx 50k | $0.341 | saved $1.99 | completed | parent a4558a55
- T2 | expert-opus55 | expert | claude-opus-5-5 | medium | ctx 51k | $0.345 | saved - | completed | parent bb1f13fc
- T2 | coder-opus55 | coder | claude-opus-5-5 | medium | ctx 66k | $0.617 | saved $9.59 | completed | parent af9331ba
- T3 | expert-fable | expert | claude-fable-5-1 | medium | ctx 168k | $3.525 | saved - | handoff | parent bb1f13fc
- T3 | retriever-code | retriever | claude-sonnet-5-5 | medium | ctx 30k | $0.123 | saved - | completed | parent a4d1bb36
- T3 | retriever-code | retriever | claude-sonnet-5-5 | medium | ctx 29k | $0.092 | saved - | completed | parent a4d1bb36
- T3 | coder-opus55 | coder | claude-opus-5-5 | medium | ctx 55k | $0.484 | saved $2.96 | completed | parent a4d1bb36
- T3 | retriever-code | retriever | claude-sonnet-5-5 | medium | ctx 17k | $0.071 | saved - | completed | parent a4d1bb36
- T3 | coder-opus55 | coder | claude-opus-5-5 | medium | ctx 52k | $0.429 | saved $0.80 | completed | parent a4d1bb36
- T3 | coder-opus55 | coder | claude-opus-5-5 | medium | ctx 75k | $0.796 | saved $27.49 | completed | parent a4d1bb36
- T3 | expert-fable | expert | claude-fable-5-1 | medium | ctx 57k | $0.822 | saved $1.83 | completed | parent bb1f13fc
- T4 | expert-opus55 | expert | claude-opus-5-5 | medium | ctx 144k | $2.926 | saved $2.84 | completed | parent bb1f13fc
- T4 | retriever-code | retriever | claude-sonnet-5-5 | medium | ctx 36k | $0.175 | saved - | completed | parent a952afd3
- T4 | coder-opus55 | coder | claude-opus-5-5 | medium | ctx 164k | $1.962 | saved $13.72 | handoff | parent a952afd3
- T4 | coder-opus55 | coder | claude-opus-5-5 | medium | ctx 94k | $0.945 | saved - | completed | parent a952afd3
- T4 | coder-opus55 | coder | claude-opus-5-5 | medium | ctx 79k | $0.753 | saved $5.14 | completed | parent a952afd3
- T5 | expert-opus55 | expert | claude-opus-5-5 | medium | ctx 86k | $0.821 | saved $2.22 | completed | parent bb1f13fc
- T5 | retriever-code | retriever | claude-sonnet-5-5 | medium | ctx 28k | $0.108 | saved - | completed | parent ae9bf3a0
- T5 | coder-opus55 | coder | claude-opus-5-5 | medium | ctx 62k | $0.580 | saved $13.39 | completed | parent ae9bf3a0
- T5 | coder-opus55 | coder | claude-opus-5-5 | medium | ctx 118k | $1.773 | saved $7.49 | completed | parent ae9bf3a0
- T5 | critic | critic | claude-fable-5-1 | medium | ctx 46k | $1.000 | saved - | completed | parent bb1f13fc
- T5.1 | expert-opus55 | expert | claude-opus-5-5 | medium | ctx 139k | $5.303 | saved - | completed | parent bb1f13fc
- T5.1 | retriever-digest | retriever | claude-sonnet-5-5 | medium | ctx 23k | $0.089 | saved - | completed | parent a869ccaf
- T5.1 | retriever-code | retriever | claude-sonnet-5-5 | medium | ctx 39k | $0.132 | saved - | completed | parent a869ccaf
- T5.1 | coder-opus55 | coder | claude-opus-5-5 | - | ctx - | - | saved $6.57 | orphaned | parent bb1f13fc
- T5.1 | discuss | other | claude-opus-5-5 | medium | ctx 43k | $0.336 | saved - | completed | parent bb1f13fc
- T5.1 | coder-opus55 | coder | claude-opus-5-5 | medium | ctx 163k | $2.272 | saved $9.04 | completed | parent a869ccaf
- T5.1 | coder-opus55 | coder | claude-opus-5-5 | medium | ctx 68k | $0.793 | saved $3.09 | completed | parent a869ccaf
- T5.1 | coder-opus55 | coder | claude-opus-5-5 | medium | ctx 163k | $4.006 | saved - | handoff | parent a869ccaf
- T5.1 | coder-opus55 | coder | claude-opus-5-5 | medium | ctx 164k | $2.670 | saved $2.79 | handoff | parent a869ccaf
- T5.1 | coder-opus55 | coder | claude-opus-5-5 | medium | ctx 163k | $4.097 | saved $14.26 | handoff | parent a869ccaf
- T5.1 | coder-opus55 | coder | claude-opus-5-5 | medium | ctx 166k | $3.433 | saved $8.67 | handoff | parent a869ccaf
- … 22 more: PY ~/.claude/pa3/pa_ledger.py report

## Discussions
- D1 | - | executed

## Deferred
- T5 | superseded — long tail — one definition per type
- from T10: timeline regenerate after the phase's last commit. (unconsumed)

## Changes
- 2026-09-29 developer: launch.py _audit_flag_line sort key made type-safe via natural_key (PhaseEnd_Phase3_5 crashed router seed after approval); fix applied outside the loop by a coder; upstream report filed by developer
- 2026-09-29 developer: added T8 — docs/formats.md: LIST.CD verified on US, runtime reader, repack note (issue #2)
- 2026-09-29 developer: T8 also corrects docs/formats.md §2.1 'length in bytes (unpadded)': lengths are multiples of 0x800 in SC01-SC07 (MAIN's are not); issue #2 reply drafted at .run/issue2-reply.md for the developer to rewrite and post
- 2026-09-29 router: T1 next -> done
- 2026-09-29 router: T2 next -> done
- 2026-09-29 router: T3 next -> done
- 2026-09-29 router: T4 next -> done
- 2026-09-30 critic: reopened T5 as T5.1 — long tail — one definition per type (gate reading fixed)
- 2026-09-30 router: developer: milestone reading for --check-structs: dup_classes gates tier-1 plus unlisted tier-2 (docs/struct-twins.md with per-class evidence); outside_canon excludes object-declaring block-scope stack frames (reported block_frames=N); dead counts intra-canon uses. Header line unchanged; verified by exit 0 under this reading
- 2026-09-30 developer: T8 also corrects docs/formats.md §4.4 (the game does NOT expect a zero-filled LZSS ring: the ring lives in scratchpad 0x1F800000 and is never cleared, so a valid stream must not read an unwritten slot) and adds to §4.6 the rule that a type-4 stream's terminator must land in the same 2048-byte sector as in the retail file (the decoder drops the rest of that sector and the loader then checks the next sector for the PAC magic; e.g. SC01.CD sub-file 1 stream must be 407,553-409,600 bytes); evidence: src/800.c LzssDecodeSector ~5465-5515, sector callback ~7198/7315, discussion of issue #2
- 2026-09-30 router: T5.1 next -> done
- 2026-09-30 router: T6 next -> done
- 2026-09-30 router: T7 next -> done
- 2026-09-30 router: T8 next -> done
- 2026-09-30 developer: added T9 — story §10 + retrospective §7 for P37 T5-close, PA3 migration and P38
- 2026-09-30 developer: added T10 — publish the P38 type census in README and timeline
- 2026-09-30 developer: T9 next -> done
- 2026-09-30 developer: developer: T10 also refreshes docs/story.md §11 Gen3 row from the P38 census (1,650 definitions, 53 listed twins, 229 lying declarations) — docs/story.md added to T10 files
- 2026-09-30 router: T10 next -> done

## Plain-English Recap
Phase 3.38 was the second half of the "structs" work in the readability generation: the game's C already compiles to the original bytes, and this phase made its data types readable by giving every struct (a C record type) one definition in a small set of shared header files instead of thousands of private copies. It started from 7,255 struct definitions with 206 groups of duplicates and 40 names that meant different things in different files, and ended with 1,650 definitions, all in the canonical headers except records declared inside function bodies, with no unexplained duplicates. The two biggest types, a 0x24C-byte entity record and a 0x10C-byte record used across the engine, were designed once in `include/struct_types.h` and folded in wherever the byte check allowed; the 53 duplicate groups that remain have no evidence that they are the same type and are listed with their reason in `docs/struct-twins.md`. Along the way the function declarations were rebuilt on the new types, which took the declarations that could not see their types from 1,106 to 0 and the declarations that disagree with their function from 1,796 to 229. Every change was checked by recompiling all 218 game binaries and comparing them byte for byte, and the phase closed with that check and the struct census both green.
