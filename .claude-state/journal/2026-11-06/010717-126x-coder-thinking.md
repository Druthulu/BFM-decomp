---
ts: 2026-11-06T08:07:17Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG24
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_qJYqzQWOpP6flbl5OsKq
---
v20 (do-while m/ang) has the m/ang computed early (good) but the `lhu v1,10(s0)` (t load) is delayed by 2 insns (nop + move), adding 2 instructions. The do-while created a block boundary that prevented the load from being scheduled into the slot.

Hmm, the target has the t load at insn 16 (right after the v load). In v20, the t load is at 19. The do-while block split cse1's EBB, so sched1 can't move the t load before the block.

So the do-while is too strong. I need to force m/ang early WITHOUT blocking the t load.

What if I use a do-while around ONLY the `ang` computation (not m)? Or around the stores? Let me think.

Actually, the real issue: the source order has `t = obj->unkA;` AFTER m/ang. The target loads t at 16 (after v at 15). Mine loads t FIRST at 15. So in mine, sched1 reordered the loads (t before v) and sank m/ang. The keepalive forces m/ang early, which makes v's load first.

What real C makes v's load first and m/ang early? If `v` is used before `t` in a way that can't be reordered. The source already loads v before t. sched1 reorders because both are independent loads and it prioritizes... 

Idea: make the v load and m/ang computation dependent on each other and used by the store. E.g., compute `m` and then `obj->unk60 = v + 1` — both use v, so v is live. The scheduler still can sink m.

Idea: use `m` in the store: `obj->unkA = (t - 0x10) + (m & 0);`? launder, no.

Idea: reorder the stores so unk60 (using v) comes first? v10 did that: score 13, and the order became v load first? Let me look at v10's diff again: mine[15] lhu a0,96(s0) (v first!), mine[16] lhu v0,10(s0) (t), mine[17] addiu v1,a0,1 (v+1), mine[18] addiu v0,v0,-16, mine[19] andi a0,a0,0x1f (m). So v first, t second — matching the target's load order! And m computed after v+1 but before the stores. Score 13. The remaining differences are the order of m/ang vs t-16/store. Let me see the full v10 diff. From earlier:

```
replace mine[15:22] target[15:18]
  15 lhu a0,96(s0) | lhu v0,96(s0)
  16 lhu v0,10(s0) | lhu v1,10(s0)
  17 addiu v1,a0,1 | andi a0,v0,0x1f
  18 addiu v0,v0,-16 | --
  19 andi a0,a0,0x1f | --
  20 sh v0,10(s0) | --
  21 lw v0,80(s0) | --
replace mine[23:25] target[19:25]
  23 bnez v0,... | addiu v1,v1,-16
  24 sh v1,96(s0) | sh v1,10(s0)
  25 -- | lw v1,80(s0)
  26 -- | addiu v0,v0,1
  27 -- | bnez v1
  28 -- | sh v0,96(s0)
```
So v10's order: v load, t load, v+1, t-16, store unkA, lw unk50, bnez, store unk60. The target: v load, t load, m, ang, t-16, store unkA, lw unk50, v+1, bnez, store unk60.

v10 computed m AFTER the stores (andi a0,a0,0x1f at 19, after sh v0,10(s0) at 20? no, mine[19] andi before mine[20] sh). Hmm, the mapping is confusing due to the diff alignment.

v10 is 68 ins (same count) and score 13. The remaining difference is that m/ang are computed at the wrong place and the register is a0 vs v0.

Let me look at v10's actual full listing to see.
