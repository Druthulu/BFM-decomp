# func_8013D9B0 (ov_SC04_011_jr_8013C98C.c) — T7 agent c17

**Final lever-free score: 15** (from 96). mine 140 ins vs target 141. `PACK/body.c` has no pin, no asm statement, no
added volatile and no invented zero term; it uses only the existing `gte_*` macros from `include/gte_inline.h`.

**What is left is not in the body.** Three residues remain and all three come from one cause: the `include/gte_inline.h`
spelling of the GTE macros. With ONE header macro respelled the same body scores **2**; with two it scores **0**
(`scratch/PA.c` = 2, `scratch/PROOF_K1.c` = 0; both are proof files with the macro text written inline, so they are NOT
lever-free bodies and are not offered as closes). The header change is outside what an agent may edit. Whether to make
it is the coordinator's call (see (d)).

## (a) The residual in one sentence
Start (96): wrong shape. The tree's body walks two `u16 *` pointers, so loop.c builds a third giv. Its four `rect`
stores are `*(s16 *)(u8buf + k)`, so the scheduler hoists the loads over them. The LoadImage call is declared with
one argument, so the kept `img` copy disappears. The flag and the struct giv are swapped between s0 and s1. Final
(15): one missing `move t4,v0` before the `swc2 $29`; `i`/`n` one register low (t4/t5 where the target has t5/t6);
`addiu v0,sp,28` (the IRGB pointer) one slot late (after `lwc2 $6` where the target has it before `mtc2`).

## (b) Passes and decisions (file:line in tools/reference/gcc-2.7.2)
1. **Shape: loop.c giv choice.** Rewritten with one `Cmd_8013D53C *p`, as func_8013D8FC/func_8013D53C walk the same
   `D_801EDABC` list. loop.c then makes exactly one reduced giv, based at the textually last field read (`p->data`,
   +12 → `s1 = s2+12`) — `record_giv` loop.c:4341, `combine_givs` loop.c:5494. The old `(s16 *)psVar14` casts on a
   `u16 *` biv produced a third walked pointer (`s0 = s2+10`, an extra callee-saved register, frame 80 not 72).
   PROVEN (v1: 96 → 46).
2. **Call arity.** `func_800599B8` is LoadImage(RECT *, u16 *). The target keeps `img = src + n` live in `a1` through
   the whole pixel loop (`addu a1,t3,v0; move t2,a1`) and passes it implicitly. That is the METHOD "dropped call
   argument" entry. PROVEN (part of v1).
3. **Rect store serialisation (the four "memory" barriers): sched.c `true_dependence` sched.c:834 + expr.c
   INDIRECT_REF MEM_IN_STRUCT_P expr.c:4568-4575.** `*(s16 *)(buf + k) = p->x` is an INDIRECT_REF of a NOP_EXPR, so the
   store is not marked in-struct. The loads `p->x` are in-struct with a varying address, so they count as independent
   of the stores and get hoisted above them. `s16 rect[4]` with `rect[k] = p->x` puts both sides in-struct, and the
   four lhu/nop/sh pairs come out serial as in the target. PROVEN (v1 46 → v2a 28).
4. **i vs n (t5/t6): global.c `allocno_compare` global.c:587-600** (priority = floor_log2(refs)·refs/live).
   i = 4459.5 and n = 4500 were within 1%. Moving `i = 0;` from before `if (cmd == 9)` to the top of that block
   shortens i's live range from 74 to 60 (5500), so i is allocated first. The `move t5,zero` still reaches the
   `bne` delay slot. PROVEN (X2 21 → X2_A2 15, in the proof context).
5. **flag vs giv (s0/s1): the same comparator.** giv 8837 (refs 19, live 86) beat flag 7031 (refs 15, live 64).
   Two fixes were ruled out: live length cannot drop below about 58 (the pixel loop alone), and the giv's refs are
   fixed by the seven field reads. The move that works puts the flag store in both arms of the inner test:
   `if (r < tr) { flag = 1; r += 1; } else flag = 1;`. The duplicate stores sit at loop depth 3, weighted by flow's
   loop_depth (flow.c:1401), so the flag's refs go from 15 to 24 (15000 > 8261). reorg then merges them back into
   one delay-slot `li s0,1`: the `.jump2` dump still has 6 `(set s0 1)` and the final bytes have 3 (`redundant_insn`
   reorg.c:1952). The extra RTL insns also raise the inner loop's `insn_count`, so loop.c no longer hoists the
   `&gte[1]` pointer (next item). PROVEN: X2_A2_C3/C6/C9 = 0 and C0 = 15 in the proof context; K1_C0 = 39 vs K1 = 15
   lever-free.
