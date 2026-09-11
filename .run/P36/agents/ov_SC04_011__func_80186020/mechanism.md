# func_80186020 (ov_SC04_011_jr_8017D494.c): mechanism (P36 T7 S104, agent e11)

**Result: score 0 in plain C.** No pin, no asm, no added volatile. Levers go from 1 to 0 (the `$2` pin on `y`).
Signature unchanged. No copy of this class elsewhere (greps of the `-0x60`/`0x120` pair and of the pin find only
this body).

## (a) The residual in one sentence
Same count (60/60). Every value the target keeps in `v0` is in `v1` in mine and the other way round, in BOTH arms.
The free body's shared `u16 x, y` get x→v0 and y→v1; the target has x→v1 and y→v0.

## (b) The pass and the decision (proven on the `.lreg`/`.greg` dumps and bytes)
global.c allocates in priority order (`allocno_compare`, `global.c:594-610`). `find_reg` gives each allocno the
first register that is free of conflicts and preferences (`global.c:945-990`). In the free body:
- In arm 1, `x = x + y` is HImode arithmetic. It expands into an SI temp (r91) and a HI copy into `x`. cse then
  routes the two later readers (the `D_801EFD48` store and `y + x`) through r91, so the copy into `x` dies and
  r91 is a LOCAL. local-alloc allocates it before global runs and gives it `v0`, its first choice.
- Global then sees `y` (reloaded with `D_801EFD44` while r91 is live) as conflicting with `v0`. `x`, the
  highest-priority allocno (26666 vs y's 21428), has no `v0` conflict and a copy preference for r91's `v0`, so it
  takes `v0`. `y` falls to `v1`. The pin forced `y` into `v0`.

What the target's allocation needs (read off the working body's `.greg`: order `x a b y`, dispositions
x→3, a→3, b→2, y→2):
- The two `v1` roles (arm 1's D48 accumulator, arm 2's D48/D44 value) must CONFLICT with `v0`. That happens when
  the variable is live while a `v0` compare temp (`slti v0,…`) is live, so `find_reg` skips `v0` for them.
- The two `v0` roles must be global and must not overlap any local that sits in `v0`.
- Arm 1's sum must not be a separate local temp.

## (c) The moves that closed it (joint; each alone scores worse)
```c
    if ((D_801EFD40 & 2) != 0) {
        s32 a;                                  /* arm-1 locals, SImode */
        s32 b;
        a = (s16)D_801EFD48;                    /* the test operand hoisted into `a` */
        if (a >= 0x120) { … } else if (a < -0x5F) { … }
        a = D_801EFD48;
        b = D_801EFD4C;  p = …;  a = a + b;  b = D_801EFD44;  D_801EFD48 = a;  b = b + a;  … = b;
    } else {
        u16 x;                                  /* arm-2 locals, HImode */
        u16 y;
        if (D_801EFD40 & 1) { x = D_801EFD48; if ((s16)x >= 0x120) return; y = x + 0x60; }
        else                { x = D_801EFD48; if ((s16)x < -0x5F) return; y = x - 0x60; }
        x = D_801EFD44;  p = …;  D_801EFD48 = y;  x = x + y;  … = x;
    }
```
1. **Split the shared variables per arm** (S104 d7/d22: one variable per case), and give each arm the width its
   arithmetic proves. Arm 1 as `s32` makes `a = a + b` a plain SImode add into `a`, so no HI→SI temp and no local
   r91. Arm 2 stays `u16`: its `move v1,v0` (the HI copy of the `lh`) and the 16-byte frame (the dead
   sign-extension intermediate r96/r100 with class `ST_REGS or none` that reload spills; see `.lreg`) are
   HImode-only artefacts. With `s32` in arm 2 both vanish (`scratch/c3/w_s32_s32.c`, 56 ins).
2. **Hoist the arm-1 test operand into `a`** (`a = (s16)D_801EFD48; if (a >= 0x120) … else if (a < -0x5F)`).
   `a` is now set in one block and read in the else-if block, so it is block-global
   (`local-alloc.c:469-476` requires a single block and `reg_n_deaths == 1`). It is also live across the
   `slti v0` temps, so it conflicts with `v0` and takes `v1`. The target shows the same thing: the `lh v1,D48` of
   the test and the later `lhu v1,D48` share `v1`.
