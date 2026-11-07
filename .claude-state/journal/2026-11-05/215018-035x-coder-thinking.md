---
ts: 2026-11-06T04:50:18Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG20x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_Raw2bvR8bwIFZ102SRgJ
---
d2 has extra residual. b1/b10 remain best at 5.

Let me think about the ori issue differently. In target, ori comes right after lui. In mine, lh comes between. This is sched1 ordering of two independent chains. The `sw ra,16(sp)` position also differs (mine at 148 before and, target at 150 after a3 setup).

Maybe the issue is the function's prologue: `move a1,a0` at 134 both. Then mine: lui v1; lui v0; lh v0; ori v1; sw ra; and... Target: lui v1; ori v1; lui v0; lh v0; lui a3; addiu a3; sw ra; and.

Since target's order is essentially source/birth order (mask const first, then currentLocationId load, then p address, then ra save, then and), and mine deviates, maybe the do-while block split changes sched1 priorities (block number affects priority).

Alternative idea: avoid do-while; instead prevent the D_800A2E20 hoist by giving the store a dependence on `val` that is real and codegen-neutral... The store value is `&D_800A2E20`. What if we store `(s32 *)((u8 *)&D_800A2E20 + (val - val))`? identity launder — forbidden.

Hmm, what about making the D_800C7C64 store part of the same statement as *p = val? e.g., comma operator: `(D_800C7C64 = &D_800A2E20, *p = val);` — gcc emits same insns; scheduling might differ? Unlikely.

What about using a conditional: `if (val == val) D_800C7C64 = ...` no.

Let's reconsider: maybe the crack isn't about blocking the hoist; maybe it's about making the register allocation match regardless of order. The residual with a1 (score 17) had mask in a0 and D_800A2E20 in v1. If we could get mask into v1 and D_800A2E20 late... 

What if we declare `mask` as a *pointer* or use it differently? Hmm.

Another thought: use `s32 mask = ~0xF000; s32 idx = currentLocationId & mask;` and reorder declarations: put `s32 *p = &D_800C7C60;` before mask? Then birth order changes: p's address setup born first. Target has mask first though.

Let me try a batch of declaration-order permutations with the do-while around the stores (b1 style), since b1 has the right register assignment and only scheduling differs. Maybe one permutation makes sched1 produce target order.

Variants:
e1: move `s32 *p = &D_800C7C60;` declaration before mask.
e2: move `s32 id;` earlier.
e3: declare p uninitialized and assign after the loads but before the do-while.
e4: put the do-while around the stores with `p` init inside but also move `id` computation inside? no.

Actually, maybe the a3 setup placement is tied to the `p` init's birth position relative to the block. In target, p init is born in the entry block (source: after val). In mine (b1), p init is also source after val, but the do-while creates a new block starting at D_800C7C64; p init stays in the entry block. sched1 then can place it anywhere in entry block; it chose late (after loads). Target placed it at insn 6 (before and) because... in target, no do-while, so the entry block includes everything; sched1 priority put p init early.

Hmm what if the p init is *used* in the same block: if the do-while block is the same block... 

Alternative: what if instead of do-while we use a different real-C construct that blocks the store hoist but doesn't split the block before the ori: e.g., `if (1) { stores }`? gcc folds if(1) at the tree level, so no barrier.

What about `while (0) {}` placed... no.

Hmm, what about making the stores volatile-free but through a pointer that the compiler can't prove... 

Actually, let's revisit: do we even need the loads to precede the stores in the final schedule? Target order is what matters. Could we get target's exact order with a *different* C that doesn't need a barrier? The target order is the natural birth order. Maybe a1's problem is purely register allocation: mask in a0 instead of v1, and the D_800A2E20 address hoisted. What if we force the mask into v1 by using it later? E.g., if mask were used again after the loads... no, identity.

Let's look at a1's asm more: 
```
130 addiu sp
134 move a1,a0
138 lui a0,0xffff
13c ori a0,a0,0xfff
140 lui v1,D_800A2E20
144 addiu v1
148 lui v0,currentLocationId
14c lh v0
150 lui a3,D_800C7C60
154 addiu a3
158 sw ra,16(sp)
15c lui at,D_800C7C64
160 sw v1,0(at)
164 and v0,v0,a0
...
```
Target:
```
134 move a1,a0
138 lui v1,0xffff
13c ori v1,0xfff
140 lui v0,currentLoc
144 lh v0
148 lui a3,D_800C7C60
14c addiu a3
150 sw ra
154 and v0,v0,v1
...
174 lui v0,D_800A2E20
178 addiu v0
17c lui at,D_800C7C64
180 sw v0,0(at)
```
So target defers the D_800A2E20 address to after the D_800D34AE load (174), whereas a1 hoists it to 140. And mask in v1 vs a0: because a0 is used for the cdFileLocTable pointer later? In target a0 is free at start, v1 holds mask. In a1, a0 holds mask and v1 holds D_800A2E20.

If we prevent the D_800A2E20 hoist, local-alloc naturally gives mask v1. So the barrier/do-while does that. The residual is ori/a3 order.

Could we instead force the D_800A2E20 address computation to be textually later AND make sched1 not hoist by giving it a dependence on `val`? What if the D_800A2E20 store is written as part of the `*p = val` statement with a comma or as two stores to p? No.

Hmm, what about making the D_800C7C64 store depend on `raw`? e.g. write `D_800C7C64 = &D_800A2E20;` but compute the address as `(s32 *)((s32)&D_800A2E20 + (raw & 0))` — launder, forbidden.

Wait, maybe reordering *source* so the D_800C7C64 store is after `id = raw & 0xFFF;` and the loads, and then sched1 hoists it... we tested b3 = 17, so it hoisted.

What about placing the D_800C7C64 store inside the `if`? No, changes semantics/flow.

OK, maybe accept 5 and try to fix the sched1 order with other real-C moves. The order issue: mine has lh between lui and ori. What if we compute `idx` using a temp that delays the lh? E.g., `s32 cur = currentLocationId; s32 idx = cur & mask;` — adds a load? `cur = currentLocationId` is a lh; then and. Same insns maybe.

What if mask is computed *after* idx in source but used... no.

Let me try:
e1: `s32 mask = ~0xF000; s32 idx = currentLocationId & mask;` but with the do-while around stores and `p` declared first (before mask).
e2: mask as `s32 mask = 0xFFFF0FFF;` (same).
e3: `u32 idx = currentLocationId & mask;`
e4: `s32 idx = currentLocationId & ~0xF000;` with do-while.
e5: swap the order: idx declared before mask: `s32 idx = currentLocationId & ~0xF000; s32 mask...` can't.
e6: Use `(s16)currentLocationId & mask`?
e7: `s32 idx = (s32)currentLocationId & mask;`

Also try the do-while placed *before* the declarations? Not possible.

Actually here's another thought: the `sw ra,16(sp)` (prologue save) is a scheduler anchor. In target it's at 150; in mine 148. Fine.

The ori: target forms mask before the load; mine after. This is one insn moved. The a3 setup: target early, mine late. Both are sched1 priorities. Since both differ in the same direction (target does constant/address setup earlier, mine delays them behind the load), maybe if we reduce the "priority" of the load chain... e.g., make the load's result needed later? The load currentLocationId feeds and->idx->addresses. 

What if we reorder the source: `s32 idx; ... idx = currentLocationId & mask;` after the other loads? No, raw/val depend on idx.

Try `s32 mask = ~0xF000; s32 idx = mask & currentLocationId;` (operand order) — might change RTL and scheduling. Also `s32 idx = currentLocationId & mask;` with mask first.

Let me test a batch of these micro-variants with the do-while.
