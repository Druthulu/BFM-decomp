---
ts: 2026-10-17T10:57:38.916Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: ae39e3e55ca2abfd6
model: claude-opus-5-5[1m]
effort: medium
turnId: 50f5af05-e353-44b9-ba7b-703e4f789154
---
This is a tooling bug where match_one prepends headers to an already-preprocessed file, which blocks lane 1 since it's outside my scope to edit tools—I'll just report it. Switching back to lane 2, I want to keep exploring the in-tree compiler using m7 as my baseline, which scores 8 with just an e2/d swap needed; I'm checking which pseudo register corresponds to d in m7, since it has the highest priority among globals, and it looks like that's r79.

I'm tracing through why d conflicts with v0 via e2, checking if e2 could be tied to a0 through combine_regs since it's a load from memory rather than a register-to-register move, which rules out the tie mechanism. Since e2 can't claim a0 as a local, I'm now digging into how local allocation's find_free_reg function picks registers, looking at whether MIPS defines a custom REG_ALLOC_ORDER that would affect which register gets chosen first.

Since no calls exist to force avoiding call-clobbered registers, I conclude e2 must be global, needing a single-set value used across a block boundary — meaning I need a label or jump that breaks the tail into separate blocks without altering the actual control flow, and I'm considering whether a real conditional branch avoids the d/v copy coalescing that CSE would otherwise trigger.

I'm looking into whether the delay-slot move in the target branch, combined with CSE's handling of register equivalence classes for simple copies, determines which of d or v becomes the canonical register — I need to check how make_regs_eqv decides this.
