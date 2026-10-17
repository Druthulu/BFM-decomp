---
ts: 2026-10-17T16:10:08.098Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a7f42f9bd4d9f47ca
model: claude-opus-5-5[1m]
effort: medium
turnId: 1d9764d9-f745-4839-857f-1b214f31db78
---
I'm comparing register priorities between r92 and r93 — r93 wins due to its shorter live range, since instruction scheduling (sched1, run before local-alloc with -fschedule-insns) moved the field load earlier, extending r92's lifetime unnecessarily.

Looking more closely, the division expansion creates a temp for the adjusted value before shifting (t = p; if negative, t += 4095; result = t>>12), and this temp is distinct from the shift-result pseudo in the vq case, whereas in target they may collapse into the same register. The original pinned version forces fld to $2, which pushes the shift result pseudo to grab v1 instead of v0 — so I need to figure out why the shift result loses v0 to the field load, likely tied to priority computation based on reference count and live range length.

I'm comparing allocno priorities: the shift's adjusted value has fewer refs but a shorter live range than another pseudo competing for the same register, so for the field load to win the tie, it needs either a lower allocno number or the scheduler to avoid hoisting the load above the shift — meaning the instruction scheduling order within the basic block matters as much as the allocation priority itself.

Global allocation preferences come from copies, and r99 conflicts with v1 since the fld local overlaps its lifetime, creating a circular constraint. I'm wondering if manually expanding the division into explicit shift-and-adjust logic instead of relying on the compiler's div lowering would change the pseudo allocation enough to break that cycle.

Let me check vv's version: score 4, 54 instructions, and see what differs there.
