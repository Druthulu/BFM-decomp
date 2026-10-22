---
ts: 2026-10-22T11:15:23Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM2x
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_fnDQ46hdmaXAQzJdia8l
---
Pre-sched RTL: insn 235 = load into reg 167; insn 238 = `set a0 = 167` (the COPY!); 240 = a1=320; 242 = a2=240; 244 = call.

After scheduling: the copy (238) was COALESCED with the load (235) — the load became `set a0 = mem[73+32]` (insn 238 with uid 238 but content = load). So the load and the copy merged (coalesce pass), and the resulting insn kept uid 238 (the copy's uid) but the load's content.

Then sched1 reordered: 240 (li a1) before 238 (the load).

Hmm! So the order became li-then-load. Interesting — GCC's coalesce merged them, and the merged insn has the LUID of the copy (238) which is > 240? No, 238 < 240.

Wait, so insn 238 (load, after coalesce) has a LOWER uid than 240 (li). Yet it was scheduled after. So the scheduler preferred the li.

GCC sched1's `rank_for_schedule` gives priority based on "birth" — the number of insns that must be scheduled before it *within the block* plus a "birth" boost for insns whose operands are ready. There's also the rule that "an insn that is a call's operand setup gets a boost"?

Hmm, and there's `sched1`'s "delay slot" consideration: the block's first insn goes into the previous block's delay slot. sched1 tries to maximize the "bonus" for filling delay slots. Actually, in GCC's `sched1`, there's a heuristic `compute_insn_cost` and the "issue_rate" model.

Hmm, but the important observation: **in the target the load came first**. So something about the target made the load win.

Now let's think about the ASM version: the asm is between the load and the call. Then:
- block A: [load 235]
- block B: [asm, copy→a0, li a1, li a2, call]

Wait, but in the asm version the a0 copy would also exist. Let's dump the original to see.

Actually here's the thing: with the asm, the block containing the call is separate, and the load is in the previous block. So the load is forced first by block order.

Now, WITHOUT the asm, we need the scheduler to pick the load before the li. Since the li has a higher scheduling priority (birth boost), we need to give the load a higher priority or make the li unavailable.

**Idea: make the li depend on the load!** But the li's value is 320, independent.

Hmm, but WAIT. What if we reorder the ARGUMENTS so the load is not a0 but... no, semantics.

**Idea: what if a0 is set from the load in a way that creates a real dependency chain**? The `set a0 = 167` copy — coalesced.

**Idea: prevent the coalescing** so we have [load → copy a0] then the li. Then within the block, the copy depends on the load. The li is independent. Scheduler still might put the li first. Hmm.

**Idea: increase the load's scheduling priority by making it have more dependents?** No.

**Idea: Make the li a1,320 not a constant birth but something with a dependency.** E.g. write the second argument as an expression that GCC computes as 320 but with a dependency on the load? That changes semantics.

Hmm, wait. Let me reconsider. What does the TARGET's pre-sched RTL look like? Maybe in the target, the order of the arg setup in the RTL is: a0 first (load), a1, a2. And the scheduler didn't reorder. In our candidate, the RTL order was: load, copy-a0, li-a1, li-a2 — same order. After coalescing, the load absorbed the copy's uid, and then the scheduler reordered li before the load.

Hmm, so with the asm, the scheduler couldn't reorder across the block boundary.

**KEY IDEA**: What if we make the load be in a DIFFERENT BLOCK from the call, using a construct that survives to scheduling time?

In GCC 2.7, `flow` (the CFG pass) runs... let me check: the dump files include `.flow` — that's the "flow" pass dump (pass_flow). When does it run relative to sched? Let me check the .flow dump and see if the branch survived.

Hmm, but my goto/switch variants produced identical output (score 2), so those constructs were removed before scheduling.

What construct survives until scheduling? A real conditional branch. But a branch adds an instruction.

Hmm... unless the branch is one the target already has!

Look at the target: the join block at 3ad4. The `beqz v0,3ad4` at 39e0 jumps to 3ad4. So the join block is reached by a branch AND by fall-through.

What if we move the CALL into a different block? E.g., restructure so that the call is inside the `if` body (the != 0 branch) and also in the else branch? No, that duplicates.

Hmm, hold on. Let's reconsider: what if the load is placed at the END of the if-body block (before the branch target), i.e., the load happens in the if-body and the join block uses it? But the join is reached from two paths...

OK here's another thought: **What if we make the load's value flow through the `if` condition?** No.

Let me look at the problem from the "what does GCC's sched1 do" angle and try to make the load win the priority battle.

GCC sched1's `rank_for_schedule`:
```
  /* Find the earliest insn in the block that this one must wait for. */
  ...
  priority = birth (number of insns that must be scheduled before)
```
Actually in GCC 2.7 sched1.c, `rank_for_schedule` computes:
```
      /* Calculate the number of insns that we must wait for: the birth. */
      ...
      if (insn->priority > max_priority) ...
```
Hmm. Let me recall the actual code. GCC 2.7 sched1.c has:

```c
static int
rank_for_schedule (block, block_insns)
{
  ...
  /* Compute the dependencies.  */
  ...
  for each insn:
      /* Calculate the number of insns that this insn must wait for.  */
      ...
      /* The insn's priority is the number of insns that must precede it, plus
	 the "birth" bonus. */
```

And there's the crucial bit in GCC's sched1 `schedule_insns`:
```
  /* SCHEDULE_GROUP_P: instructions that are part of a call are scheduled together. */
```
The call group! In GCC 2.7's sched1, calls are grouped: `sched1` uses `SCHED_GROUP_P` for call_insn, meaning the call and its "dependents" (the arg setup) are scheduled together as a unit.

Hmm, but the group in our candidate was [li a1, li a2, call] and the load was separate. In the target, the group is [li a1, li a2, call] and the load is in the previous block.

Hmm. GCC's sched1 "call group" logic: in `schedule_insns`, when it encounters a call_insn, it collects the insns that "must be scheduled with it" (`call_scheduled`?). Actually GCC's sched1 has:
```
	  /* If this is a call, then we must schedule all the insns
	     that are used by the call at the same time.  */
```
That's for the "hard reg" setup.

OK, let me try an entirely different approach for item 2: maybe the difference isn't about the load at all. What if we make the CALL have a different shape so that the whole group is scheduled differently?

Alternatively: **make the load not a "movsi" but come from a different instruction** — e.g., `lwc1`? no.

Hmm, let me try: what if the load is `lw` from a pointer that GCC computes (e.g., `p + 0x20` where p is a u8*)? That's `v08_castload` — same result.

What if the load's address uses a different base register (e.g., a copy of p)? That would add a move.

Hmm. Let me look at this from yet another angle: **maybe the fix is to give the load a "birth boost" by making it depend on the immediately preceding instruction**. The load is at 73+32; reg 73 is s0. If the load depended on the result of the previous store's computation, it'd be forced later, not earlier.

Actually, for the LOAD to be scheduled FIRST in the block, it needs the HIGHEST priority. In GCC's sched1, the priority of an insn is computed via `rank_for_schedule`, and the key is:

```c
      /* Compute the priority: the number of insns that must be scheduled
	 before this one.  */
      ...
      /* Add a bonus for insns that are "birthed" early. */
```

Honestly, let's try empirical things:

Try: make the a0 value come from a COPY that can't be coalesced, so the block is [load 235, copy-a0 238, li-a1 240, li-a2 242, call]. If the copy isn't coalesced, then within the block the order would be load, copy, li, li, call? The scheduler might still put the li first (it has no deps). Hmm.

How to prevent coalescing? The copy `set a0 = 167` — coalescing happens in the `coalesce` pass (combine). It merges the load into the copy. If we could make the copy not a simple reg-reg move... e.g. `t = load; func(..., t, ...)` — the call's a0 operand is the pseudo 167 directly (no copy), and then register allocation assigns 167 to a0. In our dump there IS a copy (insn 238: set a0 = 167). Hmm, that copy came from... the asm? No, this is the no-asm candidate. Interesting — so GCC created a copy for the call arg.

Hmm, why? Because `167` is `reg/v:SI` (a pseudo). The call needs a0. GCC's expand emits `set a0 = 167`? That's unusual; normally the pseudo would be allocated to a0. This copy is likely because the pseudo 167 is used in a way that... Hmm, or maybe because `t` is also used in the `movsi_internal2` pattern.

Whatever. Let's try: make the pseudo's value flow to the call without a copy by using the load expression directly in the call (v03_inline) — that gave the same score 2.

Let me try a bunch of micro-variants around the call:
- Put the call's args in a different order in the source? Not possible (order defines semantics), BUT the arg evaluation order in C is unspecified; GCC evaluates right-to-left typically! So `func_8001D0E8(t, 0x140, 0xF0)` — GCC evaluates args in reverse order, so the li a2=240 is set first, then a1=320, then the load. In the RTL the order was: load(235), copy(238), li a1(240), li a2(242). Hmm.

OK let me try yet another approach: **use the `func_8001D0E8` call with the load as a0 but write the second arg with a redundant computation that GCC folds late**. E.g. `0x140` vs `(0x140 | 0)`. If GCC folds it only after scheduling, the li would be a non-constant expression → lower priority → the load wins!

That's promising! Let's try: `func_8001D0E8(t, 0x140 | 0, 0xF0 | 0);` or `0x140 + 0`, or `0x140 * 1`, or `(0x100 + 0x40)`.

GCC's fold at the front end would fold `0x140 | 0` to 0x140 immediately (fold-const.c is used by the front end). Hmm, the front end uses `fold` for constant expressions, so `0x140|0` → 0x140 at parse time. Damn.

What about something the front end can't fold but the optimizer can, AFTER scheduling? E.g. `0x140 & ~0` → fold handles it. Hmm.

What about a value that depends on a runtime value in a way that's provably constant but not at the front end? Like `D_80126B5E - D_80126B5E`? That's a global — the front end can't fold it (globals aren't constant in the front end), but the optimizer (cse/jump) could fold it to 0 later. But the value would need to be 320.

