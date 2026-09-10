# func_8017BF88 (ov_SC02_031, 14 copies) — T7 agent c34 (S103)

**Result: score 0, lever-free.** No register pin, no asm, no added volatile, no do-while, no invented term, no dead
assignment. Whole-object check on the `--try --keep` object: `objdump -drz` of the ENTIRE `.o` is identical to
`.run/P36/delever/baseline/src/ov_SC02_031/ov_SC02_031_jr_8017AE2C.o`; `.text`/`.data`/`.rodata` compare equal (`cmp`).
Candidates: `scratch/v/e1.c`, `scratch/{g,h,k,m}/*.c`; dumps `scratch/dumps_{e1,f1,gz,m3,m8}/`; `scratch/dump.sh` splices
a body into `scratch/base_tu.c` and dumps it.

Two independent moves (each proven alone):

```c
    u16 r;                       /* was: s32 v1; s32 rnd;  v1 = rand(); rnd = v1;  */
    s32 c;
    r = rand();                  /* arms use r & 0xFF, the join uses r & 0x7F00 */
    ...
    c = *(u16 *)(a0 + 0x2);      /* the tail: c is set TWICE */
    ... four stores (the z temp inlined) ...
    c++;
    *(u16 *)(a0 + 0x2) = c;      /* was: *(u16 *)(a0 + 0x2) = c + 1; */
```

## (a) The residual in one sentence

(1) COUNT, 86 vs 87: the target's `move v1,v0` after `rand` is missing — the target keeps TWO copies of the random value
(`$v1`, read by both arms' `andi 0xff`, and `$a2`, copied in the `bnez` delay slot and read after the join by
`andi 0x7f00`), mine keeps one (`$v0 -> $a2`); (2) REG in the tail: the counter `c` (`lhu 2(s1)`/`addiu`/`sh`) and the
z component (`lh 20(sp)`/`sll 8`/`sw 0x18`) have `$a0`/`$v1` swapped.

## (b) The passes and the decisions (all PROVEN on dumps + bytes)

### (1) The missing copy: cse's `(set REG0 REG1)` swap (cse.c:7440-7476), defeated by a HImode destination

* Lever-free text `v1 = rand(); rnd = v1;` (both `s32`): `rnd` lives past the block (used after the join), so
  `make_regs_eqv` makes it the canonical register (cse.c:826-862), and the special case for `(set REG0 REG1)`
  (cse.c:7454-7476, gate `GET_CODE (SET_SRC) == REG` at :7457) retargets the call-result copy to `rnd` and kills `v1`.
  One pseudo, one move: `$v0 -> $a2`.
* `u16 r = rand();`: expand emits the call-result copy `(set (reg:SI 82) (reg:SI 2))` and then
  `(set (reg/v:HI 76) (subreg:HI (reg:SI 82) 0))` (`dumps_m3/m3.i.rtl`). The source is a SUBREG, not a REG, so the swap's
  gate fails and both pseudos survive (the METHOD's c4 rule: a copy into HImode is a SUBREG move and survives). cse
  substitutes r82 for `(subreg:SI r76)` in the arms (same extended basic block), but not after the join label (two
  predecessors), so the arms read r82 = `$v1` and the join reads r76 = `$a2`. That is the target, both moves included.
* Proven: `scratch/v/e1.c` (only `rnd` re-declared `u16`, rest = body_free) 14 -> 6, count 87 = 87, residual (1) gone.
  `m/m4.c` (one `s32 r`) = 9, 86 ins; `m/m2.c` (`s32 r`, `(u16)r` at the join) = 8, 86 ins: a CAST does not create the
  HImode pseudo, only a `u16` variable does.

### (2) The tail swap: sched1's `birthing_insn_p` (sched.c:2469-2499) needs `reg_n_sets == 1`; local-alloc ranks on the result

* `localalloc_sim.py dumps_e1/e1.i.lreg func_8017BF88 173` (0 mismatches): c chain q4 = r98+r113, 4 refs, life 54..64
  -> **8000**; z chain q5 = r99+r114, 4 refs, life 56..68 -> **6666**. c ranks first and takes `$v1` (`$v0` is held by
  `li 32`), z gets `$a0`: the mirror image of the target.
* Why c's life is short: sched1 schedules backwards and `adjust_priority` (sched.c:2507-2546) raises an insn with no
  deaths that BIRTHS a register to `max_priority` — `birthing_insn_p` returns `reg_n_sets[i] == 1` (sched.c:2490). The
  `lhu` of c births r98 (set once), so it is launched as soon as its user `addiu` is scheduled and lands right before it
  (`.sched` of e1: "launching 168 before 194", then `184, 168, 189, 192 …`).
* `c++; *(u16 *)(a0 + 2) = c;` makes ONE pseudo (r78) set twice (`lhu` and `addiu`). Neither insn is "birthing" now:
  in `dumps_m3/m3.i.sched` insn 201 (`addiu`) keeps priority 2 and waits in the ready list from T-4 to T-10 while the
  launch-priority loads go first, and insn 169 (`lhu`) follows it. Forward order: `lh x, lhu c, sll, sw, lh y, addiu c,
  sll, sw, lh z, li 32, sw, sh c, sll z, sw z` — which is the TARGET'S FINAL ORDER instruction for instruction.
* local-alloc on that order (`localalloc_sim.py dumps_m3/m3.i.lreg func_8017BF88 165`, 0 mismatches): c = q3, one
  pseudo, 4 refs, life 44..64 -> **4000**; z = q5, 8000. z ranks first -> `$v1`; c conflicts with `$v0` (the x/y/li
  chains) and `$v1` -> `$a0`. Target.
* Control `m/m8.c` (identical to body.c except `*(u16 *)(a0 + 2) = c + 1;`): 6, the swap back; sim: c q4 (r78+r118),
  life 54..64, 8000 > z 6666.
* Where `c` is read does not matter: `m/m6.c` (`c = *(u16 *)(a0 + 2); c++;` both at the end) is also 0, and so are
  `k1-k6` (six positions/widths of the `c++`). Only the second SET on the pseudo matters. `u16 c` also 0 (`m/m7.c`).

## (c) The source moves that closed it

1. **The random value as a `u16` variable** (`u16 r = rand();`, used for both `r & 0xFF` and `r & 0x7F00`): 14 -> 6.
2. **The counter incremented in place before the store** (`c++; *(u16 *)(a0 + 2) = c;` instead of storing `c + 1`):
   6 -> 0. Alone on the s32 text (`m/m9.c`) it scores 9: the tail registers are right and only residual (1) is left.
3. Readability, all still 0: the `v0`/`v1`/`rnd` temporaries and the tail's `z` temporary and block removed (`r` used
   directly; `sp10[2] << 8` stored in address order).

