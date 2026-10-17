---
ts: 2026-10-17T11:46:36.274Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a4daaa68013ad062c
model: claude-opus-5-5[1m]
effort: medium
turnId: 271cef5f-aa35-4bfd-88b6-c572019ec154
---
The pack for 801813B4 doesn't match the class rows, so I'll just use packs as reference and work from the source TU directly for classification, picking an exemplar per class and falling back to source when no pack exists. I'll set up a helper script using delever_search for trial runs against the real TU and match_one for scoring against targets, since those are the required tests.

Let me start simple with db4e4996d215 (8018084C) and a88fd15989e7 (80180200), which score 1 with a missing `move v0,s0` -- I need to read body_tree.c and body_free.c for 80180200.
