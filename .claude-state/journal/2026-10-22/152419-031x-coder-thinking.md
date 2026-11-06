---
ts: 2026-10-22T21:24:19Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG18
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_Q4qE6LehAXQiopG9hF8x
---
Interesting! In the base (with barrier), arm3's last store is ALSO `(const_int -80)` with movhi_internal2 — so k WAS folded to a constant. The only difference between arm1 and arm3 blocks is the `asm_input ("")` insn (insn 177) between the two zero stores and the last store.

So the asm insn (a zero-width `asm_input`) breaks the common suffix. Without it, the last 3 insns match.

So to defeat cross-jump in plain C, I need SOME insn difference in the suffix. Since the final insns must be identical in asm, the difference must be a pattern that assembles identically.

Options: the `sh v0,48` store pattern. In both arms it's movhi_internal2 with const -80. If in arm3 I make it movhi_internal with a register, the asm would be `sh v0,48` and the li -80 must come from elsewhere (a real reg definition).

So I need k to survive as a register through cse2. In the base, k was folded. Why? Because k is a const-initialized local. cse2's REG_EQUAL propagation.

How to make a value that is -80 but not a constant to cse2?

Idea: derive it from a variable: `s16 k = sp10.v[2] < 0x380 ? -0x50 : -0x50;` folds.

Idea: compute from another value at runtime, e.g. `k = 0x380 - 0x3D0;` folds.

Idea: `k = (s16)(0xFFB0 + 0)` folds.

Idea: use an existing value: at that point, is there a register holding something? In the target, arm3's block is preceded by the compare. `sp10.v[2]` is in v0 (loaded). k = -0x50 could be derived: no.

Idea: use a static const global: `extern s16 D_something;` → a load, extra insn.

Hmm. So the movhi_internal2-with-const pattern is what both have. Maybe instead make arm1 differ: arm1's store as a register store, i.e. in arm1 use a variable k1 = -0x50 that survives... same problem.

OK, so what about a *different* pattern for the same asm: `(set (mem:HI) (reg))` vs `(set (mem:HI) (const))` requires the reg version. Alternatively `(set (mem:HI) (subreg:HI (reg:SI k) 0))` — the "HI from SI subreg" version, which is what w2 had (s32 k). In w2 the store at 14cc got folded? w2's merge was 3 insns (sh zero,36; sh zero,46; sh v0,48) so arm3's last store STILL matched arm1's. So the subreg also folded to a const by cse2.

What if k is s32 and *not* const-initialized but computed... no.

New angle: make the two arms' *jump* differ. Cross-jump merges the suffix including the jump; if the successors differ, no merge. Both jump to 14fc. But what if I restructure the if-chain so arm1's fallthrough goes to the join while arm3 jumps? In the target, arm1 ends with `j 14fc; sh v0,48` — an explicit jump. So arm1's block ends with a jump too.

Hmm, but why does arm1 need a jump? Because it's followed by the cond2 test.

What if I reorder the chain: make arm1 the LAST else (fallthrough)? Then the layout changes entirely.

What about the *successor* difference: arm1 jumps to 14fc (the join after the chain), arm3 also. Same.

OK, radical idea: what if the target's arm1 and arm3 blocks differ because the ARM3 block's jump has a different target? No, both 14fc.

Alright, let me reconsider: maybe cross-jump in gcc 2.7.2 only merges when the blocks are *not* in the same "then/else" chain... no.

