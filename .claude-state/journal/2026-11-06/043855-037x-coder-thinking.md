---
ts: 2026-11-06T11:38:55Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG30
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_SiYMrMQkcT1TmvodmCvJ
---
Default insn_cost is 1 unless defined per-insn. Let me check for `insn_cost` in the 2.7.2 tree (default: `#define INSN_COST(INSN) 1`?). In sched.c, `insn_cost` is a function pointer set by machine? Let me grep.
