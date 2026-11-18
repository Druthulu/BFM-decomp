# TASK_PROGRESS — T17 attempt 2 (paused by the developer, 2026-11-18)

Running note with full history: phase-ends/current/logs/T17.progress.md (read it too). Attempt 1 digest: logs/T17.progress1.md.

## Done so far
- Wave A1 = 462 types (.run/3.45/t17/a1.tsv). At pause: c24's 48 open rows -> 47 finished (c26/c26b/c26c: absorbs, folds, survivors M8/Rec8/S800D22E4/Blk20/Unkstruct_80183480, walls Mat32 WIDTH, Ent ADDRESS-FOLD, Blk16 WIDTH, Blk32 800.c WIDTH, H16 REGALLOC); Owner_8012ACE0_8012ACE0 open (S5 deferred).
- Unkstruct_800B5CB8 per-source split: c21 9,317; c22/c22b held 778 (11fdc91a64); c27 W1 865 (7d7f9f19a9) + 87 not-pool typed; `(Unkstruct_800B5CB8 *)` casts in src 12,876 -> 9,959 (W1), 9,511 with W2.
- Judges: c23 (782 decided), c25/c25b (257 decided, 213 residual: .run/3.45/t17/c25/residual3.tsv), c24/c24b (48 recipes), c28 (83 recipes: .run/3.45/t17/c28/rows.tsv, header.patch, respell.patch, kept_restamp.tsv).
- Tool: struct_twins RHS_CV/RHS_ARROW union leaf fix (35546015f7). Gate at 1ae3b6596c/7d7f9f19a9: pending_types 2353, casts_C 291368, P 94218, I 43672, untypeable 32438, broken 0.
- Cookbook C0635-C0642 banked.

## In flight
- Nothing running (pause). No background shells or builds (checked: no cc1/make/restruct/census processes).

## Uncommitted state
- c27 W2 (actor batch: 173 + 10 sources to Unkstruct_801202A0, a2 window via member:extD.kSC06_018_801932EC): 131 files in src/include/config, uncommitted; backup .run/3.45/t17/c27/W2_pause.patch. Verified: cc1 0 errors, asm identical 4121 TUs, R22 218/218. NOT run: sig_evidence write + --check, gates.sh (census, twins --write, ghidra, dispositions, lever, residue, recite, --gate, ratchet). Resume per logs/T17.c27.progress.md.
- c26c's S5 + Owner_8012ACE0 patch (not in tree): .run/3.45/t17/c26c/s5_owner.patch (1,287 files).

## Hypotheses rejected
- c22's 61 "walls" are not byte walls (no typed leaf / KEPT base / var windows): c28 gave recipes.
- Leaving c28's +0xD4/D6/D8 pointee reads as `(s32)E->unk64 + K`: rejected; unkD4 union (228 respells) instead.
- (u16) casts for M8 reads: rejected (the bar); M8 survivor as the 4 x u16 value type.

## Current hypothesis
- After W2 and c29, A1 pending = Unkstruct_800B5CB8 residual (213 c25 sources + any walls) only; carry it per R211 (A5/T21 takes A1-A4 leftovers) as a question/recommendation in the summary, or a further judge pass.

## Next 5 steps
1. A coder finishes c27 W2: sig_evidence -j 16 + --check, gates.sh, per-key revert if untypeable rises, --write-ratchet, commit the 131 files (logs/T17.c27.progress.md).
2. c29 applier: c28 recipes (header.patch, respell.patch re-anchored on the live tree, keys, kept_restamp, kind-341 and SC02_026 variant merges) + actor unkD4 union (228 respells) + S5/Owner from s5_owner.patch with func_80181824's model-data +0x50 read decided (record type or member access; no ratchet edit).
3. Count A1 pending from config/struct_dispositions.tsv vs a1.tsv; decide 800B5CB8 residual (213: not-pool done; no-caller 37, render 23, ret-of 12, holder+0xCC 12, dead-no-flow 9 ...).
4. End: leverage_rank.py -j 16, `make tools-health` (foreground), R22, restore docs noise (progress.json, story-timeline, struct-map) per Context.
5. logs/T17.md + tasks/T17.md (per batch counts, coder runs, A2 projection), task_log finish, commit, report.

## Gotchas
- Before relaunching after a developer stop, check the coder is really dead (cc1/restruct processes, scratch-dir mtimes): c26/c28 survived the first stop and were duplicated.
- commit_task.sh stages phase-ends/current/logs/ itself (T17.progress.md rides in coder commits).
- Coder handoff patches go under .run/3.45/t17/c<k>/, not logs/ (c26b's was 6.8 MB).

## State to carry verbatim
- HEAD 75896848c4 (+ this commit). Live coders: none. Coder ids: c27 ac502e9b7d4da93cc (paused, blocked report).

## Coder runs so far
- See logs/T17.progress.md "Coder runs so far" (c1-c28; this attempt: c22, c22b, c23, c24, c24b, c25, c25b, c26 (+dup), c26b, c26c, c27, c28 (+dup)).

## Reports commissioned
- none (retriever) this attempt.

## Deviations (for the summary)
- 2026-11-18 developer pause (relayed correction): c27 told to stop at its next step; W1 committed green, W2 left uncommitted with patch and note; no new coder started.
