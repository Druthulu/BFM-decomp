---
ts: 2026-11-07T00:41:31Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cP1
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_AhvG19SCLoneBIZTM7z1
---
In the .lreg dump (before sched1), insn 53 (the val load) is already AFTER 65 (the *p=0 store): `(insn 65 62 53 ...)` and `(insn 53 65 68 ...)`.

So the order was already 56,59,62,65,53 BEFORE sched1. So the reordering happened earlier — in the .combine or .cse2 or .flow dump. The insn 53 has REG_EQUIV (mem D_801B7A84) — interesting: `val = D_801B7A84;` got REG_EQUIV (the load is equivalent to the memory). And insn 73 also has REG_EQUIV (mem D_801B7A84).

So the load was moved down by combine or cse2! Combine (or cse2) can move insns? cse2 doesn't reorder; combine can (it merges and can move). Actually, the REG_EQUIV note suggests cse2 or combine replaced uses.

Let me check the .cse2 and .combine dumps for the order of 53 vs 56.

Hmm, wait: in the .flow dump? Let me check where the order flips. Let me grep each dump for the chain "insn 65 62 53" vs "insn 65 62 56".

Actually the simplest: check the .combine dump (after combine) and .cse2 (after cse2).

Order of passes: cse1 (.cse), loop (.loop), cse2 (.cse2), flow (.flow), combine (.combine), sched (.sched).

Let me check .combine first.
