---
ts: 2026-10-17T08:50:57.382Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: ad689c37ea88bcff0
model: claude-opus-5-5[1m]
effort: medium
turnId: f24e09ce-98d5-45d3-8db8-69a0d3469b71
---
This looks like a PsyQ-style GTE scale matrix function, using fixed t0-t6 registers with interleaved loads before the mfc2 calls to hide GTE latency — likely hand-scheduled assembly rather than naive compiler output, though it could also be compiled from C with careful optimization.

Next, I'll look at func_8001E378, which is 188 instructions long.
