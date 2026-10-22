---
ts: 2026-10-22T00:49:49Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG14
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_vytjgjVDmbi5ACrF9Wz7
---
func_80191020's launder: `__asm__("" : "=r"(vol) : "0"(vol));` — the comment says "sched1 otherwise hoists the PAN multiply ahead of this one". So the launder blocks sched1 from hoisting a multiply.

The do-while might block that (a CFG/scheduling barrier)! The combos will tell.

Let me check the combo sweep progress.
