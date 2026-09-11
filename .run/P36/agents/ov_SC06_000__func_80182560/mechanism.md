# func_80182560 (ov_SC06_000_jr_8017AE2C.c) — e12, P36 T7 S104

**Score: 2 -> 0, zero levers** (the `la` asm deleted; plain C).

## (a) Residual
COUNT, one extra instruction: the store `p[-7] = 0` came out absolute (`lui at,%hi(D_801AEBCC-28); sw zero,%lo(..)(at)`)
where the target stores through the register that already holds `&D_801AEBCC` (`sw zero,-28(a2)`).

## (b) Pass and decision (PROVEN on the .cse dump, scratch/dumps_free vs scratch/dumps_c1)
cse1, `find_best_addr` (tools/reference/gcc-2.7.2/cse.c:2622):
- free text: the store's address is `(plus (reg p) -28)`, not a REG, so `fold_rtx` runs FIRST (cse.c:2662-2664); `p`'s
  constant equivalent `(symbol_ref D_801AEBCC)` is substituted and the sum folds to `(const (plus sym -28))`. That is a
  CONSTANT address (cheap-cost comparison never happens) -> the assembler macro `lui at; sw`. `.cse` insn 14 shows it.
- closed text: the store's address is `(reg q)` with `q = p - 7`. A REG address is not folded; the lookup of `q`'s class
  finds `(plus (reg p) -28)` with the SAME `ADDRESS_COST` as a REG (1, config/mips/mips.h:2895, mips.c:1652-1653) and a
  higher rtx cost, which the tie-break PREFERS (cse.c:2711-2721, "(p->cost + 1) >> 1 > best_rtx_cost"); the symbolic
  constant costs 2 (mips.c:1631, SYMBOL_REF_FLAG clear under -G0) and loses. `.cse` insn 17 shows
  `(mem (plus (reg 73) -28))`; `q` survives only as the call argument, which sched puts in the `jal` delay slot
  (`addiu a2,a2,-28`) exactly as the target.

## (c) The move
Name the derived pointer: `p = &D_801AEBCC; q = p - 7; *q = 0; *p = D_801AEAFE; func_8017EF68(.., .., (s32)q);`
(The `(s32)&D_801AEBCC` cast on the pointer assignment in body_free.c also dropped — cosmetic.)

## (d) Generator proposal
When an `la` lever feeds a pointer `p` that is then indexed with a NEGATIVE/nonzero constant (`p[-k] = ..`) and the free
residual is `lui at; sw/lw ..(at)` in place of `sw ..,-4k(reg)`, introduce `q = p - k` before the first such access and
rewrite `p[-k]` (and every later `p - k` expression) as `*q` / `q` — find_best_addr turns a REG address back into
`reg+const` but folds a written `reg+const` to a constant.

## (e) What did not work
Nothing else was needed: the first hypothesis scored 0. The sweep's R7/R9/R10/R18 moves all stay at 2 because none of
them changes the address from `(plus p K)` to a REG.

## (f) Method
Step 1 (whole objdump, count first) settled it in one look: 30 vs 31, one `lui at` — a folded constant address, not a
register problem. The residual_moves table has no row for "REG address un-folded by find_best_addr's tie-break"; it is
worth one (it is the inverse of S103 c11's re-association, and the same function: find_best_addr).

## (g) Structs
A struct would NOT help here and could hurt: `S.f0 = 0; S.f7 = x; f(&S)` gives constant addresses (CONSTANT_ADDRESS_P,
cse.c:2656, never replaced by a register) -> two `lui at` stores. The target's shape needs a POINTER variable whose
first access is through a REG address; a struct POINTER `q` (`q->f0 = 0; q->f7 = ..`) would put the base on `&f0`
(0x801AEBB0), not on 0x801AEBCC as the target has it. Not tested on bytes (the plain-pointer text already closes).

## Copies
Same TU: func_8018270C closes with the identical text (its own pack). See scratch/copies.txt for the la-lever
copies elsewhere.
