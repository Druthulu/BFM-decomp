---
ts: 2026-10-17T16:32:17.380Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: ac899e71a72e1a646
model: claude-opus-5-5[1m]
effort: medium
turnId: 7b755c42-d9e9-446c-8f08-faa68444d116
---
I'm comparing load ordering between my version and the target: in the source, ang loads before bx/by, but my scheduling puts bx first since ang isn't pinned to a0. I'm wondering if writing the call directly with the arg inline would force ang's load right before the call, though that might actually be worse ordering.

For the addPrim block, I'm noticing the target loads bidx and pv early with the 0xff00 constant computed later, while mine does it in the opposite order. The key question is whether a second set of pv (via the asm block) kills the "birthing boost" priority that sched1 gives to pseudos being defined for the first time, which could explain why the instruction ordering differs.

I should try rewriting pv so it gets a genuine second assignment in real C — load it, mask it, then store the combined value — to see if that legitimately reproduces the two-set pattern and matches the target's scheduling.
