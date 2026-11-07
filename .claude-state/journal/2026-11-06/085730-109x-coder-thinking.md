---
ts: 2026-11-06T15:57:30Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO05
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_ItZVgqtTcXei7xO9im38
---
j6 (do-while around the call) gives 10 ORDER, 346 ins — interesting, changed the order. Not 0.

Time check: ~09:02. Started item 4 ~08:47 → 15 min. Tries now ~29. Let me do a few more to reach 30+ and 20 min.

Let me test a couple more quickly:
k1: `arg = &D_800AF648; ... func_80052E38(arg);` with the call in a do-while AND arg used... 

Actually, let me test the combination that got the la first (vh1) plus fixing the spill order. The vh1 residual (12) is spill order: target has sw s7/lui s7, sw s2/addiu s2, sw s6/addiu s6 interleaved; vh1 has them later. What if I keep the setups in source order BEFORE the call but move the call earlier than ot? No, the call must be after ot.

Hmm, what if I put the `arg` assignment first, then the setups, then ot, then the call (original order), but add a *second use* of arg somewhere to keep the set? We need a zero-cost use.

Idea: use arg as the base of the *D_800AF648* store? no.

Idea: `ot = (u32)&D_800A6610[...]` — could write `ot = (u32)arg - (u32)&D_800AF648 + (u32)&D_800A6610[...]`? That's a real expression using arg! It computes the same value (arg - &D_800AF648 = 0). Hmm, that's an identity-ish trick (arg - itself). It might fold. Not allowed as an identity launder.

OK, I'll wall item 4. But wait — let me reconsider the possibility that the *2-output launders* are not needed if the arg launder is fixed. The 2-output removal gave 39 with the arg launder kept. So they're needed.

Both load-bearing. WALL with best lever-free 43 (c1).

Hmm, but actually — maybe I should reconsider whether c1 is really the best lever-free. c1 = all 3 asm removed, score 43, 344 ins. Yes, that's the only fully lever-free body. So best 43.

Wait, is c1 fully lever-free? It still has the 6 pins (register asm declarations). The row kind is "launder" only; the pins are a different kind, already present in the def — allowed to stay. So c1 is "lever-free" w.r.t. the row kind (launder). Good.

Let me do 2-3 more tries to be safe (30+), then write the WALL.

Actually, hold on. Let me reconsider the 2-output launder with a *different* plain-C approach: the launder re-ties n and otz. What if we introduce a second *set* of n and otz that is real and zero-cost by using a *compound assignment*? E.g., `n &= 0xFFFF;`? That's an identity (mask) — not allowed and might add code. 

What if `n` is used in a way that naturally re-sets it: the target's `if (n < 4)` in each tail. If we write the two tails differently: e.g., in the POLY tail `if (n < 4)`, in the LINE tail `if ((u32)n < 4)`. Different C spelling but same RTL → still merged.

Hmm.

What about giving n a second set via `n = w >> 8;` in the LINE tail only — costs 1 insn (350). Not zero.

OK, wall.

Actually, wait. Let me look at the moves for func_8017DC80 or similar — maybe another shard already cracked this exact function! grep moves for 8017DC80.
