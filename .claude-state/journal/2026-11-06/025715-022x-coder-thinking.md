---
ts: 2026-11-06T09:57:15Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG26x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_n6fTP6JE89OWqxTV77u9
---
Interesting: "T7.c1: rung D ... pin becomes a parameter" — so there's a known technique: the pin becomes a parameter. E.g., `func(s32 a0, s32 a1, s32 rv)`? That changes the signature too.

Hmm, but "pin becomes a parameter" would be a signature change of the *definition*; callers would pass the pinned register. Not applicable here.

Let me look at how other similar void-with-$2-pin functions got cracked lever-free in other shards. Search moves.md for "$2" and "v0".
