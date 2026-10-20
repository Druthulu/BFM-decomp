---
ts: 2026-10-17T17:36:43.006Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: acf1e900976d98019
model: claude-opus-5-5[1m]
effort: medium
turnId: 82d9c87a-028e-4c83-b14d-9d07f43471e2
---
With 7 pins in a 133-instruction function and 9 callee-saved registers live, the global allocation priority is off by one spot according to the comment—this points to the greg-pri-refs logic. I want to check the free0 diff and compare the allocation order against the target.
