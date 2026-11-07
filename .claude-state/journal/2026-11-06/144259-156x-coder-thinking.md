---
ts: 2026-11-06T21:42:59Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW50x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_tXLmQbs2t1u6XVFtBx3U
---
The verification completed: 141 includers checked, bad = [] — all score 0. So w7 = score 0 on every includer.

Now I can record item 3:
- results.tsv row: PARTIAL:pin, best 0, tries 9, wall '-', evidence.
- moves.md line.
- win.c = w7.c (done).
- notes.md (done, but let me update with the verification result).
- log (done, but the item 3 line says "~14:52" — let me fix to the actual time; and confirm 141/141).

Wait, the log currently says "Start 14:30, end ~14:52" — the actual end is ~14:43. Let me update. Also the log says "141/141 via verify.py" which is now verified.

Let me append the results row.

Row: `func_8012B8E4__func_8012B8E4	src/shared/ov/func_8012B8E4.h	func_8012B8E4	keepalive,pin	PARTIAL:pin	0	9	-	...`

Evidence (≤140 chars): "keepalive asm -> do{}while(0) on the d cast (C0535) anchors the sll; pin kept (global-alloc swaps d->s1 without it); 0 on 141/141 includers". Count: ~140. Let me trim: "keepalive asm -> do{}while(0) on d cast (C0535) anchors sll; pin kept (lever-free swaps d->s1); 0 on 141/141 includers". ~120 chars.

Let me append.

Wait — the results row format: `dir file func kinds result best tries wall evidence`. For PARTIAL, wall = '-' (MATCH rows: wall '-'; PARTIAL is a wall? The brief says "wall (WALL/PARTIAL) = a tag from walls.txt or a new <pass>-<what>". So PARTIAL needs a wall tag! "wall (WALL/PARTIAL) = a tag". And "MATCH rows: wall `-`". So for PARTIAL:pin, I need a wall tag describing the remaining blocker. The blocker is global-alloc swapping d→s1 without the pin. Tag: `global-pri-bank-order` or `lreg-index-conflict`. From walls.txt: `global-pri-bank-order global-alloc priority order assigns the hard regs in a different order than the target (G22x)`. That fits. Or `lreg-index-conflict`. Let me use `global-pri-bank-order`.

Hmm, but the PARTIAL's kept lever is the pin; the wall is why the pin can't be removed: global-alloc assigns d to s1 (not s0) because of the priority/conflict. `global-pri-bank-order` fits.

Let me append the row with wall=global-pri-bank-order.

Let me do it.
