---
ts: 2026-11-06T04:49:34Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG20x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_ahMyAx5ElhEQUNPrHhnP
---
All the same residual. The a3 setup is late in mine, early in target. And ori.

Hmm. Wait — target's a3 setup early is because in target, p is used in the store at 18c which is in the delay slot of bltz. sched1 placed the p address setup at 148. 

Maybe the actual issue is the do-while creates a separate basic block, so p's init insn is in block 0 and use in block 1, and sched1 in block 0 schedules it late (it doesn't matter). While target has no block split, so sched1 places it by priority early.

So maybe we need a construct that blocks the D_800A2E20 store hoist but does NOT create a basic-block split... but any control-flow construct splits blocks. Hmm.

Alternatively, can we block the hoist via a data dependence instead? Consider: the D_800C7C64 store value could legitimately depend on something loaded. In target, value = &D_800A2E20. What if we write the store after computing an address that depends on a loaded value? Not allowed to change semantics.

But wait — maybe the hoist isn't the problem; the problem is register allocation of mask (a0 vs v1) and the D_800A2E20 address. Let me reconsider a1's diff: mask in a0, D_800A2E20 addr in v1. With do-while: mask in v1, D_800A2E20 late in v0. So the do-while fixed those. The remaining is just sched1 order of ori and a3.

Could a different move fix sched1 order? The ori/a3 ordering: target ori immediately after lui (contiguous constant formation) and a3 setup right after lh. Mine: lh between lui and ori; a3 setup after two loads.

Idea: form the mask constant in a way that produces `li`? ~0xF000 = 0xFFFF0FFF. lui+ori required.

What if mask is used as an `andi`? No, 0xFFFF0FFF needs lui/ori.

What if we make the mask's use immediately after its definition in source: e.g., `s32 mask = ~0xF000; s32 idx = currentLocationId & mask;` — source already.

The scheduling: sched1 orders by "priority" = insn number (birth). lui mask, lui currentLoc, lh, ori? Why would ori be born after lh? The RTL birth order: `mask = ~0xF000` becomes lui+ori. Then `idx = currentLocationId & mask`: lh, and. Birth order: lui, ori, lh, and. So source/birth order gives ori before lh! But mine has lh before ori — sched1 moved it. Target has ori before lh (birth order preserved).

Hmm, why does sched1 move ori after lh in mine? Maybe because of the do-while block split affecting priorities. In target (no split), ori stays before lh.

Wait, but a1 (no do-while) also had a different order: a1 was lui a0(mask); ori; lui v1(D_800A2E20); addiu; lui v0 currentLoc; lh... Let me re-check a1 dump: 
```
138 lui a0,0xffff
13c ori a0,a0,0xfff
140 lui v1,D_800A2E20
144 addiu v1
148 lui v0,currentLocationId
14c lh v0
```
So in a1, ori came right after lui (good) but the D_800A2E20 address was hoisted (bad).

So target = a1's ori order + no D_800A2E20 hoist. With do-while we got no hoist but ori order changed.

Maybe a different construct blocks the D_800A2E20 store hoist without splitting the block where mask is computed. What if the D_800C7C64 store is in a do-while, but the mask/idx computations are also... hmm.

What if we move the D_800C7C64 store to AFTER the `and` and loads, i.e., source order, and block its hoist by making it depend on `raw`? For example: `D_800C7C64 = &D_800A2E20;` could be placed right after `s32 raw = D_800D34AC[idx];` — sched1 could still hoist it above the load because independent.

What if the pointer store value is computed from a local variable that is initialized from a load: `s32 *q; ... q = &D_800A2E20;` no dependence.

Hmm, what about combining: use `p` for both stores? Target stores D_800A2E20 into D_800C7C64 with at register; and D_800C7C60 with a3.

Let me think about the barrier's real effect once more. `asm volatile("" ::: "memory")` creates a fake insn with memory clobber. In sched1, it acts as a barrier: insns before it can't move after, and vice versa. In target, the barrier is right after the declarations, i.e., BEFORE the two stores but AFTER the loads? No! The loads are initialized in the declarations: `s32 raw = D_800D34AC[idx]; s32 val = D_800D34AE[idx*2];` are before the barrier. So the barrier separates the loads (before) from the stores (after). That's exactly why the stores can't be hoisted above the loads, and the mask/idx (before) schedule as in a1.

So we need a memory barrier between the loads and stores in real C. Options that gcc 2.7.2 treats as memory clobbers: a function call to an opaque function. But that adds a call. Unless the call is to a function that... hmm.

What about a volatile memory access? `volatile` is a different lever probably. But is volatile explicitly forbidden? The brief: "Lever-free = none of the row kinds in <dir>/kinds remain: no pin, launder, barrier, keepalive macro or asm; no new lever of any kind." A volatile store/load is a classic lever (volatile access as a barrier). "no new lever of any kind" — volatile would be a new lever kind. So no.

What about a pointer with a cast through a different type to force a memory clobber? No, alias only.

Hmm, but maybe we don't need a barrier at all — maybe a different arrangement of the C yields the same schedule without blocking. The issue is sched1 hoisting the D_800A2E20 address+store above the loads. Why does sched1 hoist it? Priority: the store's birth is later (source), but sched1 uses REG_N_REFS/live length priority. The store insn has priority... Hmm.

What if we restructure so the D_800C7C64 store is textually before the loads? Then target order? No, target has it after.

Let me try: make the D_800A2E20 store's address come from a register that's already needed... 

Another approach: reorder so that `p = &D_800C7C60` and the D_800C7C64 store appear in a *loop* that runs once — the do-while. We tried. The block split changes ori order.

Could we put the whole function body in a do-while? Then the entire body is one block (entry + loop body), and the split occurs after everything. Let's try: 
```
void f(s32 arg0) {
  extern ...
  do {
    ... entire body ...
  } while (0);  // !FAKE: do-while
}
```
But there's a `return` inside the if — return inside do-while is fine. Would that preserve ordering? The block split at the end. Maybe sched1 then keeps the body order as target. Let's test d1.

Also maybe wrap only the declarations+loads... Let's test d1.

Also d2: wrap the part from `D_800C7C64 = ...` through the end (including the if/return) in do-while.
d3: put do-while around the loads (raw,val) so they're a block, then stores after.

Let me try.
