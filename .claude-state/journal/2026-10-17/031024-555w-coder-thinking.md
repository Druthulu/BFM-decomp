---
ts: 2026-10-17T09:10:24.660Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: ad689c37ea88bcff0
model: claude-opus-5-5[1m]
effort: medium
turnId: f24e09ce-98d5-45d3-8db8-69a0d3469b71
---
I'm reconsidering func_80020F34 more carefully, since it's hand-written and differs from the others in 800.c: three GPF passes, no frame, and a load scheduled between the GPF and mfc2 of results. I'm questioning whether gcc 2.7's scheduler could actually move an ordinary C load across the asm volatile boundary like that.

In older gcc, asm volatile acts like a scheduling barrier that flushes pending memory and register dependencies, so the loads and mtc2/mfc2 sequence are more likely fixed macro patterns than scheduler-reordered code. I'm recognizing the register pattern—t0-t3 feeding mtc2 $8-$11, and mfc2 $12-$14 feeding sh stores—as matching known PsyQ GTE macros like gte_ldclmv and gte_stclmv rather than arbitrary compiler output.

This looks like it could be the PsyQ libgte ScaleMatrix function, where a matrix's columns get multiplied by a vector's components, with the loads for the next column interleaved with the GPF and mfc2 store sequence from the previous one.

My conclusion is this is hand-written assembly: a PsyQ libgte-style leaf function with the next-column loads deliberately scheduled into the GPF latency window, using fixed t0-t6 registers in a discipline that a compiler like gcc wouldn't naturally produce.

Now moving on to examine func_800CBA44 in the overlays (md_MAIN_027).
