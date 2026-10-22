---
ts: 2026-10-22T09:33:24Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM2
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_CmrG8tAXgXpNSJ8m1r2p
---
This is a rabbit hole. Let me switch strategy to pure experimentation with the real body, since each try is ~1s, and use the gcc source only if needed.

Actually — wait. Let me reconsider the problem. Maybe I'm over-thinking: maybe the swap is in **cse**, and the .combine dump is actually the dump AFTER cse (i.e. the file naming may be: 'c' → .cse? no...).

Hmm, let me test directly: does the tree change between the .combine and .cse dumps? In .combine: (plus (reg 118) (symbol_ref)); in .cse: also (plus (reg 118) (symbol_ref)) (I saw "D_80195AF6" grep output for cse showing insn 190 `(set (reg/v:HI 113) (mem/s:HI (plus:SI (symbol_ref:SI ("D_80195AF6")) (reg:SI 118))))` — WAIT! In the cse dump, the tree is (plus (symbol_ref) (reg 118)) — SYMBOL FIRST! And in the combine dump it's (plus (reg 118) (symbol_ref))!

So the order FLIPPED BACK between combine and cse! That means: combine swapped it to index-first, and CSE swapped it back to symbol-first?? That's weird. Unless the .combine and .cse dumps are in the other order (cse before combine)? No — CSE runs after combine in gcc 2.7.

Hmm, actually maybe I mixed up: earlier I grepped the "cse" dump for "D_80195AF6" and got:
```
(insn 190 188 193 (set (reg/v:HI 113) (mem/s:HI (plus:SI (symbol_ref:SI ("D_80195AF6")) (reg:SI 118)))) -1 (nil) (nil)
```
Wait no — that grep output labeled "#### cse" showed the same insn 190 with symbol first and no pattern number (-1) — that's the same as the .rtl dump! And the "#### combine" grep showed insn 194 with (plus (reg 118) (symbol_ref)).

Hmm! So .cse looks like .rtl (insn 190, -1 pattern) — meaning the .cse file might actually be the RTL dump?! I bet the flag mapping is: 'r' → .rtl AND ... no. Let me check: in the "#### rtl" grep I got insn 190 with symbol first; in "#### cse" also insn 190 with symbol first and the same "-1 (nil) (nil)" pattern. So .cse and .rtl look identical?! Possibly the file .i.cse is actually the dump after... hmm, they might just be similar.

Let me verify by diffing the .rtl and .cse dumps. If they're identical, the flag mapping means one of them is a duplicate.

Also let me grep the .combine and .cse for the number of insns. Let me check sizes: .rtl 412130, .cse 458027, .cse2 458020 — .cse and .cse2 are nearly identical sizes (458027 vs 458020) — so .cse/.cse2 are the CSE dumps (cse and cse2 passes), and they're AFTER combine. And .rtl (412130) is before.

But then in the .cse dump, the plus is (plus (symbol) (reg 118)) — symbol first — while in .combine it's (plus (reg 118) (symbol))! So CSE swapped it BACK to symbol-first.

Wait, that can't be: the final asm is "addu v0,v0,a1" = index first = (plus 118 a1). Hmm, but the .cse dump shows symbol first...

Hold on. Maybe the .combine dump is dumped at a point where combine's *tentative* result is shown but then reverted? Combine works on a copy and undoes changes if the combination fails. The dump might show combine's in-progress state (with the substitution applied) while the final state (after undo) is different!

That's plausible: the .combine dump in gcc 2.7 shows the insn after try_combine's changes, but if the combination is rejected, combine restores. So the "swap" might be an artifact of the dump.

OK so the truth is in the .cse dump: (plus (symbol_ref) (reg 118)) — symbol FIRST. And yet the final asm is "addu v0,v0,a1" (index first)! So the swap happened after CSE — in reload/reload1/sched.

Reload! In reload.c, when an operand needs to be in a register, for commutative operations reload may swap the operands. Let me check reload.c for a swap of commutative operands. grep "commutative" in reload.c.

Actually, the important thing: the target's asm has pointer-first. So the difference is in reload's handling. Let me look at reload.c for the relevant code. Let me grep for "swappable" / "commutative".
