---
ts: 2026-10-17T11:20:06.745Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a5faba3cdb29155cb
model: claude-opus-5-5[1m]
effort: medium
turnId: e4e5bc1c-68a3-4a95-bce5-27c78dfaef1c
---
I'm trying to trace through cse_main's logic, specifically how it determines the basic block path by calling cse_end_of_basic_block, to understand how the "2 to 73 (17 sets)" block boundaries get computed.

Rather than continuing the theoretical label-use counting, I decide to verify directly against the dump: insn 58 disappeared and jump 60 now uses reg 92 instead of reg 102, confirming cse1's scan spanned both BB0 and the block starting at label 57. I start tallying instruction counts across BB0, the 57-block, and BB1 to see if they add up to the reported 17 sets.

I'm trying to pin down whether LABEL_NUSES(57) being 1 stems from the dump showing "2 to 73" during cse1's first scan, or from how jump 21's JUMP_LABEL was set — the arithmetic only works out to 17 for the [N,T(27)] path, not the direct [T(21)] path, so I keep second-guessing which branch cse actually followed first.

Rather than chase that further, I'm looking for a way to keep pe alive through cse1 by making sure its use doesn't land in a block cse1 can collapse with its set — maybe by routing pe's use through the reset/else block, or by tying pe's value into some other computation in the head block (like the mask or offset values) that cse2 would need to preserve anyway, though neither of those existing computations seems to fit.

Maybe the resolution is different: in cse2 the BB1 read/store could begin as (mem pe) with pe's set still reachable, getting replaced once, while in cse1 that same replacement doesn't happen because pe's source expression there isn't something cse1 can recognize as (plus pd 4) in the first place.

If pe equals pd plus a variable k whose value cse1 only partially folds, I'm checking whether cse1 would fold that sum to a constant immediately, and comparing costs between the plus-expression and its folded constant form using the target's address cost function to see which candidate gets picked for the memory reference.

Comparing costs, the plain register-plus-register form wins over the folded constant, so pe stays as pd+k rather than being replaced. Later, combine picks up k's known constant value and substitutes it directly into pe's expression, turning it into pd+4.

But pe gets used twice -- once for reading, once for storing -- so I can't fold the constant into both references, meaning there's still an extra addition instruction either way. I'm wondering whether the original macro used a do-while(0) wrapper, since that variant seemed to let the read fold cleanly, and testing that version might reveal whether it's a genuine match or just another artificial lever.

Then I start considering if the loop boundary itself matters -- since cse1's EBB stops at the LOOP_END note, maybe the head should come after the i-loop in source order, but that would change statement ordering and produce different assembly entirely, so that's ruled out. I also wonder whether the else-block reset, which sets the address to 0 absolutely in the target, might originally have been written as a pointer dereference set to 0 that then got transformed differently across cse1 and cse2.

I notice something: this absolute store matches the target's else-branch pattern exactly, which suggests that in the original source both branches accessed memory through pointers, but only the else-branch access got constant-folded in cse2 while the then-branch one ping-ponged back to a pointer-offset form. That's odd though, since both branches lie in the same extended basic block where the pointer set is alive, so I'd expect both to ping-pong the same way -- unless something about how cse2 scanned the else block only once changed the outcome.

So accesses ended relative through mechanism (a) pe's set being alive at cse2, or (b) pd being an unknown constant—maybe pd is a static pointer variable loaded from memory, but the target shows an immediate address constant, so that doesn't fit either. This pushes me back toward (a): pe's set must still have a use that survives cse1 but gets eliminated by cse2.

Then the real question becomes what creates that extra use path. It's probably the jump-threading pass between cse1 and cse2 that merges blocks into EBBs, changing LABEL_NUSES counts so a block reachable from two paths during cse1 collapses to one reachable path afterward. I need to figure out why cse1's initial scan followed the branch into block 57 in the first place — likely because LABEL_NUSES(57) was still 1 at that point.

Deleting jump 60 would break the pad==0 path reaching label 57 from both branches, so cse1 must have rewritten jump 21 to 73 before removing it. I should just grep cse.c around cse_insn for how JUMP_LABEL is used to confirm the actual mechanism instead of guessing further.
