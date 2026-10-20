---
ts: 2026-10-17T18:25:13.310Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: abe44831ff24b6c2f
model: claude-opus-5-5[1m]
effort: medium
turnId: 38414235-3946-4014-b22c-6e9e31b9cd68
---
Comparing the two PLUS expressions symbolically, the terms differ (sym244 vs sym438, a1 vs a0), so no conflict is detected; even with a constant offset wrapped in CONST, recursing with find_symbolic_term still locates the underlying symbol correctly.

I'm trying to figure out what actually makes memrefs_conflict_p return a conflict here — probably a case where one side has no symbolic term at all, meaning the address is purely register-based. The load's index register, after canonicalization via reg_known_value, might resolve to such a plain register reference, which would explain the different outcome.

Shifting focus, I wonder if the store ordering issue is really about scheduling rather than the address comparison. In gcc 2.7's backward list scheduler, schedule_block builds the ready list from insns with no dependents and schedules in reverse, so I need to check rank_for_schedule to see how it orders candidates by priority and insn LUID when choosing what to place last.
