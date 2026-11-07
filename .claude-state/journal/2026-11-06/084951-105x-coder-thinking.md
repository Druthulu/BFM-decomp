---
ts: 2026-11-06T15:49:51Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO04x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_mToOCdxOGuxe5YfyIYkP
---
Still 6. Hmm, the pattern didn't work here. Maybe the tree-level passes removed the keep/reset before RTL? Or cse still folded.

Let me check the c1 cse dump... Actually, let me reconsider. In item 3 the pattern worked because the *second* expression's operands were `d` and `n`, and the reset made n's value opaque. Here the reset+restore makes mb ≡ keep, and cse's fold_rtx for `(plus mb 24)`: mb's value is keep's value, which is... the old mb = symbol. Does cse know keep's value is the symbol? Yes: `keep = mb` and mb = symbol → keep ≡ mb (same qty) with the symbol value. After `mb = 0` the qty is invalidated; `mb = keep` re-links them, but does cse still know the qty's *constant value* (symbol)? The invalidation removes the table entries; the qty itself may still have the constant value recorded in qty_const. Hmm, `invalidate` may clear the qty's constant too.

Apparently it still folded. Let me dump c1's cse quickly. Actually, maybe the tree-level (front end) already propagated `keep` — no.

Let me check whether the reset/restore even survived to RTL: grep the c1 TU's RTL dump. That takes time. Let me instead try variations:

c2: `mb = 0;` then `mb = (u8 *)&D_800AF630;` (recompute the symbol) — cse knows the constant again → folds.

c3: use a keep variable and use *keep* in the second call: `func_800491AC(keep + 0x18);` — then the expression uses keep, whose value is the symbol → folds.

Hmm.

Maybe the real mechanism in the target: the asm's opaque set makes the *base register* unknown, so the second plus can't fold, AND the allocator keeps the base in s0.

What if I make the second expression use a *different symbol expression* that combine can't fold to the same constant but computes the same address? E.g. `(u8 *)&D_800AF630` vs `(u8 *)&D_800AF630`. Same.

What about using the address of a different symbol at the same location? Not available.

Hmm, what if the base is loaded through a *global pointer variable*? e.g. `u8 **g = &D_800AF630_ptr;` no.

Let me look at what the target's first call actually is again: `lui s0,0; addiu s0,s0,0` — the base in s0 — and the arg `addiu a0,s0,24`. Note: the base in s0 is used by BOTH calls. In the orig, the base reg 82 is live across both calls (s0 callee-saved).

In mine, s0 = base+24 (the folded constant), also live across both calls.

What if I make the *first* call's argument computed as an addiu by using a different expression form? E.g. `func_8004914C(mb + 0x18)` where mb is a variable — cse folds. 

Hmm, what if mb is declared `volatile`? That's a barrier lever (not allowed).

What about making the +0x18 come from a variable: `s32 off = 0x18; call1(mb + off); ...` — cse still folds (off is constant).

Hmm.

Let me look at the problem from the allocator angle: maybe I don't need to break the cse fold; maybe I need s0 to hold the base instead of base+24. If both calls use the same folded address reg (base+24), the target would be `move a0,s0` twice — that's mine. The target has addiu, so the fold must be broken.

OK, what if we make the two calls' arguments use *different* base registers: 
```
u8 *mb = (u8 *)&D_800AF630;
u8 *mb2 = mb;
call1(mb + 0x18);
call2(mb2 + 0x18);
```
cse merges mb2 with mb → same.

What if mb2 is assigned inside a conditional so cse treats it as a merge point:
```
u8 *mb2;
if (something always true) mb2 = mb; else mb2 = mb;
```
flow folds.

Hmm.

What about a *real* dead-reset that cse can't undo: `mb = 0;` and then compute the second address from a *fresh* symbol reference that's a different RTL constant expression: `(u8 *)&D_800AF630 + 0x18` — the RTL is `(plus (symbol_ref) 24)` which combine folds into a `const` → lui/addiu (2 insns). The target has 1 addiu off s0. Not matching.

