---
ts: 2026-10-22T00:05:53Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG10r
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_q2iZ9D3NBIGJGumLs5VK
---
SO CLOSE! Score 1: the only difference is the operand ORDER of the `addu`: mine `addu v0,v0,a1` vs the target `addu v0,a1,v0`.

That's an operand-order swap in one insn! The C:
```
D_801270C8 = *(s16 *)((u8 *)p + off + 4);
```
where off = idx*8 and p = &D_80195AF6.

The target: `sll v0,v0,0x3; addu v0,a1,v0; lh v0,4(v0)` → the address = a1 + (idx*8), i.e. base + index.
Mine: `addu v0,v0,a1` → the address = (idx*8) + a1 — the operands swapped.

This is a "commutative swap" — the C0505/R-family: "a constant-operand commutative swap is undone by fold (fold-const.c) and only a var/var swap can reach the allocator" (from the delever_search comment: "the caller-saved swap is decided in local-alloc's block_alloc/combine_regs by which dying pseudo the operand ties to — the temp inlined/introduced first").

So I need to swap the operands of the addition: the address should be computed as p + off (base + index) rather than off + p.

In C: `*(s16 *)((u8 *)p + off + 4)` → the address = p + off + 4. gcc computed it as (off*1) + p? Hmm, the off is `((Unkstruct_800B5CB8 *)a0)->unk100 * 8` and the C is `(u8 *)p + off + 4`.

Hmm, so gcc's add is (p + off) but the register assignment made it `addu v0,v0,a1` where v0 = off*8 and a1 = p. The target has `addu v0,a1,v0` (a1 = p first, v0 = the index second).

So the difference: the order of the two addends in the RTL. This comes from how the expression was built: `(u8*)p + off + 4` — gcc builds ((p + off) + 4) hmm, but the target's is p + (off*8)? Hmm: the target does `sll v0,v0,0x3` (idx*8) then `addu v0,a1,v0` (p + idx*8) then `lh v0,4(v0)` (the +4 folded into the load's offset ✓).

Mine: `sll v0,v0,0x3; addu v0,v0,a1` (idx*8 + p) — the operands swapped, and then `lh v0,4(v0)`.

So the same structure but with the addends swapped. This is a commutative-swap dial!

How to control the operand order? The address expression: `(u8 *)p + off + 4`. gcc's expand: the address = p + off*1 + 4. The multiply by 8 is done on the index. The final add: p + (idx*8) vs (idx*8) + p.

The RTL is built by combine/combine_givs. The order depends on which operand is the "base". Hmm.

Options to flip:
(a) Write the expression differently: `*(s16 *)((u8 *)p + (off + 4))`? Hmm, that would make the +4 part of the index: off+4 → then the address = p + (idx*8+4) → the load would be `lh v0,0(v0)` hmm, and the target has `lh v0,4(v0)`. ✗

(b) `*(s16 *)((u8 *)p + off) + 4`? no, the type.

(c) Swap the roles: make the base the index and the offset the pointer? Hmm.

(d) The C0505 catalog: "a constant-operand commutative swap is undone by fold (fold-const.c) and only a var/var swap can reach the allocator" — so the swap here is var/var (p vs the scaled index). The fix might be to change WHICH variable holds what: e.g., if `off` were a pointer... no.

Hmm, let me think: mine computes `addu v0,v0,a1` = (v0 = idx*8) + (a1 = p). The target: (a1 = p) + (v0 = idx*8).

In the RTL, the addition's operands are ordered as they appear in the expression tree. gcc's expand for `(u8*)p + off`:
- p is a pointer (Pmode), off is an s32 → the addition is (p) + (off converted to a pointer) → the tree is (plus p off). Then the multiply: off = idx*8 (the sll) → the tree is (plus p (mult idx 8)).

Hmm, so the tree is (plus p (mult ...)) → the target's order ✓. But mine has (plus (mult ...) p)? Hmm, that would be a reassociation by combine.

Hmm, actually the swap might be introduced by `combine` (the RTL combiner) which canonicalizes the plus operands (e.g. by cost). The "commutative swap" family (R25/R26?) in the R-catalog is about this.

Hmm, so how do I flip it? Options:
- Make the index expression a different shape so the combiner orders it differently. E.g. if the index were computed as `off` (a variable) rather than `idx * 8` inline. Hmm! Currently: `off = ((Unkstruct_800B5CB8 *)a0)->unk100 * 8;` — the multiply is done separately (into v0) and then added. Hmm, but mine has the same sll.

Hmm, the difference is just the operand order in the add. Let me try:
- Swap the source: `D_801270C8 = *(s16 *)((u8 *)p + off + 4);` → maybe `*(s16 *)((u8 *)p + 4 + off)`? Hmm, that changes the tree order: p + 4 + off → hmm.

