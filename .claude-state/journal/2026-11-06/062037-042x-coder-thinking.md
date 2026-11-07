---
ts: 2026-11-06T13:20:37Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO02
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_vgU2c0D6YqVdQ4oOfdGy
---
Now notes.md and moves.md append. Let me write notes.md.

Then move to item 2.

Item 2: func_8017E464, barrier = `__asm__ __volatile__("" ::: "memory");` inside the do-loop, between `nn = (s32)buf;` and `s0 &= 0x1F;`. It's a memory barrier keeping the stores/loads ordered around func_80015978? Let's remove it and see the diff.

Also item2 has pins (register __asm__) which stay.

Let me write item1 notes and moves line.
