# func_801837E8 (ov_SC05_018_jr_8017D604.c) — P36 T7 S104 agent d5

**Result: score 0 in plain C, no levers** (before: 1 lever, the `register s32 p __asm__("$2")` pin in case2; after: 0).
Took one `--try`; four spellings reach 0 (below). `PACK/body.c` = variant **b**.

The move (case2 only): delete the hoisted temp `v0` and write the update as a compound assignment, so the `+0xFC` read comes
after the lhs load:
```c
    s32 p;
    p = *(s32 *)(a0 + 0x20);
    *(u16 *)(p + 0x12) += *(u16 *)(a0 + 0xFC);
```

## (a) The residual
Same 94 instructions. In case2's block, three block-local pseudos are permuted: the pointer `p` (`lw 32(s0)`), the `+0xFC`
value `fc` and the tied load/sum `ld/sum` (`lhu 18(p)` + the `addu`). Mine: ld/sum=$v0, fc=$v1, p=$a1. Target: p=$v0,
ld/sum=$v1, fc=$a1. No instruction is missing (counted first: 94/94, same mnemonics in the same order).

## (b) The pass and the decision (PROVEN on dumps + bytes)
local-alloc, `block_alloc`, **the special case for exactly three quantities**, `local-alloc.c:1486-1507` (the same code for the
suggested-register pass is at `:1439-1462`):
```c
    case 3:
      if (qty_compare (0, 1) > 0) EXCHANGE (0, 1);
      if (qty_compare (1, 2) > 0) EXCHANGE (2, 1);
    case 2:
      if (qty_compare (0, 1) > 0) EXCHANGE (0, 1);
```
`EXCHANGE` swaps *positions* in `qty_order`, but `qty_compare` is always called on the fixed *qty numbers* 0, 1, 2, and qty
numbers are handed out in BIRTH order while the block is scanned. This is not a sort. Worked out for a block with exactly
three qtys (pri = `qty_compare`'s floor_log2(refs)·refs/len):
- pri1 > pri0 and pri2 > pri1 → order [q2, q1, q0]
- pri1 > pri0 and pri2 ≤ pri1 → order **[q0, q1, q2]** (q0 goes first even though q1 ranks higher)
- pri1 ≤ pri0 → [q0, q1, q2], or [q0, q2, q1] when pri2 > pri1.
So **the first-born qty is allocated first unless the priorities strictly increase in birth order.** `find_free_reg` then
hands out the lowest free register ($2, $3, then $5, because `$a0` is live for the call argument).

Case2's priorities (`.lreg`, block 11): p 3000 (3 refs), fc 3333/5000, ld/sum 13333/10000 (tied, 4 refs).
- **body_free**: the source reads `v0 = +0xFC` BEFORE the lhs load, so expand emits fc, p, ld (`.rtl`); sched1 hoists p
  but ld still comes after fc. Births: q0=p, q1=fc, q2=ld/sum. 3333>3000 and 13333>3333 → [ld/sum, fc, p] → ld/sum $2, fc $3,
  p $5 (the residual).
- **body.c**: the compound assignment evaluates its lhs first (`lhs = lhs + rhs`, PLUS_EXPR operand 0 expanded first), so
  expand emits p, ld, fc (`.rtl`). Births: q0=p, q1=ld/sum, q2=fc. 10000>3000 but 5000<10000 → [p, ld/sum, fc] → p $2,
  ld/sum $3, fc $5 = the target.
Byte evidence: the dump of the matching body shows `;; Register 93 in 2` (p) while a correct sort would give it $5.
body.c's own dump (`PACK/scratch/dumps_b/`) prints q0=p 3000, q1=ld/sum 10000, q2=fc 5000; the patched simulator matches it
(0 mismatches) and the shipped one does not (3).

**Tool defect found (`tools/localalloc_sim.py`)**: it ranks every block with a full sort, so it gets this block wrong
(3 mismatches on the matching body, and it predicts the *residual*). A scratch copy with the three-qty rule added,
`PACK/scratch/lsim3.py` (a 10-line change right before the `for q in ids:` allocation loop), gives 0 mismatches on every block
of func_801837E8 in both dumps. Over the whole TU dump (1,058 blocks, via `PACK/scratch/scan.py`) the three-qty blocks with
a mismatch drop from 10–11 of 40 to 6, and blocks of any other size stay the same. All 6 left are in func_8017D604, and the
one I read is a separate defect: the simulator gives a qty its suggested register `$30`, which `find_free_reg` never hands out
(eliminable/frame register, `local-alloc.c` find_free_reg `ELIMINABLE_REGS`). **Recommend promoting the three-qty rule into
localalloc_sim.py** (it also applies to the suggested-register pass order, `:1439-1462`, which the simulator also fully sorts).

## (c) Source moves that close it (all score 0)
- **b** (body.c): `p = *(s32 *)(a0 + 0x20); *(u16 *)(p + 0x12) += *(u16 *)(a0 + 0xFC);`
- a: `*(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) += *(u16 *)(a0 + 0xFC);` (no locals)
- e: `p = …; *(u16 *)(p + 0x12) = *(u16 *)(p + 0x12) + *(u16 *)(a0 + 0xFC);` (the long form: only the operand ORDER matters)
- d: the fully nested long form.
Also s1/s3: the same compound with a body-local struct pointer (`p->f12 += s->fFC`) → 0.

## (d) Generator proposal
When a register residual is a permutation inside one basic block that has **exactly three local qtys** (the `.lreg` block
has three `Register N in M` locals) and the first-born qty is the one the target puts in the lowest register, re-order the
block's source so its birth order gives the three-qty rule's result: **inline a hoisted single-use rhs temp (`v = *(T*)(b+K);
… x = x + v;`) into its use, placed after the lhs load (`x += *(T*)(b+K)`)**. More generally, try each of the 3! birth
orders (inline or hoist the temps) and predict the result with the fixed-index rule before compiling.

## (e) What did not work (bytes)
- c: `p` read first, then `v0 = +0xFC`, then the long form → 5 (fc is still born before ld).
- s2: struct pointer with the hoisted `v0` temp (`v0 = s->fFC; p->f12 += v0;`) → 5. The struct does not fix it; the order does.
- free_000 (swap the `+` operands, `v0 + *(p+0x12)`) → 5: the tie moves (sum ties to operand 1), but fc is still born second.
- The sweep's R8/R9 moves (history.txt, best 4) reorder statements but always keep a hoisted fc temp born before the ld.

## (f) Where the method fell short
- Step 1 sends me to `localalloc_sim.py` for a per-block permutation, and for exactly this shape it gives the wrong answer
  (it predicts the residual for the matching body). The fixed-index three-qty order is not in `residual_moves.md`, and no
  simulator has it. Reading `block_alloc` from its sort onward, not only `qty_compare_1`, found it.
- The first move to try came from asking "what would the original `obj->f += self->g` look like": the decompiler's hoisted
  rhs temp was the lever, and the pin was compensating for it.

## (g) Structs question
No. The decision is **evaluation order** (which qty is born second), not the access type. Tested with body-local structs: a
struct pointer with the compound assignment → 0 (s1, s3), and a struct pointer with the hoisted temp → 5 (s2). The
`expr.c:4568-4577` aggregate channel (alias/dependence) plays no part: nothing here reorders a load across a store. Struct
typing would help *indirectly*, though: the natural struct spelling of this line is `self->obj->f12 += self->fFC;`, which is
the matching order, while the cast-soup decompile hoisted the rhs into a temp. So a struct pass makes the right C shape the
obvious one. The candidate types: the actor at `a0` (u16 state `+0x34`, s32 `+0x1C`, `obj *` `+0x20`, s16 `+0xFC`, read with
`lh` for the `< 9` test) and the object at `+0x20` (u16/s16 `+0x12`). But the pin itself did not need structs.