6. **GTE pointer hoisting: loop.c `move_movables` threshold.** threshold = 2·(1+n_non_fixed) (loop.c:532) was 58-60
   against an inner loop of 58-64 real insns. Desirability is `threshold·savings·lifetime >= insn_count`
   (loop.c:1631), and threshold drops by 3 per insn moved (loop.c:1719). So the first life-1 invariant is always
   hoisted and the second never is. The target hoists the RGB pointer (`s4`, in the pre-header after the `== 0xff`
   test) and hoists neither the IRGB nor the ORGB pointer. In plain C: `fc = gte;` inside an explicit
   `if (cmd != 0xff) { fc = gte; do … while }`, as body_free had it. Setting it before the `while` puts the
   `addiu s4` before the test and steals `move s3,zero` from the delay slot (L2 = 17 vs L4 = 15). PROVEN.
7. **The `move t4,v0` cannot come from plain C** (reasoned, then checked on bytes with 7 spellings: S1, S2, S2b, T1-T4,
   K2, L3, L5). t4 appears only in `move t4,v0; swc2 $29,0(t4)`. Two ways to get a copy fail:
   - A local qty (local-alloc.c:472) copied from the dying `v0` is tied to it and deleted.
   - Otherwise combine folds `R = sp+32; O = R` (combine.c:900-1000: nothing blocks it when R dies in the copy and no
     volatile insn or call sits between them). The `addiu` must follow the volatile `dpcl` (the sched barrier), so
     the combine.c:988 volatile guard never applies.

   Suppose instead the copy survives cse's swap (cse.c:7440-7474) because O is a global allocno. To land in t4 it
   must conflict with v0, v1, a0-a3 and t0-t3. a0/t0/t1 (tr/tg/tb) are live only after the store, so O would need a
   later use, and t4 would then appear again. It does not. So O is a hard register: the asm itself writes `$12`.
   PROVEN by the proof files. `"move $12, %0\n\tswc2 $29, 0($12)" :: "r"(p) : "$12", "memory"` gives the exact bytes
   (`move` = `addu $12,$2,$0` = 0x00406021, the target word). The `$12` clobber is what pushes i/n to t5/t6: global.c
   marks clobbers live against the inputs (global.c:716). PsyQ's inline_o.h clobber list (`$12-$15`) scores 6, so
   the original clobbered `$12` only.
8. **The IRGB address before `mtc2`.** It must be set before the `mtc2` asm and must not be hoisted (item 6), which
   rules out a single-set pseudo. Plain C only gets there with a dead second store (`scratch/PA_4.c` = 0 together with
   the header macro). A dead store is an invented construct, so it was REFUSED. Reusing one pointer for IRGB and ORGB
   makes it a global allocno that dies twice; it gets a0, because sched1 lifts its set above the andi's and so it
   conflicts with `pix` in v0 (L3/L5/K2 = 17). The natural explanation is one asm for
   `mtc2 $0,$8; lwc2 $6,0(%0); lwc2 $28,0(%1)`: both input pointers are computed before the asm, the RGB pointer
   first (life 2, hoisted) and the IRGB pointer second (life 1, not hoisted). PROVEN (PROOF_K1 = 0; PA without it = 2).

## (c) The moves (lever-free body.c, score 15)
- One `Cmd_8013D53C *p` walked with `p++` in an explicit `if (cmd != 0xff) { … do { … } while (cmd != 0xff); }`, with
  `u16 cmd` (the `andi 0xffff` before every compare).
