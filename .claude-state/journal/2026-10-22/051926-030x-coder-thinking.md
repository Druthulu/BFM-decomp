---
ts: 2026-10-22T11:19:26Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM2x
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_xW1iT4GHXLB0fZAsOUaa
---
We have cse.c, sched.c (sched1), loop.c, rtl.h. sched.c in GCC 2.7 contains both sched1 and sched2. Let's look at sched1's priority logic.

Let me grep for "birthing" and "launch_priority".
