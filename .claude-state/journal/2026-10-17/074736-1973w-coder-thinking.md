---
ts: 2026-10-17T13:47:36.218Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: abe7336983cc0fdaf
model: claude-opus-5-5[1m]
effort: medium
turnId: ad81449e-f0c8-40b2-83c6-f273f94996ed
---
I'm figuring out that the matching lines fall within func_801810FC, where instructions setting pseudo registers for symbols get merged by CSE — the MIPS movsi expander forces the symbol into a pseudo, and CSE then replaces one register with another.

Thinking through how to block this: pinning the first call to hard register $4 (a0) works because the call clobbers it, but inserting a label alone won't stop CSE unless it's a genuine branch target, and since there's no conditional structure in this code path, the register equivalence survives across the call. I need another approach since the second call's value might not come directly from a symbol reference.

I'm wondering if the mismatch comes from two different symbolic names resolving to the same address only post-linking, which cse wouldn't treat as equal, or perhaps the argument is actually a raw absolute constant like 0x800AF648 rather than a relocatable symbol reference, which would produce different instruction bytes than the lui/addiu pair generated from a true symbol.

Then I consider whether global-alloc assigns s0 because r177 is left unallocated and gets rematerialized through a REG_EQUIV note during reload instead of being spilled normally.

That only applies with a single use, so that's not the fix here. I'm wondering whether separating each call's constant load into its own pseudo would stop CSE from merging them—checking how gcc 2.7's cse handles call boundaries, since symbol constants seem to survive invalidation across calls. Maybe restructuring the code with a loop or different control flow between the two calls could break the CSE opportunity.

I'm also considering whether wrapping the address in an equivalent-but-different expression, like adding and subtracting an offset, or referencing a different symbol at the same address, would prevent the compiler from recognizing them as the same constant—though many of these tricks would just get folded back by simplification.

Given how tricky pin4 is, I think it's more efficient to set it aside for now and check pin5 and the launder cases first before circling back, since time is limited.
