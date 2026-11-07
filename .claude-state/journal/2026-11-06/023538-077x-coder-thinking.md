---
ts: 2026-11-06T09:35:38Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG25x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_2PWTrIitmHZ7KLP7o5Uz
---
The lreg dumps are identical in insn numbering except insn 127 vs 125. The store we care about (392 = 0x188) — insn 59 is `lh` from 392 (the `*(s16*)(s0+0x188) < 0x80` load). Where's the store `*(u16*)(s0+0x188)=0`? Let me search for a set to (mem (plus ... 392)) with zero. Let me print more of the function region and find "const_int 392" occurrences.

Let me grep for "392" in the region lines 67365-67900 for both.
