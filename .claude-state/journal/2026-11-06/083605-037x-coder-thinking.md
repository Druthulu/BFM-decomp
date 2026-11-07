---
ts: 2026-11-06T15:36:05Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO05
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_K4MyONHqdNw9KkQISxUQ
---
Same. So gcc always materializes &sym+24 once. Need to make the address not constant-foldable per site.

Key insight: the launder makes mb unknown, so `mb + 0x18` is a register add. To replicate in plain C, we need mb to hold the address in a register but not be known as a constant to cse. Is there any plain-C way? 

What if mb is assigned from a memory load, e.g. a global variable containing the address? That changes the object (extra load) — target has no load. No.

What if the base pointer is a function parameter? Not here.

Hmm, wait. Maybe the target's base s0 is not &D_800AF630 but something else... no, lui s0 with R_MIPS_HI16 D_800AF630.

Let me reconsider: target computes s0=&D_800AF630 then addiu a0,s0,24 twice. The launder achieves this because after the asm, mb's value is unknown but the register holding it is the same register (asm tied "0"). So gcc knows the *register* has the address? No — the asm produces a new value in the same register, so gcc considers it unknown, but it's physically the same. So `mb + 24` must be an add.

In plain C, we can get the same by ensuring the register holding the base is not treated as a constant. One way: use the address of a local? No.

Another thought: maybe use a union/pointer variable assigned via a cast from a runtime value that happens to be the address — no.

Could we instead restructure so the target's addiu comes from a different source? The target is fixed; we must produce addiu a0,s0,24.

What if we write `func_8004914C((u8 *)&D_800AF630 + 0x18)` but make the compiler keep the base in a register by using the base *elsewhere* after both calls? E.g. use mb (base) again later, forcing the base (not the sum) to be live, and then the sums are computed per call? Let's think: if we use `mb` (base) later, say `D_800AF630[0] = mb[0]`? Hmm, that adds code.

Actually the issue is cse's constant folding: mb is a constant, so `mb+24` folds to a constant expression. If the sum is a constant, gcc will materialize the constant once (s0=&sym+24) and reuse across the call. To get base+24 per call, the add must not be constant-folded. 

Plain-C way to prevent constant folding of `mb + 0x18`: make the offset unknown. E.g. `mb + (u32)param_4 & 0` no (identity). Hmm.

Wait — maybe there's another way: what if mb is a `u8 *` set to &D_800AF630 and we do the addition in a context where gcc doesn't fold: `(u8 *)((u32)mb + 24)` — combine folds to constant. Same.

Let me look at what the moves say about a similar case: line 44: "launder: p = *abase; p += 0x2D (self-reassign stales cse (plus p K) equiv, bump chain stays addiu)". In that case p was loaded from memory (not constant), so self-reassign works. Here mb is constant.

Hmm, is there another technique: "C0414 dead-reset cse-breaker". Let me read C0414 cookbook.

Let me grep cookbook index for cse-breaker/dead-reset.
