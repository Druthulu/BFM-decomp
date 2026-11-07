---
ts: 2026-11-06T13:33:20Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO02
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_TBThAOmvuXbfQPgaizvM
---
In orig cse2 (before cse2 runs), insn 291 real addiu, 293 asm, ..., 312 no-op. Same as nobar's cse2 except the asm.

So cse2 runs and in nobar it deleted 291 & folded 312. In orig, the asm prevented it. Why? Because cse's `invalidate_from_clobbers` for the asm: the asm has `(clobber (mem:BLK (scratch)))`. Hmm, but the equivalence is a1 = fp+16, a register value.

Ah wait — maybe it's not cse2 but `delete_dead_from_cse` (called after cse_main at line 2867 for cse1 only; for cse2 at 2926 no delete_dead). Hmm.

Let me look at cse_insn's handling of ASM_OPERANDS: search for "asm" handling that invalidates the table. Let me grep "invalidate" in cse.c.
