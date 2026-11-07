---
ts: 2026-11-06T04:51:45Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG20x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_z9sbrSawT5t79KTvmTHJ
---
Same residual (a3 now at 19-20 due to more code before). So p's init is placed at the very end of the entry block regardless. The do-while makes the block end before p's store.

I wonder: what if we eliminate the do-while by making the D_800C7C64 store depend on the loads through a *real* semantic dependence that costs no insns? 

Idea: use the `idx`/`raw`/`val` variables in the store address in a way that simplifies to the constant. That's laundering.

Idea: reorder source so the D_800C7C64 store comes after the `and` but sched1 doesn't hoist because its source position (birth) is after... sched1 hoisted it in a1 because its priority was high. Why? Let me check gcc sched.c priority formula: priority = INSN_PRIORITY from the dependence graph = length of longest path to the end of block, weighted. The store's address computation (lui+addiu) has no dependents, so its priority is low (1). The lh has dependents (and, etc.) so higher priority. Then sched1 should schedule high priority first... yet it scheduled the store's address early. Hmm, maybe it's not sched1 but the "flow" pass or local-alloc spilling that produced the order.

Actually the instruction order after sched1 then sched2? GCC 2.7.2 at -O2 runs: flow, local-alloc, global-alloc, sched1, ... The final order is sched1's output. sched1 orders by INSN_PRIORITY (higher first) among ready insns. Let me check sched.c.

Actually, maybe it's the initial RTL order (birth) that matters, and sched1 preserves it when priorities tie. The birth order of the D_800C7C64 store: source order after val. In a1, sched1 moved it before the and/loads? Let's re-read a1: 
```
138 lui a0,0xffff      (mask)
13c ori a0
140 lui v1,D_800A2E20  (store addr)  <- born after val per source!
144 addiu v1
148 lui v0,currentLoc
14c lh v0
```
So the store address moved before the load of currentLocationId, even though currentLocationId's load is born earlier (source). That's sched1 reordering by priority. So the store address insns have HIGH priority. Why? Maybe because INSN_PRIORITY is computed backwards from block end; a store near the block end... no, the store is early.

Hmm wait — maybe in a1 the store's address is in a different block? No.

Let me look at sched.c to understand. But maybe faster: try to change the store's form so it isn't hoisted: e.g., store via a pointer variable `s32 **pp = &D_800C7C64; *pp = &D_800A2E20;` — adds insns.

Or store using a cast `*(s32 **)&D_800C7C64 = &D_800A2E20;` — same insns.

What if we declare D_800C7C64 as a local pointer variable? It's a global.

Hmm, let me reconsider the problem. Maybe there's a smarter restructuring: the target's structure could be reproduced if we reorder the *loads* to after the store address computation in source, i.e., make the store address born before the loads but scheduled after. No.

Let me try: swap the source order so `D_800C7C64 = &D_800A2E20;` comes right after `s32 *p = &D_800C7C60;` but before `id`. Already (orig). And sched1 hoists it.

What if we add a *real* dependence: make the store's value depend on `val` legitimately: `D_800C7C64 = (s32 *)((u32)&D_800A2E20);` no. 

What about storing `&D_800A2E20` but computed as `(s32 *)((u8 *)&D_800A2E20 + (idx & 0))`? laundering, not allowed.

What about using the loaded value in the store of D_800C7C64 in a way that's semantically required? It's not.

OK, different approach: can we get the target without needing the barrier at all by making the loads themselves later? The problem in a1 is the store hoisted above the loads. What if the loads are moved *earlier* than the store address in the final schedule? They already are in target. In a1, the store address is at 140 and the load at 148 — store before load. If we make the load's birth earlier (e.g., move the `currentLocationId` load before the mask in source?), sched1 might keep it early. Source order: mask first, then idx (load). Try moving the currentLocationId load to the top: `s32 idx = currentLocationId; s32 mask = ~0xF000; idx &= mask;` etc. Let's experiment with different source orders of mask/idx and see if a1's order flips without do-while.

Candidates g-batch (no do-while, just reorder):
g1: `s32 cur = currentLocationId; s32 mask = ~0xF000; s32 idx = cur & mask;`
g2: `s32 idx = currentLocationId & ~0xF000;` (no mask var)
g3: declarations with p first, then mask.
g4: `s32 mask = ~0xF000; s32 idx = currentLocationId & mask;` but the stores moved before the raw/val loads? no.

Actually the real question: what makes the store address high priority? Let me read sched.c quickly for the priority formula.
