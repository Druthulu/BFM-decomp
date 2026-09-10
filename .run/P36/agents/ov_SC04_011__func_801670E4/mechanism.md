# func_801670E4 (src/ov_SC04_011/ov_SC04_011_jr_8015C32C.c): T7 agent c14

**CLOSED: score 0** (`--try ... body.c --body`: "score 0 (OTHER; mine 279 ins, target 279) — MATCH"; run twice, stable).
The whole-function `objdump -drz` of my scratch object is identical to the tree object's, relocations included
(`scratch/d_final/fn.dis` vs `scratch/target.dis`). All seven NEEDED levers are gone: the two pins ($2, $4), the barrier and
the four launders. There is no asm, no pin, no added volatile and no zero term. `PACK/body.c` is the text to bank; the
whole-object gate is still the coordinator's job.

**The same body also closes both shared twins** (read-only `--try` on a scratch copy of the whole TU, with the
`#include` replaced by `body.c` and the three `D_` table symbols swapped):
`src/shared/ov/func_801670E4__07fc245b.h` in ov_SC04_021 scores 0, and `func_801670E4__5e212bc3.h` in ov_SC04_008 scores 0
(`scratch/twin_07fc245b.c`, `scratch/twin_5e212bc3.c`). Negative control: `body_free.c` put through the same route scores 45
(`scratch/twin_neg.c`), the same as in this TU. They carry the identical lever set, so the coordinator can bank all three
from one text.

## The moves (five source edits; the first alone fixes the instruction count)

| step | body | score |
|---|---|---|
| start | `body_free.c` | 45 (281 vs 279) |
| 1 | pass `&f.cx` straight to the calls; delete `va`, `vb`, `vc` (`scratch/a1.c`) | 36 (279 vs 279) |
| 2 | `p = D_80193330; i = 0;` moved to just before the first loop (`b1.c`) | 28 |
| 3 | the same for `p = D_80193344; i = 0;` in the `if` block (`c1.c`) | 22 |
| 4 | block 2 rewritten in plain statements, no `gA`/`cxv`/`czv` temps (`v2/n000.c`) | 4 |
| 5 | `f.col[1].g = cv;` written before `f.col[1].r = cv;` (`v3/d1.c`) | **0** |
| tidy | `ap`/`mp` deleted, `f.m1` used directly; unused decls dropped (`e2.c` = `body.c`) | 0 |

Ablations of the final body (one move taken back, all `--try`): `va`/`vb` put back → 5 (280 vs 279); block-1 `p`/`i`
put back at their old place → 8; block 2 put back to the `gA`/`cxv`/`czv` spelling → 18. Move 5 alone on `body_free.c` → 41.
Every move is needed.

Block 2 as it now reads:
```c
    p = D_8019331C;
    i = 0;
    f.v[3].y = 0;  f.v[2].y = 0;  f.v[0].y = 0;
    f.col[1].g = 0xA0;  f.col[1].b = 0x10;  f.col[1].r = 0x10;
    f.pos[0] = D_801269A4 - (s16)f.cx;
    f.pos[1] = D_801269A8 - (s16)f.cy;
    f.pos[2] = D_801269AC - (s16)f.cz;
```

## (a) The residual

