---
ts: 2026-11-06T11:41:12Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG29
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_NCkLNwfLSVHVNFsNGrhW
---
All ≥81. v07 (Blk8 copies adjacent after stores) = 85. Best 81.

Total tries: 30 + 12 + w1,w2,w3 = 45 scored tries. Time now ~04:47? Let me check and then wrap item 1 as WALL.

Actually wait — before giving up, let me reconsider one more idea that could create the WAR: what if the group A stores and the Blk8 copy share a destination struct, so the compiler's alias analysis... no, still no dependency.

What if the copy is written as `D_80126960 = *(Blk8 *)&D_80120210;` but the destination struct type is the SAME struct as a variable that's live? No.

Hmm, one more idea: use `volatile`? No, that's a lever.

Another: what if the function's temps are declared in an order such that the BLKmode copy's registers are allocated to the same pseudos? The BLKmode move uses two pseudo regs that get allocated; sched1 doesn't know.

I'm confident: WALL.

Let me check the time.
