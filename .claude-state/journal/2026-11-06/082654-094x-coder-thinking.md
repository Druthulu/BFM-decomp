---
ts: 2026-11-06T15:26:54Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO03x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_ShhT7XAx3bpKK269t4mJ
---
Now append 5 rows to results.tsv. Format (tabs): `dir file func kinds result best tries wall evidence`.

Rows:
func_80188498__ov_SC03_090_jr_80188274  src/ov_SC03_090/ov_SC03_090_jr_80188274.c  func_80188498  launder  WALL  2  51  sched1-ready-order  <evidence>
... etc.

Evidence ≤140 chars: "sched1 ready-list: the launder's vol 2nd-set node flips vol/pan mult order; lever-free 236 ins pan-first (a3 vs a2); best real-C 14"

Let me count: ~140. Let me shorten: "sched1 ready-list: launder's vol 2nd-set node flips vol/pan mult order; without it 236 ins pan-first (a3 vs a2); best real-C 14" = 127 chars. Good.

I'll append with a python script (avoid echo). Write a small script or use the Write tool? The file already exists; appending via python is cleanest. Let me write a script that appends the rows.

Actually, "One action per command: a results.tsv fix is its own step, never folded into a check command." I'll make appending its own command.

Let me use a Python script under the shard dir.
