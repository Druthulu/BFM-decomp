# func_80182FB4 (src/ov_SC05_001/ov_SC05_001_jr_8017BEBC.c) — d31, P36 S104

**RESULT: score 0 in plain C, zero levers and zero gotos.** Levers before → after: **3 → 0** (2 `__asm__` launders
+ 1 `$3` pin), plus all 9 goto labels gone. `PACK/body.c` is the goto chain rewritten as a structured `switch`.
All three other copies of the class close with the same text at 0 (table at the end). The free sweep's best was 8
(free_151, a do-while); body_free.c scored 34.

## (a) The residual
body_free: 34, COUNT (212 vs 214). free_151: 8. Once the nop-fill noise from the case 1 misschedule is removed, two
real defects are left:
1. **case 1, the `func_8012B178` call**: the target computes `addiu a1,v0,-16384` BEFORE `move a0,s0`, and reorg puts
   the move in the `jal` delay slot. Mine had `move a0,s0; …; jal; addiu a1,…` (the addiu in the slot). In the free body
   the tail after the join also landed in `$a2/$a1` instead of `$v0`, and the load-delay nops were filled differently
   (hence the 2 missing instructions).
2. **MERGE_4C0** (the `func_8012ADE4` block): the ptr load `lw v1,32(s0)` and the constant `li v0,2` have their
   registers swapped (the `$3` pin).

## (b) Mechanism (every step proved on bytes and read in the dumps under `scratch/dumps_*`)
1. Defect 1: expand_call loads `a0` then `a1` (`calls.c:1855-1881`, args in written order, no PUSH_ARGS_REVERSED on
   MIPS). With `arg1 = ret - 0x4000` as one pseudo that dies at `a1 = P`, combine substitutes P's definition into the
   hard-register load (`can_combine_p`, `combine.c:803ff`; nothing there refuses it on MIPS), so the addiu sits AFTER
   `a0 = s0`. sched1 then keeps LUID order: equal priority, class 3 for both (`rank_for_schedule`, `sched.c:2385-2436`).
   The original computed the whole argument in EACH arm of the sign test, so `arg1` (reg/v 128 in `.combine`) is set
   in two blocks. That makes it a global allocno, and global.c's copy preference gives it `$a1`, so `a1 = 128` becomes
   a no-op. Each arm ends `sll v0; negu v0; addiu a1,v0,-16384`, and **post-reload cross-jump** (`jump.c:2371`
   find_cross_jump, run from `toplev.c:3142`) merges the two identical tails. That leaves the target's
   `bgez v0,T; addiu v0,s1,-4096; T: sll; negu; addiu a1` with the addiu ahead of `move a0,s0`. Proof: `.combine`
   shows both tails (insns 267-270 and 278-282); `.jump2` has one. A ternary
   `-((d >= 0 ? d : sVar1 - 0x1000) << 4) - 0x4000` gives the same bytes, because fold distributes the shift, negate
   and minus into both COND_EXPR arms. The in-place `if (d < 0) d = …;` form scores 32 (`scratch/n1.c`).
2. Defect 2: the MERGE_4C0 block has exactly THREE local quantities: q0 = ptr (refs 2, pri 3333), q1 = HImode const 2
   (refs 2, pri 10000) and q2 = the `lh` temp. In the goto body the `+ 0x800` result went into the shared, global
   `uVar2`, so q2 had 2 refs and pri 10000, equal to q1. local-alloc's hand-written 3-quantity sort
   (`local-alloc.c:1486-1507`) compares FIXED quantity numbers, not `qty_order[]` slots. With
   compare(0,1) > 0 and compare(1,2) == 0 it swaps twice and returns BIRTH order, so ptr takes `$v0` first.
   Storing the sum directly in that arm (`*(s32 *)(param_1 + 0xe0) = … + 0x800;`) makes the add's result a local
   pseudo tied to the `lh` temp (`combine_regs`, the temp dies there). q2 then has 4 refs and pri 20000 > q1, the sort
   really reorders to [q2, q1, q0], and ptr is allocated last into `$v1`. Simulator (lsim3) on `.lreg`, 0 mismatches:
   c1 = q0 v0 / q1 v1 / q2 v0; f1 = q2 v0 / q1 v0 / q0 v1. The two stores to `+0xe0` (this arm and the rand arm) and
   the two copies of the whole merge block (case 0 and case 1 in the structured text) are merged by the same jump2
   cross-jump, which gives the target's shared `j TAIL; sw v0,224(s0)`.

## (c) The moves (the body is structured, so each is one line of C)
1. case 1: compute the argument in each arm, `if (d >= 0) arg1 = -(d << 4) - 0x4000; else arg1 =
   -((sVar1 - 0x1000) << 4) - 0x4000;`, replacing the in-place `if (ret < 0) ret = …; ret <<= 4; ret = -ret;` plus the
   launders.
2. the `func_8012ADE4` block: store `*(s32 *)(param_1 + 0xe0) = … + 0x800;` in place, not through the shared `uVar2`
   (which replaces the `$3` pin).
3. (readability, byte-neutral) the whole goto chain rewritten as a structured `switch`: every `goto EXIT` became an
   inline `func_80184580(param_1); return;`, MERGE_4C0 is written out in both case 0 and case 1, MERGE_4E8 is the
   `else if`, and the rand arm's `uVar2` is local to its block. Cross-jump re-merges all the duplicates. The locals were
   also simplified (`ptr0/arg0/ptrA/arg1` inlined, `ptr2` inlined, `ret` no longer reused, the stale `§17 pin` comment
   dropped) and the `(void (*)(void *))` cast on the exit call removed. Each change was `--try`d at 0, alone and
   combined.
