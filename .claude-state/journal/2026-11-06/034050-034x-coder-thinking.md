---
ts: 2026-11-06T10:40:50Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG28x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_eMc5PUfmwAIZPccVID2o
---
Second use is exactly our case: "barrier dropped: do { t = D_801A9A88[a1*5]; sp10[4] = t; } while (0); keeps the following u16 adds out of the t load-delay slot". So wrapping the load statement (and maybe the following store) in do-while(0) splits the block and keeps the load late.

Let me try wrapping `t = unkC4;` in a do-while(0). But careful: the do-while(0) around a single statement creates a block boundary after? In the target, the load is after the unk5C store and before the unk58 store. If I wrap just `t = ...` in do{}while(0), the block split occurs around it. Hmm, but does the do-while(0) block become a separate basic block? `do { S } while(0)` compiles to a loop note; loop.c removes it (loop optimization on a 1-trip loop). The effect on cse1's EBB: the NOTE_INSN_LOOP_BEG/END splits the EBB.

Let me just try: wrap `t = ...;` in do-while(0).
