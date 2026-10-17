---
ts: 2026-10-17T10:36:26.595Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a55474736c80a3baf
model: claude-opus-5-5[1m]
effort: medium
turnId: e20d419a-4489-4243-b756-85abe7c2d13c
---
I'm working through how launch priority interacts with ties - launched instructions get bumped to max priority, but when multiple instructions share that max priority, the scheduler breaks ties using LUID ordering, picking from the end of the sorted ready array.

So the real question is why the c-chain instructions get scheduled before the or in backward order: if they're also at max priority and have higher LUIDs because they appear later in the original source order, backward scheduling would naturally select them first, placing them after the or in final output.

Since c is multiply-set in the original free body (assigned, then OR'd in-place), it isn't single-set, so I'm thinking I need to restructure that region into separate single-set temporaries to test scheduling variants, mirroring the pattern where w, c, and cl are computed before being stored into p[2] and p[3].

I'm sketching a few variants: computing cl as a single combined expression placed after w, trying it before w instead, and swapping which values feed into the p[2] store directly — basically probing different orderings to see how the scheduler reshuffles instructions relative to the observed sequence of shifts, ORs, and stores.

Now I'm wondering about reg_n_sets counting — whether a dead reassignment of a parameter pseudo gets counted since the incoming parameter copy itself is a set, meaning reusing an already-dead parameter variable as w could hit n_sets=2 without introducing a fresh dead store. I'm checking which parameters (p, bits, tbli) are actually dead by that point in the loop so one could be repurposed this way.

Since entry and this use happen in the same basic block before the loop, bits could be treated as local, which might shift how the allocator assigns registers. Worth testing this reuse directly to see if it changes the output.

I confirmed in sched.c that `adjust_priority` triggers `or` scheduling only when a register has exactly one set, since REG_DEAD notes are gone by then. I'll test giving the pseudo a second set by reusing a dead parameter (e.g. `bits = c0 | x1; p[2] = bits;`), starting with that variant.
