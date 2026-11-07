---
ts: 2026-11-06T08:48:58Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG24x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_9iP0LMMFd6X7OzeIuXgy
---
The scratch TU at p3 has no keepalive asm at 5878 (good, c1), but it does have a launder asm at 4316 (another function in the TU, irrelevant).

But the RTL dump shows `(insn 265 128 130 (use (reg/v:SI 78)) -1 (nil))` in the else block. Where does that come from? Interesting: maybe from the C code `val = nudge;` in the else — no. Let me look at the full else-block RTL in the .cse dump before insn 132... the cse dump doesn't show insn 265; the combine dump does. Wait, the combine dump at 30990-31014 shows insn 124 (the if copy), jump, label 128, then insn 265 (use reg78), then notes, then insn 134 neg reg77.

Hmm, insn 265 with a USE of reg78 appears in the combine dump but not in cse — combine's dump prints the RTL *during/after* combine, and an insn `(use (reg78))` could be a leftover from... Hmm, actually combine's dump includes the RTL after the whole pass. An insn `(use reg)` alone is unusual.

Hold on: maybe this `(use)` comes from the *asm* in a different place... no.

Wait, maybe I'm looking at the wrong function? Line 30694 is ";; Function func_80187988" in combine. Yes.

Hmm, the `(use (reg/v:SI 78))` at insn 265, right after label 128 (else block) — in GCC 2.7.2, an asm with only register inputs gets represented as `(asm_operands ...)`; but a plain `(use)` insn is what `expand_asm` produces for... Actually, I recall GCC's `expand_asm_operands` emits `(insn (asm_operands ...))` for volatile asm and for non-volatile asm with no outputs it may emit a `(use)` insn? Hmm.

But c1 has no asm. Unless the scratch TU p3 is not c1... The scratch has two `val = nudge;` at 5875 and 5877 and no keepalive. So it's c1. Yet the combine dump shows a `(use reg78)`.

OH WAIT. I bet this is from the *sequence*: `(insn 265 128 130 (use (reg/v:SI 78)))` — insn 265's prev is 128 (the label) and next is 130. In the cse dump, insn 130 was a note and insn 132 the copy. In the combine dump, insn 265 is a NEW insn (number > 265?) inserted... no, insn numbers 265 suggests it was created by combine? Hmm, insn 265 > 134, so it's an insn created by combine (combine creates new insns with higher numbers). But combine would delete, not add a use.

Actually — combine's dump is printed with `-dc` after combine, and it may show `(use)` for a *dead* set it kept? Hmm.

Wait, maybe I misread: maybe this combine dump section is from a different function or the dump shows the RTL *before* combine for the next function. Let me look at the lines before 30694: the combine dump prints ";; Function X" then ";; Combiner statistics" then the RTL. The RTL after combine. And combine's statistics for this function: 65 substitutions, 7 successes.

The merged insn 134 `(neg reg77)` with REG_DEAD reg77 — that's the merge. And the `(use reg78)` at 265... could be the if-branch's copy? No, 124 is that.

Let me look at the full function RTL in the combine dump from 30694 to the end, specifically the region around the if/else. Actually the key question: why did combine merge 132+134? Because insn 132 (copy reg78=reg77) is used only by 134. To block it, reg78 must have another use between 132 and 134, or 132 must be in a different block.

But here's the thing: in the cse dump, insn 132 and 134 are in the SAME block (label 128 ... no branch between). So combine merges. The asm version presumably had `(insn (use reg78))` between 132 and 134 — exactly the blocking use! And that's what the target compiled from.

So the real C needs a use of val between the copy and the negation, i.e., a `(use)` RTL insn with no code. What real C generates a `(use)` insn with no code? 

Hmm! A `(use)` insn in RTL comes from... In GCC 2.7.2, `emit_insn (gen_rtx (USE, VOIDmode, reg))` is emitted for certain constructs. One known source: an `asm` — but banned. Another: **`(void)` casts**? No.

Another known source: the `__attribute__((...))`? No.

Actually, a `(use)` insn with no code can come from a **`volatile` read**? No, that's a load.

Hmm, what about a *variable that is only read* — flow might keep a `(use)` for debug? No.

Wait — maybe the `(use)` insn 265 is actually from the **`(s32)param_1` cast in the call**? No, that's elsewhere.

Let me look at the combine dump around the if block (insns 118-136) fully to understand. And also find where insn 265 appears in the cse2 dump (post-combine, post-cse2) to see if it survives. Let me print the combine RTL region from 30900 to 31030.
