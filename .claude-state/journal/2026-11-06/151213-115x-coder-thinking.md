---
ts: 2026-11-06T22:12:13Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM3
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_gDG8D1sDqt9DANb1WpsJ
---
i2's residual: the `lui a1,0xff; ori a1,a1,0xffff` (mask 0xFFFFFF) is scheduled 2 slots earlier than the target (target has a nop before it). This is a sched1 placement: mine has the mask materialization at 150/154, target at 154/158 — shifted by one insn (with nops in the delay slots).

Let me see the context lines 145-165 of both.
