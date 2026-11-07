---
ts: 2026-11-06T17:43:41Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO05x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_DeN1ynIRMa01pWUb4Pxr
---
Time 17.9 min. t2/t3/t4 = 5.

Let me look at t2's diff to confirm it's the same order issue. Probably.

Hmm, what if I could make the *sra* be the first scheduled instruction while keeping the named lo? The sra is inline in the sum expression. sched1 orders by dependencies/priorities. The srl (lo) has a lower UID. sched1's backward scheduling might place... 

Idea: give the sra a *dependency* that forces it earlier? No.

Idea: compute lo from a *later* expression so its UID is after the sra: e.g., 
```
s32 lo;
p[0x79] = (u16)(((sh16 >> 16) + (lo = ...)) >> 1);
```
s1 = 7 (sh16=v1).

So hi-first → v1. lo-first → v0 but wrong order.

There's a coupling: the register assignment and the scheduling order both flip together.

Maybe try: lo-first form but with the two shifts' *sources* arranged so sched1 orders them sra-first: e.g., make the srl depend on the sra's result? No (wrong semantics).

Hmm, what if lo is computed first but from a different expression that sched1 schedules later: `lo = (s32)(sh16 >> 31) & 1;`? adds an and.

I'll stop. Time 18 min. Let me do a couple more and record the WALL with best 5 at 20 min.

Actually — hold on. What if the score-5 body is close enough that a different *final expression* fixes the order? The target order: sra, srl, addu, sra, sh. Mine (t2): srl, sra, addu, sra, sh. So only the first two are swapped.

sched1 (backward) schedules the block; the final order depends on the insn priorities. The sra and srl are independent; their order in the final schedule is determined by the scheduler's list scheduling. If the source has srl first, it usually keeps it.

What if I write the sum as `(lo + (sh16 >> 16))` (operand order swapped)? The addu would be `addu v0,v1,v0`? The target's addu is `addu v1,v1,v0` (hi + lo). If the C is `lo + hi`, the addu operands swap → mismatch. But maybe the scheduler/combine canonicalizes.

Let me try: lo-first, sum = `(lo + (sh16 >> 16))`. The order might become: srl (lo), sra (hi), addu. Still srl first.

What if the lo expression is moved *after* the hi shift textually but assigned to the named lo via a comma... s1 (7).

I'll accept. Let me record the WALL now after a couple more tries to hit 20 min. Let me also verify the score on a few other includers for the best body (p2) — just to see if the residual is consistent (interesting for the log). Actually, for a WALL, best = 5.

Let me do 2 more batches and then finalize.
