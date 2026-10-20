---
ts: 2026-10-17T18:46:37.547Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a6ee12ed7d3da1789
model: claude-opus-5-5[1m]
effort: medium
turnId: c73a5082-25b2-49a4-a028-dd1d5ff9dd77
---
I notice something odd in p2: the tag load uses a0 while psVar14 is computed from s2, which is the reverse pattern. This hints that cse didn't propagate the cursor substitution into psVar14 here, likely because that variable belongs to a block outside the cse range, since equivalences seem to reset at block boundaries like the jump following the tag check.

So I need to figure out how to keep the tag load inside cse's range for `cursor = param_1` while pushing `psVar14 = param_1+5` outside it, perhaps by restructuring the loop so the tag load happens at a new block entry point created by a jump target, since the early-return branch naturally continues the extended basic block via fallthrough.

So the duplication happens before cse runs, meaning the copy stays in the same ebb and gets replaced again. I'm considering restructuring the loop with explicit goto labels so the tag load sits right after a label, but since goto-based loops lack the NOTE_INSN_LOOP_BEG markers, jump.c won't rotate them, leaving only one tag load instead of the two needed to match the target's pattern.

I'm now thinking about whether an early-return pattern like `if (gate) return gate;` naturally produces a label before the tag load, since gcc expands that as a conditional jump around the return code, landing on a label right where the rest of the function continues -- which could be exactly the split point I need to break the ebb for cse.

But with -O2 enabling both cse-follow-jumps and cse-skip-blocks, cse would likely trace right through that single-predecessor label anyway, since it only breaks when a label has multiple incoming paths. So the real fix might need a label with two predecessors, like a loop back-edge landing right before the tag load, but the loop structure complicates this since there appear to be two separate load points to consider.

Maybe the discrepancy is that the original compiler actually used param_1 itself as the loop cursor rather than a copy — so param_1 gets incremented directly inside the loop and lives across iterations, getting allocated to a saved register like s2 with a `move s2,a0` at entry, which would change how psVar14 is computed relative to it.

At -O2, the incoming argument gets copied into a pseudo, and the original a0 hard register typically isn't reused afterward. In my pinned version, the addiu reading a0 means param_1's pseudo got allocated to a0 and stays live until that instruction, while cursor sits at $18. I consider dropping the cursor variable and replacing its uses with param_1 directly, but that would put param_1's pseudo in a different register like s2, not a0—yet the target clearly reads a0 for that addiu, implying there must be two distinct live values rather than one collapsed variable.

I'm now wondering if the first tag load structure matters—whether rewriting the do-while as a plain while loop with an earlier initial load would change register allocation, but it seems to end up the same. Another angle: maybe the first load addresses cursor through an expression that cse doesn't canonicalize the same way, though folding seems to collapse that too. I'm considering forcing param_1 to appear distinct from cursor in cse's view by inserting an explicit assignment of cursor from param_1 early on.

I'm checking whether moving the cursor assignment to a point cse can't track—like laundering it through a cast—would work, but that seems disallowed. I'm also wondering about reordering the tag load relative to the counter increment, though the counter needs to read s2 first regardless. My best bet now is comparing the instruction counts between versions, suspecting the move from s2 to a0 might be landing in a delay slot in one variant but not the other, so I want to inspect that diff directly.
