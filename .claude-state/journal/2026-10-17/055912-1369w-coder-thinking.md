---
ts: 2026-10-17T11:59:12.671Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a8e969c8cbf9244d6
model: claude-opus-5-5[1m]
effort: medium
turnId: 150f717e-3914-450b-b185-2137b70bb2af
---
I'm comparing register allocations between source and target for b and pb0, noting that pb0 has the longest live range so local-alloc deprioritizes it, assigning it to t1 later in the process.

If b is a single pseudo spanning all three rows, its priority drops since its lifetime is long, while splitting b per row would give it a shorter life and higher priority. I want to check the actual local-alloc priority table for g1 to confirm which register pb0 and b end up with.
