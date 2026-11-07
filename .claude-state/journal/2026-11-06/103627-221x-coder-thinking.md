---
ts: 2026-11-06T17:36:27Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO05x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_4Ti7STeeOob39iMrNiEW
---
set_preference(dest=75, src) — src is the SET_SRC of the insn setting 75. The two setters: `(ashift (reg 77) 16)` and `(ashift (reg 147) 16)`. `GET_RTX_FORMAT(ashift)[0]` = 'e' → src = XEXP(src,0) = reg 77 / 147, copy=0. Then if src_regno is a hard reg (reg_renumber[77] >= 0, i.e., 77 was allocated by local-alloc!), set_preference records 77's hard reg as a preference for 75.

So if local-alloc assigned 77 (angle) to v1, then 75 prefers v1! In the final asm, the first sll is `sll v1,a0,16` — 75 in v1 and 77 in a0? Hmm, but if 77 were v1, the sll would be `sll v1,v1,16`. Unless 77's qty includes several pseudos.

Wait, the preference is from 77's *reg_renumber* at global time. If 77 was allocated v1 by local-alloc... but then the sll source would be v1. The asm shows the source a0. Contradiction — unless the source is a different pseudo (e.g., the angle's copy).

Hmm, maybe the insn is `(set (reg 75) (reg 77))`? No.

Let me look at the *sched1* dump (nd.i.sched) — the last RTL before local-alloc — for the sh16 insns to see the actual src regs.
