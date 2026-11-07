---
ts: 2026-11-06T10:17:15Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG27x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_QLDWqVfFfn1CMCo24mHP
---
b7 scored 29 (worse). b4 18. None hit.

I'm burning time. Let me reconsider the whole approach for these pin items.

Let me look at the moves.md for the exact tag "lreg-qty-order" and see if there's a known crack. Line 178 is a WALL. Line 143 WALL. 

Hmm, but maybe there's a MATCH for a similar case. Let me search moves.md for "MATCH" lines mentioning "pri" or "priority" or "qty".

Actually, let me reconsider the problem from the perspective of: the pin is `register s32 div __asm__("$16")`. What does the pin actually do? It forces div into s0. But maybe it ALSO affects the RTL: `register ... __asm__("$16")` makes the variable a hard register, so `div` IS s0 throughout. The divs use s0 directly.

Lever-free, div is a pseudo. The allocation gives it s1.

To get div→s0, we need div's priority > a's. 

Let me look at the RTL birth/death precisely. Let me grep the lreg for item 3's function and find r76/r77 birth/death.

Let me use alloc_table's numbers: nopin: r76 (a?) pri 6086 refs 7 live 23; r77 (div?) pri 5384 refs 7 live 26. Wait, in nopin, which is which? nopin asm: "s1->s0 x7, s0->s1 x4" — mine has a in s0? Let me check: nopin mine[2] move s0,a2 (a→s0), mine[4] move s1,a3 (div→s1). So a=s0 (r76, pri 6086), div=s1 (r77, 5384).

So a: refs 7, live 23. div: refs 7, live 26.

To flip: div's pri > a's. 

Idea: increase div's refs to 8. Since refs = number of occurrences in insns, and div appears in the div instructions + bnez checks... 

Hmm, what if the divisor is used in a THIRD place that doesn't add an instruction? Like if the source computed `q = diff / div` in a way that the compiler emits the same. 

What if we write `div = (s16)div` as `div = (s16)(div + 0)`? adds.

Hmm.

Idea: decrease a's refs to 6. a appears in: move(def), andi(use+def), bne(use), subu(use), addiu(use), addiu(use). If we could make the `if (a == cur)` comparison use a *different* expression... 

What if `cur` is computed as `ang & 0xFFF` and a as `arg2 & 0xFFF`, and we write `if ((a & 0xFFF) == cur)`? Then a's mask is inside the comparison, and the `a = a & 0xFFF` statement is removed. Then a is used in: move(def), the comparison's mask (use), subu (use), addiu (use), addiu (use) = 5 refs? But then the andi would be recomputed... Actually if we write `a = arg2; ... if ((a & 0xFFF) == cur)`, then `a & 0xFFF` is computed once and cse'd. Hmm, but the masked value is also used in `diff = cur - a` etc. — those use the masked a. So we'd need `a = a & 0xFFF` anyway.

Hmm.

Idea: make a's live LONGER (to 27+). a's death is at `t = a - 0x1000`. If I move the `t = a + 0x1000` computation AFTER `t = a - 0x1000`... the order changes.

Hmm.

Let me step back and consider the possibility that these items are genuinely hard walls, and the shard expects mostly WALLs. The brief says "write a lever-free body ... that scores 0" but also defines WALL as an acceptable result (with evidence). Given the difficulty, maybe the intended outcome is WALL for all 4? That seems odd for a shard.

Let me reconsider item 3's target more carefully. The target's div is s0 and a is s1. Let me compute what the target's RTL priorities would be if the source were EXACTLY our nopin. We got a=6086, div=5384. The target needs div > a. So the original source's RTL must differ.

What if the original source had `a` as a *different type* making its qty size larger? No.

What if the original source computed `a` later (after the ang computation), shortening a's live and... no, shortening a's live INCREASES a's pri.

Wait — I need a's pri LOWER. So a's live must be LONGER or refs fewer. If a is born EARLIER, its live is longer. In the source, `a = arg2` is the first statement. If we move it even earlier... it's already first.

Hmm, what if `a` is initialized at declaration `u32 a = arg2;`? Same.

What if a's last use moves later? The last use is `t = a - 0x1000` in the second if-block. The second if-block is before the divisions. If we moved `a`'s use into the division blocks... no.

OK, what if we increase div's refs by making the sign-extension a *separate* statement with a cast? `div = (s16)div;` → sll+sra (2 insns, refs: use+def). What if we write `div = (s16)(div & 0xFFFF);`? Same.

