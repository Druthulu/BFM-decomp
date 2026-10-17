---
ts: 2026-10-17T13:42:48.483Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a91f36121b5043b6a
model: claude-opus-5-5[1m]
effort: medium
turnId: 2eee350e-3a84-4d56-9c95-e752be0f81a2
---
I'm tracing through the register move sequence, trying to figure out why t1 ends up in v0 rather than v1 - it seems the global register allocator assigns v0 to t1 since it doesn't span any call boundary, which matters if v0, v1, a0-a3, and t0-t9 are all simultaneously live.

Could this be driven by hard-register preferences from copy instructions during global allocation? I'm considering whether a copy like `$16 = t1` biases allocation toward s0, and whether allocation order between t and t1 determines which gets the preference - looking at how GCC's global.c handles hard_reg_preferences and set_preference when one operand is already a hard register.

But t1 crosses basic block boundaries due to the branch, so local-alloc's tying of copies within a block wouldn't apply here. I'm now wondering if there's a way to tie t and t1 together directly so the preference transfers regardless of allocation order.

Maybe the cleanest route is to just rewrite the computation explicitly in C, avoiding any clever register tricks, by computing the remainder directly and letting the compiler pick whatever registers it wants.

I'm not certain of the exact instruction ordering here, so I should try out a few variants (c1, c2, c3) testing whether the branch checks t or r directly and where the move into s0 falls relative to the bgez.
