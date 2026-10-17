---
ts: 2026-10-17T11:15:14.680Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: ae39e3e55ca2abfd6
model: claude-opus-5-5[1m]
effort: medium
turnId: e556b3f3-3497-4364-81b2-e77d256de80a
---
Both the global-d and global-v allocation designs leave e2 assigned to the wrong register, so neither approach satisfies the constraints unless e2's lifetime doesn't overlap with v's global allocation — which seems to create a contradiction.

So I'm narrowing down to a single configuration: e2 local, d local to v0, v local to v1, with no tie between them. That means I need to reread the combine_regs condition comparing sizes and register classes — maybe d's size being smaller than v's REG_SIZE (e.g., d is HImode while v is SImode from an abs operation) is what triggers the special case, though that would require a subreg truncation that might not form a valid instruction pattern.

Trying another angle: what if the abs computes into an SImode temp, then truncates via subreg into the HImode destination — tying the temp to v, then the destination to the temp, which just reproduces the same problem. I'm now wondering if qty_min_class comes into play: if v's register chain happens to be tied to something with a restricted class (like an HI/LO multiply register), that could shrink the class enough for the condition to trigger.

If v's chain had a HI_REG preference like the mult result registers, that would change the generated code, so this seems ruled out. So v staying alive past the abs instruction in sched1 is required given that d is local, with X's store being the only later use—meaning X gets scheduled after abs in sched1 but moved earlier in sched2, past the flag load and abs. I'm now considering whether this gap comes from a memory dependency that exists before reload but not after, particularly around how X's address (a symbol_ref) might get handled differently with MIPS and -G0.

I'm checking whether rtx_addr_varies_p and memrefs_conflict_p behave differently before versus after reload — specifically how canon_rtx substitutes known register values when determining if two memory accesses can conflict.

So memory dependencies can only increase in sched2, meaning the vanishing dependency must come from registers instead. X must follow something after abs via a true dependency on a register set later, since X as a store sets no registers itself — unless X's own address is computed from a late-assigned pseudo, like a store through a pointer that itself derives from a known symbolic constant.

But that pointer-set insn would typically get boosted right before its use, so it wouldn't force X to go late on its own. I'm trying to figure out what value could be computed after abs that equals v exactly but survives copy propagation — any obvious copy or identity arithmetic would get folded away by cse or combine, so I need something subtler. Maybe the key is that v itself doesn't die at the abs instruction because it's also used by X placed after abs, or because v feeds into the abs instruction in a different way than I assumed.

Let me think through the actual scheduling mechanics: abs gets boosted and placed as late as possible, becoming ready only once its dependencies sh28 and sh24 are scheduled, while X is ready immediately since it has no successors. For X to win the ready-list race against abs, it needs to beat out other boosted instructions at the moment both are ready — and since X is never boosted while others are, X typically loses unless the ready list happens to be clear of higher-priority boosted insns at the right cycle. I'm tracing through specific cycles to see when the ready list composition would actually let X get picked before abs.

Now I'm trying to figure out why X has priority 2 rather than reflecting its full dependency chain depth, comparing it against other instructions with similar priority values like the addu operations — it seems the priority numbering isn't simply chain depth from the start of the schedule, since instructions at various points in the chain (load, lhu, ior, flags) end up with priorities 1 through 3 in a pattern I need to untangle.

To get X to tie with the sh instructions at priority 4, I'm considering whether X could depend on a deeper chain, like an anti-dependency through the second load-store pair, which would push its priority up to match. If priorities tie, the tie-break likely falls to instruction ordering (LUID), where larger values get picked first in backward scheduling, which would explain why 138 is chosen over 135 — and if X's source position gives it a larger LUID than the sh instructions, that could explain the selection order too.

Right, priority is predecessor-based, computed over LOG_LINKS recursively — that explains why the first instruction has low priority and the last has high priority, confirming it's backward scheduling. So raising X's priority means finding predecessors deep in its dependency chain, and I need all of those predecessors to also precede X in the target ordering — checking against the sequence of stores, loads, and the lhu instruction to see if that holds.

The chain depth tops out around 3 while the sh instructions sit at depth 4, so I'm looking at whether removing the sh's dependency on the flags store would lower its priority enough that X could tie with it, with ties then broken by instruction order.

This hinges on whether the e2 load actually aliases the flags store — I need to check if the rule only applies between a varying in-struct access and a fixed scalar one, or whether the load is marked unchanging, which would require tracing through true_dependence in the 2.7 scheduler.
