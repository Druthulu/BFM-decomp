---
ts: 2026-10-17T17:28:39.922Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: acf1e900976d98019
model: claude-opus-5-5[1m]
effort: medium
turnId: 82d9c87a-028e-4c83-b14d-9d07f43471e2
---
This is a large straight-line block with many hoisted constants, and the scheduling difference centers on when m24 (0xFFFFFF) gets materialized — late in the target but early in mine, since my version hoists it to the top of sched1 while the target reuses t0 right after e1b's death.

I'm wondering if pinning the hard register $8 for both m24 and e1b creates an output dependency that forces m24's load to follow e1b's use, whereas without that pin sched1 is free to float the constant load wherever priority dictates. I'm considering whether rewriting m24 as a derived expression (like the bitwise complement of mFF) that cse folds into a constant might force the right ordering, or whether the original source code naturally produced this late placement through some masking operation on the struct field.
