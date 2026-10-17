---
ts: 2026-10-17T11:22:42.737Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a5faba3cdb29155cb
model: claude-opus-5-5[1m]
effort: medium
turnId: e4e5bc1c-68a3-4a95-bce5-27c78dfaef1c
---
I'll switch to running quick experiments rather than full theory, since I can check a candidate's head fast. The key requirement is that pe's set must be alive at the start of cse2 and dead after, so I'm considering whether a use inside the i-loop region—one that cse1 doesn't replace but cse2 does—could satisfy that.

Looking at the do-while loop structure, the loop-top label has one use from the back edge, and cse_basic_block only continues past a label if it has zero remaining uses, so that label still ends the extended basic block in both passes. I'm now checking whether cse_around_loop or the loop's exit point might instead be the relevant boundary.

The real divergence seems to arise specifically with a do-while loop lacking a break/continue, where the code following the loop has no label in between — cse1 stops the EBB at the LOOP_END note, while cse2 continues the EBB through the fall-out of the back branch into the following code. Since our head block can't itself contain such a loop, this avenue looks like a dead end for explaining the difference.

Let me reconsider combine's behavior: it won't fold pd's constant offset into pe's set because pd has multiple uses. So instead I'm considering splitting the derived pointer into two separate ones, pe for the read and pf for the store, each merged by combine into their own single-use contexts.

But cse would likely unify pf with pe anyway if they compute the same value, collapsing back to one use with two references. The only way around this is if pe's equivalence class retains an address expression that find_best_addr won't simplify away—meaning pe's offset needs to be an opaque pseudo rather than a literal constant, so cse can't fold it into (plus pd 4) directly.

I'm recalling that fold_rtx also tries substituting cheaper equivalent constants for operands before folding, picking whichever version—folded constant or substituted-operand form—has the lower cost.

Still tracing replacement logic...

I'm wondering if later insns referencing pe would still pick up this folded (plus pd 4) from its class, which seems unavoidable given when the src gets recorded. Trying another angle, maybe pe is built with an IOR instead of PLUS so cse's constant folding on a symbol can't simplify it, leaving the expression unresolved rather than substituted.

But then checking address costs, mips' default cost function likely rejects an IOR address anyway, and combine would just fail to form a valid memory address from it, so that avenue doesn't help either — plus it's not even semantically equivalent unless alignment guarantees hold. I'm circling back to whether the combine pass could still produce the desired (plus pd 4) address pattern after a second cse pass, with the pointer used in both a load and a store.

But combine only merges two single-use definitions, not a value feeding two separate memory references. Even if cse tried to unify two pseudos that both compute pd+4 within the same extended basic block, it would just make one a copy of the other, and canonicalization would collapse them back into the same register, right where I started with two uses instead of one.

So I'm now suspecting the real explanation involves inlining: maybe `pad` and `prev` are reached through a pointer parameter of a function that gets inlined, and gcc 2.7.2's `integrate.c` substitutes constant arguments into the RTL before cse ever runs. During that substitution, `copy_rtx_and_substitute` rebuilds MEM expressions by calling `copy_address` on the address, which could produce a non-canonical `(plus (symbol_ref) (const_int 4))` that later needs `memory_address` to force it into a register.

I'm tracing through `expand_inline_function`'s logic for how it decides whether a constant argument value gets substituted directly versus forced through a register, since that branch determines whether the symbol-plus-offset ever gets canonicalized before reaching cse.

Since most formals aren't `TREE_READONLY`, the actual value typically gets copied to a pseudo anyway, so this path doesn't produce the gain I'm looking for. I'm now trying a different angle—wondering whether the symbol could stay alive through cse1 via a use that's only eliminated as dead code afterward, perhaps through the loop pass.

Actually, rethinking this: if a use of pe lies in a different extended basic block than pe's set, neither cse1 nor cse2 would fold it, so pe stays live and forces the extra instruction. But if all uses are in the same EBB as the set, cse1 would replace them all, leaving nothing for cse2 to fold away—so that's not quite it either.

This suggests I need a cse1-only boundary condition, like a LOOP_END note marking an EBB end that only exists before jump optimization runs. Jump-structure changes after cse1—like thread_jumps merging blocks based on redundant conditional tests that cse1's path-following couldn't resolve but thread_jumps can—could create the scenario where the second CSE pass sees a merged EBB that the first pass didn't.

