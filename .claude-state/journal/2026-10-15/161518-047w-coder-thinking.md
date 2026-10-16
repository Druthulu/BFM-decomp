---
ts: 2026-10-15T22:15:18.185Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a355e5f4e671b32e5
model: claude-opus-5-5[1m]
effort: medium
turnId: e98fac13-aa90-492f-ab26-6b8eacc10264
---
I'm checking why zero folds showed up for E1 - it seems plausible since T2's lineage fold already existed, and TNC sites with canonical base types would have already been restamped by the residue_cause lookup against the latest bases.

I should write a quick scratch diagnostic to count TNC sites that have any MEMBER entry on the same base regardless of type, to confirm this. I also want to check E2's coverage: how many band types have globals_at, how many of those have found declarations, and how many are canonical-typed — another scratch script to verify.
