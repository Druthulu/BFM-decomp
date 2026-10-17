---
ts: 2026-10-17T16:49:22.101Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: ab7c1b2050f875aa7
model: claude-opus-5-5[1m]
effort: medium
turnId: e9067380-d3b2-4c4e-97d8-f140a92e4fcf
---
The simple regex won't catch K&R style function definitions since there are parameter declarations between the parens and the brace. I need to write my own extractor that finds function names at line start, then scans forward to find the first opening brace after it.
