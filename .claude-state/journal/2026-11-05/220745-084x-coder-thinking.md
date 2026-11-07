---
ts: 2026-11-06T05:07:45Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG20x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_WsR86aHV2ydky4ZhekAE
---
Now append results.tsv rows and moves.md lines. One action per command (the brief says a results.tsv fix is its own step). I'll write with python or printf. Tabs required. Use printf with \t.

Let me construct rows:
dir	file	func	kinds	result	best	tries	wall	evidence

Row1: func_8017F5A4__ov_SC07_010_jr_8017AE2C	src/ov_SC07_010/ov_SC07_010_jr_8017AE2C.c	func_8017F5A4	barrier	MATCH	0	9	-	sched1: do-while(0) per byte store keeps next lbu below the sb; direct ((u8*)a0)[i] avoids the v1 pointer copy
Row2: func_800D0214__resident_jr_800D00E4	src/resident/resident_jr_800D00E4.c	func_800D0214	barrier	MATCH	0	34	-	greg/cse: s32 *q=&D_800A2E20 at top + do-while(0) around the D_800C7C64 store keeps its addr late, mask v1
Row3: func_8013A2BC__func_8013A2BC	src/shared/ov/func_8013A2BC.h	func_8013A2BC	barrier	MATCH	0	20	-	cse: dead reset v0=0 after the sh kills store->reload eq; delete_dead_from_cse drops it; 141/141 includers

Check evidence ≤140 chars each.
Row1 evidence length: let me count roughly: "sched1: do-while(0) per byte store keeps next lbu below the sb; direct ((u8*)a0)[i] avoids the v1 pointer copy" ~112. OK.
Row2: "greg/cse: s32 *q=&D_800A2E20 at top + do-while(0) around the D_800C7C64 store keeps its addr late, mask v1" ~110. OK.
Row3: "cse: dead reset v0=0 after the sh kills store->reload eq; delete_dead_from_cse drops it; 141/141 includers" ~108. OK.

Append with python (script, not inline? The rule says scripts not inline python -c; a heredoc python is arguably inline. Better use printf via Bash. printf with tabs is fine and allowed? It's a shell builtin. The rule about "Read files with the Read tool or a ranged sed, not a bare cat chain" — writing via printf is fine.

Let me use printf >> results.tsv. That's one action.
