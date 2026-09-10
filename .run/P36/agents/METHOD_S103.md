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
