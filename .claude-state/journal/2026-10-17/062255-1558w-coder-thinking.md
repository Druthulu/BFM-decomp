---
ts: 2026-10-17T12:22:55.389Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: aa713f978f6769f98
model: claude-opus-5-5[1m]
effort: medium
turnId: 29f80c87-241a-492d-b40b-c42d868c661f
---
I'm tracing a rare fallthrough case where the jump target resolves to a code label, which means the check returns 0 in both branches—unless the epilogue structure changes that outcome.

For MIPS in this GCC version, I'm checking whether the beqz/bnez polarity differs between my output and the target, and tracing through fill_eager_delay_slots to see whether it tries the jump target or the fallthrough first based on branch prediction.
