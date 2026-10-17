---
ts: 2026-10-17T12:32:19.716Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a7981821383929cc1
model: claude-opus-5-5[1m]
effort: medium
turnId: 6481a00e-d05d-4284-8eb3-bba059849bf7
---
I'm noting that non-constant plain register addresses aren't folded by cse, only (plus reg const) forms get unconditionally folded, which explains why s0 stays unknown until the plus-form store appears in block 1 — so the real question is whether the address only becomes that plus-form shape after cse1 has already run.

Working through the idea that an intermediate pseudo could carry the address: cse would fold its constant-plus source according to cost comparisons (mips rtx_cost treats CONST and PLUS similarly), then combine would substitute that pseudo's rewritten source back into the memory reference, which lines up with how the call-argument rebasing to `addu $5,$16,16` appeared in c0.

Turning to scheduling, I'm trying to figure out whether sched1's knowledge of the base value (via REG_EQUAL) is what let it hoist the loads above the store in c0's output, and whether that REG_EQUAL note could later get stripped if combine folds the base-setting insn into something else -- which would explain why the reordering doesn't trigger on a second pass.

That combine-distributive-law lever idea is excluded. I'm thinking about whether a pointer variable reused for two meaningfully different values could resist folding—but tracing it through, cse would still know the pointer's value at each point and fold both accesses to absolute addresses anyway, so that path doesn't work either.

Now I'm considering whether cse ignorance really requires an EBB boundary or non-constant source, and whether sched ignorance needs no REG_EQUAL note or multiple sets with no loop notes or labels present at schedule time. A base register set twice with both sets live might work, but a simple if/else assigning different constants to base still leaves branches in the code, which doesn't match. I'm also wondering if the original source had a trivial loop like a single-iteration for-loop, since that could leave loop notes behind without actual branching in the final assembly.

I'm checking whether jump.c deletes LOOP_BEG/LOOP_END notes for loops that get optimized away entirely -- specifically whether jump_optimize has logic to strip loop notes once the loop body has been eliminated, which would explain the lack of branches despite a loop in the source.
