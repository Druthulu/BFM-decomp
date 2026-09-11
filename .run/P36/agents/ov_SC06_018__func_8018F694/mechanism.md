# func_8018F694 (src/ov_SC06_018/ov_SC06_018_jr_80187AEC.c) — d13, P36 T7 S104 — CLOSED at 0, zero levers

**Final: score 0 (478/478 ins, byte-identical), plain C.** Lever count 1 → 0. The whole change against `body_free.c`
is one line:

    -                c = t >> 6;
    +                c = (s16)t >> 6;

The same one-line move (plus deleting the launder line) closes **all five** copies of this text in the tree — each
`--try` at 0 (bodies in `scratch/copy_<fn>.c`):

| function | TU | ins | score |
|---|---|---|---|
| func_8018F694 | src/ov_SC06_018/ov_SC06_018_jr_80187AEC.c | 478 | 0 |
| func_8018C3F8 | src/ov_SC06_018/ov_SC06_018_jr_80187AEC.c (the variant that calls func_8018C7A8) | 236 | 0 |
| func_801875D0 | src/ov_SC06_032/ov_SC06_032_jr_80182890.c | 236 | 0 |
| func_8018F3E4 | src/ov_SC06_032/ov_SC06_032_jr_80182890.c | 478 | 0 |
| func_8018B3D0 | src/ov_SC06_033/ov_SC06_033_jr_80186574.c | 478 | 0 |

(Found by `grep -rn -A1 "t = bp->tm;" src/ | grep launder` → exactly 5 sites.)

## (a) The residual
COUNT +2. `t = bp->tm` (an `s16` field) loaded as `lhu v0; sll s2,v0,16; sra a1,s2,16` where the target has one
`lh a1`, and `c = t >> 6` came out as `sra s2,s2,22`, reading the **sll temp**, where the target has `sra s2,a1,6`. No
register or order defect anywhere else. The count settled it at once: two instructions too many, both in the
sign extension.

## (b) The pass and the decision (proved on dumps, `scratch/dumps_free/`, `scratch/dumps_w1/`)
1. **Expand** — `mips.md:2340-2359` `extendhisi2`: at -O2 `force_not_mem` (`:2346`) turns every `(int)` of an s16 memory
   read into `movhi P92 ← mem; P93 = subreg(P92) << 16; t = P93 >> 16`. Combine normally turns that back into `lh`.
2. **cse1** — `fold_rtx`'s associative block `cse.c:5577-5667`: for `c = t >> 6`, `lookup_as_function (t, ASHIFTRT)`
   (`:5594`) finds `(ashiftrt P93 16)` in t's class and rewrites the shift as `P93 >> 22` (6+16, `:5630-5666`). Seen in the
   free compile's `.cse` dump, insn 103: `(ashiftrt:SI (reg:SI 93) (const_int 22))`. **This settles the cookbook §197-A
   "cse vs combine" argument: it is cse.** Combine only suffers the consequence.
3. **combine** — P93 now has two readers (t's `sra 16` and c's `sra 22`), so the 3-insn combine at t's insn keeps I2
   (`added_sets_2 = ! dead_or_set_p (i3, i2dest)`, `combine.c:1458`), the PARALLEL does not match, and `lh` is never
   formed → `lhu; sll; sra` plus `sra 22`.

