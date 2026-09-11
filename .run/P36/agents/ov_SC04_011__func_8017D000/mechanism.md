# func_8017D000 (ov_SC04_011, TU ov_SC04_011_jr_8017AE2C.c) — T7 agent c44

**Result: score 0, lever-free.** No register pin, no asm, no added volatile, no do-while, no invented term, no dead
assignment. The fix is inside the function body only. Whole-object check on the `--try --keep` object: `objdump -drz` of the
ENTIRE `.o` (every function, relocations included) is identical to `.run/P36/delever/baseline/src/ov_SC04_011/
ov_SC04_011_jr_8017AE2C.o`, and `.text` compares equal with `cmp`. Candidates are in `scratch/` (`a1.c`, `b1.c`, `c1.c`,
`d1.c` = `body.c`, `e1.c`) with their `.dis`; the pass dumps are in `scratch/dumps_free/` and `scratch/dumps_d1/`.

No lever-free copy existed elsewhere: `git grep` finds no other definition that touches `D_801EEDA8`, and
`related.txt` listed no port candidate (the only `func_8017D000` in `src/shared/ov/` is an unrelated function with the same
overlay address).

## (a) The residual in one sentence

COUNT 296 vs 293. There were three independent defects. (1) In the `== 0xB` arm, `f` and `v` had swapped registers and
`f + 1; sw` was hoisted above `negu; andi 0xc0`. (2) In the else arm, `*(s16 *)(q + 0xF) = x` became an absolute
`lui at; sh v0,15(at)` (+1) where the target writes `sh v0,15(a2)`. As a result `addiu a0,a2,15` left the `jal` delay
slot (+1 `nop`). (3) In the tail, `*(u16 *)(p - 0x18)` became an absolute `lui v0; lhu v0,-24(v0)` (+1) where the target
reads `lhu v0,-24(s0)`.

## (b) The passes and the decisions (all three proven on bytes and in dumps)

### Defects 2 and 3: cse folds a base+offset MEM address into an absolute address. A register address is not folded.

