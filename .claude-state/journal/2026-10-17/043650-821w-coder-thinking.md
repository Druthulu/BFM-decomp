---
ts: 2026-10-17T10:36:50.240Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: ae39e3e55ca2abfd6
model: claude-opus-5-5[1m]
effort: medium
turnId: 50f5af05-e353-44b9-ba7b-703e4f789154
---
The register reordering doesn't look promising as an explanation. I need to be more systematic: in the m1 tail, everything matches except the e2/d registers swap and a block-2 load discrepancy involving hoisting — I should trace what register r95 actually corresponds to in m1.

Checking its conflicts, it seems the D load value from block 2 is supposed to target v1, but its lifetime overlaps with v0/v1 usage differently depending on scheduling order. The key difference seems to be that in the free.c version, diff gets removed and reassigned in the tail, which changes diff's conflict set and allocation priority — if diff gets allocated before r95 and claims a0, then r95 can't take a0 either since it also conflicts with v0/v1, which would explain why free.c's allocation diverges from mine.

I think the clearest path forward is to directly inspect the RTL for instructions referencing registers 95, 77, and 101 in the greg dump for block 2, to see exactly how their live ranges and conflicts are structured.
