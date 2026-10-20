---
ts: 2026-10-17T18:47:30.149Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a6ee12ed7d3da1789
model: claude-opus-5-5[1m]
effort: medium
turnId: c73a5082-25b2-49a4-a028-dd1d5ff9dd77
---
I'm tracing how the pinned register gets copied without a value laundering step, which causes combine to merge the set and copy into one instruction and free up the register unexpectedly. To preserve the original pseudo, I need to check whether that hard register gets another use later in the loop, so I'm checking the earlier grep results for its usage.

Looking at MIPS's register class behavior, since it doesn't use small register classes, combine freely merges the set and copy. I'm considering that the delay-slot filling from the loop body (fallthrough) is what's actually moving this copy instruction into that position after the branch.

So I'm restructuring the source: pi should be declared and computed before the if-check, but the puVar9 assignment needs to move inside the if block, right before the do-loop, so combine can't merge it across the branch boundary. I'm editing the block structure to shift where puVar9 gets assigned relative to the conditional.
