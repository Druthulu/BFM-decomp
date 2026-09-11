# func_8018270C (ov_SC06_000_jr_8017AE2C.c) — e12, P36 T7 S104

**Score: 2 -> 0, zero levers** (the `la` asm deleted; plain C).

Identical mechanism to func_80182560 (full text in ../ov_SC06_000__func_80182560/mechanism.md, dumps proven there).

## (a) Residual
COUNT +1: `p[-7] = 0` stored absolute (`lui at; sw zero,-28(at)`) instead of `sw zero,-28(v0)` through `&D_801AEBCC`.

## (b) Pass and decision
cse1 `find_best_addr` (gcc-2.7.2 cse.c:2622): a non-REG address `(plus (reg p) -28)` is `fold_rtx`ed first
(cse.c:2662-2664) into the constant `(const (plus D_801AEBCC -28))`; a REG address `(reg q)` is not folded and the
equal-ADDRESS_COST tie-break (cse.c:2711-2721; mips.c:1652 = 1 = REG) swaps in `(plus (reg p) -28)` instead.

## (c) Move
`q = p - 7; *q = 0; *p = D_801AEAFE; func_8017EF68(.., .., (s32)q);`

## (d) Generator proposal
When an `la`-lever pointer is accessed at a nonzero constant index and the free residual is an extra `lui at` on that
access, introduce `q = p + k` and access `*q` (pass `q` wherever `p + k` was written).

## (e) Did not work / (f) method
First try closed; the sweep's block/swap/bystander moves cannot turn a `reg+const` address into a REG.

## (g) Structs
No: struct field accesses on the global give constant addresses (cse.c:2656 never replaces them) — the opposite of the
target. The close needs the pointer variable.
