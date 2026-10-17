---
ts: 2026-10-16T16:48:27.951Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a6262df0e8a0d472a
model: claude-opus-5-5[1m]
effort: medium
turnId: 7850ba3c-c3b4-45a3-a86f-0ae36df32364
---
All 241 failures turn out to be SHARED names bound to the same object, which disproves my earlier hypothesis — the real cause is restruct batches binding multiple names to one object, like a local variable cast to two different Unkstruct types in the same function. I'm now checking whether this sharing already existed at T3, since twins_listed showed 738 there, meaning these objects might not have been shared yet at that point.

The dry run reveals all 241 failing rows are SHARED (multiple names bound to one object) rather than UNBOUND, ruling out the TNC-evidence hypothesis. I'll examine a source example to understand why these names share an object.
