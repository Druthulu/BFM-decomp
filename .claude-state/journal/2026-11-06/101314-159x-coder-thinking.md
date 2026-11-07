---
ts: 2026-11-06T17:13:14Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO05x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_OsplCbwIfo9H7hwpeMQx
---
In the lreg dump (after local-alloc, before reg-renumber display?), the pseudos 87 and 117 are still shown as pseudos. So the lreg dump doesn't rename block-local pseudos in the RTL text? The `;; Register X in Y` comments give the assignment.

The insn 664 shows `(reg:SI 117)` used in a store (the 0x8E store). Its REG_DEAD there. And insn 563-564 define it. So its live range is 563→664 (101 insns!), not 12. Hmm, the "used 10 times across 12 insns" line I read was probably for another pseudo.

So the constant 117: refs 2, life 563→664 = 101 insns → priority 2*1/101 = 0.02.
The mask 87: refs 13, life 571→1384? Hmm, the lreg insn numbers go up to 1384? The ands are at insns 1063-1384. So the mask's life is 571→1384 = 813 insns → priority 39/813 = 0.048.

Mask 0.048 > constant 0.02 → the mask should win t6. But it doesn't!

So my model is definitely wrong somewhere. Maybe qty_birth/death are not the RTL insn numbers but UIDs, and the priority division uses those.

I should stop theorizing and try a different empirical approach: brute-force small C changes that alter the mask's allocation. Since the mask is one variable, maybe declaring it in a different position (e.g., first among the locals) changes the pseudo number and the qsort tie-break. Let me try moving `u32 m24;` to the top of the declarations (before p0).

Also try declaring m24 as `s32` vs `u32`, and initializing at declaration `u32 m24 = 0xFFFFFF;` at the top.

Let me batch these.
