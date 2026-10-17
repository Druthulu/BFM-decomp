---
ts: 2026-10-17T11:23:38.333Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a5faba3cdb29155cb
model: claude-opus-5-5[1m]
effort: medium
turnId: e4e5bc1c-68a3-4a95-bce5-27c78dfaef1c
---
I'm noticing pf gets set to &D_8011511E in certain switch cases, acting as a persistent base pointer across calls since it's stored in a callee-saved register. I need to trace how pf is dereferenced inside body_tree to understand what offsets it actually reads.
