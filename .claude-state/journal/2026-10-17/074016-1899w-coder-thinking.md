---
ts: 2026-10-17T13:40:16.998Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a715c83225823a44a
model: claude-opus-5-5[1m]
effort: medium
turnId: cb00494e-7b3a-4f28-b3fa-24b3d50bb0ef
---
I'm comparing register allocations between my version and the target, trying to match which temporary holds which value (the mask constant, the pointer, and the index) so I can align the conflicting register assignment correctly.

In the target, a3 holds m24 across both statements, a2 is i4, t0 is mFF, a0 is pv, with v1 and v0 as temps — so priority ordering puts pv ahead of i4/m24/mFF but after the temps. In mine, pv ended up in v1 instead, meaning i4, m24, and mFF shifted into a0, a2, a3. This suggests I need pv's live range to overlap with the lhu temp so local-alloc pushes it later in priority, likely by reordering when pv's load happens relative to that lhu statement.

I'm also considering whether the memory load for pv could get folded into its single use via combine, but since MIPS can't do a MEM operand directly in an AND instruction, that substitution isn't possible — so update_equiv_regs wouldn't treat it as equivalent either. I want to check the actual local register allocation table for the if-branch block to see how qty priorities and hard register assignments were computed for pv, a0, a2, and a3 in that specific block.
