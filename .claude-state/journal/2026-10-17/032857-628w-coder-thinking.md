---
ts: 2026-10-17T09:28:57.676Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: ab0fc0b10970aee54
model: claude-opus-5-5[1m]
effort: medium
turnId: d5f3c548-1279-4293-8954-e6ee5462dd24
---
I'm sketching a scratch judge script that takes a translation unit and line numbers, applies variant-to-canonical replacements on those lines, rebuilds the candidate text, looks up relevant recipes through includers for headers, runs the full judge, restores the original, and prints a verdict—reusing delever's recipe-and-includer logic. I'm also checking argument compatibility for the canonical gte_SetRotTransMatrix_m function.

I need to verify that each macro variant maps cleanly to a canonical with matching signature—gte_rtv0tr_m taking no args matches gte_rtv0tr, gte_ldv0_m(r) matches gte_ldv0(r), gte_rtv0_m() matches gte_rtv0()—and confirm canonical definitions actually exist in the header for gte_SetRotMatrix, gte_ldv0, gte_rtv0, gte_rtv0tr, and gte_SetRotTransMatrix, since one report flagged no single canonical macro for gte_rtv0tr_m's signature even though gte_rtv0tr is present.
