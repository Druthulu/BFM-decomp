---
ts: 2026-10-17T10:31:27.093Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a55474736c80a3baf
model: claude-opus-5-5[1m]
turnId: e20d419a-4489-4243-b756-85abe7c2d13c
---
The goal is to make func_80177B5C compile to a MATCH with no levers (no register pin, no asm, no volatile, no builtins). The only gap left is one `or v0,a1,v0` that lands one slot off, so I'll start Lane 1 (the permuter) in the background and meanwhile hand-test statement-order moves from the pack.
