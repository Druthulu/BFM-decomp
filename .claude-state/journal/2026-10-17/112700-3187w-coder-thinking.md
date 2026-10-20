---
ts: 2026-10-17T17:27:00.206Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: af409a99e99c8a1de
model: claude-opus-5-5[1m]
effort: medium
turnId: c8240978-1a00-4d67-b18c-1013d63f9b42
---
I'm noticing scheduler 1 reordered the return-value set past the v computations, so I need to figure out how to make the return expression depend on the store (or share a value with it) so it stays scheduled after, without introducing extra instructions.

I'm digging into sched1's tie-breaking logic for ready insns with equal priority — it seems to fall back on LUID ordering when scheduling in reverse, which would determine whether the store or the return-value set gets placed last in the block.

This dependency-group reasoning is getting too speculative—maybe it's better to just empirically test reordering the statements in the block and compare the resulting schedule dump against the original to see what actually happens.
