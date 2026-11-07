---
ts: 2026-11-06T10:19:28Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG27x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_BM0oWZaTKr0GPaNSSPDW
---
Both still have the same register swap: mine has a in s0 (mine[21] subu v1,a0,s0 — a is s0), div in s1.

Hmm, in d2, div is arg3 (parameter) but still got s1. Let me check d2's alloc priorities. If arg3's pseudo birth is at entry, its live should be longer → lower pri. Hmm.

Wait, maybe the parameter pseudo is born at insn 0 but the RTL's first insn for the function... Let me check d2's alloc.

Actually, let me reconsider: I've spent ~13 min on item 3. Let me consider that these are walls.

But hold on — maybe there's a MUCH simpler explanation I'm missing: the pin `$16` might be removable by changing the *declaration* of `a` from `s32` to `u32` or reordering... no, tried.

Let me look at the moves.md entry 141 again: "the game's real prototype is s32, not void: the s32 return keeps $v0 live across the gte_stsz asm, so local-alloc gives the &sp10/load temp $v1 ($3) instead of $v0 ($2)". This is a case where a prototype change was the crack, but we can't change prototypes.

Hmm, but wait — for the HEADER items, the function's return type is part of the header. Could the "real prototype" differ? For item 3, the return type is `s32` already. For item 2, `s32`.

OK. Let me now step back and think about the overall strategy. I have 4 items, all keepalive,pin. I've made progress on none to score 0. Time spent: item1 ~10 min, item2 ~18 min, item3 ~12 min. Total ~40 min. 

The brief says 20-30 min per item, then WALL. So item 1 is a WALL (evidence: matches moves.md:300). Items 2 and 3 are heading to WALL.

But wait — maybe I'm missing something fundamental. Let me re-read the item 3 pin comment: `register s32 div __asm__("$16"); /* $s0 */`. And the keepalive on `ang`.

Hmm, what if the pin can be replaced by making `div` a *hard register through a different mechanism*? The brief says "no pin (register-asm/`__asm__` reg steer)". So no.

What if the allocation can be fixed by adding a real use of `div` before the call? E.g., `div = arg3; if (div == 0) ...`? That adds code.

Hmm.

Let me look at the wall tag list for the exact mechanism. walls.txt has:
- lreg-qty-priority (line 24)
- global-pri-bank-order (27)
- greg-ref-count (33)

For item 3: div and a have equal refs; div's live is longer → lower pri → loses s0. Tag: `lreg-qty-priority` (local-alloc qty priority gives the hard reg to the other pseudo). But both are global here, so `global-pri-bank-order` or `greg-ref-count`.

Actually, both div and a are GLOBAL (live across blocks/calls). So the allocation is global-alloc. The tag `global-pri-bank-order` fits: "global-alloc priority order assigns the hard regs in a different order than the target".

Hmm wait, but a's pri 6086 > div 5384, so a is allocated first. The target wants div first. The lever would be to flip the priorities. We established refs are equal (7) and live differ (23 vs 26). To flip, need a ref-count change or live change.

Let me try ONE more thing: what if `a` is used one more time in a way that adds no instruction? For example, the `if (a == cur)` — what if we write `if (cur == a)`? Same.

What if we write `diff = cur - a;` as `diff = -a + cur;`? The `-a` might add a neg instruction. No.

Hmm, what if `t = a + 0x1000` is written `t = 0x1000 + a`? Same RTL (commutative fold).

What about making `a`'s live longer by reordering: move `a = a & 0xFFF;` to the END (after `cur = ang & 0xFFF;`)? Tried (a4, score 20).

Hmm.

Let me try making div's live SHORTER by moving `div = arg3` later in the source while keeping the prologue copy. In the target asm, `move s0,a3` is at position 4 (prologue). If the source has `div = arg3` after the ang computation, gcc still needs the value of arg3 before the call. Let me test: move `div = arg3;` to after `ang = ang - 0x400;`.

