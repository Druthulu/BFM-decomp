---
ts: 2026-10-17T15:46:29.174Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: ae6f058bb8615c3ec
model: claude-opus-5-5[1m]
effort: high
turnId: 747feadd-bdf1-4a7e-b93c-524c55511a38
---
I'll spawn two retrievers, starting with one examining the residue mechanics in lever_census.py—how residue is parsed, strict_failures, the unused-residue check, how writer residue_text and cause classes work, whether --write-residue preserves existing pass/instrument/cause data, and what the current distribution of cause classes and instruments looks like in lever_residue.tsv.

A second retriever should trace the cast-gate leftovers (func_80026514, func_800268D0, func_800CBA44 and their K&R-empty declarations), how type_census detects lying, the state of lying_exceptions.tsv, and the unbacked CAST_NONSTRUCT macro reporting—while leaving any log-reading to retriever-digest since logs are off-limits for retriever-code. I also want a third retriever-digest pass over tasks T7–T10 plus the T10 log, tracking how survivor rows' instrument/cause fields evolved and which rows got re-judged this phase versus earlier.

Now I should combine the lying-decl details from the code retriever with the CAST_NONSTRUCT identity the digest retriever pulls from T8/T10 logs, and T11 can wait since it's just starting. Time to write up the briefs.
