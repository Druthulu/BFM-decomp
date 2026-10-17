---
ts: 2026-10-17T14:06:22.239Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: abe7336983cc0fdaf
model: claude-opus-5-5[1m]
effort: medium
turnId: ad81449e-f0c8-40b2-83c6-f273f94996ed
---
I'm tracing a pointer into a global struct, storing fields at offsets 0, 0x10, and 0x20 with mixed relative and absolute values, then calling a function three times with increasing index and advancing pointer offsets. I'm working out how this translates into a natural C struct-array initialization pattern.

I think find_best_addr is comparing address costs: register-relative stays cheap at offset 0, but gets folded to absolute for certain offsets when cse determines that's cheaper, which explains why some stores stay p-relative (16, 32) while others go absolute (20, 24). I want to test a version where idx comes from a function call, a table pointer is loaded from a global, and the pointer gets advanced by 0x20 without that addition folding into the call argument.

Pin that structure against the actual data: writing to fields of a struct through the pointer, calling the second function with the table offset by 8, then three more calls where the pointer advances by 0x10 and 0x20 between them. I need to check the Unkstruct_8017DFB8 field layout (unk0, unk10, unk20) and how the separate globals are declared, then try building variants from there.
