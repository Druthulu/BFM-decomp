---
ts: 2026-10-17T09:07:14.817Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: ad689c37ea88bcff0
model: claude-opus-5-5[1m]
effort: medium
turnId: f24e09ce-98d5-45d3-8db8-69a0d3469b71
---
I'm considering whether the spill slot gets stored as a halfword but reloaded as a byte for the sb store, and wondering if that mismatch is what gcc is doing with the s32 variable.

Actually comparing more carefully, the reload mode matches in both cases—only the store mode differs, which suggests the pseudo itself may be HImode, meaning u2 could be a 16-bit variable rather than s32. But that would also affect the operand ordering of the addu computation for u, so I need to check whether the masked expression writes differently with u16 variables, and whether that matches the actual diff I'm seeing for h1 where u is u16 and v stays s32.
