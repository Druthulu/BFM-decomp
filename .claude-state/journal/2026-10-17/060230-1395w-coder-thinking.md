---
ts: 2026-10-17T12:02:30.800Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a4daaa68013ad062c
model: claude-opus-5-5[1m]
effort: medium
turnId: 271cef5f-aa35-4bfd-88b6-c572019ec154
---
I'm tracing how the loaded value moves between the local pseudo-register and the global one, noticing that in the free-compiled version the copy got optimized away so the load writes directly into the global variable instead of going through the temporary first.

I'm wondering if this is tied to how gcc 2.7.2 handles REG_EQUIV for pseudos loaded once from a fixed memory address, versus the load actually coming from a function return value elsewhere. Might be worth checking the cookbook catalog for a matching idiom tied to this global address or a pool-allocation pattern.
