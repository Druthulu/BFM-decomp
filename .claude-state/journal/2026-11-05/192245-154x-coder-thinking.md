---
ts: 2026-11-06T02:22:45Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG18x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_kZSeMMt1ENhoqMxQdwSN
---
The barrier is `__asm__ __volatile__("" ::: "memory");` inside `case 0:`'s if, between the `if (unk98 == 0)` test and the stores. Note this is a *memory* clobber barrier, not a zero-byte plain barrier. We need a lever-free body scoring 0.

Let me get the target asm for this function and the nopin score. Extract the def: lines 3254-3300? The function ends at the closing brace. From the sed output: `void func_80183ACC(s32 a0)` at 3254, and the body ends around 3300. Let me find the exact end line.
