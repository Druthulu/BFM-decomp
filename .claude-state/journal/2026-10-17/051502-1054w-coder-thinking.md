---
ts: 2026-10-17T11:15:02.761Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a7979eba5885c3edf
model: claude-opus-5-5[1m]
effort: medium
turnId: 921e828f-1fac-424f-94a0-d040638a6158
---
I'm comparing the instruction scheduling around the barrier and call site, checking where the addiu and move instructions land relative to the jal delay slot versus the target ordering.

The real discrepancy seems to be in the first block's branch structure—figuring out how the no-barrier version turns a conditional-plus-jump pattern into a single branch with the zero assignment moved into its delay slot, which looks like the classic reorg.c optimization for collapsing a branch around an unconditional jump.

I'm not sure the delay slot filled with v0=0 would block this rule, so I need to actually trace through reorg.c's relax_delay_slots function to see how it decides to invert the branch.
