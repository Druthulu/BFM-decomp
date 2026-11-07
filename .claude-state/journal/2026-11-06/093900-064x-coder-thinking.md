---
ts: 2026-11-06T16:39:00Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO05x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_j3sckTNO0N7SODJHFgTR
---
Order: flow (2971/2983) → combine (3004) → sched1 (3033) → local_alloc (3049) → global_alloc (3077).

Wait, but cse1 runs earlier (~2860) and cse2? Let's see: cse1 at 2860ish, then jump_opt, then flow?, combine, sched1, local_alloc. Hmm, and cse2 where? The -dt cse2 dump exists; probably after combine? Let me not worry.

So combine runs BEFORE local_alloc. So `arg0 | 0` would be folded to a copy before local_alloc → same as plain copy. Damn.

What survives combine as a non-copy but produces no extra instruction? `+ zr` where zr is a register variable: combine can't fold it because $0 is a register (though $0 is constant zero, combine might know? It produced `addu $5,$4,$0` and maspsx turned it into `move`? The build object has `move a1,a0` — maspsx converts addu with $0 to move. So the instruction stream has an extra addu→move, i.e., the move is part of the target anyway.)

So the target itself has `move a1,a0`, meaning the original source had a real copy-ish op. Our lever-free body needs to produce `move a1,a0` with self=a1.

Since the pin is forbidden, we need another way to keep self distinct. What about `self = arg0 + 0;`? combine folds const 0 addition into a copy? It would become `(set 73 72)` → same problem.

Hmm. But wait: what exactly goes wrong with the plain copy? Global-alloc assigns param 72→a1 and self 73→a0. Then the then block uses... let me understand which pseudo each arm uses. In win.c's cse/rtl: does the then block use 72 or 73? Let me look at the rtl for win.c.