Let me think about the target's tree: the address = p + idx*8, and the load's offset is +4. So the tree is (plus p (mult idx 8)) with the MEM's offset 4. So the +4 was split off as the MEM's offset (offset_of_int... hmm, the "split" happens in reload: the address (plus (plus p (mult idx 8)) (const 4)) → reload splits the constant 4 into the MEM's offset ✓).

Mine: the tree must be (plus (mult idx 8) p) → hmm, i.e. the operands swapped at the RTL level.

Hmm, since gcc's combine canonicalizes commutative operands by cost, the order might depend on the register numbers or the "cost" of the operands. Hmm.

Let me look at the R-family for the commutative swap: "R25, R26" hmm. The delever_search comment says: "lane B's map: the caller-saved swap is decided in local-alloc's block_alloc/combine_regs by which dying pseudo the operand ties to — the temp inlined/introduced first; a constant-operand commutative swap is undone by fold (fold-const.c) and only a var/var swap can reach the allocator."

So: a var/var swap CAN reach the allocator. Our case: v0 (the index) vs a1 (p). Hmm, and the target has a1 first.

Hmm, so the swap is decided by local-alloc/combine_regs based on which dying pseudo the operand ties to. So if I change the allocation (e.g. by introducing a temp), the order could flip.

Ideas:
(a) Use a temp for the index: e.g. `off = ...; s32 t = off; D_801270C8 = *(s16 *)((u8 *)p + t + 4);` hmm.
(b) Change the address expression to `((u8 *)p + off) + 4` explicitly (it already is).
(c) Use `p` differently: e.g. `D_801270C8 = *(s16 *)((u8 *)(p + off/8) + 4);` hmm, off/8 = idx (a division) — hmm, off = idx*8 so off/8 = idx. But then the sll would be gone ✗ (the target has the sll).

Hmm, the target: `sll v0,v0,0x3` then `addu v0,a1,v0`. So the index is scaled by 8 and added to p.

(d) What if the pointer arithmetic is written with the pointer on the right? In C, `off + (u8*)p` — that's invalid C (can't add a pointer to an integer... well, GCC allows it as an extension? `off + p` where off is s32 and p is a pointer → error). Hmm, but `(u8 *)p + off` vs `off + (u8 *)p` — hmm, in GNU C, `int + pointer` is an error.

Hmm. What about casting: `*(s16 *)((u8 *)(off + (s32)p) + 4)`? Hmm: (s32)p = the address as an integer; off + that → an integer; then cast to a pointer. The tree: (plus (mult idx 8) (convert p)) — the index first! That might give the target's order... no wait, the target has p FIRST: `addu v0,a1,v0` = a1 + v0 = p + index. So I want the tree (plus p index).

Hmm, mine is (plus index p) and the target is (plus p index). So I want the tree with p first.

The C `(u8 *)p + off` should give (plus p off)... but gcc's combine reassociated it. Hmm, combine's reassociation: it may swap the operands by cost. Hmm.

Hmm, since the operand order is decided by the ALLOCATOR (combine_regs/local-alloc), the fix might be to change the allocation. E.g., if the index were computed into a different reg...

Hmm, what if I use a temp variable for the scaled index, e.g.:
```
off = ((Unkstruct_800B5CB8 *)a0)->unk100 * 8;
D_801270C8 = *(s16 *)((u8 *)p + off + 4);
```
That's the current. The sll is in off's assignment.

Hmm, what if the index is not a variable but inline: `D_801270C8 = *(s16 *)((u8 *)p + ((Unkstruct_800B5CB8 *)a0)->unk100 * 8 + 4);` — then the sll is inline. Hmm, the target's order: the sll at 84 comes right before the addu at 85 ✓ (both are in the same "expression").

Hmm, let me try a few variants:
v2: inline the index (no `off` variable).
v3: use a temp: `s32 t = off; ... p + t + 4`.
v4: swap: `*(s16 *)((u8 *)p + 4 + off)`? Hmm, that changes the tree to ((p + 4) + off) → hmm, reload would split the 4 → the address = p + off with the MEM offset 4? Hmm, (plus (plus p 4) off) → hmm, combine would reassociate to (plus p (plus 4 off))?

Let me try v2 and v3.

Hmm, also: the `off` variable is declared at the function scope. Its assignment `off = idx * 8` is in the block. What if `off` were declared inside the block (scope)? That's a C0505 "decl order/scope" dial. Hmm, that might change the allocation.

Let me try v2 (inline index) first — hmm, but `off` is used only there. Hmm, the target has the sll and the addu adjacent, suggesting the index is a temp used once (like the current `off`).

Hmm. Let me think about the swap mechanism once more: "the caller-saved swap is decided in local-alloc's block_alloc/combine_regs by which dying pseudo the operand ties to — the temp inlined/introduced first".

