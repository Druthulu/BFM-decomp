---
ts: 2026-11-06T10:34:02Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG28
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_TSWQteipYR08MThvwOhK
---
All 4 items have exactly one row, 4 moves lines, shard 1.3M.

Let me double check the PARTIAL win.c for CF3E8 is truly lever-free of barriers (it keeps pins, which is the PARTIAL kind). And confirm no `__asm__("")` remains.

Also, let me make sure I didn't accidentally leave `nopin.c` etc. with issues — not important.

One more: the brief says the results.tsv row for PARTIAL: "PARTIAL:<kinds still kept>". I wrote `PARTIAL:pin`. Good.

Also the log path: `phase-ends/current/logs/T11.cG28.md` — done.

Now, the RETURN: "your final message starts with the bare word done (or blocked) as its very first word, nothing before it; + ≤ 10 lines: per item dir result best wall; nothing else."

So my final message must start with "done" and list per item dir result best wall.

Let me compose:
done
func_800CD314__md_MAIN_047 WALL best 6 lreg-v0-local-first
func_801810E4__ov_SC01_080_jr_8017AE2C WALL best 2 sched-store-sink
func_800CF3E8__md_MAIN_003 PARTIAL:pin best 0 -
func_80023BF0__800 WALL best 97 global-hardreg-reserve

That's it. But wait — the general coder instructions say to commit with commit_task.sh; the brief overrides with "no git, no commit". So no commit. The report format for this brief is the ≤10-line per-item list. Good.

Before finalizing, let me do a last sanity check on the PARTIAL win.c scoring 0 (already verified). And ensure the log doesn't violate anything.

One thing: the brief says "no make, no git, no commit". I used `grep`, `sed`, etc. Fine.

Let me also confirm I didn't write anything under src/ or other forbidden dirs. I only wrote under .run/P40/T11/G28/ and appended to .run/P40/T11/moves.md and wrote phase-ends/current/logs/T11.cG28.md. The log is required by the brief. Good.

Wait — did dumpbody.py or delever_search write under .run/P36/engine/score? The --try scratch is removed automatically; I also removed the --keep p3 dir. Fine.

Let me do a final check that the shard's win.c files have no leftover barriers for the WALL bodies (they're lever-free). CD314 win.c: 0 asm. 801810E4 win.c: 0. 80023BF0 win.c: 0. CF3E8 win.c keeps pins (PARTIAL) and 0 barriers. Verified earlier for the first three; CF3E8 verified 0 `__asm__("");`.

Done. Let me write the final report.
