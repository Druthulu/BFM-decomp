---
ts: 2026-10-22T10:00:32Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM2
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_bjMH4JSadWmIZ1dmuUWk
---
`equiv_constant(x)` — returns the constant equivalent of a REG via qty_const. This is used to replace uses of a reg with its constant! Let me find the caller: probably in cse's main loop, where a SET's source is a REG: `if (src_const = equiv_constant (src))` → replace.

Let me grep for equiv_constant callers.
