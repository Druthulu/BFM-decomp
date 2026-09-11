# func_80182868 (ov_SC02_027) — agent e18, P36 T7 S104 — score 0, ZERO levers

(a) Residual: score 5 (COUNT, 120 vs 119) — identical to func_80183ADC's: mine copies the `func_8012C1B8` result into
`$a0` before the `bnez` (`move a0,v0` hoisted, every later jump off by 4), the target keeps it in `$v0` and does
`move a0,v0` in the `jal func_8001C214` delay slot. The tree faked it with the launder `__asm__("" : "=r"(v0) : "0"(v0))`.

(b) Pass and decision: the assignment chain `if ((*(s32 *)(a0 + 0x20) = v0 = f()) == 0)` makes the call value its own
block-local pseudo (tied to `$v0`) and `v0` a COPY of it, so `v0` conflicts with `$v0` and global.c's `find_reg` takes
its copy preference `$a0` (global.c:1001-1010). Proved in full on the twin func_80183ADC (alloc_table before/after, see
../ov_SC02_027__func_80183ADC/mechanism.md); here proved on bytes only (`--try` 0).

(c) Move: `v0 = ((s32 (*)(void))func_8012C1B8)(); *(s32 *)((s32)a0 + 0x20) = v0; if (v0 == 0) {` in place of the chain;
the launder and its `§67` comment (which describes the lever) deleted.

(d) GENERATOR PROPOSAL: split an assignment chain in an `if` condition (`if ((M = v = CALL()) == 0)` → `v = CALL(); M = v;
if (v == 0)`) whenever `v` is read after the branch.

(e) The sweep's best (3: R18 bystander + R7 do-while) was compensating, not the mechanism.

(g) Structs: no (the lever is an expression-shape pseudo split, not a memory-access channel). The body's existing
`Stride8_*` struct tables are unaffected.

Copy closed with the same move: src/ov_SC02_028/ov_SC02_028_jr_8017D898.c func_80180970 — `--try` 0,
scratch/copy_SC02_028_func_80180970.c (the whole definition; its launder + §67 comment removed).
