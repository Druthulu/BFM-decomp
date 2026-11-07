---
ts: 2026-11-06T04:30:48Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG20
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_KopLzs5IwDl2yM1Vgc99
---
This is the ready-list scheduling. The "launching" lines are just when pending insns become ready. The reordering of the p load above the chain would be a ready-list choice based on priority. The p load's priority is 1; the chain's is higher. So it shouldn't be chosen first... unless the p load is in the "insn_queue" and gets launched at a specific T.

I've spent enough. Let me do the WALL path: generate a batch to reach 30 tries, record the best (14) and a wall tag.

Actually, wait. Let me reconsider: maybe the target's p load priority is 2 because the merge store IS in the same block. Let me check the target's block boundaries: at sched1 time (before jump2), the merge store at 494c might NOT yet be a label — the jumps to it are created by jump2/cross-jump AFTER sched1. In the target's original build, at sched1 time the merge store might have been reachable by fall-through from the `<0x11` arm with no label, making it the same block. Then the p load's priority = 2, and the chain's = 4, so the chain is scheduled first. That would explain the target!

In our build, the label at the merge exists at sched1 time because our C has a `goto call;` in the else arm and the arms jump over it. Hmm, but the target also has the else arm before the `<0x11` arm (reordered), and the earlier arms jump to 494c. Those jumps create a label at 494c at sched1 time (the label is needed for the jumps). Unless the compiler's arm reordering happens in jump2.

Actually, the jumps from 48b8/48d0/48f8 to 494c: those are in the target's final assembly. At sched1 time, were they jumps or fall-throughs? The compiler orders the basic blocks; the `<0x11` arm is placed between the else arm and the merge. The earlier arms (n<8, n<0x16, ==0) are before the else arm, so they must jump over the else and `<0x11` arms to reach the merge. Those jumps exist at jump-optimize time (before sched1). So the merge has a label at sched1. So the p load's priority is 1 in the target too. Hmm.

OK, I'll stop. Let me reach 30 tries with a batch and record WALL.

Wait, actually — one more idea that's cheap and plausible: the target's `<0x11` arm has a `nop` after the first lw (4928) and after the obj->1C lw (4934). Those nops are load-delay slots. In mine, the p load got hoisted INTO one of those slots? Mine: 4930 lw v1,28(s2); 4934 lw a0,32(s1) — the p load is in the delay slot of the obj->1C load! In the target, 4930 lw v1,28(s2); 4934 nop; 4938 sll. So the target has a nop (no insn in the delay slot), and the p load is later. In mine, the p load fills the delay slot.

So the hazard logic filled the load-delay slot of the obj->1C load with the p load (which is independent). In the target, the slot was a nop. To prevent the p load from filling that slot, the p load must not be ready at that time — e.g., its address must depend on something not yet computed. If the p load's address depended on the obj->1C load's result, it couldn't fill the slot. But that's a fake dependency.

Hmm, unless the p load's address is computed from a value that's defined later. In C, p = *(a0+0x20) — address a0, always ready.

What if the p load is through a pointer variable q that is assigned AFTER the obj->1C load? E.g., `q = (s32*)((s32)a0 + 0x20);` before the p load. The q assignment is a copy, ready early. No.

What if q is computed from v? no.

The target's nop suggests the original compiler did NOT have the p load ready in that slot. Maybe the original C had the p load AFTER the addiu (so its birth is after), and sched1 didn't move it into the slot because... hmm, but sched can move any ready insn.

Let me test the variant where the p load is after the addiu (x1 was chain, add, p) — we saw the RTL for w9/x1 had p before add (232<235), suggesting the scratch was stale. Let me re-dump x1 specifically and check the RTL order. Actually, let me just run a fresh --keep for x1 and dump.

Given time, let me do the batch first (to reach 30 tries) and include a couple of these. I'll generate variants:
- y1: p load after addiu (rebuild correctly) — x1 already.
- y2: q pointer assigned after the chain, then p = *q.
- y3: `p` as `Unkstruct_800B5CB8 *` type.
- y4: multiply into `n` then v.
- y5: multiply as `*(s32*)(obj+0x1C) * 0x60`.
- y6: do-while around the 0x1A store.
- y7: do-while around the whole arm body.
- y8: dead reset of p after the store (p = 0) — to break cse differently.
- y9: `v = *(s32 *)(obj + 0x1C) * 3; v = v * 32;`
- y10: swap the store and the multiply.
- y11: use `((Unkstruct_800B5CB8 *)p)->unk18 = v;` with p assigned via `q`.

Let me create and score them in one sc.sh batch. Then record.

Actually, y8 (dead reset) is interesting: `p = model; store; p = 0;` dead → cse invalidates, then the merge store needs p → reload. Hmm, the merge store is after the arm; p must hold the model. If p=0 dead, then p is reloaded at the merge... that changes the structure.

Let me just do a batch of 12.
