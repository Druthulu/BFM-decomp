---
ts: 2026-10-17T16:36:01.034Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: ac8178896d2313b85
model: claude-opus-5-5[1m]
effort: medium
turnId: 589d16b4-5a62-4ce6-8a45-63d170f3cb6e
---
I'm thinking about how to handle this heavily decompiled function—dropping all launder calls first for scoring, then figuring out how to naturally defeat CSE's unification of the three symbol uses per group, since in gcc 2.7 CSE doesn't treat CALL_INSNs as block boundaries but does invalidate on calls for hard regs and memory.

One approach is making copy propagation unify the pseudo across three uses, since each `P = sym` assignment would get folded into the first pseudo through equivalence tracking. Alternatively, the argument expression could be rewritten as a global pointer dereference rather than a constant, changing lw vs la codegen—but the real target uses three separate `la $a1,SYM` instructions, meaning the original compilation never unified them, possibly because the three groups sat in different CSE blocks separated by labels or branches (maybe an inlined conditional broke cse-follow-jumps behavior). I want to check the score without launders first and then examine the assembly between each group's uses to see what's actually breaking CSE's unification.
