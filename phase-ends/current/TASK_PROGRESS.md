# T17.c24 progress (coder, read-only judge of 48 open wave-A1 rows) — handoff 1

## Done so far
- Snapshot of 4c191bc99c at .run/3.45/t17/c24/snap (src include config); read code only there.
- cc1 probe harness: .run/3.45/t17/c24/w/{cc1one.sh,cc1all.sh,mkvar.py,mkrespell.py}; `python3 mkvar.py NAME 'LINE|old|new'` makes
  w/v_NAME/include, `bash cc1all.sh NAME` writes w/err_NAME.txt (~100 s, baseline err_base 0 lines).
- Probe results (error lines = use sites of the renamed/retyped field): p20 player unk20 2401 (2388 lines/671 files); aD8 actor unkD8 82;
  s28 small unk28 4; fx30 fx unk30/unk32 6; m12 model unk12 716; a44 actor unk44/unk48 591; a90 actor unk90 as incomplete ptr: 11
  arithmetic sites; a90r all unk90 uses 112; aCC (add `void *p;` to actor unkCC and unkD0 unions) 0 errors; a90t (unk90 typed
  `Unkstruct_80185680_2 *`) 0 errors; fx2C fx unk2C/unk2E 45.
- In flight (background, may have finished): a36 (actor unk36), m14 (model unk14) -> w/err_a36.txt, w/err_m14.txt. Prepared not run: fx14.
- Respell files written (c24/): respell_A801593E4.tsv (player unk20, 2388), respell_D_801EC450_t.tsv (actor unkD8, 82),
  respell_Unkstruct_800CB7B8.tsv (small unk28, 4), respell_Unkstruct_8017F370.tsv (fx unk30/32, 6), respell_S8016380C.tsv (actor
  unk44/48, 587), respell_Unkstruct_801A7B08.tsv (fx unk2C/2E, 45), respell_Owner_8012ACE0_8012ACE0.tsv (11 arithmetic unk90 sites).
- w/leftover.tsv: leftover sources per type (src0 sources still naming the type in the snapshot). w/judg.tsv: prior judge rows.
  w/mkkeys.py + w/prior_keys.json: source->parent from prior keys files.
- cc1 test w/t/a.c: an 8-byte struct copy compiles to the same lwl/lwr pairs for align 1 (s8[8]) and align 2 (SVECTOR).

## Decisions so far (row -> action; recipe)
- Unkstruct_8018396C: absorb actor; hand-fold ov_SC03_090_jr_8017CA80.c:4970-4971 -> `->unk2.u += 1`, `->unkCC.val = 0` (store) ; delete def. high.
- +0xCC group: add `void *p;` to actor unkCC and unkD0 unions (aCC: 0 respells). 8017E1E4 (27 srcs): `.unkCC.v0.unkCC`->`.unkCC.val`,
  `.v1.unk0`->`.unkCC.p`, `->unk2`->`.unk2.s`. 801803FC (4 copies): unk6/A/E->unk4/8/C.i.hi.u, v1 retyped `void *` + `.unkCC.p`.
  801ABEE0: ptr1 retyped `Unkstruct_801ABEE0_2 *`/void*, `->unkCC.p`, :8058 `*(s32*)(s2+0xCC)`->`((Unkstruct_801202A0*)s2)->unkCC.p`,
  :8070 `.unkCC.val`. D_801EC450_t (ov_SC03_028_jr_8017DF98.c:5238-5253): arr[0..3]->unkCC.p, unkD0.p, unkD4, unkD8 (needs unkD8
  union {s32 val; void *p;}, 82 respells). 80182AC0 leftover 7 (c6 refuse: owner of +0xCC) resolved by `.unkCC.p`: absorb actor.
- MainStruct: hand-fold func_8018622C (ov_SC02_005_jr_80185E80.c:220-249) with typed locals: f_20->unk20 (model, field_4 = model
  unk4.s), f_CC/f_D0 -> unkCC.p/unkD0.p, f_D4 -> unkD4, f_E8 -> extC.kSC02_005_801816FC.unkE8; D_801E43A4 extern -> actor*; 3 protos.
- Ent83178 (ov_SC02_011_jr_80183178.c:120,130): pointee = model record (kind table D_801955B0 state func_80182FF0 calls
  guess_InitActorModel, ov_SC02_011_jr_8017AE2C.c:8119-8124); typed local `Unkstruct_8001C9D0 *r = ((Unkstruct_801202A0 *)s0)->unk20; r->unk10.s = ...`.
- Owner_8012ACE0: retype actor `void *unk90` -> `Unkstruct_80185680_2 *unk90` (a90t: 0 errors) + respell the 11 `unk94*8 + unk90`
  sites to `->unk90[->unk94.x].unk0`; bodies func_8012ACE0__*.h `o->list[i].unk4` -> `o->unk90[i].unk4`, param -> actor*.
