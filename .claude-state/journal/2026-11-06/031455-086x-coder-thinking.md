---
ts: 2026-11-06T10:14:55Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG27x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_7CCnf6Kn0RAk5EHx6RNV
---
Item 3's globals order: 81 98 78 82 79 76 77.
- r76: pri 6086, refs 7, live 23, crosses 1 call
- r77: pri 5384, refs 7, live 26, crosses 1 call

So r76 (pri 6086) is allocated before r77 (5384). Which is `a` and which is `div`? The target wants div=s0, a=s1. Currently (nopin) mine has div=s1, a=s0 — so the higher-priority r76 gets s0 and is `a`; r77 is `div` (lower pri, gets s1).

Wait, mine: "s1->s0 x7, s0->s1 x4" — mine has a in s0, div in s1. So r76 = a (pri 6086 → s0), r77 = div (5384 → s1).

Target wants div=s0, a=s1. So we need div's pri > a's pri. Currently div 5384 < a 6086. Need to flip: div > a.

div: refs 7, live 26. a: refs 7, live 23.

If we can shorten div's live to 22 (or lengthen a's live to 27), the priorities flip.

div's live = from `div = arg3` (prologue) to the last div use. a's live = from `a = arg2` to the last use.

In item 3, `a = arg2; ... div = arg3;` — a is assigned first, then div. Both in the prologue. Their live ranges end at their last uses.

Hmm, if we swap the assignment order: `div = arg3; a = arg2;` — the live lengths might change slightly. Also `div = (s16)div` and `a = a & 0xFFF` positions.

Let me look at the target asm to understand the intended order:
From the --explain diff:
- target[1:3]: sw s1,20(sp); move s1,a2   → a = arg2 → s1 (early)
- target[4:5]: move s0,a3 → div = arg3 → s0
- mine: move s0,a2 (a→s0); sw s1; move s1,a3 (div→s1)

So target prologue: save s1, move s1,a2 (a), then move s0,a3 (div).

The target has a→s1 and div→s0.

Now, priorities: div must outrank a. div: refs 7, live 26. a: refs 7, live 23. Since both have refs 7, the shorter live wins. a's live is shorter (23) → a wins s0. To flip, div's live must be < a's, i.e., div's live < 23, or a's live > 26.

div's live: from `div = arg3` to the last div use. a's live: from `a = arg2` to the last use.

In the source, `a = arg2; div = arg3;` — a is assigned first, so a's birth is earlier. If we assign div FIRST (`div = arg3; a = arg2;`), div's birth is earlier and a's later. That would make div's live LONGER and a's SHORTER — wrong direction.

We want div's live SHORTER: assign div LATER (after a). Currently div is already after a. Hmm.

The live length is death - birth. To shorten div's live, move `div = arg3` later (closer to the divs) or shorten a's... 

But the target's prologue has `move s0,a3` (div) after `move s1,a2` (a). So div is assigned after a in the target too.

Hmm, the death points: a's last use and div's last use. In the target, the divisions are in the `else` branch; a is used in `diff = cur - a` etc. Let me look at the target asm to see the last uses.

Actually, let me reconsider: the difference between live 23 and 26 is 3 RTL insns. Small. Maybe a statement reorder can flip it.

Let me try:
1. Move `a = a & 0xFFF;` and `cur = ang & 0xFFF;` around.
2. Move `div = (s16)div;` earlier/later.
3. Swap `a = arg2; div = arg3;` order.
4. Move `div = (s16)div;` before `ang = ...`.

Let me check the target asm around the div/a sign-ext:
From --explain:
- mine[14:15] sll v1,s1,0x10 (deleted vs target) — this is div's sign-ext (div in s1).
- target[14:16]: sll s0,s0,0x10; andi s1,s1,0xfff — div sign-ext in s0, a mask in s1.

So target order: div sign-ext (sll s0) then a mask (andi s1). Mine: div sign-ext (sll v1... hmm mine[14] sll v1,s1,0x10 — that's sll v1 = s1<<16; then mine[18] sra s1,v1,0x10. So mine's div sign-ext is sll v1,s1,0x10; sra s1,v1,0x10 (2 insns, dest s1). Target: sll s0,s0,0x10; sra s0,s0,0x10 (dest s0).

So mine's div sign-ext uses a temp v1 (because div is in s1 and the sll dest must differ? no, sll can be in-place). Hmm, mine: `sll v1,s1,0x10` then `sra s1,v1,0x10`. Target: `sll s0,s0,0x10; sra s0,s0,0x10`. So mine uses a temp v1 for the intermediate, target is in-place. That's because of the register assignment (div in s1, and s1 is also used... hmm).

Anyway, the key is the priority flip. Let me try statement reorders.

Let me look at the full target asm for item 3 to understand. Let me keep the orig object and objdump.

Actually, let me just try variants and score. Item 3's lever-free baseline (nopin) score should be ~20. Let me first score nopin, then variants.

Let me test:
- a1: swap `a = arg2; div = arg3;` → `div = arg3; a = arg2;`
- a2: move `div = (s16)div;` before `ang = ...`
- a3: move `a = a & 0xFFF;` before `div = (s16)div;`
- a4: move `div = (s16)div;` after `cur = ang & 0xFFF;`
- a5: declare div before a (decl order)
- a6: `div = (s16)arg3;` at decl, remove later

Let me batch.
