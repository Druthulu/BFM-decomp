---
ts: 2026-11-06T12:49:06Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG31y
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_njeZ7qnaLFHDtsVVO4Cv
---
The target:
```
1c74: sh v0,266(s1)   ← unk10A = idx
1c78: sll v0,v0,0x3
1c7c: lh v1,266(s1)   ← reload unk10A for tmp2
```
Mine:
```
1c78: sll v1,v0,0x3     ← shifted into v1 (early)
1c7c: sh v0,266(s1)     ← store
1c80: sll v0,v0,0x3     ← another shift into v0!
```
So mine computes the shift TWICE (once into v1 before the store, once into v0 after) — because the store of unk10A and the reload can't be forwarded... Actually mine has an extra `sll` (v1) — that's the tmp2 index computed from idx before the store, then after the store it recomputes? No: mine at 1c80 `sll v0,v0,0x3` uses v0 = idx — but idx was just stored; v0 still holds idx. Then 1c84-1c8c: tmp1 = D_801ED5F0[idx<<3]... wait, the target's index is `idx * 2` with sll v0,v0,0x3? Hmm, `sll v0,v0,0x3` = idx*8 = (idx*2)*4 → the element size is 4 bytes (s32) with index idx*2 → yes.

So mine computes the tmp2 index (v1 = idx<<3) BEFORE the store, then the tmp1 index (v0 = idx<<3) after. Since both are the same value, why twice? Because the store to unk10A is a memory barrier for cse? Both use idx. Actually gcc computed `idx<<3` twice because... in the C:
```
tmp1 = D_801ED5F0[idx * 2];
tmp2 = D_801ED5EC[((Unkstruct *)param_1)->unk10A * 2];
```
The second uses the RELOADED unk10A (which equals idx). So the C has two different sources: idx and the field. In the target, the reload produces v1 = unk10A, then sll v1,v1,0x3.

In mine, the compiler *forwarded* the store into the reload (cse: the store `unk10A = idx` then the load `unk10A` → forwards idx) → so both are idx → the shift is computed twice (once for tmp2, once for tmp1) because the memory order... Hmm.

Wait, actually mine's order is: sll v1,v0,0x3 (for tmp2, using idx forwarded), then store, then sll v0,v0,0x3 (for tmp1) then tmp1 load, then tmp2 load using v1.

The target's order: store, sll v0 (tmp1 index), lw v0 (tmp1), lh v1, sll v1, lw v1 (tmp2).

Hmm, so in the target, the reload of unk10A happens after the store and the tmp1 load. In mine, the tmp2 index is computed before the store (using the forwarded idx).

The original C's `idx` variable is the same as the stored value; cse forwards. The target must have had a barrier preventing the forward — the memory barrier asm (line 112) was between i70a and i70b... no, the barrier was before the block. Hmm, the original comment says the keepalive asm (`"r"(idx) : "memory"`) was merged with the memory barrier at line 112 (before `i70b = ...`). That barrier made the store not forwardable? Actually the store `unk10A = idx` happens at line 117, and the reload at line 131. cse would forward the store into the load unless something invalidates. In the target, the store and the load are both kept (target has sh then lh).

