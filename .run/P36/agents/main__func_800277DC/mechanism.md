# func_800277DC (main, src/800.c) — T7 agent e25 (S104)

**Result: score 0, lever-free** (no pin, no asm except the TU's Sony GTE macros, no volatile, no do-while, no goto).
Levers 2 -> 0 (the NEEDED `$8`/`$9` pins on `t0`/`t1`); the hand-hoisted pointer temps (`potz`, `psz0`, `psz1`,
`t0 = a0 + 3`, `t1 = a3 + 4`, `mask`, `shiftAmt`, `otp`, `cnt`) are all gone — loop.c makes every one of them itself.
Signature unchanged. No other copy of the class (`grep` over `src/`).

It is the LINE_G3 twin of func_800279AC (LINE_G4, closed in the same batch, `../main__func_800279AC/mechanism.md`):
the same loop written the same way, with 3 vertices, `gte_stsz3`/`gte_avsz3`, a 0x1C-byte source record, a 0x20-byte
primitive and tag length 7. See `body.c` for the text: a local `struct { s32 flag, otz, sz0, sz1, sz2; } g;` for the GTE
scratch words, body-local struct views `src = a0` / `p = (void *)a3` of the two untyped parameters, a
`for (; count != 0; count--, src++)` loop with `continue`s, the tree's own max-of-three `if/else`.

## (a) Residual
Free body: 51, COUNT 124 vs 116 — a 32-byte frame with `s0`/`s1` saved (mine) vs 24 bytes with none, two extra walked
pointers (`t0 = a0+16`, `t1 = a3+28` beside `t5`/`t3`: the tree's `t0`/`t1` hand-givs next to loop.c's own), every
temp one register off, and the `otz` reload inside the rgb0 chain. The sweep's best = 49.

## (b) Passes and decisions
1. **The hand-written induction pointers are the defect, not the allocation.** The tree pre-computed `t0 = a0 + 3`,
   `t1 = a3 + 4` and walked them (pinned to `$8`/`$9`) BESIDE the counter; unpinned, loop.c keeps them as extra bivs next
   to the givs it derives itself (S103 c2: `record_giv` `loop.c:4421`, `combine_givs` `:5494` — one register per
   walked pointer, hence two extra `addiu` per iteration and the callee-saved spill). Writing the loop as field accesses
   off the walked record pointers (`src->i0`, `p->rgb1`) lets strength reduction build exactly the target's `t0 = src+3`
   / `t1 = p+4` givs (the `+3`/`+4` are the lowest field offsets used, `code` at 3 and `rgb0` at 4). PROVEN on bytes
   (0 with the struct views; the 800279AC loop shape transfers unchanged).
2. **loop.c's biv initial value from a hard register** (as func_800279AC, `loop.c:3453-3509`, `valid_initial_value_p`
   `:4120-4146`): walking the parameter itself (`scratch/v_nocopy.c`, `a3 += sizeof(PrimT)`) initialises the `+4` giv
   from `(reg $a3)`, and `p`/giv swap `a3`/`t1` = 15; walking a LOCAL copy `p = (void *)a3` makes the initial value the
   pseudo = 0. PROVEN on bytes (the .loop dump reading is func_800279AC's, same shape; not re-dumped here).
3. **sched1's struct-vs-scalar exception** (`true_dependence` `sched.c:817-839`, as func_800279AC): scalar
   `s32 flag, otz, sz0, sz1, sz2;` (`scratch/v_scalar.c`) = 11 — the `otz` reload hoisted over the `p->rgb0` struct
   store. The struct `g` = 0, and so is the array `s32 st[5]` (`scratch/v_array.c`: an ARRAY_REF is also `/s`,
   `expr.c:4568-4577`) — the tree's `st[5]` array was already right; its comment's "one array pins the layout" was the
   alias fact, not the frame. PROVEN on bytes.
4. The max-of-three must stay the tree's nested `if (sz0 > sz1) { m = sz0; if (m < sz2) m = sz2; } else { m = sz1;
   if (m < sz2) m = sz2; }` — jump2 cross-jumps the two `if (m < sz2)` tails into the target's shared block and reorg
   leaves the `lw a0,16(sp)` in both paths; the flat `m = sz1; if (m < sz0) …; if (m < sz2) …` (`g1/a.c`, `b.c`),
   the if/else and the ternary forms (`g1/c.c`, `d.c`) score 47-51. PROVEN on bytes; the pass reading is not dumped.

## (c) Moves (joint)
1. delete the hand-hoisted temps and the pinned `t0`/`t1`: write the loop over typed record pointers
   (`src->…`, `p->…`, `src++`, `p++`) — func_800279AC's shape.
2. walk a local copy of the primitive parameter (`p = (void *)a3`), return it.
3. keep the GTE scratch words in one aggregate (`struct g` or the tree's `st[5]`).

## (d) Generator proposal
When a loop body walks hand-made `base + K` pointers pinned to registers beside a walked record pointer, rewrite every
`*(T *)(tK + off)` as a field access `rec->field` at `off + K` and delete the pointer (loop.c rebuilds the giv), then
apply func_800279AC's two rules (walk a local copy of a pointer parameter; keep address-taken GTE slots in one aggregate).
Before any of it: the TU's other `gte_stsz*`/`0x0?000000` OT-link loops are the template — port the closest one.

## (e) What did not work
Scalars for the GTE words = 11; walking the parameter = 15; the four other max-of-three spellings = 47-51 (`scratch/g1/`).

## (f) Where the method fell short
Nothing in steps 1-16 pointed at the twin; the coordinator's "diff against every same-TU function" did — func_800279AC
(the next function in the file) is this loop with one more vertex. Once one of the pair closed, the other took one
`--try`. A "structural twin" note (same loop, different vertex count / tag) in the pack builder would have paired them.

## (g) Structs
**Yes.** The close is three struct/aggregate types: the GTE scratch block `{ s32 flag, otz, sz0, sz1, sz2; }` (why: an
aggregate `otz` read keeps its true dependence on the `p->rgb0` struct store — `sched.c:834-836` frees only a
non-struct fixed-address read), the source record `{ u8 pad[3]; u8 code; u32 rgb1, rgb2, term, rgb0; u16 i0, i1, i2,
i3; }` (0x1C) and the LINE_G3 primitive `{ u32 tag, rgb0, xy0, rgb1, xy1, rgb2, xy2, term; }` (0x20) — the last two
turn the hand-written `+3`/`+4` pointer arithmetic into field accesses loop.c strength-reduces itself. Tested on bytes as
body-local declarations; the struct phase should hoist them to file-scope typedefs (`LINE_G3` next to the TU's
`LineG4`, a `SrcT` next to `SrcQ`) and change the parameter types to them — a signature change the K&R `extern void
*func_800277DC();` at src/800.c:17352 would accept, not needed for the bytes.
