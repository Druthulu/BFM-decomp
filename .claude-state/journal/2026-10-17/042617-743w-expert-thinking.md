---
ts: 2026-10-17T10:26:17.407Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: afda95bec87dc8de3
model: claude-opus-5-5[1m]
effort: medium
turnId: 1e35bd3f-abc8-4289-9a6e-6d49268d15f8
---
With a cap of 4 concurrent crack coders, I'm planning to first run delever_permute on head-class exemplars, checking whether it's keyed by nhash so I can target specific hash prefixes with --only, and I'll do a dry run with --plan first to verify the selection before executing.

Then I need to figure out propagation: a successful match should bank every copy via delever_permute --bank, followed by R22 per batch. Given the scale, I'm thinking of splitting work into phases — I'd handle the compute-heavy permuter plan/run myself (since it's long background compute, not editing), while coders handle the actual edit-build-test loops, manual cracks using the move catalog, and R22 verification. The tricky part is that concurrent coders all touching the same residue TSV and running make clean/R22 simultaneously could collide, so I need to think through how to partition the work to avoid that conflict.

Since the full gate (make clean, extract-all, check-all) can't run concurrently without clashing, crack coders should work in isolated scratch directories using only match_one against extracted asm, which should be safe to run in parallel. A single serial coder would then handle propagation to all copies, batch R22 runs, TSV updates, and commits. I still need to check what match_one actually requires, how many of the 38 classes have prior permuter attempts, and clarify the hash mismatch I noticed — the head-class hash isn't the same as the function's permuter nhash, so I should run delever_permute --plan to clarify.
