---
ts: 2026-10-22T06:47:42Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG15b
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_u7Ld7uVB7ZH0aSGmrHre
---
Interesting: in the tree, the boosted insns are 68, 56, 35, 24, 27, 40. In cand, boosted: 66, 54, 33, 22, 25, 38, and 15 at T-21.

Note in cand, insn 15 has priority 7f000001 at T-21, and in the tree insn 15 has priority 1. So the tree's insn 15 is NOT boosted but cand's insn 15 IS. And the tree has an extra boosted insn 68 (T-2) vs cand 66 (T-2) — probably the same instruction (the last one).

The key difference is insn 15: in cand it's boosted (7f000001) at T-21, in tree it's priority 1. Since the tree has 2 more insns (71 vs 69 total; block 4..71 vs 4..69), the numbering shifts.

The boosted insn 15 in cand: let's find what insn 15 is. Let me look at the .rtl dump (tree.i.rtl = RTL before sched? or after?). The .sched dump contains the final RTL with insn numbers. Let me grep the sched dump for the insn listing (after the ready list, the dump prints the resulting RTL with insn numbers).

Let me look at lines 55-120 of cand.i.sched.
