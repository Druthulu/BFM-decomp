---
ts: 2026-11-06T03:04:22Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG18x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_g1EBBYep0mLggx6FsXQl
---
Combine runs after cse2. So combine deleted the first store (store-to-store elimination: `combine` has `try_combine` and also the `delete_noop_moves`? Actually the pass at 3004 is combine_instructions; it can merge the store+load? The .combine dump shows the store gone and the addiu using 135. Combine's `try_combine` merged the store and the load? Hmm, combine works on 2-3 insns: insn 178 (store mem28 <- 135), insn 181 (reg136 <- mem28), insn 183 (reg137 <- reg136 - 1). Combine could merge the load into the ALU and then the store... Actually the load 181 was already forwarded by cse1 (in the .cse dump the load was gone: insn 183 used 135). So combine deleted the now-dead store 178? Combine's `combine_instructions` calls `try_combine` and also deletes insns that become dead (`delete_dead_from_cse`? no). Hmm.

Anyway: combine removed the dead store to memory. So combine DOES delete a dead store to memory when its value is overwritten by a later store to the same address (store-to-store elimination in combine).

For our `flag = 0` store: is there a later store to flag? No. So it survives.

What if we make the flag store's value the SAME as the later unk1C store... different address.

What if the cse-breaker store is to `unk1C` with the value that the *final* store will write? That's exactly the dead store elimination pattern: `unk1C = X; ... unk1C = Y;` — combine removes the first store if X's value is not used. But then the target's first store (unkDC) would also be removed (it's the same pattern). Hmm.

Wait, actually — the target HAS `unk1C = unkDC; ... unk1C = unk1C - 1;`. The first store is NOT dead in the target because the second store's value depends on the loaded unk1C! The load reads the stored value. Without cse forwarding, the first store is needed. With forwarding, it's dead.

So the cse-breaker must prevent the *load* from being forwarded, and then the store is needed. The `flag = 0` store does that (score 1) but survives.

