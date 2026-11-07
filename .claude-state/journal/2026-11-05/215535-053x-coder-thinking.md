---
ts: 2026-11-06T04:55:35Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG20x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_sW0R2oYIiZe91yxDSi6k
---
Let me use hdump.sh to dump the passes for the a1 body (barrier-free) and see where the reload disappears. Need absolute outdir under my shard dir. hdump.sh <includer TU> <header basename> <body.c> <outdir> <tag>. But note the header basename: hdump replaces `#include "../shared/ov/<basename>"`. Our includer has `#include "../shared/ov/func_8013A2BC.h"`, so basename = func_8013A2BC.h. fn=${2%.h} = func_8013A2BC.

Outdir must be absolute under my shard. Let me run for a1 (no barrier) and orig (barrier) and compare .cse1/.cse2/.greg etc.

Disk: dumps go under my item dir and delete after reading.