Hmm: `func_8001D0E8(t, D_801X - D_801X + 0x140, 0xF0)` — the load from the globals might not be removed (they're not const). Hmm, D_ symbols are `extern s16` etc, not const, so GCC must load them. That changes the code.

What about `0x140` written via a `static const`? A file-scope `static const int K = 0x140;` — the front end folds constants for static const? It would create a VAR_DECL, and the load might be folded at the RTL level (after expand, before sched). Hmm.

What about an expression involving a local variable that GCC can prove is the same? e.g.
```c
s32 k = 0x140;
func_8001D0E8(t, k, 0xF0);
```
GCC would copy-propagate k → 320 before scheduling. Same.

Hmm, what about the ORDER of evaluation: GCC evaluates call args right to left. So the RTL order would be a2=240 first, a1=320, then a0. But the dump showed load(235) first, copy(238), a1(240), a2(242). Hmm, the copy a0=167 was at 238 which is after 235 (load). So the order in RTL is load, copy, a1, a2 — not reverse.

OK. Let me try yet another thing: **What if we make the load's result used by the `if` that precedes it?** No.

**What if we restructure so the load happens BEFORE the if-block?** Then the load would be scheduled much earlier — wrong position.

Hmm hold on, let me reconsider the target structure once more:

```
39dc: andi v0,v0,0xff
39e0: beqz v0,3ad4
39e4: li a1,832     (delay slot of the beqz)
...
3ad0: sh v0,14(s0)
3ad4: lw a0,32(s0)  <- join
```

Wait, is 3ad4 really the join? The `beqz v0,3ad4` — yes, the branch target is 3ad4.

So in the target, the join block = [lw a0, li a1, jal, li a2].

Hmm, and the fall-through path reaches 3ad4 after `sh v0,14(s0)` at 3ad0 (whose delay slot is 3ad4). So the lw at 3ad4 is in the sh's delay slot.

Interesting: the join block's first instruction is in the delay slot of the preceding block's last instruction. That's standard MIPS layout.

Now in the candidate: 3ad4 = li a1,320; 3ad8 = lw a0,32(s0); 3adc = jal; 3ae0 = li a2,240.

So the join block = [li a1, lw a0, jal, li a2]. The scheduler put li a1 first.

**Crucial**: in the candidate, `li a1,320` is the FIRST instruction of the join block, placed in the sh's delay slot. The delay slot of the sh is a position where an instruction with NO dependencies is preferred (it must be safe to execute there). The `li a1,320` has no dependency on the sh → good delay-slot candidate. The load `lw a0,32(s0)` also has no dependency on the sh, but it depends on s0 which is fine.

GCC's `sched1` has a specific heuristic for delay slots: it tries to fill the delay slot with an instruction that has few dependencies. Hmm.

Hmm OK. Let me try to just brute-force many variants. But 15 variants all gave 2. Let me try more creative ones:

(a) Move the whole `{ t = load; call; }` block ABOVE the `if` statement? No, wrong semantics.

(b) What if the load is moved to a different place in the C such that it's in a different CFG block but at the same machine position? For example, what if the load is inside the `if` body (the !=0 path) and ALSO in the else path? Then two loads → 2 extra? No — the target has exactly ONE load. Unless the two loads are in different blocks and GCC's cross-jumping merges them... they'd be identical, so cross-jumping would merge the blocks! Hmm, but the paths differ.

Hmm, hold on! Let's reconsider. What if we DUPLICATE the load into both arms of the `if`? Then:
- The !=0 arm: [... sh v0,14(s0); lw a0,32(s0)]
- The ==0 arm (the `beqz` target): [lw a0,32(s0); li a1,320; jal; li a2,240]

GCC would then have 2 loads in different blocks → cross-jumping might merge them (identical instruction sequences) → but the blocks aren't identical overall.

And the count would be 201 (extra load) unless one is eliminated. Since the load is in a different block from its use in the ==0 arm... hmm, actually in the ==0 arm, the load would be at the top and the use right after → fine, 1 load. In the !=0 arm, the load would be after the sh → the use is in the join block. So the !=0 arm's load and the join's use are across blocks → needs a phi → GCC would keep both loads (201 ins) OR CSE them (the join's load is the same address, and the !=0 path's load dominates the join? no, the join has 2 preds).

Hmm, so 2 loads. The target has 1. Unless GCC's "tail merging"/cross-jump merges the ==0 arm's load with the !=0 arm's load — they're in different blocks, not adjacent.

Hmm.

(c) What if we restructure to make the call the FIRST thing in the join block but move the load into the previous block? The previous block ends with the sh. If the load were BEFORE the sh in the C source (i.e., inside the if body before the last store), it would be scheduled before the sh → wrong position (the target has the load after the sh).

Hmm, unless... the sh's delay slot is 3ad4, and the target's load is at 3ad4. What if the load were placed in the delay slot of the sh by being right after it in the RTL? It IS right after in the C source (the if-body ends with the sh, then the join block starts with the load). And sched1 moved the li ahead of it.

So we need the li to NOT be first in the join block.

**Idea: make the li's dependency chain include the load!** For instance, if the second argument were `0x140` but computed as `320` from a variable that is... no, semantics.

**Idea: make the load's priority higher by having MORE dependents in the block?** The load has 1 dependent (the call's a0 use). The li has 1 dependent (the call). Equal.

