---
ts: 2026-11-06T22:15:13Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM3
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_TtafUFhBFLOgMdzAUOOi
---
Let me try wrapping the sxy store block and the pkt[0x14] block in do-whiles, plus combinations with the otp do-while.

Actually, the do-while's effect on the schedule might come from splitting the EBB so sched1 schedules the two EBBs separately. The otp do-while creates a boundary before `otp=...`. The mask materialization is in the *first* EBB (the packet store) — it's used by both, but it's born in the first EBB. Hmm, the mask at 163 is before the otp do-while boundary.

Wait, the constant is used by the packet store's and (before the boundary) and the otp store's and (after). So it's materialized in the first EBB. The target schedules it at 166, which is before the packet store's and (190). So both are in the same EBB (the packet store region).

The difference must be sched1's ready-list ordering within the big EBB. The do-while changed the EBB *after* it, which changed the register allocation (fixed!), and incidentally the schedule. But the constant placement still differs.

To shift the constant later within the first EBB, I could split the EBB earlier (e.g., a do-while around the sxy stores), which would make sched1 treat the mask in a smaller EBB and possibly place it differently.

Let me try wrapping the sxy store block in a do-while (before the packet store). And also wrap `pkt[0x14]...` block.

Let me generate m1..m5.
