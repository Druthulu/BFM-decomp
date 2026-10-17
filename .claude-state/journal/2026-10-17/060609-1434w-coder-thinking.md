---
ts: 2026-10-17T12:06:09.743Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a8e969c8cbf9244d6
model: claude-opus-5-5[1m]
effort: medium
turnId: 150f717e-3914-450b-b185-2137b70bb2af
---
I'm comparing the target and my version here: both reload index [0] via lh, but mine forwards the value for [1] instead of reloading it. I'm digging into why CSE treats the stored HI value differently—likely because the sign-extended memory access gets recorded against a truncated SImode subreg rather than matching cleanly with the later load.

I suspect this comes down to basic block boundaries created by the division trap check (the conditional branch and break instruction), which would normally make CSE forget earlier equivalences unless it's following the extended basic block along the fallthrough path—so the ordering of the division relative to the stores and loads in my version versus the target must differ enough to change which value survives across that branch.

Though actually I wonder if invalidation is about alias checking on the store itself: CSE's invalidate logic for a MEM store checks whether the base register and offset provably differ from an existing cached entry, and maybe the discrepancy is really about how the address is computed (through an explicit integer cast) rather than which block boundary matters.

To force reload of element [1] in plain C, I should try spelling the read identically to how [0] is read, or read directly from the symbol, or reorder the accesses to see which variant triggers the reload.
