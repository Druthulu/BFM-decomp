# func_801823BC (ov_SC06_000_jr_8017AE2C.c) — e28, P36 T7 S104

**Score: 4 (sweep best 2) -> 0, zero levers** (the `$17` pin AND the launder asm both deleted; plain C). First `--try`.

## (a) Residual
COUNT +1 (29 vs 28): the store `*(s32 *)((s32)q - 82) = 0` came out absolute (`lui at,%hi(D_801AEB52-82); sw zero,..(at)`)
where the target stores through the callee-saved register holding `&D_801AEB52` (`sw zero,-82(s1)`, in the `jal` delay
slot, after `addiu a2,s1,-82`). The pin was only there because the launder needed q in a known register; the register
itself (`$s1`) is what global alloc gives q anyway once the call argument keeps it live across the first call.

## (b) Pass and decision (the e12 mechanism, same TU; e12 proved it on .cse dumps for func_80182560)
cse1 `find_best_addr` (gcc-2.7.2 cse.c:2622): the free text's address `(plus (reg q) -82)` is not a REG, so `fold_rtx`
runs first (cse.c:2662-2664), substitutes q's constant equivalent `(symbol_ref D_801AEB52)` and folds the address to
`(const (plus sym -82))` — a CONSTANT address, never replaced again (cse.c:2656) -> `lui at; sw`. A REG address
`(mem (reg r))`, `r = q - 41`, is not folded; the lookup of r's class finds `(plus (reg q) -82)` at the same ADDRESS_COST
as a REG (1: mips.h:2895, mips.c:1652-1653) and a higher rtx cost, which the tie-break prefers (cse.c:2711-2721); the
symbolic constant costs 2 (mips.c:1631) and loses. r stays live as the third call argument, so cse2 does not re-fold
(e12's func_80184A68 (b)3: a derived pointer with no other live use is re-folded in cse2).
Proven on bytes here (score 0); the dump reading is e12's (not re-dumped for this function).

## (c) Move
Name the derived pointer and pass it: `r = (s32 *)((s32)q - 82); *r = 0; func_8017EF68(&D_801B20E0, &D_801A158C, (s32)r);`
(`r = (s32 *)(q - 41);` also scores 0 — scratch/v2.c.)

## (d) Generator proposal
When a launder/`la` pointer's constant-offset access comes out as `lui at; sw/lw %lo(SYM+k)(at)` where the target has
`sw k(reg)`, and the same `p + k` is also passed to a later call, name `r = p + k`, access `*r` and pass `r`.

## (e) What did not work
The sweep's R4/R7/R9/R12 moves stay at 2 (ORDER): none of them turns the address into a REG. Nothing else was needed.

## (f) Method
Counting first + e12's sibling text closed it on the first try; the method worked as written (brief + neighbours).

## (g) Structs
A struct on the global would give CONSTANT field addresses (cse.c:2656), the opposite of the target; a struct pointer
based at D_801AEB52 with fields at -2/-78/-82 is not expressible (negative offsets) — the base would move to
D_801AEB52-82 and the offsets change. The deciding fact is REG vs `reg+const` address in find_best_addr, not aliasing.

## Copies
func_80182464 (same TU) closes with the identical text (its own pack). No other copy of the `q - 2, q - 78` call in src/.
