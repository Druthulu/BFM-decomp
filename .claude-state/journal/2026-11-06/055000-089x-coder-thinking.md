---
ts: 2026-11-06T12:50:00Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG31y
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_nePrikU78HdILd0Nwy1l
---
So `writes->all = 1` requires a store with a varying address that is NOT (MEM_IN_STRUCT or PLUS) or is QImode. E.g. a store through a plain pointer variable (address = a REG, varying, not PLUS, not in_struct) → all = 1!

So a store like `*(u16 *)pq = 0;` where pq is a pointer variable (address is a plain reg) would set all=1 → invalidating the struct entries → the reload survives!

But adding such a store adds insns. Hmm, unless the store is one that already exists in the target: the `D_801F32D0 = 0` store — its address is a symbol_ref (not varying) → no.

What about the store `((Unkstruct *)param_1)->unk10A = idx;`? Address = `(plus (reg) (const))` → varying, PLUS → not all, nonscalar=1. So it invalidates struct entries — including the load? But the load is `in_struct` → `nonscalar && p->in_struct` → removed. So the load's memory entry is removed... but the *forwarding* still happened, so cse must forward through a different mechanism: cse's `cse_insn` for the store records the equivalence "the MEM equals the stored value" (src_eqv) — and later a load of the same MEM is replaced via that equivalence... but invalidate_memory removed it.

Hmm, actually cse processes insns in order: the store at line 117 inserts an entry for the MEM expression with the stored value? Then the load at 131... invalidate_memory is called for the store BEFORE processing it, so it invalidates prior entries, then the store inserts `mem -> value`. The load then finds it. That's store→load forwarding.

So to break it: the store must not be able to record the equivalence — e.g., if the stored value is not a simple register... or if the store's MEM can't be in the table.

Alternatively, put a *second* store between them that invalidates: e.g. a store through a plain pointer reg (all=1). What real store in this function has an address that's a plain register? `((Unkstruct *)param_1)->unkD8 = ...` — address plus. Hmm.

What about `func_8001C2C4(((Unkstruct *)param_1)->unk20)`? That's after.

Honestly, the lever-free path here is unclear and I'm at 22+ min. The best is 44.

Hmm, but hold on: the ORIGINAL had the asm at line 129 between the store (117) and the load (131). What if instead of an asm, we insert a real *call* or a real aliasing store... there's nothing free.

BUT: maybe there's another way to keep the reload: make `unk10A`'s load not be forwardable because the stored value is not the same value: if the C stored a *truncated* value, e.g. `unk10A = (s16)idx;` — the stored subreg would be `(subreg:HI (reg idx))` where idx is u16... same.

What if idx were declared as s32 (not u16) and the store `unk10A = idx` truncates: RTL `(set (mem/s:HI) (subreg:HI (reg idx) 0))`. The load `(set (reg:SI) (sign_extend:HI (mem/s:HI)))`. cse's store forwarding: it records the MEM equivalence to the stored *source*... In cse.c, the store forwarding mechanism is `src_eqv`/`src_eqv_volatile`: for a store, cse records `src_eqv = src` and then when a later load of the same MEM is seen, `src_eqv` is used. Since the store's src is a subreg of idx, the load result equals `(subreg:HI (reg idx))`. Then the multiply needs sign_extend of that subreg → gcc can combine into an extend of idx. So still forwarded.

To truly prevent: the stored value must be *unknown* relative to the load... 

Alternative: make the load NOT be from the same MEM expression: e.g. load through a `volatile`? no.

What if the load is from a *different field offset* that aliases? no.

OK. Let me step back and consider the budget: it's 05:52 now; item 2 started 05:30 → 22 min. Best 44, tries ~45. The remaining residual needs the cse memory-clobber replacement (a lever) plus the idx ref count.

I'll record this as a WALL. Tag: `cse-store-forward` already exists (walls.txt line 38: "cse forwards a loaded value the target reloads (G30x)") — here it's a store forward, but the closest existing tag is `cse-store-forward`. Let me use that (walls.txt has `cse-store-forward	cse1/combine	cse forwards a store into a reload and combine drops the dead store (G18x)`). 

Evidence ≤140 chars: "cse1 forwards the unk10A store into the reload (the asm memory clobber kept it); the idx ref-count lever (+1 ref -> pri 16000, takes $v0) also went with the same asm".

Now, wait. Before I finalize the WALL, one more consideration: the expert's message says PARTIAL rows require only the listed kinds kept. My best (44) keeps NONE of the kinds (no asm at all) — so it's a plain WALL with best = 44 (the best lever-free body). Good.

But hmm — maybe I should double-check whether the do-while-heavy w4 might actually be crackable with one more move on the cse issue. Let me think of a lever-free cse-breaker from the cookbook: C0414 "dead-reset cse-breaker" — a dead reset (`x = 0;` where x is dead) invalidates cse. E.g. `D_801F32D0 = 0;` is already a dead-ish reset (it's later set to 1 conditionally).

What about a dead reset between the store and the load: e.g. `tmp = 0;`? That's a register reset, not memory.

C0414's mechanism: "dead-reset cse-breaker" — e.g. `_pm2 = 0` after ReadRotMatrix empties the &m2/&m3 cse class so global.c rematerialises addiu per site. It's about register equivalence classes, not memory.

Hmm, what about: after the store, write `((Unkstruct*)param_1)->unk10A = idx;` a SECOND time? That would add a store insn.

What about writing the reload as `*(s16 *)((u8 *)param_1 + 0x10A)`? Same address rtx.

What if the load goes through a union type? e.g. a local union declared in the function:
```
union { Unkstruct_800B5CB8 s; u8 b[0x10C]; } *pu = (void *)param_1;
```
Then `pu->s.unk10A = idx; tmp2 = D_801ED5EC[pu->s.unk10A * 2];` — the MEM rtx is the same.

I think the memory-clobber replacement is not available lever-free here.

Decision: WALL for item 2, best 44 (w4). 

Wait — one more: what if I use `D_801F32D0 = 0;` moved between the store and the load? It's a symbol store (not varying) → doesn't invalidate struct entries. But it might still change sched. Cheap to test as one more try. Also try moving the `unk10A` store AFTER the tmp1 load (i.e. reorder: tmp1 load, store, reload) — that changes which store is between.

Actually the target's order is: store unk10A; sll; lh reload; ... So the store is before. Fine.

Let me do 2 final tries (D_801F32D0 moved, and idx as s32) and then write the WALL.

Actually time: 05:52. Let me do these two quickly (each ~15 s).
