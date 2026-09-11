# func_8017DD70 (ov_SC01_008, src/ov_SC01_008/ov_SC01_008_jr_8017BE9C.c) — mechanism (d33, P36 S104)

**Result: score 0, ZERO levers** (tree: 1 `$19` pin + 2 launders = 3 levers -> 0). Plain C, no asm, no pin, no volatile,
no `+0`, no do-while. Body: `PACK/body.c`. The same text (symbols renamed) closes all three other copies of the class — table
at the end.

## (a) The residual, counted
Lever-free text (`body_free.c`): score 31, COUNT, 182 vs 184 instructions. Counting the whole objdump (baseline snapshot
`.run/P36/delever/baseline/...o`) gave two separate defects:
1. **two MISSING copies** `move v1,s3` of `c` — one before `slti v0,v1,6 / beq v1,1` in the `flags & 0x10` arm, one before
   `li v0,9 / bne v1,v0` in the tail (the two launders `c3 = c` were faking exactly these);
2. **a callee-saved swap** `changed` s3 / `c` s4 versus the target's `c` = s3, `changed` = s4 (the `$19` pin).

## (b) The passes and decisions (read in tools/reference/gcc-2.7.2, proven on bytes)
1. Missing copies = the WIDTH of `c`. With `s16 c`, every `(int)c` is expanded as `sll 16; sra 16` (insns 63/64 in `.cse`,
   REG_EQUAL `(sign_extend:SI (reg/v:HI 75))`). `c` is set from an `lbu`, so it has 24 sign-bit copies and combine's
   `simplify_shift_const` (`combine.c:7926-7942`, `(ashiftrt (ashift X 16) 16)` with `num_sign_bit_copies(X) > 16`) reduces
   the pair to `(set (reg:SI 176) (subreg:SI (reg/v:HI 75) 0))` — a mode-changing SUBREG move that nothing folds further
   (`.combine` insn 443, feeding a `branch_equality` against a register-held 9). That is the target's `move v1,s3`.
   With `s32 c` there is no extension; cse forwards `c3 = c` (a same-mode REG copy, `cse.c:7440-7474`) and the tests read
   `c`'s register (or the call-argument copy `a0`) directly -> the two copies vanish. [proved: 31 -> 15, 182 -> 184 ins]
2. Callee-saved swap = `allocno_compare` priority (`global.c:594-607`, `floor_log2(refs)*refs/live`, refs from flow
   `flow.c:2067/2315`). `.greg` of the 15-point text: `changed` r77 7 refs / live 92 = 1521.7 beats `c` r75 6 refs / live 91 =
   1318.7, so `changed` is allocated first and takes s3. The 7th ref is the SECOND `result = changed` copy (one per arm of the
   `d >= 6` if/else). The target has ONE test of `changed` after the if/else: its `move v0,s4` in both branch delay slots is
   reorg duplicating the single sign-extension copy of an `s16 changed` into the slots (exactly as the lever-free relative
   func_8018AEE8 in ov_SC03_001 shows at e10/e18/e2c). Final `.greg`: `c` r75 6 refs / live 90 = 1333.3 now beats
   `changed` r77 6 refs / live 92 = 1304.3 -> c = s3, changed = s4. [proved: 15 -> 0 with both edits; `s32 changed` +
   single test = 3 (one `move v0,s4` short — the extension copy only exists for the HImode flag)]

## (c) The moves that closed it
1. `s32 c;` -> `s16 c;` and the launder temp `c3` deleted (test `c` directly: `c < 6`, `c != 1`, `c == 9`).
2. `s32 changed;` -> `s16 changed;`, and the `result` temp (assigned `changed` in both arms of the `d >= 6` if/else) deleted:
   the if/else becomes `if (d >= 6) {...} else if (d < 0) {...}` and ONE `if (changed != 0)` follows it.
Readability extras, each re-proven at 0: `(u16)flags != 0` / `(u16)val` for `& 0xFFFF`, `if (--D_80115122 == 0)`,
`if (flags & 0x40)` without `!= 0`. KEPT (needed): the `nz = ret != 0; return ret & -nz;` temp (inlining it: 14) and the two
block-scoped base pointers `base1/base2` for `pb/pe` (every single-expression spelling re-associates to `(idx*2 + p) + 46`: 7).

## (d) Generator proposal
When a register residual swaps a callee-saved FLAG (a local only ever assigned 0/1 and read into a `result`/copy temp in
several arms) with a byte-loaded local, and/or copies `move vN,sK` of a byte-loaded local are MISSING before its compares:
re-declare the flag and the byte local `s16` (split them out of any list), delete the copy temps (`c3 = c`, per-arm
`result = flag`) and test the variable once after the join — the width creates the SUBREG copy (`combine.c:7926`), the
deleted per-arm copies lower the flag's refs below the rival's (`global.c:594`).

