---
ts: 2026-10-22T00:07:47Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG10r
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_bah7EPa4VGBcycyspM9N
---
Not in the reference tree (it's a partial tree). Let me check combine.c for the commutative swap logic.

Actually, let me be pragmatic and just try variants. The key: the add's operand order. Let me try:

(a) `D_801270C8 = *(s16 *)((u8 *)p + 4 + off);` — the +4 first.
(b) Introduce a temp: `u8 *qa = (u8 *)p + off; D_801270C8 = *(s16 *)(qa + 4);`
(c) Make the index an unsigned: `off = (u32)((Unkstruct_800B5CB8 *)a0)->unk100 * 8;` — hmm, the sign extension of the index matters (the target's `addu at,at,v0` is an addu = unsigned add, so the index is treated as unsigned). Hmm! Interesting: the target's `addu` (not addiu) means the index was sign-extended/zero-extended to 32 bits.

Hmm, so maybe the type of the index expression matters for the tree. In the C, `off` is s32 and `((Unkstruct_800B5CB8 *)a0)->unk100` is probably s32.

Let me try (b) — a temp pointer — first (it changes the tree shape: the add's result is a separate pseudo, and the MEM's address = qa + 4 → the load's offset 4 ✓).

Let me write it:
```
                off = ((Unkstruct_800B5CB8 *)a0)->unk100 * 8;
                {
                    u8 *qa = (u8 *)p + off;
                    D_801270C8 = *(s16 *)(qa + 4);
                }
```
Hmm, a block scope. Or just:
```
                off = ((Unkstruct_800B5CB8 *)a0)->unk100 * 8;
                D_801270C8 = *(s16 *)((u8 *)p + off + 4);
```
(current).

Let me try (b).

Hmm, hold on. Let me think about the "cost" of the operands: the index is the result of a MULT (sll) — a pseudo; p is a pseudo (the address). In gcc's combine, `simplify_operand` and the "swapping" in combine's `convert_add`/`add` handling: combine has a step that swaps the operands of a commutative operation if one is cheaper.

The R-family hint said: "the caller-saved swap is decided in local-alloc's block_alloc/combine_regs by which dying pseudo the operand ties to — the temp inlined/introduced first".

"the temp inlined/introduced first" — so: if the index is INLINED (not a separate temp), the swap goes one way; if INTRODUCED (a separate temp), the other way.

In v1, `off` is a variable (a temp) but gcc inlined it (used once → the sll's result goes straight into the addu). Hmm, actually "off" is a variable whose value is used once: gcc's local-alloc might still keep it as a pseudo.

Hmm! What if I make `off` used TWICE so it's not inlined? E.g. compute the address from `off` twice? That would change the code ✗.

Hmm, what if the index is introduced as a temp INSIDE the expression: `*(s16 *)((u8 *)p + (s32)(((Unkstruct_800B5CB8 *)a0)->unk100 * 8) + 4)` — same as v3.

Hmm.

Let me look at this from a completely different angle: what if the p's assignment is moved? The launder was between the `if` and the store. Hmm.

Actually, hold on! Let me look at the original def again:

```
            D_80195AF6_t *p = D_80195AF6;
            s16 newval = D_80195AF6[((Unkstruct_800B5CB8 *)a0)->unk100].f0;

            if (newval >= CAST_SIGN(s16, (u8 *)a0, 0xE)) {
                __asm__("" : "=r"(p) : "0"(p));  // launder
                s1 = 1;
                ((S0E_80184828 *)((u8 *)a0 + 0xE))->h = newval;
                off = ((Unkstruct_800B5CB8 *)a0)->unk100 * 8;
                D_801270C8 = *(s16 *)((u8 *)p + off + 4);
                D_801E43B4 += 1;
            }
```
Hmm, the launder is INSIDE the if-block. And in v1 (no launder), the score is 1 with only the operand order differing. So the launder's ONLY effect here is the operand order of the add!

Interesting. So the launder (making p a hard reg) fixed the operand order.

Hmm! What if instead of the launder, I make p a hard reg another way? Hmm, "no register vars" (the brief: "no `register` vars, no `__asm__`").

Hmm. What if p is declared as a register variable without the asm? `register D_80195AF6_t *p;` — the brief says "no `register` vars" (that's a pin-ish lever). Hmm, and it wouldn't pin a specific reg anyway.

Hmm. So I need the operand order flipped by a pure C change.

Options:
1. Change the expression so that the index is the FIRST operand naturally: e.g. `*(s16 *)((u8 *)p + off + 4)` → hmm.

Hmm, what if the pointer is added to the index in a different way, e.g. via a union or a cast to an integer:
`D_801270C8 = *(s16 *)((u8 *)((s32)p + off) + 4);` — hmm, (s32)p = the address as an integer; then + off (an integer add) → the tree = (plus (convert p) off) → hmm, and then cast back to a pointer. Hmm! The integer add's operands: (convert p) and off → the tree (plus (convert p) off) → the convert might be folded away → (plus p off) → p first ✓. Hmm, but the convert might change the operand costs.

Hmm, but the target's `addu` (not addiu) suggests the index is zero/sign-extended to 32 bits: the address = p + (index zero-extended) — so the tree is (plus p (zero_extend index)). Hmm! In the target: `sll v0,v0,0x3` then `addu v0,a1,v0` — the addu's second operand is the scaled index in v0 (already a full register). Hmm, so the extension happened before the sll.

In mine: `addu v0,v0,a1` = the index + p. Hmm, the same operands, swapped.

So the difference is ONLY the order. Hmm, and both use `addu`.

Let me try: `D_801270C8 = *(s16 *)((u8 *)((u32)p + off) + 4);` hmm, (u32)p is a no-op cast on a 32-bit target → the tree = (plus p off) — hmm.

Hmm, what if the index is a `u32`? `off = (u32)unk100 * 8;` → then the address = p + (u32 off) → the tree = (plus p (zero_extend off))? Hmm, the zero-extension would be folded (the sll result is already 32-bit) → the tree = (plus p off).

Hmm! The KEY might be the extension: in the target, the index is zero-extended to 32 bits before the add (hence `addu`), and gcc's canonicalization might place a zero_extend operand differently.

Hmm, mine also uses `addu`. Hmm.

OK, empirical. Let me try 3 variants in a row:
(b) a temp pointer: `u8 *qa = (u8 *)p + off; D_801270C8 = *(s16 *)(qa + 4);`
(d) `D_801270C8 = *(s16 *)((u8 *)p + (off + 4));` — hmm, this makes the +4 part of the index → the load's offset would be 0 ✗ (the target has lh v0,4(v0)).
(e) `D_801270C8 = *(s16 *)((u8 *)p + off) ;` hmm.

Let me try (b) first.

Hmm, hold on! What about the "off" variable's TYPE? `s32 off` and the assignment `off = unk100 * 8`. What if `off` were `u32`? Hmm, then `(u8*)p + off` → the index is zero-extended → the tree = (plus p (zero_extend off)) — hmm, and gcc's canonicalization might order it as p first ✓ (since the extend is a "costlier" operand?).

Let me try (f): `u32 off;` (change the declaration's type).

Hmm, but the decl is at the function scope and `off` is used only here. Changing s32 → u32 is a legit C0505 "width" dial!

Let me try both (b) and (f).

Actually, let me think about which is most likely. The target's add is `addu` (32-bit unsigned add). With `off` as s32, the index would be sign-extended to 64-bit then truncated... on a 32-bit target, an s32 index is used directly (no extension needed) → `addu`. With u32, also `addu`. Hmm, no difference.

OK, let me try (b) and (f) — 2 calls.

Actually, let me reconsider: maybe the swap is decided by which operand the "dying pseudo" ties to. In mine, the index (v0) is the destination of the sll AND the add. Hmm.

Hmm! What if I break the tie by making the index a separate temp that is NOT the add's destination? E.g. if the sll's result were in a different reg than the add's destination. Hmm, the add's destination is v0 (the index's reg) in both.

Hmm, in the TARGET: `addu v0,a1,v0` — the destination v0 = the index's reg (v0) ✓ and the source a1 = p. So in the target, the destination is the index's reg (the second source) — hmm, that's the "destination is the second operand" case. In mine, the destination is the first source.

In gcc's RTL, the destination of a `set` is usually a fresh reg; here it's v0 (the index's reg) — so combine put the result in the index's reg (the "dying pseudo" ties to it).

Hmm, so the difference is the operand order in the tree. Hmm, and the tree order for a commutative op in gcc is decided by `canonicalize_commutative_operation` in fold_rtx, which sorts by COMMUTATIVE_COST. Hmm, in gcc 2.7.2 fold-const.c:

```c
/* Return 1 if X is a commutative operation... */
...
rtx
canonicalize_commutative_operation (op, x, y)
{
  int xcost, ycost;
  ...
  xcost = COMMUTATIVE_COST (x);
  ycost = COMMUTATIVE_COST (y);
  ...
  /* Make sure that X is the more expensive of the two... */
  if (xcost > ycost) { swap }
```
Hmm, and COMMUTATIVE_COST is defined in fold-const.c as:
```c
#ifndef COMMUTATIVE_COST
#define COMMUTATIVE_COST(x) 0
#endif
```
Hmm, or in expr.h. Hmm, but mips.h might define it. My grep over the reference tree found nothing (the tree is partial — maybe config/mips/mips.h isn't included).

OK: empirical. Let me try the variants. Let me do (b) first.
