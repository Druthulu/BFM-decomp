---
ts: 2026-10-17T13:35:52.717Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a715c83225823a44a
model: claude-opus-5-5[1m]
effort: medium
turnId: cb00494e-7b3a-4f28-b3fa-24b3d50bb0ef
---
I'm puzzling over why the "live" value stays the same between the two cases despite the insn position differing—wondering if it's actually tied to reg_live_length from the flow analysis rather than something computed locally in the allocator, since priority is based on qty_n_refs divided by the death-birth range.
