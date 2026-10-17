---
ts: 2026-10-17T15:55:22.857Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: ac3c2f25cd86a3f15
model: claude-opus-5-5[1m]
effort: medium
turnId: 1e24caa4-da16-47fc-bf5f-4d2783fa9592
---
I'm counting roughly 435 file/function pairs, needing to exclude the 27 instruction rows and the func_80188C04 family of 11 functions to land near the planned 430. I'm also wondering whether the 8 pilot survivors from the earlier 20-function test are still sitting in the TSV, so I'll wait for the retriever results before finalizing scale estimates.

At 20-30 minutes per function with 4 coders, that's roughly 35-50 hours of work, but the plan only budgets 14 hours — so coders must be batching multiple functions each rather than working strictly sequentially. I'm thinking batches of 6-8 functions per coder to stay within context limits, with each coder's report kept terse so my own context can hold ~60 coder runs' worth of output.

The trickier design question is concurrency: with singletons having only one copy, cracks get applied directly to src, but running `make check` per binary across 4 parallel coders editing the same build tree risks collisions — I suspect T10 already solved this, so I'll hold off on designing it myself and wait for the retriever before drafting the actual work list.
