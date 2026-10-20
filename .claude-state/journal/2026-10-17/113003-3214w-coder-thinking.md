---
ts: 2026-10-17T17:30:03.264Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: acf1e900976d98019
model: claude-opus-5-5[1m]
effort: medium
turnId: 82d9c87a-028e-4c83-b14d-9d07f43471e2
---
With registers fixed, the store ordering is now off since it comes after unk16, and I need c7840 to live longer at lreg but still store early — but sched2 won't reorder stores due to aliasing concerns. Moving the init earlier in m3 didn't help since sched1 places constant sets independently of that, so I need to check how sched1 actually orders the constant sets in k1 to figure out what controls c7840's birth position.

Maybe if c7840's p0 store is placed earlier among the other stores, its birth stays tied to its first use since backward scheduling in sched1 seems to position constant sets just before their first reference — so reordering unk12 before unkE and moving c7840's store ahead of the c64 store might shift things, though that could affect the final instruction order depending on how sched1 and the target output align.

Store order itself seems fixed since sched2 won't reorder potentially-aliasing stores, so the only freedom is where the c7840 constant set lands — interesting that in the target, all constant sets are hoisted to the top, likely because sched2 can freely move li instructions once hard registers are assigned. I want to check the sched1 dump to see where c7840's set actually falls in that order.
