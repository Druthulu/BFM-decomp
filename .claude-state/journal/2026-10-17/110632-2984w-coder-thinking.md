---
ts: 2026-10-17T17:06:32.267Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: acf1e900976d98019
model: claude-opus-5-5[1m]
effort: medium
turnId: 82d9c87a-028e-4c83-b14d-9d07f43471e2
---
I'm checking whether the load of 'a' must happen before the store since the scheduler won't hoist loads over potentially aliasing stores, meaning the source order must have 'a' loaded first, followed by the store, matching the register allocation pattern I'm seeing.

I'm trying to figure out why in variant f, 'a' gets v1 and 'b' gets a0, versus in variant g where the allocation flips — likely coming down to local allocation priority rules, where constants get highest allocation priority and the order in which 'a' and 'b' are born determines which hard register each grabs first.

I'm digging into gcc's local-alloc priority formula, which weights quantities by number of references, size, and loop depth divided by live-range length. To make 'a' allocate before 'b' in variant g despite 'a' living longer, I'd need 'a' to accumulate more references somehow, since more refs raise its priority score in that calculation.

I'm also considering whether 'b' ends up with register v1 because of a suggested-register copy relationship with a hard register, similar to how a parameter pseudo gets allocated — checking if that mechanism could explain the difference between the two orderings.

Maybe D_801F6CA8 and D_801F6CAC are actually adjacent elements of an array rather than separate statics, which would change how they're being iterated over.

Maybe b gets priority if a's register got reused for const3 instead. I'm thinking about making b's live range outlast a's by reordering the stores, but the target loads a first, and local-alloc runs after sched1 in this gcc version, so register scheduling isn't that flexible here.

Rechecking rest_of_compilation ordering, sched1 does run before local-alloc, so birth/death luids reflect post-scheduling order. In the final instruction order, a's life span comes out longer than b's — 6 versus 3 — so b would win the register, unless a is actually treated as a global quantity rather than a local one, which changes which allocation pass handles it.

I'm considering whether b ties with a's quantity because of how the parameter pseudo for b gets initialized at function entry — if it's a copy from the hard register at the first insn, it could be long-lived, but local-alloc only treats a pseudo with multiple sets as a single quantity if it stays within one basic block.

Given my time budget across this many cases, I should check the RTL dumps directly rather than keep guessing, trying cheap hypotheses like a declared as a different type or b being a reused cast of the parameter.
