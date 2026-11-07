---
ts: 2026-11-06T21:18:09Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW50
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_3QZBmeqXbEp1zdtAeMg3
---
x is messy. Not helpful.

Time: 14:33, 35 min. I must stop item 1 and record a WALL. But let me reconsider: the WALL requires "best = lowest score of a lever-free body" = 4. And a wall tag. Which tag? This is a global-alloc priority/allocno-order issue where off outranks e. Tags available: `greg-ref-count` (global-alloc ref-count priority gives a hot pseudo a different hard reg), `global-pri-bank-order`, `greg-lo-reg-count`. The most fitting: `greg-ref-count` — global-alloc ref-count priority gives off (3 refs) a0 over e (2 refs). The launder raised e's refs to 4.

Actually the mechanism: global-alloc allocno priority (refs/live_length) orders e below off; the launder adds refs. So tag `greg-ref-count`.

But wait — maybe I should try ONE more thing: the "real 2nd set" could be achieved by making the pointer arithmetic real. What if `e` is used to compute the lim value too, but through a *different pointer* that is a copy of e, and that copy prevents cse sharing? We tried a/b (146).

Let me try one final idea: `e = (s16 *)((u8 *)D_801E8F78 + off) - off/... ` no.

Actually, let me reconsider the frame: the target has frame 40 due to pad[2]. What if the pad is used in a way that creates an extra use of e? No.

Let me just try 3 more variants to be safe (already >30 tries), then write the WALL row.

Actually, hold on. Let me reconsider the allocno order list: "78 108 117 74 127 150 76 95 141 73 128 79". e=79 last. Why is e last? Because e's live_length might be 4 but n_refs 2 → pri 0.5. off 95: 3 refs/8 = 0.375. So e should be before off. Since it's not, maybe allocno_live_length for e is not 4 but something like 8+ because the REG_EQUIV pseudo is live over the whole function in global-alloc's view? 

Actually, look at flow dump line 18: "Register 79 used 2 times across 4 insns; pointer." But maybe the LAST flow dump before global-alloc has different numbers. The flow pass runs once before global-alloc (after combine). The dump file cand.i.flow is from that pass. So 2 refs/4 insns.

Hmm, unless allocno_live_length uses `reg_live_length[i]` but the allocno for e includes another pseudo with a large live_length. Which pseudo could be tied to e? None obviously.

Wait, maybe the printed order isn't priority-sorted because `dump_conflicts` is called with the order but the list I see is from a different point. Let me look at the exact dump_conflicts code at 1643-1665.

Actually, line 4 "12 regs to allocate: 78 108 ..." — maybe this is printed at line 1652 inside dump_conflicts, using allocno_order. Fine.

I'll accept the WALL. But let me reconsider whether the item is even a "singleton crack" that should match. The list says this shard's items are singletons with levers. The expectation is some MATCH, some WALL. A WALL is acceptable.

Let me do a couple more tries to be thorough (≥30 tries already met), then write results.tsv for item 1 and move to item 2.

Actually, before giving up: one more idea that often works — change the *declaration order* of locals so the pseudo numbering changes the tie-break. But priorities aren't tied (0.5 vs 0.375). Hmm.

Another idea: change `lim` from s32 to s16. `lim` is loaded as s16 (sign-extended). If lim is s16, the comparison `t < lim` would need extension. Changes code maybe.

Another: make `off` unsigned so its live range... no.

Another: what if `t` is compared differently: `if (lim > t)`? Same.

Let me try one final: move `off = idx*4` to be computed inside the `if (t < lim)` block (after the branch). Then off is born later, live shorter → HIGHER priority → off still gets a0 (worse). No.

What if off is computed before `t = func_80029504()`? off needs idx.

OK, WALL it is. Let me record item 1.

Actually wait — let me reconsider the possibility of using `e` twice by NOT letting cse merge: use a `volatile` on one of the loads? That would force a reload (extra code). No.

