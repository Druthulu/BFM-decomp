---
ts: 2026-10-17T11:11:40.349Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a5faba3cdb29155cb
model: claude-opus-5-5[1m]
effort: medium
turnId: e4e5bc1c-68a3-4a95-bce5-27c78dfaef1c
---
I'm still puzzling over why the tree-free version collapses, and decide to just experiment with test dumps instead of reading further. I sketch out a first test case involving pointer comparisons and conditional stores to see how it behaves.

The cost model holds up: PLUS addresses like `pe[1]` get folded by `fold_rtx`, but plain REG addresses (`*pe`) don't. I'll now test the REG-address forms.
