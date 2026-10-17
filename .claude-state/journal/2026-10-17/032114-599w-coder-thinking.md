---
ts: 2026-10-17T09:21:14.445Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: ab0fc0b10970aee54
model: claude-opus-5-5[1m]
effort: medium
turnId: d5f3c548-1279-4293-8954-e6ee5462dd24
---
All 136 SHB defs appear dead with no uses, which is odd given the census notes three live SHB definitions were judged dead by the oracle, which "refused" removal. That's strange since deleting a truly dead macro shouldn't change output bytes unless it's actually referenced indirectly through a header inclusion.

Looking closer, ENGINE_SHB shows up 4 times in shared headers—maybe through token pasting. I want to examine the 3 volatile TUs alongside those 4 ENGINE_SHB mentions.
