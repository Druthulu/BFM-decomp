---
ts: 2026-10-22T05:25:02Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG08c
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_NsWZaudj54R9VqSGfpql
---
y1's residual (33): the callee-saved bank is permuted:
- mine: s0 = the counter (i), s2 = r, s3 = t.
- target: s3 = the counter, s2 = t, s0 = r.

So the target: r=$16 (s0), t=$18 (s2), i=$19 (s3); mine: i=$16 (s0), r=$18 (s2), t=$19 (s3).

So in mine, the counter takes s0 (the first callee-saved) — it's the first LO_REG created (the loop counter is created first) — while in the target the counter is LAST (s3).

And mine: r=s2, t=s3; the target: t=s2, r=s0.

So the target's order: r, ?, t, i → hmm, the target has r=s0, t=s2, i=s3, and s1 = ? (some other var).

Mine: i=s0, r=s2, t=s3.

So I need: the counter to be allocated LAST (its pri lowest or its allocno highest), and r before t.

Since the tie-break is the lower allocno wins, and the LO_REGs are allocated in the order 116, 124, 136, 144 → $16, $17, $18, $19.

Hmm: in y1, the four LO_REGs are (loop 1: the counter i?, the call result t?) and (loop 2: ...). Hmm, but in the target, both loops have the same register assignment (i=s3, t=s2, r=s0) — the two loops are separate code with separate pseudos, but the ROM has them in the SAME registers (s3, s2, s0) — because the two loops are... hmm, they're at different addresses, so they can use different regs. But the target shows both loops using s3 (the counter), s2 (t), s0 (r) ✓ — the same regs in both loops!

Interesting: so in the ROM, the loop variables of BOTH loops are in the same registers. Hmm, that means the 4 LO_REGs in the .greg order are: r116 (loop1's r?), r124 (loop1's t?), r136 (loop2's r?), r144 (loop2's t?) — and the counter is a separate pseudo (not a LO_REG?).

Hmm, hmm. Whatever: mine has the counter in s0 (the first LO_REG slot).

So the difference: in the ROM the counter is in $19 (the LAST callee-saved) and r in $16 (the first).

Lever-free: the counter is in $16 (the first) → the counter's LO_REG is allocated first → its allocno is the lowest → it's created first.

The counter `i` is created first because the `for` loop's init `i = 0x600` comes first in the code ✓.

To make the counter LAST: it must be created last, or have a lower priority.

Hmm! The counter's pseudo is created at the loop's init. What if the counter's assignment were moved later? E.g. the loop as:
```
for (i = 0x600; i < 0xB00; i += 0x100)
```
The init creates the pseudo first.

Hmm, what if the loop were:
```
i = 0x600;
while (i < 0xB00) { ... i += 0x100; }
```
Same (the init is first).

Hmm, what if the counter were assigned inside the loop body (a do-while style)? Then the pseudo is created later ✓:
```
i = 0x600;   /* hmm, still first */
```
Hmm, the assignment `i = 0x600` creates the pseudo at that point — before the loop body's `t = call`.

To create the counter's pseudo LAST, the first assignment to i must come after the t/r assignments. E.g.:

```
for (;;) {
    t = func_8012C658(0x265, 2, a0);
    if (t != 0) { r = rand() & 7; ... }
    i += 0x100;      /* the counter's first assignment here! */
    if (i > 0xB00) break;
}
```
Hmm, but the ROM's loop: `li s3,1536` (i = 0x600) is BEFORE the loop (in the diff: mine[105] `li s0,1536` vs the target's `li s3,1536`) ✓ — so the counter's init is before the loop in the ROM ✓ → the counter's pseudo IS created before t's in the ROM too!

Hmm! But in the ROM the counter lands in $19 (the last). So the pin is what puts it there ✓ (the pins decide, not the priorities).

Hmm, so lever-free the counter would be first (as in mine) unless the priorities change.

Hmm, so the levers:
1. t's pri vs r's pri (both 40000, ties → the allocno).
2. The counter's pri.

The counter's pri (refs 4, live 2 → 40000) — hmm, the counter has refs 4? (the init, the compare, the increment, the uses in the address computations ✓ 4 refs).

Hmm, so all the loop vars have pri 40000 and the tie-break is the allocno: the counter (created first) wins $16 ✗.

