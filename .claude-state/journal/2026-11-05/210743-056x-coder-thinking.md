---
ts: 2026-11-06T04:07:43Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG20
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_zQIkMMHhrRxjI4tQk0rI
---
Interesting: c5 changed the first load to `lhu v1,46` + sll/sra (sign extension) because x = t (s32) forced the s16 to be widened at assignment? Actually `x = *(s16*)` where x is s32: the load is HImode then sign-extend to SImode. In the original, `diff -= *(s16*)` let the compiler do `lh` directly (sign-extended load). With x being used as s32 and assigned, the compiler did `lhu` + shifts? Weird: it emitted lhu then sll 0x10, sra 0x10 — that's a sign extension from u16? Hmm.

This is because x's type is s32 and the load is s16; normally that's `lh`. But cse/combine chose lhu+sll+sra? Odd. Actually the first load is `lhu v1,46(s0)` then sll/sra — sign-extend. That's what GCC does when it wants to zero-extend then sign? Whatever, it's worse.

But importantly, the second load is now TWO loads? The diff shows mine has `lhu v1,46` at 37 (sign-extend) and another at 42? Hmm.

Let me step back and think about time. This is item 2; budget 20-30 min per item. I've spent ~15 min on it. Let me consider whether this is a WALL.

But before that, let me try the most plausible original C: maybe the first access is `*(s16*)((s32)s0 + 0x2E)` and the second is `((s16 *)((s32)s0 + 0x2E))[0]`? same.

Let me examine the ORIGINAL function's ROM behavior: the double load could be explained if the source had the second access as `*(s16 *)((s32)s0 + 0x2E)` inside an expression that also *stores* something to memory via a pointer, making cse invalidate. The `+=` store to 0xE is such a store! If the source order were:
```
x2 = *(s16*)(s0+0x2E);
*(u16*)(s0+0xE) = *(u16*)(s0+0xE) + (x2<<6);
```
store after. But what if the source did:
```
*(u16*)(s0+0xE) = *(u16*)(s0+0xE) + (*(s16*)(s0+0x2E) << 6);
```
still store last.

What if the original had TWO statements writing 0xE:
```
*(u16*)(s0+0xE) += 0;          // store invalidates the 0x2E load entry
x2 = *(s16*)(s0+0x2E);
```
No, adds a store.

Hmm, the target has no store between.

Let me look at the `lh v0,46(s0)` at 77cc: is it possible this load is NOT a C-level load but part of the `lh` for the `diff` expression, and the second `lh` at 77d8 is a **reload of a spilled pseudo**? No stack spill visible.

Actually! Maybe the second `lh` is a reload because the first load's value register (v0) is **clobbered by the `lhu v1,14(s0)`**? No, different reg.

What if cse DID forward, producing `x2 = x1` copy, and then **global_alloc assigned x1 and x2 to the same register and the copy was optimized away**... that gives one load (baseline). So no.

Let me try: make the first load's value live across a call? no call.

New idea: use a **pointer to the field** and make the two accesses through pointers that cse cannot equate because one is `s16*` and the other is `u16*`... mode same.

Hmm, what about **different MEM alias sets**? GCC 2.7.2 doesn't have alias sets (that's 3.x).

What about `MEM_IN_STRUCT_P` — we saw exp_equiv_p ignores it, but the HASH includes it? Let me re-read the hash function: `hash += (unsigned) MEM; x = XEXP (x, 0); goto repeat;` — the hash does NOT include in_struct. But `hash_arg_in_struct` is an output. So same hash. The table chain compares with `exp_equiv_p` which ignores in_struct. So no.

Let me look at how a load is *recorded*: maybe struct loads aren't recorded? `insert` stores in_memory and in_struct. cse_insn's src lookup happens regardless.

Wait, actually there's a subtlety: when cse processes a load, it does `src_elt = lookup(...)` and if found, `src = src_elt->exp`? Then `sets[i].src = src` and later the dest is recorded as equal to src_elt. If the load is a struct load and the previous is a non-struct load, the entry matches anyway.

OK. Let me try a completely different structural move: put the two 0x2E accesses in **separate functions**? No.

What about the `t = diff << 9;` — maybe the original had `t` assigned differently, and the second load is from a **different C variable holding a pointer** that the compiler treats as a fresh load because the pointer was passed through a function? no.

Let me look at the problem from the "what real C would a decompiler author write" angle. The barrier was added by the decomp team at P36 rung B. Perhaps the barrier was needed because they couldn't find the original form; maybe it's genuinely a WALL (cse-load-forward). But the brief's premise is that some are crackable with moves. Let me try the moves catalog: temps, decl order/scope, s16/u8 widths, loop shape, statement order, init at decl, &&/|| folds, pointer reuse.