Hmm, actually let me reconsider the ROM. Maybe the ROM's arm1 isn't `-0x50` but a store of a *pre-existing* register whose value is -80 from elsewhere, e.g. `unk30 = k` where k was set earlier in the function (before the chain) as -0x50 AND ALSO used elsewhere (so it can't be folded). Then the arm3 store would be a reg store, arm1 a const store → no merge. And the li -80 would be born early... but the target shows `li v0,-80` INSIDE arm1 and arm3 (1458 and 14cc), not at the function top. So no.

Wait — 1458 li v0,-80 in arm1 and 14cc li v0,-80 in arm3. Two separate lis. So both arms materialize -80 locally. Both are const stores in RTL.

Therefore, in the ROM the difference between the blocks must be in an insn OTHER than the last store... but the suffix sh0,36/sh0,46 is identical too. Unless the ORDER differs in one arm! Look at target arm3 again: 14d0 sh zero,36; 14d4 sh zero,46 — same as arm1 145c/1460.

Everything identical. So the ROM's compiler did NOT cross-jump these two blocks, while ours does. Different compiler? Maybe the ROM build used a different gcc (2.7.2 vs 2.8?) or -fno-cross-jumping? But the ROM DID cross-jump arm2/arm4 (they share the tail at 14ec). Unless that sharing came from the source.

Hmm! What if arm2/arm4's shared tail in the ROM comes from cross-jump, meaning cross-jump is on. Then arm1/arm3 must differ. 

Unless... the ROM's arm3 is NOT identical: maybe in arm3 the last store is `unk30 = k` where k is a *variable* that is also stored somewhere else. Look at the function tail:

```
((...)a0)->unk32 = 0;
if (sp10.v[0] < -0x400) sp10.v[0] = -0x400;
if (sp10.v[1] >= -0x101) sp10.v[1] = -0x102;
```

Target tail: 1500 lh v0,16(sp); slti -1024; beqz; li v0,-1024 (delay); sh v0,16(sp); 1518 lh v0,18(sp); slti -257; bnez; move a0,s0 (delay); li v0,-258; sh v0,18(sp).

Hmm, what if the ROM source had `s16 k` declared at function scope, assigned -0x50 in arm3, and the compiler kept it in a register because... no, the li is inside arm3.

Let me look at this from yet another angle: maybe our compiler merged arm1 and arm3 in the *base* build too, but the asm insn prevents it. So the ROM's source had something at that spot. What plain C produces a zero-width RTL insn between two stores? NOTHING in plain C — except a construct that creates an insn that later vanishes... 

Hmm! What about the `do { } while (0)` trick (loop notes)? A `do{}while(0)` creates a NOTE_INSN_LOOP_BEG... no, for an empty body the compiler may drop it.

What about a store to a local variable that's optimized away? Like `pad[0] = 0;` where pad is dead → removed by dead-store elimination, but it might survive until after jump2? DSE (flow) runs before jump2? flow runs early. Hmm.

The moves mention "§373 DEAD-RESET CSE-BREAKER": `pb = 0;` dead assignments used to break cse. Those are real insns though (dead but present at cse time).

For cross-jump (jump2, post-reload), a dead insn would have been removed by dbr/flow before... Actually a dead store to a stack slot might survive to jump2! And it would occupy an insn slot (asm-wise it would emit a `sw`/`sh`) — no good, it must not emit.

Unless it's a store to a slot that's later overwritten... it still emits an insn.

OK. What about a difference in the *delay slot*: the j's delay slot contains sh v0,48 in both.

Let me step back and consider: maybe the real ROM source for arm3 uses a *different variable type* making the store pattern `movhi_internal` (reg) with the li born from a different source... The target's li at 14cc is 3 insns before the store — consistent with a register k whose li is hoisted by sched1, OR with a const store whose li sched1 placed early.

Honestly, since both are plausible, and my job is just to find ANY plain-C body scoring 0, let me try to make k survive as a register by preventing cse2 folding. Ways:

(a) Give k a second use that cse can't fold, e.g. `k` used in a comparison that is later folded... 

(b) Declare k as `volatile s16 k` — adds a stack store, no.

(c) Use `u16 k = 0xFFB0;` → store as HI: value 0xFFB0, same bits, same asm (`li v0,-80`? the li would be 0xffb0 → `li v0,-80` since it's the same 16-bit pattern... for HImode the li would be `li v0,0xffb0` = 65456 → same encoding as -80 in 16 bits? MIPS li with 0xffb0: addiu v0,zero,0xffb0 = 0xFFB0 = -80 as signed 16. Same instruction!). But cse still folds a constant.

Hmm.

(d) Make the value not a literal constant but a register copy from a memory location that holds -0x50... e.g. sp10.v[1]? no.

New idea: **use the existing `k` but make the arm1 store the register too** — no.

**Different approach: attack the CFG.** What if I write arm3's body such that it's not a separate block but shares code with arm1 by construction... no, target has both.

**Wait.** Maybe I should reconsider which arms merge. In the base with the barrier, the merge doesn't happen because of the asm. What if instead of preventing the merge, I make the compiler merge a DIFFERENT pair such that the layout matches? No.

Let me look at this from the "what would the original source look like" angle once more, and consider that arm1's body might differ in a way that's invisible: e.g. the original might store `unk30` BEFORE `unk24`/`unk2E` in one arm, and sched1 reorders. Since sched1 runs BEFORE jump2, the final order is what matters — and it's the same. Unless sched1's reordering differs per block due to dependencies... they're independent stores to the same base register; sched1 might reorder differently. Both blocks show the same final order.

Hmm, hold on! Maybe the ROM's arm3 block does differ: notice arm1's `li v0,113` is in the *delay slot* of the branch at 1444 (i.e., it's part of the PREVIOUS block's delay slot? No — the branch at 1444 is `beqz v0,146c`, and the delay slot at 1448 has li v0,113, which belongs to the branch's block but executes in both paths.

In arm3: 14b8 beqz v0,14e0; 14bc li v0,113 (delay); 14c0 sh v0,32.

So the delay-slot li is in the *branch* block, not the arm block. Both same.

BUT: cross-jump's block comparison starts from the block's head. arm1's block head is 144c (sh v0,32). arm3's head is 14c0. The blocks include: sh32, li1536, sh34, li-80, sh0, sh0, j, sh48. Identical.

Honestly, maybe gcc 2.7.2's cross-jump has a constraint that the two blocks must not have the same predecessor... they don't.

Wait — maybe it's about `rtx_equiv_p` and the REG_DEP_* scheduling notes? Notes aren't compared.

Hmm, but what about `REG_EQUIV (const_int -80)` notes — from the dump, arm1's store has `expr_list:REG_EQUIV (const_int -80)`. Notes aren't compared.

Let me test the hypothesis directly: does cross-jump merge two identical blocks in this compiler? In w2 it merged 3 insns of arm1/arm3. Yes it does.

So the ROM's arm1 and arm3 genuinely differ in RTL. The only invisible-to-asm differences available: mem flags (/s vs not), subreg, and pattern choice. We tried subreg (s32) — folded. Let's check whether w2's arm3 store at 14cc was a const store: the merge included sh v0,48, so yes.

Hmm, but wait: in w2 arm3 the `li -80` is at 14c0 (a separate insn), and arm1's li -80 is in the delay slot at 145c. So the *suffix* match was sh0,36; sh0,46; sh v0,48 — the last store matched, meaning const.

What if I could get k to survive as a register? Let's try harder:

`u16 k; ... k = sp10.v[2] ...` no.

**Idea: make k's value come from a global that is 0?** no.

**Idea: reuse an existing computed value.** -0x50 = -80. Is there anything in the function equal to -80? The tail has -0x400 and -0x102. No.

**Idea: `s16 k = -0x50;` but use k TWICE in the arm, once in a way that gets folded later**: e.g. `unk2E = k - k;` → folds to 0 (store zero). Then k has 2 uses; cse still folds both.

**Idea: store through a union?** no.

**Idea: `s32 k = -0x50;` and store `unk30 = (s16)(k & 0xFFFF);`** — folds.

OK, different tack: maybe the difference is in the FIRST insn of the block. Cross-jump merges the longest common SUFFIX. If the last store differs, no merge. But also: gcc's find_cross_jump has a rule — it requires at least... let me actually read the compiler's cross-jump code to find a lever. jump.c in gcc 2.7.2. Is the source available in the repo? tools/bin/gcc-2.7.2-psx/ — maybe only binaries. Let me check for source.

Actually, gcc's cross-jump (find_cross_jump) has this important detail:

```
  /* Don't allow the first insn of the block to be the matched one... */
  /* We don't cross-jump two blocks if one of them is the target of the other... */
```

and crucially:

```
      /* If we run past the beginning of the block, stop. */
```

and

```
  /* Do not allow the labels to be crossed... */
```

Hmm, also there's this in gcc's jump.c cross_jump:
```
	  /* Don't do this if the block is the last block in the function... */
```

And a big one: `onlyjump_p` / `simplejump_p` requirements.

Let me look for another lever: `condjump_p`. In cross_jump, blocks are compared only if... 

Honestly, empirical iteration is cheaper. Let me generate a batch of ~10 variants and score them all at once (sc.sh does one compile each, ~fast).

Variants:
1. w6: k at function top (s16).
2. w7: k at function top (s32).
3. w8: arm3 store `unk30 = k;` with `s16 k = -0x50;` declared at top of function, assigned in arm3 (`k = -0x50;` in arm3).
4. w9: arm3 stores via a `s16 *` local pointer.
5. w10: arm1 stores via `s16 *` local pointer.
6. w11: arm3's unk24 and unk2E stored via `*(s16*)` casts (mem without /s) — we saw the cast didn't change anything.
7. w12: arm1's unk30 store written as `unk30 = -0x50 + 0;`? folds.
8. w13: arm3 uses `unk30 = k;` where k is `s16 k = -0x50;` and additionally `sp10.v[1] = sp10.v[1];`?? no.

Alternatively: change the arm ORDER in the source so that arm3 comes before arm1 (swap the two conditions' bodies). Then arm3 is at the position of arm1... the layout would differ. The target has arm1 first. Hmm, but if the compiler merges them, the merged block's placement might still match? Probably not.

Wait — actually, here's a thought: what if I make arm1 and arm3 NOT identical by making arm1's `unk22` store different... no, must be 0x600.

Hmm, what about the possibility that in the ROM's source, arm3 stores `unk30 = k` where k is a *parameter-derived* value... 

Let me look at the sibling function func_8017D6D0 (right after) for the idiom. Not helpful.

New idea — **the `(s16)` truncation of sp10.v[2]**: In arm3, the condition is `sp10.v[2] < 0x380` (a plain s16 compare). In arm1 the condition is complex. What if the original arm3 body reused a temp from the condition? no.

OK let me try yet another approach: maybe the merge can be avoided by making arm1's block have a *different number of insns* than arm3's — e.g. arm1 stores unk30 with the li born as a separate insn placed differently... but asm must match exactly.

Alright, since the asm is identical, maybe the real answer: the ROM's arm1 block and arm3 block differ because the ROM's arm1 store is `(const_int -80)` in HImode (movhi_internal2) and arm3's is a *register* (movhi_internal) — with the register being v0 and the li coming from sched1 hoisting. That's exactly the s32-k attempt; but cse2 folded it. Why? Because `(subreg:HI (reg:SI k) 0)` with REG_EQUAL const → cse2 substitutes the const. To block cse2, k must have no REG_EQUAL/known constant at cse2 time. 

**Idea: make k's value unknown to cse2 but still -80 at runtime: `k` set from a `s16` variable that the compiler proved is -80? No — anything provable gets folded.**

**Idea: prevent the fold by having k assigned in a way that produces a non-constant insn: `k = -0x50;` where k is `volatile`?** volatile forces a memory store+load, extra insns. No.

**Idea: use a `register` var? Not allowed.**

**Idea: multi-set k so cse2's REG_EQUAL is dropped**: e.g. `s16 k = -0x50; if (0) k = 0;` — dead code removed at the frontend.

Hmm, what about `s16 k = -0x50; k = k;`? folds away.

Let me try: does the compiler even keep the `s32 k` version's store as a reg if the value is -0x50 but k is used in TWO arms? no.

OK, alternative: **make the store's address differ**. arm3's store to unk30 could be written as `*(s16 *)((u8 *)a0 + 0x30)` — we tried (w4: arm3's store via cast, 106 merged). So mem flags don't matter.

**What about making arm3's store to a DIFFERENT but overlapping address expression that cse2 can't fold to the same? e.g. `((s16 *)((u8*)a0 + 0x20))[8] = k;`** → after folding, same. Merged.

Hmm, hold on. What if the difference is a `NOTE_INSN` that survives? No.

Let me revisit: maybe cross-jump here isn't jump2's cross-jump but the *dbr* (delayed branch reorganization) or "reorg" merging. The tool comment says "c10's cross-jump only in .jump2". In our w2 case the merge appears in .jump2.

Let me read gcc's jump.c cross_jump conditions. Is the gcc source in the repo? Let me check tools/bin.

Actually — here's a much better idea. gcc's `find_cross_jump` has this:

```
  /* Do not cross jump if the two blocks have different numbers of insns... */
```
and importantly:
```
      if (i1 == BB_HEAD (b1) || i2 == BB_HEAD (b2)) ...
```
and
```
  /* If the blocks are the same except for the last insn, ... */
```

Also there's `rtx_renaming`: `rtx_equiv_p` treats a register as equivalent only if the *register numbers* can be consistently renamed, and it uses `exp_equiv_p` with `labels`... but importantly it requires `REGNO >= FIRST_PSEUDO_REGISTER` renaming? After reload all are hard regs.

OK, I'm going too deep. Practical decision: try a batch of ~10 quick variants, see if anything scores 0; if not, WALL with evidence. But a WALL requires ≥20 min and ≥30 scored tries. I'm at ~15 min with 6 tries.

Let me think about the most promising batch:

Since the merge is of the common suffix and the asm is fixed, the ONLY way is a different insn pattern in the suffix. Let me enumerate the suffix insns and find a pattern alternative for each:

- sh zero,36(s0): `(set (mem:HI ...) (const_int 0))` → movhi_internal2. Alternative: store a register holding 0 → movhi_internal, asm `sh reg,36(s0)`. But the target has `sh zero,36` — the register must be $0! `sh zero` means the source register is zero. movhi_internal with a reg allocated to $0? gcc never allocates a pseudo to $0, but if the value is the constant 0, expand uses `(const_int 0)` → movhi_internal2 → emits `sh zero`. Hmm, actually `sh zero,36(s0)` comes from movhi_internal2 with const 0 (it uses $0 directly).

- j 14fc + sh v0,48.

So for arm3 to differ, one of these must be a different pattern producing the same asm.

What if arm3's unk24 store is `unk24 = t;` where t is a variable known 0? → reg store, asm `sh <reg>,36` — but the reg would be allocated somewhere, not $0, unless... the value 0 forces $0? In gcc, storing a zero constant uses movhi_internal2 which emits `sh zero`. If it's a register holding 0, gcc would emit `sh v0,36` (different asm). Unless the reg is allocated to $0 — not possible.

So the only candidate is the last store (sh v0,48) — with v0 being a real reg. In arm3, if the store source is a REG (not const), the pattern is movhi_internal and the asm is `sh v0,48` — matching! The li -80 must then come from a separate insn (from k's definition), which sched1 places at 14cc (3 insns before) — exactly the target! And in the target, arm1's li -80 at 1458 is also 3 insns before its store, but for arm1 the li is generated by movhi_internal2's scratch.

So the ROM's source very likely had exactly that: arm1 stores a constant, arm3 stores a variable. And in the ROM's build, the variable's li was NOT folded by cse2.

So: how did the ROM's cse2 not fold? Maybe because in the ROM's source k was assigned in a way that produced a register with no const note — e.g. `k` assigned from a *different* expression like `k = -0x50;` where k is s16 and cse2's REG_EQUAL propagation requires the reg to be "not used before"... 

Hmm, in our base build, k WAS folded (const store in arm3). With the barrier present. So our compiler folds k. The ROM's didn't. Different code shape.

What if in the ROM k was assigned in the *condition* block or before the chain? e.g.:

```
s16 k = -0x50;
...
} else if (sp10.v[2] < 0x380) {
    ...
    unk30 = k;
}
```
Then k's definition is in the entry block and the use in arm3 — cse2's REG_EQUAL propagation across blocks might not happen (cse2 works per EBB; a const set in the entry block does get a REG_EQUAL note and cse2 CAN propagate constants to other blocks via `cse_set_around_loop`? no, that's loops). Actually gcc's cse does handle cross-block constant propagation through REG_EQUAL notes when the register is unchanged — there's `reg_eqv` machinery and `fold_rtx` for REG looks at `REG_EQUAL` notes only within the current EBB's table... I believe cross-block REG_EQUAL propagation is done by `cse_set_around_loop` only for loops, so a constant defined in the entry block and used in arm3 would NOT be folded by cse2 (the table is reset per EBB).

But then the li would be born at the entry block, not in arm3. Unless... the register gets its li in the entry block and stays live — but the target has the li inside arm3.

Hmm, unless flow/sched1 rematerializes? No.

OK, so k's definition IS in arm3. Then cse2 folds it.

Unless the definition is in a place cse2 can't see: e.g. inside an `if` that merges? 

What about this: k's definition is a *store* to a stack slot then a load? extra insns.

Alright — maybe the actual difference in the ROM is not the last store but a different `li` placement, i.e. arm3's li -80 at 14cc vs arm1's at 1458 are both 3-before-store. Identical.

Hmm hold on, let me recount arm1: 144c sh32, 1450 li1536, 1454 sh34, 1458 li-80, 145c sh0-36, 1460 sh0-46, 1464 j, 1468 sh48. The li -80 at 1458 is 3 insns before sh48 (145c,1460,1464 in between). 
arm3: 14c0 sh32, 14c4 li1536, 14c8 sh34, 14cc li-80, 14d0 sh0, 14d4 sh0, 14d8 j, 14dc sh48. Also 3 insns between.

Identical in every way. So the ROM's compiler did NOT merge them, and the RTL difference is invisible in asm — OR the ROM's compiler is a different version.

Given the barrier currently in the tree produces a 0 score, and the item is in the "barrier" class, the task is to find a lever-free equivalent. If the RTL difference is invisible, the only possibilities are pattern-level differences like mem flags (tried), subreg (tried), and... 

**REG_EQUIV vs REG_EQUAL notes!** Cross-jump compares only PATTERN — but `insn` vs `jump_insn`? What about `INSN_CODE`?

Hmm — actually! There's one more possibility I overlooked: gcc's `find_cross_jump` refuses to merge when the insns have different `INSN_CODE`? No, but it does compare via `rtx_equiv_p` which compares the *patterns*.

OK — but what if the two blocks' patterns differ in the *order* of insns after sched1? Both same order.

Let me try the mem-flag thing more carefully: our w5 changed arm1's store to `*(s16 *)((u8 *)a0 + 0x30) = -0x50;` — score 106 (merged). So mem/s doesn't matter (or expand makes them equal anyway).

I've spent ~20 min. Let me do a fast batch of remaining plausible variants (10+), then decide. Time is 15:35ish.

Batch (all barrier-free):
- v1: k at function level s16, used in arm3.
- v2: k at function level s32.
- v3: arm3: `s16 k = -0x50;` + store via `*(s16*)((u8*)a0+0x30)` (mem non-struct + reg).
- v4: arm3: `s16 k = -0x50;` and `((Unkstruct*)a0)->unk30 = k;` but with k declared `u16`.
- v5: arm3 stores `unk30 = k;` and arm1 stores `unk30 = -0x50;` — with arm1's stores written via a local `s16 *q` pointer (changes arm1's block patterns? no).
- v6: split arm3's body: `s16 k = -0x50; ...; ((Unkstruct*)a0)->unk2E = 0; ((Unkstruct*)a0)->unk30 = k;` with the two zero stores written as `unk24 = 0, unk2E = 0;` in one statement (comma) — probably same.
- v7: make arm3 the fallthrough (reorder the chain: put cond3 test first) — big layout change, unlikely.
- v8: arm3's k assigned AFTER the other stores: `((Unkstruct*)a0)->unk20=...; ...; { s16 k = -0x50; ((Unkstruct*)a0)->unk30 = k; }` — k's birth is right before the store. Then sched1 might still hoist the li to 14cc position, and cse2 folds → merge. Try anyway.
- v9: `s16 k = -0x50;` used twice: `unk2E = 0; unk30 = k;` plus `sp10.v[1] += k - k;`? no.

Honestly the most promising is to prevent cse2's folding by giving k a use that cse2 can't constant-fold — e.g. storing k to a stack slot that's later dead? Adds insns.

WAIT. What about `sp10.v[1]`? The target tail does `if (sp10.v[1] >= -0x101) sp10.v[1] = -0x102;`. Hmm, -0x102 and -0x101. And k=-0x50.

Hmm, let me reconsider the possibility that arm1's block in the ROM is NOT the same: what if the ROM's arm1 stores unk22 = 0x600 *after* unk30? No, order is fixed by sched1... but sched1 could produce different orders for blocks with different dependency graphs. Both blocks have identical dependency graphs.

Decision: I'll do one more high-value experiment: check whether cross-jump in this compiler merges two blocks that differ ONLY by a REG_EQUIV note... no.

Alternative high-value experiment: maybe the merge is defeated by making the last store in arm3 use a *pointer deref with a different mode*, e.g. store unk30 as two u8 stores? No — asm differs.

Let me try the "k used twice" idea concretely: in arm3, `((Unkstruct*)a0)->unk30 = k;` and `sp10.v[0] = sp10.v[0];`? no.

Actually! Here's a clean one: cse2 folds k's constant into its uses only if k is not *modified* and has a REG_EQUAL note. If k is set TWICE in the same block (two sets), cse may drop the note. But two sets = two insns.

Hmm, what if k is assigned from a value that cse2 knows is constant only through a *different* register, e.g. `k = (s16)0xFFB0;` — same.

Let me look at whether `-O2` folding of a HImode const store happens in *combine* rather than cse2. If it's combine (which runs before sched1), then the pattern is fixed early. In the base dump, arm3's store was already movhi_internal2 with const at jump2, and combine runs before sched1. To see where the fold happens, check .combine or .cse dumps of the base for arm3's store.

Let me grep the base .rtl (initial RTL) for arm3's store pattern: if the initial RTL already has `(const_int -80)` (from the frontend folding k), then k was folded at expansion — meaning the C frontend propagated the constant. In that case, NO C spelling with a constant-initialized variable can avoid it; I'd need a value the frontend can't fold.

Check .rtl dump.
