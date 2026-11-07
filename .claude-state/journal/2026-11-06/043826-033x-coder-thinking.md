---
ts: 2026-11-06T11:38:26Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG30
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_OECeYB9TsexJI6fU2wyB
---
The do-while broke the register allocation: because `w_` (a2) got spilled differently, mFF pin $7 now... wait t0->a1: the pin $7 is a3. The mask mFF (0xFF000000) is in a3 in target. In mine v1, a3 was spilled to 16(sp)?? Line 22: `sw a3,16(sp)` vs target `sw a2,16(sp)`. So mine saved a3 (the pin!) — pin mFF in $7 got spilled. Hmm.

Actually the do-while introduced loop notes which changed register allocation (loops add ref counts → x,y got s1/s2 but s8 etc.). Messy.

Maybe better to not use do-while, and instead find a different real-C move.

Let me think again about what splits EBBs without a loop. A conditional that's constant-folded later? e.g. `if (c1 != c1)`? Fake. A `goto` and label? That also creates CFG but jump opt removes.

Alternatively, maybe restructure so that sched1's priorities change naturally. In mine v0, the problem: within one EBB, sched1 orders: [sh vx],[lw w_],[move a0],[addu x],[sh vy],[sh vy],[lw h_],[li 8],[addu y],[sb p3],[lw tag],[li 56],[sb p7],...

Target order is source order. sched1's priority function: gcc 2.7.2 sched.c `priority()` computes for each insn the max over successors of (1 + priority(succ))? Let me check the actual source.

In gcc-2.7.2/sched.c, there is `priority (insn)` = number of insns in the longest path starting from insn (in the dependency DAG). Insns with larger priority are scheduled first. So the adds (which feed several stores) have priority 2-3, while `sb p[3]` has priority 1 (nothing depends on it) and the byte stores priority 1. So the adds go first. In the target, the barrier split makes them separate blocks.

Hmm, but wait: target's second EBB order starts with lw t1(w_), lw a2(tag), addu x... Within that EBB sched1 could reorder too, but they happen to be near source order.

So we need a real way to split. Options:
1. do-while — tried, wrecks regalloc.
2. A function call — not allowed to add calls (would change semantics).
3. Make the byte stores have dependents so they get high priority? E.g. write them through a temp? Hmm.

What about reordering the source so the scheduler's chosen order matches? sched1's priority ordering depends only on the dependency graph, not source order. Unless priorities tie: for equal priority, the list scheduler picks... In gcc's sched.c, the ready list is sorted by priority; ties broken by ??? It's a linked list insertion, first-come. So source order matters for ties.

Alternatively change the dependency graph: make the adds depend on the stores. In real C: e.g. compute `x += w_` where w_ is re-read from the stack? No.

Hmm wait — what if we make the tag2 load occur BEFORE the adds in source (it does: 2466 tag2 = *p; then x += w_). But the tag load must wait for the byte stores (aliasing). In target, order is stores, tag load, x add. In mine, adds were scheduled before the byte stores. Because adds have higher priority than stores.

What if the stores to p[4..6] etc. are made to have dependents by combining them into wider stores? Target has separate sb's, so no.

Alternative: make the vx/vy stores depend on something that also depends on the adds? No.

Real C move possibility: change `vx = x`/`vy = y` to copies after the adds? That changes values.

Hmm, what about splitting via a struct assignment that cse1 splits? Actually what about making the first block a separate `if` statement with a condition known true? That'd be a fake-ish construct.

Wait — maybe the barrier can be replaced by a *store* to a variable that's later used, creating an ordering edge. But identity launders don't count.

Let me reconsider: perhaps there's a different natural C formulation where the early stores are emitted with higher priority. For example, if p is a `u8*` and the c stores are written via a struct pointer or as an array, priorities change? Not priority, but the graph.

Hmm, actually what about the adds' priority: x += w_ (addu s1,s1,t1) feeds sh 16(v0), sh 32(v0) → priority 2. y += h_ feeds 2 stores → 2. vx stores: vx = x is a move feeding 2 stores → move has priority 2, stores 1.

