---
ts: 2026-10-17T16:35:11.157Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: ac3c2f25cd86a3f15
model: claude-opus-5-5[1m]
effort: medium
turnId: da7823f9-4546-4a0b-8e5a-1b168f412af7
---
I'm thinking about pins that don't correspond to row kinds — if a function has a pin lever but no pin row, that pin needs to be excused by another row type, like a missing-parameter row. That's likely why 8003388C has 13 pins covered by other causes rather than its own row.

So MATCH becomes about singleton-row kinds getting removed while other row kinds persist independently — consistent with the row-level crack rule. But I'm now worried about 80186B70, where removing one pin could orphan its missing-parameter row, forcing the banker to drop that row too unless another pin key still matches. I also need to flag the barrier crack via raw casts instead of struct fields — swapping to plain casts without the safety flag is a real codegen-affecting change that increases raw pointer casts in the type census, which complicates the residue ledger.

The MEM_IN_STRUCT_P scheduling alias flag change is a legitimate C-level difference, not just an identity swap, so I'll accept it since the cast residue re-sweep covers it. New wall tags like greg-pri-refs, cse-copy-merge, lreg-v0-local-first, and combine-arg-fold all look fine to add. Now I'm ready to spawn W05 and add it to the tracking list.
