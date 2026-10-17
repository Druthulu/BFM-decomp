---
ts: 2026-10-17T13:59:05.711Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a715c83225823a44a
model: claude-opus-5-5[1m]
effort: medium
turnId: cb00494e-7b3a-4f28-b3fa-24b3d50bb0ef
---
With the mechanism confirmed that an extra instruction creates a tie which r227 wins, I now need to figure out where a vanishing instruction could come from — one present in the sched1 stream but absent from the final output. I'm considering candidates like a reload no-op move with identical hard register copies, USE/CLOBBER insns, or insns deleted by reload for pseudos with REG_EQUIV, and starting to dig into the global pseudos mny/my for the no-op move case.

I'm tracing specific copy patterns involving mn/mx and wx/wy, checking whether any copy results in both sides getting the same hard register after local-alloc and global-alloc preferencing, and also considering gte macro outputs and clobber insns generated when assigning to multi-word pseudos piecewise as other possible sources of a vanishing instruction.

Now I'm testing whether self-assignments like `x = x` could produce a redundant move, but ruling it out since store_expr skips emitting an insn when target and temp are identical. I'm also checking whether redundant type conversions like `(s16)(u16)mny` could survive to RTL, but these get folded away at the tree level before expansion, so that's not it either — wondering if volatile qualifiers might be relevant instead.

Shifting focus, I'm wondering about jumps that get removed specifically by jump2 after reload rather than earlier passes. Since jump2 runs after reload while sched1 counts live lengths per basic block including jump insns, a jump that survives jump1 and cse but later becomes trivial and gets deleted in jump2 could be the culprit — especially since jump_optimize can rerun after cse or loop under certain flags like -fthread-jumps.

I'm also considering a different angle: instead of chasing which pass removed an insn, maybe the real fix is reordering the preheader so that r227's live range starts earlier relative to r229, by inserting a non-hoisted insn between their definitions.

Then I wonder if swapping the hoisting order (hoist r229 before r227) would survive sched2's tie-breaking — but with equal priority and no dependency edge, sched2 would just preserve LUID order anyway, so that likely won't help unless one gets a different dependency-driven priority.

I'm also second-guessing whether the loop-invariant pseudos themselves have different structure than I assumed, maybe the original source used a different addressing pattern with different registers.

I've spent a while on this now, so I'm trying a batch of guesses about what instruction might be "vanishing" -- things like a cast that gets optimized away, or a GCC-emitted USE instruction tied to register variables, volatile accesses, or end-of-block bindings in older GCC versions.

Now I'm focused on CLOBBER instructions instead: GCC emits these when assigning to multiword pseudos or when initializing small structs field-by-field in a register (via `emit_no_conflict_block` or `store_constructor`). That points toward a small struct local variable, say a two-field 16-bit struct that fits in a single register, being assigned piece by piece.

For local-alloc to apply, the source register must actually die at the copy point. I'm considering whether a variable with multiple sets—dying and being reborn later—could still count as local, but that likely pushes it into global allocation instead, so this path doesn't quite fit either.

I'm running low on time for this approach, so I'm trying another angle: maybe a jump insn gets deleted by jump optimization, or a no-op reload occurs during the function's call setup inside the loop.

I'm checking a few more cheap possibilities involving narrowing variables and subreg copies, like using an intermediate temp for the HI result that CSE might later equate with mny, but each attempt keeps collapsing to a dead or redundant copy.

Then I trace through global allocation: since mny is global and the local temp sy are both live across the copy without gcc's old allocator recognizing they share the same value, they end up assigned different registers, forcing a real move instruction.

I consider reordering the case statements so r229 is born first, wondering if that changes which store sched2 emits first — but I don't see an existing hook point outside the loop to exploit. I also wonder whether wrapping the stsz3 statement in a do-while(0) would change how loop.c interprets it as a loop structure, potentially affecting scheduling.

The reference counts would shift equally either way, so the priority ordering might not resolve cleanly — I'll just try the wrapping approach with variants and see what happens.

Confirmed the mechanism: an extra insn in the loop ties r227/r229, letting the lower allocno win. I'll test whether wrapping a gte_stsz call in `do { } while (0)` changes loop.c's hoisting order, as a cheap probe for an insn present during sched1's live-length measurement but absent from the final output.
