---
ts: 2026-11-06T15:28:36Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO05
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_fPD8MiSXlwEUQ7bWqVvJ
---
There's a wealth of moves. Now let me look at the item dirs. The five items:

1. func_8018FCE8__ov_SC06_032_jr_8018FCE8 — src/ov_SC06_032/ov_SC06_032_jr_8018FCE8.c — launder — 200
2. func_8018AD9C__ov_SC06_033_jr_80186574 — src/ov_SC06_033/ov_SC06_033_jr_80186574.c — launder — 146
3. func_8018D98C__ov_SC06_033_jr_8018D98C — src/ov_SC06_033/ov_SC06_033_jr_8018D98C.c — launder — 327
4. func_8017DC80__ov_SC07_002_jr_8017C8D0 — src/ov_SC07_002/ov_SC07_002_jr_8017C8D0.c — launder — 232
5. func_801821C8__ov_SC04_005_jr_8017BEBC — src/ov_SC04_005/ov_SC04_005_jr_8017BEBC.c — pin — 0

Interesting — item 5's line count says 0? Probably "lines" column meaning line count of body. Anyway.

Let me look at the item directories (which exist per the ls at top): func_8017DC80__ov_SC07_002_jr_8017C8D0 etc.

Let me check the contents of each item dir and the src functions. Let me first list the item dirs.
