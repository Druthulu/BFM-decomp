---
ts: 2026-11-06T15:43:34Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO04x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_2bTo75moxpINNOPHCz1I
---
All 9 — the difference is elsewhere (the constant-load register/position). Hmm, maybe the diff at 104-115 is not about n at all. Let me look at the actual sched order in the dumps to see what the launder changes.

Wait — all variants scored 9, including f3 (dead-reset). So the diff isn't influenced by n's 2nd set? Let me check the diff of the target vs mine more carefully: it's `lui v1; lw v1; nop; addiu v1,v1,500` vs `lui v0; lw v0; nop; addiu v0,v0,500` and the mult uses a2,v1 vs a2,v0. So the only difference is which register holds the constant and the exact schedule slot.

Hmm, since the whole function is 311 insns and score 9, maybe the *order* of a few insns differs.

Wait, maybe the launder's removal caused the mult's operand to be different: target `mult a2,v0` where v0 = the constant (D+500) and a2 = n. Mine `mult a2,v1`. And in mine, the load chain is placed at 88c-898 (before mflo at 89c); in target at 898-8a4 (after the addiu a2,v0,8 at 894). So the launder moved n's addiu *before* the constant chain.

The launder is `"=r"(n)` — an output constraint on n. This creates a REG_DEP_OUTPUT dependency that changes sched1's priority for the addiu? Actually the asm is a separate insn; the addiu (n=q+8) is followed by the asm (set n = asm(n)). In target's machine code, there's no asm insn (it's zero-byte). The sched1 ordering: the asm insn is a separate instruction; sched1 schedules around it. The asm's presence may change the ready-list priorities: the asm insn has to come after the addiu, and the constant chain is independent — sched1 chose to put the constant chain after the addiu because of the asm's scheduling effect (the asm is a barrier-ish insn that delays).

Hmm! Maybe the asm acts as a scheduling barrier in sched1 (ASM insns can't be moved). Since sched1 schedules a block and the asm sits between the addiu and the mult, the addiu must be scheduled before the asm, and the constant chain... 

So the real-C replacement needs to influence the schedule similarly. Since all my variants still score 9, maybe the register difference (v1 vs v0) is a global-alloc effect of the asm insn (which takes a register?). Hmm, an empty asm with "=r" ties a register.

Let me look at the dumps: compare the .sched (sched1 output) and .lreg/.greg between orig and a1. Actually the .s file (final asm) from the dumps: `o4.s` vs `a4.s`. Let me diff the two .s files for this function.
