---
ts: 2026-11-06T06:31:09Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG22x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_SDNdnCWCYaA1niM3YCyR
---
Cal-saved order (after caller-saved ones): 74 (6470), 78 (5454), 73 (4576), 81 (3414), 76 (3043), 83 (2564), 72 (1290).

That's 7 callee-saved allocnos → $16..$22 (s0..s6). Which are base and sign? base=$21(s5), sign=$22(s6) in w3 (mine). Hmm wait, mine: base s5 ($21), sign s6 ($22). The order assigns: 74→$16, 78→$17, 73→$18, 81→$19, 76→$20, 83→$21, 72→$22.

Hmm, but earlier registers in the target asm: $16=tmp(hh), $17=j, $18=mod, $19=i, $20=half, $21=sign, $22=base, $23=arg0.

So mapping: 74=?, 78=?, 73=?, 81=?, 76=?, 83=?, 72=?
From the target's final: $16=hh/tmp, $17=j, $18=mod, $19=i, $20=half, $21=sign, $22=base, $23=arg0(s7).

Hmm, but here r80/r125 are caller-saved (v0). r74 (11 refs, live 51, 6470) = half? r78 (8 refs, live 44) = sign? Let me not guess.

In mine (w3), base=$21 (s5) and sign=$22 (s6). So the 6th allocno (83, pri 2564) = base, and the 7th (72, pri 1290) = sign.

Target wants base=$22 (7th) and sign=$21 (6th). So we need sign's priority > base's: sign 2564, base 1290 → swap.

sign: 5 refs, live 39 → pri 2564 (floor_log2(5)=2 → 2*5/39*1e4 = 2564).
base: 4 refs, live 62 → 1290 (2*4/62 = 1290).

Wait: base has 4 refs and live 62 (it spans the inner loop and across). sign has 5 refs live 39.

Target wants base in $22 → base must have LOWER priority than sign. It already does (1290 < 2564)! But mine gave base $21 and sign $22 — meaning base was allocated BEFORE sign?! That contradicts.

Unless I have base/sign swapped. Let me identify precisely: in the target's asm, `move $22,$2` (base = tmp) — $22=s6. And `sra $21,$20,31` (sign = half>>31) — $21=s5.

In w3's diff: `move s5,v0` (mine) vs `move s6,v0` (target) — so mine's base is in s5=$21 and target's base is in s6=$22. And `sra s6,s4,0x1f` (mine) vs `sra s5,s4,0x1f` (target): mine's sign is s6=$22, target's sign is s5=$21.

So mine: base=$21, sign=$22. The allocation order 74,78,73,81,76,83,72 → $16..$22. So base = 6th (r83, pri 2564) and sign = 7th (r72, pri 1290). But sign should have 5 refs/live 39 = 2564 and base 4 refs/live 62 = 1290.

Hmm, so r83 (2564) = base? That would mean base has 5 refs live 39. And r72 (1290, 4 refs, live 62) = sign.

Hmm. Let me not guess: which is which? sign is set inside the inner loop, used once (`subu v1,t0,s5`). sign: 2 refs (set + use), live short. base: set once per outer iteration, used in the inner loop's addu.

r72: 4 refs, live 62 — long live, few refs. That fits `base` (set in the outer loop, used in the inner loop = live across the inner loop). Actually base is set once per outer iteration and used once per inner iteration; live from the outer body start to the end of the inner loop ≈ 62 insns. Yes, r72 = base.

And r83: 5 refs, live 39 = sign? sign is set at the top of the inner loop and used at the bottom; live ~39 insns (the whole inner loop). Hmm, that fits too.

But if base = r72 (last, $22) in w3, then mine would have base=$22... but the diff says mine has base in s5 ($21). Contradiction.

Unless the 7 callee-saved aren't assigned in that order to $16..$22 — because of conflicts with hard regs or preferences. The table shows r74..r72 all conflict with s0 (hard reg 16)! "conflicts v0,v1,a0,a1,a2,a3,s0,sp". So they can't take $16! Interesting — why conflict with s0?

Because... hmm, `conflicts ... s0 ...` for ALL of them. So $16 is excluded for these allocnos, meaning the first gets $17. And there must be an allocno that takes $16 — the one that conflicts with fewer. Let me look for who got $16: in the final asm, $16 = the hh/tmp value.

This is getting complicated. Let me step back and consider the time budget seriously.

Time: item 2 started at 23:21. It's probably ~23:50 now. I've spent ~30 min on item 2. The brief: 20-30 min per item, past 30 min stop and record a wall (a WALL needs ≥20 min and ≥30 scored tries). I have ~8 scored tries. So it's not a WALL — it's a PARTIAL at best.

For PARTIAL I need a score-0 body keeping only the pins. w3 is 5. Let me try a couple of quick variants to flip base/sign:

Variant: give `sign` a second set (real C) — e.g. `sign = half >> 31;` is already a set; adding `sign = (s32)sign;`? Hmm, that's an identity launder — not allowed.

Variant: change the order of statements in the inner loop: `sign = half >> 31;` is the first statement. Move it after the obj call? That changes scheduling.

