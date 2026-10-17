---
ts: 2026-10-17T16:15:15.855Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a7f42f9bd4d9f47ca
model: claude-opus-5-5[1m]
effort: medium
turnId: 1d9764d9-f745-4839-857f-1b214f31db78
---
I'm wondering if the register preference for r98 traces back to how r74 is reused earlier in the multiplication chain—maybe splitting that variable into a separate copy would resolve the conflict with v1 versus v0.

I keep circling the block-2 tie between the adjacent local value and the field value, trying to figure out why fld wins in the target. It's possible the shift result isn't local in the real code, or the scheduling order differs enough that the register allocator's priority flips, so I want to compare the luid ordering and birth points in the sched1 dump against the "vo" variant to see where sra actually gets scheduled.

I recall gcc 2.7.2's scheduler bumps the priority of "birthing" instructions so they're placed later relative to their use, which means during backward scheduling they get picked earlier. In the vo ordering, both sra and lhu are birthing insns while a0 (a hard register) isn't, so a0 ends up scheduled earliest and sra latest — I'm trying to see if that same birthing-priority logic explains the ordering difference in A1.

Let me try another angle: avoid crossing the call boundary with the field read, and instead restructure the post block directly, writing the store as `A->unkA = A->unk60 - adj;` right after computing adj, then following with the call result assignment separately.
