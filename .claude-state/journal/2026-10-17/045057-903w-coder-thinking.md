---
ts: 2026-10-17T10:50:57.315Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: affd4bdd851658ceb
model: claude-opus-5-5[1m]
effort: medium
turnId: 3036a8ad-ba82-454c-8ac7-51f507a74f6e
---
I'm tracing the CSE mechanics difference between the two versions: in V2, the base-set happens in a fresh EBB after the empty loop, letting cse1 fold block 3's constant with base=sym, while in f2 the set sits inside the loop itself, splitting it into a separate EBB from block 3 and preventing that same folding.

So the actual requirement seems to be that block 3 lives in an EBB where cse1 doesn't know base, and the barrier instruction right after LOOP_END must be inert. I'm checking whether f2's block 3 could start with a harmless statement — like the address computation or the li a0,2 — to act as that barrier instead of a constant load, looking through the exact instruction ordering block 3 uses.

Target order shows a1's set (addiu a1,s0,20) landing second, right after li a0,2, so if p is the barrier-first insn, I'd expect addiu a1 before li a0 — a mismatch. Unless p is tied directly to a1 via regalloc since it doesn't cross the call, making the copy vanish and leaving just addiu a1,s0,20 at the top, with li a0,2 scheduled freely afterward in the barrier-free portion.

I'm trying to match block 2's pattern where li a0 comes first, then addiu a1, then li v0,7 and the stores/loads, but with p forced first as the barrier this still seems to produce roughly 2 mismatched positions. I wonder if instead the EBB split should originate from inside block 3 itself — treating the first statement of block 3, the zero-store at offset 0x14, as its own loop boundary.

I'm reconsidering whether the original source actually contains explicit loops around each statement, and whether the barrier could instead come from something that vanishes after sched1, like a trivial self-assignment that disappears before the final pass — which would mean two loop constructs sit back-to-back, with a LOOP_END immediately followed by another LOOP_BEG.

Still, that doesn't quite work since a LOOP_END always leads to a real insn from the next block. The only way around it is if the loop containing the self-reset is positioned right before the call insn of the next block, so the argument setup (a0/a1 assignments) emitted after the loop note end up becoming the barrier instead.

Testing n7 (19 mismatches) shows block 2's a0/a1 moved below the stores rather than at the top where the target has them — so that's not quite right either. It seems a0 and a1 are hard-register sets with low scheduling priority, likely placed last when scheduling backward, which might explain why the target puts them right before the call.

But maybe this is actually about scheduling freedom from a lack of barriers — a0/a1 can float to the very top of the region since the sched region boundary is the previous call, and sets of call-used regs after a call get ordered right after that call due to reg_pending_sets dependencies. That makes me wonder if jump_optimize deletes the loop notes for an empty do-while loop before scheduling even runs, which would explain why the target region is barrier-free.

I've found that every base-known-to-cse1 variant in block 3 loses count and every do-while adds a sched barrier, but the target shows neither—so I'll check whether jump.c strips loop notes before sched1, which could explain a cse split without the barrier.
