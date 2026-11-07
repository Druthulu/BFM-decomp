---
ts: 2026-11-06T04:39:57Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG20
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_LWCqBRuCCWIvCJXbd8qJ
---
All three MATCH wins re-verified at score 0 against the current tree.

Now write the log file phase-ends/current/logs/T11.cG20.md. The LOG EXTRA: per item, record start/end time, minutes, tries.

Timeline:
- Item 1 func_8017D7B4: start 20:39, end 20:52 (~13 min), 8 tries, MATCH (temp reuse + do-while).
- Item 2 func_80182560: start 20:52, end 21:16 (~24 min), 9 tries, MATCH (s16 temp + dead reset).
- Item 3 func_801854B8: start 21:16, end 21:22 (~6 min), 2 tries, MATCH (do-while around var).
- Item 4 func_801810A4: start 21:22, end 21:39 (~17 min), ~45 tries, WALL (best 6, sched1-load-order).

Also mention the correction (GCC sources at tools/reference/gcc-2.7.2/) and friction (none? The printf apostrophe error was my own, not a permission denial). Let me note the moves.

Also the FRESH check: I extracted orig.c at each item's start from the current src; no src changes observed (no commits, other batches). I'll note that.

Let me write the log. Note: the log path is phase-ends/current/logs/T11.cG20.md. Let me check the logs dir exists.

Also, per the harness rules, I should not read phase-ends/*/logs/, but writing is fine.

Let me write a terse markdown log.
