---
ts: 2026-10-17T18:48:33.486Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: aed641f299013cd69
model: claude-opus-5-5[1m]
effort: medium
turnId: a05808f2-3ac4-478a-96ff-4005570aa66e
---
I'm tracing how strength reduction turns the loop's pointer and index variables into induction variables with their own registers, and thinking about what effect the barrier asm inside the loop has on preventing the compiler from hoisting the address computation out of the loop body.

I'm wondering if a volatile asm barrier in the loop affects memory invariants rather than symbolic address constants, which doesn't quite explain things. The bivs s0 and s1 get strength-reduced normally in the target, and most givs are reduced except the call address — same as mine — so the real question is why loop invariant motion didn't hoist the lui/addiu for that symbol in the target version.

Register pressure or n_times_set thresholds in loop.c might be the deciding factor rather than the asm barrier itself. I'm thinking the best path forward is to test C variants empirically, starting with computing the call argument's pointer arithmetic at a different point in the loop.

Still writing loop code...
