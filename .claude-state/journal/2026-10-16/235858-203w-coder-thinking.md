---
ts: 2026-10-17T05:58:58.798Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a0517ed1d1bb7f9bc
model: claude-opus-5-5[1m]
effort: medium
turnId: f9047d91-6ccc-4e9c-9be7-6616c974f0fb
---
For overlay names, I need to filter callers by binary—matching callers within a given overlay to functions at that overlay's address. Since overlay source directories map to build object paths, I can identify callers by checking which cache files correspond to that overlay's build directory, keeping in mind some source directories build into multiple binaries.

Now I'm assembling the results into a table, listing each row with its register and a summary of the calling context, computed from the READ-type reclassification entries.