So: the add's operands are (index, p) in mine and (p, index) in the target. The "dying pseudo" tie: the operand whose pseudo dies at this add... The index (v0) dies at the addu? No — v0 is the RESULT of the addu (`addu v0,v0,a1` → v0 = v0 + a1). Hmm, so v0 is both the index and the result — the "dying pseudo" is a1? no, a1 = p survives (used later? no, p is dead after).

Hmm. In the target: `addu v0,a1,v0` → v0 = a1 + v0. Same result, the operands swapped.

So the difference is purely which reg is the destination/source. Both compute p + idx*8.

Hmm! In the target, the destination is v0 and the first source is a1 (p); in mine, the destination is v0 and the first source is v0 (the index). So in the target, the index (v0) is the SECOND operand; in mine, the index is the FIRST.

So in the target's tree: (plus p index); in mine: (plus index p).

Hmm. So the source expression's tree order differs. In C, `(u8 *)p + off` → the tree is (plus p off) → so the TARGET matches the natural C order and mine was swapped by combine/combine_regs.

Hmm, so what did I change? I removed the launder! The launder (`asm("" : "=r"(p) : "0"(p))`) forced p into a hard reg. Hmm.

Hmm, and the launder's presence/absence changed the operand order. Hmm.

Hmm, so the fix might be to change the expression so that the swap doesn't happen. E.g., writing the address as `((u8 *)p + off) + 4` (as now) vs `(u8 *)(p + off) + 4`? Hmm, p is D_80195AF6_t* so p + off (in elements!) would be different. Hmm.

Let me try some variants:
v2: `D_801270C8 = *(s16 *)((u8 *)p + off) + 4;` — no, the type changes (s16 vs s32) ✗.
v3: `D_801270C8 = *(s16 *)((u8 *)p + off + 4);` (current) with `off` declared as a local in the block.
v4: use a `u8 *` variable: `u8 *pb = (u8 *)p; D_801270C8 = *(s16 *)(pb + off + 4);` — hmm, that adds a copy.

Hmm, v4: hmm.

v5: What if the index is scaled differently: `D_801270C8 = *(s16 *)((u8 *)p + (off) + 4);` same.

Hmm, what about the ORDER of the two operands in the C: `off + (u8*)p`? Invalid in C (int + pointer) — hmm, actually GCC allows `int + pointer`? No, that's an error in C. But `(u8 *)p + off` vs ... hmm.

What about making the index an unsigned/size_t? Hmm.

Let me think about the "temp inlined/introduced first" hint: the swap is decided by which dying pseudo the operand ties to. The two operands: p (a1) and the index (v0). Both die at the addu (p dies, the index dies). Hmm.

Hmm, "the temp inlined/introduced first": if the index were introduced as a temp (a separate pseudo) rather than inlined, the order might flip.

Let me try:
v2:
```
                off = ((Unkstruct_800B5CB8 *)a0)->unk100 * 8;
                D_801270C8 = *(s16 *)((u8 *)p + off + 4);
```
(current) → mine has (index + p).

v3: what if the address is computed via a temp pointer:
```
                u8 *pb = (u8 *)p + off;
                D_801270C8 = *(s16 *)(pb + 4);
```
Hmm, that adds a copy (the pb = p + off is the same add). Hmm, the add's operands: p + off → the same tree. Hmm, but with pb, the add's result is a separate pseudo (pb) and the MEM's address = pb + 4 → the load's offset = 4 ✓. The add would be (plus p off) or (plus off p) — hmm, same question.

Let me try v3 and v2-with-scope-changed. Let me also try:
v4: `D_801270C8 = *(s16 *)((u8 *)p + off) ;` hmm, wrong offset.

Hmm, what about the possibility that the ORDER depends on the ORDER of the `p` declaration vs `off`? The C0505 catalog: "declaration order only on an exact tie" (the s-bank order) — hmm, that's for the callee-saved bank.

Let me just try a few variants. Each is cheap (25s).

v2: p's use: `*(s16 *)((u8 *)p + off + 4)` with `off` declared in the block scope.
v3: with a `u8 *pb` temp.

Let me write both and score them in sequence.

Actually, let me think about the R-family for the commutative swap: the families include "R25, R26" (the temp inlined/introduced). The delever_search R-rules can generate candidates automatically! But I can't run the sweep (only --try).

Hmm, but maybe I can approximate: "the temp inlined/introduced first" — so INTRODUCING a temp might flip the order.

Let me try:
v2: introduce a temp for the index: `s32 t = off;` hmm.

Let me try v3 (a `u8 *` temp) and v2 (introduce a temp for the scaled index inside the expression).

Actually, the simplest: what if the address is `((u8 *)p + off) + 4` (as now) vs `(u8 *)p + (off + 4)`? The latter: the tree = (plus p (plus off 4)) → reload would split the 4 → hmm, (plus off 4) is not a constant → reload can't split it into the MEM's offset → the load would be `lh v0,0(v0)` with the address = p + off + 4 → the target has `lh v0,4(v0)` ✗.

OK let me try v2/v3 empirically.
