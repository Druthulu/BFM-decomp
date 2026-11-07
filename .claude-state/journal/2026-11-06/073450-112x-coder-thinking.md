---
ts: 2026-11-06T14:34:50Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO02x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_Ikkt4Vnc15H6VcBlBNHm
---
In c1 (no keepalive), block 3 is insns 43-105 (the asm insn removed, so 2 fewer). The scheduling order (final): 45, 47, 49, 52, 58, 61, 64, 67, 70, 72, 75, 77, 86, 89, 94, 96, 98, 100, 104, 105. Wait, the T- order: T-1=105, T-2=104, T-3=100, T-4=98, T-5=96, T-6=94, T-7=89, T-8=86, T-9=77, T-10=75, T-11=72, T-12=70, T-13=67, T-14=64, T-15=61, T-16=58, T-17=52, T-18=49, T-19=47, T-20=45. So the final order: 45, 47, 49, 52, 58, 61, 64, 67, 70, 72, 75, 77, 86, 89, 94, 96, 98, 100, 104, 105.

Hmm, so in c1, the order is also 45, 47, 49, 52... same as orig? But the final asm differs (a1 at position 31). Wait, the insn numbers shifted because the asm was removed. Let me map: in c1, insn 45 = ? and insn 49 = ?

The ready list at T-19 has 45 and 47, and 47 is launched before 45 (so order 47, 45? or 45,47?). "ready list at T-19: 45 (1) 47 (1), now 47 45" — the list after is "47 45", meaning 47 is at the head. Hmm, the scheduler picks the head. So 47 is launched at T-19, then 45 at T-20. So the final order (from last to first): ... T-19=47, T-20=45. So the order is 45, 47, 49, 52... Wait, T-20 is the last launch (first in final order). So final order: 45 (T-20), 47 (T-19), 49 (T-18), 52 (T-17), 58 (T-16), ... 

Hmm, that's the same order as orig (45,47,49,52...). But the final asm has a1 late. So maybe insn 45/47 are not the a1 la.

Wait, in c1 the asm insn is removed, so the insn numbering differs from orig by 2 after the asm position. Let me map the insns to operations. Let me look at the .rtl dump (pre-sched) for c1 to see insn 45, 47, 49, 52.

Actually, the final asm for c1 (from the score diff) has a1 at insns 31-32. The sched order 45,47,49,52... corresponds to the emitted order. Let me just look at c1's .s for the function.

Let me read c1's .s function.
