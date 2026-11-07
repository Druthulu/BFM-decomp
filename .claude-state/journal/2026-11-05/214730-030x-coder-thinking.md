---
ts: 2026-11-06T04:47:30Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG21
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_Hg9pOxcQe8qIFCLp0meA
---
So fill_eager_delay_slots takes insns from the fall-through thread (THREAD = likely direction). It requires `! insn_sets_resource_p (trial, &opposite_needed, 1)` — i.e., the insn must not set a resource needed at the opposite thread (the branch target).

Our candidate: bnez v0, 4d48 (target = epilogue). Thread direction likely fall-through (not likely true?). `li v0,128` sets v0. Is v0 needed at opposite_thread (4d48)? At 4d48: lw ra, addiu sp, jr ra. So no v0 needed → the condition passes → it can move li into the delay slot. Target's version: why not? Because the empty asm insn came first — asm insns: `insn_sets_resource_p` for an asm with no outputs sets nothing, references nothing? Hmm. But `may_trap_p`? Or `eligible_for_delay` fails for asm? Actually maybe the asm insn itself is not eligible for delay and also `lose` logic: if the first insn can't be placed, `lose=1`, and for a non-owned thread the search stops. Wait, `lose` is set when the insn conflicts; then `(! lose || own_thread)` stops the loop. The asm insn: `insn_sets_resource_p (trial, &needed, 1)`? The asm is volatile; in the RTL, `__asm__ __volatile__("")` with no operands becomes an `asm_operands` insn. `mark_referenced_resources`/`mark_set_resources` might treat asm as setting/using memory? Not for empty asm without "memory" clobber.

Hmm — actually maybe the difference is elsewhere: with the asm, reorg's `stop_search_p`? No.

Wait — maybe with the asm the *order* is: asm insn, then li. The asm insn can't be moved (`eligible_for_delay` false for asm? or `may_trap_p` true for asm?), so `lose=1` and the search stops → slot unfilled → nop. That's the mechanism.

So to reproduce lever-free, we need the first insn after the branch to be ineligible for the delay slot or to conflict. An insn that sets a resource needed at the branch target. What resource is needed at 4d48? ra and sp (the epilogue). So if the first insn after the branch sets ra or sp... not expressible in C here.

Alternatively, `may_trap_p`: an insn that can trap can't go into the delay slot if the branch might not be taken... condition: `! insn_sets_resource_p (trial, &opposite_needed, 1) && ! may_trap_p (pat)`. A memory load can trap → may_trap_p true. So if the first insn of the if-body were a LOAD, it can't be moved into the delay slot → nop.

In the target, the if-body is `D_80078EBF = 0x80;` = li + lui + sb. First insn li. Could we arrange the body to start with a load? E.g.:

```
if (0x80 < D_80078EBF) {
    D_80078EBF = (D_80078EBF & 0) + 0x80;  // no
}
```

Hmm, we need a real load that's part of the semantics. There is none.

But wait — maybe we don't need to fill the delay slot with nop by blocking; maybe we can restructure so the branch itself changes. Let me consider: what if we make the comparison a `if (D_80078EBF >= 0x81)`? Same code.

Another thought: what if the `li v0,128` is replaced by a value already in a register? The target has `li v0,128`. Same.

OK, alternative approach: prevent `fill_eager_delay_slots` from taking the insn by making the thread direction opposite. `fill_eager_delay_slots` is called with likely direction. If the branch is "likely taken" vs "likely not", the thread from which insns are taken changes. In the target, the delay slot is nop, so nothing taken. If we make the insn after the branch be on the opposite thread (the branch target), then... no, the target is the epilogue.

Hmm, what determines `thread_if_true`? reorg uses branch probability from REG_BR_PROB or heuristics (mostly "guess the branch direction" via `mostly_true_jump`). For our bnez, the fall-through is the if-body. If gcc thinks the branch is likely taken, it would take insns from the target (epilogue) — which would be a different fill. Since the target has nop, no fill at all.

Let me consider the structure differently. The asm also might affect the CFG/EBB so that the if-body is a separate basic block and reorg's thread logic differs. Actually! The asm creates an additional insn; but more importantly maybe it affects cse/flow so the `j 4d48` after the body is a simplejump... hmm.

Let me just experiment. Cheap tries:

T1: do-while(0) around the clamp body.
T2: `add = 0x80; D_80078EBF = add;` (add temp).
T3: `if (D_80078EBF >= 0x81) { D_80078EBF = 0x80; }` — same likely.
T4: `if (0x80 < D_80078EBF) { D_80078EBF = 0x80; }` with D_80078EBF declared volatile? That's a lever (launder? volatile is a barrier-ish lever — not allowed; "no new lever of any kind").
T5: Reorder the clamp before the store? No.
T6: Make the body a compound assignment: `D_80078EBF |= 0x80;`? Wrong value.

Hmm wait. Let's reconsider the actual semantics: D_80078EBF is u8, add ∈ {3,6}. After adding, if > 0x80, set to 0x80. The target code: `lbu v0; addu v0,v0,v1; sb v0; andi v0,v0,0xff; sltiu v0,v0,129; bnez v0, skip; li v0,128; ... sb`.

