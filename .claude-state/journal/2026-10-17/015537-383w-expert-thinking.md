---
ts: 2026-10-17T07:55:37.340Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: ab69a93f9cd77e107
model: claude-opus-5-5[1m]
effort: medium
turnId: 7bef1fd5-5435-4f74-83eb-9c1fc618b386
---
I realize rows are keyed by (file, func, kind), and since the writer preserves unmatched rows with their existing cause, I need to drop the 80182334 pin row from the config input so the residue gets reclassified fresh rather than retaining its old cause.

My plan is to build a modified residue input file that excludes both that pin row and the stale 80038308 row, then run the strict check with the new residue input and write a fresh residue output before moving on to instrumentation.
