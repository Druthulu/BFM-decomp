---
ts: 2026-11-06T04:36:31Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG20
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_P7wwASZLXTA0OCxGl7N7
---
z11 = 29, 110 ins. Worse (jump2 didn't merge as expected, or the stores weren't cross-jumped).

Hmm. The cross-jump merging requires the stores to be byte-identical with the same registers. With separate stores, the registers might differ. Target's shared store uses v1/v0 consistently. 

This is a deep rabbit hole. z8 = 6 is the best. Let me try a couple more refinements on z8:
- The remaining diff is the p load/addiu order and a nop. Since z8's p load priority is 1 (sh in another block) vs addiu 2, I need the p load's priority to be 2. That requires the sh in the same block. The label between the arm and the store is the problem.

What if I add a do-while around the p load + add + store (the shared store)? No, the shared store is shared.

What if I make the `<0x11` arm's store be the shared store but reach it by fall-through without a label? The label is created by the other arms' jumps. If the other arms were AFTER the `<0x11` arm in the code layout (so they fall through to the merge too), no label. The compiler orders arms; our if-else order is n<8, n<0x16, ==0, <0x11, else. The target's order (final) is n<8, n<0x16, ==0, else, <0x11, merge. So the compiler reordered the else and <0x11 arms. The label exists regardless.

Alternatively, make the store not shared: duplicate it ONLY in the `<0x11` arm and keep the shared one for the others? Then the `<0x11` arm has its own store (in-block, priority 2) and the others use the shared. But then the `<0x11` arm's store is a separate instruction that jump2 might merge with the shared one (if identical). If merged, we're back. If not, we get an extra store. Hmm.

Let me try: in z8, give the `<0x11` arm its own store and `goto call;`, leaving the shared store for the others. z1 did this WITHOUT the p reuse (score 27). With the p reuse, maybe better. Let me build z12 = z8 + `<0x11` arm own store + goto call.

Actually, the target's `<0x11` arm's store IS the shared 494c (the others jump to it). So the target's source had a shared store. So duplicating shouldn't match. But the block/priority analysis suggests the store was in-block at sched1. Contradiction.

Hmm, unless at sched1 the shared store's label was AFTER the store (i.e., the label is at the `call:` point, not the store). The other arms jump to the store (494c), which is before `call` (4950). So the label must be at 494c. But maybe jump2 moved the store before the label later? The final code has the label at 494c (the jump target). At sched1, maybe the store was at the end of the `<0x11` block and the label was elsewhere; jump2 then retargeted the jumps to the store. Possible: the original C had the store shared (one statement), and the compiler placed the label at the store. So the label exists at sched1. Then the p load's priority is 1 in the target too, and the addiu (2) should win... but the target has lw first. So my priority reasoning must be wrong.

Maybe the p load's priority is 2 because the store is in the same block: if the label is placed AFTER the store (at the call), the store is in the `<0x11` block. Then the other arms' jumps target... the call label? No, they need the store.

I'm going in circles. Let me just try z12 (own store + goto) and a few variants, then wrap up. Time 21:38.

z12: z8 + `<0x11` arm's own store + goto call (leaving the shared store for the others).
