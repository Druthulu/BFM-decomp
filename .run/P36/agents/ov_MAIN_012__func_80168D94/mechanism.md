# func_80168D94 (src/ov_MAIN_012/ov_MAIN_012_jr_8015A3C8.c): T7 agent c33

**CLOSED: score 0** (`--try … body.c --body`: "score 0 (OTHER; mine 76 ins, target 76) — MATCH"). The whole-function
`objdump -drz` of the candidate object is identical to the baseline object's (`scratch/final.dis` vs
`scratch/target.dis`). All five NEEDED levers are gone: the pins on `$2`, `$4` and `$3`, the launder and the memory
barrier. There is no asm, no pin, no added volatile, no zero term, no dead assignment and no do-while.

**The same text closes all six copies and the shared header** (read-only `--try`, each score 0):
`src/ov_MAIN_012`, `src/ov_SC02_037`, `src/ov_SC03_107` (`_jr_8015A3C8.c`), `src/ov_SC07_006`, `src/ov_SC07_007`,
`src/ov_SC07_011` (`_jr_8015C32C.c`), and `src/shared/ov/func_80168D94.h` (with the header's plain `ApplyMatrixSV(…)`
call, `scratch/hdr_body.c`). Negative control: `body_free.c` scores 24 on the header, the same as here.

## The moves (two edits; each one alone scores worse)

1. **Head (the same move as func_80169058, pack A):** each arm keeps its `rand()` result in its own block-local
   `int r` and stores straight into `v10[0]`/`v10[1]`; the function-scope `v1`/`v0` are deleted.
2. **Tail:** read `+0xE` straight into its store (`*(u16 *)(s1 + 0x18) = *(u16 *)(s1 + 0xE);`) instead of
   through a local `c` loaded together with `a`/`b` at the top of the block.

| body | score |
|---|---|
| `body_free.c` | 24 (78 vs 76) |
| `b/tailonly.c`: move 2 only | 18 (78) |
| `b/b1.c`: move 1 only | 6 (76; REG: `a`,`b`,`c` in v1/a0/a1, target a0/a1/v1) |
| **`b/n2.c` = `body.c`**: both | **0** |

