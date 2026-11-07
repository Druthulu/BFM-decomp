---
ts: 2026-11-06T17:29:35Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO05x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_7B9hTwexnGKMv7b0nNCd
---
KEY: "75 conflicts: 72 73 75 2 29" and "75 preferences: 3" → pseudo 75 (sh16) has a *preference* for register 3 (v1)!

The preference comes from a copy: `(set (reg 75) (reg 77))`? or from the sll: `(set 75 (ashift 77 16))` — the ashift's output prefers the same reg as its input (reg 77)? reg 77 is the angle/p[0x79] value. In the target, sh16=v0 while the input (77) is... 

"75 preferences: 3" means qty_phys_sugg includes reg 3 (v1) — a copy/arith preference. That's why 75 gets v1! The ashift `sll 75, 77, 16` prefers to write the same register as 77 (the input), i.e., 77 is in v1? Actually the preference comes from combine_regs: for `(set (reg 75) (ashift (reg 77) 16))`, the input 77 dies and the output 75 prefers 77's register (v1).

So sh16 gets v1 because the angle value (77) is in v1. In the target (pinned), sh16 is forced to v0.

To get sh16=v0 lever-free: make the input (angle / p[0x79]) be in v0? Then the preference would be v0. The angle comes from `angle = func_80029D3C(cmp79)` → the call result in v0! If angle stays in v0, then `sll v0,v0,16` — exactly the target's line 163: `sll v0,a0,0x10`? Hmm, target line 163 is `sll v0,a0,0x10` — a0 = angle? angle would be in a0 in the target (the call result moved to a0).

Let me look at the target's asm around the sh16 block to understand the registers.
