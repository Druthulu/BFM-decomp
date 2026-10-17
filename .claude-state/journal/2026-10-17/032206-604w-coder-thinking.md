---
ts: 2026-10-17T09:22:06.832Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: ab0fc0b10970aee54
model: claude-opus-5-5[1m]
effort: medium
turnId: d5f3c548-1279-4293-8954-e6ee5462dd24
---
I'm planning a script that textually expands each macro use site, substituting parameters while preserving line-by-line formatting and matching the use site's indentation, so the token stream stays identical to the preprocessor output (line number shifts only affect __LINE__, which doesn't matter here). I'm also considering how to handle the trailing comment marker on each use line.

Now I need to figure out where lever_census expects the `// !FAKE:` marker on each expanded lever — the register asm pins and the `__asm__("")` launder each need their own marker, so I should grep the census code for how it detects "marked" lines before proceeding.
