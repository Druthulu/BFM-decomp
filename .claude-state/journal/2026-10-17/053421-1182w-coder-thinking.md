---
ts: 2026-10-17T11:34:21.932Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a54c7d32163ae0888
model: claude-opus-5-5[1m]
effort: medium
turnId: 06fcde63-5d28-4e8d-8c65-7414dbf4e61d
---
Since m is already zero-extended from the lhu load, I'm wondering if declaring m explicitly as a u16 variable would let the compiler see it's already masked and drop the redundant andi, since the current approach can't see across the block boundary.

On MIPS with PROMOTE_MODE, a u16 local gets promoted into a full SImode register with known zero-extension semantics, meaning `k = m` would just collapse into a plain subreg move — which brings back the equivalence problem, since the earlier mu16 tests already hit this with a plain copy. The real issue seems to trace back to how cse.c picks the class head when k and m become equivalent, so I need to look closely at how that's handled around that section of the code.