Can we make the `flag = 0` store *dead*? It writes flag, which is never read after. The compiler doesn't know? flag's address is taken, so the store must be kept (the compiler can't prove nobody reads it via the pointer). If we use a local that is NOT address-taken, the store is a pseudo set (no memory invalidation).

What if we use a local whose address IS taken but whose store is later overwritten by another store to the same address that combine can eliminate? E.g.:
```
flag = 0;     // cse-breaker
...
flag = 1;     // later store; combine sees store-store and removes the first!
```
Then the first flag store is dead and combine removes it. But the second `flag = 1` store would remain (unless also removed). Where to put the second store? It must be after the first and before... it would add an instruction unless it's also dead. If both are dead and to the same address, combine removes the first but keeps the last (the last dead store remains). ✗

Unless the last store is to a location that combine can prove dead? No.

Hmm, what about making the flag store *not* a memory store but still invalidating cse? What if we store to a local that is a struct/array element whose address is taken... same.

What if the cse-breaker is a store to a *global* whose value combine can fold? no.

OK, what about a completely different approach: make the *load* not cse-forwardable by giving the store a REG_EQUAL note that differs... The store's value is the loaded unkDC (pseudo 135). The load of unk1C gets forwarded to 135. If the store's source were a *different pseudo* than the load's source... it's the same value.

What if we write:
```
((Unk*)arg0)->unk1C = ((Unk*)arg0)->unkDC + 0;
```
The front end folds +0. What about `((Unk*)arg0)->unk1C = ((Unk*)arg0)->unkDC * 1;`? Folds.

What about storing a value that the compiler computes differently, e.g., `unk1C = (s32)(u32)unkDC;`? Same.

Hmm, what about making the *store* go through a different MEM expression that cse can't match to the load, but combine can still see the store as needed and codegen emits `sw v0,28(s1)`:
- Store via a pointer variable `p = &unk1C`: the address is (reg p); the load via the struct (plus s1 28). cse: the store's address (reg p) and the load's (plus s1 28) are different expressions; cse's memory invalidation uses `write_dependence_p` which compares MEMs: a store to (reg p) may alias the load (plus s1 28) since p is unknown → the load's table entry is invalidated → no forwarding! Then reload folding might turn `(mem (reg p))` into `sw 28(s1)` if p = s1+28 is folded. h5 tested a pointer to the field for the *decrement* (load side) — 105. Let me try the pointer for the STORE side (h3/h4 did; 105). Hmm, both failed.

Why did h3 (store via a pointer) fail? Maybe because the pointer assignment `p = (s32*)(arg0+0x1C)` was folded by the front end/cse into the address, making the store's address equal to the load's.

Let me test a *global* pointer: no.

Hmm, what if the store is via a function-like opaque? no.

What if the load is via a pointer variable that is *reassigned* to break cse's equivalence: 
```
u8 *p = arg0;
unk1C = unkDC;       // via arg0
p = 0;               // dead reset of p (register) — C0414
... 
((Unk*)p)->unk1C -= 1;  // p is 0?! no
```
No.

OK, let me try one more class: use `sp10` as the cse-breaker with a store that is later overwritten by the GTE asm? The GTE ops are before. No.

Let me try: store to flag, then *load* flag? A load doesn't help.

What about making the flag store part of a `do-while` so it's... no.

Given the time, let me consider: i2 score 1 — the only residual is one extra `sw zero,24(sp)` in the load-delay slot. What if we place the dead-reset store so that it fills a delay slot that the target leaves as a nop? The target has `lw v0,28(s1); nop; addiu` — the nop is the load delay. Mine has the store there. If the store were placed elsewhere... but any placement is an extra instruction (108 vs 107). The target is 108 ins; mine with the store is 108 (the store replaces the nop). So mine has the same count but the wrong instruction (store vs nop).

So if we can make the store *be* the nop... impossible. We need the store gone.

Hmm, what if the dead-reset store is scheduled into a place where the target also has a real instruction that we could... no.

What if the dead-reset is a store to a location whose store is combined with a *later* store in the target: the target's final store is `sw v0,28(s1)`. If our dead-reset store were to 28(s1) with the value v0... that's the store we need! Wait:

Sequence: `unk1C = unkDC;` (store A) then we need the load to not forward. What if instead we write:
```
unk1C = unkDC;
unk1C = unk1C;      // redundant store of the same value? cse removes
```
Hmm.

Actually, here's a thought: what if the cse-breaker is a store to unk1C of the SAME value (unkDC) *between* the store and the load? Then:
- store A: unk1C = unkDC
- store B: unk1C = unkDC (same value)
- load: unk1C
cse: after store B, the memory entry is unkDC (same); the load forwards to unkDC → no reload. ✗

What if store B stores a *different* value, and the load reads it, then... that changes semantics. ✗

OK. Let me look at the problem from the ORIGINAL source's likely form once more. The target has a redundant store+load, which gcc would normally optimize away. The reconstruction added a barrier. Maybe the original C had a `volatile` on unk1C? That would be a lever (volatile). Not allowed.

Or maybe the original C accessed unk1C via two different *struct types* where cse's alias analysis failed. Hmm.

Let me try: store via `Unkstruct_80181EA0` (the struct type) and load via a *different* struct type that has a field at 0x1C, e.g. `Unkstruct_800B5CB8` (used elsewhere in the TU). The offsets differ? unk1C in Unkstruct_800B5CB8 is at 0x1C too (the same struct layout). Let me try: store via `((Unkstruct_80181EA0*)arg0)->unk1C` and decrement via `((Unkstruct_800B5CB8*)arg0)->unk1C`. Both MEM_IN_STRUCT with offset 28. cse compares the MEM rtx: both `(mem/s:SI (plus reg 28))` — identical → forwarded. Unless the struct types have different alias sets (gcc 2.7.2 has no alias sets based on types, just MEM_IN_STRUCT_P). So same.

What if one access is via a `u8*` cast (not in-struct) and the other via the struct (in-struct)? The MEM rtx differs in MEM_IN_STRUCT_P, but rtx_equal_p ignores flags... Actually, cse's `exp_equiv_p`/`rtx_equal_p` might compare MEM_IN_STRUCT_P? In gcc 2.7.2, `rtx_equal_p` compares only the format fields, not the flags. But cse's memory invalidation uses `true_dependence`/`write_dependence_p` which DO consider MEM_IN_STRUCT_P (the `fixed_scalar_and_varying_struct_p` stuff). Hmm, but forwarding is a table lookup by address expression; if the addresses are rtx_equal, the table finds the entry.

Hmm, but the *load* in the target is `lw v0,28(s1)` and the store `sw v0,28(s1)`. So both are plain.

Let me try the different-struct-type idea anyway (cheap), plus a few more:
k1: store via Unkstruct_800B5CB8, load via Unkstruct_80181EA0.
k2: store via a u8* cast: `*(s32*)((u8*)arg0+0x1C) = unkDC;` load via struct.
k3: store via struct, load via u8* cast.
k4: store via `*(s32*)(arg0+0x1C)` (not in-struct), load via struct.
k5: store via struct, load via `*(s32*)(arg0+0x1C)`.
k6: `unk1C = unkDC` then `((Unk*)arg0)->unk1C = ((Unk*)arg0)->unk1C - 1;` (same).

I tried g2/g4/h6/h7 similar. Let me try the mixed in-struct/non-in-struct forms, since cse's memory table invalidation uses alias info.

Actually g2 (`*(s32*)(arg0+0x1C) -= 1;`) → 105. So mixed didn't help.

Let me try one more: make the load go through an `s16` read plus... no.

Time check: item 3 ~40 min. I have i2 at score 1 — a genuinely promising crack. Let me try to eliminate the extra store with a few more ideas:

l1: `flag = 0;` but make flag's store dead by *not taking flag's address*: the address is taken by gte_stflg(&flag). Can't change.
l2: Use a different address-taken local: sp10. `sp10[0] = 0;` → survived (109, i3 score 7).
l3: Use a store to a *global* that combine folds? no.
l4: Put the dead-reset store *inside* a `do-while` with the load, so combine/cse might... no.
l5: Use `flag = 0;` and then make the *decrement* use flag? no.

What about the store to flag being combined with the *existing* gte_stflg store to flag? gte_stflg(&flag) happens early; our store is later. No.

Hmm, what if we put the cse-breaker store to flag BEFORE the loop (inside the else branch, before the loop) — then it's before the first store, so it wouldn't break the store→load forwarding. ✗

What if the cse-breaker store is placed between the store and the load but is a store to a location that the *target's own code* overwrites later: `flag` is not.

Wait — what about `sp10`? The target's code: gte_stsxy(sp10) writes to sp10 early. After our region, func_801820E4(arg0) is called — a call may write to sp10 (the callee's stack frame overlaps sp10? No, sp10 is in this function's frame; a callee's frame is below sp).

