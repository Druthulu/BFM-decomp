---
ts: 2026-11-06T15:16:15Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO04
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_jjhmA7uV7tLbDXA1U9Cp
---
Item 1 MATCH at 08:16 (started 08:00) — 16 minutes.

Only pins remain ($4 and $5), which are not the row kind (launder).

Now: append results.tsv row, moves.md line, notes.md. Then item 2.

Let me write the results row. Tabs. I need to be careful to append exactly one row.

Row:
func_801806D8__ov_SC03_099_jr_8017BEBC \t src/ov_SC03_099/ov_SC03_099_jr_8017BEBC.c \t func_801806D8 \t launder \t MATCH \t 0 \t 36 \t - \t evidence

Evidence (≤140 chars): "sched1 birth-order: vol 2nd set `vol = vol | 0x3000;` before the call + arg `(vol | (0x3000|sx))&0xFFFF`; fold keeps li a0,2715 before ori; launder asm dropped"

Length ~150. Trim: "sched1: vol 2nd set `vol = vol | 0x3000;` + arg `(vol|(0x3000|sx))&0xFFFF` -> fold birth order puts li a0,2715 before ori; launder asm dropped" ~135. Good.

Then moves.md line: `launder | func_801806D8 | MATCH: vol 2nd set vol = vol | 0x3000 before the call + arg kept as (vol | (0x3000|sx)) & 0xFFFF (redundant or folds: li a0,2715 born before ori); launder asm dropped (O04)`

Then notes.md in the item dir.

Let me do these appends.
