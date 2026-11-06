---
ts: 2026-10-22T16:18:07Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG16
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_hc24uevsm6Jn1RpEfPQE
---
At the pre-pass RTL, the first compare is `(ne:SI (reg 73) (reg 72))` = (it, p), with the branch to a fall-through label 32 and then a jump to zero. That's `if (it == p) goto zero;` expanded as `if (it != p) goto body` + `goto zero`. So GCC inverted the condition: EQ → NE with swapped labels. Then later (cse2) it became `(eq (72) (73))` = (p, it) — i.e., the condition was inverted back and the operands swapped by the `jump`/`cse` optimization ("jump bypass" / `invert_jump`). The `invert_jump` for a NE with two regs uses `gen_rtx_fmt_ee (EQ, ...)` and calls `swap_operands`? Something in `jump.c`'s `invert_jump_1` or `redirect_jump` may swap operands to preserve the delay slot.

So the branch operand order is determined by the optimization, not the source. But the target has (it, p) = beq v1,a0. Mine ends with (p, it) = beq a0,v1. So the target's compiler ended with the EQ in source order.

Difference: the target's C might have written the comparison as `if (p == it)` so that after inversion/swap it lands as (it,p)? Let's trace: source `if (p == it) goto zero` → expand: NE (p,it) goto body; goto zero. Then invert: EQ (it,p) → beq v1,a0 = target! So `if (p == it)` should give the target. But q14 (`if (p == it)`) scored 1 with the same beq a0,v1. Hmm, so q14 gave (eq p it) as well? That means the invert doesn't swap, and the source order is preserved through expand/invert: `if (p == it)` → NE(p,it) → invert to EQ(p,it) → beq a0,v1 (same as mine). And `if (it == p)` → NE(it,p) → invert to EQ(it,p) → beq v1,a0. But q9 (`it == p`) gave beq a0,v1! Contradiction.

Unless q9's C's `if (it == p)` was transformed differently. Let me re-check q9's C: 
```
test:
    p = it + 0x658C;
    it = (s32)D_801202A0;
    if (it == p) goto zero;
```
Yes. And the pre-pass RTL shows NE(it,p) → so invert gives EQ(it,p) = beq v1,a0 expected. But cse2 shows EQ(72,73) = (p,it). So something swapped between .rtl and .cse2 — likely `cse`'s `fold_rtx` canonicalizes comparisons by swapping operands to put the *more expensive* / *lower-numbered* first? In cse.c's fold_rtx for EQ, there's code that swaps operands if one is a constant; not for regs.

Hmm, maybe the `combine` or `jump` pass. The cse2 dump shows the swap already. Let me check the `.cse` (first cse) dump: is the EQ (it,p) or (p,it)? And `.combine`. Let me grep each pass dump for the if_then_else order around this compare.

Actually the cse2 dump is *after* cse2 (the second cse). The first cse dump (.cse) would show the order after cse1. Let me check .cse and .combine.

If the swap happens in cse1's `fold_rtx`, maybe the reason is that `reg 72` (p) has a REG_EQUAL `(plus (symbol) K)`? p = it + K where it has REG_EQUAL symbol → p's REG_EQUAL is (plus symbol K). Hmm, then cse could fold the compare to a constant (symbol+K vs symbol) — but it doesn't because it's a jump.

Alternatively, the *target*'s C had p computed differently so that the compare order stayed. 

This is getting deep. Let me approach empirically: generate variants that change the *branch structure* so that the final encoding lands as beq v1,a0. Ideas:
- Write `if (it != p) goto body; goto zero;`? The source would be `if (it != p) goto body;` then fallthrough to zero. That's the *uninverted* form: NE(it,p) → beq? The .rtl showed exactly this: NE(it,p) goto body, goto zero. And the final code is beq a0,v1. So the invert+swap gave (p,it).
- Write `if (it == p) goto zero;` → same.

What if I write the compare with the *other* variable order and also change the CFG so no inversion happens? E.g. put the zero block after the compare (fallthrough) so the branch is a straight `beq it,p` without inversion:
```
test:
    p = it + K;
    it = B;
    if (it != p) goto body;
    return 0;      // zero block fallthrough
body:
    ...
```
That's the same CFG as the target? The target's layout: test: it=B; beq it,p,zero; move v0,0; body: ... The zero block is at the end (label 65). So the branch is `beq it,p` to zero. If GCC emits it as NE to body (inverted), the layout differs.

Actually, GCC's if-conversion: `if (it == p) goto zero;` where zero is later → expand as NE to the next label (body) + jump to zero. Then `jump` optimization may invert and redirect. The final beq order is what it is.

Let me try the C written as:
```
if (it == p) return 0;
body:
...
```
That gives the same tree.

Hmm, what about `if (p == it) return 0;`? tried (q14) → 1.

What about avoiding the comparison entirely by using a subtraction and a branch on zero? q16/q18 gave 1.

Maybe the operand order difference comes from `reg 72` (p) having a REG_EQUAL that makes cse's `fold_rtx` swap. If p's value were not a REG_EQUAL (e.g., p computed with a real 2nd set), the order might not swap. But p = it + K with it = symbol → REG_EQUAL (plus symbol K).

What if we prevent p's REG_EQUAL by making p's computation non-foldable: `p = it + K` where the addition is not a constant... e.g., `p = (s32)((u8 *)it + 0x658C)` — same RTL.

Alternatively, if p were a *memory* value? no.

Let me test a batch of CFG/compare spellings with the q9 structure:
r1: `if (it != p) goto body; return 0; body:` (explicit inverted form, zero fallthrough)
r2: `if (it == p) return 0;` then body (no goto zero)
r3: `if (p != it) goto body; return 0;`
r4: `if (p == it) return 0;`
r5: use `do { if (*(u16*)it == 0) return it; it += 0x10C; } while (it != p); return 0;`
r6: `if (it != p) { ... } return 0;`
r7: swap the order of the `it = B` and `p = it + K` statements? p needs it=A. Could compute p first then it=B — q9 already does that.

Actually, maybe the target's C computes p *inside the test block* before `it = B`, exactly q9. And the branch order difference is a register-number artifact: maybe the target's C declared the variables in a different order, so p and it got *different pseudo numbers* and the cse swap (which may order by pseudo number) produced (it,p). In mine, p is pseudo 72 and it is 73; the compare at cse2 is (72,73) = (p,it). If in the target p were pseudo 73 and it 72, the swap would give (72,73) = (it,p) = target! So the difference could be the *declaration order* / pseudo numbering: q9 declares `s32 p; s32 it;` → p=72, it=73. If we declare `s32 it; s32 p;` → it=72, p=73 → cse's canonical order (72,73) = (it,p) → beq v1,a0 = target!

That's a very plausible mechanism: cse's fold_rtx canonicalizes (eq a b) by swapping to put the lower pseudo number first? Let me test: q19 = q9 with `s32 it; s32 p;` declaration order.

Actually in the original src, the declarations are `s32 p; s32 it;` (p first). The lever-free base too. But q9 has p,it. Let me test it,p.

Let me run a batch of these.
