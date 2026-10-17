---
ts: 2026-10-17T16:39:44.226Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a26a2e7a9927b54ee
model: claude-opus-5-5[1m]
effort: medium
turnId: 253b27e4-07a4-41f7-b188-1141b6e4bbf5
---
I'm comparing instruction priorities at T-2 between the original and c2 schedules, noticing that register 72's death and the boost flag on the priority value seem tied to a register-pressure heuristic rather than a true difference in behavior.

I recall gcc 2.7.2's sched.c has an adjust_priority function with a `birthing_insn_p` check that boosts priority when an insn's single death corresponds to a register whose lifetime is just starting, based on reg_n_sets counts for the destination register—so I'm trying to pin down whether the barrier clobber of a0 affects reg_n_sets[4] and thus flips the birthing classification between the two versions.

The function checks whether the destination register is live before the insn; if live, it falls back to checking whether that register has exactly one set. So in backward scheduling, since a0 is live after call 80 uses it, I need to check reg_n_sets[4] in c2's case to see whether a0 is set only once there.

I'm trying to figure out why 78 wouldn't get boosted — maybe there's a specific "birth boost" mechanism tied to how many times the hard register is set that differs between o and c2.

I should test some real C variations: reordering statements, moving the store after, using a temp variable for the function argument, or changing multiplication order, to see which arrangement produces the right register-set count.

I don't see any other spot in target where a0 gets set besides the move from s0, and a clobber wouldn't generate an actual instruction, so I can't add a real a0 set without changing the code's behavior. I'm running low on leads here, so I'll tentatively mark this as sched1-birth-boost and try a few more C variants with different argument types before giving up on this path.

Looking at ready-list priorities, insn 78 gets boosted near the call but still loses against insn 75's higher priority at the critical cycle, and since the boost amount is fixed I don't see a way to flip that ordering unless a0's liveness changed, which it can't. I'll record this as my best attempt scoring 10 and move on to try a couple more variants quickly.
