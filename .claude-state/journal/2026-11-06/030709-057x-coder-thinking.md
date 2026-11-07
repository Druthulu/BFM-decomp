---
ts: 2026-11-06T10:07:09Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG26x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_afDeFHDtD7ruUtGcUY71
---
I can use cc1_dumps_tu.sh on a spliced TU (the --try scratch copy). But the scratch is deleted unless --keep. Let me use --keep to get the TU copy path (the .run/P36/engine/score/.../p3/ directory contains the spliced TU? Let me check). The --keep printed "candidate object .../p3/cand.o". Let me list that dir.

Actually, an easier approach: dump the pass with `-dg` (global alloc) to see priorities. Let me check what the p3 dir contains.

But wait, disk is capped (~4 GB free). Dumps are large; I must delete them after reading.

Let me first check the p3 dir.
