---
ts: 2026-11-06T12:56:02Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO01x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_JTOcMNQPQan1X1eQyNsB
---
Now append moves.md lines for items 1 and 2. Format: `kind | func | MATCH: move / WALL tag — mechanism (O01x)`.

Item 1: `barrier | func_80186CE0 | MATCH: do{}while(0) around the fifth-word store (C0535) keeps the u16 RMW adds out of the t load-delay slot (target nop) (O01x)`

Item 2: `barrier | func_8018BCD4 | WALL sched1-const-pair-hoist — sched1 lifts the 0x64808080 lui/ori pair above the sh y store in the join block; 32 lever-free bodies, best 2 (O01x)`

Also write notes.md in each dir. Let me do the moves appends (one command each, or combined — appending to moves.md is allowed). I'll do them in one command with two printf's.

Then notes.md for each item.

Then item 3: func_80180EC0 (319 ins, big).
