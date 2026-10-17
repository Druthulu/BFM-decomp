---
ts: 2026-10-17T16:12:37.984Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a7f42f9bd4d9f47ca
model: claude-opus-5-5[1m]
effort: medium
turnId: 1d9764d9-f745-4839-857f-1b214f31db78
---
I'm trying to figure out why sra appears first in A1 under sched1's backward list scheduling, where priority follows critical path length and ties break by original order — checking whether insn 98's in-place shift on r93 creates a dependency that would force this ordering.

I'm also considering register pressure heuristics—whether the shift insn being a "birthing" instruction that kills a register affects its scheduling priority, and whether the local variable adj would need to be global for the in-place product register to match. The delay slot filling from the target block's first instruction could also explain why sra appears first in the A1 ordering.

Now I'm tracing through the target block's actual instruction order—a0 move, then lhu, then sra, then subu—and trying to figure out what scheduling pass (sched1 vs sched2, pre- or post-reload) would need to produce that same ordering with the hard registers already assigned.
