---
ts: 2026-11-06T03:20:43Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG18x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_qnC23fyoRjMtSIvT8Tb9
---
Target:
- 52b4: lui v0; lw v0 (D_80126B78) → for the obj+0x14 computation
- 52c0: lhu a0,18(v0) — D_80126B78->unk12
- 52c4: lhu v0,20(a1) — obj->unk14
- 52d0: sh v0,20(a1) — the store
- 52d4: lui v0; lw v0 (D_80126B78 AGAIN) — for the unk2A store
- 52dc: lw v1,44(s0) — unk2C
- 52e0: lhu v0,18(v0)
- 52e4: bnez v1
- 52e8: sh v0,42(s0) — unk2A store (in the delay slot)

So the global pointer is loaded twice: before the obj store and after it. Mine caches it in a2.

Why does the target reload? Because the store to obj+0x14 (through a1 = obj) may alias the global pointer variable D_80126B78, so the compiler must reload D_80126B78 after the store. Wait — but in mine, the compiler loaded D_80126B78 ONCE into a2 before the store and reused it after. That means mine's cse decided the store can't alias the global (or didn't reload). Hmm, actually mine's sequence: at 18-20 mine loads `lui a2; lw a2; lhu v1,42(s0)` early — the global loaded into a2 before the obj store. Then after the store, it uses a2.

In the target, the global is loaded right before the obj computation (52b4) and again right before the unk2A store (52d4). The first load is AFTER the svec stores (52b4 vs the call at 5288). So the target loads the global late (not early), and reloads after the obj store.

In mine, the compiler hoisted the global load early (to 18-20, before the obj store) and reused it. Hmm.

The barrier in the target is between the obj store and the unk2A store, forcing the reload. Without it, cse could... wait, cse wouldn't hoist a load above a store unless it knows no alias. The global load in mine is at position 18-20, which is before the obj+0x14 store. The store to obj+0x14 could alias D_80126B78 (the global variable). If it could, the compiler couldn't hoist the load above the store... unless the load was already there (from the first use before the store).

Sequence in source:
```
obj = unk20;
*(u16*)(obj+0x14) += (unk2A - *(u16*)(D_80126B78+0x12));   // store to obj+0x14, load D_80126B78
[barrier]
unk2A = *(u16*)(D_80126B78+0x12);                          // load D_80126B78 again
```
The first D_80126B78 load is before the store; the second after. cse could forward the first load's value to the second IF it knows the store doesn't clobber D_80126B78. Since the store is through obj (unknown pointer), cse must assume it may alias the global → reload. But mine did NOT reload (it used a2) — so cse (or another pass) decided no alias, or the load was already hoisted.

Actually, mine's global load at 18-20 is early — before the obj store. And the use after the store uses a2. That means cse kept the value in a register across the store. This is a cse "memory not clobbered" decision: cse's `cse_insn` invalidates table entries on a store if `write_dependence_p` says the store may write the location. For a fixed global vs a varying pointer store, `fixed_scalar_and_varying_struct_p` may say the store doesn't clobber the fixed scalar if the stored MEM is not in a struct... The obj store is `*(u16*)(obj+0x14)` — a MEM not in a struct (a raw cast), so `fixed_scalar_and_varying_struct_p` says a fixed scalar (the global) is not clobbered by a varying non-struct store. Hence cse keeps the global value.

In the target, the global is reloaded → the original C must have made the store look like it could clobber. Hmm, or the barrier.

The barrier (memory clobber) forces cse to invalidate everything. Lever-free: make the obj store a *struct* store (MEM_IN_STRUCT_P=1), so cse's alias analysis says a varying struct store MAY clobber the fixed scalar global → reload! 

The store is `*(u16 *)(obj + 0x14) = *(u16 *)(obj + 0x14) + ...;` where obj is an s32 (a raw pointer). If we write it via a struct type, e.g. `((Unkstruct_800B5CB8 *)obj)->unk14 = ...` (if unk14 is at 0x14), the store becomes MEM_IN_STRUCT → cse's fixed_scalar_and_varying_struct_p would say the varying struct store may clobber the fixed scalar → invalidate → reload!

That's the classic lever mentioned in the TU comments: "gcc-2.7.2 sched alias (sched.c true_dependence) only lets a MEM_IN_STRUCT varying-address load hoist above a non-MEM_IN_STRUCT fixed-address store". Here we need the opposite: a struct store to force the cse invalidation.

Let me check: the store is to obj+0x14 as u16. `obj = ((Unkstruct_800B5CB8 *)a0)->unk20;` — obj is an s32 pointer. The target's store is `sh v0,20(a1)` where a1 = obj (32(s0) loaded at 5294).

Let me try: `((Unkstruct_800B5CB8 *)obj)->unk14 = ...` — does Unkstruct_800B5CB8 have a field at 0x14? Let me check the struct. Actually the code uses `*(u16 *)(obj + 0x14)`; the struct Unkstruct_800B5CB8 has fields unk12, unk16, unk1A... Let me look at the struct definition for an offset-0x14 field. Alternatively use a different struct type that has a field at 0x14, e.g., `Unkstruct_80181EA0_3`? Let me grep engine_types for a struct with unk14.

Simpler: define a local struct type? Can't add types outside the body? The constraint says no signature or decl change outside the body; a local struct definition inside the body is allowed? Hmm, "no signature or decl change outside the body". A local typedef inside the body is a body change. But it may affect codegen. Let's first try existing struct types.

Let me grep for structs with a field at 0x14 (unk14).
