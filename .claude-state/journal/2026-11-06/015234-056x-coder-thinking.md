---
ts: 2026-11-06T08:52:34Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG24x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_GGBveqhSiwaID9aBQJqx
---
All merged. GCC removes those early.

Let me think differently. Maybe the merge isn't done by combine but by cse (copy propagation). Look at the cse dump: after cse1, insn 132 (copy) and 134 (neg reg78) are both present! So cse1 kept them. Then combine merged. OK.

So we need to block combine specifically. What does combine not merge across?
- A CODE_LABEL (block boundary).
- Any insn that uses the destination.
- A call.
- A memory reference that might alias? combine doesn't care.

Given jump.c runs before combine and removes redundant labels, we need a label that survives jump.c. jump.c removes a label if it's not a jump target. Our goto makes it a target, but jump.c also removes jumps to the immediately-following label (threading). What if the label is a target of a jump from a *different* place, so jump.c keeps the label but the jump... any jump we add costs an insn.

What if the label is at the end of the else block, targeted by a jump that jump2 (after reload) can remove? Hmm.

Alternative: a `do { ... } while (0)` where the loop is *not* removed because... hmm, gcc 2.7.2 might keep do-while(0) as a loop at RTL with a branch that jump2 removes? C0535 says "do{}while(0) splits cse1 EBB" — from the cookbook, do-while(0) splits the cse1 extended basic block! That means the do-while DOES create a label/branch at RTL that blocks cse1. But our c2 test with `do { val = nudge; } while (0);` gave score 1 — the do-while was around the *copy* only, with the neg outside. Let me re-read C0535.

Let me read cookbook C0535.
