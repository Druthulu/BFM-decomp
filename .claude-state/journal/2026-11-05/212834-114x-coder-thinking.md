---
ts: 2026-11-06T04:28:34Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG20
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_2QRodrgzp2KbUc3F67Bh
---
Wait — this is the sched dump for a DIFFERENT function? "Function func_8017C8D0" — the TU is ov_SC06_016_jr_8017C8D0.c and the first function is func_8017C8D0. The dump includes all functions in the TU; the insn numbers here (200-265) belong to func_8017C8D0, not our func_801810A4! I need to find the section for func_801810A4.

Let me grep for "Function func_801810A4" in the sched dump.
