---
ts: 2026-11-06T21:38:02Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW49x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_KMga7KCw0ba7nzUztaI2
---
No-pin do-while = 3. So the pin is load-bearing; v03 (pin kept) is the MATCH.

Time 14:38. Item 3 started ~14:20 → 18 min. Let me do 2 more minutes of checks (e.g., verify v03's asm matches and the exact mechanism), then finalize at 14:40.

Actually, the mechanism: v03 hoists `a = arg0` above the inner if. Let me verify the generated asm for v03 on includer 0 to confirm the move is in the beqz delay slot. Since the score is 0 (byte-identical), it's confirmed by definition. Good.

Let me now:
1. Append the results row for item 3.
2. Append the moves.md line.
3. Update notes.md (times, final).
4. Write the log phase-ends/current/logs/T11.cW49x.md.

Then final report.

results.tsv row for item 3:
`func_80160C28__func_80160C28	src/shared/ov/func_80160C28.h	func_80160C28	keepalive	MATCH	0	25	-	keepalive asm dropped; hoisting `a=arg0` above the inner if puts the copy in the beqz delay slot (sched1 ready order); $4 pin (non-row lever) stays, load-bearing (W49x)`

Evidence ≤140 chars. Let me count: "keepalive asm dropped; hoisting a=arg0 above the inner if puts move a0,s0 in the beqz delay slot; $4 pin (not a row kind) stays" — ~130. Good.

Tries: 25 (v01-v24, v25) + n2 = 26 scored on includer 0, plus the 141-includer sweep. Let me say 26.

Let me append.
