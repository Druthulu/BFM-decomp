# func_80140958 (src/ov_SC04_011/ov_SC04_011_jr_80140608.c), T7 agent c48, S103 (minimum-lever)

c29's files are kept as `scratch/c29_body.c` / `scratch/c29_mechanism.md`; c13's as `scratch/prev_body.c` /
`scratch/prev_mechanism.md`. All my candidates, spliced TUs and dumps are in `scratch/c48/` (`gen.py` builds every
variant from `tmpl.c`, `t.sh <body> [tag]` scores one and dumps it).

**Status: SCORE 0 (260/260, byte-identical) with TWO marked levers. The tree carried 4 NEEDED levers (11 marked in all).**
No unmarked steering is left: c13's dead initialiser and c29's shared `size` (one variable for two unrelated 8s) are
both gone. The body is `body_free.c` with three plain-C moves and the two levers below.

## The two levers kept (the body's lines)
```
register s16 size __asm__("$2");  // !FAKE: pin $2 size — a hard reg is may_not_optimize (loop.c:596), so scan_loop (loop.c:649) cannot hoist the in-loop li 8 (P36 S103 c48 minimum-lever)
__asm__ __volatile__("" :: "r"(j));  // !FAKE: keepalive j — +3 depth-3 refs so allocno_compare (global.c:587-609) ranks j 14/76 over k 13/75 and j takes $a2 (P36 S103 c48 minimum-lever)
```
The pin is the tree's own `eight` pin, moved into the inner block and narrowed to `s16`. The keepalive is the tree's
`[L2]`, in the same place (the last statement of the inner loop body).

## Plain-C moves (the three defects solved without a lever, from c13 and c29, all unchanged)
1. The y store goes inside each arm (`*(s16 *)(q - 10) = *e - 4;` / `*e + 3;`), with no join store. jump2's
   cross-jump (`find_cross_jump`, jump.c:2371) re-merges the two stores into the target's `j 620`. This replaces the
   tree's `memory` barrier.
2. addPrim is written as a read-modify-write through one local: `w = op[2]; w &= mhi; w |= (u32)ot & m24; op[2] = w;`.
   The multi-set temp gets no birthing boost in sched1 (sched.c:2469-2540). This replaces the tree's `$4` pin on `op`.
3. The pre-loop order is the tree's `j = 0; k = m; t3v = m * 4;`. This is the target's output order.

## Single-lever table (every other move as in body.c; `--try` scores)
| lever set | pre-loop order | the 8 | score |
|---|---|---|---|
| none | tree (j,k,t3v) | literal | 49 (261 ins) |
| none | c13 (t3v,k,j) | literal | 43 (261 ins) |
| keepalive j only | tree | literal | 39 (261: the 8 is hoisted) |
| keepalive j only | c13 | literal | 43 |
| pin $2 size only | tree | pinned | 10 (j/k swap a2/a3) |
| pin $2 size only | c13 | pinned | 4 (ORDER: 3 pre-loop insns reversed) |
| pin $6 j only | tree | literal | 43 (259 ins: the increment changes) |
| launder size only, volatile `"=r"(size) : "0"(8)` | tree / c13 | laundered | 28 / 22 (261 ins: the asm blocks sched) |
| launder size only, non-volatile `"=r"(size) : "0"(size)` | tree | laundered | 35 |
| **pin $2 size + keepalive j** | **tree** | **pinned** | **0** |
| pin $2 size + keepalive j | c13 | pinned | 4 (order) |
| pin $2 size + pin $6 j | tree | pinned | 13 (258 ins) |
| volatile launder + keepalive j | tree | laundered | 18 |
| one asm doing both (`"=r"(size) : "0"(8), "r"(j)`) | tree | laundered | 18 |
| *keepalive j + c13's dead `s16 size = 0;`* | tree | var | *0, but the dead store is steering* |
| *keepalive j + c29's shared `size`* | tree | var | *0, but the shared variable is steering* |

So no single lever reaches 0. Each of the two remaining defects is a separate pass decision, and neither lever
touches the other's pass. Candidates: `scratch/c48/v_*.c`, `w_*.c`.

