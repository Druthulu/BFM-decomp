---
ts: 2026-10-17T16:44:09.181Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: ac899e71a72e1a646
model: claude-opus-5-5[1m]
effort: medium
turnId: 7b755c42-d9e9-446c-8f08-faa68444d116
---
In case 11, the shared symbol address for &D_80075A40 is kept in a register across the call since both m and p reference it, while the target code recomputes p's address afterward — suggesting the real source computes p after the call, and cse reuses that constant's register for the second occurrence of the symbol.

To defeat this, I need p's address to be spelled differently so cse can't match the two occurrences. One option: instead of `&D_80075A40 + ((idx+1)<<7)`, write it as `&D_80075A40 + 0x80 + (idx<<7)`, which produces a different constant offset form `(plus sym 128)` rather than bare `sym`, preventing register reuse. I'm now checking whether the target's lui/addiu sequence for m's argument matches this altered form or if the ordering differs.

If the argument is loaded through a pseudo rather than directly into a0, that pseudo survives the call and gets reused by cse. So removing the laundering variable and passing the direct address instead should prevent the post-call store from sharing that pseudo, matching the original comment's explanation of what the "0"(m) launders were doing.
