---
ts: 2026-11-06T21:06:58Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW50
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_NXSQ3UpR8zPMKuf5HvQu
---
Confirmed: off (insn 54) got a0 (reg 4), e (insn 73) got a1 (reg 5).

So local-alloc gave off a0. Now let me find qty_birth/death. Perhaps qty_birth/death use the qty's first/last *reference* but e's death extends? Or maybe e's REG_EQUIV makes its qty get merged/eliminated.

Wait — maybe the qty for e (reg 79) is a *separate* qty, but it has REG_EQUIV so global-alloc can delete the set and rematerialize at the use. Then e wouldn't compete at all in global-alloc; it's local though.

Let me look at the actual local-alloc behavior. qty_birth[q] and qty_death[q] are set in local-alloc. Let me read where.
