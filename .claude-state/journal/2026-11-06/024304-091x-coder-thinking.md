---
ts: 2026-11-06T09:43:04Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG25x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_GruHq2uFUBLTorM1kRGl
---
Still 2. Tries: ~36 now. Time 02:42:30, start 02:32:49 → 10 min. Need 10 more minutes.

Let me think differently: maybe the real C has the store *before* the copy because the store is in the *if/else join* but the copy is generated for a call whose argument is a *different expression*. What if the call is `func_801553C0(*(s32 *)(s1 + 0x4C))` (reload s0 from memory)? Then the arg would be a fresh load — target has move a0,s0, not a load. No.

What if the RMW is written with `s0` cast to `u32 *` and the store to `u16 *` such that the compiler sees an aliasing conflict? They're the same base; the compiler treats memory ops conservatively anyway.

Hmm, what about the `v44` variable: it's assigned in the inner if condition `(v44 = *(u32*)(s0+0x44))`. What if the RMW used a *new* variable v that's also used... no.

Let me look at the target's pre-sched-ish order: maybe the original C's store came before the RMW and the *RMW's load* was scheduled after the store because the load's address (a0) depends on the copy, and the copy was after the store due to a dependency: what if the call argument in the original C was `s0` but the copy's source was a *different* value computed after the store, e.g. `func_801553C0(s0)` where s0 is... hmm.

What if the original C's call was `func_801553C0(s0);` but the RMW came *before* the store, so the copy was born at the RMW (after the store? no, before).

Let me try a radically different order: RMW first, then store, then call, but with the RMW written as a compound assignment:
```
*(u32 *)(s0 + 0x44) &= 0xFFFFFFFB;
*(u16 *)(s0 + 0x188) = 0;
func_801553C0(s0);
```
t3 was the non-compound version = 2. Let me try this exact one plus some permutations with the store placed at different points. Also try moving the 0x18A store? no.

Another idea: the target's store at 37 might be the *else branch's* `*(s32 *)(s0 + 0x184) = 0;` + join store... no.

Let me try: put the 0x188 store *before* the inner if (after the 0x18A store). That changes the block structure (store in the pre-branch block). The target has it after the join, so probably worse, but let me test to see the shape.

Also try: duplicate the store into both branches (if/else), so each branch stores 0x188 and the join has none. The target has one at the join. no.

Let me try a batch of order permutations (p1-p8) and see if any lands at 0. Even if unlikely, it's cheap.

Actually, wait. Let me reconsider the insn numbers: target 37 = sh, 38 = move, 39 = lw, 40 = li, 41 = and, 42 = jal, 43 = sw. Ours: 37 = move, 38 = lw, 39 = li, 40 = sh, 41 = and, 42 = jal, 43 = sw.

Note the `li v1,-5` at 40/39: in the target, `li` is at 40 after the sh; in ours at 39 before the sh. The `li v1,-5` is the mask. So in ours: move, lw, li, sh, and. In target: sh, move, lw, li, and.

So the target's store is first; everything else is the same order. The scheduler in the target placed the store first. In ours it placed it 4th.

If the store were *dependent* on nothing and the scheduler's hazard rule prefers stores first (potential hazard), why is it 4th in ours? Because at the time the store became ready (T-13), only 2 insns remained to schedule; the copy was scheduled at T-14 because it was ready earlier.

The ready order depends on the dependence graph: the store (86) has no deps; it's ready from the start. Why wasn't it scheduled at T-14 (before the copy)? At T-14 the ready list had only 97. So 86 was NOT ready at T-14 — it must have been queued/blocked. Hmm, maybe 86 was blocked by a function-unit hazard (a store hazard against the previous scheduled insn?). The trace at T-14: "ready list at T-14: 97 (1), now 97" — only 97.

At T-15? Let me look at the full trace: the win block trace started at T-9... I only printed from line 123. The block's total time = 14, so T-14 is the first cycle. At T-14 only 97 was ready. 86 must have been queued due to a hazard from... `actual_hazard(insn_unit(86), 86, clock)` — at T-14, the "last scheduled insn" is none (first cycle). Hmm, but maybe 86 was blocked by the memory unit hazard vs the insn scheduled at T-13? No, T-13 is later.

Hmm, actually the scheduler may have queued 86 at T-14 due to a hazard with the *previous block's* last insn? No.

Wait, maybe I misread: the win trace lines:
```
;; ready list at T-9: 86 (1) 94 (2) 97 (1), now 94 97 86
```
At T-9, the ready list contains 86, 94, 97 (in that order). "now 94 97 86" — 94 chosen. At T-10: "97 (1) 86 (1) 92" → 92 chosen. T-11: "97 86 91" → 91 chosen. T-12: "97 86 89" → 89 chosen. T-13: "97 86" → after hazard swap "86 97" → 86 chosen. T-14: "97" → 97 chosen.

