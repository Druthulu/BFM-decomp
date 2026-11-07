---
ts: 2026-11-06T12:07:27Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG28y
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_SsywznkUKL8nOoSUDxBh
---
`char two` also gives 2 (same as s8). Good. Still the store sink.

It's 05:07:23. Item 4 started ~04:56. 11.5 min. Need ~20 min → 05:16.

Let me do a few more. Actually, let me reconsider whether there's any way to stop the sched. Let me look at the sched2 source to understand the priority. Maybe a real-C change in the RTL can flip it.

Actually, let me reconsider: the target has the store at 29. The barrier is AFTER the store (end of middle block). Without it, sched moves li a0 up. But wait — maybe the barrier's position matters. The barrier is at the END of the middle block, right after the store. So the store is the last insn before the barrier. sched2 can't move the store past the barrier. But the li a0 is AFTER the barrier (in the tail). So the barrier separates them. Without the barrier, they're in the same sched region.

If I could create a scheduling boundary right after the store WITHOUT asm... A do-while around the store creates a loop boundary. Tested (v_s8_store_dw = 4). Hmm, the do-while around the store gave 4 (worse) — it fixed the store but hoisted something else (like the sibling's e15 "fixes the store but hoists lh v0,52(sp); li a2,1, score 4").

So the do-while boundary DOES create a scheduling boundary! But it introduces a different problem (hoisting other insns). The sibling hit the same: "e15: fixes the store but hoists lh v0,52(sp); li a2,1, score 4".

Let me look at v_s8_store_dw's diff to see what it hoists. Maybe I can fix that.

v_s8_store_dw = score 4. Let me check its diff.

This is promising! If the do-while around the store fixes the store sink but hoists something else, maybe I can address the hoist.

Let me dump v_s8_store_dw's diff.
