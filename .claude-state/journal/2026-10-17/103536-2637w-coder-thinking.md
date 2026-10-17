---
ts: 2026-10-17T16:35:36.198Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: ac8178896d2313b85
model: claude-opus-5-5[1m]
effort: medium
turnId: 589d16b4-5a62-4ce6-8a45-63d170f3cb6e
---
I'm realizing the three uses of that symbol fall within a single extended basic block since function calls in gcc 2.7's cse don't terminate blocks, so cse merges them into one pseudo register. I need to find a natural way to split them—like inserting a code label via a conditional branch between the uses—since there's no obvious structural boundary separating these calls already.

I'm checking whether labels separate the call sites into distinct cse blocks, and counting the groupings of three uses—two laundered, one not—across each site. I wonder if varying the address expression per call (different symbol_ref forms, pointer offsets, or computing into the arg register directly) could stop cse from unifying them, though most variants just fold to the same RTL.

I'm also considering whether the whole pattern is from an unrolled loop of three actors, but gcc 2.7 doesn't unroll automatically, and the third call's divergence (writing s1 itself) undermines that theory—unless loop invariant hoisting pulls the symbol address out once per iteration, which would explain the repeated `la $a1`.

On rematerialization, local-alloc.c's requirement of exactly two references per pseudo (set + use) means cse could legitimately replace repeated symbol constants with a cheaper register, and I'm now thinking about what breaks those cse equivalence classes across basic block boundaries—labels, jumps, and call-clobbered hard registers all reset things, but pseudos should survive.

I want to check whether a conditional branch between uses could split the extended basic block cse tracks, since cse ends a block at a CODE_LABEL unless jumps fall through. To pin this down I should read through the actual function structure, starting with the first hundred or so lines.
