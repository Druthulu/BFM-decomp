---
ts: 2026-10-17T10:50:29.751Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: ae39e3e55ca2abfd6
model: claude-opus-5-5[1m]
effort: medium
turnId: 50f5af05-e353-44b9-ba7b-703e4f789154
---
Sharing that pseudo-register badly disrupts scheduling, creating anti-dependencies between the two sets and killing boost potential. So m7 with 8 remains my best result. I'm wondering if combining m14's idea of merging flags/d into a global variable with the m7 approach could work—making a single global that holds flags, d, and arm results together, though that risks introducing conflicts too.

Checking m14's register assignments, d conflicts with v0, v1, and a0 locally, while prev needs v0. If flags takes v0 in the target, prev can't also be local there, so either flags stays local and prev becomes global, or vice versa. Making prev global means it needs to reuse a pseudo from another block without disturbing a1's availability—candidates like `a`, `diff`, or `spd` each introduce their own register conflicts (a0, v0, a3 respectively), so none seem to resolve cleanly yet.

I'm now wondering about the param pseudo arg0_ — in m8 it seems eliminated, likely because combine merged the initial copy from the hardware register directly into its first use, killing the original set and making it effectively local to the tail rather than spanning the whole function. That would only not happen if arg0_ is referenced in two separate places within block 0, like a direct assignment through a cast alias, which would force it to stay live longer.

But the target code shows the store using a2, not a0 or a1, so if arg0_ were actually used there I'd expect the store to reference whichever register arg0_ got allocated — meaning something else is going on with how global allocation resolves the conflicts against the tail's hard register usage.

I'm also checking m7's d global against the tail: prev, e1, v1, and flags all line up, but e2 conflicts at v0 since d claims it. That suggests flags might need to live longer, past e2's load, to free up v0 — so I'm looking at whether that reshuffling matches the final store of 0x1000 into arg0->unk20+0x1A, which loads v1 and sets v0 for the immediate.

I'm trying to figure out why making e2 global broke scheduling in m11 while matching for m7 — the residual 68-instruction count suggests something else shifted, maybe a load that wasn't CSE'd. Checking whether e2 needs to be live across a block boundary or assigned in block 0 to force global allocation, like an explicit zero-initialization at function scope.

I'm also considering inserting a real block boundary, since dead labels or do-while(0) get optimized away. The abs idiom recognition requires a specific pattern (compare, negate, label), so maybe the store instruction sits between the comparison and negation, breaking that pattern match in a way that matches the target's branch/move/negate sequence.

I'm trying to figure out exactly when jump.c's abs-folding pass runs and whether it always converts explicit if-based negation into the abs idiom regardless of variant, then reconsidering whether the mystery global variable even matches the original source before shifting to examine how the target loads the value into the register.

Maybe each struct field access is independent rather than cached in a variable, since the compiler can't re-derive a value from memory once it's gone—so the question becomes whether `arg0->unk20` gets reloaded between the flag-set and the subsequent assignment chain, given that chained assignments evaluate right-to-left.

So if unk1C is stored first and unk18 second, that would normally require three separate loads unless something preserves the earlier load. I'm digging into how 2.7's CSE invalidation logic decides whether a store to a varying address kills a cached memory load, since that's what would explain getting only two loads instead of three.

Thinking about register tying, suggestions arise when a pseudo is copied from a hard register that dies right at function entry, which could explain why e2 gets suggested a0. But that seems to contradict the requirement that e2 be local, so maybe d itself is local instead, which would mean v either doesn't die at that point or is global.

I'm reconsidering whether r78's global status comes from being assigned twice within the block or from local_alloc's criteria — specifically whether REG_BASIC_BLOCK is nonnegative and REG_LIVE_LENGTH isn't -1, which determines if a register qualifies as local versus getting bumped to global allocation.

So the key condition requires reg_n_deaths equal to exactly 1 for a register to be treated as local — dying in two places pushes it to global status, which matches what the table shows. This means for v to avoid tying with the result of abs, v must not die right at that abs instruction, which could happen if there's a store of X occurring after the abs in scheduling order rather than before it. I need to check whether that's the ordering in free.c's version.

