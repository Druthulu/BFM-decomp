---
ts: 2026-10-17T17:09:06.071Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: acf1e900976d98019
model: claude-opus-5-5[1m]
effort: medium
turnId: 82d9c87a-028e-4c83-b14d-9d07f43471e2
---
I'm comparing the register allocation details between the two versions — in the original, register r74 stayed live across 8 instructions with priority 2500 and got allocated to a0 despite a being pinned, which seems odd since pinning a should make a0 unavailable while live. I'm checking the other version where r74's liveness is only 6 instructions to see if that explains the difference.

Now I'm trying to figure out why a got a1 instead of v1 or v0 in case k, even though a's priority (5000) and lower allocno number should theoretically win it v0 first under tie-break rules. This contradicts my working model of the allocation order, so I suspect something in `block_alloc`'s qty-checking logic — possibly related to how `find_free_reg` filters call-clobbered registers in its first pass — is blocking the allocation I'd expect.
