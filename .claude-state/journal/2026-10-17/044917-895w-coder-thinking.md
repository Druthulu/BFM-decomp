---
ts: 2026-10-17T10:49:17.529Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: affd4bdd851658ceb
model: claude-opus-5-5[1m]
effort: medium
turnId: 3036a8ad-ba82-454c-8ac7-51f507a74f6e
---
Loop notes act as hard barriers in sched1: the insn right after a loop note becomes a barrier, forcing all pending sets to propagate forward. That explains why insn 26, right after the top LOOP_BEG note, has a ref_count of 22 and why a0/a1 end up depending on it through output dependencies.

I'm checking whether this same mechanism explains the ordering in block 3 of the target — if the first insn after a loop note is the set of a0, everything downstream should chain off it the same way, producing the natural order seen for stores and loads without needing to know what base resolves to.

That matches block 2's behavior exactly, confirming base-unknown explains it. With base unknown and f2's re-set giving n_sets=2, the only remaining issue is the barrier insns. f2 uses do-while loops to hide both the base's initial set and its re-set, so I need the first insn after each loop note to be harmless — ideally the a0 set — but a0 sets only get emitted at call expansion time after arguments are evaluated, so that ordering depends on where the call itself sits.

I'm trying different arrangements: maybe the top-level do-while should contain something other than the base assignment, or the barrier right after LOOP_END could be the `la` instruction itself rather than base's set. I'm checking what happens without the top do-while (count 68) versus with it, and considering whether block 1 even needs `la` first in scheduling order, since sched2's reordering means the target barrier sequence doesn't have to start that way.

I'm also questioning whether "move a0,zero" can really precede the prologue's "sw s0,16(sp)" — if the prologue is emitted as raw text by function_prologue rather than as RTL insns, that would explain why it can appear after other instructions in the output.

I'm comparing prologue instruction orderings between my version and the target — mine saves ra before s0, but the target saves s0 before setting up `la` and saves ra after. I'm wondering if there's a different way to split the cse basic block without relying on loop notes, maybe through cse_end_of_basic_block behavior.

I'm also considering whether a jump-to-label pattern could create the right code structure, but jump optimization before cse would likely delete an unused label and trivial jump, so that doesn't help — I need something that actually forces a new basic block boundary.

Let me think about loop barrier placement instead, checking whether the barrier insns in block 3 (the no-op and the store instruction) could align with code that's naturally positioned first, like the argument setup for the function call — since in this gcc version, call arguments are computed into pseudos and only moved to hard registers right before the call itself.

Then there's the call with r0 as an argument, followed by the pseudo-set for base+20, which might get allocated directly into a1 since it feeds into the store base. But the target shows the store using s0, not a1, so I'm second-guessing whether r0 is really the store base or just the call argument — maybe I need to try a variant where the block starts with the base+0x14 computation, stores through it, then the call, but that still leaves the li a0,2 ordering mismatched against the target.

I'm now wondering whether the ordering discrepancy is resolved by scheduling after reload reordering things despite the barrier notes persisting through to final, or whether I'm wrong about this being a do-while loop at all — maybe the source structure is simpler and each block naturally sets a0 and a1 first before the stores, matching the target's layout without needing barriers to explain the base value.

Both properties — base being opaque to cse and unknown to sched — would hold if base were a function parameter instead of something loaded via la inside the function. I'm testing whether base could instead come from an extern const pointer, an inlined accessor function, or a static local variable initialized to the address, but each of these seems to get resolved through a load that cse would still see through.

Let me reconsider the loop barrier arrangement: trying placing the barriers from LOOP_BEG and LOOP_END at the boundaries of each block regardless of what the first emitted insn actually is, to see if that matches the target layout where a0 gets set before the store/pointer computation.

I'm trying placing the reset after call 2 so the barrier insn is a0/a1, but block 3's first emitted insn still needs to be that set — considering whether a comma expression inside the call arguments could force the stores to emit before a0 is set, but on MIPS the a0 assignment still ends up last regardless of argument evaluation order.

Maybe instead block 3 could start with an empty loop (`do {} while(0)`) followed by the base assignment, so cse1/cse2 collapse that into a no-op barrier insn, making everything after it free just like block 2. I want to test variants where the second reset sits inside versus outside that empty loop to see how cse handles the EBB grouping.

For block 1, I'm checking whether the target's instruction order—move a0, then la, then the store—conflicts with la acting as a barrier right after LOOP_BEG, since that would normally prevent reordering unless sched2 swaps them after reload.

Comparing my prologue scheduling (addiu sp, sw ra, sw s0, la, sw zero, move a0) against the target's (addiu sp, move a0, sw s0, la, sw ra, sw zero), it looks inconsistent with la being a true barrier, since sw ra ends up after la in the target while move a0 ends up before sw s0—so I need to reconsider whether barriers only constrain insns after them based on dependencies on prior register sets/uses.

So I'm thinking the target might not have any loop notes at the top at all, meaning there's no do-while structure there, and I should reconsider how a0 gets zeroed and scheduled first in backward scheduling.

Now I'm asking whether the base register truly needs to be unknown to both scheduling and cse separately, or if unknown base in sched1 automatically propagates. Since cse tracks values per EBB independently of n_sets, if cse knew base=sym at the top of the same EBB it would fold base+k into a constant, producing lui/addressing — but the target shows mixed addressing (some absolute, some s0-relative), which suggests cse's knowledge of the base value is inconsistent across blocks.

I'm trying to figure out what actually causes the EBB boundary without loop notes, since a barrier right after the call doesn't line up with the target's instruction order. That leaves a CODE_LABEL as the likely candidate, but only one that survives jump1's deletion of unreferenced labels — meaning it must be a label actually targeted by a real conditional jump.

I'm also considering whether a GNU computed-label (`&&label`) could force LABEL_PRESERVE_P and dodge deletion, though that feels like a stretch. Really I should just check what `cse_end_of_basic_block` in 2.7.2 treats as block-ending conditions, since whether CALL_INSN itself terminates an EBB matters here.

f2's residue is explained: in sched1, LOOP_BEG/LOOP_END notes force a full barrier, but the target shows no barrier (sw ra comes after la), so the original must break cse's knowledge of `base` some other way. Now I'll check what actually ends a cse EBB.
