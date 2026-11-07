---
ts: 2026-11-06T10:16:31Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG27x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_ilPKej8ljxmvxx5O9xEJ
---
In a1, r76 pri 6363 (live 22) and r77 pri 5185 (live 27). Which is which? a1's asm: mine[2] move s1,a3 (div→s1), mine[4] move s0,a2 (a→s0). So a is in s0 (higher pri = r76 = a, pri 6363) and div in s1 (r77, 5185).

Wait, in a1 the source order is `div = arg3; a = arg2;` but the prologue asm shows `move s1,a3` (div) then `move s0,a2` (a). And a (pri 6363) got s0, div (5185) got s1.

Hmm, so a's live became 22 (shorter!) and div's 27. By swapping the assignment order, a (assigned second) has a later birth → shorter live → higher pri. That made it WORSE (a wins s0 more strongly).

So to make div win, I need div's live SHORTER: assign div LATER (after a). That's the ORIGINAL nopin order (`a = arg2; div = arg3;`), where div live 26, a live 23. Still div 5384 < a 6086.

Hmm. In nopin, a live 23, div live 26.

I need div < a's live, i.e., div's live < 23. To shorten div's live by 4: move `div = arg3` later by 4 RTL insns. But the target has `move s0,a3` at position 4 (prologue). So div's birth is early in the target.

Wait — but if div's birth is early and its death is at the last div, its live is ~26. Then in the target, div's pri = 2*7/26 = 5384 < a's 6086. So the target's alloc would give a s0! But the target has div s0. Contradiction!

Unless the target's refs differ. Let me reconsider: maybe in the target, div has 8 refs and a has 6.

Hmm, refs are computed from the RTL, which should match the asm. Let me count div's uses in the target asm:
- move s0,a3 (def)
- sll s0,s0,0x10 (use) + sra s0,s0,0x10 (def) = 2
- div zero,v1,s0 (use) + bnez s0 (use) = 2
- div zero,v1,s0 (use) + bnez s0 (use) = 2
Total = 1 + 2 + 2 + 2 = 7 refs. Same.

a's uses:
- move s1,a2 (def)
- andi s1,s1,0xfff (use+def) = 2
- bne s1,a0 (use) = 1
- subu v1,a0,s1 (use) = 1
- addiu v0,s1,4096 (use) = 1
- addiu v0,s1,-4096 (use) = 1
Total = 7.

Hmm, both 7. So the priority difference is purely live length. And div's live is longer (born earlier, dies later). So a should win s0. But the target has div in s0!

Wait, maybe the qty_death/birth in the target differ because the *RTL* order differs from the asm order (scheduling). The RTL (pre-sched) has the source order. In the source, `a = arg2; div = arg3;` (a first). So a's birth is earlier. a's death (last use) is before div's death. 

live_a = death_a - birth_a. live_div = death_div - birth_div. birth_a < birth_div, death_a < death_div. Hard to say.

From the nopin alloc: a live 23, div live 26. So div's span is longer.

But the target has div s0. So in the target's RTL, div's pri > a's pri. That means the target's RTL is DIFFERENT from our reconstruction's RTL.

What could make div's live shorter in the original? If the divisor were assigned LATER in the source (after the ang computation), its birth would be later. But the target asm has `move s0,a3` at position 4 (prologue). Hmm — but wait! `move s0,a3` in the prologue could be the *argument save* emitted by gcc for a parameter used after a call, not necessarily `div = arg3` at the top. If the source used `arg3` directly in the divisions (no div variable), gcc would create a pseudo for arg3 that's live across the call and emit `move s0,a3` in the prologue. Then the pseudo's birth is at the prologue (insn ~8) — same.

Hmm.

