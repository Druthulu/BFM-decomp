---
ts: 2026-10-17T17:07:40.719Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: acf1e900976d98019
model: claude-opus-5-5[1m]
effort: medium
turnId: 82d9c87a-028e-4c83-b14d-9d07f43471e2
---
I'm questioning whether do-while(0) actually generates a loop in gcc 2.7 -- my notes suggest it emits loop notes, but the jump pass might strip out empty loops anyway, so I want to check the allocation logic for k.
