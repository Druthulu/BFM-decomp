---
ts: 2026-11-06T12:53:42Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG31y
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_lV4EXIqvv3bwkARCRzoe
---
h2 didn't get written (identical). All variants stay at 18. The differences are stable.

Let me get the actual candidate asm to compare in detail. Use hdump.sh with the includer 0 TU, inlining the body.

`.run/P40/T10/hdump.sh <includer TU> <header basename> <body.c> <outdir> <tag>` — it replaces `#include "../shared/ov/<header basename>"` in the TU with the body.

Note: hdump.sh needs an absolute outdir under my shard dir.

Let me run it for c1.
