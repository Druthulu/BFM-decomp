# PhaseEnd — Phase 3.39: Casts to declared data (implements Gen 3.39)
Approved: 2026-10-02 | Closed: 2026-10-02 | Planner: claude-opus-5-5/medium | Tasks: 12 done, 1 superseded

## Milestone
Milestone: 0 uncovered raw address casts in the 4 census forms: every raw P/I/X/M site is a member access, a declared symbol, a reinterpret macro backed by its KEPT row, or covered by a latest restruct ledger RESIDUAL row naming its cause (reading A, REPLAN 2026-10-02; the canonical-types campaign that removes TYPE-NOT-CANONICAL residue is 3.40's input, sized by that ledger); `lever_census --check --strict --residue config/lever_residue.tsv` 0 (reading A, 2026-10-01; literal --strict 0 moves to 3.40); lying-decl census 0 outside ledgered exceptions; R22 218/218 — verified by: `PY tools/type_census.py --check-casts --residue` exit 0 (T10's gate: uncovered raw P+I+X+M = 0, unbacked macros 0, `types_floor_lying` 0 outside `config/lying_exceptions.tsv`), `PY tools/restruct.py --rung S --check-residue --only <seg>` exit 0 for each of `ov_*`, `md_*`, `main`, `src/shared/*`, `PY tools/lever_census.py --check --strict --residue config/lever_residue.tsv` exit 0, and `make clean && make extract-all JOBS=16 && make check-all JOBS=16` → `check-all: 218 passed, 0 failed of 218`, all at the closing commit
Verified: `PY tools/timeline.py --check && PY tools/readability_progress.py --check` → fresh (82 rows), OK last row at HEAD 20faec8d4, rc 0 (coder, before commit 2, logs/T12.c1.md); re-run by expert at 89f52cd82a: timeline fresh, readability STALE by the self-referential HEAD comparison only

