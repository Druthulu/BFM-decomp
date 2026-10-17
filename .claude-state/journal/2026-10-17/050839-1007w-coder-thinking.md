---
ts: 2026-10-17T11:08:39.325Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: ab50896154463e490
model: claude-opus-5-5[1m]
effort: medium
turnId: 85e7d1e7-b84c-459c-bcd4-f4464ab922bc
---
I'm thinking about how to break combine's assumption that the copy always folds into the branch—maybe by separating the copy and branch into different basic blocks, or giving the pseudo-register a second live use, such as passing it as an argument to an inlined helper or callee function.

The key question is what makes combine fail: if the pseudo from the copy remains live after the conditional branch, substituting it into the branch produces a parallel set that isn't recognized as a valid pattern, so combine backs off. I need to find an expression using that value in the branch's taken arm that generates real code without CSE eliminating it via jump equivalence tracking.

This hinges on whether CSE's record_jump_equiv logic, which records that a comparison is true along a given path, happens before or interacts with combine's pass, and whether rerunning CSE after loop optimization at -O2 changes the outcome.

After combine, I'm tracing through regmove, local-alloc, global, reload, and jump optimization stages, since reload itself can eliminate no-op moves when allocation merges two pseudos into the same register. I'm also wondering if combine could merge the variable even when it's assigned twice in different branches, depending on how can_combine_p evaluates the second definition.

I'm wondering if declaring the callee with a narrower return type like s16 or u8 would change how the promoted value gets copied in MIPS mode, since the real return type might be hidden behind the cast and affect how the register copy is generated.

Let me try writing several test variants with different return type declarations and compile each to compare.

I'll test several plain-C variations—a different callee return type, an inlined helper, a second use of `v`, and a basic-block split—each targeting combine's preconditions, scoring them with match_one against the regenerated ROM target.
