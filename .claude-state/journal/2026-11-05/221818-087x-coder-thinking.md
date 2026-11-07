---
ts: 2026-11-06T05:18:18Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG21
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_mFpvVbEgLBynRuMe3Z9e
---
Wait, the date says 22:18, not 22:25. Item 2 started 21:53 → 25 min. Good.

Hmm, but check.py uses func_8014B944 — yes, it's the same script. Good, 141/141.

Now let me clean up the dumps (Disk is capped): rm -rf the dump dirs for item 2. Also item 1 had no dumps.

Then append the results rows. I need to append item 1's row (WALL, best 5, tries 36) — item 1 started 21:42, now 22:18 = 36 min, ≥30 tries. OK, I can record it now.

Wait, item 1: did I actually reach 36 tries? 10 + 18 + 8 = 36. Yes. And ≥20 min. ✓.

For item 1, the wall tag: `dbr-delay-fill` (line 19 in walls.txt): "delayed-branch fill takes a fall-through insn the target leaves out of the slot (G18x)". Evidence: reorg.c fill_eager_delay_slots; stop_search_p halts on an asm insn; no C insn is unmovable there (li doesn't trap, doesn't set sp).

For item 2: MATCH, best 0, tries = let me count: baseline 2 + v1 + p1-p5 (5) + q1-q3 (3) + r1,r2,r4,r5,r6 (5) + s1,s2,s3 (3) + nb1 + t1,t2,t3 (3) + u1,u2,u3 (3) + w1,w2,w4 (3) + x1,x2,x3 (3) = 2+1+5+3+5+3+1+3+3+3+3 = 32. Plus the 141-includer checks. Let me say 32.

Now let me append the rows to results.tsv. The format: `dir file func kinds result best tries wall evidence`.

Row 1:
`func_8014A59C__func_8014A59C	src/shared/ov/func_8014A59C.h	func_8014A59C	barrier	WALL	5	36	dbr-delay-fill	reorg.c fill_eager_delay_slots; stop_search_p halts only on asm/jump/label; li v0,128 sets nothing live at the epilogue (sp) and cannot trap, so eager moves it into bnez's slot; target nop`

Keep evidence ≤140 chars. Let me count. "reorg.c eager fill moves li v0,128 into bnez slot; stop_search_p halts only on asm/jump/label, li can't trap and sets nothing live (sp)" — ~140.

Row 2:
`func_8014B944__func_8014B944	src/shared/ov/func_8014B944.h	func_8014B944	barrier	MATCH	0	32	-	do{...}while(0) around the a1-free ifs splits the block (order); union-member read of D_80078EA6 forces the cse reload; 141/141 includers 0`

Let me check the evidence length ≤140: that's ~170. Trim.

Also, before appending: the brief says "First read .run/P40/T11/moves.md; after each item append one line `kind | func | MATCH: move / WALL tag — mechanism (G21)`" to moves.md. And results.tsv gets the row.

I'm behind on the moves.md appends (item 1 and item 2). Let me do them now: two separate commands (one action per command — "One action per command: a results.tsv fix is its own step").

Also cleanup dumps: rm -rf $D/dump* for item 2 (and check sizes).

Let me first clean up, then write notes.md files, then append results/moves.

Actually, let me keep moving: items 3,4,5 remain. Let me record items 1 and 2 now, then proceed.

Order of operations per item: results row + moves line + notes.md. Let me do item 2's notes and rows, item 1's row/moves/notes, then move on.

Let me be efficient: 
1. Cleanup dumps (item 2).
2. Write notes.md for item 1 and item 2 (Write tool).
3. Append results.tsv rows (2 lines in one command? The brief says "Per item append exactly one row"; a single append of two rows is fine, but "One action per command: a results.tsv fix is its own step" — that's about fixes. I'll do one append with both lines.)
4. Append moves.md lines.

Actually, let me do the results append per item to be safe (exactly one row per item).

Let me first check the disk/dump cleanup.
