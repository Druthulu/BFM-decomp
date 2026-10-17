---
ts: 2026-10-17T11:17:36.510Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a7979eba5885c3edf
model: claude-opus-5-5[1m]
effort: medium
turnId: 921e828f-1fac-424f-94a0-d040638a6158
---
I'm realizing the fill only applies to non-jump targets, so for jump 17 the delay slot filling must've happened via the eager delay-slot filling logic, picking the fallthrough thread's instruction since the branch prediction favored that path.

Then I'm trying to trace why fill_simple didn't pick up an earlier independent instruction (the base address setup) for jump 17's slot in this case, versus the other example where it apparently did get filled from before.

In a2's eager path, I'm realizing fill_simple should fill jump 23's delay slot from v0=0 before it, making it a SEQUENCE — and then steal_delay_list_from_fallthrough lets jump 17 steal that same v0=0 insn into its own slot, since it's dead on the taken path but executed on both. That matches the invert-to-93 relaxation I'm looking for, while in the cal case the fallthrough thread starts with an asm volatile that blocks this stealing.

For plain C I'm now wondering whether the real difference is prediction order: if mostly_true_jump predicts 17 as taken, eager fills from the target thread (move a0,s0) first, which would prevent the fallthrough-steal path from ever happening, so I need to check how mostly_true_jump reads the branch condition here.
