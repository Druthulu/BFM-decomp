---
ts: 2026-10-17T16:41:01.650Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a26a2e7a9927b54ee
model: claude-opus-5-5[1m]
effort: medium
turnId: 253b27e4-07a4-41f7-b188-1141b6e4bbf5
---
I'm tracing how the return value pseudo gets tied to register v0 versus a1, checking whether global allocation would naturally assign v0 to it if there's no conflicting use, especially for the void-function case.

Since local-alloc runs before global-alloc, it grabs v0 for the block-local temps first, leaving the call-value pseudo without v0 unless pinned somehow. Rather than fight allocation order, I'll just test the PARTIAL approach: c2 plus the else branch setting v0 to NULL plus a keepalive asm.