Hmm.

Let me try yet another approach: use `register` without asm on div. In gcc, a `register` variable might get `reg_preferred_class` = GR_REGS but that's the same. No.

Let me try: make `div` a *parameter* pseudo used directly (no local variable). Then the pseudo for arg3 is live from entry to the divs. Its refs might be different. v4-like. Let me test for item 3: remove `div` and use `(s16)arg3` in the divisions.

Actually, a6 did `div = (s16)arg3` at decl and scored 40 (72 ins). Let me try `q = diff / (s16)arg3;` (no div variable).

Let me also try making `a` a separate variable for the mask: `s32 am = a & 0xFFF;` used later, and `a` local. Hmm.

I think I should timebox item 3. Let me do a couple more tries then mark WALL if needed.

Actually, let me look at the alloc table's "live" definition: qty_death - qty_birth. For div: birth at insn ~8 (move), death at insn ~34 → 26. For a: birth at ~6, death at ~29 → 23.

If I move `div = arg3` LATER in the source (e.g., after the ang computation), the RTL birth of div moves later, but gcc must copy arg3 before the call. How does gcc handle `div = arg3` placed after the call? The pseudo for arg3 would be live across the call → global, and the copy is at the prologue. Actually, gcc's expand would emit `(set (reg div) (reg a3))` at the point of assignment (after the call), which is WRONG since a3 is clobbered. But gcc knows a3 is clobbered; it would keep arg3 in a pseudo and the copy `move s0,a3` in the prologue. Hmm, actually the assignment `div = arg3` after the call would emit a move from the a3 hard reg... which is invalid. GCC handles this by `load_register`? Hmm.

Actually, when a function parameter is used after a call, gcc (with -fcaller-saves or global-alloc) assigns the parameter pseudo to a callee-saved register and copies at entry. The RTL is: the parameter's initial move (from a3 to the pseudo) at function entry. So the birth is at entry regardless of where the source uses it.

So div's birth is fixed at entry.

Then live = death - birth, and death is the last use. To shorten, move the divs earlier — impossible (they're last).

Therefore, in the target, div's live MUST be > a's (div dies later). So the target's div pri < a pri by live. Yet the target has div in s0. So the target's REFS must differ: div refs > a refs by enough.

Target: div refs must be ≥ 8 (so floor_log2=3) while a refs 7. OR a refs ≤ 6.

Let me count refs more carefully from the RTL. The alloc table says both 7. Hmm.

Wait — maybe in the original, `a` was NOT masked in place; maybe `a` was used as the raw arg2 and a separate `cur`-like variable held the masked value. Then a's refs would be fewer. Hmm, but the target has `andi s1,s1,0xfff` in-place, meaning the masked value IS a (same register). If a were a separate masked variable `am = a & 0xFFF`, the andi could be `andi s1,s0,0xfff` (different regs) — target is in-place, so a is masked in place.

Unless the original used `a` only for the masked value: `u32 a = arg2 & 0xFFF;`? Then the andi would be in the prologue (right after the move), not after the call. Target has it after the call. Hmm.

Hmm, unless the `andi` after the call is because the mask statement is after the call in the source: `a = a & 0xFFF;`.

OK let me try to give div an extra ref via a *real* C construct that adds no instruction. What about `if (div) ...`? adds a branch.

What if the division is written with an explicit `(s16)` cast at each use, but cse merges them? `q = diff / (s16)div;` twice. Then div's refs: the cast uses div twice → more refs, but the sign-ext would be recomputed? cse might keep one. Let me test: keep `div = arg3;` (no sign-ext), and use `(s16)div` in the divisions. Then the sign-ext (sll/sra) would be hoisted by cse to... where? Maybe block 0 (after the call), matching the target's `sll s0,s0,0x10`. And div's refs would increase (2 casts + 2 divs). Let me test.

Actually that's promising! Let me test:
```
div = arg3;
ang = ...;
a = a & 0xFFF;
cur = ang & 0xFFF;
...
q = diff / (s16)div;
```
The cast (s16)div at each division. CSE would create one sign-extended temp and reuse it. The temp's refs... div's refs: def + 2 cast uses = 3? Hmm, fewer.

Hmm, actually the sign-ext temp would be global (used in 2 blocks). div would be local-ish? No, div is used in 2 blocks (the casts) → global.

Let me just test it.

Let me also test `a = a & 0xFFF` vs `a = arg2 & 0xFFF` placement.

Time: 03:19. Let me do a final batch for item 3, then decide.
