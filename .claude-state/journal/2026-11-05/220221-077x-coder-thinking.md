---
ts: 2026-11-06T05:02:21Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG20x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_GhJUtxmv6yT6y369YYlc
---
All 12. Persistent.

Let me reconsider: maybe the crack is not about the call-arg reload but about the *register allocation* — if the stored value v0 were in a register that's not a0, then the copy `move a0, v0` would appear (1 insn) and the reload wouldn't. But target has the reload `lw a0,0(a0)`, which is 1 insn too, plus the nop. Hmm, but if cse forwards and reg 76 is assigned v0, then `move a0,v0` (1 insn) vs target `lw a0,0(a0)` + nop (2 insns). So 1 short.

Wait, maybe the difference could be made up elsewhere: if the move lands in a delay slot, no extra nop. In mine the sh went into the call's delay slot. Target has `lw a0,0(a0)` then `jal` with `nop` in the delay slot.

Hmm, what if we make the stored value live in a register other than a0 so the copy is emitted, and the sh can't go into the delay slot... that's still not the target.

Let me look at the a1 diff more carefully with the full asm to see the differences beyond the reload. Let me get the full diff (score 12 breakdown: register pairs v1->a0 x5, a0->v0 x4 = 9 + 3 hunk = 12?). The diff showed several replacements. The differences include the whole block's register assignment (v1 vs a0 for the pointer). Maybe if I get the pointer into a0, everything aligns.

The pointer p = &D_80127524: target a0, mine v1. In target, a0 holds p through the block. Why? Because in target, the call arg reload uses a0 (the call's first arg register). local-alloc assigns the load result to a0 (call arg). And p itself was allocated a0 earlier. Hmm, actually the pointer p and the call-arg load result are different pseudos but both got a0 in target (not simultaneously live: the reload overwrites p).

In mine, p is in v1 and the call arg is the stored value in a0.

So if we could make p land in a0... that's global-alloc. The moves list has "greg-pri-refs", "global-hardreg-reserve" etc.

Hmm. Maybe a different formulation of the whole function gets target. Let me think about what the original C (pre-lever) probably was, and what the barrier was compensating for. The barrier's only effect is preventing the cse forward (and the schedule). 

What if we make the *call* not be an indirect-cast call but a direct call? `func_80138C30(*p)` where func_80138C30 is declared `extern void func_80138C30(void *a0);` at the top. Currently the body casts `((void (*)(s32))func_80138C30)(*p)`. Target's asm is `jal func_80138C30` with the arg in a0. Using a direct call might change the argument handling? The cast to a function pointer with s32 arg vs the declared void* arg — the value is the same. Let me try calling it directly: `func_80138C30(*p);` — the declaration says `extern void func_80138C30(void *a0);`. Hmm, passing *p (s32) to void* — implicit conversion warning but compiles. Let me test.

Also try declaring the arg type differently.

Also try: `func_80138C30((void *)*p);`.

Let me test k1: direct call.
