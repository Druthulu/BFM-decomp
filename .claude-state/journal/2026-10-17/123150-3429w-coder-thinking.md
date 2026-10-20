---
ts: 2026-10-17T18:31:50.196Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a0b7566fdaca12346
model: claude-opus-5-5[1m]
effort: medium
turnId: 5fa06e7a-0d54-4425-8d05-7af8227a2b37
---
Most variants simplify the boolean to a direct set-less-than, but I want to keep the branch structure and second masking step intact, using a multi-step pseudo-register assignment for "ok" that preserves the same register allocation pattern seen in the a1 variant.

The real puzzle is why v0 ends up holding the constant 14 instead of the comparison result -- it comes down to local allocation running before global allocation, with v0 being free right as the call result dies at the masking instruction. I'm considering introducing a separate local variable for the masked result so it ties to v0 naturally, letting "ok" remain a global pseudo that picks up v0 afterward -- though I recall a similar approach scoring worse on instruction count, so I need to check whether that version accidentally folded the boolean into a plain comparison instead of preserving the branch.

I'm also looking at why jump.c's store-flag optimization fails when "ok" is reused as both the comparison input and the assignment target -- the optimization requires the target not appear in the condition, so reusing the same pseudo blocks the fold. I'm now trying variations like converting through a u8 type or reordering the comparison to see if either avoids that restriction while still landing the constant in v0.

Trying the subtraction form doesn't match either since it alters the instruction sequence. I'm now wondering if ok could be purely local, but the branch structure rules that out, and reordering the call result through an intermediate temp doesn't change which variable the andi targets, so that avenue seems like a dead end too.

Local-alloc ranks pseudos by priority within a block, and since ok is global it gets skipped — v0 stays live from the call through the andi copy, then dies right as the constant 14 is born, so 14 naturally grabs v0 since it's first in MIPS's register allocation order. To stop that, I'd need v0 occupied through that window, which could happen if the andi result itself were tied locally to v0 instead — then 14 would land in v1, though that risks the jump folding into a store-flag pattern unless something prevents it.

I'm also considering whether gcc's jump.c would merge an intermediate `ok = r` assignment via CSE, and whether MIPS's slt-based store-flag conversion (turning if/else constant assignments into scc-style code) would kick in regardless of how I structure the branch — I need the target to literally emit move/li instructions rather than slt.

I'm considering whether comparing ok masked against a constant still keeps ok out of the jump condition, since the mask creates an intermediate temp — that seems to score wrong too. So I need the compare operand to literally be the ok pseudo itself, with ok also appearing in v0, which points toward using a shared constant across multiple blocks instead.

I'm tracing register allocation order: when the constant 14 is born it would get v1, while ok prefers v0 since it's copied from the call result. This means I need li 14 placed before the andi in RTL order, but that depends on whether sched1 runs before local-alloc — and the target's final layout with ok in v0 and 14 in v1 suggests a specific scheduling of when 14 is actually born.

I'm wondering if a switch statement or ternary produced different jump expansion, maybe something like `switch(r){case 0xE: ok=1; break; default: ok=0;}` or a conditional expression comparing against a masked return value, since those could avoid the store-flag folding that the simple if/else version triggered.

Trying different structural variants now: a goto-based version jumping to labeled blocks for the true/false case, a nested if-else with `r` declared as `u8`, and checking whether BRANCH_COST on MIPS affects which form the compiler picks. Since the earlier d1-d9 attempts were lost, I need to regenerate and re-test these candidates from scratch.
