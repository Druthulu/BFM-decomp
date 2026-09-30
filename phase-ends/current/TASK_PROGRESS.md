# TASK_PROGRESS — T3 attempt 1

Task: T3 head-type layouts and canonical files
Attempt: 1   Agent: expert-fable   Ctx at handoff: n/a   Commit: 1a35655ab (last coder), this handoff commit follows

## Done so far
- Census refreshed with `--sites` into `.run/P37/census` (restruct's hard-coded input dir) at HEAD 42a9cd7f5: run `census_t3` → `.run/logs/census_t3.log`; heads separate again (`Unkstruct_800B5CB8` 107,580 sites/11,184 bodies, `Unkstruct_80126B58` 65,397/17,047; 18,739 types); the P37 T4e census had them merged as `Unkstruct_800D3888` (stale `body_base_type.json`, now regenerated).
- c1 5aaa25154: `tools/head_types.py` (max-site split, weighted-interval DP over layout ∪ conflicts; `--header`, `--decisions`, `--selftest`), `include/struct_types.h` (generated block, both heads), `docs/struct-map-decisions.md` (skeleton + generated per-offset block), `include/common.h:64` includes struct_types.h, `CANON_HEADERS = (engine_types.h, include/struct_types.h)`; audit-types 26 (0 in new file), selftests 24/54, R22 green.
- c2 e4341ee11: `tools/delever.py includers()` follows `-Iinclude` (relative first, else include/x; scans include/*.h; cache key "I|"); hand-written `Unkstruct_80078E78` (0x98, evidence-named fields) in struct_types.h; `src/800.c:8` `typedef Unkstruct_80078E78 Blk98_80029274;` (R22 byte-identical, not reverted); decisions doc's three hand sections filled (canonical file set, resolution rule, player block). R22 green.
- c3 1a35655ab: restruct `pass_hint` (:522-531 skips non-str rows; classify_residual emits aligned mnemonic rows as `pairs`, regs as `regs`), `drop_overlaps` (:698-710) → nested-base overlapping edits become KEPT(overlap-edit) instead of `Refuse:`; +2 selftests (56); snapshot-baseline at e4341ee11 (7,428 objects, 218/218) + calibrate 146/146 identical, positive control DIFFERS; `--selftest --real` 61/61 OK, linked-control OK.
- Exemplar proofs (all `final IDENTICAL`, 0 TYPE-NOT-VISIBLE, logs `.run/logs/t3c3_try_1..9.log`): 800B5CB8 → ov_SC06_032_jr_80182890 (MEMBERS 123, S2 7), ov_SC02_027_jr_8017D898 (193/4), md_SC07_004 (220/17), md_SC07_003 (82/2), src/800.c main (108/10); 80126B58 → ov_MAIN_012_jr_8015A3C8 (104/5), ov_SC03_107_jr_8015A3C8 (102/4), md_MAIN_046 (24/3), md_MAIN_036 (15/2). 80126B58 has 0 main bodies (map), so no main exemplar exists for it.

## In flight
- verify command running detached: `bash tools/run.sh --wait t3_verify --max 280` (repeat) → `.run/logs/t3_verify.log`; expected `restruct --selftest --real: 61/61 OK`, `extract-all: 217 extracted, 0 failed of 217`, `check-all: 218 passed, 0 failed of 218`. Started at HEAD 1a35655ab, clean src/.
- Uncommitted tracked-but-gitignored outputs: `.run/P37/census/{struct_map_top.json,type_census.json,type_census.txt}`, `.run/P36/delever/calibration.json`, `docs/struct-map.md` (regenerated) — commit with `git add -f` first (T1 gotcha), then commit_task.
- Not yet written: `phase-ends/current/logs/T3.md`, `phase-ends/current/tasks/T3.md`.

## Hypotheses rejected
- "Unkstruct_80078E00 exists in the preview / the map" — preview ov.h has only 800B5CB8, 80126B58, 8018E71C, dac960ce, 0caecd54, f8ed2b9f; map has no cluster at 0x80078E00; `D_80078E00` 0 occurrences in src (`.run/P38/T3/player_vs_heads.py`: of 9 scalar player globals, 1 agrees with 80126B58, 0 with 800B5CB8; both heads have s32 at +0xB4 where hp_current is u16).
- "actor-struct.md describes a head layout" — no; the code's player record is `Blk98_80029274` (0x98 at 0x80078E78, src/800.c) / `Blk80078E78` (resident_jr_800D00E4.c:546) / `u8 D_80078E78[]` in 880 TUs.
- "a type in include/ is visible to restruct" — was false: `delever.py:663-674` resolved includes relative-only and never scanned include/ (fixed in c2).
- "`--try-file` crashes are caused by the new include graph" — c2 reproduced both crashes with HEAD~1's graph; pre-existing (fixed in c3).

## Current hypothesis
All done-when clauses hold except the literal name `Unkstruct_80078E00` (defined as `Unkstruct_80078E78` by evidence; a deviation, not a redefinition) and "one main TU" for `Unkstruct_80126B58` (0 main bodies in the map). The verify run should be green; then only the log, summary, commit and return remain.

## Next 5 steps
1. `bash tools/run.sh --wait t3_verify --max 280` until done; read the three result lines; if red, report as failure with the output (do not weaken).
2. `git add -f .run/P37/census/struct_map_top.json .run/P37/census/type_census.json .run/P37/census/type_census.txt .run/P36/delever/calibration.json` then include `docs/struct-map.md` in the commit paths.
3. Write `phase-ends/current/logs/T3.md` (timeline above; retriever questions: 3 retriever-code, no report ids; scripts in `.run/P38/T3/`), and `phase-ends/current/tasks/T3.md` from `templates/task.template.md` (≤150 lines; Verified line from step 1; Deviations: Unkstruct_80078E78 not _80078E00; no main exemplar for 80126B58; include/ canonical file instead of per-space files; two restruct fixes + delever include fix outside the plan's file list; gotchas: `harness:` comment text `/* 0xNN */` inside a C comment kills the build; `generalizable:` include graph must model -Iinclude; `binding:` head-type overlaps resolve by max-site split, unions deferred; `Next task needs:` Unkstruct_800B5CB8 is a suspect merged cluster (25 % dropped sites) → T5 split candidate; REFUSED bodies = per-candidate compile errors (e.g. md_MAIN_036:300 `ar46E98` undeclared)).
4. `PY tools/task_log.py finish T3`; `git mv phase-ends/current/TASK_PROGRESS.md phase-ends/current/logs/T3.progress1.md` (respawn does this first); `bash tools/commit_task.sh T3 "head types canonical; include graph, try-file fixes; log and summary" docs/struct-map.md`.
5. Return the expert contract (STATUS done, COMMIT hash, MILESTONE n/a).

## Gotchas
- The expert's Bash hook denies reading tool sources even by range; code facts come from retriever-code.
- `restruct` reads `.run/P37/census/*` (hard-coded), not `.run/P38/census`; cluster names change when membership changes (lowest AT global).
- `restruct --selftest --real` fails on stale calibration after any commit that moved HEAD ("calibrated at X, HEAD is Y"): snapshot-baseline + calibrate on a clean green tree first.
- `--try-file` on the 9 exemplars takes 1.5–125 s each; run through run.sh.
- commit_task.sh refuses gitignored-but-tracked paths; `git add -f` them first.

## State to carry verbatim
- Commits: c1 5aaa25154, c2 e4341ee11, c3 1a35655ab. Census head 42a9cd7f5.
- head_types summary lines: `Unkstruct_800B5CB8: fields=101 kept_sites=75717 dropped_sites=25393 conflict_offsets=50 overlaps=167 misaligned=4 union_candidates=27`; `Unkstruct_80126B58: fields=152 kept_sites=61599 dropped_sites=1713 conflict_offsets=50 overlaps=71 misaligned=5 union_candidates=4`.
- Per-space bodies: 80126B58 ov 16,773 · md 311 · main 0; 800B5CB8 ov 15,245 · md 502 · main 22 · boot.c 1.
- Verify log: `.run/logs/t3_verify.log`. Coder logs: `phase-ends/current/logs/T3.c1.md`, `T3.c2.md`, `T3.c3.md`. Scratch scripts: `.run/P38/T3/{map_dump.py,bodies_by_space.py,player_vs_heads.py,player_use_widths.py}`; offsets dumps `.run/P38/T3/D_80126B58.offsets.txt`, `D_800B5CB8.offsets.txt`.
- Known-true control line from `--selftest --real`: "known-true p[1]/p[2]: whole-object DIFFERS · reloc-only True · linked IDENTICAL"; linked-control OK.

## Coder runs so far
- c1 coder-opus55 — done 5aaa25154 — logs/T3.c1.md
- c2 coder-opus55 — blocked (tool bugs), committed e4341ee11 — logs/T3.c2.md
- c3 coder-opus55 — done 1a35655ab — logs/T3.c3.md

## Reports commissioned
- none (three retriever-code answers under 300 lines, no report ids)