Actually, gcc's RTL: if `div = arg3` is after the call, it would emit a move from a3 (hard) which is clobbered → the compiler would need to save a3. GCC's global-alloc sees the pseudo `div` is live across the call only if the assignment is before the call. If after, then div is born after the call from the hard reg a3 — but a3 is clobbered. GCC would emit `move div, a3` after the call, which is WRONG (a3 clobbered). Hmm, but gcc assumes the incoming argument a3 is valid until... Actually, the function prologue's `move s0,a3` IS the copy of the argument. If the source assigns div after the call, gcc would still need to copy a3 at entry (because a3 is an incoming arg and it's used after a call). GCC's `init_emit`/`expand_function_start` creates pseudos for args and copies them at entry if needed. So the birth stays at entry.

Hmm.

OK, let me try the "increase div refs" via a real third use. What if the code uses `div` in the `t = a + 0x1000` line somehow? No.

Actually — here's a thought: what if the source computes the sign-extension of div TWICE (in two places) but cse merges them into one instruction? Then the RTL has 2 sign-exts (more refs) but cse folds them. Hmm, cse runs before local-alloc? The pass order: cse, then... Let me check: in gcc 2.7.2 -O2, the order is: jump, cse, ... flow, combine, sched, local-alloc, global-alloc, ... Actually `cse` runs before local-alloc. So cse would merge duplicate sign-exts. Hmm.

What if we use `(s16)div` in both divisions (no explicit sign-ext stmt)? Then cse creates one sign-ext temp. div's refs: 2 casts + 2 divs? Let me count: div is used in the 2 casts (2 refs) + def (1) = 3. The sign-ext temp (used in 2 divs) is separate. Hmm, that was c1 (score 24).

Hmm.

Let me try yet another idea: make `a` and `div` SWAP their live lengths by moving the `if (a == cur)` early return and the division structure. 

Actually, you know what? Let me look at the target's `a` and `div` refs by considering the target asm. Both 7. Live: div longer. So the target's alloc contradicts the priority formula... UNLESS the target's qty_death/birth differ from the asm order due to the RTL being scheduled differently.

Wait — the alloc table's live is from the RTL (pre-sched). In the target, the RTL is unknown. But the asm (post-sched) order is what we see. The RTL order could differ.

Hmm, in our nopin RTL, a's birth insn 17, death ~319; div's birth insn 20, death ~395. Let me compute: a live = (death - birth) = 302? But the table says 23. So "live" isn't the insn number difference; it's the number of insns in the live range? Or qty_death - qty_birth in some normalized unit. Hmm, the table's live column for a=23, div=26.

Actually, looking at local-alloc.c: `qty_death[q] - qty_birth[q]` where birth/death are `2 * insn_number`. So live is in "half-insn" units? Hmm.

Whatever. The point: div's live > a's live.

To flip, I need a's live > div's. Since a's death < div's death and a's birth > div's birth... wait, a's birth (insn 17) < div's birth (insn 20)! So a is born EARLIER. And a dies earlier. The spans overlap.

a: 17 → 319 (span 302)
div: 20 → 395 (span 375)

To make a's span > div's, move a's death later or birth earlier. Birth earlier is impossible (a is the first assignment). Death later: move a's last use after the divisions. 

Hmm! What if the `t = a - 0x1000` (the last use of a) is moved to after the division? In the source:
```
if (diff < -0x800) { t = a - 0x1000; diff = cur - t; }
```
This is before the `if (diff >= 0) { q = diff / div; ... }`. Can't move.

What if a is used in the `d = q;` line? No.

Hmm, what if the mask `a = a & 0xFFF` is moved to the END (just before the divs)? Then a's birth is still `a = arg2` (insn 17), death is the last use (same). No change.

OK. I think items 2 and 3 are walls of the alloc-priority class. Let me record them and move to item 4, then item 1's 30 tries.

Actually, wait. Let me reconsider item 3 ONE more time with a completely different structure. The `else` block:
```
d = 0;
} else {
    s32 t;
    diff = cur - a;
    ...
}
```
What if `t` is declared outside (function scope)? Then t's allocation might change and indirectly... no.

