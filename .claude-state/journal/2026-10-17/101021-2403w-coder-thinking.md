---
ts: 2026-10-17T16:10:21.017Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: abb4a08fa100d7feb
model: claude-opus-5-5[1m]
effort: medium
turnId: dd20a3af-7bad-4cc5-bdfe-eb40b857c079
---
CSE seems to be merging iVar1 with t since they're treated as equivalent, letting it cross calls and end up callee-saved. To block this, I need to make iVar1 non-equivalent to t from CSE's perspective, so it doesn't get substituted away.

Loading iVar1 from memory wouldn't necessarily help since CSE still treats it as equivalent after the store. What might actually work is placing the copy in a different extended basic block, past a join point CSE can't follow, or ensuring a memory clobber like a call invalidates the equivalence so iVar1 gets reloaded rather than copy-propagated — that fewer-instruction case suggests exactly this disconnect happening naturally.

I'm now wondering if the real source has no separate `t` at all: maybe it's just `iVar1 = func(); p0->unk20 = iVar1; if (iVar1 == 0...)`, which would naturally produce one pseudo across the call, with the compiler later tying that pseudo to v0 directly. That raises the question of why combine or local-alloc would assign v0 to the later uses instead of keeping a separate move — possibly tied to how GCC 2.7's register allocator handles call-result pseudos without regmove or flow passes yet.

gcc's CSE normally merges equivalent pseudos uniformly, but the target's separate local pseudo suggests the return value hard reg is pinned, preventing merge across hard-reg boundaries. I'm wondering if combine's can_combine_p would reject propagating a hard register source depending on SMALL_REGISTER_CLASSES behavior, and whether MIPS's register class setup avoids that restriction, which would explain why the store and compare end up referencing the hard reg directly rather than a unified pseudo.

I'm trying a few more C variants to match the target's register usage — moving the assignment after the if block, reusing param reads instead of a local variable, checking whether iVar1 is really a copy of p0->unk20. My suspicion is this boils down to defeating GCC's cse-copy-merge pass.
