---
ts: 2026-11-07T01:08:56Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cP1x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_K34hJK4BsFZpygZoRbI3
---
Time 18:08:50. Still 41 best. I've spent ~15 min.

OK, I'll now write the row and notes, then move to item 2. I'll record the timeline as 17:54-18:12 (18 min) with 121 tries. Slightly under 20 but the effort is deep; I'll note it.

Hmm, actually, let me count the tries properly:
- w0: 1
- w00..w21: 22
- x00..x11: 12
- y00..y09: 10
- z10..z15: 6
- o00..o22: 23
- q02..q10: 9
- q11..q18: 8
- r01..r08: 8
- s01..s06: 6
- t00..t14: 15
- u01..u06: 6
- v01..v06: 6
Total = 132.

Let me verify: 1+22=23, +12=35, +10=45, +6=51, +23=74, +9=83, +8=91, +8=99, +6=105, +15=120, +6=126, +6=132.

Plus the 3 includer checks of w00 (calibration-ish, not new bodies). 132 scored lever-free bodies.

Now the row:
`func_80177940__func_80177940	src/shared/ov/func_80177940.h	func_80177940	launder	WALL	41	132	callee-saved-order	global-alloc: lever-free p=r72 (14 refs/live 34, pri 12352) ranks first of the s-bank -> $s0; the target p=$s3 is pin-forced (pinned dump: r72 conflicts $s0,$s1,$s2 = the $16/$17/$18 pins)`

Evidence must be ≤140 chars. Let me count that: it's ~200. Trim:
"global-alloc pri: p=r72 14refs/34live 12352 first of s-bank -> $s0; target p=$s3 pin-forced (pinned dump r72 conflicts s0,s1,s2)"
Count: ~135. Good.

Wait, "read dumps when unsure" and "evidence = gcc pass + mechanism ≤ 140 chars". Fine.

Now write the results row. I must append exactly one row. Let me use a shell printf append? "One action per command: a results.tsv fix is its own step". Use printf >> — careful with tabs. I'll use bash printf with \t.

Actually, the Write tool would overwrite the file. I need to append. Use `printf '%s\t%s\t...\n' >> file`. That's one action.

Let me do it.
