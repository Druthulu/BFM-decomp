---
ts: 2026-10-17T17:30:09.134Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: ac3c2f25cd86a3f15
model: claude-opus-5-5[1m]
effort: medium
turnId: fc7a601a-bbe9-478a-af6a-6ab88c3f06f1
---
With scores verifying at zero and the match rate landing exactly at 40%, that crosses the threshold for Haiku-first routing, though I'm noting Haiku's successful cracks mostly depend on the fake do-while(0) wrap pattern in three of five cases.

For the single-kind G shards, I'm splitting work: G01 and G02 are already on Opus, so Haiku takes G03-G21 plus G24-G25, but I need to pull out any oversized items (over 100 lines) or items with unknown size into new Opus shards for safety, leaving only the smaller confirmed items for Haiku. Any Haiku walls or partial failures will get retried later as Opus shards, and Haiku runs count against the concurrency cap just like any other slot — logging this as usage record WH1.