To make the counter lose, its pri must be < 40000: e.g. live 3 → 16*10000/3 = 53333? hmm: pri = 2^floor(log2 4)*4*10000/live = 16*10000/live → live 2 → 80000?! Hmm, that doesn't match 40000.

Hmm: the table says pri 40000, refs 4, live 2. With my formula: 2^floor(log2 4)=4 → 4*4*10000/2 = 80000 ≠ 40000. Hmm! So the formula must be different: maybe pri = 2^floor(log2 refs) * refs * 10000 / live with refs=4: 4*4=16 → 16*10000/2 = 80000. But the table says 40000 → so the formula gives 40000 for (4,2) → 8*10000/2 = 40000 → so pri = 2^(floor(log2 refs)-1) * refs * 10000/live? Hmm, for refs 4: 2^(2-1)=2 → 2*4*10000/2 = 40000 ✓. And for refs 3, live 3 (item 1): 2^(1-1)=1 → 1*3*10000/3 = 10000 ✓✓. And refs 2, live 2: 2^(1-1)=1 → 1*2*10000/2 = 10000 ✓✓. And refs 4, live 7 (item 1): 2*4*10000/7 = 11428 ✓✓ (the notes said 11428 ✓).

So the formula is pri = 2^(floor(log2(refs))-1) * refs * 10000 / live. (The alloc_table.py docstring said "floor(log2 refs) * refs / live * 1e4" — hmm, that gives 8*10000/7 = 11428 ✓ for refs 4 — hmm, that contradicts my new formula. Hmm: floor(log2 4) = 2 → 2*4*10000/7 = 11428 ✓ with the DOCSTRING's formula. And for (4,2): 2*4*10000/2 = 40000 ✓✓. And for (3,3): floor(log2 3) = 1 → 1*3*10000/3 = 10000 ✓✓. And (2,2): 1*2*10000/2 = 10000 ✓✓.

So the docstring's formula ✓ (I miscalculated earlier). Good: pri = floor(log2 refs) * refs * 10000 / live.

OK so all four LO_REGs: refs 4, live 2 → 40000 ✓ (a tie) → the allocno decides.

So for item 5, everything hinges on the pseudo creation order (the allocno) and the refs/live of the loop variables.

Levers:
(a) Make `r` have more refs (5+ → floor(log2 5)=2 → 2*5=10 → pri = 10*10000/live; with live 2 → 50000 > 40000 ✓ → r would win $16 ✓✓).
Hmm! How to give r 5 refs without changing the code? r's refs: the def (1) + 2 uses (the two multiplies) = 3? Hmm, but the table says the loop vars have refs 4. Hmm.

Hmm, r = rand() & 7 → refs: the def + 2 uses = 3. Hmm. But maybe the table's r115 etc. are t's.

Hmm, let me think about which is which: r108 (block 6), r115 (block 5), r116 (block 5, LO_REG), r117 (block 5), r119 (a0, block 5), r123 (block 5), r124 (block 5, LO_REG), r125 (block 5)...

So in block 5 (the first loop) there are 8 pseudos: r115, r116(LO), r117, r119, r123, r124(LO), r125, r111.

The LO_REGs (r116, r124) are the ones wanting callee-saved regs: those would be `i` and `t` (live across the call ✓). And `r` is live across the rand() call too... hmm, r is assigned AFTER the call, so it's live across the rand() call ✓ → it should be a LO_REG too.

Hmm, but r115 has hard v0 (a local allocno). Hmm.

OK, I'm going too deep. Let me try more empirical variants around y1 (the best, 33):

z1: y1 + the counter's live range changed (e.g. the counter used via a temp inside the body).
z2: y1 + r via a temp (y4-style) combined.
z3: y1 + t via a temp (y5-style) combined.
z4: y1 with the loop as a do-while.
z5: y1 + the loop bounds as variables.
z6: y1 + r assigned via a temp: `s32 r2 = rand() & 7; r = r2;` (hmm, that adds a copy).
z7: y1 with `r` declared/used in a different order.
z8: y1 with the counter `i` copied into a temp at the top of the body.

Let me generate ~10 and score.

Time: 23:33. I need to wrap up by ~00:15. Let me do 2-3 more batches for item 5, then record both items 4 and 5,then write the log.
