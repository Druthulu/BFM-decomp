# func_801A4ACC (md_SC07_004) — P36 S104 agent e35 — score 54 (lever-free; sweep best 24) -> 0, ZERO levers (was 2 pins: `$16` on the object, `$17` on the mirror)

(a) Residual: REG only (237/237), a rotation of the three callee-saved holders: object `$s1` (target `$s0`), mirror
`$s2` (target `$s1`), the `&D_801F8888` pointer `$s0` (target `$s2`).

(b) Pass and decision (`tools/alloc_table.py free|c1 func_801A4ACC scratch/`):
- Lever-free, `s2 = &D_801F8888` is ONE function-scope pseudo set in cases 0/1/2 (r75: 9 refs over a live length of 31,
  priority 8709) — it outranks the object (r73: 31 refs / 144, 8611) and the mirror (r74: 12 / 90, 4000), so
  `allocno_compare` (`global.c:594-610`) orders it first and `find_reg` (`global.c:945-990`) hands it the first
  callee-saved register `$s0`; the object then takes `$s1`, the mirror `$s2`.
- With `s32 *s2` declared INSIDE each case block (METHOD d7), there are three pseudos of 3 refs each over ~20 insns
  (c1: r82 1363, r95 1500, r100 1500) — every one below the mirror's 4000 — so the order is object (`$s0`), mirror
  (`$s1`), and the three pointers, which do not conflict with each other, all land in `$s2`. The three per-case
  `lui s2; addiu s2` are the target's. Proven on bytes (`--try` 0, 237/237) and on the two tables.

(c) Moves:
1. `s32 *s2;` moved from the function scope into `case 0: { … }`, `case 1: { … }`, `case 2: { … }` (scratch/c1.c — this ONE
   move alone closes it, 0); both pins deleted.
2. Readability (body.c = scratch/c6.c, also 0): the decompiler temps `v0` (in the tests), `a0_`, `a1`, `a2` and the labels
   `cb4:`/`e58:` deleted — `if ((D_801F8894 & 0x4000) == 0) goto end;`, `if ((*(u16 *)&D_801F888C | *(u16 *)&D_801F888E) != 0)`,
   `func_8002D4C8(4, 0xABE)` direct, the case-1/2 mirror call written per case (`func_80132288(&D_801F8898, &D_801B011C,
   *(s32 *)D_801B80FC)` — post-reload cross-jump re-merges the tails as the target has them, `jump.c:2371`),
   `*(u16 *)((s32)s0 + 0x34) += 1`, case 4's field updates as compound assignments on the re-read `0x20` pointer,
   one `end: func_80132784((s32)s0, *(s32 *)((s32)s0 + 0x64), 0);`. Each intermediate step (c2–c5) scored 0 too.

(d) GENERATOR PROPOSAL (d7, confirmed again): when a REG residual rotates the callee-saved holders and the pseudo that
takes `$s0` is a constant/address pointer SET IN SEVERAL switch cases and used only inside each, declare it inside each
case — splitting an n-case variable into n per-case ones divides its refs by n (priority `floor_log2(refs)*refs/live`
collapses) and the per-case pseudos share the last callee-saved register. Generators move declarations (R2/R4) but never
split one declaration into per-arm ones.

(e) Did NOT work: the free sweep's 190 compiles (best 24: R6 inline `a0_`, which only re-routes the `$a0` temp — the
callee-saved rotation stays), R2/R4 declaration moves (provably dead: the three priorities differ, `global.c:604-610`).

(f) Method gap: none — the allocation table named it in one read (r75 at 8709 vs r73 at 8611 vs r74 at 4000: the
pointer must fall below 4000, so it must lose refs, i.e. be split). First `--try`.

(g) Structs: NO for the lever — global.c's priority arithmetic over a pointer pseudo; no memory-ordering question.
`D_801F8888`/`D_801F8898` are two 16-byte objects (a `u16` pair at +4/+6, an `s32` flag at +0xC) that `func_8013240C`/
`func_80132288` take by pointer — a struct type would make `s2 = &D_801F8888` a typed pointer and read better; the same
pseudo, same bytes. `a0` is an actor (`u16` state at 0x34, `s16` flag at 0x70, pointers at 0x20/0x64/0x6C/0xCC). Not tested.

(h) Joint check (e35): all four e35 body.c files spliced into one copy of the tree TU with the four `extern void func_801A395C`
turned into `extern s32` (`md_SC07_004__func_801A3594/scratch/joint.py` -> `scratch/joint_tu.c`, object `scratch/joint.o`):
each of the four scores 0 through `--try` (whole-TU), and the object's `.text` (sha1 ad583f4dfb0c), `.rodata`, `.data`/`.sdata`/
`.bss`, relocations and symbol table are identical to the baseline snapshot; the only difference is the source-path string.
Gotcha for the next agent: a splice regex `^[^\n;]*\bfn\([^;{]*\)\s*\{` also matches a CALL line ending in `{`
(`if (func_801A3594(...)) {` at :2061) — anchor the definition at column 0 (`^[A-Za-z_]`).
