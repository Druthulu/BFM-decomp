# func_800314DC (src/800_b_2.c) — S104 agent e23 — CLOSED at 0, ZERO levers (2 pins + the dead `pad[2]` -> 0)

## (a) The residual
Score 15, REG-caller, 135 vs 135: two independent `$v0`/`$v1` swaps — (1) `base = (t & 0xFF00) + (s8)t*2` lands in
`$v1` (tied to the `t & 0xFF00` operand) where the target has `$v0` (`addu v0,v1,v0`); (2) in the lerp arm every
value is mirrored: mine keeps `256 - f` in `$v0` and the D_8006AB30 load / product / sum / result in `$v1`, the target
the reverse. Count and order already identical.

## (b) The passes and the decisions (PROVEN on the `.lreg`/`.greg` dumps, scratch/dumps_free, dumps_ss, dumps_fin)
1. local-alloc's tie (`block_alloc`, local-alloc.c:1123ff; `combine_regs` local-alloc.c:1722): the addu's output is tied
   to its FIRST dying input, `t & 0xFF00` (q11 = r161 + r76 -> `$v1`, `tools/localalloc_sim.py`). The target's output is
   NOT tied to operand 1. `combine_regs` refuses when the output already has a quantity or is not a local
   (`reg_qty[sreg] >= -1`, local-alloc.c ~1742). Reusing `t` as the sum's destination makes `t` die in TWO places
   (`.lreg`: "Register 76 … dies in 2 places") -> refused by local-alloc (local-alloc.c:472) -> allocated by global.c,
   which gives it the lowest free register, `$v0` (`.greg` dispositions: `76 in 2`), while the `& 0xFF00` temp keeps
   `$v1`.
2. local-alloc's quantity order in the lerp block (`qty_compare_1`, local-alloc.c:1598): free text
   q3 {256, 256-f} 20000 > q4 (D_8006AB32 load) 10000 > q1 {q, product, sum} 7500 -> q3 takes `$v0`. With the result
   stored IN the arm (`e->unk14 = … >> 8;`) the `srl` result becomes a block-local tied into q1 (8 refs, 13333 > q4);
   with the product+sum written as `q = A * B; q += C * D;` q1 reaches the target order (q1 `$v0`, q3/q4 `$v1`, idx `$a0`,
   f `$a1`), and jump2's cross-jump re-merges the two arms' identical `sh v0,20(a3)` tails into the target's one store
   (`li v0,0x3FFF` in the `j`'s delay slot). One-expression product: 16; `q = load; q = q * w;`: 21 (COUNT).
3. The 8-byte frame (`vars= 8`, no `$sp` reference): a pointer written as two statements (`r = D_80073140;
   r += p->unk0A; … = *r;`) whose uses all fold into one address: `.lreg` "Register 74 used 4 times … ST_REGS or none",
   no disposition in `.greg`, so reload gives it a stack slot (reload1.c:2331-2352; S103 c35 / d25, read in reverse:
   here the TARGET has the slot). The tree's dead `s32 pad[2];` was faking exactly that slot.

## (c) The moves that closed it (PROVEN on bytes; each necessary)
1. `base` deleted; `t` reused: `t = h; t = (t & 0xFF00) + ((s8)t * 2); e->unk18 = h; t -= 0x3C00; d = p->unk24; d -= t;`
   (with the lerp fixed: 3 -> 0; `base` as the sum's own variable in any of 9 orders: 3..12).
2. The result stored in each arm instead of through `res`; the lerp as
   `q = D_8006AB30[d >> 8] * (0x100 - (d & 0xFF)); q += D_8006AB32[d >> 8] * (d & 0xFF); e->unk14 = q >> 8;`
   (15 -> 3 alone).
3. `s32 pad[2];` deleted; `e->unk00 = D_80073140[p->unk0A];` -> `r = D_80073140; r += p->unk0A; e->unk00 = *r;`
   (the same slot from the lerp table pointer `tb = D_8006AB30; tb += d >> 8; q = *tb * …` also scores 0, scratch/f5.c;
   keeping the tree's `pad[2]` instead also scores 0, scratch/p0.c). `base`/`res` and every stale pin comment dropped.

## (d) GENERATOR PROPOSAL
Two rules: (i) when an arithmetic result's register equals its FIRST operand's in mine but the SECOND operand's in the
target, reassign the result into a local that is already dead at that point (reuse the variable whose last use is the
other operand's producer), so the output dies in two places and global.c allocates it; (ii) when a value that joins
two if/else arms is only stored once after the join, move the store into both arms (cross-jump re-merges the tails
after reload) — this makes the result block-local and adds it to its producer's quantity.

## (e) What did not work (bytes)
- Merging `res` into `base`, `q`, or `t` (15 / 54 / 13), and into `base` with `q` too (22): still global, preference
  from the first operand (global.c `set_preference`) keeps `$v1`.
- The whole-lerp one-expression store (16), `w = 0x100 - f` named first (26), `f`/`i` named (17-19), `q *= w; q += …`
  with the load separate (21, COUNT).
- `base` spellings with the tie intact (b1-b9: 3..12), `d = p->unk24 - t;` in one statement with the reuse (10),
  `e = D_800A4C28; e += p->unk51;` for the frame (5), no frame at all (2), `B12 *b` two-step (12).

## (f) Where the method fell short
The residual printed one `v1->v0 x13, v0->v1 x8` permutation; it was two unrelated decisions in two blocks
(local-alloc tie in one, `qty_compare_1` order in the other) — `tools/localalloc_sim.py` per block separated them in
two runs. The allocation table alone (global priorities) says nothing about either. d14's "rename a late local to an
earlier-dead one" is the family of move 1; it was the per-block simulator's "tied to r161" line that pointed at it.

## (g) Structs
No. `Obj`/`Slot`/`B12` are already structs here; the decisions are local-alloc's tie and quantity order and reload's
slot for a folded pointer — none is an aggregate/scalar alias question. (Writing the lerp tables as one `u16 [][2]`
struct array would change the relocations of D_8006AB32 — identical only after linking — and not the allocation.)
