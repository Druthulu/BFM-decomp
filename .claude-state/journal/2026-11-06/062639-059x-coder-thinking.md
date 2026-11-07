---
ts: 2026-11-06T13:26:39Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO02
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_ruVeUjZWIhAHb3fyOWRf
---
This is the final RTL listing after sched1 (the dump shows the scheduled order). The block 17 (from 221 to 371) is the do-loop body. I need to find insn 218 (addiu sp+16) and the s0 chain within block 17.

Let me search for "const_int 16" lines 25571, 25584, 25604 — those are at the end of the dump (after the final listing starts at 25549?). Hmm, the listing after the sched report is the *scheduled* RTL. The block 17's insns are numbered 221-371. Let me read from 25650 onward to see the scheduled listing.

Actually, the dump structure: for each block it prints the ready lists, then after all blocks, it prints the final insn chain. The listing starting around 25549 is the function's RTL after scheduling.

I want to see the sched decisions for the loop body block (block 17, head 221, end 371). The ready lists at the top (lines 25500-25520) are the tail of block 17's T-26..T-49. I need the beginning of block 17's ready list, which is earlier. Let me find "basic block number 17".
