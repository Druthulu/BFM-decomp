---
ts: 2026-11-06T22:19:43Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM3
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_mkWJpSa0FVEzsxwVQElz
---
MATCH confirmed, lever-free (no asm/register). win.c = s1.c.

Now fix the results row for item 1. Let me write a small python script to replace the row.

Actually simpler: use sed to replace the specific line? The line contains tabs. Use python.

Let me write a script under .run to rewrite the row: read results.tsv, replace the line whose first field is func_80183534..., write back.

The new row:
`func_80183534__ov_SC06_029_jr_8017C954	src/ov_SC06_029/ov_SC06_029_jr_8017C954.c	func_80183534	pin	MATCH	0	87	-	do{}while(0) EBB split around the first 3 sxy stores + the otp block: local-alloc splits the tail, oidx qty gets $3 (target); 197 ins`

Evidence ≤140 chars for the WALL case; MATCH rows wall "-". The evidence for a MATCH can be a short mechanism. Let me keep it concise.

Let me do it.
