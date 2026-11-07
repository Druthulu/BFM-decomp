---
ts: 2026-11-06T13:29:18Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO02
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_JKRpGouuRw4pvbPfX4bs
---
The source order is aa (115), nn (116), barrier (117), chain (118-121), d[2] (122), call (123).

But the RTL has the chain insns numbered 293-305 and the nn set at 310. So gcc emitted the `nn = (s32)buf` set AFTER the chain?! That's odd... unless the insn numbers in the dump are the *scheduled* order's insn UIDs, which are assigned at expansion. Hmm.

Wait, maybe insn 288 is `nn` and 310 is something else. Let me check insn 288 and 293 in the listing.