**Idea: Use the `asm` alternative — but we can't.**

**Idea: what if the function call is replaced by something that forces the a0 setup to be scheduled first?**

Hmm, what about making the call's first argument NOT a plain register but a memory operand? MIPS has `lw` only for loads; there's no `lw a0, 32(s0)` as a call operand form in GCC's MIPS (no memory operands for calls).

**Idea: what if we add an extra use of the loaded value that GCC eliminates but that raises the load's priority?** E.g. `t = load; func(t, 0x140, 0xF0);` plus `if (t == 0x12345678) { }` — GCC removes the branch but the comparison might raise the load's priority... but the comparison is removed before scheduling.

Hmm.

**Idea: check whether the difference is actually caused by the ASM's presence as a "scheduling barrier" rather than a block boundary.** In GCC, `__asm__ __volatile__` with no memory clobber is a barrier only for the asm's own operands. But GCC's `asm` statement in the middle of a function splits the basic block in the RTL (the asm insn is a barrier for scheduling: sched1 won't move insns across an asm? Actually GCC's sched1 does NOT schedule across volatile asm).

With the asm, the block containing the call is [asm, copy-a0, li-a1, li-a2, call]. The load is in the previous block. So block order forces load first.

Without the asm: one block, and the scheduler chose li first.

**So: I need a block boundary.** What survives until sched1?

