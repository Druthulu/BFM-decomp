---
ts: 2026-11-06T05:28:53Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG21x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_0fpIqHRxYo49WGE1oRqy
---
I have a bug in variant 'hitfirst' and 'sw_expr' — but let me just run and score; compile errors will show.

Wait, 'rv_inv' replace logic is convoluted; let me just check the result compiles.

Also 'sw_expr' has `case 3: ... return (s32)func_80172710;` — that skips func_80178BF8, changing semantics. Let me fix: it should goto tail. Actually I wrote `return (s32)func_80172710;` — wrong semantics (the call would be skipped). The target calls func_80178BF8 for all non-return paths. Let me remove that variant or fix it. I'll fix it in a second pass; first run.

Actually, let me just run and see scores. Compile errors are fine (they're still "tries"? The brief says "scored tries" — a compile error isn't a score. Let me make sure candidates compile).

Let me run the generator and score all.
