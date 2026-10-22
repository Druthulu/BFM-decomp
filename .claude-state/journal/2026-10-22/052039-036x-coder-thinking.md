---
ts: 2026-10-22T11:20:39Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM2x
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_Gy70pbFNq0rWkEB7Xw37
---
There are two `schedule_insns` — one at 987 (with `#if 0`?) and one at 4666. This file is a mix (maybe both sched1 and sched2 with #ifdef). Let's look at line 987 area and see if it's the forward scheduler guarded by `#if 0` or a different macro.

Actually, in GCC 2.7, `sched.c` contains `sched1` (forward) and `sched2` was moved to `sched2.c`? Hmm, no: GCC 2.7's `sched.c` contains both `pass_sched` (forward) and `pass_sched2`? Let me look at the top of the file.

Actually GCC 2.7 introduced a unified `sched.c` with `#ifdef TWO_WAY` ... hmm no. In GCC 2.5-2.7, `sched.c` had the forward scheduler; the backward one (`sched2`) was added in GCC 2.7 in the same file guarded by `#ifndef TWO_WAY`?

Let me look at line 900-1000 for context, and check for "TWO_WAY".
