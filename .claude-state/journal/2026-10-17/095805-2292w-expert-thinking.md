---
ts: 2026-10-17T15:58:05.331Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: ac3c2f25cd86a3f15
model: claude-opus-5-5[1m]
effort: medium
turnId: 8d79bbc0-6d30-411b-a4e2-472ff86f0d65
---
I'm realizing the scorer relies on baseline objects in build/, so a clean during banking would wipe out the reference build crack coders depend on for scoring. I'm also tracing whether swapping function A in a shared translation unit while another coder edits function B in the same file could cause conflicts—seems like it should still compile consistently as long as the rebuild captures both changes correctly, but a clean mid-process could break that.

Given this, bankers likely need to run the gate when crack coders aren't active, perhaps between rounds once all coders finish—costing roughly 10 minutes for the gate plus 25 minutes for banking, adding up over many rounds. I'm weighing an alternative: an incremental rebuild without a full clean, which risks minor read/write races but avoids the idle time, saving the full clean gate for bigger checkpoints like every couple of rounds or at the very end.

I think larger rounds with more functions per coder reduce the number of sync points needed, though staggered finish times still waste time waiting for all four. One option is spawning the next coder immediately when one finishes rather than waiting, running incremental checks continuously and reserving the full clean gate for round barriers or the final verification. I'm also considering whether the scoring baseline could live in a separate snapshot of the build directory instead of requiring a clean rebuild each time.
