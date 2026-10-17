---
ts: 2026-10-17T16:29:24.295Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: abb4a08fa100d7feb
model: claude-opus-5-5[1m]
effort: medium
turnId: dd20a3af-7bad-4cc5-bdfe-eb40b857c079
---
I'm recognizing this as CSE's register retargeting optimization — when a set of a register is immediately followed by a copy to another register, and the source dies there, CSE rewrites the original instruction to target the destination directly and removes the now-redundant copy.

I need to figure out how to break this chain, possibly by inserting an instruction between the load and copy that doesn't get rescheduled, or by restructuring the store order so the copy isn't immediately adjacent to the set.

Actually, I realize the zero-extend case matters here: if tmp9 is a QI register, the load becomes a zero-extend rather than a plain register copy, so combine might fold the load and zero-extend together into a single `lbu` before I can intervene—meaning cse's copy-elimination trick only kicks in for reg-to-reg moves, not zero-extends. I'm now digging into the exact conditions cse.c checks (around line 7000 in 2.7.2) for when it collapses a preceding set into the destination directly.

I'm wondering whether the lingering copy gets merged away later since r94 stays live through the stores, which could explain why c5 still comes out at 25, matching c0. Let me compare c5's target against mine to spot the actual divergence.