Variant: change `hh = half; pos[0] -= hh / 3;` — hmm.

Alternatively, look at it from the target's perspective: with the launder present, base=$22 and sign=$21. The launder changes tmp's RTL (an extra set). How does that change base/sign priorities? Possibly via loop.c's move_movables (the launder insn affects what gets hoisted) or via live lengths.

Honestly, at this point the pragmatic move is: item 2 = PARTIAL:pin with best 5? But the INTERFACES say PARTIAL requires win.c scores 0. If I can't get 0, it's a WALL (best = lowest score of a lever-free body). Hmm: "WALL (best = lowest score of a lever-free body)".

But note: w3 is NOT lever-free (it keeps the pins). The lever-free best is win.c (both removed) = 41? or the goto = 44. Actually the lowest lever-free score I have is 41 (w1).

Hmm, hold on. Let me reconsider. Maybe there IS a way to keep the launder's effect in plain C: the launder forces `tmp` to be a distinct value at that point. What if instead I write:

```c
base = tmp;
tmp = tmp;   // ??? identity
mod = (tmp << 16) >> 18;
```
`tmp = tmp` is an identity statement — disallowed as a launder ("identity-statement launders do NOT count as a crack").

What about `tmp = (tmp << 16) >> 16;`? That's an identity in value but a real computation — combine might fold it to a sign-extend (sll+sra = 2 insns, not folded since it's a real sign-extend of a 32-bit value... actually `(tmp<<16)>>16` is a sign-extension; combine may fold it into the following `>>2`... hmm, `mod = (tmp << 16) >> 18` = ((tmp<<16)>>16)>>2. So if I write `tmp = (tmp << 16) >> 16; mod = tmp >> 2;` — that's a real 2nd set and the value is the same! And the target's insns: `sll $2,$2,16; sra $18,$2,18`. With my rewrite: `sll $2,$2,16; sra $2,$2,16; sra $18,$2,2` — 3 insns instead of 2. Unless combine merges `(sra (sll x 16) 16)` with the following sra 2 → back to sra 18. Then no extra insn and no 2nd set. Hmm, combine would likely do that.

What about `tmp = (s16)tmp;`? That's a real sign-extend in C: `sll/sra` or `seh`? MIPS has no seh; it's sll+sra = 2 insns. Then mod = tmp>>2. Combine could fold `(sra (sra (sll x 16) 16) 2)` → `(sra (sll x 16) 18)`. Likely folded.

Hmm.

OK, let me take stock and make a decision:

Item 2's status: the pins are load-bearing for at least three separate effects (base copy, $2 allocation, blocking loop.c). This is a genuine wall. The best lever-free body scores 41 (w1: for loops, both levers removed, 107 insns).

But wait — before declaring, the goto version scored 44 and had a structurally-correct shape (no hoisting) except the base copy was merged. What if I combine the goto loop with a plain-C way to keep the base copy? 

Idea: make `base` used *before* tmp is used again, so cse can't merge... cse merges copies regardless of use order.

Idea: `base = tmp;` and later `tmp` is *set again* (`tmp = u * 0x600 + 0x2000` in the next outer iteration). cse's copy propagation: base = tmp, then tmp is redefined later — cse keeps the copy valid until the redefinition. It would still merge base into tmp for the range where they're equal. cse's `make_regs_eqv` merges them into one pseudo, so the move disappears.

To prevent merging, the copy must be "opaque" — which needs a hard reg (pin) or asm (launder). Both are levers.

BUT: there's another way — a *dead reset*? No, that breaks the value.

Hmm, what about using `base` in a context that forces a different register... no, merging happens at the RTL level before allocation.

OK. So the base copy can only survive with a pin or asm. That's a hard wall: "cse-copy-merge" (already a wall tag).

Wait — but hold on. In the target, is the `move $22,$2` really a copy of tmp to base? Yes. And with the launder (asm), cse can't propagate through the asm because the asm *sets* tmp. Right: the launder is a SET of tmp, so after it tmp is a "new" value; base (assigned before) is a different pseudo. That's exactly how the launder creates the copy.

Plain C can't make a copy survive cse except via a hard reg.

Therefore: MATCH is impossible without a lever → this is a WALL, not a PARTIAL.

Hmm, but PARTIAL:pin requires score 0 with the pins kept. w3 (launder removed, pins kept) = 5. So even PARTIAL fails unless I fix the base/sign swap.

Let me try 2-3 quick variants for the base/sign swap in w3:
1. Move `sign = half >> 31;` to after `obj = ...`? 
2. Change `sign = half >> 31;` to `sign = half < 0;`? That's a different computation (slt vs sra) — no, the target has `sra $21,$20,31`.
3. Reorder `pos[1] -= 0x24;` vs `pos[0] = step;`.
4. Add `base` refs: e.g. use base in the inner loop twice? no.

Hmm, what about this: the launder gave `tmp` a second set, which affects the ref count of the pseudo `base`? No...

Let me look at the difference in the .greg order between the target (with launder) and w3 (without). That will show exactly which allocno's priority changed.

I have dmp (target, with levers) and dmp3 (w3). Let me compare their alloc tables' order lines.
