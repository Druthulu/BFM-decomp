---
ts: 2026-10-17T12:48:41.448Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a7981821383929cc1
model: claude-opus-5-5[1m]
effort: medium
turnId: 6481a00e-d05d-4284-8eb3-bba059849bf7
---
I'm noticing that f2 writes blocks 1-3 using constant-spelled addresses directly rather than base-register offsets like o1 does, which suggests cse rebased those constant addresses onto register 75 rather than folding them to absolute form.

In contrast, cse2 in f2 actually converts constant addresses into reg-plus-offset form when the base register already holds a related symbolic value, which is the opposite direction from what happened in t1. This points toward the anchor register idea — in c0 the anchor was the sym register from the first call's argument, with blocks 2 and 3 mostly using absolute addressing except where that anchor register gets reused.

Since constant addresses shouldn't get replaced, something else must be rewriting them to (plus 75 k) — I should check the f2 cse1 dump for one of the block 2 stores to see what's actually happening.
