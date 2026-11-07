---
ts: 2026-11-06T21:56:01Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM3x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_BrdPp6Ozwywt7GCjSPMZ
---
"wrap the two copy statements in do{}while(0) ... splits cse1's extended basic block, so the copies are not merged/re-ordered there and sched1 sees them in source birth order."

So do-while splits the EBB at cse1 — meaning jump1 does NOT merge when the loop body is non-trivial? In our w6/w7 it didn't work.

Hmm, maybe the EBB split works but the issue is combine (which runs on basic blocks after flow). Let me actually verify with a dump whether the do-while kept the block boundary in w6.

Let me dump w6 and check the .combine for a code_label between the copy and the compare.

Actually — maybe the copy is being deleted by a different mechanism: **local-alloc coalescing** (the copy's source dying?) or **flow**. Let me check the final asm for w6 (does it have a move? no, 55 ins, beq a0,v0).

Let me dump w6 and look at the RTL after combine and after lreg.

Actually, let me look at the lreg dump for w6 to see if there's a copy.

Alternatively, check the .flow dump: if the copy `iv2c = iVar2` exists there, then it's combine. Let me dump w6.
