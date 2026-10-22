---
ts: 2026-10-22T07:20:45Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG15b
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_ZnVPCwTJNBhZtmz8fkHt
---
Now I can see the structural difference:

TREE:
- insn 266: `(set (reg:SI 145) (mult ...))` — the ×127 product in pseudo 145.
- insn 268: `(set (reg:SI 147) (const_int 1717986919))` — the magic constant in pseudo 147.
- insn 269: the division (mult of 145 by 147).
- insn 270: (set 148 ...), 271: (set 149 (ashiftrt of 145)), 273: (set (reg/v:SI 137) ...) — the division result → pseudo 137? Hmm, insn 273: `(set (reg/v:SI 137) ...)` with REG_EQUAL (div:SI 145) — so 137 = the quotient.
- insn 275: the ASM: `(set (reg/v:SI 137) (asm_operands ...))` — the launder: a 2nd set of pseudo 137 (vol's pseudo).

So in the tree, vol's pseudo is 137 and it gets: the division result (273) and the asm's copy (275) → 2 sets ✓.

C2 (my compound divide):
- insn 266: `(set (reg/v:SI 137) (minus ...))` — hmm, 137 holds the product (0xA0 - av)...
- insn 269: (set (reg:SI 147) const) — the magic.
- insn 270: the division: `(truncate (lshiftrt (mult (sign_extend (reg/v:SI 137)) (sign_extend (reg:SI 147)))))` — the dividend is pseudo 137 (which holds the product).
- insn 271: (set 148 ...), 272: (set 149 (ashiftrt of 137)), 274: `(set (reg:SI 145) ...)` with REG_EQUAL (div:SI 137) — the quotient in pseudo 145.
- insn 276: `(set (reg/v:SI 137) (reg:SI 145))` — the copy of the quotient INTO vol (137).

So in C2, vol's pseudo 137 = the product initially, then the quotient is computed into 145, then copied back into 137. So vol (137) has 2 sets: the product (266) and the copy (276)!! Interesting — so vol has 2 sets in C2 as well (the product and the final copy) ✓ (that's why the multiply order got fixed).

But the structure differs: in the tree, 137 = the quotient (1 set) + the asm (2nd set); in C2, 137 = the product (1 set) + the copy of the quotient (2nd set).

The tree's pseudo 145 = the product (1 set); C2's 145 = the quotient.

The KEY difference for the allocation: in the tree, the division's dividend (145) is a separate pseudo from vol (137); in C2, the dividend IS vol (137) and the quotient is a separate pseudo (145) copied back.

So the register allocation differs: in the tree, the dividend pseudo 145 got v1 and the quotient 137 got a1; in C2, the dividend (137) got a1 and the quotient (145) got... hmm.

Let me now find a spelling that gives the TREE's structure in plain C:
- The division's result assigned to vol directly: `vol = X / 0xA0;` ✓ (the tree's structure: the quotient → vol).
- And vol needs a 2nd set: the tree's is the asm's self-copy.

So: `vol = ((0xA0 - av) * 0x7F) / 0xA0;` (one expression, the quotient → vol ✓) + a 2nd set of vol.

The 2nd set must be a copy that emits nothing. In the tree it's `(set 137, asm_operands)` — a self-copy of vol (the asm's tied output).

In plain C, `vol = vol;` gets removed by cse. But `do { vol = vol; } while (0);` survives as a 2nd set (as we saw in item 3) — but cand09 (with the do-while) gave 191 ins (one too few) and score 25.

Hmm! 191 vs 192: the tree has one MORE instruction than cand09. Which one? The tree's asm... hmm, the asm emits nothing. So the difference is elsewhere: maybe the tree's `vol` (137) having 2 sets forces an extra copy somewhere (e.g. the call argument `vol | (0x3000 | sx)` needs a copy of vol).

In cand09: `vol = ((0xA0 - av) * 0x7F) / 0xA0; do { vol = vol; } while (0);` — the do-while's self-copy is inside a loop → the loop might be optimized away entirely (loop.c removes a 1-iteration loop) → and then the self-copy is gone → vol has 1 set → and the count drops to 191.

Hmm, but in item 3 the do-while DID keep the boost killed. Here maybe not.

Let me look at cand09's diff to see what's missing.

Actually, let me try a different tactic: mimic the tree's structure exactly:
```
vol = ((0xA0 - av) * 0x7F) / 0xA0;   /* the quotient → vol (1 set) */
vol = vol;                             /* 2nd set — but cse removes it */
```
cse removes `vol = vol`. Hmm. But what if the copy is written differently so cse keeps it? E.g.:
```
vol = ((0xA0 - av) * 0x7F) / 0xA0;
{ s32 t = vol; vol = t; }   /* cse merges t and vol → removed */
```
Hmm.

What about a copy through a function call? No.

What about `vol = (s32)vol;`? cse removes.

Hmm, so how did the tree's asm survive? Because an asm insn is never removed.

So for a plain-C 2nd set of vol, the options are: a mode change (changes the value), a compound assign (changes the value), a loop (maybe removed), or a volatile (a barrier lever).

