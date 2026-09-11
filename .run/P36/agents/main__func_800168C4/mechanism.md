# func_800168C4 (main, src/800.c) — T7 agent e20 (S104)

**Result: score 0, lever-free** (no pin, no asm, no volatile, no do-while, no goto). Levers 2 -> 0 (the NEEDED `$3` pin
on `t` and the NEEDED `"memory"` barrier). Signature unchanged. Whole-object check on the `--try --keep` object: `.text`
(101,572 bytes), `.data`, `.rodata` byte-equal to `.run/P36/delever/baseline/src/800.o` (`scratch/cmpobj.sh`).

```c
s32 func_800168C4(s32 arg0) {
    u8 *base = D_800AF630;

    arg0 &= 3;
    if (arg0 == 0) {
        D_800AF7CE += D_80062BA0[D_800B9A18];
    } else {
        D_800AF7CE += D_80062BA0[arg0];
    }
    if (*(u16 *) (base + 0x19E) >= 0xFFU && *(u16 *) (base + 0x188) != 0) {
        return 1;
    }
    return 0;
}
```

## (a) Residual
Free body: 17, COUNT 25 vs 31 — the two table reads merged into one `lbu` after the join (the target keeps one per arm,
`j` + `nop` between), the `lhu 414(base)` hoisted above the `sh D_800AF7CE` into the load-delay slot (the target leaves a
`nop` after `lhu D_800AF7CE` and loads 414 only after the store), and every temp one register off (`v0/a0` vs
`v1`). The sweep's best (u16 `t`) = 8: arms kept apart, but the 414 load still hoisted over the store.

## (b) Passes and decisions (all PROVEN on dumps `scratch/mini/dumps_a1`, `dumps_c1` + bytes)
1. **sched1 believes `*(u16 *)(base + 0x19E)` cannot alias `D_800AF7CE`** (it is the SAME address: 0x800AF630 + 0x19E
   = 0x800AF7CE). The load's MEM is not `/s` (`dumps_a1/t.i.cse` line 99), so the in-struct rule is not it:
   `init_alias_analysis` records `base`'s pseudo (set once, `REG_EQUAL (symbol_ref D_800AF630)`) as a known value
   (`sched.c:421-433`), `canon_rtx` substitutes it (`sched.c:371-376`), and `memrefs_conflict_p` compares two different
   constant symbols -> no conflict (`sched.c:776-779`). So `true_dependence` is 0 and the load fills the delay slot. The
   tree's `"memory"` barrier faked the dependence.
   The target's order comes from a BLOCK BOUNDARY instead: with the `D_800AF7CE += …` written in EACH arm, sched1 sees
   two stores (insns 32, 49 in `dumps_c1/t.i.sched`) and the join label 51 between the second store and the 414 load,
   so nothing moves across. After reload, jump2's cross-jump (`toplev.c:3142`, `find_cross_jump` `jump.c:2371`) merges
   the two identical `lhu/addu/sh` tails (`t.i.jump2`: one store insn 49, the new label 98 before its load) — the target's
   `j 4510` into the shared tail. sched2 then sees a HARD base register (`$5`, no known value) and keeps the load after
   the store (`memrefs_conflict_p` returns 1). This also gives the per-arm `lbu` (each arm's own table read survives up to
   the merge) — no `u16` temp needed.
2. **jump1's if-conversion on the hard return register** (e10's func_80021174 mechanism): `if (A && B) return 1;
   return 0;` expands the return value straight into `(reg:SI 2)`; jump.c's first transform (jump.c:725-830) hoists
   `$2 = 0` above the chain's condjump (`dumps_c1/t.i.jump`: insn 86 before jump_insn 58) and the store-flag
   (jump.c:1012-1210) turns the second test into `$2 = (y != 0)` (insn 89/91: the target's `sltu v0,zero,v0`). With `$2`
   live across the 414 load's block, local-alloc gives the load/compare temps `$3` — the target's `lhu v1,414(a1)`.
   The tree's `if (t >= 0xFF) return y != 0; return 0;` returns a VALUE through a pseudo (expr.c:2609-2621), `$2 = 0`
   stays after the test, and the temps take `$2` (score 3, `scratch/b1.c`).

## (c) Moves (joint)
1. `t = D_80062BA0[…]` in each arm + one `D_800AF7CE += t;` after the join -> the `+=` in EACH arm (17 -> 3).
2. `t = *(u16 *)(base + 0x19E); if (t >= 0xFF) return y != 0; return 0;` -> `if (x >= 0xFF && y != 0) return 1;
   return 0;` (3 -> 0). `t` is gone.

## (d) Generator proposal
When a `"memory"` barrier sits between a store to a global symbol and a load through a set-once pointer to ANOTHER
symbol (sched1 canon's both to constants and calls them independent, `sched.c:776`), and the store follows an if/else
join, sink the store (the statement after the join) into BOTH arms — cross-jump re-merges it after reload
(`jump.c:2371`) and the join label keeps sched1 from hoisting the load; and rewrite `if (c) return E != 0; return 0;` as
`if (c && E != 0) return 1; return 0;` whenever the target builds `$v0` with `move v0,zero` in the test's delay slot.

## (e) What did not work
`scratch/a1.c` (`u16 *p = (u16 *)(base + 0x19E); t = *p;` — a scalar MEM) = 8: the load is not `/s`, the alias
decision is the known-value symbol compare, not MEM_IN_STRUCT_P. `scratch/e/`: `t` in each arm + `+= t` per arm, widths
s32/u32/u16/s16/u8 = 3-15 (only the per-arm store without a temp and u8 reach 3); every `b*` stays 3 without move 2.

## (f) Where the method fell short
The residual printed three hunks (count, order, registers) that were one decision each in THREE different passes; the
alias fact (`sched.c` known values: a pointer set once to `&SYM_A` never aliases `SYM_B`) is not in steps 1-16 — worth
adding: "a load through a set-once symbol pointer hoisted over a store to another symbol = sched1 known-value alias;
the fix is a block boundary (the store per arm / cross-jump), not a barrier". The sibling func_800167F0 (src/800.c:3806)
has the SAME prologue (`if (mask == 0) v1 = …; else …; D_800AF7CE = D_800AF7CE + v1;` + a NEEDED barrier + `raw =
*(u16 *)&s0[0x19E]`) — move 1 very likely closes its barrier too (not tried; not my function).

## (g) Structs
No — tested reasoning, not bytes: a struct type for `D_800AF630` (`base->f_19E`) would make the load `/s`, but the
deciding test is `memrefs_conflict_p`'s two-constant-symbols compare after `canon_rtx` (`sched.c:776`), which runs
regardless of MEM_IN_STRUCT_P, so the load would still be hoisted. Notable for the struct phase: `base + 0x19E` IS
`D_800AF7CE` (0x800AF630 + 0x19E), and `base + 0x188` is `D_800AF7B8` — the `u16 D_800AF7CE` global is a field of the
`D_800AF630` block the code also reads through `base`.
