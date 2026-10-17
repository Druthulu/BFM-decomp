---
ts: 2026-10-17T10:42:43.253Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: affd4bdd851658ceb
model: claude-opus-5-5[1m]
effort: medium
turnId: 3036a8ad-ba82-454c-8ac7-51f507a74f6e
---
I notice REG_EQUAL applies to the cse even when the set's source is the constant symbol itself, since GET_CODE differs from REG. I'm considering introducing a variable `a` set before the loop, with `base` derived afterward, trying to figure out which register holds which value across the blocks so s0 can correctly carry `a` through the first call and `base` through the later ones.

Combine would need i2's destination to die at i3, but since `a` is still used in block 1, combine can't delete i2 outright — it might keep both sets (adding a redundant second `la`), unless register allocation's copy coalescing ties `a` and `base` to the same hard register and eliminates the redundant copy once `a` dies, producing identical code either way. I think I just need to try it and see which path the compiler actually takes.

Switching tracks, I'm now wondering about cse1 versus cse2 and whether either splits the extended basic block at LOOP_END — since the dump shows block 2/3 using `k(s0)` offsets while block 1 keeps its symbol constants separate (because it's a different symbol, D_800A5E8C, not related to base). This looks consistent with cse's related-value mechanism: when looking up a constant lacking an exact match, cse can find a register holding a related constant and fold `(plus base k)` accordingly, which explains why free.c (without the do-while) ends up folding base+k into actual constants resolved via lui, while h2's version keeps them as register-relative offsets.

Rather than digging deeper into cse internals, I want to just test a candidate: maybe the real source uses h2's structure, but blocks 2/3 access memory through a `base2` variable assigned after the do-while loop (`base2 = base;`), which would explain the different addressing pattern.