OK, another idea: make the cse-breaker store a store to a *pseudo-backed* memory location that flow removes: what about a local `s32 z` whose address is taken by a dummy `&z`? Then it's memory-resident; the store survives. ✗

What about a store to a *union/bitfield* that combine turns into a no-op? no.

Hmm, what if we use an *assignment to a struct field that is later overwritten by the epilogue*? no.

Let me try the dead-reset with a store to a location that combine deletes as a "store of the same value": e.g., `D_800AF7BE = D_800AF7BE;`? A load+store of the same global; cse might remove the store as redundant. And the load would be an extra instruction. Hmm.

What about `D_800AF7BE = D_800AF7BE + 0;`? same.

What about storing a constant to a global that is already known to have that constant? The compiler doesn't know.

OK, let me try one clever thing: make the cse-breaker store the *store that the target already has* by reordering: the target's final store (unk1C = v0-1) is at 20ac, shared with the bnez path. The bnez path's delay slot has `addiu v0,v0,-1`. Hmm.

What if we put the cse-breaker store AFTER the decrement? Then it wouldn't break the forwarding.

I think item 3 is a WALL, but i2 at score 1 is close. Let me try ~6 more variants targeting the extra store, then decide.

m1: `flag = 0;` inside a do-while with the load: `do { flag = 0; unk1C -= 1; } while (0)`.
m2: `flag = 0;` and then `flag = 0;` again (same value twice) — maybe cse removes both? Or combine removes the first.
m3: `flag = 0;` then after the decrement `flag = 1;` (to make the first store dead; the second might be removed as dead by flow? no).
m4: use `sp10[0] = 0;` and `sp10[0] = 0;` twice.
m5: `flag = 0;` placed immediately before the load, then `flag = flag;` after (redundant).
m6: `flag = 0;` with flag's value later used: e.g., `if (flag) ...`? adds a branch.

Let me test m1, m2, m3, m4.
