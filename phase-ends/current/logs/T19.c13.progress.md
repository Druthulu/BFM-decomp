# TASK_PROGRESS T19.c13 (applier, A3 batch foldsurv + held items) — handoff at context threshold

## Done so far (committed, each green: asm 0 diff, R22 218/218, sig unledgered 0, gates RC 0 or noted)
- 218c128f8e step 0: obj0xA.patch (6 `*(s16 *)obj`), casts_I ratchet 43667 -> 43673 with the expert's note. Residue: rows already in ledger.jsonl, check-residue 0.
- 07953cce05 chunk 1: 22 survivor rows (all batch survivors except OtBlk_80180894), sizes 8017E2EC_3 0x58, 8017F1B8_2 0xC, 8017E908 0x40,
  80182CA4_2 0xC, 80180FE8 0xE, 8017D8AC 0x44; scalars: 80183A88 deleted (h `s32 (**)(void)`, P casts kept), SC02_041 `aD80186144` asm alias
  (80186144 + alias 8017E130 deleted), SC03_010 `aD8019FF14` alias; Rec_8018B23C +0x8/+0xC word unions (24 sites respelled f8.i.lo/hi, fC.i.lo/hi),
  SC06_016 func_80184804 -> Rec_8018B23C_80184918 (801847C8 deleted). Gate at this commit: one FAIL "scalar not applied" (fixed by stamp, as T18.c22).
- 317d9e4062 stamps 80183A88/80186144/801847C8 applied:07953cce05; 41 star fold rows set (setrows FOLD); ratchet pending 1247, C 289806, untypeable 29233.
- 5e3b7b1725 engine `--fold-batch --write` w/b2.txt (21 lines, one target per line): 30 rows applied; D_801AB676/D_801897BC (8017C8B0 non-source
  tables) retyped `s16 X[][4]` (judge: decide apart). Cites remapped once (struct_types + engine_types). Metrics unchanged. NOT YET STAMPED.

## In flight (in TASK_PROGRESS.patch, base 5e3b7b1725; `git apply` it)
- Stamps: 30 engine rows applied:5e3b7b1725 (stamp.py) — green on its own.
- Absorbs: 8017E9E8 -> S8012C658 unk6.u (3 copies); 801819B4_2: SC02_027/028 `*(s32 *)(s0 + 0x64)` reads -> actor unk8/unkC.i.hi.u,
  md_MAIN_033 s3 -> Ent_80164930_80164930 (asm 0 diff); types + alias 80187844 deleted; config retargets (decf4920 / 800CB76C_3 -> Ent).
- 80185020: SC02_011 s0 -> Unkstruct_80182E70->unk10; RenderHead sources (SC06_008/010/018(alias 80182C98_3)/022/024/032/033, SC01_077,
  SC04_011 func_80185020) -> `((RenderHead *)*(s32 *)(a0 + 0x20))->unk10.w.unk1N.s`; HELD SC04_011 func_80184FC4 sub -> `((SVECTOR *)(sub + 0x10))->vx/vy/vz`
  asm IDENTICAL (attempt 1 worked; no wall). Type deleted; row written (rows_extra.py).
- Hand folds asm 0 diff: 8018762C, 801853D0_2 -> SVECTOR; 80183D30_2 (+alias 8018AB20_2), 8018E428_3 -> `((PrimTag *)(ot + 0x40))->w`;
  80184C68 -> G4P rgb0..3 (target G4P); 8017E558_2 -> GroupRec g0.s / unkC.v0.gC; 8018A3C8_2 -> Ctl_8018A550 (f0 now union {w; h.lo/hi}, no other f0 user).
- PROBLEM (why not committed): 80185910 (+0x3 len byte, +0x18 xy2 word), 8017F424 (+4,+8,+0x10,+0x18,+0x20 words), 801859F4_2 (+4, +0x20 words),
  8017C954 (+0x18 word) were spelled as raw `*(u32 *)(p + k)` with RESIDUAL rows (restruct --residue, 14 sites, check-residue 0) ->
  struct_twins --gate FAIL casts_P 94032 > ratchet 94021 (+11). Ratchet must not be raised. Everything else in the patch was green
  (asm 0 diff over 1885 units, R22 218/218 t19c13_r22_h, sig 0, gates otherwise RC 0; pending 1247 -> 1217, C -17, untypeable -3).
