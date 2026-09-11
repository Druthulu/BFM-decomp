# func_8017E710 (ov_SC03_006_jr_8017AE2C.c) — e6, P36 T7 S104

**Result: score 0, ZERO levers** (1 lever before → 0 after: the `ang` pin `$2`). Body: `PACK/body.c` (= `scratch/q2/q2_t3.c`).
**The same text closes the whole class — 13 functions, every one proven 0 with `--try`** (list below).

## (a) The residual, in one sentence
The lever-free body puts the `(s16)(ang - base) < 0` compare temps in `$v0` and pushes `ang` (the second `ratan2`
result, which the ±0x480 arms and the join read) to `$v1`; the target keeps `ang` in `$v0` and the compare in `$v1`
(REG, 9 → 7 after the sweep; every single move plateaued at 7).

## (b) The pass and the decision (read in `scratch/dumps_free`, `dumps_w2`, `dumps_fin`; all proven on bytes)
- `ang` spans blocks 1–4 (it is read in both arms and at the join) → refused by local-alloc (`local-alloc.c:472`,
  `reg_basic_block[i] >= 0 && reg_n_deaths[i] == 1`) → global. The compare's `subu` (r101) and `sll` (r103) are
  one-block one-death pseudos → local-alloc allocates them FIRST, and `$2` is free there (the call's `$v0` died at the
  `andi`), so both take `$2` (`.lreg` `;; Register 101 in 2.`). Global-alloc then records `$2` as a hard conflict of `ang`
  (`global.c:1256/1291`, `.greg` `74 conflicts: … 2 …`) and `find_reg` gives it `$3`.
- **No local may be alive in `$2` across the compare while `ang` is.** Any block-1 local overlapping the compare also
  overlaps `ang`, so the compare temps must stop being locals: make the compare's destination a USER variable that is
  (i) GLOBAL — reused in another block, so `local-alloc.c:472` refuses it — and (ii) the destination of BOTH the
  `subu` and the `sll`, so there is no anonymous shift temp left to be local (`d <<= 16` sets `d` in place; `(s16)d < 0`
  creates a sign-extension temp that goes local → `$2` again, 11, `scratch/f/f_cast.c`).
- With both global, `allocno_compare` (`global.c:594-610`) orders `ang` (r74, pri 27000: 9 refs / live 10) before `d`
  (r76, 24000: 6/5). `ang` takes its preference `$2` (set_preference from `(and (reg 2) 4095)`, `global.c:1535`), `d`
  its preference `$3` (the tail `sra`). `.greg` of the close: `4 regs to allocate: 74 76 72 73`, `74 preferences: 2`,
  `76 preferences: 3`.
- `ang`'s priority needs the join's `ang = *(u16 *)(a0 + 0x6)` reuse that `body_free.c` already carried: without it
  `ang` drops to 7 refs (14000), `d` is allocated first, and the fresh join-block `lhu` local in `$v0` overlaps `ang`,
  which goes to `$a0` (5, `scratch/f/f_noanglhu.c`). That reuse is also what the function header's note asked for.

