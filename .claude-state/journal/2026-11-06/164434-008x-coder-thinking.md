---
ts: 2026-11-06T23:44:34Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG23x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_qjAQGRBeKjepIWlFKDGJ
---
Now let me copy the current def to orig.c and check for pin/launder. Two levers here: `register s32 mode __asm__("$19")` — pin; and `__asm__("" : "=r"(q) : "0"(q))` — launder.

The launder makes `q` a new reg (breaks cse equivalency with &D_800C7C60). The pin keeps mode in $19 (s3).

Wait, mode in $19 = $19 is s3. Hmm, in MIPS o32: $16-$23 = s0-s7. $19 = s3.

Let's first copy orig.c. Let me check the copy for the header items too.

Let me start with the resident item. Write orig.c.

Actually before that, let me read the headers.
