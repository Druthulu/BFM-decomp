---
ts: 2026-10-17T10:46:13.515Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: affd4bdd851658ceb
model: claude-opus-5-5[1m]
effort: medium
turnId: 3036a8ad-ba82-454c-8ac7-51f507a74f6e
---
I'm checking birthing_insn_p's logic—it boosts launch priority for dead stores where the destination register is live but only set once, which explains why dead-end stores float to the front of the block. This seems to distinguish the base set (boosted since n_sets==1) from f2's case where n_sets==2 keeps it unboosted, and I'm now considering whether the hard register argument sets (a0/a1) factor into this differently, since moving a0 first in block 1 of the target seems tied to this ordering.

Trying to reconcile f2's actual instruction order—la base, then the dead store, then move a0—with the target's order where move a0 comes first and the store floats after la rather than to the very front. I'm wondering if la and the block's top aren't actually in the same scheduling region, which would explain the discrepancy, so I want to trace through f2's sched1 output for block 1 step by step.

C0052 reveals register-defining insns with `reg_n_sets==1` get LAUNCH_PRIORITY, and dead-end stores float to block fronts — likely explaining the block-1 and block-3 residue. I'll now check f2's sched1 order for block 1.
