---
ts: 2026-10-17T12:10:26.934Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a54c7d32163ae0888
model: claude-opus-5-5[1m]
effort: medium
turnId: 06fcde63-5d28-4e8d-8c65-7414dbf4e61d
---
I notice insn 331 got a huge priority boost to 0x7f000001, which looks like a scheduling heuristic forcing it to be placed as late as possible, likely tied to register-kill behavior in backward scheduling.

Comparing this against the preheader block where all insns have equal priority and no such boost appears, it seems the boost only triggers when a copy carries a REG_DEAD note — the copy kills m since the later instruction reads k. That could explain why the copy ends up scheduled after j instead of before it, which is the opposite of what I want for minimizing k's live range, so I need to trace through the scheduler's birthing logic to see exactly which condition assigns that priority value.
