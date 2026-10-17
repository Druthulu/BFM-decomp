---
ts: 2026-10-17T05:59:58.352Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a0517ed1d1bb7f9bc
model: claude-opus-5-5[1m]
effort: medium
turnId: f9047d91-6ccc-4e9c-9be7-6616c974f0fb
---
I realize my regex is actually matching plain function call statements too, since the character class allows leading whitespace before the function name. I need to tighten the pattern so it doesn't accidentally catch bare calls like a simple function invocation line.
