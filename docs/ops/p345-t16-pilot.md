# 3.45 T16: the tracing pilot (largest family, parent model, wave projection)

Pilot of the absorption and typing waves (T17-T29) on a stratified sample of 120 placeholder types. Commits
3b8ce507db..442aedd8ec. Parent model: docs/gen3-standards.md rule 4 "Worked example: the actor". Techniques:
cookbook C0624-C0628. Wave membership: docs/ops/p345-t16-waves.tsv.

## Method
- Sample (120 types): the core of the largest family (Unkstruct_800B5CB8, Unkstruct_80126B58, the player views, T2's
  52 C1 members on 800B5CB8) plus views by field band (1, 2, 3-5, 6+) and source kind (param, local, global, field,
  return), drawn from T14's tables regenerated at HEAD (`struct_twins --sources`).
- Judging: 4 read-only coders in parallel (c1-c4, own scratch dirs), one row per (type, source group): absorb (parent,
  offset or variant), fold, survivor (root object cited) or refuse, with the code facts that decide it.
- Applying: one applier at a time through the fold engine (`restruct.py --fold-batch`, extended in c5-c7: gap-union
  variants, sign unions, pointer/scalar leaf maps, fixed-point unions, per-source keys files) and rung T
  (`restruct.py --type-batch`, extended in c8-c9: header TU visibility, global-key planning cost), by the edit procedure
  (docs/ops/p345-t15-typing-engine.md), every batch committed green (R22 218/218 and the full gate list).

## Judging (done-when 1)
- c1 17 types / 21 rows ~11 min; c2 40 / 40 ~7 min; c3 31 / 35 ~13 min; c4 32 / 36 ~14 min (each ~180k tokens).
- 132 rows: absorb 108, fold 12, survivor 10, refuse 2. About 30 types per 10-minute judge run.
- One wrong premise corrected mid-run (R3.45-013): +0x0 u16 is the object type, +0x2 its state; func_8001CB6C/CF48
  init the 0x38 sprite record, not the actor slot.

## Parent model (done-when 2)
- Objects live in typed pools; type at +0x0, state at +0x2. The actor slot Unkstruct_801202A0 (0x10C, 96 slots at
  0x801202A0) keeps its common fields flat; per-kind data sits in four gaps, each a named union of per-kind variant
  structs: extA 0x24 (2 variants), extB 0xA0 (19), extC 0xE0 (15), extD 0x100 (20), named by owning handler
  (`kSC02_005_80181BE8`) or shared-body class (`kcls_<hash>`). Not one SOTN-style `ext` tail: the evidence puts the
  per-kind words between common fields (include/struct_types.h:353-460).
- Other roots: sprite record Unkstruct_800B5BD8 (0x38), model record Unkstruct_8001C9D0 (0x84), fx Unkstruct_8011DB30
  (0x38), small object Unkstruct_8011D030 (0x58), player Unkstruct_80126B58 (0x254, its own object).
- Unkstruct_800B5CB8 is a mis-merge (named after sprite record #4; actor, sprite and model views joined): split per
  source. T16 split its shared+main+resident slice (163 sources: actor 80, sprite 14, model 4, 65 stay).

## Applying (done-when 3)
- Placeholder ledger (config/struct_dispositions.tsv): pending types 2,915 -> 2,822 (93 finished).
  Absorbed and applied 82; 6 absorbs ledgered pending (absorb rows now 89; parents: actor slot 69, sprite 7,
  player 4, fx 4, model 2, small object 2, other 1); survivors 12 (the pool roots and owned globals, objects cited);
  new folds 4.
- Applier runs: c5 47 absorbs (3.7 h), c6 30 of c5's 33 refusals on second attempt (2.3 h), c7 per-source split of
  the player group and the 800B5CB8 slice (3.8 h), c8 folds/survivors + 4 actor helpers typed (7.9 h, 4.4 h of it one
  slow chunk of global keys), c9 the cost fix and rung T over 964 keys (6 chunks, ~25-33 min write + ~25 min gates each).
- Refusals and second attempts: judges refused 2. c5's applier refused 38 (pointer vs s32 19, fixed-point halves 11,
  multi-parent 4, include order 2, straddle 1, other 1); c6's second attempt (leaf maps, fixed-point unions) and c7's
  per-source split cleared all but 3, ledgered pending for T17 with cause (player unk20 field retype; typed void*
  adoption moves bytes; a straddling field). Rung T: 0 DIFFERS, 0 walls; 4 compile errors (conflicting SHARED_FN
  prototypes) ledgered pending.
- Rung T over the sample's sources (1,178 keys, ledger labels T16c8-*, T16c9-*): typed 196 (param 165, local 23,
  param-copy 3, ret-of 3, field 2), pending 978, compile error 4. Global keys 263, typed 0.
- Casts (`struct_twins --sources`): 482,635 -> 479,065 (-3,570: C -3,557, P -13); sources 103,610 -> 103,436.
  Absorption itself removes no cast (it renames the view to its parent); rung T removes them.
- Pending reasons (rung T): field source with no single typed holder 282; 2+ cast types on one source ~180 (134 of them
  `&guess_g_PlayerActor`, read through Unkstruct_80126B58 143x, a per-file copy S126B58 134x, u8/s32/s16 scalars);
  arith/mixed kind 137; type not canonical (block-local LBlk16/Blk16) ~60; non-cast uses ~70.

