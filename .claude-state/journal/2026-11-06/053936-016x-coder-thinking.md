---
ts: 2026-11-06T12:39:36Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO01
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_09tdfyss2P0nhUuZpW8z
---
So mine has `lui a2,0xff00` (mFF) at 376, target at 379. 3 instructions later. What are those 3 instructions? Likely `li a0/a1` and the ott address computation.

Let me get the actual instruction listing around 370-385 from the object. Use --keep to get the candidate object and dump it.

Let me run with --keep.
