---
ts: 2026-11-06T16:30:59Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW48
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_Mawp4YjxtIIEbzr146xw
---
The scratch .c from --keep is the TU copy? It's 16 lines in .s — probably only the body, not the TU. Let me check that file's head. Actually the --keep scratch TU is "ov_SC01_084_jr_8017F690.c" which should be a spliced copy. But compile produced 16 lines. Maybe cpp failed. Check cpp.err.
