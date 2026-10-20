---
ts: 2026-10-17T18:25:45.994Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a11ed4236c71ce25b
model: claude-opus-5-5[1m]
effort: medium
turnId: 638017c5-5103-4585-b12e-50498d92977e
---
I'm realizing jump threading doesn't happen when ok reuses the same pseudo as the original comparison, whereas threading occurs only when the compare value is a distinct pseudo—that explains why a1's 62 instructions weren't threaded either.

I try rearranging the operand order, introducing a constant local before the call, or tweaking how the andi combines with the return value, but local-alloc keeps assigning v0 to the constant pseudo since it's free right after the call. Changing the comparison semantics isn't an option since I need to preserve behavior exactly.

The register preference would already favor v0, but the conflict with 14 blocks that merge. I'm now wondering about the original source: maybe it's a function returning u8, with a call-site return-type cast, and the comparison `func() == 0xE` being compiled as a branch rather than a sltu-based value in this gcc 2.x MIPS codegen.

I'm testing several candidate reconstructions — using s32 vs u8 for ok, assigning the result of the cast call directly, then comparing against 0xE in an if-else that sets ok to 1 or 0, versus assigning `ok = (ok==0xE)` directly in each branch. I should also check how func_800291B4 itself is declared to narrow down the right pattern.
