---
ts: 2026-11-06T06:37:54Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG23
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_HSmSOoWxPYCPMyl7s1VE
---
Items 4 and 5 (func_80191C50 and func_801919A0) have IDENTICAL lever sets (same lines) — they're twins (different overlays, same body). That's a big hint: if one cracks, the other will with the same move.

Items 3 (func_8019059C) has 3 pins ($16, $3, $2) and 8 launders.

Let me start with the twins (items 4,5): 2 pins ($3 dst, $2 tmp) and 8 launders (mp, mm, m18).

Plan: 
1. Score the "pins removed only" and "launder removed only" variants to find a PARTIAL.
2. Try the known launder crack (do-while(0) or a real 2nd set).

The launder here is `__asm__ __volatile__("" : "=r"(mp) : "0"(mp));` — a tied output/input on mp, same as item 1's otz but *volatile*. These are 8 of them.

In item 1, the do-while(0) didn't work for the copy. But here the launders are on `mp`/`mm`/`m18` variables in a different context.

Let me look at the body around one of them. Let me read the function (308 lines — that's fine to read, under 20k? 308 lines × ~60 chars = ~18k, ok but let me read in ranges).

Let me read func_801919A0's orig.c in chunks.
