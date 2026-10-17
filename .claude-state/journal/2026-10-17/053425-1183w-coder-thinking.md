---
ts: 2026-10-17T11:34:25.463Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a7979eba5885c3edf
model: claude-opus-5-5[1m]
effort: medium
turnId: 921e828f-1fac-424f-94a0-d040638a6158
---
I'm wondering if cross-jump merging makes these two addressing forms equivalent regardless—like whether declaring the variable as an array and using different indexing expressions would still collapse to the same assembly, making the distinction unnatural to pursue.

Instead, I'm considering whether restructuring the block layout could avoid the merge altogether—having the first arm fall through to the join rather than jump, or routing arms to distinct labels that only later coincide. That raises questions about how jump.c handles redundant/adjacent labels, and whether find_cross_jump's insn comparison (via rtx_renumbered_equal_p, ignoring certain notes) would still treat the blocks as equal and merge them anyway.

Even if the RTL patterns differ slightly, matching REG_EQUAL/REG_EQUIV notes can let the compiler still merge them. I'm also wondering whether the address loads in each arm reduce to the same lui/addiu (or `la` macro) sequence, and whether the two arms reference what are actually identical string constants—since gcc 2.7.2's varasm.c hashes STRING_CST contents via const_hash and would assign them the same label, making the arms truly equivalent at the RTL level.

I'm trying to figure out how the original code structure avoided this merging—maybe it used a table lookup, a switch over a computed rank, or separate symbols at distinct addresses rather than identical string literals, since the linker won't merge genuinely different symbols even if their contents overlap.

Looking at the jump table ordering, each comparison block ends with a jump to the join point, and I'm checking whether the delay slot after each jump is filled—since "la" expands to two instructions and isn't eligible for delay-slot filling, that likely explains the nop pattern matching mine. I'm now wondering if cross-jumping optimization is simply always enabled at this optimization level, which would explain the collapsing behavior regardless of code shape, and I want to check the cross-jump detection logic directly to confirm.
