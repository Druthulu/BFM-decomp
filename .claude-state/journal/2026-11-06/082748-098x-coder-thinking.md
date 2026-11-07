---
ts: 2026-11-06T15:27:48Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO03
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_3FdZxXs1vwbYkkIMI3s7
---
Good. Now item 3: func_8017FBEC in ov_SC02_037_jr_8017AE2C.c, launder, 101 lines. Body 102 lines (6542-6643). This is the shared 237-ins function cloned in items 3,4,5.

FRESH: orig.c extracted at 07:59 from current src. Let me diff it against the current src (nothing should have changed since no banking in this task, but check).

The body has two launders? Let me look: line 6615 has a pin, line 6621 a pin, line 6630 a launder (`vol`). Only one launder (line 6630).

The function is large (237 ins). Let me first score the launder-free version.

Let me extract the body and check.

Actually, orig.c was extracted. Let me verify the three clones are identical bodies (they have different function names).

Let me start with item 3 (func_8017FBEC). Score nolaunder.
