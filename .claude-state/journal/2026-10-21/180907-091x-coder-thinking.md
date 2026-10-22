---
ts: 2026-10-22T00:09:07Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG10r
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_SyqfswRC7d1txFSbixjp
---
Still the same. Hmm! The add is always (index + p).

Hmm, so the tree really is (plus index p) in all my variants. And the target is (plus p index).

Hmm! What if the SOURCE expression's tree is (plus p index) but gcc's combine swapped it because the p operand is a PSEUDO and the index is also a pseudo... hmm, and in the launder version p is a HARD reg.

Hmm, so: in the target, p is in a1 (a hard reg) and the index in v0 (a hard reg). In mine, both are hard regs too (a1 and v0). Hmm! The same registers!

So the ONLY difference is the tree order, and the tree order is decided by fold/combine. Hmm, but the C is identical except for the launder. So the launder changed the tree order. With the launder, p is a hard reg from the start (the asm's output) — so the address tree is (plus hardreg index) hmm, and the "canonicalization" of a commutative op with a hard reg vs a pseudo...

Hmm, hmm. Since both end up in hard regs (a1, v0), the difference must be in the ORDER the operands appear in the tree BEFORE allocation.

Let me think about expand: the address `(u8*)p + off + 4`:
- p is a local variable (a pseudo) → its value is the address.
- The address expression: (plus (plus p off) 4) → hmm, actually expand builds the address as: the base p (a pseudo) + the offset off (a pseudo) → the tree (plus p off).
- Then the +4 → hmm, the MEM's address is (plus (plus p off) 4) → fold_rtx's simplify_plus would flatten: (plus p off 4) → and the constant goes last ✓.

So the tree = (plus p off) → p FIRST. But the output is (plus v0 a1) = (index p) — the index first. So the swap happened in combine.

And with the launder, p is a hard reg (a1) and the tree (plus a1 v0) stayed.

Hmm! So the swap happens when the operand is a PSEUDO. In combine.c, there's a step that swaps the operands of a commutative operation to put the "cheaper" one first — and the cost of a pseudo vs a hard reg differs.

Hmm, so if p were a hard reg, no swap. How to make p a hard reg without asm? A call argument (a0-a3) or a return value.

Hmm!! What if p were passed to a call? There's no call in that block... but the whole function has calls. Hmm, p is used only in that block.

Hmm, what if the address is used as a call argument somewhere? No.

OK, alternative: what if the swap is not about hard-vs-pseudo but about the operand COSTS: in combine's canonicalization, the cost of an operand = its "cost" (rtx_cost). A pseudo (a register) has cost 1; a symbol_ref has a higher cost. Hmm.

Hmm, hmm. Let me think about it via the "combine" source. In combine.c's `simplify_operand`/`convert_add`, there's:

```c
      /* If we are adding a constant to a register, ... */
```
and in `match_operand`... Hmm.

There's also combine's "swap" in `convert_add`:
```c
	  /* If we have an addition of two registers, ... */
```

Hmm, and in fold-const.c's `simplify_plus`:
```c
rtx
simplify_plus (rtx x, rtx y)
{
  ...
  /* Fold CONST op CONST to CONST.  */
  ...
  if (GET_CODE (x) == CONST_INT && GET_CODE (y) == CONST_INT) ...
  ...
  /* Handle the case of (plus (plus ...) ...) */
  ...
  /* Commutative operation: put the constant last */
  ...
      if (GET_CODE (x) == CONST_INT && GET_CODE (y) != CONST_INT) ...
```
Hmm, the reassociation in simplify_plus: `(plus (plus a b) c)` → it may reassociate to put the CONST last. And the order of a and b is preserved.

Hmm.

OK — the "canonicalize_commutative_operation" in gcc 2.7.2's fold-const.c:

```c
rtx
canonicalize_commutative_operation (op, x, y)
{
  int xcost, ycost;
  ...
  xcost = COMMUTATIVE_COST (x);
  ycost = COMMUTATIVE_COST (y);
  ...
  /* Make sure that X is the more expensive of the two...  */
  if (xcost > ycost)
    return gen_rtx (GET_CODE (op), GET_MODE (op), y, x);
  ...
}
```
and COMMUTATIVE_COST is defined in expr.h or fold-const.c as:
```c
#define COMMUTATIVE_COST(x) 0
```
Hmm, but mips.h might define it as:
```c
#define COMMUTATIVE_COST(x) (REG_P(x) ? 0 : ...)
```
Hmm. My grep found nothing in the reference tree (which lacks config/mips/mips.h? the grep included config/mips/*.h and found nothing). Hmm, so COMMUTATIVE_COST is probably the default.

OK. Let me try yet another approach: since the difference is a single commutative swap and the launder's only role is to make p a hard reg, maybe I can achieve the same by making the ADDRESS p's value be used in a way that requires a hard reg...

**IDEA**: What if the newval load used p (a1) instead of re-materializing the address in `at`? Then p would be live longer (used at 73 and 85) and the tree... hmm, but the target has the `at` materialization ✗.

**IDEA 2**: What if the `off` variable is declared as `register`? Hmm, "no register vars".

**IDEA 3**: What if the multiplication `unk100 * 8` is replaced by a shift of a different expression, changing which operand is "dying"?

Hmm, hold on! What about the ORDER of the two operands in the C: the tree (plus p off) — but the output is (plus off p). So the swap is by the OPTIMIZER. What if the tree were built as (plus off p)? Then the optimizer might keep it (if it only swaps to a canonical form, it would swap back ✗).

Hmm.

Let me look at gcc's combine.c for the "swap" of commutative operands to see the trigger. Let me grep combine.c for "swap".

Given my context budget, let me do one targeted grep and then decide.
