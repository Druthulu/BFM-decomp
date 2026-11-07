---
ts: 2026-11-07T00:43:54Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cP1
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_FwMyj4UcRQFEXIGX046J
---
In the target's sched1 (with barrier): the block after the call has insns 53 (load val), 55 (the asm barrier), 58,61,64,67 (the stores), 70,72,75,77.

The trace: T-1: 81 (jump). T-2: ready list 58,61,64,67,72,77 → picks 77 (priority 2). T-3: 72 ... 75 (7f000001) → picks 75. T-4: 72 67 64 61 58 → picks 72 (priority 2). T-5: 67 64 61 58 70(7f000001) → picks 70...

Hmm, this trace seems to be listing in reverse (T-1 = first?). Whatever. The important bit: where's 53 and 55? Let me see more of the trace.

Actually, let me look at the target's final insn order in the .sched dump for the block.
