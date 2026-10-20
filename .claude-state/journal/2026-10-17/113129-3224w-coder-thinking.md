---
ts: 2026-10-17T17:31:29.659Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: acf1e900976d98019
model: claude-opus-5-5[1m]
effort: medium
turnId: 82d9c87a-028e-4c83-b14d-9d07f43471e2
---
In backward scheduling, a birthing instruction (one that sets a register still live afterward) gets top priority, so it's scheduled as late as possible — right before its first use, which explains why constants sit just before they're needed. But this boost only applies when the register is set exactly once; if c7840 were assigned twice, that birthing priority wouldn't apply and the const set would instead be ordered earlier by luid.

Trying to force a double-set on c7840 runs into cse, though — if the second assignment writes the same constant value the register already holds, cse would likely collapse it into a no-op and delete it, leaving REG_N_SETS back at 1. I'm also checking whether m24 and e1b follow a similar pattern, since e1b is a pseudo without pin constraints and its set appears very early in the target schedule rather than being boosted.

Lui/ori constant pairs count as two sets, which should prevent boosting — yet m24 ends up placed late in the target while e1a/e1b get placed early, which seems to depend on luid ordering rather than priority since all have double sets. In my version m24 gets hoisted to the top instead, so something in free0 — possibly combine or cse — must be altering how m24's set is scheduled relative to the others.
