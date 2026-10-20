---
ts: 2026-10-17T17:32:04.132Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: acf1e900976d98019
model: claude-opus-5-5[1m]
effort: medium
turnId: 82d9c87a-028e-4c83-b14d-9d07f43471e2
---
I'm tracing how m24's register allocation gets t1 while conflicting with e1b's t0, checking where in the scheduled instruction order m24 gets born relative to e1b's death at the store.

Thinking through the local-alloc logic: without the hard register pin, e1b and m24 have non-overlapping quantities, so whichever gets allocated first could grab t0 while the other reuses it if free. The pinned version forces m24's set after e1b's store, suggesting the ordering follows luid-based priority where equal-priority instructions with higher luid get scheduled later in backward scheduling — which matches m24's late placement in the source given its high luid.

Priority in backward scheduling is really about longest path length to the block end via predecessor links; since m24's lui has no predecessors, its priority should be low, meaning it'd normally be chosen early, same as e1a/e1b. So for m24 to end up scheduled late in target, something must be forcing a higher priority — maybe a real data dependency, or the way gcc 2.7 splits large 32-bit constants into two insns (high/low) versus a single `li` for smaller constants, which could explain why m24 behaves differently from a one-set birthing insn.

Actually, position gets fixed at selection time: an instruction becomes ready in backward scheduling only once all its uses are scheduled, so m24's ori isn't ready until the and's using it are placed. Once ready, it competes with other low-priority insns by luid tie-break, and since m24's definition sits late in the source (after the ot computation), it has a high luid and gets picked later rather than early.

But the constant 0xFFFFFF is defined in the final block with a late luid, yet in my trace it's placed early—so I'm wondering if CSE merged m24's constant with another lui/ori sharing the same immediate, or if it's tied to the p1 store masking with m24. I need to pause and check the actual sched1 position of m24's sets in free0's output.
