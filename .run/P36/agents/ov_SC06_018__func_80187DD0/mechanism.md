# func_80187DD0 (src/ov_SC06_018/ov_SC06_018_jr_80187AEC.c), e5, P36 T7 S104: MINIMUM-LEVER at 0

**Final: score 0 (174/174 ins, byte-identical).** Lever count 1 → 1, but the kind changes: the `register u32 v0 __asm__("$2")`
pin becomes ONE marked `do { … } while (0);` around the two halfword stores, which is ordinary C (step 8). No pin, no asm,
no volatile. The best lever-free text scores **2** (below). The nibble-packing block now reads:

    v0 = *(u32 *)(a1 + 0x60);
    a0 = *(u8 *)(a1 + 0x61) | ((v0 & 0xF) << 8);
    v1 = (((s32)v0 >> 16) & 0xFF) | ((v0 & 0xF0) << 4);
    do {  // !FAKE: do-while — …
        *(u16 *)(param_1 + 0x104) = a0;
        *(u16 *)(param_1 + 0x106) = v1;
    } while (0);

**The same block closes all five other copies of the class, each `--try` at 0** (`scratch/copy_<fn>.c`, built by
`scratch/port.py`, which swaps only this block into the tree's text): func_80181F40 (ov_SC06_020), func_80185E64 (ov_SC06_022),
func_8018833C (ov_SC06_024), func_80182B74 (ov_SC06_032), func_80186858 (ov_SC06_033). That is 6 pins → 6 marked do-whiles.

## (a) The residual
Same count, a register permutation in one block (local-alloc). The target has the loaded word `w` in v0 and the `(w&0xF)<<8`
temp in v1. The lever-free text swaps them (and the or's result with them).

## (b) The pass and the decision (local-alloc, proved with `lsim3.py` on every candidate's `.lreg`, 0 mismatches)
Quantities in the block (numbers are local-alloc's birth/death indices, 2 per insn). The target needs this assignment:
q2 = {w, w&0xF0, <<4} → v0, q3 = {w&0xF, <<8} → v1, q5 = {>>16, &0xFF, the second or} → v1, q4 = {lbu 0x61, the first
or} → a0, q0 = {mask, a1} → a1. `qty_compare_1` (local-alloc.c:1598) ranks by `floor_log2(refs)·refs/(death−birth)`,
with ties going to the lower qty number:
- q2 (8 refs) against q3 (4 refs): **24/L2 ≥ 8/L3**. That holds only when sched1's order is `lw, andi 0xf, lbu, sll 8, or,
  <group 2>, sh, sh`: L2 = 18, L3 = 6, a 13333 tie that q2 wins on number. If the 0x104 store is scheduled inside q2's range
  (the lever-free default: sched1 puts it right after the first or because the group-2 insns are birthing-boosted,
  sched.c:2507-2545), then L2 = 20, q3 wins, and w loses v0. That is the residual.
- q4 (4 refs, L4 = 16 when the store sits after group 2) against q0 (9 refs, L0 = 50): 0.50 < 0.54, so q0 takes a0 and
  the lbu gets a1. Fixing the first condition alone turns the v0/v1 residual into an a0/a1 one (score 11,
  `e3/u16u16_aa.c`: u16 result variables make the ors SUBREG-destination sets that fail `birthing_insn_p`, which moves
  the store late). L4 cannot drop to 14 without a barrier (the lbu→or load latency queues the lbu behind the `sll`,
  sched.c:2583-2600), so q4 needs a fifth ref.
- **The do-while supplies both.** flow counts a ref at `loop_depth` (2 inside the loop; propagate_block tracks the LOOP notes, flow.c:1440-1449, and mark_used_regs adds `reg_n_refs += loop_depth`, flow.c:2711), so the store's use of a0 makes
  q4 5 refs: 10/16 = 0.625 > 0.54. The LOOP notes are a full sched barrier (sched.c:2053-2074), so the stores cannot
  be hoisted into q2's range: L2 = 18. `lsim3` on `scratch/dumps_b9/`: q2 13333, q3 13333, q5 11666, q4 **6250**, q0
  5400. That is exactly the target assignment. In sched2 the barrier only keeps the stores where the target has them.

## (c) The move
Inline the two packed values into one expression each (`a0 = lbu | ((w & 0xF) << 8)`, so the lbu's destination is set
once and stays birthing-boosted, which puts it between `andi` and `sll`) and wrap the two stores in `do { } while (0)`.
Each piece is needed. Body_free + the do-while alone scores 10, because `a0` is set twice there, the lbu is not
boosted and it is scheduled first.

## (d) GENERATOR PROPOSAL
For a local-alloc permutation where `lsim3` shows the loser short by one ref or by 2 in live length, try (1) a
`do { <the store that is the losing quantity's last use> } while (0)`, which doubles that ref (flow loop_depth) and pins
the store after everything above it. Also try (2) inlining a two-statement `x = load; x |= y;` into one expression so the load's
destination is set once (it becomes birthing-boosted). Score the pair, and each alone. Mark (1) as `!FAKE: do-while`.

## (e) What did not work (all `--try`, ~1,100 candidates in `scratch/e1`..`e9`)
| family | best | why |
|---|---|---|
| inline / operand order / statement order of the 7 temps (`e1`, 160) | **2** (`u32_a1101_s01_o0.c`, in `body_plain_best.c`) | the second or's result ties to `(w&0xF0)<<4` (q2 13636 > q3), so w gets v0, but the or result lands in v0, not v1 |
| variable reuse / compound assignment (`e2`, 256) | 3 | the same tie structures |
| u16/s16 result variables (`e3`, 180) | 11 | v0/v1 right, a0/a1 swapped (q4 0.50 < q0 0.54, above) |
| extra copies to add refs (`e4`/`e5`, 330) | 3 | cse folds the copies before flow counts the refs |
| `const` reads to relax the store→load dependences (`e6`/`e7`) | 2 | RTX_UNCHANGING_P reorders everything (up to 93 worse) |
| barrier between `sll` and `lbu` (`e8`) | 9 | the allocation is exactly right, but the barrier survives into sched2, the lbu cannot fill the lw delay slot, +2 nops |

## (f) Where the method fell short
- `lsim3.py` was decisive: every hypothesis was two numbers on its table. It needs a documented home (it lives in
  another agent's scratch). It should also print each qty's registers' refs, which is how the loop-depth ref showed up.
- Nothing in the method says flow's `reg_n_refs` is **weighted by loop depth**, so a `do { } while (0)` changes
  allocation priorities as well as the schedule. That is a second, independent effect of the same marked construct (d4 used only the barrier).
- A two-sided allocation constraint (q2≥q3 AND q4>q0) where every plain-C single move fixes one side and breaks the
  other is a case for an exhaustive search over the priority arithmetic, not for more spellings.

- Interpretation (not proven): two stores wrapped in `do { … } while (0)` is the shape of a C statement macro
  (`#define SET_PAIR(p, a, b) do { … } while (0)`), so this may be the original text rather than a lever. The sibling
  in 800.c (`local[1] = a1[3].b1 | ((w & 0xF) << 8); local[2] = …`) is lever-free because it sits inside a real
  `while` loop, which again points to loop depth as the missing fact.

## (g) Structs answer
Unlikely to remove this lever. The deciding quantities are refs and live lengths in local-alloc, plus sched1's
placement of the 0x104 store. Struct field access would make the reads and stores `MEM_IN_STRUCT_P`, and they already
are (every `*(T *)(p + K)` is a PLUS_EXPR address, expr.c:4568-4577). `true_dependence` (sched.c:817-842) disambiguates
only against a fixed address, and both sides here are register-based, so the dependences cannot change. Tested the only
aliasing channel that could move the store, `const` (RTX_UNCHANGING_P): it makes things worse. What a struct *could*
supply is the original's shape of this block, e.g. a colour struct written through a pointer inside a loop over parts. If
the original sits in a real loop, the do-while stands in for real loop depth, and that information lives in the caller's
structure, not in a type.

Files: `body.c` (min-lever text), `body_plain_best.c` (best lever-free text, 2), `scratch/copy_<fn>.c` (5 class copies
at 0), `scratch/port.py`, `scratch/an.sh` (dump + lsim3 + sched order for one candidate), `scratch/dumps_b9/` (the close),
`scratch/dumps_u16aa/` (the a0/a1 case), `scratch/e1`..`e9` (candidate families with `eN_scores.txt`).
