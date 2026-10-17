---
ts: 2026-10-17T10:53:43.995Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: affd4bdd851658ceb
model: claude-opus-5-5[1m]
effort: medium
turnId: 3036a8ad-ba82-454c-8ac7-51f507a74f6e
---
Since fold_rtx would substitute a known constant equivalent, cse must not know s0's actual value in blocks 2/3, while scheduling also treated it as opaque there—suggesting s0 is only known as a concrete value in block 1, not downstream.

I'm wondering whether the base register gets materialized late, after cse has already run—maybe by loop invariant motion, or by combine merging a symbol-set with a later plus operation, dropping the notes cse would need. The question is what kind of operation combine could fold that cse itself couldn't—something like a subreg or zero_extend interaction that cse's folder doesn't handle but combine's pattern matching does.

I'm also considering an address-taken local where a pointer-to-pointer indirectly stores the base, forcing it into stack memory, but that doesn't match since there's no ADDRESSOF mechanism in this GCC version. I'm also thinking about whether cse treats user variables differently from temporaries, or whether a code label or loop structure between the set and its uses could split the optimization into separate blocks that cse processes independently.

I'm tracing through a loop-with-break scenario: the exit jump, the barrier after it, and whether the continuation label becomes unreferenced and gets deleted by an earlier jump-optimization pass before cse ever sees the code, which would explain why the set and uses end up isolated.

I'm reconsidering whether cse actually folds the pointer arithmetic once the base is known, confirming from the earlier example that it does fold and produces the smaller result — so I need another way to make the base opaque, perhaps by making it a function parameter instead of a local constant.

Thinking about combine: if cse never emits a REG_EQUAL note because the source isn't a foldable constant, then later when combine simplifies the expression down to a plain symbol reference, that simplification happens without any equivalence note attached, since there was nothing to carry forward in the first place.

I'm now exploring what kinds of expressions combine can simplify that cse itself can't fold — maybe something like masking a value into two disjoint bitfields that together recombine to the original symbol, which cse's folder wouldn't recognize but combine's more aggressive simplification rules could reduce back to the bare value.

Tracing through combine's substitution, the two and/or operations fold away and base ends up as a plain copy of r, with no REG_EQUAL and base treated as an opaque pseudo distinct from r. I'm now second-guessing whether this bitwise-hack pattern still counts as "natural" code, since it's not a pin/asm/volatile/builtin case.

This looks like it crosses into the forbidden "launder" category the project's ethics rules reject, so I need to find a genuinely natural reason for the opacity instead. I'm considering whether cse's handling of symbol refs for function-local statics or strings could explain it, or whether cse's invalidation behavior on calls — which clobbers call-clobbered hard regs and memory but not pseudos — might be the real mechanism at play.

I'm also checking whether setjmp-style calls trigger special CSE notes, whether the basic block processing has an insn-count flush threshold (not applicable here with only 60 insns), or whether cse_insn has special-case logic for skipping symbol refs tied to user variables in its recording table.

Thinking further about how CSE tracks the base register's value: since the quantity for base traces back to a constant-valued set, canon_reg and fold_rtx could substitute that constant into address computations when it's cheaper than the register itself, depending on rtx_cost comparisons for symbol references on this target. I'm tracing through find_best_addr to see how it would handle a register-based memory address in that case.

Checking whether the folding logic actually skips plain register addresses, which would explain why block 1 still uses base-relative addressing for the register at offset zero despite CSE knowing the constant value. This matches what I see in the target: absolute addresses for the fixed symbols, but base-relative addressing preserved at offset -12 and offset 0, consistent with a1 holding base-12 as a live pseudo register and the source code writing everything through base. This confirms block 1 is fully explainable by CSE's known behavior.

Now for blocks 2 and 3, it seems CSE doesn't actually know the base there, since nearly everything got folded to absolute addresses except the exact register match at base+4, while the target shows all addresses as s0-relative. This points to an EBB boundary existing between the first call and block 2, with constants getting rebased to base in a second CSE pass after being turned into related values in a first pass.

A CODE_LABEL right after the call would create a natural scheduling boundary too, since labels split basic blocks for scheduling purposes — a0/a1 sets placed at the top of a new block matches the target exactly. So I'm now thinking the target is consistent with a CODE_LABEL surviving right after call 1 (and possibly call 2) into the CSE passes.

For this to happen with zero extra code, I need a jump whose condition can't be folded until cse runs — like a variable that's provably constant but not foldable by the earlier expand/jump1 passes, so jump1 can't remove the branch yet, and only cse1 figures out the condition is always false and lets jump2 clean up the jump and label afterward.

I'm wondering if label-following affects whether cse thinks the path continues past the jump. Let me try a simpler natural-code hypothesis instead — maybe something like `if (base == 0) return;` on a symbol address, since cse can fold a symbol-reference comparison against zero to known-false, which would explain the behavior without needing a contrived index loop.

This leads me to a null-pointer-check pattern: the compiler might not fold `D_800A5E94 == 0` at tree level if the address is first assigned through a variable, so the comparison and jump get emitted, then cse1 later recognizes the symbol is nonzero and folds the branch away. That's a completely natural C idiom — assigning a global address to a pointer variable and checking it against NULL before dereferencing.

I should test this empirically instead of reasoning it through abstractly. I'll construct test cases with a base symbol and an if-block followed by two more blocks, then trace through how cse1 and the jump-optimization pass interact — since jump optimization likely runs after cse1 and could merge the label away, letting cse2 see everything as one extended basic block and resolve the base reference cleanly.

If base's set has REG_EQUAL, sched knows it and can freely reorder stores/loads — comparing target block 2's instruction order against h2's, the a0/a1 positions differ too, likely because h2 has a do-while barrier constraining things while target doesn't. With base known, scheduling priorities alone determine ordering, and c27 claimed all 120 orderings converge given h2's barrier — but without one the result could vary, so I should just test it directly.

I'll test a pointer check like `if (base) { block 1 }`, since this is a natural way to produce a real CODE_LABEL that ends cse1's EBB without a scheduling barrier, matching the target's barrier-free schedule.
