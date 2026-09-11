# func_800384A8 (src/800_c.c) — P36 S104 agent e3 — score 2 -> 0, ZERO levers, BUT A SIGNATURE CHANGE (parked)

## (a) The residual
Two instructions: the target indexes `D_800B9CD8` with the raw `$a0` (`sll v0,a0,7; subu v0,v0,a0`), the lever-free body
has no value for `raw` at all (it read an uninitialised local, landing in `$v1`). The tree faked it with
`register s32 raw __asm__("$4")` next to an UNUSED `s16 arg0` parameter.

## (b) The pass decision
Not a pass: the parameter's declared width. `mips.h:1153` defines `PROMOTE_PROTOTYPES`, so a prototyped `s16` parameter
arrives as an int and is narrowed at entry (`assign_parms`, function.c:3664-3676); every SImode use then re-extends it —
`--try` of `s16 arg0` + `arg0 * 0x1FC` gives exactly `sll a0,a0,16; sra a0,a0,16` extra (score 2, 72 vs 70 ins,
`scratch/s16.c`). The target has no extension, so the parameter is a full `s32` in the original. No plain-C spelling of
an `s16` parameter can drop that extension (the incoming value is not known to be sign-extended).

## (c) The move
`void func_800384A8(s16 arg0)` -> `void func_800384A8(s32 arg0)`, the pinned `raw` deleted, `arg0 * 0x1FC` indexes the
table. Score 0 (70/70). Nothing else changed.

SIGNATURE CHANGE: the only other declaration is `extern void func_800384A8(s16 a0);` at src/800_b_2.c:1884, a different
TU. Its one caller, func_8002EC10, passes `*s0` with `s16 *s0` (src/800_b_2.c:1889). That is an `lh` value, already
sign-extended, so moving that prototype to `s32` should not change the caller's bytes. I did not test this (800_b_2.c is
another agent's TU). The definition's parameter type alone decides this function's bytes, and the mismatched `s16`
prototype in the other TU compiles regardless. Parked for the structs phase per Drew S104 (d).

## (d) GENERATOR PROPOSAL
When a `register … __asm__("$4"..."$7")` pin is the ONLY reader of an incoming argument register and the matching
parameter is narrow (s16/u16/s8/u8) and unused, delete the pin, widen the parameter to `s32` and substitute it for the
pinned local (a signature move; flag it for the caller TUs' prototypes).

## (e) What did not work
The sweep's R14 (param-width s16->s32) alone scored 2 because it widened `arg0` without routing the pinned `raw` to it
(the pin's local is a SEPARATE uninitialised variable in body_free.c). Keeping `s16 arg0` and using it: 2 (above).

## (f) Where the method fell short
body_free.c's `raw` is an uninitialised read — the lever remover should map a `$aN` pin to parameter N when the
parameter is otherwise unused (then R14 would have closed this on its own).

## (g) Structs question
No. The defect is a parameter width, not an access shape; no struct type changes the entry narrowing.
