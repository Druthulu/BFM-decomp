---
ts: 2026-10-17T10:38:25.906Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: ae39e3e55ca2abfd6
model: claude-opus-5-5[1m]
effort: medium
turnId: 50f5af05-e353-44b9-ba7b-703e4f789154
---
Since scheduling runs backward from the end, insn 63 gets its priority boosted at T-2 in the free version because of how adjust_priority treats register deaths, but in m1 that boost doesn't apply since the diff now shows two sets instead of one.

I'm wondering if instead of reusing diff directly, I could structure the computation as `d = v; if (d < 0) d = -d;`, which would naturally produce two sets for d across control flow and make it global, matching the target's branch/move/negate pattern.

This matches the abssi2 pattern from mips.md: branching on sign, moving the value, then negating with subu (negu is just an alias for subu with a zero register), which aligns exactly with what the m2 assembly output shows.

Now I'm checking if an explicit if-statement style would change block boundaries during scheduling, since reorg would place the move into the delay slot while the if-branch could split into separate blocks that scheduling can't cross -- the key question is whether the e2 load happens before or after this branch structure in the m3 variant.
