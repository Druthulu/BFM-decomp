---
ts: 2026-11-06T13:32:53Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO02
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_FFSegecuQDecgJbCio9J
---
So insn 291 exists in the loop dump but not in the sched dump's function region (only line 28272 which is another function). The sched dump is written after sched1; sched1 is the pass that... does it delete insns? No. But between loop and sched1 there's cse2 (line 2915-2929) and jump_optimize. The cse2 dump (written before cse2) still has 291. So cse2 or the subsequent jump_optimize deleted it.

Note in nobar.i.cse2, insn 288 is `a0 = reg74+4` (already combined into an addiu) and 291 is `a1 = fp+16`.

Then cse2 runs. Since 291 sets a1 and later 312 sets a1 = a1 (a no-op with REG_EQUAL), cse2 might delete the no-op and keep 291... or keep the no-op and delete 291 (if it considers 291 dead because a1 is re-set... but the no-op reads a1).

Actually, `a1 = a1` is a no-op; cse2's canon_reg may replace the source `a1` with its equivalent `fp+16`, making the insn `a1 = fp+16` (a real addiu) and then insn 291 becomes dead (a1 is overwritten before use) → deleted by delete_dead_from_cse. That's exactly the swap: 291 deleted, 312 becomes the addiu.

In the ORIG, the asm at 293 blocks cse2's propagation of the REG_EQUAL across it? No... the asm is between 291 and the chain. cse2's REG_EQUAL for the no-op at 312 comes from the call's use of a1... 

Hmm, why would the asm prevent it? cse's equivalence: at 291, a1 = fp+16 → record a1's value. Then the asm clobbers memory but not a1. Then at 312, `a1 = a1` → cse would replace with `a1 = fp+16` (same thing). Then 291 is dead? Only if a1 is not used between. But it IS used? No — a1's only use is the call at the end. So 291 is dead after cse2 rewrites 312.

Unless cse doesn't propagate a1's value across the asm because the asm is a "clobber all registers" barrier! YES: the asm in sched_analyze clobbers all regs (for scheduling), and for CSE, `cse_insn` treats asm as... Let me check cse.c's handling: an asm with a memory clobber may invalidate the register equivalence table? In cse.c, `invalidate_memory` on a store. For an asm, cse's `cse_insn` calls... hmm.

Empirically: the barrier prevented cse2 from propagating a1's value to the call site, keeping the real addiu at 291. That's the mechanism!

So a real-C construct that makes cse2 unable to propagate a1 across the chain. What invalidates a register equivalence in cse? A call! A call clobbers caller-saved registers — cse invalidates the equivalence table at a call for caller-saved regs. But a1 ($5) is caller-saved... and there are calls (rand) BEFORE 291, but not between 291 and 312.

If there were a call between 291 and 312, cse would invalidate a1's value → the no-op at 312 couldn't be folded → 291 survives. But a call adds code.

Alternatively, a *set of a1* between 291 and 312 would kill it — but that adds code.

Hmm, what about `volatile`? A volatile read of a variable writes... 

What invalidates a register's known value in cse? Any instruction that sets the register (clobber). Also a "memory clobber" asm invalidates memory, not registers. Hmm, but the asm in orig has `(clobber (mem:BLK (scratch)))` — only memory. So why did it prevent the a1 propagation?

Let me verify that it did: look at the orig's cse2 dump — does it have the same two a1 sets (291 real, 312 no-op) or did cse already fold? In the orig cse dump (after cse_main), we saw 291 (real) and 312 (no-op). Same as nobar. So after cse_main both are the same.

The difference must be in cse2 (after the loop pass). Let me check orig's cse2 dump for 291 and 312.

Actually, wait. In the orig's cse dump, insn numbers shifted: 310/312 vs nobar 308/310 (because of the extra asm insn). Both have the real addiu + no-op. So the state is the same except for the asm.

Then cse2 runs. In nobar, cse2 folded 312 into the addiu and deleted 291. In orig, presumably the asm blocks the propagation because the asm's clobber of mem:BLK (scratch) — cse's `invalidate_memory` is for memory; but the equivalence of a1 is a REG_EQUAL... 

Hmm, cse's table records `reg_eqv_table`: a1 = fp+16. At the asm, cse_insn processes the asm: for an asm, it calls `invalidate_memory` and also, importantly, in `cse_insn` there's code: "If this is an asm, invalidate everything" — let me check cse.c. There's a notion: `if (GET_CODE (insn) == INSN && GET_CODE (PATTERN (insn)) == ASM_OPERANDS) { invalidate_from_clobbers; ... }`. The clobber is mem:BLK — invalidates memory.

But the key: cse's substitution of `a1` at 312 uses the reg_eqv_table entry for a1. If the asm's processing clears the register equivalence table (because the asm might change a1? The asm has no explicit reg clobber, but cse might treat an asm as clobbering all registers conservatively — in cse.c there's `if (asm) ... invalidate_regs?`).

Let me check cse.c for asm handling.
