# func_80176734 (ov_SC04_011_jr_801734BC.c) — T7 agent c18 — CLOSED, score 0

Start: lever-free score 90 (mine 364 / target 371). The mechanical best (g5: `chg` u16, `amp` s16, block-A stores swapped)
was 32; no `best_body.c` was in the pack, so I rebuilt that text from `history.txt`'s path. Final: **score 0**, in
`PACK/body.c`. I compared the `--try` object's objdump with the tree object (`build/src/ov_SC04_011/ov_SC04_011_jr_801734BC.o`),
relocations included, and they are byte-identical. The body has no register pin, no asm, no added volatile, no zero term
and no alias. `u8 dum[8]` (the dead frame slot), `pv` and `ix` come from body_free.c and are still needed: removing any
one of them scores 18, 32 and 32.

## (a) The residual, one sentence per part

- (A) Blocks A–C, 11 register pairs. The target has the sprite pointer in `$a1` and block A's `q` in `$a0`; block B's
  index base is in `$a0`. Mine had them the other way round, and block B's `pp` was in `$v1`.
- (B) Callee-saved shift `s4->s3`/`s5->s4`. The g5 widths (`chg` s16/u16, `amp` s16) already fix it.
- (C) Block J has 2 MISSING instructions: the `move $v1,$s5` copy of `chg` and the second test `beqz $v1 -> Lzero`.
  Mine folded that test into a `j`.
- (D) The block-I change flag is in `$s0` in the target (the same register as `amp`) and in `$a0` in mine.
- (E) Block I has 1 MISSING instruction: `move $v1,$a1` (a copy of `tgt`), stored and then masked in place
  (`andi $v1,$v1,0xff`). Mine stored `$a1` and masked into a fresh register.

## (b) Pass, decision, file:line. Every claim was checked in this function's own dumps (PACK/scratch/dumps_fin)

(A) global.c `find_reg`. Merged, `p` is one pseudo (r82): 12 refs across 41 insns, priority 8780, hard conflicts
    `v0,v1,a0`. The `a0` conflict comes from block B's local index base, which local-alloc put in `$a0` and which is live
    inside p's block-B range. So the scan in ascending regno order (`global.c:945-990`) lands on `$a1`. Block A's `q`
    (r85, priority 1818) is allocated later and gets `$a0`. When the pointer was split, block A's `p` was a
    5-ref/16-insn pseudo (priority 6250) whose only hard conflict was `v0`, so it took `$a0` first.
(C)+(B) This is combine, not cse. `chg` is `short`, and there is no PROMOTE_MODE on MIPS (config/mips/mips.h defines none).
    So every `chg != 0` expands to an sll/sra sign extension. At the outer test, cse1 gives the extension (r267) two users:
    the outer `bnez` and the inner `beqz`. The inner test sits after a label, on cse's AROUND path (`cse.c:8173-8177`).
    That path records no equivalence for the skipped jump (`cse.c:8446-8450` calls only `invalidate_skipped_block`), so
    cse does not know r267 == 0 there and keeps the test. The inner `amp != 0` IS deleted, because amp == 0 was recorded
    at the earlier fall-through (`cse.c:7511`). combine then simplifies `(ashiftrt (ashift chg 16) 16)` to `chg`
    (`combine.c:7932-7942`). This works because `num_sign_bit_copies` of `chg` is above 16: every set of it is a 0/1
    value, and the table is built by `set_nonzero_bits_and_sign_copies`, `combine.c:718`. r267 has two users, so it
    cannot be substituted into them. It survives as the register copy `move $v1,$s5`. After cse2, `thread_jumps`
    (`jump.c:4161`) redirects the outer `bnez r267 -> T` past `T: beqz r267` (the same condition with the opposite
    sense, and the label is reached with no insns between) to Lbig. That gives the exact target shape.
    `amp` is `short` for the same combine reason. Its join-point widening `(s32)amp` for the `!= 0`/`/` users becomes the
    surviving `move $v0,$s0` (combine dump, insn 638: `(set r228 (subreg:SI (reg/v:HI 78)))`).
(D) Source fact, not a pass decision. The author reuses `amp` as block I's change flag, so it is one pseudo and gets one
    hard register (`$s0`, because amp crosses the switch calls).
