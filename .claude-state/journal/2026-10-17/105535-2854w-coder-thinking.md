---
ts: 2026-10-17T16:55:35.991Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a6aaa11811b8be773
model: claude-opus-5-5[1m]
effort: medium
turnId: c3153718-defe-4620-a7c2-e0184cae88c0
---
I'm tracing register allocation ordering — the tag load into v1 forces the sw v1,4 store to happen earlier, which explains why the target version uses t2 for the tag constant instead.

I'm checking that the p->tag load doesn't cross any aliasing stores to overlapping byte offsets within the same word, confirming the ordering is safe since all the byte stores target distinct offsets. Now I'm considering whether moving the explicit `val = *(u32*)p` read earlier in the source would reproduce the target's scheduling.
