---
ts: 2026-10-17T08:06:15.862Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: aee27218559a6cb07
model: claude-opus-5-5[1m]
turnId: 924c6b58-d828-4a45-885e-7f9083635c03
---
Approach: first enumerate the 10 failing sites with a scratch script that reuses type_census's own backing logic, so I see whether keys drifted (`local:aN` to `param:aN`) or lines shifted. Then let restruct's rung-S writer append fresh rows scoped to the affected segment, instead of hand-editing the ledger, which keeps the census honest. If the tools can't back a site, I'll report it rather than patch.
