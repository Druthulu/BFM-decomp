---
ts: 2026-11-06T17:46:56Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO05x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_Jj5ur8TYUxsKjfGxId4k
---
The moves.md has 4 O05x lines (my appends) but the tail shows the last 4 lines include two from other shards (func_80183BB0, func_80183D30) — wait, those are before mine; the tail -4 shows 2 other lines + 2 of mine. My 4 lines are there (grep counts 4 "(O05x)"). Good.

Final report: starts with "done", then ≤10 lines: per item dir result best wall.

Items:
- func_8017EAD8__ov_SC05_007_jr_8017BEBC — MATCH 0
- func_8017E5D0__ov_SC06_011_jr_8017BEBC — WALL best 52, global-pri-bank-order
- func_801817D0__ov_SC07_010_jr_8017AE2C — WALL best 21, lreg-qty-priority
- func_8015126C__func_8015126C — WALL best 5, lreg-qty-priority

No commit (scratch-only, per brief).