So in the target, cse did NOT forward. In mine (w4), cse DID forward (using idx directly for tmp2's index). Wait, does mine still have the `lh`? Mine has no `lh v1,266(s1)` at 1c7c — right, it forwards.

Hmm! So there are TWO residual issues:
(a) cse forwards the unk10A store into the reload (target keeps the reload).
(b) the shift register.

Interesting. How did the original prevent the forwarding? The memory barrier asm at line 112 was BEFORE the block, so it doesn't separate the store from the load. Hmm, but the original had the store `unk10A = idx` at line 117 and the load at line 131 with nothing in between... and yet the target has both. Because the asm keepalive (with "memory" clobber) at line 129 sits between the store and the tmp2 load! Yes: line 117 store, then line 129 asm("" : : "r"(idx) : "memory"), then line 131 tmp2 load. The memory clobber invalidates cse's memory equivalence → the reload survives.

So the asm barrier (merged keepalive) served double duty: (1) +1 ref on idx, (2) memory clobber preventing store→load forwarding.

Lever-free replacements:
(1) +1 ref on idx: need another real use of idx.
(2) A memory clobber between the store and the reload: lever-free alternatives — a real store to an unknown location? Or make the reload's address opaque? Or use a volatile read? Volatile is a barrier-kind lever (no).

Hmm, what real C makes cse not forward a store to a load of the same field? If the two accesses use different types (e.g. store as u16 through one expression, load as s16 through a different alias), cse's MEM_IN_STRUCT/alias info might differ → no forwarding. In the C: `((Unkstruct*)param_1)->unk10A = idx;` and `...->unk10A * 2` — same field, same type.

What if the reload goes through a *pointer* local: `u16 *pa = &((Unkstruct*)param_1)->unk10A; *pa = idx; tmp2 = D_801ED5EC[*pa * 2];` — cse would still forward (same MEM).

What if the load is from a *volatile* pointer? That's a barrier-ish lever (volatile). Not allowed ("no new lever of any kind"; barrier = volatile/asm barrier). A volatile load would also emit different code (lhu vs lh).

Hmm, what about a call between them? No call there.

What if the store is to the struct and the load is from a cast pointer of a different type, e.g. `*(u16 *)((u8 *)param_1 + 0x10A)`? cse's MEM alias: both are mem/s with different... cse compares rtx equality: the store is `(mem/s:HI (plus (reg) (const 266)))` and the load would be `(mem/s:HI (plus (reg) (const 266)))` — identical → forward.

Unless the load's address is computed via a pointer variable that cse can't equate: e.g.
```
u8 *pp = (u8 *)param_1 + 0x10A;  /* but this would be a real addiu */
```
Extra insn.

Hmm. What about making the store a *different width*: store `unk10A` as u16 (2 bytes) and load as... the target has `sh v0,266(s1)` and `lh v1,266(s1)` — both 2 bytes. If in C the store were through a u16 lvalue and the load through an s16 lvalue, the MEM modes are both HImode → same.

What if the store is `((u8*)param_1)[0x10A] = idx;` (byte store!) — no, the target stores a halfword.

Hmm, so how to break the cse forward lever-free? Ideas:
- Reorder: put the tmp1 load BETWEEN the store and the tmp2 load — cse forwarding works regardless of intervening loads (they don't alias... the D_801ED5F0 load is a different symbol; cse's "memory invalidation" only happens on stores).

Wait — the target's order has the tmp1 load between the store and the tmp2 reload. In mine, the tmp2 index is computed BEFORE the store (sched moved it).

Hmm, but the actual forward is a cse decision (cse1/cse2), not sched. Let me check: does the target really keep the reload because of the asm memory clobber? Yes, per the original comment.

Lever-free alternative to a memory clobber: a real *store* to an unknown/aliasing location between them! Is there one in the C? The `unk10A` store is the last store before. What about `D_801F32D0 = 0;` — that's before the block (line 114), and it's a store to a global scalar. If we move `D_801F32D0 = 0;` to between the store and the reload... but the target has it before (1c64 sh zero,0(at) right after i70a). Hmm, the target's order: `sh zero,0(at)` (D_801F32D0=0) at 1c64 — before the store of unk10A at 1c74.

So the target has no intervening store; only the asm clobber.

Therefore, to crack this item lever-free, we need cse to not forward. Options:
(a) make the two MEMs non-identical in cse's eyes: different MEM flags. cse's `rtx_equal_p` on MEM includes the attributes (MEM_IN_STRUCT_P etc. via `mem_attrs`?). In gcc 2.7.2, MEMs are compared with rtx_equal_p which compares the whole expression including the `mem/s` attributes? Actually in 2.7.2, MEM rtx have an `unchanging`/`in_struct` flag stored in the rtx fields (`MEM_IN_STRUCT_P` etc. are macros over the rtx). rtx_equal_p for MEM compares XEXP(0) only? Let me check: rtx_equal_p in rtl.c compares code and then all operands; the flags (MEM_IN_STRUCT_P) are stored in the `rtx` union's `rtunion`? In 2.7.2, MEM_IN_STRUCT_P is a bit in the rtx (in `rtunion fld[0]`? no — it's stored in the rtx's `volatil`/`unchanging`/`in_struct`/`integrated` bitfields). rtx_equal_p doesn't compare those flags! Hmm.

But cse's invalidation logic (`invalidate_memory`) uses the MEM attributes: a store to a MEM_IN_STRUCT is recorded as "struct" and only invalidates matching... In cse.c, `invalidate_memory (x, write)` uses `struct_equiv`? The cse memory table records (mem, ...) with attributes; a later load is looked up and *invalidated* if the store's attributes don't match: `struct_equiv`?

Let me check cse.c's approach: `invalidate_memory` records `struct_equiv` and `mem_attrs`. Hmm, in 2.7.2 cse.c has:

```
/* Record the fact that X is written.  ... */
static void
invalidate_memory (x, write)
```
It sets `struct_equiv` if MEM_IN_STRUCT_P and only invalidates entries with `struct_equiv`... Something like "a store to a struct member does not invalidate loads from non-struct memory"? That's the idiom "struct alias" used elsewhere (MEM_IN_STRUCT). But here both are the same MEM.

Different idea: make the store and the load use different *base expressions* that aren't equal: e.g. store via `((Unkstruct*)param_1)->unk10A` and load via a pointer variable `u16 *pq` that is `(u16 *)param_1 + 0x85` — but the address computation would need an insn... unless cse can fold it: `(plus (reg param_1) (const 266))` — if the C is `*(u16 *)((u8 *)param_1 + 0x10A)`, the address is the same plus → cse sees the same rtx → forwards.

Hmm, what if the load uses a DIFFERENT register for the base: e.g. `pq = (u16 *)param_1;` then `pq[0x85]`. cse would fold pq to param_1 (copy propagation) → same.

What if the load is via `i70b`? No.

OK, different approach: what if the tmp2 index uses the reload but the *store* is what we drop? I.e., accept cse forwarding but make it produce the target's insns: the target keeps the reload because the value is not equal... 

Actually WAIT. Let me reconsider: maybe in the target the reload is kept because `idx` is a `u16` and the store truncates it: `unk10A` is a u16 field, so storing idx (u16) is exact. If idx were s32 (not u16), the store would truncate to 16 bits, and the reload would NOT equal idx (different value) → no forwarding! Then the reload must happen. And the target's `lh v1,266(s1)` is a *signed* load (lh) while the store is `sh`. If unk10A is s16 in the struct and the load is s16, then `unk10A * 2` sign-extends.

Hmm, but the target's asm at 1c7c is `lh` (sign) — so the field is s16 and the load is signed. In the C, `((Unkstruct_800B5CB8 *)param_1)->unk10A` is used in `D_801ED5EC[...->unk10A * 2]`. What's unk10A's declared type in Unkstruct_800B5CB8? Let me check. If it's u16, gcc would emit lhu. The target has lh → the field is s16 or the C casts.

And idx is `u16 idx = D_801ED4B4[i70a]` (lbu → u16). Storing a u16 into an s16 field: values 0..255 fit.

So if idx is u16 and the field is s16, is the store's value equal to idx? cse's store forwarding compares the stored value (idx, u16 in HImode subreg?) with the load's result (s16). In RTL: `(set (mem/s:HI) (subreg:HI (reg idx) 0))` and the load `(set (reg:HI) (mem/s:HI))` — cse's equivalence: the load result equals the stored subreg → cse creates a register equivalence with the subreg of idx. Then `(s16)` extension of that subreg... The original comment says the target keeps the reload; the asm clobber forced it.

So: does the field's type matter? In the original C, idx is u16 and the field is (presumably) u16 → the store is exact.

Hmm, let me check the struct definition.
