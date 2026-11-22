# TASK_PROGRESS T20.c15 (A4 batch r1 applier)
## Done so far
- 92a770e161 / 7d7e5a0c48: 49 survivors (+7 resizes), 5 scalars applied+stamped (ratchet 632).
- 18ab364e3a / 74f585171d: 19 absorbs into Ent30D80, 80034DFC, 80037F3C, 80039C70, OBJ598, Blob36, S_D2394, GroupRec (ratchet 613).
- 42b1334515 + stamp commit: PsyQ GsOT/GsOT_TAG (survivor sdk), 800CB00C + 80027C10_2 fold onto GsOT (ratchet 611).
- Every commit: unit asm 0 diffs, R22 218/218, sig_evidence 0 failed, gates RC 0 (after twins --write + census rerun).
## In flight
- nothing uncommitted (no patch).
## Hypotheses rejected with evidence
- 800CAE74_3 all-pointer retype: slt -> sltu (md_MAIN_031); fixed with (s32)p compare.
- U2 as (s16)D_80078EA6: CSE drops the reread (ov_SC03_006_after asm); asm alias aD80078EA6 identical.
- Blk36_800296F8 survivor: census dup_classes=1 (tier-1 class with G4, SW20); row reverted to apart.
- kind 680 word union at +0xFC: needs 6,970 unkFC/unkFE lines in 591 files respelled (no anonymous unions in cc1 2.7).
## Current hypothesis
- OtBlk -> GsOT +0x4 via asm-alias extern keeps bytes (func_80015498 probe: cc1 asm differs only in symbol name, same address).
## Next 5 steps
See .run/3.45/t20/c15/progress.md (OtBlk fleet, Vec role 2, F3 LINE_G2 site, Obj_80015760 RenderWork member, kind 680 decision).
## Gotchas
- remapcites exactly once per chunk (resetcites HEAD first; skip the chunk's new rows); then recite.py.
- gcc probe messages use unicode quotes.
- New PsyQ types need ledger rows (not in struct_twins.PSYQ).
## State to carry verbatim
- pending_types 611; HEAD snapshot for asm diffs: .run/3.45/t20/c15/head (archive of 3ef9172742, refresh before next chunk).
