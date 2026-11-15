# T7.c14 progress (handoff)

## Done so far (commits)
- 56e8d0b988 ledger rows: 474 twin + 569 value folds, 29 traces -> apart conflict; 20 C1 members untouched.
  - HEAD reclass: .run/3.45/t7/c14/groups.py on `git archive df407fb61c` (tree/), join.py -> joined.tsv, build.py (RETARGET/NEW maps) -> decisions.tsv, b1..b5.txt/.parts.
  - remaps (judged target left the class): V011 -> Unkstruct_801312D0 (80135260 link-folded into 6 B Vec3s), V052 -> Unkstruct_8013B83C (Blk8_8017B614 -> SVECTOR via link, PsyQ not judged), V015 -> Rec8_8018A390_8018523C (Box_80133784 grew by C36), V034 -> DrTpage (DrMode grew by C37), V028 key rekey.
  - unjudged/new: Unkstruct_8017EA44 -> Src_8013B598_8013B598 (V013), Unkstruct_80180D40 -> Pair16 (V027), T070 Unkstruct_8017F374 -> Unkstruct_8017FD24 (same fields unk70/72/FC/FE, sibling overlays SC03_093/097).
  - Q16 wall row rewritten to fold value -> Blk16_956C (judged; same 16 B s32x4) -> applied in b5.
- b1 5dd969094e (56 parts/112 rows) stamp; prep bd413ba95d (Actor_8017E878.f20 alias spelling).
- b2 9719ab46df (54/135) stamp; hand fold 2e2670f2a0 Work_80183634 -> Work_801832E0 (engine refusal: nested struct field `l`), stamped.
- b3 6da65bfba9 (53/122) stamp. b4 b5249be8f9 (54/93) stamp.
- b5 5129284641 (49 value parts/322 rows) + stamp. Walker misses fixed (see gotchas).
- engine: restruct attributed defs fold within one effective alignment (`_fold_eff_align`), selftest 155/155 (commit after b5 stamp).
- prep6 (HEAD at handoff start): ElemK array part ledger split; Pair16 fields `SVECTOR x, y`; S80190C84 typedef -> `typedef struct S80190C84 S80190C84;` (ledger: member row rekeyed `S80190C84@src/shared/engine_types.h:3173` target `S80190C84`, NOT yet stamped; stamp with the prep6 commit id).

