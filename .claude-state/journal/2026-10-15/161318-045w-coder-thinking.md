---
ts: 2026-10-15T22:13:18.299Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a355e5f4e671b32e5
model: claude-opus-5-5[1m]
effort: medium
turnId: e98fac13-aa90-492f-ab26-6b8eacc10264
---
The census confirms the 95% threshold matches my projection: 6,676 types cover it, leaving 6,066 long-tail types, which checks out against the full 12,742-type count. Now I'm second-guessing whether the census output files I generated should be committed, since the instructions say the tree must stay clean apart from my own files, but these outputs were produced by the task I was asked to run.

I'll check the diff size on docs/struct-map.md, and if it's just reflecting a fresh HEAD-based census, I'll go ahead and commit those outputs as part of the refresh and note that in my summary. Next I'm moving on to writing the selftest cases, inserting them before the fold-keep reference.
