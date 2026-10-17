---
ts: 2026-10-17T08:10:17.127Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: aee27218559a6cb07
model: claude-opus-5-5[1m]
effort: medium
turnId: 924c6b58-d828-4a45-885e-7f9083635c03
---
I'm noticing only one macro-carry row actually got carried, func_801811A8, where the line numbers matched between old and new. For func_80185AC0 the line numbers shifted slightly and the base appears to differ (local vs param a0), so the normalization step likely isn't resolving that mismatch, which explains why it wasn't carried while the other case was.
