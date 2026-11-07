---
ts: 2026-11-06T02:27:35Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG18x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_vKh1LQWv0I0nmTe9bAWg
---
This is a rabbit hole again. Given the score is 8 with a single nop missing, and moves.md lists many `dbr-delay-fill` WALLs, item 2 is likely a WALL. But let me try a couple more clever C shapes:

The delay-slot fill by reorg of an insn from the fall-through into a conditional branch's slot happens in `fill_simple_delay_slots` via `fill_slots_from_thread(insn, condition, fallthrough, ..., 1, ...)`. It walks the fall-through thread BACKWARD from the end of the thread? Actually the "thread" is the fall-through block; it takes insns from the END of the thread (before the jump). Hmm, no: for filling a delay slot, it takes insns that would execute *after* the branch on that path — i.e., the beginning of the thread. The function `fill_slots_from_thread` starts at `thread` and walks forward while the insn is safe.

The addiu is the first insn of the fall-through thread. reorg took it. To prevent: make it unsafe on the taken path. Conditions in fill_slots_from_thread: `if (GET_CODE (trial) == JUMP_INSN)`, `if (! eligible_for_delay(...))`, `if (sets_cc0_p)`, `if (reg_referenced_p (condition...))`? Let me grep the function body for the safety checks.
