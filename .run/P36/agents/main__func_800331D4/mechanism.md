# func_800331D4 (src/800_b_2.c) — S104 agent e16 — CLOSED at 0, ZERO levers (1 pin -> 0)

## (a) The residual
Score 9, REG-caller, 30 vs 30: the loop counter `i` and loop.c's second walked pointer (the `p+6` giv) swap `$a1`/`$v1`
(target: i = `$v1`, giv = `$a1`). Count and order already identical. The exact twin of func_800348A8 (same TU, same
`D_800A46E8` walk, only the type test differs: `(*p & 0x3F) == 1` vs `p[0] == 5`), which agent e2 closed this session.

## (b) The pass and the decision
global.c allocation order, `allocno_compare` (global.c:587-603), priority `floor_log2(refs)*refs/live`; refs counted by
flow weighted by loop depth (flow.c:2067). In the lever-free text the giv outranks `i`, takes `$v1` first. Not re-dumped
here — the reading is e2's (main__func_800348A8/mechanism.md (b)), and the bytes confirm it on the first `--try`.

## (c) The move that closed it (PROVEN on bytes, first try)
`return i + 1;` -> `return ++i;` — the increment adds a set and uses of `i` inside the loop (x loop depth), raising its
priority past the giv's; combine folds `i = i + 1; $v0 = i` back into `addiu v0,v1,1`, zero bytes changed.
Both spellings score 0: the tree's do-while with only that one line changed (scratch/min.c), and the delivered
body.c, which also rewrites the do-while as the `for` + one `&&`/`||` condition that func_800348A8 uses (the twin's
shape; readability).

## (d) GENERATOR PROPOSAL
When a REG residual swaps a loop counter with another loop-carried pseudo and the counter's only exit use is
`return i + K;`, rewrite it `return ++i;` (K = 1) — and apply it to every same-TU function that walks the same global
with that return (grep `return i + 1;` beside `D_800A46E8`).

## (e) What did not work
Nothing else tried — the first `--try` closed. The sweep (g6b/s3/s3b, 390 compiles) never mutates a return expression's
side effects, which is why it sat at 9.

## (f) Where the method fell short
It did not: the brief named e2's close, and the twin was recognisable from the body text alone. `related.txt` lists
func_800348A8 third (src/800_b_2.c:7060, sharing `D_800A46E8`); a twin_rescan after e2's bank would have remapped this
one for free.

## (g) Structs
No. The decision is a refs count in global.c; the `D_800A46E8` record (0x54 bytes: u16 type @0, u16 @4, u16 @6) as a
struct would re-spell `p[2]`/`p[3]` as fields at the same `(mem (plus p K))` addresses and change nothing here.