## Tasks
- T1 — phase-start health, carry cleanup and baselines | Done: timeline fresh, README live (Levers 3,729), 18 stale conflicting-types rows superseded through restruct (census conflicting_types 18 → 0), tools-health OK, R22 218/218, oracle recalibrated, selftest --real 82/82; P39 census baselines below. | commit: - | tasks/T1.md | logs/T1.md
- T2 — cast and lying gate instruments, reinterpret-macro set | Done: `type_census --check-casts` gate (raw by form, macro sites vs restruct ledger, lying vs TSV), kept-cast macro set in include/common.h with five make-check proofs + one R22, `lever_census --strict --residue`, both selftests extended, caches invalidated, check-structs still 0. | commit: - | tasks/T2.md | logs/T2.md
- T3 — rung S sweep, overlays (forms P and X) | Done: every ov_* body with a P/X site has a latest rung-S ledger row (sweep t3_S1..S61, each batch R22 218/218 and committed by restruct_cycle.sh; 34,131 undrawable bodies ledgered RESIDUAL by cause); kept casts are T2 macros, all backed (unbacked 0); 17 missing fields added to Unkstruct_80126B58 in one header fan-out. | commit: - | tasks/T3.md | logs/T3.md
- T4 — rung S sweep, md_*, main and shared bodies (forms P and X) | Done: every md_*, main and src/shared/* body with a P/X site has a latest rung-S ledger row (drawn, kept, or RESIDUAL by cause); md swept in t4_md_S1..S5, main in t4_main_S1, each R22 218/218 and committed by restruct_cycle.sh; shared had nothing drawable. The fleet-wide "P/X = 0 except T5-owned" clause is not met (see Deviations). | commit: - | tasks/T4.md | logs/T4.md
- T5 — globals and absolute addresses to declared symbols (forms I and M, residual non-struct bases) | Done: forms I and M at 0 uncovered: ~1676 global/gaddr sites drawn to typed externs (R2 extern array mostly) by the recipe ladder; every refused site and every non-global I/M base is a ledger RESIDUAL with a specific cause; R22 218/218. progress: readability snapshot 'P3.39 T5: forms I/M closed' (raw I 49831, M 15129), timeline and README regenerated in the T5 commit. | commit: - | tasks/T5.md | logs/T5.md
- T6 — lying declarations to 0 outside the ledger | Done: lying 229 → 11, all 11 ledgered in config/lying_exceptions.tsv (3 callees, 4 rows); 22 of 25 (callee, def_file, kind) groups drawn by restruct rung D (def + all callers, C0508), R22 218/218; check-structs 0. progress: readability snapshot 'P3.39 T6: lying declarations ledgered (229 -> 11 ledgered)' at 9aa588736; timeline (82 rows) and README regenerated in the T6 commit. | commit: - | tasks/T6.md | logs/T6.md
- T7 — GTE to one spelling | Done: baseline measured; returned `question`: two done-when clauses, as `lever_census --strict` counts them, are unreachable without a plan change. | commit: - | tasks/T7.md | logs/T7.md
- T7.1 — GTE to one spelling (predicate read as the census documents it) | Done: direct GTE statements in bodies 492 -> 0 (inline 477 + via-per-TU 15 respelled to include/gte_inline.h calls, oracle IDENTICAL per file, R22 218/218); per-TU GTE macro defs 150 -> 0; variants live once each in the generated header under `// !FAKE:` lines; gte-levers 434 untouched and marked. progress: readability snapshot 'P3.39 T7.1: GTE to one spelling (direct GTE 492 -> 0, per-TU gte defs 150 -> 0)'; timeline and README regenerated in the T7.1 commit. | commit: - | tasks/T7.1.md | logs/T7.1.md
- T8 — pins and asm the unified types explain; residue ledger | Done: delever run over the T3-T7 bodies (gte-lever 434 -> 91, asm 1409 -> 1405, R22 218/218); every remaining pin/asm/gte-lever/per-TU asm def has a config/lever_residue.tsv row (2433 rows, 3528 sites); strict-with-residue gate rc 0 (reading A). progress: readability snapshot 'P3.39 T8: lever residue TSV (2433 rows, reading A)'; timeline and README regenerated in 822728ab44. | commit: - | tasks/T8.md | logs/T8.md
- T9 — milestone gate and record (Phase 3.39, the cast campaign, reading A) | Done: every gate of the milestone green on 3a9377c926 (src identical since T8): casts --residue 0, check-residue 0 in all four segments, check-structs 0, lever strict+residue 0, R22 218/218, tools-health OK, calibrate + selftest --real green; series rendered. progress: lever snapshot 'P3.39 close: reading A (residue 3528)' and readability snapshot 'P3.39 close: cast campaign, reading A' at 3a9377c926; levers.md, timeline (82 rows) and README regenerated in the T9 commit. | commit: - | tasks/T9.md | logs/T9.md
- T10 — residue coverage gate (--check-casts --residue) and 3.40 sizing | Done: per-site residue coverage in restruct and type_census (one shared matcher), ledger-only P/X gap closed, `type_census --check-casts --residue` gate and residue census written; on the T4 tree P/X uncovered 0, gate fails only on I/M uncovered and lying. | commit: - | tasks/T10.md | logs/T10.md
- T11 — progress snapshot and chart catch-up | Done: README Types now states the live `--check-casts --residue` gate numbers with the per-form covered/uncovered split; readability row 'P3.39 T11: chart catch-up' at e7203a358, timeline and README regenerated. progress: raw P=257,464 I=49,831 X=13,790 M=15,128 (gate, P37 census) / 336,219 four-form total (P39 census); uncovered P=0 I=0 X=0 M=0; macro sites 20,963 (unbacked 0); levers 3,711 (1,868 pins + 1,843 asm); lying 229 over 24 callees (ledgered 0); struct defs 1,650; gates passed: readability_progress --check, timeline --check, progress --readme --check. | commit: - | tasks/T11.md | logs/T11.md

## Decisions that still bind
- T1 — `timeline.py --check` compares every cell except the latest row's Commits count (self-referential: the timeline's own commit moves it).
- T2 — a kept cast is spelled only by a registered macro of include/common.h and is honest only with its ledger row; `--check-casts` is the campaign's gate, `--check` stays the broader (non-gating on block frames) reading.
- T2 — reading A for levers: `lever_census --check --strict --residue config/lever_residue.tsv` is the gate; residue rows are excluded from failures and counted in every total.
- T3 — a struct-map type with no canonical definition (TYPE-NOT-CANONICAL) is residual for rung S; its bodies get ledger-only RESIDUAL rows (`restruct --rung S --residue`), and `--check-residue` (uncovered 0) is the coverage check.
- T4 — tools/gate_main.py gates gate_lane draft slates only (it git-checkouts main TUs, conflicts with R102); main's rung-S gate is the per-object oracle plus the cycle's clean R22 (config/check.main.sha is one of the 218).
- T5 — I/M global sites close through `restruct --rung S --recipes --forms I,M` first; RESIDUAL only with the refusing recipe as cause (R2-NO-SCALAR-EXTERN, R2-WIDTH, R2-DIFFERS, R2-REKEYS, R2-COMPILE-ERROR, R2-HEADER-EXTERN, R3-NOT-CONTIGUOUS, R3-COMPILE-ERROR); non-global I/M bases close with `--residue --forms I,M`.
- T6 — a lying declaration stays only with a config/lying_exceptions.tsv row whose cause is byte evidence from a real judgement (compile error or DIFFERS object), never untried.
- T7.1 — GTE asm in a body is spelled only as a call of an include/gte_inline.h macro, except gte-lever statements awaiting T8; new spellings enter the header through `gte_consolidate --inventory && --header`, never by hand.
- T8 — per-TU asm macro definitions are ledgered as kind asm-macro rows, func = macro name, cause `asm-macro-def(<launder|instruction|barrier>)`; same-name defs in one TU share one row (157 rows for 164 defs).
- T10 — residue coverage is per site, matched on (form, normalised base, off) within the body's latest rung-S row, never on line; both gates use `restruct.residue_match`.
- T10 — a `--residue` row for a body with an existing latest S row merges (keeps KEPT/MEMBER entries and verdict) so macro backing survives.
- Kept casts and lying declarations stay only with a ledger row: rule R123 (rules_add).
- Raw cast residue is covered per site by a cause-named RESIDUAL row: rule R124.
- GTE asm in bodies is spelled only through include/gte_inline.h: rule R125.
- The lever gate is `--strict --residue config/lever_residue.tsv` until the literal 0 in 3.40, and asm-macro rows follow the T8 shape: rule R126.
- main's rung-S gate is the per-object oracle plus a clean R22, not gate_main.py (environment fact, already in docs/ops/gate-main-only-with-gate-main.md and the T4 ops note).
- `timeline.py --check` masks the newest row's Commits cell (environment fact, docs/ops/p39-t1-2026-10-01-restruct-stale-supersede-timeline-check.md).
- Next task needs: the 3.40 planner sizes the canonical-types campaign from residue_census (TYPE-NOT-CANONICAL 291,819 sites over about 13k map types, where the top 81 types cover half) and from config/lever_residue.tsv (2,433 rows, 3,528 sites, 70 tagged [3.40-agent]), which is the input for the literal `lever_census --check --strict` 0.
- Next task needs: the standing request (developer, 2026-10-02) for every phase close is to update the README graphs, story section 10 and retrospective section 7, and the wiki pages. The 3.40 planner gives it a task, as T12 did here.
- Promoted at this close: cookbook C0518-C0528, skills `tools-edit-kit-corpus` and `d1-snapshot`, rules R123-R126.

## Rules proposed
- (none)

## Cookbook entries added
- (none)

## Research
R3.39-001 | find instruments for phase 3.39 | P39 cast/lever/lying-decl instruments | type_census, lever_census, argcheck, gte_inline | retriever-code | 2026-10-01 | 21 lines

## Audit
- seed: median 14k, max 15k, n=20 (phase 3.39)
- CLAUDE.md: 909 bytes
- .claude/skills/commit-task-autostage/SKILL.md: 1024 bytes
- .claude/skills/d1-snapshot/SKILL.md: 932 bytes
- .claude/skills/project-architect/SKILL.md: 12987 bytes
- .claude/skills/restruct-cycle-watch/SKILL.md: 1119 bytes
- .claude/skills/retire-doc-consumers/SKILL.md: 927 bytes
- .claude/skills/tools-edit-kit-corpus/SKILL.md: 756 bytes
- .claude-state/memory/MEMORY.md: 76 bytes
- HOW_WE_WORK.md: 6619 bytes
- cookbook/INDEX.md: 246267 bytes
- rules/INDEX.md: 14705 bytes
### Carry audit — phase 3.39 (2026-10-01T16:13:34Z → open UTC, 1 sessions, 2521 requests)

| file (read) | chars | n |
|---|---|---|
| restruct.py | 587.7k | 139 |
| lever_census.py | 154.2k | 34 |
| gte_consolidate.py | 138.4k | 19 |
| type_census.py | 136.1k | 36 |
| PHASE_PLAN.md | 120.1k | 6 |
| restruct_cycle.sh | 32.8k | 5 |
| story.md | 32.5k | 2 |
| head_types.py | 27.9k | 4 |
| progress.py | 26.3k | 1 |
| retrospective.md | 23.5k | 2 |
| file (write) | chars | n |
|---|---|---|
| restruct.py | 86.8k | 90 |
| gte_consolidate.py | 51.7k | 38 |
| TASK_PROGRESS.md | 17.3k | 5 |
| lever_census.py | 16.3k | 17 |
| im_composition.py | 14.4k | 2 |
| type_census.py | 13.6k | 13 |
| p39_replan_edit2.py | 11.6k | 1 |
| story.md | 10.3k | 4 |
| result kind | chars | n |
|---|---|---|
| Read | 1.5M | 322 |
| bash other | 772.5k | 674 |
| tools/card.py | 335.9k | 23 |
| tools/restruct.py | 264.2k | 161 |
| run.sh | 262.5k | 325 |
| tools/plan_edit.py | 182.1k | 52 |
| Grep | 155.0k | 94 |
| tools/type_census.py | 148.9k | 62 |
| tools/outline.py | 141.4k | 18 |
| Agent | 76.7k | 73 |
- whole reads over 20.0k: 0
- seed floor: retriever-code 5,601 (n 16, prev 5,364) · retriever-digest 5,420 (n 1, prev 5,577)
- outline credit: 28 outlines · 22 followed by a ranged read · 1.5M chars credited
- warm pings: 41 pings over 11 runs, 22 warmed waits over the TTL, rewrites across warmed waits 0, waits past the cap 5, cost: pings $0.6366 + relay $2.2716 + re-arm $3.3549 = $6.2631 vs rewrites replaced $8.9103, cheaper than one rewrite: yes, undelivered 0
- toasts by cause (waiting): question 0, review 0, replan 1, permission 3, input 0, discussion 6, crash 0, idle 0, stop 0, subagent-stop 0, model 0, other 0
- router turns by cause: loop 99, relay 41, re-arm 65, other 3, relay cost $2.2716
- retriever re-asks: 3 of 14 retriever briefs repeat a lookup of the same run
- router: pa-session dd908460 · requests 377 · ctx at end 227.4k · growth T1 +8.5k, T2 +3.7k, T3 +35.1k, T3 +4.0k, T3 +6.4k, T4 +2.1k, T4 +620, T4 +18.5k, T10 +2.2k, T5 +5.5k, T5 +23.5k, T11 +1.7k, T6 +7.9k, T7 +2.2k, T7.1 +3.5k, T8 +4.1k, T8 +5.6k, T9 +5.0k, T12 +1.9k · top: other 27.8k/112, Agent 26.2k/25, tools/plan_edit.py 24.2k/22, tools/status.py 11.7k/21, Read 9.9k/2
- noise: 102 lines 7.2k chars — usage: : 86 lines/6.0k, No such file or directory: 16 lines/1.2k
- price: read $0.20/Mtok · 1h write $7.01/Mtok · output $17.53/Mtok (phase model mix)
- median requests after a read: 2
- carry/request: 1726 chars, 2521 requests (prev 912 chars, 2692 requests, growth 89.3%)
- flag: /home/musashi/bfm-decomp/tools/restruct.py read 139× / 587741 chars > audit.file_chars_flag
- flag: carry per request grew 89% vs 3.38
- flag: 2 whole-plan reads by expert-opus55, planner-phase
- flag: 256 tool-source reads by coder-opus55, critic, expert-opus55, retriever-code
  /home/musashi/bfm-decomp/tools/restruct.py  2.3k chars  coder-opus55
  /home/musashi/bfm-decomp/tools/restruct_cycle.sh  3.8k chars  coder-opus55
  /home/musashi/bfm-decomp/tools/type_census.py  9.5k chars  coder-opus55
  /home/musashi/bfm-decomp/tools/restruct.py  4.2k chars  coder-opus55
  /home/musashi/bfm-decomp/tools/type_census.py  2.0k chars  coder-opus55
  /home/musashi/bfm-decomp/tools/gte_consolidate.py  22.8k chars  coder-opus55
  /home/musashi/bfm-decomp/tools/gte_consolidate.py  12.2k chars  coder-opus55
  /home/musashi/bfm-decomp/tools/lever_census.py  5.6k chars  coder-opus55
  /home/musashi/bfm-decomp/tools/lever_census.py  7.1k chars  coder-opus55
  /home/musashi/bfm-decomp/tools/gte_consolidate.py  12.5k chars  coder-opus55
  /home/musashi/bfm-decomp/tools/gte_consolidate.py  3.7k chars  coder-opus55
  /home/musashi/bfm-decomp/tools/gte_consolidate.py  1.1k chars  coder-opus55
  /home/musashi/bfm-decomp/tools/gte_consolidate.py  3.9k chars  coder-opus55
  /home/musashi/bfm-decomp/tools/gte_consolidate.py  1.9k chars  coder-opus55
  /home/musashi/bfm-decomp/tools/gte_consolidate.py  1.4k chars  coder-opus55
  /home/musashi/bfm-decomp/tools/gte_consolidate.py  2.4k chars  coder-opus55
  /home/musashi/bfm-decomp/tools/lever_census.py  4.8k chars  retriever-code
  /home/musashi/bfm-decomp/tools/lever_census.py  2.5k chars  retriever-code
  /home/musashi/bfm-decomp/tools/lever_census.py  1.5k chars  retriever-code
  /home/musashi/bfm-decomp/tools/lever_census.py  1.8k chars  retriever-code
  /home/musashi/bfm-decomp/tools/lever_census.py  2.5k chars  retriever-code
  /home/musashi/bfm-decomp/tools/gte_consolidate.py  4.7k chars  retriever-code
  /home/musashi/bfm-decomp/tools/gte_consolidate.py  9.9k chars  retriever-code
  /home/musashi/bfm-decomp/tools/restruct.py  2.1k chars  retriever-code
  /home/musashi/bfm-decomp/tools/restruct.py  11.9k chars  retriever-code
  /home/musashi/bfm-decomp/tools/restruct.py  1.7k chars  retriever-code
  /home/musashi/bfm-decomp/tools/restruct.py  10.6k chars  retriever-code
  /home/musashi/bfm-decomp/tools/restruct.py  2.0k chars  retriever-code
  /home/musashi/bfm-decomp/tools/restruct.py  1.1k chars  retriever-code
  /home/musashi/bfm-decomp/tools/restruct.py  11.6k chars  retriever-code
  /home/musashi/bfm-decomp/tools/restruct.py  3.6k chars  retriever-code
  /home/musashi/bfm-decomp/tools/restruct.py  2.9k chars  retriever-code
  /home/musashi/bfm-decomp/tools/type_census.py  3.1k chars  retriever-code
  /home/musashi/bfm-decomp/tools/restruct.py  1.2k chars  retriever-code
  /home/musashi/bfm-decomp/tools/gte_consolidate.py  17.0k chars  coder-opus55
  /home/musashi/bfm-decomp/tools/type_census.py  1.8k chars  retriever-code
  /home/musashi/bfm-decomp/tools/type_census.py  5.0k chars  retriever-code
  /home/musashi/bfm-decomp/tools/type_census.py  1.1k chars  retriever-code
  /home/musashi/bfm-decomp/tools/type_census.py  3.0k chars  retriever-code
  /home/musashi/bfm-decomp/tools/type_census.py  1.4k chars  retriever-code
  /home/musashi/bfm-decomp/tools/type_census.py  8.5k chars  retriever-code
  /home/musashi/bfm-decomp/tools/type_census.py  1.3k chars  retriever-code
  /home/musashi/bfm-decomp/tools/type_census.py  12.6k chars  retriever-code
  /home/musashi/bfm-decomp/tools/type_census.py  1.6k chars  retriever-code
  /home/musashi/bfm-decomp/tools/argcheck.py  1.0k chars  retriever-code
  /home/musashi/bfm-decomp/tools/type_census.py  1.9k chars  retriever-code
  /home/musashi/bfm-decomp/tools/gte_consolidate.py  2.3k chars  coder-opus55
  /home/musashi/bfm-decomp/tools/gte_consolidate.py  2.6k chars  coder-opus55
  /home/musashi/bfm-decomp/tools/restruct.py  7.6k chars  retriever-code
  /home/musashi/bfm-decomp/tools/restruct.py  9.8k chars  retriever-code
  /home/musashi/bfm-decomp/tools/restruct.py  8.6k chars  retriever-code
  /home/musashi/bfm-decomp/tools/restruct.py  794 chars  retriever-code
  /home/musashi/bfm-decomp/tools/head_types.py  11.3k chars  coder-opus55
  /home/musashi/bfm-decomp/.claude/skills/restruct-cycle-watch/SKILL.md  1.2k chars  coder-opus55
  /home/musashi/bfm-decomp/tools/restruct_cycle.sh  9.1k chars  coder-opus55
  /home/musashi/bfm-decomp/tools/restruct.py  4.4k chars  coder-opus55
  /home/musashi/bfm-decomp/tools/restruct.py  2.0k chars  coder-opus55
  /home/musashi/bfm-decomp/tools/restruct.py  1.7k chars  coder-opus55
  /home/musashi/bfm-decomp/tools/restruct.py  884 chars  coder-opus55
  /home/musashi/bfm-decomp/tools/type_census.py  1.5k chars  coder-opus55
  /home/musashi/bfm-decomp/tools/type_census.py  888 chars  coder-opus55
  /home/musashi/bfm-decomp/tools/delever_cycle.sh  8.6k chars  retriever-code
  /home/musashi/bfm-decomp/tools/lever_census.py  3.6k chars  retriever-code
  /home/musashi/bfm-decomp/tools/delever.py  2.2k chars  retriever-code
  /home/musashi/bfm-decomp/tools/delever.py  2.1k chars  retriever-code
  /home/musashi/bfm-decomp/tools/lever_census.py  816 chars  retriever-code
  /home/musashi/bfm-decomp/tools/restruct.py  8.0k chars  coder-opus55
  /home/musashi/bfm-decomp/tools/restruct.py  20.3k chars  coder-opus55
  /home/musashi/bfm-decomp/tools/restruct.py  1.5k chars  coder-opus55
  /home/musashi/bfm-decomp/tools/restruct.py  11.4k chars  coder-opus55
  /home/musashi/bfm-decomp/tools/restruct.py  4.0k chars  coder-opus55
  /home/musashi/bfm-decomp/tools/restruct.py  14.2k chars  coder-opus55
  /home/musashi/bfm-decomp/tools/restruct.py  9.7k chars  coder-opus55
  /home/musashi/bfm-decomp/tools/restruct.py  12.5k chars  coder-opus55
  /home/musashi/bfm-decomp/tools/restruct_cycle.sh  9.1k chars  coder-opus55
  /home/musashi/bfm-decomp/tools/restruct.py  2.3k chars  coder-opus55
  /home/musashi/bfm-decomp/tools/restruct.py  2.2k chars  coder-opus55
  /home/musashi/bfm-decomp/tools/restruct.py  4.8k chars  coder-opus55
  /home/musashi/bfm-decomp/tools/restruct.py  1.1k chars  coder-opus55
  /home/musashi/bfm-decomp/tools/restruct.py  640 chars  coder-opus55
  /home/musashi/bfm-decomp/tools/restruct.py  1.2k chars  coder-opus55
  /home/musashi/bfm-decomp/tools/restruct.py  1.4k chars  coder-opus55
  /home/musashi/bfm-decomp/tools/restruct.py  680 chars  coder-opus55
  /home/musashi/bfm-decomp/tools/restruct.py  1.2k chars  coder-opus55
  /home/musashi/bfm-decomp/.claude/skills/restruct-cycle-watch/SKILL.md  1.2k chars  expert-opus55
  /home/musashi/bfm-decomp/tools/type_census.py  128 chars  coder-opus55
  /home/musashi/bfm-decomp/tools/lever_census.py  14.6k chars  coder-opus55
  /home/musashi/bfm-decomp/tools/lever_census.py  15.1k chars  coder-opus55
  /home/musashi/bfm-decomp/tools/delever.py  2.4k chars  coder-opus55
  /home/musashi/bfm-decomp/tools/delever.py  2.1k chars  coder-opus55
  /home/musashi/bfm-decomp/tools/lever_census.py  2.8k chars  coder-opus55
  /home/musashi/bfm-decomp/tools/lever_census.py  3.0k chars  coder-opus55
  /home/musashi/bfm-decomp/.claude/skills/restruct-cycle-watch/SKILL.md  1.2k chars  expert-opus55
  /home/musashi/bfm-decomp/tools/restruct.py  3.4k chars  expert-opus55
  /home/musashi/bfm-decomp/tools/type_census.py  2.8k chars  expert-opus55
  /home/musashi/bfm-decomp/tools/type_census.py  2.2k chars  expert-opus55
  /home/musashi/bfm-decomp/tools/timeline.py  978 chars  coder-opus55
  /home/musashi/bfm-decomp/tools/timeline.py  4.4k chars  coder-opus55
  /home/musashi/bfm-decomp/tools/timeline.py  10.2k chars  coder-opus55
  /home/musashi/bfm-decomp/tools/restruct.py  4.7k chars  coder-opus55
  /home/musashi/bfm-decomp/tools/restruct.py  1.0k chars  coder-opus55
  /home/musashi/bfm-decomp/tools/restruct.py  1.8k chars  coder-opus55
  /home/musashi/bfm-decomp/tools/restruct.py  8.3k chars  coder-opus55
  /home/musashi/bfm-decomp/tools/restruct.py  716 chars  coder-opus55
  /home/musashi/bfm-decomp/tools/restruct.py  3.6k chars  coder-opus55
  /home/musashi/bfm-decomp/tools/restruct.py  1.3k chars  coder-opus55
  /home/musashi/bfm-decomp/tools/restruct.py  4.5k chars  coder-opus55
  /home/musashi/bfm-decomp/tools/restruct.py  7.7k chars  coder-opus55
  /home/musashi/bfm-decomp/tools/restruct_cycle.sh  2.0k chars  coder-opus55
  /home/musashi/bfm-decomp/tools/lever_census.py  8.4k chars  coder-opus55
  /home/musashi/bfm-decomp/tools/lever_census.py  4.7k chars  coder-opus55
  /home/musashi/bfm-decomp/tools/lever_census.py  7.0k chars  coder-opus55
  /home/musashi/bfm-decomp/tools/restruct.py  2.1k chars  coder-opus55
  /home/musashi/bfm-decomp/tools/type_census.py  2.9k chars  coder-opus55
  /home/musashi/bfm-decomp/tools/restruct.py  3.9k chars  coder-opus55
  /home/musashi/bfm-decomp/tools/restruct.py  11.4k chars  coder-opus55
  /home/musashi/bfm-decomp/tools/restruct.py  11.0k chars  coder-opus55
  /home/musashi/bfm-decomp/tools/restruct.py  7.3k chars  coder-opus55
  /home/musashi/bfm-decomp/tools/restruct.py  4.0k chars  coder-opus55
  /home/musashi/bfm-decomp/tools/restruct.py  1.0k chars  coder-opus55
  /home/musashi/bfm-decomp/tools/restruct.py  5.1k chars  coder-opus55
  /home/musashi/bfm-decomp/tools/restruct.py  1.6k chars  coder-opus55
  /home/musashi/bfm-decomp/tools/restruct.py  816 chars  coder-opus55
  /home/musashi/bfm-decomp/tools/restruct.py  3.5k chars  coder-opus55
  /home/musashi/bfm-decomp/tools/restruct.py  2.0k chars  coder-opus55
  /home/musashi/bfm-decomp/tools/restruct.py  2.3k chars  retriever-code
  /home/musashi/bfm-decomp/tools/restruct.py  2.8k chars  retriever-code
  /home/musashi/bfm-decomp/tools/restruct.py  2.8k chars  retriever-code
  /home/musashi/bfm-decomp/tools/restruct.py  2.0k chars  retriever-code
  /home/musashi/bfm-decomp/tools/lever_census.py  14.1k chars  coder-opus55
  /home/musashi/bfm-decomp/tools/lever_census.py  2.4k chars  coder-opus55
  /home/musashi/bfm-decomp/tools/restruct.py  4.7k chars  coder-opus55
  /home/musashi/bfm-decomp/tools/restruct.py  1.6k chars  coder-opus55
  /home/musashi/bfm-decomp/tools/restruct.py  3.6k chars  coder-opus55
  /home/musashi/bfm-decomp/tools/restruct.py  4.5k chars  coder-opus55
  /home/musashi/bfm-decomp/tools/restruct.py  3.5k chars  coder-opus55
  /home/musashi/bfm-decomp/tools/restruct.py  9.6k chars  coder-opus55
  /home/musashi/bfm-decomp/tools/restruct.py  8.1k chars  coder-opus55
  /home/musashi/bfm-decomp/tools/struct_layout.py  10.1k chars  coder-opus55
  /home/musashi/bfm-decomp/tools/head_types.py  11.3k chars  coder-opus55
  /home/musashi/bfm-decomp/tools/type_census.py  1.7k chars  coder-opus55
  /home/musashi/bfm-decomp/tools/type_census.py  14.5k chars  coder-opus55
  /home/musashi/bfm-decomp/tools/type_census.py  3.7k chars  coder-opus55
  /home/musashi/bfm-decomp/tools/share_census.py  1.6k chars  coder-opus55
  /home/musashi/bfm-decomp/tools/type_census.py  3.6k chars  coder-opus55
  /home/musashi/bfm-decomp/tools/type_census.py  9.7k chars  coder-opus55
  /home/musashi/bfm-decomp/tools/type_census.py  517 chars  coder-opus55
  /home/musashi/bfm-decomp/tools/type_census.py  2.0k chars  coder-opus55
  /home/musashi/bfm-decomp/tools/type_census.py  1.7k chars  coder-opus55
  /home/musashi/bfm-decomp/tools/type_census.py  2.4k chars  coder-opus55
  /home/musashi/bfm-decomp/tools/type_census.py  16.1k chars  coder-opus55
  /home/musashi/bfm-decomp/tools/type_census.py  1.2k chars  coder-opus55
  /home/musashi/bfm-decomp/tools/restruct.py  2.0k chars  coder-opus55
  /home/musashi/bfm-decomp/tools/restruct.py  4.3k chars  coder-opus55
  /home/musashi/bfm-decomp/tools/restruct.py  2.7k chars  coder-opus55
  /home/musashi/bfm-decomp/tools/restruct.py  1.7k chars  coder-opus55
  /home/musashi/bfm-decomp/tools/restruct.py  7.4k chars  coder-opus55
  /home/musashi/bfm-decomp/tools/restruct.py  3.3k chars  coder-opus55
  /home/musashi/bfm-decomp/tools/restruct.py  405 chars  coder-opus55
  /home/musashi/bfm-decomp/tools/restruct.py  9.7k chars  coder-opus55
  /home/musashi/bfm-decomp/tools/restruct.py  13.4k chars  coder-opus55
  /home/musashi/bfm-decomp/tools/restruct.py  2.5k chars  coder-opus55
  /home/musashi/bfm-decomp/tools/restruct.py  11.2k chars  coder-opus55
  /home/musashi/bfm-decomp/tools/restruct.py  2.2k chars  coder-opus55
  /home/musashi/bfm-decomp/tools/lever_census.py  3.4k chars  coder-opus55
  /home/musashi/bfm-decomp/tools/lever_census.py  3.3k chars  coder-opus55
  /home/musashi/bfm-decomp/tools/lever_census.py  3.0k chars  coder-opus55
  /home/musashi/bfm-decomp/tools/restruct.py  12.4k chars  coder-opus55
  /home/musashi/bfm-decomp/tools/restruct.py  1.2k chars  coder-opus55
  /home/musashi/bfm-decomp/tools/restruct.py  3.4k chars  coder-opus55
  /home/musashi/bfm-decomp/tools/restruct.py  1.2k chars  coder-opus55
  /home/musashi/bfm-decomp/tools/type_census.py  6.3k chars  retriever-code
  /home/musashi/bfm-decomp/tools/restruct.py  6.4k chars  retriever-code
  /home/musashi/bfm-decomp/tools/restruct.py  4.5k chars  retriever-code
  /home/musashi/bfm-decomp/tools/restruct.py  1.3k chars  retriever-code
  /home/musashi/bfm-decomp/tools/restruct.py  297 chars  retriever-code
  /home/musashi/bfm-decomp/tools/restruct.py  4.6k chars  retriever-code
  /home/musashi/bfm-decomp/tools/restruct.py  1.8k chars  retriever-code
  /home/musashi/bfm-decomp/tools/restruct.py  3.2k chars  retriever-code
  /home/musashi/bfm-decomp/tools/restruct.py  755 chars  retriever-code
  /home/musashi/bfm-decomp/tools/restruct.py  380 chars  retriever-code
  /home/musashi/bfm-decomp/tools/gate_main.py  231 chars  retriever-code
  /home/musashi/bfm-decomp/tools/restruct.py  3.2k chars  expert-opus55
  /home/musashi/bfm-decomp/tools/type_census.py  765 chars  expert-opus55
  /home/musashi/bfm-decomp/tools/restruct.py  2.1k chars  expert-opus55
  /home/musashi/bfm-decomp/tools/restruct.py  1.8k chars  expert-opus55
  /home/musashi/bfm-decomp/tools/restruct.py  2.5k chars  expert-opus55
  /home/musashi/bfm-decomp/tools/restruct.py  1.6k chars  expert-opus55
  /home/musashi/bfm-decomp/tools/type_census.py  1.6k chars  expert-opus55
  /home/musashi/bfm-decomp/tools/readability_progress.py  7.0k chars  expert-opus55
  /home/musashi/bfm-decomp/tools/lever_census.py  841 chars  critic
  /home/musashi/bfm-decomp/tools/lever_census.py  1.9k chars  critic
  /home/musashi/bfm-decomp/tools/lever_census.py  1.9k chars  critic
  /home/musashi/bfm-decomp/tools/restruct.py  5.5k chars  retriever-code
  /home/musashi/bfm-decomp/tools/restruct.py  4.9k chars  retriever-code
  /home/musashi/bfm-decomp/tools/head_types.py  1.9k chars  retriever-code
  /home/musashi/bfm-decomp/tools/head_types.py  3.4k chars  retriever-code
  /home/musashi/bfm-decomp/tools/restruct.py  838 chars  retriever-code
  /home/musashi/bfm-decomp/tools/restruct.py  772 chars  retriever-code
  /home/musashi/bfm-decomp/tools/lever_census.py  2.8k chars  retriever-code
  /home/musashi/bfm-decomp/tools/lever_census.py  8.2k chars  retriever-code
  /home/musashi/bfm-decomp/tools/lever_census.py  1.9k chars  retriever-code
  /home/musashi/bfm-decomp/tools/lever_census.py  294 chars  retriever-code
  /home/musashi/bfm-decomp/tools/lever_census.py  6.6k chars  retriever-code
  /home/musashi/bfm-decomp/tools/restruct_cycle.sh  8.9k chars  expert-opus55
  /home/musashi/bfm-decomp/.claude/skills/restruct-cycle-watch/SKILL.md  1.2k chars  expert-opus55
  /home/musashi/bfm-decomp/tools/lever_census.py  2.4k chars  retriever-code
  /home/musashi/bfm-decomp/tools/lever_census.py  3.8k chars  retriever-code
  /home/musashi/bfm-decomp/tools/lever_census.py  7.5k chars  retriever-code
  /home/musashi/bfm-decomp/tools/gte_consolidate.py  3.3k chars  retriever-code
  /home/musashi/bfm-decomp/tools/gte_consolidate.py  13.0k chars  retriever-code
  /home/musashi/bfm-decomp/tools/gte_consolidate.py  18.6k chars  retriever-code
  /home/musashi/bfm-decomp/tools/lever_census.py  1.4k chars  retriever-code
  /home/musashi/bfm-decomp/tools/gte_consolidate.py  3.1k chars  retriever-code
  /home/musashi/bfm-decomp/tools/gte_consolidate.py  1.9k chars  retriever-code
  /home/musashi/bfm-decomp/tools/lever_census.py  2.8k chars  retriever-code
  /home/musashi/bfm-decomp/tools/commit_task.sh  515 chars  coder-opus55
  /home/musashi/bfm-decomp/tools/restruct.py  11.2k chars  coder-opus55
  /home/musashi/bfm-decomp/tools/restruct.py  5.3k chars  coder-opus55
  /home/musashi/bfm-decomp/tools/restruct.py  13.6k chars  coder-opus55
  /home/musashi/bfm-decomp/tools/restruct.py  4.6k chars  coder-opus55
  /home/musashi/bfm-decomp/tools/restruct.py  1.7k chars  coder-opus55
  /home/musashi/bfm-decomp/tools/restruct.py  1.3k chars  coder-opus55
  /home/musashi/bfm-decomp/tools/restruct.py  1.1k chars  coder-opus55
  /home/musashi/bfm-decomp/tools/restruct.py  603 chars  coder-opus55
  /home/musashi/bfm-decomp/tools/restruct.py  6.1k chars  retriever-code
  /home/musashi/bfm-decomp/tools/restruct.py  13.1k chars  coder-opus55
  /home/musashi/bfm-decomp/tools/restruct.py  9.0k chars  coder-opus55
  /home/musashi/bfm-decomp/tools/restruct.py  2.3k chars  coder-opus55
  /home/musashi/bfm-decomp/tools/restruct.py  1.4k chars  coder-opus55
  /home/musashi/bfm-decomp/tools/restruct.py  4.1k chars  coder-opus55
  /home/musashi/bfm-decomp/tools/type_census.py  2.8k chars  coder-opus55
  /home/musashi/bfm-decomp/tools/restruct.py  2.2k chars  retriever-code
  /home/musashi/bfm-decomp/tools/restruct.py  682 chars  retriever-code
  /home/musashi/bfm-decomp/tools/restruct.py  3.2k chars  retriever-code
  /home/musashi/bfm-decomp/tools/restruct.py  3.8k chars  retriever-code
  /home/musashi/bfm-decomp/tools/restruct.py  2.3k chars  retriever-code
  /home/musashi/bfm-decomp/tools/restruct.py  612 chars  retriever-code
  /home/musashi/bfm-decomp/tools/restruct.py  3.9k chars  retriever-code
  /home/musashi/bfm-decomp/tools/restruct.py  707 chars  retriever-code
  /home/musashi/bfm-decomp/tools/restruct.py  3.1k chars  coder-opus55
  /home/musashi/bfm-decomp/tools/restruct.py  1.2k chars  coder-opus55
  /home/musashi/bfm-decomp/tools/restruct.py  5.8k chars  coder-opus55
  /home/musashi/bfm-decomp/tools/restruct.py  5.7k chars  coder-opus55
  /home/musashi/bfm-decomp/tools/restruct.py  2.2k chars  coder-opus55
  /home/musashi/bfm-decomp/tools/restruct.py  9.9k chars  coder-opus55
  /home/musashi/bfm-decomp/tools/restruct.py  7.2k chars  coder-opus55
  /home/musashi/bfm-decomp/tools/restruct.py  5.5k chars  coder-opus55
  /home/musashi/bfm-decomp/tools/restruct.py  1.1k chars  coder-opus55
  /home/musashi/bfm-decomp/tools/restruct.py  480 chars  coder-opus55
  /home/musashi/bfm-decomp/tools/restruct.py  696 chars  coder-opus55
  /home/musashi/bfm-decomp/tools/restruct.py  1.9k chars  coder-opus55
  /home/musashi/bfm-decomp/tools/restruct.py  901 chars  coder-opus55
  /home/musashi/bfm-decomp/tools/progress.py  26.3k chars  coder-opus55
  /home/musashi/bfm-decomp/tools/type_census.py  3.0k chars  coder-opus55
  /home/musashi/bfm-decomp/tools/type_census.py  1.3k chars  coder-opus55

## Agent runs
- T1 | expert-opus55 | expert | claude-opus-5-5 | medium | ctx 95k | $1.695 | saved $6.16 | completed | parent dd908460
- T1 | coder-opus55 | coder | claude-opus-5-5 | medium | ctx 42k | $0.289 | saved $10.39 | completed | parent ab2ccc0e
- T1 | coder-opus55 | coder | claude-opus-5-5 | medium | ctx 26k | $0.153 | saved - | completed | parent ab2ccc0e
- T1 | discuss | other | claude-opus-5-5 | medium | ctx 40k | $0.264 | saved - | completed | parent dd908460
- T2 | expert-fable | expert | claude-fable-5-1 | medium | ctx 107k | $2.618 | saved $1.62 | completed | parent dd908460
- T2 | retriever-code | retriever | claude-sonnet-5-5 | medium | ctx 29k | $0.112 | saved - | completed | parent a0700824
- T2 | retriever-code | retriever | claude-sonnet-5-5 | medium | ctx 18k | $0.067 | saved - | completed | parent a0700824
- T2 | retriever-code | retriever | claude-sonnet-5-5 | medium | ctx 22k | $0.096 | saved - | completed | parent a0700824
- T2 | coder-opus55 | coder | claude-opus-5-5 | medium | ctx 40k | $0.273 | saved $6.26 | completed | parent a0700824
- T2 | coder-opus55 | coder | claude-opus-5-5 | medium | ctx 30k | $0.183 | saved $5.99 | completed | parent a0700824
- T2 | coder-opus55 | coder | claude-opus-5-5 | medium | ctx 78k | $0.752 | saved $12.31 | completed | parent a0700824
- T3 | expert-opus55 | expert | claude-opus-5-5 | medium | ctx 126k | $2.791 | saved $0.04 | completed | parent dd908460
- T3 | retriever-code | retriever | claude-sonnet-5-5 | medium | ctx 37k | $0.138 | saved - | completed | parent ad064e24
- T3 | coder-opus55 | coder | claude-opus-5-5 | medium | ctx 126k | $1.825 | saved $12.15 | completed | parent ad064e24
- T3 | retriever-code | retriever | claude-sonnet-5-5 | medium | ctx 17k | $0.061 | saved - | completed | parent ad064e24
- T3 | coder-opus55 | coder | claude-opus-5-5 | medium | ctx 60k | $0.590 | saved $10.50 | completed | parent ad064e24
- T3 | coder-opus55 | coder | claude-opus-5-5 | medium | ctx 86k | $1.602 | saved $3.85 | completed | parent ad064e24
- T3 | coder-opus55 | coder | claude-opus-5-5 | medium | ctx 105k | $1.529 | saved $4.80 | completed | parent ad064e24
- T3 | coder-opus55 | coder | claude-opus-5-5 | medium | ctx 83k | $0.910 | saved $8.79 | completed | parent ad064e24
- T3 | expert-opus55 | expert | claude-opus-5-5 | medium | ctx 39k | $0.352 | saved $0.30 | completed | parent dd908460
- T3 | coder-opus55 | coder | claude-opus-5-5 | medium | ctx 83k | $1.184 | saved - | completed | parent aeb8b77e
- T3 | retriever-code | retriever | claude-sonnet-5-5 | medium | ctx 13k | $0.050 | saved - | completed | parent a498ea15
- T3 | expert-opus55 | expert | claude-opus-5-5 | medium | ctx 101k | $1.784 | saved $0.46 | completed | parent dd908460
- T3 | coder-opus55 | coder | claude-opus-5-5 | medium | ctx 75k | $0.714 | saved $6.46 | completed | parent a5e316cb
- T3 | coder-opus55 | coder | claude-opus-5-5 | medium | ctx 41k | $0.337 | saved - | completed | parent a5e316cb
- T4 | expert-opus55 | expert | claude-opus-5-5 | medium | ctx 56k | $0.578 | saved - | completed | parent dd908460
- T4 | retriever-code | retriever | claude-sonnet-5-5 | medium | ctx 21k | $0.086 | saved - | completed | parent a249a71f
- T4 | coder-opus55 | coder | claude-opus-5-5 | medium | ctx 57k | $0.833 | saved - | completed | parent a249a71f
- T4 | expert-opus55 | expert | claude-opus-5-5 | medium | ctx 44k | $0.394 | saved - | completed | parent dd908460
- T4 | coder-opus55 | coder | claude-opus-5-5 | medium | ctx 42k | $0.552 | saved - | completed | parent a5185324
- T4 | retriever-code | retriever | claude-sonnet-5-5 | medium | ctx 11k | $0.040 | saved - | completed | parent ad233cc4
- T4 | expert-opus55 | expert | claude-opus-5-5 | medium | ctx 55k | $0.645 | saved $0.47 | completed | parent dd908460
- T4 | critic | critic | claude-fable-5-1 | medium | ctx 30k | $0.414 | saved - | completed | parent dd908460
- T4 | planner-phase | planner | claude-opus-5-5 | medium | ctx 60k | $0.416 | saved $0.63 | completed | parent dd908460
- T4 | retriever-code | retriever | claude-sonnet-5-5 | medium | ctx 27k | $0.090 | saved - | completed | parent abd5c715
- T10 | expert-opus55 | expert | claude-opus-5-5 | medium | ctx 57k | $0.586 | saved - | completed | parent dd908460
- T10 | coder-opus55 | coder | claude-opus-5-5 | medium | ctx 67k | $0.926 | saved $1.03 | completed | parent a5a5ce1f
- T10 | coder-opus55 | coder | claude-opus-5-5 | medium | ctx 60k | $0.537 | saved $8.47 | completed | parent a5a5ce1f
- T5 | expert-opus55 | expert | claude-opus-5-5 | medium | ctx 69k | $0.739 | saved - | completed | parent dd908460
- … 34 more: PY ~/.claude/pa3/pa_ledger.py report

## Discussions
- I1 | Phase 3.39 first task: regenerate the timeline and README after the 3.38 close (tools/timeline.py; tools/progress.py --r | planned:3.39/T1
- D1 | README debt chart tracking and P3.39 progress; keeping the developer in the loop | executed

## Deferred
- T7 | superseded — GTE to one spelling
- from T12: 3.40 planner: carry the standing phase-close docs request as a task; 3.40 inputs are named in story §10 Phase 39 part (residue_census TNC 291,819, config/lever_residue.tsv). (unconsumed)
- from D1: "uncovered" series beside raw casts in the timeline chart (so green-by-ledger does not read as debt gone) → 3.40

## Changes
- 2026-10-01 router: T1 next -> done
- 2026-10-01 router: T2 next -> done
- 2026-10-02 router: T3 next -> done
- 2026-10-02 router: T10 queued -> next
- 2026-10-02 router: T10 next -> done
- 2026-10-02 router: T5 queued -> next
- 2026-10-02 developer: added T11 — progress snapshot and chart catch-up
- 2026-10-02 developer: D1 2026-10-02: every census-moving task closes with readability_progress --snapshot, timeline.py, progress.py --readme in its commit and a 'progress:' line in its summary Done
- 2026-10-02 router: T5 next -> done
- 2026-10-02 router: T11 queued -> next
- 2026-10-02 router: T11 next -> done
- 2026-10-02 router: T6 next -> done
- 2026-10-02 critic: reopened T7 as T7.1 — GTE to one spelling (predicate read as the census documents it)
- 2026-10-02 critic: 2026-10-02 critic (T7 question): T7 -> T7.1, done-when clauses read as lever_census's own docstring defines them (direct = not via a gte_inline.h macro; per-TU defs of kind gte). T8 done-when gains: per-TU asm macro definitions (lever_census pt, the 164 non-GTE launder/instruction/barrier defs left after T7.1) reach 0 by deletion or by a residue-row shape for definitions (config/lever_residue.tsv kind asm-macro, func = macro name, strict_failures :1142-1143 matches rows instead of the synthetic entry, selftest control). Milestone gate wording unchanged: lever_census --check --strict --residue config/lever_residue.tsv exit 0.
- 2026-10-02 router: T7.1 next -> done
- 2026-10-02 router: T8 next -> done
- 2026-10-02 router: T9 next -> done
- 2026-10-02 developer: added T12 — phase-close docs: README graphs, story and hindsight lessons, wiki
- 2026-10-02 developer: 2026-10-02: before the close of every phase, update the README graphs and the story/hindsight lessons and wiki pages; T12 does it for 3.39 (standing request, carry to later phases)
- 2026-10-02 router: T12 next -> done

## Plain-English Recap
Phase 3.39 was the cast campaign: the decompiled C still read memory through raw pointer arithmetic such as `*(s16 *)(p + 0x10)`, and the goal was that every such "raw cast" either becomes a named struct member or global, or is kept on purpose with a written reason. Early on the sweep hit a wall: about 292,000 sites point into structs that have no single agreed definition yet, so the plan was changed (the "replan", reading A, 2026-10-02) to accept those sites as recorded residue, each one listed in the restruct ledger with its cause, and to leave giving those structs their canonical definitions to Phase 3.40. Under that reading the phase delivered: zero uncovered raw casts, every intentional cast spelled by one of five registered macros backed by a ledger row, lying function declarations cut from 229 to 11 (all ledgered), GTE (the PlayStation geometry coprocessor) instructions spelled one way through one header, and every remaining compiler-steering "lever" (pins and inline asm) listed in a lever residue file. All 218 game binaries still rebuild byte-identical. Raw cast counts fell from 503,016 to 336,219 overall.

Milestone verification, all at commit 78a8415257 from a clean source tree (only an unrelated discussion index line and an untracked agent file were dirty; gate outputs were restored after the run, not committed):
- `PY tools/type_census.py --check-casts --residue` exit 0: uncovered P=0 I=0 X=0 M=0, unbacked macros 0, lying 11 (ledgered 11) (.run/logs/p339_c1_casts.log).
- `PY tools/restruct.py --rung S --check-residue --only <seg>` exit 0 for `ov_*`, `md_*`, `main`, `src/shared/*`: uncovered 0 sites / 0 bodies each (.run/logs/p339_c2_resid.log).
- `PY tools/lever_census.py --check --strict --residue config/lever_residue.tsv` exit 0: residue 3528, residue-unused 0, direct GTE in bodies 0 (.run/logs/p339_c2_resid.log).
- `make clean && make extract-all JOBS=16 && make check-all JOBS=16` exit 0: `check-all: 218 passed, 0 failed of 218` (.run/logs/p339_c4_r22.log).
- `PY tools/phaseend_index.py verify` printed RED (0/1) (.run/logs/p339_close_verify.log): it parsed the whole multi-command `verified by` text as one clause and expected the check-all line in the first command's output. Its first command exited 0. Each clause was then run alone, and every one was green (above).
