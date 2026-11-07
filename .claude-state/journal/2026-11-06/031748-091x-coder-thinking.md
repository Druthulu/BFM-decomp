---
ts: 2026-11-06T10:17:48Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG28
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_Pm2z5qsFFYw7H2NgeRPC
---
d1: pointer is s3 (not fixed), and 1 insn short. So d1 didn't fix the pointer; the r2 s16 alone changed things differently.

d7/d8 have 188 insns and 15 diffs. The remaining diffs in d7 are mostly the v0/v1 swap in the block plus the andi from u16 y, plus a store reorder.

Let me try: d7 with y as s32 (d1-like) but r2 u16. d2 = r2 u16 only → 32. d7 = r2 u16 + y u16 → 15. So the y u16 helped. But it adds the andi.

What if y as s16? c31 was y s16 + r2 s16 → 21 (189 ins). d5 = y s16 + h s16 = 58.

Hmm, what about y as s32 but with a cast at use? The andi in d7 comes from `y` being u16 and used in `y - (rand() & ...)` where y needs widening (andi 0xffff). Target has no andi. So u16 y isn't semantically matching.

Let me try y as u32 (no truncation, different class): d13 = r2 u16 + y u32. And d14 = r2 s16 + y u32. Also d15 = r2 u16 + y s32 (that's d2=32).

Also maybe the andi comes from something else. Let me just try a few.

Time is ~03:32, 19 min. Let me do one more batch of ~8, then record WALL with best 15.
