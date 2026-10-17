---
ts: 2026-10-17T16:45:45.210Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a26a2e7a9927b54ee
model: claude-opus-5-5[1m]
effort: medium
turnId: 253b27e4-07a4-41f7-b188-1141b6e4bbf5
---
I'm checking whether the loads after the stores in the tail block would get hoisted by the scheduler without a barrier, since the stores write to offsets on s0 that overlap with the later loads — this is exactly the kind of true dependence gcc 2.7's scheduler needs to respect.

Forcing that dependence to appear without adding a new "lever" is tricky — a volatile cast would do it but feels disallowed. I'm now wondering if the pin vs barrier results (8 vs 9 instructions) point to the s1/s2 register allocation order as the real lever, so I want to try varying declaration order or loop indexing style while keeping the barrier to isolate the pinning issue.