(E) cse1 `(set REG0 REG1)`. A `u16 v = tgt` is a same-mode copy: `make_regs_eqv` (`cse.c:826-862`) keeps `tgt`
    canonical, because it lives longer, the uses of `v` become `tgt`, and the copy dies. A `u8 v = tgt` is
    `(set (reg:QI v) (subreg:QI tgt))`, which is not a REG source, so it survives. `v` is block-local, so local-alloc gives
    it `$v1`, and the zero_extend of `v` for the compare is tied to it where it dies. That is the in-place `andi $v1,$v1,0xff`.

## (c) The source moves that closed it (applied to g5 = 32)

1. One variable `p` for the sprite pointer in blocks A, B (both loads) and C. The four variables p/pp/q/pp are gone, and
   the block-A stores are back in their body_free order. Result 32 -> 19.
2. Block J/K is written as the nested if that the bytes show:
   `if (amp || chg || flag[0x47]) { if (amp || chg) { ...slew...; flag[0x47] = 1; } else flag[0x47] = 0; }`.
   The gotos and the `c = chg` copy are gone. Result 19 -> 15 (with `chg` s16).
3. `chg2` is deleted, and block I's change flag is written into `amp`. Result 15 -> 8.
4. Block I's `v` is `u8` (it was `u16`), and the compare is `cach[0x47] != v`. Result 8 -> 0.
Cleanups at 0: `av` is inlined (`amp` is tested and divided directly), and block F's `t` is inlined (`chg = (st[7] != m)`).
Both still score 0.

Ablation on the final body (one move undone at a time): p split in block C -> 2; chg2 separate -> 12; J in goto form with
`c = chg` -> 8; v u16 -> 9; chg u16 -> 1 (the whole callee-saved bank shifts); chg s32 -> 53; amp s32 -> 22;
amp u16 -> 5. `tgt` u16 or s16 both score 0 (I kept u16, which matches the `lhu`).

## (d) Generator proposals

- (A) When one argument/temporary register holds "the same" pointer in several consecutive blocks of the target, but
  mine spreads those reloads over different registers: MERGE the per-block locals that are loaded from the same
  expression into ONE function-scope variable. The joint live range picks up the hard conflicts of the blocks' local
  pseudos and pushes the pointer to the target's register (generator: "R24 merge same-source block locals").
- (C) When the target has a `move $vN,$sK` copy of a flag that is then tested twice with a label between, write the
  flag as `short` and test it in a nested `if (a || flag || x) { if (a || flag) ... }`. Do not try a copy variable
  plus a fence: combine turns the s16 widening into the copy, and cse's AROUND path keeps the second test.
- (D) When two flags the source keeps apart share one callee-saved register in the target (one of them does not cross
  a call), make them ONE variable.
- (E) When a `move` copy of a wider local is missing before a byte store and an in-place `andi 0xff`: declare the copy
  `u8`. A narrowing copy is a SUBREG move that cse keeps. This is the byte-sized twin of generator R20 (c4's u16 lesson).

## (e) What did not work (byte evidence)

- `tgt` s32/u32 with a u16 `v` (m3: 35). The copy still folded, and chg2 moved.
- `v` inlined as `(u8)tgt` (8): no copy, as expected.
- `q` computed inside the `if` arm (12): it must be in the entry block.
- Merging block D's `pp` into `p` too (6): the target keeps D's pointer in `$a0`, so it is a separate variable.
- Keeping the goto form of block J (8): with no label between the two tests, cse knows `c == 0` and folds the second
  test, which is why the tree needed a launder there.

## (f) Where the method fell short

- The pack had no `best_body.c` although the brief named it. I rebuilt it from `history.txt`, and the path's two R7
  moves cancel out.
- The residual view hides the real pattern: **the same hard register for one role across many blocks** (`$a1` for the
  sprite pointer in A/B/C, `$s0` for amp/chg2, `$v1` for nearly every byte temp). Reading the whole objdump for "which
  register does this role live in, block by block" found moves 1 and 3 in two compiles. A census tool that groups the
  target's registers by the source expression they hold, and flags a register that holds one role across blocks, would
  make "merge the locals" mechanical.
- The tree's `c = chg` + launder had the wrong mechanism. The copy is combine's reduced sign extension, not a C copy.
  The class list in METHOD_S103 had no entry for "a copy created by combine from a narrow type's extension".
