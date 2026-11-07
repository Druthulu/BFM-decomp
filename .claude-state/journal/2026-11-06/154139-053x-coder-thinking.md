---
ts: 2026-11-06T22:41:39Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM4
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_78A249xjX9l30WiXBbI5
---
So:
- r76 = u5 (insn 52)
- r78 = iVar4 (insn 81, 90, 100: minus)
- r79 = q (div results, insn 110, 112, 125)
- r80 = ? (4 refs/4, prefers v0)

So in the target: u5 (r76) = $a0, iVar4 (r78) = $v1, q (r79) = $v1 (shares with iVar4 since iVar4 dies in the div).

In w0: u5 (r76) = $v1, iVar4 (r78) = $a1, q (r79) = $a1.

So the difference: the allocation order/preferences. In the target, r76 (u5, pri 7142) gets $a0; r78 (iVar4, pri 30000) gets $v1. In w0, r76 gets $v1 and r78 gets $a1.

The .greg order is the same in both: 78 80 79 [74] 77 76. r78 is allocated first. In the target, r78 → $v1. In w0, r78 → $a1 (preference).

Why does r78 prefer $a1 in w0? The preference must come from a copy. Hmm, in w0, is there a copy between r78 and $a1? No.

Wait, maybe the "prefers a1" in the alloc table is not a copy preference but the *preferred class* or a preference set by `find_reg`'s "preferred" register from the previous... Hmm.

Let me look at global.c's preference mechanism. Search for "preferences".
