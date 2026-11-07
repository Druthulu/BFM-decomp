---
ts: 2026-11-06T14:18:32Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO02x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_ZI4kq9jWOH0SVJjGHSTX
---
The greg dispositions for c1:
- 159 (n) in 12 (t4)
- 160 (i) in 11 (t3)
- 161 (src) in 9 (t1)
- 162 (dst) in 10 (t2)

So global-alloc assigned i -> $11 (t3) and dst -> $10 (t2). Confirmed: it IS global-alloc. Target needs i -> $10 (t2), dst -> $11 (t3).

So the priority order: dst allocated before i. In global-alloc, the allocation order is `allocno_order` sorted by allocno_compare. Higher priority first. And when allocating, find_free_reg picks the best available reg.

The available regs: $10 and $11 (t2, t3) — both caller-saved. The first allocated gets... which one? find_free_reg scans the register class in order. The MIPS GENERAL_REGS order likely $2,$3,$4,...$15. So first allocated gets the lowest-numbered free reg that doesn't conflict. At the time dst/i are allocated, $2-$9 may be taken, so $10 is the first free, then $11.

So the higher-priority one gets $10. Target: i gets $10 -> i has higher priority. Currently dst gets $10 -> dst higher.

Now let me figure out the actual priorities. Let me find where global-alloc prints them. There's a debug output maybe with -dg that prints allocno priorities? Let me search global.c for printf/fprintf.