In target's first EBB, move a0,s1 (vx) is before the c stores. In mine, move a0,s1 appears at 384c after sh s1,8. Hmm.

What if we could raise the priority of the byte stores by giving them an extra use — e.g., reuse a value after: `p[3] = 8; ... ; q = p[3];`? That's a real read if used later. Not in target.

OK, different tack: the source with barrier produced target; maybe the *real* original source used a different structure that naturally orders. The barrier is marked "NEEDED DIFFERS (P36 rung B tus9)" meaning previous searches couldn't crack it. It's a singleton shard, likely designed to test hard walls. We have a 20-30 min budget per item; 4 items. So don't over-invest.

Let me try a few cheap moves:
(a) v2: v0 but with the tag2 load moved earlier in source (before the c stores?) No — must stay after p[3] store due to aliasing. Could put it right after the first tag store (before p += 8)? It's a different packet.

(b) v2: use do-while only around the first group (p+=8 .. vx/vy stores) but as a plain block `{ ... }`? A plain compound statement doesn't create RTL boundaries.

(c) Instead of do-while, use `if (1) { ... }`? Also fake.

Hmm, the do-while changed regalloc because of loop notes. What if I put the do-while only around the second group (tag2=0xE1000200; ot store) and around... The v1 problem seems to be the first do-while (it made a loop with the whole first block, changing live ranges/ref counts). Let me try v2 = v0 + only the second do-while (small). And v3 = v0 + first do-while only.

Actually wait. Look at target more carefully: is the first group really one EBB with the second? The barrier at 2455 is after `p[7]=0x38` and before `vy=y`. But target shows vy=y (move v1,s2 at 3858) after p[7] store (3854) — consistent with source order; the barrier there separates `p[3]=8, vx=x, p[7]=0x38` from `vy=y, c stores, vx/vy stores`. Yet target order has the first group then second group in source order, which is what you'd get anyway.

The big separation is the barrier at 2465 (before tag2 load). That one keeps the adds and the tag load after the vx/vy stores.

In v0 the adds went before. Let's test whether a do-while just around [tag2 load .. pmask store] fixes it without the regalloc damage. And the third barrier (before tag2=0xE1000200) as a second do-while.

Let me also consider: maybe use a do-while around the FIRST group only (which changes s1/s2?). Try variants.

Let me write v2 (only middle group wrapped) and v3 (only last group wrapped), and score both.

Actually, note v1's regalloc damage: it spilled a3 (mFF pin) and used t0/t1. That's because of the loop? Hmm, do-while(0) at the top of a function... loop.c processes the loop; a one-trip loop; REG_N_REFS += loop_depth. The first block's variables x,y,c1.. get loop_depth 1, changing priorities. That's what changed.

So avoid wrapping large blocks with many live vars. The middle group has x,y,w_,h_,tag2,otp,pmask,p. Also many. Hmm.

Alternatively use a construct that splits cse1's EBB but not a loop. What splits cse1 EBB? cse1 uses `NOTE_INSN_BASIC_BLOCK`? In gcc 2.7.2, cse.c: EBB = extended basic blocks, ended by jumps and labels. A do-while(0) creates a label + branch, which splits. But other constructs also create labels/branches: a `goto` + label, an `if` with constant condition, a switch, a `&&`/`||` short circuit (creates branches!). The brief mentions `&&`/`||` folds as a real C move.

Interesting: C0414 (dead-reset cse-breaker). Also maybe an `if` that the jump pass folds.

Hmm, but a branch also splits sched1's blocks? sched1 in 2.7.2 operates on "extended basic blocks" (`sched_analyze` per EBB?) Let me check sched.c: `schedule_insns` iterates over basic blocks; for each, if it's a "block with no jumps in" it does EBB scheduling (`sched_analyze` from the head of the EBB?). Let me read sched.c briefly to understand what splits sched1's region and how priority works.
