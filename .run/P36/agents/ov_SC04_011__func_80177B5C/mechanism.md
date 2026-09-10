# func_80177B5C (ov_SC04_011_jr_801734BC.c) — T7 agent c19 — IN PROGRESS

Start: lever-free score 135 (mine 142 / target 147). Current best: **61** (147 / 147), `PACK/body.c`
(= `scratch/v8a.c`). No pin, no asm, no volatile, no zero term.

## (a) The residual

The lever-free body had the wrong SHAPE, not wrong registers: the target's prologue copies three incoming argument
registers into other registers (`move s5,a2`, `move s1,a3`, `move t6,a1`, and `move s0,a0` after the stack load of the
5th argument), then reads the ARGUMENT register for the early uses and the COPY for the late ones. That is gcc 2.7.2's
K&R narrow-parameter conversion, not four laundered copies.

## (b) Passes and decisions (read in this function's own dumps, `scratch/dumps_*`)

1. `assign_parms` (function.c, the `nominal_mode != passed_mode` arm): a K&R `s16`/`u16` parameter arrives as SImode,
   is copied to an SImode temp, and is converted into a HImode pseudo in the conversion insns. Two pseudos, different
   modes, so cse cannot fold the copy (`cse.c` `(set REG0 REG1)` needs the same mode). In the `.lreg`: `(set (reg:SI 76)
   (reg:SI a2))`, `(set (reg/v:HI 75) (subreg:HI (reg:SI 76) 0))`. cse substitutes the SI temp into the first
   extended basic block's uses; the loop breaks the ebb, so the post-loop uses read the HI pseudo (a callee-saved
   register). PROVED on bytes: 142 -> 147 instructions, and the s0/s1/s5 roles land (score 135 -> 61 with the moves below).
   The sibling func_80177DA8 (same TU, lever-free, matched) declares `s16 idx` the same way and shows the same
   `move t7,a2; sll a2,a2,16; sra a2,a2,16` prologue.
2. `m = n` with `u8 m` (the sibling's spelling): the QImode copy survives cse, which gives the target's
   `bnez v0 / move a3,v0` (tested value and kept digit are two pseudos).
3. `x1 = (u16)(x - 3)`: the truncation is narrowed by the front end, so the add is done on the SI temp and a single
   `andi` follows it. `(x - 3) & 0xFFFF` on an `s16 x` makes cse share one sign extension between x1 and x2 (+2 insns);
   `u16 x1` puts the `andi` at the use (wrong order).
4. sched1 birthing boost (`sched.c:2469` `birthing_insn_p`, `adjust_priority` `:2507`, `LAUNCH_PRIORITY` `:3902`):
   a single-set pseudo's defining insn is launched immediately before its consumer; a multi-set one keeps priority 1
   and sinks to the top of the block. The post-loop `cs`/`cl`/`uv` REUSED (body_free) were multi-set, so sched1
   hoisted them above the tag store; one name per value (`cs2`, `cl2`, `tt2`) gives the target order. PROVED (v7a).
5. local-alloc (`local-alloc.c` block_alloc/combine_regs): `yt <<= 16` made `yt` one global pseudo for two values; the
   target's pre-loop `(yt+1)<<16` chain lands in a1 only when the block-0 `yt` is local and the loop value `yl` is a
   separate pseudo. PROVED (v7a 115 -> v8a 61).

## (c) Moves so far (each on bytes)

- K&R params `u16 bits; s16 tbli; s16 x; s16 y;`, all `yt/tr/xr/yr/bb` copies deleted (the conversion makes them).
- `n = (u32)(bits << 16) >> 28; m = n;` with `u8 m` (sibling spelling); `nv` uses `m`.
- `x1 = (u16)(x - 3); x2 = (u16)(x + 5);` and `(u16)(x + 0x2A)`, `(u16)(x + 0x32)` post-loop.
- pre-loop `cs` inlined (`((yt + 1) << 16) | x1`), post-loop one name per value (`cs`, `cs2`, `cl2`, `tt`, `tt2`).
- `yl = yt << 16` for the loop (separate from `yt`).

## (d) Generator proposal (draft)

When the target's prologue copies `$aN` to another register AND the early uses read `$aN` while the post-loop uses
read the copy, re-declare that K&R parameter `s16`/`u16` and delete the body's copy variable.

## (e) Remaining residual (score 61)

Block-0 caller-saved permutation: target ca/mk1/cc1 = t0/t1/t2 (mine a1/t0/t1), p = t3 (mine t2), cs chain a1 (mine
v1), cl v1 (mine t3). The target's sched1 order puts the cl chain BEFORE the p[2] store (while v0 holds `cs|x1`), so
its temps take v1 and the cs chain is pushed to a1. Work continues.

## (f) Method notes

- The COUNT step decided everything: 142 vs 147 was four prologue copies + one QImode copy, all from declarations.
