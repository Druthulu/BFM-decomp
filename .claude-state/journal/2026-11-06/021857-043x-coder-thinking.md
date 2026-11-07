---
ts: 2026-11-06T09:18:57Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG25x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_8UfV7z4cvULlmCOurEDN
---
hdump.sh <includer TU> <header basename> <body.c> <outdir> <tag> — it splices the body in place of the header include. It expects a TU that has `#include "../shared/ov/<basename>"`. Includer: src/ov_MAIN_012/ov_MAIN_012_jr_801380E0.c.

Let me dump orig (with keepalives) and w1, and diff the .combine/.cse/.lreg dumps to find the pass. This will tell me the mechanism precisely and suggest a real-C move.

Outdir must be absolute under my shard dir. Let me do it.
