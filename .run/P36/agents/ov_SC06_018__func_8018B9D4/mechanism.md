# func_8018B9D4 (src/ov_SC06_018/ov_SC06_018_jr_80187AEC.c), e5, P36 T7 S104: CLOSED at 0, zero levers

**Final: score 0 (81/81 ins, byte-identical, frame included), plain C.** Lever count 1 → 0 (the `$0` pin), and the
`s32 pad[2]` and `r1..r4` keepalives are gone as well. The whole change from `body_free.c`: the `var_ea/var_fe/var_a0/var_v0`
temp chain is replaced by direct field arithmetic on memory:

    if (*(s16 *)(param_1 + 0xEA) < *(s16 *)(param_1 + 0xFE)) {
        *(s16 *)(param_1 + 0xEA) += 0x40;
        if (*(s16 *)(param_1 + 0xEA) >= *(s16 *)(param_1 + 0xFE)) { ... }
    } else {
        *(s16 *)(param_1 + 0xE8) += 0x40;
        if (*(s16 *)(param_1 + 0xE8) < *(s16 *)(param_1 + 0xFE)) return;
        ...

The class's other copy closes with the same text (callees renamed): **func_80186BAC**
(src/ov_SC06_032/ov_SC06_032_jr_80182890.c) scores **0** (`scratch/copy_func_80186BAC.c`).

## (a) The residual
Same count (81/81). The target has `lh v0,234(s1); lh v1,254(s1); move a0,v0; slt v0,v0,v1; beqz; addiu v0,a0,64`. The
lever-free text has `lh v1; lh v0; nop; slt v0,v1,v0; addiu v0,v1,64`. The target keeps a **copy** of the loaded 0xEA value
(`move a0,v0`) that lives past the compare. The free text has no copy, and the compare and the add read one register.

## (b) The pass and the decision (proved on dumps, `scratch/dumps_n2e/`, `dumps_c1/`, `dumps_c5/`)
The copy comes from **combine's narrow-load split**, `combine.c:1887-1940`: when a 3-insn combination builds
`(parallel [(set A (sign_extend (mem:HI))) (set P (mem:HI))])` because the narrow load's destination P is still
needed, combine splits it into `A = sign_extend(mem)` (= `lh`) plus `P:HI = (subreg:HI A)`, a register copy.
- P is still needed because `*(s16 *)(p+0xEA) += 0x40` re-reads the halfword, and cse1 forwards that read to the
  HImode load pseudo P (`.cse` insn 104: `(plus:SI (subreg:SI (reg:HI 83)) 64)`). So P has two readers: the extension
  for the compare, and the add.
- `.combine` insns 92/93: `(set (reg:SI 85) (sign_extend:SI (mem:HI …234)))` and `(set (reg:HI 83) (subreg:HI (reg:SI 85) 0))`.
- The copy's source is a **SUBREG**, so local-alloc's `optimize_reg_copy_1` does not touch it. That function rewrites a
  later use of the source onto the copy so the two can be tied, and it is only called for `GET_CODE (SET_SRC) == REG`
  (`local-alloc.c:1003-1007`). A85 dies at the `slt` and not at the copy, so `combine_regs` cannot tie them either →
  two registers → `move a0,v0`.

Why each temp spelling fails (bytes + dumps):
- `var_a0 = var_ea` (s32): a REG-REG copy. cse canonicalises it onto var_ea and deletes it.
- `var_a0 = (s16)var_ea` (`c1`): cse keeps the re-extension, combine reduces it to `(set 79 77)` (sign-bit copies), and then
  **local-alloc's `optimize_reg_copy_1` rewrites the `slt` to read 79** (`.lreg` insn 103) and ties them. Score 5.
- `s16 var_a0; var_a0 = var_ea` (`c5`): a SUBREG copy, but cse `fold_rtx` SUBREG case (paradoxical subreg of a reg
  equivalent to a lowpart subreg → the inner reg) folds the add's `(subreg:SI (reg:HI 79))` back to 77. The copy dies. Score 5.
- So the copy has to be created **after** cse by combine, and with a SUBREG source. That is the 1887 split, and only
  a second READ of the same halfword creates it. A temp chain never does.

## (c) The move
Spell the field update as the original almost certainly wrote it, `*(s16 *)(p + 0xEA) += 0x40;`, and re-read the field
in the following test instead of reusing a temp: `if (*(s16 *)(p + 0xEA) >= …)`. The else arm takes the same spelling on
0xE8 (`+= 0x40` as `s16` or `u16`, both 0). The re-read after the store is forwarded by cse (store-to-load), and
the target's `sll/sra` of the stored value is exactly that forwarded extension. The frame also came out right with no
pad: `.frame vars=32` in both.

## (d) GENERATOR PROPOSAL
When the target keeps a `move rX,rY` right after an `lh rY` (or `lb`) and rX is used later only in an `addiu`/`sh` back
to the same field, rewrite the decompiler's temp chain `t = *(s16 *)(p+K); u = t; if (t < …) { v = u + C; *(s16 *)(p+K) = v;
if ((v << 16) >> 16 …` as `if (*(s16 *)(p+K) < …) { *(s16 *)(p+K) += C; if (*(s16 *)(p+K) …`. That is, **collapse the temps into
compound assignment on the memory lvalue and re-read the field at each test**. The tell is mechanical: a `move` whose
source was just loaded by `lh`/`lb` and which the text spells with a `+ zr` / `$0` pin or a launder.

## (e) What did not work (all `--try`)
| spelling | score |
|---|---|
| body_free (start) | 5 |
| all 81 width combinations of var_ea/var_fe/var_a0/var_v0 ∈ {s32,s16,u16} (`scratch/w/`) | best 4 (`u16 var_a0`: copy kept but an extra `andi 0xffff`) |
| `var_a0 = (s16)var_ea` | 5 (optimize_reg_copy_1 ties it, above) |
| `var_ea` kept, `var_v0 = var_ea + 0x40`, `(s16)var_v0` test | 5 |
| `+= 0x40` text but with `pad[2]` kept | 8 (the frame is 8 bytes too big, the body is identical) |
| `+= 0x40` text, pad and `r1..r4` deleted | **0** |

## (f) Where the method fell short
- Counting said "same count, one `nop` vs `move`": that is a copy the target keeps. Step 3's listed causes are all
  about copies that **cse** deletes (R20/R21 width or distance). This one is deleted by **local-alloc
  `optimize_reg_copy_1`** (`local-alloc.c:700`, caller `:1003`), a pass the method never names. Worth a line in step 3:
  "a copy that survives cse and combine can still be folded by optimize_reg_copy_1 when its source is a REG that dies
  later in the same block with no jump in between; a SUBREG-source copy (combine.c:1887 split) is exempt."
- The pad and the keepalives were part of the lever: the temp spelling needed a `pad[2]` to make the frame right. A
  close that deletes the temps has to delete the pad too. Otherwise it scores 8 and looks worse than the start.
- No generator reaches "replace a temp chain with a compound assignment on the lvalue". R6 (inline) inlines one temp
  at a time, and the first step alone does not create the second read.

## (g) Structs answer
A struct would help the READABILITY, not the decision: `e->ea += 0x40; if (e->ea >= e->fe)` gives the same RTL as the
cast spelling (the field reads are `mem:HI` either way). The deciding facts are the second read of the same `s16`
location, the combine split and the SUBREG copy, and none of them involve aliasing. The struct is the natural way to
write the re-read, and that is likely why the original has it. Not tested separately. The cast text already closes.

Files: `body.c` (the closed text), `scratch/copy_func_80186BAC.c` (the SC06_032 copy, 0), dumps in `scratch/dumps_n2e/`
(close), `scratch/dumps_c1/` and `scratch/dumps_c5/` (the two refuted copy spellings), `scratch/w/` (the width sweep).