I'm also considering whether an infinite loop with an unconditional break at the end counts as a "do-nothing" loop structure, similar to do{}while(0), since the back edge becomes unreachable after optimization — which likely falls into a banned category.

Switch statements with jump tables seem unrelated here. Looking more carefully at the LOOP_END structure, the i-loop's end is positioned after the head, which doesn't affect uses occurring earlier. I also check whether placing pe's use right after the i-loop (e.g., a store statement following the loop) could let cse2 merge across the LOOP_END boundary — but since the loop exits via a break to an exit label, this creates an EBB boundary in both passes anyway, so that approach doesn't work either.

So option (a) looks dead in plain C. Turning to (b): pd's constant might be unknown in cse2 if cse1 altered pd's defining instruction — for instance, if cse1 replaced the symbol-reference source with an equivalent register already holding that symbol, turning pd's set into a simple copy, which could still preserve constant-class knowledge through the other register's earlier set within the same EBB.

For (e), I'm thinking about why validate_change would reject substituting the constant directly into cse2's memory operand — likely because the MIPS instruction pattern requires a register address rather than accepting (mem (const)) directly, so I'm checking which load/store patterns (like the HImode move or zero-extend load) actually allow general memory operands versus requiring registers. For (f), I'm considering whether making the offset an explicit pseudo holding 4, rather than a literal in the address, might let cse fold it back to a constant successfully.

Now I'm digging into cse.c's qty_const logic — specifically the check that excludes a PLUS-valued qty_const from being used as a constant argument, and wondering under what conditions qty_const actually ends up being a PLUS rather than wrapped in a CONST, since that distinction matters for whether CONSTANT_P treats it as foldable.

I'm tracing is_const assignment in insert(): it's set true for CONSTANT_P values or for fixed_base_plus_p results, which covers things like frame-pointer-plus-constant stack addresses. That means a PLUS qty_const would come from a stack-relative address, not from our symbol case, so pd's constant should still just resolve to the plain symbol.

I'm also reconsidering whether pd's qty could be marked invalid in cse2 — this happens when a register gets a fresh qty from reassignment, gets invalidated by a call clobbering hard regs, or by invalidate_skipped_block, which wipes out registers set inside a block that a branch jumps around.

Tracing the path again: BB0 to BB1, then the conditional branch toward the store block — if that target follows a barrier it's a TAKEN jump with no invalidation, not a skipped-block case, so that theory doesn't hold up either. I'm running out of straightforward explanations and starting to wonder if the real answer involves something less obvious, like the decl being accessed through an array-with-index pattern that collapses to a constant address at compile time, even though the asm only shows a plain lui/addiu pair.

Maybe the original source read the pad data through a pointer offset into a struct, rather than the theorized merge. Given the twenty-try limit, I should just empirically test a few plausible natural spellings: a pointer-plus-offset dereference, an else-if chain, a local struct typedef cast over the address, or a differently nested if/else-if structure that changes which block gcc emits first.

Comparing branch orderings, the target seems to match a structure where equality with the previous value triggers the decrement while any mismatch falls through to storing the new value, which lines up with an inverted bne/beq pairing rather than the store-then-decrement order I tried. I'm also wondering whether the original wrapped this in a loop over multiple pads, which would explain the structural mismatch I keep hitting.

Thinking through the GCC 2.7.2 internals, I suspect the real transformation happens in thread_jumps within jump.c, which rewrites a conditional branch to skip to a second conditional branch's target when the two conditions are equivalent after register substitution -- this could explain why cse1 alone can't produce the redundant-test elimination I'm looking for, but thread_jumps running afterward could.

I wonder if JUMP_LABEL on jump 21 doesn't actually point to label 57, which would prevent LABEL_NUSES from counting it correctly despite mark_jump_label normally recomputing this. Let me test by making b2's condition textually distinct so nothing can thread, then check cse1's path dump: in a2 it processes "2 to 73, 17 sets" / "2 to 57, 22 sets" / "58 to 73, 7 sets" — that third block transition is worth digging into further.

This is taking longer than expected without a clear answer, so I should consider stepping back and assessing what the general probability is here.

Actually, I want to check if the same function exists in a sibling overlay, like ov_MAIN_012's func_8013F350, since that might already have a matched exemplar without needing extra levers.

Since cse1's paths still reach the store block, a jump-structure split before it is tough to achieve. I'll check whether the copy in ov_MAIN_012, or other head-class copies, offer a lever-free version instead.
