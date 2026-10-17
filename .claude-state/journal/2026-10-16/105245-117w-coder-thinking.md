---
ts: 2026-10-16T16:52:45.529Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a6262df0e8a0d472a
model: claude-opus-5-5[1m]
effort: medium
turnId: 7850ba3c-c3b4-45a3-a86f-0ae36df32364
---
I'm noticing that overlays can load at the same address region, which means different overlays might place entirely unrelated routines at that same address — so the "same routine address across binaries" pattern could actually be misleading if it's just coincidental overlay placement rather than a genuinely shared routine.

Looking at the 0x80162834 example though, the body (a function call through a dispatch table indexed by a struct field) matches between SC01 and MAIN_012, and the shared key being cited there is the body-hash key rather than just the address key, which suggests this is a real shared routine rather than a false positive from address coincidence. I want to run a union-find pass over the shared classes to see which key types (body-hash vs address-only) are actually driving the grouping, so I can count real components and figure out which names should be folded together.
