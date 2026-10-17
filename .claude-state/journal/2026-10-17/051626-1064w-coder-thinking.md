---
ts: 2026-10-17T11:16:26.050Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: ae39e3e55ca2abfd6
model: claude-opus-5-5[1m]
effort: medium
turnId: e556b3f3-3497-4364-81b2-e77d256de80a
---
This confirms my fear: the final load merges with the earlier reference since the unchanging memory entry survives the intervening stores, so CSE treats them as equal regardless of the const change. I need to use a different expression form for the final load so it can't be matched to the same cached value.

I'm trying address arithmetic variants that fold to the same offset at expand time despite looking different in source, so cse would still merge them anyway — waiting to see the g2 result before deciding which approach actually avoids the merge.
