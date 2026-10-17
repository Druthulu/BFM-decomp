---
ts: 2026-10-17T11:14:56.842Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a5faba3cdb29155cb
model: claude-opus-5-5[1m]
effort: medium
turnId: e4e5bc1c-68a3-4a95-bce5-27c78dfaef1c
---
This should fold if qty_const is known, so I'm questioning whether the replacement only happens on the last scan through BB1 — maybe scan order matters here, so I'm tracing through the block sequence from BB0 through the branch paths to count the instruction sets involved.

Counting through the different path lengths, I'm realizing BB1 seems to get visited in two separate scans, which suggests these aren't independent re-scans but rather cse_main repeatedly calling cse_basic_block to find the next starting point based on the computed path — and for jump-following paths, the next insn to resume from may differ. I recall noting that in cse2 the rescans start from insn 2 each time, with path [N,T] leading to association and path [N,N] leading to folding, so I'm now wondering if the real distinction is the after_loop parameter's effect on cse1's behavior.

I'm trying to pin down why cse1 replaces the memory reference with a plus expression but doesn't fold it, while cse2 does fold it — tracing through how fold_rtx handles a MEM source via find_best_addr suggests it should fold either way, so the difference must come from which scan actually processes that instruction last.

Rather than keep theorizing, I want to trace the actual jump-following paths through the basic blocks to see which scan order leaves the folding undone, since the path that follows both branches as not-taken seems to be the one where something blocks the fold at that particular block.

Actually, there's a ping-pong pattern here: const folds to r73 (lower cost register) then later scans fold it back to (plus r72 4), oscillating. The outcome in cse1 vs cse2 depends on whether r73's defining insn is still alive — in cse1 it survives until deleted as dead, while in cse2 it's already gone, so cse2 would need r73's set to persist for the same ping-pong to recur.

But if it folds too far and resolves to the register directly, pe ends up live as a separate register, which is bad. I need to work out exactly how many times each occurrence gets scanned so the read and store both settle on the same (plus pd 4) form, letting pe's def become dead and get deleted, which is the outcome I actually want.

The real issue is that pe's set gets deleted as dead after cse1 since all its uses were replaced. I need something to keep (plus pd 4) alive in the class during cse2 — maybe a use that survives cse1's pass but becomes dead only after cse2's rewriting, which would explain the discrepancy between passes.

Maybe it's loop merging via jump optimization — the loop structure with its break condition and back-edge label could change EBB boundaries between cse1 and cse2. Or perhaps the relevant use of pe sits in a block cse1 treats as a separate EBB, like the store/else blocks guarded by barriers, or the join label with multiple incoming edges.

If label 59's use count changes between cse1 and cse2, that would change whether the store block joins into the same EBB as pe's definition, altering whether pe survives as a live value versus getting folded back into the pointer-plus-4 expression through the value-numbering class.

I'm considering whether cse1's jump-folding naturally produces this single-use label, or whether I need a nested conditional structure where the store block isn't preceded by a barrier yet at cse1 time — then checking what follow-jumps actually requires: a label with LABEL_NUSES==1 preceded by a BARRIER, and whether the store block's position relative to the join label could satisfy that without an artificial always-false condition.

I'm also wondering if the else-branch assignment to the global could have originally used the `pe` pointer too, with cse1 folding it into the absolute address form seen in the target, rather than the source writing the global directly.

Looking at c28's earlier analysis, the do-while loop stored `pe[1]` while folding the read — similar pattern but banned in my case. That makes me think about what naturally creates a cse1-only boundary: a NOTE_INSN_LOOP_END note, which cse1's end-of-basic-block scan explicitly stops at, could be the key distinguishing feature coming from a real loop construct.

Found it: cse1's find_best_addr keeps `const(sym+4)` equivalent to pe's set `r73 = pd+4`, so cse1 marks it stable and deletes the set as dead, leaving cse2 nothing to fold back to—pe's set needs to survive cse1 and only get replaced in cse2. I'll check the cse block-end rules next.