Let me record the wall. But actually, let me try the idea of using `e` as the base for the lim load and see if there's a variant that keeps 147 insns and flips allocation. a/b were 146. What if we ALSO add a use that brings it back to 147? E.g., lim via e (146) + something that adds 1 instruction in the right place. Hmm, fragile.

Let me instead check: what if we compute lim via e but write the condition with the SYMBOL so they don't share? 
```
e = (s16 *)D_801E8F78;
off = idx*4;
lim = ((s16(*)[2])e)[idx][0];        // e+off
if (t < lim) {
    if (D_801E8F78[idx][1] == 0 || ...)  // sym+off+2
}
```
Then e is used for lim (1 use) and the condition uses the symbol. But target's condition uses e. Different.

Alternatively:
```
lim = D_801E8F78[idx][0];   // sym+off
e = (s16*)D_801E8F78;
if (t < lim) { if (*(s16*)((u8*)e+off+2)... }
```
current.

I'll stop. Record WALL.

Hmm, but actually the task says budget 20-30 min per item, and I'm at 35. Let me be efficient now: record item 1 and move on. I still have 3 items.

Wait, actually let me reconsider one promising move: the moves log line 44: "launder,pin | func_80186368 | MATCH — launder: p = *abase; p += 0x2D (self-reassign stales cse (plus p K) equiv, bump chain stays addiu)". So a self-reassign `p += K` stales cse. Our e is a constant; can't add.

Line 30: "launder | func_801A31CC | MATCH — pointer reuse: a1 = (u8 *)link; *(s32 *)a1 = 0; keeps the store base in the link reg". Pointer reuse.

Hmm. What if I reuse `e` for the `p = D_801E8F98[idx]` load? e is a s16*, p is void*. Not the same.

OK. Let me also consider: maybe I can flip the allocation by changing the *frame* — no.

Let me record WALL and move on. Actually, let me reconsider the score: "score 4 (REG-caller; mine 147 ins, target 147)". The wall tag from walls.txt: `greg-ref-count` fits ("global-alloc ref-count priority gives a hot pseudo a different hard reg"). Evidence: "global-alloc allocno order puts off(3 refs/8 insn) before e(2 refs/4); launder gave e 4 refs".

Let me write the row and append to moves.md. Format: `dir file func kinds result best tries wall evidence`.

dir = func_8017E590__ov_SC01_009_jr_8017E590
file = src/ov_SC01_009/ov_SC01_009_jr_8017E590.c
func = func_8017E590
kinds = barrier,launder
result = WALL
best = 4
tries = 31 (let me count precisely)
wall = greg-ref-count
evidence = "greg allocno order 95(3ref/8) before 79(2ref/4); launder's +2 refs raise e past off; barrier only orders the hoist" ≤140 chars.

Let me count tries: win, w1, w2, w3, v1, v2, v3, v4, a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, s, u, v, w2, x, y, l_only, b_only. That's 33 (including 2 CEs: w2? no w2 is the new one; old w2/w3 CEs). Let me say 30+ scored.

Hmm wait, I named a new file w2.c overwriting the old w2.c. Fine.

Let me update notes.md and results.tsv. Then move to item 2.

Actually, hold on. I want to give item 1 a bit more effort since it's the first and I'm learning. But the budget says 20-30 min. I'm at 35. The rule: "past 30 min stop and record a wall". So I must stop.

Let me write the results row and notes, then move on quickly.

Before that, let me double check: is `win.c` currently the lever-free best (score 4)? Yes, win.c has no asm. Good. The row result WALL with best 4.

Let me also delete the dumps to save disk (capped).

Let me write notes.md for item 1, append results.tsv, append moves.md. Then clean dumps.

One action per command. Let me do results.tsv append first (its own step). Actually the instruction: "One action per command: a results.tsv fix is its own step, never folded into a check command." So I'll write results.tsv alone.

Let me prepare the exact evidence string ≤140 chars:
"greg allocno order: off=95(3 ref/8 ins) before e=79(2 ref/4); launder +2 refs lifts e past off; barrier only fixes hoist order"
Count: ~120. Good.

Let me write.
