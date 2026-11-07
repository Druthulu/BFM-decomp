---
ts: 2026-11-06T05:01:59Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG20x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_2AfKmKH7CIMYAxY16gRP
---
delete_dead_from_cse only deletes register sets, not MEM stores.

OK. New approach: maybe accept that a real-C dead store can't be deleted, and instead find a construct that makes cse's forwarding *harmless* to codegen. The target wants `lw a0,0(a0)` (reload). The forwarding gives `move a0, v0` (a register copy) instead. Since the stored value is the same, the reload is 1 insn vs the move 1 insn — same count! The difference: target has the reload, mine has the move? Wait mine has 45 vs target 47 — 2 fewer. Let me recount: mine has `(set (reg:SI 4 a0) (reg/v 76))` which after allocation may become a move (or be coalesced away if reg 76 is assigned a0). In the final asm, mine has no insn for it — the value is already in a0 (reg 76 allocated to a0). Target has `lw a0,0(a0)`.

So the difference is 1 instruction plus the load delay nop = 2.

Hmm, if reg 76 (the stored value) were allocated to a register other than a0, the copy `move a0, v0` would appear — still 1 insn, but not a load. Not matching.

OK, so we need the reload. cse must not forward.

Let me try: make the store's source a *call result* or something with do_not_record? `do_not_record` is set by volatile MEMs, PRE_INC, CALL, ASM_OPERANDS volatile, UNSPEC_VOLATILE. If the store's source expression contains a CALL, do_not_record → the store isn't recorded → no forwarding! And what call? There's none.

But what about storing the result of a *memory load with a side effect*? A volatile load would be a lever.

What about a PRE_INC address in the store? `*p++ = v0;` — the store's dest address is (mem (pre_inc p))? In C, `*p++ = v0;` — gcc emits the store with the post-increment handled separately (flow's auto-inc), not a PRE_INC rtx in the store dest usually. Actually for `*p++ = v0`, the RTL is a store to (mem (reg p)) plus a separate set of p = p+4, which flow may merge into an auto-increment. The store's dest would be plain. Hmm.

What about a store through a `register`-declared pointer? no.

What if the store is `*p = v0` where p is `volatile s32 *`? lever.

Hmm, what about making the store's source a *bit-field*? ZERO_EXTRACT dest → src_volatile=1 → no record. But that's the dest.

What about storing an expression that cse can't record because it has a MEM: the src `hash_arg_in_memory` is set but the store is still recorded with elt->in_memory from inner_dest (MEM) = 1 regardless. Hmm, src_in_memory doesn't prevent recording.

Wait, actually there's `sets[i].src_volatile`: set when do_not_record. Only volatile/CALL/PRE_INC etc.

Idea: use a function call to a *pure* builtin whose result is used: no.

Let me look at the problem from the "what C produced the original" angle: The original had the barrier because the decompiler needed it. The crack moves used elsewhere: for cse-store-forward, moves.md shows WALL for func_8013F1BC ("only a barrier/volatile stops it"). And for func_801902EC MATCH via reassignment killing the cse addr class. Also func_8018C2D8 MATCH via pointer reuse.

Here the store address is `(mem (reg p))` where p's equivalence is the symbol. If we make the *store* go through an address that cse hashes differently from the load, the forward breaks. E.g., store via `*(s32 *)((u8 *)p + 0)` — same. What if we store via a pointer whose value is computed at runtime in a way cse can't fold but codegen is the same? For instance, `s32 *q = p; *q = v0;` — cse's copy propagation makes q equal p (REG_EQUAL), folds. `s32 *q = &D_80127524;` same.

What if the store is through a *different symbol that aliases*? no.

Hmm, what about changing the *load* side: make the call arg load use an address that cse can't fold to the same MEM. The target asm loads from a0 = &D_80127524. If the C is `func_80138C30(*p)` the address is p. If instead `func_80138C30(*(s32 *)((u8 *)p + 0))` — same.

What if we introduce a second pointer variable that is assigned *from memory*: e.g., `s32 **pp = &D_80127524;`? Then `**pp`? The load would be via pp → cse folds pp to the address of the symbol... hmm, `&D_80127524` is a constant address, pp's REG_EQUAL is a CONST. `**pp` = load pp (folded to the constant address), then load that address — the address is a constant symbol address, same MEM.

What if the pointer comes from a global that holds the address? no such global.

OK, maybe try: assign p AFTER the sh store, i.e., recompute p between the store and the call:
```
*p = v0;
if (v0 != 0) {
    *(s16 *)(D_80127524 + 0x1A) = 1;
    p = &D_80127524;       // reassignment
    func_80138C30(*p);
}
```
The reassignment `p = &D_80127524` may kill the cse equivalence class of p (moves list: "reassignment kills the cse sym class"). But cse would still know p == &D_80127524 after the assignment (REG_EQUAL). However, the *store* entry is keyed on the MEM, not p. Hmm.

But wait: the store's dest in cse is `(mem (reg 75))` folded to the symbol; the load at 64 also folds to the symbol. Reassigning p doesn't change the MEM key.

Unless the load uses a different register p2 that cse assigns a *new quantity*; the MEM address would be (reg p2) with p2's REG_EQUAL = symbol → folded to symbol. Same.

Hmm hmm.

Let me look at this from the sched angle: maybe we can avoid cse's forwarding by making the load happen in a *different basic block* than the store's entry. The forwarding at insn 64 suggests cse follows into the block after the conditional jump. What if we make the `if` body a *loop* so cse_around_loop invalidates? i1 tried do-while(0) = still 12. Maybe cse1's loop handling didn't kick in for a zero-trip loop (flow removed the loop before cse?).

What about a real loop that executes once: `for (i = 0; i < 1; i++)`? gcc might unroll at RTL? No unrolling in 2.7.2. But loop.c would add overhead. Bad.

What about `switch`? A switch with one case might create a jump table/block boundary. Hmm.

What about putting the call in the `else` of the if? `if (v0 != 0) { sh; } else { } func(*p);` — no, the call is inside the if.

What if we invert the condition: 
```
if (v0 == 0) goto end;
sh;
call(*p);
end:
```
Target code has `beqz v0` to the end. The original C `if (v0 != 0) {...}` compiles to beqz to the skip label. Inverting to `if (v0 == 0) goto skip;` produces the same. But cse might treat the block differently? The call block would be the fall-through; cse follows fall-through and might still forward.

What if the call is after a `return` in the else? no.

Let me try some structural variants: 
j1: `if (v0 == 0) { } else { sh; call; }` 
j2: `if (v0 == 0) goto skip; sh; call; skip:;`
j3: put the sh and call in a nested `if (1)`? folded.
j4: `while (v0 != 0) { sh; call; break; }` — a real loop with a break; loop.c may simplify.

Let me test j1, j2, j4 quickly.
