# func_8017E060 (ov_SC04_012) — mechanism (P36 T7 S104, agent d25)

**Final: score 0, plain C, ZERO levers (1 pin → 0).** Copies of the class also closed at 0 with the same text (table at the end).

```c
void func_8017E060(s32 *param_1)
{
    extern s8 D_80191C70;

    *(&D_80191C70 + param_1[0x34 / 4]) = 0;
    func_801292C8((u8 *)param_1);
}
```

## (a) The residual in one sentence
All 12 instructions are identical; only the FRAME differs — mine `addiu sp,-32 / sw ra,24(sp)`, target `-24 / 16(sp)`: the
lever-free body allocates one unused 4-byte stack slot (rounded to 8) for a pseudo that no longer appears in any insn.

## (b) The pass and the decision (read in the dumps, proven on bytes)
- The decompiler text sets `p` TWICE: `p = (s32)&D_80191C70; … p += new_var;` → pseudo 74, `reg_n_sets = 2`, `reg_n_refs = 4`
  (flow dump: "Register 74 used 4 times across 5 insns").
- combine merges insns 11 (`p = sym`, i1), 20 (`p = r + p`, i2) and 23 (`*(s8*)p = 0`, i3) into one
  `(set (mem:QI (plus r75 sym)) 0)` — p vanishes from every insn. But the ref-count bookkeeping at `combine.c:2305-2314`
  (i2) and `:2327-2337` (i1) only zeroes `reg_n_refs` when `reg_n_sets` reaches 0: i2's branch is skipped because
  `i2dest_in_i2src` (`combine.c:1394`, `p = p + r` reads p), and i1's decrement takes `reg_n_sets` 2 → 1 only. So pseudo 74
  keeps `reg_n_refs = 4` with no insn referencing it (the known exception documented at `combine.c:56-57`).
- regclass sees no uses → prefers `ST_REGS or none` (.lreg dump); global lists "1 regs to allocate: 74" but gives it no
  hard register (.greg dispositions: only `75 in 2`).
- reload `alter_reg` (`reload1.c:2327-2352`): `reg_renumber < 0 && reg_n_refs > 0` and no equivalence → `assign_stack_local`
  → a 4-byte slot → `compute_frame_size` rounds the frame 24 → 32. That is the whole residual.
- Byte evidence: `scratch/b1.c` (`p = &D; p += x; *(s8*)p = 0;`) scores 4 (the residual reproduced), `scratch/b2.c`
  (`p = &D + x;` — ONE set) scores 0, `body.c` (no temp at all) scores 0. In b2's dumps the combined-away pseudos 73/75
  drop out of the .lreg register list (refs zeroed, set count 1 → 0). Dumps: `scratch/dumps_free/`, `scratch/dumps_b2/`.
- Why the tree's `$4` pin worked: a hard register is never given a stack slot by alter_reg (only pseudos), so the stale
  count did nothing.

## (c) The move that closed it
Delete the twice-set temp: write the store as one expression, `*(&D_80191C70 + param_1[0x34 / 4]) = 0;` (the sibling
functions func_8017D99C/func_8017DAE4 in the same TU spell the same global exactly this way), and pass `param_1` to
func_801292C8 as the file-scope prototype `(u8 *a0)` says (same bytes as the void(void) cast — a0 already holds param_1).
`D_80191C70[param_1[0x34/4]] = 0` with a body-local `extern s8 D_80191C70[]` also scores 0 (`scratch/a1.c`), but the TU's
other functions declare the scalar `extern s8 D_80191C70;`, so body.c keeps that.

## (d) GENERATOR PROPOSAL
When the residual is FRAME-ONLY (identical instruction mnemonics/operands except the `addiu sp` / `sw|lw ra` offsets, mine
larger by 8), look in `.lreg` for a pseudo with refs > 0 that appears in NO insn ("ST_REGS or none") — a local set more than
once whose every set combine folded into an address — and rewrite its `x = A; x += B;` (or `x = A; … x = x op B;`) chain
into a single initialisation `x = A + B;` or inline it into its one use; mechanically: "merge consecutive sets of the same
local into one expression when the later set reads the local".

## (e) What did not work (byte evidence)
- The mechanical sweep (R2–R34, 190+ compiles, history.txt): swaps, widths, inlining `r`/`new_var`, blocks, do-while, param
  copy — best 2, never 0, because every candidate kept `p = &D; p += …` (two sets of p). Re-scored here: the regen's
  `free_000.c` (`new_var` inlined, `p += r`) is still 4 with the identical frame diff. (The sweep's "2" came from a
  statement swap, not examined further — it cannot fix the frame while p is set twice.)
- `s8 *p; p = &D; p += x; *p = 0;` (`scratch/b3.c`): still 4 — the pointer type does not matter, the SET COUNT does.

## (f) Where the method fell short
- The residual class printed as `OTHER` and the brief's pointers (allocation table, register levers) aim at register or
  order residuals; a frame-size-only diff is a different class — stale `reg_n_refs` → reload stack slot — and it is not
  in `residual_moves.md` as far as this pack shows. The .lreg line "used N times … ST_REGS or none" for a pseudo absent from
  every insn is the tell; worth a row in residual_moves.md and a check in `--explain`.
- The first `--try` of the most natural reading of the function closed it: with a 12-instruction body, trying the plain
  idiomatic spelling BEFORE the generators would have saved the whole sweep.

## (g) The structs question
No. The lever holds a stale reference count in combine's bookkeeping (`combine.c:2305-2337`) for a local set twice; a struct
type changes which insns reference memory, not how many times `p` is set. `param_1` is an entity whose 0x34 field is the
slot index into the `D_80191C70` byte table (func_8017D99C/func_8017DAE4 write `*(s32 *)(obj + 0x34) = slot`), so a struct
with `s32 slot` at 0x34 would read better; it is not needed for the bytes (this body closes with the cast form).

## Copies table (each `--try` at 0)
| function | TU | file |
|---|---|---|
| func_8017E060 | src/ov_SC04_012/ov_SC04_012_jr_8017AE2C.c | PACK/body.c |
| func_801846EC | src/ov_SC03_007/ov_SC03_007_jr_80183894.c | PACK/scratch/copy_ov_SC03_007_func_801846EC.c |
| func_8017DE40 | src/ov_SC04_008/ov_SC04_008_jr_8017AE2C.c | PACK/scratch/copy_ov_SC04_008_func_8017DE40.c (file-scope prototype there is `func_801292C8(void)`, so the call is cast `((void (*)(u8 *))func_801292C8)((u8 *)param_1)`; `..._noarg.c` with a plain `func_801292C8();` also scores 0) |
