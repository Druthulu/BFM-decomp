---
ts: 2026-11-06T04:19:23Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG20
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_pRoFmk8N9cTmpdsiLMXR
---
No improvement. The remaining hoist of the p reload above the sll chain persists.

Let me think: the target reload is at 4944, after `sll v0,v0,0x5` at 4940. Mine at 4930 (after lw obj->1C, before sll). So sched1 hoisted the p load (lw a0,32(s1)) above the sll/addu/sll chain. To stop it, we need a dependency: the p load's address (s1) doesn't depend on the multiply.

The fence was after the multiply and after p's load (two fences). Real C: create a dependency between the multiply and the p load, e.g., use a temp for the multiply's intermediate and reuse it in p's address? No.

What about making the p load happen AFTER `v = v + 0x600` in source? The source order is multiply, p, add. Target: multiply, p, add. So source matches target; only the scheduler moved p's load earlier (above the multiply's sll chain). To stop sched1, the p load must have a dependency on the multiply.

Idea: make `p`'s load depend on `v` via a dummy? e.g., `p = (Unk*)((s32)((Unk*)a0)->unk20 + (v & 0))` — the `v & 0` folds to 0, dependency gone.

Hmm. The classic do-while split didn't work here because sched1 can still hoist across? Wait, w6 wrapped the multiply in do-while and it stayed at 14. Maybe the do-while didn't split the EBB in this context (the arm is inside an if-else chain; the do-while adds a loop note but sched1 still moves?). Or the do-while changed something else.

Let me look at w6's actual diff to see if the p load moved.

Actually, maybe a better approach: reorder the source so that the p load is *after* the add:
```
v = *(s32*)(obj+0x1C) * 3 * 32;
v = v + 0x600;
p = ((Unk*)a0)->unk20;
```
Target order: multiply, p load, addiu. If source is multiply, add, p, sched might produce multiply, add, p (not target). Hmm.

What about `v = (*(s32*)(obj+0x1C) * 3 * 32) + 0x600;` one expression then p? Sched would interleave.

Let me try: p load after add (w8). And also a variant where p is loaded at the top and reused (but the store kills cse, forcing reload — target has two loads: one at 4924 before the store, one at 4944). Wait, target's first load at 4924 is for the 0x1A store from the RAW pointer expression `((Unk*)*(s32*)(a0+0x20))->unk1A = 0xC00;` — the raw expression loads model once. Then the store `sh v0,26(v1)` at 492c. Then the multiply. Then p's load at 4944 (cse can't reuse because the sh may alias `*(a0+0x20)`). So target has exactly the natural cse behavior: raw store loads model; store kills; p load reloads.

Mine: the raw store's load is at 4920 (lw v1,32(s1)), sh at 4928. Then 492c lw v1,28(s2) (obj->1C), 4930 lw a1,32(s1) (p reload), sll chain, addiu, sh. So mine hoisted the p reload above the multiply chain. Same as target except position of the p reload.

To force p's reload after the multiply, sched1 must not hoist it. sched1 hoists loads to fill latency. A dependency would stop it. What if the multiply result `v` is used to compute the store address? No.

What if we make `v` and `p` share a register by reusing a variable? E.g., assign p to the same variable as something? No.

Hmm, what about using the dead-reset trick to make the p load's value register... no.

Let me look at sched1's behavior: it schedules within the basic block. The block here starts after the branch `bnez` at 4900? Actually the `< 0x11` arm is the fall-through of the `bnez` at 4900; the block includes the arm and ends at the j. The p load is in the same block as the multiply. sched1 can move it up to the block start (right after the branch delay slot). Target has it at 4944.

Why does the target keep it after the sll? Because the fence (asm) was a scheduling barrier in the original... but the ROM has no fence. So the original compiler scheduled it after. The scheduler's heuristic (priority) put it later. So a plain C that gives the scheduler the same priorities would work. The difference in priority may come from the source structure: e.g., if `p` is used immediately after (the sh), its load is on the critical path and gets priority... but it was hoisted in mine, meaning it had high priority and was scheduled early. In target it's later — maybe because the load was born later (the pseudo's birth order).

Birth order: in the RTL, the p load insn is after the multiply insns. sched1's list scheduling picks ready insns by priority; a load with a use nearby (the addiu then sh) might be scheduled... Hmm.

Maybe the difference is the *order of the sll/addu* chain: target does sll v0,v1,1; addu v0,v0,v1; sll v0,v0,5. Mine: sll v0,v1,1; addu v0,v0,v1; sll a0,v0,5. Same. Then target lw v1; addiu; sh. Mine lw a0 (hoisted); addiu; sh.

What if we make the `+0x600` part of the same expression as the multiply? `v = *(s32*)(obj+0x1C) * 3 * 32 + 0x600;` — then the addiu is part of the chain and p's load might be scheduled after the whole chain? Let me test (w8). Also `v = *(s32*)(obj+0x1C) * 96 + 0x600;`.

Also try moving p's load after the add (w9).

Let me test these.
