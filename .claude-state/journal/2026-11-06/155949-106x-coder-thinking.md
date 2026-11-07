---
ts: 2026-11-06T22:59:49Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM4
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_lf4D3aqhTtoRlL3lAzSn
---
w34 = 36. Not better.

OK, WALL with best 25.

Let me now write:
1. results.tsv row.
2. moves.md line.
3. notes.md update.
4. The log.
5. Clean up the dump dirs.

Let me double check the results.tsv header: `# dir	file	func	kinds	result	best	tries	wall	evidence` (tabs). So my row:
`func_8012B8E4__func_8012B8E4	src/shared/ov/func_8012B8E4.h	func_8012B8E4	keepalive,pin	WALL	25	32	lreg-qty-priority	<evidence>`

The wall tag: from walls.txt, `lreg-qty-priority` exists ("local-alloc qty priority (refs/live length) gives the hard reg to the other pseudo (G22)"). That fits: local-alloc gives $s0 to the block-local s1ang raw instead of the global d.

Evidence ≤140 chars: "local-alloc gives block-local s1ang raw (lh across jal, 2refs/7) $s0; global d (9/27, conflicts $16) then $s1. mask-in-place fixes d/s1ang but d=arg1's $a1 pref shifts iVar4 to $a1; best 25 (s16 d)"

Let me count the chars: roughly 190. Too long. Trim:
"local-alloc gives block-local s1ang raw (lh across jal, 2refs/7) $s0; d (9/27, conflicts $16) -> $s1; mask-in-place fixes d/s1ang but d=arg1 $a1 pref shifts iVar4; best 25 (s16 d)"
~170. Still long. The limit is ≤140 chars for the evidence. Let me trim more:
"local-alloc gives block-local s1ang raw (lh across jal, 2refs/7) $s0; d (9/27, conflicts $16) -> $s1; mask-in-place fixes d but d=arg1 $a1 pref shifts iVar4; best 25 (s16 d)"
Count: let me estimate ~160. 

Hmm, "≤140 chars". Let me be strict:
"lreg gives block-local s1ang raw (lh across jal,2refs/7)$s0; d(9/27,conflicts$16)$s1; mask-in-place fixes d but d=arg1 $a1 pref shifts iVar4; best 25(s16 d)"
Count: 
"lreg gives block-local s1ang raw (lh across jal,2refs/7)$s0; " = 62
"d(9/27,conflicts$16)$s1; " = 26 → 88
"mask-in-place fixes d but d=arg1 $a1 pref shifts iVar4; " = 57 → 145
"best 25(s16 d)" = 14 → 159.

Too long. Trim:
"local-alloc: block-local s1ang raw (lh across jal)$s0, d(conflicts$16)$s1; mask-in-place fixes d but d=arg1 $a1 pref shifts iVar4; best 25(s16 d)"
Count: "local-alloc: block-local s1ang raw (lh across jal)$s0, d(conflicts$16)$s1; " = 76
"mask-in-place fixes d but d=arg1 $a1 pref shifts iVar4; " = 57 → 133
"best 25(s16 d)" = 14 → 147.

Still 147. Trim "local-alloc:" to "lreg:" (-9) → 138. Good:
"lreg: block-local s1ang raw (lh across jal)$s0, d(conflicts$16)$s1; mask-in-place fixes d but d=arg1 $a1 pref shifts iVar4; best 25(s16 d)"

Let me count precisely later with a tool (awk length).

Now the moves.md line format: `kind | func | MATCH: move / WALL tag — mechanism (RM4)`. So:
`keepalive,pin | func_8012B8E4 | WALL lreg-qty-priority — block-local s1ang raw (lh across jal, 2refs/7) takes $s0 in local-alloc so d (9/27, conflicts $16) lands $s1; mask-in-place (s1ang=s1ang&0xFFF + do-while cast) fixes d/s1ang but d=arg1's $a1 preference shifts iVar4 $v1->$a1; best 25 (s16 d), 32 tries (RM4)`

Let me write the files.

First, let me count the tries precisely and check the evidence length.

Also, I should clean up the dumps. Let me list the dump dirs and remove them.

Let me also write the log with the timeline (start/end time per item, minutes, tries). Start: 15:26. End: ~16:20. That's ~54 min. Hmm, past the 30-min wall. I'll record it.

Let me now do the writes. First the results row (one action per command, per MOVES+).

Actually, the brief says "Per item append exactly one row to RM4/results.tsv". Let me use a script/heredoc with tabs. I'll write via a Python one-liner? The rules say scripts, not inline python -c. Let me use a small python script under .run/ or use printf. A printf with \t is fine (it's a shell command, not a script file). But the "one action per command" rule: the results.tsv fix is its own step.

Let me compute the evidence length first.
