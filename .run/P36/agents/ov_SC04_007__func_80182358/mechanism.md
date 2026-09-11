# func_80182358 (ov_SC04_007) — d4, P36 T7 S104

**Result: score 0 (10 before). No pin, no asm, no added volatile; one `do { } while (0)`, marked per METHOD step 8.
Lever count: 1 asm launder → 0 asm/pin + 1 marked do-while.** The same body (renamed) also scores 0 on all three copies:
ov_SC04_005:func_80185CEC, ov_SC04_002:func_8018691C, ov_SC02_041:func_801832F8 (`--try`, each 111/111).

## (a) The residual
Same count (111 each). Two symptoms with one cause: `li s2,127` (`vol = 0x7F`) lands after the first `jal func_8012EFB8`
instead of in the prologue next to `li s1,7`; and the a0 copy takes `$v0` with the three sp10 load temps in `$v1/$v1/$v0`
where the target has the copy in `$v1` and all three temps in `$v0` (the "v0<->v1 x4" pairs).

## (b) Pass and decision (proven on the `.sched` / `.sched2` / `.lreg` dumps of the real TU, `scratch/dumps_{free,tree,d1}`)
1. **sched1 places vol=127 after the call.** Block 0 is scheduled backward. After the jump (T-1), `p = &D_80126B58` (insn
   15) is the only single-set pseudo, so `birthing_insn_p` (sched.c ~2468) boosts it to LAUNCH_PRIORITY
   (`adjust_priority` sched.c:2507, LAUNCH_PRIORITY sched.c:187/3902) and it takes T-2. At T-3 the store `sp18[2] = 0` (48) and
   the load `v = sp18[0]` (53) both have priority 4 (both inherit it from the call through the memory-flush anti-dep,
   sched.c:1650/1781, cost 1 after mips.h ADJUST_COST); `schedule_select` (sched.c:2616) picks the store by
   `potential_hazard` (sched.c:1318). At T-4 the load is `blocking insn 53 for 1 cycles` (memory unit, mips.md:153-161), so
   the next priority group, {vol=127 (21), pan=7 (18)}, both priority 1, both multi-set so never boosted, fills the slot, and
   the LUID tie-break (`rank_for_schedule` sched.c:2385-2437) picks 21. It is now after the call.
2. **sched2 cannot move it back.** sched.c:1705 tests `call_used_regs[i]` with the loop index `i`, not `regno + i`, so every
   hard-reg set after a call gets an ANTI dependence on that call (seen in `.sched2`: insn 21 carries `REG_DEP_ANTI 45`).
3. **The register swap is a side effect.** With 21 inside the a0 copy's block-0 range (reg 72, 8 insns → 9 in the matching
   order), local-alloc's `qty_compare_1` (local-alloc.c:1598) priority for r72 drops from 5000 to 4444 below the three temps'
   5000, so the temps take `$v0` first and r72 gets `$v1`. `tools/localalloc_sim.py` reproduces both dumps, 0 mismatches.
4. **What the tree's launder actually did** (tree `.sched`): `__asm__("" : "=r"(pan) : "0"(pan))` is one more insn (50),
   priority 1 with a LUID above 21, ready from T-2, so it fills the T-4 stall instead of 21. It was a stall filler; it did
   not kill a birthing boost (pan already has five sets), whatever the journal's "§393 birthing-boost re-tie on pan" says.

## (c) The moves that closed it (joint edit)
- `v = sp18[0];` moved above `sp18[2] = 0;` (inert alone: score 10).
- `sp18[2] = 0;` wrapped in `do { } while (0);` (in its original place, above the load: score 9).
- Together: score 0. d1 `.sched` shows the mechanism: the store carries the LOOP_BEG note, so sched.c:2058-2074 makes it
  depend on every earlier set/use and flush pending memory (the load 50 included), and sets `reg_pending_sets_all`, so the jump
  depends on it. Backward: T-1 jump, T-2 store (barrier), T-3 `p` (boosted), T-4 load (not blocked: the store is two cycles
  away), T-5 call (priority 4 beats the priority-1 inits). vol=127 and pan=7 stay above the call, which is the target order
  `jal; lh; lui/addiu; bgez; sh` (reorg still puts the sh in the bgez slot).
