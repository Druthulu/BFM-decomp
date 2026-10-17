---
ts: 2026-10-17T11:50:12.648Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a9b75b3e3c01d6fa8
model: claude-opus-5-5[1m]
effort: medium
turnId: 9b80ef94-0ae1-44c6-acfd-ddecb9279a50
---
I'm comparing how the -160 constant gets loaded differently across the sched, target, and free variants—tracing whether the compiler reuses a single register load for both stores or re-emits the immediate each time.

Let me try a few placement variants: moving c1 before the unk1C block, declaring it as s16, placing it at the very top of the function, or loading unk1C into a local byte variable first.

I found that pinning causes the `-160` constant to get its register allocated early (v1) rather than late (v0, unpinned). I'll test earlier placements of `c1 = -0xA0` along with a narrower type.
