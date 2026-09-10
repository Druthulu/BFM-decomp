# The method that closed 14 of 22 in S102 (S103 addendum to PROMPT.md — read it after PROMPT.md, it takes precedence)

0. Read `PACK/neighbours.txt` first. One agent closed on its FIRST `--try` because a sibling's header spelled the crack out
   in English. **A `@stuck:` note is a CLAIM: two were refuted on bytes last session.**
1. Dump the target function WHOLE off the tree's own object (`mipsel-linux-gnu-objdump -drz build/src/<tu>.o`, the tree
   object is byte-identical to the original), not the residual's hunks — the hunk view scrambles moves into branch delay
   slots and hides a repeated shape. Dump your candidate's object the same way from your `PACK/scratch/` compile.
2. **COUNT FIRST.** The residual text cannot tell you whether an instruction is MISSING or the registers are WRONG; one
   agent chased a register theory for hours when cse had forwarded a just-stored value and deleted a load.
3. If instructions are missing (or extra), ask what emits them. The answers last session:
   - a dropped call argument (the call declaration was narrower than the callee — pass the argument the target passes);
   - a copy cse deleted because the producer sat immediately before it (move the producer away / reorder, generator R21);
   - a copy deleted because two locals shared a WIDTH (give one local the width the bytes prove, generator R20);
   - a block merged by cross-jump, whose equality test compares symbol names BY POINTER, so a body-local
     `extern T alias __asm__("SYM");` keeps the blocks apart at zero byte cost (this is a DECLARATION alias, allowed);
   - a call-result copy folded by combine into its single use (`combine.c:914-917`, no SMALL_REGISTER_CLASSES on MIPS).
   - (S103 c2) an EXTRA instruction per loop iteration + an extra callee-saved register = a second walked pointer
     (`q = p + k`, both stepped): loop.c strength reduction keeps both bivs. Delete `q`, write `q[i]` as `p[i+k]`; the
     field read that is textually LAST becomes the base giv (`record_giv` prepends, loop.c:4421; `combine_givs` :5494).
     Add `-dL` to the dump flags for any count gap inside a loop — its "Cannot eliminate biv" lines name the defect.
   - (S103 c4) MISSING `move`s / second `andi 0xffff` on a value used masked or cast to 16 bits: re-declare the copy's
     destination (or a post-decremented counter) as `u16`/`s16`, splitting it out of any comma declaration list. No
     PROMOTE_MODE on MIPS gcc 2.7.2, so a u16 local is a HImode pseudo: a same-mode SI copy is folded by cse's
     `(set REG0 REG1)` case (`cse.c:7440-7474`, gate `:7455` wants a REG source), a copy into HImode is a SUBREG move and
     survives; a u16 `cnt--` takes `copy_to_reg` (`expr.c:8645`). Several joint width moves may be needed at once.
   - (S103 c3/c12) a MISSING `move sK,$aN` whose source has no visible reader, but `$aN` reaches a `jal`/`jalr` (a
     dispatch-table handler) unwritten on another path: the handler READS it implicitly. Pass the value as that call's
     argument N-4 (widen the table's declaration in the body: `extern s32 (*D_x[])(void *, s32);`) AND reuse the source
     variable later as the LATER operand of a sum, so its last mention comes after the copy's (`make_regs_eqv`,
     `cse.c:846-862`; the swap `cse.c:7454`). Neither move helps alone. A consumer count that ignores calls reading
     `$a0-$a3` will call this "unreachable" — it was wrong twice.
   - (S103 c6/c10) MISSING instructions + `j` stubs into the MIDDLE of a common sequence in the target = post-reload
     CROSS-JUMP (`toplev.c:3142`, `find_cross_jump` `jump.c:2371`). Two opposite uses: (c6) a shared `goto do_call` tail
     rewritten as one call per site raises the allocator's ref count for the call's arguments, and cross-jump re-merges
     the calls AFTER allocation, so the bytes keep one; (c10) two identical tails merged that the target keeps apart —
     make their SHAPES differ (a loop's exits falling to the function's single final `return`).
   - (S103 c10) a parameter-vs-local callee-saved swap: pass the parameters through to a callee at its REAL arity (one
     more ref each for `allocno_compare`, zero bytes — jump2 deletes the self-copies, `jump.c:425-462`).
   - (S103 c5) a WHOLE missing test (a second null check): compile once with `-fno-thread-jumps`; if that reproduces the
     target, it is jump threading (`jump.c:4161`) — re-read the value from memory before the second test.
   - (S103 c7) a callee-saved swap where the loser is short on refs: duplicate a join-point statement (a pointer/counter
     step) into both arms of the if/else inside the loop — loop uses count double (`flow.c:2067`); check
     `floor_log2(refs)·refs/live` beats the rival first.
   - (S103 c1/c8) a register permutation among pointers/temps: a local REUSED across statement groups dies more than once
     and is refused by local-alloc (`local-alloc.c:472`) — split it into one name per value (generator R23 does this).
     `tools/alloc_table.py` prints the GLOBAL priority; local-alloc ranks by `qty_compare_1` (`local-alloc.c:1598`) —
     `../ov_SC04_011__func_80135168/scratch/lpri.py` computes that from the `.lreg` dump.
   - (S103 c11) the target keeps a global's address in a callee-saved register but yours rematerialises `lui`/absolute
     loads (a "launder" lever): write the late field reads relative to a DERIVED pointer the body already has
     (`*(T *)(arr + (D - K))`, not `*(T *)(base - K)`) — fold_rtx re-associates before folding (`cse.c:5580-5667`) and
     `find_best_addr` (`cse.c:2622`) folds base-relative reads to absolute; the FIRST cse pass must not reach them (a
     two-insn clamp arm stops it at the join label, `cse.c:8039`); the second pass (`.cse2`, dump flag `-dt`) re-associates.
   - (S103 c11) a value tied into the wrong register by local-alloc (`local-alloc.c:1722`, refused when the destination is
     not local, `:1774`): REUSE one temp across blocks so flow makes it block-global (`flow.c:1204/1428`) and global.c's
     preference scan (`:1535`, `:1037-1071`) picks the argument register.
   - (S103 c11) a table load hoisted over a store (a `"memory"` barrier lever): `p[i]` is an aggregate access
     (`expr.c:4568-4575`) that `true_dependence` (`sched.c:817`) treats as independent of a scalar store; a cast-wrapped
     byte-offset read (`*(u8 **)((u8 *)tbl + i * 4)`) is not marked and stays after the store.
   - (S103 c18) the INVERSE of the split: when the target keeps ONE register for one role across several blocks (the same
     `$aN`/`$sN` loaded from the same expression in each), MERGE the per-block locals into one function-scope variable —
     one pseudo with the combined refs picks up the conflicts that put it in the target's register (`find_reg`,
     `global.c:945-990`). Read the whole objdump block by block for "same register, same role" — the hunk view hides it.
     Also: two flags the target keeps in ONE `$sN` → reuse one variable for both.
   - (S103 c18) a copy the target keeps after a `short` flag test (`move $v1,$sN`): combine reduces a sign extension of a
     0/1 value to a plain copy (`combine.c:7932-7942`, sign-bit copies `:718`) and the extension's second user keeps it —
     the tree's `c = chg` launder was faking exactly that copy; declare the flag `s16`, test it in a nested `||` if.
   - Dumps: `tools/cc1_dumps_tu.sh` now also writes `.cse2` (`-dt`) and `.jump2` (`-dJ`).
   - (S103 c10/c2/c4) READ LEVER-FREE BODIES that share your callees, globals or shapes ANYWHERE in the overlay, not only
     `neighbours.txt`: the answer to c10's function was in a different file (`func_80135888`), c4's was a sibling spelled
     lever-free under a stale `@stuck:` note. `grep -rln '<callee or global>' src/ov_SC04_011/`.
   - (S103 c2) grep the TU for the other functions that touch the same global/struct and READ THEIR BODIES, not only the
     headers in `neighbours.txt` — a sibling walking the same list gave the shape and the struct type.
4. Only then the allocation table (`tools/alloc_table.py`). Declaration-order moves are PROVABLY DEAD on a register
   residual whose allocnos have distinct priorities — `global.c:604-610` compares priority first and ties only by allocno
   number. Priority and live length are arithmetic: one body closed by moving a priority 6524 past 6666, another by
   shortening a live length from 44 to 43.
5. Many real closes are JOINT edits whose every single step scores worse than the start — do not abandon a move because it
   scored worse alone; try the combination the reading predicts.
6. Two REFUSALS: an invented identically-zero term (`x + 0*y`, `x - x`, a dummy dependency) is a compiler-forcing construct
   in C clothing and is NOT a close — the phase's rule is *ban the silence, not the lever*; and a body whose improvements
   are compensating errors is reported, not claimed. A plain `volatile` that the body did not already carry is also a lever.
7. Write `PACK/body.c` and `PACK/mechanism.md` EARLY and keep them current. All scratch under `PACK/scratch/`.
