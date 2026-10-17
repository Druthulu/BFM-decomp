---
ts: 2026-10-17T10:27:26.916Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: afda95bec87dc8de3
model: claude-opus-5-5[1m]
effort: medium
turnId: 1e35bd3f-abc8-4289-9a6e-6d49268d15f8
---
I'm figuring out the tooling flow: applying the body to an exemplar function, then propagating that change to every residue sibling in the class. I also need to check whether agent packs already exist for the head classes before building new ones.

Now I'm sketching the coder brief design — one crack coder per class capped at four concurrent, scratch-only with no source edits, running permutation attempts with longer durations. I'm weighing whether propagation (which does touch source) should run serially after crack coders finish, since concurrent dirty-tree edits risk reading bodies mid-change.

I'll organize this into waves: four crackers followed by one propagator that banks, propagates, runs R22/TSV checks, and commits, then repeat. Many of the 38 classes are near-duplicate function variants across copies, so a crack on one exemplar might port to its siblings via a port-scan; I should track coder wall-time per wave and check how large existing packs are before writing the actual cracker brief.
