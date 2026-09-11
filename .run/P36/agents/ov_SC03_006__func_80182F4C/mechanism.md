# func_80182F4C (ov_SC03_006_jr_8017AE2C.c) — e6, P36 T7 S104

**Result: score 0, ZERO levers** (1 lever before → 0 after: the `p1` pin `$4`). Body: `PACK/body.c` (= `scratch/p/pb.c`,
the temp renamed `list`). One line changed from `body_free.c`, one added: the cell-list pointer is loaded into its
own local and `p1` is formed from it — `list = *(s32 *)(base + 0x14); … p1 = list + dx;` (instead of `p1 = …; … p1 += dx;`).
No other copy of the class exists in `src/` (grepped `0xFA00`, the `>> 7 & 0x1FF` index, the `* 22` record stride).

## (a) The residual, in one sentence
A whole-function register rotation (29, REG-caller): the target puts the walked pointer `p1` in `$a0` (freed by the
entry `sll a0,a0,16`) and everything allocated after it one register lower (base t0, p3 t1, p2 t2, c0 t3, 0xffff t4,
outerIdx t5, val t6, c1 a3); the free body gives `$a0` to `val` (the hoisted `(s16)a0`) and pushes `p1` to `$a3`.

## (b) The pass and the decision (`scratch/dumps_free`, `dumps_u16`, `dumps_fin`; proven on bytes)
All 15 contenders are GLOBAL (loop-carried). Order (`.greg`): `91 92 90 82 86(p1) 78 75 88 87 77 130 79 149(val) 73 97`.
- `val` (r149) = `(ashiftrt r150 16)` with r150 the local `sll` result in `$4` → `set_preference` (`global.c:1535-1573`,
  first operand of a non-copy SET, renumbered to the local's hard reg) gives `val` a preference for `$a0`.
- `find_reg` pass 0 (`global.c:950-953`) excludes `regs_someone_prefers` — built by `prune_preferences` from the
  preferences of LOWER-priority conflicting allocnos — so `n` (r90), `p1` (r86), `c1`… all skip `$a0` (and `$a1`, `a1`'s
  preference): `n → a2`, `p1 → a3`, …; `val`, allocated 13th, takes its `$a0`.
- The target's `p1` in `$a0` needs (i) `$a0` removed from `val`'s preferences and (ii) `$a0` preferred by `p1` itself.
  Loading the list pointer into a separate local does both: `list` (r87) is one-block/one-death → local-alloc gives it
  the first free register, `$4` (`.lreg` `;; Register 87 in 4.`), so every global live in that block (`n`, `c1`, `base`,
  `c0`, `outerIdx`, `val`, `a1`, the 0x8000 constant) records `$4` as a hard conflict and `prune_preferences` strips
  `val`'s `$a0` preference (`.greg` of the close: no `150 preferences` line); `p1 = list + dx` gives `p1` a preference for
  `list`'s `$4` (`;; 86 preferences: 4`), and `p1` does not conflict with `list` (born where `list` dies). `p1` is then the
  first allocno that can take `$a0`, and the rest shift down by one — exactly the target map.

## (c) The move
`p1 = *(s32 *)(base + 0x14);` → `list = *(s32 *)(base + 0x14);` (new `s32 list;`), and `p1 += dx;` → `p1 = list + dx;`.
Probes (`scratch/p/`): folding the load into the add (`p1 = *(s32 *)(base + 0x14) + dx;`) → 4 (COUNT: the load is no
longer scheduled early); `p1 = dx + *(…)` → 3. The temp must be a separate statement at the load's position.

## (d) GENERATOR PROPOSAL
**R-new "seed a preference through a load temp":** when a REG rotation shows the target giving a pointer P the
argument register that a parameter copy vacated (and the free body gives it to the parameter-derived value), split
`P = LOAD; … P += X;` into `T = LOAD; … P = T + X;` — the load temp is local-allocated to the first free register
and turns into both a hard conflict for the block's other globals and a `set_preference` for P. Test on every
`P = LOAD; … P op= …` pair in the function (cheap: one `--try` each).

## (e) What did not work (bytes)
- `s16 a0` parameter (signature change, the TU's two later `extern`s rewritten, `scratch/trytu.sh`) → 29; a first-declared
  `s16 val = a0;` → 29 (the d15 prologue-order move is not this residual: the copy order is already right).
- reusing the parameter `a0` as `p1` (`scratch/b1_p1_is_a0.c`) → 29: combine folds the entry copy into the `sll`, so no
  copy preference survives.
- the sweep's best 8 (`free_083.c`, `u16 p1`) truncates a pointer and adds an `andi` — a compensating error; it
  reached the right map by the same channel (a HImode `p1` makes the load a separate local in `$a0`), which is what
  pointed here.

## (f) Where the method fell short
- The allocation table prints `prefers a0` on `val` but not WHY the target's other allocnos avoid `$a0`; the deciding
  fact was `find_reg`'s pass-0 exclusion of `regs_someone_prefers` (a lower-priority allocno's preference steals a
  register from every higher-priority one it conflicts with). Worth a column in `alloc_table.py`: for each allocno, the
  registers excluded in pass 0 by others' preferences.
- The compensating-error candidate (`u16 p1`) was the best clue: diffing ITS `.greg`/`.lreg` against the free body's
  showed a new local in `$4` — read the sweep's best candidate's dumps even when the candidate is not honest.

## (g) Structs answer
No. Tested on bytes with a body-local `struct Grid_80182F4C { u16 x0, y0, stride, pad6; u16 *tbl; u8 padC[8]; s32 cells,
recA, recB; } *base;` and field accesses: the close stays 0 (`scratch/st/st_close.c`) and the free body stays 29
(`scratch/st/st_free.c`). The lever was a global-alloc preference decision, not an aliasing or address-folding one.
