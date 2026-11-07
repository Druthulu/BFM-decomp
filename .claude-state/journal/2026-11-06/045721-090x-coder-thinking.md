---
ts: 2026-11-06T11:57:21Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG29
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_h42Xe1laDpHafDNScA44
---
All 14. The lbu is preserved but the schedule/regalloc differs. Let me look at one (y07, REG-caller) to see the diff.

The issue is the register rotation: temp_a0=v1, temp_v0=a0, temp_v1=v0. Target: a0, v0, v1.

Why? Because the intervening store changed the order at cse/alloc time. Hmm.

Actually, wait: in y01 the final asm had temp_a0=v1, temp_v0=a0, temp_v1=v0. That's a rotation. Why?

Let me think: with the intervening store, at cse time the code is:
```
lbu a0,5(s0)      ; temp_a0
lbu v0,6(s0)      ; 
subu
...
sb v0,6(s0)
sh v1,16(s0)      ; intervening
lbu v0,6(s0)      ; reload (now real)
```
Then sched1 reorders. The final register assignment differs because the live ranges changed.

Target wants temp_a0=a0, temp_v0=v0, temp_v1=v1. Mine has a rotation. Maybe I can fix the allocation by changing declaration order or temp types.

Let me look at the y07 diff to understand.
