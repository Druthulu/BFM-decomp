# func_80015760 (main, src/800.c) — T7 agent e15 (S104)

**Result: score 0, lever-free** (no pin, no asm, no volatile, no do-while added, no invented term). Levers 2 -> 0
(the NEEDED `$21` pin on `tagCode` and the NEEDED `$3` pin on `mask`), and the tree's `y0++; y0--;` no-op pair (an
identically-zero term the free body carried) is gone too. Signature unchanged. Whole-object check on the
`--try --keep` object: `.text` (101,572 bytes), `.data`, `.rodata` byte-equal to
`.run/P36/delever/baseline/src/800.o`. `body.c` = `scratch/u/c0.c`.

The decisive text (whole body in `body.c`):
```c
    s16 y0;                                   /* was s32 + `y0++; y0--;` */
    ...
    if (width == 8) {
        code = 0x74000000;
        len = 0x03000000;                     /* the length word set in BOTH arms */
    } else {
        code = 0x7C000000;
        len = 0x03000000;
    }
    ...
            clut = 0x40560000;
            pkt[3] = *uv | clut;
            mask = 0x00FFFFFF;
            tag = *ot & mask;
            tag |= len;
            pkt[0] = tag;
            mask &= (u32)pkt;
            *ot = mask;
```

## (a) Residual
Free body: 23, a callee-saved permutation (`s5->s4`, `s4->s3`) plus COUNT moves: the `0x00FFFFFF` mask was hoisted
out of the loop into `$s3` (`lui s3,0xff; ori` before the loop) and the `0x03000000` tag was rematerialised inside
the loop (`lui a2,0x300`) — the target is the opposite: the mask rebuilt in `$v1` every iteration, the tag kept in
`$s5` across the loop (`lui s5,0x300` in the delay slot of the loop-skip branch).

