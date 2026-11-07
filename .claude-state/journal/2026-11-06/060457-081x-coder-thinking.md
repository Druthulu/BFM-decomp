---
ts: 2026-11-06T13:04:57Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO01
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_JFpYvEOukAtiyXdQFaZi
---
All still 9/217 — dbr fills the slot.

The wall tag: `dbr-delay-fill` fits ("delayed-branch fill takes a fall-through insn the target leaves out of the slot").

But let me try harder — the fill is of a *fall-through* insn into a delay slot. dbr's `fill_simple_delay_slots` does this when the insn is safe. 

Hmm, one idea: what if the second test's comparison value is loaded into a register that's already... 

What if the second test is `if (D_8011512C == 0xA)` but written as `if (0xA == D_8011512C)`? Same RTL.

What if the second test's `li v0,10` is actually needed *before* the first branch? E.g. if the source computes both constants first:
```
s16 v = D_8011512C;
if (v == 4) return;
if (v == 0xA) return;
```
t5 = 9.

What if the two tests are combined into a single comparison tree:
```
if (D_8011512C == 4 || D_8011512C == 0xA) return;
```
a4 = 9.

Hmm. What if I make the first branch's delay slot contain something real, e.g. the `for (i = 0; ...)` init? No, that's after.

What if the first test's branch target is a *different* return? In the target both branches go to the same address.

OK — what if the second test is not a constant compare but a range check? `if (D_8011512C == 0xA)` — target has li v0,10 + beq.

Let me consider: maybe the fix is to make the *first* test produce a different branch shape, e.g. `if (D_8011512C != 4) { if (D_8011512C == 0xA) return; }` — then the first branch is bne to the else, and the fall-through has li 10. Target has beq. No.

Alternatively, maybe I should target the second test instead: what if the *second* test's `li v0,10` is what dbr moves into the first slot; if the second test's compare value came from an `addiu` of an existing register (e.g. `li v0,10` from `addiu v0,v1,...`) it'd be different.

Hmm, what if the second test uses `D_8011512C == 0xA` where the constant is loaded via a variable that's set earlier:
```
s16 ten = 0xA;  // at function top
...
if (D_8011512C == ten) return;
```
gcc would propagate the constant → li.

What if `ten` is a global? extra load.

I think this is a genuine dbr-delay-fill wall. But hold on — maybe I can make the second block's first insn a *load* instead of `li`. In the target, the first insn of the fall-through block after the first beq is `li v0,10`. In mine, dbr moved it into the delay slot. If instead the first insn were a load (`lh v1, ...`), dbr might still fill it (loads are safe) — the target's own layout shows the `lh` at 67 before the `li 4`.

OK. Let me also consider: maybe the barrier's real effect is to prevent *flow/cse* from merging and the nop arises elsewhere. But we've seen the exact difference: one nop.

Real-C constructs that block dbr's fill: an insn that can't go in a delay slot — a branch, a jump, a call, or an asm. There's no real C that emits a "non-movable" insn here without changing the code.

Actually! What about making the first branch's target block *closer* so dbr doesn't fill? No.

Let me try a few more shapes and then record the wall (need ≥30 tries):
- u1: `if (D_8011512C == 4) return; if (D_8011512C == 0xA) return;` with the first as `if (4 == D_8011512C)`.
- u2: swap: put the `== 0xA` test first and the `== 4` second, and see (t4 = 12).
- u3: `if (D_8011512C == 4) return; ret = 0; if (D_8011512C == 0xA) return;` (ret=0 is a redundant store, maybe kept as a move) — extra insn.
- u4: use `else { if ... }`.
- u5: `if (D_8011512C == 4 || D_8011512C == 0xA) { return; }` (a4).
- u6: `while (D_8011512C == 4) return;`? weird.

Hmm, what about making the *second* condition depend on the first test's result? E.g.:
```
if (D_8011512C == 4) return;
if (D_8011512C == 0xA) return;
```
→
```
if (D_8011512C == 4) return;
if (D_8011512C != 4 && D_8011512C == 0xA) return;
```
folds.

What about:
```
switch (D_8011512C & 0xF) { case 4: case 0xA: return; }
```
adds andi.

Let me try u1, u4, and a do-while(0) around the second if, plus a goto into the second block (a label at the second if — a label doesn't emit code but might create a basic block boundary! A `label:` before the second if would create a CODE_LABEL in RTL, which is a barrier-ish for dbr? Actually a label at a block head doesn't stop dbr's fill... but it might! dbr's fill_slots_from_thread stops at labels? Let me try:

```
    if (D_8011512C == 4) {
        return;
    }
L2:
    if (D_8011512C == 0xA) {
        return;
    }
```
The label must be used or gcc deletes it. If unused, gcc removes it at jump opt.

Hmm, use it: `goto L2;` before? That'd add a jump.

OK let me try a few and then record. Actually, let me reconsider the problem completely differently: what if instead of the two separate ifs I use a `switch` on a *value* so the branch structure matches? t1 = 9.

I'll do 4 more tries then record the wall.

Actually, hold on. Let me reconsider: maybe I can make the *first* beq's delay slot filled with a *nop* by making the branch's condition such that the following `li` can't be hoisted — e.g., if the `li v0,10` were actually a `move v0, <reg>` where the reg is only valid on the not-taken path? dbr checks for liveness/clobbering.

What if the second test compares against a value that's in a register only after the first branch? E.g.:

```
if (D_8011512C == 4) return;
ret = 0xA;      // no...
```

Hmm: what if the second comparison's constant is `ret`-based? no.

Let me try: make the second test use a variable that's set after the first test:
```
    s16 lim;
    if (D_8011512C == 4) return;
    lim = 0xA;
    if (D_8011512C == lim) return;
```
`lim` would be a pseudo with a constant → `li v0,10` and dbr can still fill. Same.

I'm convinced: dbr-delay-fill wall, best 9.

Wait — actually, one more: what if I *reorder the two tests* so that the target's exact sequence arises without a fill? The target is:
```
lh v1
li v0,4
beq v1,v0,ret
nop
li v0,10
beq v1,v0,ret
nop
```
Hmm, in mine:
```
lh v1
li v0,4
beq v1,v0,ret
li v0,10      <- filled
beq v1,v0,ret
nop
```
So the target has 2 nops and mine 1. The fill only happened for the first.

If I could make the *first* test's delay slot need to be a nop... 

What if the first test is `if (D_8011512C == 4) { return; }` and I add a `volatile` read after? no.

OK, let me also try one thing: what if the first test's branch target is a *far* block (not shared)? E.g. give each return its own statement... they're merged by jump opt.

Let me just try 4 more variants and record.

Actually — hmm, what about the ORDER of the two ifs being `== 4` then `== 0xA` but with the FIRST one written as a `switch`? no.

Let me try:
- v1: `if (D_8011512C == 4) { return; }` then `if (D_8011512C == 0xA) { return; }` with a `do{}while(0)` around the first.
- v2: with a do-while around the second.
- v3: `if (D_8011512C == 4) goto done; if (D_8011512C == 0xA) goto done;` where done is a label at the end (t3 = 9).
- v4: make the first test `if (D_8011512C < 5 && D_8011512C == 4) return;`? folds.

Let me run v1, v2 and 2 more.
