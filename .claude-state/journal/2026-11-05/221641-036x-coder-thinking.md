---
ts: 2026-11-06T05:16:41Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG21x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_WR4U0sAwHjMWGRovN2Lt
---
Requires >200 lines. Let me pad the test file with a bunch of dummy definitions, or just use the real TU. Simpler: append ~200 lines of dummy functions. Actually easier: copy the real includer TU, but that's big. Let me just generate padding in the scratch t.c via a script.

Actually, let me instead test with the real TU using hdump: hdump already does the splice and compile. I can make two variants: orig (barrier) and nobar. Then compare `.frame` for func_80175820. Let me do nobar dump.

Actually, I already have the nobar candidate object and the orig object. The orig object showed `addiu sp,sp,-16` mid-function. Let me check the nobar .s frame by dumping nobar with hdump.

But the deeper question is: why vars=16 for the barrier body? Let me look at the RTL around the asm in the *function*. I can locate the asm by its source location: `("src/shared/../shared/ov/func_80175820.h")`. Let me grep the rtl for that.