## The two paths (why each needs its own lever)
### Path 1: the constant 8 (loop.c invariant motion)
- The target keeps `li v0,8; sh v0,2(a1); sh v0,0(a1)` inside the inner loop.
- `scan_loop` (loop.c:681-690) moves a set when one of three cases holds:
  - (1) `reg_in_basic_block_p`, which needs `regno_first_uid == this set` and the last use in the same block;
  - (2) the register is not a user variable;
  - (3) the set is always executed.
- `move_movables` (loop.c:1631) then moves it if `threshold * savings * lifetime >= insn_count`.
  - Here `threshold = 2 * (1 + 28) = 58`, `savings = n_times_used = n_times_set = 1` (loop.c:598), and the lifetime is
    2 (a set and two stores).
  - That gives 116 ≥ 74, so the 8 is hoisted. The `.loop` dump says `Insn 476: regno 240 (life 2) ... moved to 609`,
    and it is then hoisted out of the outer loop too.
  - The other in-loop constants (0x30, 0x38, 0x78, 0x4056) stay in the loop only because each has one use (life 1:
    58 < 74).
- So the 8 stays only in two situations:
  - It is a hard register (`may_not_optimize`, loop.c:596). That is the pin.
  - It is a user variable whose first mention at `reg_scan` time is an EARLIER insn that is gone before flow, so that
    local-alloc still sees it as a one-block qty and gives it `$v0`. The earlier insn can be a dead set (c13) or a use
    that cse folds (c29).
- I found no honest source of such an earlier mention. The sprite's w/h has no other meaning in this function:
  the call's `dx` 8, the `b[-2] & 8` flag bit and the `& 7` masks are all unrelated.
- The routes that rule out anything short of the pin, each checked on bytes or in the source:
  - Every literal spelling is hoisted.
  - A set in both arms is a global allocno and loses `$v0` (c13 s3, 18).
  - A set before the `j == 0` branch is case (3) and is hoisted.
  - A launder changes the schedule (18-35).

### Path 2: j vs k in global.c
- In the target's output order j is born first, and sched1 overwrites the live lengths with the output order
  (sched.c:4947). The result is j 11/75 against k 13/74 (k is 13 because cse makes k the head of m's class,
  cse.c:826-862, so `t3v` reads k).
- `allocno_compare` gives j 4400 and k 5270, so k is allocated first and takes `$a2`.
- If `t3v` reads m, k has 11 refs. j would still lose, 11/75 against 11/74, because it lives one insn longer.
  It would need 12 refs.
- j's natural count is 11. A use in arm A is folded by cse before flow, and the exit test reads the SImode increment
  temp (both shown by c13/c29).
- The keepalive adds exactly one depth-3 ref, which gives j 14/76 = 5526 against k 13/75 = 5200 (read from
  `alloc_table.py v_pin8ka`, proven on bytes).
- c13's order (`t3v` first, j last) gets the allocation right but the 3-instruction order wrong (4) with or without
  the keepalive (`w_c13_pin8ka` 4).

## Proven vs not proven
- Proven on bytes: every score in the table, and the priorities 5526/5200 (v_pin8ka) and 4400/5270 (v_pin8).
- Proven from the loop dump: the hoist and the life-1 retention.
- Not proven: that NO honest C gives j a 12th ref or gives the 8 an honest earlier mention. That is an argument from
  the passes, plus c13's and c29's ~60 failed spellings, not an exhaustive search.

## Generator proposal
When a body closes only with a steering-in-C-clothing construct, emit the equivalent standard lever instead and count it:
- **Loop-hoist class (a constant hoisted out of a loop: extra `li` in the preheader, temps shifted):** a dead
  initialiser or a shared named constant that defeats `reg_in_basic_block_p` maps to ONE `register T v __asm__("$N")`
  pin, with N the target's register for the in-loop `li`.
- **Priority class (a register swap between two globals whose `allocno_compare` gap is under one depth-weighted
  ref):** maps to ONE keepalive on the loser, at the deepest loop level.
- Always score each lever alone before combining. Here the table shows they are independent, so the minimum is their
  sum.

## Where the method fell short
- The brief's lever kinds have no counted form for "first mention deleted before flow" (a dead store or a folded use).
  Those constructs are exactly what the pin replaces. It would help to list them in METHOD_S103 as known C-clothing
  for the loop.c case-(1) test.
- gcc 2.7.2 rejects `"+r"` constraints ("output operand constraint contains `+'"). A launder must be written
  `"=r"(x) : "0"(x)`. That belongs in the lever-form list.
