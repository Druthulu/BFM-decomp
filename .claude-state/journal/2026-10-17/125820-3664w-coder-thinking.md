---
ts: 2026-10-17T18:58:20.901Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a6ee12ed7d3da1789
model: claude-opus-5-5[1m]
effort: medium
turnId: c73a5082-25b2-49a4-a028-dd1d5ff9dd77
---
I'm thinking about how CSE collapses the stack address computation for `rot` into a single reused register across calls, while the target recomputes the address each time—likely because the compiler treats `rot` and `&rot[0]` as equivalent regardless of how they're spelled, so I need another way to prevent that reuse.

The key insight is that normally gcc puts the frame address directly into a call-clobbered hard register (like a1), so after the call that value is gone and must be recomputed. But if I introduce an intermediate pointer variable assigned to `rot` and reused across multiple calls, that creates a pseudo register holding the stack address which CSE happily reuses across calls instead of recomputing it—so the fix is to avoid the intermediate variable and pass `rot` directly to each call.