* `find_best_addr` (cse.c:2621). An address that is not a bare REG is first run through `fold_rtx` and accepted by
  `validate_change` with NO cost test (cse.c:2659-2662). `p` / `q` carry the constant equivalence `&SYM`, so
  `(plus p -24)` folds to `(const (plus SYM -24))`, which is a valid MIPS address (the assembler's `lui at` macro). This is
  why the tree needed the three launders.
* A BARE REG address skips that fold. For a REG, cse looks up the register's equivalence class and takes the member with
  the lowest `ADDRESS_COST`, breaking ties by the higher `rtx_cost` (cse.c:2708-2735). `ADDRESS_COST(REG)=1`
  (mips.h:2895), `(plus reg small_int)`=1, and `(const (plus sym k))`=2 (`mips_address_cost`, mips.c:1615-1653). So
  for `s = q + 15; *s = x;` the class of `s` is {`s`, `(plus q 15)`, `(const D_801EED4D+15)`}. The tie at cost 1 goes to
  `(plus q 15)` (the higher rtx_cost). The constant, at cost 2, is never chosen. Dump proof: `dumps_d1/d1.i.rtl` insn 433
  is `(set (mem:HI (reg 240)) …)`, and `d1.i.cse` rewrites it as `(set (mem:HI (plus (reg 236) 15)) …)`. The tail
  behaves the same way: insn 485 becomes `(mem:HI (plus (reg 86) -24))`.
* After that, the pointer temp's only other use is the call argument. The `(set s (plus q 15))` insn stays where the
  source put it, just before the call (it is kept as a PLUS because `rtx_cost` of the CONST is higher). So reorg puts
  `addiu a0,a2,15` back into the `jal` delay slot, and the tail's `r` ties to `p`'s `$s0` (`addiu s0,s0,-24` in the
  first `jal`'s delay slot), as in the target.

### Defect 1: sched1's `birthing_insn_p` boost. The `u8` width removes it.

* With `s32 v`, the last insn of the chain (`v = t & 0xC0`) is a SET of a REG that is live after it and set only once.
  `birthing_insn_p` (sched.c:2468-2499) returns 1 for it, and `adjust_priority` (sched.c:2539-2545) raises it to
  `max_priority` when it becomes ready in the backward list scheduler. So the `v` chain is placed right before its first
  `sb`, and `f + 1; sw` is scheduled above `negu/andi` (`dumps_free/free.i.lreg`: order 255 257 **262 265** 258 259 268).
* With `u8 v` (the width of every destination it is stored to), combine folds the truncating move into the `and`, and
  that insn's destination becomes `(subreg:SI (reg:QI 191) 0)`. `birthing_insn_p` wants `GET_CODE (SET_DEST) == REG`,
  so it gets no boost, and sched1 keeps source order: 255 259 262 269 272 275 278 (`dumps_d1/d1.i.sched`). Local-alloc
  then gives `v` `$v0` and `f` `$v1`, as in the target. This is the same fact the tree's asm launder was forcing: an asm
  output is not a plain birthing SET of the chain.

## (c) The source moves that closed it (three, independent; the scores are additive)

1. `s32 v = -(f & 1) & 0xC0;` → `u8 v = …` (the width of the ten `u8` stores). 33 → 17 (`a1.c`).
2. Else arm: `s16 *s = (s16 *)(q + 0xF); *s = x; … func_800176F0(s);` instead of `*(s16 *)(q + 0xF) = x; …
   func_800176F0(q + 0xF);`. On top of 1: 17 → 2 (`c1.c`).
3. Tail: `r = p - 0xC; D_801EED98 = *(u16 *)r + (u16)D_80193E88; *p = D_801EED98 - 4; func_800176F0(p - 0x40);
   func_800176F0(r);` instead of the reassigned `p` + `w`. On top of 1: 17 → 15 (`b1.c`). 1+2+3: **0** (`d1.c`).
   Control: 2+3 without 1 = 16 (`e1.c`, MIXED), so move 1 is exactly defect 1.

## (d) GENERATOR PROPOSALS

* **COUNT +1 `lui at` / `lui vN` on an offset load/store where the target uses `k(reg)` of a pointer that holds `&SYM`:**
  name the offset address as a pointer local (`T *s = (T *)(base + k); *s = …`), and if the target also passes
  `base + k` to a call, pass `s` there. cse's `find_best_addr` keeps a register address as `(plus base k)` (cost tie,
  cse.c:2715-2721) but folds a written-out `base + k` to an absolute address (cse.c:2659). This is the plain-C
  replacement for the `__asm__("" : "=r"(p) : "0"(p))` launder whenever the pointer's other uses are call arguments.
* **ORDER + swapped `$v0/$v1` where the target computes a value's whole chain before an unrelated `x+1; sw`:** if the
  value is only stored narrow (`sb`/`sh`), declare it with the store width (`u8`/`s16`). The subreg destination stops
  sched1's birthing boost (sched.c:2468-2545). Test: `.lreg` shows the chain's last insn scheduled right before its first
  use.

## (e) What did not work (byte evidence)

* `*(s32 *)(a0 + 0x1C) = f + 1;` with `f` not reassigned: 21 (`a2.c`). Worse, because the register swap stays.
* `b1.c` (tail only, on top of move 1): 15. That fixes the tail's `lui`; the else arm's absolute `sh` + `nop` remain.
* The mechanical search's best (15, a do-while + `R8 base tmp0`) never tried a pointer local on a MEM address. Its
  `R12 width t` moves narrowed `t`, not `v`.

## (f) Where the method fell short

* METHOD_S103's launder list (c11: "write the read relative to a DERIVED pointer") describes the case where the pointer
  is NOT known constant to cse. Here the pointer IS a known constant in the same block, and the answer is simpler:
  make the address itself a REGISTER. `find_best_addr` never folds a REG, only non-REG addresses (cse.c:2659 vs
  :2708-2735). This should be the FIRST launder move tried: it is one line and needs no pass-ordering conditions.
* COUNT-first worked: the three extras were one `lui at`, one `nop`, and one `lui v0`, each visible only in the whole
  objdump (the hunk view split the `sh 15(a2)` across two hunks).
