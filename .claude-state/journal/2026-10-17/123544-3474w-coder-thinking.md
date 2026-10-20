---
ts: 2026-10-17T18:35:44.274Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a6ee12ed7d3da1789
model: claude-opus-5-5[1m]
effort: medium
turnId: c73a5082-25b2-49a4-a028-dd1d5ff9dd77
---
I'm puzzled why that constant load into register 19 got scheduled after the call, since sched1 normally doesn't move instructions across call boundaries and there's no loop here to explain the reordering.

Rather than keep guessing why gcc did this, I'll just try a few concrete variants: moving the s3 assignment earlier in the source, giving s3 a pointer type instead, or inlining it directly into the final expression.