Other spellings that also score 0: `b/n1.c` (the tree's shape with `s32 c = …` moved into the inner block after `t`),
`b/n3.c`, `b/n4.c` (`a` also inlined, only `b` a local), and 42 of 2,520 statement orders in the grid `g1/`
(`gen_g1.py`, `g1.out`). `body.c` is the smallest change from the tree's text.

## (a) The residual

Counted first: 78 against 76. The two extra were the `move v1,v0` after each `jal rand` (pack A's defect, with the
same cause). After move 1 the count was right and a register permutation was left in the tail: the three loads
`lhu +6/+0xA/+0xE` went to `v1,a0,a1` and the target has `a0,a1,v1`.

## (b) Mechanism

**Move 1:** as pack A (`../ov_MAIN_012__func_80169058/mechanism.md` (b)). The function-scope `v0` dies in several places,
fails local-alloc.c:472, becomes a global allocno and conflicts with the arm temps in `$2`, hence the `move`. A per-arm
`r` is block-local and tied to the call's `$2`. The duplicated in-arm stores are merged back into one at the join label
by jump2's cross-jump (toplev.c:3142, `find_cross_jump` jump.c:2371). PROVED on `.lreg`/`.greg`/`.sched2`/`.jump2`
in pack A. Here it is proved on bytes (b1.c: count 78 → 76).

**Move 2: local-alloc's ranking of three equal quantities.** PROVED with `tools/localalloc_sim.py` on
`scratch/dumps_abc/` (`b/p_abc.c`, score 6) and `scratch/dumps_n2/` (`body.c`), 0 mismatches against the dumps.
- sched1 (toplev.c:3033, before local_alloc at :3052) moves the three `+6/+A/+E` loads below the two `v10` stores. They
  have the same priority, so `rank_for_schedule` falls through to `INSN_LUID` (sched.c:2428) and their order and
  position follow the source text.
- With `a, b, c` loaded together (`p_abc`), the three quantities are born at 44/46/48 and die at 54/56/58: 2 refs over a
  life of 10 each, priority 2000 each. `qty_compare_1` (local-alloc.c:1598) breaks the tie by qty number (birth order),
  so a, b, c take the lowest free registers in order (`find_free_reg`, local-alloc.c:2073). `$2` is taken by `t`
  (priority 5714), so they get `v1`, `a0`, `a1`.
- With `+0xE` read in its store statement (`n2`), sched1 keeps that load after `z` and `t` (its LUID is the highest). It is
  born at 52 and dies at 58, a life of 6 and priority 3333. It ranks ahead of `a`/`b` (2000 each, still a before b by qty
  number) and takes `v1`; `a` takes `a0` and `b` takes `a1`. That is the target's allocation, which the `$4`/`$3` pins
  forced.
- Grid rule (2,520 orders, exact): the zero set is exactly the orders with `S16 < z < c` and `b < z < t`. Only `c`
  has to be born after `z`, and `a` may be born anywhere, as long as it does not outrank `b` (a shorter life or an
  earlier birth).

The memory barrier lever (after the `v10` stores) and the launder served move 1: they kept `v0`/`v1` apart and the
stores in place. They are not needed once the stores are in the arms.

## (c) The moves, one line each

1. Per-arm `int r = rand();` and direct `v10[0]`/`v10[1]` stores in each arm; delete `v1`/`v0`.
2. `*(u16 *)(s1 + 0x18) = *(u16 *)(s1 + 0xE);` in place of the local `c` loaded at the head of the block.

## (d) Generator proposal

**"Birth the loser last":** when a register permutation among N block-local loads-into-locals that all have 2 refs
(sim priorities tied, qty-number order) puts the wrong one first, move the load of the value that the target gives the
LOWEST register to its use (inline it into its store, or declare it after the other temps). Its sched1 LUID is then the
highest, its life the shortest, and `qty_compare_1` ranks it first. Check the prediction with `localalloc_sim.py` before
compiling: one candidate per load. The grid `gen_g1.py` (all interleavings of the independent loads with the stores,
about 2 minutes at `xargs -P 20`) is the brute-force fallback, and it found the rule at once.

## (e) What did not work (byte evidence)

- Decl-order permutations of `a/b/c` at the top (`b/p_*.c`): 6 or 4. The loads stay adjacent, so the lives tie or the
  wrong one wins.
- Fully inlined tail with no locals (`b/c1.c`, `b/c2.c`): 14. The `v10[1]`/`v10[2]` reads move and `z` changes register.
- `b` inlined, `a` a local (`b/n5.c`): 6. `localalloc_sim` on `scratch/dumps_n5/` shows the `+A` and `+E` loads both
  born after `t` with a life of 6 and priority 3333 each. `+A` wins on qty number and takes `v1`, `+E` takes `a0`, and
  `a` (2000) is left with `a1`. Only the value the target puts in the lowest register may be born late.
- Move 2 without move 1 (`b/tailonly.c`): 18.

## (f) Where the method fell short

- The residual printed the register pairs of the tail and hid the COUNT defect in the head behind them. METHOD's
  "count first" was again the whole diagnosis for move 1. Pack A's close transferred to it unchanged.
- `localalloc_sim.py` answered move 2 exactly. Its output ("birth/death" per qty) makes the fix arithmetic: shorten
  the one that must win. A generator could read the sim table and propose "inline the load of qty X into its use"
  whenever X must outrank tied quantities.

Scratch: `scratch/sc.sh`, `scratch/dump.sh <body> <tag>`, `scratch/b/` (candidates), `scratch/gen_g1.py` + `g1/` +
`g1.out` (grid), `scratch/dumps_abc/`, `scratch/dumps_acb/`, `scratch/dumps_n2/`.
