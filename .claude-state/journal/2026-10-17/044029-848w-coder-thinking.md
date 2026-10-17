---
ts: 2026-10-17T10:40:29.531Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: affd4bdd851658ceb
model: claude-opus-5-5[1m]
effort: medium
turnId: 3036a8ad-ba82-454c-8ac7-51f507a74f6e
---
The scaffold reproduces correctly. I'm noticing differences in instruction ordering between the two target blocks—block 1 moves a0 to zero early, while block 2 stores to offset 4 before setting a0, with the value 7 stored after the loads. This suggests alias-blocking affects ordering in a source-order-ish way, so I want to experiment with setting base n_sets to 2 to test this.

Thinking about macro-style possibilities, each block could be a do-while macro declaring its own pointer variable, giving separate pseudos per instance—but that mirrors a previously refused approach that still scored decently, so a redundant re-set isn't automatically disqualifying under the refusal criteria (no register pinning, no asm statements, no added volatile or builtins).

I'm checking the scheduling dump for register numbers to infer the known base value in block 2, and considering whether the original source used a global struct array with a color field as the real access pattern.

Looking closer at why block 1 differs from blocks 2 and 3: block 1 folds several loads to constants because cse recognizes the base symbol within the same extended basic block as its assignment, while live pseudo r0 handles the base-minus-12 offset and r0 itself handles the base offset directly. This implies blocks 2 and 3 sit in separate EBBs where cse loses track of the base, meaning there's an EBB boundary — likely a label — between block 1 and block 2, possibly from an original conditional or loop construct that got optimized away.

I'm trying to recall how gcc 2.7.2's cse.c determines basic block boundaries — specifically how cse_end_of_basic_block handles code labels, jumps, and loop notes like NOTE_INSN_LOOP_BEG, and whether a do-while(0) loop structure would leave behind the kind of notes that explain this EBB split.

So I'm now wondering if block 1 was originally wrapped in some kind of macro using do-while(0), or possibly a genuine loop structure, which would explain why only block 1 ends the extended basic block while blocks 2 and 3 don't show the same pattern. Testing against c27's cases (x1, x2, x3) to see which hypothesis fits, then trying to reconstruct what the original source macro might have looked like.

Since each macro invocation operates on constant arguments within its own block, cse would normally fold everything to constants again unless a register value persists across the extended basic block boundary -- and since cse at a new EBB start doesn't track register contents from prior EBBs, a pseudo like a load-address instruction set once in block 1 and reused in blocks 2 and 3 would stay as a register reference rather than collapsing. That points to the base variable being the one set in block 1 and reused later, which matches hypothesis h2.

I'm now trying to pin down whether cse actually attaches a REG_EQUAL note to that symbol-address set, which would make scheduling treat it as a known constant anyway -- I need to check the exact condition in the gcc 2.7.2 cse.c source rather than relying on memory, so I should search for whether that source file exists somewhere in the repo.

The dump scaffold reproduces h2. Now I'll check gcc 2.7.2's cse REG_EQUAL condition and init_alias_analysis to find a way of setting `base` that avoids getting an opaque or missing REG_EQUAL note, which would unblock sched1.
