---
ts: 2026-10-17T09:27:28.900Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: ab0fc0b10970aee54
model: claude-opus-5-5[1m]
effort: medium
turnId: d5f3c548-1279-4293-8954-e6ee5462dd24
---
I notice func_8013AD38 appears across 52 translation units as a copy class, with 9 distinct bodies identified. Given the census shows 91 gte-lever sites across 60 rows per file/func/kind, I should examine the variant calls within each body.

To find these function bodies I need to locate the start of each function and brace-match to extract its full text, then search for gte_*_m variant names. Those variant names should be documented in gte_inline.h near comments marking "gte variant," so I can grep those header comments to build a mapping of variant names to their canonical forms.