## Before and after (one per source kind)
Param, md_MAIN_025.c func_800CB068 (player block; 1745ef06c5):
```
-void func_800CB068(void *a0) {
-    u16 bits = ((Unkstruct_80126B58 *)a0)->unkB8;
-        ((Unkstruct_80126B58 *)a0)->unk197 += 1;
+void func_800CB068(Unkstruct_80126B58 *a0) {
+    u16 bits = a0->unkB8;
+        a0->unk197 += 1;
```
Local, ov_SC06_008_jr_8017C294.c func_8017FE28 (actor slot from a spawn; f243c1da44):
```
-    s32 s0;
-            ((Unkstruct_801202A0 *)s0)->unk4.i.hi = ((Unkstruct_8017FC34_2 *)a0)->unk6 + (rand() & 0x3F) - 0x20;
-            ((Unkstruct_801202A0 *)s0)->unk10.val = -((Unkstruct_8017FC34_2 *)a0)->unk10;
+    Unkstruct_801202A0 *s0;
+            s0->unk4.i.hi = ((Unkstruct_8017FC34_2 *)a0)->unk6 + (rand() & 0x3F) - 0x20;
+            s0->unk10.val = -((Unkstruct_8017FC34_2 *)a0)->unk10;
```
Global, ov_MAIN_012_jr_801789AC.c func_80178D40 (per-source absorb; 03e446178d): the player global's view now names
the player block; the global itself is not typed yet (its other views, S126B58 and scalar reads, are A1 work):
```
-    Actor_80178D40 *pv = &(*(Actor_80178D40*)&guess_g_PlayerActor);
+    Unkstruct_80126B58 *pv = &(*(Unkstruct_80126B58*)&guess_g_PlayerActor);
```
Field, md_SC07_003.c func_801A5A10 (local loaded from a field; the field Unkstruct_801A5A10.unk20 retyped; 1745ef06c5):
```
-    s32 p;
-    ((Unkstruct_80184178_2 *)p)->unk1A = 0x3000;
+    Unkstruct_80184178_2 *p;
+    p->unk1A = 0x3000;
```
Return, md_MAIN_025.c func_800CBBA0 (func_8014C088 returns Unkstruct_800CB098 *, 2,180 files; 1745ef06c5):
```
-extern s32 func_8014C088(s32 a0, s32 a1);
-    s32 ret;
-    if (((Unkstruct_800CB098 *)ret)->unk2 >= 2) {
+extern Unkstruct_800CB098 *func_8014C088(s32 a0, s32 a1);
+    Unkstruct_800CB098 *ret;
+    if (ret->unk2 >= 2) {
```

## Wave projection (done-when 4)
Types (2,822 pending; docs/ops/p345-t16-waves.tsv, one row per type with its wave; `top_cand` is a layout hint):
- A1 (T17) 462: the actor family and the pool views: F00001's 35 pending members, Unkstruct_800B5CB8's per-source
  split (11,415 sources, 88k casts: the wave's main cost), and every pending type whose best parent is a pool root
  (actor 142, 800B5CB8-fit 142, player 98, sprite 38, model 6, fx 1). Includes the player global's views.
- A2 (T18) 621: types whose casts sit mostly in ov_SC03.
- A3 (T19) 525: ov_SC02 197, ov_SC06 174, ov_SC04 154.
- A4 (T20) 659: ov_SC05 94, ov_SC01 101, ov_SC07 75, md_* 186, shared 123, main+resident 76, ov_MAIN 4.
- A5 (T21) 555: types with no cast source (309 `apart own`: they own declared objects, survivor or twin judgments;
  246 named only in declarations); plus whatever A1-A4 leave.
- Cost model: judging ~30 types per 10-min coder run (550 types ~ 18 runs, 4 in parallel); applying ~4.5 min per type
  absorbed when batched per parent on one line (C0627: the walk over every file naming the parent dominates).
Regions (sources and casts at src1): B1 (T22) shared + md_* + ov_MAIN + main+resident 9,590 sources / 33,115 casts;
B2 (T23) ov_SC01 + ov_SC07 12,180 / 57,196; B3 (T24) ov_SC02 12,336 / 57,819; B4 (T25) ov_SC04 11,081 / 49,699;
B5 (T26) ov_SC05 9,339 / 42,438; B6 (T27) ov_SC06 14,199 / 73,912; B7 (T28) ov_SC03_001..096 17,845 / 83,941;
B8 (T29) ov_SC03_097..126 16,866 / 80,945.
- Rung T cost (c9, measured): ~1.5 s to plan a key, ~40 s to judge a typed key (dry run + write ~1,500 s per ~160
  keys, ~32 typed); about 20% of keys typed per pass, the rest pending on order (holders, callees) or on absorption
  (2+ cast types). One pass over 103k sources at this rate is ~270 h of engine wall time; the judge runs per key.
  c9's typed keys mostly touched 2-10 files (shared declarations: 46 one-file, 140 two-to-ten, 6 more); region-local
  keys may judge faster, unmeasured. Judging a TU's keys together (bisect on DIFFERS) is the lever before B1.
