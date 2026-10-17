---
ts: 2026-10-17T10:56:07.206Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: ae39e3e55ca2abfd6
model: claude-opus-5-5[1m]
effort: medium
turnId: 50f5af05-e353-44b9-ba7b-703e4f789154
---
I'm noticing that in the m23_free dump, the separate `d = v` copy has disappeared from the assembly — it looks like CSE or combine merged the computation of v directly into d, since the addu instruction now writes to d instead of v.

So d (r79) ends up global and prefers v0, while e2 (r82) conflicts only with sp and lands in v1. The puzzle is where v went: it seems coalesced into d because v's only remaining uses (the X store and the branch comparison) got rewritten to use d's register directly, suggesting CSE canonicalized the comparison to the older register or combine folded the copy away entirely. To get the target code — v1 and v0 kept distinct with an explicit move — I need v to stay live past the copy so register allocation can't coalesce it with d.

I'm recalling how cse's make_regs_eqv decides which register becomes canonical when merging equivalence classes — it tends to prefer whichever register has the longer lifespan or is tied to global usage, not simply the older one.

For the MIPS case, I'm working through whether the delay-slot move happens before or after the branch logically, since in original RTL the move likely preceded the branch, meaning the branch condition still correctly tests the pre-move register value.

Then I'm considering whether the target pattern is actually just an abs-with-distinct-destination case, where the copy originates from the abs template rather than CSE preferring the longer-lived register. That reframes the m7 global-register issue as needing control flow introduced after the second register's use within the same block.

I'm also wondering whether that second register could be the same pseudo as one of the arguments, or whether the abs result first lands in a local temp before being copied into the global destination, which combine or cse might fold away. I'm trying to figure out which local register could overlap with that temp's lifetime during scheduling while still producing the right code shape.

The scheduling order might differ before final reordering, but checking that constant load case rules it out since the destination still needs that same register. I'm also considering whether the flags value's lifetime could overlap with the other load if the store and load don't actually alias, or whether unchanging/readonly memory semantics apply here.

If arg0 points to a const-qualified struct, GCC 2.7 would mark that load with RTX_UNCHANGING_P, and true_dependence treats unchanging reads as non-conflicting with ordinary stores — which could explain why the scheduler felt free to reorder these accesses.

So CSE wouldn't necessarily merge the two loads since the flags store invalidates the first load's entry before the second (unchanging) load occurs, meaning sched1 no longer needs to force the second load after the flags write, and it gets hoisted since it's a single-set definition.

Looking at the m7 scheduling trace, the second load is already placed late, with its lifetime spanning from near the abs instruction to the end, while the flags value dies right at its store—so I'm wondering if extending the flags' lifetime instead would help, depending on how early the store gets scheduled relative to its dependents.

Reconsidering the problem differently: maybe the real issue is with the destination register d needing to be allocated while another register v is still free, or whether a tie can be avoided based on whether v's lifetime extends past the abs instruction, its death markers, or mode mismatches preventing allocation conflicts.

Checking other avoidance conditions — whether v is a shorter integer type like a HI/short variable instead of a full SI word, which could change register allocation, or whether v might be classified as a global quantity used across multiple blocks that affects whether e2 could reuse a0 while d takes v0, with locals possibly occupying v1 during e2's lifetime.

I'm now tracing whether e2's load could actually be scheduled earlier than the subu/addu computation of v in sched1, since there's no dependency forcing order there -- the flags-setting shift only depends on an earlier chain, not on v. That means e2's load could overlap with the three tied pseudos forming v (the D load, subu, and addu), and if v turns out to be global, the intermediate subu result becomes a local value instead.

I'm also considering how v could be made global without disrupting other assignments, since v's definition (D minus prev plus spd) and an earlier search noting block 2 might point to a way to name it as block-global.

Trying variant m25: combining the m7 framework with reusing block 2's D value as v, since block 2's D (r96) already prefers v1, matching the target's v1 usage in the tail — that consistency makes it worth testing.
