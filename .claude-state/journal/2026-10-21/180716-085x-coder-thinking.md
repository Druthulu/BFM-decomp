---
ts: 2026-10-22T00:07:16Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG10r
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_weL1WvFIdenwCbh7gmGL
---
Not relevant. Let me stop reading source and go empirical with the operand swap.

The swap: `addu v0,v0,a1` vs `addu v0,a1,v0`. The two operands: the scaled index and p.

Since gcc's tree for `(u8*)p + off` is (plus p off_reg) [p first], but the output has the index first, the swap must come from combine/combine_regs. Hmm, actually, maybe gcc's tree IS (plus off_reg p)! Because expand builds the address as (plus (convert off) p)? Hmm, for pointer + int, gcc builds (plus ptr int). Hmm.

Hmm, but the tree order in the RTL might be affected by how the address is built: for `*(s16 *)((u8 *)p + off + 4)`, the MEM's address = (plus (plus p off) 4) — hmm, gcc's `plus` canonicalization in fold_rtx sorts the operands? fold_rtx's `simplify_plus` puts the CONST last, and for two non-const operands, `canonicalize_commutative_operation` might sort by cost/reg number!

`canonicalize_commutative_operation` in fold-const.c: it swaps operands so that the more "expensive"/less preferred one is second, based on `COMMUTATIVE_COST`. Hmm.

And `combine.c` also swaps.

So the order depends on the operands' costs. The index (a multiply result) vs p (a symbol address). Hmm.

To flip it, I could change one operand's shape. E.g., if the index were a plain register (not a multiply result)... hmm, but the sll is needed.

Hmm! What if the index is computed as a variable holding the scaled value and used via a "copy"?

Hmm, let me try a simpler idea: what if the address expression puts the constant +4 FIRST: `((u8 *)p + 4) + off`? Then the tree = (plus (plus p 4) off) → fold would canonicalize: (plus p (plus 4 off))? hmm, fold_rtx's simplify_plus would reassociate (4 + off) into (plus off 4) hmm.

Hmm. Let me try a few:
(a) `D_801270C8 = *(s16 *)((u8 *)p + 4 + off);`
(b) `D_801270C8 = *(s16 *)((u8 *)(p) + off + 4);` (same)
(c) introduce a temp: `u8 *qa = (u8 *)p + off; D_801270C8 = *(s16 *)(qa + 4);`
(d) `off = ...; D_801270C8 = *(s16 *)((u8 *)p + off) + ...` hmm no.

Let me try (a) and (c).

Hmm, wait. Actually — maybe a much better idea: the LAUNDER made p a hard reg (a1) and the target's tree is (plus p index). The launder is `asm("" : "=r"(p) : "0"(p))`. Its effect: p is a hard reg → the address is built as (plus hard_reg index)?

Hmm! With p as a hard reg, the tree is (plus a1 v0) — p first ✓. Without the launder, p is a pseudo, and the tree becomes (plus v0 a1) — the index first, hmm, why?

Hmm, maybe because combine's "canonicalize_commutative_operation" sorts by reg number or by whether the operand is a pseudo vs a hard reg! Hmm: in gcc's fold_rtx, `canonicalize_commutative_operation` uses COMMUTATIVE_COST: the operand with the lower cost goes second? The cost of a hard reg (a1) vs a pseudo (v0)...

Hmm, in the TARGET, the tree is (plus a1 v0) where a1 is HARD and v0 is the pseudo. In mine, (plus v0 a1) — hmm, but in mine, is a1 hard? The diff showed "register pairs (mine -> target, count): v0->a1 x1, a1->v0 x1" — meaning mine's v0 ↔ target's a1 and mine's a1 ↔ target's v0! So in MINE, the index is in a1 and p is in v0! And in the target, the index is in v0 and p is in a1.

