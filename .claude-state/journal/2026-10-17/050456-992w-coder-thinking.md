---
ts: 2026-10-17T11:04:56.610Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a5faba3cdb29155cb
model: claude-opus-5-5[1m]
effort: medium
turnId: e4e5bc1c-68a3-4a95-bce5-27c78dfaef1c
---
I'm noticing CSE keeps plain offset-0 register reads since they're cheaper than the symbol form, so it's odd that my `lhu a0,0(a0)` case still got folded — maybe in base.c the entire pointer dereference was eliminated for a different reason, since pd itself seems to have only one use.

Let me check H15_struct.c, which I tried earlier for the struct case, and go back through the first lines of my earlier out_*.txt results to compare scores.
