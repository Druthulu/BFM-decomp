---
ts: 2026-10-22T00:36:45Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG11
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_dRApKfcI1eiKorpMRrJ7
---
Only the pre-existing pins remain (other kinds, allowed to stay) — no launder asm ✓.

Everything is done:
- 8 items, one row each in results.tsv ✓
- 2 MATCH with win.c scoring 0 ✓
- 6 WALL with evidence ✓
- notes.md per item ✓
- moves.md: 8 lines appended ✓
- log at phase-ends/current/logs/T11.cG11.md ✓
- No commit (the brief forbids git/commit for this shard) ✓

Final report: start with "done", ≤10 lines, per item dir result best wall.

Let me write the report:

done
func_8018AA98__ov_SC03_014_jr_801848E4 — MATCH, best 0, wall -
func_80181CF4__ov_SC03_097_jr_8017D898 — MATCH, best 0, wall -
func_801832A8__ov_SC02_026_jr_8017C180 — WALL, best 14, wall sched1-birth-boost
func_8018389C__ov_SC02_026_jr_8017C180 — WALL, best 14, wall sched1-birth-boost
func_8017DE84__ov_SC02_039_jr_8017BEBC — WALL, best 13, wall cse-copy-merge
func_80185380__ov_SC03_014_jr_801848E4 — WALL, best 28, wall cse-case-table
func_80180054__ov_SC03_030_jr_8017AE2C — WALL, best 48, wall cse-copy-merge
func_8017E780__ov_SC03_092_jr_8017AE2C — WALL, best 2, wall sched1-call-group
rows in .run/P40/T11/G11/results.tsv, 8 moves.md lines, log phase-ends/current/logs/T11.cG11.md; no commit (brief forbids git).

That's 10 lines. Good.
