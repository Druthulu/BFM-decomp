---
ts: 2026-10-17T16:33:42.403Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: abb4a08fa100d7feb
model: claude-opus-5-5[1m]
effort: medium
turnId: dd20a3af-7bad-4cc5-bdfe-eb40b857c079
---
I'm figuring out which variable stays canonical based on which one's last use occurs later in the block—since iVar1 gets used early but then there's a later reload from memory, I need to check whether keeping t alive longer actually changes the liveness comparison.

If the hard register case applies (firstr < FIRST_PSEUDO_REGISTER), the new value always becomes canonical regardless, which could explain why t replaces v0 directly. But if iVar1 inherently lives until the later call while t dies at an earlier comparison, then t can never outlast iVar1 within the same block—unless the copy crosses a cse basic-block boundary, which would reset the comparison entirely.

Maybe instead iVar1 is set by rereading `p0->unk20` after the store, letting cse substitute the known memory value r75 for the load, which would explain why the reload disappears into a plain register copy rather than a real lw instruction.

This confirms the mechanism: make_regs_eqv in cse.c line 840 marks iVar1 canonical since it outlives t across the block. I should update the notes with this evidence and move on to writing the log for T11.c04, accepting the 80188680 case as solid enough without further digging.
