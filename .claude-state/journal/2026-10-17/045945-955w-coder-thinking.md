---
ts: 2026-10-17T10:59:45.938Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a55474736c80a3baf
model: claude-opus-5-5[1m]
effort: medium
turnId: e20d419a-4489-4243-b756-85abe7c2d13c
---
I should jot down my attempts so far in notes.md while continuing to brainstorm. One idea is making x1 depend on a load so its definitions get priority 2 in the x1or structure, and I'm examining whether the K&R-style s16 parameter gets sign-extended in the callee—looking at the target code, there's no sext of a3, just a direct addiu using a3.

I'm checking whether x1's definitions could float to the top of the ready list by LUID ordering, placing them above other priority-2 instructions, but that would change register allocation for x1 across its long live range, which doesn't match what we're seeing. I'm also considering reordering the source so the c-chain comes before w, or making the store to p[2] not directly dependent, trying to find a configuration that reproduces the target scheduling.

What catches my attention now is the idea that w could have a second consumer beyond the store — if that consumer sits above the chain but gets deleted later (say, by reload turning a same-register copy into a no-op), it could explain why the or lands exactly where we need it, directly above the chain rather than above the store.

But this runs into trouble: cse would still fold w into the store directly, and the copy insn itself would just get scheduled adjacent to w's definition anyway, so nothing actually moves the or higher. I need the chain insns to become ready only once the store is scheduled, meaning the store would have to depend on the chain's output — but the chain's result feeds other ori operations, not p[2], so that link doesn't naturally exist unless something else ties them together.

Trying another angle: what if the store reads the same pseudo w that the chain also assigns, creating an anti-dependence? But then w would be set twice and die twice, forcing it into global allocation instead of staying local — which breaks the scheduling trick I'm after.

I'm also checking the store-to-memory relation: the chain insns don't touch memory at all, so the store can't anti-depend on them that way. It seems within plain sched1 semantics this scenario is impossible unless reg_n_sets exceeds one, or birthing_insn_p fails because the destination isn't live at that point in the backward liveness scan.

Checking whether the SET lives inside a PARALLEL doesn't change anything—a CLOBBER element isn't a SET, but the actual SET element still counts as birthing. Nor does it help if the destination is a subreg, a wider integer type, or a hard register variable, since register variables are pinned and forbidden anyway. So it really does come down to reg_n_sets[w] needing to be greater than one.

I'm now wondering whether reg_n_sets, computed during flow's life analysis, stays accurate through combine—combine deletes insns and merges them, but I'm not sure it updates reg_n_sets afterward, so scheduling might be working with stale counts.

I'll write up the notes while the permuter runs, then check whether combine leaves reg_n_sets stale—if it deletes a set after flow counted it, sched1 could still see two sets.
