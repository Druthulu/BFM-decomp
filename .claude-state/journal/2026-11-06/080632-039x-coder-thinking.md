---
ts: 2026-11-06T15:06:32Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO03
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_B4nEKe2pKWAojLF8Tifi
---
cse's qty_const is per extended basic block (cse invalidates at basic block boundaries unless it's a "simple" block?). In 2.7.2 cse, qty_const is set when a reg is set to a constant in the block. So `s0 = 0; a0 = s0 << 10;` in the same EBB → folded.

So splitting the EBB between them should stop cse. d4 inserted do-while around the init → that adds a label at the loop end; but does cse see the init and shift in different blocks? cse works on extended basic blocks; a do-while(0) with a label creates a basic block boundary. But the score was 5, not 2 — meaning it made things worse/different. Let me look at d4's disassembly to understand.

Let me dump d4. Use --keep.

Actually, maybe better: the classic C0535 move is `do { } while (0)` — an *empty* loop — which "splits cse1 EBB" (creates a label with no code). An empty do-while(0) might be eliminated entirely before cse though... C0535 says it splits cse1 EBB. So insert `do { } while (0);` between `s0 = 0;` and `a0 = s0 << 10;`? But an empty loop with no side effects may be removed in the front end. Hmm, C0535 says it works for sched1-birth-order. Let me read cookbook C0535.
