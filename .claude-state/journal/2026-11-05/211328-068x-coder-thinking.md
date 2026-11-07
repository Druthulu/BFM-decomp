---
ts: 2026-11-06T04:13:28Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG20
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_qqAnrYujz9p6KcGxBRL9
---
Mine: pointer a2, i counter a1, t in a0, p in a0 (after), var in v0. Target: pointer a1, i counter v1, t in a0, p in v1, var v0.

So mine assigned the pointer to a2, target a1. Why? The pins reserve a0 and v0. Then global_alloc's order: the pointer pseudo vs the loop counter. Target: pointer a1 (first free), counter v1 (after a0? no, a0 is pinned to t). Hmm.

The target's structure: the loop body is different. Target's loop uses a0 as the base pointer to D_801924DC and v1 as i; mine uses v1 as the base and a1 as i. The target also loads D_801C7E38[i] AFTER the loop (at de4) using v0 = i*4, while mine loads it before computing var (at df8). And the target's `p` is in v1, mine in a0.

The core difference likely: in the target, the loop exit path (`de0: sll v0,v1,2`) and the code after the break merge, and `p = D_801C7E38[i]` happens after `t = D_801C7E78`? Target order: lw p (de4), lw t (df4), li v0,1, sh. Mine: lw t (de4), compute var, sll i, lw p, li v1,1, sh. So mine moved the p load later and the var computation earlier — that's the scheduling/ordering difference the barrier prevented.

The barrier is between `*(u16 *)(p + 0x10A) = 1;` and `var = 60 - t * 15;`. In source: p = ..., t = ..., store, BARRIER, var = 60 - t*15. So the barrier keeps `var = 60 - t*15` AFTER the store. Without it, sched moved the var computation before the p load/store (mine computes var at de8-df4 before loading p at e04). The barrier forced the store before the var computation.

Target order: p load (de4), t load (df4), li v0,1, sh (dfc), then sll/subu/li/subu for var (e00-e10). So the store comes before the var computation.

So again the barrier prevents reordering. We need a real dependency or ordering.

Idea: make `var = 60 - t * 15;` depend on the store. Hmm. Or use the same variable/temp to create a WAR: `p` is used by the store; the var computation uses `t`. Independent.

What if we reuse `t`? `var = 60 - t * 15;` — if the store `*(u16*)(p+0x10A) = 1;` used a temp that is then reused... The store's address uses p. If we assign `p` again after the store? Dead.

The dead-reset trick: after the store, do a dead reset of `p` or of the loaded value, but that doesn't order the var computation.

Actually, what we need is the var computation to be *after* the store in the scheduled output. The scheduler moved the independent var computation earlier. To prevent, make `t` (used by var) be loaded after the store, or make var depend on the store.

In target, the `lw a0,D_801C7E78` (t) is at df4, AFTER the p load (de4) and just before the store. In mine, t is loaded at de4 (before the p load). So the ORDER of the p and t loads flipped, and the var computation followed.

So the issue is sched1 ordering of the two independent loads: target loads p first then t; mine loads t first then p. And target computes var after the store; mine before.

Hmm, the barrier's role: memory barrier prevents the t load (a memory op) from moving across the barrier? The barrier is after the store. The t load is BEFORE the barrier in source (`t = D_801C7E78;` then store then barrier then var). So the t load is before the barrier. But the var computation (not memory) is after the barrier in source; sched moved it up. A memory barrier doesn't stop arithmetic from moving! So how did the barrier keep var after the store? Because the barrier is an ASM insn, which is a scheduling barrier (ASM_OPERANDS with volatile is a full scheduling barrier). So it stops all reordering across it, including the var arithmetic.

So we need the var computation to depend on the store or on something that keeps it after. Real C: make `var` computation depend on the stored value? The store writes 1 to p+0x10A. What if we write `*(u16 *)(p + 0x10A) = 1;` and then read it back? Extra load.

Alternative: reorder the C so the var computation naturally comes after. It already is after in source. The scheduler moves it. To stop sched1, use a do-while(0) EBB split around the var computation (C0535). Let's try: wrap `var = 60 - t * 15;` in do-while(0). Hmm, a loop around it might prevent the hoist.

Or use the dead-reset/2nd-set trick to give the scheduler a dependency.

Let me first understand why the pointer register differs (a2 vs a1). That's regalloc, maybe secondary to scheduling. The primary score components: 34 with many diffs. Let me try simple variants:

v1: do-while(0) around `var = 60 - t * 15;`.
v2: do-while(0) around the store+var.
v3: reorder: move `var = 60 - t*15` before the store? Target has store before var, so no.

Let me try v1 first. Actually, wait: the barrier also sits between the store and var; if we wrap var in do-while, sched1 might still hoist? The do-while creates a loop; sched1 won't move an insn out of/into the loop body across the loop boundary? The loop body executes once but sched1 doesn't know; it treats the loop boundary as a barrier (there's a branch). So the var computation would stay in the loop body after the store. But the loop adds a nop/branch? If sched can't... Actually a do-while(0) compiles to no branch (jump.c removes the always-false back edge?) — GCC's `do{}while(0)` is a loop that executes once; jump.c removes the loop? In practice, C0535 says it "splits cse1 EBB" — the loop notes remain for sched1, and the branch may be removed but the note acts as a barrier. In item 1, do-while added no extra insns. Let's test.

Let me create v1.
