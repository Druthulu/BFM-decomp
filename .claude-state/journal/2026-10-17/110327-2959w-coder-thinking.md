---
ts: 2026-10-17T17:03:27.630Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: acf1e900976d98019
model: claude-opus-5-5[1m]
effort: medium
turnId: 82d9c87a-028e-4c83-b14d-9d07f43471e2
---
I noticed the extractor matched a call site for func_800CD894 based on a conditional pattern, so I need to fix that case specifically. LoaderInitFileTable shows zero asm, which makes me wonder if the register pin is coming through a macro instead—worth checking. My plan is to try adjusting real C code (declaration order, temp variable timing, pointer reuse) so the register allocator naturally picks the same register the pin expects, rather than forcing it artificially.

I'll work through each `pin` row by creating lever-free copies and experimenting with plain C moves until the allocator naturally picks the target register, scoring results with dt.sh. If nothing works within ~30 minutes for an item, I'll document the gcc pass blocking it instead.
