---
ts: 2026-11-06T12:28:26Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG31
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_7FgGCnccbf76HOlQZ6G2
---
All worse than 2. Barrier stays at 2 (b0). Now I have 30 tries for item 2.

Wait — before recording WALL, let me reconsider whether the keepalive might be crackable with a cleverer real-C move, since 19 is the dominant term. Hmm, 19 is REG-caller with a 3-cycle rotation. 

One more idea worth 2 tries: since the asm gives pb 5 refs, what if I reduce the number of competing *global* pseudos? E.g. `eight` (s32 eight = 8) is a loop-invariant; `m` (D_8011511A)... 

Actually — hmm, what about `j`? Target has j in t0. j is the loop counter, used in `j == 0` and `j++`. In mine j is in a3.

Honestly, the cleanest interpretation: the register assignment follows a priority order that the 5 asm refs flip. Nothing in real C adds 5 refs to a constant address.

BUT: there's one legitimate trick — `pb` is used as an index into D_800AE7BC. What if the code uses `pb` in a place where it's naturally reused... 

Let me try one final idea: make `pb` a `u16 *const`? No effect.

Alternatively make the expression use the address twice per statement: `D_800AE7BC[*pb].ot[2]` → `D_800AE7BC[*pb].ot[2]` where `.ot[2]`... no.

OK, record WALL for item 2 with best = 21? Wait: the lever-free best. v0.c = 21. But hold on: is there a better lever-free body? My best lever-free candidates were v0 (21), v1 (30), p2 (20!). p2 = 20 is lever-free (both asm removed) and scores 20. Actually p2 = "pb2 initialised at its declaration" on k0.c — k0 has the keepalive removed but the BARRIER KEPT. Hmm: k0 = orig minus keepalive = barrier kept. So p2 has the barrier → not lever-free.

Lever-free = v0-based. My p-series was on k0 (barrier kept). So lever-free best = 21 (v0).

Hmm, can I combine? Let me make one final attempt: v0 (both removed) + pb2 init at decl, and v0 + best barrier order (t5/t8 = 4 with barrier kept).

Actually let me test the combination "barrier fixed as much as possible + keepalive best": since neither is fully fixed, best = min over lever-free.

Let me try 2 combos: v0 + pb2-at-decl; v0 + t5-order. If one gives < 21, use it as best.

Then record.

Actually, also worth one shot: PARTIAL is only if score 0, so no.

Let me run the combos.
