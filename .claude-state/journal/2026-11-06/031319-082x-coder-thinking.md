---
ts: 2026-11-06T10:13:19Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG27x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_rc6WECiE3Y7QDpQsnE6B
---
g1's asm: 
```
38f8: sll v1,s1,0x10     # d sign-extend (d in s1)
38fc: andi s0,s0,0xfff    # s1ang masked (s1ang in s0)
3900: addiu v0,v0,-1024   # u5
3904: andi a0,v0,0xfff    # u5 mask
3908: bne s0,a0
390c: sra s1,v1,0x10
```
So s1ang is in s0, d in s1. Still swapped! Despite s1ang being global (pri 6363 > d 5185).

Wait, the alloc table said r75 (s1ang) pri 6363 and r74 (d) pri 5185, and the global order is 77 79 78 76 75 74. So r75 (s1ang) is allocated before r74 (d). The first callee-saved reg available... r77/r79/r78/r76 don't cross calls (they get caller-saved). r75 (s1ang) crosses the call → gets s0. r74 (d) → s1. Yes.

So to flip, d must come BEFORE s1ang in the global order: d pri > s1ang pri. d 5185 vs s1ang 6363. Need d > 6363.

d: refs 7, live 27 → 5185. To get > 6363: shorten live to 22 (2*7/22=6363, tie → lower allocno r74 wins). Or increase refs to 8: floor_log2(8)=3, 3*8/27 = 0.888 → 8888 > 6363! 

How to increase d's refs from 7 to 8 without adding instructions? Hmm. refs count uses+defs. d is: def (move), use (sll), def (sra), use×2 (divs) = 5? But the table says 7. Maybe sll and sra each count differently.

Alternatively, shorten d's live range. d's live = 27 (from insn 6 to the last div). If we move the `d = (s16)d` later or the divisions earlier... hmm.

Actually, the cleanest: make s1ang's priority LOWER by reducing its refs or lengthening its live range. s1ang (global) refs 7, live 22. If we lengthen its live range (define it earlier / use it later), pri drops. E.g., live 30 → 2*7/30 = 0.466 → 4666 < d 5185 → d gets s0! 

Can we lengthen s1ang's live range without changing instructions? The live range is from the load to the last use. The last use is `addiu v0,s0,-4096` (position 33). The load is at position 9. If we move the load EARLIER (e.g., before `d = arg1`), the live range grows. r6 tested s1ang load before d=arg1 (in the nopin structure where s1ang was local). In g1's structure, let me try moving the load earlier.

Actually, the live length in the alloc table is measured in insn numbers (qty_death - qty_birth). Moving the load earlier by a few insns increases live.

But careful: the target's asm has the load at a specific position. If we move the source load earlier, the asm might change.

Hmm, but the target's `lh s1,18(v0)` is after `lw v0,32(v0)`. The `lw v0,32(arg0)` is forced before the load. 

Let me try: in g1, move the s1ang load to before `d = arg1;`. The live range grows by ~1. Not enough (need +8).

Alternatively, reduce s1ang's refs: currently 7. If we remove one use... but the uses are all needed.

Hmm, wait. In g1, s1ang is used as u6 (5 uses). What if we keep s1ang as the masked value but ALSO use a separate u6 for some uses? That splits refs.

Actually, hold on. Let me reconsider the target: maybe in the ORIGINAL, s1ang and u6 were SEPARATE globals: s1ang (refs ~3) and u6 (refs ~5). Then:
- s1ang: global, pri = 1*3/live. If live ~20 → 1500.
- u6: global, pri = floor_log2(5)*5/live = 2*5/~40 = 2500.
- d: 5185.
Order: d (5185) first → s0. Then u6 (2500) → s1. Then s1ang (1500) → s2. But target uses only s0,s1! Unless s1ang and u6 share a register (tied). If they're tied (local-alloc combine), they'd be one qty. But they can't be tied if both are global (reg_qty -1).

Hmm, unless the andi is a self-set (s1ang = s1ang & 0xFFF) making them the same pseudo. Then refs 7.

OK so in the target, the s1ang/u6 qty has ~7 refs and is global. Its pri must be < d's 5185. With refs 7, live must be > 27*7/7... let me solve: 2*7/live < 0.5185 → live > 27.0. So if s1ang's live length > 27, d wins.

In g1, s1ang live = 22. If we make it 28+, d wins! How? Move the load earlier in the source and/or the last use later.

The last use of s1ang in g1 is `addiu v0,s0,-4096` (insn 33). The load is at insn 9. Live 22 (in the RTL, insn numbers differ).

If we move the s1ang load to the very beginning (before `d = arg1`), the birth moves earlier by ~2 insns → live 24. Still < 28.

Hmm. What if we use s1ang even later, e.g., in the division blocks? That would extend the live range a lot. But adds uses (refs up).

Hmm, what if the live length is measured in the RTL (pre-scheduling), where the load and uses are at different positions.

Alternatively, increase d's refs to 8. How? If d were used one more time. E.g., the sign extension: `d = (s16)d` — maybe writing it as `d = d & 0xFFFF; d = (s16)d;`? No.

Hmm, what if d's declaration/use creates an extra ref? For instance, `q = iVar4 / d` twice = 2 uses. What if we compute `q = iVar4 / d;` once and reuse? That changes code.

Let me reconsider: d refs 7, live 27. In g1, d is r74 with refs 7 live 27. To get refs 8: maybe `d = (s16)(d + 0)`? adds instructions.

To shorten live to 22: move the sign-ext earlier? The sign-ext is at insn 55 (RTL). If we move `d = (s16)d;` earlier (right after `d = arg1`), d's live would be ~2, and the sign-extended value would be a separate global... hmm, no: the self-set means the same pseudo, so moving the sign-ext earlier shortens the *raw* part but the pseudo's birth is still insn 6 and death at the last div. qty_birth is the first def, qty_death the last use. So live stays ~27.

Hmm, actually for a self-set pseudo, birth = first def (insn 6), death = last use (last div). So live is fixed ~27.

To shorten d's live: move `d = arg1` LATER (closer to the divs). But the target has `move s0,a1` in the prologue.

Hmm, but wait: if d's def moves later, the prologue changes. Unless the copy in the prologue is for a DIFFERENT variable.

Hmm hmm.

Let me reconsider: in the target, is d's live length really 27? We don't know the original RTL. But the target has `move s0,a1` at position 3 and the divs at ~37-53. So d's live is ~50 in the target asm. In RTL terms maybe 27.

OK, let me try a different approach for B: make s1ang global with a LONGER live range by moving its load to the top (before everything) and keeping the uses. Let me test in g1's structure.

Also, let me try making s1ang global but with FEWER refs: e.g., use u6 for most uses and s1ang only once in a later block:
```
s1ang = *(...);
u5 = ...;
d = (s16)d;
u6 = s1ang & 0xFFF;
...
iVar4 = u5 - u6;
...
q = iVar4 / d;
if (q == 0 && s1ang) q = 1;   // fake use
```
No, adds code.

Let me just try: g2 = g1 with the s1ang load moved to the very top (before d=arg1).

And g3 = g1 with the s1ang load after u5 (later birth → shorter live → worse). Skip.

Let me also try g4 = g1 with `d` declared before s1ang vs after (allocno number order matters for ties).

Let me create g2 and test.
