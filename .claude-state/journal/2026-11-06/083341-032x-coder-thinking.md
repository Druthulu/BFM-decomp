---
ts: 2026-11-06T15:33:41Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO05
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_ovVqjcg2hA9BdvaayDcD
---
Without launder, mine has `move a0,s0` where target has `addiu a0,s0,24`. So the base mb is in s0 and the +0x18 add is folded into the call arg. With launder, mine matches: presumably `addiu a0,s0,24` twice (or one addiu reused?). Target: `addiu a0,s0,24` at 107 and 109 — two separate addiu (one per call). Mine (c1): `move a0,s0` twice — the add was CSE'd into a single value held in s0 (so s0 = mb+24, and both calls pass s0). So cse computed mb+0x18 once into s0, and both call args are copies.

So to crack: make the second `mb + 0x18` not cse-unifiable with the first. C0414 dead reset: after the first call, set `mb = 0;` then... no, the second call needs mb+0x18.

Wait — actually think again. In c1, cse unified both uses of `mb + 0x18` into one expression computed once. The value computed is mb+24 (s0). The launder breaks it so each use re-adds. How do we break it in C without asm?

Idea: make the two additions syntactically different but semantically same: e.g. first call `func_8004914C(mb + 0x18)` and second `func_800491AC(&((u8*)mb)[0x18])` — cse sees same tree. Not helpful.

Idea: use a second variable set to a different expression that folds to the same address, e.g. `mb2 = mb + 0x18;` — then cse still merges.

C0414 dead reset variant: reset mb between the calls to a different value, and re-derive for the second call:
```
mb = (u8 *)&D_800AF630;
func_8004914C(mb + 0x18);
mb = (u8 *)&D_800AF630;   /* 2nd set */
func_800491AC(mb + 0x18);
```
Does the re-set break the cse equivalence for `(plus (symbol_ref) 24)`? The cse hash entry for the address expression is keyed by the RTL expression; cse's constant folding of `(plus symbol 24)` might be cached in the expression hash (not register). Actually, cse's `make_regs_eqv` and `insert` table: for a constant expression like `(plus (symbol_ref) (const_int 24))`, cse would find an existing hash entry and reuse the register holding it if still valid. The register is mb (s0) holding &D_800AF630, and then `mb+24` is computed... Hmm, but mine shows s0 = mb+24, so the register s0 holds the sum, not mb.

The moves mention for a similar launder: "launder: p = *abase; p += 0x2D (self-reassign stales cse (plus p K) equiv, bump chain stays addiu)". That is a self-reassign on the pointer: `p += 0x2D`. For our case, we can do:
```
mb = (u8 *)&D_800AF630;
func_8004914C(mb + 0x18);
mb += 0x18;      /* self-reassign: stales cse (plus mb 0x18) equiv */
func_800491AC(mb);
```
This is real C: mb becomes &D_800AF630 + 0x18, and the second call passes mb. But the target wants `addiu a0,s0,24` where s0 is the base... If mb is self-reassigned to the sum, the register s0 might hold the sum and the call arg is `move a0,s0` again — no, then target addiu wouldn't match. Let's think: target has s0 = &D_800AF630 (base) and two `addiu a0,s0,24`. So the target keeps base in s0 and adds 24 per call.

So the self-reassign must happen after computing the call arg... Actually if we do:
```
mb = (u8 *)&D_800AF630;
func_8004914C(mb + 0x18);
mb = (u8 *)&D_800AF630;   /* re-set to base */
func_800491AC(mb + 0x18);
```
then s0 could hold base, and each call does addiu a0,s0,24. But cse might still unify the two (plus) expressions into one register across the call... The re-set of mb to the same constant value: cse's table has mb = &D_800AF630 after the set. The hash entry for (plus (symbol) 24) was created at the first use and holds the register? But if cse reused it across the call, it would need a callee-saved register (s0) and indeed c1 shows s0 holding the sum across the call. The re-set of mb doesn't invalidate the hash entry of the sum; the sum's register is still live. Hmm, cse's hash table is per-basic-block? No, cse is global per EBB.

Alternative approach: make the second call's base a different pointer variable computed separately:
```
u8 *mb2;
mb = (u8 *)&D_800AF630;
func_8004914C(mb + 0x18);
mb2 = (u8 *)&D_800AF630;
func_800491AC(mb2 + 0x18);
```
cse: mb2 = &D_800AF630 (same value as mb), then mb2+24 — cse's hash for (plus (symbol) 24) exists, so it reuses... it would reuse the register from the first computation if valid. Unless the first sum's register is not valid because it was computed before the call and... no, cse holds it across calls if needed (it's a constant, rematerializable? cse might not keep it across a call if it can't). Actually in c1, it did keep it in s0 across the call — because cse reused it and regalloc put it in a callee-saved reg.

Hmm, but wait: with launder, target does two addiu. The launder is an asm that makes mb an "unknown value", so cse's knowledge that mb == &D_800AF630 is killed after the asm, hence the second mb+24 can't fold to the symbol and must be computed. That's the key: the launder redefines mb to an unknown value, so cse doesn't know it's a constant address.

To replicate in plain C: make mb's value unknown to cse after the first call. E.g. pass mb through an opaque function? No. Use a volatile? Not allowed maybe.

C0414 dead reset is the documented plain-C replacement: set the variable to 0, then... but we need the value for the second use.

What if we reuse mb as the base for a different symbol, then reset? Hmm.

Alternative: assign mb from a non-constant expression that happens to be the same address at runtime but cse can't fold: e.g.
```
mb = (u8 *)&D_800AF630;
func_8004914C(mb + 0x18);
mb = (u8 *)(&D_800AF630);  // same
```
no.

What about making the second use go through a variable whose value cse sees as derived from mb but not constant:
```
mb = (u8 *)&D_800AF630;
func_8004914C(mb + 0x18);
mb = mb + 0x18;       // mb = base+24
func_800491AC(mb);
```
Here the call arg is mb (a register), target expects addiu a0,s0,24. But if s0 holds base+24, the call arg is `move a0,s0`, not addiu. Unless gcc keeps base in s0 and computes mb into a temp... Let's just test variants; cheap.

Variants:
A) re-set to base between calls.
B) self-increment: mb += 0x18 before second call, call mb.
C) two variables mb/mb2 each set to base.
D) mb = (u8*)&D_800AF630; first call mb+0x18; mb = (u8*)&D_800AF630 + 0x18; second call mb.
E) C0414-ish: after first call `mb = 0;` then `mb = (u8*)&D_800AF630;` then call. The intermediate 0 might kill cse class.

Let me write these as candidates. Since there are 3 sites, I need to modify all 3 consistently (they're identical). I can do sed replacements.

The site text:
```
    mb = (u8 *)&D_800AF630;
    func_8004914C(mb + 0x18);
    func_800491AC(mb + 0x18);
```
(after removing launder lines). Wait in c1 the launder lines were removed leaving:
```
    mb = (u8 *)&D_800AF630;
    func_8004914C(mb + 0x18);
    func_800491AC(mb + 0x18);
```

Variant D: replace the 3 lines with:
```
    mb = (u8 *)&D_800AF630;
    func_8004914C(mb + 0x18);
    mb = (u8 *)&D_800AF630 + 0x18;
    func_800491AC(mb);
```
Hmm.

Actually, wait. Let me reconsider the target's exact instruction sequence. Let me disassemble orig (target) around insn 100-115 to see the full shape.
