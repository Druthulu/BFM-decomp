---
ts: 2026-11-06T10:11:58Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG27
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_A2clAHbRMBzBTDWCwFtn
---
Now append results.tsv rows. Format (tabs): `dir file func kinds result best tries wall evidence`.

The existing header is:
`# dir	file	func	kinds	result	best	tries	wall	evidence`

Let me append 4 rows. I'll use a Python script to append with tabs (to avoid shell quoting issues). Or printf with \t. Let me use a script under .run. Actually, I can use printf. Let me write with Python for safety.

Rows:
1. func_8017D730__ov_SC06_006_jr_8017BEBC | src/ov_SC06_006/ov_SC06_006_jr_8017BEBC.c | func_8017D730 | keepalive,pin | WALL | 19 | 34 | flow-unused-result | flow deletes dead 2nd-branch t/v0/v1 (17 ins); keepalive-only keeps all but v1->a1
2. func_80182420... | src/ov_SC03_124/... | func_80182420 | keepalive,pin | WALL | 13 | 66 | expand-void-return | void def drops rv; keepalive keeps it live but $3 not $2; pin $2 needs a return
3. func_8018A168... | src/ov_SC04_018/... | func_8018A168 | keepalive,pin | WALL | 13 | 32 | expand-void-return | void def drops rv; keepalive keeps it live but $3 not $2; pin $2 needs a return
4. func_80189E68... | src/ov_SC05_017/... | func_80189E68 | keepalive,pin | WALL | 13 | 32 | expand-void-return | void def drops rv; keepalive keeps it live but $3 not $2; pin $2 needs a return

Evidence ≤140 chars: "void def drops rv; keepalive keeps it live but $3 not $2; pin $2 needs a return" = ~83 chars. Good.

Order: the list.tsv order is SC03, SC04, SC05, SC06. I'll append in list order for consistency.

Let me append with a Python script.
