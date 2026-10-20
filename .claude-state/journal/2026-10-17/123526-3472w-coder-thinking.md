---
ts: 2026-10-17T18:35:26.050Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a6ee12ed7d3da1789
model: claude-opus-5-5[1m]
effort: medium
turnId: c73a5082-25b2-49a4-a028-dd1d5ff9dd77
---
I'm trying to figure out why the generated code places the lui s3 instruction later, after the call, rather than before it—wondering if the scheduler avoids moving loads across calls, or if a constant propagation/CSE pass is substituting the address differently and affecting where that register gets set.