## (d) GENERATOR PROPOSALS

* **REG, a load->modify->store chain loses a local-alloc contest in a straight-line block** (target keeps the chain in a
  HIGHER register than a shorter-looking rival, and its load is emitted early): rewrite `x = LOAD; …; STORE(x + k)` as
  `x = LOAD; …; x += k; STORE(x)` — two SETs on one pseudo turn off sched1's birthing boost (sched.c:2490
  `reg_n_sets == 1`), the load drifts early, the chain's live length grows and its `qty_compare_1` priority drops.
  Check with `localalloc_sim.py` first: the rival must beat `floor_log2(refs)*refs/life` of the lengthened chain.
* **COUNT, a missing call-result copy where the target keeps two registers for one value across an if/else + join**:
  re-declare the variable as `u16`/`s16` (the value is only ever used masked to 16 bits) so the copy into it is a SUBREG
  move that cse's `(set REG0 REG1)` swap (cse.c:7457) cannot take.

## (e) What did not work (byte evidence)

* Every statement ORDER of the tail with the `c + 1` store (`scratch/h/o1-o12.c`): 6, 9, 11 or 14 — sched1 normalises
  the order; the stores that inline `sp10[2]` after the `sh` pick up nops (89 ins: the `lhu` no longer fills the load
  delay slots once `c` is in `$v0`).
* `*(u16 *)(a0 + 2) += 1;` at the end (`v/f1.c`, `v/f6.c` with s16): 11, 89 ins — the read-modify-write has one set per
  pseudo, so the `lhu` is birthed late.
* Width grid on the tail (`scratch/g/`, 48 bodies: c in s32/u16/s16/u32 × z in s32/s16 × 3×2 positions): best 4 with
  `s16 z` — z's chain gets 3 pseudos (6 refs, 8571 > 8000, registers right) but the `(s32)z << 8` becomes
  `lhu; sll 16; sra 8` (88 ins). A register fix bought with a count loss; not a close.
* The mechanical search's best (4) used a do-while barrier; this close needs none.

## (f) Where the method fell short

* The METHOD's list has no row for "a chain's LOAD placement decides a local-alloc contest". The deciding fact was one
  line of sched.c (`birthing_insn_p`'s `reg_n_sets == 1`), and it only showed up in the `.sched` trace
  ("launching 168 before 194") once I read the ready list next to `localalloc_sim.py`'s birth/death columns. Proposed
  METHOD row: *for a straight-line REG swap, run `localalloc_sim.py`, then check in the `.sched` trace whether the losing
  chain's first insn was LAUNCHED (priority 7f000001); if so, a second SET on that pseudo (`x += k` before the store)
  removes the launch and lengthens the chain.*
* The two residuals were independent and the score mixed them (14 = one COUNT hunk + one REG hunk). Splitting the
  residual by block before any move would have saved the 48-body grid: the grid only probed the tail while it still had
  the `c + 1` store.
* Pack A in the same TU had the same author habit seen from the other side: both closes are "the expression form the
  original author wrote leaves a different pseudo/set count", not a declaration-order dial.
