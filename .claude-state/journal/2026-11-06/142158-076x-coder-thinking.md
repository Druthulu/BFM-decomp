---
ts: 2026-11-06T21:21:58Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW50x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_EIuV6O5EJgqbVNPpg2yc
---
As expected: they emit `sw s0,32(sp)` instead of `move v0,s0`. So the only way to get `move v0,s0` is a dead register set, which flow deletes.

Interesting: these variants show that if the value is *used* (stored), it's kept, but as a store, not a move. So the target's move is genuinely a dead value.

I'm done. Time 14:21. Need until ~14:28. Let me use the time to prepare the results row and check item 3's setup reading (but that's item 3). Hmm.

Let me just do more genuine item-2 work: verify the pinned orig dump to confirm the mechanism (that the pin gives $2). Let me dump orig (pinned) and inspect the lreg allocation for rv. This is useful evidence.

Build min_orig for item 2 with the orig body.
