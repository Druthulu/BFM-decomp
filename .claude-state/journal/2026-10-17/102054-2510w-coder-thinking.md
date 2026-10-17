---
ts: 2026-10-17T16:20:54.468Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: ac899e71a72e1a646
model: claude-opus-5-5[1m]
effort: medium
turnId: 7b755c42-d9e9-446c-8f08-faa68444d116
---
I'm comparing why the array base address gets hoisted differently in my version versus the target: in mine the symbol gets treated as loop-invariant and split into its own register, while in the original the pointer's addressing forms the symbol plus register offset together instead of separating them out.

I'm wondering whether loop.c only hoists invariants that execute unconditionally on every iteration, since both branches here return anyway. Comparing the pinned-register version against mine, the address computation differs in whether the symbol gets folded into the load versus kept as a separate add, which might come down to loop's register-pressure heuristics when hard registers are pinned.

I'm digging into loop.c's movement condition, which weighs savings times lifetime against insn_count — so if the loop body has more instructions overall, hoisting gets suppressed. That means I could block the hoist either by bloating the loop's instruction count or by shrinking the invariant's lifetime, which is just the distance between where the symbol gets loaded into a register and where it's used.

I'm wondering if forcing the symbol addition into the memory address expansion itself, rather than as a separate computation, changes things — comparing how the `q` case computes its shifted index once and reuses it across two loads, versus the CE0 case where the index comes from a different shift. I want to test a few address expression variants for the CE0 load to see which one avoids the hoist.
