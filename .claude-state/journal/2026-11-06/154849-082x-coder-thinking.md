---
ts: 2026-11-06T22:48:49Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM4
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_A9xIzLxr8IGiJ6RlV2sv
---
The sched1 priority: insn 16 (lw pointer) priority 1, insn 20 (lh s1ang) priority 2. In w6, insn 16 is launched last (T-16), after 20 (T-14). Hmm, but the final order (from the lreg dump) was 16, 20, 25... Wait, the sched dump says "launching 16 before 20 with 1 stalls at T-15" and "ready list at T-16: 16, now 16". Hmm, the scheduling is from the END backwards (T-1, T-2...). So the final order is 16 first, then 20? Let me parse: the scheduler fills from the end. At T-16, insn 16 is placed; at T-14, insn 20 is placed. So in the final order, 20 comes before 16? The T index counts backward: T-1 = last, T-16 = 16th from last. So insn 16 is at position 16 from the end, insn 20 at position 14 from the end → 20 is AFTER 16 in the final order? Hmm, T-14 > T-16 means 20 is closer to the end. So the final order is: ..., 16, ..., 20, ...? No wait.

Ugh, let me just compare the two sched dumps. Let me get w0's sched priorities.
