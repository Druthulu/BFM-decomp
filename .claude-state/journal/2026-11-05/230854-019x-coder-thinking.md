---
ts: 2026-11-06T06:08:54Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG22x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_VgkU2wm03xME3IxFN4NC
---
priority = floor_log2(nrefs) * nrefs / live_length * 10000 * size.

nrefs is reg_n_refs which is loop-weighted? Let's check flow.c where reg_n_refs is incremented.
