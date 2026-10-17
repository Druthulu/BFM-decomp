---
ts: 2026-10-17T15:50:08.780Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: ae6f058bb8615c3ec
model: claude-opus-5-5[1m]
effort: high
turnId: 8006c97b-6a60-4f7b-9d5b-7accf0cbe0ec
---
I'm noticing a discrepancy between the 384 missing-parameter sites and the 255 rows in the TSV, and trying to reconcile the instrument refusal count with the 16 distinct instruments actually listed.

Actually, I think the T7 refusal naming didn't land in the output since --write-residue keeps rows verbatim. The real cause seems to be a scratch-register pin tied to local-alloc register choice, not a missing-parameter issue, so I should reclassify it under that wall instead. The head-class residue spans 607 rows across 20 classes with walls derived from the T9 log, and the gate stays red regardless given the head-class, missing-param, and asm-macro/asm-body counts.

For the two pending research reports plus the unwritten cast-gate one, I can't just write a new report body since that's forbidden — instead I'll note in the task that no report covers it and the retriever findings are inlined directly into Interfaces, which the rule permits. Running adopt now.
