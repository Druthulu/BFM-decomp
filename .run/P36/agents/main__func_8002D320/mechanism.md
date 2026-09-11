# func_8002D320 (src/800_b_2.c) — S104 agent e23 — CLOSED at 0, ZERO levers (2 pins -> 0), STRUCT spelling

## (a) The residual
Score 34, COUNT 108 vs 102: each of the two `do { } while (i < 8)` loops carries one extra loop register + one extra
step per iteration (loop 1: `addiu s0,s1,-5` beside the walked `p`; loop 2: `addiu s0,s3,68` beside `p` and `mask`),
plus a fourth callee-saved register ($s3, frame 40 vs 32). The `s3->s1`, `s1->s0` pairs are fallout.

## (b) The pass and the decision (PROVEN on the `-dL` dump, scratch/dumps_fin/fin.i.loop, and on bytes)
loop.c strength reduction + global.c order.
- The tree walks a `u8 *p` that is USED DIRECTLY (`*p`, `*p = 0` in loop 1; `*(s32 *)p = 0` in loop 2), so the biv
  is not eliminable and the address givs (`p-1`, `p-0x41`, `p-5`; `p+0x40`, `p+0x3C`) get their own reduced register
  — the extra `addiu` per loop. The target has exactly the registers loop.c produces when the loops walk a `Slot *`:
  - loop 1: every access is a FIELD (`unk45`, `unk44`, `unk04`, `unk40`), none is the biv itself, so
    `biv 72 can be eliminated` / `biv 72 was eliminated`: ONE register (reduced giv r132 = `&s->unk45`, initial
    `D_800A4C6D`) — the target's `s0` with offsets 0/-1/-65/-5 (`record_giv` loop.c:4341, `combine_givs` loop.c:5494,
    biv elimination `maybe_eliminate_biv`).
  - loop 2: `s` itself is the call argument (`Cannot eliminate biv 72: biv used in insn 166`), the three field givs
    combine into r127 = `&s->unk04` — the target's `s1 = D_800A4C28` / `s0 = s1 + 4` pair, both stepped by 72.
  - the constant `0x60000` is hoisted by loop.c (`Insn 38: regno 81 … moved`), so it needs no local.
- Register order (`tools/alloc_table.py fin`): r127 30000, r132 28125 -> `s0` (disjoint); `s` (r72, one pseudo for both
  loops) 20000 -> `s1`; `i` (r73, one pseudo for both loops) 13125 conflicts with `s` in loop 2 -> `s2`; the hoisted
  0x60000 (r81, 882) conflicts with r132 and `i` -> `s1` (pass 0, regs_used_so_far, global.c:949-952). That is the target.
  With the tree's separate `mask` variable no ordering works: `i` 7272 vs `mask` 4242 (8 vs 7 refs over 33 insns),
  `allocno_compare` global.c:587-610 — what the `$18` pin was faking.

## (c) The moves that closed it (PROVEN on bytes)
1. Both loops walk `Slot *s` (the TU's `Slot`, 0x48 bytes, src/800_shared.h:56) with field accesses instead of a `u8 *p`
   with byte offsets; `mask` and `p` deleted; `0x60000` written inline.
2. Loop 1 starts at `(Slot *)(D_800A4C6D - 0x45)` (D_800A4C6D IS `&D_800A4C28[0].unk45`, 0x4C28 + 0x45 = 0x4C6D) so the
   relocation stays `D_800A4C6D+0`. `s = D_800A4C28;` is the natural spelling and compiles to the SAME instructions with
   a `D_800A4C28+0x45` relocation (score 2 OTHER, `addiu s0,s0,69` vs `addiu s0,s0,0` — identical only after LINKING;
   scratch/l1b.c). Use it once D_800A4C6D is retired as a symbol (STRUCTS phase).
3. Loop 2's step order `s++, i++` (as `for (…; s++, i++)` or `s++;` at the body's end); `i++, s++` scores 2 (ORDER).
Byte-neutral: loop 1 `i++, s++` in the header; `func_8003B250(s->unk40, s)` inline or through an `id` temp.

Stepping stone (also 0, scratch/sC.c): loop 1 as a backward `goto` loop over the tree's `u8 *p` (no LOOP_BEG, no loop.c,
loop.c:352-361 — e16's func_80031B7C close) + loop 2 as the struct `for`. A goto-only version of BOTH loops has the
target's instruction count (102) but swaps `i`/`mask` (score 16, scratch/g12.c) — the priorities above.

## (d) GENERATOR PROPOSAL
When a loop walks `u8 *p = D_X` with `p[K]`/`*(T *)(p + K)` accesses and `D_X` sits at a known offset inside a typed
array (`D_X - D_BASE < sizeof(struct)`), rewrite the loop over `STRUCT *s` with field accesses: whether the walked
pointer is ever used DIRECTLY decides loop.c's biv elimination (one register vs two) — a textual generator can emit
both the `s = D_BASE` and the `(STRUCT *)(D_X - off)` starts and score them.

## (e) What did not work (bytes)
- goto loop 1 only: 39; goto loop 2 only: 20; both goto: 16 (i/mask swap in both loops, count right).
- Both goto + every split of i / mask / p into per-loop variables, both declaration orders (16 bodies, scratch/gen.py):
  best 8 (split i + split mask: loop 2 right, loop 1's `i` 4444 still outranks `mask` 588).
- Struct loop 2 with `i++, s++` (header or body): 2 (ORDER). Loop 1 as a real `for` over `u8 *p`: 21 (the extra giv).

## (f) Where the method fell short
The residual reads as "extra instruction per loop"; METHOD's S103 c2 rule ("delete q, write q[i] as p[i+k]") does not
apply (there is no second pointer in loop 1). The e16 goto-loop reading got the COUNT right but not the registers; the
struct spelling was found by noticing that D_800A4C6D = D_800A4C28 + 0x45 (the two loops walk the SAME array) and that
loop 2's target (`s1` walked + `s0 = s1 + 4` walked) is exactly loop.c's "biv used directly + one combined giv" shape.
The `.loop` dump's "biv … can be eliminated" vs "Cannot eliminate biv" lines are the check.

## (g) Structs
YES — this close IS a struct close. Giving the walked pointer the `Slot` type (fields unk04 @4, unk40 @0x40,
unk44 @0x44, unk45 @0x45) changes loop.c's decision: with every access a field offset from `s`, loop 1's biv is never
used directly and is eliminated (one register instead of two), and loop 2's givs combine at `&s->unk04`. The channel is
loop.c's biv elimination, not the `expr.c:4568` aggregate/scalar alias one. The symbol `D_800A4C6D` should become
`D_800A4C28[0].unk45` in the STRUCTS phase (identical only after linking).
