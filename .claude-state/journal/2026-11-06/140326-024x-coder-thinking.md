---
ts: 2026-11-06T21:03:26Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW49x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_GomKKXeJc8r2jOl7bFSs
---
The .lreg file contains RTL of many functions (the whole TU). The "Register 78 in 2" at line 140 is in the *first* function section? Wait, our function is the last in the TU? The dump is ordered by function; the first function dumped may be func_800CC... Let me find the section for func_800CC4E8: the earlier sed found ";; Function func_800CC4E8" and the register list. Line 140 is right after block 12 of *that* function... but hold on: our function has 8 basic blocks per the earlier output. The block 12 at line 136 belongs to the NEXT function? No: sed printed from ";; Function func_800CC4E8" to the next ";; Function", and it showed "8 basic blocks" then block 0..12? Wait it showed "Basic block 10", "11", "12" — inconsistent with "8 basic blocks". So the sed range crossed into another function because the section header is ";; Function" only at the start; the "8 basic blocks" line appeared before block 0..12? That means the register/block listing after "8 basic blocks" is wrong... 

Hmm, actually the format: for each function, it prints ";; Function name", then register info, then "N basic blocks", then block list, then ";; Register N in M." lines, then the RTL insns. The block list I saw (block 0..12) with 8 basic blocks is contradictory. Unless the sed range includes the *next* function's block list because the next function's header line ";; Function ..." came later. Let me redo: find line numbers of all ";; Function" lines and inspect around our function.
