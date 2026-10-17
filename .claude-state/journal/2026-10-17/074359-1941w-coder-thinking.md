---
ts: 2026-10-17T13:43:59.130Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a91f36121b5043b6a
model: claude-opus-5-5[1m]
effort: medium
turnId: 2eee350e-3a84-4d56-9c95-e752be0f81a2
---
I'm tracing how register allocation plays out here: m always ends up copied from v0 after the call, but v0 also gets used by the shift computation temporaries, so the ordering of allocation priority between those shift temps and m matters for which register each ends up in.

Since t is pinned to a hard register, local-alloc's combine_regs logic should tie the shift temporaries directly to that hard register when they die into it, which is the behavior I want from the pin. A cleaner way to force this might be to write the shift operations as in-place assignments to t itself — `t >>= 6; t <<= 6;` as separate statements — so no intermediate temps get created at all, avoiding the whole register conflict issue.

I'll rewrite the shift steps as in-place assignments to `t`, eliminating the temp allocations my version was routing through `v0`/`v1`.
