---
ts: 2026-10-17T13:47:18.905Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a715c83225823a44a
model: claude-opus-5-5[1m]
effort: medium
turnId: cb00494e-7b3a-4f28-b3fa-24b3d50bb0ef
---
I notice dumpbody copies the translation unit elsewhere with relative includes, which is causing the issue. I'll fix this by writing my own variant, db2.sh, that uses the include-fixer to produce absolute includes instead.