OK, wait. Let me reconsider the possibility that the target's `a` is NOT a self-set. In the target: `move s1,a2` (a=arg2), `andi s1,s1,0xfff` (a masked in place). If the source had `a = arg2 & 0xFFF;` at the top, the RTL would be `(set a (and (reg arg2) 0xFFF))` — a single def with an and. Then the asm would be `move s1,a2; andi s1,s1,0xfff` (or `andi s1,a2,0xfff`!). Hmm, `andi` can take a register source: `andi s1,a2,0xfff`. But the target has `andi s1,s1,0xfff` — in-place, suggesting a self-set (two insns).

Hmm, but the target has `move s1,a2` and later `andi s1,s1,0xfff` separated by the call. If it were `a = arg2 & 0xFFF`, the andi would be right after the move (in the prologue), not after the call. So the mask is a separate statement after the call: `a = a & 0xFFF;`. OK, self-set confirmed.

Similarly div.

Hmm.

Let me reconsider: maybe the original source had `div` as a *s16* parameter? `s32 func_8012BB3C(s32 arg0, s32 arg1, u32 arg2, s32 arg3)` — arg3 is s32. The divisor `div = (s16)arg3`? Then the sign-ext is at the prologue. No.

Let me look at the target's `sll s0,s0,0x10; sra s0,s0,0x10` — that's `(s16)div` computed after the call. So `div = (s16)div;` after the call.

OK. Let me try to make div's live shorter by moving `div = arg3` to after the `ang` computation in the source (so birth is later), even though the target asm has the move early. If gcc still emits `move s0,a3` early because div is live across the call... yes! If `div = arg3` is placed AFTER the call in the source, gcc can't use a3 after the call (clobbered), so it must copy a3 to a callee-saved reg BEFORE the call — in the prologue! So the move would still be in the prologue, but the *pseudo's birth* (in RTL) would be at the move in the prologue. Hmm, same.

Wait, but if `div = arg3` is after the call, then the copy `move s0,a3` must happen before the call. gcc's global-alloc inserts the copy at the parameter's... Actually, gcc copies the parameter to the pseudo at the point of the assignment. If the assignment is after the call, a3 is already clobbered. So gcc would... hmm, gcc handles this by copying at function entry if the pseudo is live across a call. The `move` would be in the prologue.

So the birth is still early. Hmm.

Let me try a different lever: make a's live LONGER. If a's last use moves later, a's live grows. The last use of a is in `t = a - 0x1000` (the second if). If I reorder the two `if (0x800 < diff)` and `if (diff < -0x800)` blocks, a's last use moves. The target order is >0x800 then <-0x800. Swapping would change the asm.

Hmm.

OK, let me look at the actual nopin RTL to see the birth/death of a and div. Let me grep the lreg for item 3. Actually, let me look at the alloc table's "dies in 3 places" for div (r77 in nopin): div dies 3 times? That's the 2 divs + the sign-ext? Hmm, "dies in 3 places" — REG_DEAD notes.

Let me look at the RTL to find the birth/death insn numbers. Let me grep the lreg for r76/r77.

Actually, this is a lot of effort. Let me consider: is there a simpler lever? The `--explain` says the pin and keepalive are both NEEDED. The keepalive on `ang` anchors it before the `div = (s16)div` / `a &= 0xFFF`. The pin forces div→s0.

Given item 2 was a wall and item 3 is similar, maybe items 3/4 are also walls. But let me try a few more C variants for item 3.

Idea: since a and div have equal refs (7), the tie-break is live length. What if I make a's refs 8? Then a wins MORE. No, I want div to win. Make div's refs 8: floor_log2(8)=3 → 3*8/26 = 9230 > a 6086 → div wins! 

How to add a ref to div without changing the instruction count? Hmm. What if the division is written as `q = diff / div;` and the zero-check... 

Wait — what if div is used in the sign-extension as `div = (s16)div` AND `div` is also used in a comparison? No.

Hmm, what if `div` is used 3 times in the divisions? There are 2 divs. 

What if we write `q = diff / div;` and also `if (div == 0) q = 0;`? adds code.

Hmm.

