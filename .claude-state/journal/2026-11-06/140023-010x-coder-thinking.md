---
ts: 2026-11-06T21:00:23Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW49x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_fFwhhY5BzzPxRp0sdZR6
---
Good — sc.sh gives one line per candidate. Let me write several candidate bodies.

Let me think about what levers could flip the v0/v1 assignment.

In the last block, target x->v0, y->v1; mine x->v1, y->v0. Notice this is the opposite of the first blocks (mine t->v1). So it's not a global preference; it's per-block priority. In block 1, the target's pseudo (sub result) has higher priority than the load. In mine the load has higher priority than the sub. In the last block, mine gives v0 to y (the second-born), target gives it to x (first-born).

Interesting: in mine, the *later-born* pseudo gets v0 in the last block (y is second load) and the *earlier* pseudo (load) gets v0 in block 1. Contradictory... unless priority is by refs.

Hmm, maybe it's about live length. In the last block, x and y are both born early and die at their stores; y dies later (its store is in the delay slot, after the jal). So y has a longer live range -> higher priority -> v0. In target, x got v0 despite shorter life... because the pin forced x? No wait, in target the pin was on x ($2), so x got v0 by force, and y took v1. Right! The target's last block allocation is entirely pin-driven. And the first blocks: t was pinned to $2, so t got v0. So the target tells us nothing about natural allocation; the pin produced it.

So the question: can real C make GCC pick v0 in all these places? The natural pick is v1 for t (block1) and v0 for y (last block). We need to flip both.

Since local-alloc prefers longer-lived/higher-ref pseudos for the first register, and the register list order determines v0 vs v1... If we could make t's pseudo the highest priority in its block, it'd get v0. Currently the load gets v0 first. Why? Because the load is allocated first? Hmm.

Wait, maybe I have the preference order backwards: maybe lower priority gets the first register because local-alloc allocates in *reverse* priority? Let me actually read local-alloc.c block_alloc.

Let me grep the reference source.