- `s16 rect[4]` filled field by field (`rect[0] = p->pad4 …`), then `n = p->w * p->h`, then `src = p->data`.
- `img = src + n; dst = img;` and `func_800599B8(rect, img)` (LoadImage at its real arity).
- `i = 0;` at the top of the `cmd == 9` block. `flag = 0;` after `n` is computed.
- The step toward the DPCL result, per channel: `if (r != tr) { if (r < tr) { flag = 1; r += 1; } else flag = 1;
  if (tr < r) r -= 1; }`.
- `u32 gte[6]` (fog colour / IRGB / ORGB; the frame needs 32 bytes of locals), plus a separate `u32 *fc = gte`
  pointer for `gte_ldrgb`, set inside the `cmd != 0xff` guard.

## (d) Generator proposals
- **GTE macro proposal (for the header owner).** Pattern: a `$12` pin plus a launder feeding one GTE store, and the
  bytes read `addiu vX,…; move t4,vX; <cop2> 0(t4)`. That is a MACRO spelling difference, not a body lever. Respell
  the macro in the PsyQ inline_o.h style, `move $12,%0` then the op on `0($12)`, clobbering `$12` only. If the
  target computes a load pointer before `mtc2`, the load macros are one multi-instruction asm. Here
  `gte_ldIR0z/gte_ldrgb/gte_ldIRGB/gte_stORGB` are used ONLY by the 136 copies of this function (header comments:
  "136 definitions in 136 files; not a PsyQ name"). So the respelling touches nothing else. It must ship together
  with the lever-free body for every copy, because the old levered bodies pin `pb` to `$12`, and under a
  `move $12,%0` macro that would emit `move t4,t4`.
- **Flag duplication (R-class candidate).** Pattern: a callee-saved swap where the loser is a flag set once per `if`
  inside an inner loop, and `floor_log2(refs)·refs/live` loses by less than 2x. Put the flag store in both arms of
  the innermost if/else. Each duplicate adds loop_depth refs, and reorg's `redundant_insn` folds it back into the
  single delay-slot `li`, so the bytes do not change. It is the if/else twin of METHOD c7 (a join-point
  statement duplicated into both arms).
- **Rect/aggregate copies through a byte buffer.** When the target serialises lhu/sh pairs into a stack buffer that
  the tree held apart with `"memory"` barriers, retype the destination as an array of the element width
  (`s16 rect[4]`), so that the stores are ARRAY_REFs and both sides are in-struct (sched.c:834). This completes
  METHOD c11 from the store side.

## (e) What did not work (byte evidence, scratch/*.c)
- The tree's two walked `u16 *` pointers: 3 pointers, frame 80.
- Struct copy `rect = *(Rect *)&p->pad4` (X3): fixes s0/s1, because the block move is one insn with one giv ref, but
  it emits `lwl/lwr` (movstrsi_internal, align 2, mips.c output_block_move) — 16.
- Copying the rect through a pointer temp (Y1-Y4): cse folds the temp away — 15.
- Every plain-C route to `move t4,v0` (S1, T1-T4: a copy `pb = pa`, a reuse after the asm, `pa` read after the asm): either
  loop-hoisted or combined away.
- Reusing one GTE pointer (S2, L3, L5, K2): global, lands in a0 — 17-19.
- Flag at the end of the `r != tr` block (C1): 9 in the proof context. Flag in both inner ifs (C2, C8): extra insns.
- inline_o's full clobber list: 6. The dead-store trick (PA_4): 0, REFUSED as invented.

## (f) Where the method fell short
- Nothing in the pack says that a lever cluster can encode a HEADER difference. Here the 25 NEEDED sites (the `$12` pin,
  the launder, the `$2` pins and the i/n pins) were almost all compensating for one GTE macro spelling. A cheap
  check before any grinding: if the target has `move <fixed reg>,vX` immediately before a cop2 op and that register
  never appears again, try the macro as an inline_o-style asm in scratch. This one check (PA) took the score from
  15 to 2.
- alloc_table.py settled s0/s1 and t5/t6 by arithmetic, as advertised. The loop.c hoisting decisions (which GTE pointer
  is moved out) needed the `.loop` dump ("Insn N: regno R (life L), savings S moved / not desirable") read against
  `threshold` and `insn_count`. alloc_table does not show them, and they decided three of the residues.
