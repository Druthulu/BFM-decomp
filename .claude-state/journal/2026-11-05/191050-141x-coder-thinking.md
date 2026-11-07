---
ts: 2026-11-06T02:10:50Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG18x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_DjX2YZvqThgO6Ilb6k6p
---
Reproduced in the mini TU: the vA trailing jump (uid 368) is gone after the first jump pass. Now gdb the mini TU and find the delete. UIDs identical (the mini dump shows the same UIDs: 366 store, 371 note, 374 label).

Let me gdb miniVA.i with the breakpoint on delete_insn, condition code==28 && uid==368, and print the backtrace.