## (c) The moves (JOINT — each alone scores 7–11)
1. Declare `s32 d;` and write the compare as `d = ang - base; d <<= 16; if (d < 0) {` (the sign of the low halfword).
2. Reuse `d` for the third tail term: `d = (s16)*(u16 *)(out + 4) >> 1; *(s16 *)(out + 4) = *(u16 *)(a0 + 0xE) + d;`
   (the target keeps that term in `$v1` — `lhu v1,28(sp); sll; sra v1,v1,17` — which is `d`'s register).
3. Keep `body_free.c`'s `ang = *(u16 *)(a0 + 0x6); *(s16 *)(in + 0) = ang;` reuse (and drop the pin).
Probes (`scratch/f/`): 1 without 2 → 7; 1+2 with `(s16)d` → 11; `d = (ang - base) << 16` → 11; 1+2 without 3 → 5;
2 on the first tail term instead of the third → 7 (COUNT: it re-plans the tail schedule).
Search path that found it: `scratch/r/` (48 reuse spellings; the lhu reuse of `d` scored 2 = the register was right
everywhere but the lhu) then `scratch/q2/` (d's second life moved to each `$v1` site of the target: only `t3` → 0).

## Other copies of the class — all 0 (`scratch/ports/`, made by `scratch/port.py` from each tree body)
`src/ov_SC03_118/ov_SC03_118_jr_8017AE2C.c` func_8017EA24 · `src/ov_SC05_004/ov_SC05_004_jr_8017BEBC.c` func_8017DB00 ·
`src/ov_SC02_031/ov_SC02_031_jr_8017AE2C.c` func_8017EE3C · `src/ov_SC03_028/ov_SC03_028_jr_8017AE2C.c` func_8017D370 ·
`src/ov_SC03_024/ov_SC03_024_jr_8017DF84.c` func_8017FBC8 · `src/ov_SC02_011/ov_SC02_011_jr_8017AE2C.c` func_8017DE10 ·
`src/ov_SC03_113/ov_SC03_113_jr_8017C294.c` func_8017E878 · `src/ov_SC03_111/ov_SC03_111_jr_8017AE2C.c` func_8017C95C (each `--try … --body`, 0);
the shared header `src/shared/ov/func_8017D0BC__4f23330c.h` (func_8017D0BC) — `--body` cannot splice an `#include`d
definition, so each of its four TUs was scored as a WHOLE TU with the `#include` line replaced by the ported text:
`scratch/ports/tu_ov_SC03_002.c`, `tu_ov_SC03_125.c`, `tu_ov_SC05_018.c`, `tu_ov_SC04_020.c` → 0 in all four. The ported
body is `scratch/ports/shared_func_8017D0BC.c` (its `Mtx8_8017DE10_8017D0BC` type name kept).

## (d) GENERATOR PROPOSAL
**R-new "globalise the compare temp":** when a REG residual swaps a multi-block variable V (the loser) with the temps
of a sign/compare chain computed from V in the same block (`subu; sll; bgez` / `(s16)(V - W) < 0`), rewrite the test
as an in-place user temp `t = V - W; t <<= 16; if (t < 0)` and give `t` a second life at each later site whose target
register equals the compare's target register (a load/shift term in another block), trying every site (`--try`
enumerates them); keep any existing reuse that raises V's refs. Precondition check: `.lreg` shows the compare temps
local in V's desired register and `.greg` lists V with that register as a conflict.

## (e) What did not work (bytes)
- widths/types of `ang`/`base` (s32/u32/int/u16, `s16` → 131 ins), `>=` polarity, `<< 16` spelling, `arg = -(ang - base)`:
  128 variants, none below 7 (`scratch/enum/`).
- a local `t` + `ang = t` copy (`scratch/w*.c`, `m/`): sched1 hoists the copy above the compare (a multi-set dest is
  not birthing, `sched.c:2469/2540`; `.sched` T-2 `107 (3) 109 (7f000001)`), then local-alloc's `optimize_reg_copy_1`
  (`local-alloc.c:700`, call `:1007`) rebases the compare onto the copy — `(minus (reg 76) …)` in `.sched`,
  `(minus (reg 74) …)` in `.lreg`. A single-set copy is merged by cse instead. The copy route is closed in plain C.
- reusing `arg` for the compare (`x1`): combine folds `arg`'s first life into the compare, no second allocno.
- the free sweep's best 7 was `R6 inline ang` = dropping the lhu reuse (the very reuse the close needs, move 3).

## (f) Where the method fell short
- Nothing in steps 12–15 covers "make a LOCAL temp GLOBAL on purpose" — every listed move either splits a reused temp
  (S103 c1/c8, d15) or merges per-block locals (S103 c18). Here the answer was the inverse of d15: a reused temp is the
  CURE, because the target's register for `ang` is only reachable if nothing local sits in `$2` across the compare.
  Worth a step: "if a multi-block variable loses its register to a same-block local chain, the chain must become a
  global user variable — reuse its name at the target's same-register sites."
- The residual (REG-caller) hid that the target's `$v1` appears again in the tail: listing every target site that
  uses the compare's register (block by block, step 1 of METHOD) gave the candidate reuse sites directly.

## (g) Structs answer
Not the channel. The lever held a register against a local-alloc vs global-alloc ORDER decision (`local-alloc.c:472`
+ `global.c:594-610`), not an aliasing or address-folding decision; no memory access in the residual block changes
with a struct type. A struct for `a0` (`s16 x@6, y@0xA, z@0xE; s32 dx@0x10, dz@0x18; s16 vx@0x12, vy@0x16, vz@0x1A`)
and `SVECTOR in/out` would make the body readable but leaves the `ang`/compare allocation untouched. Not tested on
bytes (reasoned: the residual block contains no loads or stores).