Let's think about GCC 2.7's pass order precisely. I can determine it empirically from the dump file names: cand.i.flow, cand.i.jump, cand.i.jump2, cand.i.cse, cand.i.cse2, cand.i.loop, cand.i.sched, cand.i.sched2, cand.i.rtl, cand.i.dbr, cand.i.lreg, cand.i.greg.

The order in the dump dir listing is alphabetical, not pass order. But the numbering suggests: rtl (rtl pass), loop (loop pass), cse (cse1), jump (jump1?), cse2 (cse2), jump2, sched, sched2, lreg, greg, dbr.

In GCC 2.7, `pass_all_early_optimizations` includes: expand, sra, cse1, cse2, jump1(optimize_jumps?), cse3, jump2, ... and `pass_all_optimizations` includes: expand, sched1, ... then `pass_all_late_optimizations`: cse3, jump3, dbr, ...

Actually GCC 2.7's c-passes.c:
```
pass_all_early_optimizations:
  NEXT_PASS (pass_fixup_cfg);
  NEXT_PASS (pass_local_function);
  NEXT_PASS (pass_reorder_blocks);   /* reorder_blocks */
  NEXT_PASS (pass_split_edge);?   
  NEXT_PASS (pass_expand);
  NEXT_PASS (pass_sra);
  NEXT_PASS (pass_cse);      /* cse1 */
  NEXT_PASS (pass_ce1);
  NEXT_PASS (pass_ce2);
  NEXT_PASS (pass_ce3);
  ...
```
Hmm I'm not sure.