## (b) Passes and decisions (all PROVEN on dumps `scratch/dumps_*` + bytes)
Four independent decisions, each byte-proven by removing it from the 0 body:
1. **loop.c invariant motion of the mask** (`dumps_free/free.i.loop`: `Insn 195: regno 112 (life 5) ... moved`).
   A set-once constant in the loop is movable (`loop.c:703-708`, `n_times_set == 1`) and desirable when
   `threshold * savings * lifetime >= insn_count` (`loop.c:1631`; threshold = 1 + n_non_fixed_regs = 29 with a call,
   `loop.c:532`, 25 GPRs + hi/lo/hilo non-fixed with `-msoft-float`, `mips.h:1186` + `:525-530`, minus 3 per move,
   `loop.c:1719`). No literal spelling survives: cse1 merges the two literal masks into one pseudo with life 4-5.
   `mask &= (u32)pkt;` makes the mask SET TWICE in the loop -> not movable -> rebuilt per iteration in `$v1`, with the
   final `and v1,s1,v1` writing into it (the tree's `$3` pin faked exactly this). Literal/set-once forms = 63-65
   (`scratch/k/*_m2_*`, `*_m3_*`).
2. **local-alloc's constant equivalence halving the tag's priority** (`local-alloc.c:1016-1030`: a pseudo set once
   whose REG_EQUAL is a constant becomes REG_EQUIV; `:1058-1064`: its `reg_live_length *= 2`). With one
   `tagCode = 0x03000000;` the pseudo prints `used 3 times across 66 insns` (live 33 doubled) and ranks LAST
   (`allocno_compare`, `global.c:594-607`, priority 385-455) -> no hard register -> reload substitutes the constant at
   the use (the in-loop `lui a2,0x300`). Set in both arms of the sprite-size if/else it has 2 sets, no REG_EQUIV,
   `r83: refs 4, live 42, priority 1904` — between `width` (1960) and `flags` (1846) in `scratch/c0` —
   so it takes the sixth callee-saved register, `$s5` (`.greg` dispositions `83 in 21`). A single set anywhere else
   (`scratch/h/h5*`, `scratch/u/c1.c`) = 53-57.
3. **sched1's birth boost on the pkt[0] word** (`sched.c:2465-2490` `birthing_insn_p`, `:2537-2543`): with
   `pkt[0] = (*ot & mask) | len;` the ior's set-once temp is boosted to max priority and scheduled after the
   `and mask,pkt` (score 2, `scratch/v1_sched.txt`: `ready list at T-6: ... 203 (7f000001)`); a `tag` variable set
   twice (`tag = *ot & mask; tag |= len;`) is not boosted and the target order `and; or; and; sw` comes out (0).
   Single-assignment spellings of `tag` = 2 (`scratch/p/t3.c`, `t4.c`).
4. **the same boost on `y0`'s definition in block 0**: the free body's `y0++; y0--;` in the `flags & 0x80` arm only
   served to give `y0` three sets so its `subu` is not boosted (`dumps_noyy` vs `dumps_t1`: `ready list at T-2: ...
   41 (7f000001)` only without the pair; score 13 without it). Declared `s16` (a screen coordinate) the definition
   is `(set (subreg:SI (reg/v:HI 75) 0) ...)` (`dumps_c0/c0.i.sched`, insn 42) — a SUBREG destination fails
   `birthing_insn_p`'s `GET_CODE (SET_DEST (pat)) == REG` (`sched.c:2477`). Same bytes, no dead statements.
   (`s16`/`u16` both 0; `u32` = 13; `y0 = a; y0 -= b;` = 13, because combine merges the two sets and decrements
   `reg_n_sets`, `combine.c:2309`.)
Plus `clut = 0x40560000;` as a variable (not a literal): loop.c moves it (life 3), it is REG_EQUIV, spilled, and
reload rematerialises it at the use in the target's `$a2` (`.greg` order ends `... 114`, priority 468); the literal
has life 1, is not moved, and local-alloc gives it `$v1` (score 7, `scratch/u/c4.c`).

## (c) Moves (joint — every single one scored worse alone)
1. `tagCode = 0x03000000;` -> `len = 0x03000000;` in both arms of the `width == 8` if/else (23 -> 8 with the next).
2. `mask = 0x00FFFFFF; ... *ot = (u32)pkt & mask;` -> `mask &= (u32)pkt; *ot = mask;` (8 -> 2 with `clut` a variable).
3. `pkt[0] = (*ot & mask) | tagCode;` -> `tag = *ot & mask; tag |= len; pkt[0] = tag;` (2 -> 0).
4. `s32 y0` + `y0++; y0--;` -> `s16 y0` (0 stays 0; the no-op pair is gone).
5. Readability, all 0: `tx` folded into `x0`, `tagHi = width; if (tagHi == 8)` -> `if (width == 8)`, the tag/code
   names, K&R-free formatting. (`count` must stay: `digitCount = flags & 0xF; if (digitCount == 0)` = 6.)

## (d) Generator proposal
When a pinned constant holder lives across a loop and the unpinned body rematerialises it inside the loop (`lui` at
the use), give the variable a SECOND identical assignment on a sibling path (both arms of the nearest if/else) —
two sets defeat local-alloc's REG_EQUIV live-length doubling (`local-alloc.c:1064`); and when a pinned constant
inside a loop is hoisted by the free body, make it read-modify-write (`mask &= x;`) so loop.c's `n_times_set == 1`
test (`loop.c:705`) refuses it. For a sched1 order residual on a value's definition, try the SUBREG-destination
spelling (a `s16`/`u16` declaration) or a two-step assignment before any no-op pair.

## (e) What did not work
432 structural spellings (`scratch/e/`, `e_scores.txt`: color/yWord/tag/mask/clut variable-vs-inline x tag placement
x `y0++/--` x if+do-while vs while) — best 22: none varies the NUMBER of sets. Tag placements with one set
(`c1`-`c4`, `h5*`) 52-57. Reusing `count`/`tx`/`value` for the tag (`h2`-`h4`) 18-24. `mask` spellings with the
literal or a set-once variable 63-65; `a0`-`a3` operand orders x `b0`-`b3` update forms x `u32`/`s32` mask: all 2.

## (f) Where the method fell short
Nothing in steps 1-16 names local-alloc's REG_EQUIV live-length doubling (`local-alloc.c:1064`) — the reason a
constant-holding local ranks last in `allocno_compare` and ends up rematerialised — nor loop.c's movable threshold.
The allocation table showed the priorities (it settled move 1 by arithmetic: 4 refs over live 40-43 lands between
width 2000 and flags 1846), but the `.loop` dump's `moved to` / `not desirable` lines were what explained the mask and
the `clut` register. Add `-dL` `.loop` reading to step 3 for any constant hoisted/not hoisted.

## (g) Structs
Tested: no. `pkt` is a sprite packet (`SPRT_8`/`SPRT_16`: tag, code|rgb, xy, uv|clut) — a struct
`{ u32 tag; u32 rgbc; u32 xy; u32 uvclut; }` would turn `pkt[k]` into field stores off one base, which is the same
MEM shape loop.c's giv combination already produces (`pkt + 12` as one giv, stores at -8/-4/0). None of the four
decisions (loop motion by set count, REG_EQUIV doubling, two birth boosts) involves an aggregate-vs-scalar memory
dependence, so a struct would not plausibly change them.
