---
ts: 2026-10-17T16:52:10.213Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: ac33bcc12f95b099e
model: claude-opus-5-5[1m]
effort: medium
turnId: 642fce30-a585-4106-9bf9-735136648dff
usage: {input: 8, cacheRead: 310278, cacheWrite: 4892, output: 1680}
---

None of those quite: each coder gets a batch of about 8 functions and keeps its context for the whole batch. The 30-minute limit applies per function, not per coder. When one function hits the limit, the coder records its wall and moves on to the next, and it's retired only when its batch is done.

**How T11 groups the work.** Not by kind. The expert sorted the 396 functions by size and dealt them out in turn across 50 batches, so a pin, a launder and a barrier can all land in the same batch.

**Exemplar and propagate.** We did do that, in T9. It cracked one example from each of the 38 lever classes that repeat across many functions, and its fix covered every copy. What's left for T11 are the singletons: functions whose lever text appears nowhere else. So there is no exact solution to copy. That's why T11 cracks them one at a time.

**Your warm-context idea is still right.** Singletons of the same kind tend to fall to the same few moves. In T10, about half the wins came from two tricks:
- reusing a variable or a block-local to steer the compiler's choices (6 wins);
- putting a store in each branch of an if, instead of using a barrier (4 wins).

A coder that has just cracked three barriers with the second trick will crack a fourth barrier faster than a new coder would. Grouping functions from the same source file helps as well, because the coder has already read that file's types and headers.

The cost is modest. A coder's context grows with each function, but the re-read part is cached and costs about a tenth of fresh input. So 8 to 12 related functions per coder is a good range. Much longer than that, and old notes start to crowd out the current function.

**My recommendation.** Have T11's expert re-deal the 43 batches nobody has started yet. Each batch would hold one lever kind, and functions from the same file where possible. Every coder would also add the moves that worked to one shared notes file, which the next coder reads first. That spreads what's learned across coders, not just within one. The 7 batches already running carry on unchanged, so nothing is lost.

It doesn't change the cap or the milestone, only how T11 deals its work. Pick an option in the picker.