- Obj_8017D7CC (ov_SC03_115_jr_8017BEBC.c:3418-3441): actor; f002->unk2.u, f020->unk20 (keep `(s32 *)` cast), f070->unk70.s, f0C0->unkC0.u. high.
- Obj1CDC (3 fns, kinds 652/655 SC05_010): x/y/z->unk4/8/C.i.hi.s, unkFC/FE/10A .s, unk100/102 -> extD.kSC05_010_801828E0 (+s16 unk102),
  unk20->unk14 typed local (model; u16 RMW vs model s16 unk14 -> sign union, probe m14), unk64->unk34.u, unk64->unk100 needs parent kind variant (open).
- Cnt_8018E8A0: hand-fold 9 lines (SC02_011:4631,4697-4698; SC03_006:10280,10346-10347; SC03_029:6400,6466-6467) f[0x84] ->
  extD.kSC02_011_8018EBEC.unk108 (new variant `{u8 pad0[0x8]; s16 unk108;}`); delete Cnt + 2 aliases. high.
- S8016380C (shared func_8016380C.h, 136 TUs): `m` is Unkstruct_8013B83C u8[8] (align 1) struct copy at +0x44; union at actor +0x44
  spanning unk44/unk48 (587 respell lines, respell_S8016380C.tsv) or one cast per TU; decision.
- Ent: rebase func_8013E4B4.h (one shared body) to `S8012C658 *p = (S8012C658 *)s0; p[i].unk6.u / p[i].unkA.u`; S8012C658 unk6/unkA
  -> union {s16 s; u16 u;} (8 store respells: ov_SC04_003:4690,4692; func_8012C658.h:23,25; ov_SC02_011_jr_80188E3C:160,162;
  ov_SC06_029:6087,6090,7741,7743 -> .s). Byte risk (giv base): scratch_cmp one TU first; if DIFF -> wall. med.
- Actor_80178D40: interpreter reads unkDC[idx] (runtime index) over common unkDC + whole extC gap (0xDC-0xF8): wall candidate /
  decision (restructure 0xDC-0xF8 = 636 unkDC + 1228 extC respells). Other fields: unk20->unk12 typed local, unkD4 actor*.
- Player trio (A801593E4, Ent8018B390, Actor4C): player +0x20 union `{ s32 val; Unkstruct_8001C9D0 *m; } unk20` (model def already
  above player); 2388 respell lines (respell_A801593E4.tsv): `*(T *)(x->unk20 + K)` -> `x->unk20.m-><model field>`, casts on the field
  -> `.m`, rest `.val`; views: p20->field12 -> unk20.m->unk12.u; SubEnt8018B390 unk10/12 -> model unk10.s/unk12.s; Actor4C `p` ->
  model*, `p->unk20 = (Actor4C *)&D` -> `= (s32)&D`. Gate risk: union-path sources (C0634) -> run c20/untyp.py diff. med.
- 800CB7B8: small unk28 -> union {u16 u; u8 b;} (4 respells .u); view unk14 s32 splits small pad14; unk20 s32 onto `s16 *unk20`
  (no arithmetic on the field: node is a local). high.
- 8017F370: fx unk2C/unk2E -> union {s32 val; struct {union{u16 u; s16 s;} lo; u16 hi;} i;} unk2C (45 respells, also serves
  801A7B08 s16 and 801AB5D4 u16), fx unk30/unk32 -> union {s32 val; struct {u16 lo; union{s16 s; u16 u;} hi;} i;} unk30 (6 respells). med.
- 80183020: model unk12 is already union {s16 s; u16 u;} at the snapshot: hand-rename the 6 casts (SC06_014:4604,4609;
  SC06_016:4097,4102,4103) to Unkstruct_8001C9D0, same leaves; delete def. high.
- 801AB5D4: absorb fx (c10), no conflict (unk2.s, unk1C, unk2C u16). 801A7B08: absorb fx (c11) after the fx unk2C union. 80129010:
  absorb fx (c9), needs fx unk14 word/halves union for view u16 +0x16 (probe fx14 prepared).
- 8017DDE0: fold into SubRec_801EB5C8_8017D7EC (src/shared/engine_types.h:3019-3030; u16 f0..fA, s32 fC..f18: exact match), rename unkN->fN. high.
- 8017DCF8_2: absorb model (unions now present). 8018445C a0: absorb model (+0x4 unk4.s, c8). 801A4ACC/80180384/80181164/801868EC/
  80142608: actor; hand-fold the unk64 arithmetic: 801A4ACC md_SC07_004.c:3273 -> `->unk64->unkCC.val = 0`; 80180384 SC01_077:3885 ->
  `(s32)->unk64->unk20 + 0x34`; 80181164 SC05_005:4340 -> `->unk64->unk36`; 801868EC SC05_010:4202 -> `(s32)&->unk64->unk76` +
  extF variant kSC05_010_80183C84 {u8 unkC8;}; 80142608 (124 copies of func_80142608) :1600 `*(short *)(unk64 + 0x36)` -> actor unk36
  needs sign union (probe a36). 801A5C44: unk70.s, s2 void* `.unkCC.p`, s1 = unkD4 (kind 799 non-actor ptr: rule-4 debt), extD variant
  kSC07_004_801A5B20 add s16 unk100.
