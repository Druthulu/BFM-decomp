# func_80175AB8 (ov_SC04_011_jr_801734BC.c) — T7 agent c11 — CLOSED, score 0

Start: lever-free score 41 (mine 191 / target 188). Final: **score 0**, `PACK/body.c`, with no register pin, no asm, no
added volatile (the `*(volatile u32 *)&slot[6]` store was already in body_free.c and is still needed: removing it
scores 20), no zero term, and no declaration alias. Four source moves, each one needed (ablation on the final body:
a -> 30, b -> 37, c -> 8, d -> 3).

## (a) The residual, one sentence per part

- (A) The target keeps `&D_8011F7F0` in `$s2` for the whole function and reads the two late fields as `-52($s2)`/`-50($s2)`.
  Mine folded every late field read to an absolute `lui/lhu` and dropped the pointer, which is 3 extra instructions and
  a callee-saved register renumbering (`s2->s3`, `s3->s4`). This was the launder lever, and it is 30 of the 41 points.
- (B) The target computes `(s16)(r1 + r2)` in `$a1`; mine computed it in `$s0` (the `$4`/`$5` pins).
- (C) Mine hoisted the `D_80193B4C[idx]` table load above the `D_8011F83A = idx` store (the memory barrier).

## (b) Pass, decision, file:line (every claim below was checked in this function's own dumps, PACK/scratch/d_FIN)

(A) is a cse1/cse2 split. It takes two source facts, and both are needed.
1. `fold_rtx` tries its **associate** path before it tries constant folding (`cse.c:5580-5667`, then `simplify_binary_operation` at
   `:5670`). For an address `(plus arr 20)`, where `arr`'s class holds `(plus base -72)` (the kept `arr = base - 0x48`
   insn), `lookup_as_function` (`cse.c:1224`) returns that PLUS, so the fold gives `(plus base -52)` and returns
   **before** the fold to a constant. A read written relative to `base` (`base - 0x34`) has no PLUS in `base`'s class,
   so it goes straight to `const(D_8011F7F0-52)` through `find_best_addr` (`cse.c:2622`, the validate_change of
   fold_rtx). Result: fields read through `arr` stay register-relative, and fields read through `base` go absolute.
2. The fold is only safe if **cse1 does not see the late reads** (if cse1 turns them into `(plus base -52)`, cse2 folds
   that to a constant, which I proved in an experiment: 7 folded in cse2). The clamp written
   `(D_8011F824 < 1000) ? D_8011F824 : 0x3E7` (the global read twice) reaches jump1 as an if/else whose then-arm is TWO
   insns (reload + zero_extend). The if/else -> `x = b; if (..) x = a;` rewrite at `jump.c:699-750` needs a single
   `x = a` insn (`:728`), so it does not fire. cse1's TAKEN path then stops at the join CODE_LABEL (`cse.c:8039`), and
   the late reads are processed in a fresh block ("Processing block from 165 to 0"), so they stay `(plus arr 20)`.
   cse1 turns the reload into a copy, `delete_dead_from_cse` (`toplev.c:2867`) deletes it, the post-cse1 jump pass
   (`toplev.c:2869-2870`, always run at -O2) now applies the if/else rewrite (1 label left), and cse2 follows the path
   AROUND, sees `arr`'s class and associates the reads to `(plus base -52)`. Nothing after cse2 folds addresses.
   Target shape confirmed: 6 `(plus reg75 ..)` in cse1, 6 `(plus reg74 ..)` in cse2.
