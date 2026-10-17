---
ts: 2026-10-17T11:13:33.171Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a5faba3cdb29155cb
model: claude-opus-5-5[1m]
effort: medium
turnId: e4e5bc1c-68a3-4a95-bce5-27c78dfaef1c
---
Tracing through the memory address case: for (mem r73) where r73 equals r72 plus 4, I'm checking whether the equivalence class includes a folded constant result alongside the original expression, since inserting that constant could change which candidate gets chosen as the best address when comparing costs and tie-breaking rules.

But I notice fold didn't actually produce a constant in cse1's scan, even though insn 8 should have set qty_const for r72 when processing the symbol constant source. That's odd given the scan range processed. I suspect there's a special case in fold_rtx's operand loop around how REG arguments are folded for addresses—possibly a condition that skips constant substitution specifically when the register is part of a memory address, which would explain why cse1 leaves it unfolded while a later pass folds it.
