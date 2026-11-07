---
ts: 2026-11-06T12:47:45Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO01x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_LCm6NjjGBWAry7NazS0T
---
That's final_prescan_insn — it only prints "#nop" comments. The actual `nop` in the object is a real insn in the RTL: sched1 places `nop`? Hmm, in 2.7.2, sched.c handles load delay by treating the load as needing a gap. Let me look for how sched decides. grep sched.c for "get_attr".
