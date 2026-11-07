---
ts: 2026-11-06T17:22:07Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO05x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_TLZDWBdsIvupftCaWQvY
---
o1 (drop the p2 store): 208 ins — can't tell if the mask moved (score 70 due to missing instructions). Let me check o1's diff for the mask's register... Actually let me not spend more; the diagnostic isn't decisive without inspection.

Time 16.3 min. Let me finish with a couple more tries, then record.

Let me try one last promising idea: the target's mask is in t6. Maybe if the mask's *first use* is before the p2 store (insn 76) in the chain, the mask would be born earlier and take t6 before the constant is allocated? The allocation is priority-based, not chain-based, so no.

Alternatively, maybe the answer is that the mask must have FEWER refs so its priority drops below the constant's, letting the constant take t6 first... no, that's what happens.

We need the mask's priority HIGHER than the constant's. The mask: refs 13, life 61 (flow) → pri 2.56. Constant: refs 2, life 393 → 0.02. The mask's priority is already much higher, yet it got t7 — so priority isn't the deciding factor; the *conflict* is: the constant is allocated FIRST despite lower priority? That can't be unless the first (suggestion) loop allocated the constant to t6.

Let me check the suggestion loop hypothesis by looking at what suggestions exist. The constant `(set (reg 117) (const_int))` — no copy. Hmm.

OR: the mask is allocated t7 because t6 is in `used` via `regs_live_at` for the mask's live range: a HARD register t6 might be live there! Which hard reg is used explicitly in the RTL? The GTE macros use $12,$13,$14 (=t4,t5,t6) in asm! The asm volatile clobbers "$12","$13","$14" — those are t4, t5, t6! 

YES! The gte_SetRotMatrix/TransMatrix asm clobbers $12,$13,$14 (t4,t5,t6). If those clobbers are live across the mask's live range... The asm insns are at the top (insns ~13-14?), and the mask's live range starts at 16. The clobbered regs t4,t5,t6 are marked live at the asm insns, not at 16.

But wait — the clobbers are at the beginning; the mask is born at 16 (after the asm). So t6 should be free after the asm.

Hmm, but the *constant* 0x8E is at insn 5-6 — BEFORE the asm? The asm (gte) is at insns 13-14. The constant at 5-6 is before. Hmm.

Actually, look at the target asm: the gte macro is inlined at the very beginning (lw/ctc2 with t4,t5,t6), then the rest. The mask (t6) is materialized at insn 16 — right after the gte block. In the target, t6 is free after the ctc2s.

In mine, the mask at insn 16-17 is in t7 and the constant at 5-6 in t6. The constant at insn 5-6 is BEFORE the gte block (13-14)? That seems odd: the constant is hoisted above the gte asm. Then its live range spans the asm, which clobbers t6! A value in t6 live across an asm that clobbers $14 (t6) would be destroyed!

Hold on: the asm clobber list is "$12","$13","$14" = t4,t5,t6. If the constant is in t6 and live across the asm, the clobber would corrupt it. But the asm is at 13-14 and the constant's use at 76 — so the constant IS live across the asm. GCC would not put it in t6 if the asm clobbers t6... unless the clobbers are only marked at the asm insn and the allocator respects them.

In the target, the constant is in t7 (not clobbered) and the mask in t6 (born after the asm) — consistent!

In mine, the constant is in t6 — live across the asm that clobbers t6?! That would be a miscompile... unless the constant is *rematerialized* after the asm (its def at insn 5 is before the asm, but maybe the allocator placed it there knowing...).

Hmm, wait: maybe the instruction numbering in the final asm: insn 5-6 is the constant, insn 13-14 the gte asm? Let me look at the actual mine asm start.
