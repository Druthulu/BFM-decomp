# T7.c11 progress (handoff at context threshold)

## Done so far (committed, green)
- engine a1c79af0c6: `--fold-batch FILE [--write]` (restruct.py fold_batch), sign union `union { s16 s; u16 u; } <name>;` (target's field name, else unk<HEX>), placement at earliest def in include order (_fold_order/_fold_defpos/_fold_types_before; P["placed"]; target row rekey), tag-only `_hf_file_edits` fix, `_fold_is_pad` (`pad` real unless byte array), struct_twins `ledger_rekey` in ledger_write. selftests 151 -> 153/153; twins 28/28.
- 9a2b90a8f9: refuse a merged member field type defined after the target (C13 broke every engine_types includer).
- 7813260d17: walker `_lvl` types `*(T **)&x`; `_extern_names` block-scope/file extern of another type shadows a global (800.c D_800A651C, 80135A4C Box, md_SC05_026 Panel cases).
- batch 1 4eea1a8a29 (24 comps / 38 rows), stamp b2fcd18448. batch 2 (C3, control target Unkstruct_80126B58) 2580f7f1f7, stamp 80b66ddcfc; controls 4/4, no re-point needed.
- gates b1 and b2: scratch 4284/4284 identical, 0 no-member; R22 218/0; census OK after census -> twins --write -> census; ghidra OK; dispositions --check rc0; sig rc0; lever rc0; rule T2 0/0/0.

## In flight (uncommitted; saved in TASK_PROGRESS.patch, also still in the tree)
batch 3 = hand folds, base 80b66ddcfc:
- C13 Blk_8016CBC0,Slot_998 -> Blk_8016CF04_8016CF04: Rec typedefs moved above target (engine_types.h), then engine fold (driver .run/3.45/t7/c11/hand_c13.py, fold_write(guard=False)).
- C12 Blk8_80126940,Blk8_8017B614 -> SVECTOR: v[0..2] -> vx/vy/vz, bare `x.v` -> `&x.vx` (4131+143 sites, hand_c12.py), then engine fold (SVECTOR unchanged). Hand fix in ov_SC06_027_jr_8017BEBC.c func_8017D104 (`L.a.v[i]` via Locs fields, walker miss).
- C37 PolyG4_80021284 -> DrMode_80021284: hand merged def (union unk4 {u32 code0; struct{u8 r0,g0,b0,code} v1}, size 0x24), 800.c respelled (hand_c37.py).
- C30 BYTES_800CFAD0 -> PrimTag: resident.c:747 `->b3` -> `((PrimTag *)&D_80114E7C)->len` (scratch identical), def deleted.
- C51 S80172C50 -> struct S8_80172780: 2 tokens (scratch identical), packed def deleted.
- C47 Owner4EE8 -> Unkstruct_8002F4E4: target pad14 -> `Rec14 **unk14`, def deleted, 9 code tokens in 800_b_2.c (size-proxy scratch identical; load-bearing check was conservative).
- C54 St_8017E95C_r -> Unkstruct_80181E08: attempt1 merged 0xf4 = DIFF (8017BEBC.o); attempt2 target grown to 0x104 (padF4[0x10]) + unk0 at 0; alias Obj80180D84 re-pointed.
- C49 S9 -> Rec9: 537 tokens in 135 files (masked-text), S9 def deleted.
- restruct ledger respelled for the hand names (ledger_subs.py, 5 rows; untracked file, not undone by a restore).
- `struct_twins --dispositions` run (file_line refresh, 3768 lines).
- gate state: full scratch 4283/4284 + fixed file identical; census after twins --write: check OK, check-structs OK, controls 4/4, BUT check-casts uncovered I=1 (FAIL). R22, ghidra, sig, lever, T2 not run.

## Hypotheses rejected
- dup/stale after b1 is twins lag: no; C17 (OtBlk union drops 0x800A651C cite from 2 apart rows) and C32 (body hash joins Unkstruct_8018A970_2/8018B354, SHARED) cause real gating classes. Excluding both made b1 green.

## Current hypothesis
- the uncovered I site comes from a batch-3 respell (likely C12 `&x.vx` or C49/C54 retype changing a census site's form/base); find it with `restruct.py --check-residue --only ov_* <non-ov TUs> --forms P,I,X,M` (lists it), then `--rung S --residue --label t7c11_b3 --only …` to cover it.

## Next 5 steps
1. find + cover the uncovered I site (rule T2: --residue, --residue --restamp, --check-residue) ; rerun census --check-casts.
2. R22 alone; ghidra --write/--check; dispositions --check; sig_evidence -j16 + --check; lever_census --check --strict --residue config/lever_residue.tsv -j 16.
3. commit batch 3 (paths: `git status --porcelain -- src include config docs/struct-twins.md`; restore docs/struct-map.md first); `--fold-stamp` the 12 hand rows (C13 2, C12 2, C37, C30, C51, C47, C54, C49) with the commit; commit.
4. wall row for C31 Q16 (disposition wall, class fold, evidence `src/shared/ov/func_8012A418.h:6 +0x0`, reason `residual:LOAD-BEARING-SIZE attempt1:retype-Q16-to-Blk164-141/141-DIFF attempt2:explicit-4-word-copy-via-Blk164-words-141/141-DIFF`; logs .run/3.45/logs/c11_c31_a1.log, c11_c31_a2.log), dispositions --check, commit.
5. C17 and C32: return as `question` to the expert (they need ledger judgments: fold Unkstruct_8018B354 into Unkstruct_8018A970_2; OtBlk_80182890_8018FB5C/OtBlk_8018FE0C lose their address cite after OtBlk_80180894 gains a union). Then inventory (`struct_twins --inventory --out .run/3.45/t7/c11/inv_b3.tsv`), make tools-health (restore progress.json, story-timeline.*, struct-map.md), log.

## Gotchas
- the hook blocks sed/cp/cat on files > 20k chars: edit big files with python scripts.
- census dup/stale needs census -> twins --write -> census.
- fold_batch's first run respelled the restruct ledger for C13/C17/C32 names that were later not committed.
- commit_task.sh stages phase-ends/current/logs/T7.progress.md.

## State to carry verbatim
- inv: before 4015 placeholders (inv_before.tsv), after b1 3977 (inv_b1.tsv); b2 not inventoried.
- --fold-batch cost: 26-27 comps 541-581 s write (dry 36 comps 1274 s); C3 alone 613-622 s (1505 files).
- scripts: .run/3.45/t7/c11/{comps.py,comps.tsv,b1c.txt,b2.txt,hand_c12.py,hand_c13.py,hand_c37.py,hand_c47.py,hand_c49.py,hand_c54.py,ledger_subs.py,edit_lines.py,cc1one.py}
