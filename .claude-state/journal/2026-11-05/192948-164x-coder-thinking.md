---
ts: 2026-11-06T02:29:48Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG18x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_MjQqpPylOfv1mfq3D5wg
---
The prediction: `mostly_true_jump(insn, condition)` — for `bnez v0, epilogue` (a return-ish branch), the prediction is likely "taken" (prediction > 0), so it first tries the TARGET thread (the epilogue). The epilogue's first insn `lw ra,20(sp)` — can it be moved into the delay slot? `opposite_needed` = fallthrough live regs. The epilogue's lw ra sets ra; ra is live at the fallthrough (the function continues and uses ra? at the fall-through, ra is needed for the final return). So rejected. Then the next insn... The epilogue thread: lw ra; lw s0; addiu sp; jr ra. Each sets a resource live at the fallthrough → rejected. So target-thread fill fails.

Then (prediction > 0 path): `if (delay_list == 0 && own_fallthrough)` → fill from the fall-through with `thread_if_true=0`. This scans the fall-through thread: the addiu. opposite_needed = mark_target_live_regs(insn_at_target) = live regs at the epilogue. If v0 is not live there, the addiu is fillable → it takes it. That's mine.

For the target to have a nop, this fall-through fill must have failed. Reasons: (a) v0 live at the epilogue target; (b) own_fallthrough false (a label between the branch and the addiu); (c) the addiu not eligible_for_delay.

own_fallthrough = own_thread_p (NEXT_INSN (insn), NULL_RTX, 1) — checks that the fall-through thread has no other entry points (no labels) and is "owned". If there's a label between the branch and the addiu, own_fallthrough would be false → no fall-through fill! 

In the target's final asm, is there a label at the addiu (a84)? The branch targets listed: a60, a74, ab0, b0c, b3c, b08... none at a84. So no label. But wait — labels can be removed if unreferenced. If the label at a84 existed at reorg time but was unreferenced, jump2 would have deleted it. Hmm, but an unreferenced label would have been deleted by the first jump pass (LABEL_NUSES==0). So it wouldn't survive to reorg.

Unless the label is referenced by a branch that was later optimized... e.g., a branch to a84 that got redirected/deleted. Possible: a `goto` from somewhere to the addiu's label, later threaded away. Hmm.

(c) eligible_for_delay for MIPS: let me check the MIPS definition. `eligible_for_delay` is usually defined as 1 unless specific insns. Let me check config/mips/mips.h in the reference tree.

Actually, (b) is interesting: own_thread_p checks that the thread is owned (no labels that other branches enter). If the addiu is preceded by a label (even one that's only referenced by a branch that jumps to the *same* addiu), own_fallthrough could be false.

Hmm, in the target's final asm there's no label at a84, but reorg runs BEFORE final; jump2 (which deletes unreferenced labels) runs BEFORE reorg. So a label at the addiu would have been deleted by jump2 if unreferenced. Unless it was referenced at jump2 but the referencing branch was optimized by reorg itself.

Hmm.

Let me try the simplest hypothesis test: (a) v0 live at the target. In the target's RTL, maybe the epilogue target block starts with something that uses v0? Let me look at the target's asm at b3c: lw ra; lw s0; addiu sp; jr ra; nop. No v0. So v0 not live.

Hmm, but `mark_target_live_regs` computes live regs at the target label considering the whole flow. If some path to b3c uses v0 before overwriting... no.

Let me look at the actual dbr dump of MINE to see the decision (it prints "Reorg function" info but not decisions). Hmm.

Alternative: maybe the target's nop is not from reorg but from *sched2*: sched2 could have moved the addiu out of the delay slot? No, sched2 runs before reorg (delay slots are empty then).

Wait, actually: what if in the target, the `addiu v0,a0,1` was NOT the first insn of the fall-through thread because the `lhu a0,52(s0)` (state load) was still there? I.e., in the target, `state` was loaded INSIDE the if (after the branch) rather than before! Look at the target: a34 `lhu a0,52(s0)` — the state load is BEFORE the switch dispatch (a34). Hmm, it's before the branch. So a0 is loaded early.

Hmm wait, maybe in the target the addiu's source a0 is dead at the target... it is.

Let me just try (b): insert a label at the addiu via a `goto` from somewhere. For example, make the `if` body a labeled target:
```
case 0:
    if (unk98 == 0) {
    again:
        unk34 = state + 1;
        ...
    }
    break;
```
A label `again:` at the addiu with no goto → unreferenced → deleted early. Need a referenced label: e.g., a `goto again;` from somewhere that jump2 can't remove.

Hmm, this is getting complicated. Let me check the moves.md for `dbr-delay-fill` cracked examples (MATCH). Search for "delay" in moves.md MATCH lines. Line 81: "MATCH: x=(n+1)*32-dw in do-while(0)... tt load in do-while(0) (lhu before sll)". Line 247: "MATCH: do { t = D_801A9A88[a1*5]; sp10[4] = t; } while (0) — the loop-shaped range keeps the u16 adds out of the t load delay slot (target nop)". These are delay-slot WALLS/CRACKS via do-while.

So a do-while might help! The C0535 trick: do{}while(0) affects scheduling/cse. Let me try wrapping the `addiu+sh` in a do-while, or the whole if body, or the store alone. b4 wrapped the store in a do-while → still 8. Let me try other placements:
- do { unk34 = state+1; } while (0) — b4 (same).
- do { lhu-ish state read? } no.
- Wrap the two calls? no.
- Wrap the addiu+sh+the rest?

Alternatively, use the `goto` trick from line 18: "MATCH — goto loop: no LOOP notes, -1 not hoisted to s3". Hmm.

Another idea from the wall tag `dbr-delay-fill`: the fill happens because reorg predicts the branch as "likely taken" (bnez to the epilogue = return, predicted taken). If the prediction were "not taken", reorg would fill from the fall-through FIRST (same result). Hmm.

What if we make the branch NOT predictable (prediction 0)? Then it tries the fall-through first with own_fallthrough; same.

What if own_fallthrough is false: insert a label at the fall-through start that is referenced. How about making the code after the if a jump target from elsewhere: e.g., the case-0 body is also reached by a `goto` from another case? Not semantically valid.

Hmm, what about making the addiu ineligible: `eligible_for_delay` for MIPS. Let me check the MIPS definition.
