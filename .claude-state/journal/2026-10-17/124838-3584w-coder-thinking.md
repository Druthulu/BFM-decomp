---
ts: 2026-10-17T18:48:38.676Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a0b7566fdaca12346
model: claude-opus-5-5[1m]
effort: medium
turnId: 5fa06e7a-0d54-4425-8d05-7af8227a2b37
---
This approach is worse, scoring 2 with immediates still present. I'm going back to try fixing the immediates while keeping u as s16, considering whether a separate s32 subtraction expression assigned to a temp could avoid the HImode narrowing issue that combine/expand introduces.

The real problem is that the C compiler's convert_to_integer narrows the subtraction arithmetic when assigning to a 16-bit variable, distributing the truncation. To block this, I need an operand that resists simple truncation, but constants in range won't help. The key insight is that a separate copy instruction like "move a0,v1" (addu with zero) only survives when a0 and u are distinct pseudos that combine doesn't merge — if both are s32 and used in a store plus comparison, combine eliminates the intermediate copy entirely.

So the behavior differs based on whether the mode is HI vs SI and how the subtraction/truncation interacts with the copy: for HI mode copies get kept in some cases, while for SI mode with truncation to s16 the copy gets folded directly into the store. The difference between the -0x120 and -0x700 lines seems to come down to local-alloc's ordering choices rather than the code pattern itself, so I'm considering whether rephrasing the comparison (shift-based truncation vs explicit cast) or introducing a fresh s32 temp variable might change which register gets allocated where.

Since local-alloc's tie-breaking favors lower allocno numbers, and pseudo registers get assigned in declaration order during expand_decl, declaring a new helper variable at a different point in the source could shift its regno and potentially flip the allocation outcome for the -0x700 and -0x6C0 lines. I want to try moving the declaration of that variable to different positions to see if it produces the register pattern I'm after.

I found that local-alloc swaps v0/v1 on the -0x700 line, and declaring a fresh s32 temp at different positions changes the pseudo number and tie-break. I'll sweep through the declaration positions to test this.
