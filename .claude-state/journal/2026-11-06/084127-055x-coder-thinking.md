---
ts: 2026-11-06T15:41:27Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO05
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_CODnhCJwdXj7DhtUpwns
---
The do-while split the EBB and prevented the sum merge! Now mine has:
```
107 move a0,s0
109 move a0,s0
110 addiu a3,sp,104
```
Hmm wait — mine[107] is move a0,s0 but target[107] is addiu a0,s0,24. So the sum is still in s0? Let me look at the disassembly of vba around 105-115. It seems s0 still holds the sum? And a3 got sp+104 (the p0 pointer) instead of s0.

Actually the do-while changed register allocation: the p0 pointer went to a3 instead of s0, so s0 is still the sum. So the EBB split didn't break the sum.

Hmm, but wait: in target s0 = &D_800AF630 and then s0 = sp+104. In mine (vba): s0 = ? Let me disassemble. Actually mine[107] move a0,s0 implies s0 = base+24 still. The do-while moved the p0 pointer to a3.

So the do-while didn't help; it just reallocated.

Let me look at the disassembly to be sure.
