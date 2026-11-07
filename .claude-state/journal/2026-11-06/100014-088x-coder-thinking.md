---
ts: 2026-11-06T17:00:14Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW47x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_aCEN5OWGWJcGVQsokMGS
---
Item 2's win.c keeps the $4/$5 pins — allowed (pins are a different kind than the row's launder, pre-existing, not added). The launder asm is gone.

All done. Final report must start with the bare word done, then ≤10 lines: per item dir result best wall.

Report:
done
- func_800CB118__md_MAIN_041: WALL best 7, wall lreg-callresult-copy-pref (43 tries).
- func_8017D8E8__ov_SC03_108_jr_8017BEBC: MATCH 0 (twin func_8017DE00 shape, launder gone).
- func_8017E9A0__ov_SC03_112_jr_8017C294: MATCH 0 (h load + q=(h<<4)+s2 before t, pin gone).
- results.tsv 3 rows; log phase-ends/current/logs/T11.cW47x.md; no commit (task forbids git).

Keep it ≤10 lines.