- 8017C954's non-source users moved to G3P: src/800.c func_800173DC (`*(u32 *)&p->x0` I-form for the 3 xy words) and md_MAIN_034 func_800CB5D0.

## Hypotheses rejected (evidence)
- New CAST_WIDTH/CAST_ALIAS macro sites: type_census --check-casts "unbacked 2" — KEPT backing needs a rung-S judgement entry (restruct.py:1265-1300
  s_back_macros: an earlier KEPT(<class>) entry same off+base/line); --residue only writes RESIDUAL. No tool path found yet to create KEPT entries.
- Raw P casts + RESIDUAL: gate casts_P +11 (above).
- `h = *(s32 (***)(void))(...)` hid a P cast from the census (P -1): respelled `(s32 (**)(void))*(s32 *)(...)`.

## Current hypothesis
- The word/byte accesses over SDK packet members need either (a) KEPT(WIDTH) rows from a rung-S run (`restruct --rung S --plan/--apply --only <fn>`
  with --base on the packet pointer? untested) so CAST_WIDTH/CAST_ALIAS macros are backed, or (b) an expert call: keep those 4 views as
  pending/wall until KEPT rows can be made. Do NOT raise casts_P.

## Next 5 steps
1. `git apply phase-ends/current/TASK_PROGRESS.patch` on 5e3b7b1725; split: revert only the 4 raw-cast types (80185910, 8017F424, 801859F4_2, 8017C954 pkt sites;
   keep the G3P move only if 8017C954 can still be deleted) -> restore those views + rows (they stay pending fold rows), rerun chk.py, R22, sig, gates
   (expect casts_P back to 94021), `--write-ratchet` alone, commit; then stamp absorbs/80185020/hand folds applied:<that commit>.
2. Ask the expert about KEPT rows for packet word/byte macro sites (or find the rung-S route) for the 4 packet views.
3. OtBlk_80180894: its ~60 aliases (OtBlk 90 uses, OtBlk_80016450 = D_800A651C, Env_*, Ot_*) are OT-org records; only Ctl801800B8 (5 uses, SC06_006)
   is the camera-cut record. Recommended (judge c6 note "split Ctl801800B8 off"): new survivor type for the camera-cut record, OtBlk survivor
   cites its OT object (D_800A651C src/800.c:1087). Brief said the reverse; raise to the expert.
4. Optional survivor static declarations (D_801C8B80, D_80188614, D_801AED08/D_801B0F68, D_80185AEC/AFC, D_80196C04, D_80192D28, D_801861EC, 8017D8AC buf): not started.
5. a3_status.py counts only survivor/wall/applied fold|absorb as finished: patch it to accept `scalar` with ` applied:` (80183A88), then log T19.c13.md.

## Gotchas
- remapcites.py (c9) writes; running it twice corrupts cites (happened twice; undone with .run/3.45/t19/c10/w/resetcites.py HEAD then one remap).
- Engine moves targets from engine_types.h into struct_types.h: remap engine_types cites too (w/remapeng.py HEAD) or survivors' cites break.
- fold-batch lines must share one target (w/group.py); write is fast (~8-70 s/line).
- After census, rerun struct_twins --write then census if dup_classes>0 (C0654). Restore docs/struct-map.md before commit.
- `#line` files: host-gcc error lines are shifted (SC07_002 7889 vs real 7736): fix such sites by hand.
- Comments naming a deleted type block deltype.py; write provenance without the type name.

## State to carry verbatim
- Work dir .run/3.45/t19/c13/w/: chk.py (BASE OUT [TYPES]; head snapshot .run/3.45/t19/c13/head = git archive of 317d9e4062 — refresh before use),
  def.py, uses.py, resp.py (host-gcc probe respell), deltype.py, retf.py (OLD=NEW config retargets), setrows.py + rows_extra.py (all row texts),
  stamp.py, remapeng.py, group.py, clean.txt (30 engine keys), b2.txt, dry/ logs.
- Logs .run/3.45/logs/t19c13_*.log (gates_h = the casts_P fail).
