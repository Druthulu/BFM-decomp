---
ts: 2026-10-17T05:15:38.879Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a7f214c1b8ceabcd8
model: claude-opus-5-5[1m]
effort: medium
turnId: edd2b196-9038-4e7d-9ca7-b103d9ac818f
---
Given the scope of affected binaries, I'll apply all edits first then run an incremental check-all with parallel jobs rather than testing per-binary, since so many share the same headers. Now I'm going through the local per-overlay functions one by one.

I'll convert the three pass-through shared bodies and func_801376E8 to return s32 instead of void, updating their caller declarations accordingly, then verify each per-overlay copy against objdump output and confirm correctness with make check.
