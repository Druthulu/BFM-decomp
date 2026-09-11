# func_8017BF50 (ov_SC03_124_jr_8017AE2C.c) — d18, P36 T7 S104

**Result: score 0, ZERO levers** (1 pin `$17` → 0). First `--try`. `PACK/body.c`.
Nine copies of the class close with the same text (table at the end, candidates in `scratch/copy_*.c`).

## (a) The residual
COUNT, 85 vs 81 ins, frame 0x48 vs 0x40: mine keeps THREE loop pointers (`s2` = D, `s3` = D+0x1C, `s1` = D+0x18,
the stores at `-4(s1)`, `0(s1)`, `0(s3)`, two `addiu …,32` steps) plus an extra callee-saved `$s5`; the target keeps TWO
(`s2` = D, `s1` = D+0x1C with the stores at `-8/-4/0(s1)`). The `move s4,a0`/`s5` register shifts are fallout of the
extra callee-saved register, not a separate defect.

## (b) The pass and the decision (proved on the `.loop` dumps, `scratch/dumps_old`, `scratch/dumps_new`)
loop.c strength reduction (`strength_reduce`, loop.c:3214). The decompiler's `s1` is not a source variable: it is the
REDUCED GIV loop.c built from the real pointer. Written as its own variable it becomes a SECOND biv:
- old (`body_free.c`): `Reg 76: biv verified` (s2) AND `Reg 75: biv verified` (s1, "initial value is complex");
  `Cannot eliminate biv 75: biv used in insn 147` (the `s1[0]` store uses the biv itself, maybe_eliminate_biv
  loop.c:5952/5976), and its two other address givs (`s1-8`, `s1-4`) are combined and reduced to a THIRD register:
  `giv at 129 combined with giv at 138; giv at 138 reduced to (reg:SI 106)`.
- new (`body.c`): one pointer biv (`Reg 75`, init `D_801E17F8`), three address givs `+0x14/+0x18/+0x1C`, all combined
  into the textually LAST one (`giv at 135/126 combined with giv at 144; giv at 144 reduced to (reg:SI 105)` —
  `record_giv` prepends, loop.c:4421-4422; `combine_givs` loop.c:5494, called at :3770; reduction print :3992) = the
  target's `addiu s1,s2,28` and `-8/-4/0(s1)`; the biv is kept because `*(v3+0x30) = s2` uses it
  (`Cannot eliminate biv 75: biv used in insn 148`) = the target's `s2`.

## (c) The move
Delete `s1` and write its three stores as offsets from `s2`, the pointer the loop already walks:
`s1[-2] / s1[-1] / s1[0]` → `*(s32 *)(s2 + 0x14) / (s2 + 0x18) / (s2 + 0x1C)`; delete `s1 = D + 0x1C` and `s1 += 8`.

## (d) Generator proposal
When a loop steps two pointers by the SAME stride and one is initialised to the other plus a constant K (`q = p + K`
before the loop, `q += S`, `p += S` in the same arm), delete `q` and rewrite every `q[i]` / `*(T *)(q + c)` as
`*(T *)(p + K + c·sizeof)` — the decompiler printed loop.c's reduced giv as a variable (an R-family "giv un-reduce";
it generalises S103 c2, which only covered `q = p + k` read inside one loop).

## (e) What did not work
Nothing else tried; the sweep (R2–R26, 332 compiles) plateaued at 21 because no generator deletes a pointer and
re-bases its accesses on another. The header's explanation ("$16-$19 pinned … strength reduction splits the s1 base")
read the symptom right and the cause backwards: the split came from the second biv, not from the allocator.

## (f) Where the method fell short
It did not — step 3's S103 c2 bullet ("a second walked pointer, `q = p + k`, both stepped: loop.c keeps both bivs.
Delete `q`") names this exactly; the only gap is that c2's wording is about READS with an index, and this was STORES
through a separately-stepped pointer. The tree header's comment should be replaced (proposal below).

## (g) Structs answer
Yes, and the struct spelling is the natural one: the 0x20-byte records at `D_801E17F8` are an array of
`struct { u8 pad[0x14]; s32 x, y, z; }` (0x14/0x18/0x1C written from three `s16` values; the record's address is
stored into the spawned object's +0x30). `scratch/body_struct.c` (body-local `struct Slot20`, `s2->x/y/z`, `s2++`)
also scores 0 — the struct field accesses give loop.c exactly the one biv + three address givs. It is the channel
here not through `expr.c:4568` aggregate marking but through ONE pointer variable instead of two: a struct type makes
the decompiler print `p->x` instead of inventing `s1 = p + 0x1C`. Either spelling banks; the struct one is
preferable once the record type has a name in `engine_types.h`.

Suggested header comment for the bank:
`/* One walked pointer: the 0x20-byte records are written at +0x14/+0x18/+0x1C from s2 — loop.c combines the three
 * address givs into the last one (s1 = s2+0x1C), and the s2 store to the spawned object keeps the biv. A separate
 * s1 pointer is a second biv and costs a third register. */`

## Copies (all `--try` score 0, candidates in `scratch/`)
| function | TU | file |
|---|---|---|
| func_8017BF50 | src/ov_SC03_124/ov_SC03_124_jr_8017AE2C.c | PACK/body.c |
| func_8017BF50 | src/ov_SC03_001/ov_SC03_001_jr_8017AE2C.c | scratch/copy_ov_SC03_001__func_8017BF50.c (file-scope `D_801EE680`, no body-local extern) |
| func_8017BF50 | src/ov_SC05_017/ov_SC05_017_jr_8017AE2C.c | scratch/copy_ov_SC05_017__func_8017BF50.c |
| func_8017BF50 | src/ov_SC04_018/ov_SC04_018_jr_8017AE2C.c | scratch/copy_ov_SC04_018__func_8017BF50.c |
| func_8017BF70 | src/ov_SC04_015/ov_SC04_015_jr_8017AE2C.c | scratch/copy_ov_SC04_015__func_8017BF70.c |
| func_8017C234 | src/ov_SC03_002/ov_SC03_002_jr_8017AE2C.c | scratch/copy_ov_SC03_002__func_8017C234.c |
| func_8017C234 | src/ov_SC04_020/ov_SC04_020_jr_8017AE2C.c | scratch/copy_ov_SC04_020__func_8017C234.c |
| func_8017C234 | src/ov_SC03_125/ov_SC03_125_jr_8017AE2C.c | scratch/copy_ov_SC03_125__func_8017C234.c |
| func_8017C234 | src/ov_SC05_018/ov_SC05_018_jr_8017AE2C.c | scratch/copy_ov_SC05_018__func_8017C234.c |