(B) local-alloc's tie. At `sum = r1 + v0`, `combine_regs` (`local-alloc.c:1722`) ties the result to the first operand
   that dies there (r1, which crosses a call, so `$s0`). The tie is refused only if the destination is not a local
   pseudo (`:1774`, `reg_qty[sreg] == -1`). Reusing ONE temp `t` for the B0 call result
   (`t = func_801783D0(D_8011F804, 0)`) and for the sum makes `t` live in blocks 0 and 2, so flow marks it
   REG_BLOCK_GLOBAL (`flow.c:1204/1428`). That mark is sticky even after combine folds away its first life ("used 4
   times across 2 insns", no block). global then sees the non-copy preferences `5 16` (a1 from `set_preference`
   `global.c:1535` on the shift insn, s0 from the add's first operand), and `find_reg`'s preference scan
   (`global.c:1037-1071`, ascending regno) picks `$a1`.
(C) sched1 alias. `expand_expr` INDIRECT_REF (`expr.c:4568-4575`) marks `p[i]` MEM_IN_STRUCT_P (its operand is a
   PLUS_EXPR). `true_dependence` (`sched.c:817`, exclusions at +18/+21) declares a varying-address in-struct load
   independent of a fixed-address scalar store, so the load is hoisted. Wrapping the arithmetic in a cast
   (`*(u8 **)((u8 *)D_80193B4C + idx * 4)`) makes the operand a NOP_EXPR: the load is not /s, `memrefs_conflict_p`
   reports a conflict, and the load stays after the store. (A test with `(&D_8011F7F0)[0x4A] = idx`, an in-struct
   store, gave the same order but the wrong relocation addend. That confirms the mechanism from the other side.)

## (c) The source moves that closed it

1. The late field reads go through the struct base: `*(u16 *)(arr + 0x14)` / `(arr + 0x16)`, not `(base - 0x34)` /
   `(base - 0x32)`. This is the same spelling the matched sibling func_80175DA8 uses (`s + 0x10`).
2. The clamp is a ternary that reads the global twice, placed in the call: `(D_8011F824 < 1000) ? D_8011F824 : 0x3E7`
   (`uv` and `k` deleted).
3. One temp `t` for both `a1` arguments: `t = func_801783D0(D_8011F804, 0); p = func_80177EA4(p, t, ...)` and later
   `t = func_801783D0(q >> 2, 8) + func_801783D0(a2v, 0);` (r1, r2, sum and a0v deleted; `(s32)(q << 16) >> 18`
   simplified to `q >> 2`).
4. The table read is byte-offset pointer arithmetic, `*(u8 **)((u8 *)D_80193B4C + idx * 4)`, which also drops the
   function-pointer cast on func_80024054.

## (d) Generator proposals

- (A) When the residual shows a global's address rematerialized as absolute `lui/l*` in the target's later blocks while
  the target holds it in an s-register: rewrite `*(T *)(base - K)` as `*(T *)(arr + (D - K))` for a derived pointer
  `arr = base - D` that the body already has. If the reads sit after an `if`/clamp, also try the clamp as a ternary that
  reads the global twice (a two-insn then-arm keeps jump1 from rewriting it, so cse1 stops at the join).
- (B) When a sum/temp lands in the callee-saved register of its dying operand but the target puts it in the argument
  register: reuse one temp variable for an earlier value that the target also passes in that same argument register,
  in a different basic block. That makes the pseudo REG_BLOCK_GLOBAL and routes it through global's preference scan.
- (C) When the diff shows an indexed table load hoisted above a scalar store: spell the index as
  `*(T *)((u8 *)TABLE + i * sizeof(T))` (a cast-wrapped PLUS, which is not MEM_IN_STRUCT_P).

## (e) What did not work, with byte evidence

- Clamp spellings on the old base-relative reads: if/else (41), a ternary on `uv` (48), `>=` forms (46/48), goto (41),
  a `k = uv; if (k>=1000)` form (40). All still folded, because cse followed the AROUND path.
- `do { } while (0)` around the clamp (43, the label merged past LOOP_END) or around the sv call (43). The second one
  broke cse1 but cse2 re-folded, which led to the cse1/cse2 split reading. Not used: it is a fence, not C.
- For (B): inlining the sum, operand swap (v0), s16/u16 sum, a 75-way width matrix over r1/r2/sum (all 3), and reusing
  `sv` (s16 or s32), `k` (30), `uv` (44), `r1` (56) or `r2` (2, the sum lands in v0 via the copy preference).
- For (C): `D_8011F83A[0]`, a struct field, and `*D_8011F83A` (8: the forced address register gets shared by the load
  and the store).

## (f) Where the method fell short

- The residual's register-pair line for (A) (`s2->s3 x4`) reads as a register problem, but it is a COUNT problem (a
  kept pointer versus rematerialized constants), which confirms METHOD step 2. The deciding fact was a
  **cse1-versus-cse2 difference**, and neither `residual_moves.md` nor the alloc table shows it: I had to add `-dt` (the
  cse2 dump) to the dump flags. **Proposal: `cc1_dumps_tu.sh` should dump cse2 (`-dt`) by default.** A fold that cse1
  avoids and cse2 re-applies is invisible without it.
- The allocation table closed (B) once I read the `.greg` preference line (`5 16`), but the fix was a local/global
  classification (flow's REG_BLOCK_GLOBAL), and the table only shows that as an empty `blk` column. It would help if
  the table stated "global because multi-block" versus "global because it dies twice".
- The sibling's body (func_80175DA8, `s + 0x10` reads) held the (A) spelling. METHOD step 3's "read the sibling
  bodies, not only the headers" is the step that would have found it first.
