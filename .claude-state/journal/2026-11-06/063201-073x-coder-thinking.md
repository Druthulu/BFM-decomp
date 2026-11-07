---
ts: 2026-11-06T13:32:01Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO02
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_4NtUnGQeMTDe5Notzt7x
---
Now it's clear: after cse, insn 291 is the real `a1 = fp+16` (early, right after a0), and insns 308/310 are NO-OP moves `a0 = a0` and `a1 = a1` inserted at the call site (cse's copy propagation leaves the hard-reg copies; they're no-ops deleted later by the final jump pass).

So at sched1, both the real addiu (291) and the no-op move (310) exist! The no-op move 310 is `(set (reg a1) (reg a1))` with REG_EQUAL fp+16. Then sched1 schedules: it placed 310 at the call site and apparently 291...? In the sched dump, insn 291 wasn't listed in block 17's ready list (the list had 288, 293, 295, 297, 299, 302, 305, 310, 312...). Wait, the ready list DID include insn 288 (aa) but not 291! Hmm, the ready list at the start listed: 389, 225, 228, 230, 233, 237, 239, 241, 243, 246, 249, 252, 254, 257, 261, 263, 265, 267, 270, 273, 276, 278, 281, 288, 293, 295, 297, 299, 302, 305, 310, 312, 315, 318, 321, 324, 329, 332, 335, 338, 343, 348, 351, 354, 361, 363, 365, 370, 371.

No 291! So insn 291 was deleted before sched1. Which pass deletes it? The no-op move deletion happens at the final jump_optimize (after sched2)... but there's also `delete_dead_from_cse` (called after cse_main) and jump_optimize calls in between (line 2870: jump_optimize(insns,0,0,0) if tem). Hmm, jump_optimize with noop_moves=0 doesn't delete no-op moves.

Wait, insn 291 was `(set (reg/v:SI 5 a1) (plus fp 16))` after cse (the real addiu). And 310 is `(set (reg:SI 5 a1) (reg/v:SI 5 a1))`. Hmm, two sets of a1: 291 (the real one) and 310 (a no-op). At sched1, 291 is gone and 310 remains! So some pass deleted 291 and kept 310. Probably `delete_dead_from_cse` (it deletes insns whose value is dead? no) or the second jump_optimize with noop_moves=0...

Hmm, actually maybe cse2 (the second cse pass, before sched1) removed 291 as dead (since a1 is re-set by 310 before the call, 291's value is dead) — yes! delete_dead_from_cse or dead store elimination: 291 sets a1, then 310 sets a1 = a1 (same value), so 291 is dead? But 310 reads a1 (the value 291 wrote)! `a1 = a1` uses a1. So 291 isn't dead... unless cse2 knows 310 is a no-op and deletes it, keeping 291. But the sched dump shows 310 with the addiu and 291 gone.

Confusing. Whatever the mechanism, the net effect: after cse, the value is materialized at the call site (310) instead of early (291).

KEY: in the ORIG (with the asm barrier), the barrier sits between 291's position and the chain. Would cse2 still do this? Let me check the orig cse dump to see if 291 survives.

Actually, the difference between orig and nobar might be exactly here: with the asm, cse2's dead-code elimination doesn't remove 291? Let me look at the orig .cse dump.

Let me dump orig.i.cse around the same place.
