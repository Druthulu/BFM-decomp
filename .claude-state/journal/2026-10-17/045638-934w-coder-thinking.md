---
ts: 2026-10-17T10:56:38.647Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: affd4bdd851658ceb
model: claude-opus-5-5[1m]
effort: medium
turnId: 3036a8ad-ba82-454c-8ac7-51f507a74f6e
---
I'm trying to figure out how flow's recomputation counts a no-op set that survives reload deletion — I need a case where base's second set becomes a self-assignment after cse2, so it still gets counted during life analysis despite emitting nothing.

I'm wondering whether cse1 would catch this earlier: cse1 deletes a no-op set within the same extended basic block if the destination's value already matches the source, so for the trick to work, the second set needs to live in a position cse1 can't reach — maybe across EBB boundaries or inside a conditional — while still folding into a redundant self-assignment by the time cse2 runs.

I'm also considering whether a dead parameter copy could be deleted silently by flow's propagate_block before the counting even happens, which would explain some of the odd set counts, but that doesn't quite fit either. Let me look at this from a different angle on how the opacity arises.

Combine's simplify_rtx can do things fold_rtx can't, like reasoning about nonzero_bits and sign-bit copies for and/shift simplifications — though for a SYMBOL_REF the nonzero_bits logic is murky since pointer alignment isn't generally tracked that way in 2.7.2.

Reading from constant memory is another option, but combine doesn't substitute loads with their initializer values even when RTX_UNCHANGING_P is set, so that path seems blocked.

This makes me doubt artificial expressions are the answer, so I'm reconsidering what original source construct could produce this state — maybe something to do with inline function parameters and how integrate.c handles them.

Function inlining substitutes constant parameter values directly into the pseudo, or emits a move when the parameter is mutable, and cse would record that as a note — but this doesn't explain modification of the base pointer's address either, so I'm now considering whether a plain `register` storage-class declaration without explicit asm register binding could be relevant.

I'm also reconsidering the loop-note barrier condition — it only triggers when a LOOP_BEG/END note sits in the middle of a scheduling basic block, so a note right at the block's start (after a label) might not count, since sched_analyze only processes notes within head..tail and basic block boundaries come from flow analysis.

Actually tracing through, a loop note right at the block head would put the barrier on the first instruction itself, which would misplace a0/a1 in block 2 — so loop notes don't work here. I need a plain label instead, one that survives through both cse passes without letting cse2 fold things back to constants.

If a label's address is taken via the computed-goto extension, LABEL_PRESERVE_P keeps it alive through dead-code elimination as a harmless zero-byte marker in the final assembly — but that's a GNU extension, not natural C. I'm also considering whether a switch statement with a single case or a simple goto-to-next-label pattern could force a label to survive jump1's cleanup, since jump1 only removes jumps that target the immediately following instruction.

What about loops? While/for loops always generate loop notes, while if/else chains rely on jumps whose conditions matter. If cse1 can fold a conditional jump on a known pseudo value (like testing a variable just assigned a constant) that jump1 couldn't simplify, the jump might become unconditional or vanish entirely — decrementing LABEL_NUSES and deleting the label, so cse2 ends up seeing a single extended basic block instead of the split one I need.

This still doesn't address why sched needs opacity at all — the n_sets/note approach doesn't help scheduling. Both the cse2 splitting problem and the sched opacity problem seem to need the same underlying fix: maybe the base pointer in the original code wasn't computed from a loop variable at all, but from something else like indexing into a fixed data structure.

Wait — maybe the target's load instruction isn't actually a symbol address. If the "la" there is really a raw constant integer cast to a pointer rather than a relocated symbol reference, CSE would treat it as a CONST_INT rather than a SYMBOL_REF, which changes how memory conflict analysis and REG_EQUAL notes interact with it entirely.

Actually, in a fixed-address world the absolute lui immediates would carry the real numeric address regardless of relocation, so masking HI16/LO16 for relocs wouldn't matter here since both mine and target show identical literal bytes either way. I want to go back and actually read memrefs_conflict_p's constant arm to settle this properly.

I found that `reg_n_sets` gets recounted per flow pass, so dead sets before that point don't count—and noticed an untested case where `lui/addiu` could encode a raw integer constant cast to a pointer rather than a symbol, which the alias oracle might handle differently. I'll check its constant-handling branch next.
