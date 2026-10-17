---
ts: 2026-10-17T16:11:20.706Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a7f42f9bd4d9f47ca
model: claude-opus-5-5[1m]
effort: medium
turnId: 1d9764d9-f745-4839-857f-1b214f31db78
---
I notice the ordering discrepancy: in my block the a0 move comes after the sra and lhu, but in the reference dump the a0 setup appears earlier despite having a later instruction number, suggesting scheduling placed it first in program order.

Maybe the difference is how the sra statement is written -- if it's a separate assignment like `v1 >>= 12` writing back to the same pseudo versus folding the shift directly into the subtraction expression, the scheduler's priority could change. I should try tail variants that inline the shift into the subtraction rather than as a standalone statement, and also double check the call argument types, then fall back to brute-forcing more tail combinations.