WAIT. Let me re-read: "register pairs (mine -> target, count): v0->a1 x1, a1->v0 x1" — the diff tool found that mine's v0 corresponds to the target's a1 (1 place) and mine's a1 to the target's v0 (1 place).

So in mine: the index is in... hmm. The diff line: "85 addu v0,v0,a1 | addu v0,a1,v0". So mine's insn 85 = `addu v0,v0,a1`: the destination v0, the sources v0 and a1. The target's = `addu v0,a1,v0`: the destination v0, the sources a1 and v0.

And the register pairs: mine's v0 ↔ target's a1, mine's a1 ↔ target's v0. So the REGISTERS are swapped between mine and the target: mine's v0 holds what the target's a1 holds, and mine's a1 holds what the target's v0 holds.

Hmm! So the difference is not just the operand order — the whole register assignment of the two values is swapped!

So: in the target, the scaled index is in v0 and p is in a1. In mine, the scaled index is in a1 and p is in v0? Hmm, hmm. Let me re-read: mine's insn 85 = `addu v0,v0,a1` = v0 = v0 + a1. If mine's v0 ↔ target's a1, then mine's v0 holds the target's a1's value = p! And mine's a1 ↔ target's v0 = the index.

So in mine: v0 = p (the base), a1 = the index → the add = p + index, computed as `addu v0,v0,a1` = (p) + (index) ✓ — the same operation, the operands in the same order semantically! But the REGISTERS differ: mine has p in v0 and the index in a1; the target has p in a1 and the index in v0.

Hmm! But the diff only shows ONE insn differing (insn 85) — so the other insns (69-70: `lui a1; addiu a1,a1,0` for &D_80195AF6, and 84: `sll v0,v0,0x3`) matched. Hmm! In mine, the `lui a1; addiu a1,a1,0` (the p materialization) — so p is in a1 in mine too! And the sll is in v0 in mine.

So in mine: p → a1, the index → v0, and the add is `addu v0,v0,a1` = index + p (v0 = the index, a1 = p) with the destination v0.
In the target: p → a1, the index → v0, and the add is `addu v0,a1,v0` = p + index with the destination v0.

Hmm, so the same registers, just the operand order in the add differs! And the "register pairs (mine->target)" line is the diff tool's guess (it pairs the operands positionally).

OK so: the tree order differs: mine (plus v0 a1) = (plus index p); the target (plus a1 v0) = (plus p index).

So the target's tree = (plus p index) — the natural C order ✓. Mine = (plus index p) — swapped.

So gcc swapped the operands in mine. The swap is decided by combine/combine_regs' commutative canonicalization. To flip it, I need to change the operand costs/shapes.

Idea: make the index operand a "hard reg" or change the expression so the canonicalization prefers p first. Hmm.

Since the source is `(u8 *)p + off` → the tree (plus p off_reg) — and gcc swapped it to (plus off_reg p)... hmm, that's odd: gcc's canonicalize_commutative_operation puts the operand with the LOWER cost FIRST? Let me think: in fold-const.c:

```c
rtx
canonicalize_commutative_operation (rtx op, rtx x, rtx y)
{
  int xcost = COMMUTATIVE_COST (x);
  int ycost = COMMUTATIVE_COST (y);
  ...
  if (xcost > ycost) { swap }
```
Hmm, and COMMUTATIVE_COST for a REG is... in mips.h, `COMMUTATIVE_COST(x)` is defined? Hmm.

Hmm, in gcc 2.7.2's fold-const.c:
```c
/* Return the cost of X in a commutative operation, i.e. the value of
   X when the operation is done with the other operand first.  */
#define COMMUTATIVE_COST(x) \
  (GET_CODE (x) == REG ? 0 : ...)
```
Hmm. Let me look at the actual definition — it's in fold-const.c or expr.h. Let me grep. This is worth it: if COMMUTATIVE_COST(REG) is defined per-target, the swap depends on the operand type. In mips.h there might be a definition.

Let me grep for COMMUTATIVE_COST.
