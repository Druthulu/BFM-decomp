---
ts: 2026-10-17T16:16:32.684Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a7f42f9bd4d9f47ca
model: claude-opus-5-5[1m]
effort: medium
turnId: 1d9764d9-f745-4839-857f-1b214f31db78
---
I'm realizing the store to param_1+0x14 forces a reload of arr[0] via `lh a0,16(sp)` since the compiler can't assume aliasing survives the write—whereas my version reused a1 from CSE instead of reloading. Similarly the load of offset 0x10 after the write to 0x14 needs fresh reads rather than cached values, since without a barrier the optimizer would otherwise trust the stale cached arr[0].

I'm wondering if invalidation depends on whether the write address is "varying" versus fixed, so maybe aliasing the array through a pointer variable would make reads register as nonfixed and get invalidated properly — though cse's forward propagation back to sp+16 might undo that fix. I should also consider reading through a differently-typed field access to dodge the aliasing issue.

For the write side, I'm thinking of trying the struct-typed store instead, since store to in_struct memory might trigger different invalidation semantics than a raw cast store — worth just testing a few variants to see which one reproduces the behavior.