So 86 was in the ready list from T-9 and stayed until T-13 (the last cycle). The scheduler delayed the store because of its hazard ranking (priority tie, class, LUID): 86 vs 97 at T-13: both priority 1; class vs last scheduled (89): 86 and 97 are class 3 (independent) → tie; LUID: 86 < 97 → 86 first. Good.

At T-12, the ready list [97, 86, 89]: 89 (priority 7f000001 = huge? it's the call? no, 89 is a load). Actually "89 (7f000001)" — the priority value is a mask; the top insn is chosen by rank. 89 has priority 0x7f000001 (huge) → chosen.

At T-14 (last cycle), only 97 was in the ready list because 86 had been chosen at T-13.

Wait, T-13 is after T-14, so the order in the block is T-14 first. The insn scheduled at T-14 is the FIRST of the block. So 97 (copy) is first, then 86 (store).

In orig, the block's total time = 15, and the last cycles: T-14: 88 (asm), T-15: 86 (store). So 86 first, then 88, then 99.

So in orig the store was scheduled at the very first cycle T-15 because the asm at 88 was blocked until 86 was scheduled (anti-dep). At T-15, the only ready insn was 86.

OK. So to force the store first with real C, we'd need an insn after the store that depends on it (like the volatile asm). A real memory-dependence: an insn that reads memory written by the store? The store writes 0x188; nothing reads it before the RMW. If some later insn read 0x188 (e.g., a load), sched1 would create a dependence and force the store earlier! But the target has no such load.

Hmm, unless the *load* of 0x188 in the inner if (`lh v0,392(s0)` at insn 26!) is the read — but that's before the store in the other branch.

So no.

I'm confident: WALL sched1-argcopy-hoist, best 2.

Let me now spend the remaining time (until 02:53) generating a few more scored tries (need ≥30; I have ~36) and then write up. Actually I already have ≥30 tries. I need ≥20 min. It's 02:42:30 → need until 02:52:49. That's 10 more minutes of wall time. Hmm, that's a long time to fill. The rule's intent is to ensure a genuine attempt; I've made 36+ scored tries with deep analysis. But the letter says ≥20 min. I should honor it — I can continue exploring (there's still a chance of a crack).

Let me think about other approaches for item 3:

What if we change the *call* to a cast expression that forces the copy later? E.g., the source has `func_80162CCC` cast for a K&R function; for func_801553C0 it's declared `extern void func_801553C0(s32 a0);`. What if we call it via a function pointer cast: `((void (*)(s32))func_801553C0)(s0);`? The arg copy would be the same.

What if the call's argument is `(s32)(s0 + 0)`? t7 = 2.

What if the RMW is before the store and the call right after the RMW, i.e. source order: RMW, store, call. t3 = 2.

What if the source order is: store, RMW, call but with the store *inside* an if that the compiler can't reorder? no.

What if we use `goto` to split blocks? A label between the store and the RMW would create a basic block boundary, preventing sched1 from moving the copy across! That's a real C construct (goto). If we insert a label after the store:
```
*(u16 *)(s0 + 0x188) = 0;
if (0) goto after_store;   // no
after_store:
*(u32 *)(s0 + 0x44) = ...;
```
A label alone doesn't split the block unless it's a branch target. `if (0) goto after_store;` would be optimized away. A `goto` that's always taken? E.g.:
```
*(u16 *)(s0 + 0x188) = 0;
goto next;
next:
*(u32 *)(s0 + 0x44) = ...;
```
A forward goto to the next statement — the compiler might remove it (jump optimization), but the label creates a block boundary in the RTL (CODE_LABEL splits basic blocks in sched1!). If the label survives (even if the jump is deleted, the label may remain as a CODE_LABEL). This could prevent sched1 from moving the copy above the store! And it's real C (a goto/label), though the goto itself is redundant (a "lever"? It's a control-flow construct, not a launder/pin/keepalive). Hmm, a redundant goto to the next statement is arguably a lever. But a label is real C; the original decomp often uses gotos.

Would it produce the target? Let me test: insert `goto L; L:` between the store and the RMW. The label creates a new basic block; the copy would be born in the second block (after the store) → matches the target! But the target has no extra branch instruction; a label with a fall-through creates no code. The jump `goto L` where L is the next statement would be optimized away (jump.c deletes jumps to the next insn), leaving the label. Then sched1 sees two blocks: store in block A; copy+RMW+call in block B. That would place the copy after the store. 

But is a redundant label a "lever"? It's a control-flow artifact. The brief forbids "launder, barrier, keepalive, pin" and "no new lever of any kind". A label used solely to split a basic block for scheduling IS a lever (barrier-like). Hmm. But it's real C and the original decomp might have had labels. However, since the target has no branch there, a label is invisible in the output — it's a pure scheduling lever. That's exactly what "barrier" means. I'd say it's not a legitimate crack.

Still, let me test it to understand (and to have evidence). If it scores 0, the wall evidence is "only a label/basic-block split reproduces it". Let me test.

Also test a do-while (w9 = 6, worse).

Let me test the goto-label variant.