I counted first: 281 against 279, so two instructions were extra. Both came from one defect. `&f.cx` (sp+16) was held in
callee-saved `s0` and copied into each argument (`addiu s0,sp,16; move a1,s0; move a2,s0` at the head, and
`addiu s0,sp,16; move a0,s0` in the `if` block). The target rematerialises `addiu aN,sp,16` at each call instead. The rest
was order and registers: (i) `la s2` / `move s4,zero` (the loop's `p` and `i`) sat at the top of the entry block and at the
top of the `if` block, where the target has them after the argument setup; (ii) block 2's `v0`/`v1`/`a0` assignment
(the `$2`/`$4` pins); (iii) `sb v1,84` / `sb v1,85` swapped around the first `jal`.

## (b) Mechanisms (passes and decisions)

**Move 1: cse, cheapest equivalent** (PROVED on `.rtl`/`.cse`, `scratch/d_free` vs `scratch/d_final`). `f.cx` is at offset 0
of `f`, and `f` is the first local, so `&f.cx` expands to the bare `(reg:SI 69 virtual-stack-vars)`. A REG call argument is
not forced into a pseudo, so expand emits `(set (reg a1) (reg 69))` directly (`d_final/t.i.rtl` insns 98/100/140/151). With
`va = &f.cx` the value first lands in a USER pseudo (`d_free` insn 52 `(set (reg/v 90) (plus fp 16))`). cse's cheapest-source
choice (`cse.c:6776-6803`: a REG elt costs less than the PLUS) then rewrites every later `(set aN (plus fp 16))` to
`(reg/v 90)` (`d_free/t.i.cse` insns 112, 152, 163). That makes 90 live across four calls, so it gets `s0` and each use costs
a `move`. Without the variable, the only register that holds fp+16 is the hard `a1`. cse replaces a2's source with it
(`d_final/t.i.cse` insn 100 `(set a2 (reg a1))`, which is the target's `move a2,a1`), and the call's `invalidate_for_call`
(`cse.c:1725`, called at `cse.c:7247`) kills that equivalence. Each later `&f.cx` is therefore rematerialised. `f.a8`/`f.m1`
are `(plus 69 K)`, are forced into pseudos by expand, and stay shared in `s1`/`s0`, which is what the target does with them.
The launders did the same job by making `va`'s value opaque to cse.

**Moves 2 and 3: sched1 tie-breaks** (PROVED on the `.sched` trace, `d_final/t.i.sched` block 0). `p = SYM` and `i = 0` have
no dependence inside the block. They sit in the ready list from the start with priority 1 (`priority`, `sched.c:1425`: the
cost-minus-one sum along the dependence chain). Two rules then decide where they land in the backward list schedule.
- `schedule_select` (`sched.c:2616`) takes the same-priority insn with the greatest `potential_hazard` first, so every
  priority-1 store (memory unit, `mips.md:161`) is placed before them: "insn 93/90/87/.../55 has a greater potential hazard".
- Among the unit-less leftovers, `rank_for_schedule` (`sched.c:2385`) falls through to `INSN_LUID`, and the highest LUID
  goes first.

In the old text `p`/`i` had LUIDs 55/58, lower than the argument copies `a1 = fp+16` / `a2 = a1` (98/100 emitted at the
call). So they lost every tie and floated to the block head. Written right before the loop, they get the block's highest
LUIDs (176/179). They are taken at T-46/T-47, straight after the last store and before `a2 = a1` (100). The final order is
`sh a1; addiu a1,sp,16; sh a2; move a2,a1; la s2; move s4,zero`, the target's. The `if` block is the same case.

**Move 4: block 2, local-alloc eligibility plus order.**
- PROVED on `.lreg`/`.greg`: the old spelling reused `gA` for `0xA0` and for `D_801269A4`. `d_c1/t.i.lreg` shows
  "Register 84 used 4 times across 12 insns; dies in 2 places". `local-alloc.c:472` gives a pseudo to local-alloc only when
  `reg_n_deaths == 1`, so `gA` became a global allocno. It was allocated after every local qty and got `a0`
  (`.greg` dispositions: "84 in 4"). That is the `li a0,160` / `lw a0,D_801269A4` against the target's `v0`. Spelled
  without the temp, `0xA0` is a QImode temp that dies at its store and `D_801269A4` gets its own temp. Both are local qtys
  and both get `v0`, as in the target.
- Proved on BYTES ONLY, not traced: the statement order. The split alone (`s_m1.c`, the old order with `0xA0` inlined)
  scores 17, and inlining every temp in the old order (`s_m3.c`) scores 20. I then enumerated 144 natural orders of the
  plain statements (`scratch/v2/`: 6 `col` orders × 2 `pos` orders × 2 `v.y` orders × 3 `p/i` positions × `v.y` stores
  before/after). The ones that score 4 (then 0 with move 5) all have: the `v[].y` zero stores first (3,2,0), `col` in
  g,b,r order, and `pos` in 0,1,2 order. The `p/i` position inside block 2 does not matter. I read this as sched1/sched2
  LUID tie-breaks over the `lh`/`lw` pairs, but I did not trace it pass by pass.

**Move 5: sched1 LUID order plus the reorg delay slot** (PROVED on `.sched` and bytes). The two `cv` stores have equal
priority and both use the memory unit, so their relative order is source order. `fill_simple_delay_slots` puts the last one
before the `jal` into the slot. The target's `sb v1,85; jal; sb v1,84` means `g` (+0x55) was written before `r` (+0x54).

## (c) The moves, one line each

1. Pass `&f.cx` itself to `func_80149350` (twice) and to the `if` block's `func_80017E68`; delete the `va`/`vb`/`vc` pointer
   locals.
2. Put each loop's `p = <table>; i = 0;` immediately before its `do`, in the entry block and in the `if` block.
3. Write block 2 as plain statements: `v[].y = 0` ×3, `col[1].g/.b/.r`, then `pos[k] = D_… - (s16)f.c?` in k order, with no
   reused `gA` temp and no `cxv`/`czv` temps.
4. `f.col[1].g = cv;` before `f.col[1].r = cv;`.

## (d) Generator proposals

- **R24 "no alias for a frame address"**: when the target does `addiu aN,sp,K` at every call but mine holds sp+K in a
  callee-saved register and copies it (`move aN,sK`), and the body has a pointer local set to `&local` or `&s.first_member`,
  delete the local and write the address-of at each use. A user pseudo holding a fixed-base address becomes cse's
  cheapest equivalent for every later `&x` (`cse.c:6776`). The launder lever on such a local is the flag to look for.
- **R25 "late loop init"**: when a loop's `p = SYM; i = 0;` lands at the block head in mine but later in the target (after
  argument setup or stores), move those statements to immediately before the loop. The textual position is their LUID,
  which is the last tie-break (`sched.c:2385`) once the memory-unit hazard rule (`sched.c:2616`) has placed the stores. The
  barrier lever just before them is the flag to look for.
- **R26 "slot store order"**: when two stores of one value around a `jal` differ only in which one is in the delay slot,
  swap the two source statements.
- Block 2 is R12/R20-style: a reused temp that "dies in 2 places" in `.lreg` is a global allocno. Inline or split it, then
  enumerate the natural statement orders. That grid is cheap (144 compiles, about 2.5 minutes) and found the order at once.

## (e) What did not work (byte evidence)

- Moving `p`/`i` to other early places in block 1 (`b3`-`b7.c`: after `ent = arg0`, after `f.cz = arg3`, after the `col`
  stores, after `f.code`, before the `col` stores): all 36, no change. Only a place after the call works (`b1.c` before the
  loop and `b2.c` right after the call both score 28), because that is what gives the highest LUIDs.
- `f.col[1].g = f.col[1].r = cv;` (`d3.c`) stays at 4. `f.col[1].r = f.col[1].g = cv;` (`d2.c`) scores 0, the same as move 5.
- Block 2 with only the temp split (`s_m1`/`s_m2`, 17) or everything inlined in the old order (`s_m3`, 20). The order is needed
  as well.

## (f) Where the method fell short

- **The start was not a register problem, and the pins pointed the wrong way.** The two pins ($2/$4) were block-2 cosmetics.
  The count gap came from the launders. Counting first (METHOD step 2) went straight to it: 281 against 279, then the
  whole-function objdump showed the `s0` copies.
- **The TU header's `@stuck` note above func_801670E4 is wrong**: "gcc's list-scheduler puts `la $s2` + `addu $s4` BEFORE the
  callee-arg address setup ... Inert to ~40 statement-order permutations". Its permutations kept `p = …; i = 0;` in the
  early part of the block. The fix is to put them after the call (move 2). The coordinator should replace the note when
  banking. This is the third refuted `@stuck` claim.
- **The sched trace needs `schedule_select` in view.** The `;; ready list ... now` line in the `.sched` dump is not always
  the insn scheduled next: `schedule_select`'s "greater potential hazard" line reorders the list after it. Reading only the
  `now` lists gave me a wrong prediction first. A tool that replays the pick order (`rank_for_schedule` +
  `potential_hazard`) would make LUID-placement moves computable.
- `residual_moves.md` has no row for "user pointer local to a frame address makes cse share it across calls" (move 1) or
  for "the textual position of an independent init sets its sched LUID" (move 2). Both are cheap to detect from the diff.
- The mechanical search never deleted a pointer local whose value is `&local` (R6 "inline" only inlined single uses), and it
  never moved an init statement across a call.

Scratch: `scratch/dump.py` (splice the body, then cpp, cc1 with dumps, maspsx, as, objdump of this function),
`scratch/rtl1.py` (one line per insn), `scratch/sc.sh` (scoring), `scratch/fn.sh`.
