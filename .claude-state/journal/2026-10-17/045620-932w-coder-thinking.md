---
ts: 2026-10-17T10:56:20.001Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a55474736c80a3baf
model: claude-opus-5-5[1m]
effort: medium
turnId: e20d419a-4489-4243-b756-85abe7c2d13c
---
In v07 the ordering now places or above the chain, matching the target, but x1's definitions with lower priority got scheduled too late backward. I need to figure out how to reposition that node so it launches earlier like it does in the free version.

So I'm wondering if x1 should stay single-set while the or-expression becomes multi-set, trying to pin down what actually determines priority 2 versus priority 1 for these insns — maybe it's whether the successor chain reaches a multi-cycle instruction. I try a few variants: merging the zext into the multi-set or-expression, or giving x1's def another late consumer, but each path seems to dead-end since x1 is only used once and its producer stays single-set regardless.

Looking at LUID ordering among the priority-1 ready instructions, I notice insn 65 gets scheduled right after 42 and before the big block of loop-invariant moves (313, 315, 332, 319), landing near the top of the output — which lines up with where x1's addiu/andi actually sit in the target, right after the first store. That suggests sched2 is largely reordering by LUID once priorities tie, so I want to trace where the corresponding store insn falls in sched1's order to confirm this pattern.

Actually v07's ordering shows 65 placed before 61, contradicting my LUID-priority assumption — so the ready-list dynamics must be more complex, with high-LUID loop-hoisted instructions getting picked up differently. The better approach is probably to hill-climb from v07's structure, which already nails the or/chain ordering, and just search for where x1 should float to get the register assignment right, since v07 scored 81 versus my 79.

18 stays ready until all other prio-2 insns are exhausted, since its LUID is lowest among them, so prio-2 instructions dominate the schedule before 18 gets picked, and only then does prio-1 (x1) get scheduled. That confirms x1 ends up above 44, 45, 53, etc., unless x1's own priority computation—likely based on recursive successor costs—differs from what I assumed.

Maybe priority 2 marks instructions on a dependence chain to something with latency, like the lbu load at insn 50. But 50 itself shows prio 1 with ref_count 9, which doesn't fit that theory cleanly. I should check how priority() is actually computed in sched.c.

v07's scheduling now matches the target order for the `or` chain, but x1's defs (64, 65) still sink to the block top because they're priority 1 instead of 2. I'll dig into what determines an instruction's priority 2 classification.
