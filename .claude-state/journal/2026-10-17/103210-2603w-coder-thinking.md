---
ts: 2026-10-17T16:32:10.691Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: abb4a08fa100d7feb
model: claude-opus-5-5[1m]
effort: medium
turnId: dd20a3af-7bad-4cc5-bdfe-eb40b857c079
---
I'm looking at the condition where the destination register becomes the "first"/cheapest in its equivalence class—this happens based on register lifetime rules, where a new register takes priority if it lives beyond the current basic block, following the logic in make_regs_eqv around lines 840-860.

To stop the swap from firing, I'd need to insert something between the copy and its source so they aren't directly adjacent, or change which register lives longer so the cheapest-register selection doesn't flip. I'm trying variations where an intermediate store or assignment sits between the load and the copy to see if that breaks the adjacency the optimizer relies on.

If u8-typed with a separate zero-extend insn, combine could merge the load and extend into one lbu—that matches d5's result of 25. I'm checking whether other variants like folding an identity add or mask operation would get banned or also collapse early, and considering if changing tmp9's type to s32 changes how the load expression combines.

What about declaring tmp9 as u16 or s16 instead? Then the sign-extend of a half-word zero-extend might simplify back into a single zero-extend of the byte load, likely still producing lbu—worth testing both variants to confirm.
