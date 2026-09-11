# func_801809E4 (ov_SC01_080_jr_8017AE2C.c) — e19, P36 S104 T7

**Final: score 0, plain C, ZERO levers** (tree: 1 pin `$19`; before → after = 1 → 0). `body.c` = `scratch/perloop.c`.

(a) Residual (21, register-only): the `+0x2C` mask value and loop.c's hoisted `0x19` constant swap `$s2`/`$s3` in every
one of the five masked spawn loops (target: `li s3,<mask>` before `i = 0`, `li s2,25` hoisted after it).

(b) Mechanism (`tools/alloc_table.py`, dumps `scratch/dumps_free`, `scratch/dumps_pl`): global allocation order,
`allocno_compare` (`global.c:594-607`). Lever-free, ONE function-scope `mask` is set five times and read in five loops:
15 refs over 131 insns → priority 3435, far above every loop-hoisted `0x19` pseudo (3 refs, ~600), so `mask` is allocated
first and takes the lowest free callee-saved register `$s2`; each hoist then gets `$s3`. With ONE `mask` PER LOOP (a block
local, set once before `i = 0`, read once in its loop), each mask pseudo has 3 refs over a range that starts before
`i = 0` — longer than its loop's hoist (which move_movables places after `i = 0`) → priority 555 < 600/652: the hoist of
that loop is allocated first and takes `$s2`, the mask it conflicts with takes `$s3`. That is the target in all five loops.
The header's "every pin-free spelling tried (decl order, s32/u16/int, a separate k var for 0x19)" never split the variable.

(c) Move (one line): `s16 mask;` at function scope → a block `{ s16 mask = K; i = 0; do { … } while (…); }` per loop
(S103 c1/c8 "one name per value" / S104 d7 per-arm local — the mask looks like a macro parameter in the original).

(d) GENERATOR PROPOSAL: when a register residual is a callee-saved swap between a variable assigned several constants
(one per loop / per block) and loop-hoisted invariants of those loops, split the variable into one block-local per
assignment (R23's split, but applied to a variable whose every value is a CONSTANT — the constant sets make it look like a
"single value" to a death-count-based splitter, which is why R23 did not fire: "dies in 0 places").

(e) Did not work (history, 191 compiles): R7 blocks/do-while, R8 temps, decl order — all 21; they keep one pseudo.

(f) Method: the allocation table's priority column (3435 vs ~600) was the whole argument; the splitter only looks at
multi-death locals (`local-alloc.c:472`), and this one is a GLOBAL pseudo refused nothing — it simply had too many refs.

(g) Structs: no. The decision is the ref count/live length of the mask pseudo; no memory access pattern is involved.
(R26's D_801C5D40 alias was the sweep's best and is not needed.)

**Copies closed (same TU):** `func_80180D54` carries the same `register s16 mask __asm__("$19")` pin over two 0x3FF loops.
Block-local mask (declared at the top of each arm, ASSIGNED after the `+0x1C` store so `li s3,1023` keeps its slot):
`scratch/copies/D54_perblock2.c` scores **0** with the pin deleted (3 levers → 2; its two `p0`/`p1` launders are a
different class — cse keeps `sp+24` in a callee-saved pseudo across `func_800D20C0` without them, `scratch/copies/D54_a.c`
/ `D54_b.c` score 29; left in place). Initialising `s16 mask = 0x3FF;` at the declaration instead scores 2 (ORDER, the
`li` moves above the store).
