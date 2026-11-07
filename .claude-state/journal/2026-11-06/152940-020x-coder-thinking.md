---
ts: 2026-11-06T22:29:40Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM4
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_s4Xw7Gdraa0yziU6ksH6
---
After greg, registers are replaced by hard regs. Let me instead look at the pre-greg dump: w0.i.lreg is after local-alloc (registers numbered). Actually the lreg dump shows reg numbers. Let me grep in the lreg dump section for reg 75 within our function.
