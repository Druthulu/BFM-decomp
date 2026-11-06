---
ts: 2026-10-22T21:57:37Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG18
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_CRqTzu1cC24A0ucUzQMp
---
s2 = 4 (read + -0x60 pair in a do-while).

The 4-class is: 79 ins, the -0x60 group in the delay slot.

I've been at this ~18 min with ~42 tries. Let me make one more focused attempt at getting the group out of the delay slot, then WALL.

New idea: the -0x80 group is NOT hoisted. What's different? It comes later in source. So sched1's ready-list ordering prefers the first group.

What if I make the -0x60 group's values *depend on the -0x80 group's stores* (memory dep)? E.g. store -0x80 first, then store -0x60 derived from... no, values are constants.

What if the -0x60 group is written AFTER the -0x80 group in source and the LAW-1c reversal applies? i1/i2 tried orders; the asm order would then be -0x80 first (mismatch).

OK. Alternative: make the -0x60 group's *addresses* come from the table index so they're dependent on the chain? no.

Let me try one thing: what if the -0x60 stores are written as storing to `D_80126970` and `D_80126976` but the two are declared in a struct so the addresses are computed... no.

I'll WALL item 4 with best 4 (s2/q-variants).

Hmm, but wait — the WALL requires the best lever-free body in win.c. Let me set win.c = s2 (score 4).

Hmm, s2 has a do-while with the !FAKE comment. Is a do-while a "lever"? The brief says `do{}while(0)` only with `// !FAKE: do-while` — so it's permitted as a plain C move. OK.

Let me finalize item 4 with best 4, and record.

Actually hold on. Let me reconsider one more idea before WALLing: the reason the -0x60 group is hoisted is that it's ready at the lh. What if I *remove* the lh from the block start by making the table read happen earlier — i.e. move the read to the TOP of the if-block, before `func_8017E664()`? The call would split the block. In the target, the read is after the call.

What if I move the `v1 = ...` read before the call and keep the stores after? Then the delay slot issue vanishes but the asm order changes (lh before jal) — mismatch.

OK, WALL. Actually — one more idea: what if the two `sh` stores of -0x60 could be made to depend on the loaded v1 by using v1 as the *base* of the store address in a way that folds? E.g. `*(s16 *)((u8 *)&D_80126976 + (v1 & 0))` — `v1 & 0` folds to 0 → constant address. gcc's fold will do it.

What about `(v1 * 0)`? folds.

What about `(v1 >> 31 & 0)`? folds.

Fine, WALL.

Actually, let me try ONE more: the `Blk8` copy at the end reads D_801944F4[...] — if the -0x60 stores came after it (j2 = 26, 79 ins). No.

And one final: what if the -0x60 group is placed between the table read and the v1 stores but *after* the Blk8 copy... no, order.

Decision: WALL, best 4, tag `sched1-load-delay-fill` (new tag, defined in evidence).

Wait — there's an existing tag `sched2-load-delay-fill` in moves ("sched2-load-delay-fill — li a1 arg const has no dep on the lw unk20, fills its load delay (target nop); best 8"). That's exactly the same mechanism but sched2. Here it's sched1. So the tag `sched1-load-delay-fill` is apt and consistent with the existing naming.

Let me finalize.

Time: 16:06, item 4 at 18 min, ~45 tries. Good.

Set win.c = s2, clean up, notes, results, moves.
