---
ts: 2026-10-17T10:41:13.025Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: ae39e3e55ca2abfd6
model: claude-opus-5-5[1m]
effort: medium
turnId: 50f5af05-e353-44b9-ba7b-703e4f789154
---
I'm tracing whether the parameter pseudo register in m8 is being treated as local, trying to figure out if gcc 2.7's local-alloc logic considers its lifetime confined to the entry block.

For global candidates sharing with e2, I need a register live across multiple blocks that gets assigned a0 elsewhere without breaking things — trying 'a' (r76) via m7, noting it already has two sets so a third from the m11 combination might be fine priority-wise.
