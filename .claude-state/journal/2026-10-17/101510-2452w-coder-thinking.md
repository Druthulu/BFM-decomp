---
ts: 2026-10-17T16:15:10.386Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: abb4a08fa100d7feb
model: claude-opus-5-5[1m]
effort: medium
turnId: dd20a3af-7bad-4cc5-bdfe-eb40b857c079
---
I'm checking whether moving the declaration actually changed the pseudo ordering, since that affects scheduling tie-breaks—f5/f6 show no change. Looking at the schedule dump, without the register pin the ang pseudo needs a copy into a0 for the call, but with the pin it's already bound directly to $4.

I'm wondering if sched1's rank_for_schedule tie-breaking is giving a priority boost to insns that "birth" a register, similar to the earlier birth-boost issue I tagged against local-alloc, but that boost shouldn't apply to hard registers like a0. Since the bx load is winning the tie anyway, I want to pull up the actual .sched dump for that block to confirm what's driving the order.
