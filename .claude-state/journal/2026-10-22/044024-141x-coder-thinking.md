---
ts: 2026-10-22T10:40:24Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM2
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_XoSdE4lmbOpxHDW6CUfZ
---
Time 04:39:43. The last two items have ~13 min wall each. Let me do one or two more batches to cross 04:47, then write up.

Actually, let me be smart: I'll start the write-up now and run one more batch in the same call. The write-up involves several files. Let me:

1. Save the best bodies as best.c per item.
2. Append results rows to results.tsv.
3. Append to each item's notes.md.
4. Append to moves.md.
5. Write the log file.

Let me do the batch + the best.c/results.tsv in one call.

For the best bodies:
- 80184828: best 1 → any of the variants; use the base v1.c (lever-free, score 1) → best.c.
- 8018483C: best 5 → x1.c (base) or v9.c (115 insns). I'll use v9.c? Hmm, v9 = the address used twice (score 5, 115 insns). Both 5. I'll use x1.c (the simplest lever-free body).
- 8017DA30: best 4 → v1.c.
- 8018389C: best 14 → c1.c.
- 8017D81C: best 12 → var/w17_store_first.c.

Let me now write the results.tsv rows. Format: `dir file func kinds result best tries wall evidence` (tabs).

The "dir" column = the item dir name (e.g. func_8018483C__ov_SC02_000_jr_8018173C). The "file" = the src file path.

Tries counts (my scored tries):
- 80184828: batch1 19 + batch2 12 + batch3 10 + batch4 4 + batch5 8 = 53 scored (plus 3 errors) → let me count precisely:
  batch1: 19 files, all scored = 19
  batch2: 14 files (v26..v36 = 11 + v2*,v3* = 20 files? hmm). Let me just count the score lines I saw: batch1 = 19 lines; batch2 = 14 lines; batch3 = 10 lines; batch4 = 4 lines; batch5 = 8 lines → 55.
- 8018483C: 12 (w01-w12: 9 scored) + 16 (w2*,w3*: 16 scored) + 8 (x4*) + 10 (z5*,z6*)... hmm, let me recount:
  First batch: 12 generated, 3 errors → 9 scored.
  Second batch (vars2: w20-w39 = 20 files): the output showed w20..w39 = 17 scored + 3 errors (w22, w33, w38) → 17.
  Third batch (vars3: x40-x47 = 8): 8 scored.
  So 8018483C = 9 + 17 + 8 = 34 ✓
- 8017DA30: batch1 (x01-x14 = 14, 1 error x05) = 13; batch2 (y01-y10 = 10) = 10; batch3 (z50-z59 = 10, 1 miss) = 9; batch4 (z60-z69 = 10) = 10 → 42 ✓
- 8018389C: batch1 (z01-z14 = 14, 3 errors) = 11; batch2 (z20-z35 = 16, 2 errors) = 14; batch3 (z40-z45 = 6, 1 error) = 5; batch4 (y01-y15 = 15, 1 miss+2 errors) = 12; batch5 (y20-y35 = 16) = 16; batch6 (y40-y51 = 12, 1 error) = 11; batch7 (y60-y65 = 6, 1 error) = 5; batch8 (y70-y81 = 12, 1 error) = 11; batch9 (y90-ya1 = 12) = 12; batch10 (yb0-yb11 = 12, 3 errors) = 9; batch11 (yc0-ycb = 12, 3 errors) = 9 → total ≈ 125 ✓
- 8017D81C: batch1 (w01-w16 = 16) = 16; batch2 (w20-w24 = 5 + w30-w36 = 7) = 12; batch3 (w26-w29 = 4) = 4; batch4 (w30-w36 = 7) = 7 (hmm, overlapping names w30-w36 in vars4 — the earlier batch2 had w30-w36 too... whatever); batch5 (w40-w50 = 11) = 11; batch6 (w60-w65 = 6) = 6; batch7 (w70-w82 = 13, 1 error) = 12; batch8 (w90-wa1 = 12) = 12; batch9 (wb0-wba1 = 12) = 12; batch10 (wc0-wcb = 12) = 12 → ≈ 104 ✓

Good, all ≥30.

Now the wall tags:
- 80184828: combine-commutative-swap (new, defined in notes.md)
- 8018483C: cse-const-addr-copy (new, defined in notes.md)
- 8017DA30: sched1-argcopy-hoist (in walls.txt)
- 8018389C: sched1-birth-boost (in walls.txt)
- 8017D81C: cse-const-holder (new, defined in notes.md)

Evidence (≤140 chars each): "gcc pass + mechanism".

1. 80184828: "gcc pass combine: simplify_rtx puts the constant last in a commutative plus, so the address tree (sym,idx) becomes (idx,sym); the launder's hard-reg pseudo is the only way to keep the pointer a REG" — too long (>140). Let me shorten:
"combine simplify_rtx swaps a commutative plus to put the constant last; the pointer must stay a REG (the launder's hard-reg pseudo) to keep it first" = ~148. Hmm.
Shorten: "combine simplify_rtx puts the constant last in a commutative plus; the pointer must be a REG (launder hard-reg pseudo) to stay first" = 135 ✓

2. 8018483C: "expand/cse fold a constant-address initializer into its use, so the copy `move s0,v0` dies; only the launder's hard-reg pseudo keeps it" = ~135 ✓
Let me count: "expand/cse fold a constant-address initializer into its use, so the copy `move s0,v0` dies; only the launder's hard-reg pseudo keeps it" — 135 ✓

3. 8017DA30: "sched1/reload_cse sink the a1 setup into the call delay slot; the launder's asm anchors the arg setup at the arm top" = 118 ✓

4. 8018389C: "sched1/sched2 sink the shared 0x66666667 magic next to its mult; the target materialises it at the tail top in $a0" = 118 ✓

5. 8017D81C: "cse forwards the const holder into its uses, so the li is born at the first use; the launder's read births it at the assignment" = 128 ✓

Also the results.tsv header exists: "# dir	file	func	kinds	result	best	tries	wall	evidence". I need to append 5 rows.

Let me write everything now. Also the notes.md appends and moves.md lines.

moves.md line format: `kind | func | MATCH: move / WALL: tag — mechanism. (RM2)`

E.g.:
"launder | func_80184828 | WALL combine-commutative-swap — combine simplify_rtx puts the constant last in a commutative plus; the pointer must be a REG (launder hard-reg pseudo) to stay first (RM2)"

Let me write all the files now. Let me do it in a couple of Write/Edit calls.

First: results.tsv + best.c copies + notes.md appends.

Let me be careful with the tab characters in results.tsv. I'll use python to write it (tabs).

Let me also delete the dump dirs (disk): .run/P40/T11/RM2/func_80184828.../dump_rm2_28 (9.2M), func_8018483C.../dump_rm2_83c (16M), func_8018389C.../dump_rm2_89c (25M), and the _lab dir. Total ~50M — fine but the brief says to delete them after reading ✓. Let me delete.

Let me write the files.
