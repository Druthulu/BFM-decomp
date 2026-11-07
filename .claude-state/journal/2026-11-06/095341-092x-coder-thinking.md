---
ts: 2026-11-06T16:53:41Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW48
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_0zutFBGvtow6LpSB9pJF
---
Item 2 MATCH. Time check and record. Let me count tries for item 2: win (no asm) 1, x1 2, y1 3, y2 4 (y2 compile error doesn't count). Actually the first y2 was a compile error — not a scored try. Tries = 4.

Let me record results.tsv, moves.md, notes.md. Then item 3.

Evidence for item 2 (≤140 chars): "cse: name m and n=m+0x30 per call; dead-reset `m=0; n=0;` after each invalidates the constant class (C0414); each site re-materialises lui/addiu".

Let me count: about 140. Fine.

Also, the dead-reset `m = 0; n = 0;` — is that a "dead store kept only to steer a pass" which the catalog refuses? The brief's MOVES+ explicitly endorses C0414 (dead-reset cse-breaker), so it's allowed. I'll note it in the log.

Now, before that: the FRESH check for item 2 was done (orig == src). Good.

Let me append the results row.
