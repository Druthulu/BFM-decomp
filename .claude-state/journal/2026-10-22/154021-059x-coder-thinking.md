---
ts: 2026-10-22T21:40:21Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG18
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_yl3RTyMFEcxCcWy7cdRV
---
MATCH. Item 2 done in ~15 min (15:35 → 15:50). 

Now set win.c = b1, write notes, results row, moves line. Clean up.

The mechanism: init-at-decl `s16 sp10[2] = {0, -0x40};` — the two dead stores are emitted as an initializer at the declaration point (before the load in the entry block), giving `sw $ra` the successor it needs, so sched2 keeps it in the prologue.

Note the comment block in the body references the clobber — since win.c is a scratch artifact, I should keep it tidy but it doesn't matter much. Actually the win.c is the deliverable body for a future src edit; the stale comment about the clobber should be adjusted. Let me trim that comment to describe the new mechanism (it's my artifact under .run; fine either way). I'll update it briefly.

Let me finalize item 2.
