---
ts: 2026-10-17T17:09:57.274Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: ab7c1b2050f875aa7
model: claude-opus-5-5[1m]
effort: medium
turnId: e9067380-d3b2-4c4e-97d8-f140a92e4fcf
---
I'm working out callee-saved register assignment by priority—q gets s0, r gets s1, sector gets s2, matching the order allocnos are picked for available hard registers.

In my version sector has s0, q has s1, r has s2, meaning sector's priority score comes out highest, which contradicts the target ordering, so I need to check whether sector's priority should actually be lower than q and r's. I'm also noticing a swap between s3 and s4 for j versus another variable, and wondering why i/outer ends up at s7 in both versions, possibly because of low priority or late allocation order. I'm reconsidering the priority formula involving log2 of refs times refs over live range times size, and thinking sector's long live range and many refs versus q's possibly split live regions could explain the discrepancy—I should pull up the actual allocation table for a1 to verify.
