---
ts: 2026-10-17T08:51:40.395Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: ad689c37ea88bcff0
model: claude-opus-5-5[1m]
effort: medium
turnId: f24e09ce-98d5-45d3-8db8-69a0d3469b71
---
I'm drafting func_8001E378, tracing how it calls func_8004978C with the matrix argument at sp+48, where the rotation matrix occupies the first 18 bytes and the translation vector sits at offset 20 within that structure.

I'm working through the sequence of matrix operations: setting the rotation matrix from `sc`, transferring column vectors through rtir into `res`, then copying the result back through SetRotMatrix/SetTransMatrix on the global matrix `g`, and finally loading/storing the translation portion at `res+20`. I'm noting that the compiler CSE'd some address calculations (reusing a0 and v1 across blocks), which tells me how to structure the decompiled C using s16 arrays consistent with the sibling function's pattern.
