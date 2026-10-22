---
ts: 2026-10-22T11:19:45Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM2x
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_4hVkHvzmSl5JBbjms9MW
---
This is the sched2 (backward) code. sched1 is in a different file? In GCC 2.7, sched1 is `sched1.c` and sched2 is `sched.c`? Hmm — actually in GCC 2.x, `sched.c` contains BOTH sched1 and sched2 (sched2 was added in 2.7 with `sched2` pass). But the file we have (sched.c, 4968 lines) seems to be the backward scheduler (sched2). The forward one (sched1.c) isn't here.

Let me check: `grep -n "sched1" file`.

Actually the file has `rank_for_schedule` used by a backward scheduler (`schedule_insn` with "currently executing insn"). And `adjust_priority` with `INSN_PRIORITY(prev) >>= 3` — that's backward.

So we have sched2's source but not sched1's. Hmm.

But we have cse.c and loop.c — those are the passes mentioned in walls.txt (cse-const-addr, cse-copy-merge). Good for items 1 and 5.

Let me check if sched1.c exists anywhere in the project... `.run/gccmap/` only has those files. Let me check `tools/reference/gcc-2.7.2`.

Actually, let me not go down this path too far. Let me instead consider: is there a GCC source for sched1 anywhere? Let me check tools/reference/gcc-2.7.2.
