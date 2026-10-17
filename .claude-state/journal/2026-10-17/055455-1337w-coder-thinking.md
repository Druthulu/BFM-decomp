---
ts: 2026-10-17T11:54:55.310Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a4daaa68013ad062c
model: claude-opus-5-5[1m]
effort: medium
turnId: 271cef5f-aa35-4bfd-88b6-c572019ec154
---
I'm testing how the null-check branching affects register allocation, trying variants where the else-branch returns NULL directly versus assigning to a shared pseudo, to see which matches the target's assembly layout for v and a1.

I'm trying other explanations too, like whether v is a trivial reassignment or shares storage with the parameter, but nothing quite accounts for why target allocates v0 to v first while mine gives it a1 — it seems tied to how the local allocator in block 2 claims registers before the global pass runs.

Actually, I think I've found it: the parameter a0 is itself being reused as the pseudo variable. If the original code does something like `a0 = func_801290DC(0x44, a0)`, then a0's pseudo is a global live range (param, alive from function entry) that naturally gets allocated to v0 — the initial `move v0,a0` is just copying the incoming param into its pseudo register, then `a1 = v0` sets up the call argument, and the call's return in v0 directly becomes the updated a0 pseudo. That would explain the whole register pattern. So the structure is likely parameter reuse: `a0` reassigned from the function call result, then an if/else around it (if (a0) {...} else a0 = NULL;) before returning a0.
