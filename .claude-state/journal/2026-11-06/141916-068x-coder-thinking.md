---
ts: 2026-11-06T21:19:16Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW50x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_Y3zrLRtBtR0IFXrq51fO
---
Just metadata (kinds, 2?, 28). No crack.

Time is passing slowly. Let me check the clock. I'll do a genuinely useful dump analysis for item 2's win.c to confirm 42 ins and the exact diff, and then write notes.

Actually, let me try ONE more creative idea that might actually work: what if the value is kept by making `rv` the *source* of a `REG_UNUSED`-style use in a `parallel`? No C.

Or: what if the function's last statement is a *store* whose address computation uses rv AND the store is the same as `*a0 = sp20`? E.g., `*(s32 *)((s32)rv) = sp20;` where rv = (s32)a0. Then rv is used as the address. But target's store base is s0 (a0). If rv is in v0, the base would be v0. No.

What if `rv` is used as the value stored, and the store is the last: `*a0 = rv = (s32)a0;`? stores a0, not sp20.

I'm confident. Let me wait out the clock with real work: write the notes.md for item 2 now (it's needed anyway), and re-verify the win.c score. Then at ~14:28 record the wall.

Let me write notes.md for item 2.
