---
ts: 2026-11-06T02:32:27Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG18x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_E9Xn6hWxP92o0aVy6r8M
---
All 8. The dbr fill is stubborn. Let me check the dbr dump to see if reorg's fill is from the fall-through and whether a label could block it. Actually, let me test the label hypothesis directly: add a label at the addiu that is referenced by a branch that jump2 keeps. How? Use a goto from *within the same if body* that is not optimized away: e.g.,

```
if (unk98 == 0) {
    if (state == 0) goto L;   // adds a branch
L:
    unk34 = state + 1;
```
That adds a branch — wrong bytes.

Alternatively, make the addiu a jump target via a computed goto? no.

Let me examine the dbr dump of mine to confirm the fill source and check `own_fallthrough`. Let me dump the dbr pass for nopin (p4 scratch) and look at the RTL around the branch: the .dbr dump shows the final RTL with delay slots as SEQUENCE insns.

Actually, a better idea: check whether reorg's fill came from the *target* thread or the fall-through. In mine, the addiu is in the delay slot — it's from the fall-through (the addiu was after the branch). 

Hmm, what if the fill is prevented by making the addiu's destination register live at the target? We could make the epilogue use v0 by... the function is void, but we could add a statement after the switch that uses v0? The target's epilogue has no v0 use. 

What if we make the branch's target thread *own* an insn that fills the slot instead? No.

OK — maybe the real difference is in `prediction`. `mostly_true_jump` for a `bnez v0, epilogue` where the target is the function exit: prediction is based on the branch direction and the target's position. If prediction > 0 (likely taken), reorg tries the target thread first; if that fails, the fall-through. If prediction <= 0, fall-through first. Either way the fall-through addiu is taken... UNLESS `own_fallthrough` is false.

`own_fallthrough = own_thread_p (NEXT_INSN (insn), NULL_RTX, 1)`. Let me read own_thread_p: it checks that no label in the thread is referenced from outside, and that the thread is not the target of a jump. The thread starts at NEXT_INSN(insn) = the insn right after the branch (the delay-slot candidate). If there's a CODE_LABEL anywhere in the fall-through thread that is a branch target, own_fallthrough = false.

In the target's final asm, no label at a84. But labels can be deleted at final? No, jump2 deletes unreferenced labels.

Hmm, hold on: what if the original C's case 0 body starts with a `break` target... no.

Let me try yet another angle: maybe the target's nop arises because reorg's fill from the fall-through is blocked by the *call* later in the thread: the addiu's value v0 is used by the sh, and reorg's scan for the fall-through thread requires the insn to be removable from the thread — the addiu is used by the sh (which is in the same thread), so removing the addiu to the delay slot keeps the sh after; fine.

But `insn_references_resource_p (trial, &set, 1)` where `set` accumulates resources set by the insns ahead of the trial in the thread? At the start, set is empty. So the addiu passes.

Then the check `! insn_sets_resource_p (trial, &needed, 1)` — needed is also empty initially. Then `if (condition == const_true_rtx || (! insn_sets_resource_p (trial, &opposite_needed, 1) ...))` — opposite_needed = live regs at the target (epilogue). If v0 is NOT live, the addiu is accepted and moved. In mine it is moved. In the target it isn't → v0 must be live at the epilogue in the target's RTL!

What could make v0 live at the epilogue? `mark_target_live_regs` marks registers live at the target label, considering the epilogue. In the target's RTL, maybe the return label's block contains a `(use (reg v0))`? Hmm. Or maybe the target label at b3c is not the epilogue but a shared block that uses v0 before jumping to the epilogue.

In the target's asm, b3c is the epilogue directly. But the RTL at reorg time might have a label there with the epilogue emitted in final. The live-regs at the return label: for a void function, nothing.

Hmm, wait — maybe the bnez's target is NOT the epilogue label in the RTL! Look at the target: `a7c: bnez v0, b3c`. b3c is the epilogue. But maybe in the RTL the branch targets a label that is at the end, and the epilogue label b3c is the same. Yes.

OK, let me just test the hypothesis empirically: make v0 live at the epilogue by adding a *use* of v0 after the switch. E.g., add at the end of the function: `if (0) ...` no. Or make the function body end with a statement that uses v0 in a way that emits no code... hmm, any real use emits code.

Alternatively, if the branch's delay slot were filled by reorg only when v0 is dead, then making v0 live at the target would leave the nop. But adding a live v0 at the target would also add code.

Hmm, what about making the bnez condition register NOT v0 but something else? The target's bnez uses v0 (the lh result). The `lh v0,152(s0)` loads unk98. So the condition is v0. Fine.

What if the addiu's dest were a0 (state) instead of v0? Then the fill would be allowed (a0 not live at the target). Same result.

I'm stuck on the mechanism. Let me look at the dbr dump of the ORIG (with barrier) to see the delay slot and what reorg did. The orig's dbr dump would show the bnez with a nop slot. And nopin's dbr shows the addiu in the slot. Comparing the RTL before reorg (.sched2 dump) might reveal a structural difference the barrier caused: the barrier (asm memory clobber) is an insn between the branch and the addiu. At reorg time, the asm insn sits right after the bnez. The fall-through thread starts with the ASM_INPUT insn. `stop_search_p` or the trial loop hits the asm insn: `GET_CODE(pat) == USE/CLOBBER`? An ASM_INPUT with a memory clobber is an INSN with pattern `(asm_input (""))` maybe plus a clobber in a PARALLEL. In fill_slots_from_thread, the trial = the asm insn; `eligible_for_delay`? An asm insn is not eligible; the loop would `lose` and stop? So no fill → nop. That's the barrier's mechanism.

So lever-free: we need an insn between the bnez and the addiu that blocks the fill. But any real insn emits bytes. Unless it's an insn that emits no bytes AND is not a lever: a `USE`/`CLOBBER` insn! We discussed USE insns. Can we get a USE/CLOBBER insn right there? 

Hmm! What about a `(clobber)` from a call? No.

What about the `do{}while(0)` creating a NOTE? Notes are skipped.

What about a label? Labels are skipped/stop? In fill_slots_from_thread, `if (GET_CODE (trial) == CODE_LABEL) { own_thread = 0; continue; }` — a label does NOT stop the scan; it just clears own_thread. And `stop_search_p(trial, ...)`: let me check — stop_search_p returns 1 for a CODE_LABEL if not own_thread? Let me read stop_search_p.

Actually the loop condition: `! stop_search_p (trial, ! thread_if_true) && (! lose || own_thread)`. If the label clears own_thread and then something causes lose... Hmm.

But more importantly: `own_fallthrough` is computed BEFORE, by own_thread_p(NEXT_INSN(insn)): if there's a label in the fall-through thread that is entered from elsewhere, own_fallthrough = 0 → the fall-through fill is skipped entirely → nop! And a label that's *referenced* would do it.

So: a label at the addiu (or anywhere in the fall-through thread) that is referenced from outside the thread → own_fallthrough = false → no fill → nop! And the label would appear in the final asm... but the target's final asm has no label at a84. However, labels that are unreferenced are deleted at jump2. A label referenced by a branch that is later removed... 

Hmm, wait: if the label is referenced by a branch that survives to final, the label would show. The target has no such label. But what about a label referenced only by a branch that jump2/reorg deletes? For example, the label at a84 is the target of the `j` from a58/a6c? No, those go to the epilogue.

Hmm, what about a label that is referenced by a *fallthrough-into* edge? own_thread_p also checks `! label_is_jump_target_p`? Let me read own_thread_p.