- Negative control: a plain `{ sp18[2] = 0; }` block scores 10 (BLOCK notes do nothing). The do-while's ref-weight effect
  (flow.c:1401) touches no pseudo here (the store is frame-relative with a constant), so the sched1 barrier did the work.

## (d) Generator proposal
When the residual is a constant init (`li sN,K` of a multi-set local) sitting after the first `jal` instead of in the
prologue, and the `.sched` trace for block 0 shows `blocking insn L for 1 cycles` followed by that init's uid being picked,
find the store after the call that sits right before load L in the backward order (a store into the call's out-buffer).
Move it below the first read of that buffer and wrap it in `do { … } while (0)` (marked `!FAKE: do-while`). If you want a
cheaper test first, check whether the init lands in a stall slot: grep `.sched` for `blocking insn` then the init uid.

## (e) What did not work (byte evidence, all `--try`)
- free sweep's best `free_020` (store moved BEFORE the call): 5, and it changes semantics (the callee writes sp18).
- store after the first return test (v3): 2 (prologue fixed, the sh lands in the next load-delay slot, bgez slot is a nop).
- store after the abs (v2): 3. Store next to `sp28[2] = 0` or before the sp20 loads (v4/v5): 5 (112 ins).
- `p` assigned after the inits, or right before the call (n_a, n_b): 10. `p` is still single-set and still boosted.
- vol/pan order swapped (n_c): 10 (pan=7 goes after the call instead). Ternary abs (n_e): 10. Plain block (n_f): 10.
- do-while around the two inits (d3): 20. do-while around the store above the load (d2): 9. Around the load (d4): 9.
- Body-local struct types (s1/s2): 10, the residual is identical (see g).
- Plain C with no marker: I found none. The only other route I can derive needs `p` non-birthing (reg_n_sets ≥ 2) with its
  set after the inits by LUID. Then the store takes T-2, p fills the stall at T-3 and the load goes at T-4. I found no natural
  second set of `p`: a dead set is deleted before flow counts sets, and reusing another pointer's variable merges two
  hard registers. This is derived and not tested on bytes.

## (f) Where the method fell short
- The residual reads as a register permutation (v0<->v1 x4) plus one moved `li`. Method step 4 (the allocation table) would
  send an agent after the permutation, but the permutation is downstream of a sched1 decision. What decided it here was the
  `.sched` ready-list trace: the `blocking insn N for 1 cycles` line and the uid picked right after it. A tool that flags
  "an insn picked in a stall slot crossed a call" would name this class in one line.
- Journal attempt 4 (NEAR, 94) saw the symptom right ("only one constant ever hoists") but not the cause (the stall slot).
  Journal attempts 1-3 call the launder a "birthing-boost re-tie". That is a mislabel: pan is multi-set without it.
- `cc1_dumps_tu.sh`'s `.lreg` extraction by `awk '/Function X/,/Function Y/'` runs past the function when the next name
  differs. Cut on the next `;; Function` line instead.

## (g) Structs question
No, not for this lever. I tested it on bytes: body-local `struct SVec { s16 vx, vy, vz, pad; }` for the four vectors, plus
`struct Act` (u16 x/y/z at +6/+A/+E) for `a0` and `p`, gives score 10 with the identical residual. The same struct spelling
plus the do-while gives 0 (`scratch/s3.c`). The decision is a function-unit stall (mips.md memory unit) plus sched1's
birthing boost on `p` (`reg_n_sets`), and struct typing changes neither. The array accesses are already `/s`
(MEM_IN_STRUCT_P, expr.c:4568-4577), and the store and load are frame-relative at different constant offsets, so alias
analysis was never involved. The struct spelling is still the better-reading source (an SVECTOR in/out pair and an actor's
position fields), so a structs phase can adopt `s3.c`'s types at no cost.
