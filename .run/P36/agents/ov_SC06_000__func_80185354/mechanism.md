# func_80185354 (ov_SC06_000_jr_8017AE2C.c) — e28, P36 T7 S104

**Score: 22 free (sweep best 18) -> 0, zero levers** (the `$16` pin deleted; plain C). Second `--try`.

## (a) Residual
COUNT +4 (43 vs 39) and one extra callee-saved register: the free text walks TWO pointers — `s2` = `e` (the call
argument, stepped `+44`) and `s0` = `e + 32` (`addiu s0,s2,32`, stores at `-8(s0)`/`0(s0)`) — plus an extra `s3` for the
parameter. The target walks ONE pointer `s0` (initialised `lui/addiu` to `D_801AED08`, stepped `+44` in the branch delay
slot) and addresses both stores as `24(s0)`/`32(s0)`.

## (b) Pass and decision
loop.c strength reduction (`strength_reduce`, gcc-2.7.2 loop.c; givs recorded by `record_giv` :4341, merged by
`combine_givs` :5494). In the free text `e` is itself a BIV (`e = e + 0x2C`); its field addresses `e+0x18`/`e+0x20` are
DEST_ADDR givs of that biv, and the pass reduces one of them into a new register (`s0 = e + 32`) while `e` must survive
for the call argument — two stepped registers. The tree's `$16` pin hid `e` from loop.c (a hard register is never a biv),
which is why the pin was NEEDED. In the target, `e` is a GIV of the counter biv `i` (`D_801AED08 + i*0x2C`): the call
argument and both field addresses are givs with the same multiplier, `combine_givs` folds them into ONE reduced register
with constant offsets, and `i` stays as the call's second argument and the exit test (`slti v0,s1,200`).
Proven on bytes (score 0); the `-dL` dump was NOT taken (the prediction from S103 c2/d16 closed on the first spelling).

## (c) Move
Index the array by the loop counter instead of walking a pointer:
`for (i = 0; i < 200; i++) { e = D_801AED08 + i * 0x2C; func_80185520(e, i); … }` (the do-while and `e += 0x2C` deleted).
A do-while with the same indexed `e` (scratch/a3.c) scores 23 — the `for` (rotated loop, loop.c sees the canonical
biv/giv shape) is part of the close; writing each access as `D_801AED08 + (i-1)*0x2C + K` (a2.c) scores 32.

## (d) Generator proposal
When the residual shows two callee-saved registers stepped by the same stride (one `addiu sK,sJ,K` before the loop) and
the tree pins the walked pointer, rewrite `p = BASE; do { … p += S; } while (++i < N)` as
`for (i = 0; i < N; i++) { p = BASE + i * S; … }` — the pointer becomes a giv of the counter and combines into one.

## (e) What did not work
The sweep's R4/R6/R7/R8/R9/R10/R12 moves reach 18-19: none turns the walked pointer into a counter giv.

## (f) Method
S103 c2 / S104 d16-d18 in METHOD_S103.md named this exact class ("a walked destination pointer -> index the array by the
loop counter"); counting first (+4, one extra `$s`) pointed straight at it. Worked as written.

## (g) Structs
Yes, plausibly the ORIGINAL shape: `D_801AED08` is an array of 0x2C-byte records (`struct { u8 pad[0x18]; u32 f18;
u32 pad1c; u32 f20; … } D_801AED08[200];`, see func_801853F0's `+0x1C/+0x20/+0x24` fields) and `&D_801AED08[i]` is
exactly the indexed giv the close needs. A struct type would not change the pass decision beyond what the indexed form
already does (the decisive fact is biv vs giv in loop.c, not aliasing); not tested with a body-local struct.
