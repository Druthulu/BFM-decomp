---
ts: 2026-10-17T14:09:14.236Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: abe7336983cc0fdaf
model: claude-opus-5-5[1m]
effort: medium
turnId: ad81449e-f0c8-40b2-83c6-f273f94996ed
---
I'm realizing the param ends up hoisted with its lui/load before the call, and stores remain absolute because CSE knows the register holds a known constant symbol after assignment, so it folds the pointer-plus-offset into a direct constant address.

The disassembly shows an absolute store at offset 16 rather than relative, meaning p wasn't recognized as a known constant at that point in the original, unlike for the y/z symbols which stayed separate. That suggests p's value must have come from somewhere CSE couldn't track within the same extended basic block — maybe it was assigned at the top of the function before an early guard return, putting it in a different block than the stores that use it.

Since the code after that guard is reached from multiple branches in an if-chain, it joins at a label with multiple predecessors, which starts a fresh CSE block where p's constant value is no longer visible. Though plain local-alloc equivalence tracking (REG_EQUIV) might normally preserve such a substitution, that mechanism seems blocked here, possibly because p gets assigned more than once or interacts with a parameter variable also used in a dispatch table lookup.

Thinking through a candidate implementation: declaring p as a pointer initialized at the top before the guard, then bumping it by 0x20 partway through the function after it's used in several calls — this gives p exactly two assignments, which should prevent REG_EQUIV from applying and matches the earlier-scored variant that bumped p in place.

But I'm stuck on scheduling: the target seems to place p's load after the lh instructions near line 65, which suggests p's constant value isn't known early — maybe cse doesn't track p as a simple constant because it's set from something non-trivial, like a loaded pointer value or an asm-level assignment, rather than a direct address-of expression.

If p were an absolute address instead of a reloc'd symbol, the generated immediates would differ from the relocated zero-immediate bytes the scorer compares against, which would hurt the score since the baseline object has relocations — so that explanation doesn't fit well either.

I'm also second-guessing the cost model: find_best_addr only folds symbol+offset to an absolute address if it's cheaper, and MIPS address costs make that fold questionable unless -G0 applies, so I'm not sure that's the right path.

Maybe the pointer isn't a simple pseudo at all — maybe it's an array element accessed through an index variable that cse can't constant-fold, and I should look more closely at the actual target store sequence to figure out the addressing pattern being used.

The repeated stores with increasing offsets alongside calls passing an incrementing index and advancing pointer look like a manually unrolled loop rather than compiler-generated unrolling, so I'm trying to figure out what source loop structure would produce that without actual loop codegen — and whether cse fails to see p as constant because of how it's assigned (maybe through a conditional expression or some integer cast trick that blocks folding).

I'm also reconsidering where p gets assigned relative to the first rotate call: if the assignment happens before that call, cse should already know it's constant across the block, so that doesn't explain the asm distinction in the target. Maybe the stores are nested inside a do-while(0) block or some other label boundary that resets cse's knowledge of p.

I'm starting to wonder if this particular S16 case is just a wall I'm not going to crack right now, and I should check how much time I've spent on it.
