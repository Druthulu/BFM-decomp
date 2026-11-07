---
ts: 2026-11-06T12:31:28Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG31
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_QzrcwUWBfqAOogWl4ymo
---
Let me now generate a batch of variants on v0.c (lever-free). I'll aim for 25.

Variants (indent 44 spaces for the FT3 block, 48 for FT4):

A) fade/cc block: swap the order of `cc = fade << 8; cc = fade | cc; cc = cc | (fade << 16);` — permutations (6). But changing the cc chain changes the result? cc = fade<<8; cc = fade|cc → (fade<<8)|fade; cc = cc | (fade<<16). Reordering those three statements changes semantics. Only safe orders: the chain must build cc. Alternatives: `cc = (fade << 16) | (fade << 8) | fade;` in one statement (a real-C move, same value) — that changes the insn order/combine.

B) `gopz = za;` placement relative to `fade = ...` (2 variants ×2 regions).

C) rgbc/uvc0/uvp1/uv2 store order (a few).

D) `otp = ...` placement.

E) `pkt += 0x20;` placement.

F) The `if (fade < 0) fade = 0;` placement.

Let me do:
1. cc one-liner in FT3
2. cc one-liner in FT4
3. both
4. gopz after the fade clamp (FT3)
5. gopz after the cc chain (FT3)
6. rgbc after uvc0/uvp1/uv2 (FT3)
7. otp before the stores (FT3)
8. pkt += 0x20 before otp (FT3)
same set for FT4 (indent 48) → 8 more
17-20: box fill swaps (4)
21-24: my/mny order (4)
25: v0 + d202-style barrier drop is already v0 (lever-free includes the barrier). Right, v0 has all levers removed.

Hmm, the lever-free base is v0 = 71. Any variant on v0.

Let me write the generator with 25 variants. To keep it manageable, I'll parametrize on the two regions (FT3 indent 44, FT4 indent 48) — but the text differs slightly (uv2/uv3, uvw). Let me handle FT3 only for most, plus a few FT4.

Let me write it.