- Probably the original spelling: `scratch/body_abs.c` has NO `d`/`arg1` locals. Both calls are written as an ABS-macro
  expansion, `-0x8000 - (ABS(0x1000 - sVar1) << 4)` and `-(ABS(0x1000 - sVar1) << 4) - 0x4000` with
  `ABS(x) = ((x) >= 0 ? (x) : -(x))`, and it also scores 0. fold turns `-(0x1000 - sVar1)` into `sVar1 - 0x1000`,
  which is exactly the target's `addiu v0,s1,-4096` arm. No ABS macro exists in the tree's headers, so body.c keeps
  the explicit if/else.
- `s32 pad[4]` STAYS. It is the target's `vars=16`, and without it the frame is 32 (score 10). `.lreg` has no
  no-hard-reg pseudo ("zombie") that could account for the 16 bytes, so it is a real dead 16-byte local in the
  original (a VECTOR/2×SVECTOR-sized aggregate). It was unmarked in body_free and is not a lever.

## (d) Generator proposal
**When the target has a call argument computed BEFORE an earlier argument's `move aN,sK` (the earlier move ends up in
the jal delay slot), and the text computes that argument after an in-place `if (x < 0) x = y;` fix-up, rewrite it as
an if/else that assigns the FULL argument expression in each arm (`if (x >= 0) a = F(x); else a = F(y);`).** Post-reload
cross-jump re-merges the identical tails, and the argument local becomes a global with an `$aN` preference. Companion
rule: **when a goto-merge block's final value flows into a variable shared with another arm (`v = …; goto STORE;`) and
the block has a 3-quantity register swap, store the value directly in that arm**. This adds refs to the tied temp so the
3-quantity sort really reorders. Both follow from S104's "goto chain → structured C" pattern (d3/d9/d11/d17): write
each arm's whole tail and let cross-jump merge. No text-mutation generator reaches it.

## (e) What did not work (bytes)
- body_free: 34. free_151 (do-while on `sum`): 8. c1 (move 1 only): 4. c2 (moves 1+2, goto text): 0.
- n1: structured, but case 1 back to in-place `if (d < 0) d = …; f(-(d << 4) - 0x4000)`: 32, 212 ins.
- t1: case 0 as a ternary on a local `d` (`d >= 0 ? d : sVar1 - 0x1000`): 7. The arms come out swapped
  (`bgez` vs `bltz`). The ABS form on the expression itself (t2) gives 0.
- p5: the rand arm storing in each branch (no shared `uVar2` store): 19 (217 ins). The single store after the if/else is
  load-bearing.
- s1: structured, with the rand arm storing per branch and the BEE8 test placed before the merge block: 33.
- c3: `pad[4]` removed: 10 (frame 32 vs 48).

## (f) Where the method fell short
- The residual's hunk view put the case-1 call's addiu in the delay slot and made it look like a scheduling or
  launder problem. Dumping `.combine` showed the real question: why the target's argument pseudo was NOT combined into
  the `a1` load. The only structural answers are a call in between or a definition in another block. Reading
  `can_combine_p` for "what would refuse this" gave the two-arm spelling on the first `--try`.
- The 3-quantity quirk (d5's lesson) predicted the second close exactly: quantity numbers, not slots, are compared.
  lsim3 reproduced both allocations with 0 mismatches. `tools/localalloc_sim.py` (the full sort) would have mispredicted
  c1, so lsim3's fix should be merged into the tool.
- The structured rewrite was tried only AFTER the goto text closed. It worked on the second try. Doing it first (S104
  step 14) would probably have closed both defects at once, because structured arms naturally store per arm and
  compute per arm.

## (g) Structs question: NO for this class (tested)
A body-local `Ent` struct (step 0x02, y 0x0a, speed 0x14, timer 0x1c, model 0x20, state 0x34, target 0xe0, phase
0xe4, count 0xe8), applied to every `param_1` access: on the closed body it stays 0 (`scratch/g1.c`, byte-neutral).
On body_free it stays 34 (`scratch/g0.c`). The levers came from control-flow shape (which values are block-global,
where cross-jump merges), not from memory aliasing. The `expr.c:4568` aggregate/scalar channel is not involved:
nothing here reorders a load around a store. The struct is still worth having for readability, and the field
offsets above are the entity layout the neighbouring functions use (`param_1 + 0x20` = model/child object whose
`+0x12` is a rotation, `+0x1a` a scale/angle). The one struct-shaped fact is the dead 16-byte local behind
`pad[4]`.

## Copies (all `--try` at 0 with the same text; only the exit callee's name and declaration differ)
| function | TU | file |
|---|---|---|
| func_80182FB4 | src/ov_SC05_001/ov_SC05_001_jr_8017BEBC.c | PACK/body.c |
| func_8018128C | src/ov_SC03_112/ov_SC03_112_jr_8017C294.c | PACK/scratch/copy_func_8018128C.c |
| func_8017F2E8 | src/ov_SC03_108/ov_SC03_108_jr_8017BEBC.c | PACK/scratch/copy_func_8017F2E8.c (keeps its own `extern void func_801808B4();` and `(void *)` call) |
| func_8017F674 | src/ov_SC03_110/ov_SC03_110_jr_8017D898.c | PACK/scratch/copy_func_8017F674.c |
