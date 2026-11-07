---
ts: 2026-11-06T11:39:06Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG29
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_aJ4pr0t5Bh0ey85fwlPS
---
Let me use hdump.sh with the first includer to compare sched1 dumps of orig vs w1. But hdump.sh expects `<includer TU> <header basename> <body.c> <outdir> <tag>`. The header basename is func_8012A1BC.h. The include line in the TU is `#include "../shared/ov/func_8012A1BC.h"`. Let me run it for w1.

This will dump passes into the outdir. Let me do it and grep the sched1 dump.
