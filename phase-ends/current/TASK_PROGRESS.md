# TASK_PROGRESS — T16 attempt 1

Task: T16 the tracing pilot: the largest family's model and the wave projection
Attempt: 1   Agent: pa-expert   Ctx at handoff: ~190k   Commit: 957d856a21 (+ this commit)
Why stopped: developer correction 2026-11-16 (Windows restart): pause all work now, return. Not a context handoff.

## Done so far
- Sample (done-when 1): 121 types (.run/3.45/t16/sample.tsv, sample.py seed 345016): core 57 (800B5CB8, 80126B58, 3 player cocasts, 52 C1) + 64 views (bands 1, 2, 3-5, 6+ x kinds param(4)/local/global/field/return(3)). Inputs regenerated at HEAD 803d7ec9f6: .run/3.45/t16/src0/ (--sources), inv.tsv.
- Judges c1-c4 (read-only, parallel): 132 rows over 120 types (.run/3.45/t16/c{1..4}/judgments.tsv, model.tsv, notes.md; merged all.tsv): absorb 108, fold 12, survivor 10, refuse 2. Cost: c1 17 types 11 min 178k tok; c2 40 / 7 min / 179k; c3 31 / 13 min / 184k; c4 32 / 14 min / 189k.
- Expert decisions: .run/3.45/t16/decisions.tsv (A 85 type-level absorbs, S 21 per-source, F 11, V 7, H 8 held with reason).
- Parent model (done-when 2): pools with type at +0x0 / state at +0x2; actor Unkstruct_801202A0 (0x10C x96 at 0x801202A0) flat common + gap unions extA 0x24/0x10, extB 0xA0/0x34, extC 0xE0/0x18, extD 0x100/0xA, variants k<OVL>_<FUNC>; fixed-point unions unk4/8/C/DC (.val/.i.hi); sprite Unkstruct_800B5BD8 (0x38), model Unkstruct_8001C9D0 (0x84), fx Unkstruct_8011DB30, small Unkstruct_8011D030, player Unkstruct_80126B58 grown to 0x254. Written in docs/gen3-standards.md rule 4 (worked example) — committed with this progress commit.
- Applied (done-when 3), all gates green per coder log, 0 walls, scratch_cmp identical every time:
  - c5 5e7174360d / 4eff7d005c / 1381d314c3: engine gap variants, parents, 47 A rows (pending 2914->2867).
  - c6 8fbd596ed3 / 27386bd006 / 0102d71006: leafmap + fixed point, 30 more A rows (->2837).
  - c7 1df67e0abc / 03e446178d / 97e95b3b0c: per-source fold-batch keys files; multi-parent rows; 800B5CB8 slice shared+main+resident 163 -> actor 80, sprite 14, model 4, stay 65 (->2834).
  - c8 4322b6cfe9 / f73f76198f / 36a7a758e1 / 4f72a4a357 / e7540bebef / 957d856a21: F/V rows (5 applied, 7 survivors, 6 pending with reasons; ->2822), type_visible fix for header TUs, 4 actor helpers typed `Unkstruct_801202A0 *` (2303 files, 10 P casts removed), sample keys chunk01 (182 global keys: all PENDING, 2+ cast types 129, LBlk16 not canonical 46).
- Cookbook C0624-C0627 written (committed with this commit).

## In flight
- Nothing running. c8 stopped chunk02 at key 28/182 (last ledgered `&guess_g_PlayerActor@ov_SC07_000`); tree clean, no patch needed (c8 log :34).

## Hypotheses rejected
- R3.45-013 "+0x02 is the actor kind; func_8001CB6C/CF48 init the actor" — wrong: +0x0 u16 type (func_8017849C.h:15-35), +0x2 state; those init the 0x38 sprite record; D_800B5CB8 = sprite #4.
- 800B5CB8 is one object — no: actor slot + sprite + model merged (c1 notes).

## Current hypothesis
The model holds (77/85 type-level absorbs and the per-source slice landed byte-identical). Rung T on global sources of the player pointer is pending on 2+ cast types until the player views are absorbed per source; global keys cost ~87 s each even when pending, so pre-filter (2+ cast types, alias not canonical) before the remaining chunks.

## Next 5 steps
1. Respawn reads this file, archives it (git mv to logs/T16.progress1.md), commits.
2. One coder (T16.c9): pre-filter the remaining sample keys (.run/3.45/t16/c8/chunk02.txt tail -n +29, chunk03..07: 964 keys) by the cheap pending reasons, then `--type-batch` the rest per the edit procedure (docs/ops/p345-t15-typing-engine.md:84-103), commit per chunk.
3. Same coder: task-end gates: fresh census, leverage_rank -j 16, make tools-health, `struct_twins --sources --check` AFTER and `restruct --type-check --sources-dir .run/3.45/t16/src0` into .run/3.45/t16/c8/metrics.txt.
4. Expert: pick five before/after functions (one per kind: param = a C1 handler in 03e446178d; local; global = &guess_g_PlayerActor copy; field; return), write docs/ops/p345-t16-tracing-pilot.md (model, counts, wave plan), project T17-T21 / T22-T29 from the rates below.
5. Expert: logs/T16.md, tasks/T16.md with the Review: block, task_log finish, commit, return `review`.

## Gotchas
- C0626/C0627: never adopt a view's typed pointer onto a parent `void *`; screen `->field + k` arithmetic on typed parent pointers.
- Actor-parent fold-batch component ~77 min (target walk): one batch line per parent.
- commit_task.sh sweeps phase-ends/current/logs/ into coder commits (progress note rode along in 1df67e0abc).
- casts.tsv `off` under CAST_ALIAS typed base is the macro index, not bytes.

## State to carry verbatim
- Agents (finished): judges c1 a24c87110ab029c80, c2 a44b6fff82cabda67, c3 a12deb53836746075, c4 a58d0a1eb4a139a76; appliers c5 a7e8cac3e44617f63 (3.7 h, 224k), c6 a70a81de4ff7f243f (2.26 h, 235k), c7 ab2c4d84ef6a347f5 (3.8 h, 280k), c8 a53c7d1f2b1f348d2.
- BEFORE metric: --sources 482635 casts (C 309695, P 112224, I 46489, X 10309, M 3918), 103610 sources; placeholders 2915 (pending 2914 at c5 start). After c8: pending 2822.
- F00001 (src0): 241 types, 188,398 casts; by region main+resident 143, md_* 3566, ov_MAIN 926, ov_SC01 10886, ov_SC02 24063, ov_SC03 67222, ov_SC04 18440, ov_SC05 16324, ov_SC06 32023, ov_SC07 9583, shared 5222. 800B5CB8 sources by region: SC03 4176, SC06 1799, SC02 1688, SC04 1241, SC05 1020, SC01 585, SC07 477, md_* 335, shared 142, ov_MAIN 29, main+resident 21 (11,415 left after c7).
- Research: R3.45-013 (adopted). Review must offer wave sizes and order, never a narrower finish.
