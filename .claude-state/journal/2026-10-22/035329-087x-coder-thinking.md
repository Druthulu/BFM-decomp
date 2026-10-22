---
ts: 2026-10-22T09:53:29Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM2
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_njQp48I7G1Trv5rfPhUB
---
All 1 (except v65 = 2). The mechanism is robust: the address's first operand ends up a constant → combine's constant-last swap.

Interesting: v66 `(u8 *)off + (u32)(u8 *)p + 4` also gives 1 — so the tree (plus (reg off) (symbol)) → no swap (the first operand isn't a constant) → the asm would be "addu v0,v0,a1" (index first) — the same as before, so score 1 ✓ consistent.

Hmm! So in v66 the tree's first operand is a REG (off) and the second is the symbol → no swap → the asm is index-first. That confirms the mechanism.

So we need the tree (plus (reg PTR) (reg idx)) — with the pointer in a REG.

Now: in v66 the symbol is in the second position and is NOT substituted (it's a symbol in the tree). Interesting: so cse/expand DID substitute p's constant into the address in the other variants.

Hmm, so in v66, is the tree (plus (reg off) (symbol))? Or (plus (reg off) (reg p))? Either way, the pointer is second.

What if I write the address so the pointer comes first but is NOT a constant at expand: e.g. `*(s16 *)((u8 *)p + off + 4)` where p's value... ugh, circular.

NEW IDEA: What if the pointer's value comes from the *second* operand of a plus that gcc can't fold? Hmm.

NEW IDEA 2: What if we make the address's base a *MEM* (memory operand)? E.g. the address = `&some_global` — no.

NEW IDEA 3: Since the swap requires XEXP(x,0) to be a CONSTANT — what if the first operand is a constant but the SECOND operand is also a constant? Then no swap (the condition requires XEXP(x,1) != CONST_INT). Hmm: the condition is (CONSTANT_P(XEXP(x,0)) && GET_CODE(XEXP(x,1)) != CONST_INT). If XEXP(x,1) were a CONST_INT, no swap! But our index is a reg, not a const.

Hmm, but what if the *whole address* were (plus (symbol) (const_int))? Then the constant folds entirely.

NEW IDEA 4: What if the first operand is a constant but wrapped: e.g. (plus (const (symbol)) (reg))? CONSTANT_P(CONST) is true → still swaps.

NEW IDEA 5: The swap happens in simplify_rtx — which is called on the MEM source. What if the load's address is NOT a MEM but a REGISTER (i.e. the address is computed into a reg first)? Then simplify_rtx is called on the SET source = (plus ...) — hmm, the same swap would apply to the PLUS.

Hmm, unless the PLUS's first operand is a REG in that case: e.g. `pa = (u8 *)p + off;` → the SET source = (plus (symbol) (reg off)) → swap → (plus (reg off) (symbol)) → "addu v0,v0,a1"... and then the load `*(s16 *)(pa + 4)` → "lh v0,4(v0)" (one insn fewer) → count 110 ✗.

OK. I've spent a LOT on this. Let me now consider the possibility that the wall is real for item 1 and move on to the other items, which might be more tractable.

Actually hold on, one more idea, and it's a good one: **the pointer could be a REG if the compiler cannot see it as a constant because the pointer is stored in a `u8*`-typed variable that is ASSIGNED from a non-constant expression**...

Hmm no. Let me think about the ACTUAL original source once more. The target's asm has the pointer materialized into a1 at the ARM START (2c0c) — i.e. the pointer pseudo lives across the whole arm (from the arm's start to the final add). In our compile, the same happens (a1 materialized at the arm start). So both have a pseudo for the pointer.

In ours, the pseudo's value is the symbol (expand substituted it at the use). In the target, the use referenced the pseudo.

Hmm, so the ONLY difference is whether expand substituted.

Hmm, let me look at the expand.c source from a DIFFERENT gcc version we might have... The papermario tree has expr.c — in gcc 2.7, `expand_expr` is in expand.c, but expr.c has `expand_expr` calls. Hmm.

Wait, actually: maybe I should look at gcc-papermario's expr.c for the REG case handling — in gcc 2.5, expr.c DID contain expand_expr. Let me check if expr.c has "expand_expr (tree_exp, ...)" definition.
