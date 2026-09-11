# func_8017F368 (ov_SC03_001_jr_8017AE2C.c) — d16, P36 S104

**Result: score 0, ZERO levers** (the tree has 2 NEEDED pins: `zr` $0 and `dst` $4; lever count 2 → 0). No asm, no pin,
no added volatile, no do-while, no dead initialiser. The class's four other copies close with the same text (table in
`scratch/copies.md`). Starting point: body_free.c at 51 (the free sweep's best was 40; not used).

## (a) The residual in one sentence
Two independent defects: (1) COUNT +3: each vertex loop kept TWO registers for the destination (the `dst` biv for
`dst[0]` + a reduced giv for `dst[1]/dst[2]`, one extra `addiu` per loop plus a prologue `addiu`), where the target walks
ONE register at offsets 0/2/4; (2) `attr & 0xFF` lived in ONE pseudo ($s1) where the target keeps it in $a0 for the
first table index and copies it to $s1 (`move s1,a0` in the `bne` delay slot) for the post-call one; and, once (1) was
fixed, (3) the source pointer biv and its reduced giv came out $a1/$a2 swapped.

## (b) Passes and decisions (all proven on bytes by the moves below)
1. **loop.c strength reduction.** A walked pointer `dst` stepped by 4 is a biv; `dst[0]` is a bare deref of it (not a giv)
   so the biv cannot be eliminated; `dst+2`/`dst+4` are givs of it, combined (`combine_givs`, loop.c:5494) into a new
   reduced register → two registers. Written as `va[i].vx/.vy/.vz`, all three addresses are DEST_ADDR givs of the counter
   `i` with mult 8 (`record_giv` loop.c:4341) that `combine_givs` folds into ONE reduced register with offsets 0/2/4 —
   the target. `.loop` dump (scratch/dumps_sf): "giv at 252 combined with giv at 260 … reduced to (reg:SI 332)". The
   tree's `$4` pin on `dst` faked exactly this (a hard reg is not a biv). The source tables are the opposite case: the
   target's two-register `p1`/`p2` shape is what loop.c makes by itself from `p1[0], p1[1], p1[2]` with `p1 += 4`
   ("Cannot eliminate biv 81: biv used in insn 256"; "giv at 272 combined with giv at 288") — the tree's hand-written
   `p2 = p1 + 2` / `p2[-1]` was re-creating loop.c's output in the source.
2. **cse copy canonicalisation.** With `s32 type2 = type`, the copy is a REG→REG set: `make_regs_eqv` (cse.c:846-862)
   makes `type2` the class head because it lives beyond the cse block and longer than `type`, so every later use —
   including the first loop's `sll`, reached through cse's followed jump — is rewritten to `type2`, and the
   `(set REG0 REG1)` swap (cse.c:7440-7474) retargets the `andi` to it. One pseudo → $s1 everywhere. With **`u8 type2`**
   the copy is `(set (reg:QI 79) (subreg:QI (reg:SI 78) 0))` — a SUBREG source, no equivalence, both pseudos survive:
   `type` (short-lived → $a0), `type2` (crosses calls → $s1). The later `zero_extend:SI (reg:QI 79)` costs nothing: combine
   rewrites it to `(ashift (subreg:SI (reg/v:QI 79) 0) 5)` (`.combine` insn 228; expand_compound_operation combine.c:4788,
   the AND dropped on nonzero_bits from `reg_nonzero_bits`, combine.c:6920 — the last step read, not single-stepped).
   The copy placed BEFORE the `if` lands in the `bne` delay slot exactly as in the target (fill from the branch's own
   block); placed after the `p1 =` line it stays after the `addu` (scored 17).
3. **global.c allocation order** (`allocno_compare`, global.c:604-610). With one `p1` reused by both loops, pseudo r80 had
   16 refs / live 44 → priority floor_log2(16)·16/44 = 14545, ahead of the reduced source givs r329/r333 (13500), so p1
   took $a1 and the giv $a2 (target: the reverse). One pointer per loop (`p1`, `p2`) gives each 8 refs over ~22 insns
   → floor_log2(8)·8/22 ≈ 10909 < 13500: the giv is allocated first ($a1), the pointer next ($a2), `i` last ($a3).
   (Table: `tools/alloc_table.py c7u8 func_8017F368 PACK/scratch`.)

## (c) The moves (one line each)
1. `u16 va[16]`/`vb[16]` + walked `dst` → `SVECTOR va[4], vb[4]` indexed `va[i].vx/.vy/.vz` (51 → 22; u16[4][4] same).
2. Drop the hand-made `p2 = p1 + 2`/`p2[-1]`: read `p1[0], p1[1], p1[2]`; loop as `for (i = 0; i < 4; i++, p1 += 4)`
   (i++ before the pointer step, same LUID order as the tree's while) (22 → 18).
3. `type2 = type + zr` ($0 pin) → `u8 type2; … type2 = type;` before the `if` (18 → 14).
4. One source pointer per loop: `p1` for the outer quad, `p2` for the inner (14 → 0).

## (d) Generator proposals
- **R-giv (new):** when a loop walks a pointer `d` over a LOCAL ARRAY (`d = arr; … d[0], d[k]…; d += n`) and the residual
  is COUNT +1 per loop with one extra `addiu` step and a prologue `addiu`, rewrite the walk as `arr[i]` indexed by the
  loop counter (struct-typed if the stride matches a known struct); conversely, when the target shows TWO registers for
  one source (offset 0 in one, the rest in another), un-hand-write any `q = p + k` twin and read `p[k]` directly.
- **R-width-copy:** when two pseudos hold one value in the target (a `move sK,aN` copy right after the producer) and the
  lever is `y = x + zr`, declare `y` with the narrowest width the value's range proves (`u8` for `& 0xFF`, `u16` for
  `& 0xFFFF`), no zero term.
- **R-split-reuse:** a pointer variable reused by two sibling loops whose reduced giv lands in the neighbour register →
  one variable per loop (halves refs and live length; arithmetic on the alloc table predicts it).

## (e) What did not work (bytes)
- walked `SVECTOR *dst` with `dst->vx…; dst++` (scratch/neg_structptr.c): 48 — the struct type is NOT the channel,
  indexing by the counter is.
- `for (i = 0; i < 4; i++) { …; p1 += 4; }` (pointer step after i++ in the body): 22 — the step order matters.
- keeping the explicit `p2 = p1 + 2` twin with `va[i]`: 22 (a0/a1 swap).
- `type2` as `s8`: 22–25 (sign extension adds an insn); `type2 = attr` (from attr): 12; `u8 type; s32 type2`: 4;
  both u8: 15; `s32 type2 = type`: 15 (after the `if`), 17 (after `p1 =`), 18 (before the `if`). `u16`/`s16 type2`
  score the same as `u8` (14 at that stage) — any narrower-than-SI width breaks the REG→REG copy; `u8` is the one the
  `& 0xFF` range proves.
- removing the dead `pad0[16]`: 147 (frame layout — not a lever, left as the tree has it).

## (f) Where the method fell short
Nothing blocked. The allocation table settled move 4 by arithmetic in one step. The one gap: step 3's list has the
"second walked pointer → `p[i+k]`" entry (S103 c2) but not its mirror for a DESTINATION array: a hard-reg pin on a
walked pointer (`register T *dst __asm__("$4")`) whose header says "a hard reg is not a biv" is the signature for
"index the array by the loop counter". Worth one line in the method.

## (g) Structs answer
Giving `va`/`vb` the `SVECTOR` type reads well and matches, but the bytes do not depend on it: `u16 va[4][4]` matches
too and a walked `SVECTOR *` does not (48). What decides is ARRAY INDEXING by the counter (address = giv of `i`,
loop.c) versus a walked pointer (a biv). The `type2` lever is a width question, not a struct question. So for this
class: structs make the text honest (`.vx/.vy/.vz`, the SVECTOR the GTE calls expect), the counter-indexing is the move.
No `expr.c:4568` aggregate-vs-scalar channel is involved.
