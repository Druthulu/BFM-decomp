# func_80184A68 (ov_SC06_000_jr_8017AE2C.c) — e12, P36 T7 S104

**Score: 9 -> 0.** Levers: 1 `asm` launder -> 0 asm, 1 marked `do { } while (0)` (step 8's allowed-but-marked construct).
NOT a strict plain-C close: every do-while-free spelling I found stays at 9 (see (e)).

## (a) Residual
COUNT, 20 vs 16: the two neighbour-byte accesses `a0[-1]`, `a0[1]` (load and store each) come out ABSOLUTE
(`lui v0; lbu v0,%lo(D_801AECC5-1)(v0)`, `lui at; sb v0,..(at)`, same for +1) where the target addresses them off the
register that already holds `&D_801AECC5` (`lbu v0,-1(a0)`, `sb v1,1(a0)`). Four `lui`s extra.

## (b) Pass and decision (PROVEN on dumps: scratch/dumps_c1 = derived pointers without the barrier, scratch/dumps_body)
Two cse passes, one function (`find_best_addr`, gcc-2.7.2 cse.c:2622):
1. A written `p[-1]` is `(plus (reg p) -1)`: not a REG, so `fold_rtx` runs first (cse.c:2662-2664) and folds it with p's
   known constant into `(const (plus D_801AECC5 -1))` — a CONSTANT address, never replaced again (cse.c:2656).
2. A REG address `(mem (reg q))`, `q = p - 1`, is not folded; the lookup of q's class finds `(plus (reg p) -1)` at the
   SAME address cost as a REG (1: mips.h:2895, mips.c:1652-1653) and a higher rtx cost, which the tie-break prefers
   (cse.c:2711-2721); the symbolic constant (cost 2, mips.c:1631) loses. That gives `-1(a0)`.
3. But if the rewrite in 2. happens in **cse1**, `q` is dead afterwards (flow deletes its set) and **cse2** sees the
   written `(plus (reg p) -1)` again and folds it as in 1. (dumps_c1: `.cse` has `(plus 72 -1)`, `.cse2` has
   `(const (plus D_801AECC5 -1))`). In func_80182560 the same rewrite survives cse2 only because `q` is ALSO the call
   argument, so `q`'s set is still live and its class still holds `(plus p -28)` in cse2.
4. The close: cse1 must NOT see `q`'s equivalence, cse2 must. The only boundary that differs between the two passes is
   `NOTE_INSN_LOOP_END`: `cse_end_of_basic_block` ends the block there only when `! after_loop` (cse.c:8054-8056).
   A `do { q = p - 1; r = p + 1; } while (0);` puts a LOOP_END between the sets and the uses: `.cse` processes
   "block from 2 to 25" then "29 to 57" and leaves `(mem (reg 73))`; `.cse2` processes "2 to 57" as one block and
   rewrites to `(mem (plus (reg 72) -1))`; flow then deletes the dead `q`/`r` sets. Byte-identical.

## (c) Moves
- name the neighbour pointers: `q = p - 1; r = p + 1;` and access `*q`, `*r` instead of `p[-1]`, `p[1]`;
- put their definitions in a `do { … } while (0)` (marked `// !FAKE: do-while — …`), exactly the shape of a
  `#define`-style macro body in the original source. Both variants (definitions inside the do-while, or an empty
  do-while after them, or p's set inside too — scratch/c3, c4, c5) score 0.

## (d) Generator proposal
When a launder/`la` pointer's constant-offset accesses come out absolute (`lui` + `%lo(SYM±k)`) and the target uses
`±k(reg)`: introduce one derived pointer per offset (`q = p + k`, access `*q`); if the derived pointer has another
live use (a call argument) that alone closes it, else wrap the derived-pointer definitions in a marked
`do { } while (0)` so cse1 stops at LOOP_END and only cse2 does the REG->`reg+k` rewrite.

## (e) What did not work (bytes)
- derived pointers alone (scratch/c1 top-level, c2 declared inside the if): 9 — cse1 rewrites, q dies, cse2 folds.
- body_free.c and the sweep's R7/R9 moves: 9 (they keep `p[k]`, which fold_rtx folds in either pass).
- A structured/goto rewrite does not apply: a CODE_LABEL ends the block in BOTH passes; only LOOP_END differs.
- I found no plain-C construct other than a loop that puts LOOP_END in the insn stream; an always-false/always-true
  test that cse1 folds away (so jump deletes a label before cse2) would be the refused invented-condition kind.

## (f) Method
Counting first (20 vs 16, four `lui`s) + reading func_80182560's close gave the idea; the `.cse` vs `.cse2` dumps were
decisive — the residual alone cannot show that the fold happens in the SECOND cse pass. The sibling func_801851CC
(same shape, `-=`) is FOLDED in the target (absolute CC4/CC6), which fits: the original spelled the two differently.

## (g) Structs
A struct over the three bytes (`struct { u8 b, g, r; } D_801AECC4`) does not help: field accesses on a global are
constant addresses (cse.c:2656), and through a pointer `s = &D_801AECC4` the base register would hold CC4 with offsets
0/1/2 — the target's base is CC5 with -1/0/+1. The deciding fact is the cse1/cse2 boundary, not aliasing, so the
expr.c:4568 aggregate channel is not in play. Not tested on bytes.
