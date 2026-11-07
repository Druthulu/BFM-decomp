---
ts: 2026-11-06T15:07:18Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO04
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_xAcgZmidGHz9wAcJmpvZ
---
Now clear. Candidate (u16):
```
4b7c li v0,16
4b80 bne a2,v0,4b8c
4b84 andi a1,a1,0xffff   ← cast's andi, fills bne delay slot
4b88 li a2,15
4b8c sll a2,a2,0x8
4b90 li a0,2715
4b94 ori a1,a1,0x3000
4b98 or a1,a1,a2
4b9c jal
4ba0 andi a1,a1,0xffff   ← final mask
```
Target:
```
4b7c li v0,16
4b80 bne a2,v0,4b90
4b84 sll a2,a2,0x8        ← delay slot
4b88 li a2,15
4b8c sll a2,a2,0x8
4b90 li a0,2715
4b94 ori a1,a1,0x3000
4b98 or a1,a1,a2
4b9c jal
4ba0 andi a1,a1,0xffff
```
So target has only ONE andi (the final mask) and both slls. Candidate has 2 andis and both slls = 238? but score said 237. Hmm: candidate 4b88 li a2,15; 4b8c sll — target 4b88 li; 4b8c sll. Same. So candidate = target + 1 andi = 238. But the tool said mine 237, target 237. Hmm, maybe mine lacks an insn elsewhere (target's 4b58 nop?). Target had `4b54 addiu v0,a2,160; 4b58 nop; 4b5c mult v0,a0`. Candidate: 4b54? not shown but 4b5c mult v0,a0 — the -B14 shows 4b5c mult; so 4b58 exists. Hmm.

Whatever: mine has an extra andi (238 vs target 237 measured by the tool as 237/237? maybe the tool counts differently). The tool said mine 237. Since target has 237 and mine has 238 per my count... maybe the tool's insn count excludes something.

Anyway: I need to eliminate the cast's andi OR make the final mask fold. Note: with `vol = (u16)vol`, the final `& 0xFFFF` is NOT folded (still present at 4ba0) — because `or` with 0x3000 and sx could exceed? sx ≤ 0xF00, vol ≤ 0xFFFF → or ≤ 0xFFFF. gcc doesn't know vol ≤ 0xFFFF... it does after zero_extend, but combine maybe doesn't.

Alternative: get a 2nd set of vol that emits NO insn. Options in gcc 2.7.2:
- `vol = (s16)vol;` gave 239 (2 insns: sll+sra probably).
- `vol = (u8)vol` → andi 0xff (1 insn).
- What about a use that's not a definition? We need a *2nd set* to kill sched1's birth boost... Actually do we? The launder is a tied output+input: it's both a def and a use. Its effect on sched1: it makes the vol computation's result "born" at the asm.

Alternative mechanism entirely: instead of a 2nd set of vol, make the PAN division's result the one with the boost killed. Since the problem is sched1 hoisting the PAN multiply above the VOL one: if pan (sx) got a 2nd set, its multiply's birth... hmm, the pan mult result is sx which is then reused.

Another idea: reorder source statements — compute pan (sx) first, then vol. Comment says 9 spellings tried and all identical. But those were with the launder in place. Without the launder, source order might matter now! Let's try swapping: 
```
sx = (sx + 0xA0) / 0x14;
if (sx == 0x10) sx = 0xF;
vol = ((0xA0 - av) * 0x7F) / 0xA0;
sx = sx << 8;
```
Wait but the target order is vol first then pan (target: mult v1,a0 [vol] then mult v0,a0 [pan]). Hmm, target has vol's mult first. In my plain drop, mine had pan first. So the launder forces vol's mult first.

If I reorder source to compute vol first... it already is first in source! `vol = ...` then `sx = ...`. And sched1 still hoisted pan first. So source order doesn't help — consistent with the comment.

OK, so what makes sched1 order vol first in the target? The launder's tied output creates a def at that point. sched1's priority: an insn that is a "birth" gets boosted. Hmm.

Alternative: use `do { } while (0)` around the vol statement? tried (16).

Let me consider a different approach: change vol's *type* so the division emits differently. c_hvol (u16 vol) gave 238/9.

What about making vol's computation a two-step with a temp:
```
s32 q;
q = (0xA0 - av) * 0x7F;
vol = q / 0xA0;
```
Two sets? No — vol set once. But q's birth... Try it.

Or:
```
vol = (0xA0 - av) * 0x7F;
vol = vol / 0xA0;
```
This is a REAL 2nd set of vol, value-preserving, same total computation. c_split did exactly that: 236/30. Hmm, that means the 2nd set didn't help ordering (still pan first).

Wait — c_split gave score 30 (same as plain drop), meaning the 2nd set of vol (as a division) did NOT change the schedule. So "2nd set" alone isn't the mechanism; the andi version changed it because the andi is a cheap insn placed early.

Hmm, so what did the launder do? It's a zero-width asm with a tied operand. In RTL, `asm` insns are barriers for sched? No, but sched1 treats them with a priority and they're not moved.

Let me think about the actual effect: with the launder, target's vol mult at 4b4c comes before pan mult at 4b5c. Without, pan mult comes first (mine: 207 mult v1,a2 then later vol). The launder makes vol's result live at a point between the two computations.

Since vol's andi (u16) fixed the ordering (237/2 — one slot off), the mechanism is: vol's def gets a use right after, forcing the mult earlier.

So: I need an *extra use* of vol between the vol computation and the pan computation, with no insn emitted. A use with no insn: e.g. passing it to a function? emits code. 

What about making the final expression use vol twice? e.g. `(vol | (0x3000 | sx)) & 0xFFFF` → `(vol & 0x7F | ...)`. no.

Zero-insn uses: a cast `(u16)vol` emits andi. But a cast to the *same* type, e.g. `(s32)vol` — nothing, folded.

Hmm, what about `vol = vol;`? Tree folds.

What about using vol in the `if (sx == 0x10)` condition? no, changes semantics.

OK, alternative: accept the extra andi but make the final mask disappear so total stays 237! If we write the arg as `(u16)(vol | (0x3000 | sx))` (c_u16late2 gave 236) — hmm that removed one andi and gave 236.

Wait: c_u16late2 = plain drop + `(u16)(...)` instead of `& 0xFFFF` — 236 ins, meaning the u16 cast on the or-result emitted nothing (it's a subreg of a 32-bit value; gcc knows it must mask but... 236 = one less than 237, so the andi vanished entirely). That's wrong (target has it).

So: combine `vol = (u16)vol;` (andi #1) + `(u16)(...)` (no insn) = 237? Let's try: a1 + both changes. Then insns = 236 + 1 = 237 and the andi sits at the bne delay slot... but target's andi is at the jal slot and the sll at the bne slot. Still one slot off? Hmm, but the jal slot then has nop.

Alternatively: keep `& 0xFFFF` (target's andi at jal) and remove the cast's andi. Can't have both.

Hmm, what if the 2nd set of vol is spelled so that it's the SAME value and combine merges the cast's andi into the final mask? Not possible positionally.

New idea: make the 2nd set of vol be a *store*? no.

Let me reconsider: maybe I don't need vol's 2nd set at all. What if I change the pan computation's shape so its mult naturally lands after vol's? E.g. compute pan via a different expression that sched1 values differently:
`sx = (sx + 0xA0) / 0x14;` — maybe `sx = (sx + 0xA0) / 20;` same. Or `sx = (sx + 160) / 20;` — identical.

Or introduce a temp for the pan: `s32 pn; pn = (sx + 0xA0) / 0x14; if (pn == 0x10) pn = 0xF; sx = pn << 8;` — but the comment says reusing sx is a lever for register allocation (pan in $a2). Since we're lever-free-ish, using a separate var may break allocation.

Hmm. Let me reconsider the problem: maybe there's an entirely different, simpler plain-C move: the `& 0xFFFF` at the call arg is the andi that ends in the jal delay slot. In the plain drop, the schedule is pan-mult-first. What if we make the vol multiply's result used earlier by making `vol` participate in the `if (sx == 0x10)`? No.

Let me look at cookbook C0414 (dead-reset cse-breaker) — not relevant.

Another approach: a *loop* wrapper? no.

Think about sched1 priorities: insn priority = length of the longest path from the insn to the end of the block, weighted. The launder asm has high priority (asm insns get priority... in gcc, `asm` insns are given a high priority in sched1 — actually SCHED_S_TASK_HIGH? In sched.c, an asm insn gets priority = ...). The launder forces vol's chain to end at the asm, shortening vol's path to the end, which raises the priority of vol's mult? Hmm, no: the asm is *before* the pan mult, so it truncates vol's dependency chain to the end of block, LOWERING vol's priority... but it did the opposite.

Whatever the mechanism, empirically the andi near-cracked it.

Let me try: `vol = (u16)vol;` AND `(u16)(vol | ...)` at the call (removing `& 0xFFFF`). Expect 237 and maybe correct slots.

And also: `vol = (u16)vol;` placed between the pan division and the shift? 

And: `vol = (u16)vol;` twice? no.

Let's try a batch:
- d1: u16 cast + `(u16)(...)` arg.
- d2: u16 cast placed right after the vol division but with `sx` cast? no.
- d3: `vol = (u16)vol;` before `sx = (sx+0xA0)/0x14;` — that's what c_u16 is (cast right after vol division). Actually in orig, the launder is right after the vol division, and sx line follows. So yes.
- d4: cast placed after the `if (sx == 0x10)` block but before the shift.

Let me do d1 and d4.
