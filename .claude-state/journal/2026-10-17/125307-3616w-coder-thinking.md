---
ts: 2026-10-17T18:53:07.737Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a0b7566fdaca12346
model: claude-opus-5-5[1m]
effort: medium
turnId: 5fa06e7a-0d54-4425-8d05-7af8227a2b37
---
I'm tracing why the copy assignment to a0r happens before the subtraction, checking whether combine actually merges the load into that register given the pseudo doesn't die at that point since it's still used in the subsequent addition.

That points to CSE: since e1's load value gets canonicalized to a0r because a0r lives longer (survives into a later block), so e1's uses get rewritten to a0r while the original load pseudo becomes dead, essentially turning the load target into a0r directly. So the fix might require making e1 the longer-lived variable instead, or forcing a second separate load so the two values stay genuinely distinct instead of collapsing into one canonical register under CSE.

I'm also wondering if pinning v0 as a hard register would stop CSE from substituting it, since CSE typically avoids merging hard registers, and whether other type variations (u8/u16 copies, signed vs unsigned loads) might dodge the copy-merge behavior without adding extra sign-extension instructions.

I'm also considering restructuring where the move happens — maybe skipping the intermediate copy entirely and storing the loaded value directly after the comparison, avoiding the need for a0r altogether, and checking where exactly the target places that store relative to the branch delay slot.

I'm thinking about why cse picks a0r as canonical over the other register — it likely comes down to which one has the longer live range within the extended basic block, since the store in the then-arm appears to fall through into the same ebb as the comparison.

If I restructure so both arms jump to a shared store label instead of falling through separately, that join point would have two predecessors and start a new ebb, which should break cse's ability to see a0r's later use as being in the same lifetime scope.

But actually checking cse's internals, it seems the equivalence tracking uses global last-uid/cuid ordering rather than strict ebb boundaries, so I need to check whether that global comparison would still let it match regardless of how I split the blocks.

Maybe swap which register is the long-lived one: a0 could hold the original loaded value copied before subtraction, while e1 gets decremented by 48 and becomes the new pseudo used in the comparison, breaking the copy equivalence right after the subtract.