3. **Arm 2 reads `D_801EFD48` into `x` in each sub-block** (`x = D_801EFD48; if ((s16)x …) …; y = x ± 0x60;`).
   `x` now spans three blocks, and its HI copy is born while the `lh` result (local `v0`) is still read by
   `slti`, so `x` conflicts with `v0` and takes `v1`. `y` takes `v0`. This is what the target's
   `lh v0; move v1,v0; slti v0,v0,…` is.

Proven on bytes:
- `body.c` (block-scoped declarations) and `scratch/c10/g_abb_s32s32_v.c` (function-scope declarations): 0.
- Without move 2 (`scratch/c11/n3_nohoist.c`): 15, because cross-jump merges the arm tails once the registers
  line up.
- Without move 3 (`n1_arm2free.c`): 14.
- `a` as `s16` (`n4_a_s16.c`): 22.
- Without the `*(s16 *)&D_801EFD4C` store casts (`n5_nocast.c`): 1.

## (d) Generator proposal
When a register residual swaps `v0`/`v1` (or any pair) between variables SHARED by two if/else arms, first split
them per arm (one variable per role per arm, at the widths the instructions prove: `s32` where the target adds in
a register with no HI copy, `u16` where it keeps a `move` of an `lh`). Then, for each variable the target puts in
the register that also holds an earlier TEST operand (`lh vN,G; slti …,vN,K` followed by a later reload of `G`
into `vN`), hoist the test operand into that variable (`v = (s16)G; if (v >= K)`). This makes it block-global and
makes it conflict with the compare temp's register.

## (e) What did NOT work (byte evidence, scratch/c*/ with their scores)
- The free body: 22. The regen sweep's 122 candidates: best 10 (`scratch/regen_scores.txt`). The history's "7" path
  could not be reproduced from its label.
- Renaming or splitting per arm with `u16` everywhere (`c/`, `c2/`): 10-24. Arm 1's cse temp r91 always takes `v0`.
- Widths alone (`c3/`, 16 combinations): best 15. `s32` in arm 2 deletes the HI `move` and the frame.
- Arm 1 `s32` + arm 2 `u16` `y2` with a shared `s32 x` (`c4/t_s32s32_x_s32u16.c`): 4. The `x + y2` add
  zero-extends (`andi 0xffff`). Folding the add into the store removes the `andi` but lets cross-jump merge the
  tails (`c9/`: 7).
- A single-set D44 temp to get the scheduler's birthing boost (`c8/`): 10. The D44 load is then hoisted above the
  sum (`sched.c:2477-2490` boosts it, `sched.c:2425-2428` breaks the tie), so it overlaps `y`.

## (f) Where the method fell short
- The allocation table (`tools/alloc_table.py`) was the deciding read. It showed r91 as a LOCAL in `v0` and
  `y` "conflicts v0". What it cannot show is WHICH local causes a conflict. Grepping `.lreg` for the local's
  block and life settled it.
- The winning move 2 (hoisting a test operand into an existing variable, so that it conflicts with the compare
  temp) is not in METHOD. It is the inverse of S103 c18's "same register, same role → one variable": here the
  target's `lh v1,G … lhu v1,G` said "same register, same variable". A block-by-block read of the target for
  "which values share a register" found it. The hunk view hid it.
- Enumeration was effective: about 300 bodies in 8 batches through `--try`. Each batch was shaped by the previous
  batch's residual.

## (g) Structs question
No. The lever came from register-allocation conflicts between user variables (local-alloc/global), with no memory
ordering involved. The globals `D_801EFD44/48/4C` are three separate scalars (x-offset, position, velocity-like).
Making them fields of one struct would put `MEM_IN_STRUCT_P` on the accesses. Nothing here depends on alias
decisions, although cse's store-forwarding into `x = x + y` (`cse.c` invalidation of varying-address entries,
`cse.c:1701-1720`) would be worth re-checking in the structs phase. Not tested.

Files: `body.c` (score 0), `scratch/c{,2..11}/` (candidate batches), `scratch/tryall.sh`, `scratch/splice.py`,
`scratch/dumps_{free,i1,m_xyc_u,k1_u16,match}/`.
