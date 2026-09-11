# func_80181744 (ov_SC04_004_jr_8017AE2C.c) — d32, P36 T7 S104

**Result: score 0 in plain C with zero levers.** It started at 14 lever-free (the regen best was 8) with 3 levers in the tree:
a `$2` pin, a `$3` pin and a `"memory"` launder. The same text, with only the per-overlay symbols renamed, also closes the
class's two other copies (table at the end): 3 bodies, 9 levers removed.

## (a) The residual (14, COUNT 65 vs 67)
It has three separate defects, and each needs its own move:
1. **Two instructions missing in the `0x102 != 0` arm.** The target has `lh v0; beqz v0,else; move v1,v0; j join;
   addiu v0,v1,-1`. Mine had `bnez a1,join; addiu a1,a1,-1`. Mine had no copy, so reorg put the one-insn arm into an
   inverted branch's delay slot. The tree faked the copy with `tmp`/`$3` and the launder asm.
2. **A hidden frame defect.** It appears as soon as (1) is fixed: the frame grows from 40 to 48.
3. **A register permutation in the late block.** The target has `lw v0,32(s0); lhu a1,262(s0); lhu v1,18(v0)`. Mine had the
   pointer in `a1`, `0x106` in `v1` and the sum in `v0`. The tree pinned the pointer to `$2`.

## (b) The passes and decisions (tools/reference/gcc-2.7.2)
- **Defect 1: combine's sign-extend split, `combine.c:1887-1935`.** Under `-O2`, mips.md's `extendhisi2` expander
  (`config/mips/mips.md:2346-2357`) loads a `(mem:HI)` into a HImode pseudo R78 and sign-extends it with `sll 16`/`sra 16`
  through a temp R80. When the source decrements the field in memory, `(*(s16 *)(a0 + 0x102))--`, cse replaces the
  then-arm's reload of `mem:HI` with R78, so R78 stays live past the test. combine then combines the three insns
  (i1 = load, i2 = shl, i3 = sra). The resulting PARALLEL `[(set R79 (sign_extend mem)) (set R78 mem)]` is split by that
  special case into `R79 = sext(mem)` (the `lh`) and `R78 = (subreg:HI R79)`. That copy sits in the test block, before the
  branch, and combine never crosses blocks, so it survives. It is the target's `move v1,v0`: reorg moves it into the
  `beqz` delay slot, and the arm keeps two insns (`j` + `addiu`). **Proved** on the variant-B `.combine` dump (insn 65
  `(set (reg:HI 78) (subreg:HI (reg:SI 79) 0))`). Every spelling that makes the HImode copy in the ARM instead (an
  `s16 t = v0;`, `r = v0 - 1` with an `s16 r`; 18 variants, `scratch/v/H*`, `T*`) is folded by cse (the paradoxical
  `subreg:SI (subreg:HI P)` canonicalises back to P, `.cse` dump of T1c) or by combine, and scores 13–14.
