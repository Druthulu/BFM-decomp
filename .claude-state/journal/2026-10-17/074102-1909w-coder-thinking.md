---
ts: 2026-10-17T13:41:02.608Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a715c83225823a44a
model: claude-opus-5-5[1m]
effort: medium
turnId: cb00494e-7b3a-4f28-b3fa-24b3d50bb0ef
---
I'm puzzled by the instruction ordering — insn 95 appears after insn 112 in the sequence, which seems odd since local-alloc shouldn't reorder instructions like that. I'm trying to recall whether this is actually happening during scheduling rather than register allocation in this gcc version.

Right, GCC 2.7's pipeline runs sched1 before register allocation (cse, loop, cse2, flow, combine, sched1, lreg, greg, sched2), so sched1 is the one responsible for reordering here. Looking at the target's layout, the pv load appears in the same relative position as mine, so the live ranges shouldn't conflict with the lhu temporaries — yet target gets a0 while mine gets v1, which suggests v0 is tied up by another live value (likely the address register) and the allocation priority differs because the target reuses a2 for i4 in a subsequent addu, changing which registers are free when pv gets allocated.

I'm now tracing register assignment order: mine assigns pv→v1, i4→a0, m24→a2, mFF→a3, while target assigns pv→a0, i4→a2, m24→a3, mFF→t0. That shift implies something, probably a1, stays pinned as a live hard register in both cases, but in target v1 must conflict with pv in a way it doesn't in mine, forcing pv down to a0 instead.

I'm checking where v1's lifetime overlaps pv's load in the target schedule — pv's load seems to get placed earlier relative to the lhu chain than in mine, causing the overlap. This points to sched1 needing to hoist the pv load instruction earlier, driven by critical-path priority in that scheduling pass.

Trying to influence this through dependency restructuring is tricky since gcc 2.7's scheduler walks backward from the end picking ready insns by priority. I'm considering experimenting with different ways of writing the expression — with and without explicitly referencing pv in the mask-and-combine operation — to see which ordering emerges.

I think the better approach is to isolate the if-branch first by keeping the else-branch's levers as a baseline, since mixing both at once makes diagnosing which variant works much harder.

The register assignment in the if-branch hinges on how sched1 orders the `pv` load against the `lhu` chain before local-alloc, and the pins lock that in. I'll now vary each branch's source spelling independently while keeping the other branch's levers fixed for isolation.
