---
ts: 2026-10-17T05:53:38.143Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a0517ed1d1bb7f9bc
model: claude-opus-5-5[1m]
effort: medium
turnId: f9047d91-6ccc-4e9c-9be7-6616c974f0fb
---
Using --all-defs with one body risks replacing the 4-copy SC07 variant with mismatched type names from the 123-variant, which could break things even if it compiles with both types present. I'm wondering if restricting to one def per variant group via --tu would be safer, though that limits scope to a single def at a time.

For the shared header callers, I need to hand-edit the declaration since the existing void-parameter signature won't match; with K&R-style empty parens this might still be tolerated, but I should check how rung D handles the interim declaration state across all 136 includers.

The real concern though is whether calling with an actual argument changes the generated assembly -- gcc might emit an extra move instruction to place param_1 into a0 before the jal, which would alter bytes that currently match since the delay slot is a nop. That's the key risk I need to verify before committing to this rewrite approach.