Hmm, what if `cur` is declared `u32` (it is) and `a` is `u32` (b1, no change).

Let me look at the keepalive role in item 3: `__asm__ __volatile__("" : : "r"(ang))` after `ang = ang - 0x400`. In the target asm, the order is: `addiu v0,v0,-1024` (ang), `sll s0,s0,0x10` (div sign-ext), `andi s1,s1,0xfff` (a mask), `andi a0,v0,0xfff` (cur). So ang's addiu, then div's sll, then a's andi, then cur's andi. The keepalive anchors ang before div/a/cur. Similar to item 2.

So the keepalive replacement might be the same C lever as item 2's. And the pin replacement is the alloc issue.

Given the time, let me make a decision: record items 1, 2, 3 as WALLs with best scores (item1: 1, item2: 21, item3: 17) and evidence, then do item 4, then come back if time.

But wait — the brief says a WALL needs ≥20 min and ≥30 scored tries on that item. I have ~12 tries on item 3. Hmm. Let me do more tries to satisfy the requirement, or try harder.

Actually, let me reconsider the fundamental issue once more. Maybe there IS a real C lever: the C0505 catalog mentions "pointer reuse". Hmm.

Let me look at the target asm for item 3 once more. The key: div=s0, a=s1. Both global. The alloc table says a pri 6086 > div 5384.

What if we make `div`'s refs 8 by adding a *real* use that emits the SAME instruction? For example, the division `diff / div` emits `div zero,v1,s0; bnez s0; ...; mflo v1`. The `bnez s0` is the zero check. What if we also use div in the `q == 0` check? `if (q == 0) q = 1;` — q, not div.

Hmm, what if we write `if (div == 0) q = 1;`? That would replace the `q == 0` check — different code.

Hmm.

What if the source has `q = diff / div;` where the result is used in a modulo too? `r = diff % div;` — adds a mod (already emitted internally, but a separate C mod would add a second mflo). Hmm, actually gcc emits div+mod together for one division; a second `%` would reuse. Let me test: add `s32 r = diff % div;` somewhere and use r? That adds code.

OK. Let me try a few more variants and then wall it:
- e1: move `a = a & 0xFFF;` to after `cur = ang & 0xFFF;` (tried a4-ish)
- e2: `diff = cur - a;` moved before the mask? no.
- e3: split the `a` mask into a separate variable `am` and use am in the later uses (making a local). Then a (local, short) and am (global). div (global) vs am (global). Let me think: a = arg2 (local, dies at mask), am = a & 0xFFF (global). Then local-alloc gives a s0 (only local-crossing). Then am prefers s0 (copy pref from the andi in-place?). Hmm, then div competes with am. 

Actually, in item 3's target, the andi is in-place (`andi s1,s1`), so a and am share. If I split, the andi might be `andi s1,s0` (different regs) — not target.

Hmm.

Let me look at this from the "what if the original source is different" angle. The target's `move s1,a2` (a) then `move s0,a3` (div). In the source, `a = arg2; div = arg3;` — a first. Matches.

The target's `sll s0,s0,0x10` (div) BEFORE `andi s1,s1,0xfff` (a). In the source, `div = (s16)div;` before `a = a & 0xFFF;` — matches.

The target's `andi a0,v0,0xfff` (cur) after a's andi. Source: `cur = ang & 0xFFF;` after. Matches.

So the source order matches. The ONLY difference is the register allocation.

Given the alloc math (a 6086 > div 5384), the target's allocation is impossible with THIS source unless the priorities differ. So the original source must differ in a way that changes refs/live.

Hmm, what if the original had `a` as the raw arg2 (parameter) and the masked value as a separate variable, and the andi is in-place because the masked variable's register happens to equal a's? Let me test d1 again but check the alloc: d1 used arg2 directly (a = arg2 removed). Score 20. Let me check d1's priorities.

Let me hdump d1.
