---
ts: 2026-10-17T13:46:44.796Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: abe7336983cc0fdaf
model: claude-opus-5-5[1m]
effort: medium
turnId: ad81449e-f0c8-40b2-83c6-f273f94996ed
---
I'm noticing the target repeats "lui a0; addiu a0" before each jal call, suggesting the address value isn't kept as a cross-call pseudo but instead gets rematerialized from a constant equivalence each time rather than spilled and reloaded.

I'm trying to figure out why global allocation wouldn't just assign s0 to that pseudo in the target like mine does, even though s0 is free there -- maybe global-alloc's handling of cross-call pseudos with REG_EQUIV constants deliberately avoids allocating them to callee-saved registers, preferring rematerialization instead when the pseudo has constant equivalence and low priority relative to other live ranges.

I wonder if the second call's argument isn't the raw symbol but a field access, like `&D_800AF648.field0`, which would still produce a lui/addiu pair but through a different offset computation — worth testing against the actual disassembly.

Thinking about CSE behavior across calls: in gcc 2.7's calls.c, expand_call precomputes arguments into pseudos when they're expensive, even for constant addresses, under certain optimization conditions involving loop depth and rtx_cost thresholds — that mechanism could explain why the second lui/addiu pair gets reused or regenerated differently than expected.

I'm uncertain about tracing this through reasoning alone, so I should check the actual dump instead. I'll try reconstructing the translation unit by splicing in the candidate body and resolving the include paths so cc1 can process it directly.
