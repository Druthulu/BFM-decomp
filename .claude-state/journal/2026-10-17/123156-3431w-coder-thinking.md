---
ts: 2026-10-17T18:31:56.204Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: aed641f299013cd69
model: claude-opus-5-5[1m]
effort: medium
turnId: a05808f2-3ac4-478a-96ff-4005570aa66e
---
I'm puzzling over why the unk00 store and its address chain seem to get scheduled in their own region — since the barrier appears to force that store plus its load into a separate scheduling block, I'm wondering what C construct could actually cause that split, since a plain label alone wouldn't do it unless it's an actual jump target.

Maybe a loop structure like iterating over a struct array to find a matching entry, followed by a conditional check on the index, creates the needed basic-block boundary at the branch. Or perhaps giving the store a dependent successor — a later load that could alias the same struct field — would raise its scheduling priority, though the other loads in the block reference distinct symbols so that doesn't obviously apply.

I'm also considering whether gcc2's backward scheduler just places the store near the end since it has no dependents, and whether introducing an output dependency through another overlapping store to the same struct field could pull it earlier.

I'm wondering if reordering value computation versus the unk00 assignment matters, but scheduling can still reorder regardless. The real culprit might be how sched1 in this old gcc builds its ready list — scheduling backward from the end of the block, starting with insns that have no dependents, which would explain why the last insn chosen ends up being the one it is.

Rather than fight the scheduler theory, I think I should test concrete source variations directly — maybe reusing the loaded value as a temp variable within the i==0 block, since D_800BA320 is referenced three times there and the head pseudo could be shared across those uses.

I'm also reconsidering the alias logic: if the store weren't marked /s (MEM_IN_STRUCT_P false), true_dependence would assume no aliasing against the /s varying load, which could explain why disambiguation does or doesn't trigger here.

So I'm exploring whether rewriting the store with pointer-cast indexing on a plain s32 array—rather than struct-style symbol+index addressing—would flip MEM_IN_STRUCT_P to 0 while keeping rtx_varies_p true for the address, which matters for getting the right scheduling behavior.
