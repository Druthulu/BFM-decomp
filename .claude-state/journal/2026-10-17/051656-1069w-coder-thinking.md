---
ts: 2026-10-17T11:16:56.607Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a7979eba5885c3edf
model: claude-opus-5-5[1m]
effort: medium
turnId: 921e828f-1fac-424f-94a0-d040638a6158
---
I'm trying to figure out why filling v0=0 into the branch failed at label 26 — maybe v0 is actually live there in the original code, perhaps because the branch condition itself tests v0 rather than some other register.

Tracing through the actual delay-slot filling order: jump insn 17 likely gets filled first, then by the time insn 23 is processed it's already become a SEQUENCE, so the later check in relax_delay_slots sees a different insn type than expected, which would explain the discrepancy in behavior between my case and the working a2 case.
