---
ts: 2026-11-06T10:09:34Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG26x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_zjR2WNypkQsXFTu0kSgp
---
This is the case-0 loop (i0, c0). Note the counter `reg/v:HI 74` (HImode!) — c0 is `s16 c0`. Hmm, this is case 0: `c0 = 0; for (i0 = 0; i0 < 5; i0++) { if (...) c0++; }`. Here the increment is on reg 74 (c0), and i0... hmm.

Wait: `reg/v:HI 74` set to 0 then incremented — that's c0 (s16). And r76 set to 0 is i0? Let me look further for the loop compare.

Anyway, I need the case-1 loop. It's later. Let me find the next D_801AECD8 use (line 22243 or 22639). The case-1 loop uses `lw 0(a1)`, `lhu 2(v0)`, `bne v0,a2`, `li v1,1`.

Let me look at line 22639 area.
