---
ts: 2026-10-22T05:22:50Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG08c
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_mKmjxQ25wLa7t3mECvJh
---
Item 5: two pins ($19 on the loop counter i, $18 on the call result t). The lever-free version: 58, 167 ins.

The notes say: the four globals wanting callee-saved regs are the LOOP variables (pri 40000, refs 4, live 2, "pref LO_REG") — the .greg order is 120 128 142 150 92 75 73 72 74.

Hmm, "pref LO_REG" — the loop registers.

Key: the ROM has the loop counter in $19, the call result t in $18, and r in $16. Lever-free: t takes $16 (more refs), r takes $18, the counter moves.

So the lever: the allocation order of the callee-saved regs. To flip: the call result `t` must have a LOWER priority than r, or the counter must rank first.

Hmm, pri 40000 for the loop variables (refs 4, live 2 → 4*4*10000/2 = 80000? hmm: 2^floor(log2 4)=4 → 4*4*10000/live = 16*10000/2 = 80000. Hmm, the notes say 40000 → maybe refs 4 live 4: 16*10000/4 = 40000 ✓).

So the four loop variables have pri 40000 each, and the allocation order (the .greg order) decides: 120 128 142 150 → the first gets $16.

To get the ROM's order (r=$16, t=$18, i=$19), we'd need r first, t third, i fourth.

Hmm. The loop variables: i (the counter), t (the call result), r (the rand value), and maybe v/w.

Their priorities are equal (40000) → the tie-break is the allocno number (global.c:607) → the earlier-created pseudo wins. So the order is by creation: 120, 128, 142, 150.

To flip the order, we need to change the CREATION order (i.e. the order of the pseudo creation in the RTL) — that follows the source order of the variables' first definitions!

In the source: `t = func_8012C658(...)` comes first, then `r = rand() & 7`. And `i` is the loop counter (created first, at the for loop).

Hmm, so the creation order: i (the counter, first), t, r → the allocation: i=$16, t=$18?, r=$19?

Hmm, but the notes say lever-free t takes $16 (it has more refs) → so t's pri > the others.

Hmm: t has more refs (it's used in 4 places) → pri = 2^floor(log2 refs)*refs*10000/live.

To make r win $16 and t get $18: t's pri must drop below r's, or r's must rise above t's.

Hmm, the ROM: r=$16, t=$18, i=$19 — so the order is r, ?, t, i. Hmm, 4 regs: $16=r, $17=?, $18=t, $19=i.

Hmm, so the allocation order (by pri) = r, X, t, i.

Lever-free: t=$16 (the most refs) → so t's pri is the highest.

To make r the highest: r's refs/live must beat t's. r = rand() & 7 → used in 2 places (2 multiplications) → refs 3 (def + 2 uses)? t = the call result → used in 4 places (t != 0, t+0x10, t+0x18) → refs 4.

Hmm, pri: t (refs 4, live 2) = 16*10000/2 = 80000; r (refs 3, live 2) = 1*3*10000/2 = 15000. Hmm, so t >> r ✓ (matches the notes).

To flip: make r's live range shorter or its refs higher? r's live range: from the assignment to its last use (the 2nd store) → live ~2-3.

Hmm, pri = 2^floor(log2 refs)*refs*10000/live: r with refs 3 → 3; with refs 4 → 16 → a big jump! So if r had 4 refs (instead of 3), its pri would be 16*10000/live vs t's 16*10000/live → a tie → the tie-break (the allocno) decides.

Hmm! So: if r's refs = 4 and its live = the same as t's, they'd tie and the creation order would decide. r is created AFTER t (in the source) → t would still win ✗. Hmm, unless the creation order flips.

Hmm, alternatively: make r's live range SHORTER than t's. E.g. if r's last use is earlier... hmm.

Alternatively: use r more (increase its refs): e.g. `r = rand() & 7;` used twice → 3 refs. If it were used 4 times → pri 16x.

Hmm, how to add a ref to r without changing the code? E.g. `r = rand() & 7;` → `r = (rand() & 7) & 7;`? That changes the code (an extra andi) ✗. Hmm, but maybe gcc folds it ✓ (and & 7 of an & 7 → the same) → no code change but an extra ref? Hmm, after folding, the refs may be the same.

Hmm.

Alternatively: make t's live range LONGER (lower pri). t's live range = from the call to its last use. If t were used later (e.g. after the loop) → longer live → lower pri ✓. Hmm, but that changes the code.

Hmm, the loop: `for (i = 0x600; i < 0xB00; i += 0x100) { t = func_8012C658(...); if (t != 0) { r = rand() & 7; ... } }`.

Hmm, what if the call result is assigned to a temp and then to t (an extra copy)? That adds refs to the temp but not to t.

Hmm.

What about the loop counter i: it's in $19 in the ROM (the LOWEST of the four). Lever-free it lands in $16. To make i the lowest priority: i's pri should be the lowest. i's pri = 40000 (refs 4, live 2)? Hmm, the notes say the four loop variables all have pri 40000 (refs 4, live 4?). Hmm, but i's refs: the loop counter has few refs (the init, the compare, the increment) → refs 3? Hmm.

Hmm, "the four globals that want callee-saved registers are the LOOP variables (pri 40000, refs 4, live 2, 'pref LO_REG')" — so all four have the same pri → the tie is broken by the allocno → the creation order.

So: i, t, r, and one more (v or w?) all with pri 40000 → the order is by creation. In the source, `i` is created first (the for loop's init) — hmm, but the notes say lever-free "the call result t takes $16 (it has more refs)". So t's pri > 40000.

Hmm, so t has more refs than the others.

The ROM's order: r=$16, ?=$17, t=$18, i=$19. So r is created first?? Hmm, r is declared before t in the source (`s32 r;` then `register s32 t`), so r's pseudo number is lower than t's ✓ → r wins the tie ✓. And i is declared first (`register s32 i` is the first declaration) → i's number is the lowest → i would win the tie ✗ (the ROM has i in $19, the last).

Hmm, but i is a LOOP variable (pref LO_REG) — the loop registers are allocated differently (the loop's registers are assigned by the loop optimizer: i is the induction variable → it gets the "loop register" treatment).

Hmm, and the notes say lever-free the loop counter lands in $16. Hmm.

This is complex. Let me try empirically:
x1: the loop counter as a different type (s16/u16)? changes the code.
x2: `t` assigned via a temp: `s32 t2 = func_8012C658(...); t = t2;` → changes t's pri? Hmm, it adds a pseudo.
x3: the loop written as a while/do-while.
x4: the loop bounds as variables.
x5: `r` computed twice? no.
x6: the loop counter incremented in the body vs the for-header.
x7: the `t != 0` test as `if (t)`.
x8: r's uses: `r` used twice — what if we introduce a second variable `r2 = r` for the second store? That adds a pseudo but changes the code (an extra copy) ✗.
x9: the loop counter `i` as a local declared inside the loop.
x10: the whole `for` loop as a `do-while`.

Let me check the item 5 orig.c freshness first! (diff against the current src).

Let me do that plus the item-4 final batch in one call.

Actually, let me check the freshness of item 5's orig.c right now (important!) and score item 5's nopin.
