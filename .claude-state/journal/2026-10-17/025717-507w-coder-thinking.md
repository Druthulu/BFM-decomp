---
ts: 2026-10-17T08:57:17.947Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: ad689c37ea88bcff0
model: claude-opus-5-5[1m]
effort: medium
turnId: f24e09ce-98d5-45d3-8db8-69a0d3469b71
---
I'm wondering if that constant address actually points to a persistent variable the loop reads once, rather than something reloaded every iteration — maybe the compiler hoisted the load out of the loop since the value doesn't change.

Checking register usage in the target: s1 only ever shows up in that single lwc2 load, and the ot/otshift pair occupy t9/s0. Since my version's register pressure differs by one (needing an extra temp like t0 for the max comparison), it's plausible the global allocator pushed the constant's pseudo into a callee-saved register like s1 simply because local allocation ran out of temporaries, not because the value itself is special.

I'm now trying to trace how a, b, and c get assigned across the max calculation — in the target, v1/t0/a0 all hold distinct live pseudos simultaneously, suggesting the compiler duplicated the load of c into both branches of the comparison rather than hoisting it once.

Maybe this is actually an array like `long sz[3]` rather than separate variables, which would explain the load ordering differences—target loads t0=8(sp) first, then v1=12(sp). I should try a few variations with the array hypothesis and the "a > b" conditional form to see what matches.