The dump names: cse (cse1), jump (jump1), cse2 (cse2), jump2 (jump2), sched (sched1), sched2 (sched2), lreg (local alloc), greg (global alloc), dbr (delayed branch), rtl, loop.

So the order is roughly: rtl → loop → cse1 → jump1 → cse2 → jump2 → sched1 → sched2 → lreg → greg → dbr.

Hmm, "jump1"/"jump2" — the `jump` pass (optimize_jumps) ran BEFORE sched1. So a goto would be removed by jump1/jump2 before scheduling. That matches my goto variant failing.

What creates a block boundary that survives jump2 but before sched1?

The `flow` pass (pass_flow) — the dump `cand.i.flow` exists. When does flow run? In GCC 2.7, `pass_flow` is in `pass_all_late_optimizations`? Hmm, but "flow" dump is present. GCC 2.7 has `pass_flow` (the CFG cleanup) which runs... Actually in GCC 2.7 the pass `flow` (pass_flow in flow.c) runs in `pass_all_late_optimizations`? Hmm, but the "jump" pass and "cse" run before sched.

Hmm, so if flow runs after sched, then a CFG branch created by the front end survives until sched1.

Let me check: GCC 2.7 c-passes.c `pass_all_optimizations`:
```
  NEXT_PASS (pass_local_optimization);   /* e.g. expand, jump, cse, sched... */
```
Ugh.

EMPIRICAL: my `switch (0) { case 0: ... break; }` variant gave score 2 with 200 ins — meaning the switch was fully optimized away (no jump table, no branch). And `if (t == t)` gave 2 with 200 ins. And `goto` gave 2.

So all these constructs were removed before scheduling.

What about a REAL branch that produces the same instructions? E.g. a conditional whose two arms are identical → GCC's cross-jumping merges them (jump2). Hmm, cross-jumping is in the `jump` pass which is before sched. So identical arms get merged.