## In flight (stopped here; uncommitted, in the working tree AND in phase-ends/current/TASK_PROGRESS.patch, 1957 files)
- b6 (.run/3.45/t7/c14/b6.txt): --write applied 6 comps / 167 rows (SVECTOR 34, ElemK 4, B8 45, Args 44, Pair16 6, S80190C84 34); skipped CVECTOR (B4, 54), U8 comp (18), up, Rec80182744_s.
- walker misses: 14313 sites respelled by `fixnm.py b6 --write` (165 files) + hand: ov_SC02_000_jr_8018173C.c:5092-5097 `stk.unk0.v0.f*`, ov_SC06_029_jr_801867D0.c:4589 `.vx`; make -k reports 0 "no member".
- gate rerun FAILS at scratch: 136 `FAIL new` (e.g. md_MAIN_041.o, ov_SC0*_jr_8016AB6C.o) while `make` builds them; c14_b6_mk2.log has 172 `jtbl_rodata_pads` lines = likely a REAL codegen change (switch jump-table count drift, as b5's func_8012ACE0 showed) -> find the differing function with the base/new `cc1 -S` diff recipe (b5: compile the TU from a `git archive <base>` copy and from the tree, diff the .s), then ladder or revert that component.
- base for b6 scratch: the engine-fix commit (prep6's parent). To restart b6 cleanly: `git checkout -- src include config docs` (prep6 committed state) then re-run --write.
## Hypotheses rejected
- dup gating 142564f85464 after b5 was not the fold itself: tier-1 because block-scope `struct { u16 k; u16 v; } trio[3]` (ov_SC03_118_jr_801863CC.c, ov_SC05_004_jr_8017F210.c) became the only meaningful signature once Pt_80015F04 {x,y} folded; retyped to Unkstruct_80181FAC_2 (bytes identical).
- jtbl_rodata_pads "table-count drift" errors under `make` of single objects are build artefacts; scratch_cmp is the judge.

## Next 5 steps
1. b6 gates green -> commit, `--fold-stamp` b6 keys + `S80190C84@src/shared/engine_types.h:3173` with prep6 commit, commit.
2. Apply `.run/3.45/t7/c14/patch_attr2.py` (tag def with trailing `__attribute__` declares nothing; adds selftest), selftest, commit.
3. CVECTOR comp (B4_80165140 line in c14_write_b6.log SKIPPED): split 34 array-shaped members (cvec_arr.txt) -> B4_80165140 (reach 134; if refused as attributed re-render use B4_8017F154), 20 scalar -> CVECTOR; ledger edit like prep6.py; then b7 = CVECTOR scalar, array part, U8 comp (18), up, Rec80182744_s.
4. Twin leftovers (b8): respell alias field types to the target's spelling first (Drv_8017E550/E878 Coord_* -> Coord_8017E330; PRIM_8018FE20 SV_8018FE20 -> SV_8017DAC4; Prim_8017F40C -> SVECTOR; Q_8017DCC0 V_8017DCC0 -> Sv_8017FA2C, C_8017DCC0 vs Cv_8017FA2C after CVECTOR; Poly_8016CBC0 SVEC_8016CBC0 -> SVEC_md_MAIN_047_800CCBC0; Prim_8016B6BC Vtx_8016B6BC (now SVECTOR) -> SVECTOR_80016B60); Node_800CB658 (Src_800CB658 typed ptr vs target void *) hand-fold or wall.
5. Bit-field targets (engine refuses): Ang2_8012B77C_8012B77C -> Rot1CDC, Drm_801833F0 -> DrTpage, Unkstruct_800249F0/800D29F8 -> PrimTag: hand-fold (token retype + byte-field respell) with scratch_cmp; else wall rows with two attempts. Then final groups.py at HEAD, docs/struct-twins.md, leverage_rank -j 16, `make tools-health`, log T7.c14.md.

## Gotchas
- Every value batch hits walker misses: accesses through a struct FIELD typed with a member (`s->pt[i].vx`, `fr.v[3].z`), macro-param bases (`#define RW32(p) (((T *)(p))->v)`), macro-aliased globals (`#define RES_FILE aResourceIdMap`). Fix recipe: worktree `.run/3.45/t7/c14/wt` at the batch base; `cd wt && python ../plan_maps.py <b>` -> <b>_maps.json; after --write, scratch FAIL objects -> `make -k -O -j16 <objs>` -> grep "has no member named" -> `<b>_nomem.txt` -> `python nomem.py <b>_nomem.txt` -> `python fixnm.py <b> [--show|--write]`; leftovers by hand.
- scratch_cmp reports compile failures as `FAIL new`; the gate's "no-member" grep reads the scratch log, which has no compiler text: always look at `fail` count.
- Engine renders spurious union variants (`short` vs `s16`, pad-subset field lists, arrays vs scalars): union variant structs 36 -> 75 in struct_types.h (engine behaviour; flag for the expert).
- Engine refuses: PsyQ target when any member has array-shaped fields (split those to their own target); tag defs with trailing attribute (patch_attr2); bit-field targets; field type alias defined after the target (respell to the target's spelling).
- gate.sh step 3 census is non-fatal by design (census -> twins --write -> census).

## State to carry verbatim
- notes: .run/3.45/t7/c14/notes.md; gate: `bash .run/3.45/t7/c14/gate.sh <label> <base> [from-step]`; commit file list: `bash .run/3.45/t7/c14/changed.sh`.
- inventory after b1: 3857 definitions / 3843 placeholders (c13: 3969/3955).
