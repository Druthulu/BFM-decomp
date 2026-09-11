# func_8017B614 (ov_SC07_010, 5-copy class) — T7 agent d6 (S104)

**Result: score 0, lever-free, first `--try`.** No pin, no asm, no added volatile, no do-while, no invented term.
Levers before → after: **3 → 0** (the `$16` pin, the launder, the barrier).

Whole-object check on the `--try --keep` object (`scratch/cand.o`): `objdump -drz` of the entire object (all 9,004 lines,
every function, relocations included) is identical to `.run/P36/delever/baseline/src/ov_SC07_010/ov_SC07_010_jr_8017AE2C.o`
(`scratch/obj.diff` is empty). `.text`, `.data`, `.rodata`, `.sdata` and `.bss` are `cmp`-equal. The symbol tables differ only in
the `FILE` symbol, which is the scratch path.

**The other 4 copies (the same text with renamed symbols) also score 0.** `scratch/port.py` pairs the extern lists by
position, and the ports are in `scratch/ports/`:
`src/ov_MAIN_012/ov_MAIN_012_jr_801789AC.c`, `src/ov_SC02_037/ov_SC02_037_jr_8017AE2C.c`,
`src/ov_SC03_107/ov_SC03_107_jr_801789AC.c`, `src/ov_SC07_011/ov_SC07_011_jr_8017AE2C.c`. Each ported body got
`--try` → score 0 (function-level only; I did not run the whole-object check on those four).

## (a) The residual in one sentence
Two independent defects. (1) `param_2` was kept in `$s0` for the whole function, where the target compares `$a1` and copies
`$a1→$s0` only in the block-move arm (the pin plus the launder were faking that copy). (2) `li 1; sh D_801A94D0` was emitted above
the six tail `lh` loads, where the target has it below them (the barrier was faking that order).

## (b) Passes and decisions (read in `tools/reference/gcc-2.7.2/`, the same mechanism as S103 c30 on the 126-copy ov_SC04_011 class)
1. **cse canonical register, `make_regs_eqv` (cse.c:849-858).** A new pseudo becomes the class head only if it lives past the
   current basic block. A then-arm-local `src` does not, so `param_2` stays canonical, the copy is deleted, and `param_2` lives
   across the `movstrsi` scratch clobbers of `$v0-$a1`, which puts it in `$s0`. A function-scope `src` assigned in BOTH arms lives
   past the block, becomes canonical, and keeps the copy. Global's `expand_preferences` (global.c:781-821) then hands `src` `$s0`
   and leaves `param_2` in `$a1`.
2. **sched1 hoists the store and sched2 repairs it, through `true_dependence` (sched.c:815-836).** sched1's `birthing_insn_p`
   priority boost puts the loads after `sh 1` in every spelling. sched2 can sink `sh 1` below the `0(s0)`/`0(s1)` loads only if
   they are independent. That needs the loads to be MEM_IN_STRUCT_P at a varying address (COMPONENT_REF, expr.c:4888) and the
   store to be scalar at a fixed address. The `sb zero,D_8012694C` must stay ABOVE the loads, so it must itself be an in-struct
   access: `extern u8 D_8012694C[]; D_8012694C[0] = 0;`.

## (c) The source moves (byte ladder in THIS TU, all by `--try`)
- `body_free.c` → 13.
- + one function-scope `u8 *src` assigned in both arms (the arm shape of func_8017B238, which is banked in this TU) → **6**
  (`scratch/A2_free_arm.c`; only the `sh 1` order is left).
- + tail loads as `((SV4_8017B368 *)&D_801A7CCC)->a` / `…&D_801A7CC4)->a`, with the scalar `D_8012694C` kept → **4**
  (`scratch/B_noarray.c`).
- + `extern u8 D_8012694C[]; D_8012694C[0] = 0;` → **0** (`body.c`; the ported banked ov_SC01_000 sibling, with symbols renamed).
- Controls: keep the array store but drop the member reads → 19 (`scratch/C_nomember.c`). Arm shape plus direct scalar tail reads
  (without the `p794`/`v…` temporaries) → 19 (`scratch/A_armonly.c`). Without the member reads, cse re-materialises the
  addresses differently. So the member reads and the array store are a JOINT close, the same as in S103.

Proven on bytes: the ladder above. Not independently re-proven here: the pass attributions (b1) and (b2). They are inherited from
S103 c30's dumps on the ov_SC04_011 copy, and the identical byte ladder (13/6/4/0) is consistent with them.

## (d) Generator proposal
When a `$16` pin + launder + barrier trio sits on a function whose NAME has a lever-free banked variant in another overlay
(`related.txt`'s first section), port the variant, renaming the extern symbols by position in the extern list
(`scratch/port.py`: pair the two bodies' `extern … D_x` lists in order). Then `--try` every copy of the class. This closed 5/5
copies with zero search here. A class-wide "port-the-banked-twin" pass should run BEFORE the R2–R26 free sweep, which spent
1,699 compiles on this class and never left 13.

## (e) What did not work
- The free sweep (history.txt: g6/s1/s2/s4/s7, 1,699 compiles) stayed at 13. None of its moves (block, param-copy, bystander,
  do-while, inline, base tmp) touch either of the two real channels: the scope of `src` across the if/else, or the
  MEM_IN_STRUCT_P flag on the tail accesses.
- The single-move ablations above (19, 4) show that no one-step move reaches 0.

## (f) Where the method fell short
Nothing was left to crack. `related.txt` put the lever-free ov_SC01_000 variant first, and the brief's R71 lead said to port it
first. The one compile was the whole job. The shortfall is upstream: the regen sweep does not try the banked cross-overlay
twin before its generators. Also, 5 copies were listed but not named in the pack; `grep -l 'rung B tus9'` over each TU's
func_8017B614 body finds them.

## (g) Structs question
**Yes, and here it is not "plausibly": struct typing is exactly what replaced the barrier.** The barrier existed only because
sched2's `true_dependence` (sched.c:830-834) could not separate the scalar `sh D_801A94D0` from the `lh 0(s0)` / `lh 0(s1)`
loads. Once those loads are COMPONENT_REFs of an 8-byte `SV4_8017B368` (`{s16 a, b, c, pad}`) laid over `D_801A7CCC` and
`D_801A7CC4`, they are `mem/s`, and the store sinks. The struct types this implies:
- `D_801A7CC4` / `D_801A7CCC`: two `SV4_8017B368` (s16 x,y,z,pad) position vectors (the `D_801A7CC4..CC8` and `D_801A7CCC..CD0`
  triples; func_8017B7A8 and func_8017B940 write the same triples field by field). Typing them as one struct global each would
  remove the `((SV4_8017B368 *)&…)->a` casts.
- `D_8012694C`: the byte at +4 of the camera object `D_80126948`, whose s32 fields +0x3C..+0x50 are `D_80126984..D_80126998`.
  `D_8012694C[0]` is a stand-in for `camera.field_4 = 0`. A real struct type for `D_80126948` would make this store a genuine
  COMPONENT_REF (the in-struct flag the bytes need) and turn the seven scalar externs into field accesses.
The `$16` pin plus launder was not a struct issue: it was the scope of `src` (cse.c:849-858).
