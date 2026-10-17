---
ts: 2026-10-17T11:57:25.194Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a8e969c8cbf9244d6
model: claude-opus-5-5[1m]
effort: medium
turnId: 150f717e-3914-450b-b185-2137b70bb2af
---
I'm trying to trace which priority values get assigned when insn 22 schedules its dependents, checking how insns 15, 18, and 20 propagate priority through their dependency chains since 18 also feeds into insns 34 and 37.

This is taking a while without resolving cleanly — I should just look directly at the launch logic in schedule_insn rather than keep tracing dependency chains by hand, since the timing budget matters here.
