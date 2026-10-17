---
ts: 2026-10-17T11:59:19.708Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a9b75b3e3c01d6fa8
model: claude-opus-5-5[1m]
effort: medium
turnId: 9b80ef94-0ae1-44c6-acfd-ddecb9279a50
---
I'm tracing the `move a0,s0` discrepancy — it seems tied to where `sc` gets assigned from `slot` since that value crosses calls while live in s0. If `sc` were given a0 via register preference instead, the move would happen right at the `sc = slot` assignment point at the top of the block rather than where it currently appears.

I'm wondering whether cse eliminates `sc` by replacing its uses with `slot` directly, causing it to be deleted as dead, while in the target version `sc` stays alive because it's never fully substituted. I'm also considering whether sched1 could be pulling the `move a0,s0` earlier in the block simply because there's no dependency blocking it from being scheduled before the call.

Another angle: maybe the store into `field_4` is being filled into the jal delay slot by the reorg pass, which would force a particular instruction ordering, and the call argument itself might come from a recomputed expression like `i + 0x2F` that cse maps onto the same register as `slot` but handles differently depending on how args get expanded into pseudos before the call.

I'm running low on attempts for this instruction class — I'll try a few more variants: dropping the `slot` variable entirely so `i + 0x2F` is recomputed inline at each call site, keeping the store but changing when the call happens, or trying `slot` mapped to a different register like s16.
