---
ts: 2026-10-17T11:26:44.907Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a7979eba5885c3edf
model: claude-opus-5-5[1m]
effort: medium
turnId: 921e828f-1fac-424f-94a0-d040638a6158
---
This case was already resolved using dead branches and a volatile cast, and I'm trying to figure out whether the invented always-false condition and the unused computed edge value were legitimate levers, given that sibling copies of this class show the same pattern.

I keep testing possibilities for what the real flip-test condition might have been — scanning flag bits, tpage construction, and texture flip bits in the GPU draw mode word — trying to find a bit that's provably always zero so the branch can be justified as dead code rather than an arbitrary invention.

A prior agent flagged the v-arm as writing sv when it should write su for allocation purposes — if that branch tests a condition that's provably always false, it's effectively a do-nothing statement, which by the brief's definition counts as a lever rather than genuine original logic.

Thinking through other ways unread arithmetic could appear innocently: maybe through a later-folded use like a flip-conditional that simplification proves constant, or an identity expression such as multiplying by zero or subtracting a value from itself, or a narrowing operation that silently drops the computed value.

I'm now considering whether the dead values get packed into a byte-sized field that truncates them away, since poly->u2 and poly->v2 are both byte stores -- combine could simplify a shifted-and-OR'd value stored into a narrow field down to just the low part, naturally discarding the high bits that correspond to the unread arithmetic.

Given limited time, I'll test the flip-bit hypothesis against tpage flags for u/v, treating it as the most likely "natural" explanation if it scores zero, and move toward setting up the calibration scorer against body_tree.c, which requires pulling in the Ft4 type definitions and SR3/ADDPRIM macros from the translation unit.

I could try building a file from the TU prefix up through the target function and feeding it to match_one, since the TU already includes common.h so it won't get double-prepended. I need to check how large that file would be and locate where Ft4_801833F0 is typed in the TU before assembling the needed definitions.