## (e) What did NOT work (byte evidence)
- `s16 c` with an `s32 c3` (29, 183 ins: only one of the two copies back); `s16 c3` alone, `u8 c3` (31); `u8 c`/`u16 c` (21).
- `s16 changed` alone on the `result` text (31); `s16 c` + `s16 changed` with `s32 c3` (29).
- the `s16 c`/`s16 c3` text (15): pure s3/s4 swap — the reading of the allocation table (7 vs 6 refs) named the ref to remove.
- single `if (changed)` but `s32 changed` (3: one `move v0,s4` missing).
- `return ret & -(ret != 0);` (14); `pb/pe` as one expression, `p + 0x2E + off`, `off + (p + 0x2E)`, `pb = p + 0x2E; pb += off`,
  `&((u8*)p)[0x2E] + off`, `(u8 *)(p11a + 0x17) + off` (7 or 8).
- body-local struct `{ u16 idx; u8 pad[0x2C]; u8 cur[8][2]; u8 max[8][2]; }` with `pb = s->cur[*p11a]` (7: same re-association).

## (f) Where the method fell short / helped
- The lever-free SAME-SHAPE relative (S104 step 12, d2/d6) was the key: `grep -rn '0x45A, 0' src/` found 13 bodies;
  func_8018AEE8 (ov_SC03_001) / func_80188128 (ov_SC05_017) are lever-free with `s16 byteVal`, `s16 changed` and a single
  `if (changed != 0)` — both widths and the test shape came from reading them. `related.txt` (one overlay) could not see them.
  A generator that greps a DISTINCTIVE CONSTANT CALL (`func_8002D4C8(0x45A, 0)`) across all of src/ would have found it.
- The sweep could not reach this: the close is a JOINT width move (c AND the copies) plus a deletion of a temp that
  RESTRUCTURES the tail (if/else + separate test). Each single width move scored 29-31 from 31.
- `alloc_table.py` settled the second half in one read (7 refs vs 6, the arithmetic says one ref suffices either way).
- Note the donor itself carries `pad = byteVal + 0;` / `byteVal + 0 == 0xC` (identically-zero terms, step 6): this body does
  not need them — the `+ 0` there is probably also removable with `s16` arithmetic, a candidate for a later pass.

## (g) Structs answer
No struct is needed for this close — both levers were a WIDTH/ref-count problem (`s16` locals), not an aggregate-vs-scalar
alias decision. A struct over `D_8011511A` (`u16 idx` at 0, `u8 cur[][2]` at +0x2E, `u8 max[][2]` at +0x3E) was TESTED with a
body-local declaration: `pb = s->cur[*p11a]` expands the ARRAY_REF as `(idx*2 + p) + 46` and loses the target's base-first
`addiu v1,s1,46; addu a0,v0,v1` (score 7), so the struct would REMOVE readability-neutral block temps only at a byte cost;
the block-scoped `base1/base2` pointers stay. For the structs phase: the idiom is "base pointer held in a pseudo before the
index add", i.e. the original probably had `u8 *cur = ...; u8 *max = ...;` locals, not a struct field access.

## Copies of this class (same text, per-overlay symbols), all --try score 0
| function | TU | file |
|---|---|---|
| func_8017DD70 | src/ov_SC01_008/ov_SC01_008_jr_8017BE9C.c | PACK/body.c |
| func_8017DC10 | src/ov_SC01_009/ov_SC01_009_jr_8017BE9C.c | PACK/scratch/copy_SC01_009_func_8017DC10.c |
| func_8017E3DC | src/ov_SC01_005/ov_SC01_005_jr_8017C340.c | PACK/scratch/copy_SC01_005_func_8017E3DC.c |
| func_8017DC38 | src/ov_SC01_004/ov_SC01_004_jr_8017BE9C.c | PACK/scratch/copy_SC01_004_func_8017DC38.c |

Symbol map (008 -> 009 / 005 / 004): D_801A3458 -> D_801F32B8 / D_801CD9A8 / D_80190248; func_8017EC68 -> func_8017EB08 /
func_8017F2D4 / `((s32 (*)())func_8017EB30)` (004 keeps its cast call); func_8017D890 -> func_8017D730 / func_8017DEFC /
func_8017D758. The 004 copy has no body-local extern block (its TU declares them at file scope), as in the tree.