"pointer reuse"! Maybe the original used a single pointer variable for both accesses:
```
s16 *q = (s16 *)((s32)s0 + 0x2E);
...
diff -= *q;
...
x2 = *q;
```
cse: q = s0+0x2E (a copy of an address expression). The MEM is `(mem (reg q))`. When cse processes `*q`, it looks up `(mem (reg q))`; both accesses use the same expression → forward. Unless cse substitutes q's value into the MEM (find_best_addr chooses the address form) — then `(mem (plus s0 46))` both → forward.

Hmm.

"loop shape": put the second access in a loop that executes once with a variable condition? Adds insns.

"init at decl": maybe `s16 x2 = *(s16*)(...)` at declaration inside a block — same.

Let me reconsider: maybe the target's second load isn't needed to be a *reload of 0x2E*; maybe the target's first lh is from a DIFFERENT source expression that also loads 0x2E but is NOT the same C expression because it's **loaded as part of a 32-bit or different access that the compiler split**. Hmm.

What if the first access is `*(s16 *)((s32)s0 + 0x2E)` and the second is `((s16 *)((s32)s0 + 0x2C))[1]`? Address = s0+0x2C+2 = s0+0x2E. cse folds the PLUS: `(plus s0 44)` then `[1]` → `(plus (plus s0 44) 2)` → simplify_plus_minus → `(plus s0 46)`. Same.

What if the second index is a variable `i = 1; q = (s16*)((s32)s0+0x2C); x2 = q[i];`? cse would substitute i=1? If i is a constant via cse, then q+2 → folded. Probably.

What if the index is 1 but stored in a variable that's also modified? no.

Let me try the simplest remaining idea: **reuse the same variable for the second load without reassigning it to t**, i.e.:
```
s32 x = *(s16*)(s0+0x2E);
diff = 8 - x;
t = diff << 9;
x = *(s16*)(s0+0x2E);      // same var, second load
*(u16*)(s0+0xE) += (x << 6);
```
We tested this in c4 (x reused) and got one load (58 ins). Because cse forwarded.

What if the variable is a *different width*, e.g. `s16 x` and `s32`? c4 had s32 x.

Hmm, what if the first assignment uses a **compound assignment** `diff -= *(s16*)...` (no temp) and the second is a temp — baseline. One load.

Let me test the volatile idea just to see if it produces the target (to know whether it's even the right mechanism), then decide whether it's acceptable. Actually, I suspect volatile would produce exactly it. But the brief forbids new levers; a volatile cast is a lever. I'd rather find real C.

Hold on — maybe the real original source had the `+=` through a **different pointer type** such that the store invalidates the load. In cse, `invalidate_memory` is called for stores. If the store to 0xE is processed BEFORE the second 0x2E load in RTL order, the entry is removed. RTL order = expansion order = source order. What if the source had:

```
*(u16 *)((s32)s0 + 0xE) += 1;      // store 1: invalidates 0x2E load entries
x2 = *(s16 *)((s32)s0 + 0x2E);
*(u16 *)((s32)s0 + 0xE) += x2 << 6;
```
No, extra store.

Unless... the original source computed the 0xE load+store as a single `+=` where the store is emitted *before* the 0x2E load because the addend is loaded after? In GCC's expand, `a += b` is expanded as: load a, load b, add, store. The store is after. But maybe with a compound expression the order is: load a; store a (the same value?) no.

What about `*(u16*)(s0+0xE) = *(u16*)(s0+0xE) + ((*(s16*)(s0+0x2E)) << 6)` — order: load 0xE, load 0x2E, shift, add, store. Still store last.

Hmm, but wait: what if the original used a **post-increment** or a memory-to-memory op? no.

Let me check the possibility that the first load `lh v0,46(s0)` and the second are actually at DIFFERENT offsets but objdump shows 46 for both because of a relocation? No, s0 is a register.

I'll try the volatile test to identify the mechanism, then look for a non-volatile equivalent.

Actually, wait! Another real C mechanism: **`s16` vs `u16` in the diff expression**. What if the first load is through a **`u16`** (lhu) and then sign-extended by the subtraction? Target's first load is `lh` though. Let me double check objdump: 77cc: lh v0,46(s0). Yes.

Let me look at the actual ROM target from the ORIGINAL game, not build/ — wait, build/ IS the ROM match. Fine.

Let me try `volatile` quickly as a diagnostic.
