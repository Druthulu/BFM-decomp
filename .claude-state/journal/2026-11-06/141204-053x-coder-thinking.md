---
ts: 2026-11-06T21:12:04Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW50
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_AVVT7sOFFSuIenKN7R3g
---
There's a `-greg` switch. Let me compile with -greg to get the allocno trace. The cc1_dumps_tu.sh doesn't pass -greg. I can run cc1 manually with -greg. Let me create the TU (already have cand.i) and run cc1 with -greg.

Let me run cc1 on cand.i with -greg and capture stderr/stdout. Actually -greg prints to a file (the dump file). Let me just run cc1 with the same flags plus -greg and see.

I'll do it under my item dir.

But wait — the candidate cand.i is win.c (barrier-less, launder-less), which has the REG swap. Good, that's the case to study.

Let me run cc1 with -greg.