What if the two arms are NOT identical but the branch is still removed? E.g. `if (cond) { A } else { A }` → merged by cross-jump.

Hmm.

**What about a `for` loop that runs exactly once?** `for (i = 0; i < 1; i++) { ... }` — loop optimization (loop.c) runs before sched (the `loop` dump exists before cse). It might unroll/remove. Actually loop.c's `loop_delete`/`loop_optimize` might not remove a 1-iteration loop with a known trip count (strength reduction happens but the loop stays). Then the loop creates blocks, and the loop's body is a separate block from the preheader → block boundary! But the loop would add a branch instruction (bnez) → extra instruction. Unless the loop is fully removed.

Hmm, but wait: `do { ... } while (0)` — GCC 2.7 has a special case in the front end? Let me check: my v05_dowhile gave 2 with 200 ins. So it was removed.

Hmm, what about `while (1) { ...; break; }`? That creates a loop with a break → probably a branch. Let me try anyway.

Actually, let's think about the DELAY SLOT angle instead: the load needs to be in the delay slot of the `sh`. GCC's `delay_slot_filling` pass (delayed.c) runs LATE (after greg). It fills delay slots by choosing instructions. But here the sh is not a branch — for non-branch insns, GCC's `mips_final_prescan_insn`/`mips_insert_nop`... Actually on MIPS, EVERY instruction has a delay slot, and for non-branches the delay slot must be filled with a nop or a movable instruction. GCC's delayed.c `fill_delay_slots` handles branches; for non-branches, the layout pass just emits the next instruction.

Hmm, so the sh at 3ad0 is followed by 3ad4 (the load) — that's just sequential layout, and the sh is in a different block than the join.

OK. Let me try a bunch of "block-creating" variants and check the instruction counts:
1. `while (1) { func(...); break; }`
2. `for (;;) { func(...); break; }`
3. `do { func(...); } while (0);` (done)
4. `if (1) { func(...); }` — front-end folds.
5. `if (p) { func(...); }` — real branch, but p is always non-null? GCC doesn't know → branch + 200+ ins.
6. `switch (t & 0) {...}`.
7. `goto` with a label placed so that the goto is not trivially removable — e.g., a label inside a nested block.
8. `t = load; if (t == 0x7FFFFFFF) { func(...); } else { func(...); }` — duplicate call → cross-jump merges → but the merge happens in jump2 (before sched) → same.

Hmm, what about #8 where the two arms differ slightly so cross-jumping doesn't merge, but... then we'd have 2 calls. No.

**New idea**: What if we make the CALL itself come from a place where the load is in the previous block by using the EXISTING branch? The `if ((func_80029178(0xB3) & 0xFF) != 0) {...}` block. The target's join at 3ad4.

What if we move the load+call INTO the if-body (the != 0 arm) and put a copy of the load+call in the ==0 arm? Then each arm has its own load+call. The join would be after. But the target's structure is: the ==0 path branches directly to the join at 3ad4 (the load+call). The !=0 path falls through the body and reaches 3ad4.

So the target's join block contains the load+call. In C:
```c
if (cond) {
   ...body...
} 
{
   t = load;
   call(t, ...);
}
```
That's exactly the current C. The join block is the `{...}` block.

So the join block = [load, copy-a0, li-a1, li-a2, call].

Hmm what if we make the *load* happen in the if-body's END and the call in the join? Then the load is in the if-body block, and the join has the call. But the ==0 path also needs the load → the load would be duplicated.

WAIT. Actually, what if the load is hoisted into a block that dominates BOTH paths? I.e., the load happens BEFORE the `if (cond)` branch! Then the load is in the block before the branch, and the join block has only the call.

But then the load would be scheduled much earlier in the machine code (before the branch at 39e0), not at 3ad4. Unless... hmm. The target has the load at 3ad4, which is AFTER the branch.

Hmm, so no.

OK OK. Let me reconsider the whole thing. Maybe the difference isn't a block boundary but something about the ASM making the load's pseudo different.

Let me dump the ORIGINAL (with asm) and compare the pre-sched RTL. That will tell me exactly what the asm changes.

Let me do that.
