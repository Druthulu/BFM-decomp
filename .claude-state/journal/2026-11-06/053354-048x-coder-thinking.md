---
ts: 2026-11-06T12:33:54Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG31y
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_zO0kn0RQXZ7j84jK6fa9
---
Interesting: each arm ends `j 1e38` with the delay slot `li v0,N`. So the `j`'s delay slot holds the `li v0,N` (the ret value)! That's reorg stealing the li into the j's delay slot (since after the branch, v0 is live... hmm, it's the target's shape).

And then at 1b14: `li v0,41` — the next arm's comparison constant! So `li v0,N` (ret) is in the j delay slot AND the next arm starts with `li v0,41` (the comparison constant for unk70 == 0x29).

So the C is: `ret = 7; goto STORE;` — the `li v0,7` and `j` merged.

In my c2, `return 0` early returns produce what? Let me dump c2's asm and look.

But hold on, the biggest question: how to keep ret in v0 without the pin and without the 2 extra `li v0,0`.

Idea: What if the early returns are `return ret;` but ret is *not* live-in at entry because the C first assigns ret before those returns... 

Wait, actually, maybe I'm wrong about why ret got s0. Let me check c2's diff: with `return 0`, ret got v0. The score 55 includes 2 extra insns. So the remaining diffs (55) are mostly about other things. Hmm, 257 vs 261: mine is 4 insns short overall.

Wait, maybe the two `return 0`s are exactly 2 of the 4, and the other 2 missing are in the arms.

Let me diff c2 more comprehensively. Let me look at the diff from the start.
