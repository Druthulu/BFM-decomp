---
ts: 2026-11-06T20:20:03Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW49
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_wfvUeT2O0FUpDYhyLVbK
---
Item 3 has row kinds: barrier, launder. There are also pins ($4 q/q2) — other-kind levers, may stay.

- barrier: `__asm__("");` before `v ^= 1;`
- launder: `__asm__ __volatile__("" : "=r"(r) : "0"(r));` in both arms.

Remove both barriers/launders (3 asm lines) and score baseline.

Note: `r = 0xFFF80000;` and the launder `"=r"(r) : "0"(r)` re-ties r to its input reg (zero-byte 2nd set). The launder here makes r's constant not rematerialized at the call: "stops the constant from being rematerialised down at the call".

Also FRESH: orig.c vs src def — the src has extra lines after (extern func_80029178 etc.) because my sed range 1415,1485 included trailing lines. The diff shows orig.c lacks lines 68-71 (blank + extern). That's just the tail of the sed range, not a body change. Let me confirm the function ends at line 1481 in src. The diff says orig.c lines 1-67 match and src has 4 extra lines after. So the function body matches; those extra lines are the next declaration. Fine — no regeneration needed. Actually the orig.c is 67 lines and src def is the same 67 lines. Good.

Let me make the baseline: delete the three asm lines.

Careful: deleting `__asm__("");` (barrier) and the two launder lines. The pins `register s32 q __asm__("$4") = s0;` stay.

Let me create nolau.c and score.
