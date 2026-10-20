---
ts: 2026-10-17T18:21:09.925Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: abe44831ff24b6c2f
model: claude-opus-5-5[1m]
effort: medium
turnId: 38414235-3946-4014-b22c-6e9e31b9cd68
---
I should write the approach note first, then work through the items, all of which are barrier-kind. Let me check the T10 worked example to see what a barrier looks like, and look for an extraction tool to pull the function definition from the source for each.

I'll go through each of the 11 barrier-kind items by copying its source definition to orig.c, identifying what ordering it enforces, and applying real-C rewrite patterns (per-arm stores, goto-based loops, plain casts, || folding, member de-casting) that already worked on similar barriers elsewhere, scoring each attempt with dt.sh and tagging failures by their pass mechanism.
