---
ts: 2026-10-17T10:43:11.635Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: abb6ffee7b1153d5a
model: claude-opus-5-5[1m]
effort: medium
turnId: bd46829b-96df-48df-a479-540852ff007c
---
I'm tracing the instruction ordering in the scheduled block, noting that j lands late after the constant loads while I want it grouped earlier with k, t3v, pb, m24, and mhi. I'm digging into how the backward scheduler's rank_for_schedule tie-breaking decides ordering among independent, ready instructions.

I'm also reasoning about CSE: if k = m is computed before t3v = m*4 in the source, CSE collapses t3v's reference onto k's class head, so to keep t3v separate I need t3v's value computed via a different expression (like i*4) that CSE won't link to k.

Something later than flow must be swapping k back to v1 since there's no regmove pass in this version — I'll set that mystery aside rather than chase it further. Shifting to priority: j had 11 refs born before t3v and k, so maybe it wins the scoring race depending on how its depth-2 references from the loop preheader get counted.

Looking at output ordering, it seems to follow source order — t3v and k emitted together since they come from the same source statement, with j's loop-init appearing after the mhi assignment. So to get the right ordering I need source order j, k, t3v, with t3v not depending on k and j scoring higher priority than k.

Counting j's references: the init, the zero-test, the increment use, and the final set gives 11 total, but if k is born right after t3v while j's live range starts earlier, k's ratio can still beat j's. I need to try restructuring the loop (maybe a `while` form instead of the initial test) to push j's reference count up relative to k's.

I should check whether t3v can avoid being canonicalized into k — that depends on how cse.c's register-class head selection works in make_regs_eqv, so I want to look at that function around lines 826-862.

I see the output needs source order j, k, t3v preserved, with t3v not rewritten to k—but cse's rewrite makes k the head of m's class. I'll check the head-choice rule next.
