---
ts: 2026-10-16T14:58:53.513Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a0bf063322abc80b6
model: claude-opus-5-5[1m]
effort: medium
turnId: d7f5fc8b-b2ef-470d-a0d6-e8199f1f828e
---
Tail sites are frozen at 6,976 while TBB sits at 5,009, likely because only overrides are stamped so far — once md/main/shared get restamped, TBB should climb to match. The check-structs run takes too long so I'll background it, and I'm noticing 7,542 TYPE-NO-MEMBER sites but only 6 rows, meaning restruct is emitting these from elsewhere too. I'm wondering if there's a tool to find defs with zero member bodies, since T2.c4 had to do that manually.

I'll have the coder write a scratch script for this long-running compute job (roughly 45 minutes across batches), running it in background while I write an approach note and brief first. I'm gathering pointers for the coder — restruct_cycle.sh sections, residue_chain.sh, and R3.40-008 — and thinking a script is needed to classify TNC sites by type (band/tail/drift), possibly reusing newtnc.py or seg_cause.py. The rule is: if TBB exceeds 6,976, that's a drifted band type that needs fixing. Now I'm drafting the brief for the coder.

The dry-run shows 628 drawable bodies in md_* and 157 in main, but src/shared/* has none, so I'll run the restruct_cycle sweep on md_*/main as planned while handling shared separately with a serial --headers apply plus the residue/restamp/NO-EDIT chain, pruning zero-body defs first and checking TNC drift only on band types—dispatching this as one batched coder job.
