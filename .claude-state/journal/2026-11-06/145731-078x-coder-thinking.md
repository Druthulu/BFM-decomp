---
ts: 2026-11-06T21:57:31Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM3
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_pLocycLmtRlbwlE6eJ3H
---
Interesting! t09 = 25 (710 ins!), t11 = 25, t13 = 25 — much better than 135. Which are these? Let me map:
- i=1..7: dst types s32,u32,int,long,s16,u16,u8 → t01..t07
- i=8..14: tmp types s32,u32,int,long,s16,u16,u8 → t08..t14

So t09 = tmp as u32? Let me recompute: i=1 dst s32, 2 dst u32, 3 dst int, 4 dst long, 5 dst s16, 6 dst u16, 7 dst u8, 8 tmp s32, 9 tmp u32, 10 tmp int, 11 tmp long, 12 tmp s16, 13 tmp u16, 14 tmp u8.

So tmp as u32 (t09) → 25, 710 ins. tmp as long (t11) → 25. tmp as u16 (t13) → 25. tmp as s16 (t12) → 117 (712 ins), tmp as u8 (t14) → 137.

Wait t10 (tmp int) = 122, t12 (s16) = 117. But u32/long/u16 = 25 with 710 ins! Interesting. On this compiler, `int` is 32-bit; u32 might be `unsigned int`? long might be 64-bit? Hmm, `long` in gcc 2.7.2 mips is 32-bit. `u16` is unsigned short.

Why would u32/u16 give 710 ins and 25? Probably they change the code slightly (one extra insn) but improve allocation. Score 25 is much better.

Let me inspect t09's diff. Maybe it's close to 0 with a small residual.

Note: `tmp` as u32 means `tmp >> 16` is a logical shift (srl) instead of arithmetic (sra) — that changes an instruction! In the target, `sra v0,v0,0x10` (arithmetic). So u32 would give srl → mismatch but only 1 ins... yet 710 ins and score 25. Hmm, 25 mismatches.

Wait, t09 score 25 with 710 ins. Let me look at its diff.