Hmm, what about a compound assign that preserves the value? `vol *= 1;`? gcc folds x*1 → x? Let me think: `x *= 1` → gcc's fold: `(x * 1)` → x (yes, folded).

`vol /= 1;` → folded to x? gcc folds `/1` → x ✓.

`vol %= 1;` → x % 1 = 0 — changes the value.

`vol += 0;` → folded.

`vol -= 0;` → folded.

`vol <<= 0;` → folded.

`vol ^= 0;` → folded.

Hmm. What about `vol = vol + (vol - vol);`? folded.

What about a compound assign with a value that's zero at runtime but not provable? E.g. `vol += zero_var;` where zero_var is a local set to 0 → gcc propagates → folded.

Hmm. What about `vol |= (s32)(u8)0;`? folded.

Hmm, what about the sign trick: `vol = (s16)vol;`? changes the value (vol is a volume 0..0x7F → fits in s16! and the value is used as `vol | (0x3000 | sx)` & 0xFFFF). Hmm! If vol is always in [0, 0x7F], then (s16)vol == vol, but gcc doesn't know that.

But the CODE would differ: `vol = (s16)vol` adds a sign-extend (sll+sra or just sra since the upper bits are known zero? gcc knows vol's range? no).

Hmm, but wait: the target's code has `ori a1,a1,0x3000` and `or a1,a1,a2` and `andi a1,a1,0xffff` — the value of vol is ORed into a1. If vol were truncated to s16, the code would have an extra sign-extend → count mismatch.

OK so what about the G11-style recipe applied here: the launder's role in the tree is to give vol a 2nd set. G11's recipe was `pv &= 0xFF000000` — a compound assign that CHANGES the value but the target's code has that mask anyway.

Here, is there any compound assign that preserves the value AND survives? What about `vol = vol * 1;`? folded.

Hmm, what about a compound assign on a DIFFERENT variable to give IT a 2nd set, and hope the effect is the same? The launder's boost-kill was on vol's pseudo. But maybe what matters is the ORDER of the two multiplies, which depends on the scheduling of the division's insns — and the vol pseudo's 2 sets affect it.

Alternatively, maybe I can achieve the right order differently: the target's order is [lui a0, ori a0 (the magic), li v0,160, subu, sll, subu, mult v1,a0 (the vol mult), mfhi, addiu v0,a2,160 (the pan), mult v0,a0 (the pan mult), ...].

So the target's magic is materialized FIRST (at the top of the block) and the vol multiply comes before the pan multiply.

In C2, the magic is materialized after the ×127 and the vol mult is at the same place as the target's? Let me check C2's order: c68 lui v0, c6c ori v0, c70 mult a1,v0 (the vol mult), c78 addiu v1,a2,160 (the pan), c80 mult v1,v0 (the pan mult). So the multiply ORDER is right ✓; only the magic's placement and the registers differ.

So C2 needs: the magic materialized at the TOP of the block (before `li v0,160`).

Why is the tree's magic at the top? Because of the scheduler. In the tree the chain is [code_label, 450 (lui), 451 (ori), 259 (li 160), ...]. Since the chain is the reverse of the launch order (per my item-3 deduction), the magic was launched LAST.

Hmm, and in C2 the magic was launched earlier.

Why would the tree launch the magic last? Because in the tree, the magic's use (the vol mult) is far from its birth...

Hmm, hmm. Let me reconsider the chain direction. Let me verify with a cleaner case in this function: in the tree's chain, the first insns after the code_label are the magic materialization (450, 451). In the assembly, the magic (lui a0/ori a0) IS at the top of that region ✓ (c58). So the chain order = the assembly order here.

For item 3, the chain order in cand01 was [.., li, move, call] and the assembly was [.., li(5), sw s0, move s0,a2(7), ..] ✓ chain = assembly order.

So the chain = the assembly order = the final order. And the trace's launch order = the reverse? That was my deduction (odd but let's go with the empirical evidence: the tree's trace launched 68 first and 68 is last in the chain).

Hmm, wait. Maybe the trace's "now" list is printed with the chosen insn LAST. Let me re-examine: "ready list at T-4: 58 (1) 60 (1) 62 (1) 64 (1), now 64 62 60 58". If the chosen is the LAST of "now" (58), then the launch order was 58 at T-4. Hmm, and the chain in the tree has 58 near the end but not last.

Eh. Let me determine the direction from THIS function's tree trace: the tree's chain starts (in the case-0 block) with [450 (lui), 451 (ori), 259 (li 160), ...]. If the chain = the launch order, the lui was launched first in the block. If reversed, last.

Let me check the trace for the case-0 block: find "insn[ 450]" in the ready list and the launch order. From the grep above: "insn[ 450]: priority = 1, ref_count = 1" and "insn[ 451]: priority = 1, ref_count = 2".

Let me look at the trace of that block (the one containing 450) and see the launch sequence.

Let me print the trace section for the block with 450 in the tree'sdump.
