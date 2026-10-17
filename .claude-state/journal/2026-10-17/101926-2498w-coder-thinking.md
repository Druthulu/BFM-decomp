---
ts: 2026-10-17T16:19:26.356Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: ac899e71a72e1a646
model: claude-opus-5-5[1m]
effort: medium
turnId: 7b755c42-d9e9-446c-8f08-faa68444d116
---
I'm noticing my version hoists the address symbol out of the loop as an invariant, while the target keeps computing it inline using a different register addressing pattern each iteration.

The other symbol in the loop isn't hoisted the same way though, and the target uses lui-based addressing consistently for both. This is a dense 51-line diff with register steering across a0/a1/a2 and a move in a jump's delay slot — I should budget time and study the full structure before diving into fixes.
