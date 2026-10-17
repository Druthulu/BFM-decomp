---
ts: 2026-10-17T16:50:18.181Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a2da07d641273c840
model: claude-opus-5-5[1m]
effort: medium
turnId: 4fd2d9a2-f2f0-40d5-a2a4-89410462182c
---
That regex approach isn't panning out, so I'm abandoning it. I'm considering whether the volatile store could instead be written through an array access with a variable index that gets constant-folded, rather than a direct pointer dereference.

Actually, trying `||` short-circuit variants and different comparison widths (signed 16-bit, masking) all still forward through CSE identically. Storing a constant instead of a register also doesn't block forwarding, and even restructuring into separate if-blocks for the subtraction and the zero check just gets jump-threaded back into the same CFG as before.

I'm now suspecting the actual mechanism is CSE's jump-following logic itself — tracing how jump 14 gets redirected to label 62 because the condition at jump 30 is already known to be equivalent, which looks like CSE's own jump-threading behavior inside cse_insn rather than a separate optimization pass.

To defeat this, the zero-path simply must not retain knowledge of the pointer's value — so I'm testing whether splitting the two tests onto different expressions (like comparing against a different threshold) breaks the equivalence CSE relies on, or whether inserting a second store through an aliasing pointer invalidates the memory equivalence CSE tracks after the first store.

Then I consider mixing access patterns: storing through `*p` but loading through the direct symbol `D_80115118` — if `p` holds the same address, CSE's equivalence classes might still unify these as the same memory location via REG_EQUAL tracking, meaning the symbolic alias wouldn't actually defeat the optimization.

I also want to check whether `volatile` counts as a lever — I should look at lever_census.py's kind definitions to see what's classified as a launder or barrier.
