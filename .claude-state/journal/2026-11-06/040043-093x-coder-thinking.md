---
ts: 2026-11-06T11:00:43Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG28x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_rUEA2fqgNyBbVgzc9xC9
---
Block 2 is from insn 32 to 140 — the whole else block, including the barrier. So the barrier does NOT split the sched1 block.

So within block 2, sched1 produced the target order WITH the asm present. And my v_dw5 (do-while) produced a different order.

Let me look at the .sched dump for block 2 of the orig to see the insn order after scheduling. The dump prints the scheduled insns. Let me look at lines 7353+ around block 2.