Looking at the m7 schedule: insn 116 loads v, 132 loads e2, 134 computes abs, and 125 stores X — notably X comes after abs there. The scheduling order must differ between free.c and m7 because of how many times d gets set: when d has multiple assignments, abs doesn't get a scheduling priority boost, which changes its placement relative to X. So in free.c, abs likely gets boosted (since d has just one set) and ends up scheduled after X, while in m7 the lack of boost causes abs to land earlier.

Thinking about memory dependencies, X's store can't cross the flags store in sched2 since they share memory, so X must precede the flags store in sched1 too. That chains into flags store needing to precede the e2 load (true dependency), with abs sitting somewhere after that load in the final arrangement — so I need to figure out exactly where abs can land relative to this whole chain.

For v to survive past abs, abs itself needs to come before X in sched1, letting sched2 push abs down past the e2 load since it has no memory dependency blocking that move. But checking d's lifetime: d spans from abs to the sh24 store, and if flags also lives in v0 overlapping that same window, d and flags can't share a register — so this ordering breaks unless flags dies right at abs, which doesn't match the target code where flags stays in v0 until its own store. That means with d local, sched1 actually needs abs to come after the flags store, with X preceding the flags store, which puts v's death back at abs and creates a tie situation — unless d was already born earlier than I'm assuming.

I'm now considering whether a set-then-overwrite pattern for d, where d is set but never used before being clobbered, would make it dead on arrival and get deleted by flow analysis — versus a set-use-set-use pattern which registers two separate deaths and keeps d as a global register. This leads me to wonder if the tie-breaking actually happens inside combine_regs itself, through rules like not combining registers of mismatched sizes, not combining a smaller already-assigned object with something bigger it's tied to, or refusing to combine when the source register is still live at a particular point.

Other conditions I'm checking: combine_regs bails out if the source register already has a quantity assigned or is marked global, and bails if the destination register is a hard register or global unless it's specifically a hard register case. I'm also looking at call-crossing counts and liveness-after-set conditions, plus whether the destination's required register class is compatible with the quantity's minimum class — since a mismatch there, like needing a different class than what the source quantity supports, could block the merge even when both happen to be in the same general class.

Then there's a mode-size check: registers can only combine if one properly fits within the other's size, so if the destination is a narrower mode (say 16-bit) while the source is 32-bit, GCC would need to compute the operation at the wider size and truncate via a subreg rather than tying them directly. I also want to look at whether the used register is itself a subreg with some offset. Given v has two deaths, it should be treated as global, while d stays local, meaning no tie is possible since global registers can't merge with local ones — so I need to sort out the local ordering between d and other overlapping registers.

I'm now trying this empirically: for the target register to be allocated without the earlier one being tied up, I need either the intermediate register to stay purely local (never tied) or to become global itself, and I'm checking which combine_regs failure path would produce that outcome by tracing the abs instruction pattern's operand structure.

Looking at block_alloc in the old local-alloc.c logic, it checks whether operand0 is a register and then tries to combine the output with the first input operand that dies in this instruction — that's the path I need to trace to see if the tie actually succeeds here.

I'm trying to recall whether jump.c actually detects the abs pattern directly, or whether it's fold-const that converts the conditional negation into an abs expression before expansion reaches that stage.

Combine might still simplify the bitwise-complement-plus-one pattern back into a negation via simplify-rtx rules, so jump.c's early fold wouldn't catch it but combine would merge it afterward anyway, yielding the same final branch-and-negate sequence once reorg fills the delay slot.

This also means the blocks splitting d's assignment across branches makes d live globally, and since e2 is loaded before the conditional, it also becomes a cross-block global variable, which affects global allocation decisions. I want to try a few variants of the source to see which triggers the right folding: one where d is first set to v and conditionally complemented, one where v itself is complemented into d, and one where the conditional is already written as an if-else assigning -v or v directly. I'll start by testing the first variant.
