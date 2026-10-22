---
ts: 2026-10-22T11:19:55Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM2x
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_gMPj9NhcejmiTCa8l0Ui
---
No sched1.c. But `flow.c`, `jump.c`, `combine.c`, `cse.c` are available — very useful for understanding block formation.

Let me check `flow.c` for how it handles blocks, and more importantly: what creates a block boundary that survives to sched1.

Actually, here's the KEY question I should answer: in GCC 2.7, is `pass_flow` before or after `pass_sched`? Let me check toplev.c!
