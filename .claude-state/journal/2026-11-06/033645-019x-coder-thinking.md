---
ts: 2026-11-06T10:36:45Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG28x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_4Aj6g7BIBSvVefWLrUh6
---
nobar: pins kept, barrier removed → 63 ins, score 18 (register swaps only). So the barrier removal is fine count-wise. win0 = 66 (the extra s0/s1 copy).

So the barrier can be dropped cleanly (it only preserved ordering, which survives). Let me see nobar's diff.
