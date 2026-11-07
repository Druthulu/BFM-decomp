---
ts: 2026-11-06T12:27:15Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG31
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_r00lZhRyRXqPngKXjG0R
---
So in sched1, an asm (volatile or not — `code != ASM_OPERANDS || MEM_VOLATILE_P(x)`: for ASM_OPERANDS non-volatile, the branch is NOT taken; but the memory barrier here is `__asm__("" ::: "memory")` which is ASM_OPERANDS with a memory clobber — MEM_VOLATILE_P? A memory clobber sets MEM_VOLATILE_P on the ASM_OPERANDS? In gcc 2.7.2, `asm("" ::: "memory")` produces ASM_OPERANDS with MEM_VOLATILE_P set (the "volatile" flag comes from the clobber? Actually MEM_VOLATILE_P (x) for ASM_OPERANDS is set by `ASM_INPUT`... let me not dig).

Anyway, the barrier adds ANTI dependences from all registers last used before it, so insns can't move across it. That's a true barrier for everything.

But the do-while (loop note) should end the EBB in sched1: sched1 works on "extended basic blocks" computed in sched.c via `sched_before_next...`? Actually the EBB ends at a loop note (`NOTE_INSN_LOOP_BEG`?). Let me check how sched1 splits blocks: it uses `BLOCK_HEAD/BLOCK_END` from basic_block... no, sched.c's `schedule_block` is called per EBB found by `schedule_insns` which scans for `NOTE_INSN_LOOP_BEG`/`BLOCK`... 

Hmm, but q1 (do-while around the y store) gave 2 — no change. Maybe the reorder is by sched2 (after reload), which also uses EBBs but the loop notes are still there. So maybe sched2 ignores loop notes? Or maybe the reorder happens in `flow`/`reorg`/`dbr`.

Alternatively the reorder might come from `local-alloc`/`reload` picking a different order.

Let me test which pass: use cc1 dumps with -fno-... I can't pass flags, but I CAN dump the cc1 RTL and compare the two bodies' pass outputs. tools/cc1_dumps_tu.sh dumps per-pass RTL for a TU. Let me check its usage.
