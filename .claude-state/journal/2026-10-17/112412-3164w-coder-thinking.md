---
ts: 2026-10-17T17:24:12.858Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: ab7c1b2050f875aa7
model: claude-opus-5-5[1m]
effort: medium
turnId: e9067380-d3b2-4c4e-97d8-f140a92e4fcf
---
Since the declaration is void at all call sites, changing the return to s32 counts as a signature change, so I need a flow-unused-result tag instead, keeping it paired with win.c's b7=0.
