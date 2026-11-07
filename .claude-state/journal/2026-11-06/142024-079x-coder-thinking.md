---
ts: 2026-11-06T21:20:24Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW50
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_uxABQhu0BVmZwIIheDV9
---
Item 3: kinds = launder,pin. There are:
- 1 pin: `register s32 base __asm__("$18");` (base pinned to $18 = s2).
- 3 launders: `ap` launder (twice) and `tp` launder.

Need all gone, score 0.

The launders are tied-operand asm (2nd set of ap/tp). The pin is $18.

This is harder. Let me first check FRESH (diff orig vs src), then score the lever-free body (remove all asm) and see the residual.

Let me check src.