- **Defect 2: an orphaned death note, `combine.c:10831-10845`.** The split is a 3-insn combine with a `newi2pat`, so
  `elim_i2` is 0 (`combine.c:2089`), and the shl temp R80's REG_DEAD note finds no insn when `distribute_notes` scans
  backward. It stops at the else-arm's CODE_LABEL and emits `(use (reg:SI 80))` there. R80 then has no real insn, and
  regclass (`regclass.c:922-947`) records it as `ST_REGS or none` (`.lreg` line "Register 80 … ST_REGS or none"). global
  gives it no hard register (it is missing from `.greg`'s dispositions), and reload gives it a 4-byte stack slot:
  `(use (mem:SI (plus sp 24)))` in the final `.greg`. No instruction touches that slot, but it is part of the ORIGINAL
  frame too. **So the decompiler's `s32 local[4]` (16 bytes) was the true local plus this phantom slot.** Shrinking it to
  the `s32 local;` that `func_80180AF0` actually writes (`*a2 = …`, one word; the sibling func_80181678 declares it the
  same way) restores the 40-byte frame. **Proved:** B with `local[4]` gives frame 48, and B with `local`, `local[1]` or
  `local[2]` gives frame 40 (`scratch/v/Bl*`).
- **Defect 3: local-alloc before global.** In the free body the `0x20` pointer is the function-wide `v0` variable, and it
  is live in several blocks (call result, pointer, `rand()` result), so global allocates it. local-alloc has already given
  the block-local 0x12-load/sum and 0x106 pseudos `$2`/`$3` (`local-alloc.c` `block_alloc`, class order), so global puts the
  pointer in `a1` (its `.greg` conflicts list 2, 3, 4). If the pointer is block-local (inlined into the `+=`, or a block
  `s32 p`), local-alloc allocates it FIRST in block 9 (R95, 3 refs, "pointer"). It takes `$2`, and the others fall to
  `v1`/`a1`, which is the target. **Proved** on bytes (`scratch/v/L*`: the pointer inlined or block-local → 0; the
  function-wide `v0` kept → 5). The claim about the order inside local-alloc is from `.greg`/`.lreg`; I did not trace it
  through `qty_compare`.

## (c) The moves that closed it (joint: 1 alone = 11, 1+2 = 5, 1+2+3 = 0; 3 alone = 10, 2 alone = 20, 2+3 = 16, 1+3 = 6)
1. Write the `0x102` timer as a memory decrement with one store per arm: `if (*(s16 *)(a0 + 0x102) != 0)
   (*(s16 *)(a0 + 0x102))--; else { … *(s16 *)(a0 + 0x102) = 4; / = 0x20; }`. Cross-jump re-merges the three `sh`s
   into one. `--(*(s16 *)(a0 + 0x104))` for the counter is byte-neutral and reads better than the `cnt` temp.
2. `s32 local[4];` → `s32 local;` (passed as `&local`). This is not a lever: it is the variable's real size. The phantom
   slot is the compiler's own.
3. Write the late add as `*(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) += *(u16 *)(a0 + 0x106);`, which makes the pointer
   block-local. The `v0` variable then disappears: `if (func_80180AF0(…) == 1)` and `(rand() & 0x20) - 0x10` are written
   inline, like this overlay's sibling at line 5841.

## (d) Generator proposal
When the target shows `lh vA,K(p); beqz vA; move vB,vA; j join; addiu vA,vB,-1` (an s16 field decremented in one arm and
stored at the join), rewrite `v = *(s16 *)(p+K); if (v) v--/v = v-1; else {… v = C;} *(s16 *)(p+K) = v;` as a MEMORY
decrement with one store per arm, `(*(s16 *)(p+K))--`, AND, if the candidate's frame then comes out exactly 8 bytes too
big with no insn touching the new slot, shrink the decompiler's stack-array local to the size its callee writes
(combine's orphaned-USE phantom slot, `combine.c:10831`). Separately: a function-wide temp reused as a block-local pointer
(`v0 = *(s32 *)(a0 + K); … v0 + off …`) → inline it or declare it in the block (local-alloc takes it before global runs).

## (e) What did not work (byte evidence, all in scratch/v/)
- A/A2 (`s16 t` loaded, `t--`, one store): 15. Same combine split and phantom slot, but `t` is both the load and the
  result, so `addiu v1,v1,-1` instead of `addiu v0,v1,-1`.
- H1–H10, T1–T5 (an HImode copy made in the arm or before the `if`, from an SImode `v0`): 11–15. cse or combine folds
  the copy.
- C/H9 (`*(s16 *)(a0 + 0x102) = v0 - 1` per arm, SImode test): 11, still 65 insns.
- Only moves 1 and 3, keeping `local[4]`: 6 (frame 48).

## (f) Where the method fell short
- Count-first was right (65 vs 67), but the missing instructions came from a combine SPLIT that CREATES a copy (the
  inverse of step 3's "a copy cse deleted"). The method list has no "combine adds an insn" entry. Add one: *a
  `move` right after an `lh` whose source is the loaded register = combine.c:1887's sign-extend split; the source reads
  the field twice (the test and a memory `--`/`+=`).*
- The frame residual was a compiler artefact (a USE-only pseudo spilled) hidden inside a decompiler-sized array. The
  tree's pins had been compensating for it without anyone knowing. Rule: **a decompiler's `local[N]` sized from the
  frame is a guess; a candidate that is right except the frame is 8 bytes too big → shrink the array.** `.lreg`'s
  "ST_REGS or none" line on a 2-ref pseudo is the signature.
- The alloc table was not needed. Every defect showed up in the `.combine`/`.lreg` dumps of one targeted variant (B).

## (g) The structs question
Structs are byte-neutral here, and they were not the missing piece. `scratch/v/struct3.c` declares a body-local `E744 {
+0x1C s32 state; +0x20 u8 *sub; +0xAA s16 unkAA; +0x102 s16 t102; +0x104 s16 c104; +0x106 u16 v106; }` and writes
`e->t102--`, `--e->c104`, `*(u16 *)(e->sub + 0x12) += e->v106`. It scores **0**, but only when EVERY access (the call
arguments included) goes through `e`. With `a0` and `e` both live, it scores 13, because two pseudos cross the calls
(`s0`/`s1`). So the struct spelling wants the parameter itself typed `E744 *`, which is a signature change for the
structs phase. The deciding moves (a memory decrement instead of a temp, the local's real size, a block-local pointer) live
in expression shape and frame layout, not in `expr.c:4568`'s aggregate-vs-scalar alias channel. Field types proven by the
bytes: `0x102`/`0x104` are s16 (`lh`, and the sll-16 test), `0x106` is read as u16 (`lhu`), and `sub + 0x12` is u16.

## Copies of this class (the same text, symbols renamed; each `--try` = 0)
| function | TU | file |
|---|---|---|
| func_80181744 | src/ov_SC04_004/ov_SC04_004_jr_8017AE2C.c | PACK/body.c (= scratch/copies/func_80181744.c) |
| func_801806E8 | src/ov_SC04_003/ov_SC04_003_jr_8017BEBC.c | PACK/scratch/copies/func_801806E8.c (func_8017FA94, D_8019760C, func_8017FF9C) |
| func_801831B8 | src/ov_SC04_002/ov_SC04_002_jr_8017BEBC.c | PACK/scratch/copies/func_801831B8.c (func_80182564, D_801A86E4, func_80182A6C) |

Levers: 9 → 0 (3 per copy: pin $2, pin $3, launder).