Note: the compiler kept v0 as the value after the store (andi 0xff, sltiu 129 = `v0 < 129` i.e. `!(v0 > 0x80)`). Branch bnez v0 → skip.

What if we write the condition as `if (D_80078EBF > 0x80)` — D_80078EBF is u8, the load+add result. Same.

Now: the delay slot `li v0,128`. To stop it, we could make `li v0,128` not the first insn of the body: e.g., body computes something else first. If the body were `{ s32 z; z = 0x80; D_80078EBF = z; }`, the li goes to v0 or v1 and is still first.

What if the stored value is `add`-derived such that a computation comes first, e.g. `D_80078EBF = add + 0x7D;` where add is 3 or 6? Then value = 0x80 or 0x83 — wrong.

What about `D_80078EBF = 0x80;` written as `D_80078EBF = (u8)(0x100 >> 1);`? constant folded.

Hmm. What if the clamp value comes from a variable that is live across the branch? E.g. `add = 0x80;` *before* the branch and `D_80078EBF = add;` inside. Then inside the body the first insn would be... the store sequence `lui at; sb v1` (add in a register). The lui can be moved into the delay slot (sets at, not needed at epilogue, no trap). Then delay slot would be `lui at` and code shifts. Not the target.

Unless the value is in a register that IS needed at the branch target. What registers are live at 4d48? ra, sp. Not accessible in C.

Hmm, but `may_trap_p`: a load is the natural blocker. Is there any load we can put in the if-body first that the target also has? The target's if-body starts with li. So no.

OK, so maybe blocking is the wrong angle. Reconsider: maybe the real target shape isn't "reorg left nop because asm blocked"; maybe with the asm, reorg *did* fill the slot with the asm (which emits nothing) — same bytes. Either way the result is the same nop.

Can we get a nop in the delay slot by making the branch unconditional-ish? No.

What if we make the `j 4d48` a *different* target so the branch's delay slot can't be stolen from the branch target? The "steal from branch target" path (line 3105) applies when the scan is stopped by a simplejump to the same target. In our case: bnez → 4d48; fall-through ends with `j 4d48`. This is exactly the case where reorg steals the insn at the branch target into the delay slot and redirects both jumps. The insn at 4d48 is `lw ra,16(sp)`; it sets ra, which IS needed at... hmm, `opposite_needed` for the bnez is the live regs at 4d48 — ra, sp. So `lw ra` sets ra which is needed → conflict → not stolen. Then what fills the delay slot with `li v0,128`?

Wait, I mis-read the disassembly. Let me re-check: mine at 4d24 `bnez v0,4d44`, 4d28 `li v0,128`, 4d2c `lui at`... and target at 4d24 `bnez v0,4d48`, 4d28 `nop`, 4d2c `li v0,128`.

So in mine, li is at 4d28 (delay slot) and the rest follows at 4d2c. That means the delay slot was filled by moving li forward — a forward fill. Since for conditional jumps fill_simple_delay_slots doesn't do forward fill (target != 0 → the `if (target == 0 && ...)` fails; then resources are marked and the loop continues until a label/barrier; then the steal-from-target logic runs and fails), the fill must come from fill_eager_delay_slots. In eager, THREAD is the fall-through (likely direction) and it moves the first insn (li) into the delay slot if it doesn't set anything needed at the opposite thread. Opposite thread = 4d48 (epilogue), which needs ra/sp. li sets v0 → OK. So yes, eager fill moved li into the slot.

Now, how to make eager not fill:
- `! insn_sets_resource_p (trial, &opposite_needed, 1)` must fail, or `may_trap_p(pat)` must be true, or `lose` set.

`may_trap_p(pat)` for the first insn of the body. If the first insn is a load → may_trap_p true → lose → nop! But the target's body starts with li.

Hmm, but wait: could the target's body start with a load in some other C spelling that produces the same instructions? The target body is `li v0,128; lui at; sb`. No load.

Alternatively `opposite_needed` could include v0 if v0 were live at the epilogue. Not possible.

What if the branch direction heuristic flips: then THREAD = the branch target (epilogue), and eager takes insns from the epilogue thread into the delay slot. That would be wrong for us.

OK so maybe this item is a genuine WALL (dbr-delay-fill) — but let me not give up; the barrier trick worked. Maybe there's another C shape that creates a "lose" in the fall-through thread before li. E.g., if the body's first insn references a resource set by an insn between the branch and it? There is nothing between.

Wait — actually there's another angle: `lose` is set if any insn in the thread conflicts, and the loop continues while `own_thread`. The thread starts at the fall-through; the first insn is li. If we can put an insn BEFORE li in the thread that conflicts, then lose=1 and... for own_thread, the loop continues (it only stops if !own_thread). But `lose` prevents filling later insns? Let's look at the winner path: after `lose` is set, `if (lose && ! own_thread) break`... Let me read further.

Actually let me read the rest of the loop to see how `lose` is used.
