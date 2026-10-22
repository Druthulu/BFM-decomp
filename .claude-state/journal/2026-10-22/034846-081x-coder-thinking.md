---
ts: 2026-10-22T09:48:46Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM2
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_TieM56kJo2GOrIaAslYe
---
expr.c calls expand_expr but doesn't define it (it's in expand.c, not available).

OK. Let me stop the source archaeology and take the practical path: I have a strong model of the mechanism:

- Without the launder: p is a constant-initialized local → expand substitutes the symbol into the address → combine's simplify_rtx swaps (constant last) → "addu v0,v0,a1" (index first).
- The target: "addu v0,a1,v0" (pointer first) → the tree had a REG first operand.

Ways to get a REG first operand lever-free:
(a) Make p's value NOT a constant at expand time. E.g., p = something runtime.
(b) Make the address's first operand a non-constant expression, e.g. (plus (reg idx) (reg p)) — but that's index first → wrong.

Hmm (b): what if the tree were (plus (reg X) (reg Y)) where X = the pointer? We need the pointer in a reg.

(c) What if the pointer's value is derived from a LOAD of a global pointer variable? Semantics change.

(d) What if the pointer comes from a *function call*? no.

Hmm, what about (e): the pointer is obtained from the *same* address expression as the newval load, i.e. the address is computed once into a temp that is used twice — the temp would be a REG (the address value, not the pointer).

Hmm! Interesting: what if we compute the address into a temp pointer:
```c
u8 *pa = (u8 *)p + off;      /* pa = symbol + off → a reg (the address) */
D_801270C8 = *(s16 *)(pa + 4);
```
Here the address = (plus (symbol) (reg off)) — same swap issue? The tree for pa's value: (plus (symbol) (reg off)) — a REG result! Then the load uses (plus (reg pa) 4) → (reg pa) is a reg → the load's address is (plus (reg pa) (const 4)) → constant last ✓ no swap → the load would be "lh v0,4(pa)" — but the target has "addu v0,a1,v0; lh v0,4(v0)" (an explicit add). So v08 (tmpsplit) would differ — indeed v08 had a compile error; let me fix it (declare pa at the top of the block).

Wait, but that changes the asm: the target computes the address with an explicit add into v0 then loads with +4. If we use a temp pointer pa = p + off (without the +4), then the load is `lh v0, 4(pa)` — one instruction fewer (no add). Unless the +4 is also in the temp: `pa = (u8 *)p + off + 4;` then the load is "lh v0,0(pa)" → also one fewer.

Hmm, so the target's form (explicit addu then lh with displacement 4) arises naturally from `(u8*)p + off + 4` where the +4 folds into the displacement.

OK so (e) doesn't give the target's shape.

Let me think about (a) again: how can p's value be non-constant at expand time but still equal &D_80195AF6 at runtime, without a lever?

Option: p = &D_80195AF6[0] where the array is... constant.

Option: the pointer could be a *global variable* holding the address — not present.

Option: p could be derived from a0! E.g. is D_80195AF6 related to a0? No.

Hmm, option: what if the pointer is *not* a variable at all and instead the address expression is written to keep the symbol in a reg? Like using a MEM with a symbolic base: `*(s16 *)((u8 *)D_80195AF6 + off + 4)` — the tree would be (plus (symbol) (reg off)) → same.

Hmm. So how did the ORIGINAL source produce a REG??

MAYBE the original source had the pointer as a *parameter* of an inlined function, or the original had:

```c
D_80195AF6_t *p = D_80195AF6;
```
and gcc 2.7's expand substituted the constant only because of some property of OUR source (e.g. our p is a local declared inside a block, while the original's was at function scope?).

Hmm! That's a thought: maybe the substitution depends on the variable's scope/where the initializer is. Let me test: declare p at the top of the function (v09 did that but errored). Let me fix v09 and v08 and re-run.

Also worth testing: p declared as a *function-scope* variable assigned in the arm (v09).

Let me fix the variants:
- v08: declare `u8 *pa;` at the top of the else-block... the else block starts with "            D_80195AF6_t *p = D_80195AF6;" — I can add "u8 *pa;" next to it.
- v09: the error — let me see it.

Let me re-run those two with the error shown.
