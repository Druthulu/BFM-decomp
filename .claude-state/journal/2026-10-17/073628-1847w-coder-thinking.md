---
ts: 2026-10-17T13:36:28.139Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a2ab9a444ea3aa2ca
model: claude-opus-5-5[1m]
effort: medium
turnId: 4fd53509-0294-4563-a878-c510da735377
---
I'm tracing how CSE folds the AND with 0xffff since it already knows flag2 equals an AND with 255, which makes that mask redundant. Now I'm checking whether the zero-register version, which adds the plain register instead of the folded constant, survives CSE unfolded—looking for an expression CSE can't simplify but combine still might.

I'm also considering ways to stop CSE from recognizing flag2 as equivalent to flag, like assigning flag2 through a different type cast or a separate conditional path, so the two ternaries stay distinct rather than collapsing into the same equivalence.

I'm checking whether make_regs_eqv picks the longer-lived register as canonical based on REGNO_LAST_UID, which would mean flag2's uses get rewritten to flag entirely -- unless the copy happens outside the extended basic block where CSE's equivalence tracking doesn't apply, since the ternary's test is a branch and equivalences might not propagate past it.

I'm checking whether argument evaluation order in 2.7 MIPS (right-to-left, with the ternary possibly computed last) explains why flag2=flag appears where it does—maybe it's embedded within the call's argument list itself, placed before later args are evaluated.

Let me think about how cse picks canonical registers more concretely, and whether the gcc 2.7.2 source (cse.c, make_regs_eqv) is available to check directly.
