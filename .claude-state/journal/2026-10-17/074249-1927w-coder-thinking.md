---
ts: 2026-10-17T13:42:49.677Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a715c83225823a44a
model: claude-opus-5-5[1m]
effort: medium
turnId: cb00494e-7b3a-4f28-b3fa-24b3d50bb0ef
---
This same pattern appears in sibling functions too, suggesting it's a recurring family of statement-order issues rather than an isolated case. I should dig into the actual mechanics of sched1's backward scheduling and ready-list ranking in gcc 2.7.2, since cracking this could generalize across the whole family.

The ranking function prioritizes instruction priority, then register-pressure contribution, then LUID order as a tiebreaker. There's also a "birthing insn" adjustment during the non-reload-completed pass that tweaks priority for instructions affecting register deaths, which could be the mechanism causing this tag-load-after-use ordering.

Still writing birthing_insn_p logic...

Insns without register deaths get their priority boosted to max, which in backward scheduling means they get placed as late as possible — right before their use. That matches why pv load appears late in my version, but the target schedules pv early instead, so something differs in how deaths are counted there.

For the original to not get this boost, either pv is set more than once, or something dies at that load instruction — maybe p itself dies there, or the load uses a different pointer that dies, or pv is assigned in both branches of an if/else as the same scoped variable, making REG_N_SETS greater than one.

But setting pv in two separate basic blocks pushes it out of local allocation into global allocation, since a reg live across blocks needs REG_BLOCK_GLOBAL treatment, which changes its priority and could go either way for the result I need. I want to figure out if reusing a variable across branches naturally reproduces the effect the asm launder was faking.

Let me try reusing `ot` as the temp in the if-branch instead of introducing a new `pv`, then test with all explicit register pins stripped out, starting with the simplest version first.

Found the likely mechanism: sched1's `adjust_priority` boost gives a once-set live pseudo max priority, so if `pv` has REG_N_SETS ≥ 2 it schedules right before use—matching the target's early tag load. I'll replicate this in plain C by reusing one function-scope `pv` variable assigned in both branches (C0087).
