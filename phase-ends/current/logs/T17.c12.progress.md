# T17.c12 progress (coder handoff, 2026-11-17)

## Done so far (commits)
- 7e55b33600 setup: ledger rows for P/R/F type-level dispositions (147 rows from .run/3.45/t17/c12/upd.tsv; survivors for
  Ent_80164930_80164930 (POOL68 root), Unkstruct_8001C9D0, S8012C658, S8013A0A4, Unkstruct_8017E634, Unkstruct_801AE734),
  hand-folds (80180C28_2 unions->scalars store-only; 80166994_3 union member order; S8013A250 dead forward decl removed),
  tools/restruct.py `_fold_types_before` fix (member declarators inside inline bodies are not type names; selftest 215/215).
- 0d99a17a50 batch P: 79 player absorbs on one line + per-source Ent_801202A0, Unkstruct_8017C218_2 (6), S800D22E4 (1).
  Gates: R22 218/218, sig_evidence --check rc0, type_census OK (controls 4/4), ghidra OK, dispositions rc0, lever OK,
  check-residue uncovered 0, --gate broken 0. Hand-fold: 131 copies `else ...->unkDE = 10` -> `.unkDE.s` (walker miss).
- 98edd6777d stamps 79 rows applied:0d99a17a50 + per-source notes; ratchet pending_types 2822 -> 2737.
- e166d31cf5 batch R part 1 (not gated alone): sprite 26, small 4, POOL68 3, S8013A250->S8013A0A4, per-source 8001CD50, 800CB300.

## UPDATE (end of run): R part 2 committed 32457e37ec, gates green; stamps + ratchet (2694) committed. Nothing in flight,
no patch. Next: step 4 (Batch F). The section below is the state before that commit.

## In flight (was uncommitted, tree = R part 2)
- Model line written (9 keys, .run/3.45/t17/c12/batchM2.txt; 80180C28_2 left out: conflicts at +0x18 on the line).
- Hand-folds: 160 walker misses `((P *)*(s32 *)(x + 0x20))->F` on union fields (.run/3.45/t17/c12/fixmiss.py) + 2 manual
  (ov_SC07_002 :6169 rhs `.s`, ov_SC06_024 :3603 `unk1A.s`). R22 218/218 (log t17c12_r22_R3), sig_evidence --check rc0.
- docs/struct-twins.md `## Dead kept` + Unkstruct_8001CD50 (census dead=1 after its only source moved).
- Ledger: pending causes appended (.run/3.45/t17/c12/pend.py), survivor cites re-pointed (recite.py).
- type_census rerun was running (log t17c12_censusR2) when the handoff came.

## Hypotheses rejected (evidence)
- Typed-pointer hand-fold (A801593E4 p20 -> s32 + casts; Ent8018B390): 218/218 but --gate casts_untypeable +133, casts_C +6
  (log t17c12_gateP): reverted line-wise (.run/3.45/t17/c12/revert2.py), rows pending with cause.
- Survivor cite on a struct tag's `};` line fails the gate (must name the type): use the `struct X {` line.

## Next 5 steps
1. census OK -> `ghidra_types.py --write` + `--check`; `struct_twins.py --dispositions --check`; lever_census strict;
   `restruct.py --check-residue --forms P,I,X,M`; `--gate -j 16` (fix survivor cites with recite.py), `--gate --write-ratchet`.
2. Restore docs/progress.json, docs/struct-map.md, docs/story-timeline.* to HEAD; commit R part 2 with
   `.run/3.45/t17/c12/commit_list.py T17.c12 "<line>" <listfile>` (git status --short src include config docs).
3. `--fold-stamp` R rows: batchR3 lines 1,3,4,5 keys + batchM2 keys (36+9 minus none) applied:<R commit>; per-source notes
   for 8001CD50/800CB300; ratchet; commit.
4. Batch F: engine-clean folds Unkstruct_8017E608_2, Unkstruct_800CB82C, Blk254_80186AE4 (single dry runs 0 refusals);
   hand-folds Mat32/Dst17DC4 -> MATRIX, Blk8_801867AC -> SVECTOR; per-source F lines (Blk16 GsF_LIGHT/MATRIX/VECTOR, H16, M8)
   dry run first; the rest pending with causes (Blk20 word copies, Blk32 prim misuse in 800.c:3357-3371, ElemK variable index,
   PG4 u32 c0 vs bytes, Rec8 u16 vs s16 reads, Blk8_80133CD4 align 1 vs 2).
5. .run/3.45/t17/c12/applied.tsv and phase-ends/current/logs/T17.c12.md.

## Gotchas
- generalizable: `--fold-batch` dry run lists only the FIRST refusal of a line: run `--fold-row KEY` per key in parallel
  (xargs -P 12, ~2.4 min each) for every reason at once (.run/3.45/t17/c12/dry/).
- generalizable: type_census dup/twins_stale after an absorb: run struct_twins --write AFTER a fresh census, then census again.
- harness: single-object `make build/src/...o` fails for jtbl-derived TUs outside the binary context; judge by R22.
- harness: shell reads (cat/grep -c) of files > 20k chars are denied: use Python scripts for big file lists/edits.