Wait... actually, is that true? Let me check what gcc does with `func_800491AC((u8 *)&D_800AF630 + 0x18)` — b2 scored 6, same as a1. Let me look at b2's asm to see. If b2's second call used a fresh lui/addiu, the score would differ more. It scored the same 6, meaning it also ended up with move a0,s0 (cse merged anyway).

Hmm.

Let me reconsider the actual difference. Maybe the target's second `addiu a0,s0,24` is NOT from a separate plus but from... Let me count the instructions. Target 397, mine 397. The only diff is the 6 `move a0,s0` vs `addiu a0,s0,24`. So the base is in s0 in both; only the +24 differs.

In mine: s0 = base+24, a0 = s0 (move).
In target: s0 = base, a0 = s0+24 (addiu).

So the target keeps the *base* in s0 and adds 24 per call. The C source has `mb + 0x18` twice. For the compiler to keep the base, cse must not fold `mb+24` into a constant. But the FIRST call's plus also isn't folded (it's addiu too).

In the orig RTL, insn 232 `(plus 82 24)` has REG_EQUAL const(symbol+24) — so gcc DID know it's a constant, yet the final code is addiu off s0, not lui/addiu. Because the allocator chose to keep the base 82 in s0 and compute the plus per use (140 and 141 are separate regs, each computed by an addiu; the constant REG_EQUAL is just an optimization hint).

In mine, cse merged 141 into 140 (a0 = 140), so only one plus exists, and the allocator put 140 in s0? Hmm, but then both calls do move a0,s0.

Wait, in mine, insn 232 = plus(82,24) → reg 140, a0 = 140, call1. Then insn 241 = a0 = 140 (the second use folded to 140), call2. So 140 is live across call1 → callee-saved s0. And 82 (the base) is dead after 232 → not kept. So s0 = 140 = base+24.

In the orig, 140 and 141 are separate, each computed fresh. Then the allocator: 82 (base) is live across calls (needed for 141) → s0. 140 and 141 are each computed into a0 (the addiu in the delay slot). 

So the ONLY thing needed: prevent cse from folding the second `(plus 82 24)` to 140. The asm does it by making 82 unknown.

So I need a real 2nd set of mb between the calls that cse cannot see through, value-preserving.

My keep/reset/restore didn't work. Let me verify what it produced — maybe the front end or cse eliminated it. Let me dump c1's cse quickly. Actually let me try a different formulation: `mb = 0;` (dead) and then `mb = (u8 *)&D_800AF630;` — no.

Hmm, what about `mb = mb + 0x18;` (mb now base+24) and then `call2(mb)`, then restore? For the third face, mb is re-assigned at the top, so:
```
mb = (u8 *)&D_800AF630;
call1(mb + 0x18);
mb = mb + 0x18;     // mb = base+24 (real 2nd set, value CHANGED but consistent)
call2(mb);
```
Then call2's arg is `mb` (base+24). cse: `(set mb (plus mb 24))` — the new mb's value is the old expression. The RTL: mb_new = plus(mb_old,24); a0 = mb_new. The allocator: mb_old (base) is live across call1 → s0; mb_new computed... but `mb = mb + 0x18` means mb_new = s0+24, and a0 = mb_new → addiu a0,s0,24? Or move a0,mb_new? If mb_new is a separate pseudo, the allocator might coalesce mb_new into a0 and emit `addiu a0,s0,24`. That's exactly the target's second call!

And the FIRST call: `call1(mb + 0x18)` — cse with the fold: `(plus 82 24)` → reg 140; but now mb (82) is redefined later, so 82 must stay live → s0. And 140 = plus(82,24) is used only at call1 → a0 = addiu a0,s0,24 in the delay slot. 

That would give: base in s0, both calls addiu a0,s0,24. EXACTLY the target!

Let me test: replace the second call's argument with `mb` after `mb = mb + 0x18;`. But careful for the 3 faces: each face starts with `mb = (u8 *)&D_800AF630;` so it's fine.

The pattern per face:
```
mb = (u8 *)&D_800AF630;
func_8004914C(mb + 0x18);
mb = mb + 0x18;
func_800491AC(mb);
```
Semantically identical (mb's value used later? mb is reassigned at the next face).

Let me test this (d1).
