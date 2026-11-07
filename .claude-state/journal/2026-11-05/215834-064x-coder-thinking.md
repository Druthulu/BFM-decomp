---
ts: 2026-11-06T04:58:34Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG20x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_STCGhDkl2ydIUrhghqpi
---
insn_dead_p: a MEM store is dead only if `rtx_equal_p(r, last_mem_set)` — i.e., a second store to the same location (store-after-store). So a dead store to a local slot: if we store twice to the same location with no intervening read, the first is deleted. But `last_mem_set` tracking handles that.

So to insert a store that cse sees (invalidating scalars) and flow deletes: store twice to the same location, the first one being the "invalidating" one? Both stores would be in the same block; flow deletes the first if the second writes the same MEM and nothing reads in between. The first store must have a varying address with QImode or non-PLUS to set cse's all=1.

Hmm, but cse runs BEFORE flow; both stores are present at cse time. The first (dead) store invalidates all scalar memory entries. Then the load `*p` for the call arg can't be forwarded from the store (mem D_80127524 -> reg 76). But wait — the store `*p = v0` happens BEFORE the first dead store. cse's table gets (mem D_80127524)->76; then the dead store invalidates it; then the load is not forwarded. 

Then flow deletes the dead store (if it can prove the second store to the same location makes it dead). But the second store must be to the same location — which we'd also want to be removed? No: we need a pair where the first is dead and the second survives... Actually flow's dead-store elimination: `last_mem_set` is the last MEM set seen; when a new MEM set equal to it appears, the previous is dead? Let me read the propagate_block code around 1208-1350.

Alternatively, simpler: use a local array store that's dead. E.g.:
```
u8 pad[4];
...
pad[0] = 0;    // QImode store to a fixed stack slot: cse sees a fixed address → invalidates only that slot, not global
```
Not enough. Need varying address.

What about `*(u8 *)((u8 *)pad + i) = 0;` where i is a variable. cse: addr = PLUS (reg, reg) → varying; mode QI → all=1. flow: can it delete it? The store is to a stack slot with a varying offset — `rtx_equal_p` won't match a later store; and the slot isn't "needed" tracked for MEM... insn_dead_p returns 0 for a MEM unless it equals last_mem_set. So flow would NOT delete it. Then we'd have an extra store instruction → wrong code.

Hmm. Unless the store is to a *register* that's dead. But a register store doesn't invalidate memory in cse.

Wait — maybe we can get cse to invalidate memory via a *call* whose result is unused? A call clobbers memory (invalidate everything). A call that is dead gets deleted by flow? insn_dead_p for a SET with SET_SRC CALL returns 0 (calls can't be dead) unless call_ok... `if (!call_ok && GET_CODE(SET_SRC)==CALL) return 0`. libcall_dead_p can delete dead libcalls (like a call whose result is unused and it's a pure libcall). `func_80138C30` is not a libcall.

What about a pure function call? gcc 2.7.2 has `-fno-builtin` here; calls to known pure functions? Probably not.

Alternative: use a store to a volatile? no.

Alternative: a dead store to a stack slot via a *plus with a register* but in HImode — cse would set nonscalar only (not all), not enough. QImode needed for all=1... unless the address is not PLUS: e.g., `*(u8 *)q = 0` where q is a pointer variable (bare register). cse: addr = (reg q) → varying and not PLUS → all=1. flow: the store is to (mem (reg q)); q's value unknown → not deletable.

Hmm, so any store that invalidates is not deletable by flow. 

But wait: what if the store is to a *dead local pointer target*? If q points to a local variable `s32 x; q = &x;` then cse can fold q to the stack address (fixed) — then it's fixed, not varying, and doesn't invalidate. If q's value is unknown, it's not deletable.

Different approach: make the *store* `*p = v0` not recorded in cse's table in the first place. cse records a store's dest→src mapping. Look at where it decides: `if (! do_not_record)`? For MEM dests, cse records into the table as a "constant/expression" entry? Let me look at how the store is inserted and what prevents it. Search around line 7100-7300 for "src_elt" insertion into the table for sets.

Actually, cse inserts the *destination* expression as a table entry with the source as its value (for loads: dest REG = src expr; for stores: dest MEM = src). Then a later identical MEM load is replaced by the src. If `do_not_record` is set (e.g., the src contains a volatile or is a MEM), it won't record.

We need the store's src to be "do_not_record" or the dest to not hash. If the store's src were a MEM expression, cse wouldn't record? But the src is reg 76.

Alternatively, make the stored value a *constant*? If the store is `*p = 0` (constant), then the later load `*p` would be folded to 0 (constant). Not our case; the value is a variable.

Hmm. What about making the *load* not a plain MEM: e.g., load with a different mode and then convert? The call arg is s32. If we load as `*(u32 *)p` — same SImode. If we load via a union or a struct... cse hashes MEM mode; same.

What if the load is from `p[0]` (array index) vs store `*p`? cse folds p[0] to (mem (reg p)) — same.

What if we write the call arg as `D_80127524` directly (symbol) while the store is `*p` (reg 75)? cse folds reg 75 to the symbol via REG_EQUAL, so both hash to (mem (symbol_ref)). Unless we can prevent the folding: if p's REG_EQUAL is lost. How to lose it? Reassign p after the store: `p = &D_80127524;`? That's the same. Or assign p from a computed expression that isn't constant-foldable... e.g., `p = (s32 *)((u8 *)&D_80127524);` cse folds casts.

Hmm, what if we declare p as `volatile s32 *`? That's a lever.

What about making the store use a *different* pointer variable that cse can't fold, while the load uses p? E.g., store through a pointer obtained from an opaque source. There's no opaque source.

OK, think about the barrier's effect from the scheduling side again. Maybe we don't need to prevent cse at all if we can get the register allocation to differ. The actual target has TWO reloads: one for the sh base, one for the call arg. In a1, cse forwarded the call-arg load to reg 76 (the stored value). The sh-base load stayed because... hmm, why did the sh-base load stay? Let me check cse1. Maybe cse1 forwarded the sh-base load too, and then something re-materialized it? No, the dump shows a real load at insn 57.

Let me look at a1.i.cse (cse1).
