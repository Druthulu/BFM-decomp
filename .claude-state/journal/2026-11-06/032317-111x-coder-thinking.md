---
ts: 2026-11-06T10:23:17Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG27x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_vxL4IncnZIhxbbjLBIcE
---
h1/h2 = score 2, same as f2 (the sign-ext temp issue). So the caller-saved allocation is fine with the smaller do-while, and the remaining diff is the sign-ext temp.

So: with the keepalive + do-while, the only residual is the div sign-ext temp (v1 vs in-place s0).

Now, f3 (two-statement shift) fixed the sign-ext but shifted the caller-saved regs. Maybe with the smaller do-while (h1) + two-statement shift, the caller-saved stays and the sign-ext is in-place. Let me test h1 + `div = div << 16; div = div >> 16;`.

Let me create i1 = h1 with the shift form.
