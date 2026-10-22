---
ts: 2026-10-22T12:47:25Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG16
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_GU73rVofFY3jFnVfsNZI
---
§373 DEAD-RESET is a project-endorsed technique.

But note cookbook/C0453.md line 20: "second-set spelling (`x = x`, `x += 0`, `x &= -1`, dead-reset) is folded before `reg_n_sets` is ..." — let me read that; it suggests identity second-sets are folded (not load-bearing) but the dead-reset works. Let me read C0453 around line 20 and C0414.
