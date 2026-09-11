# func_800D1658 — e34 (P36 T7 S104) — score 24 -> 0, levers 3 -> 0 (plain C, structured, no goto)

## (a) Residual
COUNT, 43 vs 47 ins. Mine never copies the loaded value into `ret` (the target's `move s0,v0` in the `bgtz` slot),
reads the `& 0xffff` test off the load register, and so `ret` (only constants left) shares `$s0` with `slot`:
one callee-saved register fewer (no `$s1` save/restore, frame 24 vs 32), no `move s0,zero` in the `beq` slot,
and a plain `move v0,s0` instead of the target's `sll/sra 16` sign extension on return.

## (b) Pass and decision (PROVEN on the .cse/.combine dumps, scratch/dumps_{d1,d5})
`t = ret & 0xFFFF` with `ret` a `short`: C promotes `ret` by SIGN extension, which on MIPS gcc 2.7.2 expands to
`(ashift:SI (subreg:SI (reg:HI ret) 0) 16)` + `ashiftrt 16` + `and 0xffff`. The first cse pass folds the
PARADOXICAL `(subreg:SI (reg:HI ret))` to `(reg:SI v)` because ret's class holds `(subreg:HI v)` — `fold_rtx`'s
SUBREG case, `cse.c:4850-4869` (lookup of the inner reg, `return copy_rtx (SUBREG_REG (elt->exp))`). The d5 .cse
dump shows insn 61 as `(ashift:SI (reg/v:SI 73) 16)`; combine then turns the triple into
`(zero_extend:SI (subreg:HI (reg:SI 73)))`. `ret = v` is dead, flow deletes it, and `ret`'s range no longer
overlaps `slot`'s — both get `$s0`.
`(u16)ret` expands to `(zero_extend:SI (reg:HI ret))` — a single `zero_extendhisi2` pattern with no paradoxical
SUBREG, so fold_rtx has nothing to resolve; the read stays on `ret` (`andi v1,s0,0xffff`), `ret = v` survives,
`ret` conflicts with `slot` (`$s1`), and the HImode `ret` is sign-extended on return.

## (c) The moves that closed it
1. The narrow test as a CAST, not a mask: `(u16)ret == 0x8000` instead of `(ret & 0xFFFF)` (the one that matters;
   the goto spelling with only this change, scratch/c/d1.c, is already 0).
2. The goto chain as one structured condition: `if (v > 0 || ((u16)ret == 0x8000 && id != 0x27)) { ok } else
   { bad }` — also 0 (scratch/c/e1.c, delivered). `v` stays an `int` temp for the `lh`; `ret > 0` instead of
   `v > 0` is also 0 (e3).
Two pins (`$2`, `$3`) were never needed; the `$16` pin was standing in for the missing `ret = v` copy.

## (d) Generator proposal
When a `short`/`s16` local is masked `x & 0xFFFF` (or `& 0xFF` for a char) and the residual shows that local's copy
missing (a COUNT residual with one callee-saved register fewer), rewrite the mask as the unsigned cast
`(u16)x` / `(u8)x` — it expands to a zero_extend with no paradoxical SUBREG for cse's fold_rtx to see through.

## (e) What did not work (bytes)
- `ret = load; if (ret > 0) …; if ((ret & 0xFFFF) != 0x8000)` -> 22 (no int temp; ret read through the subreg).
- `ret = load` with `(u16)ret` -> 15: TWO loads (`lh` for the test, `lhu` for ret) and an extra frame slot —
  the int temp `v` is what keeps one load.
- `s16 v` -> 15 (same double load). `(u16)(ret = v) != 0x8000` -> 22. `(ret & 0xFFFF)` with `ret = v` -> 24.
- `u16 t; (t = ret) != 0x8000` -> 0 too (the same zero_extend channel; not delivered — the cast reads better).

## (f) Where the method fell short
Steps 12-16 have the width moves (c4, d8, d13) but not "a mask is a SIGN extension followed by an AND": the
paradoxical-SUBREG fold is a cse channel that deletes a user copy. The generators' R12 width moves changed
declarations; this needed an expression-level cast (like d13's `(s16)t >> 6`, the same family — cast one operand
at the use, never the declaration).

## (g) Structs
No. `D_8010EDEC` is a 12-byte record table (`+0` s16 flags, `+4` u16 qty per other TUs' comments); a struct type
would turn `*(s16 *)((u8 *)&D_8010EDEC + id * 0xC)` into `D_8010EDEC[id].flags` — readability only. The deciding
fact is how `ret`'s narrow read is expanded (sign- vs zero-extension), which a struct cannot change.
