---
ts: 2026-10-17T10:37:55.357Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a55474736c80a3baf
model: claude-opus-5-5[1m]
effort: medium
turnId: e20d419a-4489-4243-b756-85abe7c2d13c
---
I notice insn 6, the move with bits=a1, seems to have been eliminated by combine, which merges it into the bb assignment. That makes me wonder whether reg_n_sets gets recomputed afterward, since combine deleting that instruction could affect how scheduling analysis treats the register.

Tracing the actual sched1 order against the target, I'm trying to figure out why the c-chain (84/86) ends up above the x1 computation (64/65) instead of between the or (82) and the store (91). Working backward from the ready queue at each step, it seems the or instruction gets launched to max priority before the c-chain becomes ready, so to match the target order the c-chain would need higher priority than the or — I'm checking what priority mechanism could cause that.

I realize there's a conflict: making c single-set to birth it would undo the earlier deliberate choice to make c multi-set so its defs don't launch, which was needed to get v1 to hold its value instead.

I see that insn 6 was deleted by combine, leaving reg 73 single-set like the `w = c0` case, and the c chain (84/86) already outranks the `or` (82) by LUID but only surfaces because `c` is multi-set — if it were single-set it'd launch to max priority, giving the backward pass the target order 82 84 86 91. I'll try making `c` multi-set on purpose, as the earlier agent did, to control the register choice risk.
