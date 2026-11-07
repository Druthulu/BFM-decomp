---
ts: 2026-11-06T17:21:18Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO05x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_gHUuYgI1krMUZwSwSe3Z
---
Time 15.6 min. Need 4.4 more minutes. Let me run a couple more batches with different ideas, then finalize.

Idea: what if the mask's register is influenced by the *first* use's context? In the target's tail, the first mask use is in the p0 unk0 update. 

New idea: maybe I can get the mask into t6 by making the 0x8E constant *die earlier* — i.e., move its use before the mask's birth (insn 16). The constant's store is at insn 76. If the p2 packet were the FIRST packet, its store would be at insn ~5 and its constant would die early. But reordering the packets changes the target bytes.

Hmm, unless the target's packet order in the source is different from p0..p5 but sched1 reorders to the target's order? The target's packet stores appear in order p0..p5? From the target asm earlier, the packets are built in some order. The source order is p0..p5.

I'll do a final batch of 4 tries and then record the WALL at 20 min.
