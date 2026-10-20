---
ts: 2026-10-17T17:19:41.791Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: acf1e900976d98019
model: claude-opus-5-5[1m]
effort: medium
turnId: 82d9c87a-028e-4c83-b14d-9d07f43471e2
---
I'm comparing register priorities in Greg's allocation example, checking that pf34 outranks pf20 using the floor_log2(refs)*refs/live priority formula, and starting to compute pf20's priority with 8 refs and a live range of 66.

Testing adjustments: bumping pf34's refs or trimming pf20's refs changes the ratio enough to flip priority, but I'm wary that removing a reference (like the final unk18 store using t18 instead of reloading) would alter the instruction sequence since t18 isn't preserved across the call as a saved register. So I'm now considering instead lengthening pf20's live range to shift the priority balance without changing its reference count.
