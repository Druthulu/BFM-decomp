---
ts: 2026-11-06T04:46:49Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG21
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_BH2CZlqTEus7p2lXRprk
---
Wait, the block at 3080 is inside the loop after the `if (target == 0 && ...)` — meaning for a conditional jump (target != 0), the insn is NOT taken into the delay list there; instead resources are marked and the loop continues. So for conditional jumps, the forward scan does NOT fill directly — it only accumulates resources until it hits a label/barrier or a jump. Then, if the scan is stopped by an unconditional jump (`trial` is JUMP_INSN and simplejump), it tries to steal the insn at the branch target and redirect.

In our case: after `bnez v0, 4d48` comes `li v0,128` ... then `j 4d48` (simplejump to the same target). The forward scan passes li, lui, sb, then hits the `j`. Then the "steal from branch target" logic kicks in: next_trial = insn at the target of j = 4d48 (lw ra). It checks resources... but the target insn is `lw ra,16(sp)` — needed at the branch target? Hmm, wait, that logic would copy the target insn into the delay slot and redirect the j to a new label after it. That would fill the bnez's delay slot with a copy of `lw ra` and redirect... but that would change the code. Actually in our candidate, the bnez's delay slot got `li v0,128`, not a copy.

Hmm wait. Let me re-read: mine has bnez at 4d24 with delay `li v0,128` at 4d28. But the code then continues lui/sb/j. So the li at 4d28 is the delay slot and it was NOT removed from the fall-through? No — in MIPS delay slot semantics, the insn at 4d28 executes as part of the branch. The fall-through continues at 4d2c with lui. So li v0,128 is only in the delay slot (executed always), which is fine because v0 is dead at 4d48.

Which path filled it? For conditional jump, the direct fill path requires `target == 0`, so no. It must be the backward scan? No... Actually wait: maybe it's `fill_eager_delay_slots` (the second call at 4171 with non_jumps_p=0). That function handles conditional jumps and tries to fill from the target. Let me read fill_eager_delay_slots.

Actually the key question isn't the exact pass; it's how to prevent it with real C. Let me check `fill_eager_delay_slots`: it takes the insn at the branch target and moves it to the delay slot, redirecting the branch to after it. But here it moved the fall-through `li v0,128`, not the target.

Hmm, maybe it was `fill_simple_delay_slots` first call (non_jumps_p=1) that handles non-jump insns? No.

Let me reconsider: maybe the li at 4d28 is not in the delay slot of bnez but is a genuine fall-through instruction and the bnez's delay slot is... no, the delay slot is the next instruction. So li at 4d28 is the delay slot.

Actually maybe the branch got its delay slot filled by the *backward* scan? No, that moves an insn from before the branch.

Let me look at fill_eager_delay_slots.