## (c) The move that closed it, and why it works
`c = (s16)t >> 6;` — the cast sits on the operand of this one shift. t is a sign-extended s16 already, so the value is
unchanged.
- `c-typeck.c:2418-2450` (`short_shift`): a constant right shift of an operand that narrows to `short` is done IN
  `short`. Expand widens it (`expand_binop`, ashr isn't in the no-extend list) with a sign extension of `(subreg:HI t)`
  → a **second** extension pair whose `ashift` operand is **t's own pseudo (78)**, not the load's temp.
- cse still folds, but into that new pair: `.cse` insns 103/105 = `P110 = t << 16; P111 = P110 >> 22`. The load's temp
  P93 keeps ONE reader, so combine forms `(set t (sign_extend:SI (mem:HI)))` = `lh` (`.combine` insn 51,
  `extendhisi2_internal`).
- combine then collapses `(ashiftrt (ashift t 16) 22)` to `(ashiftrt t 6)` because `num_sign_bit_copies (t) = 17 > 16`
  (`simplify_shift_const`, `combine.c:7930-7944`). The truncate/re-extend back to `int` goes away the same way.
  `.combine` insn 107: `(set (reg/v:SI 79) (ashiftrt:SI (reg/v:SI 78) (const_int 6)))` = the target's `sra s2,a1,6`.

The cast does not add or hide a term. It spells the shift at the width the field has, a width/cast move of the R12
family, put on the one USE instead of on the declaration.

## (d) GENERATOR PROPOSAL
When the residual shows `lhu; sll 16; sra 16` where the target has `lh`, AND one `sra 16+N` (or `sra 24+N` after
`lbu`) where the target has `sra N`, find the source's constant right shift `v >> N` of the narrow-loaded value and
rewrite that one site as `(s16)v >> N` (`(s8)v >> N` for the byte case). Change only the shift whose count shows +16.
Casting the other uses too breaks it: see w3 below. This could be a new R-family ("narrow the shifted operand at
the use"). The tell is mechanical: the mine-side count is exactly target+16 and it reads the `sll` register.

## (e) What did NOT work (all `--try`, bytes)
| spelling | score | why |
|---|---|---|
| body_free (start) | 5 | cse fold into the load temp (above) |
| `s16 t;` (declaration width) | 5 | t becomes a HI pseudo; the compare's extension pair is in the table and c's widening is cse'd onto it → same fold |
| `s16 t, c, d;` / `s32 t; s16 c, d;` | 5 / 5 | the destination width is irrelevant; the fold is on the operand |
| `u16 t;` (the sweep's R12 best) | 2 | `lhu` + `srl`: wrong signedness, not a real near-miss |
| `do { c = t >> 6; } while (0);` | 8 | the LOOP_END note comes after c, so nothing is blocked |
| `do { t = bp->tm; } while (0);` | 5 | the NOTE_INSN_LOOP_END stops cse1 (`cse.c:8054`, `.cse` has no `const_int 22`) but cse2 runs with `after_loop=1`, ignores the note and folds (`.cse2` has it). A note is not enough for this fold; you would need a real label with uses, in both cse passes |
| `c = (t << 16) >> 22;` | 0 | same mechanism, spelled by hand, less readable. Rejected for the cast |
| `(s16)t` on c AND d | 21 | d's extra pair changes allocation (register permutation a1/v1/a2) |

Controls I read and did not need: `cse_end_of_basic_block` (`cse.c:8039-8187`) + `cse_basic_block` (`:8513-8563`, it
keeps going past a label whose only use was the fall-through). Only a label with real uses would split the ebb, and
no natural source puts one there.

## (f) Where the method fell short
- The cookbook entry that fits this residual exactly (§197-A) says **"Do not chase it with casts, widths, or a `u16`
  spelling"** and names the asm re-tie as the cure. That is refuted for casts. The declaration-width casts it tested
  are inert (confirmed: `s16 t` = 5), but a cast on the SHIFT's operand is the plain-C cure. §197-A needs a
  correction: "cast the shifted operand at the use, `(s16)v >> N`, not the declaration". Its contested attribution is
  also settled: cse `fold_rtx` (`cse.c:5594`), from the `.cse` dump.
- No sweep family (R2–R26) moves a cast onto one use site. R12 changes declaration widths only, which is why the sweep
  stopped at 2 via the wrong-sign `u16`.
- Nothing else was missing: neighbours.txt had no note on this, and the allocation table was not needed. Counting and
  one cse dump were enough.

## (g) Structs answer
Inert here. The access is already a struct field (`bp->tm`, `s16` in `Blip_8018F694`, `src/shared/engine_types.h:724-728`),
and `body_free.c` with that struct scores 5. The deciding pass is cse's value-equivalence lookup on the extension
pair (`cse.c:5594`), keyed on the **type of the value at the shift**. It has nothing to do with memory accesses or
aliasing (`expr.c:4568-4577` / `sched.c` true_dependence), so no struct retyping would move it. This lever was a
**type-at-use** problem, not a struct problem. Nothing to test on bytes beyond what body_free already is.

Files: `body.c` (the closed text), `scratch/copy_func_8018C3F8.c`, `scratch/copy_func_801875D0.c`,
`scratch/copy_func_8018F3E4.c`, `scratch/copy_func_8018B3D0.c` (the other four copies, launder line removed + the same
cast), dumps in `scratch/dumps_free/` (start), `scratch/dumps_vd/` (do-while control), `scratch/dumps_w1/` (the close).
