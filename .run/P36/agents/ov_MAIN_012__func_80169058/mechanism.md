# func_80169058 (src/ov_MAIN_012/ov_MAIN_012_jr_8015A3C8.c): T7 agent c33

**CLOSED: score 0** on the first spelling tried (`--try … body.c --body`: "score 0 (OTHER; mine 88 ins, target 88) — MATCH",
run twice). The whole-function `objdump -drz` of the candidate object is identical to the baseline object's
(`scratch/final.dis` vs `scratch/target.dis`). All three NEEDED levers are gone: the `$2` pin, the launder and the
keepalive. There is no asm, no pin, no added volatile, no zero term, no dead assignment and no do-while.

**The same text closes all six copies and the shared header** (read-only `--try`, each score 0):
`src/ov_MAIN_012`, `src/ov_SC02_037`, `src/ov_SC03_107` (`_jr_8015A3C8.c`), `src/ov_SC07_006`, `src/ov_SC07_007`,
`src/ov_SC07_011` (`_jr_8015C32C.c`), and `src/shared/ov/func_80169058.h` (with the header's plain
`ApplyMatrixSV(…)` call in place of the cast, `scratch/hdr_body.c`). Negative controls: `body_free.c` scores 18 on
ov_SC07_007, the same as here.

## The move (one edit)

```c
    if ((*(s32 *)(s1 + 0x2C) & 0x2) == 0) {
        s32 r = rand();
        v10[0] = (r & 0x7F) << 3;
        v10[1] = (((u32)(r & 0x7F00)) >> 5) + 0xC00;
    } else {
        s32 r = rand();
        v10[0] = ((r & 0x7F) << 3) + 0xE40;
        v10[1] = (((u32)(r & 0x7F00)) >> 5) + 0xE00;
    }
```
Each arm keeps its `rand()` result in its own block-local `r` and stores straight into `v10[0]`/`v10[1]`. The
function-scope `v1`/`v0` join variables and the `v10[0] = v1; v10[1] = v0;` statements after the `if` are deleted.

Ablations (all `--try`):

| body | score |
|---|---|
| `body_free.c` (`v0 = rand()` reused, `v1`/`v0` stored after the join) | 18 (90 vs 88) |
| `a/a5.c`: stores moved into the arms, `v0` still the rand result at function scope | 16 (90) |
| `a/a4.c`: one function-scope `r` reused by both arms, direct stores | 14 (91) |
| `a/a1.c`: per-arm `r`, but `v1`/`v0` still join variables stored after the `if` | 4 (88, ORDER: the two `sh` after the join's argument setup) |
| `a/a3.c` = **`body.c`**: per-arm `r`, direct stores | **0** |

Both halves are needed: the per-arm local fixes the registers, and the in-arm stores fix the order.

## (a) The residual

I counted first: 90 against 88. The extra two are `move v1,v0` after each `jal rand`. The rand result was copied out of
`$v0` into the pseudo for `v0`, and the `v1` value landed in `a2`. The target computes straight out of `$v0`
(`andi v1,v0,0x7f; sll v1,v1,3; andi v0,v0,0x7f00; …`) and ends with `sh v1,16(sp); sh v0,18(sp)` at the join label,
before the join block's `addiu a0,sp,16`.

## (b) Mechanism (proved on the dumps, `scratch/dumps_free/`, `scratch/dumps_fin/`)

1. **Why the copy exists: `v0`/`v1` are global allocnos that conflict with `$2`.** In `body_free.c` the variable `v0` is
   set in both arms and read at the join. `.lreg` says "Register 75 used 11 times across 18 insns; dies in 3 places",
   which fails `reg_n_deaths == 1` (local-alloc.c:472), so global.c allocates it (and `v1`, reg 74). The per-arm temps
   (`v0 & 0x7F`, `… & 0x7F00`) are block-local and take `$2` first in local-alloc. `.greg` then lists
   "75 conflicts: 73 74 75 2 4 5 16 29" and the same for 74, so neither can have `$2`: 75 gets `$3` and 74 gets `$6`
   (`.greg` "74 in 6  75 in 3"). `v0 = rand()` becomes `move v1,v0`, and the lever pin on `$2` was forcing the
   target's allocation.
2. **Why the per-arm `r` fixes it.** `r` is born at the call-value copy and dies inside its arm, one death, so it is a
   local-alloc quantity. It is tied to the dying hard `$2` of the call value, so the copy is deleted and `r` lives in
   `$v0`. The `<<3` and `>>5` results are also block-local temps. They die at their stores, so they take `$3` and `$2`.
   No global allocno is left in the arms (`dumps_fin/fn.lreg`: every arm register is "in block 1/2").
   A single function-scope `r` shared by both arms (`a4.c`, 14) dies in two places and is global again.
3. **Why the stores must be written in the arms: post-reload cross-jump.** With a store in each arm, `.sched2` still
   has both pairs (then-arm insns 99/108, else-arm 132/141). `.jump2` has only 132/141, because `jump_optimize (insns, 1,
   1, 0)` (toplev.c:3142, after sched2 at :3117) cross-jumped the identical tails (`find_cross_jump`, jump.c:2371;
   `do_cross_jump`, :2537). The merged pair sits AT the join label, ahead of the join block's own scheduled code. That
   is the target's order. With the stores written after the `if` (`a1.c`), sched1 schedules them inside the join block,
   after `addiu a0,sp,16` / `addiu s0,sp,32`, which is the 4-point ORDER residual. The keepalive lever (`"r"(v1),"r"(v0)`
   after the stores) faked that placement.

## (c) The move, one line

Declare the `rand()` result as a local inside each arm and store the two computed components straight into
`v10[0]`/`v10[1]` in that arm. Delete the function-scope `v1`/`v0`.

## (d) Generator proposal

**"Per-arm call result, per-arm stores":** when an if/else calls the same function in both arms, the target uses the
result straight out of `$v0` while mine has `move vK,v0` after each `jal`, and a variable is assigned in both arms and
only stored after the join, then move the store into each arm (duplicated) and give the call result a block-local
declaration in each arm. local-alloc then ties it to `$2` (one death, local-alloc.c:472), and jump2's cross-jump
(toplev.c:3142) folds the duplicated stores back to one copy at the join label. Detector: a `move rX,v0` right after
`jal`, where the pseudo holding the result "dies in N>1 places" in `.lreg`, plus identical store tails in both arms of the
target just before a join label.

## (e) What did not work (byte evidence)

Listed in the ablation table: `a5.c` (16), `a4.c` (14), `a1.c` (4). `a2.c` (`v0 = rand()` kept and the last two `v0`
statements folded into one) scores 17. The mechanical search's best, "R12 width v0 s32->u16 + R7 do-while" (1), was a
do-while barrier on top of a width change. It did not touch the variable's scope, which is the real defect.

## (f) Where the method fell short

- Nothing important. METHOD's "count first" and "a local reused across statement groups dies more than once"
  (the c1/c8 bullet) named it. The cross-jump half was METHOD's c6/c10 bullet in reverse: here the target's single copy
  of the stores is the cross-jumped one, so the source must have two.
- The search family has no move "duplicate a post-join statement into both arms" (the inverse of cross-jump). Pack B
  (func_80168D94) has the same head and closes with the same move.

Scratch: `scratch/sc.sh` (scoring), `scratch/dump.sh <body> <tag>` (splice into `tu_free.c` + `tools/cc1_dumps_tu.sh`),
`scratch/a/` (candidates), `scratch/dumps_free/`, `scratch/dumps_fin/`.