What if a's refs drop to 6? a's uses: move(def), andi(use+def), bne(use), subu(use), addiu(use), addiu(use). If one of the addiu uses is eliminated... The `t = a + 0x1000` and `t = a - 0x1000` both use a. If one used a different variable... no.

OK, let me look at the target asm once more for a clue about the ORIGINAL source. The target has `addiu v0,s1,4096` and `addiu v0,s1,-4096` — a in s1.

Hmm, what if in the original, `a` was declared as `u32` (arg2 is u32)? `a = arg2; a = a & 0xFFF;`. u32 vs s32 — mode is SImode either way. t1 for item 2 didn't change.

Let me try a few quick things for item 3:
- b1: `a` as u32
- b2: `div` as u32
- b3: move `div = (s16)div;` to right after `div = arg3;` (prologue)
- b4: move `a = a & 0xFFF;` to right after `a = arg2;`
- b5: reorder the two if blocks
- b6: `t = a + 0x1000` written as `t = 0x1000 + a` (commutative)

Let me batch.

Actually, wait. Let me reconsider the target's prologue: `sw s1,20(sp); move s1,a2; sw s0,16(sp); move s0,a3; sw ra,24(sp)`. The save of s1 BEFORE move s1,a2, and s0 save before move s0,a3. This order suggests the prologue emitted the saves as it processed each callee-saved assignment.

In our a1, the prologue was `move s1,a3; ... move s0,a2`. Hmm.

Let me just try variants. Time: 03:17. Let me be efficient.

Actually — here's a much better idea for item 3. What if we make `div` a LOCAL qty with high priority by splitting it: `s32 div0 = arg3;` (local, dies at sign-ext) and `s32 div = (s16)div0;` (global). Then local-alloc: div0 (local, crossing the call, refs 2, live ~20 → pri 1000) and a (global). Hmm, a is global. s1ang... I mean `a` is global. So local-alloc gives div0 s0 (only local-crossing qty). Then a (global) → s1. div (global) → s2. Target uses only s0,s1. No.

Hmm.

What if div0 is local with live 2 (assigned and sign-extended adjacent at the top)? pri 10000 → s0. Then div (global) uses s0 (copy pref from div0? no). Hmm.

Actually, if `div = (s16)div0` is a copy from div0, and div0 is in s0, then div has a copy preference for s0 → div gets s0! And a gets s1! TARGET!

Let me think: 
```
s32 div0;
s32 div;
a = arg2;
div0 = arg3;
ang = ...;
div = (s16)div0;   // sign-extend, div0 dies
a = a & 0xFFF;
...
q = diff / div;
```
- div0: local (born at prologue, dies at the sign-ext in block 0), crosses the call. refs 2, live ~20 → pri 1000. It's the only local-crossing qty → gets s0.
- div: global, defined by `(s16)div0` (sll/sra from s0). It has a copy preference for s0 (since the source div0 is in s0). Then div would prefer s0... but s0 is taken by div0 until the sign-ext, after which it's free. Hmm, global-alloc: a (pri 6086) and div (pri?). div's pri: refs ~5 (def + 2 divs + 2 bnez), live from sign-ext to the divs ~30 → 2*5/30 = 3333. a 6086 > div 3333 → a gets s0 first! But s0 is occupied by div0 during... div0 dies at the sign-ext (block 0), and a is live across the whole function. So a conflicts with div0 (both live across the call). a gets s1. Then div (3333) gets... s0 is free after div0 dies? In global-alloc, conflicts are computed over live ranges; div (born at sign-ext) doesn't conflict with div0 (dies at sign-ext)? They're adjacent. Hmm.

This is getting complicated. But the copy-preference idea is promising. Let me just test it empirically.

Let me create b7: split div into div0 and div.

Similarly for item 2 (d and s1ang): d is the divisor. We could split d into d0 (local) and d (global). Hmm, but d is already global.

Let me test item 3 b7.
