# func_80036AF8 (src/800_c.c) — P36 S104 agent e21 — score 31 -> 0, ZERO levers (the `$0` pin and its three `+ zr` removed)

## (a) The residual
REG + three missing copies. The target has three `move`s the lever-free text lacks:
- `move s5,a1` in the prologue, with the 0x4000 test still reading `a1`;
- `andi a2,a1,0xf; move a3,a2`, with n and idx in two registers, and the arms `addiu a3,a2,4` / `addiu a3,a2,8`;
- `andi a0,v0,0x1f` … `move s3,a0`, with drv in `a0` for the in-if index and in `s3` after the calls.
The lever-free s32 text folds each pair into one register (`s4`/`a1`/`s2`), so the callee-saved assignment rotates
(s2<->s3, s4<->s5). The tree faked each copy as `x = y + zr`, the house idiom the TU header describes (src/800_c.c:11).

## (b) The pass decision (dump-proven, `scratch/dumps_r5/`, `.greg`)
There is no PROMOTE_MODE on MIPS gcc 2.7.2, so an `s16` local is a HImode pseudo. Assigning it from an int computation
is a mode-changing SUBREG move, `(set (reg/v:HI x) (subreg:HI (reg:SI t) 0))`. cse's copy folding needs a same-mode
REG source: the `(set REG0 REG1)` case at cse.c:7440-7474 is gated at :7455 on a REG source. The SUBREG move therefore
survives, and the int temp keeps serving the early SImode uses:
- `insn 13 (set (reg/v:HI 21 s5) (subreg:HI (reg/v:SI 5 a1) 0))` is `mode = flags`. The test `mode & 0x4000` reads a1.
- `insn 29 (set (reg/v:HI 7 a3) (subreg:HI (reg:SI 6 a2) 0))` is `idx = mode & 0xF`. The arms are
  `insn 79/89 (set (subreg:SI (reg/v:HI 7 a3) 0) (plus:SI (reg:SI 6 a2) 4|8))`, computed from the SI temp, so reorg can
  put `addiu a3,a2,4` in the `bnez` slot.
- `insn 44 (set (reg/v:HI 19 s3) (subreg:HI (reg:SI 4 a0) 0))` is `drv`. The in-if `drv * 0x48` reads a0
  (`insn 63/65`), and the later uses read `(subreg:SI (reg/v:HI 19 s3))` (`insn 107/109`).
With s32 locals these are same-mode copies that cse folds, and one pseudo remains per pair. Bytes: `--try` 0 (139/139).

## (c) The move that closed it
Six declarations become `s16` (mode, idx, lo, h, drv — h was already s16). The three `+ zr` copies and two locals go:
`n` is gone (`idx = mode & 0xF; … idx += 4;` / `idx += 8;`) and `hi` is gone (drv is used throughout). Every flags
field is read through the one `s16 mode = flags;`: `lo = mode >> 4; drv = (mode >> 9) & 0x1F;`, and `req.f10 = mode;`.
Only `mode` (r9: 35, the prologue copy vanishes), `idx` (r6: 10) and `drv` (r7: 19) must be s16; `lo` may stay s32 (r8: 0).
The 625-body width sweep (scratch/e1.out) has 120 zeros. Every one has a narrow `mode`, a narrow `idx` and a narrow
`hi`/`drv`.

PARKED alternative (a SIGNATURE change): `body_parked_s16param.c` takes `s16 flags` and has no `mode`. It scores 0 too
and matches the caller's `(s16)arg1` cast in src/800.c:8073. It needs the prototype changed.

## (d) GENERATOR PROPOSAL
When a body carries `x = y + zr` (`$0` pin) copies, or the residual lacks `move sK,aN` / `move aM,aN` copies next to
masked or shifted values, delete the copy and its target local, and re-declare the value's local as `s16`/`u16`
(also the local read from a parameter the callers cast to `(s16)`). Enumerate the widths jointly: a HImode SUBREG move
survives cse (cse.c:7455), and an SImode copy does not. This extends R20/S103 c4. `+ zr` is the TU's house idiom
(func_80035270 carries the same n/idx and drv/hi pair at src/800_c.c:104-107, plus the `vol + zr` call pair at :277), so it is
the next body to try.

## (e) What did not work (bytes)
- One width at a time (g1 `s16 mode` alone 20; g3 `s16 idx` 29; g4 `u8 n` 31; g5 `u8 hi` 29; g6 `u8 drv` 31). The close
  is JOINT: 505 of the 625 width combinations are not 0.
- An if/else `else idx = n;` in place of the up-front copy (r2/r3): 15.
- Folding the temps (`req.f0c = CdPosToInt(loc) + *(s32 *)(…)` s1: 11, `b = rec[(h << 6) + …]` s2: 18,
  `rec = … + (h << 6)` s3: 4). The existing ret/hoff/tbl/rec2 temps stay.

## (f) Where the method fell short
history.txt's best (11) already had `R14 param-width flags s32->u16`, the right family on the wrong variable. The
generator changes ONE width per move, and this close needs three at once, plus the copies deleted, to show any gain.
Step 13/16's "narrow load needed twice" and S103 c4 describe the SUBREG copy, but no rule links a `+ zr` pin to a
missing width.

## (g) Structs question
No for the pass: the copies come from the MODE of the locals, which is not an aggregate/scalar alias question. A
bitfield struct for `flags` (n:4, h:5, drv:5, bit14) would read naturally. gcc would then extract with its own
shift/mask sequence, not the target's `sll 16; sra 20|25` sign-extending one, so the s16 locals are the byte-proven
reading. Not tested.
