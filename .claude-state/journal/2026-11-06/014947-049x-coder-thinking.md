---
ts: 2026-11-06T08:49:47Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG24x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_Bvc0DVZ9gtnatTqFVbXT
---
The `(use reg78)` appears in combine, lreg, sched but not cse2 or flow. Weird. Let me look at the lreg/sched dumps for the else block. Maybe it's an artifact of a different pseudo numbering: reg/v:SI 78 in combine vs in lreg could be a different pseudo (numbers are stable though).

Hmm, wait: the cse dump showed insn 132 = (set reg78 (reg77)); 134 = (set reg78 (neg reg78)). The combine dump showed insn 134 = (set reg78 (neg reg77)) and insn 265 = (use reg78). So in the combine dump, combine merged 132 into 134. But then what's the (use reg78) at 265? It's at the top of the else block. It could be the *asm use* if the asm were present... 

Let me grep the combine dump for `asm_operands` near the function.

Actually, hold on. Maybe the dumps_c1 directory got its files from the cc1 invocation on the scratch TU, but the scratch TU is the *whole* TU with all functions; the combine dump has 31353 lines and includes many functions. The `(use reg/v:SI 78)` might belong to the function at 30694 — we saw it in the RTL between label 128 and insn 134. Pseudo 78 is `val` in this function.

Hmm, could the `(use)` be from the `(s32)param_1` cast? No.

Let me look at the lreg dump around it — the lreg dump shows the final register assignment and the (use) insn's register.
