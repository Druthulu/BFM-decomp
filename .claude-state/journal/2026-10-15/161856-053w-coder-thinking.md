---
ts: 2026-10-15T22:18:56.923Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a355e5f4e671b32e5
model: claude-opus-5-5[1m]
effort: medium
turnId: e98fac13-aa90-492f-ab26-6b8eacc10264
---
I'm realizing the "final 0/0" condition is essentially unreachable since a nonempty plan always yields N/N with N≥1 — the real zero-work case is T2's run showing 50/50 identical with zero files written, meaning the batch had nothing to draw.

This looks like a premise issue in the brief: the literal "final 0/0" never fires, since an empty plan already exits earlier via the "nothing drawable" path. I need to flag this deviation rather than silently implementing dead code — the actual zero-work signature should be defined as zero files written with zero sites mapping to members, which matches what the repeated T2 batches actually demonstrate.

I worry that a batch with zero compiles could still have ledger rows that settle units and progress the next batch, so exiting early might cut off valid progress — but I'll settle on the minimal, faithful rule: exit when written is 0 and compiles is 0, meaning nothing judged and nothing written, and flag this as a deviation the expert can redirect if wrong rather than guessing further.

I need a concrete test case: a plan set with nothing drawable but a non-empty plan, maybe rS21's set where T2's ONLY applies — I should check the log for that cycle's plan description, or craft a TU whose bodies all land in TNC. Running this needs a clean tree in src/config after committing, and I'm also noting the oracle's calibration is keyed to HEAD, so every commit stales it and the next cycle will need a fresh snapshot-baseline.

Snapshot-baseline might stall if build/ isn't in sync with the tree — worth watching since a batch of 50 S files already took 33 seconds. The proof likely doesn't need CENSUS=0 since exit happens before census runs anyway, so I'll go look for T2's actual rS21 ONLY value by grepping the journal or checking the batch JSON directly.