- 8017F424_2: grow Quad_8017EF94 (engine_types.h ~2510-2519, 0x18) to 0x20 (`u8 pad18[4]; s32 unk1C;` = D_801B1B74 data at
  asm/ov_SC06_025/data/tail19.data.s:5432) + x/y sign unions; fold. med.
- 8017C218_2 leftover 15: 7 player-holder + 1 md044 -> absorb player via c14 keys files (never applied); 7 refuse (dual parent / untraced) -> decision.
- Rec8: survivor (static 8-byte record arrays D_801853A8 SC03_011, D_801C5894 SC03_118, D_801AAD6C/D_80185094/D_80185098 SC07_001;
  a1 params walk them until w == 0xFF); render +0x10 copies -> SVECTOR value copy.
- M8_801312D0: fold SVECTOR (value copies, byte-identical per w/t/a.c); 128 externs + 123 copies + 51 protos token rename.
- Blk8_80133CD4: fold SVECTOR (c12 cause "alignment 1 vs 2" is not a byte difference: w/t/a.c); 266 alias typedefs in
  engine_types.h; 14 `.c[` uses (ov_SC02_005_jr_80185E80.c:3186-3188,3667,3679 -> .vx/.vy).
- H16: real objects are the globals (guess_g_BoxHitNormalX/Y/Z s16 = SVECTOR at 0x801152A8, D_x u16): `((H16 *)&G)->h = v` -> `G = v` (stores).
- ElemK: fold SVECTOR; `.e` -> `&X.vx`, `.e[k]` -> member / `(&X.vx)[i]`.
- Mat32: wall confirmed (c18 attempt 2 COUNT, ov_SC03_099_jr_8012ACE0.c:3142-3193 mat2.w0..wC word stores); third spelling = a
  MATRIX/word union type (not a fold) or `*(s32 *)&m.m[i][j]` casts (+536). PG4 (word colors c0..c3 + u16 RMW x/y) and Blk32 800.c
  (LINE_G3 word stores) same class; PG4 could fold into G4P (include/struct_types.h ~1975, word-colour G4 view) with x/y sign unions.
- Blk20: per-source split (MATRIX-API sources -> MATRIX; `.w[` word-copy sources -> Mat32 wall class; CdSearchFile record -> own type). Not classified yet.
- Blk16: 75 of 76 leftover in GsF_LIGHT unsafe/unmatched (c18); remaining classes are 16-byte half-MATRIX value copies (repo VECTOR 12 B) -> wall class.
- Unkstruct_8001CD50, Unkstruct_800CB300, S800D22E4: not reviewed yet (8001CD50 has 0 leftover sources; definition dead -> stamp/delete).

## Hypotheses rejected (evidence)
- Union at actor +0x20 (5832 cast-form uses) for Ent83178/MainStruct/Obj*: rejected, typed locals avoid both respells and new casts.
- Gate classifier: untypeable = cast sites whose source kind not in TYPEABLE_KINDS (tools/struct_twins.py:3449-3466, 3348); RHS_CV
  (:2691) only matches `((T *)x)->f` with no `.member` tail, so union-path reads are not `field` sources.

## Next 5 steps
1. Read w/err_a36.txt, w/err_m14.txt (bash cc1all.sh a36/m14 if missing), run fx14; write respell_Unkstruct_80142608.tsv (unk36),
   respell_Obj1CDC.tsv (model unk14), respell_Unkstruct_80129010.tsv (fx unk14).
2. Classify Blk20 leftover sources (w/leftover.tsv) by function text: `.w[` / CdSearchFile / MATRIX API.
3. Review 8001CD50, 800CB300 (line-294 group), S800D22E4 (4 refused md_MAIN_044 sources) leftovers.
4. Write c24/rows.tsv (48 rows: key action parent_or_target member_or_variant recipe files confidence) from the decisions above,
   keys_<key>.txt from w/leftover.tsv + w/prior_keys.json (index + per-parent C0627 files).
5. Write phase-ends/current/logs/T17.c24.md and commit it (tools/commit_task.sh T17.c24 "log" <log>).

## Gotchas
- harness: shell reads (sed/awk with computed ranges) of files > 20k chars are denied; use Read offset/limit.
- cc1 probes miss uses in non-compiled text; `#line` remaps (ov_SC07_002_jr_8017C8D0.c +153).

## State to carry verbatim
- Snapshot commit 4c191bc99c; scratch only under .run/3.45/t17/c24/.
